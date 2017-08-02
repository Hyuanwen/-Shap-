#include "stdafx.h"
#include "ArcSDERaster.h"

clock_t t_start;
clock_t t_end;
#define START_TIME 	t_start = clock();
#define END_TIME	t_end	  = clock();	

#define SEC_PER_CLOCKS 0.001

#define LOG_USED_TIME \
	int time_i=(t_end-t_start)*SEC_PER_CLOCKS;\
	char * time = (char *)malloc(20);\
	itoa(time_i,time,10);\
	LOG("总共用时(秒):",time,100);\
	free(time);

//gdal
#include "gdal_priv.h"

using namespace std;

GDALProgressFunc _ProgressFunc;

DWORD WINAPI ThreadLoadWait(HANDLE _handle)
{
	HWND	hWnd = (HWND)_handle;

	unsigned int i = 0;
	while (true)
	{
		i = i%100;

		::SendMessage(hWnd, WM_LOADWAIT, NULL, i);
		++i;
		Sleep(1000);
	}
}

CArcSDERaster::CArcSDERaster():m_WorkspaceSrc(NULL),m_WorkspaceDes(NULL)
{
	
}

CArcSDERaster::CArcSDERaster(IWorkspacePtr ipWorkspaceSrc)
							:m_WorkspaceSrc(ipWorkspaceSrc)
{
	
}

HRESULT CArcSDERaster::RegisterWnd(HWND hwnd)
{
	m_hWnd = hwnd;
	return S_OK;
}

void	CArcSDERaster::SetTransParam(IWorkspacePtr pWorkspaceSrc, IWorkspacePtr pWorkspaceDes, const CDeuRasterTrans& trans, const string& strPrjFullPath)
{
	m_WorkspaceSrc = pWorkspaceSrc;
	m_WorkspaceDes = pWorkspaceDes;
	m_strPrjFullPath = strPrjFullPath;
	m_DeuRasterTrans = trans;
}

HRESULT	CArcSDERaster::GetRasterByType(esriDatasetType type, vector<STR_SDEINFO>& vecDT)
{
	IEnumDatasetPtr							ipEDS = NULL;
	IDatasetPtr								ipDS = NULL;
	BSTR									name;
	HRESULT									hr;
	esriDatasetType							esriDTType = esriDTAny;
	STR_SDEINFO								sdeInfo;

	ASSERT(m_WorkspaceSrc);

	//1.获取所以数据集
	hr = m_WorkspaceSrc->get_Datasets(type, &ipEDS);
	if (FAILED(hr))
	{
		return S_FALSE;
	}

	ipEDS->Reset();

	//2.遍历
	hr = ipEDS->Next(&ipDS);
	if (FAILED(hr))
	{
		return S_FALSE;
	}

	while (ipDS != NULL)
	{
		ipDS->get_Name(&name);
		sdeInfo.strName = _com_util::ConvertBSTRToString(name);

		switch (type)
		{
		case esriDTRasterBand:		
			sdeInfo.Type = deuRasterBand;
			break;

		case esriDTRasterDataset:
			sdeInfo.Type = deuRasterDataset;
			break;

		case esriDTRasterCatalog:
			sdeInfo.Type = deuRasterCatalog;
			break;

		default:
			sdeInfo.Type = deuUnknownType;
			break;
		}
		vecDT.push_back(sdeInfo);

		ipEDS->Next(&ipDS);
	}

	return S_OK;
}
HRESULT	CArcSDERaster::GetAllRasterNameAndType(vector<STR_SDEINFO>& vecDT)
{
	//1.RasterDataset
	GetRasterByType(esriDTRasterDataset, vecDT);

	//2.RasterCatalog
	GetRasterByType(esriDTRasterCatalog, vecDT);

	//3.RasterBand
	GetRasterByType(esriDTRasterBand, vecDT);

	return S_OK;
}


HRESULT	CArcSDERaster::TransRasterDTType(STR_SDEINFO sdeInfo)
{
	LOGSTR(":CoordRasterTransSDE");
	_bstr_t _bstr_filename = (sdeInfo.strName).c_str();
	LOGSTR((LPSTR)_bstr_filename);
	LOG_START;
	START_TIME;

	IWorkspaceEditPtr				ipWorkspaceEdit = m_WorkspaceDes;
	HRESULT							hr = S_OK;
	VARIANT_BOOL					variantEdit = VARIANT_FALSE;
	switch (sdeInfo.Type)
	{
	case deuRasterBand:			

		break;

	case deuRasterDataset:					

		//TransRasterDataset(sdeInfo.strName);

		hr = TransRasterDatasetByLocal(sdeInfo.strName);
		if (hr == S_FALSE)
		{
			ipWorkspaceEdit->IsBeingEdited(&variantEdit);
			if (variantEdit)
			{
				ipWorkspaceEdit->StopEditOperation();
				ipWorkspaceEdit->UndoEditOperation();
				//ipWorkspaceEdit->StopEditing(VARIANT_FALSE);
			}
		}
		break;

	case deuRasterCatalog:

		hr = TransRasterCatalog(sdeInfo.strName);
		if (hr == S_FALSE)
		{
			ipWorkspaceEdit->IsBeingEdited(&variantEdit);
			if (variantEdit)
			{
				ipWorkspaceEdit->StopEditOperation();
				ipWorkspaceEdit->UndoEditOperation();
				//ipWorkspaceEdit->StopEditing(VARIANT_FALSE);
			}
		}
		break;

	default:

		break;
	}

	END_TIME;
	LOG_USED_TIME;
	LOG_END;
	LOGSTR("=====================================================================");

	return hr;
}

HRESULT	CArcSDERaster::TransRasterDataset(const string& strRasterName)
{
	IRasterWorkspaceExPtr				ipRasterWS = m_WorkspaceSrc;
	IRasterWorkspaceExPtr				ipRasterWS_Des = m_WorkspaceDes;
	IRasterDatasetPtr					ipRasterDS;	
	IRasterDatasetPtr					ipRasterDS_Des;
	IRasterPtr							ipRasterSr;
	IRasterPtr							ipRasterDes;
	IRasterPropsPtr						ipRasterProSrc;
	IRasterPropsPtr						ipRasterProDes;
	IEnvelopePtr						ipEnvelopeSrc;

	double								dXmin = 0;
	double								dYmin = 0;
	double								dXmax = 0;
	double								dYmax = 0;
	double								dXPixel = 0;
	double								dYPixel = 0;

	long								lHeightSrc = 0;
	long								lWidthSrc = 0;

	rstPixelType						rstPixTypeSrc = PT_UNKNOWN;
	IPntPtr								ipPnt = NULL;
	HRESULT								Hr;
	VARIANT								varNoDataValue;
	varNoDataValue.vt = VT_R4;
	

	IWorkspaceEditPtr					ipWorkspaceEdit = m_WorkspaceDes;

	char								szLog[128] = {0};
	sprintf(szLog, _T("开始转换栅格数据集%s"), strRasterName.c_str());
	LOGSTR(szLog);

	IWorkspaceEdit2Ptr								ipWorkspaceEdit2 = ipWorkspaceEdit;
	VARIANT_BOOL									IsActive = VARIANT_FALSE;

	ipWorkspaceEdit2->get_IsInEditOperation(&IsActive);
	if (IsActive == VARIANT_TRUE)
	{
		AfxMessageBox(_T("数据正在被另外一个会话进程编辑....."));
		return S_FALSE;
	}

	ipWorkspaceEdit->StartEditing(VARIANT_TRUE);
	ipWorkspaceEdit->StartEditOperation();

	Hr = ipRasterWS->OpenRasterDataset(_bstr_t(strRasterName.c_str()), &ipRasterDS);
	if (FAILED(Hr))
	{
		sprintf(szLog, _T("打开栅格数据集%s失败,返回错误码:%ld"), strRasterName.c_str(), (long)Hr);
		LOGSTR(szLog);
		return S_FALSE;
	}

	IRasterDataset2Ptr					ipRasterDS2_Src(ipRasterDS);
	ipRasterDS2_Src->CreateFullRaster(&ipRasterSr);
	ipRasterProSrc = ipRasterSr;

	ipRasterProSrc->get_Extent(&ipEnvelopeSrc);

	//获取源影像坐标范围
	ipEnvelopeSrc->get_XMin(&dXmin);
	ipEnvelopeSrc->get_XMax(&dXmax);
	ipEnvelopeSrc->get_YMin(&dYmin);
	ipEnvelopeSrc->get_YMax(&dYmax);

	//像素类型及长宽像素个数
	ipRasterProSrc->get_PixelType(&rstPixTypeSrc);
	ipRasterProSrc->MeanCellSize(&ipPnt);
	ipRasterProSrc->get_Height(&lHeightSrc);
	ipRasterProSrc->get_Width(&lWidthSrc);
	ipRasterProSrc->get_NoDataValue(&varNoDataValue);	

	//分辨率
	ipPnt->get_X(&dXPixel);
	ipPnt->get_Y(&dYPixel);

	//获取波段数
	IRasterBandCollectionPtr			ipRasterBandColSrc(ipRasterSr);
	long								lBandCount = 0;

	ipRasterBandColSrc->get_Count(&lBandCount);

	IRasterStorageDefPtr				ipRasterStoDef(CLSID_RasterStorageDef);
	ipRasterStoDef->putref_CellSize(ipPnt);

	IRasterDefPtr						ipRasterDef(CLSID_RasterDef);


	//创建新栅格数据集
	Hr = ipRasterWS_Des->CreateRasterDataset(_bstr_t(strRasterName.c_str()), lBandCount, rstPixTypeSrc, ipRasterStoDef, _bstr_t(""), ipRasterDef, NULL, &ipRasterDS_Des);
	if (FAILED(Hr))
	{
		sprintf(szLog, _T("创建栅格数据集%s失败,返回错误码:%ld"), strRasterName.c_str(), (long)Hr);
		LOGSTR(szLog);
		return S_FALSE;
	}

	//空间参考系 add by chenyong 2013-10-15
	AlterSpatialReference(m_strPrjFullPath, ipRasterDS_Des);

	IRasterDataset2Ptr					ipRasterDS2_Des(ipRasterDS_Des);
	ipRasterDS2_Des->CreateFullRaster(&ipRasterDes);

	//计算目标栅格数据集的
	double			geo_x_src[4] = {0};
	double			geo_y_src[4] = {0};
	double			geo_x_des[4] = {0};
	double			geo_y_des[4] = {0};

	geo_x_src[0] = geo_x_src[1] = dXmin;
	geo_x_src[2] = geo_x_src[3] = dXmax;
	geo_y_src[0] = geo_y_src[3] = dYmin;
	geo_y_src[1] = geo_y_src[2] = dYmax;


	m_DeuRasterTrans._coord_transf(m_DeuRasterTrans.m_Para, m_DeuRasterTrans.m_TransModel, 4, geo_y_src, geo_x_src, 0, geo_y_des, geo_x_des, 0);

	//计算新栅格数据集的范围
	double		dNewXmin(0);
	double		dNewXmax(0);
	double		dNewYmin(0);
	double		dNewYmax(0);

	dNewXmin = dNewXmax = geo_x_des[0];
	dNewYmin = dNewYmax = geo_y_des[0];

	for (int i = 1; i < 4; ++i)
	{
		dNewXmax = (geo_x_des[i] > dNewXmax) ? geo_x_des[i] : dNewXmax;
		dNewXmin = (geo_x_des[i] < dNewXmin) ? geo_x_des[i] : dNewXmin;
		dNewYmax = (geo_y_des[i] > dNewYmax) ? geo_y_des[i] : dNewYmax;
		dNewYmin = (geo_y_des[i] < dNewYmin) ? geo_y_des[i] : dNewYmin;
	}

	IEnvelopePtr						ipEnvelopeDes(CLSID_Envelope);
	ipEnvelopeDes->PutCoords(dNewXmin, dNewYmin, dNewXmax, dNewYmax);

	//计算X,Y像素个数
	long		lX(0);		//Width
	long		lY(0);		//Height

	lX = (long)((dNewXmax - dNewXmin)/dXPixel);
	lY = (long)((dNewYmax - dNewYmin)/dYPixel);

	//设置nodatavalue add by chenyong 2013-11-12 临时处理
	long			lNewNodataValue(255);
	SAFEARRAY			*pArray = varNoDataValue.parray;

	for (long ii = 0; ii < lBandCount; ++ii)
	{
		//SafeArrayGetElement(pArray, &ii, (void*)&lNewNodataValue);
		//lNewNodataValue -=1;
		SafeArrayPutElement(pArray, &ii, (void*)&lNewNodataValue);
	}

	//新栅格数据集的属性信息
	ipRasterProDes = ipRasterDes;
	Hr = ipRasterProDes->put_NoDataValue(varNoDataValue);
	ipRasterProDes->put_Height(lY);
	ipRasterProDes->put_Width(lX);
	ipRasterProDes->put_Extent(ipEnvelopeDes);


	//add by chenyong 2013-10-16
 	VARTYPE						varType;
 	switch (rstPixTypeSrc)
  	{
  
  	case PT_UCHAR:
  		varType = VT_UI1;
  		break;
  
  	case PT_USHORT:
  		varType = VT_UI2;
  		break;
  
  	default:
  		varType = VT_UI4;
  		break;
  
  	}


 	STR_RASTERPARAM				para;
 	para.dPixelX = dXPixel;
 	para.dPixelY = dYPixel;
	para.dPixelXDes = dXPixel;
	para.dPixelYDes = dYPixel;
 	para.dXminSrc = dXmin;
 	para.dYmaxSrc = dYmax;
 	para.dXminDes = dNewXmin;
 	para.dYmaxDes = dNewYmax;
 	para.lBandCount = lBandCount;
 	para.type = varType;
 	para.lWidthSrc = lWidthSrc;
 	para.lHeighSrc = lHeightSrc;
 	para.lWidthDes = lX;
 	para.lHeighDes = lY;

	para.envSrc.dXmin = dXmin;
	para.envSrc.dYmin = dYmin;
	para.envSrc.dXmax = dXmax;
	para.envSrc.dYmax = dYmax;

	para.envDes.dXmin = dNewXmin;
	para.envDes.dYmin = dNewYmin;
	para.envDes.dXmax = dNewXmax;
	para.envDes.dYmax = dNewYmax;
	para.lNoValue = varNoDataValue;

	//采样
	switch (m_DeuRasterTrans.m_Resampling)
	{
	case RESAMPLING_NEAREST:
	case RESAMPLING_BILINEAR:
	case RESAMPLING_BICUBIC:

		//是否分块处理add by chenyong 2013-10-21
  		if (lX > /*5000*/10000 || lY > /*5000*/10000)
  		{
 			Hr = TransRasterByNearestBlock(ipRasterSr, ipRasterDes, para);
 		}
  		else
  		{
  			Hr = TransRasterByNearest(ipRasterSr, ipRasterDes, para);
  		}
 
  		if (FAILED(Hr))
  		{
  			AfxMessageBox(_T("栅格转换失败!"));
  			return Hr;  
  		}


		break;

// 	case RESAMPLING_BILINEAR:
// 
// 		break;
// 
// 	case RESAMPLING_BICUBIC:
// 
// 		break;

	default:

		break;
	}
	

	//计算统计 add by chenyong 2013-10-14
	IRasterBandCollectionPtr								ipRasterBandCol(ipRasterDes);

	CaComputeStatsAndHist(ipRasterBandCol);


	ipWorkspaceEdit->StopEditOperation();
	ipWorkspaceEdit->StopEditing(VARIANT_TRUE);

	sprintf(szLog, _T("完成转换栅格数据集%s"), strRasterName.c_str());
	LOGSTR(szLog);

	return S_OK;
}

