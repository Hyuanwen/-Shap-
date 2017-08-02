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

//���ﷵ�ص�ö��ֵʹ��daifengԴ�����ö�٣��Ա��ִ������
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

//���ﷵ�ص�ö��ֵʹ��daifengԴ�����ö�٣��Ա��ִ������
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

//ö����������
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
			//���
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

			//ͶӰ
		case GeoProjected:
			{
				for(int n=0; n<GeoDataMapping.ProjectedNode.pProjectedSeries.GetCount(); n++)
				{
					if(GeoDataMapping.ProjectedNode.pProjectedSeries.GetAt(n)._name.text.Compare(strEllipseName) == 0)
					{
						_ProjectedSeries mSerises = GeoDataMapping.ProjectedNode.pProjectedSeries.GetAt(n);
						Ellipse.putref_Ellip_Name(mSerises._name.text);

						_GeodeticSeries mGeodetic;
						//����������
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

		//ʹ���´����ķ�������ȡ
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

		//ͶӰ����
		double dbParam[5] = {
			500000,//����ֵ
			0,
			117,//����������
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

		//�˴��е�С���� 2013-01-09
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

	//���굥λתΪ����/�ף�Ȼ����ø�ģ���µĲ���
	//double* _7param=new double[7];
	ULONG _npara ;
	HRESULT m_hr_status;

	//�����һ����Ƶ��������ͣ��ڶ�����Ƶ��������ͣ��ڿռ�ֱ���µõ�7����
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

	//7�����͵�һ����Ƶ��������ͣ��õ�ת����ĵڶ�������, ת����������������Ƶ�����������ͬ
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

	//ԭʼ��λ�µ�ת��������
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
 ����:	 	ʸ���ۺϲ�������(�Ĳ������߲���..etc)
 ����:		in SHORT aMode,
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
	
 ����:	 	 ---
 �����߼�:   ---
 ����:		2011-01-05
 ��ע:		add by hushichen
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
	//	//MessageBox(m_pMainFrm->m_hWnd,"���������������ȷ��","����",MB_OK | MB_ICONWARNING);
	//	AfxMessageBox("���������������ȷ��");
	//	return ;
	//}

	CDeuCoordType pCoordType = GetCoordType(CtrlPtCoordType,CtrlPtCoordType,CtrlPtCoordType);
	CDeuUnits pUnit = GetUnit(UnitType,UnitType);

	//if (pUnit == NULL || pCoordType == NULL)
	//{
	//	//MessageBox(m_pMainFrm->m_hWnd,"���������������ȷ��","����",MB_OK | MB_ICONWARNING);
	//	AfxMessageBox("���������������ȷ��");
	//	return ;
	//}

	//ISevenParams *pSevenParam = GetSevenParam(_param);
	//if(CheckData(pdeuData,DEUMAINFRM.m_hWnd)==FALSE)
	//{
	//	//MessageBox(mainframe->m_hWnd,L"�����������ȷ��ת����ֹ�����������",L"����",MB_OK | MB_ICONWARNING);
	//	return;
	//}

	CDeuTrans trans ;   

	//IDeuCoordType* _coord_type=NULL;		
	//_coord_type=pdeuData->m_Deu_coord_type;

	////������ת��ǰ����������Ϊ�ռ�ֱ��
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

	//���굥λתΪ����/�ף�Ȼ����ø�ģ���µĲ���
	//double* _7param=new double[7];
	//�����һ����Ƶ��������ͣ��ڶ�����Ƶ��������ͣ��ڿռ�ֱ���µõ�7����

	trans.CalculateParam(iCount,x,y,z,x2,y2,z2,_param,np);
	//doc->_7param=_7param;

	//new 7param
	trans.CalculateParam(iCount,x2,y2,z2,x,y,z,_inv_param,np);

	double* des_x=new double[iCount];
	double* des_y=new double[iCount];
	double* des_z=new double[iCount];

	//7�����͵�һ����Ƶ��������ͣ��õ�ת����ĵڶ�������, ת����������������Ƶ�����������ͬ
	trans.CoordTransPoints(_param,iCount,x,y,z,des_x,des_y,des_z);

	//double* res_x=new double[iCount];
	//double* res_y=new double[iCount];
	//double* res_z=new double[iCount];
	//double* _residual=new double[iCount];

	//ԭʼ��λ�µ�ת��������
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
 ����:	 	 դ���ۺϲ�������(�Ĳ������߲���..etc)
 ����:		 in SHORT aMode,
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
	
 ����:		---
 �����߼�:
 ����:		2011-01-05
 ��ע:		add by hushichen
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
	//	//MessageBox(m_pMainFrm->m_hWnd,"���������������ȷ��","����",MB_OK | MB_ICONWARNING);
	//	AfxMessageBox("���������������ȷ��");
	//	return ;
	//}

	CDeuCoordType pCoordType = GetCoordType(CtrlPtCoordType,CtrlPtCoordType,CtrlPtCoordType);
	CDeuUnits pUnit = GetUnit(UnitType,UnitType);
	//if (pUnit == NULL || pCoordType == NULL)
	//{
	//	//MessageBox(m_pMainFrm->m_hWnd,"���������������ȷ��","����",MB_OK | MB_ICONWARNING);
	//	AfxMessageBox("���������������ȷ��");
	//	return ;
	//}
	//if(CheckData(pdeuData,DEUMAINFRM.m_hWnd)==FALSE)
	//{
	//	//MessageBox(mainframe->m_hWnd,L"�����������ȷ��ת����ֹ�����������",L"����",MB_OK | MB_ICONWARNING);
	//	return;
	//}

	CDeuRasterTrans pRasterTrans;
	CDeuTrans pVectorTrans;
	long hr ;

	switch(aMode)
	{
	case MODEL_D2P4	:		//��ά�Ĳ���
	case MODEL_BURSA:		//��ά����ɳ
		{
			//IDeuCoordType* _coord_type=NULL;		
			//_coord_type=pdeuData->m_Deu_coord_type;

			////������ת��ǰ����������Ϊ�ռ�ֱ��
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

			//���굥λתΪ����/�ף�Ȼ����ø�ģ���µĲ���
			//double* _7param=new double[7];
			//�����һ����Ƶ��������ͣ��ڶ�����Ƶ��������ͣ��ڿռ�ֱ���µõ�7����
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

			//�������
			//�������������
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

			//7�����͵�һ����Ƶ��������ͣ��õ�ת����ĵڶ�������, ת����������������Ƶ�����������ͬ
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

			//ԭʼ��λ�µ�ת��������
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
	case MOD_AFFINE			://����任
	case MOD_POLYNOMIAL1	://һ�׶���ʽ
	case MOD_POLYNOMIAL2	://���׶���ʽ
	case MOD_POLYNOMIAL3	://���׶���ʽ
	case MOD_POLYNOMIAL4	://�Ľ׶���ʽ
		{
			//IDeuCoordType* _coord_type=NULL;		
			//_coord_type=pdeuData->m_Deu_coord_type;
			////������ת��ǰ����������Ϊ�ռ�ֱ��
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

			//���굥λתΪ����/�ף�Ȼ����ø�ģ���µĲ���
			//double* _7param=new double[7];
			//�����һ����Ƶ��������ͣ��ڶ�����Ƶ��������ͣ��ڿռ�ֱ���µõ�7����
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

			//�������
			//�������������
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

			//7�����͵�һ����Ƶ��������ͣ��õ�ת����ĵڶ�������, ת����������������Ƶ�����������ͬ
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

			//ԭʼ��λ�µ�ת��������
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

	//Ϊÿһ��ת������һ���߳�
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

	//1. ׼��Դ��Ŀ�� ����ϵ����
	CString strSrc, strDest;
	pRasterDlg->m_edit_InCoord.GetWindowText(strSrc);
	pRasterDlg->m_edit_OutCoord.GetWindowText(strDest);

	//1.1 ƥ������ϵת��������
	__COORDTYPE _type_src  = TaskProc.FindCoordindateType(strSrc);
	__COORDTYPE _type_dest = TaskProc.FindCoordindateType(strDest);
	CDeuEllipse pSrcEllip = TaskProc.GetDeuEllipse((_type_src==PLANE)?GeoProjected:GeoDetic, strSrc);
	CDeuEllipse pDesEllip = TaskProc.GetDeuEllipse((_type_dest==GEODETIC)?GeoDetic:GeoProjected, strDest);
	/*if (pSrcEllip == NULL || pDesEllip == NULL)
	{
		MessageBox(pRasterDlg->m_hWnd, "���������������ȷ��ת����ֹ�����������", "����",MB_OK | MB_ICONWARNING);
		return -1;
	}*/

	//2. ��������
	CDeuCoordType pCoordType = TaskProc.GetCoordType(_type_src, _type_dest,0);

	//3. ׼���ĵ�λֵ����
	CDeuUnits pUnit = TaskProc.GetUnit(_type_src, _type_dest);

	/*if (pUnit == NULL || pCoordType == NULL)
	{
		MessageBox(pRasterDlg->m_hWnd, "���������������ȷ��ת����ֹ�����������", "����",MB_OK | MB_ICONWARNING);
		return -1;
	}*/

	/*
		��ȡ�ռ�ο���Ϣ
		����˵����
			1. ��ȡ��������
			2. ������
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

	//������������������������������������������BEGIN������������������������
	/*�ж��Ƿ����ת��,
	����:
	����;
	����:������һ��.
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

	//ת�ļ� ��ע��Ŀǰֻת���ļ�	
	if(pRasterDlg->_FilsList_selected.GetCount() == 0)
	{	
		MessageBox(pRasterDlg->m_hWnd, "��ת���ļ��������ļ���", "ϵͳ��ʾ", MB_OK|MB_ICONEXCLAMATION);
		g_ThreadFinished = TRUE ;
		return 0;
	}

	pRasterDlg->ShowStatusPanel("������������������������������������դ���ļ�DEMת��������������������������������������\r\n");

	double StartTick(0), EndTick(0);
	char szBeginTime[10], szEndTime[10];

	//������Ҫ�Ե���ת����������ļ��������������Ƴ�
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
		m_hr_status = trans.CoordTransDEMEntry(_src, m_in_Path, _in_driver,  	/*Դ�ļ�*/
												_des, m_out_Path,_out_driver);	/*Ŀ���ļ�*/

		EndTick = GetTickCount();
		double Result = (EndTick - StartTick)*0.001;
		ZeroMemory(szEndTime, sizeof(szEndTime));
		GetSysCurrentTime(szEndTime);

		if(m_hr_status == E_FAIL_PRIVILEGE_UID)
		{
			strMsg.Format(_T("%s\r\n��ʼʱ�䣺%s\r\n����ʱ�䣺%s\r\n%s\r\n%s%.2lf%s\r\n"), _src, szBeginTime, szEndTime, UseAuthError,_T("��ʱ:"), Result, _T("��"));
			pRasterDlg->ShowStatusPanel(strMsg);
			continue;
		}
		else if(m_hr_status == E_FAIL_PRIVILEGE_EXTENT)
		{
			strMsg.Format(_T("%s\r\n��ʼʱ�䣺%s\r\n����ʱ�䣺%s\r\n%s\r\n%s%.2lf%s\r\n"), _src, szBeginTime, szEndTime, UseBeyoundError,_T("��ʱ:"), Result, _T("��"));
			pRasterDlg->ShowStatusPanel(strMsg);
			continue;
		}

		strMsg.Format(_T("%s\r\n��ʼʱ�䣺%s\r\n����ʱ�䣺%s\r\n%s%.2lf%s\r\n"), _src, szBeginTime, szEndTime, _T("��ʱ:"), Result, _T("��"));
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

	//1. ׼��Դ��Ŀ�� ����ϵ����
	CString strSrc = _T(""); 
	CString strDest = _T("");
	CString strDriver_Src = _T("");
	CString	strDriver_Dest = _T("");

	pVecDlg->m_ComboInput.GetWindowText(strDriver_Src);
	pVecDlg->m_ComboOutput.GetWindowText(strDriver_Dest);
	pVecDlg->m_edit_InCoord.GetWindowText(strSrc);	
	pVecDlg->m_edit_OutCoord.GetWindowText(strDest);

	//1.1 ƥ������ϵת��������
	__COORDTYPE _type_src = TaskProc.FindCoordindateType(strSrc);
	__COORDTYPE _type_dest = TaskProc.FindCoordindateType(strDest);
	CDeuEllipse pSrcEllip = TaskProc.GetDeuEllipse((_type_src==PLANE)?GeoProjected:GeoDetic, strSrc);
	CDeuEllipse pDesEllip = TaskProc.GetDeuEllipse((_type_dest==GEODETIC)?GeoDetic:GeoProjected, strDest);
	CDeuCoordType pCoordType = TaskProc.GetCoordType(_type_src, _type_dest, 0);

	//׼���ĵ�λֵ����
	CDeuUnits pUnit = TaskProc.GetUnit(_type_src, _type_dest);

	//yzg 2012-9-26 ���Ӷ�EXCEL�ļ�ת����֧�� ֻҪĿ��ת���ļ���Excel ��Ҫ�ж��Ƿ�������������� begin
	if (strDriver_Dest == _T("Excel"))
	{
		//��Ҫ�ж��Ƿ�����˲�������
		if (pVecDlg->m_Controlpoint_Dlg.m_install == FALSE)
		{
			MessageBox(pVecDlg->m_hWnd, "����EXCELת��ʱ,��Ҫ����EXCEL��ʽ�Ĳ�������,����[����]��ת����ֹ��", "ϵͳ��ʾ", MB_OK|MB_ICONEXCLAMATION);
			pVecDlg->EnbleAllController();
			g_ThreadFinished = TRUE ;
			return -1;
		}
	}
	//yzg 2012-9-26 ���Ӷ�EXCEL�ļ�ת����֧�� ֻҪĿ��ת���ļ���Excel ��Ҫ�ж��Ƿ�������������� end

	double * pParam = pVecDlg->m_Controlpoint_Dlg.m_7param;
	double srcMajor = 0;
	pSrcEllip.get_Major( srcMajor );

	short srcCoordType = 0;
	pCoordType.get_CoordType( srcCoordType ) ; 

	/*
	��ȡ�ռ�ο���Ϣ
	����˵����
	1. ��ȡ��������
	2. ������
	*/
	CDeuSpatialReference pSRS = TaskProc.GetSRS(TaskProc.FindCoordinateType(strDest), strDest);
	CDeuTrans trans;
	CString _src = _T("");
	CString _des = _T("");
	CString _in_driver = _T("");
	CString _out_driver = _T("");

	_in_driver  = strDriver_Src;
	_out_driver = strDriver_Dest;

	//��ʼ�����ӳ�
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

	//���Ŀ��ת�����ļ���Excel ����Ҫ����Ŀ���ļ����� yzg 2012-9-25 begin
	trans.putref_Excel(pVecDlg->m_Controlpoint_Dlg.m_t_format);
	//���Ŀ��ת�����ļ���Excel ����Ҫ����Ŀ���ļ����� yzg 2012-9-25 end

	/*�ж��Ƿ����ת��,
	����:
	����;
	����:������һ��.
	*/

	//����Ǹ���ת�����ʼ�����Ƹ���ת����������
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
		pVecDlg->ShowStatusPanel("������������������������������������ʸ�����ݿ�����ת��������������������������������������\r\n");
		if(pVecDlg->_TablesList_selected.GetCount() == 0){
			MessageBox(pVecDlg->m_hWnd, "��ת������", "ϵͳ��ʾ", MB_OK|MB_ICONEXCLAMATION);
			pVecDlg->TranFinish("ת����ֹ");
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
			HRESULT m_hr_status = trans.CoordTransDBEntry(_src, b_dbsrc, _in_driver,		/* Դ���ݿ����Ӵ� strDBSrc */
															_des, b_dbdest, _out_driver);	/* Ŀ���ݿ����Ӵ� strDBDest */
			EndTick = GetTickCount();
			ZeroMemory(szEndTime, sizeof(szEndTime));
			GetSysCurrentTime(szEndTime);
			double Result = (EndTick - StartTick)*0.001;

			//��Ȩ����
			if(m_hr_status == E_FAIL_PRIVILEGE_UID)
			{
				strMsg.Format(_T("%s\r\n��ʼʱ�䣺%s\r\n����ʱ�䣺%s\r\n%s\r\n%s%.2lf%s\r\n"), strSrc, szBeginTime, szEndTime, UseAuthError,_T("��ʱ:"), Result, _T("��"));
				pVecDlg->ShowStatusPanel(strMsg);
				continue;
			}
			else if(m_hr_status == E_FAIL_PRIVILEGE_EXTENT) //������Χ
			{
				strMsg.Format(_T("%s\r\n��ʼʱ�䣺%s\r\n����ʱ�䣺%s\r\n%s\r\n%s%.2lf%s\r\n"), strSrc, szBeginTime, szEndTime, UseBeyoundError,_T("��ʱ:"), Result, _T("��"));
				pVecDlg->ShowStatusPanel(strMsg);
				continue;
			}

			strMsg.Format(_T("���ڸ��±� %s ���Ժ�...\r\n"), strSrc);
			pVecDlg->ShowStatusPanel(strMsg);

			//����ע��
			//CString strSrcConn = "Provider=oraoledb.oracle.1; Data Source="+pVecDlg->strDBSid_Src+"; User Id="+pVecDlg->strDBUser_Src+"; Password="+pVecDlg->strDBPwd_Src+"; persist security info=false";
			//CString strDestConn = "Provider=oraoledb.oracle.1; Data Source="+pVecDlg->strDBSid_Dest+"; User Id="+pVecDlg->strDBUser_Dest+"; Password="+pVecDlg->strDBPwd_Dest+"; persist security info=false";

			m_hr_status = trans.CoordTransDBEntryForBLOB(_src, b_dbsrc, pVecDlg->strDBUser_Src, pVecDlg->strDBPwd_Src, 
															_des, b_dbdest, pVecDlg->strDBUser_Dest, pVecDlg->strDBPwd_Dest);

			strMsg.Format(_T("%s\r\n��ʼʱ�䣺%s\r\n����ʱ�䣺%s\r\n%s%.2lf%s\r\n"), strSrc, szBeginTime, szEndTime, _T("��ʱ:"), Result, _T("��"));
			//���ڽ���
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

		pVecDlg->ShowStatusPanel("---------------------------------SDEʸ��ת��---------------------------------");

		vecSDE = pVecDlg->GetSelVec();
		if (vecSDE.size() <= 0)
		{
			MessageBox(pVecDlg->m_hWnd, "��ת������", "ϵͳ��ʾ", MB_OK|MB_ICONEXCLAMATION);
			pVecDlg->ShowStatusPanel("ת����ֹ");
			g_ThreadFinished = TRUE ;
			pVecDlg->EnbleAllController();
			return -1;
		}

		//�ж�ArcSDE������
		if (!pVecDlg->GetSrcWorkspace() || !pVecDlg->GetDesWorkspace())
		{
			AfxMessageBox(_T("ArcSDE��δ���û�����ʧ��!"));
			pVecDlg->ShowStatusPanel("ת����ֹ");
			g_ThreadFinished = TRUE ;
			pVecDlg->EnbleAllController();
			return -1;
		}

		ArcSDEVector.SetTransParam(pVecDlg->GetSrcWorkspace(), pVecDlg->GetDesWorkspace(), trans, strPrjFullPath);

		//ע�ᴰ��
		ArcSDEVector.RegisterWnd(pVecDlg->m_hWnd);

		for (int i = 0; i < vecSDE.size(); i++)
		{
			StartTick = ::GetTickCount();
			ZeroMemory(szBeginTime, sizeof(szBeginTime));
			GetSysCurrentTime(szBeginTime);

			//ת������
			HRESULT hr = ArcSDEVector.TransFeatureDTType(vecSDE[i]);
			if (hr == S_FALSE)
			{
				strMsg.Format(_T("%sת��ʧ��!\n"), vecSDE[i].strName.c_str());
				pVecDlg->ShowStatusPanel(strMsg);
				continue;
			}

			EndTick = GetTickCount();
			ZeroMemory(szEndTime, sizeof(szEndTime));
			GetSysCurrentTime(szEndTime);
			double Result = (EndTick - StartTick)*0.001;

			strMsg.Format(_T("%s\r\n��ʼʱ�䣺%s\r\n����ʱ�䣺%s\r\n%s%.2lf%s\r\n"), "����", szBeginTime, szEndTime, _T("��ʱ:"), Result, _T("��"));
			//���ڽ���
			pVecDlg->ShowStatusPanel(strMsg);
		}
	}
	else
	{
		pVecDlg->ShowStatusPanel("������������������������������������ʸ���ļ�ת��������������������������������������\r\n");

		if(pVecDlg->_FilsList_selected.GetCount() == 0){
			MessageBox(pVecDlg->m_hWnd, "��ת������", "ϵͳ��ʾ", MB_OK|MB_ICONEXCLAMATION);
			pVecDlg->ShowStatusPanel("ת����ֹ");
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
				//����ļ���׺��.xls,�ļ�������ΪExcel11��֧��2007������
				if (strFile.Find(_T(".xlsx")) != -1 || strFile.Find(_T(".XLSX")) != -1)
				{
					_in_driver = _T("Excel12");
					_out_driver = _T("Excel12");
				}
				else
				{
					//֧��2003
					_in_driver = _T("Excel11");
					_out_driver = _T("Excel11");
				}
			}

			//alter by chenyong 2014-1-17
			//if (strDriver_Src != sz_TranType_Vector[6])
 			//{
 			//	strFile = strFile.Mid(0, strFile.ReverseFind('.'));
 			//}

			//��ͬ�ļ���
			//_src = strFile.AllocSysString();
			//_des = strFile.AllocSysString();

			StartTick = ::GetTickCount();
			ZeroMemory(szBeginTime, sizeof(szBeginTime));
			GetSysCurrentTime(szBeginTime);

			HRESULT m_hr_status = trans.CoordTransFileEntry(strFile, strInPath, _in_driver,			/*Դ�ļ�*/
															strFile, strOutPath,_out_driver, NULL);	/*Ŀ���ļ�*/
			EndTick = GetTickCount();
			ZeroMemory(szEndTime, sizeof(szEndTime));
			GetSysCurrentTime(szEndTime);
			double Result = (EndTick - StartTick)*0.001;

			//strSrc = _src;
			if(m_hr_status == E_FAIL_PRIVILEGE_UID)
			{
				strMsg.Format(_T("%s\r\n��ʼʱ�䣺%s\r\n����ʱ�䣺%s\r\n%s\r\n%s%.2lf%s\r\n"), strFile, szBeginTime, szEndTime, UseAuthError,_T("��ʱ:"), Result, _T("��"));
				pVecDlg->ShowStatusPanel(strMsg);
				continue;
			}
			else if(m_hr_status == E_FAIL_PRIVILEGE_EXTENT)
			{
				strMsg.Format(_T("%s\r\n��ʼʱ�䣺%s\r\n����ʱ�䣺%s\r\n%s\r\n%s%.2lf%s\r\n"), strFile, szBeginTime, szEndTime, UseBeyoundError,_T("��ʱ:"), Result, _T("��"));
				pVecDlg->ShowStatusPanel(strMsg);
				continue;
			}

			strMsg.Format(_T("%s\r\n��ʼʱ�䣺%s\r\n����ʱ�䣺%s\r\n%s%.2lf%s\r\n"), strSrc, szBeginTime, szEndTime, _T("��ʱ:"), Result, _T("��"));
			//���ڽ���
			pVecDlg->ShowStatusPanel(strMsg);
		}
	}

	MessageBox(pVecDlg->m_hWnd, "ת����ϣ�", "��ʾ",MB_OK | MB_ICONINFORMATION);

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

	//1. ׼��Դ��Ŀ�� ����ϵ����
	CString strSrc, strDest;
	CString strDriver_Src, strDriver_Dest;

	pVecPrjDlg->m_ComboInput.GetWindowText(strDriver_Src);
	pVecPrjDlg->m_ComboOutput.GetWindowText(strDriver_Dest);

	pVecPrjDlg->m_edit_InCoord.GetWindowText(strSrc);	
	pVecPrjDlg->m_edit_OutCoord.GetWindowText(strDest);

	//1.1 ƥ������ϵת��������
	__COORDTYPE _type_src = TaskProc.FindCoordindateType(strSrc);
	__COORDTYPE _type_dest = TaskProc.FindCoordindateType(strDest);
	CDeuEllipse pSrcEllip = TaskProc.GetDeuEllipse((_type_src==PLANE)?GeoProjected:GeoDetic, strSrc);
	CDeuEllipse pDesEllip = TaskProc.GetDeuEllipse((_type_dest==GEODETIC)?GeoDetic:GeoProjected, strDest);

	/*if (pSrcEllip == NULL || pDesEllip == NULL)
	{		
	MessageBox(pVecPrjDlg->m_hWnd, "���������������ȷ��ת����ֹ�����������", "ϵͳ��ʾ", MB_OK|MB_ICONEXCLAMATION);
	pVecPrjDlg->EnbleAllController();
	return -1;
	}*/

	CDeuCoordType pCoordType = TaskProc.GetCoordType(_type_src, _type_dest, 0);

	//׼���ĵ�λֵ����
	CDeuUnits pUnit = TaskProc.GetUnit(_type_src, _type_dest);

	/*if (pUnit == NULL || pCoordType == NULL)
	{
	MessageBox(pVecPrjDlg->m_hWnd, "���������������ȷ��ת����ֹ�����������", "ϵͳ��ʾ", MB_OK|MB_ICONEXCLAMATION);
	pVecPrjDlg->EnbleAllController();
	return -1;
	}*/

	//yzg 2012-9-26 ���Ӷ�EXCEL�ļ�ͶӰ��֧�� ֻҪĿ��ת���ļ���Excel ��Ҫ�ж��Ƿ�������������� begin
	if (strDriver_Dest == _T("Excel"))
	{
		//��Ҫ�ж��Ƿ�����˲�������
		if (pVecPrjDlg->m_Controlpoint_Dlg.m_install == FALSE)
		{
			MessageBox(pVecPrjDlg->m_hWnd, "����EXCELת��ʱ,��Ҫ����EXCEL��ʽ�Ĳ�������,����[����]��ת����ֹ��", "ϵͳ��ʾ", MB_OK|MB_ICONEXCLAMATION);
			pVecPrjDlg->EnbleAllController();
			g_ThreadFinished = TRUE ;
			return -1;
		}
	}
	//yzg 2012-9-26 ���Ӷ�EXCEL�ļ�ͶӰ��֧�� ֻҪĿ��ת���ļ���Excel ��Ҫ�ж��Ƿ�������������� end

	//ISevenParams *pSevenParam = _Task2000.GetSevenParam(pdeuTask->_7param);

	/***/
	double * pParam = pVecPrjDlg->m_Controlpoint_Dlg.m_7param;

	double srcMajor = 0;
	pSrcEllip.get_Major( srcMajor );

	SHORT srcCoordType = 0;
	pCoordType.get_CoordType( srcCoordType ) ; 

	/*
	��ȡ�ռ�ο���Ϣ
	����˵����
	1. ��ȡ��������
	2. ������
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

	//��ʼ�����ӳ�
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

	//���Ŀ��ת�����ļ���Excel ����Ҫ����Ŀ���ļ����� yzg 2012-9-27 begin
	trans.putref_Excel(pVecPrjDlg->m_Controlpoint_Dlg.m_t_format);
	//���Ŀ��ת�����ļ���Excel ����Ҫ����Ŀ���ļ����� yzg 2012-9-27 end

	////����Ķϵ�ִ�й��ܵ��жϴ���
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
	//			//�����￪ʼ�ϵ���ת
	//			vec_FileName.assign(it,pdeuTask->TableList.end());
	//			vec_FileName_Out = vec_FileName;
	//			break;
	//		}
	//	}
	//}
	//else
	//{
	//	//������״̬����ʶ���ʱ��Ĭ��Ϊ����ת��
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

	//ת�ļ�
	if (strDriver_Src == sz_TranType_Vector[4]) //oracle
	{
		pVecPrjDlg->ShowStatusPanel("������������������������������������ʸ�����ݿ�����ͶӰ������������������������������������\r\n");
		if(pVecPrjDlg->_TablesList_selected.GetCount() == 0)
		{
			MessageBox(pVecPrjDlg->m_hWnd, "��ͶӰ����", "ϵͳ��ʾ", MB_OK|MB_ICONEXCLAMATION);
			pVecPrjDlg->TranFinish("ͶӰ��ֹ");
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
			HRESULT m_hr_status = trans.CoordTransDBEntry(_src, b_dbsrc, _in_driver,		/* Դ���ݿ����Ӵ� strDBSrc */
															_des, b_dbdest, _out_driver);	/* Ŀ���ݿ����Ӵ� strDBDest */

			EndTick = GetTickCount();
			ZeroMemory(szEndTime, sizeof(szEndTime));
			GetSysCurrentTime(szEndTime);
			double Result = (EndTick - StartTick)*0.001;

			//��Ȩ����
			if(m_hr_status == E_FAIL_PRIVILEGE_UID)
			{
				strMsg.Format(_T("%s\r\n��ʼʱ�䣺%s\r\n����ʱ�䣺%s\r\n%s\r\n%s%.2lf%s\r\n"), strSrc, szBeginTime, szEndTime, UseAuthError,_T("��ʱ:"), Result, _T("��"));
				pVecPrjDlg->ShowStatusPanel(strMsg);
				continue;
			}
			else if(m_hr_status == E_FAIL_PRIVILEGE_EXTENT) //������Χ
			{
				strMsg.Format(_T("%s\r\n��ʼʱ�䣺%s\r\n����ʱ�䣺%s\r\n%s\r\n%s%.2lf%s\r\n"), strSrc, szBeginTime, szEndTime, UseBeyoundError,_T("��ʱ:"), Result, _T("��"));
				pVecPrjDlg->ShowStatusPanel(strMsg);
				continue;
			}

			strMsg.Format(_T("���ڸ��±� %s ���Ժ�...\r\n"), strSrc);
			pVecPrjDlg->ShowStatusPanel(strMsg);

			m_hr_status = trans.CoordTransDBEntryForBLOB(_src, b_dbsrc, pVecPrjDlg->strDBUser_Src, pVecPrjDlg->strDBPwd_Src, 
															_des, b_dbdest, pVecPrjDlg->strDBUser_Dest, pVecPrjDlg->strDBPwd_Dest);

			strMsg.Format(_T("%s\r\n��ʼʱ�䣺%s\r\n����ʱ�䣺%s\r\n%s%.2lf%s\r\n"), strSrc, szBeginTime, szEndTime, _T("��ʱ:"), Result, _T("��"));

			//���ڽ���
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

		pVecPrjDlg->ShowStatusPanel("---------------------------------SDEʸ��ת��---------------------------------");

		vecSDE = pVecPrjDlg->GetSelVec();
		if (vecSDE.size() <= 0)
		{
			MessageBox(pVecPrjDlg->m_hWnd, "��ת������", "ϵͳ��ʾ", MB_OK|MB_ICONEXCLAMATION);
			pVecPrjDlg->ShowStatusPanel("ת����ֹ");
			g_ThreadFinished = TRUE ;
			pVecPrjDlg->EnbleAllController();
			return -1;
		}

		//�ж�ArcSDE������
		if (!pVecPrjDlg->GetSrcWorkspace() || !pVecPrjDlg->GetDesWorkspace())
		{
			AfxMessageBox(_T("ArcSDE��δ���û�����ʧ��!"));
			pVecPrjDlg->ShowStatusPanel("ת����ֹ");
			g_ThreadFinished = TRUE ;
			pVecPrjDlg->EnbleAllController();
			return -1;
		}

		ArcSDEVector.SetTransParam(pVecPrjDlg->GetSrcWorkspace(), pVecPrjDlg->GetDesWorkspace(), trans, strPrjFullPath);

		//ע�ᴰ�� add by chenyong 2013-12-4
		ArcSDEVector.RegisterWnd(pVecPrjDlg->m_hWnd);

		for (int i = 0; i < vecSDE.size(); i++)
		{
			StartTick = ::GetTickCount();
			ZeroMemory(szBeginTime, sizeof(szBeginTime));
			GetSysCurrentTime(szBeginTime);

			//ת������
			hr = ArcSDEVector.TransFeatureDTType(vecSDE[i]);
			if (hr == S_FALSE)
			{
				strMsg.Format(_T("ͶӰʸ������%sʧ��!"), vecSDE[i].strName.c_str());
				pVecPrjDlg->ShowStatusPanel(strMsg);
				continue;
			}

			EndTick = GetTickCount();
			ZeroMemory(szEndTime, sizeof(szEndTime));
			GetSysCurrentTime(szEndTime);
			double Result = (EndTick - StartTick)*0.001;

			strMsg.Format(_T("%s\r\n��ʼʱ�䣺%s\r\n����ʱ�䣺%s\r\n%s%.2lf%s\r\n"), "����", szBeginTime, szEndTime, _T("��ʱ:"), Result, _T("��"));

			//���ڽ���
			pVecPrjDlg->ShowStatusPanel(strMsg);
		}
	}
	else
	{

		pVecPrjDlg->ShowStatusPanel("������������������������������������ʸ���ļ�ͶӰ������������������������������������\r\n");

		if(pVecPrjDlg->_FilsList_selected.GetCount() == 0)
		{
			MessageBox(pVecPrjDlg->m_hWnd, "���ļ�ͶӰ", "ϵͳ��ʾ", MB_OK|MB_ICONEXCLAMATION);
			pVecPrjDlg->ShowStatusPanel("ͶӰ��ֹ");
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

			//��ͬ�ļ���
			_src = strFile.AllocSysString();
			_des = strFile.AllocSysString();

			StartTick = ::GetTickCount();
			ZeroMemory(szBeginTime, sizeof(szBeginTime));
			GetSysCurrentTime(szBeginTime);

			HRESULT m_hr_status = trans.CoordTransFileEntry(_src, m_in_Path, _in_driver,			/*Դ�ļ�*/
															_des, m_out_Path,_out_driver, NULL);	/*Ŀ���ļ�*/

			EndTick = GetTickCount();
			ZeroMemory(szEndTime, sizeof(szEndTime));
			GetSysCurrentTime(szEndTime);
			double Result = (EndTick - StartTick)*0.001;

			strSrc = _src;
			if(m_hr_status == E_FAIL_PRIVILEGE_UID)
			{
				strMsg.Format(_T("%s\r\n��ʼʱ�䣺%s\r\n����ʱ�䣺%s\r\n%s\r\n%s%.2lf%s\r\n"), strSrc, szBeginTime, szEndTime, UseAuthError,_T("��ʱ:"), Result, _T("��"));
				pVecPrjDlg->ShowStatusPanel(strMsg);
				continue;
			}
			else if(m_hr_status == E_FAIL_PRIVILEGE_EXTENT)
			{
				strMsg.Format(_T("%s\r\n��ʼʱ�䣺%s\r\n����ʱ�䣺%s\r\n%s\r\n%s%.2lf%s\r\n"), strSrc, szBeginTime, szEndTime, UseBeyoundError,_T("��ʱ:"), Result, _T("��"));
				pVecPrjDlg->ShowStatusPanel(strMsg);
				continue;
			}

			strMsg.Format(_T("%s\r\n��ʼʱ�䣺%s\r\n����ʱ�䣺%s\r\n%s%.2lf%s\r\n"), strSrc, szBeginTime, szEndTime, _T("��ʱ:"), Result, _T("��"));
			
			//���ڽ���
			pVecPrjDlg->ShowStatusPanel(strMsg);
		}
	}

	MessageBox(pVecPrjDlg->m_hWnd, "ת����ϣ�", "��ʾ",MB_OK | MB_ICONINFORMATION);

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

	//1. ׼��Դ��Ŀ�� ����ϵ����
	CString strSrc, strDest;
	pProjectDlg->m_edit_InCoord.GetWindowText(strSrc);
	pProjectDlg->m_edit_OutCoord.GetWindowText(strDest);

	//1.1 ƥ������ϵת��������
	__COORDTYPE _type_src  = TaskProc.FindCoordindateType(strSrc);
	__COORDTYPE _type_dest = TaskProc.FindCoordindateType(strDest);
	CDeuEllipse pSrcEllip = TaskProc.GetDeuEllipse((_type_src==PLANE)?GeoProjected:GeoDetic, strSrc);
	CDeuEllipse pDesEllip = TaskProc.GetDeuEllipse((_type_dest==GEODETIC)?GeoDetic:GeoProjected, strDest);

	//2. ��������
	CDeuCoordType pCoordType = TaskProc.GetCoordType(_type_src, _type_dest,0);

	//3. ׼���ĵ�λֵ����
	CDeuUnits pUnit = TaskProc.GetUnit(_type_src, _type_dest);

	//yzg 2012-8-22 15��13 ����ƽ��ֱ��ͶӰ�������ϵʱ ��Ҫ�������������������ϵ������һ������ ��������ת���󾭶Ȳ���ȷ������ 
	//                     ��ʱ����ͨ�����뾭���ֶδ���Ŀ������ϵ ������Ŀ������ϵ�Ǵ������ϵͳʱ ���Ӵ��������� begin
	//4
	if (_type_src == PLANE && _type_dest == GEODETIC)
	{
		//���Դ����ϵͳ�����뾭��ֵ
		double d_centrol_long = 0;
		double d_src_false_east = 0;
		pSrcEllip.get_Centrol_Long(d_centrol_long);
		pDesEllip.putref_Centrol_Long(d_centrol_long);

		//Ŀ������ϵ�в������붫��ֵ
		pSrcEllip.get_False_E(d_src_false_east);
		pDesEllip.putref_False_E(d_src_false_east);
	}
	//yzg 2012-8-22 15��13 ����ƽ��ֱ��ͶӰ�������ϵʱ ��Ҫ�������������������ϵ������һ������ ��������ת���󾭶Ȳ���ȷ������ end

	/*
	��ȡ�ռ�ο���Ϣ
	����˵����
	1. ��ȡ��������
	2. ������
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
		//��ȡĿ���ļ������ļ�·�� add by chenyong 2013-10-15
		string strPrjFullPath = TaskProc.GetPrjFullPathByName(strDest);

		vector<STR_SDEINFO>					vecSDE;
		CArcSDERaster						ArcSDERaster;
		CString								strMsg;

		pProjectDlg->ShowStatusPanel("---------------------------------SDEդ��ͶӰ---------------------------------");
		vecSDE = pProjectDlg->m_vecSelect;
		if (vecSDE.size() <= 0)
		{
			MessageBox(pProjectDlg->m_hWnd, "��ת������", "ϵͳ��ʾ", MB_OK|MB_ICONEXCLAMATION);
			pProjectDlg->ShowStatusPanel("ת����ֹ");
			g_ThreadFinished = TRUE ;
			pProjectDlg->EnbleAllController();
			return -1;
		}

		//�ж�ArcSDE������
		if (!pProjectDlg->m_pSrcWS || !pProjectDlg->m_pDesWS)
		{
			AfxMessageBox(_T("ArcSDE��δ���û�����ʧ��!"));
			pProjectDlg->ShowStatusPanel("ת����ֹ");
			g_ThreadFinished = TRUE ;
			pProjectDlg->EnbleAllController();
			return -1;
		}

		ArcSDERaster.SetTransParam(pProjectDlg->m_pSrcWS, pProjectDlg->m_pDesWS, trans, strPrjFullPath);

		//ע�ᴰ��
		ArcSDERaster.RegisterWnd(pProjectDlg->m_hWnd);

		for (int i = 0; i < vecSDE.size(); i++)
		{
			StartTick = ::GetTickCount();
			ZeroMemory(szBeginTime, sizeof(szBeginTime));
			GetSysCurrentTime(szBeginTime);

			//ת������
			HRESULT hr = ArcSDERaster.ProjectRasterDTType(vecSDE[i]);
			if (hr == S_FALSE)
			{
				strMsg.Format(_T("ͶӰդ������%sʧ��!\n"), vecSDE[i].strName.c_str());
				pProjectDlg->ShowStatusPanel(strMsg);
				continue;
			}

			EndTick = GetTickCount();
			ZeroMemory(szEndTime, sizeof(szEndTime));
			GetSysCurrentTime(szEndTime);
			double Result = (EndTick - StartTick)*0.001;

			strMsg.Format(_T("%s\r\n��ʼʱ�䣺%s\r\n����ʱ�䣺%s\r\n%s%.2lf%s\r\n"), "����", szBeginTime, szEndTime, _T("��ʱ:"), Result, _T("��"));
			//���ڽ���
			pProjectDlg->ShowStatusPanel(strMsg);
		}
	}
	else
	{
		//ת�ļ� ��ע��Ŀǰֻת���ļ�	
		if(pProjectDlg->_FilsList_selected.GetCount() == 0)
		{
			MessageBox(pProjectDlg->m_hWnd, "��ת���ļ��������ļ���", "ϵͳ��ʾ", MB_OK|MB_ICONEXCLAMATION);

			//pProjectDlg->ShowStatusPanel("ת����ֹ");

			g_ThreadFinished = TRUE ;
			pProjectDlg->EnbleAllController();
			return -1;
		}

		pProjectDlg->ShowStatusPanel("������������������������������������դ���ļ�ͶӰ������������������������������������\r\n");

		HRESULT m_hr_status;
		//������Ҫ�Ե���ת����������ļ��������������Ƴ�
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

			//	str.Format("����ת����%d���ļ�.", n);
			//	pProjectDlg->ShowStatusPanel(str);
			StartTick = ::GetTickCount();
			ZeroMemory(szBeginTime, sizeof(szBeginTime));
			GetSysCurrentTime(szBeginTime);

			m_hr_status = trans.CoordTransFileEntry(_src, m_in_Path, _in_driver,			/*Դ�ļ�*/
													_des, m_out_Path,_out_driver, NULL);	/*Ŀ���ļ�*/
			EndTick = GetTickCount();
			double Result = (EndTick - StartTick)*0.001;
			ZeroMemory(szEndTime, sizeof(szEndTime));
			GetSysCurrentTime(szEndTime);

			if(m_hr_status == E_FAIL_PRIVILEGE_UID)
			{
				strMsg.Format(_T("%s\r\n��ʼʱ�䣺%s\r\n����ʱ�䣺%s\r\n%s\r\n%s%.2lf%s\r\n"), _src, szBeginTime, szEndTime, UseAuthError,_T("��ʱ:"), Result, _T("��"));
				pProjectDlg->ShowStatusPanel(strMsg);
				continue;
			}
			else if(m_hr_status == E_FAIL_PRIVILEGE_EXTENT)
			{
				strMsg.Format(_T("%s\r\n��ʼʱ�䣺%s\r\n����ʱ�䣺%s\r\n%s\r\n%s%.2lf%s\r\n"), _src, szBeginTime, szEndTime, UseBeyoundError,_T("��ʱ:"), Result, _T("��"));
				pProjectDlg->ShowStatusPanel(strMsg);
				continue;
			}
			strMsg.Format(_T("%s\r\n��ʼʱ�䣺%s\r\n����ʱ�䣺%s\r\n%s%.2lf%s\r\n"), _src, szBeginTime, szEndTime, _T("��ʱ:"), Result, _T("��"));
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

	//1. ׼��Դ��Ŀ�� ����ϵ����
	CString strSrc, strDest;
	pRasterDlg->m_edit_InCoord.GetWindowText(strSrc);
	pRasterDlg->m_edit_OutCoord.GetWindowText(strDest);

	//1.1 ƥ������ϵת��������
	__COORDTYPE _type_src  = TaskProc.FindCoordindateType(strSrc);
	__COORDTYPE _type_dest = TaskProc.FindCoordindateType(strDest);
	CDeuEllipse pSrcEllip = TaskProc.GetDeuEllipse((_type_src==PLANE)?GeoProjected:GeoDetic, strSrc);
	CDeuEllipse pDesEllip = TaskProc.GetDeuEllipse((_type_dest==GEODETIC)?GeoDetic:GeoProjected, strDest);

	//2. ��������
	CDeuCoordType pCoordType = TaskProc.GetCoordType(_type_src, _type_dest,0);

	//3. ׼���ĵ�λֵ����
	CDeuUnits pUnit = TaskProc.GetUnit(_type_src, _type_dest);

	/*
	��ȡ�ռ�ο���Ϣ
	����˵����
	1. ��ȡ��������
	2. ������
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

	//������������������������������������������BEGIN������������������������
	/*�ж��Ƿ����ת��,
	����:
	����;
	����:������һ��.
	*/

	if ((pRasterDlg->iModel) == MODEL_GRID)
	{	
		trans.InitGridTranslate(pRasterDlg->m_Controlpoint_Dlg.m_GridParameter);
	}

	//������������������������������������������END������������������������
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
		//��ȡĿ���ļ������ļ�·�� add by chenyong 2013-10-15
		string strPrjFullPath = TaskProc.GetPrjFullPathByName(strDest);
		vector<STR_SDEINFO>					vecSDE;
		CArcSDERaster						ArcSDERaster;
		CString								strMsg;
		HRESULT								hr = S_OK;

		pRasterDlg->ShowStatusPanel("---------------------------------SDEդ��ת��---------------------------------");

		vecSDE = pRasterDlg->m_vecSelect;
		if (vecSDE.size() <= 0)
		{
			MessageBox(pRasterDlg->m_hWnd, "��ת������", "ϵͳ��ʾ", MB_OK|MB_ICONEXCLAMATION);
			pRasterDlg->ShowStatusPanel("ת����ֹ");
			g_ThreadFinished = TRUE ;
			pRasterDlg->EnbleAllController();
			return -1;
		}

		//�ж�ArcSDE������
		if (!pRasterDlg->m_pSrcWS || !pRasterDlg->m_pDesWS)
		{
			AfxMessageBox(_T("ArcSDE��δ���û�����ʧ��!"));
			pRasterDlg->ShowStatusPanel("ת����ֹ");
			g_ThreadFinished = TRUE ;
			pRasterDlg->EnbleAllController();
			return -1;
		}

		ArcSDERaster.SetTransParam(pRasterDlg->m_pSrcWS, pRasterDlg->m_pDesWS, trans, strPrjFullPath);

		//ע�ᴰ�� add by chenyong 2013-12-4
		ArcSDERaster.RegisterWnd(pRasterDlg->m_hWnd);

		char    szBeginTime[128] = {0};
		char    szEndTime[128] = {0};
		for (int i = 0; i < vecSDE.size(); i++)
		{
			StartTick = ::GetTickCount();
			ZeroMemory(szBeginTime, sizeof(szBeginTime));
			GetSysCurrentTime(szBeginTime);

			//ת������
			hr = ArcSDERaster.TransRasterDTType(vecSDE[i]);
			if (hr == S_FALSE)
			{
				strMsg.Format(_T("ת��դ������%sʧ��!"), vecSDE[i].strName.c_str());
				pRasterDlg->ShowStatusPanel(strMsg);
				continue;
			}

			EndTick = GetTickCount();
			ZeroMemory(szEndTime, sizeof(szEndTime));
			GetSysCurrentTime(szEndTime);
			double Result = (EndTick - StartTick)*0.001;

			strMsg.Format(_T("%s\r\n��ʼʱ�䣺%s\r\n����ʱ�䣺%s\r\n%s%.2lf%s\r\n"), "����", szBeginTime, szEndTime, _T("��ʱ:"), Result, _T("��"));
			//���ڽ���
			pRasterDlg->ShowStatusPanel(strMsg);
		}

		::SendMessage(pRasterDlg->m_hWnd,WM_TASK_FINISH_ALL,NULL,NULL);
	}
	else
	{
		//ת�ļ� ��ע��Ŀǰֻת���ļ�	
		if(pRasterDlg->_FilsList_selected.GetCount() == 0)
		{
			MessageBox(pRasterDlg->m_hWnd, "��ת���ļ��������ļ���", "ϵͳ��ʾ", MB_OK|MB_ICONEXCLAMATION);

			//pRasterDlg->ShowStatusPanel("ת����ֹ");

			g_ThreadFinished = TRUE ;
			pRasterDlg->EnbleAllController();
			return -1;
		}

		pRasterDlg->ShowStatusPanel("������������������������������������դ���ļ�ת��������������������������������������\r\n");

		double StartTick(0), EndTick(0);
		char szBeginTime[10], szEndTime[10];

		HRESULT m_hr_status;
		//������Ҫ�Ե���ת����������ļ��������������Ƴ�
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

			//	str.Format("����ת����%d���ļ�.", n);
			//	pRasterDlg->ShowStatusPanel(str);

			StartTick = ::GetTickCount();
			ZeroMemory(szBeginTime, sizeof(szBeginTime));
			GetSysCurrentTime(szBeginTime);

			m_hr_status = trans.CoordTransFileEntry(_src, m_in_Path, _in_driver,			/*Դ�ļ�*/
													_des, m_out_Path,_out_driver, NULL);	/*Ŀ���ļ�*/
			EndTick = GetTickCount();
			double Result = (EndTick - StartTick)*0.001;
			ZeroMemory(szEndTime, sizeof(szEndTime));
			GetSysCurrentTime(szEndTime);

			if(m_hr_status == E_FAIL_PRIVILEGE_UID)
			{
				strMsg.Format(_T("%s\r\n��ʼʱ�䣺%s\r\n����ʱ�䣺%s\r\n%s\r\n%s%.2lf%s\r\n"), _src, szBeginTime, szEndTime, UseAuthError,_T("��ʱ:"), Result, _T("��"));
				pRasterDlg->ShowStatusPanel(strMsg);
				continue;
			}
			else if(m_hr_status == E_FAIL_PRIVILEGE_EXTENT)
			{
				strMsg.Format(_T("%s\r\n��ʼʱ�䣺%s\r\n����ʱ�䣺%s\r\n%s\r\n%s%.2lf%s\r\n"), _src, szBeginTime, szEndTime, UseBeyoundError,_T("��ʱ:"), Result, _T("��"));
				pRasterDlg->ShowStatusPanel(strMsg);
				continue;
			}

			strMsg.Format(_T("%s\r\n��ʼʱ�䣺%s\r\n����ʱ�䣺%s\r\n%s%.2lf%s\r\n"), _src, szBeginTime, szEndTime, _T("��ʱ:"), Result, _T("��"));
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
	//CTaskת��CNode
	CNode *node = new CNode;
	node->tag_name = L"dy";
	node->ele_name = L"dy";		//����
	int iCount = lisEllipse.size();
	for (int i = 0; i<iCount;i++)
	{
		CNode *node_task = getListItem(lisEllipse,i);
		node->_sub_nodes.push_back(node_task);
	}

	//CNode���µ�.ini�ļ�
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

		//�������������ΪRGB�����Ĳ���
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

		//��������ɫ
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
		m_map2->AddLayer(pSf2,true);                                         //ӥ����ͼͬ���������ͼ��ͼ

		//���ӥ����ͼ�е������ɫ��������ͼһ��
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
		
		//��ȡͼ����Ϣ
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
			const char *pszSystem = "��";
			mainframe->m_wndCoordinateSystem.SetSystem(pszSystem);
			mainframe->m_wndCoordinateSystem.SetDatum(pszSystem);
			char *pszunits = "��";
			mainframe->m_wndCoordinateSystem.SetUnits(pszunits);
			pszunits = "�޵�λ";
			mainframe->m_wndCursorPosition.SetUnits(pszunits);	
			OGRDataSource::DestroyDataSource(poDS);	
			return;
		}
		char  *pszWKT = NULL;
		poRSR->exportToWkt(&pszWKT);		
		TRACE("%s\n", pszWKT);		

		//������ʱ��ȡ����
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
		m_map2->AddLayer(pImage2,true);                                         //ӥ����ͼͬ���������ͼ��ͼ
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
		//MessageBox(mainframe->m_hWnd,_T("�ݲ�֧�������صĸ�ʽ����!������ѡ��"),_T("��ʾ"),MB_OK | MB_ICONINFORMATION) ;
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

//Ĭ��״̬
void CDeuTaskProcess::None(CDeuDMap* p_map)
{
	/*CMainFrame* mainframe = (CMainFrame*)AfxGetMainWnd();
	BOOL IsOK = CheckMap() ;
	if (IsOK!=TRUE)
	{	
		MessageBox(mainframe->m_hWnd, "�����л�����ͼ���ڣ�", "��ʾ",MB_OK | MB_ICONINFORMATION);
		return;
	}
	CView* view1 = mainframe->GetActiveView();
	CDeu2000View * view2 = (CDeu2000View*)view1;
	CDeuDialog* pViewDlg = (CDeuDialog*)view2->m_DlgContainer.m_DeuTab.GetActiveWnd();
	CDeuDataView *pDeuDataView = (CDeuDataView*)pViewDlg;
	CMap1* m_map = &pDeuDataView->m_map1;
	*/

	p_map->SetCursorMode(MapWinGIS::cmNone);
	//m_idtyDlg.DoModal();//���
	//ʵ�ֵ����ȡ�ֶ�ֵ����
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
	//	MessageBox(mainframe->m_hWnd, "�����л�����ͼ���ڣ�", "��ʾ",MB_OK | MB_ICONINFORMATION);
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
