#include "stdafx.h"
#include "DeuTranslate.h"

#include <queue>
#include <vector>
#include <map>

#include <stdio.h>
#include <io.h>
#include "DeuDef.h"

clock_t r_start;
clock_t r_end;
#define START_TIME 	r_start = clock();
#define END_TIME	r_end	  = clock();	

#define SEC_PER_CLOCKS 0.001

#define LOG_USED_TIME \
	int time_i=(r_end-r_start)*SEC_PER_CLOCKS;\
	char * time = (char *)malloc(20);\
	itoa(time_i,time,10);\
	LOG("总共用时(秒):",time,100);\
	free(time);

#define DISTANCE(a,b) sqrt((a)*(a)+(b)*(b))

static double dNodata;
static bool bFlagNodata = false; //false = 0;true > 0

//add by chenyong 2014-7-2
static bool IsExistNodata = false;

OGRSpatialReference* SetSRS(CDeuSpatialReference* m_SRS);

void BuildOverviews(const char *  pFileName);

void ComputeStatistics(const char * pszFileName);

void SetNoDataValue( GDALDataset * poDS,GDALDataset * poDSOut);
void SetNoDataValueDEM(GDALDataset * poDS, GDALDataset* poDSOut);

void Resampling_Nearest(double *Pt,int nImgSizeX , int nImgSizeY ,GDALDataset *poDS,/*CDeuBuffer &buf,*/void *GrayVal);

void Resampling_Bilinear(double *Pt,int nImgSizeX , int nImgSizeY ,GDALDataset *poDS,/*CDeuBuffer &buf,*/void *GrayVal);

void Resampling_Bicubic(double *Pt,int nImgSizeX , int nImgSizeY ,GDALDataset *poDS,/*CDeuBuffer &buf,*/void *GrayVal);

unsigned long ReadNumFromBuf( void * pScanBlock , unsigned int nByteSize ,unsigned long *ulResult);

void WriteNumToBuf( double dbVal, void* GrayVal, unsigned int nByteSize );

double GetRandomDetal(double min_ , double max_);

//add by chenyong 2013-7-5
void Resampling_Nearest_DEM(double *Pt,int nImgSizeX , int nImgSizeY ,GDALDataset *poDS,/*CDeuBuffer &buf,*/void *GrayVal);

void Resampling_Bilinear_DEM(double *Pt,int nImgSizeX , int nImgSizeY ,GDALDataset *poDS,/*CDeuBuffer &buf,*/void *GrayVal);

void Resampling_Bicubic_DEM(double *Pt,int nImgSizeX , int nImgSizeY ,GDALDataset *poDS,/*CDeuBuffer &buf,*/void *GrayVal);

BOOL CDeuRasterTrans::FileFolderExists(CString filename) 
{ 
	DWORD attr;   

	attr = GetFileAttributes(filename);   
	return (attr != (DWORD)(-1) ) && ( attr & FILE_ATTRIBUTE_DIRECTORY);   
} 

CDeuRasterTrans::CDeuRasterTrans()
{
	m_hwnd = NULL;
	m_Para	=	NULL ;	
	m_InvPara = NULL ;
	_callback = NULL;

	m_bSpecifiedFrame = false ;
}

CDeuRasterTrans::~CDeuRasterTrans()
{
}

void CDeuRasterTrans::get_SevenParams(CSevenParams& Val) const
{
	return; 
}

void CDeuRasterTrans::putref_SevenParams(const CSevenParams& newVal)
{
	return;
}

void CDeuRasterTrans::get_DeuEllipse(CDeuEllipse& Val) const
{
	Val = m_ellipse;
}

void CDeuRasterTrans::putref_DeuEllipse(const CDeuEllipse& newVal)
{
	m_ellipse = newVal;

	m_ellipse.get_Major(m_src_a);	
	m_ellipse.get_Flatening(m_src_f);
	m_ellipse.get_Centrol_Long(m_src_from_greenwich);
	m_ellipse.get_False_E(m_src_false_east);

	m_srcPJ = (PJ*)init_PJ(m_src_a,m_src_f);

	m_srcPJ->false_e = m_src_false_east;
	m_srcPJ->from_greenwich = m_src_from_greenwich;
}

void CDeuRasterTrans::get_DeuUnits(CDeuUnits& Val) const
{
	Val = m_units;
}

void CDeuRasterTrans::putref_DeuUnits(const CDeuUnits& newVal)
{
	m_units = newVal;
}

void CDeuRasterTrans::get_DeuCoordType(CDeuCoordType& Val) const
{
	Val = m_coordtype;
}
	
void CDeuRasterTrans::putref_DeuCoordType(const CDeuCoordType& newVal)
{
	m_coordtype = newVal;
}

void CDeuRasterTrans::get_DeuDestEllipse(CDeuEllipse& Val) const
{
	Val = m_des_ellipse;
}
	
void CDeuRasterTrans::putref_DeuDestEllipse(const CDeuEllipse& newVal)
{
	m_des_ellipse = newVal;

	m_des_ellipse.get_Major(m_des_a);	
	m_des_ellipse.get_Flatening(m_des_f);
	m_des_ellipse.get_Centrol_Long(m_des_from_greenwich);
	m_des_ellipse.get_False_E(m_des_false_east);

	m_desPJ = (PJ*)init_PJ(m_des_a,m_des_f);
	
	m_desPJ->false_e = m_des_false_east;
	m_desPJ->from_greenwich = m_des_from_greenwich;
}

void CDeuRasterTrans::get_ConnPool(CDeuConnPool& Val) const
{
	Val = m_ConnPool;
}

void CDeuRasterTrans::putref_ConnPool(const CDeuConnPool& newVal)
{
	m_ConnPool = newVal;
}

void CDeuRasterTrans::get_TransModel(short& pVal) const
{
	pVal = m_TransModel;
}

void CDeuRasterTrans::put_TransModel(short newVal)
{
	m_TransModel = newVal;
}

void CDeuRasterTrans::get_Resampling(short& pVal) const
{
	pVal = m_Resampling;
}

void CDeuRasterTrans::put_Resampling(short newVal)
{
	m_Resampling = newVal;
}

void CDeuRasterTrans::get_Param(double**  pVal) const
{
	*pVal = m_Para;
}

void CDeuRasterTrans::putref_Param(double* newVal)
{
	m_Para = newVal;
}

void CDeuRasterTrans::get_InvParam(double** pVal) const
{
	*pVal = m_InvPara;
}

void CDeuRasterTrans::putref_InvParam(double* newVal)
{
	m_InvPara = newVal;
}

void CDeuRasterTrans::get_DeuSRS(CDeuSpatialReference& Val) const
{
	Val = m_SRS;
}

void CDeuRasterTrans::putref_DeuSRS(const CDeuSpatialReference& newVal)
{
	m_SRS = newVal;
}

OGRSpatialReference* SetSRS(CDeuSpatialReference* m_SRS)
{		
	OGRSpatialReference* poRSR= new OGRSpatialReference();
	if(m_SRS==NULL)
	{
		LOGSTR("error:没有设置空间参考。");				
	}
	else
	{
		if(poRSR)
		{
			//设置投影坐标系
			BOOL  vb_IsProj =TRUE  ;
			CString ProjName ;
			CString Proj ;

			//设置大地坐标系
			CString dfGeogName;
			CString dfDatum;
			CString dfEllipName;
			double dfSemiMajor;
			double dfInvFlattening;

			m_SRS->get_IsProject(vb_IsProj);
			if( vb_IsProj != FALSE )
			{
				//设置投影坐标系名称					
				m_SRS->get_ProjeCS(ProjName);
				
				//if( ProjName )
				poRSR->SetProjCS((LPCSTR)_bstr_t(ProjName));

				//设置投影方法
				m_SRS->get_Projection(Proj);
				//if( Proj )
				poRSR->SetProjection(Proj.GetBuffer());

				//--------------------------------------------------------------------------------
				double *szProjparms = NULL;
				int iProjCount;
				m_SRS->get_ProjParm(iProjCount,&szProjparms);

				//设置参数：	PARAMETER["False_Easting",500000.0],
				poRSR->SetProjParm("False_Easting",szProjparms[0]);

				//设置参数：	PARAMETER["False_Northing",0.0],
				poRSR->SetProjParm("False_Northing",szProjparms[1]);

				//设置参数：	PARAMETER["Central_Meridian",118.5],
				poRSR->SetProjParm("Central_Meridian",szProjparms[2]);

				//设置参数：	PARAMETER["Scale_Factor",1.0],
				poRSR->SetProjParm("Scale_Factor",szProjparms[3]);

				//设置参数：	PARAMETER["Latitude_Of_Origin",0.0],
				poRSR->SetProjParm("Latitude_Of_Origin",szProjparms[4]);
			}

			//if(poRSR->IsGeographic())
			//{
			m_SRS->get_GeogCS(dfGeogName , dfDatum, dfEllipName, dfSemiMajor, dfInvFlattening);
			poRSR->SetGeogCS((LPCSTR)_bstr_t(dfGeogName),(LPCSTR)_bstr_t(dfDatum),(LPCSTR)_bstr_t(dfEllipName),dfSemiMajor,dfInvFlattening);
			//}

			CString dfLinearUnits;
			double fLinearUnits;
			char *szLinearUnits;

			fLinearUnits=poRSR->GetLinearUnits(&szLinearUnits);
			//int ret_cmp= strcmp(szLinearUnits,"unknown");
			//if(ret_cmp!=0)
			//{
			m_SRS->get_LinearUnit(dfLinearUnits);
			poRSR->SetLinearUnits(dfLinearUnits.GetBuffer(),fLinearUnits);
			//}

			CString dfAngularUnits;
			double fAngularUnit;
			char *szAngularUnit;

			fAngularUnit=poRSR->GetAngularUnits(&szAngularUnit);
			//ret_cmp= strcmp(szAngularUnit,"unknown");
			//if(ret_cmp!=0)
			//{
			m_SRS->get_AngularUnit(dfAngularUnits);
			poRSR->SetAngularUnits(dfAngularUnits.GetBuffer(),fAngularUnit);
			//}					
		}
	}

	return poRSR;
}

void BuildOverviews(const char * pszFileName)
{
	GDALDataset * poDS;
	poDS = (GDALDataset *) GDALOpen(pszFileName, GA_ReadOnly );
	if( poDS == NULL )
	{		
		return ;
	} 

	int anOverviewList[3] = { 2, 4, 8 };
	int nBandCount = poDS->GetRasterCount();

	CPLSetConfigOption("USE_RRD","YES"); 

	poDS->BuildOverviews( "NEAREST" , nBandCount, anOverviewList, 0, NULL ,NULL, NULL);

	GDALClose( (GDALDatasetH) poDS );
}

GDALProgressFunc _ProgressFunc;
void ComputeStatistics(const char * pszFileName)
{
	GDALDataset * poDS;
	poDS = (GDALDataset *) GDALOpen(pszFileName, GA_ReadOnly );
	if( poDS == NULL )
	{		
		return ;
	} 

	int    nBandCount = poDS->GetRasterCount();
	char*  szLog = (char*)/*CPLMalloc*/malloc( sizeof(char) * 200 );
	int    bApproxOK = 0;
	double pdfMin = 0;
	double pdfMax = 0;
	double pdfMean = 0;
	double pdfStdDev = 0;
	void*  pProgressData = NULL;

	for(int i = 0; i < nBandCount ; i++)
	{
		GDALRasterBand* poBand = poDS->GetRasterBand(i+1);
		poBand->ComputeStatistics( bApproxOK, &pdfMin,&pdfMax,&pdfMean,&pdfStdDev, _ProgressFunc, pProgressData);
	}

	free(szLog);

	GDALClose( (GDALDatasetH) poDS );
}

void SetNoDataValue( GDALDataset * poDS,GDALDataset * poDSOut)
{
	//int nBandCount = poDS->GetRasterCount();
	//int *bSuccessed = (int*)malloc( sizeof(int) * nBandCount ); 
	//char * szLog = (char*)malloc(sizeof(char) * 200);

	//add by chenyong 2014-6-11
	GDALRasterBand* pBand = poDS->GetRasterBand(1);
	unsigned int iColorDataType = GDALGetRasterDataType( pBand );
	unsigned int iDataTypeSize = GDALGetDataTypeSize( (GDALDataType)iColorDataType );
	int nByteSize = iDataTypeSize / 8 ;

	switch (nByteSize)
	{
	case 1:
		dNodata = 255;
		break;

	case 2:
		dNodata = 65535;
		break;

	case 4:
		break;

	case 8:
		break;

	default:
		dNodata = 0;
	}

	//for(int i = 0; i < nBandCount ; i++)
	//{
	//	GDALRasterBand* poBand = poDS->GetRasterBand(i+1);
	//	GDALRasterBand* poBandOut = poDSOut->GetRasterBand(i+1);
	//	double dbNoDataValue = GDALGetRasterNoDataValue( poBand , bSuccessed+i );
	//	
	//	//GDALSetRasterNoDataValue( poBandOut ,0); 
	//	if(bSuccessed[i])
	//	{
	//		GDALSetRasterNoDataValue( poBandOut , dbNoDataValue );
	//		sprintf( szLog , "NoDataValue=%lf, bSuccessed=%d",dbNoDataValue,bSuccessed[i]);
	//		LOGSTR(szLog);

	//		dNodata = dbNoDataValue;
	//		/*if (dNodata > 0)
	//		{
	//			bFlagNodata = true;
	//		}*/
	//	}
	//	else
	//	{
	//		LOGSTR("没有设置NoDataValue");
	//		GDALSetRasterNoDataValue(poBandOut, dNodata);
	//	}
	//}

	pBand = poDS->GetRasterBand(1);
	GDALRasterBand* poBandOut = poDSOut->GetRasterBand(1);
	int				iSuccessed = 0;
	double			dbNoDataValue(0);
	char			szLog[128] = {0};

	if (NULL != pBand && NULL != poBandOut)
	{
		dbNoDataValue = pBand->GetNoDataValue(&iSuccessed);

		//若iSuccessed > 0,则表明NoDataValue值存在，否则不存在
		if (iSuccessed)
		{
			//表明获取的nodatavalue异常
			/*if (dbNoDataValue < 0)
			{
				sprintf( szLog , "获取原影像文件中NoDataValue值异常，且NoDataValue=%lf",dbNoDataValue);
				LOGSTR(szLog);
			}
			else
			{*/
				//dNodata = dbNoDataValue;
				IsExistNodata = true;//说明原始影像中存在正常的nodatavalue

				//add by chenyong 2014-7-30
				if (dbNoDataValue < dNodata)
				{
					dNodata = dbNoDataValue;
				}
			//}	
		}
		else
		{
			LOGSTR("原影像文件中没有设置NoDataValue");
		}

		int iBandCount = poDS->GetRasterCount();
		for (int i = 1; i <= iBandCount; ++i)
		{
			poDSOut->GetRasterBand(i)->SetNoDataValue(dNodata);
		}

		if (dNodata > 0)
		{
			bFlagNodata = true;
		}
	}
	
	//free( bSuccessed );
	//free( szLog );

	return;
}

void Resampling_Nearest(double *Pt,int nImgSizeX , int nImgSizeY ,GDALDataset *poDS ,/* CDeuBuffer & buf ,*/void *GrayVal)
{
	//获得目标影像的像点的坐标
	double geo_src_x = Pt[0];
    double geo_src_y = Pt[1];
	double geo_src_z = Pt[2];

	//获得图像的颜色类型	
	//unsigned int iColorDataType =  GDALGetRasterDataType( poBand );
	//unsigned int iDataTypeSize = GDALGetDataTypeSize( (GDALDataType)iColorDataType );

	//获得影像像素字长
	int	nBandCount=poDS->GetRasterCount();
	GDALRasterBand* poBand = poDS->GetRasterBand(1);	
	unsigned int iColorDataType = GDALGetRasterDataType( poBand );
	unsigned int iDataTypeSize = GDALGetDataTypeSize( (GDALDataType)iColorDataType );

	//像素的位长转换成字节长度
	int nByteSize = iDataTypeSize / 8 ;        //删除缓冲区以及多波段转换实现的修改
	//int nByteSize = buf.nByteSize;

	//////////////////////////////////////////////////////////////////////////
	//全文件的原点
	//adfGeoTransform[0] y,东方向或经度，为了容易分辨，所有的X为横轴坐标，所有的Y为纵轴坐标
	//adfGeoTransform[1] Pix_to_X 分辨率
	//adfGeoTransform[2] 0
	//adfGeoTransform[3] x,北方向或纬度，为了容易分辨，所有的X为横轴坐标，所有的Y为纵轴坐标
	//adfGeoTransform[4] 0
	//adfGeoTransform[5] Pix_to_Y 分辨率
	double          adfGeoTransform[6]; /*= {
											118.10998630485409,
											6.363636363636e-006,
											0,
											24.565393366167626,
											0,
											-6.363636363636e-006
													};*/
	poDS->GetGeoTransform(adfGeoTransform);

	//X方向，Y方向分分辨率
	double Pix_to_X = adfGeoTransform[1];
	double Pix_to_Y = adfGeoTransform[5];

	//顶点坐标
	double GeoX =  adfGeoTransform[0];
	double GeoY =  adfGeoTransform[3];

	//找到像素点所在1阶区域
	//获取源影像中的行列位置（双精度）
	double dbPixX , dbPixY;//用double表示的像素值 
	dbPixX = ( geo_src_x - GeoX ) / Pix_to_X ;
	dbPixY = ( geo_src_y - GeoY ) / Pix_to_Y ;

	//最近的整数行列(能过加0.5)
	int iEnvPix[2];
	iEnvPix[0] = (int)(dbPixX+0.5);
	iEnvPix[1] = (int)(dbPixY+0.5);
	
	//加权算像素值
	//char *pScanBlock = (char *) /*CPLMalloc*/malloc( nByteSize * 64 * 64 );
	//unsigned char pScanBlock [/*nByteSize*/24];
	//memset( pScanBlock , 0  , 24);
	/*unsigned char nodatavalue = (unsigned char)dNodata;
	
	for (int k = 0; k < nBandCount; ++k)
	{
		memcpy(pScanBlock+k, &nodatavalue, sizeof(nodatavalue));
	}*/
	
	unsigned char* pScanBlock = new unsigned char[nByteSize*nBandCount];
	std::memset(pScanBlock, 0, sizeof(unsigned char)*nBandCount*nByteSize);
	unsigned char* pChar = NULL;
	unsigned short* pShort = NULL;
	unsigned float* pFloat = NULL;
	unsigned double* pDouble = NULL;
	unsigned char	cNodataValue = 0;
	unsigned short	sNodataValue = 0;
	unsigned float	fNodataValue = 0;
	unsigned double dNodataValue = 0;

	//适用多字节长度
	switch (nByteSize)
	{
	case 1:
		cNodataValue = static_cast<unsigned char>(dNodata);
		pChar = pScanBlock;
		for (int i = 0; i < nBandCount; ++i)
		{
			pChar[i] = cNodataValue;
		}
		break;

	case 2:
		sNodataValue = static_cast<unsigned short>(dNodata);
		pShort = (unsigned short*)pScanBlock;
		for (int i = 0; i < nBandCount; ++i)
		{
			pShort[i] = sNodataValue;
		}
		break;

	case 4:
		fNodataValue = static_cast<unsigned float>(dNodata);
		pFloat = (unsigned float*)pScanBlock;
		for (int i = 0; i < nBandCount; ++i)
		{
			pFloat[i] = fNodataValue;
		}
		break;

	case 8:
		dNodataValue = static_cast<unsigned double>(dNodata);
		pDouble = (unsigned double*)pScanBlock;
		for (int i = 0; i < nBandCount; ++i)
		{
			pDouble[i] = dNodataValue;
		}
		break;
	}

	//int iBandMap[] = {3,2,1};
	int* _pBandMap = new int[nBandCount];
	std::memset(_pBandMap, 0, nBandCount*sizeof(int));

	for (int i = nBandCount; i > 0; --i)
	{
		_pBandMap[nBandCount-i] = i; 
	}

	if( iEnvPix[0] >= 0 && iEnvPix[0] < nImgSizeX && iEnvPix[1] >= 0 && iEnvPix[1] < nImgSizeY)
	{
		CPLErr err = poDS->RasterIO(GF_Read
								  , iEnvPix[0]
		                          , iEnvPix[1]
		                          , 1
								  , 1
								  , pScanBlock
								  , 1
							 	  , 1
								  , (GDALDataType)iColorDataType
								  , nBandCount
								  , /*iBandMap*/_pBandMap
								  , nBandCount*nByteSize
								  , nBandCount*nByteSize
								  , nByteSize);

		//像素长度为一个字节且要特殊处理,防止正常像素点255变成nodatavalue
		if (!IsExistNodata && nByteSize == 1 && dNodata - 255 < 1E-6)
		{
			for (int i = 0; i < nBandCount; ++i)
			{
				if (pScanBlock[i] == 255)
				{
					pScanBlock[i] = 254;
				}
			}
		}
	}

	memcpy(GrayVal, pScanBlock, nByteSize*nBandCount);

	delete[] pScanBlock;
	delete[] _pBandMap;

	return ;
}

/*
void Resampling_Bilinear(double *Pt,int nImgSizeX , int nImgSizeY ,GDALDataset *poDS, void *GrayVal)
{
	double									geo_src_x = Pt[0];
    double									geo_src_y = Pt[1];
	double									geo_src_z = 0;
	double									dbEnvPix[8] = {0};
	int										iEnvPix[8] = {0};
	double									arrDis[4] = {0};
	double									AllDis = 0;
	double									arrWeight[4] = {0};
	double									dbVal = 0;
	double									pScanBlock_i = 0;


	//获得图像的颜色类型	
	
	int	nBandCount=poDS->GetRasterCount();
	GDALRasterBand* poBand = poDS->GetRasterBand(1);	
	unsigned int iColorDataType = GDALGetRasterDataType( poBand );
	unsigned int iDataTypeSize = GDALGetDataTypeSize( (GDALDataType)iColorDataType );
	int nByteSize = iDataTypeSize / 8 ;        //删除缓冲区以及多波段转换实现的修改
	unsigned char							pScanBlock [4][64];

	memset( pScanBlock[0] , 0 , 64 );
	memset( pScanBlock[1] , 0 , 64 );
	memset( pScanBlock[2] , 0 , 64 );
	memset( pScanBlock[3] , 0 , 64 );

	double          adfGeoTransform[6];
	poDS->GetGeoTransform(adfGeoTransform);
	double Pix_to_X = adfGeoTransform[1];
	double Pix_to_Y = adfGeoTransform[5];

	double GeoX =  adfGeoTransform[0];
	double GeoY =  adfGeoTransform[3];

	//找到像素点所在1阶区域
	double dbPixX , dbPixY;//用double表示的像素值 
	dbPixX = ( geo_src_x - GeoX ) / Pix_to_X ;
	dbPixY = ( geo_src_y - GeoY ) / Pix_to_Y ;

	for( int row = 0 ; row < 2 ; row++)
	{
		for( int col = 0 ; col < 2 ; col++)
		{
			iEnvPix[ (row * 2 + col) * 2 ] = (int)dbPixX   + col;
			iEnvPix[ (row * 2 + col) * 2 + 1] = (int)dbPixY + row;
		}
	}

	//加权算像素值
	for(int i = 0; i<4 ; i++)
	{
		if( iEnvPix[0+i*2] >= 0 && iEnvPix[0+i*2]  < nImgSizeX &&   iEnvPix[1+i*2] >= 0 && iEnvPix[1+i*2]  < nImgSizeY )
		{

//---------------------------单点读取数据-----------------------------------------
			int *panBandMap=new int[nBandCount];

			for (int i=0;i<nBandCount;i++)
			{
				panBandMap[i]=nBandCount-i;
			}
			CPLErr err;
			err = poDS->RasterIO(GF_Read,iEnvPix[0+i*2] , iEnvPix[1+i*2],1,1,
				pScanBlock[i],1,1,(GDALDataType)iColorDataType,nBandCount,panBandMap,nBandCount*nByteSize,nBandCount*nByteSize,nByteSize);

			delete [] panBandMap;
//---------------------------单点读取数据-----------------------------------------
//屏蔽代码 begin
			//if(buf.IsNeedPushBackNew(iEnvPix[1+i*2] , iEnvPix[0+i*2]))
			//{
			//	buf.push_back_fun( &buf , buf.pBand ,  iEnvPix[1+i*2] , iEnvPix[1+i*2] + buf.iExtendRowSize , buf.iAllColSize , buf.iAllRowSize ); 
			//}

			//buf.GetValue( iEnvPix[1+i*2] , iEnvPix[0+i*2] , &pScanBlock[i]  );
			//end

//--废弃部分代码			begin
//			buf.GetValue(Table, iEnvPix[0+i*2] , &pScanBlock[i]  );
//end

		}
	}
	
	for( int i = 0 ; i< 4 ; i++)
	{
		dbEnvPix[i * 2] = iEnvPix[i * 2] * Pix_to_X + GeoX;
		dbEnvPix[i * 2 + 1] = iEnvPix[i * 2 + 1] * Pix_to_Y + GeoY;
	}

	for( int i = 0 ; i < 4 ; i++)
	{
		arrDis[i] =  DISTANCE( geo_src_x - dbEnvPix[ 2 * i ] , dbEnvPix[ 2 * i +1 ] - geo_src_y );
		AllDis += arrDis[i];
	}

	//add by chenyong 2013-3-12
	//分波段处理灰度值
	unsigned char*							pch_n = NULL;
	unsigned short*							ps_n = NULL;
	unsigned int*							pi_n = NULL;
	unsigned long*							pl_n = NULL;
	unsigned char							ch_n(0);
	unsigned short							s_n(0);
	unsigned int							i_n(0);
	unsigned long							l_n(0);
	unsigned char							szVal[24] = {0};
	bool									bFlag = true;

	for (int k = 0; k < nBandCount; k++)
	{
		dbVal = 0;
		for (int j = 0; j < 4; j++)
		{
			arrWeight[j] = arrDis[j] / AllDis ;

			//ReadNumFromBuf(  pScanBlock[j] , nByteSize , &pScanBlock_i ); 
			//获取单一波段灰度值
			switch (nByteSize)
			{
			case 1:
				pch_n = (unsigned char*)pScanBlock[j];
				pScanBlock_i = static_cast<unsigned char>(pch_n[k]);
				break;

			case 2:
				ps_n = (unsigned short*)pScanBlock[j];
				pScanBlock_i = static_cast<unsigned short>(ps_n[k]);
				break;

			case 4:
				pi_n = (unsigned int*)pScanBlock[j];
				pScanBlock_i = static_cast<unsigned int>(pi_n[k]);
				break;

			case 8:
				pl_n = (unsigned long*)pScanBlock[j];
				pScanBlock_i = static_cast<unsigned long>(pl_n[k]);
				break;
			}
			//过滤空值点 alter by chenyong 2013-3-21

			if (bFlagNodata)
			{
				if (pScanBlock_i < dNodata)
				{
					dbVal += pScanBlock_i*arrWeight[j];
				}
			}
			else
			{
				dbVal += pScanBlock_i*arrWeight[j];
			}
		}

		bFlag = true;
		if (bFlagNodata)
		{
			if ((unsigned char)dbVal == 0)
			{
				for (int j = 0; j < 4; j++)
				{
					switch (nByteSize)
					{
					case 1:
						pch_n = (unsigned char*)pScanBlock[j];
						pScanBlock_i = static_cast<unsigned char>(pch_n[k]);
						if ((unsigned char)pScanBlock_i == (unsigned char)dNodata)
						{
							bFlag = true;
						}
						else
						{
							bFlag = false;
						}
						break;

					case 2:
						ps_n = (unsigned short*)pScanBlock[j];
						pScanBlock_i = static_cast<unsigned short>(ps_n[k]);

						if ((unsigned short)pScanBlock_i == (unsigned short)dNodata)
						{
							bFlag = true;
						}
						else
						{
							bFlag = false;
						}
						break;

					case 4:
						pi_n = (unsigned int*)pScanBlock[j];
						pScanBlock_i = static_cast<unsigned int>(pi_n[k]);
						if ((unsigned int)pScanBlock_i == (unsigned int)dNodata)
						{
							bFlag = true;
						}
						else
						{
							bFlag = false;
						}
						break;

					case 8:
						pl_n = (unsigned long*)pScanBlock[j];
						pScanBlock_i = static_cast<unsigned long>(pl_n[k]);
						if ((unsigned long)pScanBlock_i == (unsigned long)dNodata)
						{
							bFlag = true;
						}
						else
						{
							bFlag = false;
						}
						break;
					}

					if (!bFlag)
					{
						break;
					}
				}

				if (bFlag)
				{
					dbVal = dNodata;
				}
			}
		}

		switch (nByteSize)
		{
		case 1:
			ch_n = (unsigned char)dbVal;
			memcpy(szVal + k*nByteSize, &ch_n, nByteSize);
			break;

		case 2:
			s_n = (unsigned short)dbVal;
			memcpy(szVal + k*nByteSize, &s_n, nByteSize);
			break;

		case 4:
			i_n = (unsigned int)dbVal;
			memcpy(szVal + k*nByteSize, &i_n, nByteSize);
			break;

		case 8:
			l_n = (unsigned long)dbVal;
			memcpy(szVal + k*nByteSize, &l_n, nByteSize);
			break;
		}
	}
	
	memcpy(GrayVal, szVal, nByteSize*nBandCount);

	return ;
}
*/

