// DeuDlgContainer.cpp : 实现文件
//

#include "stdafx.h"
#include "Deu2000.h"
#include "DeuDlgContainer.h"
#include "DeuDlgSingle.h"

#include "DeuData.h"

#include "DeuDataView.h"
#include "DeuRasterTrans.h"
#include "DeuDataTransform.h"


// CDeuDlgContainer 对话框

IMPLEMENT_DYNAMIC(CDeuDlgContainer, CBCGPDialog)

CDeuDlgContainer::CDeuDlgContainer(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CDeuDlgContainer::IDD, pParent)
{
	EnableVisualManagerStyle();
}

CDeuDlgContainer::~CDeuDlgContainer()
{
}

void CDeuDlgContainer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDeuDlgContainer, CBCGPDialog)
	ON_WM_SIZE()
	ON_WM_VSCROLL()
END_MESSAGE_MAP()


// CDeuDlgContainer 消息处理程序

BOOL CDeuDlgContainer::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	CBCGPVisualManager::SetDefaultManager(RUNTIME_CLASS (CBCGPVisualManagerVS2005));

	CRect m_rect;
	this->GetClientRect(&m_rect);
	m_rect.top	= m_rect.top;
	m_rect.left = m_rect.left;
	m_rect.right = m_rect.right;
	m_rect.bottom = m_rect.bottom;

	m_DeuTab.Create(CBCGPTabWnd::STYLE_3D_VS2005, m_rect, this, IDC_TAB1, CBCGPTabWnd::LOCATION_TOP);
	m_DeuTab.SetActiveTabBoldFont();
	m_DeuTab.EnableActiveTabCloseButton(TRUE);
	m_DeuTab.EnableTabDocumentsMenu(TRUE);
	
	//m_DeuTab.ShowScrollBar(1);
	//m_DeuTab.SetFlatFrame(FALSE);
	m_DeuTab.m_bActivateTabOnRightClick = false;


	m_DeuTab.SetImageList(IDB_NULL,2, RGB (255, 0, 255));
	

	/*m_DeuTab.GetClientRect(&m_rect);
	CDeuDlgTest *m_dlgTest = new CDeuDlgTest;
	m_dlgTest->Create(IDD_DIALOG_TEST, &m_DeuTab);
	m_dlgTest->SetWindowPos(&wndTop,m_rect.left, m_rect.top, m_rect.Width()+50, m_rect.Height(), SWP_SHOWWINDOW);	
	m_DeuTab.InsertTabs(m_dlgTest, "视 图   ");	*/

	CRect rct;
	GetClientRect(&rct);
	//this->ShowScrollBar(SB_VERT);
	//this->SetScrollRange(SB_VERT, rct.top, 10);
	
	InitExistTask();

	UpdateData (FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDeuDlgContainer::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	if(m_DeuTab.m_hWnd != NULL)
	{
		CRect m_rect;

		this->GetClientRect(&m_rect);

		this->m_DeuTab.MoveWindow(0, 0, m_rect.Width(), m_rect.Height());
	}
}


/*----------------------------------------------------------------*/


/* 单转 */
void CDeuDlgContainer::AddTabForSingle()
{
	CRect m_rect;
	m_DeuTab.GetClientRect(&m_rect);
	int width = m_rect.Width()+50;

	CDeuDlgSingle *m_DlgSingle = new CDeuDlgSingle;
	m_DlgSingle->Create(IDD_DIALOG_SINGLE, &m_DeuTab);
	//m_test->SetWindowPos(&wndTop, m_rect.left, m_rect.top, 100, m_rect.Height(), SWP_SHOWWINDOW);

	m_DeuTab.InsertTabs(m_DlgSingle, "单转 ");

}


/*----------------------------------------------------------------*/


/* 批转 */
void CDeuDlgContainer::AddTabForBatRechange()
{

}



/*----------------------------------------------------------------*/

/* 增加视图 */
void CDeuDlgContainer::AddTabForView()
{
	CRect m_rect;
	m_DeuTab.GetClientRect(&m_rect);
	CDeuDataView *m_DlgView = new CDeuDataView;

	m_DlgView->Create(IDD_DATA_VIEW, &m_DeuTab);
	m_DlgView->SetWindowPos(&wndTop,m_rect.left, m_rect.top, m_rect.Width(), m_rect.Height(), SWP_SHOWWINDOW);

	//将窗口指针装入容器
	CDeuData *pDeuData = DEUMAINFRM.m_deuData;
	pDeuData->vecView.Add(m_DlgView);

	//记录容器索引
	m_DlgView->OrderIndex = pDeuData->vecView.GetCount()-1;
			
	m_DeuTab.InsertTabs(m_DlgView, "视图 ");

	ResetTabOrder();
}


/* 删除视图 */
void CDeuDlgContainer::DelTabForView(int _Index)
{

	CDeuData *pDeuData = DEUMAINFRM.m_deuData;
	if(_Index < pDeuData->vecView.GetCount())
	{
		pDeuData->vecView.RemoveAt(_Index);			//移除容器中的对象
	}

	for(int n=0; n<pDeuData->vecView.GetCount(); n++)
	{
		pDeuData->vecView.GetAt(n)->OrderIndex = n;
	}

	ResetTabOrder();
	
}



/*----------------------------------------------------------------*/


/* 增加栅格 */
void CDeuDlgContainer::AddTabForRaster(TreeData* p_treedata)
{
	CRect m_rect;
	m_DeuTab.GetClientRect(&m_rect);
	CDeuRasterTrans *m_DlgRaster = new CDeuRasterTrans;

	m_DlgRaster->Create(IDD_DATA_RASTERTRANS, &m_DeuTab);
	m_DlgRaster->SetWindowPos(&wndTop,m_rect.left, m_rect.top, m_rect.Width(), m_rect.Height(), SWP_SHOWWINDOW);


	//将窗口指针装入容器
	CDeuData *pDeuData = DEUMAINFRM.m_deuData;
	pDeuData->vecRaster.Add(m_DlgRaster);

	//记录容器索引
	m_DlgRaster->OrderIndex = pDeuData->vecRaster.GetCount();
	m_DlgRaster->GlobalIndex = m_DeuTab.GetTabsNum();


	p_treedata->p1	 = m_DlgRaster;
	p_treedata->type = TIF_TASK;

	CString strname;
	strname.Format("栅格转换%d ", m_DlgRaster->OrderIndex);
	m_DeuTab.InsertTabs(m_DlgRaster, strname);

	ResetRasterAyOrder();
	ResetTabOrder();

}




/* 删除栅格 */
void CDeuDlgContainer::DelTabForRaster(int _Index)
{
	CDeuData *pDeuData = DEUMAINFRM.m_deuData;
	if(_Index < pDeuData->vecRaster.GetCount())
	{
		pDeuData->vecRaster.RemoveAt(_Index); //移除容器中的对象
	}
		//DEUMAINFRM.m_wndProject.m_dlgTreeTask.ResetTree();

	this->ResetTree();

	ResetVectorAyOrder();
	ResetTabOrder();
	
}


/*----------------------------------------------------------------*/


/*
=============================================   
功能:		增加矢量
参数:		索引			
程序逻辑:	
			删除操作不仅要更新tab索引，容器索引，
			还要更新数据的节点数据显示

=============================================
*/
void CDeuDlgContainer::AddTabForVector(TreeData* p_treedata)
{
	CRect m_rect;
	m_DeuTab.GetClientRect(&m_rect);
	
	CDeuDataTransform *pTrans = new CDeuDataTransform;
	pTrans->Create(IDD_DATA_TRANSFORM, &m_DeuTab);
	pTrans->SetWindowPos(&wndTop,m_rect.left, m_rect.top, m_rect.Width(), m_rect.Height(), SWP_SHOWWINDOW);

	/*  */
	CDeuData *pDeuData = DEUMAINFRM.m_deuData;
	pDeuData->vecVector.Add(pTrans);

	//记录容器索引
	pTrans->OrderIndex = pDeuData->vecVector.GetCount();
	pTrans->GlobalIndex = m_DeuTab.GetTabsNum();


	p_treedata->p1	 = pTrans;
	p_treedata->type = VEC_TASK;

	CString strname;
	strname.Format("矢量转换%d ", pTrans->OrderIndex);
	m_DeuTab.InsertTabs(pTrans, strname);

	ResetVectorAyOrder();
	ResetTabOrder();

}


