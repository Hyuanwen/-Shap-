// DeuPropertyFrame.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DeuPropertyFrame.h"


// CDeuPropertyFrame

IMPLEMENT_DYNCREATE(CDeuPropertyFrame, CXTPFrameWnd)

CDeuPropertyFrame::CDeuPropertyFrame()
{

}

CDeuPropertyFrame::~CDeuPropertyFrame()
{
}

BOOL CDeuPropertyFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/, CCreateContext* pContext)
{
	return m_wndSplitter.Create(this,
		2, 2,       // TODO: ��������������
		CSize(10, 10),  // TODO: ������С�����С
		pContext);
}

BEGIN_MESSAGE_MAP(CDeuPropertyFrame, CXTPFrameWnd)
END_MESSAGE_MAP()


// CDeuPropertyFrame ��Ϣ�������
