#pragma once

#ifdef _WIN32_WCE
#error "Windows CE ��֧�� CMDIChildWnd��"
#endif 

// ���в������ CDeuPropertyFrame ���

class CDeuPropertyFrame : public CXTPFrameWnd
{
	DECLARE_DYNCREATE(CDeuPropertyFrame)
public:
	CDeuPropertyFrame();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CDeuPropertyFrame();

	CXTSplitterWnd m_wndSplitter;

protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);

	DECLARE_MESSAGE_MAP()
};


