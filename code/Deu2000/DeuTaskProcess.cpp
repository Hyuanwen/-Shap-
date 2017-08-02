#include "StdAfx.h"
#include "DeuTaskProcess.h"
#include "DeuTaskCache.h"
#include "ogrsf_frmts.h"
#include "DeuGlobalParam.h"
#include "DeuGlobal.h"
#include "DeuVectorTranDlg.h"
#include "DeuRasterTranDlg.h"
#include "DeuVectorProjectTranDlg.h"
#include "DeuRasterProjectTranDlg.h"
#include "DeuDlgGridSetting.h"
#include "DeuTranslate.h"
//#include "ArcSDeVector.h"
//#include "ArcSDERaster.h"

IFFUNC(TaskName);
IFFUNC_2(m_Name);

#define FIND_NODE_IF(l,n) \
	std::find_if(l.begin(),l.end(),IFFunctor2_m_Name<CDeuCoordinateSystem*,CString>(n));

DWORD WINAPI ThreadFunc_RasterDEM(HANDLE Thread);
DWORD WINAPI ThreadVector(HANDLE _handle);
DWORD WINAPI ThreadVectorPrj(HANDLE _handle);
DWORD WINAPI ThreadRaster(HANDLE _handle);
DWORD WINAPI ThreadRasterPrj(HANDLE _handle);

CDeuConnPool* 		g_ConnPool;
BOOL g_ThreadFinished = TRUE; 

void CDeuTaskProcess::InitConnPool(CString strConn)
{
	if (NULL == g_ConnPool)
	{
		g_ConnPool = new CDeuConnPool;
	}
}

std::vector<CString>* CDeuTaskProcess::GetTabListInDB(CString strConn)
{		
	CDeuDatabase pDB;
	std::vector<CString> * p_vecTabList = new std::vector<CString>;
	VARIANT * var = NULL;

	HRESULT hr = NULL;
	pDB.putref_ConnPool(g_ConnPool);
	hr = pDB.Connect(strConn);
	if (hr == S_OK )
	{		
		//pDB->GetTabList(&var);
		VARIANT varArr =*var;
		SAFEARRAY *p = varArr.parray;

		//BSTR bstr1;
		//LPSTR lpstr1;
		LONG i = 0;
		LONG lb = p->rgsabound->lLbound;
		LONG ele = p->rgsabound->cElements;
		for ( i = lb ; i < ele ; i++)
		{
			//SafeArrayGetElement(p, &i, &bstr1);
			BSTR *pData;
			SafeArrayAccessData(p,(void **)&pData);

			CString str1 ;
			USES_CONVERSION;	
			//LPWSTR lpwStr = A2W(lpstr1);
			str1 = pData[i];
			p_vecTabList->push_back(str1);
		}
	}

	return p_vecTabList;
}

CDeuTaskProcess::CDeuTaskProcess()
{
	 
}

CDeuTaskProcess::~CDeuTaskProcess(void)
{

}

//这里返回的枚举值使用daifeng源程序的枚举，以保持代码兼容
__COORDTYPE CDeuTaskProcess::FindCoordindateType(CString strEllipseName)
{
	/*
	for(int n=0; n<GeoDataMapping.ProjectedNode.pProjectedSeries.GetCount(); n++)
	{
		if(GeoDataMapping.ProjectedNode.pProjectedSeries.GetAt(n)._name.text.Compare(strEllipseName) == 0)
		{			
			return PLANE;
		}
	}

	for(int n=0; n<GeoDataMapping.GeodeticNode.pGeodeticSeries.GetCount(); n++)
	{
		if(GeoDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._name.text.Compare(strEllipseName) == 0)
		{
			return GEODETIC;
		}
	}

	return UNKNOWN;
	*/

	std::string                      strEllipName(strEllipseName);
	CEllipManager                    EllipManager;
	CoordinateType                   Type;

	EllipManager.GetEllipTypeByEllipName(strEllipName, &Type);
    if (Type == GeoProjected)
    {
		return PLANE;
    }
	else if (Type == GeoCentic || Type == GeoDetic)
	{
		return GEODETIC;
	}

	return UNKNOWN;
} 

//add by chenyong 2013-10-15 fr
string CDeuTaskProcess::GetPrjFullPathByName(const CString& strEllipseName)
{
	std::string                      strEllipName(strEllipseName);
	CEllipManager                    EllipManager;
	string							 strFullPath;

	EllipManager.GetEllipFilePath(strEllipName, &strFullPath);
	return strFullPath;	
}

//这里返回的枚举值使用daifeng源程序的枚举，以保持代码兼容
char* CDeuTaskProcess::FindCoordType(CString strEllipseName)
{
	for(int n=0; n<GeoDataMapping.ProjectedNode.pProjectedSeries.GetCount(); n++)
	{
		if(GeoDataMapping.ProjectedNode.pProjectedSeries.GetAt(n)._name.text.Compare(strEllipseName) == 0)
		{			
			//return PLANE;
			return "3";
		}
	}

	for(int n=0; n<GeoDataMapping.GeodeticNode.pGeodeticSeries.GetCount(); n++)
	{
		if(GeoDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._name.text.Compare(strEllipseName) == 0)
		{
			//return GEODETIC;
			return "1";
		}
	}

	return "0";
}

//枚举坐标类型
char* CDeuTaskProcess::FindCustomCoordType(CString strEllipseName)
{
	for(int n=0; n<CustDataMapping.ProjectedNode.pProjectedSeries.GetCount(); n++)
	{
		if(CustDataMapping.ProjectedNode.pProjectedSeries.GetAt(n)._name.text.Compare(strEllipseName) == 0)
		{			
			//return PLANE;
			return "3";
		}
	}

	for(int n=0; n<CustDataMapping.GeodeticNode.pGeodeticSeries.GetCount(); n++)
	{
		if(CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._name.text.Compare(strEllipseName) == 0)
		{
			//return GEODETIC;
			return "1";
		}
	}

	return "0";
}

//add by chenyong 2013-01-09
CDeuEllipse CDeuTaskProcess::GetDeuEllipse(CoordinateType CT, const CString& strEllipseName)
{
    /*
	CDeuEllipse Ellipse;
		switch(CT)
		{
			//大地
		case GeoDetic:
			{
				for(int n=0; n<GeoDataMapping.GeodeticNode.pGeodeticSeries.GetCount(); n++)
				{
					if(GeoDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._name.text.Compare(strEllipseName) == 0)
					{
						_GeodeticSeries pSerises = GeoDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n);
						Ellipse.putref_Ellip_Name( pSerises._name.text);

						Ellipse.putref_Major(_tstof(pSerises._datum._ellipsoid._semi_Major_Axis._value.text));
						Ellipse.putref_Minor(_tstof(pSerises._datum._ellipsoid._semi_Minor_Axis._value.text));
						double i_f = 1.0 / _tstof(pSerises._datum._ellipsoid._inverseFlattening.text);

						Ellipse.putref_Flatening(i_f);
						Ellipse.putref_Prj_Name(_T(""));
						Ellipse.putref_Prj_Type(_T(""));
						Ellipse.putref_False_N(0);
						Ellipse.putref_False_E(0);

						break;
					}
				}
			}
			break;

			//投影
		case GeoProjected:
			{
				for(int n=0; n<GeoDataMapping.ProjectedNode.pProjectedSeries.GetCount(); n++)
				{
					if(GeoDataMapping.ProjectedNode.pProjectedSeries.GetAt(n)._name.text.Compare(strEllipseName) == 0)
					{
						_ProjectedSeries mSerises = GeoDataMapping.ProjectedNode.pProjectedSeries.GetAt(n);
						Ellipse.putref_Ellip_Name(mSerises._name.text);

						_GeodeticSeries mGeodetic;
						//大地坐标参数
						switch(mSerises._tranStandard)
						{
						case Peking54:
							mGeodetic = GeoDataMapping.GeodeticNode.pGeodeticSeries.GetAt(0);
							break;
						case XiAn80:
							mGeodetic = GeoDataMapping.GeodeticNode.pGeodeticSeries.GetAt(1);
							break;
						case WGS84:
							mGeodetic = GeoDataMapping.GeodeticNode.pGeodeticSeries.GetAt(2);
							break;
						case CGCS2000:
							mGeodetic = GeoDataMapping.GeodeticNode.pGeodeticSeries.GetAt(3);
							break;
						}

						Ellipse.putref_Major(_tstof(mGeodetic._datum._ellipsoid._semi_Major_Axis._value.text));
						Ellipse.putref_Minor(_tstof(mGeodetic._datum._ellipsoid._semi_Minor_Axis._value.text));
						double i_f = 1.0 / _tstof(mGeodetic._datum._ellipsoid._inverseFlattening.text) ;
						Ellipse.putref_Flatening(i_f);

						Ellipse.putref_Centrol_Long(_tstof(mSerises._centralMeridian._value.text));
						Ellipse.putref_Prj_Name(mSerises._projection.name);
						Ellipse.putref_Prj_Type(mSerises._projection.type);
						Ellipse.putref_False_N(_tstof(mSerises._falseNorthing._value.text));
						Ellipse.putref_False_E(_tstof(mSerises._falseEasting._value.text));

						break;
					}
				}
			}
			break;
		}
	
	return Ellipse;*/

    CDeuEllipse     Ellipse;
	CEllipManager   EllipManager;
	std::string     strEllipse(strEllipseName);

	EllipManager.GetEllipByEllipName(strEllipse, &Ellipse);

	return Ellipse;
}

//add by chenyong 2013-01-09
CDeuSpatialReference CDeuTaskProcess::GetSRS(CoordinateType _CoordinateType, CString strName)
{	
	CDeuSpatialReference pDeuSRS;
	CDeuEllipse			 Ellipse;
	CEllipManager		 EllipManager;
	std::string			 strEllipse(strName);

	EllipManager.GetEllipByEllipName(strEllipse, &Ellipse);
					
	if (_CoordinateType == GeoProjected)
	{
		/*
		p_ProjectedSeries m_ProjectedSeries;
		p_GeodeticSeries m_GeodeticSeries;
		m_ProjectedSeries = GetProjectedObject(strName);
		m_GeodeticSeries = GetGeoDeticObject(m_ProjectedSeries->_geodeticPointor.text);
		*/
			
		//////////////////////////////////////////////////////////////////////////
		//CString CSProj=	m_ProjectedSeries->_projection.text;
		//CString CSProjName = m_ProjectedSeries->_name.text;

		CString CSProj;
		CString CSProjName;

		//使用新创建的方法来获取
		Ellipse.get_Prj_Type(CSProj);
		Ellipse.get_Prj_Name(CSProjName);

		CString CSName;
		CString Datum;
		CString strEllipse;

		CSName.Format(_T("%s"), EllipManager.m_OGRSpatialReference.GetAttrValue(_T("GEOGCS")));
		Datum.Format(_T("%s"), EllipManager.m_OGRSpatialReference.GetAttrValue(_T("DATUM")));
		strEllipse.Format(_T("%s"), EllipManager.m_OGRSpatialReference.GetAttrValue(_T("SPHEROID")));

		double SemiMajor = 0.0;
		double InvFlattening = 0.0;

		Ellipse.get_Major(SemiMajor);
        InvFlattening = EllipManager.m_OGRSpatialReference.GetInvFlattening();

		pDeuSRS.put_GeogCS(CSName, Datum, strEllipse, SemiMajor, InvFlattening);
		pDeuSRS.put_Projection(CSProj);
		pDeuSRS.put_LinearUnit(_T("Meter"));
		CString Angular = _T("Degree");
		pDeuSRS.put_AngularUnit(Angular);

		pDeuSRS.put_IsProject( TRUE );

		//投影参数
		double dbParam[5] = {
			500000,//东价值
			0,
			117,//中央子午线
			1,
			0
		};
			
		//double dbFalseEasting = _tstof(m_ProjectedSeries->_falseEasting._value.text);
		//double dbCentralMeridian = _tstof(m_ProjectedSeries->_centralMeridian._value.text);

		double dbFalseEasting;
		double dbCentralMeridian;
		
		Ellipse.get_False_E(dbFalseEasting);
		Ellipse.get_Centrol_Long(dbCentralMeridian);
		
		dbParam[0] = dbFalseEasting ;
		dbParam[2] = dbCentralMeridian ;

		int nCount = 5;
		pDeuSRS.putref_ProjParm(nCount , dbParam  );

		pDeuSRS.put_ProjeCS(CSProjName);
	}
	else if (_CoordinateType == GeoDetic)
	{
		/*
		p_GeodeticSeries m_GeodeticSeries;
		m_GeodeticSeries = GetGeoDeticObject(strName);

		CString CSName	= m_GeodeticSeries->_name.text;
		CString Datum	= m_GeodeticSeries->_datum._name.text;
		CString Ellipse = Datum;
		double SemiMajor= _tstof(m_GeodeticSeries->_datum._ellipsoid._semi_Major_Axis._value.text);
		double InvFlattening=_tstof(m_GeodeticSeries->_datum._ellipsoid._inverseFlattening.text);*/

		CString CSName;
		CString Datum;
		CString strEllipse;
		double SemiMajor = 0.0;
		double InvFlattening = 0.0;

		CSName.Format(_T("%s"), EllipManager.m_OGRSpatialReference.GetAttrValue(_T("GEOGCS")));
		Datum.Format(_T("%s"), EllipManager.m_OGRSpatialReference.GetAttrValue(_T("DATUM")));
		strEllipse = Datum;
		InvFlattening = EllipManager.m_OGRSpatialReference.GetInvFlattening();

		//CSName = strName;
        //Ellipse.get_Ellip_Name(Datum);
		//strEllipse = Datum;
		//Ellipse.get_Flatening(InvFlattening);
		Ellipse.get_Major(SemiMajor);

		//此处有点小问题 2013-01-09
		pDeuSRS.put_GeogCS(CSName,CSName,strEllipse,SemiMajor,InvFlattening);
		pDeuSRS.put_LinearUnit(_T("Meter"));

		CString Angular = _T("Degree");
		pDeuSRS.put_AngularUnit(Angular);
	}
	
	return pDeuSRS;
}

