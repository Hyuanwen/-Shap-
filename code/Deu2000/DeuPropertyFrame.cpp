// DeuPropertyFrame.cpp : 实现文件
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
		2, 2,       // TODO: 调整行数和列数
		CSize(10, 10),  // TODO: 调整最小窗格大小
		pContext);
}

BEGIN_MESSAGE_MAP(CDeuPropertyFrame, CXTPFrameWnd)
END_MESSAGE_MAP()


// CDeuPropertyFrame 消息处理程序
