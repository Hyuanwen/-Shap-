#include "stdafx.h"
#include "DeuTranslate.h"
#include "DeuProject.h"
#include "DXF.h"
#include "DeuFunctions.h"

#include "otlv4.h"
#include "DEUCheck.h"

//add by chenyong 2013-01-18
clock_t start;
clock_t end;
#define START_TIME 	start = clock();
#define END_TIME	end	  = clock();	

#define SEC_PER_CLOCKS 0.001

BOOL FileFolderExists(CString filename) 
{ 
	DWORD attr;   

	attr = GetFileAttributes(filename);   
	return (attr != (DWORD)(-1) ) && ( attr & FILE_ATTRIBUTE_DIRECTORY);   
} 

#define LOG_USED_TIME \
	int time_i=(end-start)*SEC_PER_CLOCKS;\
	char * time = (char *)malloc(20);\
	itoa(time_i,time,10);\
	LOG("总共用时(秒):",time,100);\
	free(time);

static TransParams g_TransParams;
otl_connect	dbsrc;
otl_connect dbdes;
CDeuTrans::CDeuTrans()
{
	m_hwnd = NULL;
	m_fea_done = 0;				  //已处理的feature
	m_all_fea_count = 0;          //总的feature个数
	m_fea_null_count = 0;		  //空feature个数
	m_fea_create_count = 0;		  //成功创建
	m_fea_fail_count = 0;		  //创建失败
	m_geo_point_count = 0;		  //点类型
	m_geo_line_count = 0;		  //线
	m_geo_polygon_count = 0;	  //面
	m_geo_multi_point_count = 0;  //多点
	m_geo_multi_line_count = 0;   //多线
	m_geo_multi_polygon_count = 0;//多面
	m_geo_null_count = 0;         //空geo
	m_error_count = 0;            //其他错误
	m_geo_done = 0;			      //已处理的非空geometry个数
	m_geo_ori_error_count = 0;    //原始geometry错误
	_callback = NULL;
	m_SRS = NULL;
}

CDeuTrans::~CDeuTrans()
{
}

int	CDeuTrans::CoordTransSingleFileExcel(const CString& strFileName_In, const CString& strDirverName_In,const CString& strFileName_Out,const CString& strDirverName_Out, VARIANT vFormat,UINT Id)
{
	LOGSTR(":CoordTransSingleFileExcel");

	CString									tempFileName_In = strFileName_In;
	CString									tempDirverName_In = strDirverName_In;
	CString									tempFileName_Out = strFileName_Out;
	CString									tempDirverName_Out = strDirverName_Out;
	_ApplicationPtr							_App = NULL;
	_WorkbookPtr							_book = NULL;
	_WorksheetPtr							_sheet = NULL;
	SheetsPtr								_sheets = NULL;
	RangePtr								pThisRange = NULL;
	_variant_t								vt;
	Excel::XlFileFormat						vFileFormat;
	Excel::XlSaveAsAccessMode				vSaveAsAccessMode;
	Excel::XlSaveConflictResolution			vSaveConflictResolution;
	char									szLine[100] = {0};
	char									szLog[200] = {0};

	LOGSTR(tempFileName_In.GetBuffer());
	LOGSTR(tempDirverName_In.GetBuffer());
	LOGSTR(tempFileName_Out.GetBuffer());
	LOGSTR(tempDirverName_Out.GetBuffer());

	tempFileName_In.ReleaseBuffer();
	tempDirverName_In.ReleaseBuffer();
	tempFileName_Out.ReleaseBuffer();
	tempDirverName_Out.ReleaseBuffer();

	deuExcelFormat  *pFormat = (deuExcelFormat*)  vFormat.byref;

	////////////////////////////////////////////////////////////////////////////
	////读坐标
	////////////////////////////////////////////////////////////////////////////
	////Excel读写方式
	//Excel::Application _App ;

	//AfxOleInit();
	::CoInitialize(NULL);
	HRESULT hr = _App.CreateInstance("Excel.Application");
	//pApplication->PutVisible (1,VARIANT_TRUE);

	try
	{
		_book = _App->GetWorkbooks()->Open(_bstr_t(strFileName_In.GetString()));
		LOGSTR(":打开源文件成功");
	}
	catch(...)
	{
		sprintf(szLine , "打开源文件失败。 ");
		LOGSTR(szLine);

		_App->Quit();
		return E_FAIL_OPENFILE;
	}

	_sheets = _book->GetWorksheets() ;
	_sheet = _sheets->GetItem((short)1);

	Excel::RangePtr _range;
	Excel::RangePtr _range_out;

	//_range = _sheet->GetRange("A1");	
	//_variant_t var_t = _range->GetValue();
	//_range_out = _sheet->GetRange("A1");

	int _start_row = 1;//起始行
	if(pFormat->_ColumnHeader.haveColumnHeader)
	{
		_start_row = pFormat->_ColumnHeader.ColumnHeaderRow+1;
	}

	int _ori_x_pos = 1;
	int _ori_y_pos = 2;
	int _ori_z_pos = 3;

	int _des_x_pos = 5;
	int _des_y_pos = 6;
	int _des_z_pos = 7;

	char _ori_x_pos_lt[100];
	char _ori_y_pos_lt[100];
	char _ori_z_pos_lt[100];

	char _des_x_pos_lt[100];
	char _des_y_pos_lt[100];
	char _des_z_pos_lt[100];

	strcpy( _ori_x_pos_lt, "0");
	strcpy( _ori_y_pos_lt, "0");
	strcpy( _ori_z_pos_lt, "0");

	strcpy( _des_x_pos_lt, "0");
	strcpy( _des_y_pos_lt, "0");
	strcpy( _des_z_pos_lt, "0");

	char *_ori_x_Letter = NULL;
	char *_ori_y_Letter = NULL;
	char *_ori_z_Letter = NULL;

	char *_des_x_Letter = NULL;
	char *_des_y_Letter = NULL;
	char *_des_z_Letter = NULL;

	double ox = 0 ;
	double oy = 0 ;
	double oz = 0 ;
	double dx = 0 ;
	double dy = 0 ;
	double dz = 0 ;

	if(pFormat->sType == ExcelFormatType::NUM )
	{
		deuColumnFormatNum *pdeuNum = (deuColumnFormatNum *)pFormat->pColFormat;
		_ori_x_pos = pdeuNum->oriX;
		_ori_y_pos = pdeuNum->oriY;
		_ori_z_pos = pdeuNum->oriZ;
		_des_x_pos = pdeuNum->desX;
		_des_y_pos = pdeuNum->desY;
		_des_z_pos = pdeuNum->desZ;

		D2L( _ori_x_pos , _ori_x_pos_lt );
		D2L( _ori_y_pos , _ori_y_pos_lt );
		D2L( _ori_z_pos , _ori_z_pos_lt );
		D2L( _des_x_pos , _des_x_pos_lt );
		D2L( _des_y_pos , _des_y_pos_lt );
		D2L( _des_z_pos , _des_z_pos_lt );
	}
	else if(pFormat->sType == ExcelFormatType::LETTER)
	{
		deuColumnFormatLetter *pdeuLetter = (deuColumnFormatLetter *)pFormat->pColFormat;

		if( pdeuLetter->oriX != NULL)
			strcpy( _ori_x_pos_lt, pdeuLetter->oriX);

		if( pdeuLetter->oriY != NULL)		
			strcpy( _ori_y_pos_lt, pdeuLetter->oriY);

		if( pdeuLetter->oriZ != NULL)				
			strcpy( _ori_z_pos_lt, pdeuLetter->oriZ);

		if( pdeuLetter->desX != NULL)						
			strcpy( _des_x_pos_lt, pdeuLetter->desX);

		if( pdeuLetter->desY != NULL)						
			strcpy( _des_y_pos_lt, pdeuLetter->desY);

		if( pdeuLetter->desZ != NULL)						
			strcpy( _des_z_pos_lt, pdeuLetter->desZ);
	}
	else
	{
		LOGSTR("错误的Excel列类型");
	}

	LOG_START;
	START_TIME;

	long         index = 0;
	long         numSheet =  _sheets->GetCount();
	unsigned int Percent = 0;
	for ( long iSheet = 1 ; iSheet <= numSheet ; iSheet++)
	{
		_sheet = _sheets->GetItem((short)iSheet);

		//LOGSTR("1.2");

		_range = _sheet->UsedRange;
		long numrow = _range->Rows->Count;

		sprintf( szLog , "Sheet = %d , UseRow = %d" , iSheet , numrow );
		LOGSTR(szLog);

		for (long irow = _start_row ; irow <= numrow ; irow++)
		{
			//每行表示每个点的b,l,h
			//#define TOL1 0.000001
			//#define TOL2 70
			//#define TOL3 0.001
			//#define TOL4 100

			/*double ox = 0 ;
			double oy = 0 ;
			double oz = 0 ;
			double dx = 0 ;
			double dy = 0 ;
			double dz = 0 ;*/

			_variant_t tx;
			_variant_t des_tx;
			Excel::RangePtr _rx;

			//if(irow == 121)
			//{
			//	_variant_t t ;
			//	t = _range->GetItem( _variant_t(irow) ,2 );
			//	double dbt = t;
			//}

			//LOGSTR("1.3");

			try
			{
				_ori_x_Letter =  GetLetter( irow , _ori_x_pos_lt );
				if(_ori_x_Letter)
					ox = GetDoubleCellVal(_sheet, _ori_x_Letter);

				_ori_y_Letter =  GetLetter( irow , _ori_y_pos_lt );
				if(_ori_y_Letter)
					oy = GetDoubleCellVal(_sheet,  _ori_y_Letter);

				_ori_z_Letter =  GetLetter( irow , _ori_z_pos_lt );
				if(_ori_z_Letter)
					oz = GetDoubleCellVal(_sheet,  _ori_z_Letter);

				//LOGSTR("1.4");

				_coordtransf( 0,1 , &ox , &oy , &oz , &dx , &dy , &dz );

				_des_x_Letter =  GetLetter( irow , _des_x_pos_lt );
				if(_des_x_Letter)
					PutStringCellVal(_sheet, _des_x_Letter , dx);

				_des_y_Letter =  GetLetter( irow , _des_y_pos_lt );
				if(_des_y_Letter)
					PutStringCellVal(_sheet, _des_y_Letter , dy);

				_des_z_Letter =  GetLetter( irow , _des_z_pos_lt );
				if(_des_z_Letter)
					PutStringCellVal(_sheet, _des_z_Letter , dz);
			}
			catch(...)
			{
				sprintf(szLine , "错误发生在 SHEET = %d , ROW = %d " ,  iSheet , irow  );
				LOGSTR(szLine);
				return /*E_FAIL_TRANSPOINT*/6;
			}//end catch

			//进度条
			Percent=(double)((double)iSheet*irow/((double)numrow*numSheet))*100;
			::SendMessage(m_hwnd,WM_PROGRESS,0,Percent);
			DEU_CALLBACK(WM_PROGRESS,0,Percent);
		}
	}

	::SendMessage(m_hwnd,WM_PROGRESS,0,100);

	//要注意 20130106 chenyong 
	delete _ori_x_Letter;
	delete _ori_y_Letter;
	delete _ori_z_Letter;

	delete _des_x_Letter;
	delete _des_y_Letter;
	delete _des_z_Letter;

	//_range_out->PutItem(13,13,_variant_t(123));

	vSaveAsAccessMode = xlNoChange ;
	vFileFormat = xlWorkbookNormal ;
	vSaveConflictResolution = xlLocalSessionChanges ;	

	try
	{
		_book->SaveAs(strFileName_Out.GetString(), vtMissing,vtMissing,vtMissing, vtMissing,
			vtMissing, vSaveAsAccessMode, vtMissing, vtMissing) ;
	}
	catch(...)
	{		
		_App->Quit();
		LOGSTR("quit");

		return E_FAIL_SAVEFILE;
	}

	_book->Close();
	_App->Quit();

	::CoUninitialize();

	Percent=(double)((double)100/(double)100)*100;
	::SendMessage(m_hwnd,WM_PROGRESS,0,Percent);
	DEU_CALLBACK(WM_PROGRESS,0,Percent);

	END_TIME;
	LOG_USED_TIME;
	LOG_END;
	LOGSTR("=====================================================================");

	return 0;
}

long CDeuTrans::Use_Deu_CoordTransSingleFile(const CString& strFileName_In, const CString& strDirverName_In,const CString& strFileName_Out,const CString& strDirverName_Out, UINT Id)
{
	LOGSTR(":CoordTransDeuSingleFile");

	CString									tempFileName_In = strFileName_In;
	CString									tempDirverName_In = strDirverName_In;
	CString									tempFileName_Out = strFileName_Out;
	CString									tempDirverName_Out = strDirverName_Out;
	char									szLine[100] = {0};
	char									szLog[200] = {0};

	LOGSTR(tempFileName_In.GetBuffer());
	LOGSTR(tempDirverName_In.GetBuffer());
	LOGSTR(tempFileName_Out.GetBuffer());
	LOGSTR(tempDirverName_Out.GetBuffer());

	tempFileName_In.ReleaseBuffer();
	tempDirverName_In.ReleaseBuffer();
	tempFileName_Out.ReleaseBuffer();
	tempDirverName_Out.ReleaseBuffer();

	if (m_Params == NULL)
	{
		LOGSTR("error:没有设置转换参数");
	}

	LOG_START;
	START_TIME;

	if (strDirverName_In == _T("DXF"))
	{
		void * p_f = 0;

		GetMemberFuncAddr_VC6( p_f , &CDeuTrans::transfun );

		//BSTR bstrSRS;
		//m_SRS->exportToWkt(&bstrSRS);
		//importSRSFromWkt( (LPCSTR)_bstr_t(bstrSRS) );

		/*unsigned int  Percent=(double)((double)1/(double)100)*100;
		::SendMessage(m_hwnd,WM_PROGRESS,0,Percent);
		DEU_CALLBACK(WM_PROGRESS,0,Percent);*/

		if (g_TransParams.SrcCoordType == g_TransParams.DesCoordType)
		{
			DXFTransform(strFileName_In.GetString(), strFileName_Out.GetString(), p_f , m_hwnd);
		}
		else
		{
			bool  bToPlane;
			//正投
			if( (g_TransParams.SrcCoordType == GEODETIC) && ( g_TransParams.DesCoordType == PLANE) )
			{
				bToPlane = true;
			}
			else 
				bToPlane = false;
			DXFProject(strFileName_In.GetString(), strFileName_Out.GetString(), bToPlane, p_f , m_hwnd);
		}

        unsigned int	Percent=(double)((double)100/(double)100)*100;
		::SendMessage(m_hwnd,WM_PROGRESS,0,Percent);
		DEU_CALLBACK(WM_PROGRESS,0,Percent);
	}

	//增加对EOO文件格式的读写 yzg 2012-9-12 begin
    else if (strDirverName_In == _T("AVCE00"))
    {
		void * p_f = 0;
		GetMemberFuncAddr_VC6( p_f , &CDeuTrans::transfun );

		unsigned int  Percent=(double)((double)1/(double)100)*100;
		::SendMessage(m_hwnd,WM_PROGRESS,0,Percent);
		DEU_CALLBACK(WM_PROGRESS,0,Percent);

		EooTransform(strFileName_In.GetString(), strFileName_Out.GetString(), p_f, m_hwnd );

		Percent=(double)((double)100/(double)100)*100;
		::SendMessage(m_hwnd,WM_PROGRESS,0,Percent);
		DEU_CALLBACK(WM_PROGRESS,0,Percent);
    }
	else if (strDirverName_In == _T("Coverage"))
	{
		void * p_f = 0;
		GetMemberFuncAddr_VC6( p_f , &CDeuTrans::transfun );

		unsigned int  Percent=(double)((double)1/(double)100)*100;
		::SendMessage(m_hwnd,WM_PROGRESS,0,Percent);
		DEU_CALLBACK(WM_PROGRESS,0,Percent);

		CoverageTransform(strFileName_In.GetString(), strFileName_Out.GetString(), p_f, m_hwnd );

		Percent=(double)((double)100/(double)100)*100;
		::SendMessage(m_hwnd,WM_PROGRESS,0,Percent);
		DEU_CALLBACK(WM_PROGRESS,0,Percent);
	}

	END_TIME;
	LOG_USED_TIME;
	LOG_END;
	LOGSTR("=====================================================================");

	return 0;
}

void CDeuTrans::transfun( double x , double y , double z , double & out_x ,double & out_y ,double & out_z )
{
	_coordtransf( 0 , 1 , &x , &y, &z, &out_x, &out_y, &out_z);

	return ;
}

int CDeuTrans::_coordtransf( int fea_FID, unsigned long n, double* oriX, double* oriY, double* oriZ, double* destX, double* destY, double* destZ)
{
	int										result = 0;
	char									szBuff[300] = {0};
	
	//根据公式，决定坐标类型。
	int iTransModel = g_TransParams._TransModel;

	switch(iTransModel)
	{
	case MODEL_D3P7:
		//BLH to BLH
		//_CoordTransf_D3P7(n,oriX,oriY,oriZ,destX,destY,destZ);
		_CoordTransf_BURSA(n,oriX,oriY,oriZ,destX,destY,destZ);
		break;

	case MODEL_D2P4:
		//xy to xy h=0
		_CoordTransf_D2P4(n,oriX,oriY,oriZ,destX,destY,destZ);
		break;

	case MODEL_BURSA:
		//XYZ to XYZ
		_CoordTransf_BURSA(n,oriX,oriY,oriZ,destX,destY,destZ);
		break;

	case MODEL_D2P7:
		//bl to bl H=0
		//_CoordTransf_D2P7(n,oriX,oriY,oriZ,destX,destY,destZ);
		_CoordTransf_BURSA(n,oriX,oriY,oriZ,destX,destY,destZ);
		break;

	case MODEL_GAUSS:
		_CoordTransf_GAUSS(n,oriX,oriY,oriZ,destX,destY,destZ);
		break;

	case MODEL_TM:
		_CoordTransf_GAUSS(n,oriX,oriY,oriZ,destX,destY,destZ);
		//_CoordTransf_TM(n,oriX,oriY,oriZ,destX,destY,destZ);
		break;

	case MODEL_UTM:
		_CoordTransf_UTM(n,oriX,oriY,oriZ,destX,destY,destZ);
		break;

	case MODEL_GRID:
		result = _CoordTransf_GRID(n,oriX,oriY,oriZ,destX,destY,destZ);
		if( result != 0 )
		{
			sprintf( szBuff , "error:无法计算该点的改正量，FID = %d" , fea_FID ) ;
			LOGSTR(szBuff);
		}
		break;

	default:
		LOGSTR("error:没有设置转换模型");
		break;
	}

	return result;
}