HRESULT CArcSDERaster::TransRasterCatalog(const string& strCatalogName)
{
	IRasterWorkspaceExPtr						ipRasterWS_Src = m_WorkspaceSrc;
	IRasterWorkspaceExPtr						ipRasterWS_Des = m_WorkspaceDes;
	IRasterCatalogPtr							ipRasterCatalog_Src;
	IRasterCatalogPtr							ipRasterCatalog_Des;
	HRESULT										hr;

	GDALAllRegister();

	//需要处理下：
	IWorkspaceEditPtr							ipWorkspaceEdit = m_WorkspaceDes;

	char										szLog[128] = {0};
	sprintf(szLog, _T("开始转换栅格目录%s"), strCatalogName.c_str());
	LOGSTR(szLog);

	IWorkspaceEdit2Ptr								ipWorkspaceEdit2 = ipWorkspaceEdit;
	VARIANT_BOOL									IsActive = VARIANT_FALSE;

	ipWorkspaceEdit2->get_IsInEditOperation(&IsActive);
	if (IsActive == VARIANT_TRUE)
	{
		AfxMessageBox(_T("数据正在被另外一个会话进程编辑....."));
		return S_FALSE;
	}

	//检查是否存在相同名字的数据 add by chenyong 2014-2-11
	IWorkspace2Ptr					ipWorkspace2 = m_WorkspaceDes;
	VARIANT_BOOL					varExist = VARIANT_FALSE;

	ipWorkspace2->get_NameExists(esriDTRasterCatalog, _bstr_t(strCatalogName.c_str()), &varExist);
	if (varExist)
	{
		sprintf(szLog, _T("目标库中存在栅格目录%s"), strCatalogName.c_str());
		LOGSTR(szLog);
		return S_FALSE;
	}

	hr = ipRasterWS_Src->OpenRasterCatalog(_bstr_t(strCatalogName.c_str()), &ipRasterCatalog_Src);
	if (FAILED(hr))
	{
		sprintf(szLog, _T("打开栅格目录%s失败,返回错误码:"), strCatalogName.c_str(), (long)hr);
		LOGSTR(szLog);
		return S_FALSE;
	}

	ITablePtr									iptable_Src(ipRasterCatalog_Src);
	IFieldsPtr									ipFields;
	long										lIndex(0);
	long										lRows(0);
	
	iptable_Src->get_Fields(&ipFields);
	ipFields->FindField(_bstr_t("NAME"), &lIndex);
	iptable_Src->RowCount(NULL, &lRows);

	//创建RasterWorkFactory
	IWorkspaceFactoryPtr						ipWorkSF(CLSID_RasterWorkspaceFactory);
	IWorkspacePtr								ipWorks_local;

	//特定目录
	CString strExcutePath = GetStylesPath();
	string										strSpecDir = string(strExcutePath + _T("\\SDE"));
	
	if (IsExistDir(strSpecDir))
	{
		DeleteAllFile(strSpecDir);
	}
	else
	{
		CreateDir(strSpecDir);
	}

	hr = ipWorkSF->OpenFromFile(_bstr_t(strSpecDir.c_str()), NULL, &ipWorks_local);

	IRasterWorkspace2Ptr						ipRasterWS2(ipWorks_local);

	//遍历源RasterCatalog
	esriIRowPtr									ipRow;
	IRowBufferPtr								ipRowBuffer;
	IRasterCatalogItemPtr						ipRasterCatalogItem;
	VARIANT										varName;
	IRasterDatasetPtr							ipRasterDS;
	IRasterDataset2Ptr							ipRasterDS2;
	IRasterPtr									ipRaster;
	string										strFullPath;
	GDALDataset									*pDS = NULL;
	GDALRasterBand								*pBand = NULL;
	int			bApproxOK = 0;
	double		pdfMin = 0;
	double		pdfMax = 0;
	double		pdfMean = 0;
	double		pdfStdDev = 0;
	void*	pProgressData = NULL;

	IRasterPropsPtr			ipProps;
	long					lBands = 0;
	VARIANT					var;
	var.vt = VT_R4;

	IRasterBandCollectionPtr		ipRasterBandCol;
	SAFEARRAY*		pArray = NULL;
	long			fValue = 0;
	long			lNodataValue = 0;


 	for (int i = 1; i <= lRows; ++i)
 	{
 		iptable_Src->GetRow(i, &ipRow);
 		ipRowBuffer = ipRow;
 		
 		ipRowBuffer->get_Value(lIndex, &varName);
 		ipRasterCatalogItem = ipRow;
 		ipRasterCatalogItem->get_RasterDataset(&ipRasterDS);
 		ipRasterDS2 = ipRasterDS;
 		ipRasterDS2->CreateFullRaster(&ipRaster);
 		
 		CreateLocalRasteDataset( _com_util::ConvertBSTRToString(varName.bstrVal), ipRasterWS2, ipRaster);
 
 		//用gdal处理nodatavalue
 		strFullPath = strSpecDir + _T("\\") + _com_util::ConvertBSTRToString(varName.bstrVal);
 		pDS = (GDALDataset*)GDALOpen(strFullPath.c_str(), GA_Update);
 		if (NULL == pDS)
 		{
 			continue;
 		}
 
 		ipProps = ipRaster;
 		ipProps->get_NoDataValue(&var);
 		rstPixelType rstPixTypeSrc;
 		ipProps->get_PixelType(&rstPixTypeSrc);
 		pArray = var.parray;
 		ipRasterBandCol = ipRaster;
 		ipRasterBandCol->get_Count(&lBands);
 
 		for (long Band = 0; Band < lBands; ++Band)
 		{
 			::SafeArrayGetElement(pArray, &Band, &fValue);
 			lNodataValue = fValue - 1;
 
 			switch(rstPixTypeSrc)
 			{
 			case PT_UCHAR:
 				if (fValue == 256)
 				{
 					lNodataValue = fValue -1;
 				}
 				else
 				{
 					lNodataValue = fValue;
 				}
 
 				pBand = pDS->GetRasterBand(Band+1);
 				GDALSetRasterNoDataValue(pBand, lNodataValue);
 				pBand->ComputeStatistics(bApproxOK, &pdfMin, &pdfMax, &pdfMean, &pdfStdDev, _ProgressFunc, pProgressData);
 
 				break;
 
 			case PT_USHORT:
 				if (fValue == 65536)
 				{
 					lNodataValue = fValue -1;
 					
 				}
 				else
 				{
 					lNodataValue = fValue;
 				}
 
 				pBand = pDS->GetRasterBand(Band+1);
 				GDALSetRasterNoDataValue(pBand, lNodataValue);
 				pBand->ComputeStatistics(bApproxOK, &pdfMin, &pdfMax, &pdfMean, &pdfStdDev, _ProgressFunc, pProgressData);
 
 				break;
 
 			default:
 				break; 
 
 			}
 
 		}
 
 		GDALClose((GDALDatasetH)pDS);
 	}

	ipWorkspaceEdit->StartEditing(VARIANT_TRUE);
	ipWorkspaceEdit->StartEditOperation();

	BSTR										strShapeName;
	BSTR										strRasterName;

	IFeatureClassPtr							ipFeatureCls = ipRasterCatalog_Src;

	ipFeatureCls->get_ShapeFieldName(&strShapeName);
	ipRasterCatalog_Src->get_RasterFieldName(&strRasterName);

	hr = ipRasterWS_Des->CreateRasterCatalog(_bstr_t(strCatalogName.c_str()), ipFields, strShapeName, strRasterName, _bstr_t(""), &ipRasterCatalog_Des);
	if (FAILED(hr))
	{
		sprintf(szLog, _T("创建栅格目录%s失败,返回错误码:"), strCatalogName.c_str(), (long)hr);
		LOGSTR(szLog);
		return S_FALSE;
	}


	//add by chenyong 2014-3-7
	HANDLE hWait = ::CreateThread(NULL, 0, ThreadLoadWait, m_hWnd, 0, NULL);

	ITrackCancelPtr								ipTrackCancel(CLSID_CancelTracker);
	IRasterCatalogLoaderPtr						ipRasterCatalogLoader(CLSID_RasterCatalogLoader);

	ipRasterCatalogLoader->putref_Workspace(m_WorkspaceDes);
	hr = ipRasterCatalogLoader->Load(_bstr_t(strCatalogName.c_str()), _bstr_t(strSpecDir.c_str()), ipTrackCancel);
	if (FAILED(hr))
	{
		::TerminateThread(hWait, 0);
		sprintf(szLog, _T("上传栅格数据文件失败"));
		LOGSTR(szLog);
	}

	::TerminateThread(hWait, 0);


	//计算统计
	iptable_Src = ipRasterCatalog_Des;

	IRasterBandCollectionPtr			ipRasterBandCol2;
	for (int k = 1; k <= lRows; ++k )
	{
		iptable_Src->GetRow(k, &ipRow);
		
		ipRasterCatalogItem = ipRow;
		ipRasterCatalogItem->get_RasterDataset(&ipRasterDS);
		ipRasterDS2 = ipRasterDS;
		ipRasterDS2->CreateFullRaster(&ipRaster);
		
		ipRasterBandCol2 = ipRaster;

		CaComputeStatsAndHist(ipRasterBandCol2);
	}

	//
	ipWorkspaceEdit->StopEditOperation();
	ipWorkspaceEdit->StopEditing(VARIANT_TRUE);

	sprintf(szLog, _T("完成转换栅格目录%s"), strCatalogName.c_str());
	LOGSTR(szLog);
	
	return S_OK;
}
HRESULT CArcSDERaster::CaComputeStatsAndHist(IRasterBandCollectionPtr ipRasterBandCol)
{
	IRasterBandPtr											ipRasterBand;
	VARIANT_BOOL											varIsHave;
	long													lBandCount(0);

	if (NULL == ipRasterBandCol)
	{
		return S_FALSE;
	}

	ipRasterBandCol->get_Count(&lBandCount);

	for (int k = 0 ; k < lBandCount; ++k)
	{
		ipRasterBandCol->Item(k, &ipRasterBand);
		ipRasterBand->HasStatistics(&varIsHave);
		if (varIsHave == VARIANT_FALSE)
		{
			ipRasterBand->ComputeStatsAndHist();
		}

	}

	return S_OK;
}

