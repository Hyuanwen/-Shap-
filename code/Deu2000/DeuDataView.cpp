// DeuDataView.cpp : 实现文件
//

#include "stdafx.h"
#include "Deu2000.h"
#include "DeuDataView.h"
#include "ogrsf_frmts.h"


#include <vector>

// CDeuDataView 对话框

IMPLEMENT_DYNAMIC(CDeuDataView, CDeuDialog)

CDeuDataView::CDeuDataView(CWnd* pParent /*=NULL*/)
	: CDeuDialog()  //CDeuDataView::IDD
{
	this->nWndType = 1;
}

CDeuDataView::~CDeuDataView()
{
}

void CDeuDataView::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MAP1, m_map1);
}


BEGIN_MESSAGE_MAP(CDeuDataView, CDeuDialog)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CDeuDataView 消息处理程序
BEGIN_EVENTSINK_MAP(CDeuDataView, CDeuDialog)
	ON_EVENT(CDeuDataView, IDC_MAP1, 3, CDeuDataView::MouseMoveMap1, VTS_I2 VTS_I2 VTS_I4 VTS_I4)
	ON_EVENT(CDeuDataView, IDC_MAP1, 5, CDeuDataView::SelectBoxFinalMap1, VTS_I4 VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CDeuDataView, IDC_MAP1, 7, CDeuDataView::ExtentsChangedMap1, VTS_NONE)
	ON_EVENT(CDeuDataView, IDC_MAP1, 4, CDeuDataView::FileDroppedMap1, VTS_BSTR)
END_EVENTSINK_MAP()

void CDeuDataView::MouseMoveMap1(short Button, short Shift, long x, long y)
{
	// TODO: 在此处添加消息处理程序代码
	if(m_map1.m_hWnd ==NULL)
		return;
	double prjX,prjY;	
	m_map1.PixelToProj(x,y,&prjX,&prjY);

	CMainFrame* pmainframe=(CMainFrame*)AfxGetMainWnd();
	if (pmainframe)
	{
		CString sCoord;
		sCoord.Format("%.4lf",prjX);
		pmainframe->m_wndCursorPosition.SetEdit1Text(sCoord);
		sCoord.Format("%.4lf",prjY);
		pmainframe->m_wndCursorPosition.SetEdit2Text(sCoord);
	}	
}