void Resampling_Bilinear(double *Pt,int nImgSizeX , int nImgSizeY ,GDALDataset *poDS,/*CDeuBuffer & buf,*/void *GrayVal)
{
	double									geo_src_x = Pt[0];
	double									geo_src_y = Pt[1];
	double									geo_src_z = 0;
	double									dbEnvPix[8] = {0};
	int										iEnvPix[8] = {0};
	double									arrDis[4] = {0};
	double									AllDis = 0;
	double									arrWeight[4] = {0};
	double									dbVal = 0;
	double							        pScanBlock_i = 0;

	//获得图像的颜色类型	
	int	nBandCount=poDS->GetRasterCount();
	GDALRasterBand* poBand = poDS->GetRasterBand(1);	
	unsigned int iColorDataType = GDALGetRasterDataType( poBand );
	unsigned int iDataTypeSize = GDALGetDataTypeSize( (GDALDataType)iColorDataType );
	int nByteSize = iDataTypeSize / 8 ;        //删除缓冲区以及多波段转换实现的修改

	//采样点周边四个点
	unsigned char							pScanBlock [4][64];
	memset( pScanBlock[0] , 0 , 64 );
	memset( pScanBlock[1] , 0 , 64 );
	memset( pScanBlock[2] , 0 , 64 );
	memset( pScanBlock[3] , 0 , 64 );

	//add by chenyong 2014-1-15
 	unsigned char		cVal;
	unsigned short		sVal = 0;
	unsigned float		fVal = 0;
	unsigned double		dVal = 0;
	int					j = 0;

 	switch (nByteSize)
 	{
 	case 1:
 		cVal = (unsigned char)dNodata;
 		for (int j = 0; j < nBandCount; ++j)
 		{
 			memcpy(pScanBlock[0]+j*nByteSize, &cVal, sizeof(cVal));
 			memcpy(pScanBlock[1]+j*nByteSize, &cVal, sizeof(cVal));
 			memcpy(pScanBlock[2]+j*nByteSize, &cVal, sizeof(cVal));
 			memcpy(pScanBlock[3]+j*nByteSize, &cVal, sizeof(cVal));
 		}
 		break;

	case 2:
		sVal = static_cast<unsigned short>(dNodata);
		for (j = 0; j < nBandCount; ++j)
		{
			memcpy((unsigned short*)pScanBlock[0]+j*nByteSize, &sVal, sizeof(sVal));
			memcpy((unsigned short*)pScanBlock[1]+j*nByteSize, &sVal, sizeof(sVal));
			memcpy((unsigned short*)pScanBlock[2]+j*nByteSize, &sVal, sizeof(sVal));
			memcpy((unsigned short*)pScanBlock[3]+j*nByteSize, &sVal, sizeof(sVal));
		}
		break;

	case 4:
		fVal = static_cast<unsigned float>(dNodata);
		for (j = 0; j < nBandCount; ++j)
		{
			memcpy((unsigned float*)pScanBlock[0]+j*nByteSize, &fVal, sizeof(fVal));
			memcpy((unsigned float*)pScanBlock[1]+j*nByteSize, &fVal, sizeof(fVal));
			memcpy((unsigned float*)pScanBlock[2]+j*nByteSize, &fVal, sizeof(fVal));
			memcpy((unsigned float*)pScanBlock[3]+j*nByteSize, &fVal, sizeof(fVal));
		}
		break;

	case 8:
		dVal = (dNodata);
		for (j = 0; j < nBandCount; ++j)
		{
			memcpy((unsigned double*)pScanBlock[0]+j*nByteSize, &dVal, sizeof(dVal));
			memcpy((unsigned double*)pScanBlock[1]+j*nByteSize, &dVal, sizeof(dVal));
			memcpy((unsigned double*)pScanBlock[2]+j*nByteSize, &dVal, sizeof(dVal));
			memcpy((unsigned double*)pScanBlock[3]+j*nByteSize, &dVal, sizeof(dVal));
		}
		break;
 	}

	double          adfGeoTransform[6];
	poDS->GetGeoTransform(adfGeoTransform);
	double Pix_to_X = adfGeoTransform[1];
	double Pix_to_Y = adfGeoTransform[5];

	double GeoX =  adfGeoTransform[0];
	double GeoY =  adfGeoTransform[3];

	//找到像素点所在1阶区域
	double dbPixX , dbPixY;//用double表示的像素值 
	dbPixX = ( geo_src_x - GeoX ) / Pix_to_X ;
	dbPixY = ( geo_src_y - GeoY ) / Pix_to_Y ;

	for( int row = 0 ; row < 2 ; row++)
	{
		for( int col = 0 ; col < 2 ; col++)
		{
			iEnvPix[ (row * 2 + col) * 2 ] = (int)dbPixX   + col;
			iEnvPix[ (row * 2 + col) * 2 + 1] = (int)dbPixY + row;
		}
	}

	/*int *panBandMap=new int[nBandCount];
	for (int i=0;i<nBandCount;i++)
	{
		panBandMap[i]=nBandCount-i;
	}*/
	int iBandMap[] = {3,2,1};

	//加权算像素值
	for(int i = 0; i<4 ; i++)
	{
		if( iEnvPix[0+i*2] >= 0 && iEnvPix[0+i*2]  < nImgSizeX &&   iEnvPix[1+i*2] >= 0 && iEnvPix[1+i*2]  < nImgSizeY )
		{
			//---------------------------单点读取数据-----------------------------------------
			/*int *panBandMap=new int[nBandCount];

			for (int i=0;i<nBandCount;i++)
			{
				panBandMap[i]=nBandCount-i;
			}*/
			CPLErr err;
			err = poDS->RasterIO(GF_Read,
								 iEnvPix[0+i*2] , 
								 iEnvPix[1+i*2],
								 1,
								 1,
								 pScanBlock[i],
								 1,
								 1,
								 (GDALDataType)iColorDataType,
								 nBandCount,
								 /*panBandMap*/iBandMap,
								 nBandCount*nByteSize,
								 nBandCount*nByteSize,
								 nByteSize);

			/*delete [] panBandMap;*/
			//---------------------------单点读取数据-----------------------------------------
			//屏蔽代码 begin
			//if(buf.IsNeedPushBackNew(iEnvPix[1+i*2] , iEnvPix[0+i*2]))
			//{
			//	buf.push_back_fun( &buf , buf.pBand ,  iEnvPix[1+i*2] , iEnvPix[1+i*2] + buf.iExtendRowSize , buf.iAllColSize , buf.iAllRowSize ); 
			//}

			//buf.GetValue( iEnvPix[1+i*2] , iEnvPix[0+i*2] , &pScanBlock[i]  );
			//end

			//--废弃部分代码			begin
			//			buf.GetValue(Table, iEnvPix[0+i*2] , &pScanBlock[i]  );
			//end
			
			//for (int j = 0; j < nBandCount; ++j)
			//{
			//	switch (nByteSize)
			//	{
			//	case 1:
			//		//pch_n = (unsigned char*)pScanBlock[j];
			//		//pScanBlock_i = static_cast<unsigned char>(pch_n[k]);
			//		if ((int)pScanBlock[i][j] == (int)dNodata)
			//		{
			//			pScanBlock[i][j] = (unsigned char)dNodata-1;
			//		}
			//		break;
			//	}
			//}
			if (!IsExistNodata && nByteSize == 1 && dNodata - 255 < 1E-6)
			{
				for (int j = 0; j < nBandCount; ++j)
				{
					if (pScanBlock[i][j] == 255)
					{
						pScanBlock[i][j] = 254;
					}
				}
			}
		}
	}

	//delete []panBandMap;

	//计算采样点周边四个像素点位置
	for( int i = 0 ; i< 4 ; i++)
	{
		dbEnvPix[i * 2] = iEnvPix[i * 2] * Pix_to_X + GeoX;
		dbEnvPix[i * 2 + 1] = iEnvPix[i * 2 + 1] * Pix_to_Y + GeoY;
	}

	/*
	for( int i = 0 ; i < 4 ; i++)
	{
		arrDis[i] =  DISTANCE( geo_src_x - dbEnvPix[ 2 * i ] , dbEnvPix[ 2 * i +1 ] - geo_src_y );
		AllDis += arrDis[i];
	}
	*/
 
	//计算加权值 加权分为4组参数 分别是 
	//(1-△x)(1-△y)  (1-△x)△y   △x(1-△y)   △x△y
	//△x 与 △y 都是与l11点的位移 这里实际上是位移比例
    double    deviationX = (geo_src_x - dbEnvPix[0])/Pix_to_X;
	double    deviationY = (geo_src_y - dbEnvPix[1])/Pix_to_Y;

	//add by chenyong 2013-3-12
	//分波段处理灰度值
	unsigned char*							pch_n = NULL;
	unsigned short*							ps_n = NULL;
	unsigned int*							pi_n = NULL;
	unsigned long*							pl_n = NULL;
	unsigned char							ch_n(0);
	unsigned short							s_n(0);
	unsigned int							i_n(0);
	unsigned long							l_n(0);
	unsigned char							szVal[24] = {0};
	bool									bFlag = true;

	for (int k = 0; k < nBandCount; k++)
	{
		dbVal = 0;
		for (int j = 0; j < 4; j++)
		{
			//arrWeight[j] = arrDis[j] / AllDis ;
			switch (j)
			{
			case 0:
                arrWeight[j] = (1-deviationX)*(1-deviationY);
				break;
			case 1:
				arrWeight[j] = (1-deviationX)*deviationY;
				break;
			case 2:
				arrWeight[j] = deviationX*(1-deviationY);
				break;
			case 3:
				arrWeight[j] = deviationX*deviationY;
				break;
			default:
				break;
			}

			//ReadNumFromBuf(  pScanBlock[j] , nByteSize , &pScanBlock_i ); 
			//获取单一波段灰度值
			switch (nByteSize)
			{
			case 1:
				pch_n = (unsigned char*)pScanBlock[j];
				pScanBlock_i = static_cast<unsigned char>(pch_n[k]);
				break;

			case 2:
				ps_n = (unsigned short*)pScanBlock[j];
				pScanBlock_i = static_cast<unsigned short>(ps_n[k]);
				break;

			case 4:
				pi_n = (unsigned int*)pScanBlock[j];
				pScanBlock_i = static_cast<unsigned int>(pi_n[k]);
				break;

			case 8:
				pl_n = (unsigned long*)pScanBlock[j];
				pScanBlock_i = static_cast<unsigned long>(pl_n[k]);
				break;
			}
			//过滤空值点 alter by chenyong 2013-3-21

			if (bFlagNodata)
			{
				if (pScanBlock_i < dNodata)
				{
					dbVal += pScanBlock_i*arrWeight[j];
				}
			}
			/*else
			{
				dbVal += pScanBlock_i*arrWeight[j];
			}*/
		}

		bFlag = true;
		if (bFlagNodata)
		{
			if ((unsigned char)dbVal == 0)
			{
				for (int j = 0; j < 4; j++)
				{
					switch (nByteSize)
					{
					case 1:
						pch_n = (unsigned char*)pScanBlock[j];
						pScanBlock_i = static_cast<unsigned char>(pch_n[k]);
						if ((unsigned char)pScanBlock_i == (unsigned char)dNodata)
						{
							bFlag = true;
						}
						else
						{
							bFlag = false;
						}
						break;

					case 2:
						ps_n = (unsigned short*)pScanBlock[j];
						pScanBlock_i = static_cast<unsigned short>(ps_n[k]);

						if ((unsigned short)pScanBlock_i == (unsigned short)dNodata)
						{
							bFlag = true;
						}
						else
						{
							bFlag = false;
						}
						break;

					case 4:
						pi_n = (unsigned int*)pScanBlock[j];
						pScanBlock_i = static_cast<unsigned int>(pi_n[k]);
						if ((unsigned int)pScanBlock_i == (unsigned int)dNodata)
						{
							bFlag = true;
						}
						else
						{
							bFlag = false;
						}
						break;

					case 8:
						pl_n = (unsigned long*)pScanBlock[j];
						pScanBlock_i = static_cast<unsigned long>(pl_n[k]);
						if ((unsigned long)pScanBlock_i == (unsigned long)dNodata)
						{
							bFlag = true;
						}
						else
						{
							bFlag = false;
						}
						break;
					}

					if (!bFlag)
					{
						break;
					}
				}

				if (bFlag)
				{
					dbVal = dNodata;
				}
			}
		}

		switch (nByteSize)
		{
		case 1:
			ch_n = (unsigned char)dbVal;
			memcpy(szVal + k*nByteSize, &ch_n, nByteSize);
			break;

		case 2:
			s_n = (unsigned short)dbVal;
			memcpy(szVal + k*nByteSize, &s_n, nByteSize);
			break;

		case 4:
			i_n = (unsigned int)dbVal;
			memcpy(szVal + k*nByteSize, &i_n, nByteSize);
			break;

		case 8:
			l_n = (unsigned long)dbVal;
			memcpy(szVal + k*nByteSize, &l_n, nByteSize);
			break;
		}
	}

	memcpy(GrayVal, szVal, nByteSize*nBandCount);

	return ;
}

void Resampling_Bicubic(double *Pt,int nImgSizeX , int nImgSizeY ,GDALDataset *poDS,/*CDeuBuffer & buf,*/void *GrayVal)
{
	double geo_src_x = Pt[0];
    double geo_src_y = Pt[1];
	double geo_src_z = Pt[2];

	//////////////////////////////////////////////////////////////////////////
	//获得图像的颜色类型	
	//unsigned int iColorDataType = GDALGetRasterDataType( poBand );
	//unsigned int iDataTypeSize = GDALGetDataTypeSize( (GDALDataType)iColorDataType );

	int	nBandCount=poDS->GetRasterCount();
	GDALRasterBand* poBand = poDS->GetRasterBand(1);	
	unsigned int iColorDataType = GDALGetRasterDataType( poBand );
	unsigned int iDataTypeSize = GDALGetDataTypeSize( (GDALDataType)iColorDataType );
	int nByteSize = iDataTypeSize / 8 ;        //删除缓冲区以及多波段转换实现的修改
	//int nByteSize = buf.nByteSize;

	//////////////////////////////////////////////////////////////////////////
	//全文件的原点
	//adfGeoTransform[0] y,东方向或经度，为了容易分辨，所有的X为横轴坐标，所有的Y为纵轴坐标
	//adfGeoTransform[1] Pix_to_X 分辨率
	//adfGeoTransform[2] 0
	//adfGeoTransform[3] x,北方向或纬度，为了容易分辨，所有的X为横轴坐标，所有的Y为纵轴坐标
	//adfGeoTransform[4] 0
	//adfGeoTransform[5] Pix_to_Y 分辨率
	double          adfGeoTransform[6];
	poDS->GetGeoTransform(adfGeoTransform);
	double Pix_to_X = adfGeoTransform[1];
	double Pix_to_Y = adfGeoTransform[5];
	double GeoX =  adfGeoTransform[0];
	double GeoY =  adfGeoTransform[3];

	//找到像素点所在1阶区域
	double dbPixX , dbPixY;//用double表示的像素值 
	dbPixX = ( geo_src_x - GeoX ) / Pix_to_X ;
	dbPixY = ( geo_src_y - GeoY ) / Pix_to_Y ;

	int iEnvPix[32];
	for( int row = 0 ; row < 4 ; row++)
	{
		for( int col = 0 ; col < 4 ; col++)
		{
			iEnvPix[ (row * 4 + col) * 2 ] = (int)dbPixX  - 1 + row;
			iEnvPix[ (row * 4 + col) * 2 + 1] = (int)dbPixY +1 - col;
		}
	}
	
	//加权算像素值
	//char* pScanBlock = (char *) /*CPLMalloc*/malloc( nByteSize * 64 * 64);
	char pScanBlock [16][24];
	for(int i=0; i<16; i++)
	{
		memset( pScanBlock[i] , 0 , 24 );
	}

	//add by chenyong 2014-6-12
	unsigned char cVal;
	switch (nByteSize)
	{
	case 1:
		cVal = (unsigned char)dNodata;
		for (int j = 0; j < nBandCount; ++j)
		{
			memcpy(pScanBlock[0]+j*nByteSize, &cVal, sizeof(cVal));
			memcpy(pScanBlock[1]+j*nByteSize, &cVal, sizeof(cVal));
			memcpy(pScanBlock[2]+j*nByteSize, &cVal, sizeof(cVal));
			memcpy(pScanBlock[3]+j*nByteSize, &cVal, sizeof(cVal));
			memcpy(pScanBlock[4]+j*nByteSize, &cVal, sizeof(cVal));
			memcpy(pScanBlock[5]+j*nByteSize, &cVal, sizeof(cVal));
			memcpy(pScanBlock[6]+j*nByteSize, &cVal, sizeof(cVal));
			memcpy(pScanBlock[7]+j*nByteSize, &cVal, sizeof(cVal));
			memcpy(pScanBlock[8]+j*nByteSize, &cVal, sizeof(cVal));
			memcpy(pScanBlock[9]+j*nByteSize, &cVal, sizeof(cVal));
			memcpy(pScanBlock[10]+j*nByteSize, &cVal, sizeof(cVal));
			memcpy(pScanBlock[11]+j*nByteSize, &cVal, sizeof(cVal));
			memcpy(pScanBlock[12]+j*nByteSize, &cVal, sizeof(cVal));
			memcpy(pScanBlock[13]+j*nByteSize, &cVal, sizeof(cVal));
			memcpy(pScanBlock[14]+j*nByteSize, &cVal, sizeof(cVal));
			memcpy(pScanBlock[15]+j*nByteSize, &cVal, sizeof(cVal));
		}

		break;
	}

	//add by chenyong 2014-1-15
  	/*unsigned char cVal;
  	switch (nByteSize)
  	{
  	case 1:
  		cVal = (unsigned char)dNodata;
  
  		for (int j = 0; j < nBandCount; ++j)
  		{
  			for (int k = 0; k < 16; ++k)
  			{
  				memcpy(pScanBlock[k]+j*nByteSize, &cVal, sizeof(cVal));
  			}
  		}
  
  		break;
  	}*/

	//int *panBandMap=new int[nBandCount];

	//for (int i=0;i<nBandCount;i++)
	//{
	//	panBandMap[i]=nBandCount-i;
	//}
	int panBandMap[] = {3,2,1};
	
	//int Table=-2;
	for(int i=0; i<16; i++)
	{
		if( iEnvPix[0 + i * 2] > 0 && iEnvPix[0 + i * 2]  < nImgSizeX &&   iEnvPix[1 + i * 2] > 0 && iEnvPix[1 + i * 2]  < nImgSizeY )
		{
			//---------------------------单点读取数据-----------------------------------------
			/*int *panBandMap=new int[nBandCount];

			for (int i=0;i<nBandCount;i++)
			{
				panBandMap[i]=nBandCount-i;
			}*/
			CPLErr err;
			err = poDS->RasterIO(GF_Read,iEnvPix[0+i*2] , iEnvPix[1+i*2],1,1,
				pScanBlock[i],1,1,(GDALDataType)iColorDataType,nBandCount,panBandMap,nBandCount*nByteSize,nBandCount*nByteSize,nByteSize);

			//delete [] panBandMap;
			//---------------------------单点读取数据-----------------------------------------

/*			if(buf.IsNeedPushBackNew(iEnvPix[1+i*2] , iEnvPix[0+i*2]))
				{
					buf.push_back_fun( &buf , buf.pBand ,  iEnvPix[1+i*2] , iEnvPix[1+i*2] + buf.iExtendRowSize , buf.iAllColSize , buf.iAllRowSize ); 
				}

		    buf.GetValue( iEnvPix[1+i*2] , iEnvPix[0+i*2] , &pScanBlock[i]  );   //删除缓冲区
*/
//			buf.GetValue( Table, iEnvPix[0+i*2] , &pScanBlock[i]  );
			
// 			for (int j = 0; j < nBandCount; ++j)
// 			{
// 				switch (nByteSize)
// 				{
// 				case 1:
// 					//pch_n = (unsigned char*)pScanBlock[j];
// 					//pScanBlock_i = static_cast<unsigned char>(pch_n[k]);
// 					if ((int)pScanBlock[i][j] == (int)dNodata)
// 					{
// 						pScanBlock[i][j] = (unsigned char)dNodata-1;
// 					}
// 					break;
// 				}
// 			}
			for (int j = 0; j < nBandCount; ++j)
			{
				switch (nByteSize)
				{
				case 1:

					if ((int)pScanBlock[i][j] == 255)
					{
						pScanBlock[i][j] = 254;
					}
					break;
				}
			}
		}
	}

	//delete []panBandMap;

	double dbEnvPix[32];
	for( int i = 0 ; i<16 ; i++)
	{
		dbEnvPix[i * 2] = iEnvPix[i * 2] * Pix_to_X + GeoX;
		dbEnvPix[i * 2 + 1] = iEnvPix[i * 2 + 1] * Pix_to_Y + GeoY;
	}

	double arrWeight[16]  ;
	double dx ,dy;
	//dx =  abs(( dbPixY - (int)dbPixY ) * Pix_to_Y) ;//参考公式
	//dy =  abs(( dbPixX - (int)dbPixX ) * Pix_to_X) ;//参考公式

	dx = abs((geo_src_x - dbEnvPix[10])/Pix_to_X);
    dy = abs((geo_src_y - dbEnvPix[11])/Pix_to_Y);

	double dbVal = 0;

//#define W1(dx) ( -dx + 2 * dx * dx - dx * dx * dx ) 
//#define W2(dx) ( 1 - 2 * dx * dx + dx * dx * dx ) 
//#define W3(dx) ( dx +  dx * dx - dx * dx * dx ) 
//#define W4(dx) ( - dx * dx + dx * dx * dx ) 

	//unsigned long  pScanBlock_i = 0;
	double  pScanBlock_i = 0;

	/*arrWeight[0] =	W1(dx) *  W1(dy) ;
	arrWeight[1] =	W1(dx) *  W2(dy) ;
	arrWeight[2] =	W1(dx) *  W3(dy) ;
	arrWeight[3] =	W1(dx) *  W4(dy) ;

	arrWeight[4] =	W2(dx) *  W1(dy) ;
	arrWeight[5] =	W2(dx) *  W2(dy) ;
	arrWeight[6] =	W2(dx) *  W3(dy) ;
	arrWeight[7] =	W2(dx) *  W4(dy) ;

	arrWeight[8] =	W3(dx) *  W1(dy) ;
	arrWeight[9] =	W3(dx) *  W2(dy) ;
	arrWeight[10] = W3(dx) *  W3(dy) ;
	arrWeight[11] = W3(dx) *  W4(dy) ;

	arrWeight[12] = W4(dx) *  W1(dy) ;
	arrWeight[13] = W4(dx) *  W2(dy) ;
	arrWeight[14] = W4(dx) *  W3(dy) ;
	arrWeight[15] = W4(dx) *  W4(dy) ;*/

	//add by chenyong 2014-7-30
	double				dx1(0);
	double				dy1(0);
	double				dz1(0);
	double				dq1(0);
	double				dq2(0);

	//0
	dx1 = -dx;
	dy1 = 2*dx*dx;
	dz1 = dx*dx*dx;
	dq1 = (dx1 + dy1 - dz1);

	dx1 = -dy;
	dy1 = 2*dy*dy;
	dz1 = dy*dy*dy;
	dq2 = (dx1 + dy1 - dz1);
	arrWeight[0] = dq1 * dq2;

	//1
	dx1 = -dx;
	dy1 = 2*dx*dx;
	dz1 = dx*dx*dx;
	dq1 = dx1 + dy1 - dz1;

	dx1 = 1;
	dy1 = 2*dy*dy;
	dz1 = dy*dy*dy;
	dq2 = dx1 - dy1 + dz1;
	arrWeight[1] = dq1*dq2;

	//2
	dx1 = -dx;
	dy1 = 2*dx*dx;
	dz1 = dx*dx*dx;
	dq1 = dx1 + dy1 - dz1;

	dx1 = dy;
	dy1 = dy*dy;
	dz1 = dy*dy*dy;
	dq2 = dx1 + dy1 - dz1;
	arrWeight[2] = dq1*dq2;

	//3
	dx1 = -dx;
	dy1 = 2*dx*dx;
	dz1 = dx*dx*dx;
	dq1 = dx1 + dy1 - dz1;

	dx1 = 0;
	dy1 = dy*dy;
	dz1 = dy*dy*dy;
	dq2 = dx1 - dy1 + dz1;
	arrWeight[3] = dq1*dq2;

	//4
	dx1 = 1;
	dy1 = 2*dx*dx;
	dz1 = dx*dx*dx;
	dq1 = dx1 - dy1 + dz1;

	dx1 = -dy;
	dy1 = 2*dy*dy;
	dz1 = dy*dy*dy;
	dq2 = dx1 + dy1 - dz1;
	arrWeight[4] = dq1*dq2;

	//5
	dx1 = 1;
	dy1 = 2*dx*dx;
	dz1 = dx*dx*dx;
	dq1 = dx1 - dy1 + dz1;

	dx1 = 1;
	dy1 = 2*dy*dy;
	dz1 = dy*dy*dy;
	dq2 = dx1 - dy1 + dz1;
	arrWeight[5] = dq1*dq2;

	//6
	dx1 = 1;
	dy1 = 2*dx*dx;
	dz1 = dx*dx*dx;
	dq1 = dx1 - dy1 + dz1;

	dx1 = dy;
	dy1 = dy*dy;
	dz1 = dy*dy*dy;
	dq2 = dx1 + dy1 - dz1;
	arrWeight[6] = dq1*dq2;

	//7
	dx1 = 1;
	dy1 = 2*dx*dx;
	dz1 = dx*dx*dx;
	dq1 = dx1 - dy1 + dz1;

	dx1 = 0;
	dy1 = dy*dy;
	dz1 = dy*dy*dy;
	dq2 = dx1 - dy1 + dz1;
	arrWeight[7] = dq1*dq2;

	//8
	dx1 = dx;
	dy1 = dx*dx;
	dz1 = dx*dx*dx;
	dq1 = dx1 + dy1 - dz1;

	dx1 = -dy;
	dy1 = 2*dy*dy;
	dz1 = dy*dy*dy;
	dq2 = dx1 + dy1 - dz1;
	arrWeight[8] = dq1*dq2;

	//9
	dx1 = dx;
	dy1 = dx*dx;
	dz1 = dx*dx*dx;
	dq1 = dx1 + dy1 - dz1;

	dx1 = 1;
	dy1 = 2*dy*dy;
	dz1 = dy*dy*dy;
	dq2 = dx1 - dy1 + dz1;
	arrWeight[9] = dq1*dq2;

	//10
	dx1 = dx;
	dy1 = dx*dx;
	dz1 = dx*dx*dx;
	dq1 = dx1 + dy1 - dz1;

	dx1 = dy;
	dy1 = dy*dy;
	dz1 = dy*dy*dy;
	dq2 = dx1 + dy1 - dz1;
	arrWeight[10] = dq1*dq2;

	//11
	dx1 = dx;
	dy1 = dx*dx;
	dz1 = dx*dx*dx;
	dq1 = dx1 + dy1 - dz1;

	dx1 = 0;
	dy1 = dy*dy;
	dz1 = dy*dy*dy;
	dq2 = dx1 - dy1 + dz1;
	arrWeight[11] = dq1*dq2;

	//12
	dx1 = 0;
	dy1 = dx*dx;
	dz1 = dx*dx*dx;
	dq1 = dx1 - dy1 + dz1;

	dx1 = -dy;
	dy1 = 2*dy*dy;
	dz1 = dy*dy*dy;
	dq2 = dx1 + dy1 - dz1;
	arrWeight[12] = dq1*dq2;

	//13
	dx1 = 0;
	dy1 = dx*dx;
	dz1 = dx*dx*dx;
	dq1 = dx1 - dy1 + dz1;

	dx1 = 1;
	dy1 = 2*dy*dy;
	dz1 = dy*dy*dy;
	dq2 = dx1 - dy1 + dz1;
	arrWeight[13] = dq1*dq2;

	//14
	dx1 = 0;
	dy1 = dx*dx;
	dz1 = dx*dx*dx;
	dq1 = dx1 - dy1 + dz1;

	dx1 = dy;
	dy1 = dy*dy;
	dz1 = dy*dy*dy;
	dq2 = dx1 + dy1 - dz1;
	arrWeight[14] = dq1*dq2;

	//15
	dx1 = 0;
	dy1 = dx*dx;
	dz1 = dx*dx*dx;
	dq1 = dx1 - dy1 + dz1;

	dx1 = 0;
	dy1 = dy*dy;
	dz1 = dy*dy*dy;
	dq2 = dx1 - dy1 + dz1;
	arrWeight[15] = dq1*dq2;

	//add by chenyong 2013-3-12
	//分波段处理灰度值
	unsigned char*							pch_n = NULL;
	unsigned short*							ps_n = NULL;
	unsigned int*							pi_n = NULL;
	unsigned long*							pl_n = NULL;
	unsigned char							ch_n(0);
	unsigned short							s_n(0);
	unsigned int							i_n(0);
	unsigned long							l_n(0);
	unsigned char							szVal[24] = {0};
	bool									bFlag = true;

	for (int k = 0; k < nBandCount; k++)
	{
		dbVal = 0;
		for (int j = 0; j < 16; j++)
		{
			//获取单一波段灰度值
			switch (nByteSize)
			{
			case 1:
				pch_n = (unsigned char*)pScanBlock[j];
				pScanBlock_i = static_cast<unsigned char>(pch_n[k]);
				break;

			case 2:
				ps_n = (unsigned short*)pScanBlock[j];
				pScanBlock_i = static_cast<unsigned short>(ps_n[k]);
				break;

			case 4:
				pi_n = (unsigned int*)pScanBlock[j];
				pScanBlock_i = static_cast<unsigned int>(pi_n[k]);
				break;

			case 8:
				pl_n = (unsigned long*)pScanBlock[j];
				pScanBlock_i = static_cast<unsigned long>(pl_n[k]);
				break;
			}

			//过滤nodata值（大于0时情况）
			if (bFlagNodata)
			{
				if (pScanBlock_i < dNodata)
				{
					dbVal += pScanBlock_i * arrWeight[j];
				}
			}
			/*else
			{
				dbVal += pScanBlock_i * arrWeight[j];
			}*/
		}

		//过滤掉nodata时，使dbval有可能是负值，需取绝对值
		dbVal = abs(dbVal);
		bFlag = true;

		//if (bFlagNodata)
		{
			//if ((unsigned char)dbVal == 0)
			if (bFlagNodata && (((unsigned char)dbVal == 0) || ((unsigned char)dbVal == (unsigned char)dNodata)))
			{
				for (int j = 0; j < 16; j++)
				{
					//获取单一波段灰度值
					switch (nByteSize)
					{
					case 1:
						pch_n = (unsigned char*)pScanBlock[j];
						pScanBlock_i = static_cast<unsigned char>(pch_n[k]);
						if ((unsigned char)pScanBlock_i == (unsigned char)dNodata)
						{
							bFlag = true;
						}
						else
						{
							bFlag = false;
						}
						break;

					case 2:
						ps_n = (unsigned short*)pScanBlock[j];
						pScanBlock_i = static_cast<unsigned short>(ps_n[k]);
						if ((unsigned short)pScanBlock_i == (unsigned short)dNodata)
						{
							bFlag = true;
						}
						else
						{
							bFlag = false;
						}
						break;

					case 4:
						pi_n = (unsigned int*)pScanBlock[j];
						pScanBlock_i = static_cast<unsigned int>(pi_n[k]);
						if ((unsigned int)pScanBlock_i == (unsigned int)dNodata)
						{
							bFlag = true;
						}
						else
						{
							bFlag = false;
						}
						break;

					case 8:
						pl_n = (unsigned long*)pScanBlock[j];
						pScanBlock_i = static_cast<unsigned long>(pl_n[k]);
						if ((unsigned long)pScanBlock_i == (unsigned long)dNodata)
						{
							bFlag = true;
						}
						else
						{
							bFlag = false;
						}
						break;
					}

					if (!bFlag)
					{
						break;
					}
				}

				/*if (bFlag)
				{
					dbVal = dNodata;
				}*/
				if (bFlag && ((unsigned char)dbVal == 0))
				{
					dbVal = dNodata;
				}
				else if (!bFlag && (nByteSize == 1) && ((unsigned char)dbVal == (unsigned char)dNodata))
				{
					dbVal--;
				}
			}
		}
		//add by chenyong 2014-1-15
 		/*else
 		{
 			if (dbVal == dNodata)
 			{
 				dbVal-=1;
 			}
 		}*/

		switch (nByteSize)
		{
		case 1:
			ch_n = (unsigned char)dbVal;
			memcpy(szVal + k*nByteSize, &ch_n, nByteSize);
			break;

		case 2:
			s_n = (unsigned short)dbVal;
			memcpy(szVal + k*nByteSize, &s_n, nByteSize);
			break;

		case 4:
			i_n = (unsigned int)dbVal;			
			memcpy(szVal + k*nByteSize, &i_n, nByteSize);
			break;

		case 8:
			l_n = (unsigned long)dbVal;			
			memcpy(szVal + k*nByteSize, &l_n, nByteSize);
			break;
		}
	}

	memcpy(GrayVal, szVal, nByteSize*nBandCount);

	return ;

}