//add by chenyong 2013-01-09
CDeuUnits CDeuTaskProcess::GetUnit(SHORT InUnitType,SHORT OutUnitType)
{
	CString _in_unit_x = _T("");
	CString _in_unit_y = _T("");
	CString _in_unit_z = _T("");
	CString _out_unit_x = _T("");
	CString _out_unit_y = _T("");
	CString _out_unit_z = _T("");

	CDeuUnits pDeuUnits;

	switch(InUnitType)
	{
	case GEODETIC:
		_in_unit_x = _T("D");
		_in_unit_y = _T("D");
		_in_unit_z = _T("M");

		break;
	case GEOCENTRIC:
		_in_unit_x = _T("M");
		_in_unit_y = _T("M");
		_in_unit_z = _T("M");

		break;
	case PLANE: 
		_in_unit_x = _T("M");
		_in_unit_y = _T("M");
		_in_unit_z = _T("M");

		break;	

	default:
		break;
	}

	switch(OutUnitType)
	{
	case GEODETIC:
		_out_unit_x = _T("D");
		_out_unit_y = _T("D");
		_out_unit_z = _T("M");
		break;
	case GEOCENTRIC:
		_out_unit_x = _T("M");
		_out_unit_y = _T("M");
		_out_unit_z = _T("M");
		break;
	case PLANE: 
		_out_unit_x = _T("M");
		_out_unit_y = _T("M");
		_out_unit_z = _T("M");
		break;	
	default:
		break;
	}

	pDeuUnits.put_Unit_X(_in_unit_x);
	pDeuUnits.put_Unit_Y(_in_unit_y);
	pDeuUnits.put_Unit_Z(_in_unit_z);
	pDeuUnits.put_Unit_desX(_out_unit_x);
	pDeuUnits.put_Unit_desY(_out_unit_y);
	pDeuUnits.put_Unit_desZ(_out_unit_z);

	return pDeuUnits;
}

//add by chenyong 2013-01-09
CDeuCoordType  CDeuTaskProcess::GetCoordType(SHORT SrcType,SHORT DestType,SHORT CtrlPtType )
{
	CDeuCoordType CoordType;
	
	CoordType.putref_CtrlPtCoordType( CtrlPtType );
	CoordType.putref_CoordType( SrcType );
	CoordType.putref_DestCoordType( DestType );

	return CoordType;
}

//add by chenyong 2013-01-10
CSevenParams CDeuTaskProcess::GetSevenParam(double *_7param)
{
	CSevenParams pSevenParam;
		
	pSevenParam.putref_DX(_7param[0]);
	pSevenParam.putref_DY(_7param[1]);
	pSevenParam.putref_DZ(_7param[2]);
	pSevenParam.putref_RX(_7param[3]);
	pSevenParam.putref_RY(_7param[4]);
	pSevenParam.putref_RZ(_7param[5]);
	pSevenParam.putref_ScalM(_7param[6]);

	return pSevenParam;
}

//add by chenyong 2013-01-10
void CDeuTaskProcess::Task_Calculate7Param(SHORT aMode,
										   SHORT CtrlPtCoordType,
										   SHORT UnitType,
										   const CDeuEllipse& pSrcEllip,
										   const CDeuEllipse& pDesEllip,
										   int iCount,
										   double *x,
										   double *y ,
										   double *z,
										   double *x2,
										   double *y2,
										   double *z2,
										   double *residual_x,
										   double *residual_y,
										   double *residual_z,
										   double *residual,
										   double *_7param
										   )
{
	CDeuCoordType pCoordType = GetCoordType(CtrlPtCoordType,CtrlPtCoordType,CtrlPtCoordType);
	CDeuUnits pUnit = GetUnit(UnitType,UnitType);
	CSevenParams pSevenParam = GetSevenParam(_7param);
	CDeuTrans trans;   

	trans.putref_DeuCoordType(pCoordType);
	trans.putref_DeuEllipse(pSrcEllip);		
	trans.putref_DeuDestEllipse(pDesEllip);
	trans.putref_DeuUnits(pUnit);
	trans.put_TransModel(aMode);

	//坐标单位转为弧度/米，然后求得该模型下的参数
	//double* _7param=new double[7];
	ULONG _npara ;
	HRESULT m_hr_status;

	//输入第一组控制点坐标类型，第二组控制点坐标类型，在空间直角下得到7参数
	m_hr_status = trans.CalculateParam(iCount, x, y, z, x2, y2, z2, _7param, &_npara);
	if (m_hr_status == E_FAIL_PRIVILEGE_UID)
	{
		AfxMessageBox(UseAuthError);
		return;
	}
	else if (m_hr_status == E_FAIL_PRIVILEGE_EXTENT)
	{
		AfxMessageBox(UseBeyoundError);
		return;
	}

	//doc->_7param=_7param;
	//new 7param
	//m_seven_param
	pSevenParam.putref_DX(_7param[0]);
	pSevenParam.putref_DY(_7param[1]);
	pSevenParam.putref_DZ(_7param[2]);
	pSevenParam.putref_RX(_7param[3]);
	pSevenParam.putref_RY(_7param[4]);
	pSevenParam.putref_RZ(_7param[5]);
	pSevenParam.putref_ScalM(_7param[6]);

	double* des_x=new double[iCount];
	double* des_y=new double[iCount];
	double* des_z=new double[iCount];

	//7参数和第一组控制点坐标类型，得到转换后的第二组坐标, 转换后坐标类型与控制点坐标类型相同
	trans.putref_Param(_7param);
	trans.CoordTransPoints(_7param, iCount, x, y, z, des_x, des_y, des_z);

	/*if(m_hr_status == E_FAIL_PRIVILEGE_UID)
	{
	AfxMessageBox(UseAuthError);
	return;
	}
	else if(m_hr_status == E_FAIL_PRIVILEGE_EXTENT)
	{
	AfxMessageBox(UseBeyoundError);
	return;
	}*/

	//double* res_x=new double[iCount];
	//double* res_y=new double[iCount];
	//double* res_z=new double[iCount];
	//double* _residual=new double[iCount];

	//原始单位下的转换后坐标
	double* des_x_ori_unit=new double[iCount];
	double* des_y_ori_unit=new double[iCount];
	double* des_z_ori_unit=new double[iCount];

	trans.CalculateResidual(iCount, x2, y2, z2, des_x, des_y, des_z, residual_x, residual_y, residual_z, residual);
	/*if(m_hr_status == E_FAIL_PRIVILEGE_UID)
	{
	AfxMessageBox(UseAuthError);
	return;
	}
	else if(m_hr_status == E_FAIL_PRIVILEGE_EXTENT)
	{
	AfxMessageBox(UseBeyoundError);
	return;
	}*/

	delete[] des_x;
	delete[] des_y;
	delete[] des_z;

	delete[] des_x_ori_unit;
	delete[] des_y_ori_unit;
	delete[] des_z_ori_unit;

	return ;
}

/*
===================================================
 功能:	 	矢量综合参数计算(四参数，七参数..etc)
 参数:		in SHORT aMode,
			in SHORT CtrlPtCoordType,
			in SHORT UnitType,
			in IDeuEllipse *pSrcEllip,
			in IDeuEllipse *pDestEllip,
			in int iCount,
			in double *x,
			in double *y ,
			in double *z,
			in double *x2,
			in double *y2,
			in double *z2,
			in double *residual_x,
			in double *residual_y,
			in double *residual_z,
			in double *residual,
			out double *_param,
			in ULONG  *np
	
 返回:	 	 ---
 程序逻辑:   ---
 日期:		2011-01-05
 备注:		add by hushichen
=================================================
*/
void CDeuTaskProcess::Task_VectorCalculate7Param(SHORT aMode,
												 SHORT CtrlPtCoordType,
												 SHORT UnitType,
												 const CDeuEllipse& pSrcEllip,
												 const CDeuEllipse& pDesEllip,
												 int iCount,
												 double *x,
												 double *y ,
												 double *z,
												 double *x2,
												 double *y2,
												 double *z2,
												 double *residual_x,
												 double *residual_y,
												 double *residual_z,
												 double *residual,
												 double *_param,
												 double *_inv_param,
												 ULONG  *np)
{


	//if (pSrcEllip == NULL || pDesEllip == NULL)
	//{
	//	//MessageBox(m_pMainFrm->m_hWnd,"输入椭球参数不正确！","错误",MB_OK | MB_ICONWARNING);
	//	AfxMessageBox("输入椭球参数不正确！");
	//	return ;
	//}

	CDeuCoordType pCoordType = GetCoordType(CtrlPtCoordType,CtrlPtCoordType,CtrlPtCoordType);
	CDeuUnits pUnit = GetUnit(UnitType,UnitType);

	//if (pUnit == NULL || pCoordType == NULL)
	//{
	//	//MessageBox(m_pMainFrm->m_hWnd,"输入坐标参数不正确！","错误",MB_OK | MB_ICONWARNING);
	//	AfxMessageBox("输入坐标参数不正确！");
	//	return ;
	//}

	//ISevenParams *pSevenParam = GetSevenParam(_param);
	//if(CheckData(pdeuData,DEUMAINFRM.m_hWnd)==FALSE)
	//{
	//	//MessageBox(mainframe->m_hWnd,L"输入参数不正确！转换中止，请检查参数！",L"错误",MB_OK | MB_ICONWARNING);
	//	return;
	//}

	CDeuTrans trans ;   

	//IDeuCoordType* _coord_type=NULL;		
	//_coord_type=pdeuData->m_Deu_coord_type;

	////并设置转换前后，坐标类型为空间直角
	//SHORT ctrl_type;
	//_coord_type->get_CtrlPtCoordType(&ctrl_type);
	//_coord_type->putref_CoordType(ctrl_type);
	//_coord_type->putref_DestCoordType(ctrl_type);

	trans.putref_DeuCoordType(pCoordType);
	trans.putref_DeuEllipse(pSrcEllip);		
	trans.putref_DeuDestEllipse(pDesEllip);
	trans.putref_DeuUnits(pUnit);
	//trans->putref_SevenParams(pSevenParam);
	trans.put_TransModel(aMode);

	//坐标单位转为弧度/米，然后求得该模型下的参数
	//double* _7param=new double[7];
	//输入第一组控制点坐标类型，第二组控制点坐标类型，在空间直角下得到7参数

	trans.CalculateParam(iCount,x,y,z,x2,y2,z2,_param,np);
	//doc->_7param=_7param;

	//new 7param
	trans.CalculateParam(iCount,x2,y2,z2,x,y,z,_inv_param,np);

	double* des_x=new double[iCount];
	double* des_y=new double[iCount];
	double* des_z=new double[iCount];

	//7参数和第一组控制点坐标类型，得到转换后的第二组坐标, 转换后坐标类型与控制点坐标类型相同
	trans.CoordTransPoints(_param,iCount,x,y,z,des_x,des_y,des_z);

	//double* res_x=new double[iCount];
	//double* res_y=new double[iCount];
	//double* res_z=new double[iCount];
	//double* _residual=new double[iCount];

	//原始单位下的转换后坐标
	double* des_x_ori_unit=new double[iCount];
	double* des_y_ori_unit=new double[iCount];
	double* des_z_ori_unit=new double[iCount];

	trans.CalculateResidual(iCount,x2,y2,z2,des_x,des_y,des_z,residual_x,residual_y,residual_z,residual);

	//residual=_residual;
	//residual_x=res_x;
	//residual_y=res_y;
	//residual_z=res_z;

	delete[] des_x;
	delete[] des_y;
	delete[] des_z;

	delete[] des_x_ori_unit;
	delete[] des_y_ori_unit;
	delete[] des_z_ori_unit;
	//trans->ReleaseDispatch();

	return ;
}

