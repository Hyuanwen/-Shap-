// MainFrm.cpp : CDeuGlobalMainFrame 类的实现
//

#include "stdafx.h"
#include "DeuGlobal.h"
#include "DeuGlobalMainFrm.h"
#include "DeuGlobalChildFrame.h"
#include "DeuRasterFrame.h"
#include "DeuVectorFrame.h"
#include "DeuViewerFrm.h"
#include "DeuViewerDoc.h"
#include "DeuViewView.h"
#include "DeuDlgUsers.h"
#include "DeuDlgUserGroups.h"

#ifdef _DEBUG
	#define new DEBUG_NEW
#endif

// CDeuGlobalMainFrame
IMPLEMENT_DYNAMIC(CDeuGlobalMainFrame, CXTPMDIFrameWnd)
BEGIN_MESSAGE_MAP(CDeuGlobalMainFrame, CXTPMDIFrameWnd)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_MESSAGE(XTPWM_DOCKINGPANE_NOTIFY, OnDockingPaneNotify)
	ON_MESSAGE(WM_VEC_MSGPANEL, OnShowTranResult)
	ON_XTP_CREATECONTROL()

	ON_COMMAND(ID_ZOOM_OUT, ViewZoomOut)
	ON_COMMAND(ID_ZOOM_IN, ViewZoomIn)
	ON_COMMAND(ID_PREV, ViewPrve)
	ON_COMMAND(ID_LAST, ViewLast)
	ON_COMMAND(ID_DEFAULTSTATE, ViewSetDefault)	
	ON_COMMAND(ID_GLOBAL, ViewZoomAll)
	ON_COMMAND(ID_HANDMOVE, ViewZoomMove)
	ON_COMMAND(ID_REMOVELAYOUT, OnShow)
	ON_COMMAND(ID_SELECT, ViewSelect)
	ON_COMMAND(ID_SELECTCANCEL, ViewSelectCancel)
	ON_COMMAND(ID_OVERLAP, ViewOverLap)
	ON_COMMAND(ID_OVERVIEW, ShowOverviewPanel)
	ON_COMMAND(ID_SOURCE, OnShowDataSource)
	ON_COMMAND(ID_ELLIPOSID, OnDefineElliposid)
	ON_COMMAND(ID_HORIZATOL, OnDefineHorizatol)
	ON_COMMAND(ID_LINEAR_UNIT, OnDefineLinear)
	ON_COMMAND(ID_TRAN_DEF, OnDefineTran)
	ON_COMMAND(ID_ANGULAR_UNIT, OnDefineAngular)	
	ON_COMMAND(ID_HELP, OnShow)
	ON_COMMAND(ID_ABOUT, OnShow)
	ON_COMMAND(ID_USERS, ShowUsersManager)
	ON_COMMAND(ID_USERGROUP, ShowUserGroupsManager)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,        
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

CDeuGlobalMainFrame::CDeuGlobalMainFrame()
{
	XTPSkinManager()->LoadSkin(GetStylesPath() + _T("\\Office2007.cjstyles"), _T("NormalBlack.ini"));	
}

CDeuGlobalMainFrame::~CDeuGlobalMainFrame()
{
}

int CDeuGlobalMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CXTPMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
	{
		return -1;
	}

	if (!m_wndStatusBar.Create(this) || !m_wndStatusBar.SetIndicators(indicators,sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1; 
	}

	//初始化Toolbar
	if (!InitCommandBars())
	{
		return -1;
	}
	
	CXTPPaintManager::SetTheme(xtpThemeOffice2003);	
	CXTPCommandBars* pCommandBars = GetCommandBars();
	if(pCommandBars == NULL)
	{
		TRACE0("Failed to create command bars object.\n");
		return -1;
	}
	 	
	// 创建菜单
	CXTPCommandBar* pMenuBar = pCommandBars->SetMenu(_T("Menu Bar"), IDR_DEU2000MENU);
	if(pMenuBar == NULL)
	{
		TRACE0("Failed to create menu bar.\n");
		return -1;
	}
	
	/*if(GobalUserInfo.strName != "Admin")
	{
		pMenuBar->GetControl(4)->SetHideFlags(xtpHideGeneric);
	}*/
	pMenuBar->SetFlags(xtpFlagUseMDIMenus);
	pMenuBar->SetShowGripper(FALSE);
	
	//region  创建Toolbar 
	CXTPToolBar* pToolBar = (CXTPToolBar*)pCommandBars->Add(_T("视图组"), xtpBarTop);
	if (!pToolBar || !pToolBar->LoadToolBar(IDR_TOOLBAR1))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}
	pToolBar->GetControl(8)->SetHideFlags(xtpHideGeneric);

	CXTPToolBar* pToolBar2 = (CXTPToolBar*)pCommandBars->Add(_T("数据源组"), xtpBarTop);
	if (!pToolBar2 || !pToolBar2->LoadToolBar(IDR_TOOLBAR2))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}
	
	CXTPToolBar* pTranToolBar = (CXTPToolBar*)pCommandBars->Add(_T("转换操作组"), xtpBarTop);
	if (!pTranToolBar || !pTranToolBar->LoadToolBar(IDR_TOOLBAR3))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}
	
	pToolBar->ShowExpandButton(FALSE);
	pToolBar2->ShowExpandButton(FALSE);
	pTranToolBar->ShowExpandButton(FALSE);

	DockRightOf(pToolBar2, pToolBar);
	DockRightOf(pTranToolBar, pToolBar2);

	//pCommandBars->GetImageManager()->SetIcons(IDR_TOOLBAR1, IDB_LARGEICON);
	//pCommandBars->GetCommandBarsOptions()->szLargeIcons = CSize(24, 24);
	//pCommandBars->GetCommandBarsOptions()->bLargeIcons = TRUE;
	pCommandBars->GetCommandBarsOptions()->bShowTextBelowIcons = TRUE;
	pCommandBars->GetCommandBarsOptions()->ShowKeyboardCues(xtpKeyboardCuesShowWindowsDefault);
	
	CXTPPaintManager::SetTheme((XTPPaintTheme)xtpThemeNativeWinXP);
	//GetCommandBars()->RedrawCommandBars();

	m_paneManager.InstallDockingPanes(this);
	m_paneManager.SetTheme(xtpPaneThemeDefault);

	//任务
	CXTPDockingPane* pwndTaskPane = m_paneManager.CreatePane(IDR_TASKPANE, CRect(0, 0,250, 120), xtpPaneDockLeft);

	//属性 alter by chenyong 屏蔽属性面板
	//CXTPDockingPane* pwndPropertiesPane = m_paneManager.CreatePane(IDR_PROPERTYPANE, CRect(0, 0,230, 200), xtpPaneDockBottom, pwndTaskPane);
	//pwndPropertiesPane->Hide();
	//pwndPropertiesPane->SetOptions(xtpPaneNoCaption|xtpPaneNoCloseable|xtpPaneNoHideable|xtpPaneNoFloatable|xtpPaneNoDockable);

	//数据栈
	//CXTPDockingPane* pwndStackPane = m_paneManager.CreatePane(IDR_STACKPANE, CRect(0, 0, 200, 200), xtpPaneDockBottom,pwndTaskPane);

	//alter by chenyong 
	//m_paneManager.AttachPane(pwndStackPane, pwndPropertiesPane);
	pwndTaskPane->Select();
	//pwndPropertiesPane->Select();

	//鹰眼面板
	pwndOverviewPane = m_paneManager.CreatePane(IDR_OVERVIEW, CRect(0, 0,200, 120), xtpPaneDockRight);

	//消息面板
	pwndMessagePane = m_paneManager.CreatePane(IDR_MESSAGEPANE, CRect(0, 0,200, 120), xtpPaneDockBottom);
	m_Edit_msg.CreateEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""),WS_CHILD|ES_AUTOVSCROLL|ES_MULTILINE|WS_VSCROLL, CRect(0, 0, 200, 120), this, 0);
	pwndMessagePane->Attach(&m_Edit_msg);
	pwndMessagePane->Hide();
	pwndOverviewPane->Hide();

	//设置面板图片 alter by chenyong 2013-4-3
	//int nIDs1[] = {IDR_PROPERTYPANE, IDR_TASKPANE, IDR_STACKPANE, IDR_OVERVIEW, IDR_MESSAGEPANE};
	//m_paneManager.SetIcons(IDB_BITMAP1, nIDs1, 5, RGB(0, 255, 0));

	//加载Toolbar对象
	LoadCommandBars(_T("CommandBars"));
	
	//CXTPPaintManager::SetTheme(xtpThemeWhidbey);
	m_paneManager.SetTheme(xtpPaneThemeVisualStudio2005);
	GetCommandBars()->RedrawCommandBars();
	m_paneManager.RedrawPanes();

	m_paneManager.SetAlphaDockingContext(TRUE);
	m_paneManager.SetShowDockingContextStickers(TRUE);
	m_paneManager.SetShowContentsWhileDragging(TRUE);
	//m_paneManager.SetDefaultPaneOptions(xtpPaneHasMenuButton);

	//创建客户区域
	//HICON m_hicon = AfxGetApp()->LoadIcon(IDI_ICON_VIEW);
	m_MTIClientWnd.Attach(this, TRUE);	
	m_MTIClientWnd.EnableToolTips();
	m_MTIClientWnd.GetPaintManager()->m_bShowIcons = FALSE;
	m_MTIClientWnd.GetPaintManager()->SetOneNoteColors(0);	
	m_MTIClientWnd.GetPaintManager()->m_clientFrame = xtpTabFrameSingleLine;
	m_MTIClientWnd.UpdateContents();
	m_MTIClientWnd.GetPaintManager()->RefreshMetrics();

	RedrawWindow( NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE | RDW_ALLCHILDREN);
	
	return 0;
}