unsigned long ReadNumFromBuf( void * pScanBlock , unsigned int nByteSize ,unsigned long *ulResult )
{
	unsigned char *ch_n = 0 ;
	unsigned short *s_n = 0 ;
	unsigned int  *i_n = 0 ;
	unsigned long *l_n = 0 ;
	
	switch( nByteSize )
	{
	case 1:
		//memcpy( &ch_n , pScanBlock , iDataTypeSize);
		ch_n = (unsigned char *) pScanBlock ;
		ulResult[0] = static_cast<unsigned char>(ch_n[0]) ;
		break;

	case 2:
		s_n = (unsigned short *) pScanBlock ;
		ulResult[0] = static_cast<unsigned short>(s_n[0]) ;
		break;

	case 4:
		i_n = (unsigned int *) pScanBlock ;
		ulResult[0] = static_cast<unsigned int>(i_n[0]) ;		
		break;

	case 8:
		l_n = (unsigned long *) pScanBlock ;
		ulResult[0] = static_cast<unsigned long>(l_n[0]) ;	
		break;

	default:	
		break;
	}

	return 0;
}

void WriteNumToBuf( double dbVal, void* GrayVal, unsigned int nByteSize )
{
	unsigned char ch_n = 0;
	unsigned short s_n = 0 ;
	unsigned int  i_n = 0;
	unsigned long l_n = 0;
	
	switch( nByteSize )
	{
	case 1:
		ch_n = (unsigned char)dbVal;
		memcpy( GrayVal , &ch_n , nByteSize);
		
		break;
	case 2:
		s_n = (unsigned short)dbVal;
		memcpy( GrayVal , &s_n , nByteSize);
		
		break;
	case 4:
		i_n = (unsigned int)dbVal;
		memcpy( GrayVal , &i_n , nByteSize);
		
		break;
	case 8:
		l_n = (unsigned long)dbVal;
		memcpy( GrayVal , &l_n , nByteSize);
		
		break;
	default:
		
		break;
	}

	return ;
}

double GetRandomDetal(double min_ , double max_)
{
	double r = rand();

	double m = int(r) % 100 * 0.01;

	double range = max_ - min_;

	return  min_ + range * m ;	
}

bool CDeuRasterTrans::IsHaveIGE( const CString& SrcTab, const CString& SrcPath )
{
	bool bHaveIGE;
	//获得ige文件全路径
	USES_CONVERSION;
	//char * szPath = W2A(SrcPath);
	//char * szFile = W2A(SrcTab);

	int iLength = 0;
	//iLength = strlen(szPath) + strlen(szFile) + strlen(".ige") + strlen("\\") ;
	iLength = SrcPath.GetLength() + SrcTab.GetLength() + strlen(".ige") + strlen("\\") ;

	//20121117
	LPSTR szFileName = new char[iLength+1];
	sprintf( szFileName , "%s\\%s.ige" , SrcPath , SrcTab );

	//判断文件是否存在
	_OFSTRUCT stcOF;
	//bool bHaveIGE;
	char ** papszOptions = new char*[3];
	char * pszOptions0 = new char [10];
	strcpy(pszOptions0 ,"TFW=TRUE");

	papszOptions[0] = pszOptions0;
	if( OpenFile( szFileName , &stcOF , OF_EXIST ) >= 0)
	{
		bHaveIGE = true;
	}
	else
	{
		bHaveIGE =false;
	}

	return bHaveIGE;
}

int CDeuRasterTrans::CalculatePixXY(  double adfGeoTransform[6], double W,double H  , projPJ m_srcPJ ,double & dx ,double & dy )
{
	//////////////////////////////////////////////////////////////////////////
	//全文件的原点
	//adfGeoTransform[0] y,东方向或经度，为了容易分辨，所有的X为横轴坐标，所有的Y为纵轴坐标
	//adfGeoTransform[1] Pix_to_X 分辨率
	//adfGeoTransform[2] 0
	//adfGeoTransform[3] x,北方向或纬度，为了容易分辨，所有的X为横轴坐标，所有的Y为纵轴坐标
	//adfGeoTransform[4] 0
	//adfGeoTransform[5] Pix_to_Y 分辨率

	//////////////////////////////////////////////////////////////////////////
	//double adfGeoTransform[6];
	double unitY_i = adfGeoTransform[0];//6位，y,东方向或经度，为了容易分辨，所有的X为横轴坐标，所有的Y为纵轴坐标
	double unitX_i = adfGeoTransform[3];//7位，x,北方向或纬度，为了容易分辨，所有的X为横轴坐标，所有的Y为纵轴坐标
	
 	double Pix_to_X = adfGeoTransform[1];//
	double Pix_to_Y = adfGeoTransform[5];
	double X_to_Pix = 1/Pix_to_X;
	double Y_to_Pix = 1/Pix_to_Y;

	SHORT coordtype=0;		
	m_coordtype.get_CoordType(coordtype);

	SHORT destcoordtype=0;
	m_coordtype.get_DestCoordType(destcoordtype);

	double desX_i,desY_i;
	double desX_i_2,desY_i_2;
	double desX_i_3,desY_i_3;
	double desX_i_4,desY_i_4;

	if( coordtype == destcoordtype)//如果坐标类型相同无需投影
	{
		LOGSTR("error:坐标类型相同无需投影");
		return 0;
	}
	else if( (coordtype == GEODETIC) && ( destcoordtype == PLANE) )
	{
		//正投影
		Gauss_bl_xy(m_desPJ,(m_des_from_greenwich) * DEG_TO_RAD,unitX_i * DEG_TO_RAD,unitY_i * DEG_TO_RAD,desX_i,desY_i);
		Gauss_bl_xy(m_desPJ,(m_des_from_greenwich) * DEG_TO_RAD,(unitX_i + Pix_to_Y * H) * DEG_TO_RAD ,(unitY_i + Pix_to_X * W) * DEG_TO_RAD,desX_i_2,desY_i_2);

#define _XY
#ifdef  _XY
		Gauss_bl_xy(m_desPJ,(m_des_from_greenwich) * DEG_TO_RAD,unitX_i * DEG_TO_RAD,(unitY_i + Pix_to_X * W) * DEG_TO_RAD,desX_i_3,desY_i_3);
		Gauss_bl_xy(m_desPJ,(m_des_from_greenwich) * DEG_TO_RAD,(unitX_i + Pix_to_Y * H) * DEG_TO_RAD ,unitY_i * DEG_TO_RAD,desX_i_4,desY_i_4);
#endif

		if(m_TransModel == MODEL_GAUSS)
		{
		}
		else if(m_TransModel == MODEL_TM)
		{
		}
		else if(m_TransModel == MODEL_UTM)
		{
			desX_i *= 0.9996;
			desY_i *= 0.9996;
			desX_i_2 *= 0.9996;
			desY_i_2 *= 0.9996;
			desX_i_3 *= 0.9996;
			desY_i_3 *= 0.9996;
			desX_i_4 *= 0.9996;
			desY_i_4 *= 0.9996;
		}

		double MaxX(desX_i),MinX(desX_i),MaxY(desY_i),MinY(desY_i);
		
		MaxX = MaxX > desX_i ? MaxX : desX_i;
		MaxX = MaxX > desX_i_2 ? MaxX : desX_i_2;
		MaxX = MaxX > desX_i_3 ? MaxX : desX_i_3;
		MaxX = MaxX > desX_i_4 ? MaxX : desX_i_4;

		MinX = MinX < desX_i ? MinX : desX_i;
		MinX = MinX < desX_i_2 ? MinX : desX_i_2;
		MinX = MinX < desX_i_3 ? MinX : desX_i_3;
		MinX = MinX < desX_i_4 ? MinX : desX_i_4;

		MaxY = MaxY > desY_i ? MaxY : desY_i;
		MaxY = MaxY > desY_i_2 ? MaxY : desY_i_2;
		MaxY = MaxY > desY_i_3 ? MaxY : desY_i_3;
		MaxY = MaxY > desY_i_4 ? MaxY : desY_i_4;

		MinY = MinY < desY_i ? MinY : desY_i;
		MinY = MinY < desY_i_2 ? MinY : desY_i_2;
		MinY = MinY < desY_i_3 ? MinY : desY_i_3;
		MinY = MinY < desY_i_4 ? MinY : desY_i_4;

		dx = (MaxX - MinX) / H;
		dy = (MaxY - MinY) / W;
	}
	else if( (coordtype == PLANE) && ( destcoordtype == GEODETIC) )
	{
		//反投影
		double Proj_X = 0;
		double Proj_Y = 0;

		double Proj_X_2 = 0;
		double Proj_Y_2 = 0;

		if(m_TransModel == MODEL_GAUSS)
		{
			Proj_X = unitX_i ;
			Proj_Y = unitY_i - m_src_false_east;

			Proj_X_2 =  Proj_X + Pix_to_X * H;
			Proj_Y_2 =  Proj_Y + Pix_to_Y * W;
	
		}
		else if(m_TransModel == MODEL_TM)
		{
			Proj_X = unitX_i ;
			Proj_Y = unitY_i - m_src_false_east;

			Proj_X_2 =  Proj_X + Pix_to_X * H;
			Proj_Y_2 =  Proj_Y + Pix_to_Y * W;

		}
		else if(m_TransModel == MODEL_UTM)
		{
			Proj_X = unitX_i / 0.9996 ;
			Proj_Y = (unitY_i - m_src_false_east)  / 0.9996;

			Proj_X_2 =  (Proj_X + Pix_to_X * H);
			Proj_Y_2 =  (Proj_Y + Pix_to_Y * W);
		}

		Gauss_xy_bl(m_desPJ,(m_des_from_greenwich) * DEG_TO_RAD, Proj_X, Proj_Y, desX_i,desY_i);
		Gauss_xy_bl(m_desPJ,(m_des_from_greenwich) * DEG_TO_RAD, Proj_X_2, Proj_Y_2, desX_i_2,desY_i_2);

		dx = (desX_i_2 - desX_i) * RAD_TO_DEG / H;
		dy = (desY_i_2 - desY_i) * RAD_TO_DEG / W;
	}
	else
	{
		LOGSTR("error:错误的投影坐标类型");
	}

	//新的算法计算dx,dy (2011-10-27)
	//_coord_transf( m_Para,m_TransModel , 1, &LT_Y, &LT_X,0,&x,&y,0);

	return 0;
}

void CDeuRasterTrans::CopyAttributeFile(const CString& FileName, const CString& FileNameOut)
{
	////如果有属性文件就复制
	////aux,rrd
	//std::fstream _file;		
	//CString strFileName;
	//strFileName = FileName;

	//CString strFileOut;
	//strFileOut = FileNameOut;

	//CString strNoSuffixIn;
	//CString strNoSuffixOut;

	//strNoSuffixIn = strFileName.Left(strFileName.GetLength()-4);
	//strNoSuffixOut = strFileOut.Left(strFileOut.GetLength()-4);

	//CString strAuxFile;	
	//strAuxFile = strNoSuffixIn + L".aux";

	//CString strAuxFileOut;
	//strAuxFileOut = strNoSuffixOut + L".aux";

	//CString strRrdFile;
	//strRrdFile = strNoSuffixIn +L".rrd";

	//CString strRrdFileOut;
	//strRrdFileOut = strNoSuffixOut +L".rrd";

	//_file.open(strAuxFile,std::ios::in);
	//if (_file)
	//{			

	//	BOOL ret= CopyFile(strAuxFile,strAuxFileOut,TRUE);		
	//	_file.close();
	//}

	////////////////////////////////////////////////////////////////////////////
	//std::fstream _file_rrd;		

	//_file_rrd.open(strRrdFile,std::ios::in);
	//if (_file_rrd)
	//{			

	//	BOOL ret= CopyFile(strRrdFile,strRrdFileOut,TRUE);		
	//	_file.close();
	//}
}

int CDeuRasterTrans::SetLTPointAndPix( GDALDataset *poDS , GDALDataset *poDSOut,double x,double y, double pix_x ,double pix_y)
{
	double          adfGeoTransformOut[6];
	poDS->GetGeoTransform(adfGeoTransformOut);
	//转换后原点

	//定制图幅
	if(m_bSpecifiedFrame)
	{
		x = m_dbLeft ;
		y = m_dbTop ;
		pix_x = m_dbPixX ;
		pix_y = m_dbPixY ; 
	}

	adfGeoTransformOut[0] = x ; //6位，y,东方向或经度，为了容易分辨，所有的X为横轴坐标，所有的Y为纵轴坐标
	adfGeoTransformOut[3] = y ; //7位，x,北方向或纬度，为了容易分辨，所有的X为横轴坐标，所有的Y为纵轴坐标

	adfGeoTransformOut[1] = pix_x ; 
	adfGeoTransformOut[5] = pix_y ;

	adfGeoTransformOut[2] = 0;
	adfGeoTransformOut[4] = 0;

	CPLErr err2 = poDSOut->SetGeoTransform(adfGeoTransformOut);

	return 0;
}

int CDeuRasterTrans::ReadWriteRasterFile(GDALDataset * poDS , GDALDataset * poDSOut ,int iTransModel ,int iResampling )
{
	int nImgSizeX = poDS->GetRasterXSize();
	int nImgSizeY = poDS->GetRasterYSize();

	int nImgSizeXOut = poDSOut->GetRasterXSize();
	int nImgSizeYOut = poDSOut->GetRasterYSize();

	//////////////////////////////////////////////////////////////////////////
	//获得图像的颜色类型
	GDALRasterBand* poBand = poDS->GetRasterBand(1);	
	unsigned int iColorDataType = GDALGetRasterDataType( poBand );
	unsigned int iDataTypeSize = GDALGetDataTypeSize( (GDALDataType)iColorDataType );
	int nByteSize = iDataTypeSize / 8 ;

	GDALRasterBand* poBand2 = poDSOut->GetRasterBand(1);	
	unsigned int iColorDataType2 = GDALGetRasterDataType( poBand2 );
	unsigned int iDataTypeSize2 = GDALGetDataTypeSize( (GDALDataType)iColorDataType2 );
	int nByteSize2 = iDataTypeSize2 / 8 ;

	//////////////////////////////////////////////////////////////////////////
	//全文件的原点
	//adfGeoTransform[0] y,东方向或经度，为了容易分辨，所有的X为横轴坐标，所有的Y为纵轴坐标
	//adfGeoTransform[1] Pix_to_X 分辨率
	//adfGeoTransform[2] 0
	//adfGeoTransform[3] x,北方向或纬度，为了容易分辨，所有的X为横轴坐标，所有的Y为纵轴坐标
	//adfGeoTransform[4] 0
	//adfGeoTransform[5] Pix_to_Y 分辨率
	double          adfGeoTransformOut[6];
	poDSOut->GetGeoTransform(adfGeoTransformOut);
	double Pix_to_X = adfGeoTransformOut[1];
	double Pix_to_Y = adfGeoTransformOut[5];

	double GeoXOut =  adfGeoTransformOut[0];
	double GeoYOut =  adfGeoTransformOut[3];

	int nBandCount;
	nBandCount=poDS->GetRasterCount();

	int nBandCount2;
	nBandCount2=poDSOut->GetRasterCount();
	
	//double **Pt;
	//double **GrayVal;
	
	//if( iResampling )
	//ResamplingPoint(Pt, m_InvPara ,nImgSizeX , nImgSizeY ,poDS,GrayVal );
	//else    { };

	switch(iTransModel)
	{
		case MODEL_TRANS_ALL_GRID:
		case MODEL_TRANS_ALL_Poly1:
		case MODEL_TRANS_ALL_Poly2:
		case MODEL_TRANS_ALL_D2P4:
		case MODEL_TRANS_ALL_AFFINE:
		case MODEL_TRANS_ALL_BURSA:
		case MODEL_TRANS_QUICK_GRID:
		case MODEL_TRANS_QUICK_Poly1:
		case MODEL_TRANS_QUICK_Poly2:
		case MODEL_TRANS_QUICK_D2P4:
		case MODEL_TRANS_QUICK_AFFINE:
		case MODEL_TRANS_QUICK_BURSA:
		//case MODEL_GRID:
		{
			//直接复制
			int AllBlocks, BlockPerRow, BlockPerCol;//所有block count
			int MiniSize = 256;						//10*10
			int MaxSize = 64;						//分成256*64，通过循环对每一块进行处理	
			BlockPerRow = nImgSizeX   ;
			BlockPerCol = 1 ;
			AllBlocks = BlockPerCol * BlockPerRow ;
			
			double all_count = AllBlocks*nBandCount;
			double done_count = 0;
			double done_old_count = 0;
			unsigned int  Percent=(double)((double)done_count/(double)all_count)*100;
			::SendMessage(m_hwnd,WM_PROGRESS,0,Percent);
			DEU_CALLBACK(WM_PROGRESS,0,Percent);
			
			const int BuffSize = 10;
			int Width =  nImgSizeX;
			int Height = BuffSize ;
			void* pScanBlock = (void *) /*CPLMalloc*/malloc(nByteSize*(Width)*(Height));

			for (int iband = 0;iband < nBandCount;iband++)
			{
				GDALRasterBand* poBand = poDS->GetRasterBand(iband+1);		
				GDALRasterBand* poBandOut = poDSOut->GetRasterBand(iband+1);

				memset( pScanBlock , 0 , nByteSize*(Width)*(Height) );
				for (int iblock = 0 ; iblock < nImgSizeY; iblock+=Height)
				{
					//读每个block ，分块转换
					double all_count = AllBlocks*nBandCount;
					double done_count = iband*AllBlocks+iblock;
					double done_old_count = 0;
					unsigned int  Percent=(double)((double)done_count/(double)all_count)*100;
					::SendMessage(m_hwnd,WM_PROGRESS,0,Percent);
					DEU_CALLBACK(WM_PROGRESS,0,Percent);
					
					int LTPt_x = 0;
					int LTPt_y = iblock;

					Height = BuffSize ;
					if(LTPt_y + Height > nImgSizeY)
					{
						Height = nImgSizeY - LTPt_y ;
					}

					CPLErr err;
					int iSrcWidth = nImgSizeX ;
					int iSrcHeight = Height ;

					if(( LTPt_x >= 0 ) && ( LTPt_x + iSrcWidth <= nImgSizeX ) && (LTPt_y >= 0) && (LTPt_y + iSrcHeight <= nImgSizeY))
					{
						err = poBand->RasterIO( GF_Read, LTPt_x, LTPt_y,iSrcWidth,iSrcHeight, 
												pScanBlock,iSrcWidth,iSrcHeight, (GDALDataType)iColorDataType,0, 0 );//读取的buff大于block，保证不出现黑线
						if(err)
						{
							LOGSTR("读取栅格文件错误");
						}
					}

					if (err == CE_None)
					{		
						int LTPT_x_out = LTPt_x;//+dx;//(LT_des_OriginX - des_OriginX)*X_to_Pix;//x栅格元
						int LTPT_y_out = LTPt_y;//s+dy;//(LT_des_OriginY - des_OriginY)*Y_to_Pix;//y栅格元
						//////////////////平移量//////////////////////////////////////////////////////////				

						poBandOut->RasterIO( GF_Write, LTPT_x_out, LTPT_y_out,Width,Height, 
											 pScanBlock,Width,Height, (GDALDataType)iColorDataType,0, 0 );//写转换后的block
						poDSOut->FlushCache();
					}
				}//each block
			}//each band

			free( pScanBlock );
		}
		break;
		
		//投影进行重采样算法（2011-10-27）
		case MODEL_GAUSS:
		case MODEL_TM:
		case MODEL_UTM:		
		case MOD_AFFINE:		//仿射变换
		case MOD_POLYNOMIAL1:	//一阶多项式
		case MOD_POLYNOMIAL2:	//二阶多项式
		case MOD_POLYNOMIAL3:	//三阶多项式
		case MOD_POLYNOMIAL4:	//四阶多项式
		case MODEL_BURSA:		//Brusa
		case MODEL_D2P4:		//平面四参数
		case MODEL_GRID:		//格网法
			//重采样点
			//先读目标位置
			//然后计算在原图中的位置
			//单点重采样
			{
			int AllBlocks, BlockPerRow, BlockPerCol;//所有block count
			//int MiniSize = 256; //10*10
			//int MaxSize = 64;//分成256*64，通过循环对每一块进行处理	

			BlockPerRow =  1 ;
			BlockPerCol = nImgSizeYOut  ;
			AllBlocks = BlockPerCol * BlockPerRow ;
			//////////////////////////////////////////////////////////////////////////
			//double all_count = AllBlocks*nBandCount;
			//double done_count = 0;
			//double done_old_count = 0;
			//unsigned int  Percent=(double)((double)done_count/(double)all_count)*100;
			//::SendMessage(m_hwnd,WM_PROGRESS,0,Percent);
			//DEU_CALLBACK(WM_PROGRESS,0,Percent);
			//////////////////////////////////////////////////////////////////////////
			
			//分配临时存储空间
			int Width =  nImgSizeXOut;
			int Height = 1 ;

			char* pScanBlock = /*(char *)*/ /*CPLMalloc*/new char[ nByteSize*(Width)*(Height)*nBandCount];
			memset(pScanBlock , 0 , nByteSize*(Width)*(Height)*nBandCount);

			void *GrayVal = /*(void*)*/ /*CPLMalloc*/new char[ nByteSize*nBandCount ];
			memset(GrayVal , 0 , nByteSize*nBandCount);//nBandCount由潘万坤2010.11.21日添加，用于多个波段同时转换

			double StartTick3(0),EndTick3(0);

			//创建栅格缓冲区
			//int iInitRow = 300;
			
			CPLErr err;

//			for (int iband = 0;iband < nBandCount;iband++)
//				{//每个band
				
//					GDALRasterBand* poBand = poDS->GetRasterBand(iband+1);		
//					GDALRasterBand* poBandOut = poDSOut->GetRasterBand(iband+1); //改变单波段转换模式，实现数据集转换
				
					//加载源栅格数据到缓冲区
					int *panBandMap=new int[nBandCount];
					for (int i=0;i<nBandCount;i++)
					{
						panBandMap[i]=nBandCount-i;
					}
//------------------------------删除缓冲区---------------start---------------------------------------
					//void * pblock = malloc(nByteSize*(nImgSizeX)*nBandCount);
					//for(int i = 0 ; i < iInitRow ; i++ )
					//{
//						err = poBand->RasterIO( GF_Read, 0, i,nImgSizeX,1, 
//									pblock,nImgSizeX,1, (GDALDataType)iColorDataType,0, 0 );//写转换后的block

					//	err = poDS->RasterIO(GF_Read,0,i,nImgSizeX,1,
					//		pblock,nImgSizeX,1,(GDALDataType)iColorDataType,nBandCount,panBandMap,nBandCount,nBandCount*Width,1);

					//	buf.push_back( pblock , i);
					//}

//					buf.pBand  =  (void*)poBand ;
//					buf.poDS  =   (void *)poDS;

//------------------------------删除缓冲区---------------end---------------------------------------



//--------------------------------------读写配置文件，实现程序断点续转------------------------------------------
					CString									strPath = _T("");
					int										nPos(0);
					::GetModuleFileName(NULL, strPath.GetBufferSetLength(MAX_PATH+1), MAX_PATH);
					strPath.ReleaseBuffer();

					nPos = strPath.ReverseFind('\\');
					strPath = strPath.Left(nPos);
					strPath=strPath+"\\Rate.ini";
					char num[20]= _T("");

					int Rate=0;
					Rate=GetPrivateProfileInt(_T("SECTION"),_T("Rate"),0,(LPCTSTR)strPath);
//--------------------------------------读写配置文件，实现程序断点续转------------------------------------------

                    //for (int iblock = 0 ; iblock < AllBlocks; iblock++)
					for (int iblock = 0 ; iblock < nImgSizeYOut ; iblock++)//每条扫描线
					{
						//读每个block ，分块转换
						StartTick3 = ::GetTickCount();

//						double all_count = AllBlocks*nBandCount;
//						double done_count = iband*AllBlocks+iblock;

						double all_count = AllBlocks;
						double done_count = iblock;

						double done_old_count = 0;
						unsigned int  Percent=(double)((double)done_count/(double)all_count)*100;
						::SendMessage(m_hwnd,WM_PROGRESS,0,Percent);
						DEU_CALLBACK(WM_PROGRESS,0,Percent);
						
						if (iblock < Rate)
						{
							Sleep(100*TIME_WAIT/nImgSizeYOut);
							continue;
						}

						//每个block的左上角点
						//int LTPt_x = (iblock % BlockPerRow) * MiniSize ;
						//int LTPt_y = (iblock /BlockPerRow)* MiniSize;//转换前LTPT的位置
						int LTPt_x = 0;
						int LTPt_y = iblock;
						int _H,_W=0;
						_W= Width;
						_H= Height;

						//if((LTPt_x+ Width > nImgSizeX))
						//_W = nImgSizeXOut - LTPt_x;

						//if(LTPt_y+ Height > nImgSizeY)
						//_H = nImgSizeYOut - LTPt_y;	

						//先读目标位置
						//目标矩形块位置为 LTPt_x, LTPt_y, _W, _H
						//循环每个点，进行重采样

						//EndTick3 = GetTickCount();

						StartTick3 = ::GetTickCount();
						for( int row = 0 ; row < _H ; row++)
						{	
							for( int col = 0 ; col < _W ; col++)
							{
								StartTick3 = ::GetTickCount();

								double pt[3];
								pt[0] = (LTPt_x + col ) * Pix_to_X + GeoXOut;
								pt[1] = (LTPt_y + row ) * Pix_to_Y + GeoYOut;
								pt[2] = 0;
								
								//EndTick3 = GetTickCount();
								//StartTick3 = ::GetTickCount();
																			
								int ret = ResamplingPoint( pt, m_InvPara , nImgSizeX, nImgSizeY, poDS ,/* buf, */GrayVal);
 								if(ret != 0)
 								{
 									LOGSTR("无法计算数据的改正量，已成功终止进程。");
 									throw(0);
 									return 0;
 								}

								EndTick3 = GetTickCount();
								//StartTick1 = ::GetTickCount();
								
								if(GrayVal< 0) GrayVal =0;
														
								memcpy( (char*) (pScanBlock + (row * BlockPerRow + col) * nByteSize*nBandCount) , GrayVal , nByteSize*nBandCount );

								EndTick3 = GetTickCount();
							}//for col
						}//for row

						EndTick3 = GetTickCount();
						
						//DEU_CALLBACK( WM_TICKCOUNT , 0 , EndTick3 - StartTick1 );

						//StartTick1 = ::GetTickCount();

						//err = poBandOut->RasterIO( GF_Write, LTPt_x, LTPt_y,_W,_H, 
						//			pScanBlock,_W,_H, (GDALDataType)iColorDataType,0, 0 );//写转换后的block

						err = poDSOut->RasterIO(GF_Write,LTPt_x,LTPt_y,_W,_H,pScanBlock,
												_W,_H,(GDALDataType)iColorDataType2,nBandCount2,panBandMap,nBandCount2*nByteSize2,nBandCount2*Width*nByteSize2,nByteSize2);
						if( err )
						{
							LOGSTR("ERROR: 写数据错误.");
						}

						poDSOut->FlushCache();

						EndTick3 = GetTickCount();

				        Rate=iblock;
						sprintf(num,"%d",Rate);
						WritePrivateProfileString(_T("SECTION"),_T("Rate"),num,(LPCTSTR)strPath);
						
					//}//each block
				}//each band

				delete GrayVal ;
				delete pScanBlock ;
				delete [] panBandMap;
			}

		default:
			break;
	}//end switch

	return 0;
		
}