/*
===================================================
 功能:	 	 栅格综合参数计算(四参数，七参数..etc)
 参数:		 in SHORT aMode,
			 in SHORT CtrlPtCoordType,
			 in SHORT UnitType,
			 in IDeuEllipse *pSrcEllip,
			 in IDeuEllipse *pDestEllip,
			 in int iCount,
			 in double *x,
			 in double *y ,
			 in double *z,
			 in double *x2,
			 in double *y2,
			 in double *z2,
			 in double *residual_x,
			 in double *residual_y,
			 in double *residual_z,
			 in double *residual,
			 out double *_7param	
			 out double *_inv_param,
			 in ULONG*	npara
	
 返回:		---
 程序逻辑:
 日期:		2011-01-05
 备注:		add by hushichen
=================================================
*/
void CDeuTaskProcess::Task_RasterCalculate7Param(	SHORT aMode,
												    SHORT CtrlPtCoordType,
												    SHORT UnitType,
												    const CDeuEllipse& pSrcEllip,
												    const CDeuEllipse& pDesEllip,
													int iCount,
													double *x,
													double *y,
													double *z,
													double *x2,
													double *y2,
													double *z2,
													double *residual_x,
													double *residual_y,
													double *residual_z,
													double *residual,
													double *_param,
													double *_inv_param,
													ULONG*	npara
													)
{
	//if (pSrcEllip == NULL || pDesEllip == NULL)
	//{
	//	//MessageBox(m_pMainFrm->m_hWnd,"输入椭球参数不正确！","错误",MB_OK | MB_ICONWARNING);
	//	AfxMessageBox("输入椭球参数不正确！");
	//	return ;
	//}

	CDeuCoordType pCoordType = GetCoordType(CtrlPtCoordType,CtrlPtCoordType,CtrlPtCoordType);
	CDeuUnits pUnit = GetUnit(UnitType,UnitType);
	//if (pUnit == NULL || pCoordType == NULL)
	//{
	//	//MessageBox(m_pMainFrm->m_hWnd,"输入坐标参数不正确！","错误",MB_OK | MB_ICONWARNING);
	//	AfxMessageBox("输入坐标参数不正确！");
	//	return ;
	//}
	//if(CheckData(pdeuData,DEUMAINFRM.m_hWnd)==FALSE)
	//{
	//	//MessageBox(mainframe->m_hWnd,L"输入参数不正确！转换中止，请检查参数！",L"错误",MB_OK | MB_ICONWARNING);
	//	return;
	//}

	CDeuRasterTrans pRasterTrans;
	CDeuTrans pVectorTrans;
	long hr ;

	switch(aMode)
	{
	case MODEL_D2P4	:		//二维四参数
	case MODEL_BURSA:		//三维布尔沙
		{
			//IDeuCoordType* _coord_type=NULL;		
			//_coord_type=pdeuData->m_Deu_coord_type;

			////并设置转换前后，坐标类型为空间直角
			//SHORT ctrl_type;
			//_coord_type->get_CtrlPtCoordType(&ctrl_type);
			//_coord_type->putref_CoordType(ctrl_type);
			//_coord_type->putref_DestCoordType(ctrl_type);

			pVectorTrans.putref_DeuCoordType(pCoordType);
			pVectorTrans.putref_DeuEllipse(pSrcEllip);		
			pVectorTrans.putref_DeuDestEllipse(pDesEllip);
			pVectorTrans.putref_DeuUnits(pUnit);

			if(aMode == MODEL_TRANS_ALL_AFFINE)
				aMode = MODEL_TRANS_ALL_AFFINE;

			pVectorTrans.put_TransModel(aMode);

			//坐标单位转为弧度/米，然后求得该模型下的参数
			//double* _7param=new double[7];
			//输入第一组控制点坐标类型，第二组控制点坐标类型，在空间直角下得到7参数
			hr = pVectorTrans.CalculateParam(iCount,x,y,z,x2,y2,z2,_param, npara);
			if(hr == E_FAIL_PRIVILEGE_UID)
			{
				AfxMessageBox(UseAuthError);
				return;
			}
			else if(hr == E_FAIL_PRIVILEGE_EXTENT)
			{
				AfxMessageBox(UseBeyoundError);
				return;
			}

			//求逆参数
			//设置逆参数椭球
			pVectorTrans.putref_DeuEllipse(pDesEllip);		
			pVectorTrans.putref_DeuDestEllipse(pSrcEllip);

			hr = pVectorTrans.CalculateParam(iCount,x2,y2,z2,x,y,z,_inv_param,npara);
			if(hr == E_FAIL_PRIVILEGE_UID)
			{
				AfxMessageBox(UseAuthError);
				return;
			}
			else if(hr == E_FAIL_PRIVILEGE_EXTENT)
			{
				AfxMessageBox(UseBeyoundError);
				return;
			}
			//doc->_7param=_7param;
			//new 7param
			double* des_x=new double[iCount];
			double* des_y=new double[iCount];
			double* des_z=new double[iCount];

			//7参数和第一组控制点坐标类型，得到转换后的第二组坐标, 转换后坐标类型与控制点坐标类型相同
			pVectorTrans.putref_DeuEllipse(pSrcEllip);		
			pVectorTrans.putref_DeuDestEllipse(pDesEllip);
			pVectorTrans.CoordTransPoints(_param,iCount,x,y,z,des_x,des_y,des_z);
			/*if(m_hr_status == E_FAIL_PRIVILEGE_UID)
			{
			AfxMessageBox(UseAuthError);
			return;
			}
			else if(m_hr_status == E_FAIL_PRIVILEGE_EXTENT)
			{
			AfxMessageBox(UseBeyoundError);
			return;
			}*/

			//double* res_x=new double[iCount];
			//double* res_y=new double[iCount];
			//double* res_z=new double[iCount];
			//double* _residual=new double[iCount];

			//原始单位下的转换后坐标
			double* des_x_ori_unit=new double[iCount];
			double* des_y_ori_unit=new double[iCount];
			double* des_z_ori_unit=new double[iCount];

			pVectorTrans.CalculateResidual(iCount,x2,y2,z2,des_x,des_y,des_z,residual_x,residual_y,residual_z,residual);
			/*if(m_hr_status == E_FAIL_PRIVILEGE_UID)
			{
			AfxMessageBox(UseAuthError);
			return;
			}
			else if(m_hr_status == E_FAIL_PRIVILEGE_EXTENT)
			{
			AfxMessageBox(UseBeyoundError);
			return;
			}*/

			delete[] des_x;
			delete[] des_y;
			delete[] des_z;

			delete[] des_x_ori_unit;
			delete[] des_y_ori_unit;
			delete[] des_z_ori_unit;
			//trans->ReleaseDispatch();
		}
		break;
	case MOD_AFFINE			://仿射变换
	case MOD_POLYNOMIAL1	://一阶多项式
	case MOD_POLYNOMIAL2	://二阶多项式
	case MOD_POLYNOMIAL3	://三阶多项式
	case MOD_POLYNOMIAL4	://四阶多项式
		{
			//IDeuCoordType* _coord_type=NULL;		
			//_coord_type=pdeuData->m_Deu_coord_type;
			////并设置转换前后，坐标类型为空间直角
			//SHORT ctrl_type;
			//_coord_type->get_CtrlPtCoordType(&ctrl_type);
			//_coord_type->putref_CoordType(ctrl_type);
			//_coord_type->putref_DestCoordType(ctrl_type);

			pRasterTrans.putref_DeuCoordType(pCoordType);
			pRasterTrans.putref_DeuEllipse(pSrcEllip);		
			pRasterTrans.putref_DeuDestEllipse(pDesEllip);
			pRasterTrans.putref_DeuUnits(pUnit);

			if(aMode == MODEL_TRANS_ALL_AFFINE)
				aMode = MODEL_TRANS_ALL_AFFINE;

			pRasterTrans.put_TransModel(aMode);

			//坐标单位转为弧度/米，然后求得该模型下的参数
			//double* _7param=new double[7];
			//输入第一组控制点坐标类型，第二组控制点坐标类型，在空间直角下得到7参数
			pRasterTrans.CalculateParam(iCount,x,y,z,x2,y2,z2,_param, npara);
			/*if(m_hr_status == E_FAIL_PRIVILEGE_UID)
			{
			AfxMessageBox(UseAuthError);
			return;
			}
			else if(m_hr_status == E_FAIL_PRIVILEGE_EXTENT)
			{
			AfxMessageBox(UseBeyoundError);
			return;
			}*/

			//求逆参数
			//设置逆参数椭球
			/*pVectorTrans->putref_DeuEllipse(pDesEllip);		
			pVectorTrans->putref_DeuDestEllipse(pSrcEllip);*/

			pRasterTrans.CalculateParam(iCount,x2,y2,z2,x,y,z,_inv_param,npara);
			/*if(m_hr_status == E_FAIL_PRIVILEGE_UID)
			{
			AfxMessageBox(UseAuthError);
			return;
			}
			else if(m_hr_status == E_FAIL_PRIVILEGE_EXTENT)
			{
			AfxMessageBox(UseBeyoundError);
			return;
			}*/
			//doc->_7param=_7param;
			//new 7param
			double* des_x=new double[iCount];
			double* des_y=new double[iCount];
			double* des_z=new double[iCount];

			//7参数和第一组控制点坐标类型，得到转换后的第二组坐标, 转换后坐标类型与控制点坐标类型相同
			/*pVectorTrans->putref_DeuEllipse(pSrcEllip);		
			pVectorTrans->putref_DeuDestEllipse(pDesEllip);*/

			pRasterTrans.CoordTransPoints(_param,iCount,x,y,z,des_x,des_y,des_z);
			/*if(m_hr_status == E_FAIL_PRIVILEGE_UID)
			{
			AfxMessageBox(UseAuthError);
			return;
			}
			else if(m_hr_status == E_FAIL_PRIVILEGE_EXTENT)
			{
			AfxMessageBox(UseBeyoundError);
			return;
			}*/

			//double* res_x=new double[iCount];
			//double* res_y=new double[iCount];
			//double* res_z=new double[iCount];
			//double* _residual=new double[iCount];

			//原始单位下的转换后坐标
			double* des_x_ori_unit=new double[iCount];
			double* des_y_ori_unit=new double[iCount];
			double* des_z_ori_unit=new double[iCount];

			pRasterTrans.CalculateResidual(iCount,x2,y2,z2,des_x,des_y,des_z,residual_x,residual_y,residual_z,residual);
			/*if(m_hr_status == E_FAIL_PRIVILEGE_UID)
			{
			AfxMessageBox(UseAuthError);
			return;
			}
			else if(m_hr_status == E_FAIL_PRIVILEGE_EXTENT)
			{
			AfxMessageBox(UseBeyoundError);
			return;
			}*/

			delete[] des_x;
			delete[] des_y;
			delete[] des_z;

			delete[] des_x_ori_unit;
			delete[] des_y_ori_unit;
			delete[] des_z_ori_unit;
			//trans->ReleaseDispatch();
		}
		break;
	default:
		break;
	};

	return ;
}

BOOL CDeuTaskProcess::Task_RasterTransFormDEM(CDeuRasterTranDlg * pRasterDlg)
{
	if (g_ThreadFinished == FALSE )
	{
		return FALSE;
	}

	//为每一个转换开启一个线程
	HANDLE Thread;
	DWORD dwThreadId;

	Thread=::CreateThread(NULL,0,ThreadFunc_RasterDEM,pRasterDlg,0,&dwThreadId);
	
	::CloseHandle(Thread);

	return TRUE;
}

//ThreadFunc_RasterDEM
DWORD WINAPI ThreadFunc_RasterDEM(HANDLE Thread)
{
	g_ThreadFinished = FALSE ;
	CDeuRasterTranDlg *pRasterDlg = (CDeuRasterTranDlg*)Thread;

	//1. 准备源和目标 坐标系数据
	CString strSrc, strDest;
	pRasterDlg->m_edit_InCoord.GetWindowText(strSrc);
	pRasterDlg->m_edit_OutCoord.GetWindowText(strDest);

	//1.1 匹配坐标系转换的类型
	__COORDTYPE _type_src  = TaskProc.FindCoordindateType(strSrc);
	__COORDTYPE _type_dest = TaskProc.FindCoordindateType(strDest);
	CDeuEllipse pSrcEllip = TaskProc.GetDeuEllipse((_type_src==PLANE)?GeoProjected:GeoDetic, strSrc);
	CDeuEllipse pDesEllip = TaskProc.GetDeuEllipse((_type_dest==GEODETIC)?GeoDetic:GeoProjected, strDest);
	/*if (pSrcEllip == NULL || pDesEllip == NULL)
	{
		MessageBox(pRasterDlg->m_hWnd, "输入椭球参数不正确！转换中止，请检查参数！", "错误",MB_OK | MB_ICONWARNING);
		return -1;
	}*/

	//2. 坐标类型
	CDeuCoordType pCoordType = TaskProc.GetCoordType(_type_src, _type_dest,0);

	//3. 准备的单位值对象
	CDeuUnits pUnit = TaskProc.GetUnit(_type_src, _type_dest);

	/*if (pUnit == NULL || pCoordType == NULL)
	{
		MessageBox(pRasterDlg->m_hWnd, "输入坐标参数不正确！转换中止，请检查参数！", "错误",MB_OK | MB_ICONWARNING);
		return -1;
	}*/

	/*
		获取空间参考信息
		参数说明：
			1. 获取坐标类型
			2. 坐标名
	*/
	CDeuSpatialReference pSRS = TaskProc.GetSRS(TaskProc.FindCoordinateType(strDest), strDest);
	CDeuRasterTrans trans;   
	CString _src = _T("");
	CString _des = _T("");
	CString _in_driver = _T("");
	CString _out_driver = _T("");
	CString strDriver_Src = _T("");
	CString strDriver_Dest = _T("");

	pRasterDlg->m_ComboInput.GetWindowText(strDriver_Src);
	pRasterDlg->m_ComboOutput.GetWindowText(strDriver_Dest);
	_in_driver  = strDriver_Src;
	_out_driver = strDriver_Dest;

	trans.putref_DeuCoordType(pCoordType);
	trans.putref_DeuEllipse(pSrcEllip);
	trans.putref_DeuDestEllipse(pDesEllip);

	trans.putref_DeuUnits(pUnit);
	trans.put_TransModel(pRasterDlg->iModel);
	trans.put_Resampling(pRasterDlg->iReCollect);		
	trans.putref_DeuSRS(pSRS);

	//———————————————格网处理流程BEGIN————————————
	/*判断是否格网转换,
	若是:
	传参;
	否则:继续下一句.
	*/

	if ((pRasterDlg->iModel) == MODEL_GRID)
	{	
		trans.InitGridTranslate(pRasterDlg->m_Controlpoint_Dlg.m_GridParameter);
	}

	double * pParam = pRasterDlg->m_Controlpoint_Dlg.m_7param ;
	double * invParam = pRasterDlg->m_Controlpoint_Dlg.m_Invpara ;

	double srcMajor = 0;
	pSrcEllip.get_Major( srcMajor );

	SHORT srcCoordType = 0;
	pCoordType.get_CoordType( srcCoordType ) ; 

	trans.putref_Param(pParam);
	trans.putref_InvParam(invParam);
	trans.RegisterWnd((LONGLONG)pRasterDlg->m_hWnd);

	CString strInPath = _T("");
	CString strOutPath = _T("");
	pRasterDlg->m_edit_InputFile.GetWindowText(strInPath);
	pRasterDlg->m_edit_OutputFile.GetWindowText(strOutPath);

	CString m_in_Path     = strInPath;
	CString m_out_Path    = strOutPath;
	CString bstrDriver    = strDriver_Src;
	CString bstrDriverOut = strDriver_Dest;

	//转文件 备注：目前只转换文件	
	if(pRasterDlg->_FilsList_selected.GetCount() == 0)
	{	
		MessageBox(pRasterDlg->m_hWnd, "无转换文件，请检查文件！", "系统提示", MB_OK|MB_ICONEXCLAMATION);
		g_ThreadFinished = TRUE ;
		return 0;
	}

	pRasterDlg->ShowStatusPanel("——————————————————栅格文件DEM转换——————————————————\r\n");

	double StartTick(0), EndTick(0);
	char szBeginTime[10], szEndTime[10];

	//这里需要对单个转换结束后的文件进行任务描述移除
	HRESULT m_hr_status;
	CString  str, strFile,strMsg;
	for(int n=0; n<pRasterDlg->_FilsList_selected.GetCount(); n++)
	{
		_src = pRasterDlg->_FilsList_selected.GetAt(n);
		_des = _src;
		
		strFile = pRasterDlg->_FilsList_selected.GetAt(n);
		//strFile = strFile.Mid(strFile.ReverseFind('\\')+1);
		strFile = strFile.Mid(strInPath.GetLength()+1);
		//strFile = strFile.Mid(0, strFile.ReverseFind('.'));
		_src = strFile;
		_des = strFile;

		StartTick = ::GetTickCount();
		ZeroMemory(szBeginTime, sizeof(szBeginTime));
		GetSysCurrentTime(szBeginTime);
		m_hr_status = trans.CoordTransDEMEntry(_src, m_in_Path, _in_driver,  	/*源文件*/
												_des, m_out_Path,_out_driver);	/*目标文件*/

		EndTick = GetTickCount();
		double Result = (EndTick - StartTick)*0.001;
		ZeroMemory(szEndTime, sizeof(szEndTime));
		GetSysCurrentTime(szEndTime);

		if(m_hr_status == E_FAIL_PRIVILEGE_UID)
		{
			strMsg.Format(_T("%s\r\n开始时间：%s\r\n结束时间：%s\r\n%s\r\n%s%.2lf%s\r\n"), _src, szBeginTime, szEndTime, UseAuthError,_T("耗时:"), Result, _T("秒"));
			pRasterDlg->ShowStatusPanel(strMsg);
			continue;
		}
		else if(m_hr_status == E_FAIL_PRIVILEGE_EXTENT)
		{
			strMsg.Format(_T("%s\r\n开始时间：%s\r\n结束时间：%s\r\n%s\r\n%s%.2lf%s\r\n"), _src, szBeginTime, szEndTime, UseBeyoundError,_T("耗时:"), Result, _T("秒"));
			pRasterDlg->ShowStatusPanel(strMsg);
			continue;
		}

		strMsg.Format(_T("%s\r\n开始时间：%s\r\n结束时间：%s\r\n%s%.2lf%s\r\n"), _src, szBeginTime, szEndTime, _T("耗时:"), Result, _T("秒"));
		pRasterDlg->ShowStatusPanel(strMsg);
	}

	pRasterDlg->TranformOver();
		
	g_ThreadFinished = TRUE ;

	return 0;
}