HRESULT CArcSDERaster::AlterSpatialReference(const std::string &strSpatialRef, IRasterDatasetPtr ipRasterDS)
{
	ISpatialReferenceFactoryPtr							ipSpatialFac(CLSID_SpatialReferenceEnvironment);
	ISpatialReferencePtr								ipSpatialSrc;
	HRESULT												hr;
	IGeoDatasetPtr										ipGeoDS(ipRasterDS);
	IGeoDatasetSchemaEditPtr							ipGeoDSEdit(ipGeoDS);
	VARIANT_BOOL										varCan;

	hr = ipSpatialFac->CreateESRISpatialReferenceFromPRJFile(_bstr_t(strSpatialRef.c_str()), &ipSpatialSrc);
	if (FAILED(hr))
	{
		return hr;
	}

	ipGeoDSEdit->get_CanAlterSpatialReference(&varCan);
	if (varCan == VARIANT_TRUE)
	{
		hr = ipGeoDSEdit->AlterSpatialReference(ipSpatialSrc);
		if (FAILED(hr))
		{
			return hr;
		}
	}

	return S_OK;
}

HRESULT	CArcSDERaster::TransRasterByNearestBlock(IRasterPtr ipRasterSrc, IRasterPtr ipRasterDes, STR_RASTERPARAM param)
{
	VARIANT									varTemp;
	long									bElement(0);		
	long									index[2] = {0};
	VARIANT									varNewValue;
	SAFEARRAY*								psa = NULL;
	double									dXCoorSrc(0);
	double									dYCoorSrc(0);
	double									dXCoorDes(0);
	double									dYCoorDes(0);
	long									dXPixelSrc(0);
	long									dYPixelSrc(0);
	IPixelBlockPtr							ipPixBlockSrc;
	IPixelBlockPtr							ipPixBlockDes;
	HRESULT									Hr;
	long									lBlockXCount(0);
	long									lBlockYCount(0);
 	long									lBlockX(5000);
 	long									lBlockY(5000);

	//long									lBlockX(1500);
	//long									lBlockY(1500);

	char szLog[128] = {0};

	lBlockXCount = (long)((param.lWidthDes/lBlockX)+1);
	lBlockYCount = (long)((param.lHeighDes/lBlockY)+1);


	IPntPtr									ipPntOrient(CLSID_Pnt);
	ipPntOrient->SetCoords(0, 0);

	IPntPtr									ipPntOrientDes(CLSID_Pnt);
	ipPntOrientDes->SetCoords(0, 0);

	IPntPtr									ipPntSizeSrc(CLSID_Pnt);
	ipPntSizeSrc->SetCoords(lBlockX + param.lWidthDes - param.lWidthSrc, lBlockY + param.lHeighDes - param.lHeighSrc);

	IPntPtr										ipPntSizeDes(CLSID_Pnt);
	ipPntSizeDes->SetCoords(lBlockX, lBlockY);

	ipRasterDes->CreatePixelBlock(ipPntSizeDes, &ipPixBlockDes);

	IRasterEditPtr								ipRasterEdit(ipRasterDes);


	SAFEARRAYBOUND				sab[2] = {0};
	sab[0].cElements = lBlockX;
	sab[0].lLbound = 0;
	sab[1].cElements = lBlockY;
	sab[1].lLbound = 0;

	double			geo_x_src[4] = {0};
	double			geo_y_src[4] = {0};
	double			geo_x_des[4] = {0};
	double			geo_y_des[4] = {0};
	double			dNewXmin(0);
	double			dNewXmax(0);
	double			dNewYmin(0);
	double			dNewYmax(0);

	double			dXminTemp(0);
	double			dXmaxTemp(0);
	double			dYminTemp(0);
	double			dYmaxTemp(0);

	long			lWidthTemp(0);
	long			lHeighTemp(0);

	SAFEARRAY*								pArray = param.lNoValue.parray;
	long									fValue(0);

	//进度条 add by chenyong 2013-12-4
	/*unsigned double						lPixelCount = param.lBandCount* param.lHeighDes*param.lWidthDes/100;*/
	double						lPixelCount = param.lBandCount* lBlockXCount*lBlockYCount*(lBlockX/1000)*(lBlockY/1000);//数值越界，超出数值类型的表示
	double						lPixelDone = 0;

	unsigned int				Percent = lPixelDone / lPixelCount;
	::SendMessage(m_hWnd, WM_PROGRESS, 0, Percent);

	for (int k = 1; k <= lBlockYCount; ++k)
	{
		for (int j = 1; j <= lBlockXCount; ++j)
		{
			ipPntOrientDes->SetCoords((j-1) * lBlockX, (k-1) * lBlockY);

			//计算目标每个块的起始像素位置
			geo_x_des[0] = geo_x_des[3] = (j-1) * lBlockX * param.dPixelXDes + param.envDes.dXmin;
			geo_y_des[0] = geo_y_des[1] = param.envDes.dYmax - (k-1) * lBlockY * param.dPixelYDes;
			geo_x_des[1] = geo_x_des[2] = j * lBlockX * param.dPixelXDes + param.envDes.dXmin;
			geo_y_des[2] = geo_y_des[3] = param.envDes.dYmax - k * lBlockY * param.dPixelYDes;

			m_DeuRasterTrans._inv_coord_transf(m_DeuRasterTrans.m_InvPara, m_DeuRasterTrans.m_TransModel, 4, geo_y_des, geo_x_des, 0, geo_y_src, geo_x_src, 0);

			dNewXmin = dNewXmax = geo_x_src[0];
			dNewYmin = dNewYmax = geo_y_src[0];

			for (int i = 1; i < 4; ++i)
			{
				dNewXmax = (geo_x_src[i] > dNewXmax) ? geo_x_src[i] : dNewXmax;
				dNewXmin = (geo_x_src[i] < dNewXmin) ? geo_x_src[i] : dNewXmin;
				dNewYmax = (geo_y_src[i] > dNewYmax) ? geo_y_src[i] : dNewYmax;
				dNewYmin = (geo_y_src[i] < dNewYmin) ? geo_y_src[i] : dNewYmin;
			}

			//计算
			lWidthTemp = (long)((dNewXmax - dNewXmin)/param.dPixelX);
			lHeighTemp = (long)((dNewYmax - dNewYmin)/param.dPixelY);

			//源栅格集的起始像素位置
			long				lStartXSrc = (dNewXmin - param.envSrc.dXmin)/param.dPixelX;
			long				lStartYSrc = (param.envSrc.dYmax - dNewYmax)/param.dPixelY;

			ipPntSizeSrc->SetCoords(lWidthTemp, lHeighTemp);
			ipPntOrient->SetCoords(lStartXSrc, lStartYSrc);
			ipRasterSrc->CreatePixelBlock(ipPntSizeSrc, &ipPixBlockSrc);

			ipRasterSrc->Read(ipPntOrient, ipPixBlockSrc);


			for (long lBand = 0; lBand < param.lBandCount; ++ lBand)
			{
				SafeArrayGetElement(pArray, &lBand, (void*)&fValue);
				psa = SafeArrayCreate(param.type, sizeof(sab)/sizeof(SAFEARRAYBOUND), sab);
				if (NULL == psa)
				{
					sprintf(szLog, _T("Create SafeArray Failed"));
					LOGSTR(szLog);
					return S_FALSE;
				}

				for (int iY = 0; iY < lBlockY; ++iY)
				{
					index[1] = iY;
					for (int iX = 0; iX < lBlockX; ++iX)
					{
						index[0] = iX;

						//计算新栅格像素点的坐标

						dXCoorDes = param.envDes.dXmin + ((j - 1)*lBlockX + iX) * param.dPixelXDes;
						dYCoorDes = param.envDes.dYmax - ((k - 1)*lBlockY + iY) * param.dPixelYDes;

						//计算原始栅格中对应的坐标及像素
						m_DeuRasterTrans._inv_coord_transf(m_DeuRasterTrans.m_InvPara, m_DeuRasterTrans.m_TransModel, 1, &dYCoorDes, &dXCoorDes, 0, &dYCoorSrc, &dXCoorSrc, 0);

						dXPixelSrc = (int)(((dXCoorSrc - dNewXmin)/param.dPixelX) + 0.5);
						dYPixelSrc = (int)(((dNewYmax - dYCoorSrc)/param.dPixelY) + 0.5);

						
						ipPixBlockSrc->GetVal(lBand, dXPixelSrc, dYPixelSrc, &varTemp);

						switch(varTemp.vt)
						{
						case VT_EMPTY:

							bElement = fValue;
							break;

						case VT_UI1:
							bElement = varTemp.bVal;
							break;

						case VT_UI2:
							bElement = varTemp.uiVal;
							break;

						default:

							bElement = varTemp.ulVal;
							break;

						}

						Hr = SafeArrayPutElement(psa, index, (void*)&bElement);
						if (FAILED(Hr))
						{
							continue;
						}
					}

					//进度条
					//alter by chenyong 2013-12-26 progress

					lPixelDone = ((k-1)*lBlockY*lBlockX*lBlockXCount + (j-1)*lBlockX*lBlockY)*param.lBandCount + lBlockX*lBlockY*lBand + (iY+1)*lBlockX;
					Percent = (lPixelDone/10000) / lPixelCount;
					::SendMessage(m_hWnd, WM_PROGRESS, 0, Percent);

				}

				varNewValue.vt = VT_ARRAY | param.type;
				varNewValue.parray = psa;

				Hr = ipPixBlockDes->put_SafeArray(lBand, varNewValue);

				Hr = ipRasterEdit->Write(ipPntOrientDes, ipPixBlockDes);
				if (FAILED(Hr))
				{
					sprintf(szLog, _T("生成栅格数据失败,返回错误码:%ld"), (long)Hr);
					LOGSTR(szLog);
					return S_FALSE;
				}

				ipRasterEdit->Refresh();
				SafeArrayDestroy(psa);
			}
		}
	}

	::SendMessage(m_hWnd, WM_PROGRESS, 0, 100);
	return S_OK;
		

}