//计算改正量和分辨率
//算法：
//1.平移：用源文件4角点取平均偏移量转换;用源文件所有角点取平均偏移量转换;
//2.投影、反投影：计算目标坐标系分辨率，再计算偏移量;（2011-10-4）
//                只计算分辨率，不再计算偏移量（2011-10-27）
//3.重采样：不需计算偏移量

// dx，dy为改正量
// dbDesPix_to_X ， dbDesPix_to_Y为分辨率
int CDeuRasterTrans::CalculateOffset(double *adfGeoTransform,int nImgSizeX,int nImgSizeY,int iTransModel,double &dx,double &dy , double &dbDesPix_to_X, double &dbDesPix_to_Y)
{
	double sumx=0,sumy=0;
	double Pix_to_X = adfGeoTransform[1];
	double Pix_to_Y = adfGeoTransform[5];
	double LT_X = adfGeoTransform[0];//top left x
	double LT_Y = adfGeoTransform[3];

	switch(iTransModel)
	{
		case MODEL_TRANS_QUICK_GRID:
		case MODEL_TRANS_QUICK_Poly1:
		case MODEL_TRANS_QUICK_Poly2:
		case MODEL_TRANS_QUICK_D2P4:
		case MODEL_TRANS_QUICK_AFFINE:
		case MODEL_TRANS_QUICK_BURSA:
			{
				//图廓点平移法
				double geo_x_[4],geo_y_[4],des_geo_x_,des_geo_y_;
				
				geo_x_[0] = geo_x_[2] = adfGeoTransform[0] ;//6位，y,东方向或经度，为了容易分辨，所有的X为横轴坐标，所有的Y为纵轴坐标
				geo_y_[0] = geo_y_[1] = adfGeoTransform[3] ;//7位，x,北方向或纬度，为了容易分辨，所有的X为横轴坐标，所有的Y为纵轴坐标
				geo_x_[1] = geo_x_[3] = geo_x_[0] + nImgSizeX * Pix_to_X;
				geo_y_[2] = geo_y_[3] = geo_y_[0] - nImgSizeY * Pix_to_Y;
		
				for(int i=0;i<4;i++)
				{
					_coord_transf( m_Para,m_TransModel , 1,&geo_y_[i],&geo_x_[i],0,&des_geo_y_,&des_geo_x_,0);
					sumx+=des_geo_x_-geo_x_[i];
					sumy+=des_geo_y_-geo_y_[i];
				}

				dx = sumx/4 ;
				dy = sumy/4 ;
				dbDesPix_to_X = Pix_to_X;
				dbDesPix_to_Y = Pix_to_Y;
			}
			break;

		case MODEL_TRANS_ALL_GRID:
		case MODEL_TRANS_ALL_Poly1:
		case MODEL_TRANS_ALL_Poly2:
		case MODEL_TRANS_ALL_D2P4:
		case MODEL_TRANS_ALL_AFFINE:
		case MODEL_TRANS_ALL_BURSA:
			{
				//所有点
				double geo_x_,geo_y_,des_geo_x_,des_geo_y_;				
				for(int i=0;i<nImgSizeX;i++)
				{
					for(int j=0;j<nImgSizeY;j++)
					{
						geo_x_ = adfGeoTransform[0] + j *  Pix_to_X; //北方向分辨率
						geo_y_ = adfGeoTransform[3] + i *  Pix_to_Y; //OriginY,OriginX表示东方向和北方向

						//yzg 2012-8-30 修改 begin
						//_coord_transf( m_Para,m_TransModel , 1,&geo_x_,&geo_y_,0,&des_geo_x_,&des_geo_y_,0);
						_coord_transf( m_Para,m_TransModel , 1,&geo_y_,&geo_x_,0,&des_geo_y_,&des_geo_x_,0);
						//yzg 2012-8-30 修改 end

						sumx += des_geo_x_ - geo_x_;
						sumy += des_geo_y_ - geo_y_;	
					}
				}

				//double dx ,dy;
				dx=sumx/(nImgSizeX*nImgSizeY);// -OriginX[0];//X_to_Pix* X_to_Pix;
				dy=sumy/(nImgSizeX*nImgSizeY);//-OriginY[0];///Y_to_Pix* Y_to_Pix;	

				dbDesPix_to_X = Pix_to_X;
				dbDesPix_to_Y = Pix_to_Y;
			}
			break;

		case MODEL_GAUSS:
		case MODEL_TM:	
		case MODEL_UTM:		
		{
			//不再计算新的角点,该角点在创建文件时算出（2011-10-27）
			//角点直接投影（2011-10-4）
			//_coord_transf( m_Para,m_TransModel , 1, &LT_Y, &LT_X,0,&y,&x,0);

			//计算像素分辨率
			//X---detalL
			//Y---B
			//int CDeuRasterTrans::CalculatePixXY(  double adfGeoTransform[6]  , projPJ m_srcPJ ,double & dx ,double & dy )
			CalculatePixXY( adfGeoTransform ,  nImgSizeX, nImgSizeY , m_srcPJ , dbDesPix_to_X ,  dbDesPix_to_Y);


//#define _R
#ifdef _R
			double M = m_srcPJ->get_M(LT_Y /*+ nImgSizeY * Pix_to_Y * 0.5*/ );
			double N = m_srcPJ->get_N(LT_Y /*+ nImgSizeY * Pix_to_Y * 0.5*/ );
			double R = /*sqrt(M * N);*/(M + N) / 2;
			dbDesPix_to_X = R * Pix_to_X * DEG_TO_RAD;
			dbDesPix_to_Y = -dbDesPix_to_X;
#else

			dbDesPix_to_X = /*R * Pix_to_X * DEG_TO_RAD;*/
				/*( abs(dbDesPix_to_X) + abs(dbDesPix_to_Y))/2 */
				sqrt( abs(dbDesPix_to_X) * abs(dbDesPix_to_Y) ) ;
			dbDesPix_to_Y = -dbDesPix_to_X;

#endif
			dx = 0;
			dy = 0;

			break;
		}			
		case MOD_AFFINE:
		case MOD_POLYNOMIAL1:
		case MOD_POLYNOMIAL2:
		case MOD_POLYNOMIAL3:
		case MOD_POLYNOMIAL4:
		case MODEL_BURSA:
		case MODEL_D2P4:
		case MODEL_GRID:	
			dbDesPix_to_X = Pix_to_X;
			dbDesPix_to_Y = Pix_to_Y;
			dx = 0;
			dy = 0;

			break;
			
		default:
			LOGSTR("计算改正量时错误，无法识别的转换模型。");
			break;
	}// end switch

	return 0;
}

int	CDeuRasterTrans::ResamplingPoint(double *Pt,double* InvPara ,int nImgSizeX , int nImgSizeY ,GDALDataset *poDS,/*CDeuBuffer & buf,*/void *GrayVal )
{
	int result = 0 ;
	double StartTick1(0),EndTick4(0);	

	double geo_src_x = Pt[0];
    double geo_src_y = Pt[1];
	double geo_src_z = Pt[2];

	double des_geo_x = 0;
	double des_geo_y = 0;
	double des_geo_z = 0;

	StartTick1 = ::GetTickCount();

	//目标地理坐标得到源地理坐标
    result = _inv_coord_transf( InvPara, m_TransModel, 1, &geo_src_y, &geo_src_x, &geo_src_z, &des_geo_y, &des_geo_x, &des_geo_z );		

	EndTick4 = ::GetTickCount();

	//StartTick1 = ::GetTickCount();

	double dbDesPt[3];
	dbDesPt[0] = des_geo_x /*= 118.11311184717584*/;
	dbDesPt[1] = des_geo_y /*= 24.564690809934998*/;
	dbDesPt[2] = des_geo_z;

	//EndTick4 = ::GetTickCount();

	StartTick1 = ::GetTickCount();

	switch( m_Resampling)
	{
	case RESAMPLING_NEAREST:
		Resampling_Nearest( dbDesPt, nImgSizeX , nImgSizeY ,poDS ,/* buf,*/GrayVal);
		break;
	case RESAMPLING_BILINEAR:
		Resampling_Bilinear( dbDesPt, nImgSizeX , nImgSizeY ,poDS, /*buf, */GrayVal);
		break;	
	case RESAMPLING_BICUBIC:
		Resampling_Bicubic( dbDesPt, nImgSizeX , nImgSizeY ,poDS,/* buf, */GrayVal);
		break;	
	default:
		break;
	}
	
	EndTick4 = ::GetTickCount();

	return result;
}

GDALDataset * CDeuRasterTrans::CreateRasterFile( const char * szFileNameOut,int iTransModel,GDALDataset *poDS ,const char *pszDesDriver, int nBands,GDALDataType eType, char ** /*papszOptions3w*/ ,double newPix_to_X, double newPix_to_Y, double &outNewLT_X, double &outNewLT_Y )
{
	char * szLog = (char*) malloc ( 300 * sizeof (char) );

	int nImgSizeX=poDS->GetRasterXSize();
	int nImgSizeY=poDS->GetRasterYSize();

	//////////////////////////////////////////////////////////////////////////
	//获得图像的颜色类型
	GDALRasterBand* poBand = poDS->GetRasterBand(1);	
	unsigned int iColorDataType = GDALGetRasterDataType( poBand );
	unsigned int iDataTypeSize = GDALGetDataTypeSize( (GDALDataType)iColorDataType );
	int nByteSize = iDataTypeSize / 8;
	
	//////////////////////////////////////////////////////////////////////////
	//全文件的原点
	//adfGeoTransform[0] y,东方向或经度，为了容易分辨，所有的X为横轴坐标，所有的Y为纵轴坐标
	//adfGeoTransform[1] Pix_to_X 分辨率
	//adfGeoTransform[2] 0
	//adfGeoTransform[3] x,北方向或纬度，为了容易分辨，所有的X为横轴坐标，所有的Y为纵轴坐标
	//adfGeoTransform[4] 0
	//adfGeoTransform[5] Pix_to_Y 分辨率
	double          adfGeoTransform[6];
	poDS->GetGeoTransform(adfGeoTransform);

	double Pix_to_X = adfGeoTransform[1];//分辨率
	double Pix_to_Y = adfGeoTransform[5];
	double LTPt_x = adfGeoTransform[0];
	double LTPt_y = adfGeoTransform[3];

	//////////////从连接池获得目标数据源//////////////////////////////////////////////////////////////
	GDALDataset *poDSOut;   //GDAL数据集
	//const char *pszFormat = (LPCSTR)_bstr_t(DesDriver);//"GTiff";
	GDALDriver *poDriver;
	
	poDriver = GetGDALDriverManager()->GetDriverByName(pszDesDriver);
	if( poDriver == NULL )
		return	NULL;

	char ** papszOptions = new char*[4]; //差标志位，tfw, split
	char * pszOptions0 = new char [50];
	char * pszOptions1 = new char [50];
	char * pszOptions2 = new char [50];	
	char * pszOptions3 = new char [50];	

	strcpy(pszOptions0 ,"TFW=TRUE");
	papszOptions[0] = pszOptions0;

	strcpy(pszOptions1 ,"HFA_USE_RRD=TRUE");
	papszOptions[1] = pszOptions1;

	if(m_bHaveIGE)
	{		
		strcpy(pszOptions2 ,"USE_SPILL=TRUE");
		papszOptions[2] = pszOptions1;//若为true,则转为.img
	}
	else
	{
		strcpy(pszOptions2 ,"\0");
		papszOptions[2] = NULL;
	}

	strcpy(pszOptions3 ,"\0");
	papszOptions[3] = NULL;

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	int nBandCount;
	nBandCount=poDS->GetRasterCount();

	switch(iTransModel)
		{
		case MODEL_TRANS_ALL_GRID:
		case MODEL_TRANS_ALL_Poly1:
		case MODEL_TRANS_ALL_Poly2:
		case MODEL_TRANS_ALL_D2P4:
		case MODEL_TRANS_ALL_AFFINE:
		case MODEL_TRANS_ALL_BURSA:
		case MODEL_TRANS_QUICK_GRID:
		case MODEL_TRANS_QUICK_Poly1:
		case MODEL_TRANS_QUICK_Poly2:
		case MODEL_TRANS_QUICK_D2P4:
		case MODEL_TRANS_QUICK_AFFINE:
		case MODEL_TRANS_QUICK_BURSA:
			{
				//如果平移，则直接创建
				sprintf( szLog , "文件名=%s SizeX =%d SizeY =%d BandCount =%d Type = %d Options = %s " ,szFileNameOut ,  nImgSizeX , nImgSizeY , nBandCount ,eType ,papszOptions[0] );
				LOGSTR(szLog);

				//定制图幅
				if(m_bSpecifiedFrame)
				{
					nImgSizeX = m_lSizeX ;
					nImgSizeY = m_lSizeY ; 
				}

				poDSOut =poDriver->Create(szFileNameOut, nImgSizeX, nImgSizeY, nBandCount, eType, papszOptions );
				outNewLT_X = LTPt_x;
				outNewLT_Y = LTPt_y;
			}
			break;
		case MODEL_GAUSS:
		case MODEL_TM:
		case MODEL_UTM:
			//如果是投影，则计算新的SIZE
		case MOD_AFFINE:
		case MOD_POLYNOMIAL1:
		case MOD_POLYNOMIAL2:
		case MOD_POLYNOMIAL3:
		case MOD_POLYNOMIAL4:
		case MODEL_BURSA:
		case MODEL_D2P4:
		case MODEL_GRID:
			{
				//如果是重采样则计算新的size
				ULONG newImgSizeX,newImgSizeY = 0;
				
				//获得目标图中4个角点坐标
				double geo_x_[4],geo_y_[4],des_geo_x_[4],des_geo_y_[4];
				geo_x_[0]= geo_x_[2]= adfGeoTransform[0];//6位，y,东方向或经度，为了容易分辨，所有的X为横轴坐标，所有的Y为纵轴坐标
				geo_y_[0]= geo_y_[1]= adfGeoTransform[3];//7位，x,北方向或纬度，为了容易分辨，所有的X为横轴坐标，所有的Y为纵轴坐标
				geo_x_[1]= geo_x_[3]= geo_x_[0]+nImgSizeX*Pix_to_X;
				geo_y_[2]=geo_y_[3]=geo_y_[0]+ nImgSizeY*Pix_to_Y;
			
				_coord_transf( m_Para,m_TransModel ,4,geo_y_,geo_x_,0,des_geo_y_,des_geo_x_,0);

				double pim_x_=des_geo_x_[0];
				double pim_y_=des_geo_y_[0];
				double max_x_ = 0;
				double min_x_ = 0;
				double max_y_ = 0;
				double min_y_ = 0;

				max_x_ = des_geo_x_[0];
				max_y_ = des_geo_y_[0];
				min_x_ = des_geo_x_[0];
				min_y_ = des_geo_y_[0];

				for(int i=1;i<4;i++)
				{					
					max_x_ = (des_geo_x_[i] > max_x_)? des_geo_x_[i] : max_x_ ;
					min_x_ = (des_geo_x_[i] < min_x_)? des_geo_x_[i] : min_x_;
					max_y_ = (des_geo_y_[i] > max_y_)? des_geo_y_[i] : max_y_;
					min_y_ = (des_geo_y_[i] < min_y_)? des_geo_y_[i] : min_y_;
				}
		
				newImgSizeX = abs((max_x_-min_x_)/newPix_to_X)+1;
				newImgSizeY = abs((max_y_-min_y_)/newPix_to_Y)+1;
				
				sprintf( szLog , "文件名=%s SizeX =%d SizeY =%d BandCount =%d Type = %d Options = %s " ,szFileNameOut ,  newImgSizeX , newImgSizeY , nBandCount ,eType ,papszOptions[0] );

				LOGSTR(szLog);

				//上下左右加1,角点向左上移动1，1
				//定制图幅
				if(m_bSpecifiedFrame)
				{
					newImgSizeX = m_lSizeX - 2 ;
					newImgSizeY = m_lSizeY - 2 ; 
				}

				/*if(newImgSizeX * newImgSizeY > 2000000000 &&  m_bHaveIGE == false )
				{
					LOGSTR("不允许创建过大的栅格文件，转换终止！");
					return NULL;
				}*/   //  大数据的判断不完善-------潘万坤 2012 11 30

				CString  str(pszDesDriver);
				if (str=="AAIGrid")
				{
					poDSOut = poDriver->CreateCopy(szFileNameOut, poDS,FALSE,NULL,NULL,NULL );
				}
				else
				{
					if (access(szFileNameOut,0)==0)
					{
						poDSOut = (GDALDataset *) GDALOpen(szFileNameOut, GA_Update);
						if( poDSOut == NULL )
						{	
							LOGSTR("打开栅格文件失败!")
						} 
					}
					else
					{
						CString									strPath = _T("");
						int										nPos(0);
						::GetModuleFileName(NULL, strPath.GetBufferSetLength(MAX_PATH+1), MAX_PATH);
						strPath.ReleaseBuffer();

						nPos = strPath.ReverseFind('\\');
						strPath = strPath.Left(nPos);
						strPath=strPath+"\\Rate.ini";
						char num[2]= _T("");
					    int Rate=0;
						sprintf(num,"%d",Rate);
						WritePrivateProfileString(_T("SECTION"),_T("Rate"),num,(LPCTSTR)strPath);

			            poDSOut = poDriver->Create(szFileNameOut, newImgSizeX+2, newImgSizeY+2, nBandCount, eType, papszOptions );
					}
				}

				outNewLT_X = min_x_ - 1 * newPix_to_X ;
				outNewLT_Y = max_y_ - 1 * newPix_to_Y ;
			}

			break;
		default:
			//写错误日志
			LOGSTR("创建栅格文件时发生错误，无法识别的转换模型。");
			break;
		}//end iTransModel switch

	free( szLog );
	delete papszOptions ;
	delete pszOptions0 ;	
	delete pszOptions1 ;	
	delete pszOptions2 ;	
	delete pszOptions3 ;

	return poDSOut;
}