BOOL CDeuTaskProcess::Task_VectorTransForm(CDeuVectorTranDlg* pVecDlg)
{	
	if (!g_ThreadFinished)
	{
		return g_ThreadFinished;
	}

	HANDLE Thread = ::CreateThread(NULL, 0, ThreadVector, pVecDlg, 0, NULL);
	if (NULL != Thread)
	{
		::CloseHandle(Thread);
	}
	
	return TRUE;
}

DWORD WINAPI ThreadVector(HANDLE _handle)
{
	::CoInitialize(NULL);

	g_ThreadFinished = FALSE;
	CDeuVectorTranDlg *pVecDlg = (CDeuVectorTranDlg*)_handle;

	//1. 准备源和目标 坐标系数据
	CString strSrc = _T(""); 
	CString strDest = _T("");
	CString strDriver_Src = _T("");
	CString	strDriver_Dest = _T("");

	pVecDlg->m_ComboInput.GetWindowText(strDriver_Src);
	pVecDlg->m_ComboOutput.GetWindowText(strDriver_Dest);
	pVecDlg->m_edit_InCoord.GetWindowText(strSrc);	
	pVecDlg->m_edit_OutCoord.GetWindowText(strDest);

	//1.1 匹配坐标系转换的类型
	__COORDTYPE _type_src = TaskProc.FindCoordindateType(strSrc);
	__COORDTYPE _type_dest = TaskProc.FindCoordindateType(strDest);
	CDeuEllipse pSrcEllip = TaskProc.GetDeuEllipse((_type_src==PLANE)?GeoProjected:GeoDetic, strSrc);
	CDeuEllipse pDesEllip = TaskProc.GetDeuEllipse((_type_dest==GEODETIC)?GeoDetic:GeoProjected, strDest);
	CDeuCoordType pCoordType = TaskProc.GetCoordType(_type_src, _type_dest, 0);

	//准备的单位值对象
	CDeuUnits pUnit = TaskProc.GetUnit(_type_src, _type_dest);

	//yzg 2012-9-26 增加对EXCEL文件转换的支持 只要目标转换文件是Excel 需要判断是否进行了行列设置 begin
	if (strDriver_Dest == _T("Excel"))
	{
		//需要判断是否进行了参数设置
		if (pVecDlg->m_Controlpoint_Dlg.m_install == FALSE)
		{
			MessageBox(pVecDlg->m_hWnd, "进行EXCEL转换时,需要进行EXCEL格式的参数设置,请点击[设置]！转换中止！", "系统提示", MB_OK|MB_ICONEXCLAMATION);
			pVecDlg->EnbleAllController();
			g_ThreadFinished = TRUE ;
			return -1;
		}
	}
	//yzg 2012-9-26 增加对EXCEL文件转换的支持 只要目标转换文件是Excel 需要判断是否进行了行列设置 end

	double * pParam = pVecDlg->m_Controlpoint_Dlg.m_7param;
	double srcMajor = 0;
	pSrcEllip.get_Major( srcMajor );

	short srcCoordType = 0;
	pCoordType.get_CoordType( srcCoordType ) ; 

	/*
	获取空间参考信息
	参数说明：
	1. 获取坐标类型
	2. 坐标名
	*/
	CDeuSpatialReference pSRS = TaskProc.GetSRS(TaskProc.FindCoordinateType(strDest), strDest);
	CDeuTrans trans;
	CString _src = _T("");
	CString _des = _T("");
	CString _in_driver = _T("");
	CString _out_driver = _T("");

	_in_driver  = strDriver_Src;
	_out_driver = strDriver_Dest;

	//初始化连接池
	CString strDBSrc = _T("");
	CString strDBDest = _T("");

	strDBSrc.Format("OCI:%s/%s@%s", pVecDlg->strDBUser_Src, pVecDlg->strDBPwd_Src, pVecDlg->strDBSid_Src);
	strDBDest.Format("OCI:%s/%s@%s", pVecDlg->strDBUser_Dest, pVecDlg->strDBPwd_Dest, pVecDlg->strDBSid_Dest);

	if(pVecDlg->IsAdditional)
	{
		strDBSrc += ":";
		strDBDest += ":";
		for(int n=0; n<pVecDlg->_TablesList_selected.GetCount(); n++)
		{
			strDBSrc += pVecDlg->_TablesList_selected.GetAt(n)+",";
			strDBDest += pVecDlg->_TablesList_selected.GetAt(n)+",";
		}
	}
	else
	{
		strDBSrc.Format("OCI:%s/%s@%s", pVecDlg->strDBUser_Src, pVecDlg->strDBPwd_Src, pVecDlg->strDBSid_Src);
		strDBDest.Format("OCI:%s/%s@%s", pVecDlg->strDBUser_Dest, pVecDlg->strDBPwd_Dest, pVecDlg->strDBSid_Dest);
	}

	strDBSrc  = strDBSrc.TrimRight(',');
	strDBDest = strDBDest.TrimRight(',');
	TaskProc.InitConnPool(strDBSrc);
	TaskProc.InitConnPool(strDBDest);

	trans.putref_DeuCoordType(pCoordType);
	trans.putref_DeuEllipse(pSrcEllip);
	trans.putref_DeuDestEllipse(pDesEllip);
	trans.putref_DeuUnits(pUnit);
	trans.putref_Param(pParam);
	trans.putref_DeuSRS(&pSRS);
	trans.putref_ConnPool(g_ConnPool);		
	trans.RegisterWnd((LONGLONG)pVecDlg->m_hWnd);
	trans.put_TransModel(pVecDlg->iModel);

	//如果目标转换的文件是Excel 则需要填入目标文件类型 yzg 2012-9-25 begin
	trans.putref_Excel(pVecDlg->m_Controlpoint_Dlg.m_t_format);
	//如果目标转换的文件是Excel 则需要填入目标文件类型 yzg 2012-9-25 end

	/*判断是否格网转换,
	若是:
	传参;
	否则:继续下一句.
	*/

	//如果是格网转换则初始化控制格网转换参数的类
	if ((pVecDlg->iModel) == MODEL_GRID)
	{
		trans.InitGridTranslate(pVecDlg->m_Controlpoint_Dlg.m_GridParameter);
	}

	CString strInPath = _T("");
	CString strOutPath = _T("");
	pVecDlg->m_edit_InputFile.GetWindowText(strInPath);
	pVecDlg->m_edit_OutputFile.GetWindowText(strOutPath);

	double StartTick(0), EndTick(0);
	char szBeginTime[10], szEndTime[10];

	if (strDriver_Src == sz_TranType_Vector[4])
	{
		pVecDlg->ShowStatusPanel("——————————————————矢量数据库数据转换——————————————————\r\n");
		if(pVecDlg->_TablesList_selected.GetCount() == 0){
			MessageBox(pVecDlg->m_hWnd, "无转换任务", "系统提示", MB_OK|MB_ICONEXCLAMATION);
			pVecDlg->TranFinish("转换终止");
			g_ThreadFinished = TRUE ;
			return -1;
		}

		CString strMsg;
		CString b_dbsrc = strDBSrc;
		CString b_dbdest = strDBDest;

		for(int n=0; n<pVecDlg->_TablesList_selected.GetCount(); n++)
		{
			_src = pVecDlg->_TablesList_selected.GetAt(n);
			_des = _src;

			StartTick = ::GetTickCount();
			ZeroMemory(szBeginTime, sizeof(szBeginTime));
			GetSysCurrentTime(szBeginTime);

			strSrc = _src;
			HRESULT m_hr_status = trans.CoordTransDBEntry(_src, b_dbsrc, _in_driver,		/* 源数据库连接串 strDBSrc */
															_des, b_dbdest, _out_driver);	/* 目数据库连接串 strDBDest */
			EndTick = GetTickCount();
			ZeroMemory(szEndTime, sizeof(szEndTime));
			GetSysCurrentTime(szEndTime);
			double Result = (EndTick - StartTick)*0.001;

			//授权错误
			if(m_hr_status == E_FAIL_PRIVILEGE_UID)
			{
				strMsg.Format(_T("%s\r\n开始时间：%s\r\n结束时间：%s\r\n%s\r\n%s%.2lf%s\r\n"), strSrc, szBeginTime, szEndTime, UseAuthError,_T("耗时:"), Result, _T("秒"));
				pVecDlg->ShowStatusPanel(strMsg);
				continue;
			}
			else if(m_hr_status == E_FAIL_PRIVILEGE_EXTENT) //超出范围
			{
				strMsg.Format(_T("%s\r\n开始时间：%s\r\n结束时间：%s\r\n%s\r\n%s%.2lf%s\r\n"), strSrc, szBeginTime, szEndTime, UseBeyoundError,_T("耗时:"), Result, _T("秒"));
				pVecDlg->ShowStatusPanel(strMsg);
				continue;
			}

			strMsg.Format(_T("正在更新表 %s 请稍后...\r\n"), strSrc);
			pVecDlg->ShowStatusPanel(strMsg);

			//更新注记
			//CString strSrcConn = "Provider=oraoledb.oracle.1; Data Source="+pVecDlg->strDBSid_Src+"; User Id="+pVecDlg->strDBUser_Src+"; Password="+pVecDlg->strDBPwd_Src+"; persist security info=false";
			//CString strDestConn = "Provider=oraoledb.oracle.1; Data Source="+pVecDlg->strDBSid_Dest+"; User Id="+pVecDlg->strDBUser_Dest+"; Password="+pVecDlg->strDBPwd_Dest+"; persist security info=false";

			m_hr_status = trans.CoordTransDBEntryForBLOB(_src, b_dbsrc, pVecDlg->strDBUser_Src, pVecDlg->strDBPwd_Src, 
															_des, b_dbdest, pVecDlg->strDBUser_Dest, pVecDlg->strDBPwd_Dest);

			strMsg.Format(_T("%s\r\n开始时间：%s\r\n结束时间：%s\r\n%s%.2lf%s\r\n"), strSrc, szBeginTime, szEndTime, _T("耗时:"), Result, _T("秒"));
			//窗口结束
			pVecDlg->ShowStatusPanel(strMsg);
		}			
	}
	else if (strDriver_Src == _T("ArcSDE"))
	{
		/*ArcGDBTest gdbTest;
		gdbTest.TransGDBFile();*/

		vector<STR_SDEINFO>			vecSDE;
		string						strPrjFullPath = TaskProc.GetPrjFullPathByName(strDest);
		CArcSDEVector				ArcSDEVector;
		CString						strMsg;

		pVecDlg->ShowStatusPanel("---------------------------------SDE矢量转换---------------------------------");

		vecSDE = pVecDlg->GetSelVec();
		if (vecSDE.size() <= 0)
		{
			MessageBox(pVecDlg->m_hWnd, "无转换任务", "系统提示", MB_OK|MB_ICONEXCLAMATION);
			pVecDlg->ShowStatusPanel("转换终止");
			g_ThreadFinished = TRUE ;
			pVecDlg->EnbleAllController();
			return -1;
		}

		//判断ArcSDE库配置
		if (!pVecDlg->GetSrcWorkspace() || !pVecDlg->GetDesWorkspace())
		{
			AfxMessageBox(_T("ArcSDE库未配置或配置失败!"));
			pVecDlg->ShowStatusPanel("转换终止");
			g_ThreadFinished = TRUE ;
			pVecDlg->EnbleAllController();
			return -1;
		}

		ArcSDEVector.SetTransParam(pVecDlg->GetSrcWorkspace(), pVecDlg->GetDesWorkspace(), trans, strPrjFullPath);

		//注册窗口
		ArcSDEVector.RegisterWnd(pVecDlg->m_hWnd);

		for (int i = 0; i < vecSDE.size(); i++)
		{
			StartTick = ::GetTickCount();
			ZeroMemory(szBeginTime, sizeof(szBeginTime));
			GetSysCurrentTime(szBeginTime);

			//转换处理
			HRESULT hr = ArcSDEVector.TransFeatureDTType(vecSDE[i]);
			if (hr == S_FALSE)
			{
				strMsg.Format(_T("%s转换失败!\n"), vecSDE[i].strName.c_str());
				pVecDlg->ShowStatusPanel(strMsg);
				continue;
			}

			EndTick = GetTickCount();
			ZeroMemory(szEndTime, sizeof(szEndTime));
			GetSysCurrentTime(szEndTime);
			double Result = (EndTick - StartTick)*0.001;

			strMsg.Format(_T("%s\r\n开始时间：%s\r\n结束时间：%s\r\n%s%.2lf%s\r\n"), "数据", szBeginTime, szEndTime, _T("耗时:"), Result, _T("秒"));
			//窗口结束
			pVecDlg->ShowStatusPanel(strMsg);
		}
	}
	else
	{
		pVecDlg->ShowStatusPanel("——————————————————矢量文件转换——————————————————\r\n");

		if(pVecDlg->_FilsList_selected.GetCount() == 0){
			MessageBox(pVecDlg->m_hWnd, "无转换任务", "系统提示", MB_OK|MB_ICONEXCLAMATION);
			pVecDlg->ShowStatusPanel("转换终止");
			g_ThreadFinished = TRUE ;
			pVecDlg->EnbleAllController();
			return -1;
		}

		CString strOutPutPath, strFile,strMsg;
		for(int n=0; n<pVecDlg->_FilsList_selected.GetCount(); n++)
		{				
			strFile = pVecDlg->_FilsList_selected.GetAt(n);
			//dstrFile = strFile.Mid(strFile.ReverseFind('\\')+1);
			strFile = strFile.Mid(strInPath.GetLength()+1);

			//add by chenyong 2013-01-29
			if (strDriver_Src == _T("Excel"))
			{
				//如果文件后缀是.xls,文件驱动改为Excel11，支持2007及以上
				if (strFile.Find(_T(".xlsx")) != -1 || strFile.Find(_T(".XLSX")) != -1)
				{
					_in_driver = _T("Excel12");
					_out_driver = _T("Excel12");
				}
				else
				{
					//支持2003
					_in_driver = _T("Excel11");
					_out_driver = _T("Excel11");
				}
			}

			//alter by chenyong 2014-1-17
			//if (strDriver_Src != sz_TranType_Vector[6])
 			//{
 			//	strFile = strFile.Mid(0, strFile.ReverseFind('.'));
 			//}

			//相同文件名
			//_src = strFile.AllocSysString();
			//_des = strFile.AllocSysString();

			StartTick = ::GetTickCount();
			ZeroMemory(szBeginTime, sizeof(szBeginTime));
			GetSysCurrentTime(szBeginTime);

			HRESULT m_hr_status = trans.CoordTransFileEntry(strFile, strInPath, _in_driver,			/*源文件*/
															strFile, strOutPath,_out_driver, NULL);	/*目标文件*/
			EndTick = GetTickCount();
			ZeroMemory(szEndTime, sizeof(szEndTime));
			GetSysCurrentTime(szEndTime);
			double Result = (EndTick - StartTick)*0.001;

			//strSrc = _src;
			if(m_hr_status == E_FAIL_PRIVILEGE_UID)
			{
				strMsg.Format(_T("%s\r\n开始时间：%s\r\n结束时间：%s\r\n%s\r\n%s%.2lf%s\r\n"), strFile, szBeginTime, szEndTime, UseAuthError,_T("耗时:"), Result, _T("秒"));
				pVecDlg->ShowStatusPanel(strMsg);
				continue;
			}
			else if(m_hr_status == E_FAIL_PRIVILEGE_EXTENT)
			{
				strMsg.Format(_T("%s\r\n开始时间：%s\r\n结束时间：%s\r\n%s\r\n%s%.2lf%s\r\n"), strFile, szBeginTime, szEndTime, UseBeyoundError,_T("耗时:"), Result, _T("秒"));
				pVecDlg->ShowStatusPanel(strMsg);
				continue;
			}

			strMsg.Format(_T("%s\r\n开始时间：%s\r\n结束时间：%s\r\n%s%.2lf%s\r\n"), strSrc, szBeginTime, szEndTime, _T("耗时:"), Result, _T("秒"));
			//窗口结束
			pVecDlg->ShowStatusPanel(strMsg);
		}
	}

	MessageBox(pVecDlg->m_hWnd, "转换完毕！", "提示",MB_OK | MB_ICONINFORMATION);

	pVecDlg->m_Progress.SetPos(100);
	pVecDlg->EnbleAllController();
	g_ThreadFinished = TRUE ;

	::CoUninitialize();

	return 0;
}

