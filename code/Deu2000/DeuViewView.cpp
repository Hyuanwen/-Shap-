// Deu2000View.cpp : CDeuViewView 类的实现
//

#include "stdafx.h"
#include "DeuGlobal.h"
#include "DeuViewerDoc.h"
#include "DeuViewView.h"
#include "ogrsf_frmts.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CDeuViewView
IMPLEMENT_DYNCREATE(CDeuViewView, CFormView)
BEGIN_MESSAGE_MAP(CDeuViewView, CFormView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CDeuViewView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CDeuViewView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CDeuViewView::OnFilePrintPreview)	
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

BEGIN_EVENTSINK_MAP(CDeuViewView, CFormView)
	ON_EVENT(CDeuViewView, IDC_MAPVIEW, 5, CDeuViewView::SelectBoxFinalMap, VTS_I4 VTS_I4 VTS_I4 VTS_I4)
END_EVENTSINK_MAP()

// CDeuViewView 构造/析构
CDeuViewView::CDeuViewView()
		   :CFormView(CDeuViewView::IDD)
{
	// TODO: 在此处添加构造代码
	//	SetScrollSizes(MM_TEXT, CSize(0, 0));
}

CDeuViewView::~CDeuViewView()
{
}

BOOL CDeuViewView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	return CFormView::PreCreateWindow(cs);
}

// CDeuViewView 绘制
void CDeuViewView::OnDraw(CDC* pDC)
{ 
	CDeuViewerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}

void CDeuViewView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MAPVIEW, m_MapCtrl);
}

// CDeuViewView 打印
BOOL CDeuViewView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CDeuViewView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CDeuViewView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

// CDeuViewView 诊断
#ifdef _DEBUG
void CDeuViewView::AssertValid() const
{
	CFormView::AssertValid();
}

void CDeuViewView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

CDeuViewerDoc* CDeuViewView::GetDocument() const
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDeuViewerDoc)));
	return (CDeuViewerDoc*)m_pDocument;
}

void CDeuViewView::OnInitialUpdate()
{	
	CFormView::OnInitialUpdate();	
}

int CDeuViewView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}

void CDeuViewView::OnSize(UINT nType, int cx, int cy)
{
	//CRect rct;
	//this->GetClientRect(&rct);

	CWnd* p_map = this->GetDlgItem(IDC_MAPVIEW);
	if(p_map->GetSafeHwnd())
	{	
		this->SetScrollPos(SB_HORZ, 0);
		this->SetScrollPos(SB_VERT, 0);
		int n_hMin, n_hMax, n_vMin, n_vMax;
		this->GetScrollRange(SB_HORZ, &n_hMin, &n_hMax);
		this->GetScrollRange(SB_VERT, &n_vMin, &n_vMax);
		
		//如果宽度小余横向滚动条尺寸
		if(cx < n_hMax && cy > n_vMax)
		{
			p_map->MoveWindow(5, 5, n_hMax-10, cy-10);
		}
		else if(cx > n_hMax && cy < n_vMax)
		{
			p_map->MoveWindow(5, 5, cx-10, n_vMax-10);
		}
		else if(cx < n_hMax && cy < n_vMax)
		{
			p_map->MoveWindow(5, 5, n_hMax-10, n_vMax-10);
		}
		else
		{
			p_map->MoveWindow(5, 5, cx-10, cy-10);
		}
	}

	CFormView::OnSize(nType, cx, cy);
}

void CDeuViewView::OnZoomIn()
{
	m_TaskProcess.ZoomIn(&m_MapCtrl);
}

void CDeuViewView::OnZoomOut()
{
	m_TaskProcess.ZoomOut(&m_MapCtrl);
}

void CDeuViewView::OnZoomLoad(const char* sz_file)
{
	BSTR bstrText = _com_util::ConvertStringToBSTR(sz_file);
	m_TaskProcess.ShowView(bstrText, &m_MapCtrl);
}

void CDeuViewView::OnZoomMove()
{
	m_TaskProcess.Pan(&m_MapCtrl);
}

void CDeuViewView::OnZoomAllPic()
{
	m_TaskProcess.ZoomToMaxVisibleExtents(&m_MapCtrl);
}

void CDeuViewView::OnSelect()	
{
	m_TaskProcess.SelectFeatures(&m_MapCtrl);
}

void CDeuViewView::OnSelectCancel()
{
	m_TaskProcess.RemoveSelections(&m_MapCtrl);
}

void CDeuViewView::OnClearLayers()
{
	m_TaskProcess.RemoveAllLayers(&m_MapCtrl);
}

void CDeuViewView::OnZoomPre()   //上一张视图
{
	m_TaskProcess.ZoomToPrev(&m_MapCtrl);
}