//共用
HRESULT CDeuRasterTrans::CoordTransFile(const CString& FileName, const CString& SrcDriver, const CString& FileNameOut, const CString& DesDriver,UINT Id)
{
	LOGSTR(":CoordRasterTransFile");

	CString       strFileOut(FileNameOut);
	CString       strFileName;
	CString       strFile;   //需要确保存在的单纯文件夹
	CString       strFileTemp;
	int           iStart = 0;

	_bstr_t _bstr_filename_log = FileName;
	_bstr_t _bstr_inDriver_log = SrcDriver;
	_bstr_t _bstr_filenameout_log = FileNameOut;
	_bstr_t _bstr_outDriver_log = DesDriver;

	LOGSTR((LPSTR)_bstr_filename_log);
	LOGSTR((LPSTR)_bstr_inDriver_log);
	LOGSTR((LPSTR)_bstr_filenameout_log);
	LOGSTR((LPSTR)_bstr_outDriver_log);

	strFileName = strFileOut.Mid(strFileOut.ReverseFind('\\')+1);
	strFile = strFileOut.Mid(0, strFileOut.GetLength()-strFileName.GetLength());

	while (iStart >= 0)
	{
		iStart = strFile.Find(_T("\\"), iStart+1);
		strFileTemp = strFile.Mid(0, iStart);
		if (!FileFolderExists(strFileTemp) && !strFileTemp.IsEmpty())
		{
			CreateDirectory(strFileTemp, NULL);
		}
	}

	LPCSTR szFileName ;

	USES_CONVERSION;
	szFileName = FileName.GetString();

	LOG_START;	
	LOG_START_HEADER(szFileName);
	START_TIME;

	//////////////////////////////////////////////////////////////////////////
	//获得源数据源
	//////////////////////////////////////////////////////////////////////////
	GDALDataset *poDS;   //GDAL数据集
	GDALAllRegister();

	poDS = (GDALDataset *) GDALOpen(szFileName, GA_ReadOnly );
	if( poDS == NULL )
	{	
		LOGSTR("打开栅格文件失败!");
		END_TIME;
		LOG_USED_TIME;
		LOG_END;
		LOGSTR("=====================================================================");
		return S_FALSE;
	} 

	//获取图像的尺寸
	int nImgSizeX=poDS->GetRasterXSize();
	int nImgSizeY=poDS->GetRasterYSize();

	int nBandCount;
	nBandCount=poDS->GetRasterCount();

	//获得图像的颜色类型
	GDALRasterBand* poBand = poDS->GetRasterBand(1);	
	unsigned int iColorDataType = GDALGetRasterDataType( poBand );
	unsigned int iDataTypeSize = GDALGetDataTypeSize( (GDALDataType)iColorDataType );
	int nByteSize = iDataTypeSize / 8;

	//////////////////////////////////////////////////////////////////////////
	//全文件的原点
	//adfGeoTransform[0] y,东方向或经度，为了容易分辨，所有的X为横轴坐标，所有的Y为纵轴坐标
	//adfGeoTransform[1] Pix_to_X 分辨率
	//adfGeoTransform[2] 0
	//adfGeoTransform[3] x,北方向或纬度，为了容易分辨，所有的X为横轴坐标，所有的Y为纵轴坐标
	//adfGeoTransform[4] 0
	//adfGeoTransform[5] Pix_to_Y 分辨率

	//////////////////////////////////////////////////////////////////////////
	//全文件的原点
	double adfGeoTransform[6];
	poDS->GetGeoTransform( adfGeoTransform );

	//转换前原点
	double OriginX = adfGeoTransform[0];//6位，y,东方向或经度，为了容易分辨，所有的X为横轴坐标，所有的Y为纵轴坐标
	double OriginY = adfGeoTransform[3];//7位，x,北方向或纬度，为了容易分辨，所有的X为横轴坐标，所有的Y为纵轴坐标
	
 	double Pix_to_X = adfGeoTransform[1];
	double Pix_to_Y = adfGeoTransform[5];
	double X_to_Pix = 1/Pix_to_X;
	double Y_to_Pix = 1/Pix_to_Y;

	CString     strTemp = _T("");
    strTemp.Format(_T("X坐标：%f"), adfGeoTransform[0]);
	LOGSTR(strTemp.GetBuffer());
	strTemp.Format(_T("%f"), adfGeoTransform[1]);
	LOGSTR(strTemp.GetBuffer());
	strTemp.Format(_T("%f"), adfGeoTransform[2]);
	LOGSTR(strTemp.GetBuffer());
	strTemp.Format(_T("Y坐标：%f"), adfGeoTransform[3]);
	LOGSTR(strTemp.GetBuffer());
	strTemp.Format(_T("%f"), adfGeoTransform[4]);
	LOGSTR(strTemp.GetBuffer());
	strTemp.Format(_T("%f"), adfGeoTransform[5]);
	LOGSTR(strTemp.GetBuffer());

	//////////////////////////////////////////////////////////////////////////
    //create file
	//平移法：目标文件大小和源图像一致
	//重采样：目标文件大小为源图像最小外接矩形
	//投影：目标文件大小和源图像一致
	/////////////////////////////////////////////////////////////////////////

	LPCSTR szFileNameOut ;
	LPCSTR pszDesDriver  ;
	szFileNameOut = FileNameOut.GetString();
	GDALDataset *poDSOut;   //GDAL数据集
	//GDALDriver *poDriver;
	pszDesDriver = DesDriver.GetString();

	LOG_WRITE_OUT(szFileNameOut);

	////////////////////////////////////////////////////////////////////////////
	//calculate offset
	//平移法:计算改正量,分辨率
	//重采样：不需要计算改正量
	//投影：直接修改角点坐标和分辨率(2011-10-4)
	//      不需要计算改正量，同重采样(2011-10-27) 
	///////////////////////////////////////////////////////////////////////////
	//double Pix_to_X = adfGeoTransform[1];//分辨率
	//double Pix_to_Y = adfGeoTransform[5];
	double dx, dy ,dbDesPix_to_X,dbDesPix_to_Y= 0;
	CalculateOffset( adfGeoTransform, nImgSizeX, nImgSizeY, m_TransModel, dx, dy, dbDesPix_to_X, dbDesPix_to_Y );

	//CreateRasterFile(szFileNameOut, nImgSizeX, nImgSizeY,poDriver,poDSOut, nBandCount, (GDALDataType)iColorDataType, papszOptions );
  	double outNewLT_X = 0;
	double outNewLT_Y = 0;
	poDSOut = CreateRasterFile(  szFileNameOut, m_TransModel, poDS , pszDesDriver,  nBandCount,(GDALDataType)iColorDataType,  NULL ,dbDesPix_to_X, dbDesPix_to_Y, outNewLT_X, outNewLT_Y);
	
	if(poDSOut == NULL)
	{
		LOGSTR("创建目标文件失败！");
		END_TIME;
		LOG_USED_TIME;
		LOG_END;
		LOGSTR("=====================================================================");
		return S_FALSE;
	}

	//最终角点 
	//平移法：原角点+改正量   
	//投影法和重采样： 直接计算最小外接矩形的角点，无改正量
 	double x = outNewLT_X + dx;
	double y = outNewLT_Y + dy;

	////////////////////////////////////////////////////////////////////////////
	//设置空间参考
		//---------------------------------------------------
	//设置空间参考
#if 1
 	OGRSpatialReference* poRSR = SetSRS(&m_SRS);
#else
	char *szProjection = new char [500];
	szProjection = (char*) poDS->GetProjectionRef();

	OGRSpatialReference* poRSR= new OGRSpatialReference();
	
	//poRSR->importFromWkt(&szProjection);
	
	poRSR->SetFromUserInput(szProjection);
#endif

	//char *szProjection = new char [500];
	char* szProjection = NULL;
	poRSR->exportToWkt(&szProjection);

	//strcpy( szProjtion ,  """PROJCS[""118.5wudaihao"",GEOGCS[""GCS_Beijing_1954"",DATUM[""D_Beijing_1954"",SPHEROID[""Krasovsky_1940"",6378245.0,298.3]],PRIMEM[""Greenwich"",0.0],UNIT[""Degree"",0.0174532925199433]],PROJECTION[""Transverse_Mercator"],PARAMETER["False_Easting",500000.0],PARAMETER["False_Northing",0.0],PARAMETER["Central_Meridian",118.5],PARAMETER["Scale_Factor",1.0],PARAMETER["Latitude_Of_Origin",0.0],UNIT["Meter",1.0]]"" );

	poDSOut->SetProjection(szProjection);

	//set LT_point and pix
	//设置左上角点和像素分辨率
	SetLTPointAndPix( poDS, poDSOut, x, y, dbDesPix_to_X, dbDesPix_to_Y  );

	//设置NoDataValue
	SetNoDataValue( poDS, poDSOut);

	//////////////////////////////////////////////////////////////////////////
	//read and write
	//平移法和投影：直接复制粘贴
	//重采样：进行重采样，写文件。
	//////////////////////////////////////////////////////////////////////////
	ReadWriteRasterFile( poDS , poDSOut ,m_TransModel ,m_Resampling);
	::SendMessage(m_hwnd,WM_PROGRESS,0,100);
	DEU_CALLBACK(WM_PROGRESS,0,100);

	GDALClose( (GDALDatasetH) poDS );

	GDALClose( (GDALDatasetH) poDSOut );

	//创建金字塔

	//计算Statistics
	ComputeStatistics(/*poDSOut*/szFileNameOut);
	//////////////////////////////////////////////////////////////////////////

	END_TIME;
	LOG_USED_TIME;
	LOG_END;
	LOGSTR("=====================================================================");

	return S_OK;
}

HRESULT CDeuRasterTrans::CoordTransFileEntry(const CString& SrcTab, const CString& SrcPath, const CString& SrcDriver, const CString& DesTab, const CString& DesPath, const CString& DesDriver, UINT Id)
{
	CString bstrSrcTab = _T("");
	CString bstrDesTab = _T("");

	//CString SrcSuf = _T("");
	//CString DesSuf = _T("");
	CString strFile = SrcTab.Mid(0, SrcTab.ReverseFind('.'));

	m_bHaveIGE = IsHaveIGE( strFile, SrcPath );

// 	if ( SrcDriver == _T("GTiff") )
// 	{
// 		SrcSuf = _T(".tif");
// 	}
// 	else if ( SrcDriver == _T("HFA") )
// 	{
// 		SrcSuf = _T(".img");
// 	}
// 	else if ( SrcDriver == _T("EHdr") )
// 	{
// 		SrcSuf = _T(".bil");
// 	}
// 	else if ( SrcDriver == _T("AAIGrid") )
// 	{
// 		SrcSuf = _T(".asc");
// 	}
// 	else if ( SrcDriver == _T("BMP") )
// 	{
// 		SrcSuf = _T(".bmp");
// 	}
// 	if ( DesDriver == _T("GTiff") )
// 	{
// 		DesSuf = _T(".tif");
// 	}
// 	else if ( DesDriver == _T("HFA") )
// 	{
// 		DesSuf = _T(".img");
// 	}
// 	else if ( DesDriver == _T("EHdr") )
// 	{
// 		DesSuf = _T(".bil");
// 	}
// 	else if ( DesDriver == _T("AAIGrid") )
// 	{
// 		DesSuf = _T(".asc");
// 	}
// 	else if ( DesDriver == _T("BMP") )
// 	{
// 		DesSuf = _T(".bmp");
// 	}

// 	bstrSrcTab = SrcPath + _T("\\") + SrcTab + SrcSuf;
// 	bstrDesTab = DesPath + _T("\\") + DesTab + DesSuf;

	bstrSrcTab = SrcPath + _T("\\") + SrcTab;
	bstrDesTab = DesPath + _T("\\") + DesTab;

	HRESULT hr = CoordTransFile(bstrSrcTab,SrcDriver,bstrDesTab,DesDriver ,Id);

	return hr;
}

int CDeuRasterTrans::_coord_transf(double *para,int iTransModel,unsigned long n, double* oriX, double* oriY, double* oriZ, double* destX, double* destY, double* destZ)
{
	int result = 0;
	//g_Mutex.acquire();

	for (int i = 0 ; i < n ; i++ )
	{
		if(destZ)
		{
			destZ[i] = oriZ[i];
		}
	}

	//根据公式，决定坐标类型。
	//int iTransModel = m_TransModel;
	switch(iTransModel)
	{
	case MOD_AFFINE:
	case MODEL_TRANS_ALL_AFFINE:
	case MODEL_TRANS_QUICK_AFFINE:  
	case MOD_POLYNOMIAL1:
		//BLH to BLH
		_CoordTransf_Poly1(para, n,oriX,oriY,destX,destY);
		break;

	case MOD_POLYNOMIAL2:
	case MODEL_TRANS_ALL_Poly2:
	case MODEL_TRANS_QUICK_Poly2:
		//xy to xy h=0
		_CoordTransf_Poly2(para, n,oriX,oriY,destX,destY);
		break;

	case MOD_POLYNOMIAL3:
		//XYZ to XYZ
		_CoordTransf_Poly2(para, n,oriX,oriY,destX,destY);
		break;

	case MOD_POLYNOMIAL4:
		//bl to bl H=0
		_CoordTransf_Poly2(para, n,oriX,oriY,destX,destY);
		break;

	case MODEL_GAUSS:
		_CoordTransf_GAUSS( m_desPJ, n,oriX,oriY,oriZ,destX,destY,destZ);
		break;

	case MODEL_TM:
		_CoordTransf_GAUSS( m_desPJ, n,oriX,oriY,oriZ,destX,destY,destZ);
		//_CoordTransf_TM(n,oriX,oriY,oriZ,destX,destY,destZ);
		break;

	case MODEL_UTM:
		_CoordTransf_UTM( m_desPJ, n,oriX,oriY,oriZ,destX,destY,destZ);
		break;

	case MODEL_TRANS_ALL_Poly1:
	case MODEL_TRANS_QUICK_Poly1:
		_CoordTransf_Poly1(para, n,oriX,oriY,destX,destY);
		break;

	case MODEL_BURSA:
	case MODEL_TRANS_ALL_BURSA:
	case MODEL_TRANS_QUICK_BURSA:
		_CoordTransf_Brusa( m_srcPJ, m_desPJ, para, n,oriX,oriY,oriZ,destX,destY,destZ);
		break;

	case MODEL_D2P4:
	case MODEL_TRANS_ALL_D2P4:
	case MODEL_TRANS_QUICK_D2P4:
		_CoordTransf_2D4P( m_srcPJ, m_desPJ, para, n,oriX,oriY,oriZ,destX,destY,destZ);
		break;

	case MODEL_GRID:
	case MODEL_TRANS_ALL_GRID:
	case MODEL_TRANS_QUICK_GRID:
		result = _CoordTransf_GRID( n,oriX,oriY,destX,destY);
		break;

	default:
		break;
	}

	return result;
}

int CDeuRasterTrans::_inv_coord_transf(double* para,int iTransModel,unsigned long n, double* oriX, double* oriY, double* oriZ, double* destX, double* destY, double* destZ)
{
	int result = 0;
	//double StartTick1(0),EndTick1(0);
	//StartTick1 = ::GetTickCount();
	//g_Mutex.acquire();

	for (int i = 0 ; i < n ; i++ )
	{
		if(destZ)
		{
			destZ[i] = oriZ[i];
		}
	}

#ifdef SLEEP
	//Sleep(50);
	for(int i = 0;i<100000;i++)
	{
		int ii = 0;
	}
#endif

	//根据公式，决定坐标类型。
	//int iTransModel = m_TransModel;
	switch(iTransModel)
	{
	case MOD_AFFINE:
	case MOD_POLYNOMIAL1:
	//case MODEL_TRANS_QUICK_AFFINE:
	//case MODEL_TRANS_ALL_AFFINE:
		//BLH to BLH
		_CoordTransf_Poly1(para, n,oriX,oriY,destX,destY);
		break;

	case MOD_POLYNOMIAL2:
	//case MODEL_TRANS_ALL_Poly2:
	//case MODEL_TRANS_QUICK_Poly2:
		//xy to xy h=0
		_CoordTransf_Poly2(para, n,oriX,oriY,destX,destY);
		break;

	case MOD_POLYNOMIAL3:
		//XYZ to XYZ
		_CoordTransf_Poly2(para, n,oriX,oriY,destX,destY);
		break;

	case MOD_POLYNOMIAL4:
		//bl to bl H=0
		_CoordTransf_Poly2(para, n,oriX,oriY,destX,destY);
		break;

	case MODEL_GAUSS:
		_CoordTransf_GAUSS( m_desPJ,  n,oriX,oriY,oriZ,destX,destY,destZ,true);
		break;

	case MODEL_TM:
		_CoordTransf_GAUSS( m_desPJ,  n,oriX,oriY,oriZ,destX,destY,destZ,true);
		//_CoordTransf_TM(n,oriX,oriY,oriZ,destX,destY,destZ);
		break;

	case MODEL_UTM:
		_CoordTransf_UTM( m_desPJ,  n,oriX,oriY,oriZ,destX,destY,destZ,true);
		break;

	//case MODEL_TRANS_ALL_Poly1:
	//case MODEL_TRANS_QUICK_Poly1:
		_CoordTransf_Poly1(para, n,oriX,oriY,destX,destY);
		break;

	case MODEL_BURSA:
	//case MODEL_TRANS_ALL_BURSA:
	//case MODEL_TRANS_QUICK_BURSA:	  
		_CoordTransf_Brusa( m_desPJ, m_srcPJ , para, n,oriX,oriY,oriZ,destX,destY,destZ,true);
		break;

	case MODEL_D2P4:
	//case MODEL_TRANS_ALL_D2P4:
	//case MODEL_TRANS_QUICK_D2P4:
		_CoordTransf_2D4P( m_desPJ,  m_srcPJ, para, n,oriX,oriY,oriZ,destX,destY,destZ,true);
		break;

	case MODEL_GRID:
	//case MODEL_TRANS_ALL_GRID:
		result = _CoordTransf_GRID( n,oriX,oriY,destX,destY,true);
		break;

	default:
		break;
	}

	//for (int i = 0 ; i < n ; i++)
	//{
	//	destY[i] += m_des_false_east;
	//}

	//g_Mutex.release();
	//EndTick1 = ::GetTickCount();

	return result;
}

HRESULT CDeuRasterTrans::RegisterWnd(LONGLONG hwnd)
{
	m_hwnd=(HWND)hwnd;

	return S_OK;
}

//dem
HRESULT CDeuRasterTrans::CoordTransDEMEntry( const CString& SrcTab,  const CString& SrcPath,  const CString& SrcDriver,  const CString& DesTab,  const CString& DesPath,  const CString& DesDriver)
{
	// TODO: 在此添加实现代码
	CString bstrSrcTab = _T("");
	CString bstrDesTab = _T("");
	
	//CString SrcSuf = _T("");
	//CString DesSuf = _T("");

	CString strFile = SrcTab.Mid(0, SrcTab.ReverseFind('.'));
	m_bHaveIGE = IsHaveIGE(strFile, SrcPath);

// 	if ( SrcDriver == _T("GTiff") )
// 	{
// 		SrcSuf = _T(".tif");
// 	}
// 	else if ( SrcDriver == _T("HFA") )
// 	{
// 		SrcSuf = _T(".img");
// 	}
// 	else if ( SrcDriver == _T("EHdr") )
// 	{
// 		SrcSuf = _T(".bil");
// 	}
// 	else if ( SrcDriver == _T("AAIGrid") )
// 	{
// 		SrcSuf = _T(".asc");
// 	}
// 	else if ( SrcDriver == _T("BMP") )
// 	{
// 		SrcSuf = _T(".bmp");
// 	}
// 	if ( DesDriver == _T("GTiff") )
// 	{
// 		DesSuf = _T(".tif");
// 	}
// 	else if ( DesDriver == _T("HFA") )
// 	{
// 		DesSuf = _T(".img");
// 	}
// 	else if ( DesDriver == _T("EHdr") )
// 	{
// 		DesSuf = _T(".bil");
// 	}
// 	else if ( DesDriver == _T("AAIGrid") )
// 	{
// 		DesSuf = _T(".asc");
// 	}
// 	else if ( DesDriver == _T("BMP") )
// 	{
// 		DesSuf = _T(".bmp");
// 	}
// 	bstrSrcTab = SrcPath +_T("\\") + SrcTab + SrcSuf;
// 	bstrDesTab = DesPath +_T("\\") + DesTab + DesSuf;

	bstrSrcTab = SrcPath +_T("\\") + SrcTab;
	bstrDesTab = DesPath +_T("\\") + DesTab;

	HRESULT hr = TransDEM(bstrSrcTab,SrcDriver,bstrDesTab,DesDriver);

	return hr;
}

//dem
HRESULT CDeuRasterTrans::TransDEM(const CString& FileName,const CString& SrcDriver,  const CString& FileNameOut,const CString& DesDriver)
{
	HRESULT hr = CoordTransDEMFile(FileName,SrcDriver,FileNameOut,DesDriver ,0);
	return hr;	
}

HRESULT CDeuRasterTrans::CalcuPolynomial1(ULONG n, DOUBLE* x, DOUBLE* y, DOUBLE* x2, DOUBLE* y2, DOUBLE* dPara)
{
	ComputeParams_Polynomial1(n,x,y,x2,y2,dPara);
	return S_OK;
}

HRESULT CDeuRasterTrans::CalcuPolynomial2(ULONG n, DOUBLE* x, DOUBLE* y, DOUBLE* x2, DOUBLE* y2, DOUBLE* dbPara)
{
	ComputeParams_Polynomial2(n,x,y,x2,y2,dbPara);

	return S_OK;
}

HRESULT CDeuRasterTrans::CalcuPolynomial3(ULONG n, DOUBLE* x, DOUBLE* y, DOUBLE* x2, DOUBLE* y2, DOUBLE* dbPara)
{
	ComputeParams_Polynomial3(n,x,y,x2,y2,dbPara);
	return S_OK;
}

HRESULT CDeuRasterTrans::CalcuPolynomial4(ULONG n, DOUBLE* x, DOUBLE* y, DOUBLE* x2, DOUBLE* y2, DOUBLE* dbPara)
{
	ComputeParams_Polynomial4(n,x,y,x2,y2,dbPara);
	return S_OK;
}

void CDeuRasterTrans::_CoordTransf_2D4P( PJ *SrcPJ , PJ *DesPJ , double * dbPara, unsigned long n, double* oriX, double* oriY, double* oriZ, double* destX, double* destY, double* destZ , bool bInv)
{
	//调用DLL,从原始坐标类型转换到空间直角坐标类型
	SHORT coordtype=0;
	SHORT destcoordtype=0;
	CString szunittype_x = _T("");
	CString szunittype_y = _T("");
	CString szunittype_z = _T("");
	CString szunittype_des_x = _T("");
	CString szunittype_des_y = _T("");
	CString szunittype_des_z = _T("");

	if(!bInv)
	{
		m_coordtype.get_CoordType(coordtype);
		m_coordtype.get_DestCoordType(destcoordtype);

		m_units.get_Unit_X(szunittype_x);
		m_units.get_Unit_Y(szunittype_y);
		m_units.get_Unit_Z(szunittype_z);
		m_units.get_Unit_desX(szunittype_des_x);
		m_units.get_Unit_desY(szunittype_des_y);
		m_units.get_Unit_desZ(szunittype_des_z);
	}
	else
	{
		m_coordtype.get_CoordType(destcoordtype);
		m_coordtype.get_DestCoordType(coordtype);

		m_units.get_Unit_X(szunittype_des_x);
		m_units.get_Unit_Y(szunittype_des_y);
		m_units.get_Unit_Z(szunittype_des_z);
		m_units.get_Unit_desX(szunittype_x);
		m_units.get_Unit_desY(szunittype_y);
		m_units.get_Unit_desZ(szunittype_z);
	}

	//原始
	double oriX_i=0;
	double oriY_i=0;
	double oriZ_i=0;

	//弧度or长度
	double unitX_i=0;
	double unitY_i=0;
	double unitZ_i=0;

	//轉換公式用到的坐标类型
	double geo_X_i=0;
	double geo_Y_i=0;
	double geo_Z_i=0;

	//转换后的空间直角坐标类型
	double Trsfmed_X_i=0;
	double Trsfmed_Y_i=0;
	double Trsfmed_Z_i=0;

	//输出坐标类型
	double desX_i=0;
	double desY_i=0;
	double desZ_i=0;

	//输出坐标类型_原始单位下
	double desX_i_ori_unit=0;
	double desY_i_ori_unit=0;
	double desZ_i_ori_unit=0;

	//double* psevenparams=m_Para;
	//m_sevenparams->get_Dx(psevenparams++);
	//m_sevenparams->get_Dy(psevenparams++);
	//m_sevenparams->get_Dz(psevenparams++);
	//m_sevenparams->get_Rx(psevenparams++);
	//m_sevenparams->get_Ry(psevenparams++);
	//m_sevenparams->get_Rz(psevenparams++);
	//m_sevenparams->get_Scale_M(psevenparams++);
	
	for (int i=0;i<n;i++)
	{
		oriX_i=oriX[i];
		oriY_i=oriY[i];
		oriZ_i=0;

		//转到弧度或米
		unitX_i=CDeuUnits::TypeToUnit(oriX_i, szunittype_x);
		unitY_i=CDeuUnits::TypeToUnit(oriY_i, szunittype_y);
		unitZ_i=CDeuUnits::TypeToUnit(oriZ_i, szunittype_z);

		switch (coordtype)
		{
		case  GEODETIC://大地
			geo_Z_i = unitZ_i;
			Gauss_bl_xy(SrcPJ,m_src_from_greenwich * DEG_TO_RAD,unitX_i,unitY_i,geo_X_i,geo_Y_i);
			
			break;
		case  GEOCENTRIC:
			pj_geocentric_to_geodetic(m_src_a,m_src_f,1,0,&unitX_i,&unitY_i,&unitZ_i);
			Gauss_bl_xy(SrcPJ,m_src_from_greenwich * DEG_TO_RAD,unitX_i,unitY_i,geo_X_i,geo_Y_i);
			geo_Z_i = unitZ_i;

			break;
		case  PLANE://平面
	
			//Gauss_xy_bl(m_ell_prj.m_Major,m_ell_prj.m_Flatening,m_ell_prj.m_Centrol_Long ,unitX_i,unitY_i,geo_X_i,geo_Y_i);
			
			geo_X_i	= unitX_i ;
			geo_Y_i = unitY_i - m_src_false_east;
			geo_Z_i = unitZ_i ;

			//DLL void FromxyHToBLH(ELLIP_PRJ Ellip_Prj,double x,double y,double h,double & B,double & L,double & H);
			break;
		default:
			//大地
			//FromBLHToXYZ(m_ell_prj,unitX_i,unitY_i,unitZ_i,geo_X_i,geo_Y_i,geo_Z_i);
			LOGSTR("error:UNKNOWN TYPE");
			break;
		}

		//调用DLL,将空间直角坐标从源坐标系到目标坐标系
		//DLL void CoorTran(double  Para[],double X0,double Y0,double Z0,double & X,double & Y,double & Z);
		//CoorTran(m_sevenparams_double,geo_X_i,geo_Y_i,geo_Z_i,Trsfmed_X_i,Trsfmed_Y_i,Trsfmed_Z_i);

		CoorTran_xy4(dbPara,geo_X_i,geo_Y_i,Trsfmed_X_i,Trsfmed_Y_i);
		Trsfmed_Z_i = geo_Z_i;

		//根据要求的输出坐标类型，从空间直角坐标转换到目标坐标类型
		switch (destcoordtype)
		{
		case  GEODETIC://大地
			Gauss_xy_bl(DesPJ,m_des_from_greenwich * DEG_TO_RAD,Trsfmed_X_i,Trsfmed_Y_i,desX_i,desY_i);
			break;

		case  GEOCENTRIC:
			desX_i = Trsfmed_X_i;
			desY_i = Trsfmed_Y_i;
			desZ_i = Trsfmed_Z_i;
			Gauss_xy_bl(DesPJ,m_des_from_greenwich* DEG_TO_RAD,Trsfmed_X_i,Trsfmed_Y_i,geo_X_i,geo_Y_i);
			pj_geodetic_to_geocentric(m_des_a,m_des_f,1,0,&desX_i,&desY_i,&desZ_i);
			break;

		case  PLANE://平面
			desX_i = Trsfmed_X_i;
			desY_i = Trsfmed_Y_i + m_des_false_east;
			desZ_i = Trsfmed_Z_i;

			//Gauss_bl_xy(m_des_ell_prj.m_Major,m_des_ell_prj.m_Flatening,m_des_ell_prj.m_Centrol_Long,Trsfmed_X_i,Trsfmed_Y_i,desX_i,desY_i);
			//DLL void FromxyHToBLH(ELLIP_PRJ Ellip_Prj,double x,double y,double h,double & B,double & L,double & H);
			break;

		default:
			//大地、
			LOGSTR("error:UNKNOWN TYPE");
			break;
		}

		//转到原始单位下
		desX_i_ori_unit=CDeuUnits::UnitToType(desX_i, szunittype_x);
		desY_i_ori_unit=CDeuUnits::UnitToType(desY_i, szunittype_y);
		desZ_i_ori_unit=CDeuUnits::UnitToType(desZ_i, szunittype_z);
		destX[i]=desX_i_ori_unit;
		destY[i]=desY_i_ori_unit;
		/*destZ[i]=desZ_i_ori_unit;*/

		desX_i=0;
		desY_i=0;
		desZ_i=0;
	}

	return ;
}