HRESULT CArcSDERaster::TransRasterByNearest(IRasterPtr ipRasterSrc, IRasterPtr	ipRasterDes, STR_RASTERPARAM param)
{
	VARIANT									varTemp;
	long									bElement(0);		

	long									index[2] = {0};
	VARIANT									varNewValue;
	SAFEARRAY*								psa = NULL;

	double									dXCoorSrc(0);
	double									dYCoorSrc(0);
	double									dXCoorDes(0);
	double									dYCoorDes(0);

	long									dXPixelSrc(0);
	long									dYPixelSrc(0);

	IPixelBlockPtr							ipPixBlockSrc;
	IPixelBlockPtr							ipPixBlockDes;
	HRESULT									Hr;
	SAFEARRAY*								pArray = param.lNoValue.parray;
	long									fValue(0);
	char									szLog[128] = {0};

	IPntPtr									ipPntOrient(CLSID_Pnt);
	ipPntOrient->SetCoords(0, 0);

	IPntPtr									ipPntSizeSrc(CLSID_Pnt);
	ipPntSizeSrc->SetCoords(param.lWidthSrc, param.lHeighSrc);

	IPntPtr										ipPntSizeDes(CLSID_Pnt);
	ipPntSizeDes->SetCoords(param.lWidthDes, param.lHeighDes);

	ipRasterSrc->CreatePixelBlock(ipPntSizeSrc, &ipPixBlockSrc);
	ipRasterSrc->Read(ipPntOrient, ipPixBlockSrc);

	ipRasterDes->CreatePixelBlock(ipPntSizeDes, &ipPixBlockDes);

	IRasterEditPtr								ipRasterEdit(ipRasterDes);


	SAFEARRAYBOUND				sab[2] = {0};
	sab[0].cElements = param.lWidthDes;
	sab[0].lLbound = 0;
	sab[1].cElements = param.lHeighDes;
	sab[1].lLbound = 0;

	//进度条 add by chenyong 2013-12-4
	double						lPixelCount = param.lBandCount* param.lHeighDes*param.lWidthDes/100;
	double						lPixelDone = 0;

	unsigned int				Percent = lPixelDone / lPixelCount;
	::SendMessage(m_hWnd, WM_PROGRESS, 0, Percent);

	for (long lBand = 0; lBand < param.lBandCount; ++ lBand)
	{

		//获取每个波段的nodata值
		::SafeArrayGetElement(pArray, &lBand, &fValue);
		psa = SafeArrayCreate(param.type, sizeof(sab)/sizeof(SAFEARRAYBOUND), sab);
		if (NULL == psa)
		{
			sprintf(szLog, _T("Create SafeArray Failed"));
			LOGSTR(szLog);
			return S_FALSE;
		}

		for (int iY = 0; iY < param.lHeighDes; ++iY)
		{
			index[1] = iY;
			for (int iX = 0; iX < param.lWidthDes; ++iX)
			{
				index[0] = iX;

				//计算新栅格像素点的坐标
				dXCoorDes = param.dXminDes + iX*param.dPixelXDes;
				dYCoorDes = param.dYmaxDes - iY*param.dPixelYDes;

				//计算原始栅格中对应的坐标及像素
				m_DeuRasterTrans._inv_coord_transf(m_DeuRasterTrans.m_InvPara, m_DeuRasterTrans.m_TransModel, 1, &dYCoorDes, &dXCoorDes, 0, &dYCoorSrc, &dXCoorSrc, 0);

				dXPixelSrc = (int)(((dXCoorSrc - param.dXminSrc)/param.dPixelX) + 0.5);
				dYPixelSrc = (int)(((param.dYmaxSrc - dYCoorSrc)/param.dPixelY) + 0.5);

				ipPixBlockSrc->GetVal(lBand, dXPixelSrc, dYPixelSrc, &varTemp);

				switch(varTemp.vt)
				{
				case VT_EMPTY:
					bElement = fValue;
					break;

				case VT_UI1:
					bElement = varTemp.bVal;
					break;

				case VT_UI2:
					bElement = varTemp.uiVal;
					break;

				default:

					bElement = varTemp.ulVal;
					break;

				}

				Hr = SafeArrayPutElement(psa, index, (void*)&bElement);
				if (FAILED(Hr))
				{
					continue;
				}

			}

			//进度条
			lPixelDone = lBand * param.lHeighDes * param.lWidthDes + (iY*param.lWidthDes);
			Percent = lPixelDone/lPixelCount;

			::SendMessage(m_hWnd, WM_PROGRESS, 0, Percent);
			

		}

		varNewValue.vt = VT_ARRAY | param.type;
		varNewValue.parray = psa;

		Hr = ipPixBlockDes->put_SafeArray(lBand, varNewValue);
		if (FAILED(Hr))
		{
			return Hr;
		}

		Hr = ipRasterEdit->Write(ipPntOrient, ipPixBlockDes);
		if (FAILED(Hr))
		{
			sprintf(szLog, _T("生成栅格数据失败,返回错误码:%ld"), (long)Hr);
			LOGSTR(szLog);
		}

		Hr = ipRasterEdit->Refresh();
		SafeArrayDestroy(psa);
	}

	::SendMessage(m_hWnd, WM_PROGRESS, 0, 100);
	return S_OK;

}

HRESULT CArcSDERaster::CreateLocalRasteDataset(const string& strName, IRasterWorkspace2Ptr ipRasterWS, IRasterPtr ipRaster)
{
	IRasterPropsPtr							ipRasterProps(ipRaster);
	IEnvelopePtr							ipEnvelope;
	long									lHeight(0);
	long									lWidth(0);
	rstPixelType							pixelType = PT_UNKNOWN;
	double									dPixelX(0);
	double									dPixelY(0);
	VARIANT									varNoDataValue;
	IPntPtr									ipMeanCellSize;
	HRESULT									hr;
	char									szLog[128] = {0};
	
	varNoDataValue.vt = VT_R4;

	ipRasterProps->get_Extent(&ipEnvelope);
	ipRasterProps->get_Height(&lHeight);
	ipRasterProps->get_Width(&lWidth);
	ipRasterProps->get_PixelType(&pixelType);
	ipRasterProps->get_NoDataValue(&varNoDataValue);
	ipRasterProps->MeanCellSize(&ipMeanCellSize);

	ipMeanCellSize->get_X(&dPixelX);
	ipMeanCellSize->get_Y(&dPixelY);

	//1.空间参考系
	ISpatialReferenceFactoryPtr							ipSpatialFac(CLSID_SpatialReferenceEnvironment);
	ISpatialReferencePtr								ipSpatialSrc;

	hr = ipSpatialFac->CreateESRISpatialReferenceFromPRJFile(_bstr_t(m_strPrjFullPath.c_str()), &ipSpatialSrc);

	long									lBandCount(0);
	IRasterBandCollectionPtr				ipRasterBandCol(ipRaster);
	long									lNewWidth(0);
	long									lNewHeight(0);
	IRasterDatasetPtr						ipRasterDs;
	ipRasterBandCol->get_Count(&lBandCount);

	//需要计算目标文件坐标范围
	double									dXminSrc(0);
	double									dYminSrc(0);
	double									dXmaxSrc(0);
	double									dYmaxSrc(0);

	ipEnvelope->get_XMin(&dXminSrc);
	ipEnvelope->get_YMin(&dYminSrc);
	ipEnvelope->get_XMax(&dXmaxSrc);
	ipEnvelope->get_YMax(&dYmaxSrc);

	double									geo_x_src[4] = {0};
	double									geo_y_src[4] = {0};
	double									geo_x_des[4] = {0};
	double									geo_y_des[4] = {0};

	geo_x_src[0] = geo_x_src[1] = dXminSrc;
	geo_x_src[2] = geo_x_src[3] = dXmaxSrc;
	geo_y_src[0] = geo_y_src[3] = dYminSrc;
	geo_y_src[1] = geo_y_src[2] = dYmaxSrc;

	m_DeuRasterTrans._coord_transf(m_DeuRasterTrans.m_Para, m_DeuRasterTrans.m_TransModel, 4, geo_y_src, geo_x_src, 0, geo_y_des, geo_x_des, 0);

	//计算新栅格数据集的范围
	double									dNewXmin(0);
	double									dNewXmax(0);
	double									dNewYmin(0);
	double									dNewYmax(0);

	dNewYmin = dNewYmax = geo_y_des[0];
	dNewXmin = dNewXmax = geo_x_des[0];

	for (int i = 1; i < 4; ++i)
	{
		dNewXmax = (geo_x_des[i] > dNewXmax) ? geo_x_des[i] : dNewXmax;
		dNewXmin = (geo_x_des[i] < dNewXmin) ? geo_x_des[i] : dNewXmin;
		dNewYmax = (geo_y_des[i] > dNewYmax) ? geo_y_des[i] : dNewYmax;
		dNewYmin = (geo_y_des[i] < dNewYmin) ? geo_y_des[i] : dNewYmin;
	}

	lNewWidth = (long)((dNewXmax - dNewXmin)/dPixelX);
	lNewHeight = (long)((dNewYmax - dNewYmin)/dPixelY);

	IPointPtr								ipPointOrient(CLSID_Point);
	ipPointOrient->PutCoords(dNewXmin, dNewYmin);

	//文件格式解析
	string						strFormat;
	string						strExent;

	int iPos = strName.rfind('.');
	if (iPos == -1)
	{
		return S_FALSE;
	}

	strExent = strName.substr(iPos + 1);

 	if (strExent == _T("img") || strExent == _T("IMG"))
 	{
 		strFormat = _T("IMAGINE Image");
 	}
 	else if (strExent == _T("tif") || strExent == _T("TIF"))
 	{
		strFormat = _T("TIFF");	
	}
	else
	{
		strFormat = _T("TIFF");
	}

	hr = ipRasterWS->CreateRasterDataset(_bstr_t(strName.c_str()), _bstr_t(strFormat.c_str()), ipPointOrient, lNewWidth, lNewHeight, dPixelX, dPixelY, lBandCount, pixelType, ipSpatialSrc, VARIANT_TRUE, &ipRasterDs);
	if (FAILED(hr))
	{
		sprintf(szLog, _T("创建本地栅格文件失败,返回错误码:%ld"), (long)hr);
		LOGSTR(szLog);
		return S_FALSE;
	}

	//写数据
	VARTYPE						varType;
	long			lNewNodataValue(255);
	SAFEARRAY			*pArray = varNoDataValue.parray;
	switch (pixelType)
	{
	case PT_UCHAR:
		
		for (long ii = 0; ii < lBandCount; ++ii)
		{
			SafeArrayGetElement(pArray, &ii, (void*)&lNewNodataValue);
			if (lNewNodataValue == 256)
			{
				lNewNodataValue-=1;
				SafeArrayPutElement(pArray, &ii, (void*)&lNewNodataValue);
			}
		}
		varType = VT_UI1;
		break;

	case PT_USHORT:
		
		for (long ii = 0; ii < lBandCount; ++ii)
		{
			SafeArrayGetElement(pArray, &ii, (void*)&lNewNodataValue);
			if (lNewNodataValue == 65536)
			{
				lNewNodataValue-=1;
				SafeArrayPutElement(pArray, &ii, (void*)&lNewNodataValue);
			}	
		}
		varType = VT_UI2;
		break;

	default:
		varType = VT_UI4;
		break;
	}

	STR_RASTERPARAM		para;
	para.dPixelX = dPixelX;
	para.dPixelY = dPixelY;
	para.dPixelXDes = dPixelX;
	para.dPixelYDes = dPixelY;
	para.dXminSrc = dXminSrc;
	para.dYmaxSrc = dYmaxSrc;
	para.dXminDes = dNewXmin;
	para.dYmaxDes = dNewYmax;
	para.lBandCount = lBandCount;
	para.type = varType;
	para.lWidthSrc = lWidth;
	para.lHeighSrc = lHeight;
	para.lWidthDes = lNewWidth;
	para.lHeighDes = lNewHeight;

	para.envSrc.dXmin = dXminSrc;
	para.envSrc.dYmin = dYminSrc;
	para.envSrc.dXmax = dXmaxSrc;
	para.envSrc.dYmax = dYmaxSrc;

	para.envDes.dXmin = dNewXmin;
	para.envDes.dYmin = dNewYmin;
	para.envDes.dXmax = dNewXmax;
	para.envDes.dYmax = dNewYmax;
	para.lNoValue = varNoDataValue;

	IRasterDataset2Ptr							ipRasterDS2(ipRasterDs);
	IRasterPtr									ipRasterDes;
	ipRasterDS2->CreateFullRaster(&ipRasterDes);

	switch (m_DeuRasterTrans.m_Resampling)
	{
	case RESAMPLING_NEAREST:
	case RESAMPLING_BILINEAR:
	case RESAMPLING_BICUBIC:

		//是否分块处理add by chenyong 2013-10-21
		if (lNewWidth > 5000 || lNewHeight > 5000)
		{
			hr = TransRasterByNearestBlock(ipRaster, ipRasterDes, para);
		}
		else
		{
			hr = TransRasterByNearest(ipRaster, ipRasterDes, para);
		}

		if (FAILED(hr))
		{
			return S_FALSE;  
		}

		break;

		// 	case RESAMPLING_BILINEAR:
		// 
		// 		break;
		// 
		// 	case RESAMPLING_BICUBIC:
		// 
		// 		break;

	default:

		break;

	}

	return S_OK;
}

//投影 add by chenyong 2013-11-26
HRESULT CArcSDERaster::ProjectRasterDTType(STR_SDEINFO sdeInfo)
{
	LOGSTR(":CoordProjectRasterTransSDE");
	_bstr_t _bstr_filename = (sdeInfo.strName).c_str();
	LOGSTR((LPSTR)_bstr_filename);
	LOG_START;
	START_TIME;

	IWorkspaceEditPtr			ipWorkspaceEdit = m_WorkspaceDes;
	HRESULT						hr = S_OK;
	VARIANT_BOOL				variantEdit = VARIANT_FALSE;
	switch (sdeInfo.Type)
	{
	case deuRasterBand:			

		break;

	case deuRasterDataset:					

		//ProjectRasterDataset(sdeInfo.strName);
		hr = ProjectRasterByLocal(sdeInfo.strName);
		if (hr == S_FALSE)
		{
			ipWorkspaceEdit->IsBeingEdited(&variantEdit);
			if (variantEdit)
			{
				ipWorkspaceEdit->StopEditOperation();
				ipWorkspaceEdit->StopEditing(VARIANT_FALSE);
			}	
		}

		break;

	case deuRasterCatalog:

		hr = ProjectRasterCatalog(sdeInfo.strName);
		if (hr == S_FALSE)
		{
			ipWorkspaceEdit->IsBeingEdited(&variantEdit);
			if (variantEdit)
			{
				ipWorkspaceEdit->StopEditOperation();
				ipWorkspaceEdit->StopEditing(VARIANT_FALSE);
			}
		}

	default:

		break;
	}

	END_TIME;
	LOG_USED_TIME;
	LOG_END;
	LOGSTR("=====================================================================");

	return hr;
}