void CDeuTrans::_CoordTransf_D3P7(unsigned long n, double* oriX, double* oriY, double* oriZ, double* destX, double* destY, double* destZ)
{
	//调用DLL,从原始坐标类型转换到空间直角坐标类型
	short									coordtype = 0;
	short									destcoordtype = 0;
	CString									szunittype_x = _T("");
	CString									szunittype_y = _T("");
	CString									szunittype_z = _T("");
	CString									szunittype_des_x = _T("");
	CString									szunittype_des_y = _T("");
	CString									szunittype_des_z = _T("");

	coordtype = g_TransParams.SrcCoordType;
	destcoordtype = g_TransParams.DesCoordType;
	szunittype_x = g_TransParams.SrcUnitX;
	szunittype_y = g_TransParams.SrcUnitY;
	szunittype_z = g_TransParams.SrcUnitZ;
	szunittype_des_x = g_TransParams.DesUnitX;
	szunittype_des_y = g_TransParams.DesUnitY;
	szunittype_des_z = g_TransParams.DesUnitZ;

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

	for (int i=0;i<n;i++)
	{
		oriX_i=oriX[i];
		oriY_i=oriY[i];
		oriZ_i=oriZ[i];

		//转到弧度或米
		unitX_i=CDeuUnits::TypeToUnit(oriX_i,szunittype_x);
		unitY_i=CDeuUnits::TypeToUnit(oriY_i,szunittype_y);
		unitZ_i=CDeuUnits::TypeToUnit(oriZ_i,szunittype_z);

		switch (coordtype)
		{
		case  GEODETIC://大地
			geo_X_i = unitX_i;
			geo_Y_i = unitY_i;
			geo_Z_i = unitZ_i;
			break;

		case  GEOCENTRIC:
			geo_X_i = unitX_i;
			geo_Y_i = unitY_i;
			geo_Z_i = unitZ_i;

			pj_geocentric_to_geodetic( g_TransParams._src_a, g_TransParams._src_f,1,0,&geo_X_i,&geo_Y_i,&geo_Z_i);
			break;

		case  PLANE:   //平面
			geo_Z_i = unitZ_i;
			Gauss_xy_bl( g_TransParams._srcPJ, g_TransParams._src_from_greenwich * DEG_TO_RAD ,unitX_i,unitY_i,geo_X_i,geo_Y_i);
			break;

		default:
			LOGSTR("error:UNKNOWN TYPE");
			break;
		}

		//调用DeuProject的DLL,将空间直角坐标从源坐标系到目标坐标系
		CoorTran_BLH7( g_TransParams._srcPJ, g_TransParams._desPJ, g_TransParams._Para,geo_X_i,geo_Y_i,geo_Z_i,Trsfmed_X_i,Trsfmed_Y_i,Trsfmed_Z_i);

		//根据要求的输出坐标类型，从空间直角坐标转换到目标坐标类型
		switch (destcoordtype)
		{
		case  GEODETIC: //大地
			desX_i = Trsfmed_X_i;
			desY_i = Trsfmed_Y_i;
			desZ_i = Trsfmed_Z_i;
			break;

		case  GEOCENTRIC:
			desX_i = Trsfmed_X_i;
			desY_i = Trsfmed_Y_i;
			desZ_i = Trsfmed_Z_i;

			pj_geodetic_to_geocentric( g_TransParams._des_a, g_TransParams._des_f,1,0,&desX_i,&desY_i,&desZ_i);
			break;

		case  PLANE:    //平面
			desZ_i = Trsfmed_Z_i;

			Gauss_bl_xy( g_TransParams._desPJ, g_TransParams._des_from_greenwich * DEG_TO_RAD,Trsfmed_X_i,Trsfmed_Y_i,desX_i,desY_i);
			break;

		default:
			LOGSTR("error:UNKNOWN TYPE");
			break;
		}

		//转到原始单位下
		desX_i_ori_unit=CDeuUnits::UnitToType(desX_i,szunittype_x);
		desY_i_ori_unit=CDeuUnits::UnitToType(desY_i,szunittype_y);
		desZ_i_ori_unit=CDeuUnits::UnitToType(desZ_i,szunittype_z);

		destX[i]=desX_i_ori_unit;
		destY[i]=desY_i_ori_unit;
		destZ[i]=desZ_i_ori_unit;

		desX_i=0;
		desY_i=0;
		desZ_i=0;
	}

	return ;
}

void CDeuTrans::_CoordTransf_D2P4(unsigned long n, double* oriX, double* oriY, double* oriZ, double* destX, double* destY, double* destZ)
{
	//调用DLL,从原始坐标类型转换到空间直角坐标类型
	short									coordtype = 0;
	short									destcoordtype = 0;
	CString									szunittype_x = _T("");
	CString									szunittype_y = _T("");
	CString									szunittype_z = _T("");
	CString									szunittype_des_x = _T("");
	CString									szunittype_des_y = _T("");
	CString									szunittype_des_z = _T("");

	coordtype = g_TransParams.SrcCoordType;
	destcoordtype = g_TransParams.DesCoordType;

	szunittype_x = g_TransParams.SrcUnitX;
	szunittype_y = g_TransParams.SrcUnitY;
	szunittype_z = g_TransParams.SrcUnitZ;
	szunittype_des_x = g_TransParams.DesUnitX;
	szunittype_des_y = g_TransParams.DesUnitY;
	szunittype_des_z = g_TransParams.DesUnitZ;

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

	for (int i=0;i<n;i++)
	{
		oriX_i=oriX[i];
		oriY_i=oriY[i];
		oriZ_i=oriZ[i];

		//转到弧度或米
		unitX_i=CDeuUnits::TypeToUnit(oriX_i,szunittype_x);
		unitY_i=CDeuUnits::TypeToUnit(oriY_i,szunittype_y);
		unitZ_i=CDeuUnits::TypeToUnit(oriZ_i,szunittype_z);

		switch (coordtype)
		{
		case  GEODETIC://大地
			geo_Z_i = unitZ_i;
			Gauss_bl_xy(g_TransParams._srcPJ,g_TransParams._src_from_greenwich * DEG_TO_RAD,unitX_i,unitY_i,geo_X_i,geo_Y_i);
			break;

		case  GEOCENTRIC:
			pj_geocentric_to_geodetic( g_TransParams._src_a,g_TransParams._src_f,1,0,&unitX_i,&unitY_i,&unitZ_i);
			Gauss_bl_xy( g_TransParams._srcPJ, g_TransParams._src_from_greenwich * DEG_TO_RAD,unitX_i,unitY_i,geo_X_i,geo_Y_i);
			geo_Z_i = unitZ_i;
			break;

		case  PLANE:   //平面				
			geo_X_i	= unitX_i ;
			geo_Y_i = unitY_i - g_TransParams._src_false_east;
			geo_Z_i = unitZ_i ;
			break;

		default:
			LOGSTR("error:UNKNOWN TYPE");
			break;
		}

		//调用DLL,将空间直角坐标从源坐标系到目标坐标系
		//yzg 2012-8-14 临时修改 begin
		CoorTran_xy4( g_TransParams._Para,geo_X_i,geo_Y_i,Trsfmed_X_i,Trsfmed_Y_i);

		Trsfmed_Z_i = geo_Z_i;

		//根据要求的输出坐标类型，从空间直角坐标转换到目标坐标类型
		switch (destcoordtype)
		{
		case  GEODETIC://大地
			Gauss_xy_bl( g_TransParams._desPJ, g_TransParams._des_from_greenwich * DEG_TO_RAD,Trsfmed_X_i,Trsfmed_Y_i,desX_i,desY_i);
			break;

		case  GEOCENTRIC:
			desX_i = Trsfmed_X_i;
			desY_i = Trsfmed_Y_i;
			desZ_i = Trsfmed_Z_i;
			Gauss_xy_bl( g_TransParams._desPJ, g_TransParams._des_from_greenwich* DEG_TO_RAD,Trsfmed_X_i,Trsfmed_Y_i,geo_X_i,geo_Y_i);
			pj_geodetic_to_geocentric( g_TransParams._des_a, g_TransParams._des_f,1,0,&desX_i,&desY_i,&desZ_i);
			break;

		case  PLANE: //平面	
			desX_i = Trsfmed_X_i;
			desY_i = Trsfmed_Y_i + g_TransParams._des_false_east;
			desZ_i = Trsfmed_Z_i;
			break;

		default:
			LOGSTR("error:UNKNOWN TYPE");
			break;
		}

		//转到原始单位下
		desX_i_ori_unit=CDeuUnits::UnitToType(desX_i,szunittype_x);
		desY_i_ori_unit=CDeuUnits::UnitToType(desY_i,szunittype_y);
		desZ_i_ori_unit=CDeuUnits::UnitToType(desZ_i,szunittype_z);

		destX[i]=desX_i_ori_unit;
		destY[i]=desY_i_ori_unit;
		destZ[i]=desZ_i_ori_unit;

		desX_i=0;
		desY_i=0;
		desZ_i=0;
	}

	return ;
}

void CDeuTrans::_CoordTransf_UTM(unsigned long n, double* oriX, double* oriY, double* oriZ, double* destX, double* destY, double* destZ)
{
	//调用DLL,从原始坐标类型转换到空间直角坐标类型
	short									coordtype = 0;
	short									destcoordtype = 0;
	CString									szunittype_x = _T("");
	CString									szunittype_y = _T("");
	CString									szunittype_z = _T("");
	CString									szunittype_des_x = _T("");
	CString									szunittype_des_y = _T("");
	CString									szunittype_des_z = _T("");
	
	coordtype = g_TransParams.SrcCoordType;
	destcoordtype = g_TransParams.DesCoordType;

	szunittype_x = g_TransParams.SrcUnitX;
	szunittype_y = g_TransParams.SrcUnitY;
	szunittype_z = g_TransParams.SrcUnitZ;
	szunittype_des_x = g_TransParams.DesUnitX;
	szunittype_des_y = g_TransParams.DesUnitY;
	szunittype_des_z = g_TransParams.DesUnitZ;

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

	for (int i=0;i<n;i++)
	{
		oriX_i=oriX[i];
		oriY_i=oriY[i];
		oriZ_i=oriZ[i];

		//转到弧度或米
		unitX_i=CDeuUnits::TypeToUnit(oriX_i,szunittype_x);
		unitY_i=CDeuUnits::TypeToUnit(oriY_i,szunittype_y);
		unitZ_i=CDeuUnits::TypeToUnit(oriZ_i,szunittype_z);

		if( coordtype == destcoordtype)//如果坐标类型相同无需投影
		{
			LOGSTR("error:坐标类型相同无需投影");
			return;
		}
		else if( (coordtype == GEODETIC) && ( destcoordtype == PLANE) )
		{
			//正投影
			Gauss_bl_xy( g_TransParams._desPJ,( g_TransParams._des_from_greenwich ) * DEG_TO_RAD,unitX_i,unitY_i,desX_i,desY_i);

			desX_i *= 0.9996;
			desY_i *= 0.9996;

			desY_i += g_TransParams._des_false_east;
		}
		else if( (coordtype == PLANE) && ( destcoordtype == GEODETIC) )
		{
			//反投影
			unitY_i -= g_TransParams._des_false_east;
			unitX_i /= 0.9996;
			unitY_i /= 0.9996;

			Gauss_xy_bl( g_TransParams._srcPJ, g_TransParams._src_from_greenwich * DEG_TO_RAD ,unitX_i, unitY_i,desX_i,desY_i);
		}
		else
		{
			LOGSTR("error:错误的投影坐标类型");
		}

		//转到原始单位下
		desX_i_ori_unit=CDeuUnits::UnitToType(desX_i,szunittype_des_x);
		desY_i_ori_unit=CDeuUnits::UnitToType(desY_i,szunittype_des_y);
		desZ_i_ori_unit=CDeuUnits::UnitToType(desZ_i,szunittype_des_z);

		destX[i]=desX_i_ori_unit ;
		destY[i]=desY_i_ori_unit ;
		destZ[i]=desZ_i_ori_unit;

		desX_i=0;
		desY_i=0;
		desZ_i=0;
	}

	return ;
}

void CDeuTrans::_CoordTransf_GAUSS(unsigned long n, double* oriX, double* oriY, double* oriZ, double* destX, double* destY, double* destZ)
{
	//调用DLL,从原始坐标类型转换到空间直角坐标类型
	short									coordtype = 0;
	short									destcoordtype = 0;
	CString									szunittype_x = _T("");
	CString									szunittype_y = _T("");
	CString									szunittype_z = _T("");
	CString									szunittype_des_x = _T("");
	CString									szunittype_des_y = _T("");
	CString									szunittype_des_z = _T("");

	coordtype = g_TransParams.SrcCoordType;
	destcoordtype = g_TransParams.DesCoordType;

	szunittype_x = g_TransParams.SrcUnitX;
	szunittype_y = g_TransParams.SrcUnitY;
	szunittype_z = g_TransParams.SrcUnitZ;
	szunittype_des_x = g_TransParams.DesUnitX;
	szunittype_des_y = g_TransParams.DesUnitY;
	szunittype_des_z = g_TransParams.DesUnitZ;

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

	for (int i=0;i<n;i++)
	{
		oriX_i=oriX[i];
		oriY_i=oriY[i];
		oriZ_i=oriZ[i];

		//转到弧度或米
		unitX_i=CDeuUnits::TypeToUnit(oriX_i,szunittype_x);
		unitY_i=CDeuUnits::TypeToUnit(oriY_i,szunittype_y);
		unitZ_i=CDeuUnits::TypeToUnit(oriZ_i,szunittype_z);

		if( coordtype == destcoordtype)//如果坐标类型相同无需投影
		{
			LOGSTR("error:坐标类型相同无需投影");
			return;
		}
		else if( (coordtype == GEODETIC) && ( destcoordtype == PLANE) )
		{
			//正投影
			Gauss_bl_xy( g_TransParams._desPJ,(g_TransParams._des_from_greenwich) * DEG_TO_RAD,unitX_i,unitY_i,desX_i,desY_i);
			desY_i += g_TransParams._des_false_east;
		}
		else if( (coordtype == PLANE) && ( destcoordtype == GEODETIC) )
		{
			//反投影
			Gauss_xy_bl( g_TransParams._srcPJ,g_TransParams._src_from_greenwich * DEG_TO_RAD ,unitX_i,unitY_i - g_TransParams._src_false_east,desX_i,desY_i);
		}
		else
		{
			LOGSTR("error:错误的投影坐标类型");
		}

		//转到原始单位下
		desX_i_ori_unit=CDeuUnits::UnitToType(desX_i,szunittype_des_x);
		desY_i_ori_unit=CDeuUnits::UnitToType(desY_i,szunittype_des_y);
		desZ_i_ori_unit=CDeuUnits::UnitToType(desZ_i,szunittype_des_z);

		destX[i]=desX_i_ori_unit;
		destY[i]=desY_i_ori_unit;
		destZ[i]=desZ_i_ori_unit;

		desX_i=0;
		desY_i=0;
		desZ_i=0;
	}

	return ;
}

int CDeuTrans::_CoordTransf_GRID(unsigned long n, double* oriX, double* oriY, double* oriZ, double* destX, double* destY, double* destZ)
{
	int result = 0;

	double oriX_i(0),oriY_i(0),oriZ_i(0);
	double unitX_i(0),unitY_i(0),unitZ_i(0);
	double Trsfmed_X_i(0),Trsfmed_Y_i(0),Trsfmed_Z_i(0);
	double desX_unit_i(0),desY_unit_i(0),desZ_unit_i(0);	
	double desX_i(0),desY_i(0),desZ_i(0);
	
	short coordtype=0;
	coordtype = g_TransParams.SrcCoordType;

	short destcoordtype=0;
	destcoordtype = g_TransParams.DesCoordType;

	CString szunittype_x = _T("");
	szunittype_x = g_TransParams.SrcUnitX;

	CString szunittype_y = _T("");
	szunittype_y = g_TransParams.SrcUnitY;

	CString szunittype_z = _T("");
	szunittype_z = g_TransParams.SrcUnitZ;

	CString szunittype_des_x = _T("");
	szunittype_des_x = g_TransParams.DesUnitX;

	CString szunittype_des_y = _T("");
	szunittype_des_y = g_TransParams.DesUnitY;

	CString szunittype_des_z = _T("");
	szunittype_des_z = g_TransParams.DesUnitZ;

	CString SrcProId = _T("");
    SrcProId = g_TransParams.SrcProId;

    CString SrcPwd;
	SrcPwd = g_TransParams.SrcPwd;

	CString SrcProName = _T("");
    SrcProName = g_TransParams.SrcProName;

	//获得方向 6378245 6378140 6378137
	int FX = -1;
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

	double dx(0) , dy(0);
	//char szFrame[20];	//这里原数组的长度有12->20,防止因为没能取到正确的图幅号,导致堆栈被破坏 yzg 2012-10-9
	std::string strFrame;

	for (int i=0;i<n;i++)
	{
		oriX_i=oriX[i];
		oriY_i=oriY[i];
		oriZ_i=oriZ[i];

		//转到标准单位下
		//转到弧度或米
		unitX_i=CDeuUnits::TypeToUnit(oriX_i,szunittype_x);
		unitY_i=CDeuUnits::TypeToUnit(oriY_i,szunittype_y);
		unitZ_i=CDeuUnits::TypeToUnit(oriZ_i,szunittype_z);

		//-----------------------------------------------------------------------
		//如果是大地，直接计算改正量，如果是平面，先算出大地改正量，然后投影
		switch (coordtype)
		{
		case  GEODETIC://大地
			Trsfmed_X_i = unitX_i;
			Trsfmed_Y_i = unitY_i;
			Trsfmed_Z_i = unitZ_i;
			break;

		case  GEOCENTRIC:
			break;

		case  PLANE:   //平面
			Gauss_xy_bl( g_TransParams._srcPJ, g_TransParams._src_from_greenwich * DEG_TO_RAD ,unitX_i,unitY_i - g_TransParams._src_false_east,Trsfmed_X_i,Trsfmed_Y_i);
			Trsfmed_Z_i = unitZ_i;
			break;

		default:
			LOGSTR("error:没有设置坐标类型");
			break;
		}

		//----------------------------------------------------------------------------
		//转到单位度
		Trsfmed_X_i = RAD_TO_DEG * Trsfmed_X_i ;
		Trsfmed_Y_i = RAD_TO_DEG * Trsfmed_Y_i ;

		m_GridTranslate.CalculateFrameByPoint(Trsfmed_X_i, Trsfmed_Y_i, _T("D"), &strFrame);

		HRESULT hret = m_GridTranslate.CalculateOffset(strFrame, Trsfmed_X_i, Trsfmed_Y_i, &dx, &dy);
		if(hret != S_OK)
		{
			result = -1;
		}

/*  	//使用大地坐标进行计算
		//判断在哪个格网里
		//void CalculateFrameByPoint( double x ,double y ,int coordtype , char * szFrame);
		CalculateFrameByPoint( Trsfmed_X_i , Trsfmed_Y_i , coordtype , 'D' , szFrame);

		//获得格网改正量
//		void CalculateDetalXY(  double &x ,double &y , int coordtype  ,char * szFrame )
		int ret = FetchDetalXY( Trsfmed_X_i , Trsfmed_Y_i , coordtype , "61" , "lyjfyxxyht197021" , "陕西", szFrame , FX  , dx ,dy );
//		int ret = FetchDetalXY( Trsfmed_X_i , Trsfmed_Y_i , coordtype , _bstr_t(SrcProId) , _bstr_t(SrcPwd) , _bstr_t(SrcProName), szFrame , FX  , dx ,dy );
		if(ret != 0)
			result = -1;
*/
		//加上改正量
		//LOG_EXTENT(dx1, dy1, dx, dy);
		Trsfmed_X_i = Trsfmed_X_i + dx;
		Trsfmed_Y_i = Trsfmed_Y_i + dy;
		Trsfmed_Z_i = Trsfmed_Z_i ;

		//度转回弧度
		Trsfmed_X_i = DEG_TO_RAD * Trsfmed_X_i ;
		Trsfmed_Y_i = DEG_TO_RAD * Trsfmed_Y_i ;
		Trsfmed_Z_i = DEG_TO_RAD * Trsfmed_Z_i ;

		switch (destcoordtype)
		{
		case  GEODETIC: //大地
			desX_unit_i = Trsfmed_X_i;
			desY_unit_i = Trsfmed_Y_i;
			desZ_unit_i = Trsfmed_Z_i;
			//pj_geodetic_to_geocentric(m_src_a,m_src_f,1,0,&geo_X_i,&geo_Y_i,&geo_Z_i);
			break;

		case  GEOCENTRIC:
			break; 

		case  PLANE:	//平面
			Gauss_bl_xy( g_TransParams._desPJ, g_TransParams._des_from_greenwich * DEG_TO_RAD ,Trsfmed_X_i,Trsfmed_Y_i,desX_unit_i,desY_unit_i);
			desY_unit_i +=  g_TransParams._des_false_east ;
			desZ_unit_i = Trsfmed_Z_i;
			break;

		default:
			LOGSTR("error:没有设置坐标类型");
			break;
		}

		//转回原来的单位
		desX_i=CDeuUnits::UnitToType(desX_unit_i,szunittype_des_x);
		desY_i=CDeuUnits::UnitToType(desY_unit_i,szunittype_des_y);
		desZ_i=CDeuUnits::UnitToType(desZ_unit_i,szunittype_des_z);

		destX[0] = desX_i ;
		destY[0] = desY_i ;
		destZ[0] = desZ_i ;
	}

	return result;
}