/*
=============================================   
功能:		删除矢量
参数:		索引			
程序逻辑:	
			删除操作不仅要更新tab索引，容器索引，
			还要更新数据的节点数据显示

=============================================
*/
void CDeuDlgContainer::DelTabForVector(int _Index)
{		
	CDeuData *pDeuData = DEUMAINFRM.m_deuData;
	if(_Index < pDeuData->vecVector.GetCount())
	{
		pDeuData->vecVector.RemoveAt(_Index);	
	}

	this->ResetTree();

	ResetVectorAyOrder();
	ResetTabOrder();
}


void CDeuDlgContainer::ResetTabOrder() 
{
	for(int n=0; n<this->m_DeuTab.GetTabsNum(); n++)
	{
		CDeuDialog* p_tmpdlg = (CDeuDialog*)m_DeuTab.GetTabWnd(n);
		p_tmpdlg->GlobalIndex = n;
	}
}



//更新矢量容器中子窗口的容器索引值
void CDeuDlgContainer::ResetVectorAyOrder()
{
	for(int n=0; n< DEUMAINFRM.m_deuData->vecVector.GetCount(); n++)
	{
		DEUMAINFRM.m_deuData->vecVector.GetAt(n)->OrderIndex = n;
	}
}




//更新栅格容器中子窗口的容器索引值
void CDeuDlgContainer::ResetRasterAyOrder()
{
	for(int n=0; n< DEUMAINFRM.m_deuData->vecRaster.GetCount(); n++)
	{
		DEUMAINFRM.m_deuData->vecRaster.GetAt(n)->OrderIndex = n;
	}
}



