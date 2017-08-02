#pragma once

#include "resource.h"
#include "DeuPaneVectorProject.h"
#include "DeuGlobalChildFrame.h"

class CDeuVectorProjectFrame : public CDeuGlobalChildFrame
{
	DECLARE_DYNCREATE(CDeuVectorProjectFrame)

public:
	CDeuVectorProjectFrame();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CDeuVectorProjectFrame();

protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	CXTPDockingPaneManager m_paneManager;
	CDeuPaneVectorProject m_PaneVectorProject;
};