void CDeuViewView::OnZoomNext()  //下一张视图
{
	m_TaskProcess.ZoomToNext(&m_MapCtrl);
}

void CDeuViewView::OnDefaultState()
{
	m_TaskProcess.None(&m_MapCtrl);
}

void CDeuViewView::SelectBoxFinalMap(long left, long right, long bottom, long top)
{
	long hndl = m_MapCtrl.get_LayerHandle(0);
	MapWinGIS::IShapefilePtr pSf0 = m_MapCtrl.get_GetObject(hndl);
	MapWinGIS::IImagePtr pImage0  = m_MapCtrl.get_GetObject(hndl);
	MapWinGIS::IGridPtr  pGrid0   = m_MapCtrl.get_GetObject(hndl);
	if (pSf0 || pImage0 || pGrid0){}
	else return;
		
	if (MapWinGIS::cmSelection != m_MapCtrl.GetCursorMode())
	{
		TRACE(_T("The cursor mode isn't selection !\n"));
		return;
	}

	//获取图层名称,设置根节点名称
	long hndl1 = m_MapCtrl.get_LayerHandle(0);
	CString layername = m_MapCtrl.get_LayerName(hndl1);

	if (pSf0)
	{
		//转换拖画出的矩形框的范围,获取该范围内的地物
		MapWinGIS::IShapefilePtr pSf = m_MapCtrl.get_GetObject(hndl1);
		MapWinGIS::IExtentsPtr pExtents;
		pExtents.CreateInstance(MapWinGIS::CLSID_Extents);
		double pxMin,pxMax,pyMin,pyMax;	
		m_MapCtrl.PixelToProj(left,bottom,&pxMin,&pyMin);
		m_MapCtrl.PixelToProj(right,top,&pxMax,&pyMax);
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
		unsigned long ulcolorFill = m_MapCtrl.get_ShapeLayerFillColor(hndl1);                  //填充
		m_MapCtrl.put_ShapeLayerFillColor(hndl1,ulcolorFill);
		unsigned long ulcolorLine = m_MapCtrl.get_ShapeLayerLineColor(hndl1);                  //线——颜色\宽度
		float fLine = m_MapCtrl.get_ShapeLayerLineWidth(hndl1);
		m_MapCtrl.put_ShapeLayerLineColor(hndl1,ulcolorLine);
		m_MapCtrl.put_ShapeLayerLineWidth(hndl1,fLine);
		unsigned long ulcolorPoint = m_MapCtrl.get_ShapeLayerPointColor(hndl1);                //点--颜色\大小\样式
		float fPoint = m_MapCtrl.get_ShapeLayerPointSize(hndl1);
		long lPoint = m_MapCtrl.get_ShapeLayerPointType(hndl1);
		m_MapCtrl.put_ShapeLayerPointColor(hndl1,ulcolorPoint);
		m_MapCtrl.put_ShapeLayerPointSize(hndl1,fPoint);
		m_MapCtrl.put_ShapeLayerPointType(hndl1,lPoint);

		//对选中的shape数组进行处理,解析没一个选中地物
		SAFEARRAY* arr=selectedShapes.parray;
		long MAX = arr->rgsabound->cElements;                                               //选中shape的总个数	
		long buf[1]={0};	
		//pmainframe->m_wndSelectedFeatures.SetSelectedFeaturesNum(MAX);

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
			m_MapCtrl.put_ShapeFillColor(hndl1,buf[0],RGB(255,0,0));
			m_MapCtrl.put_ShapeLineColor(hndl1,buf[0],RGB(255,0,0));
			m_MapCtrl.put_ShapeLineWidth(hndl1,buf[0],2*fLine);
			m_MapCtrl.put_ShapePointType(hndl1,buf[0],MapWinGIS::ptDiamond);
			m_MapCtrl.put_ShapePointColor(hndl1,buf[0],RGB(255,0,0));
			m_MapCtrl.put_ShapePointSize(hndl1,buf[0],2*fPoint);
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
			//pmainframe->m_wndSelectedFeatures.SetTreeContexts((CString)(LPCSTR)_bstr_t(filename), MAX,numfields,vecFieldvalues,vecFieldname);                 //(CString)(LPCSTR)_bstr_t(filename)
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
			//pmainframe->m_wndSelectedFeatures.SetTreeContexts((CString)(LPCSTR)_bstr_t(filename), 100,numfields,vecFieldvalues,vecFieldname);                 //(CString)(LPCSTR)_bstr_t(filename)
		}
		OGRDataSource::DestroyDataSource( poDS );
	}
	else
	{
	}
}