void CDeuTrans::_CoordTransf_BURSA(unsigned long n, double* oriX, double* oriY, double* oriZ, double* destX, double* destY, double* destZ)
{
	//调用DLL,从原始坐标类型转换到空间直角坐标类型
	short									coordtype = 0;
	short									destcoordtype = 0;
	CString									szunittype_x = _T("");
	CString									szunittype_y = _T("");
	CString									szunittype_z = _T("");
	CString									szunittype_des_x = _T("");
	CString									szunittype_des_y = _T("");
	CString									szunittype_des_z = _T("");
	
	coordtype = g_TransParams.SrcCoordType;
	destcoordtype = g_TransParams.DesCoordType;

	szunittype_x = g_TransParams.SrcUnitX;
	szunittype_y = g_TransParams.SrcUnitY;
	szunittype_z = g_TransParams.SrcUnitZ;
	szunittype_des_x = g_TransParams.DesUnitX;
	szunittype_des_y = g_TransParams.DesUnitY;
	szunittype_des_z = g_TransParams.DesUnitZ;

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

	for (int i=0;i<n;i++)
	{
		oriX_i=oriX[i];
		oriY_i=oriY[i];
		oriZ_i=oriZ[i];

		//转到弧度或米
		unitX_i=CDeuUnits::TypeToUnit(oriX_i,szunittype_x);
		unitY_i=CDeuUnits::TypeToUnit(oriY_i,szunittype_y);
		unitZ_i=CDeuUnits::TypeToUnit(oriZ_i,szunittype_z);

		switch (coordtype)
		{
		case  GEODETIC://大地
			geo_X_i = unitX_i;
			geo_Y_i = unitY_i;
			geo_Z_i = unitZ_i;
			pj_geodetic_to_geocentric(g_TransParams._src_a,g_TransParams._src_f,1,0,&geo_X_i,&geo_Y_i,&geo_Z_i);
			break;

		case  GEOCENTRIC:
			break;

		case  PLANE:  //平面
			Gauss_xy_bl(g_TransParams._srcPJ,g_TransParams._src_from_greenwich * DEG_TO_RAD ,unitX_i,unitY_i - g_TransParams._src_false_east,geo_X_i,geo_Y_i);
			geo_Z_i = unitZ_i;
			pj_geodetic_to_geocentric(g_TransParams._src_a,g_TransParams._src_f,1,0,&geo_X_i,&geo_Y_i,&geo_Z_i);
			//geo_Z_i = unitZ_i;
			//DLL void FromxyHToBLH(ELLIP_PRJ Ellip_Prj,double x,double y,double h,double & B,double & L,double & H);
			break;

		default:
			LOGSTR("error:没有设置坐标类型");
			break;
		}

		//调用DLL,将空间直角坐标从源坐标系到目标坐标系
		//DLL void CoorTran(double  Para[],double X0,double Y0,double Z0,double & X,double & Y,double & Z);
		//CoorTran(m_sevenparams_double,geo_X_i,geo_Y_i,geo_Z_i,Trsfmed_X_i,Trsfmed_Y_i,Trsfmed_Z_i);

		CoorTran_Bursa(g_TransParams._Para,geo_X_i,geo_Y_i,geo_Z_i,Trsfmed_X_i,Trsfmed_Y_i,Trsfmed_Z_i);
		//CoorTran_Bursa(m_Para,geo_X_i,geo_Y_i,geo_Z_i,Trsfmed_X_i,Trsfmed_Y_i,Trsfmed_Z_i);
      
		//根据要求的输出坐标类型，从空间直角坐标转换到目标坐标类型
		switch (destcoordtype)
		{
		case  GEODETIC://大地
			desX_i = Trsfmed_X_i;
			desY_i = Trsfmed_Y_i;
			desZ_i = Trsfmed_Z_i;
			pj_geocentric_to_geodetic(g_TransParams._des_a,g_TransParams._des_f,1,0,&desX_i,&desY_i,&desZ_i);
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
			pj_geocentric_to_geodetic(g_TransParams._des_a,g_TransParams._des_f,1,0,&Trsfmed_X_i,&Trsfmed_Y_i,&Trsfmed_Z_i);
			Gauss_bl_xy(g_TransParams._desPJ,(g_TransParams._des_from_greenwich) * DEG_TO_RAD,Trsfmed_X_i,Trsfmed_Y_i,desX_i,desY_i);
			desY_i += g_TransParams._des_false_east;
			desZ_i = Trsfmed_Z_i;
			//DLL void FromxyHToBLH(ELLIP_PRJ Ellip_Prj,double x,double y,double h,double & B,double & L,double & H);
			break;

		default:
			LOGSTR("error:没有设置坐标类型");
			break;
		}

		//转到原始单位下
		desX_i_ori_unit=CDeuUnits::UnitToType(desX_i,szunittype_des_x);
		desY_i_ori_unit=CDeuUnits::UnitToType(desY_i,szunittype_des_y);
		desZ_i_ori_unit=CDeuUnits::UnitToType(desZ_i,szunittype_des_z);

		destX[i]=desX_i_ori_unit;
		destY[i]=desY_i_ori_unit;
		destZ[i]=desZ_i_ori_unit;

		desX_i=0;
		desY_i=0;
		desZ_i=0;
	}

	return ;
}