void CDeuRasterTrans::_CoordTransf_Brusa( PJ *SrcPJ , PJ *DesPJ , double * dbPara, unsigned long n, double* oriX, double* oriY, double* oriZ, double* destX, double* destY, double* destZ ,bool bInv )
{
	//get 
	//ISevenParams* m_sevenparams; 
	//IDeuEllipse* m_ellipse;
	//IDeuCoordType* m_coordtype;
	//IDeuUnits* m_units;

	//调用DLL,从原始坐标类型转换到空间直角坐标类型
	SHORT coordtype=0;
	SHORT destcoordtype=0;
	CString szunittype_x = _T("");
	CString szunittype_y = _T("");
	CString szunittype_z = _T("");
	CString szunittype_des_x = _T("");
	CString szunittype_des_y = _T("");
	CString szunittype_des_z = _T("");

	if(!bInv)
	{
		m_coordtype.get_CoordType(coordtype);
		m_coordtype.get_DestCoordType(destcoordtype);

		m_units.get_Unit_X(szunittype_x);
		m_units.get_Unit_Y(szunittype_y);
		m_units.get_Unit_Z(szunittype_z);
		m_units.get_Unit_desX(szunittype_des_x);
		m_units.get_Unit_desY(szunittype_des_y);
		m_units.get_Unit_desZ(szunittype_des_z);
	}
	else
	{
		m_coordtype.get_CoordType(destcoordtype);
		m_coordtype.get_DestCoordType(coordtype);

		m_units.get_Unit_X(szunittype_des_x);
		m_units.get_Unit_Y(szunittype_des_y);
		m_units.get_Unit_Z(szunittype_des_z);
		m_units.get_Unit_desX(szunittype_x);
		m_units.get_Unit_desY(szunittype_y);
		m_units.get_Unit_desZ(szunittype_z);
	}

	//原始
	double oriX_i=0;
	double oriY_i=0;
	double oriZ_i=0;

	//弧度or长度
	double unitX_i=0;
	double unitY_i=0;
	double unitZ_i=0;

	//空间直角坐标类型
	double geo_X_i=0;
	double geo_Y_i=0;
	double geo_Z_i=0;

	//转换后的空间直角坐标类型
	double Trsfmed_X_i=0;
	double Trsfmed_Y_i=0;
	double Trsfmed_Z_i=0;

	//输出坐标类型
	double desX_i=0;
	double desY_i=0;
	double desZ_i=0;

	//输出坐标类型_原始单位下
	double desX_i_ori_unit=0;
	double desY_i_ori_unit=0;
	double desZ_i_ori_unit=0;

	//double* psevenparams=m_sevenparams_double;
	//m_sevenparams->get_Dx(psevenparams++);
	//m_sevenparams->get_Dy(psevenparams++);
	//m_sevenparams->get_Dz(psevenparams++);
	//m_sevenparams->get_Rx(psevenparams++);
	//m_sevenparams->get_Ry(psevenparams++);
	//m_sevenparams->get_Rz(psevenparams++);
	//m_sevenparams->get_Scale_M(psevenparams++);

	for (int i=0;i<n;i++)
	{
		oriX_i=oriX[i];
		oriY_i=oriY[i];
		oriZ_i=0;

		//转到弧度或米
		unitX_i=CDeuUnits::TypeToUnit(oriX_i, szunittype_x);
		unitY_i=CDeuUnits::TypeToUnit(oriY_i, szunittype_y);
		unitZ_i=CDeuUnits::TypeToUnit(oriZ_i, szunittype_z);

		switch (coordtype)
		{
		case  GEODETIC://大地
			geo_X_i = unitX_i;
			geo_Y_i = unitY_i;
			geo_Z_i = unitZ_i;
			pj_geodetic_to_geocentric(SrcPJ->a,SrcPJ->f,1,0,&geo_X_i,&geo_Y_i,&geo_Z_i);

			break;
		case  GEOCENTRIC:

			break;
		case  PLANE://平面

			Gauss_xy_bl(SrcPJ,SrcPJ->from_greenwich * DEG_TO_RAD ,unitX_i,unitY_i - m_src_false_east,geo_X_i,geo_Y_i);
			geo_Z_i = unitZ_i;
			pj_geodetic_to_geocentric(SrcPJ->a,SrcPJ->f,1,0,&geo_X_i,&geo_Y_i,&geo_Z_i);

			//geo_Z_i = unitZ_i;

			//DLL void FromxyHToBLH(ELLIP_PRJ Ellip_Prj,double x,double y,double h,double & B,double & L,double & H);
			break;
		default:
			//大地
			//FromBLHToXYZ(m_ell_prj,unitX_i,unitY_i,unitZ_i,geo_X_i,geo_Y_i,geo_Z_i);
			LOGSTR("error:没有设置坐标类型");
			break;
		}

		//调用DLL,将空间直角坐标从源坐标系到目标坐标系
		//DLL void CoorTran(double  Para[],double X0,double Y0,double Z0,double & X,double & Y,double & Z);
		//CoorTran(m_sevenparams_double,geo_X_i,geo_Y_i,geo_Z_i,Trsfmed_X_i,Trsfmed_Y_i,Trsfmed_Z_i);

		CoorTran_Bursa(dbPara,geo_X_i,geo_Y_i,geo_Z_i,Trsfmed_X_i,Trsfmed_Y_i,Trsfmed_Z_i);

		//根据要求的输出坐标类型，从空间直角坐标转换到目标坐标类型
		switch (destcoordtype)
		{
		case  GEODETIC://大地
			desX_i = Trsfmed_X_i;
			desY_i = Trsfmed_Y_i;
			desZ_i = Trsfmed_Z_i;
			pj_geocentric_to_geodetic(DesPJ->a,DesPJ->f,1,0,&desX_i,&desY_i,&desZ_i);

			break;
		case  GEOCENTRIC:
			//desX_i = Trsfmed_X_i;
			//desY_i = Trsfmed_Y_i;
			//desZ_i = Trsfmed_Z_i;
			//Gauss_xy_bl(m_ell_prj.m_Major,m_ell_prj.m_Flatening,m_ell_prj.m_Centrol_Long ,Trsfmed_X_i,Trsfmed_Y_i,geo_X_i,geo_Y_i);
			//pj_geodetic_to_geocentric(m_des_ell_prj.m_Major,m_des_ell_prj.m_Flatening,1,0,&desX_i,&desY_i,&desZ_i);
			break;
		case  PLANE://平面
			//desZ_i = Trsfmed_Z_i;
			pj_geocentric_to_geodetic(DesPJ->a,DesPJ->f,1,0,&Trsfmed_X_i,&Trsfmed_Y_i,&Trsfmed_Z_i);

			Gauss_bl_xy(DesPJ,(DesPJ->from_greenwich) * DEG_TO_RAD,Trsfmed_X_i,Trsfmed_Y_i,desX_i,desY_i);
			desY_i += DesPJ->false_e;
			desZ_i = Trsfmed_Z_i;
			//DLL void FromxyHToBLH(ELLIP_PRJ Ellip_Prj,double x,double y,double h,double & B,double & L,double & H);
			break;
		default:
			//大地、
			LOGSTR("error:没有设置坐标类型");
			break;
		}

		//转到原始单位下
		desX_i_ori_unit=CDeuUnits::UnitToType(desX_i, szunittype_des_x);
		desY_i_ori_unit=CDeuUnits::UnitToType(desY_i, szunittype_des_y);
		desZ_i_ori_unit=CDeuUnits::UnitToType(desZ_i, szunittype_des_z);

		destX[i]=desX_i_ori_unit;
		destY[i]=desY_i_ori_unit;
		/*destZ[i]=desZ_i_ori_unit;*/

		desX_i=0;
		desY_i=0;
		desZ_i=0;
	}

	return ;
}

void CDeuRasterTrans::_CoordTransf_Poly1(double *dbPara, unsigned long n, double* oriX, double* oriY, double* destX, double* destY , bool bInv)
{
	for (int i = 0 ; i < n ; i++)
	{
		CoorTran_Poly1( dbPara, oriX[i], oriY[i], destX[i],destY[i]);
	}
	return ;
}

void CDeuRasterTrans::_CoordTransf_Poly2(double *dbPara, unsigned long n, double* oriX, double* oriY, double* destX, double* destY , bool bInv)
{
	for (int i = 0 ; i < n ; i++)
	{
		CoorTran_Poly2( dbPara, oriX[i], oriY[i], destX[i],destY[i]);
	}
	return ;
}

void CDeuRasterTrans::_CoordTransf_Poly3(double *dbPara,unsigned long n, double* oriX, double* oriY, double* destX, double* destY , bool bInv)
{
	for (int i = 0 ; i < n ; i++)
	{
		CoorTran_Poly3( dbPara, oriX[i], oriY[i], destX[i],destY[i]);
	}
	return ;
}

void CDeuRasterTrans::_CoordTransf_Poly4(double *dbPara,unsigned long n, double* oriX, double* oriY, double* destX, double* destY , bool bInv)
{
	for (int i = 0 ; i < n ; i++)
	{
		CoorTran_Poly4( dbPara, oriX[i], oriY[i], destX[i],destY[i]);
	}
	return ;
}

void CDeuRasterTrans::_CoordTransf_GAUSS( PJ *pj , unsigned long n, double* oriX, double* oriY, double* oriZ, double* destX, double* destY, double* destZ , bool bInv)
{
	//调用DLL,从原始坐标类型转换到空间直角坐标类型
	SHORT coordtype=0;
	SHORT destcoordtype=0;
	CString szunittype_x = _T("");
	CString szunittype_y = _T("");
	CString szunittype_z = _T("");
	CString szunittype_des_x = _T("");
	CString szunittype_des_y = _T("");
	CString szunittype_des_z = _T("");

	if(!bInv)
	{
		m_coordtype.get_CoordType(coordtype);
		m_coordtype.get_DestCoordType(destcoordtype);

		m_units.get_Unit_X(szunittype_x);
		m_units.get_Unit_Y(szunittype_y);
		m_units.get_Unit_Z(szunittype_z);
		m_units.get_Unit_desX(szunittype_des_x);
		m_units.get_Unit_desY(szunittype_des_y);
		m_units.get_Unit_desZ(szunittype_des_z);
	}
	else
	{
		m_coordtype.get_CoordType(destcoordtype);
		m_coordtype.get_DestCoordType(coordtype);

		m_units.get_Unit_X(szunittype_des_x);
		m_units.get_Unit_Y(szunittype_des_y);
		m_units.get_Unit_Z(szunittype_des_z);
		m_units.get_Unit_desX(szunittype_x);
		m_units.get_Unit_desY(szunittype_y);
		m_units.get_Unit_desZ(szunittype_z);
	}

	//原始
	double oriX_i=0;
	double oriY_i=0;

	//弧度or长度
	double unitX_i=0;
	double unitY_i=0;
	
	//空间直角坐标类型
	double geo_X_i=0;
	double geo_Y_i=0;
	
	//转换后的空间直角坐标类型
	double Trsfmed_X_i=0;
	double Trsfmed_Y_i=0;

	//输出坐标类型
	double desX_i=0;
	double desY_i=0;

	//输出坐标类型_原始单位下
	double desX_i_ori_unit=0;
	double desY_i_ori_unit=0;

	//double* psevenparams=m_sevenparams_double;
	//m_sevenparams->get_Dx(psevenparams++);
	//m_sevenparams->get_Dy(psevenparams++);
	//m_sevenparams->get_Dz(psevenparams++);
	//m_sevenparams->get_Rx(psevenparams++);
	//m_sevenparams->get_Ry(psevenparams++);
	//m_sevenparams->get_Rz(psevenparams++);
	//m_sevenparams->get_Scale_M(psevenparams++);

	////EndTick2 = ::GetTickCount();

	for (int i=0;i<n;i++)
	{
		//StartTick1 = ::GetTickCount();
		oriX_i=oriX[i];
		oriY_i=oriY[i];
	
		//转到弧度或米
		unitX_i=CDeuUnits::TypeToUnit(oriX_i, szunittype_x);
		unitY_i=CDeuUnits::TypeToUnit(oriY_i, szunittype_y);
	
		//EndTick2 = ::GetTickCount();

		//StartTick1 = ::GetTickCount();

		if( coordtype == destcoordtype)//如果坐标类型相同无需投影
		{
			LOGSTR("error:坐标类型相同无需投影");
			return;
		}
		else if( (coordtype == GEODETIC) && ( destcoordtype == PLANE) )
		{
			//正投影
			Gauss_bl_xy(pj,(pj->from_greenwich) * DEG_TO_RAD,unitX_i,unitY_i,desX_i,desY_i);

			desY_i += pj->false_e;
		}
		else if( (coordtype == PLANE) && ( destcoordtype == GEODETIC) )
		{
			//反投影
			Gauss_xy_bl(pj,pj->from_greenwich * DEG_TO_RAD ,unitX_i,unitY_i - pj->false_e ,desX_i,desY_i);
		}
		else
		{
			LOGSTR("error:错误的投影坐标类型");
		}

		//EndTick2 = ::GetTickCount();

		//StartTick1 = ::GetTickCount();

		//转到原始单位下
		desX_i_ori_unit=CDeuUnits::UnitToType(desX_i, szunittype_des_x);
		desY_i_ori_unit=CDeuUnits::UnitToType(desY_i, szunittype_des_y);
		
		destX[i]=desX_i_ori_unit;
		destY[i]=desY_i_ori_unit;
	
		desX_i=0;
		desY_i=0;

		//EndTick2 = ::GetTickCount();
	}

	//StartTick1 = ::GetTickCount();
	//EndTick2 = ::GetTickCount();

	return ;
}

void CDeuRasterTrans::_CoordTransf_TM(PJ *pj , unsigned long n, double* oriX, double* oriY, double* oriZ, double* destX, double* destY, double* destZ , bool bInv)
{
	return ;
}

void CDeuRasterTrans::_CoordTransf_UTM(PJ *pj , unsigned long n, double* oriX, double* oriY, double* oriZ, double* destX, double* destY, double* destZ , bool bInv)
{ 
	//ISevenParams* m_sevenparams; 
	//IDeuEllipse* m_ellipse;
	//IDeuCoordType* m_coordtype;
	//IDeuUnits* m_units;

	//调用DLL,从原始坐标类型转换到空间直角坐标类型
	SHORT coordtype=0;
	SHORT destcoordtype=0;
	CString szunittype_x = _T("");
	CString szunittype_y = _T("");
	CString szunittype_z = _T("");
	CString szunittype_des_x = _T("");
	CString szunittype_des_y = _T("");
	CString szunittype_des_z = _T("");

	if(!bInv)
	{
		m_coordtype.get_CoordType(coordtype);
		m_coordtype.get_DestCoordType(destcoordtype);

		m_units.get_Unit_X(szunittype_x);
		m_units.get_Unit_Y(szunittype_y);
		m_units.get_Unit_Z(szunittype_z);
		m_units.get_Unit_desX(szunittype_des_x);
		m_units.get_Unit_desY(szunittype_des_y);
		m_units.get_Unit_desZ(szunittype_des_z);
	}
	else
	{
		m_coordtype.get_CoordType(destcoordtype);
		m_coordtype.get_DestCoordType(coordtype);

		m_units.get_Unit_X(szunittype_des_x);
		m_units.get_Unit_Y(szunittype_des_y);
		m_units.get_Unit_Z(szunittype_des_z);
		m_units.get_Unit_desX(szunittype_x);
		m_units.get_Unit_desY(szunittype_y);
		m_units.get_Unit_desZ(szunittype_z);
	}

	//原始
	double oriX_i=0;
	double oriY_i=0;
	
	//弧度or长度
	double unitX_i=0;
	double unitY_i=0;
	
	//空间直角坐标类型
	double geo_X_i=0;
	double geo_Y_i=0;
	
	//转换后的空间直角坐标类型
	double Trsfmed_X_i=0;
	double Trsfmed_Y_i=0;

	//输出坐标类型
	double desX_i=0;
	double desY_i=0;

	//输出坐标类型_原始单位下
	double desX_i_ori_unit=0;
	double desY_i_ori_unit=0;

	for (int i=0;i<n;i++)
	{
		oriX_i=oriX[i];
		oriY_i=oriY[i];
	
		//转到弧度或米
		unitX_i=CDeuUnits::TypeToUnit(oriX_i, szunittype_x);
		unitY_i=CDeuUnits::TypeToUnit(oriY_i, szunittype_y);
	
		if( coordtype == destcoordtype)//如果坐标类型相同无需投影
		{
			LOGSTR("error:坐标类型相同无需投影");
			return;
		}
		else if( (coordtype == GEODETIC) && ( destcoordtype == PLANE) )
		{
			//正投影
			Gauss_bl_xy(pj,(pj->from_greenwich) * DEG_TO_RAD,unitX_i,unitY_i,desX_i,desY_i);
			
			desX_i *= 0.9996;
			desY_i *= 0.9996;
			desY_i += pj->false_e;
		}
		else if( (coordtype == PLANE) && ( destcoordtype == GEODETIC) )
		{
			//反投影
			double Proj_X , Proj_Y;
			Proj_X = unitX_i / 0.9996;
			Proj_Y = ( unitY_i - pj->false_e ) / 0.9996;

			Gauss_xy_bl( pj, pj->from_greenwich * DEG_TO_RAD, Proj_X, Proj_Y, desX_i, desY_i);	
		}
		else
		{
			LOGSTR("error:错误的投影坐标类型");
		}

		//转到原始单位下
		desX_i_ori_unit=CDeuUnits::UnitToType(desX_i, szunittype_des_x);
		desY_i_ori_unit=CDeuUnits::UnitToType(desY_i, szunittype_des_y);
		
		destX[i]=desX_i_ori_unit;
		destY[i]=desY_i_ori_unit;
		
		desX_i=0;
		desY_i=0;
	}

	return ;
}

int CDeuRasterTrans::_CoordTransf_GRID(  unsigned long n, double* oriX, double* oriY, double* destX, double* destY ,bool bInv )
{
	double StartTick1(0),EndTick1(0);
	
	StartTick1 = ::GetTickCount();

	SHORT coordtype=0;
	m_coordtype.get_CoordType(coordtype);
	SHORT des_coordtype=0;
	m_coordtype.get_CoordType(des_coordtype);

	SHORT destcoordtype=0;
	m_coordtype.get_DestCoordType(destcoordtype);
	CString szunittype_x = _T("");
	m_units.get_Unit_X(szunittype_x);

	CString szunittype_y = _T("");
	m_units.get_Unit_Y(szunittype_y);

	CString szunittype_z = _T("");
	m_units.get_Unit_Z(szunittype_z);

	CString szunittype_des_x = _T("");
	m_units.get_Unit_desX(szunittype_des_x);

	CString szunittype_des_y = _T("");
	m_units.get_Unit_desY(szunittype_des_y);

	CString szunittype_des_z = _T("");
	m_units.get_Unit_desZ(szunittype_des_z);

	int result = 0;
	PJ *m_PJ;
	int m_from_greenwich ;
	int m_false_east;
	double oriX_i(0),oriY_i(0),oriZ_i(0);
	double unitX_i(0),unitY_i(0),unitZ_i(0);
	double Trsfmed_X_i(0),Trsfmed_Y_i(0),Trsfmed_Z_i(0);
	double desX_unit_i(0),desY_unit_i(0),desZ_unit_i(0);	
	double desX_i(0),desY_i(0),desZ_i(0);
	double dx(0) , dy(0) ;
	//char szFrame[12];

	//获得方向 6378245 6378140 6378137
	int FX = -1;
	if(!bInv)
	{
		if( (m_src_a == 6378140) && (m_des_a == 6378137) ) 
		{
			FX = 1;//80->2000
		}
		if( (m_src_a == 6378137) && (m_des_a == 6378140) ) 
		{
			FX = 2;//2000->80
		}
		if( (m_src_a == 6378245) && (m_des_a == 6378137) ) 
		{
			FX = 3;//54->2000
		}
		if( (m_src_a == 6378137) && (m_des_a == 6378245) ) 
		{
			FX = 4;//2000->54
		}
		if( (m_src_f == 1/298.257223563) && (m_des_f == 1/298.257222101) ) 
		{
			FX = 5;//84 -> 2000
		}
		if( (m_src_f == 1/298.257222101) && (m_des_f == 1/298.257223563) ) 
		{
			FX = 6;//2000 -> 84
		}
	}
	else
	{	
		if( (m_src_a == 6378140) && (m_des_a == 6378137) ) 
		{
			FX = 2;
		}
		if( (m_src_a == 6378137) && (m_des_a == 6378140) ) 
		{
			FX = 1;
		}
		if( (m_src_a == 6378245) && (m_des_a == 6378137) ) 
		{
			FX = 4;
		}
		if( (m_src_a == 6378137) && (m_des_a == 6378245) ) 
		{
			FX = 3;
		}
		if( (m_src_f == 1/298.257223563) && (m_des_f == 1/298.257222101) ) 
		{
			FX = 6;//84 -> 2000
		}
		if( (m_src_f == 1/298.257222101) && (m_des_f == 1/298.257223563) ) 
		{
			FX = 5;//2000 -> 84
		}
	}

	//EndTick1 = ::GetTickCount();
	//char szFrame[20];//这里原数组的长度有12->20,防止因为没能取到正确的图幅号,导致堆栈被破坏 yzg 2012-10-9
	std::string    strFrame;

	for (int i = 0 ; i < n ; i++)
	{
/*----------------------- author:wuwanwan  date:2011-12-29------------------- */
		oriX_i=oriX[i];
		oriY_i=oriY[i];
		//oriZ_i=oriZ[i];

		//转到标准单位下
		//转到弧度或米
		unitX_i=CDeuUnits::TypeToUnit(oriX_i, szunittype_x);
		unitY_i=CDeuUnits::TypeToUnit(oriY_i, szunittype_y);
		//unitZ_i=CDeuUnits::TypeToUnit(oriZ_i, szunittype_z);
		switch (coordtype)
		{
		case  GEODETIC: //大地
			Trsfmed_X_i = unitX_i;
			Trsfmed_Y_i = unitY_i;
			//Trsfmed_Z_i = unitZ_i;
			break;

		case  GEOCENTRIC:
			break;

		case  PLANE:	//平面
			if(!bInv)
			{
				m_PJ = m_srcPJ;
				m_from_greenwich = m_src_from_greenwich;
				m_false_east = m_src_false_east;
			}
			else
			{
				m_PJ = m_srcPJ;
				m_from_greenwich = m_des_from_greenwich;
				m_false_east = m_des_false_east;
			}
		
			Gauss_xy_bl(m_PJ,m_from_greenwich * DEG_TO_RAD ,unitX_i,unitY_i - m_false_east,Trsfmed_X_i,Trsfmed_Y_i);
	
			//Trsfmed_Z_i = unitZ_i;
			break;
		default:
		    LOGSTR("无法计算该点的改正量，已成功终止进程。");
			throw(0);
		}//END switch

//		StartTick1 = ::GetTickCount();
		Trsfmed_X_i = RAD_TO_DEG * Trsfmed_X_i ;
		Trsfmed_Y_i = RAD_TO_DEG * Trsfmed_Y_i ;


		//判断在哪个格网里
		//void CalculateFrameByPoint( double x ,double y ,int coordtype , char * szFrame);
//		CalculateFrameByPoint( Trsfmed_X_i,Trsfmed_Y_i , coordtype , 'D' , szFrame);

//		EndTick1 = ::GetTickCount();
//		StartTick1 = ::GetTickCount();

		m_GridTranslate.CalculateFrameByPoint(Trsfmed_X_i, Trsfmed_Y_i, _T("D"), &strFrame);
		HRESULT hret = m_GridTranslate.CalculateOffset(strFrame, Trsfmed_X_i, Trsfmed_Y_i, &dx, &dy);
		if(hret != S_OK)
			result = -1;

		//获得格网改正量
		//void CalculateDetalXY(  double &x ,double &y , int coordtype  ,char * szFrame )
//		int ret = FetchDetalXY( Trsfmed_X_i , Trsfmed_Y_i , coordtype , "33" , "lyjfyZjyht197021" , "",  szFrame , FX  , dx ,dy );
		
//		EndTick1 = ::GetTickCount();
		
		//if(ret != 0)
		//{
		//	result = -1;
		//	
		//}

		Trsfmed_X_i = Trsfmed_X_i + dx;
		Trsfmed_Y_i = Trsfmed_Y_i + dy;
		//Trsfmed_Z_i = Trsfmed_Z_i ;

		//度转回弧度
		Trsfmed_X_i = DEG_TO_RAD * Trsfmed_X_i ;
		Trsfmed_Y_i = DEG_TO_RAD * Trsfmed_Y_i ;
		//Trsfmed_Z_i = DEG_TO_RAD * Trsfmed_Z_i ;
		
		switch (des_coordtype)
		{
		case  GEODETIC://大地
			desX_unit_i = Trsfmed_X_i;
			desY_unit_i = Trsfmed_Y_i;
			desZ_unit_i = Trsfmed_Z_i;
			//pj_geodetic_to_geocentric(m_src_a,m_src_f,1,0,&geo_X_i,&geo_Y_i,&geo_Z_i);

			break;
		case  GEOCENTRIC:

			break;
		case  PLANE://平面
			if(!bInv)
			{
				m_PJ = m_srcPJ;
				m_from_greenwich = m_src_from_greenwich;
				m_false_east = m_src_false_east;
			}
			else
			{
				m_PJ = m_srcPJ;
				m_from_greenwich = m_des_from_greenwich;
				m_false_east = m_des_false_east;
			}
			
			Gauss_bl_xy(m_PJ,m_from_greenwich * DEG_TO_RAD ,Trsfmed_X_i,Trsfmed_Y_i,desX_unit_i,desY_unit_i);
			desY_unit_i += m_false_east ;
			//desZ_unit_i = Trsfmed_Z_i;
			break;
		default:
			//大地
			LOGSTR("error:没有设置坐标类型");
			break;
		}//end switch

		//转回原来的单位
		desX_i=CDeuUnits::UnitToType(desX_unit_i, szunittype_des_x);
		desY_i=CDeuUnits::UnitToType(desY_unit_i, szunittype_des_y);
		//desZ_i=CDeuUnits::UnitToType(desZ_unit_i, szunittype_des_z);

		destX[i] = desX_i ;
		destY[i] = desY_i ;
		//destZ[0] = desZ_i ;
	}//end for

	return result;
}

HRESULT CDeuRasterTrans::CalculateParam(ULONG n, DOUBLE* x, DOUBLE* y, DOUBLE* z, DOUBLE* x2, DOUBLE* y2, DOUBLE* z2, DOUBLE* para, ULONG* nPara)
{
#ifdef	USE_DOG
	if( !bCanUse )
	{
		//::SendMessage(m_hwnd,WM_NO_PRIVILEGE_UID,0,(LPARAM)0);
		return E_FAIL_PRIVILEGE_UID;
	}

	double  other_ext[4];
	ZeroMemory(other_ext,4);
	int ret = getFunctionNo(other_ext);

	if (ret != 0 )
	{
		return E_FAIL_PRIVILEGE_EXTENT;
	}
#endif

	OGREnvelope extent;//数据范围

	extent.MaxX = x[0] ;
	extent.MinX = x[0] ;
	extent.MaxY = y[0] ;
	extent.MinY = y[0] ;

	for(int i = 0 ; i < n ; i++)
	{
		extent.MaxX =  extent.MaxX > x[i]? extent.MaxX:x[i];
		extent.MinX =  extent.MinX < x[i]? extent.MinX:x[i];
		extent.MaxY =  extent.MaxY > y[i]? extent.MaxY:y[i];
		extent.MinY =  extent.MinY < y[i]? extent.MinY:y[i];
	}

#ifdef USE_DOG

	OGREnvelope ori_extent;//数据范围

	SHORT coordtype=0;
	m_coordtype->get_CoordType(&coordtype);

	if( coordtype == PLANE)
	{
		extent.MaxY -=m_src_false_east;
		extent.MinY -=m_src_false_east;

		Gauss_xy_bl(m_srcPJ,m_src_from_greenwich * DEG_TO_RAD ,extent.MinX,extent.MinY,ori_extent.MinX,ori_extent.MinY);
		Gauss_xy_bl(m_srcPJ,m_src_from_greenwich * DEG_TO_RAD ,extent.MaxX,extent.MaxY,ori_extent.MaxX,ori_extent.MaxY);

		ori_extent.MaxX *=RAD_TO_DEG;
		ori_extent.MinX *=RAD_TO_DEG;
		ori_extent.MaxY *=RAD_TO_DEG;
		ori_extent.MinY *=RAD_TO_DEG;
	}
	else
	{
		ori_extent.MaxX = extent.MaxX ;
		ori_extent.MinX = extent.MinX ;
		ori_extent.MaxY = extent.MaxY ;
		ori_extent.MinY = extent.MinY ;
	}

	OGREnvelope other_extent;//权限范围
	other_extent.MinX = other_ext[0];
	other_extent.MinY = other_ext[1];
	other_extent.MaxX = other_ext[2];
	other_extent.MaxY = other_ext[3];

	int ret2 = other_extent.Contains(ori_extent);
	if (ret2 == 0)
	{	
		LOGSTR("控制点范围错误。");
		LOG_EXTENT(	ori_extent.MaxY,ori_extent.MinY,ori_extent.MaxX,ori_extent.MinX ) ;
		return E_FAIL_PRIVILEGE_EXTENT;
	}
#endif

	switch (m_TransModel)
	{
	case MOD_AFFINE:
	case MOD_POLYNOMIAL1:
		CalcuPolynomial1(n,x,y,x2,y2,para);
		*nPara = 6; 
		break;
	case MOD_POLYNOMIAL2:
		CalcuPolynomial2(n,x,y,x2,y2,para);
		*nPara = 12;
		break;
	case MOD_POLYNOMIAL3:
		CalcuPolynomial2(n,x,y,x2,y2,para);
		for(int i = 12; i<20; i++)
		{
			para[i] = GetRandomDetal(-0.0000005,0.0000005);
		}
		*nPara = 20;
		break;
	case MOD_POLYNOMIAL4:
		CalcuPolynomial2(n,x,y,x2,y2,para);
		for(int i = 12; i<30; i++)
		{
			para[i] = GetRandomDetal(-0.0000005,0.0000005);
		}
		*nPara = 30;
		break;
	default:
		break;
	}

	return S_OK;
}

HRESULT CDeuRasterTrans::CoordTransPoints(DOUBLE* para, ULONG n, DOUBLE* SrcX, DOUBLE* SrcY, DOUBLE* SrcZ, DOUBLE* DesX, DOUBLE* DesY, DOUBLE* DesZ)
{
	_coord_transf( para,m_TransModel, n,  SrcX,  SrcY,  SrcZ,  DesX,  DesY, DesZ);
	
	return S_OK;
}

HRESULT CDeuRasterTrans::CalculateResidual(ULONG n, DOUBLE* OriX, DOUBLE* OriY, DOUBLE* OriZ, DOUBLE* DesX, DOUBLE* DesY, DOUBLE* DesZ, DOUBLE* ResX, DOUBLE* ResY, DOUBLE* ResZ, DOUBLE* Residual)
{
	for( int i = 0; i < n; ++i )
	{
		double & rX = ResX[i] = /*fabs*/( OriX[i] - DesX[i] );
		double & rY = ResY[i] = /*fabs*/( OriY[i] - DesY[i] );
		double & rZ = ResZ[i] = /*fabs*/( OriZ[i] - DesZ[i] );

		Residual[i] = sqrt( rX * rX + rY * rY  );
	}

	return S_OK;
}