void CDeuDataView::SelectBoxFinalMap1(long left, long right, long bottom, long top)
{
	// TODO: 在此处添加消息处理程序代码
    if(m_map1.m_hWnd ==NULL)
		return;
	long hndl = m_map1.get_LayerHandle(0);
	MapWinGIS::IShapefilePtr pSf0 = m_map1.get_GetObject(hndl);
	MapWinGIS::IImagePtr pImage0  = m_map1.get_GetObject(hndl);
	MapWinGIS::IGridPtr  pGrid0   = m_map1.get_GetObject(hndl);
	if (pSf0 || pImage0|| pGrid0 )
	{

	}
	else  return;
	
	if (MapWinGIS::cmSelection != m_map1.GetCursorMode())
	{
		TRACE(_T("The cursor mode isn't selection !\n"));		
		return;
	}
	CMainFrame* mainframe = (CMainFrame*)AfxGetMainWnd();
	CDeuTreeCtrl* m_tree = mainframe->m_wndSelectedFeatures.GetTree();
	m_tree->DeleteAllItems();

	//获取图层名称,设置根节点名称
	long hndl1 = m_map1.get_LayerHandle(0);
	CString layername = m_map1.get_LayerName(hndl1);
	CMainFrame* pmainframe=(CMainFrame*)AfxGetMainWnd();
	pmainframe->m_wndSelectedFeatures.SetTreeRootName(layername);                       //传入根节点图层名称//wanwei

	if (pSf0)
	{
		//转换拖画出的矩形框的范围,获取该范围内的地物
		MapWinGIS::IShapefilePtr pSf = m_map1.get_GetObject(hndl1);
		MapWinGIS::IExtentsPtr pExtents;
		pExtents.CreateInstance(MapWinGIS::CLSID_Extents);
		double pxMin,pxMax,pyMin,pyMax;	
		m_map1.PixelToProj(left,bottom,&pxMin,&pyMin);
		m_map1.PixelToProj(right,top,&pxMax,&pyMax);
		pExtents->SetBounds(pxMin,pyMin,0,pxMax,pyMax,0);
		VARIANT selectedShapes;
		VARIANT_BOOL success;
		pSf->SelectShapes(pExtents,0,MapWinGIS::INTERSECTION,&selectedShapes,&success);
		if (!success)
		{
			TRACE(_T("select failed! \n"));
			return;
		}

		//先还原图层颜色、线条宽度、点大小\类型
		unsigned long ulcolorFill = m_map1.get_ShapeLayerFillColor(hndl1);                  //填充
		m_map1.put_ShapeLayerFillColor(hndl1,ulcolorFill);
		unsigned long ulcolorLine = m_map1.get_ShapeLayerLineColor(hndl1);                  //线——颜色\宽度
		float fLine = m_map1.get_ShapeLayerLineWidth(hndl1);
		m_map1.put_ShapeLayerLineColor(hndl1,ulcolorLine);
		m_map1.put_ShapeLayerLineWidth(hndl1,fLine);
		
		unsigned long ulcolorPoint = m_map1.get_ShapeLayerPointColor(hndl1);                //点--颜色\大小\样式
		float fPoint = m_map1.get_ShapeLayerPointSize(hndl1);
		long lPoint = m_map1.get_ShapeLayerPointType(hndl1);
		m_map1.put_ShapeLayerPointColor(hndl1,ulcolorPoint);
		m_map1.put_ShapeLayerPointSize(hndl1,fPoint);
		m_map1.put_ShapeLayerPointType(hndl1,lPoint);
		
		//对选中的shape数组进行处理,解析没一个选中地物
		SAFEARRAY* arr=selectedShapes.parray;
		long MAX = arr->rgsabound->cElements;                                               //选中shape的总个数	
		long buf[1]={0};	
		pmainframe->m_wndSelectedFeatures.SetSelectedFeaturesNum(MAX);


		//获取图层各属性名称
		long numfields;                                                 //图层属性字段个数
		pSf->get_NumFields(&numfields);		

		MapWinGIS::IFieldPtr   pField;                                  //临时字段变量	
		BSTR        tFieldname = NULL;                                  //临时字段名变量
		VEC(BSTR)        vecFieldname;                                  //vector字段名数组
		VEC(VEC(CString)) vecFieldvalues;                              //vector字段值数组

		for (long k = 0;k<numfields;k ++)
		{
			pSf->get_Field(k,&pField);		
			pField->get_Name(&tFieldname);		
			vecFieldname.push_back(tFieldname);
		}
		BSTR filename = NULL;
		pSf->get_Filename(&filename);
		OGRRegisterAll();
		OGRDataSource   *poDS = OGRSFDriverRegistrar::Open( (LPCSTR)_bstr_t(filename), FALSE );	
		OGRLayer     *poLayer = poDS->GetLayer(0);

		for(long i=0;i<MAX;i++)
		{		
			//图层还原后,将选中shape高亮显示
			SafeArrayGetElement(arr,&i,buf);
			m_map1.put_ShapeFillColor(hndl1,buf[0],RGB(255,0,0));
			m_map1.put_ShapeLineColor(hndl1,buf[0],RGB(255,0,0));
			m_map1.put_ShapeLineWidth(hndl1,buf[0],2*fLine);
			m_map1.put_ShapePointType(hndl1,buf[0],MapWinGIS::ptDiamond);
			m_map1.put_ShapePointColor(hndl1,buf[0],RGB(255,0,0));
			m_map1.put_ShapePointSize(hndl1,buf[0],2*fPoint);
		}

		if (MAX<100)
		{
			CString sNum;
			sNum.Format("%d",MAX);
			MessageBox("已选中" + sNum + "个地物！\n", "提示",MB_OK | MB_ICONINFORMATION);	    //pmainframe->m_hWnd,
			for (long i=0;i<MAX;i++)
			{
				SafeArrayGetElement(arr,&i,buf);

				//获取这个选中shape的属性信息	
				OGRFeature     *poFeature = poLayer->GetFeature(buf[0]);	
				VEC(CString) tvecFieldvalues;                                                                  //临时字段值数组		
				const char* tstrFieldvalue ;		
				for (long k = 0;k<numfields;k ++)
				{
					
					tstrFieldvalue =  poFeature->GetFieldAsString(k) ;
					CString str    =  tstrFieldvalue;
					tvecFieldvalues.push_back(str);	
				}	
				vecFieldvalues.push_back(tvecFieldvalues);	
				OGRFeature::DestroyFeature(poFeature);
			}
			pmainframe->m_wndSelectedFeatures.SetTreeContexts((CString)(LPCSTR)_bstr_t(filename), MAX,numfields,vecFieldvalues,vecFieldname);                 //(CString)(LPCSTR)_bstr_t(filename)
		}
		else
		{
			CString sNum;
			sNum.Format("%d",MAX);
			MessageBox("已选中" + sNum + "个地物！\n"+"将只显示前100个地物属性信息!","提示",MB_OK | MB_ICONINFORMATION);	    //pmainframe->m_hWnd,
			for (long i=0;i<100;i++)
			{
				SafeArrayGetElement(arr,&i,buf);

				//获取这个选中shape的属性信息	
				OGRFeature     *poFeature = poLayer->GetFeature(buf[0]);	
				VEC(CString)  tvecFieldvalues;                                                                  //临时字段值数组		
				const char*   tstrFieldvalue ;		
				for (long k = 0;k<numfields;k ++)
				{					
					tstrFieldvalue =  poFeature->GetFieldAsString(k) ;
					CString str    =  tstrFieldvalue;
					tvecFieldvalues.push_back(str);	
				}	
				vecFieldvalues.push_back(tvecFieldvalues);	
				OGRFeature::DestroyFeature(poFeature);
			}
			pmainframe->m_wndSelectedFeatures.SetTreeContexts((CString)(LPCSTR)_bstr_t(filename), 100,numfields,vecFieldvalues,vecFieldname);                 //(CString)(LPCSTR)_bstr_t(filename)
		}
		OGRDataSource::DestroyDataSource( poDS );
	}
    else
	{

	}
}