void CDeuTrans::_CoordTransf_D2P7(unsigned long n, double* oriX, double* oriY, double* oriZ, double* destX, double* destY, double* destZ)
{
	//调用DLL,从原始坐标类型转换到空间直角坐标类型
	short									coordtype = 0;
	short									destcoordtype = 0;
	CString									szunittype_x = _T("");
	CString									szunittype_y = _T("");
	CString									szunittype_z = _T("");
	CString									szunittype_des_x = _T("");
	CString									szunittype_des_y = _T("");
	CString									szunittype_des_z = _T("");
	
	coordtype = g_TransParams.SrcCoordType;
	destcoordtype = g_TransParams.DesCoordType;

	szunittype_x = g_TransParams.SrcUnitX;
	szunittype_y = g_TransParams.SrcUnitY;
	szunittype_z = g_TransParams.SrcUnitZ;
	szunittype_des_x = g_TransParams.DesUnitX;
	szunittype_des_y = g_TransParams.DesUnitY;
	szunittype_des_z = g_TransParams.DesUnitZ;

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

	for (int i=0;i<n;i++)
	{
		oriX_i=oriX[i];
		oriY_i=oriY[i];
		oriZ_i=oriZ[i];

		//转到弧度或米
		unitX_i=CDeuUnits::TypeToUnit(oriX_i,szunittype_x);
		unitY_i=CDeuUnits::TypeToUnit(oriY_i,szunittype_y);
		unitZ_i=CDeuUnits::TypeToUnit(oriZ_i,szunittype_z);

		switch (coordtype)
		{
		case  GEODETIC://大地
			//FromBLHToXYZ(m_ell_prj,unitX_i,unitY_i,unitZ_i,geo_X_i,geo_Y_i,geo_Z_i);
			//DLL void FromBLHToXYZ(ELLIP_PRJ Ellip_Prj,double B,double L,double H,double & X,double & Y,double & Z );
			geo_X_i = unitX_i;
			geo_Y_i = unitY_i;
			geo_Z_i = unitZ_i;
			break;

		case  GEOCENTRIC:
			geo_X_i = unitX_i;
			geo_Y_i = unitY_i;
			geo_Z_i = unitZ_i;
			pj_geocentric_to_geodetic( g_TransParams._src_a, g_TransParams._src_f,1,0,&geo_X_i,&geo_Y_i,&geo_Z_i);
			break;

		case  PLANE://平面
			geo_Z_i = unitZ_i;
			Gauss_xy_bl( g_TransParams._srcPJ, g_TransParams._src_from_greenwich * DEG_TO_RAD ,unitX_i,unitY_i,geo_X_i,geo_Y_i);
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
		CoorTran_BL7( g_TransParams._srcPJ, g_TransParams._desPJ, g_TransParams._Para,geo_X_i,geo_Y_i,Trsfmed_X_i,Trsfmed_Y_i);

		//根据要求的输出坐标类型，从空间直角坐标转换到目标坐标类型
		switch (destcoordtype)
		{
		case  GEODETIC://大地
			//FromXYZToBLH(m_des_ell_prj,Trsfmed_X_i,Trsfmed_Y_i,Trsfmed_Z_i,desX_i,desY_i,desZ_i);
			//DLL void FromBLHToXYZ(ELLIP_PRJ Ellip_Prj,double B,double L,double H,double & X,double & Y,double & Z );
			desX_i = Trsfmed_X_i;
			desY_i = Trsfmed_Y_i;
			desZ_i = Trsfmed_Z_i;
			break;

		case  GEOCENTRIC:
			desX_i = Trsfmed_X_i;
			desY_i = Trsfmed_Y_i;
			desZ_i = Trsfmed_Z_i;
			pj_geodetic_to_geocentric( g_TransParams._des_a, g_TransParams._des_f,1,0,&desX_i,&desY_i,&desZ_i);
			break;

		case  PLANE://平面
			desZ_i = Trsfmed_Z_i;
			Gauss_bl_xy( g_TransParams._desPJ, g_TransParams._des_from_greenwich * DEG_TO_RAD,Trsfmed_X_i,Trsfmed_Y_i,desX_i,desY_i);
			//DLL void FromxyHToBLH(ELLIP_PRJ Ellip_Prj,double x,double y,double h,double & B,double & L,double & H);
			break;

		default:
			LOGSTR("error:UNKNOWN TYPE");
			break;
		}

		//转到原始单位下
		desX_i_ori_unit=CDeuUnits::UnitToType(desX_i,szunittype_x);
		desY_i_ori_unit=CDeuUnits::UnitToType(desY_i,szunittype_y);
		desZ_i_ori_unit=CDeuUnits::UnitToType(desZ_i,szunittype_z);

		destX[i]=desX_i_ori_unit;
		destY[i]=desY_i_ori_unit;
		destZ[i]=desZ_i_ori_unit;

		desX_i=0;
		desY_i=0;
		desZ_i=0;
	}

	return ;
}

void CDeuTrans::get_DeuEllipse(CDeuEllipse& Val) const
{
	Val = m_ellipse;
}

void CDeuTrans::putref_DeuEllipse(const CDeuEllipse& newVal)
{
	m_ellipse = newVal;
	m_ellipse.get_Major(m_src_a);	
	m_ellipse.get_Flatening(m_src_f);
	m_ellipse.get_Centrol_Long(m_src_from_greenwich);
	m_ellipse.get_False_E(m_src_false_east);

	m_srcPJ = init_PJ(m_src_a,m_src_f);

	g_TransParams._src_a = m_src_a ;
	g_TransParams._src_f = m_src_f ;
	g_TransParams._src_false_east = m_src_false_east ;
	g_TransParams._src_from_greenwich = m_src_from_greenwich ;
	g_TransParams._srcPJ = m_srcPJ ;
}

void CDeuTrans::get_DeuUnits(CDeuUnits& Val) const
{
	Val = m_units;
}

void CDeuTrans::putref_DeuUnits(const CDeuUnits &newVal)
{
	m_units = newVal;

	CString									SrcUnitX = _T("");
	CString									SrcUnitY = _T("");
	CString									SrcUnitZ = _T("");
	CString									DesUnitX = _T("");
	CString									DesUnitY = _T("");
	CString									DesUnitZ = _T("");

	m_units.get_Unit_X(SrcUnitX);
	g_TransParams.SrcUnitX = SrcUnitX ;

	m_units.get_Unit_Y(SrcUnitY);
	g_TransParams.SrcUnitY = SrcUnitY ;

	m_units.get_Unit_Z(SrcUnitZ);
	g_TransParams.SrcUnitZ = SrcUnitZ ;

	m_units.get_Unit_desX(DesUnitX);
	g_TransParams.DesUnitX = DesUnitX ;

	m_units.get_Unit_desY(DesUnitY);
	g_TransParams.DesUnitY = DesUnitY ;

	m_units.get_Unit_desZ(DesUnitZ);
	g_TransParams.DesUnitZ = DesUnitZ ;
}

void CDeuTrans::get_DeuCoordType(CDeuCoordType &Val) const
{
	Val = m_coordtype;
}

void CDeuTrans::putref_DeuCoordType(const CDeuCoordType &newVal)
{
	short									iCoord_type = 0;
	short									iDesCoord_type = 0;

	m_coordtype = newVal;
	m_coordtype.get_CoordType(iCoord_type);	
	g_TransParams.SrcCoordType = iCoord_type ;

	m_coordtype.get_DestCoordType(iDesCoord_type);
	g_TransParams.DesCoordType = iDesCoord_type;
}

double CDeuTrans::GetRandomDetal(double min_ , double max_)
{
	double r = rand();
	double m = int(r) % 100 * 0.01;
	double range = max_ - min_;

	return  min_ + range * m ;	
}

/*支持标准坐标系范围验证,如广西，厦门*/
long CDeuTrans::CalculateParam(ULONG n, DOUBLE* x, DOUBLE* y, DOUBLE* z, DOUBLE* x_2, DOUBLE* y_2, DOUBLE* z_2, DOUBLE* _Param,ULONG* _np)
{
#define DEULIC	
#ifdef DEULIC
#ifdef NDEBUG
	double			     other_ext[10] = {0};
	DEUCheck		     dc(98);
	int					 iLen = 0;
	const unsigned char* pData = dc.PData(98, iLen);

	int ilen = strlen((const char*)pData);
	if (ilen > 0)
	{
		char		szData[128] = {0};
		memcpy(szData, pData, iLen*sizeof(char));

		const char* pDelim = ",";
		char* p = strtok(szData, pDelim);
		int i = 0;

		while(p)
		{
			const char* q = (const char*)p;
			other_ext[i] = atof(q);
			p = strtok(NULL, pDelim);
			if (other_ext[i] != 0)
			{
				++i;
			}
		}

		char szextent[128] = {0};
		sprintf(szextent,"lic范围:%f,%f,%f,%f,%f,%f,%f,%f",other_ext[0],other_ext[1],other_ext[2],other_ext[3],other_ext[4],other_ext[5],other_ext[6],other_ext[7]);\
			LOGSTR(szextent);

		//此处删除
		/*if (NULL != pData)
		{
		delete[] pData;
		pData = NULL;
		}*/

		//控制点数据范围
		OGREnvelope	extent; 
		extent.MaxX = x[0];
		extent.MinX = x[0];
		extent.MaxY = y[0];
		extent.MinY = y[0];

		for (int k = 0; k < n; k++)
		{
			extent.MaxX = extent.MaxX > x[k] ? extent.MaxX : x[k];
			extent.MinX = extent.MinX < x[k] ? extent.MinX : x[k];
			extent.MaxY = extent.MaxY > y[k] ? extent.MaxY : y[k];
			extent.MinY = extent.MinY < y[k] ? extent.MinY : y[k];
		}

		OGREnvelope ori_extent;
		OGREnvelope ori_extent1;

		ori_extent1.MaxX = extent.MaxX;
		ori_extent1.MinX = extent.MinX;
		ori_extent1.MaxY = extent.MaxY;
		ori_extent1.MinY = extent.MinY;

		short coordtype = 0;
		m_coordtype.get_CoordType(coordtype);

		if (coordtype == PLANE)
		{
			extent.MaxY -= m_src_false_east;
			extent.MinY -= m_src_false_east;

			Gauss_xy_bl(m_srcPJ,m_src_from_greenwich * DEG_TO_RAD ,extent.MinX,extent.MinY,ori_extent.MinX,ori_extent.MinY);
			Gauss_xy_bl(m_srcPJ,m_src_from_greenwich * DEG_TO_RAD ,extent.MaxX,extent.MaxY,ori_extent.MaxX,ori_extent.MaxY);

			ori_extent.MaxX *=RAD_TO_DEG;
			ori_extent.MinX *=RAD_TO_DEG;
			ori_extent.MaxY *=RAD_TO_DEG;
			ori_extent.MinY *=RAD_TO_DEG;

			//范围缩小，MaxX,MaxY缩小,MinX,MinY扩大%
			ori_extent.MaxX *=0.9;
			ori_extent.MinX *=1.1;
			ori_extent.MaxY *=0.9;
			ori_extent.MinY *=1.1;
		}
		else
		{
			ori_extent.MaxX = extent.MaxX ;
			ori_extent.MinX = extent.MinX ;
			ori_extent.MaxY = extent.MaxY ;
			ori_extent.MinY = extent.MinY ;
		}

		//权限范围
		if (i == 4)
		{
			OGREnvelope other_extent;
			other_extent.MinX = other_ext[0];
			other_extent.MinY = other_ext[1];
			other_extent.MaxX = other_ext[2];
			other_extent.MaxY = other_ext[3];
			int ret2 = other_extent.Contains(ori_extent);
			if (ret2 == 0)
			{
				LOGSTR("控制点范围错误。");
				LOG_EXTENT(	ori_extent1.MaxY,ori_extent1.MinY,ori_extent1.MaxX,ori_extent1.MinX ) ;

				return E_FAIL_PRIVILEGE_EXTENT;
			}
		}
		else if (i == 8) 
		{
			OGREnvelope other_extent;
			other_extent.MinX = other_ext[0];
			other_extent.MinY = other_ext[1];
			other_extent.MaxX = other_ext[2];
			other_extent.MaxY = other_ext[3];
			int ret2 = other_extent.Contains(ori_extent);

			//根据地方坐标系的特殊情况 再进行一次判断 判断逻辑如下 0-3 为大地坐标系的授权范围 4-7 为独立坐标系的授权范围
			other_extent.MinX = other_ext[4];
			other_extent.MinY = other_ext[5];
			other_extent.MaxX = other_ext[6];
			other_extent.MaxY = other_ext[7];
			int ret1 = other_extent.Contains(ori_extent1);

			if ((ret2 == 0) && (ret1 == 0))
			{
				LOGSTR("控制点范围错误。");
				LOG_EXTENT(	ori_extent1.MaxY,ori_extent1.MinY,ori_extent1.MaxX,ori_extent1.MinX ) ;

				return E_FAIL_PRIVILEGE_EXTENT;
			}
		}
		else
		{
			LOGSTR("lic文件中授权坐标数目有误。");
		}
	}
	else
	{
		LOGSTR("lic文件中没有授权坐标转换范围");
		return E_FAIL_PRIVILEGE_EXTENT;
	}
#endif
#endif

	//Y减去东假值
	for(int i = 0 ; i < n ; i++)
	{
		y[i]	-= m_src_false_east;
		y_2[i]	-= m_des_false_east;
	}

	//根据公式，决定计算哪种参数。
	int iTransModel = m_TransModel;
	double detal =  -0.00000000033;
	double detal2 = -0.000000000001;
	double detal3 = 0.000000000001;

	switch(iTransModel)
	{
	case MODEL_D3P7:
		//BLH to BLH
		//CalcuBLH7P(n,x,y,z,x_2,y_2,z_2,_Param,_np);
		//ComputeParams_3D7PBLH(n, x, y, z, x_2, y_2, z_2,  m_srcPJ, m_desPJ, _7Param );
		CalcuXYZ7P(n,x,y,z,x_2,y_2,z_2,_Param,_np);

		*_np = 9;	
		_Param[0] += detal2;
		_Param[1] += detal2;
		_Param[2] += detal2;
		_Param[3] += detal2;
		_Param[4] += detal2;
		_Param[5] += detal2;
		_Param[6] += detal2;
		_Param[7] = detal+600;
		_Param[8] = detal2;
		break;

	case MODEL_D2P4:
		//xy to xy h=0
		Calcuxyh4P(n,x,y,x_2,y_2,_Param,_np);
		//ComputeParams_2D4Pxy(n, x, y, x_2, y_2, _7Param );
		*_np = 4;	
		break;

	case MODEL_BURSA:
		//XYZ to XYZ
		CalcuXYZ7P(n,x,y,z,x_2,y_2,z_2,_Param,_np);
		//ComputeParams_3D7PBursa(n, x, y, z, x_2, y_2, z_2, _7Param );
		*_np = 7;	
		break;

	case MODEL_D2P7:
		//bl to bl H=0
		//CalcuBL7P(n,x,y,x_2,y_2,_Param,_np);
		//ComputeParams_2D7PBL(n, x, y, x_2, y_2, m_srcPJ, m_desPJ, _7Param );
		CalcuXYZ7P(n,x,y,z,x_2,y_2,z_2,_Param,_np);
		*_np = 9;	
		_Param[0] += detal3;
		_Param[1] += detal3;
		_Param[2] += detal3;
		_Param[3] += detal3;
		_Param[4] += detal3;
		_Param[5] += detal3;
		_Param[6] += detal3;
		_Param[7] = detal+578;
		_Param[8] = detal3;
		break;

	default:
		break;
	}

	//Y加上东假值
	for(int i = 0 ; i < n ; i++)
	{
		y[i]	+= m_src_false_east;
		y_2[i]	+= m_des_false_east;
	}

	return 0;
}

void CDeuTrans::CoordTransPoints(DOUBLE* _7Param,ULONG n, DOUBLE* oriX, DOUBLE* oriY, DOUBLE* oriZ, DOUBLE* desX, DOUBLE* desY, DOUBLE* desZ)
{
	m_Params = _7Param;

	//将7参数赋值给 g_TransParams yzg 2012-9-4 begin
	g_TransParams._Para = m_Params ;
	//end

	_coordtransf( 0,n,oriX,oriY,oriZ,desX,desY,desZ);
}

void CDeuTrans::CalculateResidual(ULONG n, DOUBLE* oriX, DOUBLE* oriY, DOUBLE* oriZ, DOUBLE* desX, DOUBLE* desY, DOUBLE* desZ, DOUBLE* resX, DOUBLE* resY, DOUBLE* resZ, DOUBLE* Residual)
{
	for( int i = 0; i < n; ++i )
	{
		double & rX = resX[i] = /*fabs*/( oriX[i] - desX[i] );
		double & rY = resY[i] = /*fabs*/( oriY[i] - desY[i] );
		double & rZ = resZ[i] = /*fabs*/( oriZ[i] - desZ[i] );

		Residual[i] = sqrt( rX * rX + rY * rY  );
	}
}

void CDeuTrans::get_DeuDestEllipse(CDeuEllipse& Val) const
{
	Val = m_des_ellipse;
}

void CDeuTrans::putref_DeuDestEllipse(const CDeuEllipse& newVal)
{
	m_des_ellipse = newVal;
	m_des_ellipse.get_Major(m_des_a);	
	m_des_ellipse.get_Flatening(m_des_f);
	m_des_ellipse.get_Centrol_Long(m_des_from_greenwich);
	m_des_ellipse.get_False_E(m_des_false_east);

	//m_des_false_east = 0;

	m_desPJ = init_PJ(m_des_a,m_des_f);

	g_TransParams._des_a = m_des_a ;
	g_TransParams._des_f = m_des_f ;
	g_TransParams._des_false_east = m_des_false_east ;
	g_TransParams._des_from_greenwich = m_des_from_greenwich ;
	g_TransParams._desPJ = m_desPJ;
}

HRESULT CDeuTrans::RegisterWnd(LONGLONG hwnd)
{
	m_hwnd=(HWND)hwnd;

	return S_OK;
}

void CDeuTrans::get_DeuSRS(CDeuSpatialReference** Val) const
{
	*Val = m_SRS;
}

void CDeuTrans::putref_DeuSRS(CDeuSpatialReference* newVal)
{
	m_SRS = newVal;
}

HRESULT	CDeuTrans::CoordTransSingleTable( const CString& FileName,UINT SrcConnId,  const CString&  outFileName,UINT DesConnId)
{
	//LOGSTR("=====================================================================");
	LOGSTR(":CoordTransSingleTable");

	//从连接池获得源数据源
	CDeuConn			*pConn;  
	OGROCIDataSource    *poDS;
	VARIANT             *p_Conn;
	m_ConnPool->get_Conn(SrcConnId,&p_Conn);

	pConn = (CDeuConn*)p_Conn;
	poDS = (OGROCIDataSource*)pConn->DataSource;

#if 1
	//从连接池获得目标数据源
	//const char *pszDriverNameOut = "ESRI Shapefile";
	CDeuConn	  *pConnOut;	
	OGRDataSource *poDSOut;
	VARIANT       *p_outConn;
	m_ConnPool->get_Conn(DesConnId,&p_outConn);

	pConnOut = (CDeuConn*)p_outConn;
	poDSOut = (OGRDataSource*)pConnOut->DataSource;
#endif

	//layer to feature
	int lyrCount=0;
	lyrCount=poDS->GetLayerCount();

	//获得源图层
	OGRLayer  *TmppoLayer = NULL;
	OGRLayer  *poLayer = NULL;
	for (int i=0;i<lyrCount;i++)
	{
		TmppoLayer=poDS->GetLayer(i);
		LPCSTR LyrName = TmppoLayer->GetLayerDefn()->GetName();

		LPCSTR szFileName ;
		USES_CONVERSION;
		szFileName = FileName.GetString();

		int ret = strcmp(LyrName,szFileName);
		if(ret == 0)
		{
			poLayer =( OGRLayer *) TmppoLayer;
			break;
		}
	}

	if (poLayer == NULL)
	{
		//没有该图层
		LOGSTR(":没有获得原图层");
		return S_OK;
	}

	LOGSTR(":获得原图层");
	LOG_START;
	//LOGSTR("LOG_START");
	RESET_COUNT;
	START_TIME;

#if 1
	//获得图层范围
	//virtual OGRErr      GetExtent(OGREnvelope *psExtent, int bForce = TRUE);
	OGREnvelope extent;
	poLayer->GetExtent(&extent);
#endif

	//输出
	//create a layer
	OGRLayer *poLayerOut = NULL;
	LPCSTR szOutLyrName;
	USES_CONVERSION;
	szOutLyrName = outFileName.GetString();

#if 0
	//单字节
	LPCSTR res_lyrname;//=(LPCSTR)(_tc.GetString());  
	int _len=_tc.GetLength();
	USES_CONVERSION;
	res_lyrname=W2A(_tc.LockBuffer());
#endif

#if 1
	//设置空间参考
	OGRSpatialReference* poRSR= poLayer->GetSpatialRef();

	if(poRSR)
	{
		//const char *pszPrj="Gauss_Kruger";
		//poRSR->SetProjection(pszPrj);
		//poRSR->SetGeogCS("GCS_Beijing_1980","D_Beijing_1980","DeuEll",123,456);
		if( m_SRS == NULL )
		{
			LOGSTR(":没有设置空间参考");
			return E_FAIL_SETRSR;
		}

		BOOL  vb_IsProj ;
		m_SRS->get_IsProject(vb_IsProj);
		if(vb_IsProj == TRUE)
		{
			CString Proj = _T("");
			m_SRS->get_Projection(Proj);
			poRSR->SetProjection((LPCSTR)_bstr_t(Proj.GetString()));
		}

		CString dfGeogName = _T("");
		CString dfDatum = _T("");
		CString dfEllipName = _T("");
		double dfSemiMajor;
		double dfInvFlattening;

		//if(poRSR->IsGeographic())
		//{
		m_SRS->get_GeogCS( dfGeogName , dfDatum, dfEllipName, dfSemiMajor, dfInvFlattening);
		poRSR->SetGeogCS((LPCSTR)_bstr_t(dfGeogName.GetString()),(LPCSTR)_bstr_t(dfDatum.GetString()),(LPCSTR)_bstr_t(dfEllipName.GetString()),dfSemiMajor,dfInvFlattening);
		//}

		CString dfLinearUnits;
		double fLinearUnits;
		char *szLinearUnits;

		fLinearUnits=poRSR->GetLinearUnits(&szLinearUnits);
		int ret_cmp= strcmp(szLinearUnits,"unknown");
		if(ret_cmp!=0)
		{
			m_SRS->get_LinearUnit(dfLinearUnits);			
			poRSR->SetLinearUnits((LPCSTR)_bstr_t(dfLinearUnits.GetString()),fLinearUnits);
		}

		CString dfAngularUnits;
		double fAngularUnit;
		char *szAngularUnit;

		fAngularUnit=poRSR->GetAngularUnits(&szAngularUnit);
		ret_cmp= strcmp(szAngularUnit,"unknown");
		if(ret_cmp!=0)
		{
			m_SRS->get_AngularUnit(dfAngularUnits);			
			poRSR->SetAngularUnits((LPCSTR)_bstr_t(dfAngularUnits.GetString()),fAngularUnit);
		}
	}
#endif

	LOGSTR(":设置空间参考完毕");

#if 1

	//#if 0
		//是否已经存在了
		int iOutLyrCount = poDSOut->GetLayerCount();
		OGRLayer * TmppoLayerOut = NULL;
		for (int i = 0 ; i < iOutLyrCount ;i++)
		{
			TmppoLayerOut = poDSOut->GetLayer(i);
			if (TmppoLayerOut == NULL)
			{
				continue ;
			}
			LPCSTR LyrName = TmppoLayerOut->GetLayerDefn()->GetName();

			int ret = strcmp(LyrName,szOutLyrName);
			if(ret == 0)
			{
				//存在了，就删除
				poDSOut->DeleteLayer(i);
				break;
			}
		}

		OGRFeatureDefn * poFeaDef=poLayer->GetLayerDefn();
		poLayer->ResetReading();
		OGRFeature * poFea0 = poLayer->GetNextFeature();
		OGRwkbGeometryType type=/*poFeaDef->GetGeomType();*/poFea0->GetGeometryRef()->getGeometryType();

		switch(type)
		{
		case wkbPoint25D:
			type = wkbPoint;
			break;

		case wkbMultiPoint25D:
			type =wkbMultiPoint;
			break;

		case wkbLineString25D:
			type = wkbLineString;
			break;

		case wkbPolygon25D:
			type = wkbPolygon;
			break;

		case wkbMultiLineString25D:
			type = wkbMultiLineString;
			break;

		case wkbMultiPolygon25D:
			type = wkbMultiPolygon;
			break;

		default:
			break;
		}
		poLayerOut=poDSOut->CreateLayer(szOutLyrName,poRSR,type);
	//#else
	//	//获得目标图层
	//	OGRLayer  *TmppoLayerOut = NULL;
	//	/*OGRLayer  *poLayerOut = NULL;*/

	//	int lyrOutCount=0;
	//	lyrOutCount=poDSOut->GetLayerCount();

	//	for (int i=0;i<lyrOutCount;i++)
	//	{
	//		TmppoLayerOut=poDSOut->GetLayer(i);
	//		LPCSTR LyrName = TmppoLayerOut->GetLayerDefn()->GetName();

	//		//LPCSTR szFileName ;
	//		//USES_CONVERSION;
	//		//szFileName = W2A(FileName);

	//		int ret = strcmp(LyrName,szOutLyrName);
	//		if(ret == 0)
	//		{
	//			poLayerOut =( OGRLayer *) TmppoLayerOut;
	//			break;
	//		}
	//	}
	//#endif

	LOG_START_HEADER(szOutLyrName);

	if(poLayerOut==NULL)
	{
		//创建输出图层失败
		//LOG_NO_TABLE;
		char * no_tab=(char*)malloc(100);
		strcpy(no_tab,szOutLyrName);
		LOG("没有找到表:",no_tab,100);
		free(no_tab);
		return S_OK;
	}

	LOGSTR(":获得目标图层");

	//#if 0
		//创建字段
		int _field_count= poFeaDef->GetFieldCount();
		for (int i=0;i<_field_count;i++)
		{
			OGRFieldDefn *poField=poFeaDef->GetFieldDefn(i);
			poLayerOut->CreateField(poField);
		}
	//#endif
	//debug
	//int _out_field_out= poLayerOut->GetLayerDefn()->GetFieldCount();
#endif		

	OGRFeature *poFeature;
	//OGRGeometry * poOldGeo;
	//OGRFeature *poFeatureOut;
	unsigned int _this_fea_count=poLayer->GetFeatureCount(1);

	LOGSTR(":获得总Feature个数");

	poLayer->ResetReading();
	for (unsigned long  i=0;i<_this_fea_count;i++)
	{	
		m_fea_done++;
		//计算时间
		//START_TIME;
#if 0
		if(m_fea_done>141090)
		{
			int u=0;	
		}
#endif
		unsigned int  Percent=(double)((double)m_fea_done/(double)_this_fea_count)*100;
		::SendMessage(m_hwnd,WM_PROGRESS,0,Percent);
		DEU_CALLBACK(WM_PROGRESS,0,Percent);

		poFeature = poLayer->GetNextFeature();

		//////////////////////////////////////////////////////////////////////////
		//END_TIME;
		//LOG_GET_NEXT_FEATURE;
		//START_TIME;
		//////////////////////////////////////////////////////////////////////////

		if (poFeature ==NULL)
		{
			m_fea_null_count++;
			continue;
		}

		int fea_FID = poFeature->GetFID();
		OGRGeometry *poGeometry=NULL;
		OGRLineString *poLine=NULL;
		OGRPoint *poPoint=NULL;
		OGRMultiPoint *poMultiPoint=NULL;
		OGRMultiLineString *poMultiLineString=NULL;
		OGRPolygon *poPolygon=NULL;
		OGRMultiPolygon *poMultiPolygon=NULL; 

		poGeometry = poFeature->GetGeometryRef();
		//each geometry trans its coordinate
		if(poGeometry == NULL)
		{
			m_geo_null_count++;
#if 0
			OGRErr _error =poLayerOut->CreateFeature( poFeature ) ;
			if( _error!= OGRERR_NONE )
			{
				printf( "Failed to create feature in shapefile.\n" );
				//return S_FALSE;
				m_fea_fail_count++;					
			}
#endif

			m_fea_create_count++;
			OGRFeature::DestroyFeature( poFeature );
			continue;
		}

		OGRwkbGeometryType type=poGeometry->getGeometryType();

		double _oldX;
		double _oldY;
		double _oldZ;

		double _newX;
		double _newY;
		double _newZ;

		int _pt_count=0;
		int _ex_count;
		OGRLinearRing* _ex_ring=NULL;
		int _in_ring_count=0;
		int _geo_count=0;

		int isClockwise = -1 ;

#if 0
		OGRFeature *poFeature_D;
		OGRPoint* poPoint_D;
		//OGRPoint* poFeature_D->GetGeometryRef();
#endif
		m_geo_done++;
		switch (type)
		{
		case wkbPoint:
		case wkbPoint25D:
			m_geo_point_count++;
			poPoint=(OGRPoint*)poGeometry;

			_oldY=poPoint->getX();//经度或东方向
			_oldX=poPoint->getY();//纬度或北方向
			_oldZ=poPoint->getZ();
#if 0
			if(_oldY>extent.MaxX||_oldY<extent.MinX||_oldX>extent.MaxY||_oldX<extent.MinY)
			{
				m_geo_ori_error_count++;

				char *geo_Ori_Error=(char*)malloc(100);
				int fea_FID=poFeature->GetFID();
				itoa(fea_FID,geo_Ori_Error,10);
				LOG("原始数据错误的点FID:",geo_Ori_Error,100);
				free(geo_Ori_Error);

				LOGSTR(ERR_CroodInfoError);

				OGRFeature::DestroyFeature( poFeature );
				continue;
				//poFeature->SetGeometry(NULL);
				break;
			}
#endif

			_coordtransf(fea_FID ,1,&_oldX,&_oldY,&_oldZ,&_newX,&_newY,&_newZ);

			if(poPoint->getDimension()==0)
			{
				poPoint->setX(_newY);
				poPoint->setY(_newX);					
			}
			else if(poPoint->getDimension()==1)
			{
				poPoint->setX(_newY);
				poPoint->setY(_newX);
				//poPoint->setZ(_newZ);
			}
			break;

		case wkbLineString:
		case wkbLineString25D:
			m_geo_line_count++;

			poLine=(OGRLineString *) poGeometry;
			_pt_count=poLine->getNumPoints();

			for (int i=0;i<_pt_count;i++)
			{

				_oldY=poLine->getX(i);//经度或东方向
				_oldX=poLine->getY(i);//纬度或北方向
				_oldZ=poLine->getZ(i);

#if 0
				if(_oldY>extent.MaxX||_oldY<extent.MinX||_oldX>extent.MaxY||_oldX<extent.MinY)
				{
					m_geo_ori_error_count++;

					char *geo_Ori_Error=(char*)malloc(100);
					int fea_FID=poFeature->GetFID();
					itoa(fea_FID,geo_Ori_Error,10);
					LOG("原始数据错误的线FID:",geo_Ori_Error,100);
					free(geo_Ori_Error);

					LOGSTR(ERR_CroodInfoError);

					OGRFeature::DestroyFeature( poFeature );
					continue;
					//poFeature->SetGeometry(NULL);
					break;
				}
#endif
				_coordtransf(fea_FID ,1,&_oldX,&_oldY,&_oldZ,&_newX,&_newY,&_newZ);
				if (poLine->getDimension()==0)
				{
					poLine->setPoint(i,_newY,_newX);
				}
				else if(poLine->getDimension()==1)
				{
					poLine->setPoint(i,_newY,_newX);
				}
				else if(poLine->getDimension()==2)
				{
					poLine->setPoint(i,_newY,_newX);
				}
			}
			//_coordtransf(_pt_count,ori_x,ori_y,ori_z,Newx,Newy,Newz);
			break;

		case wkbMultiPoint:
		case wkbMultiPoint25D:
			m_geo_multi_point_count++;

			poMultiPoint=(OGRMultiPoint *)poGeometry;
			poMultiPoint->getNumGeometries();
			_pt_count=poMultiPoint->getNumGeometries();

			for (int i=0;i<_pt_count;i++)
			{
				_oldY=((OGRPoint*)poMultiPoint->getGeometryRef(i))->getX();//经度或东方向
				_oldX=((OGRPoint*)poMultiPoint->getGeometryRef(i))->getY();//纬度或北方向
				_oldZ=((OGRPoint*)poMultiPoint->getGeometryRef(i))->getZ();
#if 0
				if(_oldY>extent.MaxX||_oldY<extent.MinX||_oldX>extent.MaxY||_oldX<extent.MinY)
				{
					m_geo_ori_error_count++;

					char *geo_Ori_Error=(char*)malloc(100);
					int fea_FID=poFeature->GetFID();
					itoa(fea_FID,geo_Ori_Error,10);
					LOG("原始数据错误的多点FID:",geo_Ori_Error,100);
					free(geo_Ori_Error);

					LOGSTR(ERR_CroodInfoError);

					OGRFeature::DestroyFeature( poFeature );
					continue;
					//poFeature->SetGeometry(NULL);
					break;
				}
#endif
				_coordtransf(fea_FID ,1,&_oldX,&_oldY,&_oldZ,&_newX,&_newY,&_newZ);

				OGRPoint* poPoint=((OGRPoint*)poMultiPoint->getGeometryRef(i));
				if(poPoint->getDimension()==0)
				{
					poPoint->setX(_newY);
					poPoint->setY(_newX);
				}
				else if(poPoint->getDimension()==1)
				{
					poPoint->setX(_newY);
					poPoint->setY(_newX);						
				}
			}
			//_coordtransf(_pt_count,ori_x,ori_y,ori_z,Newx,Newy,Newz);
			break;

		case wkbMultiLineString:
		case wkbMultiLineString25D:
			m_geo_multi_line_count++;

			poMultiLineString=(OGRMultiLineString *)poGeometry;
			_geo_count= poMultiLineString->getNumGeometries();

			for (int i=0;i<_geo_count;i++)
			{
				OGRLineString* poLineString=(OGRLineString*)poMultiLineString->getGeometryRef(i);
				if (poLineString != NULL)
				{
					_pt_count=poLineString->getNumPoints();
					for (int j=0;j<_pt_count;j++)
					{
						_oldY=poLineString->getX(j);//经度或东方向
						_oldX=poLineString->getY(j);//纬度或北方向
						_oldZ=poLineString->getZ(j);

#if 0
						if(_oldY>extent.MaxX||_oldY<extent.MinX||_oldX>extent.MaxY||_oldX<extent.MinY)
						{
							m_geo_ori_error_count++;

							char *geo_Ori_Error=(char*)malloc(100);
							int fea_FID=poFeature->GetFID();
							itoa(fea_FID,geo_Ori_Error,10);
							LOG("原始数据错误的多线FID:",geo_Ori_Error,100);
							free(geo_Ori_Error);

							LOGSTR(ERR_CroodInfoError);

							OGRFeature::DestroyFeature( poFeature );
							continue;
							//poFeature->SetGeometry(NULL);
							break;
						}
#endif
						_coordtransf(fea_FID ,1,&_oldX,&_oldY,&_oldZ,&_newX,&_newY,&_newZ);

						if(poLineString->getDimension()==0)
						{
							poLineString->setPoint(j,_newY,_newX);
						}
						else if(poLineString->getDimension()==1)
						{
							poLineString->setPoint(j,_newY,_newX);
						}
						else if(poLineString->getDimension()==2)
						{
							poLineString->setPoint(i,_newY,_newX);
						}
					}//j
				}
			}//i

			break;
		case wkbPolygon:
		case wkbPolygon25D:
			m_geo_polygon_count++;

			poPolygon=(OGRPolygon *)poGeometry;

			_in_ring_count=poPolygon->getNumInteriorRings();

			for (int i=0;i<_in_ring_count;i++)
			{
				OGRLinearRing* ring=poPolygon->getInteriorRing(i);
				int _ring_count=ring->getNumPoints();
				for (int j=0;j<_ring_count;j++)
				{
					_oldY= ring->getX(j);//经度或东方向
					_oldX= ring->getY(j);//纬度或北方向
					_oldZ= ring->getZ(j);

#if 0
					if(_oldY>extent.MaxX||_oldY<extent.MinX||_oldX>extent.MaxY||_oldX<extent.MinY)
					{
						m_geo_ori_error_count++;

						char *geo_Ori_Error=(char*)malloc(100);
						int fea_FID=poFeature->GetFID();
						itoa(fea_FID,geo_Ori_Error,10);
						LOG("原始数据错误的面FID:",geo_Ori_Error,100);
						free(geo_Ori_Error);

						LOGSTR(ERR_CroodInfoError);

						OGRFeature::DestroyFeature( poFeature );
						continue;
						//poFeature->SetGeometry(NULL);
						break;
					}
#endif
					_coordtransf(fea_FID ,1,&_oldX,&_oldY,&_oldZ,&_newX,&_newY,&_newZ);

					if(poPolygon->getDimension()==0)
					{
						ring->setPoint(j,_newY,_newX);
					}
					else if(poPolygon->getDimension()==1)
					{
						ring->setPoint(j,_newY,_newX);
					}	
					else if(poPolygon->getDimension()==2)
					{
						ring->setPoint(j,_newY,_newX);
					}		
				}
			}

			_ex_ring=poPolygon->getExteriorRing();

			isClockwise = _ex_ring->isClockwise();

			_ex_count=_ex_ring->getNumPoints();
			for (int i=0;i<_ex_count;i++)
			{
				_oldY= _ex_ring->getX(i);//经度或东方向
				_oldX= _ex_ring->getY(i);//纬度或北方向
				_oldZ= _ex_ring->getZ(i);
#if 0
				if(_oldY>extent.MaxX||_oldY<extent.MinX||_oldX>extent.MaxY||_oldX<extent.MinY)
				{
					m_geo_ori_error_count++;

					char *geo_Ori_Error=(char*)malloc(100);
					int fea_FID=poFeature->GetFID();
					itoa(fea_FID,geo_Ori_Error,10);
					LOG("原始数据错误的面FID:",geo_Ori_Error,100);
					free(geo_Ori_Error);

					LOGSTR(ERR_CroodInfoError);

					OGRFeature::DestroyFeature( poFeature );
					continue;
					//poFeature->SetGeometry(NULL);
					break;
				}
#endif
				_coordtransf(fea_FID ,1,&_oldX,&_oldY,&_oldZ,&_newX,&_newY,&_newZ);

				if(poPolygon->getDimension()==0)
				{
					_ex_ring->setPoint(i,_newY,_newX);
				}
				else if(poPolygon->getDimension()==1)
				{
					_ex_ring->setPoint(i,_newY,_newX);
				}	
				else if(poPolygon->getDimension()==2)
				{
					_ex_ring->setPoint(i,_newY,_newX);
				}	
			}
			break;
		case wkbMultiPolygon:
		case wkbMultiPolygon25D:
			m_geo_multi_polygon_count++;

			poMultiPolygon=(OGRMultiPolygon *)poGeometry;
			_geo_count=poMultiPolygon->getNumGeometries();

			for (int i=0;i<_geo_count;i++)
			{
				OGRPolygon* poPolygon=(OGRPolygon*)poMultiPolygon->getGeometryRef(i);

				//内环
				_in_ring_count=poPolygon->getNumInteriorRings();

				for (int i=0;i<_in_ring_count;i++)
				{
					OGRLinearRing* ring=poPolygon->getInteriorRing(i);
					int _ring_count=ring->getNumPoints();
					for (int j=0;j<_ring_count;j++)
					{
						_oldY= ring->getX(j);//经度或东方向
						_oldX= ring->getY(j);//纬度或北方向
						_oldZ= ring->getZ(j);
#if 0
						if(_oldY>extent.MaxX||_oldY<extent.MinX||_oldX>extent.MaxY||_oldX<extent.MinY)
						{
							m_geo_ori_error_count++;

							char *geo_Ori_Error=(char*)malloc(100);
							int fea_FID=poFeature->GetFID();
							itoa(fea_FID,geo_Ori_Error,10);
							LOG("原始数据错误的多面FID:",geo_Ori_Error,100);
							free(geo_Ori_Error);

							LOGSTR(ERR_CroodInfoError);

							OGRFeature::DestroyFeature( poFeature );
							continue;
							//poFeature->SetGeometry(NULL);
							break;
						}
#endif
						_coordtransf(fea_FID ,1,&_oldX,&_oldY,&_oldZ,&_newX,&_newY,&_newZ);

						if(poPolygon->getDimension()==0)
						{
							ring->setPoint(j,_newY,_newX);
						}
						else if(poPolygon->getDimension()==1)
						{
							ring->setPoint(j,_newY,_newX);
						}
						else if(poPolygon->getDimension()==2)
						{
							ring->setPoint(j,_newY,_newX);
						}
					}
				}

				//外环
				_ex_ring=poPolygon->getExteriorRing();

				isClockwise = _ex_ring->isClockwise();

				_ex_count=_ex_ring->getNumPoints();
				for (int i=0;i<_ex_count;i++)
				{
					_oldY= _ex_ring->getX(i);//经度或东方向
					_oldX= _ex_ring->getY(i);//纬度或北方向
					_oldZ= _ex_ring->getZ(i);

#if 0
					if(_oldY>extent.MaxX||_oldY<extent.MinX||_oldX>extent.MaxY||_oldX<extent.MinY)
					{
						m_geo_ori_error_count++;

						char *geo_Ori_Error=(char*)malloc(100);
						int fea_FID=poFeature->GetFID();
						itoa(fea_FID,geo_Ori_Error,10);
						LOG("原始数据错误的多面FID:",geo_Ori_Error,100);
						free(geo_Ori_Error);

						LOGSTR(ERR_CroodInfoError);

						OGRFeature::DestroyFeature( poFeature );
						continue;
						//poFeature->SetGeometry(NULL);
						break;
					}
#endif
					_coordtransf(fea_FID ,1,&_oldX,&_oldY,&_oldZ,&_newX,&_newY,&_newZ);

					if(poPolygon->getDimension()==0)
					{
						_ex_ring->setPoint(i,_newY,_newX);
					}
					else if(poPolygon->getDimension()==1)
					{
						_ex_ring->setPoint(i,_newY,_newX);
					}
					else if(poPolygon->getDimension()==2)
					{
						_ex_ring->setPoint(i,_newY,_newX);
					}
				}
			}

			break;
		case wkbGeometryCollection:
		case wkbGeometryCollection25D:
			m_error_count++;
			break;
		default:
			m_error_count++;
			break;
		}

		if (poFeature->GetGeometryRef() == NULL)
		{
			m_geo_null_count++;
			//poFeature->SetGeometry(poOldGeo);
		}

#if 1
		OGRErr _error =poLayerOut->CreateFeature( poFeature ) ;
		if( _error!= OGRERR_NONE )
		{
			LOGSTR(":Failed to create feature ." );
			//return S_FALSE;
			m_fea_fail_count++;
			continue;
		}
#else
		OGRErr _error =poLayerOut->SetFeature( poFeature ) ;
		if( _error!= OGRERR_NONE )
		{
			LOGSTR(":Failed to SetFeature ." );
			//return S_FALSE;
			m_fea_fail_count++;
			continue;
		}
#endif
		m_fea_create_count++;

		//OGRFeature::DestroyFeature( poFeatureOut );

		//alter by chenyong 2013-5-31
		_error = poDSOut->SyncToDisk();

		//优化性能gdal未编译，暂时屏蔽/////
		//if (i == _this_fea_count - 1)
		//{
		//	poLayerOut->SetCreateIndex(true);
		//}

		//_error = poLayerOut->SyncToDisk();
		//优化性能gdal未编译，暂时屏蔽/////

		OGRFeature::DestroyFeature( poFeature );

	}//for each feature

	LOG_FEA_DONE;
	LOG_FEA_NULL;
	LOG_FEA_CREATE;
	LOG_FEA_FAIL;
	LOG_GEO_PT;
	LOG_GEO_LINE;
	LOG_GEO_POLYGON;
	LOG_GEO_MPT;
	LOG_GEO_MLINE;
	LOG_GEO_MPOLYGON;
	LOG_GEO_NULL;
	LOG_ERR_OTHER;
	LOG_ORI_ERROR;
	LOG_GEO_DONE;

	END_TIME;
	LOG_USED_TIME;

	LOG_END;
	//LOGSTR("LOG_END")
	::SendMessage(m_hwnd,WM_PROGRESS,0,100);
	DEU_CALLBACK(WM_PROGRESS,0,100);

	return S_OK;
}

void CDeuTrans::get_ConnPool(CDeuConnPool** Val) const
{
	*Val = m_ConnPool;
}
	
void CDeuTrans::putref_ConnPool(CDeuConnPool* newVal)
{
	m_ConnPool = newVal;
}

HRESULT CDeuTrans::CoordTransFileEntry(const CString& SrcTab, const CString& SrcPath, const CString& SrcDriver, const CString& DesTab, const CString& DesPath, const CString& DesDriver, UINT Id)
{
	//CString								SrcSuf = _T("");
	//CString								DesSuf = _T("");
	CString									strSrcTab = _T("");
	CString									strDesTab = _T("");

	CString									strSrcDriverName = _T("");
	CString									strDesDriverName = _T("");

// 	if (SrcDriver == _T("ESRI Shapefile"))
// 	{
// 		SrcSuf = _T(".shp");
// 	}
// 	else if (SrcDriver == _T("MapInfo File"))
// 	{
// 		SrcSuf = _T(".mif");
// 	}
// 	else if (SrcDriver == _T("AVCE00"))
// 	{
// 		SrcSuf = _T(".e00");
// 	}
// 	else if (SrcDriver == _T("DXF"))
// 	{
// 		SrcSuf = _T(".dxf");
// 	}
// 	else if (SrcDriver == _T("Excel12"))
// 	{
// 		SrcSuf = _T(".xlsx");
// 	}
// 	else if (SrcDriver == _T("Excel11"))
// 	{
// 		SrcSuf = _T(".xls");
// 	}
// 
// 	if (DesDriver == _T("ESRI Shapefile"))
// 	{
// 		DesSuf = _T(".shp");
// 	}
// 	else if (DesDriver == _T("MapInfo File"))
// 	{
// 		DesSuf = _T(".mif");
// 	}
// 	else if (DesDriver == _T("AVCE00"))
// 	{
// 		DesSuf = _T(".e00");
// 	}
// 	else if (DesDriver == _T("DXF"))
// 	{
// 		DesSuf = _T(".dxf");
// 	}
// 	else if ( DesDriver == _T("Excel12") )
// 	{
// 		DesSuf = _T(".xlsx");
// 	}
// 	else if (DesDriver == _T("Excel11"))
// 	{
// 		DesSuf = _T(".xls");
// 	}


	//if ( DesDriver == _T("Coverage") )
	//{	
		
        strSrcTab = SrcPath + _T("\\") + SrcTab ;
        strDesTab = DesPath + _T("\\") + DesTab ;
	//}
    //else
	//{
	//	strSrcTab = SrcPath + _T("\\") + SrcTab + SrcSuf;
	//	strDesTab = DesPath + _T("\\") + DesTab + DesSuf;
	//}

	//保持代码兼容性
	if (SrcDriver.Find(_T("Excel")) != -1)
	{
		strSrcDriverName = _T("Excel");
		strDesDriverName = _T("Excel");
	}
	else
	{
		strSrcDriverName = SrcDriver;
		strDesDriverName = DesDriver;
	}
	
	return CoordTransSingleFile(strSrcTab,strSrcDriverName,strDesTab,strDesDriverName,Id);
}

/*
【补充功能逻辑】：
	1. 创建克隆两张与原表结构一致的空表.[修改blob字段为varchar(2000)]；并使用oci拷贝原表到中间表A;
	2. 使用gdal 转数据到中间表B;
	3. 使用oci 将中间表B的数据转到目标表；注意：varchar数据到blob数据的转换
																	--add by hushichen 2011-07-08
*/
HRESULT CDeuTrans::CoordTransDBEntry(const CString& SrcTab, const CString& SrcPath, const CString& SrcDriver, const CString& DesTab, const CString& DesPath, const CString& DesDriver)
{
	LOGSTR(":CoordTransDBEntry");

	_bstr_t bstrSrcPath(SrcPath);
	_bstr_t bstrDesPath(DesPath);
	_bstr_t bstrConnString;

	//这段代码应该写在连接池中，实现连接池的透明操作，需要后期优化。
	//连接数据库
	//连接是否在连接池，如在获得连接，如不在，创建新连接到连接池
	long	pCount = 0;
	m_ConnPool->get_ConnCount(pCount);
	//LOG("连接数:",":",pCount);
	
	long SrcDBId = -1;
	long DesDBId = -1;
	CString	szConnString = _T("");

	for (int i = 0;i < pCount; i++ )
	{
		CDeuConn* pConn;
		VARIANT*  p_Conn;

		m_ConnPool->get_Conn( i, &p_Conn );
		pConn = (CDeuConn*) p_Conn;
		szConnString = pConn->ConnString;
		
		//bstrConnString =  _com_util::ConvertStringToBSTR(szConnString);
		//int ret1 = (bstrSrcPath==bstrConnString);

		if (SrcPath == szConnString)
		{
			SrcDBId = pConn->ConnId;	
		}

		//int ret2 = bstrDesPath._Compare(bstrConnString);

		if (DesPath == szConnString)
		{
			DesDBId = pConn->ConnId;
		}
	}

	//LOGSTR(":查找连接结束");

	if ( SrcDBId < 0 )
	{
		//无连接
		m_ConnPool->Connect(SrcPath , SrcDBId);
	}
     
	//LOGSTR(":SrcDBId");

#if 1
	if ( DesDBId < 0 )
	{
		m_ConnPool->Connect(DesPath , DesDBId);
	}
#endif
	//LOGSTR(":DesDBId");

	//单表坐标转换
	CoordTransSingleTable( SrcTab , SrcDBId ,DesTab , DesDBId );

	return S_OK;
}

HRESULT CDeuTrans::CoordTransDBEntryForBLOB(const CString& SrcTableaName, const CString& SrcConnLink, const CString& SrcUser,  const CString& SrcPwd, const CString& DestTableaName, const CString& DestConnLink, const CString& DestUser,  const CString& DestPwd)
{
	LOGSTR(":CoordTransDBEntryForBLOB");

	char									szSrcConnLink[255] = {0};
	char									szDestConnLink[255] = {0};

	strcpy(szSrcConnLink, SrcConnLink.GetString());
	strcpy(szDestConnLink, DestConnLink.GetString());

	LOGSTR(szSrcConnLink);
	LOGSTR(szDestConnLink);

	//SrcConnLink.ReleaseBuffer();
	//DestConnLink.ReleaseBuffer();

	char  szConnSrc[200];
	char  szConnDes[200];
	memset(szConnSrc,0,sizeof(szConnSrc));
	memset(szConnDes,0,sizeof(szConnDes));
	sprintf(szConnSrc , "%s",szSrcConnLink+4);
	sprintf(szConnDes , "%s",szDestConnLink+4);

	//LOGSTR(szConnSrc);
	//LOGSTR(szConnDes);

	bool IsExistColumn=false;
	char szSQL[1000];
	char szTmp[50];

	//初始连接对象
	otl_connect::otl_initialize(); // initialize OCI environment

	LOGSTR(":初始化连接成功");
	LOG_START;
	START_TIME;

	try
	{
		//:passistlabel
		dbsrc.rlogon(szConnSrc); // connect to Oracle
		dbdes.rlogon(szConnDes);	
		//LOGSTR("rlogon success");

		//检查是否包含注记字段
		sprintf(szSQL, "select column_name from all_tab_columns where table_name = upper('%s')", (char*)(_bstr_t)SrcTableaName);

		otl_stream i(50,   // buffer size
					 szSQL,// SELECT statement
			         dbsrc // connect object
					); 

		while(!i.eof())
		{ 
			// while not end-of-data
			i>>szTmp;
			if(strcmp(szTmp, "ANNOTATION") == 0)
			{
				IsExistColumn = true;
				break;
			}
		}

		if(!IsExistColumn) 
		{
			dbsrc.logoff(); // disconnect from Oracle
			dbdes.logoff(); // disconnect from Oracle
			END_TIME;
			LOG_USED_TIME;
			LOG_END;
			LOGSTR("=====================================================================");
			return S_OK;
		}

		//LOGSTR("ANNOTATION FINDED!");
		//查源表 Oid和Annotation
		sprintf(szSQL, "select t.OID, t.ANNOTATION from %s t", (char*)(_bstr_t)SrcTableaName);

		otl_stream i_src(50,    // buffer size
						 szSQL, // SELECT statement
						 dbsrc  // connect object
						);

		int oid_;
		otl_lob_stream lob_;
		otl_long_string lob_str(2000);
		//long lDataSize;
		_variant_t varBLOB;
		int n=0;

		while(!i_src.eof())
		{ 
			// while not end-of-data
			i_src>>oid_;
			i_src>>lob_;

			//查目标表
			memset(szSQL, 0, sizeof(szSQL));
			sprintf(szSQL, "select t.OID, t.ANNOTATION from %s t where OID=%d", (char*)(_bstr_t)DestTableaName, oid_);

			otl_stream i_des(50, // buffer size
				             szSQL,// SELECT statement
				             dbdes // connect object
							);

			int oid_des;
			otl_lob_stream lob_des;
			while(!i_des.eof())
			{
				i_des>>oid_des;
				i_des>>lob_des;

				//读目标表的lob字段
				lob_>>lob_str;

				long PtNum = 0;
				long PtNumPtr = (long)(lob_str.v+8*sizeof(long)+10*sizeof(double)+5*sizeof(short));
				PtNum = *(long*)(PtNumPtr);

				double *orix = new double[PtNum];
				double *oriy = new double[PtNum];
				double *oriz = new double[PtNum];
				double *desx = new double[PtNum];
				double *desy = new double[PtNum];
				double *desz = new double[PtNum];

				memset(orix,0,sizeof(double)*PtNum);
				memset(oriy,0,sizeof(double)*PtNum);
				memset(oriz,0,sizeof(double)*PtNum);
				memset(desx,0,sizeof(double)*PtNum);
				memset(desy,0,sizeof(double)*PtNum);
				memset(desz,0,sizeof(double)*PtNum);

				long PtStart = PtNumPtr+sizeof(long);
				for(int i = 0 ; i < PtNum ;i++)
				{
					oriy[i] = *(double*)(PtStart+2*i*sizeof(double));    //经度
					orix[i] = *(double*)(PtStart+(2*i+1)*sizeof(double));//纬度

					_coordtransf( 0 ,PtNum, &orix[i], &oriy[i], &oriz[i],&desx[i],&desy[i],&desz[i]);

					//坐标到chunk
					memcpy( (void*)(PtStart + 2*i*sizeof(double)) , &desy[i] , sizeof(double) );
					memcpy( (void*)(PtStart + (2*i+1)*sizeof(double)), &desx[i] , sizeof(double) );
				}

				//chunk写会lob
				memset(szSQL, 0, sizeof(szSQL));
				sprintf(szSQL, "begin "
					"  select ANNOTATION into :ANNOTATION<blob,in> "
					"  from %s "
					"  where oid=:oid<int,in> "
					"  for update; "
					"end;",(char*)(_bstr_t)DestTableaName);

				otl_stream oUpdate(1,    // buffer size has to be set to 1 for operations with LOBs
								   szSQL,// SQL statement
								   dbdes // connect object
								  );

				otl_lob_stream lob_update;

				oUpdate.set_commit(0);
				oUpdate<<lob_update;
				oUpdate<<oid_;

				int lob_len = lob_str.len();
				lob_update.set_len(lob_len);
				lob_update<<lob_str;
				lob_update.close();
				dbdes.commit(); 
			}//each in i_des
		}// each in i_src
	}//end try 
	catch(otl_exception& p)
	{ 
		// intercept OTL exceptions
		LOGSTR("blob exception");
		LOGSTR((char*)p.msg); // print out error message
		LOGSTR(p.stm_text);   // print out SQL that caused the error
		LOGSTR(p.var_info);   // print out the variable that caused the error
	}

	dbsrc.logoff(); // disconnect from Oracle
	dbdes.logoff(); // disconnect from Oracle

	END_TIME;
	LOG_USED_TIME;
	LOG_END;
	LOGSTR("=====================================================================");

	return S_OK;
}

HRESULT CDeuTrans::CalcuBLH7P(ULONG n, DOUBLE* x, DOUBLE* y, DOUBLE* z, DOUBLE* x2, DOUBLE* y2, DOUBLE* z2, DOUBLE* _7Param,ULONG* _np)
{
	*_np	= 9;

	//如果不是经纬度，先换算成经纬度
	//调用DLL,从原始坐标类型转换到空间直角坐标类型
	short coordtype=0;
	m_coordtype.get_CtrlPtCoordType(coordtype);

	CString szunittype_x = _T("");
	m_units.get_Unit_X(szunittype_x);

	CString szunittype_y =_T("");
	m_units.get_Unit_Y(szunittype_y);

	CString szunittype_z;
	m_units.get_Unit_Z(szunittype_z);

	CString szunittype_des_x;
	m_units.get_Unit_desX(szunittype_des_x);

	CString szunittype_des_y;
	m_units.get_Unit_desY(szunittype_des_y);

	CString szunittype_des_z;
	m_units.get_Unit_desZ(szunittype_des_z);

	//标准单位下
	double* unit_x=new double[n];
	double* unit_y=new double[n];
	double* unit_z=z;

	double* unit_x_2=new double[n];
	double* unit_y_2=new double[n];
	double* unit_z_2=z2;

	switch (coordtype)
	{
	case GEODETIC:
		//度转弧度
		for (int i = 0; i<n ;i++)
		{
			unit_x[i] = x[i] * DEG_TO_RAD ;
			unit_y[i] = y[i] * DEG_TO_RAD ;
			//unit_z[i] = z[i] * DEG_TO_RAD ;

			unit_x_2[i] = x2[i] * DEG_TO_RAD ;
			unit_y_2[i] = y2[i] * DEG_TO_RAD ;
			//unit_z_2[i] = z2[i] * DEG_TO_RAD ;
		}
		break;

	case GEOCENTRIC:
		break;

	case PLANE:
		for (int i = 0 ;i < n ; i++ )
		{					
			Gauss_xy_bl(m_srcPJ,m_src_from_greenwich * DEG_TO_RAD ,x[i],y[i],unit_x[i],unit_y[i]);
			Gauss_xy_bl(m_desPJ,m_des_from_greenwich * DEG_TO_RAD ,x2[i],y2[i],unit_x_2[i],unit_y_2[i]);
		}
		break;

	default:
		break;
	}

	ComputeParams_3D7PBLH( n, unit_x, unit_y, unit_z, unit_x_2, unit_y_2, unit_z_2,m_srcPJ,m_desPJ, _7Param);
	/*TRACE("\n------七参数--------\n");
	for (int t2=0; t2<7; t2++)
	{
		TRACE("%.6f ",_7Param[t2]);		
	}
	TRACE("\n");*/

	return S_OK;
}
	
HRESULT CDeuTrans::Calcuxyh4P(ULONG n, DOUBLE* x, DOUBLE* y, DOUBLE* x2, DOUBLE* y2, DOUBLE* _4Param,ULONG* _np)
{
	*_np	= 4;
	
	//判断控制点坐标类型,将控制点转到空间直角坐标
	double* unit_x=new double[n];
	double* unit_y=new double[n];
	double* unit_z=new double[n];

	double* unit_x_2=new double[n];
	double* unit_y_2=new double[n];
	double* unit_z_2=new double[n];

	double* geo_x=new double[n];
	double* geo_y=new double[n];
	double* geo_z=new double[n];

	double* geo_x_2=new double[n];
	double* geo_y_2=new double[n];
	double* geo_z_2=new double[n];

	//获得控制点坐标类型
	short _coord_type=0;
	m_coordtype.get_CtrlPtCoordType(_coord_type);

	CString szunittype_x;
	m_units.get_Unit_X(szunittype_x);

	CString szunittype_y;
	m_units.get_Unit_Y(szunittype_y);

	CString szunittype_z;
	m_units.get_Unit_Z(szunittype_z);

	CString szunittype_des_x;
	m_units.get_Unit_desX(szunittype_des_x);

	CString szunittype_des_y;
	m_units.get_Unit_desY(szunittype_des_y);

	CString szunittype_des_z;
	m_units.get_Unit_desZ(szunittype_des_z);

	for (int i=0;i<n;i++)
	{
		//转到弧度或米
		unit_x[i]	=	CDeuUnits::TypeToUnit(x[i],szunittype_x);
		unit_y[i]	=	CDeuUnits::TypeToUnit(y[i],szunittype_y);

		unit_x_2[i]	=	CDeuUnits::TypeToUnit(x2[i],szunittype_x);
		unit_y_2[i]	=	CDeuUnits::TypeToUnit(y2[i],szunittype_y);

		switch (_coord_type)
		{
		case  GEODETIC://大地
			Gauss_bl_xy(m_srcPJ,m_src_from_greenwich * DEG_TO_RAD,unit_x[i],unit_y[i],geo_x[i],geo_y[i]);
			Gauss_bl_xy(m_desPJ,m_des_from_greenwich * DEG_TO_RAD,unit_x_2[i],unit_y_2[i],geo_x_2[i],geo_y_2[i]);
			break;

		case  GEOCENTRIC:
			break;

		case  PLANE://平面
			//DLL void FromxyHToBLH(ELLIP_PRJ Ellip_Prj,double x,double y,double h,double & B,double & L,double & H);
			break;

		default:
			//大地
			//FromBLHToXYZ(m_ell_prj,unitX_i,unitY_i,unitZ_i,geo_X_i,geo_Y_i,geo_Z_i);
			LOGSTR("error:UNKNOWN TYPE");
			break;
		}
	}

	ComputeParams_2D4Pxy( n, x, y, x2, y2, _4Param);
	/*TRACE("\n------控制点对--------\n");
	for (int t1=0; t1<n; t1++)
	{
		TRACE("%.10f ",geo_x[t1]);
		TRACE("%.10f ",geo_y[t1]);
		TRACE("%.10f ",geo_z[t1]);
		TRACE("%.10f ",geo_x_2[t1]);
		TRACE("%.10f ",geo_y_2[t1]);
		TRACE("%.10f ",geo_z_2[t1]);

		TRACE("\n");
	}	
	TRACE("\n------四参数--------\n");
	for (int t2=0; t2<4; t2++)
	{
		TRACE("%.18f ",_4Param[t2]);		
	}
	TRACE("\n");*/

	return S_OK;
}

HRESULT CDeuTrans::CalcuXYZ7P(ULONG n, DOUBLE* x, DOUBLE* y, DOUBLE* z, DOUBLE* x2, DOUBLE* y2, DOUBLE* z2, DOUBLE* _7Param,ULONG* _np)
{
	*_np	= 7;
	
	//判断控制点坐标类型,将控制点转到空间直角坐标
	double* unit_x=new double[n];
	double* unit_y=new double[n];
	double* unit_z=new double[n];

	double* unit_x_2=new double[n];
	double* unit_y_2=new double[n];
	double* unit_z_2=new double[n];

	double* geo_x=new double[n];
	double* geo_y=new double[n];
	double* geo_z=new double[n];

	double* geo_x_2=new double[n];
	double* geo_y_2=new double[n];
	double* geo_z_2=new double[n];

	//获得控制点坐标类型
	short _coord_type=0;
	m_coordtype.get_CtrlPtCoordType(_coord_type);

	CString szunittype_x;
	m_units.get_Unit_X(szunittype_x);

	CString szunittype_y;
	m_units.get_Unit_Y(szunittype_y);

	CString szunittype_z;
	m_units.get_Unit_Z(szunittype_z);

	CString szunittype_des_x;
	m_units.get_Unit_desX(szunittype_des_x);

	CString szunittype_des_y;
	m_units.get_Unit_desY(szunittype_des_y);

	CString szunittype_des_z;
	m_units.get_Unit_desZ(szunittype_des_z);

	for (int i=0;i<n;i++)
	{
		//转到弧度或米
		unit_x[i]	=	CDeuUnits::TypeToUnit(x[i],szunittype_x);
		unit_y[i]	=	CDeuUnits::TypeToUnit(y[i],szunittype_y);
		unit_z[i]	=	CDeuUnits::TypeToUnit(z[i],szunittype_z);

		unit_x_2[i]	=	CDeuUnits::TypeToUnit(x2[i],szunittype_x);
		unit_y_2[i]	=	CDeuUnits::TypeToUnit(y2[i],szunittype_y);
		unit_z_2[i]	=	CDeuUnits::TypeToUnit(z2[i],szunittype_z);

		switch (_coord_type)
		{
		case  GEODETIC://大地
			geo_x[i] = unit_x[i];
			geo_y[i] = unit_y[i];
			geo_z[i] = unit_z[i];

			geo_x_2[i]	= unit_x_2[i];
			geo_y_2[i]	= unit_y_2[i];
			geo_z_2[i]	= unit_z_2[i];

			pj_geodetic_to_geocentric(m_src_a,m_src_f,1,0,&geo_x[i],&geo_y[i],&geo_z[i]);
			pj_geodetic_to_geocentric(m_des_a,m_des_f,1,0,&geo_x_2[i],&geo_y_2[i],&geo_z_2[i]);
			break;

		case  GEOCENTRIC:
			break;

		case  PLANE://平面
			Gauss_xy_bl(m_srcPJ,m_src_from_greenwich * DEG_TO_RAD , unit_x[i],unit_y[i],geo_x[i],geo_y[i]);

			geo_z = unit_z;

			pj_geodetic_to_geocentric(m_src_a,m_src_f,1,0,&geo_x[i],&geo_y[i],&geo_z[i]);

			Gauss_xy_bl(m_desPJ,m_des_from_greenwich * DEG_TO_RAD ,unit_x_2[i],unit_y_2[i],geo_x_2[i],geo_y_2[i]);

			geo_z_2 = unit_z_2;

			pj_geodetic_to_geocentric(m_des_a,m_des_f,1,0,&geo_x_2[i],&geo_y_2[i],&geo_z_2[i]);

			//geo_Z_i = unitZ_i;

			//DLL void FromxyHToBLH(ELLIP_PRJ Ellip_Prj,double x,double y,double h,double & B,double & L,double & H);
			break;

		default:
			//大地
			//FromBLHToXYZ(m_ell_prj,unitX_i,unitY_i,unitZ_i,geo_X_i,geo_Y_i,geo_Z_i);
			LOGSTR("error:UNKNOWN TYPE");
			break;
		}
	}

	ComputeParams_3D7PBursa( n, geo_x, geo_y, geo_z, geo_x_2, geo_y_2, geo_z_2, _7Param);

	/*TRACE("\n------控制点对--------\n");
	for (int t1=0; t1<n; t1++)
	{
		TRACE("%.10f ",geo_x[t1]);
		TRACE("%.10f ",geo_y[t1]);
		TRACE("%.10f ",geo_z[t1]);
		TRACE("%.10f ",geo_x_2[t1]);
		TRACE("%.10f ",geo_y_2[t1]);
		TRACE("%.10f ",geo_z_2[t1]);

		TRACE("\n");
	}	
	TRACE("\n------七参数--------\n");
	for (int t2=0; t2<7; t2++)
	{
		TRACE("%.18f ",_7Param[t2]);		
	}
	TRACE("\n");*/

	return S_OK;
}

HRESULT CDeuTrans::CalcuBL7P(ULONG n, DOUBLE* x, DOUBLE* y, DOUBLE* x2, DOUBLE* y2,DOUBLE* _7Param,ULONG* _np)
{
	*_np	= 9;

	//如果不是经纬度，先换算成经纬度
	//调用DLL,从原始坐标类型转换到空间直角坐标类型
	short coordtype=0;
	m_coordtype.get_CtrlPtCoordType(coordtype);

	CString szunittype_x;
	m_units.get_Unit_X(szunittype_x);

	CString szunittype_y;
	m_units.get_Unit_Y(szunittype_y);

	CString szunittype_z;
	m_units.get_Unit_Z(szunittype_z);

	CString szunittype_des_x;
	m_units.get_Unit_desX(szunittype_des_x);

	CString szunittype_des_y;
	m_units.get_Unit_desY(szunittype_des_y);

	CString szunittype_des_z;
	m_units.get_Unit_desZ(szunittype_des_z);

	//标准单位下
	double* unit_x=new double[n];
	double* unit_y=new double[n];
	//double* unit_z=new double[n];

	double* unit_x_2=new double[n];
	double* unit_y_2=new double[n];
	//double* unit_z_2=new double[n];

	switch (coordtype)
	{
	case GEODETIC:
		//度转弧度
		for (int i = 0; i<n ;i++)
		{
			unit_x[i] = x[i] * DEG_TO_RAD ;
			unit_y[i] = y[i] * DEG_TO_RAD ;
			//unit_z[i] = z[i] * DEG_TO_RAD ;

			unit_x_2[i] = x2[i] * DEG_TO_RAD ;
			unit_y_2[i] = y2[i] * DEG_TO_RAD ;
			//unit_z_2[i] = z2[i] * DEG_TO_RAD ;
		}
		break;

	case GEOCENTRIC:
		break;

	case PLANE:
		for (int i = 0 ;i < n ; i++ )
		{					
			Gauss_xy_bl(m_srcPJ,m_src_from_greenwich * DEG_TO_RAD ,x[i],y[i],unit_x[i],unit_y[i]);
			Gauss_xy_bl(m_srcPJ,m_src_from_greenwich * DEG_TO_RAD ,x2[i],y2[i],unit_x_2[i],unit_y_2[i]);
		}
		break;

	default:
		break;
	}

	ComputeParams_2D7PBL(n,unit_x,unit_y,unit_x_2,unit_y_2,m_srcPJ,m_desPJ,_7Param);

	/*TRACE("\n------七参数--------\n");
	for (int t2=0; t2<7; t2++)
	{
		TRACE("%.6f ",_7Param[t2]);		
	}
	TRACE("\n");*/

	return S_OK;
}

void CDeuTrans::get_TransModel(short& Val) const
{
	Val = m_TransModel;
}

void CDeuTrans::put_TransModel(short newVal)
{
	m_TransModel = newVal;
	g_TransParams._TransModel = m_TransModel ;
}

void CDeuTrans::get_Param(double** Val) const
{
	*Val = m_Params;
}
	
void CDeuTrans::putref_Param(double* newVal)
{
	m_Params = newVal;

	g_TransParams._Para = m_Params ;
}
	
void CDeuTrans::get_Excel(VARIANT& Val) const
{
	Val = g_TransParams._Excel;
}
	
void CDeuTrans::putref_Excel(const VARIANT& newVal) const
{
	g_TransParams._Excel = newVal;
}

void CDeuTrans::get_Proid(CString& Val) const
{
	Val = g_TransParams.SrcProId;
}	

void CDeuTrans::put_Proid(const CString& newVal)
{
	g_TransParams.SrcProId = newVal;
}

void CDeuTrans::get_Pwd(CString& Val) const
{
	Val = g_TransParams.SrcPwd;
}

void CDeuTrans::put_Pwd(const CString& newVal)
{
	g_TransParams.SrcPwd = newVal;
}

void CDeuTrans::get_Proname(CString& Val) const
{
	Val = g_TransParams.SrcPwd;
}
	
void CDeuTrans::put_Proname(const CString& newVal)
{
	g_TransParams.SrcPwd = newVal;
}

HRESULT CDeuTrans::CoordTransGeometry(DOUBLE* Params, VARIANT oriGeo, VARIANT* desGeo)
{
	SDO_geometry  *geo = (SDO_geometry*)  oriGeo.byref;
	SDO_geometry  *outGeo = CloneGeometry(*geo) ;

	(*desGeo).byref = outGeo ;
	
	if(!geo->ind.pointNull_)
	{
		double x = geo->obj.point_.x;
		double y = geo->obj.point_.y;
		double z = geo->obj.point_.z;

		double dx = 0;
		double dy = 0;
		double dz = 0;
		
		CoordTransPoints(Params,1,&x,&y,&z,&dx,&dy,&dz);
		
		outGeo->obj.point_.x = dx ;
		outGeo->obj.point_.y = dy ;
		outGeo->obj.point_.z = dz ;	
	}

	int igtype = geo->obj.gtype_ / 1000;
	int queSize;
	if(igtype != 3)
	{
		queSize = geo->obj.ordinatesSize;
		queSize /= 2;

		double x = 0;
		double y = 0;
		double z = 0;
		double desX = 0;
		double desY = 0;
		double desZ = 0;
		
		for (int i = 0; i < queSize ;i++ )
		{
			x=geo->obj.ordinatesQueue_[2*i];
			y=geo->obj.ordinatesQueue_[2*i+1];

			CoordTransPoints(Params,1,&x,&y,&z,&desX,&desY,&desZ);
						
			outGeo->obj.ordinatesQueue_[2*i] = desX;
			outGeo->obj.ordinatesQueue_[2*i+1] = desY;
		}
	}

	return S_OK;
}

HRESULT CDeuTrans::CoordTransFileExEntry(const CString& SrcTab, const CString& SrcPath, const CString& SrcDriver, const CString& DesTab, const CString& DesPath, const CString& DesDriver, UINT Id, VARIANT vFormat )
{
	CString									SrcSuf = _T("");
	CString									DesSuf = _T("");
	CString									bstrSrcTab = _T("");
	CString									bstrDesTab = _T("");

	if ( SrcDriver == _T("EXCEL11") )
	{
		//2003
		SrcSuf = _T(".xls");
	}
	else if ( SrcDriver == _T("EXCEL12") )
	{
		//2007
		SrcSuf = _T(".xlsx");
	}
	else if ( SrcDriver == _T("EXCEL14") )
	{
		//2010
		SrcSuf = _T(".xlsx");
	}

	if ( DesDriver == _T("EXCEL11") )
	{
		//2003
		DesSuf = _T(".xls");
	}
	else if ( DesDriver == _T("EXCEL12") )
	{
		//2007
		DesSuf = _T(".xlsx");
	}
	else if ( DesDriver == _T("EXCEL14") )
	{
		//2010
		DesSuf = _T(".xlsx");
	}

	bstrSrcTab = SrcPath +_T("\\") + SrcTab + SrcSuf;
	bstrDesTab = DesPath +_T("\\") + DesTab + DesSuf;

	return CoordTransSingleFileExcel(bstrSrcTab,SrcDriver,bstrDesTab,DesDriver , vFormat ,Id );
}

/*void	CDeuTrans::PutStringCellVal(Excel::_WorksheetPtr _sheet, char * szRowCol , double dbVal)
{
	if(szRowCol == NULL )
		return ;

	//char * szVal = new char[100];
	//sprintf( szVal , "%.15lf" , dbVal );
	_variant_t _tVal(dbVal);

	Excel::RangePtr _rx;
	_rx = _sheet->GetRange(szRowCol);
	
	//_rx->PutValue( _tVal , xlRangeValueDefault);
	_rx->NumberFormatLocal = "0.000000000000000";
	_rx->PutItem(1,1,_tVal);

	char * szLog = new char[200];
	sprintf( szLog , "CELL= %s , VALUE = %s " , szRowCol ,(LPSTR)_bstr_t(_tVal) );
	LOGSTR(szLog);
	delete szLog;
	return ;
}*/

/*void	CDeuTrans::PutStringCellVal(Excel::_WorksheetPtr _sheet, long irow , long icol , double dbVal)
{
	if(icol<1 || irow<1)
		return ;

	//char * szVal = new char[100];
	//sprintf( szVal , "%.15lf" , dbVal );
	_variant_t _tVal(dbVal);

	char Letter[100];
	Num2Letter( irow ,icol ,Letter );

	Excel::RangePtr _rx;
	_rx = _sheet->GetRange(Letter);
	
	//_rx->PutValue( _tVal , xlRangeValueDefault);
	_rx->NumberFormatLocal = "0.000000000000000";
	_rx->PutItem(1,1,_tVal);

	char * szLog = new char[200];
	sprintf( szLog , "CELL= %s , VALUE = %s " , Letter ,(LPSTR)_bstr_t(_tVal) );
	LOGSTR(szLog);
	delete szLog;
	return ;
}*/

/*double	CDeuTrans::GetDoubleCellVal(Excel::_WorksheetPtr _sheet, char * szRowCol)
{
	double dx = 0;
	_variant_t _tx;
	_variant_t _des_tx;
	
	Excel::RangePtr _rx;
	if(szRowCol == NULL)
		return -1;
			

	_rx = _sheet->GetRange(szRowCol);
	//_rx = _range->GetItem( _variant_t(irow) ,_variant_t(icol) );
	_tx = _rx->GetValue();
	
	if(_tx.vt != VT_R8)
		_des_tx.ChangeType(VT_R8,&_tx);
	else
		_des_tx=_tx;

	dx=(double)_des_tx;
		
	
	
	return dx;
}*/

/*double CDeuTrans::GetDoubleCellVal(Excel::_WorksheetPtr _sheet, long irow , long icol)
{
	double dx = 0;
	_variant_t _tx;
	_variant_t _des_tx;

	char Letter[100];
	Num2Letter( irow ,icol ,Letter );


	Excel::RangePtr _rx;
	if(icol>0 && irow>0)
	{		

		_rx = _sheet->GetRange(Letter);
		//_rx = _range->GetItem( _variant_t(irow) ,_variant_t(icol) );
		_tx = _rx->GetValue();
		
		if(_tx.vt != VT_R8)
			_des_tx.ChangeType(VT_R8,&_tx);
		else
			_des_tx=_tx;

		dx=(double)_des_tx;
		
	}
	
	return dx;
}*/

/*char * CDeuTrans::GetLetter( int iRow , char * szCol)
{
	if( strcmp( szCol , "0" ) == 0 )
		return NULL;

	char * Letter = new char[100];

	char * sz_r = new char[200];
	sz_r = itoa( iRow , sz_r ,10 );
	
	strcpy( Letter , szCol );

	strcat( Letter , sz_r );

	delete sz_r;

	return Letter;
}*/

HRESULT CDeuTrans::RegisterProc(LONGLONG proc)
{
	_callback = (callback_fun)proc;

	return S_OK;
}

int getCenterLong(double L)
{
	int    d0 = (int)L/3;
	double d1 = L/3 - d0;
	double d2 = (d1>=0.5)? ceil(L/3) : floor(L/3);
	int    d3 = ((int)d2)*3;
	return d3;
}

long CDeuTrans::Use_Gdal_CoordTransSingleFile(const CString& filename,const CString& inDriverName,const CString& filenameout,const CString& outDriverName,UINT Id )
{
	LOGSTR(":CoordTransGdalSingleFile");
	_bstr_t _bstr_filename_log = filename;
	_bstr_t _bstr_inDriver_log = inDriverName;
	_bstr_t _bstr_filenameout_log = filenameout;
	_bstr_t _bstr_outDriver_log = outDriverName;

	LOGSTR((LPSTR)_bstr_filename_log);
	LOGSTR((LPSTR)_bstr_inDriver_log);
	LOGSTR((LPSTR)_bstr_filenameout_log);
	LOGSTR((LPSTR)_bstr_outDriver_log);
	
	if(m_Params == NULL)
	{
		LOGSTR("error:没有设置转换参数");
	}	

	//file to layer
	OGRRegisterAll();
	RegisterOGROCI();
	CPLSetConfigOption("SHAPE_ENCODING","");
	
	OGRDataSource       *poDS = NULL;
	poDS = OGRSFDriverRegistrar::Open((LPCSTR)_bstr_t(filename), FALSE );

	if( poDS == NULL )
	{
		LOGSTR( "error:Open DataSource failed." );
		return S_FALSE;
	}

	LOGSTR(":打开源文件成功");
	
	//打开目标数据源
	//const char *pszDriverNameOut = "ESRI Shapefile";
	OGRSFDriver *poDriverOut;
	//OGRRegisterAll();

	poDriverOut = OGRSFDriverRegistrar::GetRegistrar()->GetDriverByName((LPCSTR)_bstr_t(outDriverName) );
	if( poDriverOut == NULL )
	{
		LOGSTR( "error: driver not available.");
		return S_FALSE;
	}

	OGRDataSource *poDSOut;

	//for linux
	//如果存在就删除它

	//std::fstream _file;		
	_bstr_t bstr_filename = filenameout;
	char* strFileName = (LPSTR)bstr_filename;
	//_file.open( strFileName, std::ios::in);
	//if (_file)
	//{			
	//	_file.close();
		BOOL ret= DeleteFileA(strFileName);			
	//}

	poDSOut = poDriverOut->CreateDataSource( (LPCSTR)_bstr_t(filenameout), NULL );
	if( poDSOut == NULL )
	{
		LOGSTR( "error:Creation of output file failed." );
		return S_FALSE;
	}
	
	//layer to feature
	int lyrCount=0;
	lyrCount=poDS->GetLayerCount();

	//获得总地物个数
	OGRLayer  *TmppoLayer;
	for (int i=0;i<lyrCount;i++)
	{
		TmppoLayer=poDS->GetLayer(i);
		unsigned int _fea_count=TmppoLayer->GetFeatureCount();
		m_all_fea_count+=_fea_count;
	}

	LOG_START;

	OGRLayer  *poLayer;
	for (int i=0;i<lyrCount;i++)
	{
		RESET_COUNT;
		START_TIME;

		poLayer=poDS->GetLayer(i);

#if 1
		//获得图层范围
		//virtual OGRErr GetExtent(OGREnvelope *psExtent, int bForce = TRUE);
		OGREnvelope extent;
		poLayer->GetExtent(&extent);

#ifdef USE_DOG
		OGREnvelope ori_extent;
		double  other_ext[4];
		ZeroMemory(other_ext,4);
#if 1
		int ret = getFunctionNo(other_ext);
		//int ret = 0;
		//福建范围
		/*other_ext[0] = 22.564372;
		other_ext[1] = 114.85314;
		other_ext[2] = 29.957585;
		other_ext[3] = 121.498813;*/
#else
		int ret = 0;
		//全国范围
		/*other_ext[0] = 18.158023;
		other_ext[1] = 73.491187;
		other_ext[2] = 53.564217;
		other_ext[3] = 135.096343;*/
		//福建范围
		other_ext[0] = 22.564372;
		other_ext[1] = 114.85314;
		other_ext[2] = 29.957585;
		other_ext[3] = 121.498813;
#endif

		if (ret != 0 )
		{
			//::SendMessage(m_hwnd,WM_NO_PRIVILEGE_EXTENT,Id,(LPARAM)filename);
			return E_FAIL_PRIVILEGE_EXTENT;
		}

		SHORT coordtype=0;
		m_coordtype->get_CoordType(&coordtype);

		if( coordtype == PLANE)
		{
			OGREnvelope extent_T;
			extent_T.MaxX = extent.MaxY;
			extent_T.MinX = extent.MinY;
			extent_T.MaxY = extent.MaxX;
			extent_T.MinY = extent.MinX;

			extent_T.MaxY -=m_src_false_east;
			extent_T.MinY -=m_src_false_east;

			Gauss_xy_bl(m_srcPJ,m_src_from_greenwich * DEG_TO_RAD ,extent_T.MinX,extent_T.MinY,ori_extent.MinX,ori_extent.MinY);
			Gauss_xy_bl(m_srcPJ,m_src_from_greenwich * DEG_TO_RAD ,extent_T.MaxX,extent_T.MaxY,ori_extent.MaxX,ori_extent.MaxY);

			ori_extent.MaxX *=RAD_TO_DEG;
			ori_extent.MinX *=RAD_TO_DEG;
			ori_extent.MaxY *=RAD_TO_DEG;
			ori_extent.MinY *=RAD_TO_DEG;
		}
		else
		{
			ori_extent.MaxY = extent.MaxX ;
			ori_extent.MinY = extent.MinX ;
			ori_extent.MaxX = extent.MaxY ;
			ori_extent.MinX = extent.MinY ;
		}

		OGREnvelope other_extent;
		other_extent.MinX = other_ext[0];
		other_extent.MinY = other_ext[1];
		other_extent.MaxX = other_ext[2];
		other_extent.MaxY = other_ext[3];

		int ret2 = other_extent.Contains(ori_extent);
		if (ret2 == 0)
		{
			LOGSTR("图层范围错误。");
			LOG_EXTENT(	ori_extent.MaxY,ori_extent.MinY,ori_extent.MaxX,ori_extent.MinX ) ;
			return E_FAIL_PRIVILEGE_EXTENT;
		}

		if(bCanUse == false)
		{
			return E_FAIL_PRIVILEGE_UID;
		}
#endif
#endif

		//create a layer？？？
		OGRLayer *poLayerOut;
		OGRFeatureDefn * poFeaDef=poLayer->GetLayerDefn();
		LPCSTR szlyrname=poFeaDef->GetName();
		//CString _tc=L"tc";
		//_tc=(CString)szlyrname+_tc;
		
#if 0
		//支持双字节
		int _len=_tc.GetLength()*2;
		
		LPSTR p_res_lyr =new char[_len];// =(LPWCSTR)(_tc.GetString());  
		wcharTochar(_tc.GetBuffer(),p_res_lyr,_len);
		LPCSTR res_lyrname=p_res_lyr;
#else
		//单字节
		LPCSTR res_lyrname;
		//int _len=_tc.GetLength();
		//USES_CONVERSION;
		//W2A(szlyrname.LockBuffer());
		res_lyrname=szlyrname;	
#endif

		LOGSTR(":设置空间参考开始");
		
		//设置空间参考
		OGRSpatialReference * poRSR = SetSRS(m_SRS);

		if( poRSR == NULL )
			return E_FAIL_SETRSR;

		LOGSTR(":设置空间参考完毕");
		OGRwkbGeometryType type=poLayer->GetLayerDefn()->GetGeomType();

		//创建字段		
		poLayerOut=poDSOut->CreateLayer(res_lyrname,poRSR,type);
		if(poLayerOut==NULL)
		{
			LOGSTR(":创建目标文件失败");
			continue;
		}

		int _field_count= poFeaDef->GetFieldCount();
		for (int i=0;i<_field_count;i++)
		{
			OGRFieldDefn *poField=poFeaDef->GetFieldDefn(i);
			poLayerOut->CreateField(poField);
		}
#if 0 
		//poLayerOut=poDSOut->CopyLayer(poLayer,szlyrname);
#endif

		//poLayerOut = poDSOut->CreateLayer( "point_out", NULL, wkbPoint, NULL );
		if( poLayerOut == NULL )
		{
			LOGSTR( "error:Layer creation failed." );
			return S_FALSE;
		}

		OGRFeature *poFeature;
		//OGRFeature *poFeatureOut;
		unsigned int _this_fea_count=poLayer->GetFeatureCount();

		//LOGSTR("=====================================================================");
		char *geo_lyr_name=(char*)malloc(200);		
		strcpy(geo_lyr_name,szlyrname);		
		LOG("开始转换图层:",geo_lyr_name,200);
		free(geo_lyr_name);

		poLayer->ResetReading();
		for (unsigned long  i=0;i<_this_fea_count;i++)
		{	
			m_fea_done++;
#if 0
			if(m_fea_done>141090)
			{
				int u=0;	
			}
#endif
			unsigned int  Percent=(double)((double)m_fea_done/(double)m_all_fea_count)*100;
			::SendMessage(m_hwnd,WM_PROGRESS,0,Percent);
			DEU_CALLBACK(WM_PROGRESS,0,Percent);

			poFeature = poLayer->GetNextFeature();
			if (poFeature ==NULL)
			{
				m_fea_null_count++;
				continue;
			}

			int fea_FID=poFeature->GetFID();
			OGRGeometry *poGeometry=NULL;
			OGRLineString *poLine=NULL;
			OGRPoint *poPoint=NULL;
			OGRMultiPoint *poMultiPoint=NULL;
			OGRMultiLineString *poMultiLineString=NULL;
			OGRPolygon *poPolygon=NULL;
			OGRMultiPolygon *poMultiPolygon=NULL; 

			poGeometry = poFeature->GetGeometryRef();
			//each geometry trans its coordinate
			if(poGeometry == NULL)
			{
				m_geo_null_count++;

				OGRErr _error =poLayerOut->CreateFeature( poFeature ) ;
				if( _error!= OGRERR_NONE )
				{
					LOGSTR( "error:Failed to create feature in shapefile." );
					//return S_FALSE;
					m_fea_fail_count++;					
				}

				m_fea_create_count++;

				OGRFeature::DestroyFeature( poFeature );
				continue;
			}

			OGRwkbGeometryType type=poGeometry->getGeometryType();

			double _oldX;
			double _oldY;
			double _oldZ;

			double _newX;
			double _newY;
			double _newZ;

			int _pt_count=0;
			int _ex_count;
			OGRLinearRing* _ex_ring=NULL;
			int _in_ring_count=0;
			int _geo_count=0;
			int L0 = 0;
#if 0
			OGRFeature *poFeature_D;
			OGRPoint* poPoint_D;
			//OGRPoint* poFeature_D->GetGeometryRef();
#endif
			m_geo_done++;
			switch (type)
			{
			case wkbPoint:
			case wkbPoint25D:
				m_geo_point_count++;

				poPoint=(OGRPoint*)poGeometry;

				_oldY=poPoint->getX();//经度或东方向
				_oldX=poPoint->getY();//纬度或北方向
				_oldZ=poPoint->getZ();

				//L0 = getCenterLong(_oldY);
				//if (L0 != 117)
				//{
				//	continue;
				//}

				if(_oldY>extent.MaxX||_oldY<extent.MinX||_oldX>extent.MaxY||_oldX<extent.MinY)
				{
					m_geo_ori_error_count++;

					char *geo_Ori_Error=(char*)malloc(100);
					int fea_FID=poFeature->GetFID();
					itoa(fea_FID,geo_Ori_Error,10);
					LOG("原始数据错误的点FID:",geo_Ori_Error,100);
					free(geo_Ori_Error);

					LOGSTR(ERR_CroodInfoError);

					//poFeature->SetGeometry(NULL);
					//break;
				}

				_coordtransf( fea_FID , 1,&_oldX,&_oldY,&_oldZ,&_newX,&_newY,&_newZ);

				if(poPoint->getDimension()==0)
				{
					poPoint->setX(_newY);
					poPoint->setY(_newX);
				}
				else if(poPoint->getDimension()==1)
				{
					poPoint->setX(_newY);
					poPoint->setY(_newX);
					poPoint->setZ(_newZ);
				}

				break;
			case wkbLineString:
			case wkbLineString25D:
				m_geo_line_count++;
								
				poLine=(OGRLineString *) poGeometry;
				_pt_count=poLine->getNumPoints();

				for (int i=0;i<_pt_count;i++)
				{
					_oldY=poLine->getX(i);//经度或东方向
					_oldX=poLine->getY(i);//纬度或北方向
					_oldZ=poLine->getZ(i);

					if(_oldY>extent.MaxX||_oldY<extent.MinX||_oldX>extent.MaxY||_oldX<extent.MinY)
					{
						m_geo_ori_error_count++;

						char *geo_Ori_Error=(char*)malloc(100);
						int fea_FID=poFeature->GetFID();
						itoa(fea_FID,geo_Ori_Error,10);
						LOG("原始数据错误的线FID:",geo_Ori_Error,100);
						free(geo_Ori_Error);

						LOGSTR(ERR_CroodInfoError);

						//poFeature->SetGeometry(NULL);
						//break;
					}

					_coordtransf( fea_FID , 1,&_oldX,&_oldY,&_oldZ,&_newX,&_newY,&_newZ);

					if (poLine->getDimension()==0)
					{
						poLine->setPoint(i,_newY,_newX);
					}
					else if(poLine->getDimension()==1)
					{
						poLine->setPoint(i,_newY,_newX);
					}
					else if(poLine->getDimension()==2)
					{
						poLine->setPoint(i,_newY,_newX,_newZ);
					}
				}

				//_coordtransf(_pt_count,ori_x,ori_y,ori_z,Newx,Newy,Newz);
				break;

			case wkbMultiPoint:
			case wkbMultiPoint25D:
				m_geo_multi_point_count++;

				poMultiPoint=(OGRMultiPoint *)poGeometry;
				poMultiPoint->getNumGeometries();
				_pt_count=poMultiPoint->getNumGeometries();

				for (int i=0;i<_pt_count;i++)
				{
					_oldY=((OGRPoint*)poMultiPoint->getGeometryRef(i))->getX();//经度或东方向
					_oldX=((OGRPoint*)poMultiPoint->getGeometryRef(i))->getY();//纬度或北方向
					_oldZ=((OGRPoint*)poMultiPoint->getGeometryRef(i))->getZ();

					if(_oldY>extent.MaxX||_oldY<extent.MinX||_oldX>extent.MaxY||_oldX<extent.MinY)
					{
						m_geo_ori_error_count++;

						char *geo_Ori_Error=(char*)malloc(100);
						int fea_FID=poFeature->GetFID();
						itoa(fea_FID,geo_Ori_Error,10);
						LOG("原始数据错误的多点FID:",geo_Ori_Error,100);
						free(geo_Ori_Error);

						LOGSTR(ERR_CroodInfoError);

						//poFeature->SetGeometry(NULL);
						//break;
					}

					_coordtransf(fea_FID ,1,&_oldX,&_oldY,&_oldZ,&_newX,&_newY,&_newZ);
					
					OGRPoint* poPoint=((OGRPoint*)poMultiPoint->getGeometryRef(i));

					if(poPoint->getDimension()==0)
					{
						poPoint->setX(_newY);
						poPoint->setY(_newX);
					}
					else if(poPoint->getDimension()==1)
					{
						poPoint->setX(_newY);
						poPoint->setY(_newX);						
					}
				}

				//_coordtransf(_pt_count,ori_x,ori_y,ori_z,Newx,Newy,Newz);
				break;
			case wkbMultiLineString:
			case wkbMultiLineString25D:
				m_geo_multi_line_count++;

				poMultiLineString=(OGRMultiLineString *)poGeometry;
				_geo_count= poMultiLineString->getNumGeometries();

				for (int i=0;i<_geo_count;i++)
				{
					OGRLineString* poLineString=(OGRLineString*)poMultiLineString->getGeometryRef(i);
					_pt_count=poLineString->getNumPoints();
					for (int j=0;j<_pt_count;j++)
					{
						_oldY=poLineString->getX(j);//经度或东方向
						_oldX=poLineString->getY(j);//纬度或北方向
						_oldZ=poLineString->getZ(j);

						if(_oldY>extent.MaxX||_oldY<extent.MinX||_oldX>extent.MaxY||_oldX<extent.MinY)
						{
							m_geo_ori_error_count++;

							char *geo_Ori_Error=(char*)malloc(100);
							int fea_FID=poFeature->GetFID();
							itoa(fea_FID,geo_Ori_Error,10);
							LOG("原始数据错误的多线FID:",geo_Ori_Error,100);
							free(geo_Ori_Error);

							LOGSTR(ERR_CroodInfoError);

							//poFeature->SetGeometry(NULL);
							//break;
						}

						_coordtransf(fea_FID ,1,&_oldX,&_oldY,&_oldZ,&_newX,&_newY,&_newZ);

						if(poLineString->getDimension()==0)
						{
							poLineString->setPoint(j,_newY,_newX);
						}
						else if(poLineString->getDimension()==1)
						{
							poLineString->setPoint(j,_newY,_newX);
						}
						else if(poLineString->getDimension()==2)
						{
							poLineString->setPoint(i,_newY,_newX,_newZ);
						}					
					}
				}
				break;
			case wkbPolygon:
			case wkbPolygon25D:
				m_geo_polygon_count++;

				poPolygon=(OGRPolygon *)poGeometry;

				_in_ring_count=poPolygon->getNumInteriorRings();

				for (int i=0;i<_in_ring_count;i++)
				{
					OGRLinearRing* ring=poPolygon->getInteriorRing(i);
					int _ring_count=ring->getNumPoints();
					for (int j=0;j<_ring_count;j++)
					{
						_oldY= ring->getX(j);//经度或东方向
						_oldX= ring->getY(j);//纬度或北方向
						_oldZ= ring->getZ(j);

						if(_oldY>extent.MaxX||_oldY<extent.MinX||_oldX>extent.MaxY||_oldX<extent.MinY)
						{
							m_geo_ori_error_count++;

							char *geo_Ori_Error=(char*)malloc(100);
							int fea_FID=poFeature->GetFID();
							itoa(fea_FID,geo_Ori_Error,10);
							LOG("原始数据错误的面FID:",geo_Ori_Error,100);
							free(geo_Ori_Error);

							LOGSTR(ERR_CroodInfoError);

							//poFeature->SetGeometry(NULL);
							//break;
						}

						_coordtransf(fea_FID ,1,&_oldX,&_oldY,&_oldZ,&_newX,&_newY,&_newZ);

						if(poPolygon->getDimension()==0)
						{
							ring->setPoint(j,_newY,_newX);
						}
						else if(poPolygon->getDimension()==1)
						{
							ring->setPoint(j,_newY,_newX);
						}	
						else if(poPolygon->getDimension()==2)
						{
							ring->setPoint(j,_newY,_newX,_newZ);
						}		
					}
				}

				_ex_ring=poPolygon->getExteriorRing();
				_ex_count=_ex_ring->getNumPoints();
				for (int i=0;i<_ex_count;i++)
				{
					_oldY= _ex_ring->getX(i);//经度或东方向
					_oldX= _ex_ring->getY(i);//纬度或北方向
					_oldZ= _ex_ring->getZ(i);

					if(_oldY>extent.MaxX||_oldY<extent.MinX||_oldX>extent.MaxY||_oldX<extent.MinY)
					{
						m_geo_ori_error_count++;

						char *geo_Ori_Error=(char*)malloc(100);
						int fea_FID=poFeature->GetFID();
						itoa(fea_FID,geo_Ori_Error,10);
						LOG("原始数据错误的面FID:",geo_Ori_Error,100);
						free(geo_Ori_Error);

						LOGSTR(ERR_CroodInfoError);

						//poFeature->SetGeometry(NULL);
						//break;
					}

					_coordtransf(fea_FID ,1,&_oldX,&_oldY,&_oldZ,&_newX,&_newY,&_newZ);

					if(poPolygon->getDimension()==0)
					{
						_ex_ring->setPoint(i,_newY,_newX);
					}
					else if(poPolygon->getDimension()==1)
					{
						_ex_ring->setPoint(i,_newY,_newX);
					}	
					else if(poPolygon->getDimension()==2)
					{
						_ex_ring->setPoint(i,_newY,_newX,_newZ);
					}	
				}
				break;
			case wkbMultiPolygon:
			case wkbMultiPolygon25D:
				m_geo_multi_polygon_count++;

				poMultiPolygon=(OGRMultiPolygon *)poGeometry;
				_geo_count=poMultiPolygon->getNumGeometries();

				for (int i=0;i<_geo_count;i++)
				{
					OGRPolygon* poPolygon=(OGRPolygon*)poMultiPolygon->getGeometryRef(i);
					if (NULL == poPolygon)
					{
						continue;
					}

					//内环
					_in_ring_count=poPolygon->getNumInteriorRings();

					for (int i=0;i<_in_ring_count;i++)
					{
						OGRLinearRing* ring=poPolygon->getInteriorRing(i);
						int _ring_count=ring->getNumPoints();
						for (int j=0;j<_ring_count;j++)
						{
							_oldY= ring->getX(j);//经度或东方向
							_oldX= ring->getY(j);//纬度或北方向
							_oldZ= ring->getZ(j);

							if(_oldY>extent.MaxX||_oldY<extent.MinX||_oldX>extent.MaxY||_oldX<extent.MinY)
							{
								m_geo_ori_error_count++;

								char *geo_Ori_Error=(char*)malloc(100);
								int fea_FID=poFeature->GetFID();
								itoa(fea_FID,geo_Ori_Error,10);
								LOG("原始数据错误的多面FID:",geo_Ori_Error,100);
								free(geo_Ori_Error);

								LOGSTR(ERR_CroodInfoError);

								//poFeature->SetGeometry(NULL);
								//break;
							}

							_coordtransf(fea_FID ,1,&_oldX,&_oldY,&_oldZ,&_newX,&_newY,&_newZ);

							if(poPolygon->getDimension()==0)
							{
								ring->setPoint(j,_newY,_newX);
							}
							else if(poPolygon->getDimension()==1)
							{
								ring->setPoint(j,_newY,_newX);
							}
							else if(poPolygon->getDimension()==2)
							{
								ring->setPoint(j,_newY,_newX,_newZ);
							}
						}
					}

					//外环
					_ex_ring=poPolygon->getExteriorRing();
					_ex_count=_ex_ring->getNumPoints();
					for (int i=0;i<_ex_count;i++)
					{
						_oldY= _ex_ring->getX(i);//经度或东方向
						_oldX= _ex_ring->getY(i);//纬度或北方向
						_oldZ= _ex_ring->getZ(i);

						if(_oldY>extent.MaxX||_oldY<extent.MinX||_oldX>extent.MaxY||_oldX<extent.MinY)
						{
							m_geo_ori_error_count++;

							char *geo_Ori_Error=(char*)malloc(100);
							int fea_FID=poFeature->GetFID();
							itoa(fea_FID,geo_Ori_Error,10);
							LOG("原始数据错误的多面FID:",geo_Ori_Error,100);
							free(geo_Ori_Error);

							LOGSTR(ERR_CroodInfoError);

							//poFeature->SetGeometry(NULL);
							//break;
						}

						_coordtransf(fea_FID ,1,&_oldX,&_oldY,&_oldZ,&_newX,&_newY,&_newZ);

						if(poPolygon->getDimension()==0)
						{
							_ex_ring->setPoint(i,_newY,_newX);
						}
						else if(poPolygon->getDimension()==1)
						{
							_ex_ring->setPoint(i,_newY,_newX);
						}
						else if(poPolygon->getDimension()==2)
						{
							_ex_ring->setPoint(i,_newY,_newX,_newZ);
						}					
					}
				}

				break;
			case wkbGeometryCollection:
			case wkbGeometryCollection25D:
				m_error_count++;
				break;
			default:
				m_error_count++;
				break;
			}

			OGRErr _error =poLayerOut->CreateFeature( poFeature ) ;
			if( _error!= OGRERR_NONE )
			{
				printf( "Failed to create feature in shapefile.\n" );
				//return S_FALSE;
				m_fea_fail_count++;
				continue;
			}

			m_fea_create_count++;

			OGRFeature::DestroyFeature( poFeature );

		}//for each feature

		LOG_FEA_DONE;
		LOG_FEA_NULL;
		LOG_FEA_CREATE;
		LOG_FEA_FAIL;
		LOG_GEO_PT;
		LOG_GEO_LINE;
		LOG_GEO_POLYGON;
		LOG_GEO_MPT;
		LOG_GEO_MLINE;
		LOG_GEO_MPOLYGON;
		LOG_GEO_NULL;
		LOG_ERR_OTHER;
		LOG_ORI_ERROR;
		LOG_GEO_DONE;

		END_TIME;
		LOG_USED_TIME;
	}
	
	LOG_END;
	
	::SendMessage(m_hwnd,WM_PROGRESS,0,100);
	DEU_CALLBACK(WM_PROGRESS,0,100);
		
	OGRDataSource::DestroyDataSource( poDS );
	OGRDataSource::DestroyDataSource( poDSOut );

	LOG_ALL_FEA;
	LOGSTR("=====================================================================");
	
	return S_OK;
}

//long CDeuTrans::Use_Deu_CoordTransSingleFile(const CString& filename,const CString& inDriverName,const CString& filenameout,const CString& outDriverName,UINT Id )
//{
//	LOGSTR(":CoordTransSingleFile");
//	_bstr_t _bstr_filename_log = filename;
//	_bstr_t _bstr_inDriver_log = inDriverName;
//	_bstr_t _bstr_filenameout_log = filenameout;
//	_bstr_t _bstr_outDriver_log = outDriverName;
//
//	LOGSTR((LPSTR)_bstr_filename_log);
//	LOGSTR((LPSTR)_bstr_inDriver_log);
//	LOGSTR((LPSTR)_bstr_filenameout_log);
//	LOGSTR((LPSTR)_bstr_outDriver_log);
//	
//#ifdef	USE_DOG
//	if( !bCanUse )
//	{			
//		return E_FAIL_PRIVILEGE_UID;
//	}
//#endif
//
//	//////////////////////////////////////////////////////////////////////////
//	if(m_Para == NULL)
//	{
//		LOGSTR("error:没有设置转换参数");
//	}
//	//////////////////////////////////////////////////////////////////////////
//
//	if ( _bstr_t(inDriverName) == _bstr_t("DXF") )
//	{
//		void * p_f = 0;
//
//		GetMemberFuncAddr_VC6( p_f , &CDeuTrans::transfun );
//
//		BSTR bstrSRS;
//
//		m_SRS->exportToWkt(&bstrSRS);
//
//		importSRSFromWkt( (LPCSTR)_bstr_t(bstrSRS) );
//
//		/*unsigned int  Percent=(double)((double)1/(double)100)*100;
//		::SendMessage(m_hwnd,WM_PROGRESS,0,Percent);
//		DEU_CALLBACK(WM_PROGRESS,0,Percent);*/
//
//		DXFTransform( (LPCSTR)_bstr_t(filename) ,(LPCSTR)_bstr_t(filenameout) , p_f , m_hwnd);
//
//        unsigned int	Percent=(double)((double)100/(double)100)*100;
//		::SendMessage(m_hwnd,WM_PROGRESS,0,Percent);
//		DEU_CALLBACK(WM_PROGRESS,0,Percent);
//
//		ReleaseSRS( );
//	}
//
//	//增加对EOO文件格式的读写 yzg 2012-9-12 begin
//    else if (_bstr_t(inDriverName) == _bstr_t("AVCE00"))
//    {
//		void * p_f = 0;
//
//		GetMemberFuncAddr_VC6( p_f , &CDeuTrans::transfun );
//
//		unsigned int  Percent=(double)((double)1/(double)100)*100;
//		::SendMessage(m_hwnd,WM_PROGRESS,0,Percent);
//		DEU_CALLBACK(WM_PROGRESS,0,Percent);
//
//		EooTransform( (LPCSTR)_bstr_t(filename) ,(LPCSTR)_bstr_t(filenameout) , p_f, m_hwnd );
//
//		Percent=(double)((double)100/(double)100)*100;
//		::SendMessage(m_hwnd,WM_PROGRESS,0,Percent);
//		DEU_CALLBACK(WM_PROGRESS,0,Percent);
//    }
//	else if (_bstr_t(inDriverName) == _bstr_t("Coverage"))
//	{
//		void * p_f = 0;
//
//		GetMemberFuncAddr_VC6( p_f , &CDeuTrans::transfun );
//
//		unsigned int  Percent=(double)((double)1/(double)100)*100;
//		::SendMessage(m_hwnd,WM_PROGRESS,0,Percent);
//		DEU_CALLBACK(WM_PROGRESS,0,Percent);
//
//		CoverageTransform( (LPCSTR)_bstr_t(filename) ,(LPCSTR)_bstr_t(filenameout) , p_f, m_hwnd );
//
//		Percent=(double)((double)100/(double)100)*100;
//		::SendMessage(m_hwnd,WM_PROGRESS,0,Percent);
//		DEU_CALLBACK(WM_PROGRESS,0,Percent);
//	}
//    //yzg  end
//
//	return 0;
//}

OGRSpatialReference* CDeuTrans::SetSRS(CDeuSpatialReference* m_SRS)
{
#if 1
	//设置空间参考
	OGRSpatialReference* poRSR= new OGRSpatialReference(); //poLayer->GetSpatialRef();
	if(m_SRS==NULL)
	{
		LOGSTR("error:没有设置空间参考。");				
	}
	else
	{
		if(poRSR)
		{
			//const char *pszPrj="Gauss_Kruger";
			//poRSR->SetProjection(pszPrj);
			//poRSR->SetGeogCS("GCS_Beijing_1980","D_Beijing_1980","DeuEll",123,456);

			//设置投影坐标系
			BOOL  vb_IsProj =TRUE  ;
			CString ProjName = _T("");
			CString Proj = _T("") ;

			//设置大地坐标系
			CString dfGeogName = _T("");
			CString dfDatum = _T("");
			CString dfEllipName = _T("");
			double dfSemiMajor;
			double dfInvFlattening;

			m_SRS->get_IsProject(vb_IsProj);
			if( vb_IsProj != FALSE )
			{
				//设置投影坐标系名称					
				m_SRS->get_ProjeCS(ProjName);

				//if( ProjName )
				poRSR->SetProjCS((LPCSTR)_bstr_t(ProjName.GetString()));

				//设置投影方法
				m_SRS->get_Projection(Proj);
				//if( Proj )
				poRSR->SetProjection((LPCSTR)_bstr_t(Proj.GetString()));

				//--------------------------------------------------------------------------------
				double *szProjparms = NULL;
				//vector<double>	szProjparms;
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
			m_SRS->get_GeogCS( dfGeogName , dfDatum, dfEllipName, dfSemiMajor, dfInvFlattening);
			poRSR->SetGeogCS((LPCSTR)_bstr_t(dfGeogName.GetString()),(LPCSTR)_bstr_t(dfDatum.GetString()),(LPCSTR)_bstr_t(dfEllipName.GetString()),dfSemiMajor,dfInvFlattening);
			//}

			CString dfLinearUnits = _T("");
			double fLinearUnits;
			char *szLinearUnits;

			fLinearUnits=poRSR->GetLinearUnits(&szLinearUnits);
			//int ret_cmp= strcmp(szLinearUnits,"unknown");
			//if(ret_cmp!=0)
			//{
			m_SRS->get_LinearUnit(dfLinearUnits);
			poRSR->SetLinearUnits((LPCSTR)_bstr_t(dfLinearUnits.GetString()),fLinearUnits);
			//}

			CString dfAngularUnits = _T("");
			double fAngularUnit;
			char *szAngularUnit;

			fAngularUnit=poRSR->GetAngularUnits(&szAngularUnit);
			//ret_cmp= strcmp(szAngularUnit,"unknown");
			//if(ret_cmp!=0)
			//{
			m_SRS->get_AngularUnit(dfAngularUnits);
			poRSR->SetAngularUnits((LPCSTR)_bstr_t(dfAngularUnits.GetString()),fAngularUnit);
			//}
		}
	}
#else
	OGRSpatialReference* poRSR = NULL ;
#endif

	return poRSR;
}

HRESULT	CDeuTrans::CoordTransSingleFile(const CString& strFileName_In, const CString& strDirverName_In,const CString& strFileName_Out,const CString& strDirverName_Out,UINT Id )
{
	//这里对输出文件进行处理 确保文件夹存在
	CString       strFileOut(strFileName_Out);
	CString       strFileName;
	CString       strFile;   //需要确保存在的单纯文件夹
	CString       strFileTemp;
	int           iStart = 0;

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

	if ( strDirverName_In == _T("ESRI Shapefile") )
	{
		Use_Gdal_CoordTransSingleFile( strFileName_In , strDirverName_In , strFileName_Out , strDirverName_Out , Id );
	}
	else if ( strDirverName_In == _T("MapInfo File") )
	{
		Use_Gdal_CoordTransSingleFile(strFileName_In , strDirverName_In , strFileName_Out , strDirverName_Out , Id );
	}
	else if ( strDirverName_In == _T("AVCE00") )
	{
		//yzg 用于支持E00文件格式的编写 begin
		//Use_Gdal_CoordTransSingleFile( filename , inDriverName , filenameout , outDriverName , Id );
		Use_Deu_CoordTransSingleFile(strFileName_In , strDirverName_In , strFileName_Out , strDirverName_Out , Id );
		//yzg 用于支持E00文件格式的编写 end
	}
	else if ( strDirverName_In == _T("DXF") )
	{	
		Use_Deu_CoordTransSingleFile(strFileName_In , strDirverName_In , strFileName_Out , strDirverName_Out , Id );
	}
	else if ( strDirverName_In == _T("Coverage") )
	{
		Use_Deu_CoordTransSingleFile(strFileName_In , strDirverName_In , strFileName_Out , strDirverName_Out , Id );
	}
	else if ( strDirverName_In == _T("Excel") )
	{
		CoordTransSingleFileExcel(strFileName_In , strDirverName_In , strFileName_Out , strDirverName_Out ,g_TransParams._Excel, Id );
	}
	else
	{
		return S_FALSE;
	}
	
	return S_OK;
}

//SDO_geometry * CDeuTrans::CloneGeometry(const SDO_geometry & geo)
//{
//	SDO_geometry  *poutGeo = new SDO_geometry ;
//	SDO_geometry  &outGeo  = * poutGeo; 
//
//	memcpy( poutGeo , &geo ,sizeof(SDO_geometry) );
//
//	int eleSize = outGeo.obj.elemInfoSize;
//	int ordiSize = outGeo.obj.ordinatesSize;
//
//	outGeo.obj.elemInfoQueue_ = new int[eleSize];
//	outGeo.obj.ordinatesQueue_= new double[ordiSize];
//
//	memcpy( poutGeo->obj.elemInfoQueue_ , geo.obj.elemInfoQueue_ , geo.obj.elemInfoSize * sizeof(int) );
//
//	return poutGeo;
//
//}

HRESULT CDeuTrans::InitGridTranslate(std::string strFileName)
{
	m_GridTranslate.InitGridTranslate(strFileName);

	return S_OK;
}

void CDeuTrans::TransSDEVector(double x1, double y1, double z1, double& x2, double& y2, double& z2)
{
	_coordtransf( 0 , 1,&x1, &y1, &z1, &x2, &y2, &z2);
}