BOOL CDeuTaskProcess::Task_VectorProjectTransForm(CDeuVectorProjectTranDlg* pVecPrjDlg)
{
	if (!g_ThreadFinished)
	{
		return g_ThreadFinished;
	}

	HANDLE Thread = ::CreateThread(NULL, 0, ThreadVectorPrj, pVecPrjDlg, 0, NULL);
	if (NULL != Thread)
	{
		::CloseHandle(Thread);
	}
	
	return TRUE;
}

DWORD WINAPI ThreadVectorPrj(HANDLE _handle)
{
	::CoInitialize(NULL);
	g_ThreadFinished = FALSE ;

	CDeuVectorProjectTranDlg* pVecPrjDlg = (CDeuVectorProjectTranDlg*)_handle;

	//1. 准备源和目标 坐标系数据
	CString strSrc, strDest;
	CString strDriver_Src, strDriver_Dest;

	pVecPrjDlg->m_ComboInput.GetWindowText(strDriver_Src);
	pVecPrjDlg->m_ComboOutput.GetWindowText(strDriver_Dest);

	pVecPrjDlg->m_edit_InCoord.GetWindowText(strSrc);	
	pVecPrjDlg->m_edit_OutCoord.GetWindowText(strDest);

	//1.1 匹配坐标系转换的类型
	__COORDTYPE _type_src = TaskProc.FindCoordindateType(strSrc);
	__COORDTYPE _type_dest = TaskProc.FindCoordindateType(strDest);
	CDeuEllipse pSrcEllip = TaskProc.GetDeuEllipse((_type_src==PLANE)?GeoProjected:GeoDetic, strSrc);
	CDeuEllipse pDesEllip = TaskProc.GetDeuEllipse((_type_dest==GEODETIC)?GeoDetic:GeoProjected, strDest);

	/*if (pSrcEllip == NULL || pDesEllip == NULL)
	{		
	MessageBox(pVecPrjDlg->m_hWnd, "输入椭球参数不正确！转换中止，请检查参数！", "系统提示", MB_OK|MB_ICONEXCLAMATION);
	pVecPrjDlg->EnbleAllController();
	return -1;
	}*/

	CDeuCoordType pCoordType = TaskProc.GetCoordType(_type_src, _type_dest, 0);

	//准备的单位值对象
	CDeuUnits pUnit = TaskProc.GetUnit(_type_src, _type_dest);

	/*if (pUnit == NULL || pCoordType == NULL)
	{
	MessageBox(pVecPrjDlg->m_hWnd, "输入坐标参数不正确！转换中止，请检查参数！", "系统提示", MB_OK|MB_ICONEXCLAMATION);
	pVecPrjDlg->EnbleAllController();
	return -1;
	}*/

	//yzg 2012-9-26 增加对EXCEL文件投影的支持 只要目标转换文件是Excel 需要判断是否进行了行列设置 begin
	if (strDriver_Dest == _T("Excel"))
	{
		//需要判断是否进行了参数设置
		if (pVecPrjDlg->m_Controlpoint_Dlg.m_install == FALSE)
		{
			MessageBox(pVecPrjDlg->m_hWnd, "进行EXCEL转换时,需要进行EXCEL格式的参数设置,请点击[设置]！转换中止！", "系统提示", MB_OK|MB_ICONEXCLAMATION);
			pVecPrjDlg->EnbleAllController();
			g_ThreadFinished = TRUE ;
			return -1;
		}
	}
	//yzg 2012-9-26 增加对EXCEL文件投影的支持 只要目标转换文件是Excel 需要判断是否进行了行列设置 end

	//ISevenParams *pSevenParam = _Task2000.GetSevenParam(pdeuTask->_7param);

	/***/
	double * pParam = pVecPrjDlg->m_Controlpoint_Dlg.m_7param;

	double srcMajor = 0;
	pSrcEllip.get_Major( srcMajor );

	SHORT srcCoordType = 0;
	pCoordType.get_CoordType( srcCoordType ) ; 

	/*
	获取空间参考信息
	参数说明：
	1. 获取坐标类型
	2. 坐标名
	*/
	CDeuSpatialReference pSRS = TaskProc.GetSRS(TaskProc.FindCoordinateType(strDest), strDest);

	//IDeuSpatialReference *pSRS = TaskProc.GetSRS(cs);
	//IDeuConnPool *pConnPool = _Task2000.GetConnPool();

	CDeuTrans trans;
	CString _src = _T("");
	CString _des = _T("");
	CString _in_driver = _T("");
	CString _out_driver = _T("");

	/*
	CString strDriver_Src, strDriver_Dest;
	pVecPrjDlg->m_ComboInput.GetWindowText(strDriver_Src);
	pVecPrjDlg->m_ComboOutput.GetWindowText(strDriver_Dest);*/
	_in_driver  = strDriver_Src;
	_out_driver = strDriver_Dest;

	//初始化连接池
	CString strDBSrc, strDBDest;
	strDBSrc.Format("OCI:%s/%s@%s", pVecPrjDlg->strDBUser_Src, pVecPrjDlg->strDBPwd_Src, pVecPrjDlg->strDBSid_Src);
	strDBDest.Format("OCI:%s/%s@%s", pVecPrjDlg->strDBUser_Dest, pVecPrjDlg->strDBPwd_Dest, pVecPrjDlg->strDBSid_Dest);

	if(pVecPrjDlg->IsAdditional)
	{
		strDBSrc += ":";
		strDBDest += ":";
		for(int n=0; n<pVecPrjDlg->_TablesList_selected.GetCount(); n++)
		{
			strDBSrc += pVecPrjDlg->_TablesList_selected.GetAt(n)+",";
			strDBDest += pVecPrjDlg->_TablesList_selected.GetAt(n)+",";
		}
	}
	else
	{
		strDBSrc.Format("OCI:%s/%s@%s", pVecPrjDlg->strDBUser_Src, pVecPrjDlg->strDBPwd_Src, pVecPrjDlg->strDBSid_Src);
		strDBDest.Format("OCI:%s/%s@%s", pVecPrjDlg->strDBUser_Dest, pVecPrjDlg->strDBPwd_Dest, pVecPrjDlg->strDBSid_Dest);
	}

	strDBSrc  = strDBSrc.TrimRight(',');
	strDBDest = strDBDest.TrimRight(',');
	TaskProc.InitConnPool(strDBSrc);
	TaskProc.InitConnPool(strDBDest);

	/*	QUERYINTERFACE(doc->m_DY_coord_type,)*/

	trans.putref_DeuCoordType(pCoordType);
	trans.putref_DeuEllipse(pSrcEllip);
	trans.putref_DeuDestEllipse(pDesEllip);

	trans.putref_DeuUnits(pUnit);
	trans.putref_Param(pParam);
	trans.putref_DeuSRS(&pSRS);
	trans.putref_ConnPool(g_ConnPool);		

	trans.RegisterWnd((LONGLONG)pVecPrjDlg->m_hWnd);
	trans.put_TransModel(pVecPrjDlg->iModel);

	//如果目标转换的文件是Excel 则需要填入目标文件类型 yzg 2012-9-27 begin
	trans.putref_Excel(pVecPrjDlg->m_Controlpoint_Dlg.m_t_format);
	//如果目标转换的文件是Excel 则需要填入目标文件类型 yzg 2012-9-27 end

	////戴峰的断点执行功能的判断代码
	//if (pdeuTask->TaskStatus == BEFOREBEGIN)
	//{
	//	vec_FileName = pdeuTask->TableList;
	//	vec_FileName_Out = pdeuTask->TableList;
	//}
	//else if(pdeuTask->TaskStatus == RUNNING)
	//{
	//	std::vector<CString>::iterator it = pdeuTask->TableList.begin();
	//	for ( ; it != pdeuTask->TableList.end() ; it++)
	//	{
	//		int ret = pdeuTask->CurTable.Compare(*it);

	//		if (ret == 0)
	//		{
	//			//从这里开始断点续转
	//			vec_FileName.assign(it,pdeuTask->TableList.end());
	//			vec_FileName_Out = vec_FileName;
	//			break;
	//		}
	//	}
	//}
	//else
	//{
	//	//当任务状态不可识别的时候，默认为重新转换
	//	vec_FileName = pdeuTask->TableList;
	//	vec_FileName_Out = pdeuTask->TableList;
	//}

	CString strInPath, strOutPath;
	pVecPrjDlg->m_edit_InputFile.GetWindowText(strInPath);
	pVecPrjDlg->m_edit_OutputFile.GetWindowText(strOutPath);
	CString m_in_Path  = strInPath;
	CString m_out_Path = strOutPath;
	double StartTick(0), EndTick(0);
	char szBeginTime[10], szEndTime[10];

	//转文件
	if (strDriver_Src == sz_TranType_Vector[4]) //oracle
	{
		pVecPrjDlg->ShowStatusPanel("——————————————————矢量数据库数据投影——————————————————\r\n");
		if(pVecPrjDlg->_TablesList_selected.GetCount() == 0)
		{
			MessageBox(pVecPrjDlg->m_hWnd, "无投影任务", "系统提示", MB_OK|MB_ICONEXCLAMATION);
			pVecPrjDlg->TranFinish("投影终止");
			g_ThreadFinished = TRUE ;
			return -1;
		}

		CString strMsg;
		CString b_dbsrc = strDBSrc;
		CString b_dbdest = strDBDest;

		for(int n=0; n<pVecPrjDlg->_TablesList_selected.GetCount(); n++)
		{
			_src = pVecPrjDlg->_TablesList_selected.GetAt(n).AllocSysString();
			_des = _src;

			StartTick = ::GetTickCount();
			ZeroMemory(szBeginTime, sizeof(szBeginTime));
			GetSysCurrentTime(szBeginTime);

			strSrc = _src;
			HRESULT m_hr_status = trans.CoordTransDBEntry(_src, b_dbsrc, _in_driver,		/* 源数据库连接串 strDBSrc */
															_des, b_dbdest, _out_driver);	/* 目数据库连接串 strDBDest */

			EndTick = GetTickCount();
			ZeroMemory(szEndTime, sizeof(szEndTime));
			GetSysCurrentTime(szEndTime);
			double Result = (EndTick - StartTick)*0.001;

			//授权错误
			if(m_hr_status == E_FAIL_PRIVILEGE_UID)
			{
				strMsg.Format(_T("%s\r\n开始时间：%s\r\n结束时间：%s\r\n%s\r\n%s%.2lf%s\r\n"), strSrc, szBeginTime, szEndTime, UseAuthError,_T("耗时:"), Result, _T("秒"));
				pVecPrjDlg->ShowStatusPanel(strMsg);
				continue;
			}
			else if(m_hr_status == E_FAIL_PRIVILEGE_EXTENT) //超出范围
			{
				strMsg.Format(_T("%s\r\n开始时间：%s\r\n结束时间：%s\r\n%s\r\n%s%.2lf%s\r\n"), strSrc, szBeginTime, szEndTime, UseBeyoundError,_T("耗时:"), Result, _T("秒"));
				pVecPrjDlg->ShowStatusPanel(strMsg);
				continue;
			}

			strMsg.Format(_T("正在更新表 %s 请稍后...\r\n"), strSrc);
			pVecPrjDlg->ShowStatusPanel(strMsg);

			m_hr_status = trans.CoordTransDBEntryForBLOB(_src, b_dbsrc, pVecPrjDlg->strDBUser_Src, pVecPrjDlg->strDBPwd_Src, 
															_des, b_dbdest, pVecPrjDlg->strDBUser_Dest, pVecPrjDlg->strDBPwd_Dest);

			strMsg.Format(_T("%s\r\n开始时间：%s\r\n结束时间：%s\r\n%s%.2lf%s\r\n"), strSrc, szBeginTime, szEndTime, _T("耗时:"), Result, _T("秒"));

			//窗口结束
			pVecPrjDlg->ShowStatusPanel(strMsg);
		}
	}
	else if (strDriver_Src == _T("ArcSDE"))
	{
		vector<STR_SDEINFO>			vecSDE;
		string						strPrjFullPath = TaskProc.GetPrjFullPathByName(strDest);
		CArcSDEVector				ArcSDEVector;
		CString						strMsg;
		HRESULT						hr = S_OK;

		pVecPrjDlg->ShowStatusPanel("---------------------------------SDE矢量转换---------------------------------");

		vecSDE = pVecPrjDlg->GetSelVec();
		if (vecSDE.size() <= 0)
		{
			MessageBox(pVecPrjDlg->m_hWnd, "无转换任务", "系统提示", MB_OK|MB_ICONEXCLAMATION);
			pVecPrjDlg->ShowStatusPanel("转换终止");
			g_ThreadFinished = TRUE ;
			pVecPrjDlg->EnbleAllController();
			return -1;
		}

		//判断ArcSDE库配置
		if (!pVecPrjDlg->GetSrcWorkspace() || !pVecPrjDlg->GetDesWorkspace())
		{
			AfxMessageBox(_T("ArcSDE库未配置或配置失败!"));
			pVecPrjDlg->ShowStatusPanel("转换终止");
			g_ThreadFinished = TRUE ;
			pVecPrjDlg->EnbleAllController();
			return -1;
		}

		ArcSDEVector.SetTransParam(pVecPrjDlg->GetSrcWorkspace(), pVecPrjDlg->GetDesWorkspace(), trans, strPrjFullPath);

		//注册窗口 add by chenyong 2013-12-4
		ArcSDEVector.RegisterWnd(pVecPrjDlg->m_hWnd);

		for (int i = 0; i < vecSDE.size(); i++)
		{
			StartTick = ::GetTickCount();
			ZeroMemory(szBeginTime, sizeof(szBeginTime));
			GetSysCurrentTime(szBeginTime);

			//转换处理
			hr = ArcSDEVector.TransFeatureDTType(vecSDE[i]);
			if (hr == S_FALSE)
			{
				strMsg.Format(_T("投影矢量数据%s失败!"), vecSDE[i].strName.c_str());
				pVecPrjDlg->ShowStatusPanel(strMsg);
				continue;
			}

			EndTick = GetTickCount();
			ZeroMemory(szEndTime, sizeof(szEndTime));
			GetSysCurrentTime(szEndTime);
			double Result = (EndTick - StartTick)*0.001;

			strMsg.Format(_T("%s\r\n开始时间：%s\r\n结束时间：%s\r\n%s%.2lf%s\r\n"), "数据", szBeginTime, szEndTime, _T("耗时:"), Result, _T("秒"));

			//窗口结束
			pVecPrjDlg->ShowStatusPanel(strMsg);
		}
	}
	else
	{

		pVecPrjDlg->ShowStatusPanel("——————————————————矢量文件投影——————————————————\r\n");

		if(pVecPrjDlg->_FilsList_selected.GetCount() == 0)
		{
			MessageBox(pVecPrjDlg->m_hWnd, "无文件投影", "系统提示", MB_OK|MB_ICONEXCLAMATION);
			pVecPrjDlg->ShowStatusPanel("投影终止");
			pVecPrjDlg->EnbleAllController();
			g_ThreadFinished = TRUE ;
			return -1;
		}

		CString strOutPutPath, strFile,strMsg;
		for(int n=0; n<pVecPrjDlg->_FilsList_selected.GetCount(); n++)
		{				
			strFile = pVecPrjDlg->_FilsList_selected.GetAt(n);
			//strFile = strFile.Mid(strFile.ReverseFind('\\')+1);
			strFile = strFile.Mid(strInPath.GetLength()+1);
 			//if (strDriver_Src != sz_TranType_Vector[6])
 			//{
 			//	strFile = strFile.Mid(0, strFile.ReverseFind('.'));
 			//}

			//相同文件名
			_src = strFile.AllocSysString();
			_des = strFile.AllocSysString();

			StartTick = ::GetTickCount();
			ZeroMemory(szBeginTime, sizeof(szBeginTime));
			GetSysCurrentTime(szBeginTime);

			HRESULT m_hr_status = trans.CoordTransFileEntry(_src, m_in_Path, _in_driver,			/*源文件*/
															_des, m_out_Path,_out_driver, NULL);	/*目标文件*/

			EndTick = GetTickCount();
			ZeroMemory(szEndTime, sizeof(szEndTime));
			GetSysCurrentTime(szEndTime);
			double Result = (EndTick - StartTick)*0.001;

			strSrc = _src;
			if(m_hr_status == E_FAIL_PRIVILEGE_UID)
			{
				strMsg.Format(_T("%s\r\n开始时间：%s\r\n结束时间：%s\r\n%s\r\n%s%.2lf%s\r\n"), strSrc, szBeginTime, szEndTime, UseAuthError,_T("耗时:"), Result, _T("秒"));
				pVecPrjDlg->ShowStatusPanel(strMsg);
				continue;
			}
			else if(m_hr_status == E_FAIL_PRIVILEGE_EXTENT)
			{
				strMsg.Format(_T("%s\r\n开始时间：%s\r\n结束时间：%s\r\n%s\r\n%s%.2lf%s\r\n"), strSrc, szBeginTime, szEndTime, UseBeyoundError,_T("耗时:"), Result, _T("秒"));
				pVecPrjDlg->ShowStatusPanel(strMsg);
				continue;
			}

			strMsg.Format(_T("%s\r\n开始时间：%s\r\n结束时间：%s\r\n%s%.2lf%s\r\n"), strSrc, szBeginTime, szEndTime, _T("耗时:"), Result, _T("秒"));
			
			//窗口结束
			pVecPrjDlg->ShowStatusPanel(strMsg);
		}
	}

	MessageBox(pVecPrjDlg->m_hWnd, "转换完毕！", "提示",MB_OK | MB_ICONINFORMATION);

	pVecPrjDlg->m_Progress.SetPos(100);

	pVecPrjDlg->EnbleAllController();

	g_ThreadFinished = TRUE ;

	CoUninitialize();

	return 0;
}