HRESULT CArcSDERaster::ProjectRasterDataset(const std::string &strDatasetName)
{
	IRasterWorkspaceExPtr				ipRasterWS = m_WorkspaceSrc;
	IRasterWorkspaceExPtr				ipRasterWS_Des = m_WorkspaceDes;
	IRasterDatasetPtr					ipRasterDS;
	IRasterDatasetPtr					ipRasterDS_Des;
	IRasterPtr							ipRasterSr;
	IRasterPtr							ipRasterDes;
	IRasterPropsPtr						ipRasterProSrc;
	IRasterPropsPtr						ipRasterProDes;
	IEnvelopePtr						ipEnvelopeSrc;

	double								dXmin = 0;
	double								dYmin = 0;
	double								dXmax = 0;
	double								dYmax = 0;
	double								dXPixel = 0;
	double								dYPixel = 0;

	double								dXPixelDes = 0;
	double								dYPixelDes = 0;

	long								lHeightSrc = 0;
	long								lWidthSrc = 0;

	rstPixelType						rstPixTypeSrc = PT_UNKNOWN;
	IPntPtr								ipPnt = NULL;
	HRESULT								Hr;
	VARIANT								varNoDataValue;
	varNoDataValue.vt = VT_R4;


	IWorkspaceEditPtr					ipWorkspaceEdit = m_WorkspaceDes;

	CDeuCoordType						coordType;
	short							coordSrcType;
	short							coordDesType;
	char							szLog[128] = {0};

	sprintf(szLog, _T("开始投影转换栅格数据集%s"), strDatasetName.c_str());
	LOGSTR(szLog);

	m_DeuRasterTrans.get_DeuCoordType(coordType);

	coordType.get_CoordType(coordSrcType);
	coordType.get_DestCoordType(coordDesType);

	if (coordSrcType == coordDesType)
	{
		AfxMessageBox(_T("坐标类型相同无需投影!"));
		return S_FALSE;
	}

	ipWorkspaceEdit->StartEditing(VARIANT_TRUE);
	ipWorkspaceEdit->StartEditOperation();

	Hr = ipRasterWS->OpenRasterDataset(_bstr_t(strDatasetName.c_str()), &ipRasterDS);
	if (FAILED(Hr))
	{
		sprintf(szLog, _T("打开栅格数据集%s失败,返回错误码:%ld"), strDatasetName.c_str(), (long)Hr);
		LOGSTR(szLog);
		return S_FALSE;
	}

	IRasterDataset2Ptr					ipRasterDS2_Src(ipRasterDS);
	ipRasterDS2_Src->CreateFullRaster(&ipRasterSr);
	ipRasterProSrc = ipRasterSr;

	ipRasterProSrc->get_Extent(&ipEnvelopeSrc);

	//获取源影像坐标范围
	ipEnvelopeSrc->get_XMin(&dXmin);
	ipEnvelopeSrc->get_XMax(&dXmax);
	ipEnvelopeSrc->get_YMin(&dYmin);
	ipEnvelopeSrc->get_YMax(&dYmax);

	//像素类型及长宽像素个数
	ipRasterProSrc->get_PixelType(&rstPixTypeSrc);
	ipRasterProSrc->MeanCellSize(&ipPnt);
	ipRasterProSrc->get_Height(&lHeightSrc);
	ipRasterProSrc->get_Width(&lWidthSrc);
	ipRasterProSrc->get_NoDataValue(&varNoDataValue);	

	//分辨率
	ipPnt->get_X(&dXPixel);
	ipPnt->get_Y(&dYPixel);

	//获取波段数
	IRasterBandCollectionPtr			ipRasterBandColSrc(ipRasterSr);
	long								lBandCount = 0;

	ipRasterBandColSrc->get_Count(&lBandCount);

	

	//计算目标栅格数据集的
	double			geo_x_src[4] = {0};
	double			geo_y_src[4] = {0};
	double			geo_x_des[4] = {0};
	double			geo_y_des[4] = {0};

	geo_x_src[0] = geo_x_src[1] = dXmin;
	geo_x_src[2] = geo_x_src[3] = dXmax;
	geo_y_src[0] = geo_y_src[3] = dYmin;
	geo_y_src[1] = geo_y_src[2] = dYmax;


	m_DeuRasterTrans._coord_transf(m_DeuRasterTrans.m_Para, m_DeuRasterTrans.m_TransModel, 4, geo_y_src, geo_x_src, 0, geo_y_des, geo_x_des, 0);

	//计算新栅格数据集的范围
	double		dNewXmin(0);
	double		dNewXmax(0);
	double		dNewYmin(0);
	double		dNewYmax(0);

	dNewXmin = dNewXmax = geo_x_des[0];
	dNewYmin = dNewYmax = geo_y_des[0];

	for (int i = 1; i < 4; ++i)
	{
		dNewXmax = (geo_x_des[i] > dNewXmax) ? geo_x_des[i] : dNewXmax;
		dNewXmin = (geo_x_des[i] < dNewXmin) ? geo_x_des[i] : dNewXmin;
		dNewYmax = (geo_y_des[i] > dNewYmax) ? geo_y_des[i] : dNewYmax;
		dNewYmin = (geo_y_des[i] < dNewYmin) ? geo_y_des[i] : dNewYmin;
	}

	IEnvelopePtr						ipEnvelopeDes(CLSID_Envelope);
	ipEnvelopeDes->PutCoords(dNewXmin, dNewYmin, dNewXmax, dNewYmax);

	//计算目标栅格分辨率
	long		lX = lWidthSrc;			//Width
	long		lY = lHeightSrc;		//Height

	dXPixelDes = (dNewXmax - dNewXmin) / lX;
	dYPixelDes = (dNewYmax - dNewYmin) / lY;

	dXPixelDes = sqrt(abs(dXPixelDes)*abs(dYPixelDes));
	dYPixelDes = dXPixelDes;

	//目标栅格分辨率
	ipPnt->put_X(dXPixelDes);
	ipPnt->put_Y(dYPixelDes);

	//设置nodatavalue add by chenyong 2013-11-12 临时处理
	long			lNewNodataValue(255);
	SAFEARRAY			*pArray = varNoDataValue.parray;

	for (long ii = 0; ii < lBandCount; ++ii)
	{
		SafeArrayGetElement(pArray, &ii, (void*)&lNewNodataValue);
		lNewNodataValue -=1;
		SafeArrayPutElement(pArray, &ii, (void*)&lNewNodataValue);
	}

	IRasterStorageDefPtr				ipRasterStoDef(CLSID_RasterStorageDef);
	ipRasterStoDef->putref_CellSize(ipPnt);

	IRasterDefPtr						ipRasterDef(CLSID_RasterDef);


	//创建新栅格数据集
	Hr = ipRasterWS_Des->CreateRasterDataset(_bstr_t(strDatasetName.c_str()), lBandCount, rstPixTypeSrc, ipRasterStoDef, _bstr_t(""), ipRasterDef, NULL, &ipRasterDS_Des);
	if (FAILED(Hr))
	{
		sprintf(szLog, _T("创建栅格数据集%s失败,返回错误码:%ld"), strDatasetName.c_str(), (long)Hr);
		LOGSTR(szLog);
		return S_FALSE;
	}

	//空间参考系 add by chenyong 2013-10-15
	AlterSpatialReference(m_strPrjFullPath, ipRasterDS_Des);

	IRasterDataset2Ptr					ipRasterDS2_Des(ipRasterDS_Des);
	ipRasterDS2_Des->CreateFullRaster(&ipRasterDes);

	//新栅格数据集的属性信息
	ipRasterProDes = ipRasterDes;
	Hr = ipRasterProDes->put_NoDataValue(varNoDataValue);
	ipRasterProDes->put_Height(lY);
	ipRasterProDes->put_Width(lX);
	ipRasterProDes->put_Extent(ipEnvelopeDes);


	//add by chenyong 2013-10-16
	VARTYPE						varType;
	switch (rstPixTypeSrc)
	{

	case PT_UCHAR:
		varType = VT_UI1;
		break;

	case PT_USHORT:
		varType = VT_UI2;
		break;

	default:
		varType = VT_UI4;
		break;

	}


	STR_RASTERPARAM				para;
	para.dPixelX = dXPixel;
	para.dPixelY = dYPixel;
	para.dPixelXDes = dXPixelDes;
	para.dPixelYDes = dYPixelDes;
	para.dXminSrc = dXmin;
	para.dYmaxSrc = dYmax;
	para.dXminDes = dNewXmin;
	para.dYmaxDes = dNewYmax;
	para.lBandCount = lBandCount;
	para.type = varType;
	para.lWidthSrc = lWidthSrc;
	para.lHeighSrc = lHeightSrc;
	para.lWidthDes = lX;
	para.lHeighDes = lY;

	para.envSrc.dXmin = dXmin;
	para.envSrc.dYmin = dYmin;
	para.envSrc.dXmax = dXmax;
	para.envSrc.dYmax = dYmax;

	para.envDes.dXmin = dNewXmin;
	para.envDes.dYmin = dNewYmin;
	para.envDes.dXmax = dNewXmax;
	para.envDes.dYmax = dNewYmax;
	para.lNoValue = varNoDataValue;

	//采样
	switch (m_DeuRasterTrans.m_Resampling)
	{
	case RESAMPLING_NEAREST:
	case RESAMPLING_BILINEAR:
	case RESAMPLING_BICUBIC:

		//是否分块处理add by chenyong 2013-10-21
		if (lX > 5000 || lY > 5000)
		{
			Hr = TransRasterByNearestBlock(ipRasterSr, ipRasterDes, para);
		}
		else
		{
			Hr = TransRasterByNearest(ipRasterSr, ipRasterDes, para);
		}

		break;

		// 	case RESAMPLING_BILINEAR:
		// 
		// 		break;
		// 
		// 	case RESAMPLING_BICUBIC:
		// 
		// 		break;

	default:

		break;
	}


	//计算统计 add by chenyong 2013-10-14
	IRasterBandCollectionPtr								ipRasterBandCol(ipRasterDes);

	CaComputeStatsAndHist(ipRasterBandCol);


	ipWorkspaceEdit->StopEditOperation();
	ipWorkspaceEdit->StopEditing(VARIANT_TRUE);

	sprintf(szLog, _T("完成投影转换栅格数据集%s"), strDatasetName.c_str());
	LOGSTR(szLog);

	return S_OK;
}

