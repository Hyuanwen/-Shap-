// ChildFrm.cpp : CChildFrame 类的实现
//
#include "stdafx.h"
#include "DeuGlobal.h"
#include "DeuViewerFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildFrame
IMPLEMENT_DYNCREATE(CDeuViewerFrame, CMDIChildWnd)
BEGIN_MESSAGE_MAP(CDeuViewerFrame, CMDIChildWnd)
END_MESSAGE_MAP()

// CChildFrame 构造/析构
CDeuViewerFrame::CDeuViewerFrame()
{
	lstrcpy(sz_ModuleType, "IsView");
}

CDeuViewerFrame::~CDeuViewerFrame()
{
}

BOOL CDeuViewerFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改 CREATESTRUCT cs 来修改窗口类或样式
	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

// CChildFrame 诊断
#ifdef _DEBUG
void CDeuViewerFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CDeuViewerFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

// CChildFrame 消息处理程序
