// ChildFrm.cpp : CChildFrame ���ʵ��
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

// CChildFrame ����/����
CDeuViewerFrame::CDeuViewerFrame()
{
	lstrcpy(sz_ModuleType, "IsView");
}

CDeuViewerFrame::~CDeuViewerFrame()
{
}

BOOL CDeuViewerFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸� CREATESTRUCT cs ���޸Ĵ��������ʽ
	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

// CChildFrame ���
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

// CChildFrame ��Ϣ�������
