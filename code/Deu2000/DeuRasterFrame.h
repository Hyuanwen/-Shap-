#pragma once

#include "DeuPaneRaster.h"
#include "DeuGlobalChildFrame.h"

class CDeuRasterFrame : public CDeuGlobalChildFrame
{
	DECLARE_DYNCREATE(CDeuRasterFrame)
public:
	CDeuRasterFrame();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CDeuRasterFrame(); 

protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	CXTPDockingPaneManager PanelManager;
	CXTPDockingPane *p_panel;
	CDeuPaneRaster m_PaneRaster;
};


