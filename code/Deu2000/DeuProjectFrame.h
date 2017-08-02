#pragma once

#include "DeuPaneProject.h"
#include "DeuGlobalChildFrame.h"

class CDeuProjectFrame : public CDeuGlobalChildFrame
{
	DECLARE_DYNCREATE(CDeuProjectFrame)
public:
	CDeuProjectFrame();           // 动态创建所使用的受保护的构造函数
	virtual ~CDeuProjectFrame();

protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	CXTPDockingPaneManager PanelManager;
	CXTPDockingPane *p_panel;
	CDeuPaneProject m_PaneProject;
};