BOOL CDeuGlobalMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CXTPMDIFrameWnd::PreCreateWindow(cs) )
	{
		return FALSE;
	}

	//cs.lpszClass = _T("XTPMainFrame");
	cs.lpszClass = _T("Deu2000");
	CXTPDrawHelpers::RegisterWndClass(AfxGetInstanceHandle(), cs.lpszClass, CS_DBLCLKS, AfxGetApp()->LoadIcon(IDR_MAINFRAME));

	return TRUE;
}

void CDeuGlobalMainFrame::OnClose()
{
	//释放内存，防止泄露
	CDeuXmlReader m_XmlReader;
	m_XmlReader.ReleaseGeoDataMapping(&GeoDataMapping);
	m_XmlReader.ReleseTaskMapping(&TasksMapping);

	if(AfxMessageBox("您确定要退出系统吗?",MB_OKCANCEL)==IDCANCEL)
	{
		return;
	}	

	CXTPMDIFrameWnd::OnClose();
}

void CDeuGlobalMainFrame::OnCustomize()
{
	CXTPCommandBars* pCommandBars = GetCommandBars();
	if (pCommandBars == NULL)
	{
		return;
	}

	CXTPCustomizeSheet dlg(pCommandBars);
	CXTPCustomizeOptionsPage pageOptions(&dlg);
	dlg.AddPage(&pageOptions);

	CXTPCustomizeCommandsPage* pPageCommands = dlg.GetCommandsPage();
	pPageCommands->AddCategories(IDR_TABMANTYPE);
	pPageCommands->InsertAllCommandsCategory();
	pPageCommands->InsertBuiltInMenus(IDR_TABMANTYPE);
	pPageCommands->InsertNewMenuCategory();

	dlg.DoModal();
}