HRESULT CArcSDERaster::ProjectRasterCatalog(const std::string &strCatalogName)
{
	IRasterWorkspaceExPtr						ipRasterWS_Src = m_WorkspaceSrc;
	IRasterWorkspaceExPtr						ipRasterWS_Des = m_WorkspaceDes;
	IRasterCatalogPtr							ipRasterCatalog_Src;
	IRasterCatalogPtr							ipRasterCatalog_Des;
	HRESULT										hr;

	//需要处理下：
	IWorkspaceEditPtr							ipWorkspaceEdit = m_WorkspaceDes;
	char										szLog[128] = {0};

	GDALAllRegister();

	IWorkspaceEdit2Ptr								ipWorkspaceEdit2 = ipWorkspaceEdit;
	VARIANT_BOOL									IsActive = VARIANT_FALSE;

	ipWorkspaceEdit2->get_IsInEditOperation(&IsActive);
	if (IsActive == VARIANT_TRUE)
	{
		AfxMessageBox(_T("数据正在被另外一个会话进程编辑....."));
		return S_FALSE;
	}


	//检查是否存在相同名字的数据 add by chenyong 2014-2-11
	IWorkspace2Ptr					ipWorkspace2 = m_WorkspaceDes;
	VARIANT_BOOL					varExist = VARIANT_FALSE;
	
	ipWorkspace2->get_NameExists(esriDTRasterCatalog, _bstr_t(strCatalogName.c_str()), &varExist);
	if (varExist)
	{
		sprintf(szLog, _T("目标库中存在栅格目录%s"), strCatalogName.c_str());
		LOGSTR(szLog);
		return S_FALSE;
	}

	sprintf(szLog, _T("开始投影转换栅格目录%s"), strCatalogName.c_str());
	LOGSTR(szLog);

	hr = ipRasterWS_Src->OpenRasterCatalog(_bstr_t(strCatalogName.c_str()), &ipRasterCatalog_Src);
	if (FAILED(hr))
	{
		sprintf(szLog, _T("打开栅格目录%s失败,返回错误码:%ld"), strCatalogName.c_str(), (long)hr);
		LOGSTR(szLog);
		return S_FALSE;
	}

	ITablePtr									iptable_Src(ipRasterCatalog_Src);
	IFieldsPtr									ipFields;
	long										lIndex(0);
	long										lRows(0);

	iptable_Src->get_Fields(&ipFields);
	ipFields->FindField(_bstr_t("NAME"), &lIndex);
	iptable_Src->RowCount(NULL, &lRows);

	BSTR										strShapeName;
	BSTR										strRasterName;

	IFeatureClassPtr							ipFeatureCls = ipRasterCatalog_Src;

	ipFeatureCls->get_ShapeFieldName(&strShapeName);
	ipRasterCatalog_Src->get_RasterFieldName(&strRasterName);

	ipWorkspaceEdit->StartEditing(VARIANT_TRUE);
	ipWorkspaceEdit->StartEditOperation();

	hr = ipRasterWS_Des->CreateRasterCatalog(_bstr_t(strCatalogName.c_str()), ipFields, strShapeName, strRasterName, _bstr_t(""), &ipRasterCatalog_Des);
	if (FAILED(hr))
	{
		sprintf(szLog, _T("创建栅格目录%s失败,返回错误码:%ld"), strCatalogName.c_str(), (long)hr);
		LOGSTR(szLog);
		return S_FALSE;
	}

	//创建RasterWorkFactory
	IWorkspaceFactoryPtr						ipWorkSF(CLSID_RasterWorkspaceFactory);
	IWorkspacePtr								ipWorks_local;

	//特定目录
	CString strExcutePath = GetStylesPath();
	string										strSpecDir = string(strExcutePath + _T("\\SDE"));

	if (IsExistDir(strSpecDir))
	{
		//DeleteAllFile(strSpecDir);
	}
	else
	{
		CreateDir(strSpecDir);
	}

	hr = ipWorkSF->OpenFromFile(_bstr_t(strSpecDir.c_str()), NULL, &ipWorks_local);

	IRasterWorkspace2Ptr						ipRasterWS2(ipWorks_local);

	//遍历源RasterCatalog
	esriIRowPtr									ipRow;
	IRowBufferPtr								ipRowBuffer;
	IRasterCatalogItemPtr						ipRasterCatalogItem;
	VARIANT										varName;
	IRasterDatasetPtr							ipRasterDS;
	IRasterDataset2Ptr							ipRasterDS2;
	IRasterPtr									ipRaster;
	string										strFullPath;
	GDALDataset									*pDS = NULL;
	GDALRasterBand								*pBand = NULL;
	int			bApproxOK = 0;
	double		pdfMin = 0;
	double		pdfMax = 0;
	double		pdfMean = 0;
	double		pdfStdDev = 0;
	void* pProgressData = NULL;

	IRasterPropsPtr			ipProps;
	long					lBands = 0;
	VARIANT					var;
	var.vt = VT_R4;

	IRasterBandCollectionPtr		ipRasterBandCol;
	SAFEARRAY*						pArray = NULL;
	long							fValue = 0;
	long							lNodataValue = 0;

  	for (int i = 1; i <= lRows; ++i)
  	{
  		iptable_Src->GetRow(i, &ipRow);
 		if (NULL == ipRow)
 		{
 			continue;	
 		}
 
  		ipRowBuffer = ipRow;
  
  		ipRowBuffer->get_Value(lIndex, &varName);
  		ipRasterCatalogItem = ipRow;
  		ipRasterCatalogItem->get_RasterDataset(&ipRasterDS);
  		ipRasterDS2 = ipRasterDS;
  		ipRasterDS2->CreateFullRaster(&ipRaster);
  
  		CreateLocalProjectRasterDataset( _com_util::ConvertBSTRToString(varName.bstrVal), ipRasterWS2, ipRaster);
  
  		//用GDAL处理nodatavalue
  		strFullPath = strSpecDir + _T("\\") + _com_util::ConvertBSTRToString(varName.bstrVal);
  
  		pDS = (GDALDataset*)GDALOpen(strFullPath.c_str(), GA_Update);
  		if (NULL == pDS)
  		{
  			continue;
  		}
  
  		ipProps = ipRaster;
  		ipProps->get_NoDataValue(&var);
  		rstPixelType rstPixTypeSrc;
  		ipProps->get_PixelType(&rstPixTypeSrc);
  		pArray = var.parray;
  		ipRasterBandCol = ipRaster;
  		ipRasterBandCol->get_Count(&lBands);
  
  		for (long Band = 0; Band < lBands; ++Band)
  		{
  			::SafeArrayGetElement(pArray, &Band, &fValue);
  			switch(rstPixTypeSrc)
  			{
  			case PT_UCHAR:
  				if (fValue == 256)
  				{
  					lNodataValue = fValue -1;
  				}
  				else
  				{
  					lNodataValue = fValue;
  				}
  
  				pBand = pDS->GetRasterBand(Band+1);
  				GDALSetRasterNoDataValue(pBand, lNodataValue);
  				pBand->ComputeStatistics(bApproxOK, &pdfMin, &pdfMax, &pdfMean, &pdfStdDev, _ProgressFunc, pProgressData);
  
  				break;
  
  			case PT_USHORT:
  				if (fValue == 65536)
  				{
  					lNodataValue = fValue -1;
  				}
  				else
  				{
  					lNodataValue = fValue;
  				}
  
  				pBand = pDS->GetRasterBand(Band+1);
  				GDALSetRasterNoDataValue(pBand, lNodataValue);
  				pBand->ComputeStatistics(bApproxOK, &pdfMin, &pdfMax, &pdfMean, &pdfStdDev, _ProgressFunc, pProgressData);
  
  
  				break;
  			default:
  				break; 
  			}
  		}
  
  		GDALClose((GDALDatasetH)pDS);
  	}

	//add by chenyong 2014-3-7
	HANDLE hWait = ::CreateThread(NULL, 0, ThreadLoadWait, m_hWnd, 0, NULL);


// 	ipWorkspaceEdit->StartEditing(VARIANT_TRUE);
// 	ipWorkspaceEdit->StartEditOperation();

	ITrackCancelPtr								ipTrackCancel(CLSID_CancelTracker);
	IRasterCatalogLoaderPtr						ipRasterCatalogLoader(CLSID_RasterCatalogLoader);	

	ipRasterCatalogLoader->putref_Workspace(m_WorkspaceDes);
	hr = ipRasterCatalogLoader->Load(_bstr_t(strCatalogName.c_str()), _bstr_t(strSpecDir.c_str()), ipTrackCancel);
	if (FAILED(hr))
	{
		::TerminateThread(hWait, 0);
		sprintf(szLog, _T("上传栅格数据集失败,返回错误码:%ld"), (long)hr);
		LOGSTR(szLog);
		return S_FALSE;
	}

	::TerminateThread(hWait, 0);
	

	//计算统计
	iptable_Src = ipRasterCatalog_Des;

	IRasterBandCollectionPtr			ipRasterBandCol2;
	for (int k = 1; k <= lRows; ++k )
	{
		hr = iptable_Src->GetRow(k, &ipRow);
		if (FAILED(hr))
		{
			continue;
		}

		ipRasterCatalogItem = ipRow;
		ipRasterCatalogItem->get_RasterDataset(&ipRasterDS);
		ipRasterDS2 = ipRasterDS;
		ipRasterDS2->CreateFullRaster(&ipRaster);

		ipRasterBandCol2 = ipRaster;

		CaComputeStatsAndHist(ipRasterBandCol2);
	}

	//

	ipWorkspaceEdit->StopEditOperation();
	ipWorkspaceEdit->StopEditing(VARIANT_TRUE);

	sprintf(szLog, _T("完成投影转换栅格目录%s"), strCatalogName.c_str());
	LOGSTR(szLog);

	return S_OK;
}