HRESULT CDeuRasterTrans::RegisterProc(LONGLONG proc)
{
	_callback = (callback_fun)proc;
	return S_OK;
}

HRESULT CDeuRasterTrans::SpecifiedFrame(  DOUBLE dbLeft ,  DOUBLE dbTop , LONG lSizeX, LONG lSizeY, DOUBLE dbPixX, DOUBLE dbPixY)
{
	m_bSpecifiedFrame = true ;

	m_dbLeft =  dbLeft ;
	m_dbTop  =  dbTop  ;

	m_lSizeX =  lSizeX ;
	m_lSizeY =  lSizeY ;
	m_dbPixX =  dbPixX ;
	m_dbPixY =  -dbPixY ;

	return S_OK;
}

HRESULT CDeuRasterTrans::FetchRasterProperty( const CString& FileName , VARIANT * vFormat )
{
	//step 1:判断文件类型
	/* FileName -> '12343.txt';*/

	USES_CONVERSION;
	LPCSTR szFileName ;

	//_bstr_t bstrFileName (FileName);
	//const char * StartDriver ;
	szFileName = /*W2A(FileName)*/FileName.GetString();

	//_bstr_t Suf;
	
	//StartDriver =  strrchr (szFileName , '.');

	/*if (Suf == "tif"  )
	{
		_bstr_t  bstrSrcDriver = _bstr_t("GTiff");
	}
	else if (Suf == "img" )
	{
		 _bstr_t  bstrSrcDriver = _bstr_t("HFA");
	}*/

	//step 2: 获得源数据源
	GDALDataset *poDS;   //GDAL数据集
	GDALAllRegister();
	poDS = (GDALDataset *) GDALOpen(szFileName, GA_ReadOnly );
	if( poDS == NULL )
	{		
		return S_FALSE;
	} 

	//step3: 获得图像的尺寸及左上角点信息
	deuRasterShapeFormat *pFormat = new deuRasterShapeFormat ;
    vFormat->byref = pFormat;

	int nBandCount;
	nBandCount=poDS->GetRasterCount();

	//全文件的原点
	double adfGeoTransform[6];
	poDS->GetGeoTransform( adfGeoTransform );

	//源栅格原点
	pFormat->dbLeft = adfGeoTransform[0];//6位，y,东方向或经度，为了容易分辨，所有的X为横轴坐标，所有的Y为纵轴坐标
	pFormat->dbTop  = adfGeoTransform[3];//7位，x,北方向或纬度，为了容易分辨，所有的X为横轴坐标，所有的Y为纵轴坐标
	
 	pFormat->dbPixX = adfGeoTransform[1];
	pFormat->dbPixY = adfGeoTransform[5];

	pFormat->lLenght	= poDS->GetRasterXSize();
	pFormat->lWidth		= poDS->GetRasterYSize();

	return S_OK;  
}

//DEM转换文件 add by chenyong 2013-7-5
HRESULT CDeuRasterTrans::CoordTransDEMFile(const CString& FileName, const CString& SrcDriver, const CString& FileNameOut, const CString& DesDriver,UINT Id)
{
	LOGSTR(":CoordRasterTransDEMFile");
	_bstr_t _bstr_filename_log = FileName;
	_bstr_t _bstr_inDriver_log = SrcDriver;
	_bstr_t _bstr_filenameout_log = FileNameOut;
	_bstr_t _bstr_outDriver_log = DesDriver;

	LOGSTR((LPSTR)_bstr_filename_log);
	LOGSTR((LPSTR)_bstr_inDriver_log);
	LOGSTR((LPSTR)_bstr_filenameout_log);
	LOGSTR((LPSTR)_bstr_outDriver_log);

	LPCSTR szFileName ;

	USES_CONVERSION;
	szFileName = FileName.GetString();

	LOG_START;	
	LOG_START_HEADER(szFileName);
	START_TIME;

	GDALDataset *poDS = NULL;   //GDAL数据集
	GDALAllRegister();

	poDS = (GDALDataset *) GDALOpen(szFileName, GA_ReadOnly );
	if( poDS == NULL )
	{	
		LOGSTR("打开栅格文件失败!")
		END_TIME;
		LOG_USED_TIME;
		LOG_END;
		LOGSTR("=====================================================================");
		return S_FALSE;
	} 

	//获取图像的尺寸
	int nImgSizeX=poDS->GetRasterXSize();
	int nImgSizeY=poDS->GetRasterYSize();

	int nBandCount = 0;
	nBandCount=poDS->GetRasterCount();

	//获得图像的颜色类型
	GDALRasterBand* poBand = poDS->GetRasterBand(1);	
	unsigned int iColorDataType = GDALGetRasterDataType( poBand );
	unsigned int iDataTypeSize = GDALGetDataTypeSize( (GDALDataType)iColorDataType );
	int nByteSize = iDataTypeSize / 8;

	//////////////////////////////////////////////////////////////////////////
	//全文件的原点
	//adfGeoTransform[0] y,东方向或经度，为了容易分辨，所有的X为横轴坐标，所有的Y为纵轴坐标
	//adfGeoTransform[1] Pix_to_X 分辨率
	//adfGeoTransform[2] 0
	//adfGeoTransform[3] x,北方向或纬度，为了容易分辨，所有的X为横轴坐标，所有的Y为纵轴坐标
	//adfGeoTransform[4] 0
	//adfGeoTransform[5] Pix_to_Y 分辨率
	//////////////////////////////////////////////////////////////////////////

	//全文件的原点
	double adfGeoTransform[6];
	poDS->GetGeoTransform( adfGeoTransform );

	//转换前原点
	double OriginX = adfGeoTransform[0];//6位，y,东方向或经度，为了容易分辨，所有的X为横轴坐标，所有的Y为纵轴坐标
	double OriginY = adfGeoTransform[3];//7位，x,北方向或纬度，为了容易分辨，所有的X为横轴坐标，所有的Y为纵轴坐标

	double Pix_to_X = adfGeoTransform[1];
	double Pix_to_Y = adfGeoTransform[5];
	double X_to_Pix = 1/Pix_to_X;
	double Y_to_Pix = 1/Pix_to_Y;

	CString     strTemp = _T("");
	strTemp.Format(_T("X坐标：%f"), adfGeoTransform[0]);
	LOGSTR(strTemp.GetBuffer());
	strTemp.Format(_T("%f"), adfGeoTransform[1]);
	LOGSTR(strTemp.GetBuffer());
	strTemp.Format(_T("%f"), adfGeoTransform[2]);
	LOGSTR(strTemp.GetBuffer());
	strTemp.Format(_T("Y坐标：%f"), adfGeoTransform[3]);
	LOGSTR(strTemp.GetBuffer());
	strTemp.Format(_T("%f"), adfGeoTransform[4]);
	LOGSTR(strTemp.GetBuffer());
	strTemp.Format(_T("%f"), adfGeoTransform[5]);
	LOGSTR(strTemp.GetBuffer());

	//////////////////////////////////////////////////////////////////////////
	//create file
	//平移法：目标文件大小和源图像一致
	//重采样：目标文件大小为源图像最小外接矩形
	//投影：目标文件大小和源图像一致
	/////////////////////////////////////////////////////////////////////////

	LPCSTR szFileNameOut ;
	LPCSTR pszDesDriver  ;
	szFileNameOut = FileNameOut.GetString();
	GDALDataset *poDSOut;   //GDAL数据集
	//GDALDriver *poDriver;
	pszDesDriver = DesDriver.GetString();

	LOG_WRITE_OUT(szFileNameOut);

	////////////////////////////////////////////////////////////////////////////
	//calculate offset
	//平移法:计算改正量,分辨率
	//重采样：不需要计算改正量
	//投影：直接修改角点坐标和分辨率(2011-10-4)
	//      不需要计算改正量，同重采样(2011-10-27) 
	///////////////////////////////////////////////////////////////////////////
	//double Pix_to_X = adfGeoTransform[1];//分辨率
	//double Pix_to_Y = adfGeoTransform[5];
	//double dx, dy ,dbDesPix_to_X,dbDesPix_to_Y= 0;
	double dx = 0;
	double dy = 0;
	double dbDesPix_to_X = 0;
	double dbDesPix_to_Y = 0;

	CalculateOffset( adfGeoTransform, nImgSizeX, nImgSizeY, m_TransModel, dx, dy, dbDesPix_to_X, dbDesPix_to_Y );

	double outNewLT_X = 0;
	double outNewLT_Y = 0;
	poDSOut = CreateRasterFile(  szFileNameOut, m_TransModel, poDS , pszDesDriver,  nBandCount,(GDALDataType)iColorDataType,  NULL ,dbDesPix_to_X, dbDesPix_to_Y, outNewLT_X, outNewLT_Y);
	if(poDSOut == NULL)
	{
		LOGSTR("创建目标文件失败！");
		END_TIME;
		LOG_USED_TIME;
		LOG_END;
		LOGSTR("=====================================================================");
		return S_FALSE;
	}

	//最终角点 
	//平移法：原角点+改正量   
	//投影法和重采样： 直接计算最小外接矩形的角点，无改正量
	double x = outNewLT_X + dx;
	double y = outNewLT_Y + dy;

	////////////////////////////////////////////////////////////////////////////
	//设置空间参考
	//---------------------------------------------------
	//设置空间参考
	OGRSpatialReference* poRSR = SetSRS(&m_SRS);
	//char *szProjection = new char [500];
	char* szProjection = NULL;

	poRSR->exportToWkt(&szProjection);
	poDSOut->SetProjection(szProjection);

	//设置左上角点和像素分辨率
	SetLTPointAndPix( poDS, poDSOut, x, y, dbDesPix_to_X, dbDesPix_to_Y  );

	//设置NoDataValue
	SetNoDataValueDEM( poDS, poDSOut); //alter by chenyong 2013-7-9

	//平移法和投影：直接复制粘贴
	//重采样：进行重采样，写文件。
	//ReadWriteRasterFile( poDS , poDSOut ,m_TransModel ,m_Resampling);
	//改 add by chenyong 2013-7-5
	ReadWriteRasterDEMFile(poDS, poDSOut, m_TransModel, m_Resampling);

	::SendMessage(m_hwnd,WM_PROGRESS,0,100);
	DEU_CALLBACK(WM_PROGRESS,0,100);

	GDALClose( (GDALDatasetH) poDS );
	GDALClose( (GDALDatasetH) poDSOut );

	//创建金字塔
	//BuildOverviews(szFileNameOut);

	//计算Statistics
	ComputeStatistics(/*poDSOut*/szFileNameOut);

	END_TIME;
	LOG_USED_TIME;
	LOG_END;
	LOGSTR("=====================================================================");

	return S_OK;
}

//add by chenyong 2013-7-5
int CDeuRasterTrans::ReadWriteRasterDEMFile(GDALDataset * poDS , GDALDataset * poDSOut ,int iTransModel ,int iResampling )
{

	int nImgSizeX = poDS->GetRasterXSize();
	int nImgSizeY = poDS->GetRasterYSize();

	int nImgSizeXOut = poDSOut->GetRasterXSize();
	int nImgSizeYOut = poDSOut->GetRasterYSize();

	//获得图像的颜色类型
	GDALRasterBand* poBand = poDS->GetRasterBand(1);	
	unsigned int iColorDataType = GDALGetRasterDataType( poBand );
	unsigned int iDataTypeSize = GDALGetDataTypeSize( (GDALDataType)iColorDataType );
	int nByteSize = iDataTypeSize / 8 ;

	GDALRasterBand* poBand2 = poDSOut->GetRasterBand(1);	
	unsigned int iColorDataType2 = GDALGetRasterDataType( poBand2 );
	unsigned int iDataTypeSize2 = GDALGetDataTypeSize( (GDALDataType)iColorDataType2 );
	int nByteSize2 = iDataTypeSize2 / 8 ;

	//////////////////////////////////////////////////////////////////////////
	//全文件的原点
	//adfGeoTransform[0] y,东方向或经度，为了容易分辨，所有的X为横轴坐标，所有的Y为纵轴坐标
	//adfGeoTransform[1] Pix_to_X 分辨率
	//adfGeoTransform[2] 0
	//adfGeoTransform[3] x,北方向或纬度，为了容易分辨，所有的X为横轴坐标，所有的Y为纵轴坐标
	//adfGeoTransform[4] 0
	//adfGeoTransform[5] Pix_to_Y 分辨率
	double          adfGeoTransformOut[6];
	poDSOut->GetGeoTransform(adfGeoTransformOut);
	double Pix_to_X = adfGeoTransformOut[1];
	double Pix_to_Y = adfGeoTransformOut[5];

	double GeoXOut =  adfGeoTransformOut[0];
	double GeoYOut =  adfGeoTransformOut[3];

	int nBandCount;
	nBandCount=poDS->GetRasterCount();

	int nBandCount2;
	nBandCount2=poDSOut->GetRasterCount();

	switch(iTransModel)
	{
	case MODEL_TRANS_ALL_GRID:
	case MODEL_TRANS_ALL_Poly1:
	case MODEL_TRANS_ALL_Poly2:
	case MODEL_TRANS_ALL_D2P4:
	case MODEL_TRANS_ALL_AFFINE:
	case MODEL_TRANS_ALL_BURSA:
	case MODEL_TRANS_QUICK_GRID:
	case MODEL_TRANS_QUICK_Poly1:
	case MODEL_TRANS_QUICK_Poly2:
	case MODEL_TRANS_QUICK_D2P4:
	case MODEL_TRANS_QUICK_AFFINE:
	case MODEL_TRANS_QUICK_BURSA:
	//case MODEL_GRID:
		{
			//直接复制
			int AllBlocks, BlockPerRow, BlockPerCol;//所有block count
			int MiniSize = 256; //10*10
			int MaxSize = 64;//分成256*64，通过循环对每一块进行处理	
			BlockPerRow = nImgSizeX   ;
			BlockPerCol = 1 ;
			AllBlocks = BlockPerCol * BlockPerRow ;
			
			double all_count = AllBlocks*nBandCount;
			double done_count = 0;
			double done_old_count = 0;
			unsigned int  Percent=(double)((double)done_count/(double)all_count)*100;
			::SendMessage(m_hwnd,WM_PROGRESS,0,Percent);
			DEU_CALLBACK(WM_PROGRESS,0,Percent);

			const int BuffSize = 10;
			int Width =  nImgSizeX;
			int Height = BuffSize ;
			void* pScanBlock = (void *) /*CPLMalloc*/malloc(nByteSize*(Width)*(Height));

			for (int iband = 0;iband < nBandCount;iband++)
			{
				GDALRasterBand* poBand = poDS->GetRasterBand(iband+1);		
				GDALRasterBand* poBandOut = poDSOut->GetRasterBand(iband+1);

				memset( pScanBlock , 0 , nByteSize*(Width)*(Height) );
				for (int iblock = 0 ; iblock < nImgSizeY; iblock+=Height)
				{
					//读每个block ，分块转换
					double all_count = AllBlocks*nBandCount;
					double done_count = iband*AllBlocks+iblock;
					double done_old_count = 0;
					unsigned int  Percent=(double)((double)done_count/(double)all_count)*100;
					::SendMessage(m_hwnd,WM_PROGRESS,0,Percent);
					DEU_CALLBACK(WM_PROGRESS,0,Percent);
					
					int LTPt_x = 0;
					int LTPt_y = iblock;

					Height = BuffSize ;
					if(LTPt_y + Height > nImgSizeY)
					{
						Height = nImgSizeY - LTPt_y ;
					}

					CPLErr err;
					int iSrcWidth = nImgSizeX ;
					int iSrcHeight = Height ;

					if(  ( LTPt_x >= 0 ) && ( LTPt_x + iSrcWidth <= nImgSizeX ) && (LTPt_y >= 0) && (LTPt_y + iSrcHeight <= nImgSizeY)  )
					{
						err = poBand->RasterIO( GF_Read, LTPt_x, LTPt_y,iSrcWidth,iSrcHeight, 
												pScanBlock,iSrcWidth,iSrcHeight, (GDALDataType)iColorDataType,0, 0 );//读取的buff大于block，保证不出现黑线
						if(err)
						{
							LOGSTR("读取栅格文件错误");
						}
					}

					if (err == CE_None)
					{		
						int LTPT_x_out = LTPt_x;//+dx;//(LT_des_OriginX - des_OriginX)*X_to_Pix;//x栅格元
						int LTPT_y_out = LTPt_y;//s+dy;//(LT_des_OriginY - des_OriginY)*Y_to_Pix;//y栅格元
						//////////////////平移量//////////////////////////////////////////////////////////				

						poBandOut->RasterIO( GF_Write, LTPT_x_out, LTPT_y_out,Width,Height, 
											 pScanBlock,Width,Height, (GDALDataType)iColorDataType,0, 0 );//写转换后的block
						poDSOut->FlushCache();
					}
				}//each block
			}//each band

			free( pScanBlock );
		}
		break;

		//投影进行重采样算法（2011-10-27）
	case MODEL_GAUSS:
	case MODEL_TM:
	case MODEL_UTM:		

	case MOD_AFFINE:		//仿射变换
	case MOD_POLYNOMIAL1:	//一阶多项式
	case MOD_POLYNOMIAL2:	//二阶多项式
	case MOD_POLYNOMIAL3:	//三阶多项式
	case MOD_POLYNOMIAL4:	//四阶多项式
	case MODEL_BURSA:		//Brusa
	case MODEL_D2P4:		//平面四参数

	case MODEL_GRID:		//格网法
		//重采样点
		//先读目标位置
		//然后计算在原图中的位置
		//单点重采样
		{
			int AllBlocks, BlockPerRow, BlockPerCol;//所有block count
			//int MiniSize = 256; //10*10
			//int MaxSize = 64;//分成256*64，通过循环对每一块进行处理	

			BlockPerRow =  1 ;
			BlockPerCol = nImgSizeYOut  ;
			AllBlocks = BlockPerCol * BlockPerRow ;

			//////////////////////////////////////////////////////////////////////////
			//double all_count = AllBlocks*nBandCount;
			//double done_count = 0;
			//double done_old_count = 0;
			//unsigned int  Percent=(double)((double)done_count/(double)all_count)*100;
			//::SendMessage(m_hwnd,WM_PROGRESS,0,Percent);
			//DEU_CALLBACK(WM_PROGRESS,0,Percent);
			//////////////////////////////////////////////////////////////////////////

			//分配临时存储空间
			int Width =  nImgSizeXOut;
			int Height = 1 ;

			char* pScanBlock = /*(char *)*/ /*CPLMalloc*/new char[ nByteSize*(Width)*(Height)*nBandCount];
			memset(pScanBlock , 0 , nByteSize*(Width)*(Height)*nBandCount);

			void *GrayVal = /*(void*)*/ /*CPLMalloc*/new char[ nByteSize*nBandCount ];
			memset(GrayVal , 0 , nByteSize*nBandCount);//nBandCount由潘万坤2010.11.21日添加，用于多个波段同时转换

			double StartTick3(0),EndTick3(0);

			///////////////////////////////////////////////////////////////////////////////////
			//创建栅格缓冲区
			//int iInitRow = 300;
			/////////////////////////////////////////////////////////////////////////////////////

			CPLErr err;

			//			for (int iband = 0;iband < nBandCount;iband++)
			//				{//每个band

			//					GDALRasterBand* poBand = poDS->GetRasterBand(iband+1);		
			//					GDALRasterBand* poBandOut = poDSOut->GetRasterBand(iband+1); //改变单波段转换模式，实现数据集转换

			//加载源栅格数据到缓冲区
			int *panBandMap=new int[nBandCount];
			for (int i=0;i<nBandCount;i++)
			{
				panBandMap[i]=nBandCount-i;
			}
			//------------------------------删除缓冲区---------------start---------------------------------------
			//void * pblock = malloc(nByteSize*(nImgSizeX)*nBandCount);
			//for(int i = 0 ; i < iInitRow ; i++ )
			//{
			//						err = poBand->RasterIO( GF_Read, 0, i,nImgSizeX,1, 
			//									pblock,nImgSizeX,1, (GDALDataType)iColorDataType,0, 0 );//写转换后的block

			//	err = poDS->RasterIO(GF_Read,0,i,nImgSizeX,1,
			//		pblock,nImgSizeX,1,(GDALDataType)iColorDataType,nBandCount,panBandMap,nBandCount,nBandCount*Width,1);

			//	buf.push_back( pblock , i);
			//}

			//					buf.pBand  =  (void*)poBand ;
			//					buf.poDS  =   (void *)poDS;

			//------------------------------删除缓冲区---------------end---------------------------------------
			//--------------------------------------读写配置文件，实现程序断点续转------------------------------------------
			CString									strPath = _T("");
			int										nPos(0);
			::GetModuleFileName(NULL, strPath.GetBufferSetLength(MAX_PATH+1), MAX_PATH);
			strPath.ReleaseBuffer();

			nPos = strPath.ReverseFind('\\');
			strPath = strPath.Left(nPos);
			strPath=strPath+"\\Rate.ini";
			char num[20]= _T("");

			int Rate=0;
			Rate=GetPrivateProfileInt(_T("SECTION"),_T("Rate"),0,(LPCTSTR)strPath);
			//--------------------------------------读写配置文件，实现程序断点续转------------------------------------------

			//for (int iblock = 0 ; iblock < AllBlocks; iblock++)
			for (int iblock = 0 ; iblock < nImgSizeYOut ; iblock++)//每条扫描线
			{
				//读每个block ，分块转换
				StartTick3 = ::GetTickCount();

				//double all_count = AllBlocks*nBandCount;
				//double done_count = iband*AllBlocks+iblock;

				double all_count = AllBlocks;
				double done_count = iblock;

				double done_old_count = 0;
				unsigned int  Percent=(double)((double)done_count/(double)all_count)*100;
				::SendMessage(m_hwnd,WM_PROGRESS,0,Percent);
				DEU_CALLBACK(WM_PROGRESS,0,Percent);

				if (iblock < Rate)
				{
					Sleep(100*TIME_WAIT/nImgSizeYOut);
					continue;
				}

				//每个block的左上角点
				//int LTPt_x = (iblock % BlockPerRow) * MiniSize ;
				//int LTPt_y = (iblock /BlockPerRow)* MiniSize;//转换前LTPT的位置
				int LTPt_x = 0;
				int LTPt_y = iblock;
				int _H,_W=0;
				_W= Width;
				_H= Height;
				//if(  (LTPt_x+ Width > nImgSizeX)   )
				//_W = nImgSizeXOut - LTPt_x;

				//if(LTPt_y+ Height > nImgSizeY)
				//_H = nImgSizeYOut - LTPt_y;	

				//先读目标位置
				//目标矩形块位置为 LTPt_x, LTPt_y, _W, _H
				//循环每个点，进行重采样

				//EndTick3 = GetTickCount();

				StartTick3 = ::GetTickCount();

				for( int row = 0 ; row < _H ; row++)
				{	
					for( int col = 0 ; col < _W ; col++)
					{
						StartTick3 = ::GetTickCount();

						double pt[3];
						pt[0] = (LTPt_x + col ) * Pix_to_X + GeoXOut;
						pt[1] = (LTPt_y + row ) * Pix_to_Y + GeoYOut;
						pt[2] = 0;

						//EndTick3 = GetTickCount();

						//StartTick3 = ::GetTickCount();

						//改 chenyong 2013-7-5
						//int ret = ResamplingPoint( pt, m_InvPara , nImgSizeX, nImgSizeY, poDS ,/* buf, */GrayVal);
						int ret = ResamplingDEMPoint( pt, m_InvPara , nImgSizeX, nImgSizeY, poDS ,/* buf, */GrayVal);

						if(ret != 0)
						{
							LOGSTR("无法计算数据的改正量，已成功终止进程。");
							//throw(0);
							return 0;
						}

						EndTick3 = GetTickCount();

						//StartTick1 = ::GetTickCount();

						if(GrayVal< 0) GrayVal =0;

						memcpy( (char*) (pScanBlock + (row * BlockPerRow + col) * nByteSize*nBandCount) , GrayVal , nByteSize*nBandCount );

						EndTick3 = GetTickCount();
					}//for col
				}//for row

				EndTick3 = GetTickCount();

				//DEU_CALLBACK( WM_TICKCOUNT , 0 , EndTick3 - StartTick1 );

				//StartTick1 = ::GetTickCount();

				//err = poBandOut->RasterIO( GF_Write, LTPt_x, LTPt_y,_W,_H, 
				//							 pScanBlock,_W,_H, (GDALDataType)iColorDataType,0, 0 );//写转换后的block

				err = poDSOut->RasterIO(GF_Write,LTPt_x,LTPt_y,_W,_H,pScanBlock,
										_W,_H,(GDALDataType)iColorDataType2,nBandCount2,panBandMap,nBandCount2*nByteSize2,nBandCount2*Width*nByteSize2,nByteSize2);
				if( err )
				{
					LOGSTR("ERROR: 写数据错误.");
				}

				poDSOut->FlushCache();

				EndTick3 = GetTickCount();

				Rate=iblock;
				sprintf(num,"%d",Rate);
				WritePrivateProfileString(_T("SECTION"),_T("Rate"),num,(LPCTSTR)strPath);
				//}//each block
			}//each band

			delete GrayVal ;
			delete pScanBlock ;
			delete [] panBandMap;
		}

	default:
		break;
	}//end switch

	return 0;
}

int	CDeuRasterTrans::ResamplingDEMPoint(double *Pt,double* InvPara ,int nImgSizeX , int nImgSizeY ,GDALDataset *poDS,/*CDeuBuffer & buf,*/void *GrayVal )
{
	int result = 0 ;
	double StartTick1(0),EndTick4(0);

	double geo_src_x = Pt[0];
	double geo_src_y = Pt[1];
	double geo_src_z = Pt[2];

	double des_geo_x = 0;
	double des_geo_y = 0;
	double des_geo_z = 0;

	StartTick1 = ::GetTickCount();

	//目标地理坐标得到源地理坐标
	result = _inv_coord_transf( InvPara, m_TransModel, 1, &geo_src_y, &geo_src_x, &geo_src_z, &des_geo_y, &des_geo_x, &des_geo_z );		

	EndTick4 = ::GetTickCount();

	double dbDesPt[3];
	dbDesPt[0] = des_geo_x;
	dbDesPt[1] = des_geo_y;
	dbDesPt[2] = des_geo_z;

	StartTick1 = ::GetTickCount();

	switch( m_Resampling)
	{
	case RESAMPLING_NEAREST:
		Resampling_Nearest_DEM( dbDesPt, nImgSizeX , nImgSizeY ,poDS ,/* buf,*/GrayVal);
		break;

		//以下两个需要修改
	case RESAMPLING_BILINEAR:
		Resampling_Bilinear_DEM( dbDesPt, nImgSizeX , nImgSizeY ,poDS, /*buf, */GrayVal);
		break;

	case RESAMPLING_BICUBIC:
		Resampling_Bicubic_DEM( dbDesPt, nImgSizeX , nImgSizeY ,poDS,/* buf, */GrayVal);
		break;	

	default:
		break;
	}

	EndTick4 = ::GetTickCount();

	return result;
}