LRESULT CDeuGlobalMainFrame::OnDockingPaneNotify(WPARAM wParam, LPARAM lParam)
{
	if (wParam == XTP_DPN_SHOWWINDOW)
	{
		CXTPDockingPane* pPane = (CXTPDockingPane*)lParam;
		if (!pPane->IsValid())
		{
			switch(pPane->GetID())
			{
			case IDR_TASKPANE:
				m_wndTaskPanel.Create(_T("STATIC"), NULL, WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS, CXTPEmptyRect(), this, 0);
				pPane->Attach(&m_wndTaskPanel);
				break;

			case IDR_PROPERTYPANE:
				m_Dlgpanel.Create(IDD_DLG_PROPERTY, this);
				pPane->Attach(&m_Dlgpanel);
				break;

			default: 
				int nIndex = pPane->GetID() - IDR_PROPERTYPANE;
				//int nIndex = 6;
				ASSERT(nIndex >=0 &&  nIndex < sizeof(m_wndPanes)/sizeof(m_wndPanes[0]));

				// create and attach the edit control for this pane.
				if (!::IsWindow(m_wndPanes[nIndex].m_hWnd))
				{
					if (!m_wndPanes[nIndex].CreateEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""),
						WS_CHILD|ES_AUTOVSCROLL|ES_MULTILINE, CRect(0, 0, 200, 120), this, 0))
					{
						TRACE0( "Error creating pane edit control.\n" );
					}
					//AdjustStyle(GetDockingPaneManager()->GetCurrentTheme());
				}

				pPane->Attach(&m_wndPanes[nIndex]);
				break;
			}
		}        

		return TRUE; // handled
	}
	return FALSE;
}

//以消息的形式 显示消息面板
LRESULT CDeuGlobalMainFrame::OnShowTranResult(WPARAM wParam, LPARAM lParam)
{
	CString m_str;
	m_str = (char *)lParam;

	//m_Edit_msg.SetWindowText("");
	pwndMessagePane->Select();

	CString m_StrLine;
	m_Edit_msg.GetWindowText(m_StrLine);
	m_StrLine += m_str+"\r\n";
	m_Edit_msg.SetWindowText(m_StrLine);
	m_Edit_msg.LineScroll(m_Edit_msg.GetLineCount());

	return 0;
}

int CDeuGlobalMainFrame::OnCreateControl(LPCREATECONTROLSTRUCT lpCreateControl)
{
	/*if (lpCreateControl->bToolBar)
	{
		CXTPToolBar* pToolBar = DYNAMIC_DOWNCAST(CXTPToolBar, lpCreateControl->pCommandBar);
		if (!pToolBar)
			return FALSE;

		if (lpCreateControl->nID == ID_VIEW_SWITCH_THEME)
		{
			lpCreateControl->controlType = xtpControlSplitButtonPopup;
			lpCreateControl->buttonStyle = xtpButtonIconAndCaption;
			return TRUE;
		}
		if (lpCreateControl->nID == ID_VIEW_PROPERTIES)
		{
			lpCreateControl->buttonStyle = xtpButtonIconAndCaption;
			return TRUE;
		}
	}*/

	return FALSE;
}

#ifdef _DEBUG
	void CDeuGlobalMainFrame::AssertValid() const
	{
		CXTPMDIFrameWnd::AssertValid();
	}

	void CDeuGlobalMainFrame::Dump(CDumpContext& dc) const
	{
		CXTPMDIFrameWnd::Dump(dc);
	}
#endif 

/*
=============================================   
 功能:	 鹰眼面板的显示
 参数:		---
 返回:		---
 程序逻辑:	---
 日期:	2011-01-04
 备注: add by hushichen
=============================================
*/ 
void CDeuGlobalMainFrame::ShowOverviewPanel()
{
	pwndOverviewPane->Select();
}

void CDeuGlobalMainFrame::ShowUsersManager()
{
	CDeuDlgUsers m_UserDlg;
	m_UserDlg.DoModal();
}

void CDeuGlobalMainFrame::ShowUserGroupsManager()
{
	CDeuDlgUserGroups m_UserGroupDlg;
	m_UserGroupDlg.DoModal();
}

void CDeuGlobalMainFrame::OnSetPreviewMode(BOOL bPreview, CPrintPreviewState* pState)
{
	GetCommandBars()->OnSetPreviewMode(bPreview);

	m_MTIClientWnd.ShowWorkspace(!bPreview);
	m_paneManager.OnSetPreviewMode(bPreview);
	CXTPMDIFrameWnd::OnSetPreviewMode(bPreview, pState);
}

void CDeuGlobalMainFrame::OnShow()
{
	/*if(m_Dlgpanel.GetSafeHwnd() == NULL){
		m_Dlgpanel.Create(IDD_DLG_PROPERTY, this);
		
	}
	m_Dlgpanel.ShowWindow(1);*/

	/*CDeuXmlReader m_XmlReader;
	_Tasks _tasks;
	m_XmlReader.LoadFile("G:\\Deu2000_Project\\Source\\bin\\TaskInfo.ini");
	m_XmlReader.GetTasks(&_tasks);

	CDeuXmlWriter m_writer;
	m_writer.BuildTaskXml("D:\\xx.xml", &_tasks);*/

	//m_dlg.MoveWindow(CXTPEmptyRect());
	//pPane->Attach(&m_dlg);
	//this->ShowMessagePane(FALSE, "sdfsfs");

	//this->SendMessage(WM_VEC_MSGPANEL, NULL, (LPARAM)"sfsfs");   
}

//放大
void CDeuGlobalMainFrame::ViewZoomIn()
{
	if(this->MDIGetActive() != NULL)
	{
		CDeuGlobalChildFrame* p_Child = (CDeuGlobalChildFrame*)this->MDIGetActive();
		
		//是否视图的操作
		if(strcmp(p_Child->sz_ModuleType, "IsView") == 0)
		{
			CDeuViewView* p_View = (CDeuViewView*)p_Child->GetActiveView();
			p_View->OnZoomIn();
		}
		else
		{
			::AfxMessageBox("请选择视图窗口");
		}
	}
}

//缩小
void CDeuGlobalMainFrame::ViewZoomOut()
{
	if(this->MDIGetActive() != NULL)
	{
		CDeuGlobalChildFrame* p_Child = (CDeuGlobalChildFrame*)this->MDIGetActive();

		//是否视图的操作
		if(strcmp(p_Child->sz_ModuleType, "IsView") == 0)
		{
			CDeuViewView* p_View = (CDeuViewView*)p_Child->GetActiveView();
			p_View->OnZoomOut();
		}
		else
		{
			::AfxMessageBox("请选择视图窗口");
		}
	}
}

//移动或叫漫游
void CDeuGlobalMainFrame::ViewZoomMove()
{
	if(this->MDIGetActive() != NULL)
	{
		CDeuGlobalChildFrame* p_Child = (CDeuGlobalChildFrame*)this->MDIGetActive();

		//是否视图的操作
		if(strcmp(p_Child->sz_ModuleType, "IsView") == 0)
		{
			CDeuViewView* p_View = (CDeuViewView*)p_Child->GetActiveView();
			p_View->OnZoomMove();
		}
		else
		{
			::AfxMessageBox("请选择视图窗口");
		}
	}
}

void CDeuGlobalMainFrame::ViewZoomAll()
{
	if(this->MDIGetActive() != NULL)
	{
		CDeuGlobalChildFrame* p_Child = (CDeuGlobalChildFrame*)this->MDIGetActive();

		//是否视图的操作
		if(strcmp(p_Child->sz_ModuleType, "IsView") == 0)
		{
			CDeuViewView* p_View = (CDeuViewView*)p_Child->GetActiveView();
			p_View->OnZoomAllPic();
		}
		else
		{
			::AfxMessageBox("请选择视图窗口");
		}
	}
}