HRESULT CArcSDERaster::CreateLocalProjectRasterDataset(const string& strName, IRasterWorkspace2Ptr ipRasterWS, IRasterPtr ipRaster)
{
	IRasterPropsPtr							ipRasterProps(ipRaster);
	IEnvelopePtr							ipEnvelope;
	long									lHeight(0);
	long									lWidth(0);
	rstPixelType							pixelType = PT_UNKNOWN;
	double									dPixelX(0);
	double									dPixelY(0);

	double									dPixelXDes(0);
	double									dPixelYDes(0);
	VARIANT									varNoDataValue;
	IPntPtr									ipMeanCellSize;
	HRESULT									hr;
	char									szLog[128] = {0};
	
	sprintf(szLog, _T("创建本地投影栅格数据集%s"), strName.c_str());
	LOGSTR(szLog);

	varNoDataValue.vt = VT_R4;

	ipRasterProps->get_Extent(&ipEnvelope);
	ipRasterProps->get_Height(&lHeight);
	ipRasterProps->get_Width(&lWidth);
	ipRasterProps->get_PixelType(&pixelType);
	ipRasterProps->get_NoDataValue(&varNoDataValue);
	ipRasterProps->MeanCellSize(&ipMeanCellSize);

	ipMeanCellSize->get_X(&dPixelX);
	ipMeanCellSize->get_Y(&dPixelY);

	//add by chenyong 2014-1-23
	CDeuCoordType				CoorType;
	m_DeuRasterTrans.get_DeuCoordType(CoorType);

	short						typeSrc;
	short						typeDes;

	CoorType.get_CoordType(typeSrc);
	CoorType.get_DestCoordType(typeDes);


	//1.空间参考系
	ISpatialReferenceFactoryPtr							ipSpatialFac(CLSID_SpatialReferenceEnvironment);
	ISpatialReferencePtr								ipSpatialSrc;

	hr = ipSpatialFac->CreateESRISpatialReferenceFromPRJFile(_bstr_t(m_strPrjFullPath.c_str()), &ipSpatialSrc);
	if (FAILED(hr))
	{
		sprintf(szLog, _T("创建空间坐标系失败,返回错误码:%ld"), (long)hr);
		LOGSTR(szLog);
		
		return S_FALSE;
	}
	long									lBandCount(0);
	IRasterBandCollectionPtr				ipRasterBandCol(ipRaster);
	long									lNewWidth = lWidth;
	long									lNewHeight = lHeight;
	IRasterDatasetPtr						ipRasterDs;
	ipRasterBandCol->get_Count(&lBandCount);

	//需要计算目标文件坐标范围
	double									dXminSrc(0);
	double									dYminSrc(0);
	double									dXmaxSrc(0);
	double									dYmaxSrc(0);

	ipEnvelope->get_XMin(&dXminSrc);
	ipEnvelope->get_YMin(&dYminSrc);
	ipEnvelope->get_XMax(&dXmaxSrc);
	ipEnvelope->get_YMax(&dYmaxSrc);

	//add by chenyong 2014-2-8
	double			dYStart = dYmaxSrc;
	double			dXStart = dXminSrc;

	double			dXEnd = dXStart + lWidth*dPixelX;
	double			dYEnd = dYStart - lHeight*dPixelY;



 	double									geo_x_src[4] = {0};
 	double									geo_y_src[4] = {0};
 	double									geo_x_des[4] = {0};
 	double									geo_y_des[4] = {0};
// 
// 	geo_x_src[0] = geo_x_src[1] = dXminSrc;
// 	geo_x_src[2] = geo_x_src[3] = dXmaxSrc;
// 	geo_y_src[0] = geo_y_src[3] = dYminSrc;
// 	geo_y_src[1] = geo_y_src[2] = dYmaxSrc;
// 
// 	m_DeuRasterTrans._coord_transf(m_DeuRasterTrans.m_Para, m_DeuRasterTrans.m_TransModel, 4, geo_y_src, geo_x_src, 0, geo_y_des, geo_x_des, 0);
// 
 	//计算新栅格数据集的范围
 	double									dNewXmin(0);
 	double									dNewXmax(0);
 	double									dNewYmin(0);
 	double									dNewYmax(0);
// 
// 	dNewYmin = dNewYmax = geo_y_des[0];
// 	dNewXmin = dNewXmax = geo_x_des[0];

	if (typeSrc == typeDes)
	{
		LOGSTR("坐标系类型相同不能进行投影");
		return S_FALSE;
	}
	else if ((__COORDTYPE)typeSrc == GEODETIC && (__COORDTYPE)typeDes == PLANE)//正投影
	{
		geo_x_src[0] = geo_x_src[2] = dXStart;
		geo_x_src[1] = geo_x_src[3] = dXEnd;
		geo_y_src[0] = geo_y_src[1] = dYStart;
		geo_y_src[2] = geo_y_src[3] = dYEnd;

		m_DeuRasterTrans._coord_transf(m_DeuRasterTrans.m_Para, m_DeuRasterTrans.m_TransModel, 4, geo_y_src, geo_x_src, 0, geo_y_des, geo_x_des, 0);

		dNewYmin = dNewYmax = geo_y_des[0];
		dNewXmin = dNewXmax = geo_x_des[0];

		//add by chenyong 2014-1-13
		for (int i = 1; i < 4; ++i)
		{
			dNewXmax = (geo_x_des[i] > dNewXmax) ? geo_x_des[i] : dNewXmax;
			dNewXmin = (geo_x_des[i] < dNewXmin) ? geo_x_des[i] : dNewXmin;
			dNewYmax = (geo_y_des[i] > dNewYmax) ? geo_y_des[i] : dNewYmax;
			dNewYmin = (geo_y_des[i] < dNewYmin) ? geo_y_des[i] : dNewYmin;
		}

		dPixelXDes = (dNewXmax - dNewXmin)/lWidth;
		dPixelYDes = (dNewYmax - dNewYmin)/lHeight;

		dPixelXDes = sqrt(abs(dPixelXDes)*abs(dPixelYDes));
		dPixelYDes = dPixelXDes;

		lNewHeight = abs(dNewYmax - dNewYmin)/dPixelXDes;
		lNewWidth = abs(dNewXmax - dNewXmin)/dPixelYDes;

	}
	else if ((__COORDTYPE)typeSrc == PLANE && (__COORDTYPE)typeDes == GEODETIC)//反投影
	{

		//double			dXEnd = dXStart + lWidth*dPixelX;
		//double			dYEnd = dYStart - lHeight*dPixelY;

		geo_x_src[0] = dXStart;
		geo_x_src[1] = dXEnd;
		geo_y_src[0] = dYStart;
		geo_y_src[1] = dYEnd;


		m_DeuRasterTrans._coord_transf(m_DeuRasterTrans.m_Para, m_DeuRasterTrans.m_TransModel, 2, geo_y_src, geo_x_src, 0, geo_y_des, geo_x_des, 0);
		
		dPixelXDes = (geo_y_des[1] - geo_y_des[0])/lWidth;
		dPixelYDes = (geo_x_des[0] - geo_x_des[1])/lHeight;

		//
		dPixelXDes = sqrt(abs(dPixelXDes)*abs(dPixelYDes));
		dPixelYDes = dPixelXDes;

		//add by chenyong 2014-2-8
		geo_x_src[0] = geo_x_src[2] = dXStart;
		geo_x_src[1] = geo_x_src[3] = dXEnd;
		geo_y_src[0] = geo_y_src[1] = dYStart;
		geo_y_src[2] = geo_y_src[3] = dYEnd;

		m_DeuRasterTrans._coord_transf(m_DeuRasterTrans.m_Para, m_DeuRasterTrans.m_TransModel, 4, geo_y_src, geo_x_src, 0, geo_y_des, geo_x_des, 0);

		dNewYmin = dNewYmax = geo_y_des[0];
		dNewXmin = dNewXmax = geo_x_des[0];

		//add by chenyong 2014-1-13
		for (int i = 1; i < 4; ++i)
		{
			dNewXmax = (geo_x_des[i] > dNewXmax) ? geo_x_des[i] : dNewXmax;
			dNewXmin = (geo_x_des[i] < dNewXmin) ? geo_x_des[i] : dNewXmin;
			dNewYmax = (geo_y_des[i] > dNewYmax) ? geo_y_des[i] : dNewYmax;
			dNewYmin = (geo_y_des[i] < dNewYmin) ? geo_y_des[i] : dNewYmin;
		}

		lNewHeight = abs(dNewYmax - dNewYmin)/dPixelXDes;
		lNewWidth = abs(dNewXmax - dNewXmin)/dPixelYDes;
		//

	}

// 	dPixelXDes = sqrt(abs(dPixelXDes)*abs(dPixelYDes));
// 	dPixelYDes = dPixelXDes;
// 
// 	//add by chenyong 2014-2-8
// 	geo_x_src[0] = geo_x_src[2] = dXStart;
// 	geo_x_src[1] = geo_x_src[3] = dXEnd;
// 	geo_y_src[0] = geo_y_src[1] = dYStart;
// 	geo_y_src[2] = geo_y_src[3] = dYEnd;
// 
// 	m_DeuRasterTrans._coord_transf(m_DeuRasterTrans.m_Para, m_DeuRasterTrans.m_TransModel, 4, geo_y_src, geo_x_src, 0, geo_y_des, geo_x_des, 0);
// 
//  	dNewYmin = dNewYmax = geo_y_des[0];
//  	dNewXmin = dNewXmax = geo_x_des[0];
// 
// 	//add by chenyong 2014-1-13
//  	for (int i = 1; i < 4; ++i)
//  	{
//  		dNewXmax = (geo_x_des[i] > dNewXmax) ? geo_x_des[i] : dNewXmax;
//  		dNewXmin = (geo_x_des[i] < dNewXmin) ? geo_x_des[i] : dNewXmin;
//  		dNewYmax = (geo_y_des[i] > dNewYmax) ? geo_y_des[i] : dNewYmax;
//  		dNewYmin = (geo_y_des[i] < dNewYmin) ? geo_y_des[i] : dNewYmin;
//  	}
//  
//  	lNewHeight = abs(dNewYmax - dNewYmin)/dPixelXDes;
//  	lNewWidth = abs(dNewXmax - dNewXmin)/dPixelYDes;
//  
 	IPointPtr								ipPointOrient(CLSID_Point);
	ipPointOrient->PutCoords(dNewXmax, dNewYmin);

	//文件格式解析
	string						strFormat;
	string						strExent;

	int iPos = strName.rfind('.');
	if (iPos == -1)
	{
		return S_FALSE;
	}

	strExent = strName.substr(iPos + 1);

	if (strExent == _T("img") || strExent == _T("IMG"))
	{
		strFormat = _T("IMAGINE Image");
	}
	else if (strExent == _T("tif") || strExent == _T("TIF"))
	{
		strFormat = _T("TIFF");	
	}

	hr = ipRasterWS->CreateRasterDataset(_bstr_t(strName.c_str()), _bstr_t(strFormat.c_str()), ipPointOrient, lNewWidth, lNewHeight, dPixelXDes, dPixelYDes, lBandCount, pixelType, ipSpatialSrc, VARIANT_TRUE, &ipRasterDs);
	if (FAILED(hr))
	{
		sprintf(szLog, _T("创建本地投影栅格数据集%s失败，返回错误码:%ld"), strName.c_str(), (long)hr);
		LOGSTR(szLog);

		return S_FALSE;
	}

	//写数据
	VARTYPE						varType;
	long			lNewNodataValue(255);
	SAFEARRAY			*pArray = varNoDataValue.parray;

	switch (pixelType)
	{
	case PT_UCHAR:
		varType = VT_UI1;
		for (long ii = 0; ii < lBandCount; ++ii)
		{
			SafeArrayGetElement(pArray, &ii, (void*)&lNewNodataValue);
			if (lNewNodataValue == 256)
			{
				lNewNodataValue-=1;
				SafeArrayPutElement(pArray, &ii, (void*)&lNewNodataValue);
			}	
		}
		break;

	case PT_USHORT:
		varType = VT_UI2;

		for (long ii = 0; ii < lBandCount; ++ii)
		{
			SafeArrayGetElement(pArray, &ii, (void*)&lNewNodataValue);
			if (lNewNodataValue == 65536)
			{
				lNewNodataValue-=1;
				SafeArrayPutElement(pArray, &ii, (void*)&lNewNodataValue);
			}	
		}

		break;
	default:

		varType = VT_UI4;
		break;
	}

	STR_RASTERPARAM		para;
	para.dPixelX = dPixelX;
	para.dPixelY = dPixelY;
	para.dPixelXDes = dPixelXDes;
	para.dPixelYDes = dPixelYDes;

	para.dXminSrc = dXminSrc;
	para.dYmaxSrc = dYmaxSrc;
	para.dXminDes = dNewXmin;////屏蔽了会出现卡在上传中，将屏蔽解除//
	para.dYmaxDes = dNewYmax;//
	para.lBandCount = lBandCount;
	para.type = varType;
	para.lWidthSrc = lWidth;
	para.lHeighSrc = lHeight;
	para.lWidthDes = lNewWidth;
	para.lHeighDes = lNewHeight;

	para.envSrc.dXmin = dXminSrc;
	para.envSrc.dYmin = dYminSrc;
	para.envSrc.dXmax = dXmaxSrc;
	para.envSrc.dYmax = dYmaxSrc;

	para.envDes.dXmin = dNewXmin;
	para.envDes.dYmin = dNewYmin;
	para.envDes.dXmax = dNewXmax;
	para.envDes.dYmax = dNewYmax;
	para.lNoValue = varNoDataValue;

	IRasterDataset2Ptr							ipRasterDS2(ipRasterDs);
	IRasterPtr									ipRasterDes;
	ipRasterDS2->CreateFullRaster(&ipRasterDes);

	IRasterPropsPtr								ipRasterPropsDes(ipRasterDes);

	switch (m_DeuRasterTrans.m_Resampling)
	{
	case RESAMPLING_NEAREST:
	case RESAMPLING_BILINEAR:
	case RESAMPLING_BICUBIC:

		//是否分块处理add by chenyong 2013-10-21
		if (lNewWidth > 5000 || lNewHeight > 5000)
		{
			hr = TransRasterByNearestBlock(ipRaster, ipRasterDes, para);
		}
		else
		{
			hr = TransRasterByNearest(ipRaster, ipRasterDes, para);
		}

		break;

		// 	case RESAMPLING_BILINEAR:
		// 
		// 		break;
		// 
		// 	case RESAMPLING_BICUBIC:
		// 
		// 		break;

	default:

		break;

	}

	sprintf(szLog, _T("完成本地投影栅格数据集%s"), strName.c_str());
	LOGSTR(szLog);

	return S_OK;
}