BOOL CDeuTaskProcess::Task_RasterProjectTransForm(CDeuRasterProjectTranDlg * pProjectDlg)
{
	if (!g_ThreadFinished)
	{
		return g_ThreadFinished;
	}

	HANDLE Thread = ::CreateThread(NULL, 0, ThreadRasterPrj, pProjectDlg, 0, NULL);

	if (NULL != Thread)
	{
		::CloseHandle(Thread);
	}

	return TRUE;	
}

DWORD WINAPI ThreadRasterPrj(HANDLE _handle)
{
	::CoInitialize(NULL);
	g_ThreadFinished = FALSE;

	CDeuRasterProjectTranDlg* pProjectDlg = (CDeuRasterProjectTranDlg*)_handle;

	//1. 准备源和目标 坐标系数据
	CString strSrc, strDest;
	pProjectDlg->m_edit_InCoord.GetWindowText(strSrc);
	pProjectDlg->m_edit_OutCoord.GetWindowText(strDest);

	//1.1 匹配坐标系转换的类型
	__COORDTYPE _type_src  = TaskProc.FindCoordindateType(strSrc);
	__COORDTYPE _type_dest = TaskProc.FindCoordindateType(strDest);
	CDeuEllipse pSrcEllip = TaskProc.GetDeuEllipse((_type_src==PLANE)?GeoProjected:GeoDetic, strSrc);
	CDeuEllipse pDesEllip = TaskProc.GetDeuEllipse((_type_dest==GEODETIC)?GeoDetic:GeoProjected, strDest);

	//2. 坐标类型
	CDeuCoordType pCoordType = TaskProc.GetCoordType(_type_src, _type_dest,0);

	//3. 准备的单位值对象
	CDeuUnits pUnit = TaskProc.GetUnit(_type_src, _type_dest);

	//yzg 2012-8-22 15：13 由于平面直角投影大地坐标系时 需要在这里增加往大地坐标系中增加一个参数 用来修正转换后经度不正确的问题 
	//                     暂时考虑通过中央经线字段传入目标坐标系 仅仅当目标坐标系是大地坐标系统时 增加此修正参数 begin
	//4
	if (_type_src == PLANE && _type_dest == GEODETIC)
	{
		//获得源坐标系统的中央经线值
		double d_centrol_long = 0;
		double d_src_false_east = 0;
		pSrcEllip.get_Centrol_Long(d_centrol_long);
		pDesEllip.putref_Centrol_Long(d_centrol_long);

		//目标坐标系中补充填入东假值
		pSrcEllip.get_False_E(d_src_false_east);
		pDesEllip.putref_False_E(d_src_false_east);
	}
	//yzg 2012-8-22 15：13 由于平面直角投影大地坐标系时 需要在这里增加往大地坐标系中增加一个参数 用来修正转换后经度不正确的问题 end

	/*
	获取空间参考信息
	参数说明：
	1. 获取坐标类型
	2. 坐标名
	*/
	CDeuSpatialReference pSRS = TaskProc.GetSRS(TaskProc.FindCoordinateType(strDest), strDest);
	CDeuRasterTrans trans;   

	CString _src;
	CString _des;
	CString _in_driver;
	CString _out_driver;
	CString strDriver_Src, strDriver_Dest;

	pProjectDlg->m_ComboInput.GetWindowText(strDriver_Src);
	pProjectDlg->m_ComboOutput.GetWindowText(strDriver_Dest);
	_in_driver  = strDriver_Src;
	_out_driver = strDriver_Dest;

	trans.putref_DeuCoordType(pCoordType);
	trans.putref_DeuEllipse(pSrcEllip);
	trans.putref_DeuDestEllipse(pDesEllip);

	trans.putref_DeuUnits(pUnit);
	trans.put_TransModel(pProjectDlg->iModel);
	trans.put_Resampling(pProjectDlg->iReCollect);		
	trans.putref_DeuSRS(pSRS);

	if(pProjectDlg->m_bSpecified == TRUE)
	{			
		trans.SpecifiedFrame(pProjectDlg->m_dbLeft,
			pProjectDlg->m_dbTop,
			pProjectDlg->m_lSizeX,
			pProjectDlg->m_lSizeY,
			pProjectDlg->m_dbPixX,
			pProjectDlg->m_dbPixY);
	}

	double * pParam = pProjectDlg->m_Controlpoint_Dlg.m_7param;
	double * invParam = pProjectDlg->m_Controlpoint_Dlg.m_Invpara;

	double srcMajor = 0;
	pSrcEllip.get_Major(srcMajor);

	short  srcCoordType = 0;
	pCoordType.get_CoordType(srcCoordType) ; 

	trans.putref_Param(pParam);
	trans.putref_InvParam(invParam);
	trans.RegisterWnd((LONGLONG)pProjectDlg->m_hWnd);

	CString strInPath, strOutPath;
	pProjectDlg->m_edit_InputFile.GetWindowText(strInPath);
	pProjectDlg->m_edit_OutputFile.GetWindowText(strOutPath);

	CString m_in_Path     = strInPath;
	CString m_out_Path    = strOutPath;
	CString bstrDriver    = strDriver_Src;
	CString bstrDriverOut = strDriver_Dest;
	double  StartTick(0), EndTick(0);
	char    szBeginTime[10], szEndTime[10];

	if (strDriver_Src == _T("ArcSDE"))//add by chenyong for sde project 2013-11-26
	{
		//获取目标文件坐标文件路径 add by chenyong 2013-10-15
		string strPrjFullPath = TaskProc.GetPrjFullPathByName(strDest);

		vector<STR_SDEINFO>					vecSDE;
		CArcSDERaster						ArcSDERaster;
		CString								strMsg;

		pProjectDlg->ShowStatusPanel("---------------------------------SDE栅格投影---------------------------------");
		vecSDE = pProjectDlg->m_vecSelect;
		if (vecSDE.size() <= 0)
		{
			MessageBox(pProjectDlg->m_hWnd, "无转换任务", "系统提示", MB_OK|MB_ICONEXCLAMATION);
			pProjectDlg->ShowStatusPanel("转换终止");
			g_ThreadFinished = TRUE ;
			pProjectDlg->EnbleAllController();
			return -1;
		}

		//判断ArcSDE库配置
		if (!pProjectDlg->m_pSrcWS || !pProjectDlg->m_pDesWS)
		{
			AfxMessageBox(_T("ArcSDE库未配置或配置失败!"));
			pProjectDlg->ShowStatusPanel("转换终止");
			g_ThreadFinished = TRUE ;
			pProjectDlg->EnbleAllController();
			return -1;
		}

		ArcSDERaster.SetTransParam(pProjectDlg->m_pSrcWS, pProjectDlg->m_pDesWS, trans, strPrjFullPath);

		//注册窗口
		ArcSDERaster.RegisterWnd(pProjectDlg->m_hWnd);

		for (int i = 0; i < vecSDE.size(); i++)
		{
			StartTick = ::GetTickCount();
			ZeroMemory(szBeginTime, sizeof(szBeginTime));
			GetSysCurrentTime(szBeginTime);

			//转换处理
			HRESULT hr = ArcSDERaster.ProjectRasterDTType(vecSDE[i]);
			if (hr == S_FALSE)
			{
				strMsg.Format(_T("投影栅格数据%s失败!\n"), vecSDE[i].strName.c_str());
				pProjectDlg->ShowStatusPanel(strMsg);
				continue;
			}

			EndTick = GetTickCount();
			ZeroMemory(szEndTime, sizeof(szEndTime));
			GetSysCurrentTime(szEndTime);
			double Result = (EndTick - StartTick)*0.001;

			strMsg.Format(_T("%s\r\n开始时间：%s\r\n结束时间：%s\r\n%s%.2lf%s\r\n"), "数据", szBeginTime, szEndTime, _T("耗时:"), Result, _T("秒"));
			//窗口结束
			pProjectDlg->ShowStatusPanel(strMsg);
		}
	}
	else
	{
		//转文件 备注：目前只转换文件	
		if(pProjectDlg->_FilsList_selected.GetCount() == 0)
		{
			MessageBox(pProjectDlg->m_hWnd, "无转换文件，请检查文件！", "系统提示", MB_OK|MB_ICONEXCLAMATION);

			//pProjectDlg->ShowStatusPanel("转换终止");

			g_ThreadFinished = TRUE ;
			pProjectDlg->EnbleAllController();
			return -1;
		}

		pProjectDlg->ShowStatusPanel("——————————————————栅格文件投影——————————————————\r\n");

		HRESULT m_hr_status;
		//这里需要对单个转换结束后的文件进行任务描述移除
		CString  str, strFile, strMsg;
		for(int n=0; n<pProjectDlg->_FilsList_selected.GetCount(); n++)
		{
			_src = pProjectDlg->_FilsList_selected.GetAt(n);
			_des = _src;

			strFile = pProjectDlg->_FilsList_selected.GetAt(n);
			//strFile = strFile.Mid(strFile.ReverseFind('\\')+1);
			strFile = strFile.Mid(strInPath.GetLength()+1);
			//strFile = strFile.Mid(0, strFile.ReverseFind('.'));
			_src = strFile;
			_des = strFile;

			//	str.Format("正在转换第%d个文件.", n);
			//	pProjectDlg->ShowStatusPanel(str);
			StartTick = ::GetTickCount();
			ZeroMemory(szBeginTime, sizeof(szBeginTime));
			GetSysCurrentTime(szBeginTime);

			m_hr_status = trans.CoordTransFileEntry(_src, m_in_Path, _in_driver,			/*源文件*/
													_des, m_out_Path,_out_driver, NULL);	/*目标文件*/
			EndTick = GetTickCount();
			double Result = (EndTick - StartTick)*0.001;
			ZeroMemory(szEndTime, sizeof(szEndTime));
			GetSysCurrentTime(szEndTime);

			if(m_hr_status == E_FAIL_PRIVILEGE_UID)
			{
				strMsg.Format(_T("%s\r\n开始时间：%s\r\n结束时间：%s\r\n%s\r\n%s%.2lf%s\r\n"), _src, szBeginTime, szEndTime, UseAuthError,_T("耗时:"), Result, _T("秒"));
				pProjectDlg->ShowStatusPanel(strMsg);
				continue;
			}
			else if(m_hr_status == E_FAIL_PRIVILEGE_EXTENT)
			{
				strMsg.Format(_T("%s\r\n开始时间：%s\r\n结束时间：%s\r\n%s\r\n%s%.2lf%s\r\n"), _src, szBeginTime, szEndTime, UseBeyoundError,_T("耗时:"), Result, _T("秒"));
				pProjectDlg->ShowStatusPanel(strMsg);
				continue;
			}
			strMsg.Format(_T("%s\r\n开始时间：%s\r\n结束时间：%s\r\n%s%.2lf%s\r\n"), _src, szBeginTime, szEndTime, _T("耗时:"), Result, _T("秒"));
			pProjectDlg->ShowStatusPanel(strMsg);
		}
	}

	::SendMessage(pProjectDlg->m_hWnd,WM_TASK_FINISH_ALL,NULL,NULL);

	g_ThreadFinished = TRUE ;
	pProjectDlg->EnbleAllController();

	::CoUninitialize();
	return 0;
}