void CDeuGlobalMainFrame::ViewSelect()
{
	//是否视图的操作
	if(this->MDIGetActive() != NULL)
	{
		CDeuGlobalChildFrame* p_Child = (CDeuGlobalChildFrame*)this->MDIGetActive();

		//是否视图的操作
		if(strcmp(p_Child->sz_ModuleType, "IsView") == 0)
		{
			CDeuViewView* p_View = (CDeuViewView*)p_Child->GetActiveView();
			p_View->OnSelect();
		}
		else
		{
			::AfxMessageBox("请选择视图窗口");
		}
	}
}

void CDeuGlobalMainFrame::ViewSelectCancel()
{
	//是否视图的操作
	if(this->MDIGetActive() != NULL)
	{
		CDeuGlobalChildFrame* p_Child = (CDeuGlobalChildFrame*)this->MDIGetActive();

		//是否视图的操作
		if(strcmp(p_Child->sz_ModuleType, "IsView") == 0)
		{
			CDeuViewView* p_View = (CDeuViewView*)p_Child->GetActiveView();
			p_View->OnSelectCancel();
		}
		else
		{
			::AfxMessageBox("请选择视图窗口");
		}
	}
}

void CDeuGlobalMainFrame::ViewClearLayers()
{
	//是否视图的操作
	if(this->MDIGetActive() != NULL)
	{
		CDeuGlobalChildFrame* p_Child = (CDeuGlobalChildFrame*)this->MDIGetActive();

		//是否视图的操作
		if(strcmp(p_Child->sz_ModuleType, "IsView") == 0)
		{
			CDeuViewView* p_View = (CDeuViewView*)p_Child->GetActiveView();
			p_View->OnClearLayers();
		}
		else
		{
			::AfxMessageBox("请选择视图窗口");
		}
	}
}

void CDeuGlobalMainFrame::ViewSetDefault()
{
	//是否视图的操作
	if(this->MDIGetActive() != NULL)
	{
		CDeuGlobalChildFrame* p_Child = (CDeuGlobalChildFrame*)this->MDIGetActive();

		//是否视图的操作
		if(strcmp(p_Child->sz_ModuleType, "IsView") == 0)
		{
			CDeuViewView* p_View = (CDeuViewView*)p_Child->GetActiveView();
			p_View->OnDefaultState();
		}
		else
		{
			::AfxMessageBox("请选择视图窗口");
		}
	}
}

void CDeuGlobalMainFrame::ViewOverLap()
{
	//是否视图的操作
	if(this->MDIGetActive() != NULL)
	{
		if((!GobalUserInfo.IsVectorView) && (!GobalUserInfo.IsRasterView))
		{
			MessageBox(PowerError, "系统提示", MB_OK|MB_ICONEXCLAMATION);
		}
		else
		{
			CDeuGlobalChildFrame* p_Child = (CDeuGlobalChildFrame*)this->MDIGetActive();
			//是否视图的操作
			if(strcmp(p_Child->sz_ModuleType, "IsView") == 0)
			{
				CString m_str;
				if(GobalUserInfo.IsVectorView && !GobalUserInfo.IsRasterView)
				{
					m_str = "Shapefile(*.shp)|*.shp|位图(*.bmp)|*.bmp|JPEG(*.jpg)|*.jpg|MapInfo(*.mif)|*.mif|MapInfo(*.tab)|*.tab|DXF(*.dxf)|*.dxf|AVCE00(*.e00)|*.e00||";
				}
				else if(GobalUserInfo.IsRasterView && !GobalUserInfo.IsVectorView)
				{
					m_str = "Gtiff(*.tif)|*.tif|HFA(*.img)|*.img|EHdr(*.bil)|*.bil|AAIGrid(*.asc)|*.asc|BMP(*.bmp)|.bmp||";			
				}
				else
				{
					m_str = "Shapefile(*.shp)|*.shp|位图(*.bmp)|*.bmp|JPEG(*.jpg)|*.jpg|MapInfo(*.mif)|*.mif|MapInfo(*.tab)|*.tab|DXF(*.dxf)|*.dxf|AVCE00(*.e00)|*.e00|Gtiff(*.tif)|*.tif|HFA(*.img)|*.img|EHdr(*.bil)|*.bil|AAIGrid(*.asc)|*.asc|BMP(*.bmp)|.bmp||";
				}

				CFileDialog m_FileDlg(true,"Shapefile", "*.shp",OFN_FILEMUSTEXIST|OFN_HIDEREADONLY, m_str, NULL);
				m_FileDlg.m_ofn.lpstrTitle = _T("打开视图文件");
				if(m_FileDlg.DoModal() == IDOK)
				{		
					CDeuViewView* p_View = (CDeuViewView*)p_Child->GetActiveView();
					p_View->OnZoomLoad(m_FileDlg.GetPathName());
				}
			}
			else
			{
				::AfxMessageBox("请选择视图窗口");
			}
		}
	}
}

