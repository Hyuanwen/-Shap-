#pragma once

#ifdef _WIN32_WCE
#error "Windows CE 不支持 CMDIChildWnd。"
#endif 

// 带有拆分器的 CDeuPropertyFrame 框架

class CDeuPropertyFrame : public CXTPFrameWnd
{
	DECLARE_DYNCREATE(CDeuPropertyFrame)
public:
	CDeuPropertyFrame();           // 动态创建所使用的受保护的构造函数
	virtual ~CDeuPropertyFrame();

	CXTSplitterWnd m_wndSplitter;

protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);

	DECLARE_MESSAGE_MAP()
};