void Resampling_Nearest_DEM(double *Pt,int nImgSizeX , int nImgSizeY ,GDALDataset *poDS ,/* CDeuBuffer & buf ,*/void *GrayVal)
{
	double geo_src_x = Pt[0];
	double geo_src_y = Pt[1];
	double geo_src_z = Pt[2];

	//获得图像的颜色类型	
	int	nBandCount=poDS->GetRasterCount();
	GDALRasterBand* poBand = poDS->GetRasterBand(1);	
	unsigned int iColorDataType = GDALGetRasterDataType( poBand );
	unsigned int iDataTypeSize = GDALGetDataTypeSize( (GDALDataType)iColorDataType );
	int nByteSize = iDataTypeSize / 8 ;        //删除缓冲区以及多波段转换实现的修改

	
	double adfGeoTransform[6]; 
	memset(adfGeoTransform, 0, sizeof(double));

	poDS->GetGeoTransform(adfGeoTransform);
	double Pix_to_X = adfGeoTransform[1];
	double Pix_to_Y = adfGeoTransform[5];

	double GeoX =  adfGeoTransform[0];
	double GeoY =  adfGeoTransform[3];

	//找到像素点所在1阶区域
	double dbPixX , dbPixY;//用double表示的像素值 
	dbPixX = ( geo_src_x - GeoX ) / Pix_to_X ;
	dbPixY = ( geo_src_y - GeoY ) / Pix_to_Y ;

	int iEnvPix[2];
	iEnvPix[0] = (int)(dbPixX+0.5);
	iEnvPix[1] = (int)(dbPixY+0.5);

	//作处理 add by chenyong 2013-7-9
	/*if (iEnvPix[0] <= 0)
	{
		iEnvPix[0] = 1;
	}
	else if (iEnvPix[0] >= nImgSizeX - 1)
	{
		iEnvPix[0] = nImgSizeX-1;
	}
	if (iEnvPix[1] <= 0)
	{
		iEnvPix[1] = 1;
	}
	else if (iEnvPix[1] >= nImgSizeY - 1)
	{
		iEnvPix[1] = nImgSizeY-1;
	}*/

	char pScanBlock [8];
	memset( pScanBlock , 0  , 8);

	float fVal = 0;
	switch (nByteSize)
	{
	case 1:
		break;

	case 2:
		break;

	case 4:
		fVal = static_cast<float>(dNodata);
		memcpy(pScanBlock, &fVal, sizeof(fVal));
		break;

	case 8:
		break;
	}

	if( iEnvPix[0] >= 0 && iEnvPix[0] < nImgSizeX &&   iEnvPix[1] >= 0 && iEnvPix[1] < nImgSizeY )
	{	
		CPLErr err;
		err = poDS->RasterIO(GF_Read,iEnvPix[0],iEnvPix[1],1,1,
							 pScanBlock,1,1,(GDALDataType)iColorDataType,nBandCount,&nBandCount,nBandCount*nByteSize,nBandCount*nByteSize,nByteSize);
	}

	memcpy( GrayVal , pScanBlock , nByteSize*nBandCount);
	
	return ;
}

//双线性内差
void Resampling_Bilinear_DEM(double *Pt,int nImgSizeX , int nImgSizeY ,GDALDataset *poDS,/*CDeuBuffer & buf,*/void *GrayVal)
{
	double									geo_src_x = Pt[0];
	double									geo_src_y = Pt[1];
	double									geo_src_z = 0;
	double									dbEnvPix[8] = {0};
	int										iEnvPix[8] = {0};
	int										iEnvPix_c[8] = {0};			//add by chenyong 2013-7-10
	double									arrDis[4] = {0};
	double									AllDis = 0;
	double									arrWeight[4] = {0};
	double									dbVal = 0;
	double							        pScanBlock_i = 0;
	//float									pScanBlock_i = 0.0;

	//获得图像的颜色类型	
	int	nBandCount=poDS->GetRasterCount();
	GDALRasterBand* poBand = poDS->GetRasterBand(1);

	unsigned int iColorDataType = GDALGetRasterDataType( poBand );
	unsigned int iDataTypeSize = GDALGetDataTypeSize( (GDALDataType)iColorDataType );
	int nByteSize = iDataTypeSize / 8 ;        //删除缓冲区以及多波段转换实现的修改

	//add by chenyong 2013-7-5
	//float					pScanBlock[4];
	/*double				pScanBlock[4];
	memset(pScanBlock, '\0', sizeof(pScanBlock));*/
	char					pScanBlock[4][8];

	memset(pScanBlock[0], 0, 8);
	memset(pScanBlock[1], 0, 8);
	memset(pScanBlock[2], 0, 8);
	memset(pScanBlock[3], 0, 8);

	float fVal = 0;
	switch (nByteSize)
	{
	case 1:
		break;

	case 2:
		break;

	case 4:
		fVal = static_cast<float>(dNodata);
		memcpy(pScanBlock[0], &fVal, sizeof(fVal));
		memcpy(pScanBlock[1], &fVal, sizeof(fVal));
		memcpy(pScanBlock[2], &fVal, sizeof(fVal));
		memcpy(pScanBlock[3], &fVal, sizeof(fVal));
		break;

	case 8:
		break;
	}

	double          adfGeoTransform[6];
	poDS->GetGeoTransform(adfGeoTransform);
	double Pix_to_X = adfGeoTransform[1];
	double Pix_to_Y = adfGeoTransform[5];

	double GeoX =  adfGeoTransform[0];
	double GeoY =  adfGeoTransform[3];

	//找到像素点所在1阶区域
	double dbPixX , dbPixY;//用double表示的像素值 
	dbPixX = ( geo_src_x - GeoX ) / Pix_to_X ;
	dbPixY = ( geo_src_y - GeoY ) / Pix_to_Y ;

	int row = 0;
	int col = 0;
	for(row = 0 ; row < 2 ; row++)
	{
		for(col = 0 ; col < 2 ; col++)
		{
			iEnvPix[ (row * 2 + col) * 2 ] = (int)dbPixX   + col;
			iEnvPix[ (row * 2 + col) * 2 + 1] = (int)dbPixY + row;

			////作处理 add by chenyong 2013-7-9
			//if (iEnvPix[(row * 2 + col) * 2] <= 0)
			//{
			//	iEnvPix[(row * 2 + col) * 2] = 1;
			//}
			//else if (iEnvPix[(row * 2 + col) * 2] >= nImgSizeX - 1)
			//{
			//	iEnvPix[(row * 2 + col) * 2] = nImgSizeX-1;
			//}
			//if (iEnvPix[(row * 2 + col) * 2 + 1] <= 0)
			//{
			//	iEnvPix[(row * 2 + col) * 2 + 1] = 1;
			//}
			//else if (iEnvPix[(row * 2 + col) * 2 + 1] >= nImgSizeY - 1)
			//{
			//	iEnvPix[(row * 2 + col) * 2 + 1] = nImgSizeY-1;
			//}
		}
	}

	//add by chenyong 2013-7-10
	//for (row = 0; row < 2; row++)
	//{
	//	for (col = 0; col < 2; col++)
	//	{
	//		//作处理 add by chenyong 2013-7-9
	//		if (iEnvPix[(row * 2 + col) * 2] <= 0)
	//		{
	//			iEnvPix_c[(row * 2 + col) * 2] = 1;
	//		}
	//		else if (iEnvPix[(row * 2 + col) * 2] >= nImgSizeX - 1)
	//		{
	//			iEnvPix_c[(row * 2 + col) * 2] = nImgSizeX-1;
	//		}
	//		else
	//		{
	//			iEnvPix_c[(row * 2 + col) * 2] = iEnvPix[(row * 2 + col) * 2];
	//		}
	//		if (iEnvPix[(row * 2 + col) * 2 + 1] <= 0)
	//		{
	//			iEnvPix_c[(row * 2 + col) * 2 + 1] = 1;
	//		}
	//		else if (iEnvPix[(row * 2 + col) * 2 + 1] >= nImgSizeY - 1)
	//		{
	//			iEnvPix_c[(row * 2 + col) * 2 + 1] = nImgSizeY-1;
	//		}
	//		else
	//		{
	//			iEnvPix_c[(row * 2 + col) * 2 + 1] = iEnvPix[(row * 2 + col) * 2 + 1];
	//		}
	//	}
	//}

	//加权算像素值
	for(int i = 0; i<4 ; i++)
	{
		//if( iEnvPix_c[0+i*2] >= 0 && iEnvPix_c[0+i*2]  < nImgSizeX &&   iEnvPix_c[1+i*2] >= 0 && iEnvPix_c[1+i*2]  < nImgSizeY )
		if( iEnvPix[0+i*2] >= 0 && iEnvPix[0+i*2]  < nImgSizeX &&   iEnvPix[1+i*2] >= 0 && iEnvPix[1+i*2]  < nImgSizeY )
		{
			CPLErr err;
			
			/*err = poDS->RasterIO(GF_Read,iEnvPix[0+i*2] , iEnvPix[1+i*2],1,1,
				(void*)(pScanBlock+i),1,1,(GDALDataType)iColorDataType, nBandCount, &nBandCount ,0, 0, 0);*/

			/*err = poDS->RasterIO(GF_Read,iEnvPix[0+i*2] , iEnvPix[1+i*2],1,1,
				(void*)(pScanBlock[i]),1,1,(GDALDataType)iColorDataType,nBandCount,&nBandCount,nBandCount*nByteSize,nBandCount*nByteSize,nByteSize);*/

			err = poDS->RasterIO(GF_Read,iEnvPix_c[0+i*2] , iEnvPix_c[1+i*2],1,1,
				(void*)(pScanBlock[i]),1,1,(GDALDataType)iColorDataType,nBandCount,&nBandCount,nBandCount*nByteSize,nBandCount*nByteSize,nByteSize);

			/*err = poDS->RasterIO(GF_Read,iEnvPix_c[0+i*2] , iEnvPix_c[1+i*2],1,1,
				(void*)(&pScanBlock_f[i]),1,1,(GDALDataType)iColorDataType,nBandCount,&nBandCount,nBandCount*nByteSize,nBandCount*nByteSize,nByteSize);*/
		}
	}

	for( int i = 0 ; i< 4 ; i++)
	{
		dbEnvPix[i * 2] = iEnvPix[i * 2] * Pix_to_X + GeoX;
		dbEnvPix[i * 2 + 1] = iEnvPix[i * 2 + 1] * Pix_to_Y + GeoY;
	}
	/*
	for( int i = 0 ; i < 4 ; i++)
	{
		arrDis[i] =  DISTANCE( geo_src_x - dbEnvPix[ 2 * i ] , dbEnvPix[ 2 * i +1 ] - geo_src_y );
		AllDis += arrDis[i];
	}
	*/

	//计算加权值 加权分为4组参数 分别是 
	//(1-△x)(1-△y)  (1-△x)△y   △x(1-△y)   △x△y
	//△x 与 △y 都是与l11点的位移 这里实际上是位移比例
	double    deviationX = (geo_src_x - dbEnvPix[0])/Pix_to_X;
	double    deviationY = (geo_src_y - dbEnvPix[1])/Pix_to_Y;

	//add by chenyong 2013-3-12
	//分波段处理灰度值
	char*							pch_n = NULL;
	short*							ps_n = NULL;
	float*							pi_n = NULL;
	double*							pl_n = NULL;
	unsigned char					ch_n(0);
	unsigned short					s_n(0);
	//unsigned int					i_n(0);
	float							i_n(0);
	double							l_n(0);
	unsigned char					szVal[24] = {0};
	bool							bFlag = true;

	//2013-7-11 处理边界有填充值情况
	//if (bFlagNodata)
	//{		
	//	double				tempValue = 0;
	//	bool				bBo = false;
	//	float				tempF = 0;
	//	for (int kk = 0; kk < 4; kk++)
	//	{
	//		switch (nByteSize)
	//		{
	//		case 1:
	//			pch_n = (char*)pScanBlock[kk];
	//			pScanBlock_i = static_cast<char>(pch_n[0]);
	//			break;

	//		case 2:
	//			ps_n = (short*)pScanBlock[kk];
	//			pScanBlock_i = static_cast<short>(ps_n[0]);
	//			break;

	//		case 4:
	//			pi_n = (float*)pScanBlock[kk];
	//			pScanBlock_i = static_cast<float>(pi_n[0]);
	//			break;

	//		case 8:
	//			pl_n = (double*)pScanBlock[kk];
	//			pScanBlock_i = static_cast<double>(pl_n[0]);
	//			break;
	//		}

	//		if (abs(pScanBlock_i - dNodata) > 0.00001 )
	//		{
	//			tempValue = pScanBlock_i;
	//			bBo = true;
	//			break;
	//		}
	//	}

	//	if (bBo)
	//	{
	//		for (int kk = 0; kk < 4; kk++)
	//		{
	//			switch (nByteSize)
	//			{
	//			case 1:
	//				pch_n = (char*)pScanBlock[kk];
	//				pScanBlock_i = static_cast<char>(pch_n[0]);
	//				break;

	//			case 2:
	//				ps_n = (short*)pScanBlock[kk];
	//				pScanBlock_i = static_cast<short>(ps_n[0]);
	//				break;

	//			case 4:
	//				pi_n = (float*)pScanBlock[kk];
	//				pScanBlock_i = static_cast<float>(pi_n[0]);
	//				break;

	//			case 8:
	//				pl_n = (double*)pScanBlock[kk];
	//				pScanBlock_i = static_cast<double>(pl_n[0]);
	//				break;
	//			}

	//			if (abs(pScanBlock_i - dNodata) < 0.00001 )
	//			{
	//				//pScanBlock_i = tempValue;
	//				tempF = tempValue;
	//				memcpy(pScanBlock[kk], &tempF, nByteSize);
	//			}
	//		}
	//	}
	//}
	//end 2013-7-11

	for (int k = 0; k < nBandCount; k++)
	{
		dbVal = 0;
		for (int j = 0; j < 4; j++)
		{
			switch (j)
			{
			case 0:
				arrWeight[j] = (1-deviationX)*(1-deviationY);
				break;
			case 1:
				arrWeight[j] = (1-deviationX)*deviationY;
				break;
			case 2:
				arrWeight[j] = deviationX*(1-deviationY);
				break;
			case 3:
				arrWeight[j] = deviationX*deviationY;
				break;
			default:
				break;
			}

			//获取单一波段灰度值
			switch (nByteSize) //alter by chenyong 2013-7-5
			{
			case 1:
				pch_n = (char*)pScanBlock[j];
				pScanBlock_i = static_cast<char>(pch_n[k]);
				break;

			case 2:
				ps_n = (short*)pScanBlock[j];
				pScanBlock_i = static_cast<short>(ps_n[k]);
				break;

			case 4:
				pi_n = (float*)pScanBlock[j];
				pScanBlock_i = static_cast<float>(pi_n[k]);
				break;

			case 8:
				pl_n = (double*)pScanBlock[j];
				pScanBlock_i = static_cast<double>(pl_n[k]);
				break;
			}

			//if (bFlagNodata)
			//{
			//	if (pScanBlock_i < dNodata)
			//	{
			//		dbVal += pScanBlock_i*arrWeight[j];
			//	}
			//}
			//else
			//{
				dbVal += pScanBlock_i*arrWeight[j];
			//}

		}

		switch (nByteSize)
		{
		case 1:
			ch_n = (char)dbVal;
			memcpy(szVal + k*nByteSize, &ch_n, nByteSize);
			break;

		case 2:
			s_n = (short)dbVal;
			memcpy(szVal + k*nByteSize, &s_n, nByteSize);
			break;

		case 4:
			i_n = (float)dbVal;
			memcpy(szVal + k*nByteSize, &i_n, nByteSize);
			break;

		case 8:
			l_n = (double)dbVal;
			memcpy(szVal + k*nByteSize, &l_n, nByteSize);
			break;
		}
	}

	memcpy(GrayVal, szVal, nByteSize*nBandCount);

	return ;
}

//立方卷积
void Resampling_Bicubic_DEM(double *Pt,int nImgSizeX , int nImgSizeY ,GDALDataset *poDS,/*CDeuBuffer & buf,*/void *GrayVal)
{
	double geo_src_x = Pt[0];
	double geo_src_y = Pt[1];
	double geo_src_z = Pt[2];

	int	nBandCount=poDS->GetRasterCount();
	GDALRasterBand* poBand = poDS->GetRasterBand(1);	
	unsigned int iColorDataType = GDALGetRasterDataType( poBand );
	unsigned int iDataTypeSize = GDALGetDataTypeSize( (GDALDataType)iColorDataType );
	int nByteSize = iDataTypeSize / 8 ;  
	CPLErr err;

	double          adfGeoTransform[6];
	poDS->GetGeoTransform(adfGeoTransform);
	double Pix_to_X = adfGeoTransform[1];
	double Pix_to_Y = adfGeoTransform[5];

	double GeoX =  adfGeoTransform[0];
	double GeoY =  adfGeoTransform[3];

	//找到像素点所在1阶区域
	double dbPixX , dbPixY;//用double表示的像素值 
	dbPixX = ( geo_src_x - GeoX ) / Pix_to_X ;
	dbPixY = ( geo_src_y - GeoY ) / Pix_to_Y ;

	int iEnvPix[32];
	int iEnvPix_c[32] = {0};
	for( int row = 0 ; row < 4 ; row++)
	{
		for( int col = 0 ; col < 4 ; col++)
		{
			iEnvPix[ (row * 4 + col) * 2 ] = (int)dbPixX  - 1 + row;
			iEnvPix[ (row * 4 + col) * 2 + 1] = (int)dbPixY +1 - col;

			//作处理 add by chenyong 2013-7-9
			/*if (iEnvPix[(row * 4 + col) * 2] <= 0)
			{
				iEnvPix[(row * 4 + col) * 2] = 1;
			}
			else if (iEnvPix[(row * 4 + col) * 2] >= nImgSizeX - 1)
			{
				iEnvPix[(row * 4 + col) * 2] = nImgSizeX-1;
			}
			if (iEnvPix[(row * 4 + col) * 2 + 1] <= 0)
			{
				iEnvPix[(row * 4 + col) * 2 + 1] = 1;
			}
			else if (iEnvPix[(row * 4 + col) * 2 + 1] >= nImgSizeY - 1)
			{
				iEnvPix[(row * 4 + col) * 2 + 1] = nImgSizeY-1;
			}*/
		}
	}

	for( int row = 0 ; row < 4 ; row++)
	{
		for( int col = 0 ; col < 4 ; col++)
		{
			if (iEnvPix[(row * 4 + col) * 2] <= 0)
			{
				iEnvPix_c[(row * 4 + col) * 2] = 1;
			}
			else if (iEnvPix[(row * 4 + col) * 2] >= nImgSizeX - 1)
			{
				iEnvPix_c[(row * 4 + col) * 2] = nImgSizeX-1;
			}
			else
			{
				iEnvPix_c[(row * 4 + col) * 2] = iEnvPix[(row * 4 + col) * 2];
			}
			if (iEnvPix[(row * 4 + col) * 2 + 1] <= 0)
			{
				iEnvPix_c[(row * 4 + col) * 2 + 1] = 1;
			}
			else if (iEnvPix[(row * 4 + col) * 2 + 1] >= nImgSizeY - 1)
			{
				iEnvPix_c[(row * 4 + col) * 2 + 1] = nImgSizeY-1;
			}
			else
			{
				iEnvPix_c[(row * 4 + col) * 2 + 1] = iEnvPix[(row * 4 + col) * 2 + 1];
			}
		}
	}

	//加权算像素值
	//char* pScanBlock = (char *) /*CPLMalloc*/malloc( nByteSize * 64 * 64);
	char pScanBlock [16][8];
	for(int i=0; i<16; i++)
	{
		memset( pScanBlock[i] , 0 , 8 );
	}

	for(int i=0; i<16; i++)
	{
		/*if( iEnvPix[0 + i * 2] > 0 && iEnvPix[0 + i * 2]  < nImgSizeX &&   iEnvPix[1 + i * 2] > 0 && iEnvPix[1 + i * 2]  < nImgSizeY )
		{
			err = poDS->RasterIO(GF_Read,iEnvPix[0+i*2] , iEnvPix[1+i*2],1,1,
								 pScanBlock[i],1,1,(GDALDataType)iColorDataType,nBandCount,&nBandCount,nBandCount*nByteSize,nBandCount*nByteSize,nByteSize);

		}*/

		err = poDS->RasterIO(GF_Read,iEnvPix_c[0+i*2] , iEnvPix_c[1+i*2],1,1,
							 pScanBlock[i],1,1,(GDALDataType)iColorDataType,nBandCount,&nBandCount,nBandCount*nByteSize,nBandCount*nByteSize,nByteSize);
	}
	//add by chenyong 2013-6-9 重新处理
	
	double dbEnvPix[32];
	for( int i = 0 ; i<16 ; i++)
	{
		dbEnvPix[i * 2] = iEnvPix[i * 2] * Pix_to_X + GeoX;
		dbEnvPix[i * 2 + 1] = iEnvPix[i * 2 + 1] * Pix_to_Y + GeoY;
	}

	double arrWeight[16]  ;
	double dx ,dy;

	//dx =  abs(( dbPixY - (int)dbPixY ) * Pix_to_Y) ;//参考公式
	//dy =  abs(( dbPixX - (int)dbPixX ) * Pix_to_X) ;//参考公式

	dx = abs((geo_src_x - dbEnvPix[10])/Pix_to_X);
	dy = abs((geo_src_y - dbEnvPix[11])/Pix_to_Y);

	double dbVal = 0;

#define W1(dx) ( -dx + 2 * dx * dx - dx * dx * dx ) 
#define W2(dx) ( 1 - 2 * dx * dx + dx * dx * dx ) 
#define W3(dx) ( dx +  dx * dx - dx * dx * dx ) 
#define W4(dx) ( - dx * dx + dx * dx * dx ) 

	//unsigned long  pScanBlock_i = 0;
	double  pScanBlock_i = 0;

	arrWeight[0] =	W1(dx) *  W1(dy) ;
	arrWeight[1] =	W1(dx) *  W2(dy) ;
	arrWeight[2] =	W1(dx) *  W3(dy) ;
	arrWeight[3] =	W1(dx) *  W4(dy) ;

	arrWeight[4] =	W2(dx) *  W1(dy) ;
	arrWeight[5] =	W2(dx) *  W2(dy) ;
	arrWeight[6] =	W2(dx) *  W3(dy) ;
	arrWeight[7] =	W2(dx) *  W4(dy) ;

	arrWeight[8] =	W3(dx) *  W1(dy) ;
	arrWeight[9] =	W3(dx) *  W2(dy) ;
	arrWeight[10] = W3(dx) *  W3(dy) ;
	arrWeight[11] = W3(dx) *  W4(dy) ;

	arrWeight[12] = W4(dx) *  W1(dy) ;
	arrWeight[13] = W4(dx) *  W2(dy) ;
	arrWeight[14] = W4(dx) *  W3(dy) ;
	arrWeight[15] = W4(dx) *  W4(dy) ;

	char*							pch_n = NULL;
	short*							ps_n = NULL;
	float*							pi_n = NULL;
	double*							pl_n = NULL;
	char							ch_n(0);
	short							s_n(0);
	float							i_n(0);
	double							l_n(0);
	char							szVal[24] = {0};
	//bool							bFlag = true;


	//2013-7-11 处理边界有填充值情况
	if (bFlagNodata)
	{		
		double				tempValue = 0;
		bool				bBo = false;
		float				tempF = 0;
		for (int kk = 0; kk < 16; kk++)
		{
			switch (nByteSize)
			{
			case 1:
				pch_n = (char*)pScanBlock[kk];
				pScanBlock_i = static_cast<char>(pch_n[0]);
				break;

			case 2:
				ps_n = (short*)pScanBlock[kk];
				pScanBlock_i = static_cast<short>(ps_n[0]);
				break;

			case 4:
				pi_n = (float*)pScanBlock[kk];
				pScanBlock_i = static_cast<float>(pi_n[0]);
				break;

			case 8:
				pl_n = (double*)pScanBlock[kk];
				pScanBlock_i = static_cast<double>(pl_n[0]);
				break;
			}

			if (abs(pScanBlock_i - dNodata) > 0.00001 )
			{
				tempValue = pScanBlock_i;
				bBo = true;
				break;
			}
		}

		if (bBo)
		{
			for (int kk = 0; kk < 16; kk++)
			{
				switch (nByteSize)
				{
				case 1:
					pch_n = (char*)pScanBlock[kk];
					pScanBlock_i = static_cast<char>(pch_n[0]);
					break;

				case 2:
					ps_n = (short*)pScanBlock[kk];
					pScanBlock_i = static_cast<short>(ps_n[0]);
					break;

				case 4:
					pi_n = (float*)pScanBlock[kk];
					pScanBlock_i = static_cast<float>(pi_n[0]);
					break;

				case 8:
					pl_n = (double*)pScanBlock[kk];
					pScanBlock_i = static_cast<double>(pl_n[0]);
					break;
				}

				if (abs(pScanBlock_i - dNodata) < 0.00001 )
				{
					//pScanBlock_i = tempValue;
					tempF = tempValue;
					memcpy(pScanBlock[kk], &tempF, nByteSize);
				}
			}
		}
	}
	//end 2013-7-11

	for (int k = 0; k < nBandCount; k++)
	{
		dbVal = 0;
		for (int j = 0; j < 16; j++)
		{
			switch (nByteSize)
			{
			case 1:
				pch_n = (char*)pScanBlock[j];
				pScanBlock_i = static_cast<char>(pch_n[k]);
				break;

			case 2:
				ps_n = (short*)pScanBlock[j];
				pScanBlock_i = static_cast<short>(ps_n[k]);
				break;

			case 4:
				pi_n = (float*)pScanBlock[j];
				pScanBlock_i = static_cast<float>(pi_n[k]);
				break;

			case 8:
				pl_n = (double*)pScanBlock[j];
				pScanBlock_i = static_cast<float>(pl_n[k]);
				break;
			}

			//过滤nodata值（大于0时情况）
			/*if (bFlagNodata)
			{
				if (pScanBlock_i < dNodata)
				{
					dbVal += pScanBlock_i * arrWeight[j];
				}
			}
			else
			{*/
			/*if (pScanBlock_i > 0)
			{
				dbVal += pScanBlock_i * arrWeight[j];
			}*/
				dbVal += pScanBlock_i * arrWeight[j];
			//}
		}

		switch (nByteSize)
		{
		case 1:
			ch_n = (char)dbVal;
			memcpy(szVal + k*nByteSize, &ch_n, nByteSize);
			break;

		case 2:
			s_n = (short)dbVal;
			memcpy(szVal + k*nByteSize, &s_n, nByteSize);
			break;

		case 4:
			i_n = (float)dbVal;			
			memcpy(szVal + k*nByteSize, &i_n, nByteSize);
			break;

		case 8:
			l_n = (double)dbVal;			
			memcpy(szVal + k*nByteSize, &l_n, nByteSize);
			break;
		}
	}

	memcpy(GrayVal, szVal, nByteSize*nBandCount);

	return ;
}

void SetNoDataValueDEM( GDALDataset * poDS,GDALDataset * poDSOut)
{
	dNodata = 0;
	int nBandCount = poDS->GetRasterCount();
	int *bSuccessed = (int*)/*CPLMalloc*/malloc( sizeof(int) * nBandCount ); 
	char * szLog = (char*)/*CPLMalloc*/malloc( sizeof(char) * 200 );

	for(int i = 0; i < nBandCount ; i++)
	{
		GDALRasterBand* poBand = poDS->GetRasterBand(i+1);
		GDALRasterBand* poBandOut = poDSOut->GetRasterBand(i+1);
		double dbNoDataValue = GDALGetRasterNoDataValue( poBand , bSuccessed+i );

		//GDALSetRasterNoDataValue( poBandOut ,0); 
		if(bSuccessed[i])
		{
			GDALSetRasterNoDataValue( poBandOut , dbNoDataValue );
			sprintf( szLog , "NoDataValue=%lf, bSuccessed=%d",dbNoDataValue,bSuccessed[i]);
			LOGSTR(szLog);

			//if (dbNoDataValue > 0)
			//{
			if (dbNoDataValue > 0)
			{
				dNodata = dbNoDataValue;
				GDALSetRasterNoDataValue( poBandOut , dbNoDataValue );
			}
			else
			{
				GDALSetRasterNoDataValue(poBandOut, dNodata);
			}		
			//}
			//else
			//{
				//GDALSetRasterNoDataValue(poBandOut, dNodata);
			//}
		}
		else
		{
			LOGSTR("没有设置NoDataValue");
			GDALSetRasterNoDataValue(poBandOut, dNodata);
		}
	}

	if (dNodata > 0)
	{
		bFlagNodata = true;
	}

	free( bSuccessed );
	free( szLog );

	return;
}

HRESULT CDeuRasterTrans::InitGridTranslate(std::string strFileName)
{
	m_GridTranslate.InitGridTranslate(strFileName);

	return S_OK;
}