void CDeuGlobalMainFrame::ViewPrve()
{

	//是否视图的操作
	if(this->MDIGetActive() != NULL)
	{
		CDeuGlobalChildFrame* p_Child = (CDeuGlobalChildFrame*)this->MDIGetActive();

		//是否视图的操作
		if(strcmp(p_Child->sz_ModuleType, "IsView") == 0)
		{
			CDeuViewView* p_View = (CDeuViewView*)p_Child->GetActiveView();
			p_View->OnZoomPre();
		}
		else
		{
			::AfxMessageBox("请选择视图窗口");
		}
	}
}

void CDeuGlobalMainFrame::ViewLast()
{
	//是否视图的操作
	if(this->MDIGetActive() != NULL)
	{
		CDeuGlobalChildFrame* p_Child = (CDeuGlobalChildFrame*)this->MDIGetActive();

		//是否视图的操作
		if(strcmp(p_Child->sz_ModuleType, "IsView") == 0)
		{
			CDeuViewView* p_View = (CDeuViewView*)p_Child->GetActiveView();
			p_View->OnZoomNext();
		}
		else
		{
			::AfxMessageBox("请选择视图窗口");
		}
	}
}

void CDeuGlobalMainFrame::OnDefineElliposid()
{
	//MessageBox("椭球定义");
}

void CDeuGlobalMainFrame::OnDefineHorizatol()
{
	//AfxMessageBox("水平基准定义");
}

void CDeuGlobalMainFrame::OnDefineTran()
{
	//AfxMessageBox("基准转换定义");
}

void CDeuGlobalMainFrame::OnDefineLinear()
{
	//AfxMessageBox("长度基准定义");
}

void CDeuGlobalMainFrame::OnDefineAngular()
{
	//AfxMessageBox("角度单位定义");
}

//显示数据源
void CDeuGlobalMainFrame::OnShowDataSource()
{
	/*if(!m_DataSrcCustomDlg.GetSafeHwnd())
	{
		m_DataSrcCustomDlg.Create(IDD_DLG_SOURCE_CUSTOM, this);
	}*/

//	CDeuDlgDataSrcCustom m_DataSrcCustomDlg;
//	m_DataSrcCustomDlg.DoModal();


    CDeuDlgEllipManager m_DataSrcDlg;
	m_DataSrcDlg.m_bManager = TRUE;
	m_DataSrcDlg.DoModal();
	
	//m_DataSrcCustomDlg.ShowWindow(SW_SHOW);
}

//函数形式 显示消息面板
void CDeuGlobalMainFrame::ShowMessagePane(BOOL IsClear, CString m_str)
{	
	if(IsClear) 
	{
		m_Edit_msg.SetWindowText("");
	}
	pwndMessagePane->Select();

	CString m_StrLine;
	m_Edit_msg.GetWindowText(m_StrLine);
	m_StrLine += m_str+"\r\n";	
	m_Edit_msg.SetWindowText(m_StrLine);
	m_Edit_msg.LineScroll(m_Edit_msg.GetLineCount());
}