#include "StdAfx.h"
#include "Deu2000Task.h"
#include "DeuData.h"
#include "deuTransForm.h"
//#include "DeuTransForm_i.c"
#include "MainFrm.h"
#include "Deu2000Doc.h"
#include "Deu2000View.h"
#include "DeuTask.h"
#include "DeuFunction.h"
#include "ogrsf_frmts.h"


IFFUNC(TaskName);

IFFUNC_2(m_Name);

#define FIND_NODE_IF(l,n) \
	std::find_if(l.begin(),l.end(),IFFunctor2_m_Name<CDeuCoordinateSystem*,CString>(n));

DWORD WINAPI ThreadFunc(HANDLE Thread);
DWORD WINAPI ThreadFunc_Raster(HANDLE Thread);
DWORD WINAPI ThreadFunc_RasterDEM(HANDLE Thread);



//////////////////////////////////////////////////////////////////////////

HRESULT CDeu2000Task::TestDB(CString strConn)
{
	LONG id;
	HRESULT hr = g_ConnPool->Connect(strConn.AllocSysString(),&id);

	return hr;
}


std::vector<CString>* CDeu2000Task::GetTabListInDB(CString strConn)
{		
	CoInitialize(NULL);
	IDeuDatabase *pDB;
	HRESULT hr = CoCreateInstance(CLSID_DeuDatabase,   NULL,   CLSCTX_ALL,   IID_IDeuDatabase,   (void**)&pDB);   
	if   (SUCCEEDED(hr)   &&   (pDB   !=   NULL))   
	{   						
		//trans->ReleaseDispatch();  
	}

	pDB->putref_ConnPool(g_ConnPool);
		
	hr = pDB->Connect(strConn.AllocSysString());

	std::vector<CString> * p_vecTabList = new std::vector<CString>;
	BSTR * bstrTab;

	VARIANT * var;


	char  *b1 ;

	if (hr == S_OK )
	{		
		pDB->GetTabList(&var);
		VARIANT varArr =*var;
		SAFEARRAY *p = varArr.parray;

		BSTR bstr1;
		LPSTR lpstr1;
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

//////////////////////////////////////////////////////////////////////////
CDeu2000Task::CDeu2000Task(CMainFrame* pMainFrn)
{
	//m_CoonPool = NULL;
	m_pMainFrm = pMainFrn;
	 
}

CDeu2000Task::~CDeu2000Task(void)
{

}




CMainFrame&  CDeu2000Task::GetMainFrm()
{
	return *m_pMainFrm;
}


void CDeu2000Task::Task_RegisterWnd(HWND hWnd)
{

	CDeuData *pdeuData = m_pMainFrm->m_deuData;
	//doc->m_DY_Trans->RegisterWnd(hWnd);
	pdeuData->m_hwnd=hWnd;

	return ;
}



void CDeu2000Task::LoadSRS()
{
#if 0
		//加载目标椭球的空间参考
		CMainFrame* mainframe=(CMainFrame*) ::AfxGetMainWnd();
		CdfData* doc= (mainframe->m_doc);

		CNode* CS=doc->m_des_ellipse;

#define TSTOF(n) _tstof((LPCTSTR)getListItem(CS->_sub_nodes,n)->data)

		CString CSName=CS->ele_name;
		CString Datum= ( getListItem(CS->_sub_nodes,4))->data;



		CString Ellipse=getListItem(CS->_sub_nodes,4)->data;
		CString CSProj=getListItem(CS->_sub_nodes,15)->data;
		DOUBLE SemiMajor=TSTOF(1);
		DOUBLE InvFlattening=TSTOF(3);

		BSTR Proj=CSProj.AllocSysString();
		BSTR _bstr_Ellipse=Ellipse.AllocSysString();
		BSTR _bstr_Name=CSName.AllocSysString();
		BSTR _bstr_Datum=Datum.AllocSysString();


		doc->m_DY_SRS->put_GeogCS(&_bstr_Name,&_bstr_Name,&_bstr_Ellipse,&SemiMajor,&InvFlattening,NULL);
		doc->m_DY_SRS->put_Projection(CSProj.AllocSysString());
		doc->m_DY_SRS->put_LinearUnit(L"Meter");
		BSTR Angular=L"Degree";
		doc->m_DY_SRS->put_AngularUnit(Angular);

#endif	

	return ;
}

CDeuCoordinateSystem * CDeu2000Task::GetDeuCoordinateSystem(CString name)
{
	CDeuData *pData = m_pMainFrm->m_deuData; 

	CDeuCoordinateSystem * cs = NULL;
	//////////////////////////////////////////////////////////////////////////
	{
		VEC(CDeuCoordinateSystem*) &vecCS = pData->vecCS;
				
		VEC_IT(CDeuCoordinateSystem*) it = vecCS.begin();
		
		it =  FIND_NODE_IF(vecCS,name);

		if (it != vecCS.end())
		{
			cs = *it;
		}
	}
	
	//////////////////////////////////////////////////////////////////////////
	{
		VEC(CDeuCoordinateSystem*) &vecCS = pData->vecCustomCS;

		VEC_IT(CDeuCoordinateSystem*) it = vecCS.begin();

		it =  FIND_NODE_IF(vecCS,name);

		if (it != vecCS.end())
		{
			cs = *it;
		}
	}
		
		
	return cs;
}


IDeuEllipse * CDeu2000Task::GetEllipse(CString EllipName)
{
	CoInitialize(NULL);

	CDeuData *pData = m_pMainFrm->m_deuData; 
	VEC(IDeuEllipse*) &vecEllip = pData->vecEllipse;

	VEC(IDeuEllipse*)::iterator it;

	for (it = vecEllip.begin();it != vecEllip.end(); it++)
	{
		BSTR bstrEllipName;
		(*it)->get_Ellip_Name(&bstrEllipName);
		
		CString cstrEllipName(bstrEllipName);
		
		int ret = cstrEllipName.Compare(EllipName);

		if (ret == 0)
		{
			return (IDeuEllipse*)(*it);
		}

	}

	return NULL;
}

CNode * CDeu2000Task::GetEllipseNode(CString EllipName)
{
	CDeuData *pData = m_pMainFrm->m_deuData; 
	//pData->m_Ellips

	if (pData->m_PrjCS)
	{
		LIST_IT(CNode*) it = pData->m_PrjCS->_sub_nodes.begin();
		for ( ; it != pData->m_PrjCS->_sub_nodes.end() ;it ++ )
		{
			CNode * node = (*it);
			CString name = ( getListItem(node->_sub_nodes,0))->data;

			int ret = name.Compare(EllipName);

			if ( ret == 0)
			{
				return node;
			}

		}
	}

	if (pData->m_GdtCS)
	{
		LIST_IT(CNode*) it = pData->m_GdtCS->_sub_nodes.begin();
		for ( ; it != pData->m_GdtCS->_sub_nodes.end() ;it ++ )
		{
			CNode * node = (*it);
			CString name = ( getListItem(node->_sub_nodes,0))->data;

			int ret = name.Compare(EllipName);

			if ( ret == 0)
			{
				return node;
			}

		}
	}

	if (pData->m_CustomPrjCS)
	{
		LIST_IT(CNode*) it = pData->m_CustomPrjCS->_sub_nodes.begin();
		for ( ; it != pData->m_CustomPrjCS->_sub_nodes.end() ;it ++ )
		{
			CNode * node = (*it);
			CString name = ( getListItem(node->_sub_nodes,0))->data;

			int ret = name.Compare(EllipName);

			if ( ret == 0)
			{
				return node;
			}

		}
	}

	if (pData->m_CustomGdtCS)
	{
		LIST_IT(CNode*) it = pData->m_CustomGdtCS->_sub_nodes.begin();
		for ( ; it != pData->m_CustomGdtCS->_sub_nodes.end() ;it ++ )
		{
			CNode * node = (*it);
			CString name = ( getListItem(node->_sub_nodes,0))->data;

			int ret = name.Compare(EllipName);

			if ( ret == 0)
			{
				return node;
			}

		}
	}



	return NULL;

}

IDeuSpatialReference * CDeu2000Task::GetSRS(CDeuCoordinateSystem *cs )
{
	 

	CoInitialize(NULL);
	IDeuSpatialReference *pDeuSRS;
	HRESULT hr = CoCreateInstance(CLSID_DeuSpatialReference,   NULL,   CLSCTX_ALL,   IID_IDeuSpatialReference,   (void**)&pDeuSRS);   
	if   (SUCCEEDED(hr)   &&   (pDeuSRS   !=   NULL))   
	{   						
		//trans->ReleaseDispatch();  
	}

	//return pDeuSRS;
	
	if (cs->m_CSType.m_strData == PRJTYPE)
	{
		CDeuProjectCS * prj_cs = (CDeuProjectCS*)cs;
				
		CDeuData *pData = m_pMainFrm->m_deuData; 

		CDeuGeodeticCS * gdt_cs = pData->FindGeodetic(prj_cs->m_GeodeticPointor.m_strData);

		//////////////////////////////////////////////////////////////////////////
		CString CSProj=	prj_cs->m_Projection.m_strData;
		
		CString CSName	= gdt_cs->m_Name.m_strData;
		CString Datum	= gdt_cs->m_Datum.m_Name.m_strData;
		CString Ellipse = Datum;
		double SemiMajor= _tstof(gdt_cs->m_Datum.m_Ellipsoid.m_Semi_Major_Axis.m_Value.m_strData);
		double InvFlattening=_tstof(gdt_cs->m_Datum.m_Ellipsoid.m_InverseFlattening.m_strData);


		BSTR Proj=CSProj.AllocSysString();
		BSTR _bstr_Ellipse=Ellipse.AllocSysString();
		BSTR _bstr_Name=CSName.AllocSysString();
		BSTR _bstr_Datum=Datum.AllocSysString();

		pDeuSRS->put_GeogCS(&_bstr_Name,&_bstr_Name,&_bstr_Ellipse,&SemiMajor,&InvFlattening,NULL);
		pDeuSRS->put_Projection(CSProj.AllocSysString());
		pDeuSRS->put_LinearUnit(L"Meter");
		BSTR Angular=L"Degree";
		pDeuSRS->put_AngularUnit(Angular);
	}
	else if (cs->m_CSType.m_strData == GEODETICTYPE)
	{
		CDeuGeodeticCS * gdt_cs = (CDeuGeodeticCS*)cs ;
		CString CSName	= gdt_cs->m_Name.m_strData;
		CString Datum	= gdt_cs->m_Datum.m_Name.m_strData;
		CString Ellipse = Datum;
		double SemiMajor= _tstof(gdt_cs->m_Datum.m_Ellipsoid.m_Semi_Major_Axis.m_Value.m_strData);
		double InvFlattening=_tstof(gdt_cs->m_Datum.m_Ellipsoid.m_InverseFlattening.m_strData);


		//BSTR Proj=CSProj.AllocSysString();
		BSTR _bstr_Ellipse=Ellipse.AllocSysString();
		BSTR _bstr_Name=CSName.AllocSysString();
		BSTR _bstr_Datum=Datum.AllocSysString();

		pDeuSRS->put_GeogCS(&_bstr_Name,&_bstr_Name,&_bstr_Ellipse,&SemiMajor,&InvFlattening,NULL);
		//pDeuSRS->put_Projection(CSProj.AllocSysString());
		pDeuSRS->put_LinearUnit(L"Meter");
		BSTR Angular=L"Degree";
		pDeuSRS->put_AngularUnit(Angular);
	}

	return pDeuSRS;
}

IDeuUnits * CDeu2000Task::GetUnit(SHORT InUnitType,SHORT OutUnitType)
{
	CoInitialize(NULL);

	BSTR _in_unit_x;
	BSTR _in_unit_y;
	BSTR _in_unit_z;
	BSTR _out_unit_x;
	BSTR _out_unit_y;
	BSTR _out_unit_z;

	IDeuUnits* pDeuUnits;
	HRESULT hr = CoCreateInstance(CLSID_DeuUnits,   NULL,   CLSCTX_ALL,   IID_IDeuUnits,   (void**)&pDeuUnits);   
	if   (SUCCEEDED(hr)   &&   (pDeuUnits   !=   NULL))   
	{   						
		//trans->ReleaseDispatch();  
	}  

	switch(InUnitType)
	{
	case GEODETIC:
		_in_unit_x=CString("D").AllocSysString();
		_in_unit_y=CString("D").AllocSysString();
		_in_unit_z=CString("M").AllocSysString();

		_out_unit_x=CString("D").AllocSysString();
		_out_unit_y=CString("D").AllocSysString();
		_out_unit_z=CString("M").AllocSysString();
		break;
	case GEOCENTRIC:
		_in_unit_x=CString("M").AllocSysString();
		_in_unit_y=CString("M").AllocSysString();
		_in_unit_z=CString("M").AllocSysString();

		_out_unit_x=CString("M").AllocSysString();
		_out_unit_y=CString("M").AllocSysString();
		_out_unit_z=CString("M").AllocSysString();
		break;
	case PLANE: 
		_in_unit_x=CString("M").AllocSysString();
		_in_unit_y=CString("M").AllocSysString();
		_in_unit_z=CString("M").AllocSysString();

		_out_unit_x=CString("M").AllocSysString();
		_out_unit_y=CString("M").AllocSysString();
		_out_unit_z=CString("M").AllocSysString();
		break;	

	default:
		pDeuUnits->Release();
		return NULL;
		break;
	}


	pDeuUnits->put_Unit_x(_in_unit_x);
	pDeuUnits->put_Unit_y(_in_unit_y);
	pDeuUnits->put_Unit_z(_in_unit_z);

	pDeuUnits->put_Unit_desX(_out_unit_x);
	pDeuUnits->put_Unit_desY(_out_unit_y);
	pDeuUnits->put_Unit_desZ(_out_unit_z);
	
	return pDeuUnits;
}

IDeuCoordType * CDeu2000Task::GetCoordType(SHORT SrcType,SHORT DestType,SHORT CtrlPtType )
{
	CoInitialize(NULL);

	IDeuCoordType *pCoordType;
	HRESULT hr = CoCreateInstance(CLSID_DeuCoordType,   NULL,   CLSCTX_ALL,   IID_IDeuCoordType,   (void**)&pCoordType);   
	if   (SUCCEEDED(hr)   &&   (pCoordType   !=   NULL))   
	{   						
		//trans->ReleaseDispatch();  
	}   

	pCoordType->putref_CtrlPtCoordType( CtrlPtType );
	pCoordType->putref_CoordType( SrcType );
	pCoordType->putref_DestCoordType( DestType );

	return pCoordType;

}

ISevenParams *CDeu2000Task::GetSevenParam(double *_7param)
{
	CoInitialize(NULL);
	//ISevenParams
	ISevenParams *pSevenParam;
	HRESULT hr = CoCreateInstance(CLSID_SevenParams,   NULL,   CLSCTX_ALL,   IID_ISevenParams,   (void**)&pSevenParam);   
	if   (SUCCEEDED(hr)   &&   (pSevenParam   !=   NULL))   
	{   						
		//trans->ReleaseDispatch();  
	}   

	pSevenParam->putref_Dx(_7param[0]);
	pSevenParam->put_Dy(_7param[1]);
	pSevenParam->putref_Dz(_7param[2]);
	pSevenParam->putref_Rx(_7param[3]);
	pSevenParam->putref_Ry(_7param[4]);
	pSevenParam->putref_Rz(_7param[5]);
	pSevenParam->putref_Scale_M(_7param[6]);

	return pSevenParam;
}

SAFEARRAY *CDeu2000Task::GetSafeArrayParam(double * pa,int n)
{
	SAFEARRAYBOUND saBound[2];  // 1表示一维数组

	saBound[0].cElements = n;     // 20表示有20个元素

	saBound[0].lLbound = 0;         // 0表示从0开始


	SAFEARRAY *p;

	p = SafeArrayCreate(VT_R8,1,saBound);  //创建SafeArray

	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////

	double *pData;
	SafeArrayAccessData(p,(void **) &pData);

	for (int i = 0; i < n ; i++)
	{
		pData[i] = pa[i];
	}
	

	SafeArrayUnaccessData(p);

	return p;
}


//
//void CDeu2000Task::CheckData()
//{
//	BOOL IsOK=TRUE;
//	ASSERT(doc);
//
//	//检查坐标类型
//	IDeuCoordType* _coord_type=NULL;		
//	_coord_type=doc->m_DY_coord_type;
//	SHORT type,type_out,type_ctrl;
//	_coord_type->get_CoordType(&type);
//	_coord_type->get_DestCoordType(&type_out);
//	_coord_type->get_CtrlPtCoordType(&type_ctrl);
//
//	if (type<0 || type_out <0|| type_ctrl <0)
//	{
//		MessageBox(hwnd,L"输入坐标不正确！转换中止，请检查参数！",L"错误",MB_OK | MB_ICONWARNING);
//		IsOK=FALSE;
//	}
//	//检查椭球，目标椭球是否存在、
//
//	BSTR ellip_name;
//	doc->m_DY_ellipse->get_Ellip_Name(&ellip_name);
//	if(ellip_name==NULL)
//	{
//		MessageBox(hwnd,L"输入源椭球不正确！转换中止，请检查参数！",L"错误",MB_OK | MB_ICONWARNING);
//		IsOK=FALSE;
//	}
//
//	BSTR des_ellip_name;
//	doc->m_DY_ellipse->get_Ellip_Name(&des_ellip_name);
//	if(des_ellip_name==NULL)
//	{
//		MessageBox(hwnd,L"输入目标椭球不正确！转换中止，请检查参数！",L"错误",MB_OK | MB_ICONWARNING);
//		IsOK=FALSE;
//	}
//
//
//	//检查单位
//	IDeuUnits* _unit= doc->m_DY_units;
//	BSTR ux,uy,uz,des_ux,des_uy,des_uz;	
//	_unit->get_Unit_x(&ux);
//	_unit->get_Unit_x(&uy);
//	_unit->get_Unit_x(&uz);
//	_unit->get_Unit_desX(&des_ux);
//	_unit->get_Unit_desY(&des_uy);
//	_unit->get_Unit_desZ(&des_uz);
//
//	if(ux==NULL || uy ==NULL || uz==NULL|| des_ux==NULL|| des_uy==NULL||des_uz==NULL)
//	{
//		MessageBox(hwnd,L"输入单位不正确！转换中止，请检查参数！",L"错误",MB_OK | MB_ICONWARNING);
//		IsOK=FALSE;
//	}
//
//	//检查7参数
//	ISevenParams* _SevenParam=doc->m_seven_param;
//	double dx,dy,dz,rx,ry,rz,m;
//	_SevenParam->get_Dx(&dx);
//
//	if (0)
//	{
//		MessageBox(hwnd,L"输入7参数不正确！转换中止，请检查参数！",L"错误",MB_OK | MB_ICONWARNING);
//		IsOK=FALSE;
//	}
//
//	return ;
//}
int CDeu2000Task::GetParaCount(SHORT aMode)
{
	int np = 0;
	switch(aMode)
	{
	case  MODEL_D3P7 :
		np = 9;
		break;

	case MODEL_D2P4	:
		np = 4;
		break;

	case MODEL_BURSA:
		np = 7;
		break;

	case MODEL_D2P7:
		np = 9;
		break;

	default:
		np = -1;
		break;
	}

	return np;

}

void CDeu2000Task::Task_Calculate7Param(SHORT aMode,
										SHORT CtrlPtCoordType,
										SHORT UnitType,
										IDeuEllipse *pSrcEllip,
										IDeuEllipse *pDesEllip,
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
										ULONG  *np)
{
	//
	CDeuData *pdeuData = m_pMainFrm->m_deuData;

	//IDeuEllipse *pSrcEllip = GetEllipse(SrcEllip);
	//IDeuEllipse *pDesEllip = GetEllipse(DestEllip);
	
	if (pSrcEllip == NULL || pDesEllip == NULL)
	{
		MessageBox(m_pMainFrm->m_hWnd,"输入椭球参数不正确！","错误",MB_OK | MB_ICONWARNING);
		return ;
	}

	IDeuCoordType *pCoordType = GetCoordType(CtrlPtCoordType,CtrlPtCoordType,CtrlPtCoordType);
	
	IDeuUnits *pUnit = GetUnit(UnitType,UnitType);

	if (pUnit == NULL || pCoordType == NULL)
	{
		MessageBox(m_pMainFrm->m_hWnd,"输入坐标参数不正确！","错误",MB_OK | MB_ICONWARNING);
		return ;
	}

	//ISevenParams *pSevenParam = GetSevenParam(_param);


	//if(CheckData(pdeuData,DEUMAINFRM.m_hWnd)==FALSE)
	//{
	//	//MessageBox(mainframe->m_hWnd,L"输入参数不正确！转换中止，请检查参数！",L"错误",MB_OK | MB_ICONWARNING);
	//	return;
	//}

	//CDYTrans trans;
	//CoInitialize(NULL);   

	IDeuTrans* trans = NULL;   

	HRESULT hr = CoCreateInstance(CLSID_DeuTrans,   NULL,   CLSCTX_ALL,   IID_IDeuTrans,   (void**)&trans);   
	if   (SUCCEEDED(hr)   &&   (trans   !=   NULL))   
	{   


		//IDeuCoordType* _coord_type=NULL;		
		//_coord_type=pdeuData->m_Deu_coord_type;


		////并设置转换前后，坐标类型为空间直角
		//SHORT ctrl_type;
		//_coord_type->get_CtrlPtCoordType(&ctrl_type);
		//_coord_type->putref_CoordType(ctrl_type);
		//_coord_type->putref_DestCoordType(ctrl_type);

		trans->putref_DeuCoordType(pCoordType);
		trans->putref_DeuEllipse(pSrcEllip);		
		trans->putref_DeuDestEllipse(pDesEllip);

		trans->putref_DeuUnits(pUnit);
		//trans->putref_SevenParams(pSevenParam);
		trans->put_TransModel(aMode);

		//坐标单位转为弧度/米，然后求得该模型下的参数

		//double* _7param=new double[7];
		//输入第一组控制点坐标类型，第二组控制点坐标类型，在空间直角下得到7参数

		trans->Calculate7Param(iCount,x,y,z,x2,y2,z2,_param,np);
		//doc->_7param=_7param;

		//new 7param



		double* des_x=new double[iCount];
		double* des_y=new double[iCount];
		double* des_z=new double[iCount];

		//7参数和第一组控制点坐标类型，得到转换后的第二组坐标, 转换后坐标类型与控制点坐标类型相同
		trans->CoordTransfArray(_param,iCount,x,y,z,des_x,des_y,des_z);

		//double* res_x=new double[iCount];
		//double* res_y=new double[iCount];
		//double* res_z=new double[iCount];
		//double* _residual=new double[iCount];



		//原始单位下的转换后坐标
		double* des_x_ori_unit=new double[iCount];
		double* des_y_ori_unit=new double[iCount];
		double* des_z_ori_unit=new double[iCount];


		

		trans->CalculateResidual(iCount,x2,y2,z2,des_x,des_y,des_z,residual_x,residual_y,residual_z,residual);


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

	}   

	//CoUninitialize();   

	return ;
}


void CDeu2000Task::Task_RasterCalculate7Param(SHORT aMode,
										SHORT CtrlPtCoordType,
										SHORT UnitType,
										IDeuEllipse *pSrcEllip,
										IDeuEllipse *pDesEllip,
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
										ULONG*	npara
										)
{
	//
	CDeuData *pdeuData = m_pMainFrm->m_deuData;

	if (pSrcEllip == NULL || pDesEllip == NULL)
	{
		MessageBox(m_pMainFrm->m_hWnd,"输入椭球参数不正确！","错误",MB_OK | MB_ICONWARNING);
		return ;
	}

	IDeuCoordType *pCoordType = GetCoordType(CtrlPtCoordType,CtrlPtCoordType,CtrlPtCoordType);

	IDeuUnits *pUnit = GetUnit(UnitType,UnitType);

	if (pUnit == NULL || pCoordType == NULL)
	{
		MessageBox(m_pMainFrm->m_hWnd,"输入坐标参数不正确！","错误",MB_OK | MB_ICONWARNING);
		return ;
	}

	


	//if(CheckData(pdeuData,DEUMAINFRM.m_hWnd)==FALSE)
	//{
	//	//MessageBox(mainframe->m_hWnd,L"输入参数不正确！转换中止，请检查参数！",L"错误",MB_OK | MB_ICONWARNING);
	//	return;
	//}

	//CDYTrans trans;
	//CoInitialize(NULL);   

	IDeuRasterTrans* trans = NULL;   

	HRESULT hr = CoCreateInstance(CLSID_DeuRasterTrans,   NULL,   CLSCTX_ALL,   IID_IDeuRasterTrans,   (void**)&trans);   
	if   (SUCCEEDED(hr)   &&   (trans   !=   NULL))   
	{   


		//IDeuCoordType* _coord_type=NULL;		
		//_coord_type=pdeuData->m_Deu_coord_type;


		////并设置转换前后，坐标类型为空间直角
		//SHORT ctrl_type;
		//_coord_type->get_CtrlPtCoordType(&ctrl_type);
		//_coord_type->putref_CoordType(ctrl_type);
		//_coord_type->putref_DestCoordType(ctrl_type);

		trans->putref_DeuCoordType(pCoordType);
		trans->putref_DeuEllipse(pSrcEllip);		
		trans->putref_DeuDestEllipse(pDesEllip);

		trans->putref_DeuUnits(pUnit);
		
		trans->put_TransModel(aMode);

		//坐标单位转为弧度/米，然后求得该模型下的参数

		//double* _7param=new double[7];
		//输入第一组控制点坐标类型，第二组控制点坐标类型，在空间直角下得到7参数
		trans->CalculateParam(iCount,x,y,z,x2,y2,z2,_param,npara);

		trans->CalculateParam(iCount,x2,y2,z2,x,y,z,_inv_param,npara);
		
		//doc->_7param=_7param;

		//new 7param

		double* des_x=new double[iCount];
		double* des_y=new double[iCount];
		double* des_z=new double[iCount];

		//7参数和第一组控制点坐标类型，得到转换后的第二组坐标, 转换后坐标类型与控制点坐标类型相同
		trans->CoordTransfArray(_param,iCount,x,y,z,des_x,des_y,des_z);

		//double* res_x=new double[iCount];
		//double* res_y=new double[iCount];
		//double* res_z=new double[iCount];
		//double* _residual=new double[iCount];



		//原始单位下的转换后坐标
		double* des_x_ori_unit=new double[iCount];
		double* des_y_ori_unit=new double[iCount];
		double* des_z_ori_unit=new double[iCount];

		trans->CalculateResidual(iCount,x2,y2,z2,des_x,des_y,des_z,residual_x,residual_y,residual_z,residual);

		delete[] des_x;
		delete[] des_y;
		delete[] des_z;

		delete[] des_x_ori_unit;
		delete[] des_y_ori_unit;
		delete[] des_z_ori_unit;
		//trans->ReleaseDispatch();  

	}   

	//CoUninitialize();   

	return ;
}



BOOL CDeu2000Task::Task_TransForm(CDeuTask * pdeuTask)
{


	//////////////////////////////////////////////////////////////////////////
	//
	//CMainFrame &pMainFrm = DEUMAINFRM;
	//CDeuData *pdeuData = DEUMAINFRM.m_deuData;
	
	//if(CCGSTask::CheckData(doc,mainframe->m_hWnd)==FALSE)
	//{
	//	MessageBox(mainframe->m_hWnd,L"输入参数不正确！转换中止，请检查参数！",L"错误",MB_OK | MB_ICONWARNING);
	//	return;
	//}

	if (g_ThreadFinished == FALSE )
	{
		return FALSE;
	}

	//为每一个转换开启一个线程

#if 1
	HANDLE Thread;
	DWORD dwThreadId;

	Thread=::CreateThread
		(NULL,0,ThreadFunc,pdeuTask,0,&dwThreadId);
	//cout<<"The new thread ID is :"<<dwThreadId<<endl;
	//::WaitForSingleObject(Thread,INFINITE);
	//::CloseHandle(Thread);
#endif

	return TRUE;
}


BOOL CDeu2000Task::Task_RasterTransFormDEM(CDeuTask * pdeuTask)
{

	if (g_ThreadFinished == FALSE )
	{
		return FALSE;
	}
	//为每一个转换开启一个线程

#if 1
	HANDLE Thread;
	DWORD dwThreadId;

	Thread=::CreateThread
		(NULL,0,ThreadFunc_RasterDEM,pdeuTask,0,&dwThreadId);
	//cout<<"The new thread ID is :"<<dwThreadId<<endl;
	//::WaitForSingleObject(Thread,INFINITE);
	//::CloseHandle(Thread);
#endif

	return TRUE;
}

BOOL CDeu2000Task::Task_RasterTransForm(CDeuTask * pdeuTask)
{

	if (g_ThreadFinished == FALSE )
	{
		return FALSE;
	}
	//为每一个转换开启一个线程

#if 1
	HANDLE Thread;
	DWORD dwThreadId;

	Thread=::CreateThread
		(NULL,0,ThreadFunc_Raster,pdeuTask,0,&dwThreadId);
	//cout<<"The new thread ID is :"<<dwThreadId<<endl;
	//::WaitForSingleObject(Thread,INFINITE);
	//::CloseHandle(Thread);
#endif

	return TRUE;
}



DWORD WINAPI ThreadFunc(HANDLE Thread)
{

	g_ThreadFinished = FALSE ;
	//CDeuData *pdeuData = DEUMAINFRM.m_deuData;

	CDeuTask *pdeuTask = ( CDeuTask* ) Thread;
	
	//////////////////////////////////////////////////////////////////////////
	CDeu2000Task &_Task2000 = *g_Task2000;

	CMainFrame & MainFrm = _Task2000.GetMainFrm();
	MainFrm.m_Msg->name = L"开始转换:";
	MainFrm.m_Msg->SendMsg();

	double StartTick = ::GetTickCount(),EndTick(0);

	//////////////////////////////////////////////////////////////////////////

	IDeuEllipse *pSrcEllip = _Task2000.GetEllipse(pdeuTask->SrcEllip);
	IDeuEllipse *pDesEllip = _Task2000.GetEllipse(pdeuTask->DestEllip);

	if (pSrcEllip == NULL || pDesEllip == NULL)
	{
		MessageBox(MainFrm.m_hWnd,"输入椭球参数不正确！转换中止，请检查参数！","错误",MB_OK | MB_ICONWARNING);
		return -1;
	}

	IDeuCoordType *pCoordType = _Task2000.GetCoordType(pdeuTask->InCoordType,pdeuTask->OutCoordType,0);

	IDeuUnits *pUnit = _Task2000.GetUnit(pdeuTask->InCoordType,pdeuTask->OutCoordType);

	if (pUnit == NULL || pCoordType == NULL)
	{
		MessageBox(MainFrm.m_hWnd,"输入坐标参数不正确！转换中止，请检查参数！","错误",MB_OK | MB_ICONWARNING);
		return -1;
	}

	//ISevenParams *pSevenParam = _Task2000.GetSevenParam(pdeuTask->_7param);
	double * pParam = pdeuTask->Param;

	//CNode *pEllipseNode = _Task2000.GetEllipseNode(pdeuTask->SrcEllip);
	CDeuCoordinateSystem *cs = _Task2000.GetDeuCoordinateSystem(pdeuTask->SrcEllip);

	IDeuSpatialReference *pSRS = _Task2000.GetSRS(cs);

	//IDeuConnPool *pConnPool = _Task2000.GetConnPool();

	LONGLONG hWnd = pdeuTask->hWnd;

	 
	//////////////////////////////////////////////////////////////////////////

	//CDYTrans trans;
	//CoInitialize(NULL);   


	IDeuTrans* trans = NULL;   

	HRESULT hr = CoCreateInstance(CLSID_DeuTrans,   NULL,   CLSCTX_ALL,   IID_IDeuTrans,   (void**)&trans);   
	if   (SUCCEEDED(hr)   &&   (trans   !=   NULL))   
	{   
		BSTR _src;
		BSTR _des;
		BSTR _in_driver;
		BSTR _out_driver;

		_in_driver = pdeuTask->Driver.AllocSysString();
		_out_driver = pdeuTask->out_Driver.AllocSysString();


		/*	QUERYINTERFACE(doc->m_DY_coord_type,)*/

		trans->putref_DeuCoordType(pCoordType);
		trans->putref_DeuEllipse(pSrcEllip);
		trans->putref_DeuDestEllipse(pDesEllip);

		trans->putref_DeuUnits(pUnit);
		trans->putref_Param(pParam);
		trans->putref_DeuSRS(pSRS);
		trans->putref_ConnPool(g_ConnPool);

		trans->RegisterWnd((LONGLONG)hWnd);
		trans->put_TransModel(pdeuTask->iModel);


#if 0

		LONG ConnId;
		CString SrcConn = L"OCI:df/o123456@abc200";
		doc->m_ConnPool->Connect(SrcConn.AllocSysString(),&ConnId);

		LONG DesConnId;
		CString DesConn = L"OCI:df/o123456@abc201";
		doc->m_ConnPool->Connect(DesConn.AllocSysString(),&DesConnId);


		std::vector<CString> vec_FileName;
		std::vector<CString> vec_FileName_Out;

		vec_FileName.push_back(L"BEIJINGSHI_GCA");
		vec_FileName.push_back(L"BEIJINGSHI_GCP");
		vec_FileName.push_back(L"BEIJINGSHI_GCH");

		//
		CDeuTask* deuTask   =   new CDeuTask;
		deuTask->TaskName   =   "Task001";
		deuTask->TaskStatus =   BEFOREBEGIN;
		deuTask->TableList.assign(vec_FileName.begin(),vec_FileName.end());

	
		//OCI:df/123@abc001
#else


	std::vector<CString> vec_FileName ;
	std::vector<CString> vec_FileName_Out ;


	if (pdeuTask->TaskStatus == BEFOREBEGIN)
	{
		vec_FileName = pdeuTask->TableList;
		vec_FileName_Out = pdeuTask->TableList;
	}
	else if(pdeuTask->TaskStatus == RUNNING)
	{
		std::vector<CString>::iterator it = pdeuTask->TableList.begin();
		for ( ; it != pdeuTask->TableList.end() ; it++)
		{
			int ret = pdeuTask->CurTable.Compare(*it);

			if (ret == 0)
			{//从这里开始断点续转
				vec_FileName.assign(it,pdeuTask->TableList.end());
				vec_FileName_Out = vec_FileName;
				break;
			}
		}
		

	}
	else
	{//当任务状态不可识别的时候，默认为重新转换
		vec_FileName = pdeuTask->TableList;
		vec_FileName_Out = pdeuTask->TableList;
	}
		BSTR m_in_Path = pdeuTask->PathName.AllocSysString();
		BSTR m_out_Path = pdeuTask->out_PathName.AllocSysString();
		CString strDriver = pdeuTask->Driver; 
		//CDeuTask *pdeuTask;
		INT ConnId ;
		INT DesConnId;
		
		 
#endif

	//如果没有任何表需要转换，则提示转换列表为空
	if ( vec_FileName.size() <= 0)
	{
		MessageBox(MainFrm.m_hWnd,"转换列表为空！","提示",MB_OK | MB_ICONINFORMATION);

		//发送结束消息给 hWnd，通知修改Running为FALSE
		::SendMessage((HWND)hWnd,WM_TASK_FINISH,NULL,NULL);
		g_ThreadFinished = TRUE ;
		return 0;
	}


		for(int i=0;i<vec_FileName.size();i++)
		{
			/************************wang*****************************/
			CString  str;
			str.Format("正在转换第%d个文件.",i);
			MainFrm.m_Msg->name=str;
			MainFrm.m_Msg->SendMsg();
			/************************wang*****************************/
			if (strDriver!=L"OCI")
			{			
				_src=vec_FileName[i].AllocSysString();

				_des=vec_FileName[i].AllocSysString();
				
				//////////////////////////////////////////////////////////////////////////
				//写转换任务描述文件
				pdeuTask->TaskStatus = RUNNING;	
				pdeuTask->CurTable = vec_FileName[i]; 	
				g_Task2000->UpdateTaskList(g_lisTask);
				//////////////////////////////////////////////////////////////////////////

				trans->CoordTransf2(_src,m_in_Path,_in_driver,_des,m_out_Path,_out_driver);
				//CoordTransf(SrcTab,SrcPath,InDriver,DesTab,DesPath,OutDriver);
				//trans->CoordTransf(_src,_in_driver,_des,_out_driver);
			}
			else
			{
				_src=vec_FileName[i].AllocSysString();
				_des=vec_FileName[i].AllocSysString();

				//trans->CoordTransf(_src,_in_driver,_des,_out_driver);

				CDeu2000Task &_Task2000 = *g_Task2000;

				//////////////////////////////////////////////////////////////////////////
				//写转换任务描述文件
				pdeuTask->TaskStatus = RUNNING;	
				pdeuTask->CurTable = vec_FileName[i]; 	
				g_Task2000->UpdateTaskList(g_lisTask);
				//////////////////////////////////////////////////////////////////////////

				trans->CoordTransfDB(_src,m_in_Path,_in_driver,_des,m_out_Path,_out_driver);
				//trans->TransfUsePool(_src,ConnId,_des,DesConnId);
			}
		}

		pdeuTask->TaskStatus = FINISHED;
		//trans->ReleaseDispatch();  
	}   

	//CoUninitialize();   

	MainFrm.m_Msg->name=L"结束转换:";	
	MainFrm.m_Msg->SendMsg();


	EndTick = GetTickCount();

	double Result = (EndTick - StartTick)*0.001;

	CString strMsg;
	strMsg.Format(_T("%s%.2lf%s"),L"用时:",Result,L"秒");
	MainFrm.m_Msg->name = strMsg;	
	MainFrm.m_Msg->SendMsg();


	//////////////////////////////////////////////////////////////////////////
	//写转换任务描述文件
	pdeuTask->TaskStatus = FINISHED;		
	g_Task2000->UpdateTaskList(g_lisTask);
	//////////////////////////////////////////////////////////////////////////


	//发送结束消息给 hWnd，通知修改Running为FALSE
	::SendMessage((HWND)hWnd,WM_TASK_FINISH,NULL,NULL);

	MessageBox(MainFrm.m_hWnd, "转换完毕！", "提示",MB_OK | MB_ICONINFORMATION);

	g_ThreadFinished = TRUE ;
	return 0;
}

//ThreadFunc_RasterDEM
DWORD WINAPI ThreadFunc_RasterDEM(HANDLE Thread)
{
	g_ThreadFinished = FALSE ;
#if 1
	CDeuTask *pdeuTask = ( CDeuTask* ) Thread;

	//////////////////////////////////////////////////////////////////////////
	CDeu2000Task &_Task2000 = *g_Task2000;

	CMainFrame & MainFrm = _Task2000.GetMainFrm();
	MainFrm.m_Msg->name = "开始转换:";
	MainFrm.m_Msg->SendMsg();

	double StartTick = ::GetTickCount(),EndTick(0);

	IDeuEllipse *pSrcEllip = _Task2000.GetEllipse(pdeuTask->SrcEllip);
	IDeuEllipse *pDesEllip = _Task2000.GetEllipse(pdeuTask->DestEllip);

	if (pSrcEllip == NULL || pDesEllip == NULL)
	{
		MessageBox(MainFrm.m_hWnd, "输入椭球参数不正确！转换中止，请检查参数！", "错误",MB_OK | MB_ICONWARNING);
		return -1;
	}

	IDeuCoordType *pCoordType = _Task2000.GetCoordType(pdeuTask->InCoordType,pdeuTask->OutCoordType,0);

	IDeuUnits *pUnit = _Task2000.GetUnit(pdeuTask->InCoordType,pdeuTask->OutCoordType);

	if (pUnit == NULL || pCoordType == NULL)
	{
		MessageBox(MainFrm.m_hWnd, "输入坐标参数不正确！转换中止，请检查参数！", "错误",MB_OK | MB_ICONWARNING);
		return -1;
	}

	//ISevenParams *pSevenParam = _Task2000.GetSevenParam(pdeuTask->_7param);
	double * pParam = pdeuTask->Param;

	//IDeuConnPool *pConnPool = _Task2000.GetConnPool();

	LONGLONG hWnd = pdeuTask->hWnd;

	//////////////////////////////////////////////////////////////////////////

	//CDYTrans trans;
	//CoInitialize(NULL);   


	IDeuRasterTrans* trans = NULL;   

	HRESULT hr = CoCreateInstance(CLSID_DeuRasterTrans,   NULL,   CLSCTX_ALL,   IID_IDeuRasterTrans,   (void**)&trans);   
	if   (SUCCEEDED(hr)   &&   (trans   !=   NULL))   
	{   
		BSTR _src;
		BSTR _des;
		BSTR _in_driver;
		BSTR _out_driver;

		_in_driver=pdeuTask->Driver.AllocSysString();
		_out_driver=pdeuTask->out_Driver.AllocSysString();



		/*	QUERYINTERFACE(doc->m_DY_coord_type,)*/

		trans->putref_DeuCoordType(pCoordType);
		trans->putref_DeuEllipse(pSrcEllip);
		trans->putref_DeuDestEllipse(pDesEllip);

		trans->putref_DeuUnits(pUnit);
		//trans->putref_SevenParams(pSevenParam);
		trans->putref_Param(pParam);
		//trans->putref_DeuSRS(doc->m_DY_SRS);


		trans->RegisterWnd((LONGLONG)hWnd);  

#if 0
		std::vector<CString> vec_FileName;
		std::vector<CString> vec_FileName_Out;

		vec_FileName.push_back(L"D:\\daifeng\\res\\data\\影像测试数据\\spot.tif");
		vec_FileName_Out.push_back(L"d:\\MyTiffOut.tif");

		//
		CDeuTask* deuTask   =   new CDeuTask;
		deuTask->TaskName   =   "Task001";
		deuTask->TaskStatus =   BEFOREBEGIN;
		deuTask->TableList.assign(vec_FileName.begin(),vec_FileName.end());

#endif

		std::vector<CString> vec_FileName ;
		std::vector<CString> vec_FileName_Out ;


		if (pdeuTask->TaskStatus == BEFOREBEGIN)
		{
			vec_FileName = pdeuTask->TableList;
			vec_FileName_Out = pdeuTask->TableList;
		}
		else if(pdeuTask->TaskStatus == RUNNING)
		{
			std::vector<CString>::iterator it = pdeuTask->TableList.begin();
			for ( ; it != pdeuTask->TableList.end() ; it++)
			{
				int ret = pdeuTask->CurTable.Compare(*it);

				if (ret == 0)
				{//从这里开始断点续转
					vec_FileName.assign(it,pdeuTask->TableList.end());
					vec_FileName_Out = vec_FileName;
					break;
				}
			}


		}
		else
		{//当任务状态不可识别的时候，默认为重新转换
			vec_FileName = pdeuTask->TableList;
			vec_FileName_Out = pdeuTask->TableList;
		}


		//如果没有任何表需要转换，则提示转换列表为空
		if ( vec_FileName.size() <= 0)
		{
			MessageBox(MainFrm.m_hWnd, "转换列表为空！", "提示",MB_OK | MB_ICONINFORMATION);

			//发送结束消息给 hWnd，通知修改Running为FALSE
			::SendMessage((HWND)hWnd,WM_TASK_FINISH,NULL,NULL);
			g_ThreadFinished = TRUE ;
			return 0;
		}

		BSTR m_in_Path = pdeuTask->PathName.AllocSysString();
		BSTR m_out_Path = pdeuTask->out_PathName.AllocSysString();
		BSTR bstrDriver = pdeuTask->Driver.AllocSysString(); 
		BSTR bstrDriverOut = pdeuTask->out_Driver.AllocSysString(); 



		for(int i=0;i<vec_FileName.size();i++)
		{
			//CString cstr_src;
			//cstr_src = m_in_Path + CString(L"\\") + vec_FileName[i] + CString(L".tif");

			//CString cstr_des;
			//cstr_des = m_out_Path + CString(L"\\") + vec_FileName[i] + CString(L".tif");
			/************************wang*****************************/
			CString  str;
			str.Format("正在转换第%d个文件.",i);
			MainFrm.m_Msg->name=str;
			MainFrm.m_Msg->SendMsg();
			/************************wang*****************************/
			_src= vec_FileName[i].AllocSysString();

			_des= vec_FileName[i].AllocSysString();


			//////////////////////////////////////////////////////////////////////////
			//写转换任务描述文件
			pdeuTask->TaskStatus = RUNNING;	
			pdeuTask->CurTable = vec_FileName[i]; 	
			g_Task2000->UpdateTaskList(g_lisTask);
			//////////////////////////////////////////////////////////////////////////

			trans->CoordTransfDEM(_src,m_in_Path,bstrDriver,_des,m_out_Path,bstrDriverOut);

		}

		pdeuTask->TaskStatus = FINISHED;
		//trans->ReleaseDispatch();  
	}   

	//CoUninitialize();   

	MainFrm.m_Msg->name = "结束转换:";	
	MainFrm.m_Msg->SendMsg();

	EndTick = GetTickCount();

	double Result = (EndTick - StartTick)*0.001;

	CString strMsg;
	strMsg.Format(_T("%s%.2lf%s"), "用时:",Result, "秒");
	MainFrm.m_Msg->name = strMsg;	
	MainFrm.m_Msg->SendMsg();

	//////////////////////////////////////////////////////////////////////////
	//写转换任务描述文件
	pdeuTask->TaskStatus = FINISHED;		
	g_Task2000->UpdateTaskList(g_lisTask);
	//////////////////////////////////////////////////////////////////////////


	//发送结束消息给 hWnd，通知修改Running为FALSE
	SendMessage((HWND)hWnd,WM_TASK_FINISH,NULL,NULL);

	MessageBox(MainFrm.m_hWnd,"转换完毕！", "提示",MB_OK | MB_ICONINFORMATION);
#endif

	g_ThreadFinished = TRUE ;

	return 0;
};

DWORD WINAPI ThreadFunc_Raster(HANDLE Thread)
{
	g_ThreadFinished = FALSE ;
#if 1
	CDeuTask *pdeuTask = ( CDeuTask* ) Thread;

	//////////////////////////////////////////////////////////////////////////
	CDeu2000Task &_Task2000 = *g_Task2000;

	CMainFrame & MainFrm = _Task2000.GetMainFrm();
	MainFrm.m_Msg->name =  "开始转换:";
	MainFrm.m_Msg->SendMsg();

	double StartTick = ::GetTickCount(),EndTick(0);

	IDeuEllipse *pSrcEllip = _Task2000.GetEllipse(pdeuTask->SrcEllip);
	IDeuEllipse *pDesEllip = _Task2000.GetEllipse(pdeuTask->DestEllip);

	if (pSrcEllip == NULL || pDesEllip == NULL)
	{
		MessageBox(MainFrm.m_hWnd, "输入椭球参数不正确！转换中止，请检查参数！", "错误",MB_OK | MB_ICONWARNING);
		return -1;
	}

	IDeuCoordType *pCoordType = _Task2000.GetCoordType(pdeuTask->InCoordType,pdeuTask->OutCoordType,0);

	IDeuUnits *pUnit = _Task2000.GetUnit(pdeuTask->InCoordType,pdeuTask->OutCoordType);

	if (pUnit == NULL || pCoordType == NULL)
	{
		MessageBox(MainFrm.m_hWnd, "输入坐标参数不正确！转换中止，请检查参数！", "错误",MB_OK | MB_ICONWARNING);
		return -1;
	}

	//ISevenParams *pSevenParam = _Task2000.GetSevenParam(pdeuTask->_7param);

	//SAFEARRAY * pPa = _Task2000.GetSafeArrayParam(pdeuTask->Param,pdeuTask->nPara);

	//SAFEARRAY * pInvPa = _Task2000.GetSafeArrayParam(pdeuTask->InvParam,pdeuTask->nPara);

	double * pPa = pdeuTask->Param;
	double * pInvPa = pdeuTask->InvParam;

	//IDeuConnPool *pConnPool = _Task2000.GetConnPool();

	LONGLONG hWnd = pdeuTask->hWnd;

	//////////////////////////////////////////////////////////////////////////

	//CDYTrans trans;
	//CoInitialize(NULL);   


	IDeuRasterTrans* trans = NULL;   

	HRESULT hr = CoCreateInstance(CLSID_DeuRasterTrans,   NULL,   CLSCTX_ALL,   IID_IDeuRasterTrans,   (void**)&trans);   
	if   (SUCCEEDED(hr)   &&   (trans   !=   NULL))   
	{   
		BSTR _src;
		BSTR _des;
		BSTR _in_driver;
		BSTR _out_driver;

		_in_driver=pdeuTask->Driver.AllocSysString();
		_out_driver=pdeuTask->out_Driver.AllocSysString();



		/*	QUERYINTERFACE(doc->m_DY_coord_type,)*/

		trans->putref_DeuCoordType(pCoordType);
		trans->putref_DeuEllipse(pSrcEllip);
		trans->putref_DeuDestEllipse(pDesEllip);

		trans->putref_DeuUnits(pUnit);
		trans->putref_Param(pPa);
		trans->putref_Param(pInvPa);
		//trans->putref_SevenParams(pSevenParam);
		//trans->putref_DeuSRS(doc->m_DY_SRS);
		

		trans->RegisterWnd((LONGLONG)hWnd);  

#if 0
		std::vector<CString> vec_FileName;
		std::vector<CString> vec_FileName_Out;

		vec_FileName.push_back(L"D:\\daifeng\\res\\data\\影像测试数据\\spot.tif");
		vec_FileName_Out.push_back(L"d:\\MyTiffOut.tif");

		//
		CDeuTask* deuTask   =   new CDeuTask;
		deuTask->TaskName   =   "Task001";
		deuTask->TaskStatus =   BEFOREBEGIN;
		deuTask->TableList.assign(vec_FileName.begin(),vec_FileName.end());

#endif

		std::vector<CString> vec_FileName ;
		std::vector<CString> vec_FileName_Out ;


		if (pdeuTask->TaskStatus == BEFOREBEGIN)
		{
			vec_FileName = pdeuTask->TableList;
			vec_FileName_Out = pdeuTask->TableList;
		}
		else if(pdeuTask->TaskStatus == RUNNING)
		{
			std::vector<CString>::iterator it = pdeuTask->TableList.begin();
			for ( ; it != pdeuTask->TableList.end() ; it++)
			{
				int ret = pdeuTask->CurTable.Compare(*it);

				if (ret == 0)
				{//从这里开始断点续转
					vec_FileName.assign(it,pdeuTask->TableList.end());
					vec_FileName_Out = vec_FileName;
					break;
				}
			}
		}
		else
		{//当任务状态不可识别的时候，默认为重新转换
			vec_FileName = pdeuTask->TableList;
			vec_FileName_Out = pdeuTask->TableList;
		}


		//如果没有任何表需要转换，则提示转换列表为空
		if ( vec_FileName.size() <= 0)
		{
			MessageBox(MainFrm.m_hWnd, "转换列表为空！", "提示",MB_OK | MB_ICONINFORMATION);

			//发送结束消息给 hWnd，通知修改Running为FALSE
			::SendMessage((HWND)hWnd,WM_TASK_FINISH,NULL,NULL);
			g_ThreadFinished = TRUE ;
			return 0;
		}

		BSTR m_in_Path = pdeuTask->PathName.AllocSysString();
		BSTR m_out_Path = pdeuTask->out_PathName.AllocSysString();
		BSTR bstrDriver = pdeuTask->Driver.AllocSysString(); 
		BSTR bstrDriverOut = pdeuTask->out_Driver.AllocSysString(); 



		for(int i=0;i<vec_FileName.size();i++)
		{
			//CString cstr_src;
			//cstr_src = m_in_Path + CString(L"\\") + vec_FileName[i] + CString(L".tif");

			//CString cstr_des;
			//cstr_des = m_out_Path + CString(L"\\") + vec_FileName[i] + CString(L".tif");
			/************************wang*****************************/
			CString  str;
			str.Format("正在转换第%d个文件.",i);
			MainFrm.m_Msg->name=str;
			MainFrm.m_Msg->SendMsg();
			/************************wang*****************************/
			_src= vec_FileName[i].AllocSysString();

			_des= vec_FileName[i].AllocSysString();


			//////////////////////////////////////////////////////////////////////////
			//写转换任务描述文件
			pdeuTask->TaskStatus = RUNNING;	
			pdeuTask->CurTable = vec_FileName[i]; 	
			g_Task2000->UpdateTaskList(g_lisTask);
			//////////////////////////////////////////////////////////////////////////

			trans->CoordTransf2(_src,m_in_Path,bstrDriver,_des,m_out_Path,bstrDriverOut);

		}

		pdeuTask->TaskStatus = FINISHED;
		//trans->ReleaseDispatch();  
	}   

	//CoUninitialize();   

	MainFrm.m_Msg->name="结束转换:";	
	MainFrm.m_Msg->SendMsg();

	EndTick = GetTickCount();

	double Result = (EndTick - StartTick)*0.001;

	CString strMsg;
	strMsg.Format(_T("%s%.2lf%s"), "用时:",Result, "秒");
	MainFrm.m_Msg->name = strMsg;	
	MainFrm.m_Msg->SendMsg();

	//////////////////////////////////////////////////////////////////////////
	//写转换任务描述文件
	pdeuTask->TaskStatus = FINISHED;		
	g_Task2000->UpdateTaskList(g_lisTask);
	//////////////////////////////////////////////////////////////////////////


	//发送结束消息给 hWnd，通知修改Running为FALSE
	SendMessage((HWND)hWnd,WM_TASK_FINISH,NULL,NULL);

	MessageBox(MainFrm.m_hWnd, "转换完毕！", "提示",MB_OK | MB_ICONINFORMATION);
#endif

	g_ThreadFinished = TRUE ;

	return 0;
};


//IDeuConnPool * CDeu2000Task::GetConnPool()
//{
//	return g_CoonPool;
//}


void CDeu2000Task::UpdateTaskList(std::list<CDeuTask*> *p_lisTask)//new or modify all tasks in file
{
//
//	//CTask转到CNode
#if 0
	//测试用传入的TaskList;
	CDeuTask *Task =new CDeuTask;
	Task->CurTable="";
	Task->TaskName="Task_001";
	Task->TaskStatus="0";

	lisTask.push_back(Task);
#else
	std::list<CDeuTask*> lisTask = *p_lisTask;
#endif


	CNode *node = new CNode;
	node->tag_name = L"TaskList";
	node->ele_name = L"TaskList";

	int iCount = lisTask.size();
	for (int i = 0; i<iCount;i++)
	{
		CNode *node_task = getListItem(lisTask,i)->GetNode();

		node->_sub_nodes.push_back(node_task);
	}


	//CNode更新到.ini文件
	CXmlOperate xmlOp2;

	CString path;
	path = GetCurrentDir();

	CString strFileName2;
	strFileName2=path + "TaskInfo.ini";

	xmlOp2.CreateFile(strFileName2,node);

	xmlOp2.flush();
}

//new or modify a task in file
void CDeu2000Task::UpdateTask(CDeuTask* Task)
{
	std::list<CDeuTask*> lisTask;

	int iCount = lisTask.size();

	typedef   std::list <CDeuTask*> ::iterator   T_It; 

	//T_It it = std::find_if(lisTask.begin(),lisTask.end(),IFFunctor<CDeuTask*,CString>(Task->TaskName));


	lisTask.remove_if(IFFunctor_TaskName<CDeuTask*,CString>(Task->TaskName));

	lisTask.push_back(Task);

	UpdateTaskList(&lisTask);

}


//remove a task from file
void CDeu2000Task::RemoveTask(CString TaskName)
{
	std::list<CDeuTask*> lisTask;

	typedef   std::list <CDeuTask*> ::iterator   T_It; 

	//T_It it = std::find_if(lisTask.begin(),lisTask.end(),IFFunctor<CDeuTask*,CString>(Task->TaskName));


	lisTask.remove_if(IFFunctor_TaskName<CDeuTask*,CString>(TaskName));


	UpdateTaskList(&lisTask);
}


void CDeu2000Task::UpdateEllipseList(std::list<CNode*> lisEllipse)
{
	
		//CTask转到CNode
	//#if 0
	//	//测试用传入的TaskList;
	//	CDeuTask *Task =new CDeuTask;
	//	Task->CurTable="";
	//	Task->TaskName="Task_001";
	//	Task->TaskStatus="0";
	//
	//	lisTask.push_back(Task);
	//#endif
		CNode *node = new CNode;
		node->tag_name = L"dy";
		node->ele_name = L"dy";//曹欣
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


void CDeu2000Task::AddData()//(曹欣)
{
	CMainFrame* mainframe = (CMainFrame*)AfxGetMainWnd();
	BOOL IsOK = CheckMap();
	if (IsOK!=TRUE)
	{	
		MessageBox(mainframe->m_hWnd, "请先切换到视图窗口！", "提示",MB_OK | MB_ICONINFORMATION);
	    return;
	}

	CFileDialog fileDlg(TRUE, "Shapefile", "*.shp",OFN_FILEMUSTEXIST|OFN_HIDEREADONLY, "Shapefile(*.shp)|*.shp|位图(*.bmp)|*.bmp|JPEG(*.jpg)|*.jpg|All Files (*.*)|*.*||",NULL);
	fileDlg.m_ofn.lpstrTitle = "Open File";
	if (fileDlg.DoModal() != IDOK)
	{
		return;
	}

	CString pathName = fileDlg.GetPathName();//(曹欣)
	BSTR bstrText = pathName.AllocSysString();

	ShowView(bstrText);
}

void CDeu2000Task::ShowView(BSTR pathString)
{
	CMainFrame* mainframe = (CMainFrame*)AfxGetMainWnd();
	CView*          view1 = mainframe->GetActiveView();
	CDeu2000View *  view2 = (CDeu2000View*)view1;

	CDeuDialog* pViewDlg = (CDeuDialog*)view2->m_DlgContainer.m_DeuTab.GetActiveWnd();

	CDeuDataView *   pDeuDataView = (CDeuDataView*)pViewDlg;
	
	CMap1*          m_map = &pDeuDataView->m_map1;  


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
		m_map->SetSendMouseMove(true);
		hnd = m_map->AddLayer(pSf,true);

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
		m_map->put_ShapeLayerDrawFill(hnd,true);
		FillColor = RGB(n0,n1,n2);
		LineColor = RGB(n3,n4,n5);
		LineWidth = 0.5;
		m_map->put_ShapeLayerFillColor(hnd,FillColor);
		m_map->put_ShapeLayerLineColor(hnd,LineColor);
		m_map->put_ShapeLayerLineWidth(hnd,LineWidth);
		PointColor = RGB(n6,n7,n8);
		PointSize = 5;
		m_map->put_ShapeLayerPointColor(hnd,PointColor);
		m_map->put_ShapeLayerPointSize(hnd,PointSize);
		m_map->put_ShapeLayerPointType(hnd,MapWinGIS::ptCircle);

		m_map->ZoomToMaxVisibleExtents();
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
		pExtents = m_map->GetExtents();
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
	}
	else if (success)
	{
		m_map->SetSendMouseMove(true);
		hnd = m_map->AddLayer(pImage,true);
		m_map->ZoomToMaxVisibleExtents();
		VARIANT_BOOL success2;
		MapWinGIS::ICallbackPtr pcBack2;
		MapWinGIS::IImagePtr pImage2;
		pImage2.CreateInstance(MapWinGIS::CLSID_Image);
		pImage2->Open(pathString,MapWinGIS::USE_FILE_EXTENSION,true,pcBack2,&success2);
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
	}
	else 
	{
		MessageBox(mainframe->m_hWnd,_T("暂不支持所加载的格式数据!请重新选择"),_T("提示"),MB_OK | MB_ICONINFORMATION) ;
		return ;
	}
}


void CDeu2000Task::ZoomIn()
{
	CMainFrame* mainframe = (CMainFrame*)AfxGetMainWnd();
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

	m_map->SetCursorMode(MapWinGIS::cmZoomIn);
}

void CDeu2000Task::ZoomOut()
{
	CMainFrame* mainframe = (CMainFrame*)AfxGetMainWnd();
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

	m_map->SetCursorMode(MapWinGIS::cmZoomOut);
}

void CDeu2000Task::Pan()
{
	CMainFrame* mainframe = (CMainFrame*)AfxGetMainWnd();
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

	m_map->SetCursorMode(MapWinGIS::cmPan);
}

void CDeu2000Task::ZoomToPrev()
{
	CMainFrame* mainframe = (CMainFrame*)AfxGetMainWnd();
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

	MapWinGIS::IExtentsPtr pmyExtents;
	pmyExtents = m_map->GetExtents();	
	//save the extents into array
	m_arrExtents.push_back(pmyExtents);	
	///////////////////////////////////////////////////////////////
	m_map->ZoomToPrev();
}

void CDeu2000Task::ZoomToNext()
{
	CMainFrame* mainframe = (CMainFrame*)AfxGetMainWnd();
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

	MapWinGIS::IExtentsPtr pmyExtents;
	long nSize  = m_arrExtents.size();
	if(nSize == 0 )
	{
		return;
	}
	pmyExtents = m_arrExtents[nSize - 1];
	m_map->SetExtents(pmyExtents);	
	m_arrExtents.resize(nSize - 1);
}

void CDeu2000Task::ZoomToMaxVisibleExtents()
{
	CMainFrame* mainframe = (CMainFrame*)AfxGetMainWnd();
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

	m_map->ZoomToMaxVisibleExtents();
}

void CDeu2000Task::None()
{
	CMainFrame* mainframe = (CMainFrame*)AfxGetMainWnd();
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

	m_map->SetCursorMode(MapWinGIS::cmNone);
	//m_idtyDlg.DoModal();//万炜
	//实现点击获取字段值功能
}

void CDeu2000Task::SelectFeatures()
{
	CMainFrame* mainframe = (CMainFrame*)AfxGetMainWnd();
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

	m_map->SetCursorMode(MapWinGIS::cmSelection);
	m_map->SetSendSelectBoxFinal(true);

}

void CDeu2000Task::RemoveSelections()
{
	CMainFrame* mainframe = (CMainFrame*)AfxGetMainWnd();
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

	long hndl1;
	hndl1 = m_map->get_LayerHandle(0);

	unsigned long ulcolorFill = m_map->get_ShapeLayerFillColor(hndl1);
	m_map->put_ShapeLayerFillColor(hndl1,ulcolorFill);

	unsigned long ulcolorLine = m_map->get_ShapeLayerLineColor(hndl1);
	float fLine = m_map->get_ShapeLayerLineWidth(hndl1);
	m_map->put_ShapeLayerLineColor(hndl1,ulcolorLine);
	m_map->put_ShapeLayerLineWidth(hndl1,fLine);

	unsigned long ulcolorPoint = m_map->get_ShapeLayerPointColor(hndl1);
	float fPoint = m_map->get_ShapeLayerPointSize(hndl1);
	long lPoint = m_map->get_ShapeLayerPointType(hndl1);
	m_map->put_ShapeLayerPointColor(hndl1,ulcolorPoint);
	m_map->put_ShapeLayerPointSize(hndl1,fPoint);
	m_map->put_ShapeLayerPointType(hndl1,lPoint);

	m_map->SetCursorMode(MapWinGIS::cmNone);
	CDeuTreeCtrl* m_tree = mainframe->m_wndSelectedFeatures.GetTree();
	m_tree->DeleteAllItems();
}

void CDeu2000Task::RemoveAllLayers()
{
	CMainFrame* mainframe = (CMainFrame*)AfxGetMainWnd();
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

	CMap1* m_map2 = mainframe->m_wndEagleEye.GetEagleEyeMap();

	CDeuTreeCtrl* m_tree = mainframe->m_wndSelectedFeatures.GetTree();
	m_tree->DeleteAllItems();
	CCoordinateDlg* m_coord = mainframe->m_wndCoordinateSystem.GetCoordinateDlg();
	m_coord->ClearEdits();
	mainframe->m_wndCursorPosition.ClearUnits();
	
	m_map->RemoveAllLayers();
	m_map->SetCursorMode(MapWinGIS::cmNone);
	m_map2->RemoveAllLayers();
	m_map2->ClearDrawings();
}

BOOL CDeu2000Task::CheckMap()
{
	BOOL IsOK = FALSE;

	CMainFrame* mainframe = (CMainFrame*)AfxGetMainWnd();
	CView* view1 = mainframe->GetActiveView();
	CDeu2000View * view2 = (CDeu2000View*)view1;
	
	if(view2->m_DlgContainer.m_DeuTab.GetActiveTab() >= 0)
	{
		CDeuDialog* pViewDlg = (CDeuDialog*)view2->m_DlgContainer.m_DeuTab.GetActiveWnd();
		CWnd* m_map = pViewDlg->GetDlgItem(IDC_MAP1);

		if (m_map)
		{
			IsOK = TRUE;
		}
	}
    return IsOK;
}

double CDeu2000Task::get_PrimeMeridian(CString strCoordSystem)
{

	BOOL bFind = FALSE; 

	CDeuData *pData = m_pMainFrm->m_deuData; 

	#define NODEVALUE(node,n) getNodeFromName(node->_sub_nodes,n)->data.AllocSysString()
	#define NODE(node,n)	  getNodeFromName(node->_sub_nodes,n)
	#define CSTR2DB(str)	_tstof((LPCTSTR)str)

	if(pData->m_PrjCS)
	{
		LIST_IT(CNode*) it =  pData->m_PrjCS->_sub_nodes.begin();

		for (; it != pData->m_PrjCS->_sub_nodes.end() ;it++)
		{
			CNode * prj = *it;
			CString name(NODEVALUE(prj,NAME));

			if( name == strCoordSystem)
			{
				bFind = TRUE;
				
				CNode	*CM			= NODE(prj,CENTRALMERIDIAN);
				double	nCM			= CSTR2DB(NODEVALUE(CM,VALUE));
				return nCM;
			}
		}
	}
	

	if(pData->m_GdtCS)
	{
		LIST_IT(CNode*) it =  pData->m_GdtCS->_sub_nodes.begin();

		for (; it != pData->m_GdtCS->_sub_nodes.end() ;it++)
		{
			CNode * gdt = *it;
			CString name(NODEVALUE(gdt,NAME));

			if( name == strCoordSystem)
			{
				bFind = TRUE;

				return 0;
			}
		}
	}

	if(pData->m_CustomPrjCS)
	{
		LIST_IT(CNode*) it =  pData->m_CustomPrjCS->_sub_nodes.begin();

		for (; it != pData->m_CustomPrjCS->_sub_nodes.end() ;it++)
		{
			CNode * prj = *it;
			CString name(NODEVALUE(prj, NAME));

			if( name == strCoordSystem)
			{
				bFind = TRUE;

				CNode	*CM			= NODE(prj,CENTRALMERIDIAN);
				double	nCM			= CSTR2DB(NODEVALUE(CM,VALUE));
				return nCM;
			}
		}
	}


	if(pData->m_CustomGdtCS)
	{
		LIST_IT(CNode*) it =  pData->m_CustomGdtCS->_sub_nodes.begin();

		for (; it != pData->m_CustomGdtCS->_sub_nodes.end() ;it++)
		{
			CNode * gdt = *it;
			CString name(NODEVALUE(gdt,NAME));

			if( name == strCoordSystem)
			{
				bFind = TRUE;

				return 0;
			}
		}
	}


	return 0;
	
}

int CDeu2000Task::get_CoordType(CString strCoordSystem)
{
	BOOL bFind = FALSE; 

	CDeuData *pData = m_pMainFrm->m_deuData; 

#define NODEVALUE(node,n) getNodeFromName(node->_sub_nodes,n)->data.AllocSysString()
#define NODE(node,n)		getNodeFromName(node->_sub_nodes,n)
#define CSTR2DB(str)	_tstof((LPCTSTR)str)


	if(pData->m_PrjCS)
	{	
		LIST_IT(CNode*) it =  pData->m_PrjCS->_sub_nodes.begin();

		for (; it != pData->m_PrjCS->_sub_nodes.end() ;it++)
		{
			CNode * prj = *it;
			CString name(NODEVALUE(prj,NAME));

			if( name == strCoordSystem)
			{
				bFind = TRUE;
				
				return PLANE;
			}
		}
	}


	if(pData->m_GdtCS)
	{
		LIST_IT(CNode*) it2 =  pData->m_GdtCS->_sub_nodes.begin();

		for (; it2 != pData->m_GdtCS->_sub_nodes.end() ;it2++)
		{
			CNode * gdt = *it2;
			CString name(NODEVALUE(gdt,NAME));

			if( name == strCoordSystem)
			{
				bFind = TRUE;

				return GEODETIC;
			}
		}
	}

	if(pData->m_CustomPrjCS)
	{	
		LIST_IT(CNode*) it =  pData->m_CustomPrjCS->_sub_nodes.begin();

		for (; it != pData->m_CustomPrjCS->_sub_nodes.end() ;it++)
		{
			CNode * prj = *it;
			CString name(NODEVALUE(prj,NAME));

			if( name == strCoordSystem)
			{
				bFind = TRUE;

				return PLANE;
			}
		}
	}


	if(pData->m_CustomGdtCS)
	{
		LIST_IT(CNode*) it2 =  pData->m_CustomGdtCS->_sub_nodes.begin();

		for (; it2 != pData->m_CustomGdtCS->_sub_nodes.end() ;it2++)
		{
			CNode * gdt = *it2;
			CString name(NODEVALUE(gdt,NAME));

			if( name == strCoordSystem)
			{
				bFind = TRUE;

				return GEODETIC;
			}
		}
	}

	return UNKNOWN;

}