void CDeuDataView::ExtentsChangedMap1()
{
	// TODO: 在此处添加消息处理程序代码
	if (m_map1.m_hWnd != NULL )
	{		
		long hndl = m_map1.get_LayerHandle(0);
		MapWinGIS::IShapefilePtr pSf0 = m_map1.get_GetObject(hndl);
		MapWinGIS::IImagePtr pImage0  = m_map1.get_GetObject(hndl);
		MapWinGIS::IGridPtr  pGrid0   = m_map1.get_GetObject(hndl);
		if (pSf0 || pImage0|| pGrid0 )
		{
		}
		else
		{
			return;
		}
		
		MapWinGIS::IExtentsPtr pExtents;
		pExtents = m_map1.GetExtents();
		double xMin,xMax,yMin,yMax,zMin,zMax;
		pExtents->GetBounds(&xMin,&yMin,&zMin,&xMax,&yMax,&zMax);

		CMainFrame* pmainframe = (CMainFrame*)AfxGetMainWnd();
		CMap1* m_map2 = pmainframe->m_wndEagleEye.GetEagleEyeMap();
		m_map2->ClearDrawings();
		long draw_hnd = m_map2->NewDrawing(MapWinGIS::dlSpatiallyReferencedList);		
		long  width = 2;
		m_map2->DrawLine(xMin+0,yMin+0,xMax-0,yMin+0,width,RGB(255,0,0));
		m_map2->DrawLine(xMax-0,yMin+0,xMax-0,yMax-0,width,RGB(255,0,0));
		m_map2->DrawLine(xMax-0,yMax-0,xMin+0,yMax-0,width,RGB(255,0,0));
		m_map2->DrawLine(xMin+0,yMax-0,xMin+0,yMin+0,width,RGB(255,0,0));
	}
}

void CDeuDataView::OnSize(UINT nType, int cx, int cy)
{
	CBCGPDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	
	if (m_map1.m_hWnd!=NULL)
	{
		m_map1.MoveWindow(5,5,cx-10,cy-10);
	}
	
//	this->MoveWindow(0, 0, cx,cy);
	
}

void CDeuDataView::FileDroppedMap1(LPCTSTR Filename)
{
	// TODO: 在此处添加消息处理程序代码
	CMainFrame* mainframe = (CMainFrame*)AfxGetMainWnd();
	CString pathName = (CString)Filename;
	BSTR    bstrText = pathName.AllocSysString();

	VARIANT_BOOL ret;
	MapWinGIS::IShapefilePtr pSf;
	pSf.CreateInstance(MapWinGIS::CLSID_Shapefile);
	pSf->Open(bstrText,NULL,&ret);

	VARIANT_BOOL success;
	MapWinGIS::ICallbackPtr pcBack;
	MapWinGIS::IImagePtr pImage;
	pImage.CreateInstance(MapWinGIS::CLSID_Image);
	pImage->Open(bstrText,MapWinGIS::USE_FILE_EXTENSION,TRUE,pcBack,&success);

	long hnd;
	if (ret)
	{
		m_map1.SetSendMouseMove(true);
		hnd = m_map1.AddLayer(pSf,true);
		
		m_map1.ZoomToMaxVisibleExtents();
		CMap1*   m_map2 = mainframe->m_wndEagleEye.GetEagleEyeMap();
		
		m_map2->AddLayer(m_map1.get_GetObject(hnd),true);                                         //鹰眼视图同步添加主视图地图
		m_map2->ZoomToMaxVisibleExtents();
		
		MapWinGIS::IExtentsPtr pExtents;
		pExtents = m_map1.GetExtents();
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
		OGRDataSource   *poDS = OGRSFDriverRegistrar::Open((LPCSTR)_bstr_t(bstrText), FALSE );		
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
		m_map1.SetSendMouseMove(true);
		hnd = m_map1.AddLayer(pImage,true);
		m_map1.ZoomToMaxVisibleExtents();
		CMap1*   m_map2 = mainframe->m_wndEagleEye.GetEagleEyeMap();
		m_map2->AddLayer(m_map1.get_GetObject(hnd),true);                                         //鹰眼视图同步添加主视图地图
		m_map2->ZoomToMaxVisibleExtents();
		MapWinGIS::IExtentsPtr pExtents;
		pExtents = m_map1.GetExtents();
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
		MessageBox(_T("暂不支持所加载的格式数据!请重新选择"),_T("提示"),MB_OK | MB_ICONINFORMATION) ;
		return ;
	}
}


BOOL CDeuDataView::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	return TRUE;
	
}