BOOL CDeuTaskProcess::Task_RasterTransForm(CDeuRasterTranDlg * pRasterDlg)
{
	if (!g_ThreadFinished)
	{
		return g_ThreadFinished;
	}

	HANDLE Thread;
	Thread = ::CreateThread(NULL, 0, ThreadRaster, pRasterDlg, 0, NULL);
	if (NULL != Thread)
	{
		::CloseHandle(Thread);
	}

	return TRUE;
}

DWORD WINAPI ThreadRaster(HANDLE _handle)
{
	CoInitialize(NULL);
	CDeuRasterTranDlg* pRasterDlg = (CDeuRasterTranDlg*)_handle;
	g_ThreadFinished = FALSE ;

	//1. 准备源和目标 坐标系数据
	CString strSrc, strDest;
	pRasterDlg->m_edit_InCoord.GetWindowText(strSrc);
	pRasterDlg->m_edit_OutCoord.GetWindowText(strDest);

	//1.1 匹配坐标系转换的类型
	__COORDTYPE _type_src  = TaskProc.FindCoordindateType(strSrc);
	__COORDTYPE _type_dest = TaskProc.FindCoordindateType(strDest);
	CDeuEllipse pSrcEllip = TaskProc.GetDeuEllipse((_type_src==PLANE)?GeoProjected:GeoDetic, strSrc);
	CDeuEllipse pDesEllip = TaskProc.GetDeuEllipse((_type_dest==GEODETIC)?GeoDetic:GeoProjected, strDest);

	//2. 坐标类型
	CDeuCoordType pCoordType = TaskProc.GetCoordType(_type_src, _type_dest,0);

	//3. 准备的单位值对象
	CDeuUnits pUnit = TaskProc.GetUnit(_type_src, _type_dest);

	/*
	获取空间参考信息
	参数说明：
	1. 获取坐标类型
	2. 坐标名
	*/
	CDeuSpatialReference pSRS = TaskProc.GetSRS(TaskProc.FindCoordinateType(strDest), strDest);
	CDeuRasterTrans trans;
	CString _src = _T("");
	CString _des = _T("");
	CString _in_driver = _T("");
	CString _out_driver = _T("");
	CString strDriver_Src = _T("");
	CString strDriver_Dest = _T("");

	pRasterDlg->m_ComboInput.GetWindowText(strDriver_Src);
	pRasterDlg->m_ComboOutput.GetWindowText(strDriver_Dest);
	_in_driver  = strDriver_Src;
	_out_driver = strDriver_Dest;

	/*	QUERYINTERFACE(doc->m_DY_coord_type,) */
	trans.putref_DeuCoordType(pCoordType);
	trans.putref_DeuEllipse(pSrcEllip);
	trans.putref_DeuDestEllipse(pDesEllip);

	trans.putref_DeuUnits(pUnit);
	trans.put_TransModel(pRasterDlg->iModel);
	trans.put_Resampling(pRasterDlg->iReCollect);		
	trans.putref_DeuSRS(pSRS);

	//———————————————格网处理流程BEGIN————————————
	/*判断是否格网转换,
	若是:
	传参;
	否则:继续下一句.
	*/

	if ((pRasterDlg->iModel) == MODEL_GRID)
	{	
		trans.InitGridTranslate(pRasterDlg->m_Controlpoint_Dlg.m_GridParameter);
	}

	//———————————————格网处理流程END————————————
	if(pRasterDlg->m_bSpecified == TRUE)
	{			
		trans.SpecifiedFrame(  pRasterDlg->m_dbLeft,
			pRasterDlg->m_dbTop,
			pRasterDlg->m_lSizeX,
			pRasterDlg->m_lSizeY,
			pRasterDlg->m_dbPixX,
			pRasterDlg->m_dbPixY
			);
	}

	double * pParam = pRasterDlg->m_Controlpoint_Dlg.m_7param ;
	double * invParam = pRasterDlg->m_Controlpoint_Dlg.m_Invpara ;

	double srcMajor = 0;
	pSrcEllip.get_Major( srcMajor );

	SHORT srcCoordType = 0;
	pCoordType.get_CoordType( srcCoordType ) ; 

	trans.putref_Param(pParam);
	trans.putref_InvParam(invParam);

	trans.RegisterWnd((LONGLONG)pRasterDlg->m_hWnd);

	CString strInPath, strOutPath;
	pRasterDlg->m_edit_InputFile.GetWindowText(strInPath);
	pRasterDlg->m_edit_OutputFile.GetWindowText(strOutPath);

	CString m_in_Path     = strInPath;
	CString m_out_Path    = strOutPath;
	CString bstrDriver    = strDriver_Src;
	CString bstrDriverOut = strDriver_Dest;

	double StartTick(0), EndTick(0);
	CString  str, strFile, strMsg;

	if (strDriver_Src == _T("ArcSDE"))
	{
		//获取目标文件坐标文件路径 add by chenyong 2013-10-15
		string strPrjFullPath = TaskProc.GetPrjFullPathByName(strDest);
		vector<STR_SDEINFO>					vecSDE;
		CArcSDERaster						ArcSDERaster;
		CString								strMsg;
		HRESULT								hr = S_OK;

		pRasterDlg->ShowStatusPanel("---------------------------------SDE栅格转换---------------------------------");

		vecSDE = pRasterDlg->m_vecSelect;
		if (vecSDE.size() <= 0)
		{
			MessageBox(pRasterDlg->m_hWnd, "无转换任务", "系统提示", MB_OK|MB_ICONEXCLAMATION);
			pRasterDlg->ShowStatusPanel("转换终止");
			g_ThreadFinished = TRUE ;
			pRasterDlg->EnbleAllController();
			return -1;
		}

		//判断ArcSDE库配置
		if (!pRasterDlg->m_pSrcWS || !pRasterDlg->m_pDesWS)
		{
			AfxMessageBox(_T("ArcSDE库未配置或配置失败!"));
			pRasterDlg->ShowStatusPanel("转换终止");
			g_ThreadFinished = TRUE ;
			pRasterDlg->EnbleAllController();
			return -1;
		}

		ArcSDERaster.SetTransParam(pRasterDlg->m_pSrcWS, pRasterDlg->m_pDesWS, trans, strPrjFullPath);

		//注册窗口 add by chenyong 2013-12-4
		ArcSDERaster.RegisterWnd(pRasterDlg->m_hWnd);

		char    szBeginTime[128] = {0};
		char    szEndTime[128] = {0};
		for (int i = 0; i < vecSDE.size(); i++)
		{
			StartTick = ::GetTickCount();
			ZeroMemory(szBeginTime, sizeof(szBeginTime));
			GetSysCurrentTime(szBeginTime);

			//转换处理
			hr = ArcSDERaster.TransRasterDTType(vecSDE[i]);
			if (hr == S_FALSE)
			{
				strMsg.Format(_T("转换栅格数据%s失败!"), vecSDE[i].strName.c_str());
				pRasterDlg->ShowStatusPanel(strMsg);
				continue;
			}

			EndTick = GetTickCount();
			ZeroMemory(szEndTime, sizeof(szEndTime));
			GetSysCurrentTime(szEndTime);
			double Result = (EndTick - StartTick)*0.001;

			strMsg.Format(_T("%s\r\n开始时间：%s\r\n结束时间：%s\r\n%s%.2lf%s\r\n"), "数据", szBeginTime, szEndTime, _T("耗时:"), Result, _T("秒"));
			//窗口结束
			pRasterDlg->ShowStatusPanel(strMsg);
		}

		::SendMessage(pRasterDlg->m_hWnd,WM_TASK_FINISH_ALL,NULL,NULL);
	}
	else
	{
		//转文件 备注：目前只转换文件	
		if(pRasterDlg->_FilsList_selected.GetCount() == 0)
		{
			MessageBox(pRasterDlg->m_hWnd, "无转换文件，请检查文件！", "系统提示", MB_OK|MB_ICONEXCLAMATION);

			//pRasterDlg->ShowStatusPanel("转换终止");

			g_ThreadFinished = TRUE ;
			pRasterDlg->EnbleAllController();
			return -1;
		}

		pRasterDlg->ShowStatusPanel("——————————————————栅格文件转换——————————————————\r\n");

		double StartTick(0), EndTick(0);
		char szBeginTime[10], szEndTime[10];

		HRESULT m_hr_status;
		//这里需要对单个转换结束后的文件进行任务描述移除
		CString  str, strFile, strMsg;
		for(int n=0; n<pRasterDlg->_FilsList_selected.GetCount(); n++)
		{
			_src = pRasterDlg->_FilsList_selected.GetAt(n).AllocSysString();
			_des = _src;

			strFile = pRasterDlg->_FilsList_selected.GetAt(n);
			//strFile = strFile.Mid(strFile.ReverseFind('\\')+1);
			strFile = strFile.Mid(strInPath.GetLength()+1);
			//strFile = strFile.Mid(0, strFile.ReverseFind('.'));
			_src = strFile.AllocSysString();
			_des = strFile.AllocSysString();

			//	str.Format("正在转换第%d个文件.", n);
			//	pRasterDlg->ShowStatusPanel(str);

			StartTick = ::GetTickCount();
			ZeroMemory(szBeginTime, sizeof(szBeginTime));
			GetSysCurrentTime(szBeginTime);

			m_hr_status = trans.CoordTransFileEntry(_src, m_in_Path, _in_driver,			/*源文件*/
													_des, m_out_Path,_out_driver, NULL);	/*目标文件*/
			EndTick = GetTickCount();
			double Result = (EndTick - StartTick)*0.001;
			ZeroMemory(szEndTime, sizeof(szEndTime));
			GetSysCurrentTime(szEndTime);

			if(m_hr_status == E_FAIL_PRIVILEGE_UID)
			{
				strMsg.Format(_T("%s\r\n开始时间：%s\r\n结束时间：%s\r\n%s\r\n%s%.2lf%s\r\n"), _src, szBeginTime, szEndTime, UseAuthError,_T("耗时:"), Result, _T("秒"));
				pRasterDlg->ShowStatusPanel(strMsg);
				continue;
			}
			else if(m_hr_status == E_FAIL_PRIVILEGE_EXTENT)
			{
				strMsg.Format(_T("%s\r\n开始时间：%s\r\n结束时间：%s\r\n%s\r\n%s%.2lf%s\r\n"), _src, szBeginTime, szEndTime, UseBeyoundError,_T("耗时:"), Result, _T("秒"));
				pRasterDlg->ShowStatusPanel(strMsg);
				continue;
			}

			strMsg.Format(_T("%s\r\n开始时间：%s\r\n结束时间：%s\r\n%s%.2lf%s\r\n"), _src, szBeginTime, szEndTime, _T("耗时:"), Result, _T("秒"));
			pRasterDlg->ShowStatusPanel(strMsg);
		}

		::SendMessage(pRasterDlg->m_hWnd,WM_TASK_FINISH_ALL,NULL,NULL);
	}

	g_ThreadFinished = TRUE ;

	pRasterDlg->m_Progress.SetPos(100);
	pRasterDlg->EnbleAllController();

	::CoUninitialize();

	return 0;
}

void CDeuTaskProcess::UpdateTaskList(std::list<CDeuTaskCache*> *p_lisTask)
{
	return;
}

void CDeuTaskProcess::UpdateTask(CDeuTaskCache* Task)
{
	std::list<CDeuTaskCache*> lisTask;
	int iCount = lisTask.size();
	typedef   std::list <CDeuTaskCache*> ::iterator   T_It; 
	//T_It it = std::find_if(lisTask.begin(),lisTask.end(),IFFunctor<CDeuTask*,CString>(Task->TaskName));

	lisTask.remove_if(IFFunctor_TaskName<CDeuTaskCache*,CString>(Task->TaskName));
	lisTask.push_back(Task);

	UpdateTaskList(&lisTask);
}

void CDeuTaskProcess::RemoveTask(CString TaskName)
{
	std::list<CDeuTaskCache*> lisTask;
	typedef   std::list <CDeuTaskCache*> ::iterator   T_It; 
	//T_It it = std::find_if(lisTask.begin(),lisTask.end(),IFFunctor<CDeuTask*,CString>(Task->TaskName));

	lisTask.remove_if(IFFunctor_TaskName<CDeuTaskCache*,CString>(TaskName));
	UpdateTaskList(&lisTask);
}

void CDeuTaskProcess::UpdateEllipseList(std::list<CNode*> lisEllipse)
{
	//CTask转到CNode
	CNode *node = new CNode;
	node->tag_name = L"dy";
	node->ele_name = L"dy";		//曹欣
	int iCount = lisEllipse.size();
	for (int i = 0; i<iCount;i++)
	{
		CNode *node_task = getListItem(lisEllipse,i);
		node->_sub_nodes.push_back(node_task);
	}

	//CNode更新到.ini文件
	CXmlOperate xmlOp2;

	CString path;
	path=GetCurrentDir();

	CString strFileName2;
	strFileName2 = path + "custom.xml";

	xmlOp2.CreateFile(strFileName2,node);

	xmlOp2.flush();
}

