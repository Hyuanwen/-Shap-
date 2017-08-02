#pragma once

#include "resource.h"
#include "DeuPaneVectorProject.h"
#include "DeuGlobalChildFrame.h"

class CDeuVectorProjectFrame : public CDeuGlobalChildFrame
{
	DECLARE_DYNCREATE(CDeuVectorProjectFrame)

public:
	CDeuVectorProjectFrame();           // 动态创建所使用的受保护的构造函数
	virtual ~CDeuVectorProjectFrame();

protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	CXTPDockingPaneManager m_paneManager;
	CDeuPaneVectorProject m_PaneVectorProject;
};


