// DeuTabControl.cpp : 实现文件

#include "stdafx.h"
#include "DeuTabControl.h"
#include "DeuPaneVector.h"
#include "DeuPaneRaster.h"

// CDeuTabControl
IMPLEMENT_DYNAMIC(CDeuTabControl, CXTPTabControl)
CDeuTabControl::CDeuTabControl()
{
	lstrcpy(sz_Type, "");
}

CDeuTabControl::~CDeuTabControl()
{
}

BEGIN_MESSAGE_MAP(CDeuTabControl, CXTPTabControl)
END_MESSAGE_MAP()
#include "DeuPaneVectorProject.h"
// CDeuTabControl 消息处理程序
void CDeuTabControl::OnNavigateButtonClick(CXTPTabManagerNavigateButton* pButton)
{
	if(strcmp(sz_Type, "Vector") == 0)
	{		
		CDeuPaneVector* p_Vector = (CDeuPaneVector*)pPanelWnd;
		p_Vector->DelTaskItem(this->GetSelectedItem()->GetIndex());
	}
	else if(strcmp(sz_Type, "VectorPrj") == 0)
	{
		CDeuPaneVectorProject* p_Vector1 = (CDeuPaneVectorProject*)pPanelWnd;
		p_Vector1->DelTaskItem(this->GetSelectedItem()->GetIndex());
	}
	else if(strcmp(sz_Type, "Raster") == 0)
	{
		CDeuPaneRaster* p_Raster = (CDeuPaneRaster*)pPanelWnd;
		p_Raster->DelTaskItem(this->GetSelectedItem()->GetIndex());
	}
}