//add by chenyong 2014-1-2
HRESULT CArcSDERaster::TransRasterDatasetByLocal(const string& strDatasetName)
{
	/*
		步骤：
		1.在生成本地文件
		2.借助GDAL来修改nodatavalue
		3.上传到ArcSDE库中
	*/

	IRasterWorkspaceExPtr						ipRasterWS_Src = m_WorkspaceSrc;
	IRasterWorkspaceExPtr						ipRasterWS_Des = m_WorkspaceDes;
	IRasterDatasetPtr							ipRasterDataset_Src;
	IRasterDatasetPtr							ipRasterDataset_Des;
	HRESULT										hr;
	const string								strTempFileName = "Temp.tif";
	IWorkspaceEditPtr							ipWorkspaceEdit = m_WorkspaceDes;

	char										szLog[128] = {0};
	sprintf(szLog, _T("开始转换栅格数据集%s"), strDatasetName.c_str());
	LOGSTR(szLog);

	IWorkspaceEdit2Ptr								ipWorkspaceEdit2 = ipWorkspaceEdit;
	VARIANT_BOOL									IsActive = VARIANT_FALSE;

	ipWorkspaceEdit2->get_IsInEditOperation(&IsActive);
	if (IsActive == VARIANT_TRUE)
	{
		AfxMessageBox(_T("数据正在被另外一个会话进程编辑....."));
		return S_FALSE;
	}

	//检查是否存在相同名字的数据 add by chenyong 2014-2-11
	IWorkspace2Ptr					ipWorkspace2 = m_WorkspaceDes;
	VARIANT_BOOL					varExist = VARIANT_FALSE;

	ipWorkspace2->get_NameExists(esriDTRasterDataset, _bstr_t(strDatasetName.c_str()), &varExist);
	if (varExist)
	{
		sprintf(szLog, _T("目标库中存在栅格数据%s"), strDatasetName.c_str());
		LOGSTR(szLog);
		return S_FALSE;
	}


	hr = ipRasterWS_Src->OpenRasterDataset(_bstr_t(strDatasetName.c_str()), &ipRasterDataset_Src);
	if (FAILED(hr))
	{
		sprintf(szLog, _T("打开栅格集%s失败,返回错误码:"), strDatasetName.c_str(), (long)hr);
		LOGSTR(szLog);
		return S_FALSE;
	}

	//创建RasterWorkFactory
	IWorkspaceFactoryPtr						ipWorkSF(CLSID_RasterWorkspaceFactory);
	IWorkspacePtr								ipWorks_local;

	//特定目录
	CString strExcutePath = GetStylesPath();
	string										strSpecDir = string(strExcutePath + _T("\\SDE"));

	if (IsExistDir(strSpecDir))
	{
		DeleteAllFile(strSpecDir);
	}
	else
	{
		CreateDir(strSpecDir);
	}

	hr = ipWorkSF->OpenFromFile(_bstr_t(strSpecDir.c_str()), NULL, &ipWorks_local);
	if (FAILED(hr))
	{
		LOGSTR("打开本地目录失败!");
		return S_FALSE;
	}

	IRasterWorkspace2Ptr						ipRasterWS2(ipWorks_local);

	//VARIANT										varName;
	IRasterDataset2Ptr							ipRasterDS2;
	IRasterPtr									ipRaster;

	ipRasterDS2 = ipRasterDataset_Src;
	ipRasterDS2->CreateFullRaster(&ipRaster);

	CreateLocalRasteDataset(strTempFileName, ipRasterWS2, ipRaster);

	//修改nodatavalue值
	IRasterPropsPtr				ipProps = ipRaster;
	long						lBands = 0;
	VARIANT						var;
	var.vt = VT_R4;

	rstPixelType						rstPixTypeSrc = PT_UNKNOWN;

	ipProps->get_NoDataValue(&var);
	ipProps->get_PixelType(&rstPixTypeSrc);

	IRasterBandCollectionPtr   ipRasterBandCol = ipRaster;
	ipRasterBandCol->get_Count(&lBands);

	SAFEARRAY* pArray = var.parray;
	long				fValue = 0;
	long				lNodataValue = 0;

	//打开本地生成文件
	GDALAllRegister();

	string strFilePath = strSpecDir + _T("\\") + strTempFileName;
	GDALDataset	*pDS = (GDALDataset*)GDALOpen(strFilePath.c_str(), GA_Update);
	GDALRasterBand*	pBand = NULL;

	int bApproxOK = 0;
	double	pdfMin = 0;
	double	pdfMax = 0;
	double	pdfMean = 0;
	double	pdfStdDev = 0;
	void* pProgressData = NULL;

	for (long i = 0; i < lBands; ++i)
	{
		::SafeArrayGetElement(pArray, &i, &fValue);

		switch(rstPixTypeSrc)
		{
		case PT_UCHAR:
			if (fValue == 256)
			{
				lNodataValue = fValue -1;
			}
			else
			{
				lNodataValue = fValue;
			}

			pBand = pDS->GetRasterBand(i+1);
			GDALSetRasterNoDataValue(pBand, lNodataValue);
			pBand->ComputeStatistics(bApproxOK, &pdfMin, &pdfMax, &pdfMean, &pdfStdDev, _ProgressFunc, pProgressData);
			
			break;

		case PT_USHORT:
			if (fValue == 65536)
			{
				lNodataValue = fValue -1;
			}
			else
			{
				lNodataValue = fValue;
			}

			pBand = pDS->GetRasterBand(i+1);
			GDALSetRasterNoDataValue(pBand, lNodataValue);
			pBand->ComputeStatistics(bApproxOK, &pdfMin, &pdfMax, &pdfMean, &pdfStdDev, _ProgressFunc, pProgressData);
			
			break;
		default:
			break; 
		}
}

	GDALClose((GDALDatasetH)pDS);


	ipWorkspaceEdit->StartEditing(VARIANT_TRUE);
	ipWorkspaceEdit->StartEditOperation();

	//创建栅格数据集
	IRasterStorageDefPtr				ipRasterStoDef(CLSID_RasterStorageDef);
	IRasterDefPtr						ipRasterDef(CLSID_RasterDef);
	IRasterDatasetPtr					ipRasterDS_Des;

	//创建新栅格数据集
	hr = ipRasterWS_Des->CreateRasterDataset(_bstr_t(strDatasetName.c_str()), lBands, rstPixTypeSrc, ipRasterStoDef, _bstr_t(""), ipRasterDef, NULL, &ipRasterDS_Des);
	if (FAILED(hr))
	{
		sprintf(szLog, _T("创建栅格数据集%s失败,返回错误码:%ld"), strDatasetName.c_str(), (long)hr);
		LOGSTR(szLog);
		return S_FALSE;
	}

	//空间参考系 add by chenyong 2013-10-15
	AlterSpatialReference(m_strPrjFullPath, ipRasterDS_Des);
	
	IRasterLoaderPtr						ipRasterLoader(CLSID_RasterLoader);

	ipRasterWS2->OpenRasterDataset(_bstr_t(strTempFileName.c_str()), &ipRasterDataset_Src);

	ipRasterDS2 = ipRasterDataset_Src;
	ipRasterDS2->CreateFullRaster(&ipRaster);

	//add by chenyong 2014-3-7
	HANDLE hWait = ::CreateThread(NULL, 0, ThreadLoadWait, m_hWnd, 0, NULL);

	hr = ipRasterLoader->Load(ipRasterDS_Des, ipRaster);
	if (FAILED(hr))
	{
		::TerminateThread(hWait, 0);
		sprintf(szLog, _T("上传栅格数据文件失败"));
		LOGSTR(szLog);
		return S_FALSE;
	}

	::TerminateThread(hWait, 0);
	//end add by chenyong

	//计算统计
	IRasterDataset2Ptr			ipRaster2Des = ipRasterDS_Des;
	IRasterPtr					ipRasterFull;
	ipRaster2Des->CreateFullRaster(&ipRasterFull);

	IRasterBandCollectionPtr								ipRasterBandCol2(ipRasterFull);

	CaComputeStatsAndHist(ipRasterBandCol2);
	//

	ipWorkspaceEdit->StopEditOperation();
	ipWorkspaceEdit->StopEditing(VARIANT_TRUE);

	sprintf(szLog, _T("完成本地栅格数据集创建%s"), strDatasetName.c_str());
	LOGSTR(szLog);
	return S_OK;
}



HRESULT CArcSDERaster::ProjectRasterByLocal(const string& strDatasetName)
{
	IRasterWorkspaceExPtr						ipRasterWS_Src = m_WorkspaceSrc;
	IRasterWorkspaceExPtr						ipRasterWS_Des = m_WorkspaceDes;
	IRasterDatasetPtr							ipRasterDataset_Src;
	HRESULT										hr;

	//需要处理下：
	IWorkspaceEditPtr							ipWorkspaceEdit = m_WorkspaceDes;
	char										szLog[128] = {0};

	IWorkspaceEdit2Ptr								ipWorkspaceEdit2 = ipWorkspaceEdit;
	VARIANT_BOOL									IsActive = VARIANT_FALSE;

	ipWorkspaceEdit2->get_IsInEditOperation(&IsActive);
	if (IsActive == VARIANT_TRUE)
	{
		AfxMessageBox(_T("数据正在被另外一个会话进程编辑....."));
		return S_FALSE;
	}

	//检查是否存在相同名字的数据 add by chenyong 2014-2-11
	IWorkspace2Ptr					ipWorkspace2 = m_WorkspaceDes;
	VARIANT_BOOL					varExist = VARIANT_FALSE;

	ipWorkspace2->get_NameExists(esriDTRasterDataset, _bstr_t(strDatasetName.c_str()), &varExist);
	if (varExist)
	{
		sprintf(szLog, _T("目标库中存在栅格数据%s"), strDatasetName.c_str());
		LOGSTR(szLog);
		return S_FALSE;
	}


	sprintf(szLog, _T("开始投影栅格数据集%s"), strDatasetName.c_str());
	LOGSTR(szLog);



	hr = ipRasterWS_Src->OpenRasterDataset(_bstr_t(strDatasetName.c_str()), &ipRasterDataset_Src);
	if (FAILED(hr))
	{
		sprintf(szLog, _T("打开栅格数据%s失败,返回错误码:%ld"), strDatasetName.c_str(), (long)hr);
		LOGSTR(szLog);
		return S_FALSE;
	}


	//创建RasterWorkFactory
	IWorkspaceFactoryPtr						ipWorkSF(CLSID_RasterWorkspaceFactory);
	IWorkspacePtr								ipWorks_local;

	//特定目录
	CString strExcutePath = GetStylesPath();
	string										strSpecDir = string(strExcutePath + _T("\\SDE"));

	if (IsExistDir(strSpecDir))
	{
		DeleteAllFile(strSpecDir);
	}
	else
	{
		CreateDir(strSpecDir);
	}

	hr = ipWorkSF->OpenFromFile(_bstr_t(strSpecDir.c_str()), NULL, &ipWorks_local);

	IRasterWorkspace2Ptr						ipRasterWS2(ipWorks_local);

	//VARIANT										varName;
	IRasterDatasetPtr							ipRasterDS = ipRasterDataset_Src;
	IRasterDataset2Ptr							ipRasterDS2;
	IRasterPtr									ipRaster;
	string										strTempFileName = "Temp.tif";

	ipRasterDS2 = ipRasterDS;
	ipRasterDS2->CreateFullRaster(&ipRaster);

	CreateLocalProjectRasterDataset(strTempFileName, ipRasterWS2, ipRaster);

	//修改nodatavalue
	IRasterPropsPtr			ipProps = ipRaster;
	long					lBands = 0;
	VARIANT					var;
	var.vt = VT_R4;

	rstPixelType			rstPixTypeSrc = PT_UNKNOWN;

	ipProps->get_NoDataValue(&var);
	ipProps->get_PixelType(&rstPixTypeSrc);

	IRasterBandCollectionPtr			ipRasterBandCol = ipRaster;
	ipRasterBandCol->get_Count(&lBands);

	SAFEARRAY* pArray = var.parray;
	long		fValue = 0;
	long		lNodataValue = 0;

	GDALAllRegister();

	string		strFilePath = strSpecDir + _T("\\") + strTempFileName;
	GDALDataset* pDS = (GDALDataset*)GDALOpen(strFilePath.c_str(), GA_Update);
	if (NULL == pDS)
	{
		sprintf(szLog, _T("打开本地文件失败!"));
		LOGSTR(szLog);
		return S_FALSE;
	}

	GDALRasterBand* pBand = NULL;

	int				bApproxOK = 0;
	double			pdfMin = 0;
	double			pdfMax = 0;
	double			pdfMean = 0;
	double			pdfStdDev = 0;
	void* pProgressData = NULL;

	for (long i = 0; i < lBands; ++i)
	{
		::SafeArrayGetElement(pArray, &i, &fValue);
		
		switch(rstPixTypeSrc)
		{
		case PT_UCHAR:
			if (fValue == 256)
			{
				lNodataValue = fValue -1;
			}
			else
			{
				lNodataValue = fValue;
			}

			pBand = pDS->GetRasterBand(i+1);
			GDALSetRasterNoDataValue(pBand, lNodataValue);
			pBand->ComputeStatistics(bApproxOK, &pdfMin, &pdfMax, &pdfMean, &pdfStdDev, _ProgressFunc, pProgressData);

			break;

		case PT_USHORT:
			if (fValue == 65536)
			{
				lNodataValue = fValue -1;
			}
			else
			{
				lNodataValue = fValue;
			}

			pBand = pDS->GetRasterBand(i+1);
			GDALSetRasterNoDataValue(pBand, lNodataValue);
			pBand->ComputeStatistics(bApproxOK, &pdfMin, &pdfMax, &pdfMean, &pdfStdDev, _ProgressFunc, pProgressData);

			break;

		default:
			break; 
		}
	}

	GDALClose((GDALDatasetH)pDS);

	ipWorkspaceEdit->StartEditing(VARIANT_TRUE);
	ipWorkspaceEdit->StartEditOperation();


	IRasterStorageDefPtr						ipRasterStoDef(CLSID_RasterStorageDef);
	IRasterDefPtr								ipRasterDef(CLSID_RasterDef);
	IRasterDatasetPtr							ipRasterDS_Des;

	hr = ipRasterWS_Des->CreateRasterDataset(_bstr_t(strDatasetName.c_str()), lBands, rstPixTypeSrc, ipRasterStoDef, _bstr_t(""), ipRasterDef, NULL, &ipRasterDS_Des);
	if(FAILED(hr))
	{
		sprintf(szLog, _T("创建栅格数据集%s失败,返回错误码:%ld"), strDatasetName.c_str(), (long)hr);
		LOGSTR(szLog);
		return S_FALSE;
	}

	//空间参考系
	AlterSpatialReference(m_strPrjFullPath, ipRasterDS_Des);

	IRasterLoaderPtr			ipRasterLoader(CLSID_RasterLoader);

	hr = ipRasterWS2->OpenRasterDataset(_bstr_t(strTempFileName.c_str()), &ipRasterDataset_Src);
	if(FAILED(hr))
	{
		sprintf(szLog, _T("打开栅格数据集%s失败,返回错误码:%ld"), strTempFileName.c_str(), (long)hr);
		LOGSTR(szLog);
		return S_FALSE;
	}

	ipRasterDS2 = ipRasterDataset_Src;
	ipRasterDS2->CreateFullRaster(&ipRaster);

	//add by chenyong 2014-3-7
	HANDLE hWait = ::CreateThread(NULL, 0, ThreadLoadWait, m_hWnd, 0, NULL);

	hr = ipRasterLoader->Load(ipRasterDS_Des, ipRaster);
	if (FAILED(hr))
	{
		::TerminateThread(hWait, 0);
		sprintf(szLog, _T("上传栅格文件失败!"));
		LOGSTR(szLog);
		return S_FALSE;
	}

	::TerminateThread(hWait, 0);

	//计算统计
	IRasterDataset2Ptr			ipRaster2Des = ipRasterDS_Des;
	IRasterPtr					ipRasterFull;
	ipRaster2Des->CreateFullRaster(&ipRasterFull);

	IRasterBandCollectionPtr								ipRasterBandCol2(ipRasterFull);

	CaComputeStatsAndHist(ipRasterBandCol2);
	//


	ipWorkspaceEdit->StopEditOperation();
	ipWorkspaceEdit->StopEditing(VARIANT_TRUE);

	sprintf(szLog, _T("完成投影栅格数据集%s"), strDatasetName.c_str());
	LOGSTR(szLog);

	return S_OK;
}
