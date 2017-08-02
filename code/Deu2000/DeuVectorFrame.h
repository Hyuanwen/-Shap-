#pragma once

#include "resource.h"
#include "DeuPaneVector.h"
#include "DeuGlobalChildFrame.h"

class CDeuVectorFrame : public CDeuGlobalChildFrame
{
	DECLARE_DYNCREATE(CDeuVectorFrame)
public:
	CDeuVectorFrame();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CDeuVectorFrame();

protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	CXTPDockingPaneManager m_paneManager;
	CDeuPaneVector m_PaneVector;
};


