#pragma once

#include "DeuPaneRaster.h"
#include "DeuGlobalChildFrame.h"

class CDeuRasterFrame : public CDeuGlobalChildFrame
{
	DECLARE_DYNCREATE(CDeuRasterFrame)
public:
	CDeuRasterFrame();           // 动态创建所使用的受保护的构造函数
	virtual ~CDeuRasterFrame(); 

protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	CXTPDockingPaneManager PanelManager;
	CXTPDockingPane *p_panel;
	CDeuPaneRaster m_PaneRaster;
};