void CDeuTaskProcess::ShowView(BSTR pathString, CDeuDMap* p_map)
{
	VARIANT_BOOL ret;
	MapWinGIS::IShapefilePtr pSf;
	pSf.CreateInstance(MapWinGIS::CLSID_Shapefile);
	pSf->Open(pathString,NULL,&ret);

	VARIANT_BOOL success;
	MapWinGIS::ICallbackPtr pcBack;
	MapWinGIS::IImagePtr pImage;
	pImage.CreateInstance(MapWinGIS::CLSID_Image);
	pImage->Open(pathString,MapWinGIS::USE_FILE_EXTENSION,TRUE,pcBack,&success);

	long hnd;
	if (ret)
	{
		p_map->SetSendMouseMove(true);
		hnd = p_map->AddLayer(pSf,true);

		unsigned int FillColor,LineColor,PointColor;
		float LineWidth,PointSize;
		int d= 1;

		//设置随机数，作为RGB函数的参数
		srand((unsigned)time(NULL)*d++ );
		int n0 = rand()%256;
		int n1 = rand()%256;
		int n2 = rand()%256;
		int n3 = rand()%256;
		int n4 = rand()%256;
		int n5 = rand()%256;
		int n6 = rand()%256;
		int n7 = rand()%256;
		int n8 = rand()%256;

		//添加随机颜色
		p_map->put_ShapeLayerDrawFill(hnd,true);
		FillColor = RGB(n0,n1,n2);
		LineColor = RGB(n3,n4,n5);
		LineWidth = 0.5;
		p_map->put_ShapeLayerFillColor(hnd,FillColor);
		p_map->put_ShapeLayerLineColor(hnd,LineColor);
		p_map->put_ShapeLayerLineWidth(hnd,LineWidth);
		PointColor = RGB(n6,n7,n8);
		PointSize = 5;
		p_map->put_ShapeLayerPointColor(hnd,PointColor);
		p_map->put_ShapeLayerPointSize(hnd,PointSize);
		p_map->put_ShapeLayerPointType(hnd,MapWinGIS::ptCircle);

		//p_map->ZoomToMaxVisibleExtents();
		p_map->SetCursorMode(MapWinGIS::cmPan);

		/*
		VARIANT_BOOL ret2;
		MapWinGIS::IShapefilePtr pSf2 ;
		pSf2.CreateInstance(MapWinGIS::CLSID_Shapefile);
		pSf2->Open(pathString,NULL,&ret2);
		
		CMap1*   m_map2 = mainframe->m_wndEagleEye.GetEagleEyeMap();
		m_map2->AddLayer(pSf2,true);                                         //鹰眼视图同步添加主视图地图

		//添加鹰眼视图中地物的颜色，跟主地图一样
		m_map2->put_ShapeLayerDrawFill(hnd,true);
		m_map2->put_ShapeLayerFillColor(hnd,FillColor);
		m_map2->put_ShapeLayerLineColor(hnd,LineColor);
		m_map2->put_ShapeLayerLineWidth(hnd,LineWidth);
		m_map2->put_ShapeLayerPointColor(hnd,PointColor);
		m_map2->put_ShapeLayerPointSize(hnd,PointSize);
		m_map2->put_ShapeLayerPointType(hnd,MapWinGIS::ptCircle);
		m_map2->ZoomToMaxVisibleExtents();
		
		MapWinGIS::IExtentsPtr pExtents;
		pExtents = p_map->GetExtents();
		double xMin,xMax,yMin,yMax,zMin,zMax;
		pExtents->GetBounds(&xMin,&yMin,&zMin,&xMax,&yMax,&zMax);
		long draw_hnd = m_map2->NewDrawing(MapWinGIS::dlSpatiallyReferencedList);	
		long  width = 2;
		m_map2->DrawLine(xMin+0,yMin+0,xMax-0,yMin+0,width,RGB(255,0,0));
		m_map2->DrawLine(xMax-0,yMin+0,xMax-0,yMax-0,width,RGB(255,0,0));
		m_map2->DrawLine(xMax-0,yMax-0,xMin+0,yMax-0,width,RGB(255,0,0));
		m_map2->DrawLine(xMin+0,yMax-0,xMin+0,yMin+0,width,RGB(255,0,0));
		
		//获取图层信息
		OGRRegisterAll();
		OGRDataSource   *poDS = OGRSFDriverRegistrar::Open((LPCSTR)_bstr_t(pathString), FALSE );		
		if (poDS == NULL)
		{
			TRACE(_T("open failed \n"));
			return ;
		}
		OGRLayer  *poLayer = poDS->GetLayer(0);		
		OGRSpatialReference* poRSR= poLayer->GetSpatialRef();
		if (poRSR==NULL)
		{
			const char *pszSystem = "无";
			mainframe->m_wndCoordinateSystem.SetSystem(pszSystem);
			mainframe->m_wndCoordinateSystem.SetDatum(pszSystem);
			char *pszunits = "无";
			mainframe->m_wndCoordinateSystem.SetUnits(pszunits);
			pszunits = "无单位";
			mainframe->m_wndCursorPosition.SetUnits(pszunits);	
			OGRDataSource::DestroyDataSource(poDS);	
			return;
		}
		char  *pszWKT = NULL;
		poRSR->exportToWkt(&pszWKT);		
		TRACE("%s\n", pszWKT);		

		//坐标暂时获取不到
		//const char *pszAxis = poRSR->GetAttrValue("AXIS");
		const char *pszPAxis0 = poRSR->GetAxis("PROJCS",0,NULL);
		const char *pszPAxis1 = poRSR->GetAxis("PROJCS",1,NULL);
		const char *pszGAxis0 = poRSR->GetAxis("GEOGCS",0,NULL);
		const char *pszGAxis1 = poRSR->GetAxis("GEOGCS",1,NULL);

		char *linearunit = NULL;
		char *angularunitsr = NULL;
		if(poRSR->IsProjected())
		{
			TRACE(_T("this layer has been projected \n"));
			poRSR->GetLinearUnits(&linearunit);
			const char *pszProjection = poRSR->GetAttrValue("PROJCS");
			const char *pszDatum = poRSR->GetAttrValue("DATUM");
			const char *pszProjection1 = poRSR->GetAttrValue("PROJECTION");
			mainframe->m_wndCursorPosition.SetUnits(linearunit);	
			mainframe->m_wndCoordinateSystem.SetSystem(pszProjection);   
			mainframe->m_wndCoordinateSystem.SetDatum(pszDatum);
			mainframe->m_wndCoordinateSystem.SetUnits(linearunit);
		}
		else if (poRSR->IsGeographic())
		{
			const char *pszGeographic = poRSR->GetAttrValue("GEOGCS");
			const char *pszDatum = poRSR->GetAttrValue("DATUM");
			poRSR->GetAngularUnits(&angularunitsr);		
			mainframe->m_wndCursorPosition.SetUnits(angularunitsr);	
			mainframe->m_wndCoordinateSystem.SetSystem(pszGeographic);
			mainframe->m_wndCoordinateSystem.SetDatum(pszDatum);
			mainframe->m_wndCoordinateSystem.SetUnits(angularunitsr);
		}
		OGRDataSource::DestroyDataSource(poDS);	
		*/
	}
	else if (success)
	{
		p_map->SetSendMouseMove(true);
		hnd = p_map->AddLayer(pImage,true);
		p_map->ZoomToMaxVisibleExtents();
		VARIANT_BOOL success2;
		MapWinGIS::ICallbackPtr pcBack2;
		MapWinGIS::IImagePtr pImage2;
		pImage2.CreateInstance(MapWinGIS::CLSID_Image);
		pImage2->Open(pathString,MapWinGIS::USE_FILE_EXTENSION,true,pcBack2,&success2);
		
		/*
		CMap1*   m_map2 = mainframe->m_wndEagleEye.GetEagleEyeMap();
		m_map2->AddLayer(pImage2,true);                                         //鹰眼视图同步添加主视图地图
		m_map2->ZoomToMaxVisibleExtents();
		MapWinGIS::IExtentsPtr pExtents;
		pExtents = m_map->GetExtents();
		double xMin,xMax,yMin,yMax,zMin,zMax;
		pExtents->GetBounds(&xMin,&yMin,&zMin,&xMax,&yMax,&zMax);
		long draw_hnd = m_map2->NewDrawing(MapWinGIS::dlSpatiallyReferencedList);	
		long  width = 2;
		m_map2->DrawLine(xMin+0,yMin+0,xMax-0,yMin+0,width,RGB(255,0,0));
		m_map2->DrawLine(xMax-0,yMin+0,xMax-0,yMax-0,width,RGB(255,0,0));
		m_map2->DrawLine(xMax-0,yMax-0,xMin+0,yMax-0,width,RGB(255,0,0));
		m_map2->DrawLine(xMin+0,yMax-0,xMin+0,yMin+0,width,RGB(255,0,0));
		*/
	}
	else 
	{
		//MessageBox(mainframe->m_hWnd,_T("暂不支持所加载的格式数据!请重新选择"),_T("提示"),MB_OK | MB_ICONINFORMATION) ;
		return ;
	}
}

void CDeuTaskProcess::ZoomIn(CDeuDMap* p_map)
{
	p_map->SetCursorMode(MapWinGIS::cmZoomIn);
}

void CDeuTaskProcess::ZoomOut(CDeuDMap* p_map)
{
	p_map->SetCursorMode(MapWinGIS::cmZoomOut);
}

void CDeuTaskProcess::Pan(CDeuDMap* p_map)
{
	p_map->SetCursorMode(MapWinGIS::cmPan);
}

void CDeuTaskProcess::ZoomToPrev(CDeuDMap* p_map)
{
	MapWinGIS::IExtentsPtr pmyExtents;
	pmyExtents = p_map->GetExtents();	

	//save the extents into array
	m_arrExtents.push_back(pmyExtents);	
	p_map->ZoomToPrev();
}

void CDeuTaskProcess::ZoomToNext(CDeuDMap* p_map)
{
	MapWinGIS::IExtentsPtr pmyExtents;
	long nSize  = m_arrExtents.size();
	if(nSize == 0 )
	{
		return;
	}
	pmyExtents = m_arrExtents[nSize - 1];
	p_map->SetExtents(pmyExtents);	
	m_arrExtents.resize(nSize - 1);
}

void CDeuTaskProcess::ZoomToMaxVisibleExtents(CDeuDMap* p_map)
{
	p_map->ZoomToMaxVisibleExtents();
}

//默认状态
void CDeuTaskProcess::None(CDeuDMap* p_map)
{
	/*CMainFrame* mainframe = (CMainFrame*)AfxGetMainWnd();
	BOOL IsOK = CheckMap() ;
	if (IsOK!=TRUE)
	{	
		MessageBox(mainframe->m_hWnd, "请先切换到视图窗口！", "提示",MB_OK | MB_ICONINFORMATION);
		return;
	}
	CView* view1 = mainframe->GetActiveView();
	CDeu2000View * view2 = (CDeu2000View*)view1;
	CDeuDialog* pViewDlg = (CDeuDialog*)view2->m_DlgContainer.m_DeuTab.GetActiveWnd();
	CDeuDataView *pDeuDataView = (CDeuDataView*)pViewDlg;
	CMap1* m_map = &pDeuDataView->m_map1;
	*/

	p_map->SetCursorMode(MapWinGIS::cmNone);
	//m_idtyDlg.DoModal();//万炜
	//实现点击获取字段值功能
}

void CDeuTaskProcess::SelectFeatures(CDeuDMap* p_map)
{
	p_map->SetCursorMode(MapWinGIS::cmSelection);
	p_map->SetSendSelectBoxFinal(true);
}

void CDeuTaskProcess::RemoveSelections(CDeuDMap* p_map)
{
	long hndl1;
	hndl1 = p_map->get_LayerHandle(0);

	unsigned long ulcolorFill = p_map->get_ShapeLayerFillColor(hndl1);
	p_map->put_ShapeLayerFillColor(hndl1,ulcolorFill);

	unsigned long ulcolorLine = p_map->get_ShapeLayerLineColor(hndl1);
	float fLine = p_map->get_ShapeLayerLineWidth(hndl1);
	p_map->put_ShapeLayerLineColor(hndl1,ulcolorLine);
	p_map->put_ShapeLayerLineWidth(hndl1,fLine);

	unsigned long ulcolorPoint = p_map->get_ShapeLayerPointColor(hndl1);
	float fPoint = p_map->get_ShapeLayerPointSize(hndl1);
	long lPoint = p_map->get_ShapeLayerPointType(hndl1);
	p_map->put_ShapeLayerPointColor(hndl1,ulcolorPoint);
	p_map->put_ShapeLayerPointSize(hndl1,fPoint);
	p_map->put_ShapeLayerPointType(hndl1,lPoint);

	p_map->SetCursorMode(MapWinGIS::cmNone);
	//CDeuTreeCtrl* m_tree = mainframe->m_wndSelectedFeatures.GetTree();
	//m_tree->delete();
}

void CDeuTaskProcess::RemoveAllLayers(CDeuDMap* p_map)
{
	//CMainFrame* mainframe = (CMainFrame*)AfxGetMainWnd();
	//BOOL IsOK = CheckMap() ;
	//if (IsOK!=TRUE)
	//{	
	//	MessageBox(mainframe->m_hWnd, "请先切换到视图窗口！", "提示",MB_OK | MB_ICONINFORMATION);
	//	return;
	//}
	//CView* view1 = mainframe->GetActiveView();
	//CDeu2000View * view2 = (CDeu2000View*)view1;
	//CDeuDialog* pViewDlg = (CDeuDialog*)view2->m_DlgContainer.m_DeuTab.GetActiveWnd();
	//CDeuDataView *pDeuDataView = (CDeuDataView*)pViewDlg;
	//CMap1* m_map = &pDeuDataView->m_map1;

	//CMap1* m_map2 = mainframe->m_wndEagleEye.GetEagleEyeMap();

	//CDeuTreeCtrl* m_tree = mainframe->m_wndSelectedFeatures.GetTree();
	//m_tree->DeleteAllItems();
	//CCoordinateDlg* m_coord = mainframe->m_wndCoordinateSystem.GetCoordinateDlg();
	//m_coord->ClearEdits();
	//mainframe->m_wndCursorPosition.ClearUnits();
	//
	p_map->RemoveAllLayers();
	p_map->SetCursorMode(MapWinGIS::cmNone);
	p_map->RemoveAllLayers();
	p_map->ClearDrawings();
}

BOOL CDeuTaskProcess::CheckMap()
{
	BOOL IsOK = FALSE;

	//CMainFrame* mainframe = (CMainFrame*)AfxGetMainWnd();
	//CView* view1 = mainframe->GetActiveView();
	//CDeu2000View * view2 = (CDeu2000View*)view1;
	//
	//if(view2->m_DlgContainer.m_DeuTab.GetActiveTab() >= 0)
	//{
	//	CDeuDialog* pViewDlg = (CDeuDialog*)view2->m_DlgContainer.m_DeuTab.GetActiveWnd();
	//	CWnd* m_map = pViewDlg->GetDlgItem(IDC_MAP1);

	//	if (m_map)
	//	{
	//		IsOK = TRUE;
	//	}
	//}
    return IsOK;
}

CoordinateType CDeuTaskProcess::FindCoordinateType(CString strEllipseName)
{
	/*
	for(int n=0; n<GeoDataMapping.GeodeticNode.pGeodeticSeries.GetCount(); n++)
	{
		if(GeoDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._name.text.Compare(strEllipseName) == 0)
		{
			return GeoDetic;
		}
	}

	for(int n=0; n<GeoDataMapping.ProjectedNode.pProjectedSeries.GetCount(); n++)
	{
		if(GeoDataMapping.ProjectedNode.pProjectedSeries.GetAt(n)._name.text.Compare(strEllipseName) == 0)
		{
			return GeoProjected;
		}
	}

	return All;*/

	std::string                      strEllipName(strEllipseName);
	CEllipManager                    EllipManager;
	CoordinateType                   Type;

	EllipManager.GetEllipTypeByEllipName(strEllipName, &Type);

	return Type;
}