//一不做，二不休，重新加载控件树的数据
void CDeuDlgContainer::ResetTree()
{
	CDeuTreeCtrl &p_tree = DEUMAINFRM.m_wndProject.m_dlgTreeTask.m_Tree;
	p_tree.DeleteAllItems();
		
	DEUMAINFRM.m_wndProject.m_dlgTreeTask.hRoot1 = p_tree.InsertItem (_T("项目"), TVI_ROOT);	
	DEUMAINFRM.m_wndProject.m_dlgTreeTask.hVecParent = p_tree.InsertItem (_T("矢量"), DEUMAINFRM.m_wndProject.m_dlgTreeTask.hRoot1);
	DEUMAINFRM.m_wndProject.m_dlgTreeTask.hRasterParent = p_tree.InsertItem (_T("栅格"), DEUMAINFRM.m_wndProject.m_dlgTreeTask.hRoot1);	

	CString strLabel;
	for(int n=0; n<DEUMAINFRM.m_deuData->vecVector.GetCount(); n++)
	{
		for(int m =0; m<m_DeuTab.GetTabsNum(); m++)
		{
			CDeuDialog* p_deudialog = (CDeuDialog*)DEUMAINFRM.m_deuData->vecVector.GetAt(n);
			if(p_deudialog == (CDeuDialog*)m_DeuTab.GetTabWnd(m))
			{
				m_DeuTab.GetTabLabel(m, strLabel);
				p_tree.InsertItem(strLabel, DEUMAINFRM.m_wndProject.m_dlgTreeTask.hVecParent);
			}
		}
	}

	for(int n=0; n<DEUMAINFRM.m_deuData->vecRaster.GetCount(); n++)
	{
		for(int m =0; m<m_DeuTab.GetTabsNum(); m++)
		{
			CDeuDialog* p_deudialog = (CDeuDialog*)DEUMAINFRM.m_deuData->vecRaster.GetAt(n);
			if(p_deudialog == (CDeuDialog*)m_DeuTab.GetTabWnd(m))
			{
				m_DeuTab.GetTabLabel(m, strLabel);
				p_tree.InsertItem(strLabel, DEUMAINFRM.m_wndProject.m_dlgTreeTask.hRasterParent);
			}
		}
	}

	p_tree.Expand(DEUMAINFRM.m_wndProject.m_dlgTreeTask.hRoot1, TVE_EXPAND);
	p_tree.Expand(DEUMAINFRM.m_wndProject.m_dlgTreeTask.hVecParent, TVE_EXPAND);
	p_tree.Expand(DEUMAINFRM.m_wndProject.m_dlgTreeTask.hRasterParent, TVE_EXPAND);

}
void CDeuDlgContainer::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	
	//this->SetScrollPos(SB_VERT, nPos);
	//SCROLLINFO scrollinfo;  
	//GetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL);  
	//switch (nSBCode)  
	//{  
	//case SB_BOTTOM:  
	//	ScrollWindow(0,(scrollinfo.nPos-scrollinfo.nMax)*10);  
	//	scrollinfo.nPos = scrollinfo.nMax;  
	//	SetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL);  
	//	break;  
	//case SB_TOP:  
	//	ScrollWindow(0,(scrollinfo.nPos-scrollinfo.nMin)*10);  
	//	scrollinfo.nPos = scrollinfo.nMin;  
	//	SetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL);  
	//	break;  
	//case SB_LINEUP:  
	//	scrollinfo.nPos -= 1;  
	//	if (scrollinfo.nPos){  
	//		scrollinfo.nPos = scrollinfo.nMin;  
	//		break;  
	//	}  
	//	SetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL);  
	//	ScrollWindow(0,10);  
	//	break;  
	//case SB_LINEDOWN:  
	//	scrollinfo.nPos += 1;  
	//	if (scrollinfo.nPos>scrollinfo.nMax)  
	//	{  
	//		scrollinfo.nPos = scrollinfo.nMax;  
	//		break;  
	//	}  
	//	SetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL);  
	//	ScrollWindow(0,-10);  
	//	break;  
	//case SB_PAGEUP:  
	//	scrollinfo.nPos -= 5;  
	//	if (scrollinfo.nPos){  
	//		scrollinfo.nPos = scrollinfo.nMin;  
	//		break;  
	//	}  
	//	SetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL);  
	//	ScrollWindow(0,10*5);  
	//	break;  
	//case SB_PAGEDOWN:  
	//	scrollinfo.nPos += 5;  
	//	if (scrollinfo.nPos>scrollinfo.nMax)  
	//	{  
	//		scrollinfo.nPos = scrollinfo.nMax;  
	//		break;  
	//	}  
	//	SetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL);  
	//	ScrollWindow(0,-10*5);  
	//	break;  
	//case SB_ENDSCROLL:  
	//	// MessageBox("SB_ENDSCROLL");  
	//	break;  
	//case SB_THUMBPOSITION:  
	//	// ScrollWindow(0,(scrollinfo.nPos-nPos)*10);  
	//	// scrollinfo.nPos = nPos;  
	//	// SetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL);  
	//	break;  
	//case SB_THUMBTRACK:  
	//	ScrollWindow(0,(scrollinfo.nPos-nPos)*10);  
	//	scrollinfo.nPos = nPos;  
	//	SetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL);  
	//	break;  
	//}  

	CBCGPDialog::OnVScroll(nSBCode, nPos, pScrollBar);

}


//
void CDeuDlgContainer::InitExistTask()
{
	for(int n=0; n<DEUMAINFRM.m_deuData->vecVector.GetCount(); n++)
	{
		CDeuDataTransform * p_vector = (CDeuDataTransform *)DEUMAINFRM.m_deuData->vecVector.GetAt(n);
		CString strlabel;
		strlabel.Format("矢量转换%d", n);
		p_vector->Create(IDD_DATA_TRANSFORM, &m_DeuTab);
		//记录容器索引
		p_vector->OrderIndex = n;
		p_vector->GlobalIndex = m_DeuTab.GetTabsNum();


		this->m_DeuTab.InsertTabs(p_vector, strlabel);
	}

	for(int n=0; n<DEUMAINFRM.m_deuData->vecRaster.GetCount(); n++)
	{

		CDeuRasterTrans * p_Raster = (CDeuRasterTrans *)DEUMAINFRM.m_deuData->vecRaster.GetAt(n);
		CString strlabel;
		strlabel.Format("矢量转换%d", n);
		p_Raster->Create(IDD_DATA_RASTERTRANS, &m_DeuTab);
		p_Raster->OrderIndex = n;
		p_Raster->GlobalIndex = m_DeuTab.GetTabsNum();

		this->m_DeuTab.InsertTabs(p_Raster, strlabel);

	}


	//ResetVectorAyOrder();
	//ResetRasterAyOrder();
	//ResetTabOrder();

	return;
}