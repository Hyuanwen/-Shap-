// Deu2000View.cpp : implementation of the CDeu2000View class
//

#include "stdafx.h"
#include "Deu2000.h"

#include "Deu2000Doc.h"
#include "Deu2000View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDeu2000View

IMPLEMENT_DYNCREATE(CDeu2000View, CScrollView)

BEGIN_MESSAGE_MAP(CDeu2000View, CScrollView)
	ON_WM_CREATE()
	//ON_WM_SIZE()
	//ON_WM_VSCROLL()
	//ON_WM_HSCROLL()
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CDeu2000View construction/destruction

//void CDeu2000View::OnSize(UINT nType, int cx, int cy)
//{
//
//	CScrollView::OnSize(nType,cx,cy);
//
//	return;
//}

void CDeu2000View::OnInitialUpdate()
{
	//SetScaleToFitSize(MM_TEXT, CSize(2000,800));

	CRect rc;
	GetClientRect(&rc);


	/*SetScrollSizes(MM_TEXT, CSize(rc.Width(), rc.Height()));*/


	//CScrollView::OnInitialUpdate();

	//m_Sheet = new CDeuPertySheet(CBCGPPropertySheet::PropSheetLook_OneNoteTabs,IDB_TOOLBAR256, 16,TRUE);
	//
	//m_Sheet->Create(this,WS_CHILD|WS_VISIBLE);
	//m_Sheet->SetWindowPos(&wndTop, 0, 0, rc.Width(), rc.Height(),SWP_SHOWWINDOW);
	//RECT r;	
	//m_Sheet->GetClientRect(&r);
	//m_Sheet->MoveWindow(&r, 1);
	//m_Sheet->SetWindowPos(&wndTop, 0, 0, rc.Width(), rc.Height(),SWP_SHOWWINDOW);
	

//	m_HScrollMax = rc.Width();

	m_DlgContainer.Create(IDD_DIALOG_CONTAINER, this);
	m_DlgContainer.SetWindowPos(&wndTop, rc.left,rc.top, rc.Width(), rc.Height(), SWP_SHOWWINDOW);
	
	
	//TRACE("widht:%d; height:%d", rc.Width(), rc.Height());
	
}


////OnVScroll()
//void CDeu2000View::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
//{
//	//this->SetScrollPos( SB_HORZ ,nPos);
//	//this->OnScroll(nSBCode,nPos);
//	long   nScrollInc;   
//	long   nNewPos;   
//	switch(nSBCode)                         //获取鼠标按键位置 
//	{     
//	case   SB_TOP:                               //左部 
//		nScrollInc   =   m_HScrollMax   -   m_HScrollPos;   
//		break;   
//	case   SB_BOTTOM:                         //右部 
//		nScrollInc   =   -   m_HScrollPos;   
//		break;   
//	case   SB_LINEUP:                         //向左按键 
//		nScrollInc   =   50;   
//		break;   
//	case   SB_LINEDOWN:                     //向右按键 
//		nScrollInc   =   -50;   
//		break;   
//	case   SB_PAGEUP:                         //按中中间活动按钮的左部区域 
//		nScrollInc   =   100;   
//		break;   
//	case   SB_PAGEDOWN:                     //按中中间活动按钮的右部区域 
//		nScrollInc   =   -100;   
//		break;   
//	case   SB_THUMBPOSITION:           //鼠标拖动到某一位置 
//		nScrollInc   =   nPos   -   m_HScrollPos;   
//		break;   
//	default: 
//		nScrollInc   =   0;   
//	} 
//	nNewPos   =   max(0,   min(m_HScrollPos   +   nScrollInc,   m_HScrollMax));   //得到实际滚动位置 
//	nScrollInc   =   nNewPos   -   m_HScrollPos;                                                         //相对滚动范围 
//
//	if   (nScrollInc) 
//	{ 
//
//		m_HScrollPos   =   nNewPos;                             //得到新的滚动位置 
//		SetScrollPos(SB_HORZ,   m_HScrollPos);   //设置滚动位置 
//		UpdateWindow();                                             //更新滚动条显示 
//	}
//
//	CScrollView::OnHScroll(nSBCode,   nPos,   pScrollBar); 
//}
//
//void CDeu2000View::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
//{
//	int y = GetScrollPos(SB_VERT);
//	int yMax = GetScrollLimit(SB_VERT);
//	  
//	ScrollWindow(0, 100);
//	UpdateWindow();
//	this->SetScrollPos( SB_VERT ,nPos);
//}
//
//BOOL CDeu2000View::OnScroll(UINT nScrollCode, UINT nPos, BOOL bDoScroll )
//{
//	
//	return CScrollView::OnScroll(nScrollCode,nPos,bDoScroll);
//}

int CDeu2000View::OnCreate(LPCREATESTRUCT lpcs)
{
	CScrollView::OnCreate(lpcs);

	//SetScaleToFitSize();
	//CRect rc;
	//GetClientRect(&rc);
	//SetScrollSizes(MM_TEXT, CSize(rc.Width(),rc.Height()));
		
	return 0;
}


CDeu2000View::CDeu2000View()
{
	// TODO: add construction code here
	
}

CDeu2000View::~CDeu2000View()
{
	//delete m_Sheet;
}

BOOL CDeu2000View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CDeu2000View drawing

void CDeu2000View::OnDraw(CDC* /*pDC*/)
{	
	CDeu2000Doc* pDoc = GetDocument();
	//ASSERT_VALID(pDoc);	
}


// CDeu2000View printing

void CDeu2000View::OnFilePrintPreview()
{
	BCGPPrintPreview (this);
}

BOOL CDeu2000View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDeu2000View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDeu2000View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CDeu2000View diagnostics

#ifdef _DEBUG
void CDeu2000View::AssertValid() const
{
	CScrollView::AssertValid();
}

void CDeu2000View::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CDeu2000Doc* CDeu2000View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDeu2000Doc)));
	return (CDeu2000Doc*)m_pDocument;
}

//BOOL CDeu2000View::PreTranslateMessage(MSG* pMsg)
//{
//	//if(pMsg->message == SC_MAXIMIZE)
//	//{
//	//	//this->IsMaxWnd = true;	
//	//}
//	return 0;
//}

#endif //_DEBUG


// CDeu2000View message handlers

void CDeu2000View::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
	/*
	CRect rc;
	GetClientRect(&rc);
	*/
	
	//CRgn m_rgn;
	//m_rgn.CreateRectRgn(rc.left, rc.top, rc.Width(), rc.Height());
	//if(IsMaxWnd)
	
	//m_Sheet->SetWindowPos(&wndTop,0, 0, rc.Width(),rc.Height(),SWP_SHOWWINDOW);
	//m_Sheet->SetWindowRgn(m_rgn, FALSE);
	
	//TRACE("width:%d; height:%d\n\r", rc.Width(),rc.Height());
	

	//m_HScrollMax = rc.Width();


}


void CDeu2000View::OnSize(UINT nType, int cx, int cy)
{
	CScrollView::OnSize(nType, cx, cy);

	if(m_DlgContainer.m_hWnd != NULL)
	{
		CRect rc;
		GetClientRect(&rc);
		m_DlgContainer.SetWindowPos(&wndTop, rc.left,rc.top, rc.Width(), rc.Height(), SWP_SHOWWINDOW);
	}
	
}


/*
=============================================   
功能:		第一次加载时，初始化历史任务     
程序逻辑:	读取容器里面的数据
日期:		2010-12-1
=============================================
*/
void CDeu2000View::InitTaskTab()
{
	


}