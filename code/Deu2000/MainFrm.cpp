// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Deu2000.h"

#include "MainFrm.h"
#include "DeuReadFile.h"
#include <map>
#include <algorithm> 
#include "DeuPertySheet.h"
#include "Deu2000Doc.h"
#include "Deu2000View.h"
#include "DeuData.h"
#include "Deu2000Task.h"
//#include "DeuDataView.h"
#include "DeuDataTransform.h"
#include "DeuRasterTrans.h"
#include "DeuFileTransform.h"

#include "DeuEditSource.h"
#include "DeuTask.h"

/* 用户管理对话框 */
#include "DeuDlgUsers.h"

/* 用户组管理对话框 */
#include "DeuDlgUsersGroup.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CBCGPFrameWnd)

CDeu2000Task *		g_Task2000;
IDeuConnPool *		g_ConnPool;
P_LIST(CDeuTask*)	g_lisTask; 

const int  iMaxUserToolbars		= 10;
const UINT uiFirstUserToolBarId	= AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId	= uiFirstUserToolBarId + iMaxUserToolbars - 1;

#define ID_WIN32DLL1 40009
#define ID_COMMAND_PLUG_MIN 40001
#define ID_COMMAND_PLUG_MAX 50001

BOOL g_ThreadFinished; 


BEGIN_MESSAGE_MAP(CMainFrame, CBCGPFrameWnd)
	ON_WM_CREATE()
	ON_WM_MENUSELECT()

	ON_COMMAND(ID_NEW_VIEW, OnNewView)
	ON_COMMAND(ID_NEW_VECTOR, OnNewVector)	
	ON_COMMAND(ID_NEW_RASTER, OnNewRaster)
	ON_COMMAND(ID_NEW_VIEW_M, OnNewView)
	ON_COMMAND(ID_NEW_VECTOR_M,OnNewVector)	
	ON_COMMAND(ID_NEW_RASTER_M,  OnNewRaster)	


	ON_COMMAND(ID_NEW_SIGLECONVERSION, OnSingleRechange)
	ON_COMMAND(ID_NEW_BATCONVERSION,  OnBatRechange)

	//////////////////////////////////////////////////////////////////////////
	//曹欣
	//ON_COMMAND(ID_NEW_FILETRANS, OnNewFileTrans)
	//////////////////////////////////////////////////////////////////////////
	ON_COMMAND(ID_VIEW_CUSTOMIZE, OnViewCustomize)
	ON_REGISTERED_MESSAGE(BCGM_RESETTOOLBAR, OnToolbarReset)
	ON_REGISTERED_MESSAGE(BCGM_CUSTOMIZEHELP, OnHelpCustomizeToolbars)
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_2000, ID_VIEW_APPLOOK_2007, OnAppLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_2000, ID_VIEW_APPLOOK_2007, OnUpdateAppLook)
	ON_COMMAND(ID_VIEW_ADDMENU, &CMainFrame::OnViewAddmenu)
	//////////////////////////////////////////////////////////////////////////
	ON_WM_ACTIVATE()
	//
	ON_COMMAND(ID_WIN32DLL1, On_WIN32DLL1)
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_2000, ID_VIEW_APPLOOK_2007, OnAppLook)
	
	ON_COMMAND(ID_MSG_WND, &CMainFrame::OnMsgWnd)
	ON_COMMAND(ID_PRJ_WND, &CMainFrame::OnPrjWnd)
	ON_COMMAND(ID_DATA_WND, &CMainFrame::OnDataWnd)

	ON_COMMAND(ID_MSG_WND_M, &CMainFrame::OnMsgWnd)
	ON_COMMAND(ID_PRJ_WND_M, &CMainFrame::OnPrjWnd)
	ON_COMMAND(ID_DATA_WND_M, &CMainFrame::OnDataWnd)
	
	ON_UPDATE_COMMAND_UI(ID_MSG_WND_M,&CMainFrame::OnMsgWndUI)
	ON_UPDATE_COMMAND_UI(ID_PRJ_WND_M,&CMainFrame::OnPrjWndUI)
	ON_UPDATE_COMMAND_UI(ID_DATA_WND_M,&CMainFrame::OnDataWndUI)

	//视图
    ON_COMMAND(ID_TOOL_ADD, &CMainFrame::OnAddData)
	ON_COMMAND(ID_TOOL_ZOOMIN, &CMainFrame::OnZoomIn)
	ON_COMMAND(ID_TOOL_ZOOMOUT, &CMainFrame::OnZoomOut)
	ON_COMMAND(ID_TOOL_PAN, &CMainFrame::OnPan)
	ON_COMMAND(ID_TOOL_ZOOMTOVISIABLEEXTENTS, &CMainFrame::OnFullMap)
	ON_COMMAND(ID_TOOL_PREVIEW, &CMainFrame::OnZoomToPrev)
	ON_COMMAND(ID_TOOL_NEXTVIEW, &CMainFrame::OnZoomToNext)
	ON_COMMAND(ID_TOOL_SELECT, &CMainFrame::OnSelect)
	ON_COMMAND(ID_TOOL_REMOVESELECTIONS, &CMainFrame::OnRemoveSelections)
	ON_COMMAND(ID_TOOL_NONE, &CMainFrame::OnNone)
	ON_COMMAND(ID_TOOL_REMOVELAYERS, &CMainFrame::OnRemoveLayers)

	//ON_UPDATE_COMMAND_UI(ID_MSG_WND,&CMainFrame::OnMsgWndUI)
	//ON_UPDATE_COMMAND_UI(ID_PRJ_WND,&CMainFrame::OnPrjWndUI)
	//ON_UPDATE_COMMAND_UI(ID_DATA_WND,&CMainFrame::OnDataWndUI)

	ON_COMMAND(ID_CS_DEF_M,&CMainFrame::OnCSDef)
	ON_COMMAND(ID_DATUM_DEF,&CMainFrame::OnDatumDef)
	ON_COMMAND(ID_DATUM_TRAN_DEF,&CMainFrame::OnDatumTranDef)
	ON_COMMAND(ID_LEN_DEF,&CMainFrame::OnLenDef)
	ON_COMMAND(ID_ELL_DEF,&CMainFrame::OnEllDef)
	ON_COMMAND(ID_ANG_DEF,&CMainFrame::OnAngDef)

	ON_COMMAND(ID_CS_DEF,&CMainFrame::OnCSDef)

	ON_WM_GETMINMAXINFO()
		
	ON_COMMAND(ID_Coord_WND_M, &CMainFrame::OnCoordWndM)
	ON_UPDATE_COMMAND_UI(ID_Coord_WND_M, &CMainFrame::OnUpdateCoordWndM)
	ON_COMMAND(ID_Cursor_WND_M, &CMainFrame::OnCursorWndM)
	ON_UPDATE_COMMAND_UI(ID_Cursor_WND_M, &CMainFrame::OnUpdateCursorWndM)
	ON_COMMAND(ID_Eye_WND_M, &CMainFrame::OnEyeWndM)
	ON_UPDATE_COMMAND_UI(ID_Eye_WND_M, &CMainFrame::OnUpdateEyeWndM)
	ON_COMMAND(ID_Fts_WND_M, &CMainFrame::OnFtsWndM)
	ON_UPDATE_COMMAND_UI(ID_Fts_WND_M, &CMainFrame::OnUpdateFtsWndM)
	//ON_COMMAND(ID_TOOL_ZOOMIN, &CMainFrame::OnTOOLZOOMIN)
	ON_UPDATE_COMMAND_UI(ID_TOOL_ZOOMIN, &CMainFrame::OnUpdateToolZoomIn)
	ON_UPDATE_COMMAND_UI(ID_TOOL_ZOOMOUT, &CMainFrame::OnUpdateToolZoomOut)
	ON_UPDATE_COMMAND_UI(ID_TOOL_PAN, &CMainFrame::OnUpdateToolPan)
	ON_UPDATE_COMMAND_UI(ID_TOOL_SELECT, &CMainFrame::OnUpdateToolSelectFeature)
	ON_UPDATE_COMMAND_UI(ID_TOOL_NONE, &CMainFrame::OnUpdateToolNone)
	ON_UPDATE_COMMAND_UI(ID_TOOL_REMOVELAYERS, &CMainFrame::OnUpdateToolRemoveAllLayers)
	ON_COMMAND(ID_USERSMANAGER, &CMainFrame::OnMenuUsersManager)
	ON_COMMAND(ID_USERSGROUP, &CMainFrame::OnMenuUsersGroup)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

class   map_find_func   { 
public:
	map_find_func(UINT MenuId):m_MenuId(MenuId){}

protected:
	UINT m_MenuId;

public: 
	bool   operator()(   const   std::map<int,void*>::value_type   &   arg ) 
	{ 
		if   (   arg.first   ==   m_MenuId   )   return   true; 
		return   false; 
	} 
};

class CDeuSize : public CSize
{
public:
	CDeuSize(UINT nCx,UINT nCy):cx(nCx),cy(nCy){}

private:
	UINT cx;
	UINT cy;

public:

	void copy(const CSize& src)
	{  
		cx = src.cx;
		cy = src.cy;
	}

	const CDeuSize& operator=(const CSize& src)
	{
		copy(src);
		return *this;
	}
};

// CMainFrame construction/destruction

CMainFrame::CMainFrame():m_HasLoadPlugins(false)
{

#if 1
	m_nAppLook = theApp.GetInt (_T("ApplicationLook"), ID_VIEW_APPLOOK_2003);
#endif
	// TODO: add member initialization code here	

	for (int i = _TOOL_ADD ; i < _TOOL_REMOVELAYERS + 1 ; i++ )
	{
		btnViewCheck[i] = 0;
	}

	g_ThreadFinished = TRUE ;
}

CMainFrame::~CMainFrame()
{
	delete g_Task2000;
	delete m_deuData;
	delete m_Msg;
}

void CMainFrame::On_WIN32DLL1()
{
	HINSTANCE hINS = m_vecPluginHandles[1];
#define WM_DEUCOMMAND  0x0601
	//::SendMessage(hwnd,WM_DEUCOMMAND,0,ID_WIN32DLL1);

	typedef void (WINAPI * On_DLL)(void*);

	On_DLL lpproc;
	lpproc = (On_DLL)GetProcAddress (hINS,"Show");

	void* pCtrl = (void*)  m_vecDockCtrlBar[0];

	if(lpproc!=(On_DLL)NULL)
		(*lpproc)(pCtrl);
	
	//((COutputBar*)pCtrl)->m_wndList.SetBkColor(RGB(255,100,50)) ;
	//((COutputBar*)pCtrl)->RedrawWindow();
}

void CMainFrame::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	if(!m_HasLoadPlugins)
	{
		m_HasLoadPlugins=true;
		//加载插件
		//LoadPlugins();
		
	}

	return;
}


void CMainFrame::OnMenuSelect(UINT nItemID, UINT nFlags, HMENU hSysMenu)
{
	return CFrameWnd::OnMenuSelect(nItemID, nFlags, hSysMenu);
	//CMenu* pMenu = DYNAMIC_DOWNCAST(CMenu, (CObject*)hSysMenu);
	//TRACE("OnMenuSelect, hSysMenu=%p is %s\n", hSysMenu,
	//	::IsMenu(hSysMenu) ? "HMENU" : pMenu ? "CMenu" : "unknown");
	//return CFrameWnd::OnMenuSelect(nItemID, nFlags, hSysMenu);
	return;
}







int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{



	CCreateContext* pContext = (CCreateContext*)lpCreateStruct->lpCreateParams;
	if (CBCGPFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_deuData = new CDeuData;
	g_Task2000 = new CDeu2000Task(this);
		
	HRESULT hr = CoCreateInstance(CLSID_DeuConnPool,   NULL,   CLSCTX_ALL,   IID_IDeuConnPool,   (void**)&g_ConnPool);   
	if   (SUCCEEDED(hr)   &&   (g_ConnPool   !=   NULL))   
	{   						
		//trans->ReleaseDispatch();  
	}  

	m_Msg = new CDeuMessage;

	OnAppLook (m_nAppLook);

	// VISUAL_MANAGER
	
	if (CBCGPToolBar::GetUserImages () == NULL)
	{
		// Load toolbar user images:
		#if 0

		if (!m_UserImages.Load (_T(".\\UserImages.bmp")))
		{
			TRACE(_T("Failed to load user images\n"));
			ASSERT (FALSE);
		}
		else
		{
			CBCGPToolBar::SetUserImages (&m_UserImages);
		}
		#endif
	}

	CBCGPToolBar::EnableQuickCustomization ();


	// TODO: Define your own basic commands. Be sure, that each pulldown 
	// menu have at least one basic command.

	CList<UINT, UINT>	lstBasicCommands;

	lstBasicCommands.AddTail (ID_VIEW_TOOLBARS);
	//lstBasicCommands.AddTail (ID_FILE_OPEN);
	//lstBasicCommands.AddTail (ID_FILE_SAVE);
	//lstBasicCommands.AddTail (ID_FILE_PRINT);
	//lstBasicCommands.AddTail (ID_APP_EXIT);
	//lstBasicCommands.AddTail (ID_EDIT_CUT);
	//lstBasicCommands.AddTail (ID_EDIT_PASTE);
	//lstBasicCommands.AddTail (ID_EDIT_UNDO);
	//lstBasicCommands.AddTail (ID_RECORD_NEXT);
	//lstBasicCommands.AddTail (ID_RECORD_LAST);
	//lstBasicCommands.AddTail (ID_APP_ABOUT);
	//lstBasicCommands.AddTail (ID_VIEW_TOOLBAR);
	//lstBasicCommands.AddTail (ID_VIEW_CUSTOMIZE);
	//lstBasicCommands.AddTail (ID_WINDOW_TILE_HORZ);
	//lstBasicCommands.AddTail (ID_VIEW_APPLOOK_2000);
	//lstBasicCommands.AddTail (ID_VIEW_APPLOOK_XP);
	//lstBasicCommands.AddTail (ID_VIEW_APPLOOK_2003);
	//lstBasicCommands.AddTail (ID_VIEW_APPLOOK_2007);
	//lstBasicCommands.AddTail (ID_VIEW_APPLOOK_VS2005);
	//lstBasicCommands.AddTail (ID_VIEW_APPLOOK_WIN_XP);
	lstBasicCommands.AddTail (ID_CS_DEF);
	

	//CBCGPToolBar::SetBasicCommands (lstBasicCommands);

	if (!m_wndMenuBar.Create (this))
	{
		TRACE0("Failed to create menubar\n");
		return -1;      // fail to create
	}

	//m_wndMenuBar.SetHeight( 10 );
	//int i = m_wndMenuBar.CalcMaxButtonHeight();
	//CSize s = m_wndMenuBar.GetButtonSize();
	
	//m_wndMenuBar.SetSizes(CSize(15,20),CSize(15,20));

	m_wndMenuBar.SetMenuSizes(CSize(25,25),CSize(15,15));


	//m_wndMenuBar.SetBarStyle(m_wndMenuBar.GetBarStyle());
	m_wndMenuBar.SetBarStyle(m_wndMenuBar.GetBarStyle() | CBRS_SIZE_DYNAMIC);

	//////////////////////////////////////////////////////////////////////////
	////从配置文件加载插件信息
	//DeuReadFile rf;	
	//m_vecPluginNames=rf.vec1;

	//m_wndMenuBar.m_vecPluginNames=m_vecPluginNames;
	//////////////////////////////////////////////////////////////////////////


	// Detect color depth. 256 color toolbars can be used in the
	// high or true color modes only (bits per pixel is > 8):
	CClientDC dc (this);
	BOOL bIsHighColor = dc.GetDeviceCaps (BITSPIXEL) > 8;

	UINT uiToolbarHotID = bIsHighColor ? IDB_TOOLBAR256 : 0;
	
	CString toolbarName;	
	//////////////////////////////////////////////////////////////////////////
	//m_ToolBarCalculator//IDR_ToolbarCalculator


	if (!m_ToolBarCalculator.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC,CRect(1,1,1,1),/*AFX_IDW_TOOLBAR*/IDR_ToolbarCalculator) ||
		!m_ToolBarCalculator.LoadToolBar(IDR_ToolbarCalculator, 0, 0, FALSE, 0, 0, IDR_ToolbarCalculator))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	//UINT arrBtn_Cal[3];
	//arrBtn_Cal[0] = ID_NEW_VECTOR;
	//arrBtn_Cal[1] = ID_NEW_RASTER;
	//arrBtn_Cal[2] = ID_NEW_VIEW;
	//m_ToolBarCalculator.SetButtons(arrBtn_Cal,3);


	toolbarName.LoadString(IDS_MAIN_TOOLBAR);
	m_ToolBarCalculator.SetWindowText(toolbarName);
		
	BOOL bV = m_ToolBarCalculator.IsVisible();

	//////////////////////////////////////////////////////////////////////////
	//m_ToolBarUtility//IDR_Utility
	if (!m_ToolBarUtility.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC,CRect(1,1,1,1),/*AFX_IDW_TOOLBAR*/IDR_Utility) ||
		!m_ToolBarUtility.LoadToolBar(IDR_Utility, 0, 0, FALSE, 0, 0, IDR_Utility))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	//UINT arrBtn_Uti[3];
	//arrBtn_Uti[0] = ID_MSG_WND;
	//arrBtn_Uti[1] = ID_PRJ_WND;
	//arrBtn_Uti[2] = ID_DATA_WND;
	//m_ToolBarUtility.SetButtons(arrBtn_Uti,3,FALSE);
	
	
	//////////////////////////////////////////////////////////////////////////
	//m_ToolBarDataSource//IDR_DataSource
	if (!m_ToolBarDataSource.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC,CRect(1,1,1,1),/*AFX_IDW_TOOLBAR*/IDR_DataSource) ||
		!m_ToolBarDataSource.LoadToolBar(IDR_DataSource, 0, 0, FALSE, 0, 0, IDR_DataSource))//IDR_DataSource
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	//////////////////////////////////////////////////////////////////////////
	//m_ToolBarView//IDR_TOOLBARVIEW
	if (!m_ToolBarView.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC,CRect(1,1,1,1),/*AFX_IDW_TOOLBAR*/IDR_TOOLBARVIEW) ||
		!m_ToolBarView.LoadToolBar(IDR_TOOLBARVIEW, 0, 0, FALSE, 0, 0,IDR_TOOLBARVIEW))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}


	//////////////////////////////////////////////////////////////////////////
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	//SkinH_Attach();

	// Load control bar icons:
	CBCGPToolBarImages imagesWorkspace;
	imagesWorkspace.SetImageSize (CSize (16, 16));
	imagesWorkspace.SetTransparentColor (RGB (255, 0, 255));
	imagesWorkspace.Load (IDB_WORKSPACE);	


	CreateWnd_DataCorral(imagesWorkspace,pContext);
	CreateWnd_Project(imagesWorkspace);
	//CreateWorkSpaceMain(imagesWorkspace);
	CreateWnd_OutPut(imagesWorkspace);


#if 0
	

	if (!m_wndOutput2.Create (_T("Output"), this, CSize (150, 150),
		TRUE /* Has gripper */, ID_VIEW_OUTPUT,
		WS_CHILD | WS_VISIBLE | CBRS_BOTTOM))
	{
		TRACE0("Failed to create output bar\n");
		return -1;      // fail to create
	}

	m_wndOutput2.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndOutput2);

#endif

#if 1
	if (!m_wndCoordinateSystem.Create (_T("坐标系统"), this, CSize (150, 150),
		TRUE /* Has gripper */, ID_VIEW_CoordinateSystem,
		WS_CHILD | WS_VISIBLE | CBRS_RIGHT))
	{
		TRACE0("Failed to create output bar\n");
		return -1;      // fail to create
	}

	if (!m_wndCursorPosition.Create (_T("当前坐标"), this, CSize (150, 150),
		TRUE /* Has gripper */, ID_VIEW_CursorPosition,
		WS_CHILD | WS_VISIBLE | CBRS_RIGHT))
	{
		TRACE0("Failed to create output bar\n");
		return -1;      // fail to create
	}

	if (!m_wndSelectedFeatures.Create (_T("选择地物"), this, CSize (150, 150),
		TRUE /* Has gripper */, ID_VIEW_SelectedFeatures,
		WS_CHILD | WS_VISIBLE | CBRS_RIGHT))
	{
		TRACE0("Failed to create output bar\n");
		return -1;      // fail to create
	}

	if (!m_wndEagleEye.Create (_T("鹰眼视图"), this, CSize (150, 150),
		TRUE /* Has gripper */, ID_VIEW_EagleEye,
		WS_CHILD | WS_VISIBLE | CBRS_RIGHT))
	{
		TRACE0("Failed to create output bar\n");
		return -1;      // fail to create
	}

	m_wndCoordinateSystem.EnableDocking(CBRS_ALIGN_ANY);
	m_wndCursorPosition.EnableDocking(CBRS_ALIGN_ANY);
	m_wndSelectedFeatures.EnableDocking(CBRS_ALIGN_ANY);
	m_wndEagleEye.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndCoordinateSystem);
	DockControlBar(&m_wndCursorPosition);
	DockControlBar(&m_wndSelectedFeatures);
	DockControlBar(&m_wndEagleEye);
	m_wndCoordinateSystem.SetMinSize(CSize(150,80));
	m_wndCursorPosition.SetMinSize(CSize(150,100));
	m_wndSelectedFeatures.SetMinSize(CSize(150,150));
	m_wndEagleEye.SetMinSize(CSize(150,150));

#endif

	//CString strMainToolbarTitle;
	//strMainToolbarTitle.LoadString (IDS_MAIN_TOOLBAR);
	//m_wndToolBar.SetWindowText (strMainToolbarTitle);

	// TODO: Delete these three lines if you don't want the toolbar to be dockable
	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	m_ToolBarCalculator.EnableDocking(CBRS_ALIGN_ANY);
	m_ToolBarUtility.EnableDocking(CBRS_ALIGN_ANY);
	m_ToolBarDataSource.EnableDocking(CBRS_ALIGN_ANY);
	m_ToolBarView.EnableDocking(CBRS_ALIGN_ANY);
	
	
	
	m_wndDataCorral.EnableDocking(CBRS_ALIGN_ANY);
	m_wndProject.EnableDocking(CBRS_ALIGN_ANY);
	//m_wndWorkSpaceMain.EnableDocking(CBRS_ALIGN_ANY);
	m_wndOutput.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	EnableAutoHideBars(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndMenuBar);	
	DockControlBar(&m_ToolBarCalculator);
	//DockControlBar(&m_ToolBarUtility);
	//DockControlBar(&m_ToolBarDataSource);
	//DockControlBar(&m_ToolBarView);

	DockControlBarLeftOf(&m_ToolBarUtility,&m_ToolBarCalculator);
	DockControlBarLeftOf(&m_ToolBarDataSource,&m_ToolBarUtility);
	DockControlBarLeftOf(&m_ToolBarView,&m_ToolBarDataSource);

	
	
	DockControlBar(&m_wndDataCorral);
	m_wndProject.AttachToTabWnd (&m_wndDataCorral, BCGP_DM_STANDARD, FALSE, NULL);
	//DockControlBar(&m_wndWorkSpaceMain);
	DockControlBar(&m_wndOutput);


	m_ToolBarCalculator.EnableCustomizeButton (TRUE, ID_VIEW_CUSTOMIZE, _T("Customize..."));
	m_ToolBarUtility.EnableCustomizeButton (TRUE, ID_VIEW_CUSTOMIZE, _T("Customize..."));
	m_ToolBarDataSource.EnableCustomizeButton (TRUE, ID_VIEW_CUSTOMIZE, _T("Customize..."));
	m_ToolBarView.EnableCustomizeButton (TRUE, ID_VIEW_CUSTOMIZE, _T("Customize..."));

	

	// Allow user-defined toolbars operations:
	//InitUserToobars (NULL,
	//				uiFirstUserToolBarId,
	//				uiLastUserToolBarId);

	//// Enable control bar context menu (list of bars + customize command):
	//EnableControlBarMenu (	
	//	TRUE,				// Enable
	//	ID_VIEW_CUSTOMIZE, 	// Customize command ID
	//	_T("自定义..."),	// Customize command text
	//	ID_VIEW_TOOLBARS);	// Menu items with this ID will be replaced by
	//						// toolbars menu

	toolbarName.LoadString(IDS_VIEW_TOOLBAR);
	m_ToolBarView.SetWindowText(toolbarName);
	//m_ToolBarView.IsVisible();
	
	toolbarName.LoadString(IDS_CAL_TOOLBAR);
	m_ToolBarUtility.SetWindowText(toolbarName);

	toolbarName.LoadString(IDS_DS_TOOLBAR);
	m_ToolBarDataSource.SetWindowText(toolbarName);


	//加载插件
	//LoadPlugins();
	return 0;
}

void CMainFrame::CreateWnd_DataCorral(CBCGPToolBarImages &imagesWorkspace,CCreateContext* pContext)
{
	if (!m_wndDataCorral.Create (_T("数据栈窗口"), this, CRect (0, 0, 200, 200),
		TRUE, ID_VIEW_WORKSPACE,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI),dwDefaultBCGDockingBarStyle, NULL)
	{
		TRACE0("Failed to create Workspace bar\n");
		return ;      // fail to create
	}

	//m_wndDataCorral.SetIcon (imagesWorkspace.ExtractIcon (0), FALSE);
}

void CMainFrame::CreateWnd_Project(CBCGPToolBarImages &imagesWorkspace)
{
	if (!m_wndProject.Create (_T("任务窗口"), this, CRect (0, 0, 200, 200),
		TRUE, ID_VIEW_WORKSPACE2,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create Workspace bar 2\n");
		return ;      // fail to create
	}

	//m_wndWorkSpace2.SetIcon (imagesWorkspace.ExtractIcon (1), FALSE);
	
}

//void CMainFrame::CreateWorkSpaceMain(CBCGPToolBarImages &imagesWorkspace)
//{
//	if (!m_wndWorkSpaceMain.Create (_T("View Main"), this, CRect (0, 0, 200, 200),
//		TRUE, ID_VIEW_WORKSPACEMAIN,
//		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
//	{
//		TRACE0("Failed to create Workspace bar 2\n");
//		return ;      // fail to create
//	}
//
//	m_wndWorkSpaceMain.SetIcon (imagesWorkspace.ExtractIcon (1), FALSE);
//
//}

void CMainFrame::CreateWnd_OutPut(CBCGPToolBarImages &imagesWorkspace)
{
	if (!m_wndOutput.Create (_T("消息窗口"), this, CSize (150, 150),
		TRUE /* Has gripper */, ID_VIEW_OUTPUT,
		WS_CHILD | WS_VISIBLE | CBRS_BOTTOM))
	{
		TRACE0("Failed to create output bar\n");
		return ;      // fail to create
	}

	m_Msg->m_wnd=(CWnd*)&m_wndOutput;
}


BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CBCGPFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}


// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CBCGPFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CBCGPFrameWnd::Dump(dc);
}

#endif //_DEBUG


// CMainFrame message handlers
void CMainFrame::OnNewRaster()
{

	//////////////////////////////////////////////////////////////////////////
	//添加树节点
	//CDeuData *pDeuData = DEUMAINFRM.m_deuData;	
	//pDeuData->vecRaster.Add();

	//VEC(CPropertyPage*) &vecPage = pDeuData->vecRasterTrans;
	//UINT iCount =  vecPage.size();



//	//////////////////////////////////////////////////////////////////////////
//	//添加属性页

	

//	CMainFrame &MainFrm = *(CMainFrame*) AfxGetMainWnd();
//	CDeu2000View &pView = *(CDeu2000View*)MainFrm.GetActiveView();
//
//	CDeuRasterTrans *pTrans=new CDeuRasterTrans();
//	pTrans->m_deuTask->TaskName = PageName;
//
////	vecPage.push_back(pTrans);
//
////	pTrans->m_psp.dwFlags |= PSP_USETITLE; 
////	pTrans->m_psp.pszTitle = PageName; 
//
//
////	pView.m_Sheet->AddPage(pTrans);
//
//

	//属性列表数据包
	TreeData *data = new TreeData;

	CDeu2000View* pView= (CDeu2000View*)DEUMAINFRM.GetActiveView();
	pView->m_DlgContainer.AddTabForRaster(data);

	

	CString PageName;
	PageName.Format("%s%d","栅格转换",DEUMAINFRM.m_deuData->vecRaster.GetCount());

	CTreeCtrl &wndTree = m_wndProject.m_dlgTreeTask.m_Tree;
	HTREEITEM item = wndTree.InsertItem (PageName, m_wndProject.m_dlgTreeTask.hRasterParent);
	wndTree.SetItemData(item,(DWORD_PTR)data);

	wndTree.Expand(m_wndProject.m_dlgTreeTask.hRoot1, TVE_EXPAND);
	wndTree.Expand(m_wndProject.m_dlgTreeTask.hVecParent, TVE_EXPAND);
	wndTree.Expand(m_wndProject.m_dlgTreeTask.hRasterParent, TVE_EXPAND);

	return;

}

//新建矢量
void CMainFrame::OnNewVector()
{

	//////////////////////////////////////////////////////////////////////////
	//添加树节点
	//CDeuData *pDeuData = DEUMAINFRM.m_deuData;
	TreeData *data = new TreeData;
	CDeu2000View* pView= (CDeu2000View*)DEUMAINFRM.GetActiveView();
	pView->m_DlgContainer.AddTabForVector(data);


	//增加树节点
	CString PageName;
	PageName.Format("%s%d","矢量转换",DEUMAINFRM.m_deuData->vecVector.GetCount());

	CTreeCtrl &wndTree = m_wndProject.m_dlgTreeTask.m_Tree;
	HTREEITEM item = wndTree.InsertItem (PageName, m_wndProject.m_dlgTreeTask.hVecParent);
	wndTree.SetItemData(item,(DWORD_PTR)data);
	
	wndTree.Expand(m_wndProject.m_dlgTreeTask.hRoot1, TVE_EXPAND);
	wndTree.Expand(m_wndProject.m_dlgTreeTask.hVecParent, TVE_EXPAND);
	wndTree.Expand(m_wndProject.m_dlgTreeTask.hRasterParent, TVE_EXPAND);

	//CDeuDataTransform *pTrans=new CDeuDataTransform();
	//pDeuData->vecVector.Add(pTrans);

	//VEC(CBCGPDialog*) &vecPage = ;
	//UINT iCount =  pDeuData->vecVector.GetCount();

	//CString PageName;
	//PageName.Format(_T("%s%d"),L"矢量转换",iCount);


	//CTreeCtrl &wndTree = m_wndProject.m_dlgTreeTask.m_Tree;
	//HTREEITEM  hItem=wndTree.GetRootItem();
	//	
	//HTREEITEM item = wndTree.InsertItem (PageName,hItem);


	////////////////////////////////////////////////////////////////////////////
	////添加属性页
	//CMainFrame &MainFrm = *(CMainFrame*) AfxGetMainWnd();
	//CDeu2000View &pView = *(CDeu2000View*)MainFrm.GetActiveView();

	//pTrans->m_deuTask->TaskName = PageName;

	////vecPage.push_back(pTrans);

	///*pTrans->m_psp.dwFlags |= PSP_USETITLE; 
	//pTrans->m_psp.pszTitle = PageName; */

	//TreeData *data = new TreeData;
	//data->p1 = pTrans;
	//data->type = VEC_TASK;
	//wndTree.SetItemData(item,(DWORD_PTR)data);

	return;

}


//产生一个新的视图page
void CMainFrame::OnNewView()
{	
	CDeu2000View* pView = (CDeu2000View*)GetActiveView();
	pView->m_DlgContainer.AddTabForView();


	//CDeuData *pDeuData = DEUMAINFRM.m_deuData;
	////VEC(CPropertyPage*) &vecPage = pDeuData->vecDataView;

	//VEC(CBCGPDialog*) &vecPage = pDeuData->vecView;
	//UINT iCount =  vecPage.size();

	//CString PageName;
	//PageName.Format(_T("%s%d"),L"视图",iCount);

	//vecPage.push_back(pDataView);

	//pDataView->m_psp.dwFlags |= PSP_USETITLE; 
	//pDataView->m_psp.pszTitle = PageName; 


	
	return;
}



void CMainFrame::OnViewCustomize()
{
	//------------------------------------
	// Create a customize toolbars dialog:
	//------------------------------------
	CBCGPToolbarCustomize* pDlgCust = new CBCGPToolbarCustomize (this,
		TRUE /* Automatic menus scaning */,
		BCGCUSTOMIZE_MENU_SHADOWS | BCGCUSTOMIZE_TEXT_LABELS | 
		BCGCUSTOMIZE_LOOK_2000 | BCGCUSTOMIZE_MENU_ANIMATIONS | BCGCUSTOMIZE_CONTEXT_HELP);

	pDlgCust->EnableUserDefinedToolbars ();
	pDlgCust->Create ();
}


void CMainFrame::OnNewFileTrans()//曹欣 继续
{
	//曹欣，新建文件转换
	//////////////////////////////////////////////////////////////////////////
	//添加树节点
	//CDeuData *pDeuData = DEUMAINFRM.m_deuData;

	//VEC(CPropertyPage*) &vecPage = pDeuData->vecFileTrans;
	//UINT iCount =  vecPage.size();

	//CString PageName;
	//PageName.Format(_T("%s%d"),L"文件转换",iCount);


	////CTreeCtrl &wndTree = m_wndProject.m_dlgTreeTask.m_Tree;
	////HTREEITEM  hItem=wndTree.GetRootItem();

	////HTREEITEM item = wndTree.InsertItem (PageName,hItem);


	////////////////////////////////////////////////////////////////////////////
	////添加属性页
	//CMainFrame &MainFrm = *(CMainFrame*) AfxGetMainWnd();
	//CDeu2000View &pView = *(CDeu2000View*)MainFrm.GetActiveView();

	//DeuFileTransform *pTrans=new DeuFileTransform;
	////pTrans->m_deuTask->TaskName = PageName;

	//vecPage.push_back(pTrans);

	//pTrans->m_psp.dwFlags |= PSP_USETITLE; 
	//pTrans->m_psp.pszTitle = PageName; 

		
	//pView.m_Sheet->AddPage(pTrans);


	//TreeData *data = new TreeData;
	//data->p1 = pTrans;
	//data->type = VEC_TASK;
	//wndTree.SetItemData(item,(DWORD_PTR)data);

	return;
	//CDeu2000View* pView = (CDeu2000View*)this->GetActiveView();
	//CDeuDataView *pDataView=new CDeuDataView;

	//CDeuData *pDeuData = DEUMAINFRM.m_deuData;
	//VEC(CPropertyPage*) &vecPage = pDeuData->vecDataView;
	//UINT iCount =  vecPage.size();

	//CString PageName;
	//PageName.Format(_T("%s%d"),L"视图",iCount);

	//vecPage.push_back(pDataView);

	//pDataView->m_psp.dwFlags |= PSP_USETITLE; 
	//pDataView->m_psp.pszTitle = PageName; 

	//pView->m_Sheet->AddPage(pDataView);
	//return;
}

afx_msg LRESULT CMainFrame::OnToolbarReset(WPARAM /*wp*/,LPARAM)
{
	// TODO: reset toolbar with id = (UINT) wp to its initial state:
	//
	// UINT uiToolBarId = (UINT) wp;
	// if (uiToolBarId == IDR_MAINFRAME)
	// {
	//		do something with m_wndToolBar
	// }

	//加载插件
	//LoadPlugins();



	return 0;
}

LRESULT CMainFrame::OnHelpCustomizeToolbars(WPARAM wp, LPARAM lp)
{
	int iPageNum = (int) wp;

	CBCGPToolbarCustomize* pDlg = (CBCGPToolbarCustomize*) lp;
	ASSERT_VALID (pDlg);

	// TODO: show help about page number iPageNum

	return 0;
}

void CMainFrame::OnAppLook(UINT id)
{
	CBCGPDockManager::SetDockMode (BCGP_DT_SMART);

	m_nAppLook = id;

	CBCGPTabbedControlBar::m_StyleTabWnd = CBCGPTabWnd::STYLE_3D;

	switch (m_nAppLook)
	{
	case ID_VIEW_APPLOOK_2000:
		// enable Office 2000 look:
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager));
		break;

	case ID_VIEW_APPLOOK_XP:
		// enable Office XP look:
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManagerXP));
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		// enable Windows XP look (in other OS Office XP look will be used):
		CBCGPWinXPVisualManager::m_b3DTabsXPTheme = TRUE;
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPWinXPVisualManager));
		break;

	case ID_VIEW_APPLOOK_2003:
		// enable Office 2003 look:
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager2003));
		CBCGPDockManager::SetDockMode (BCGP_DT_SMART);
		break;

	case ID_VIEW_APPLOOK_2007:
		// enable Office 2007 look:
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager2007));
		CBCGPDockManager::SetDockMode (BCGP_DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS2005:
		// enable VS.NET 2005 look:
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManagerVS2005));
		CBCGPDockManager::SetDockMode (BCGP_DT_SMART);
		break;

	default:
		ASSERT (FALSE);
	}

	CBCGPDockManager* pDockManager = GetDockManager ();
	if (pDockManager != NULL)
	{
		ASSERT_VALID (pDockManager);
		pDockManager->AdjustBarFrames ();
	}

	CBCGPTabbedControlBar::ResetTabs ();

	RecalcLayout ();
	RedrawWindow (NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);

	theApp.WriteInt (_T("ApplicationLook"), m_nAppLook);
}

void CMainFrame::OnUpdateAppLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio (m_nAppLook == pCmdUI->m_nID);
}


void CMainFrame::LoadPlugins()
{
	//从配置文件加载插件信息
	DeuReadFile rf;	
	m_vecPluginNames=rf.vec1;

	//顺序加载各个插件
	UINT num=m_vecPluginNames.size();
	for (int i=0;i<num;i++)
	{
		string name=m_vecPluginNames[i];
		LoadPlugin(name);
	}
}

void CMainFrame::LoadPlugin(string PlugName)
{

	HINSTANCE hmod;
	const char * szName=PlugName.c_str();

	/*
	USES_CONVERSION;
	hmod = ::LoadLibrary (A2W(szName));
	*/
	hmod = ::LoadLibrary (szName);

	m_vecPluginHandles.push_back(hmod);

	if(hmod==NULL)
	{
		string msg=PlugName+"  Fail"; 
		/*
		USES_CONVERSION;
		AfxMessageBox(A2W(msg.c_str()));
		*/
		AfxMessageBox(msg.c_str());
		return;
	}

	typedef void* (*getMenuIDFunc)(void);
	typedef void* (*getToolbarIDFunc)(void);
	typedef void* (*getDockBarIDFunc)(void);
	typedef void* (*GetDockInfoFunc)(UINT);

	getToolbarIDFunc getToolbarID;
	getToolbarID = (getToolbarIDFunc)GetProcAddress(hmod,"GetToolbarID");

	getMenuIDFunc getMenuID ;
	getMenuID = (getMenuIDFunc)GetProcAddress(hmod,"GetMenuID");
	
	getDockBarIDFunc getDockBars ;
	getDockBars = (getDockBarIDFunc)GetProcAddress(hmod,"GetControls");

	std::vector<INT> *p_vecToolbarID = NULL;
	std::vector<INT> *p_vecMenuID = NULL;
	if(getToolbarID != NULL)
	p_vecToolbarID = (std::vector<INT> *)getToolbarID(); //(std::vector<INT>*)GetProcAddress (hmod,"vecMenuID");

	if(getMenuID != NULL)
	p_vecMenuID = (std::vector<INT> *)getMenuID(); //(std::vector<INT>*)GetProcAddress (hmod,"vecMenuID");
		
	std::vector<INT> *p_vecDockCtrlBar = NULL;
	if(getDockBars != NULL)
	p_vecDockCtrlBar = (std::vector<INT> *)getDockBars(); //(std::vector<INT>*)GetProcAddress (hmod,"vecMenuID");

	//////////////////////////////////////////////////////////////////////////
	
	HINSTANCE m_hResOld =AfxGetResourceHandle(); 
	HINSTANCE m_hInstOld = AfxGetInstanceHandle();

	AfxSetResourceHandle(hmod); 

	if(p_vecMenuID)
	{
		VEC(INT) &vecMenuID = *p_vecMenuID;

		UINT numMenuIDs = vecMenuID.size();

		for (int i = 0;i < numMenuIDs; i++)
		{

			UINT id_Menu = vecMenuID[i];
			//////////////////////////////////////////////////////////////////////////
			
			LoadMenuInPlugin(/*VEC(INT) &*/id_Menu,PlugName);
			
		}
		m_wndMenuBar.AdjustLayout();
		m_wndMenuBar.AdjustSizeImmediate ();

	}

	AfxSetResourceHandle(m_hResOld); 
	
	if(p_vecDockCtrlBar)
	{
		VEC(INT) &vecDockID = *p_vecDockCtrlBar;

		UINT numDockIDs = vecDockID.size();

		for (int i = 0;i < numDockIDs; i++)
		{
			UINT id_Dock = vecDockID[i];
			//////////////////////////////////////////////////////////////////////////
			//根据id从plug获得Dockinfo
			GetDockInfoFunc getDockInfo ;
			getDockInfo = (GetDockInfoFunc)GetProcAddress(hmod,"GetDockInfo");
			
			void* pDeuVoid =(void*) getDockInfo(id_Dock);
			std::map<int,void*> *p_nParma = ((std::map<int,void*>*)pDeuVoid);
			std::map<int,void*> &nParma = *p_nParma ;

			//////////////////////////////////////////////////////////////////////////

			//LoadDockBarInPlugin(id_Dock,PlugName,hmod);
            //LoadDockBarInPlugin(id_Dock,PlugName,hmod);
			CString nPlugName =_T("");
			if (1 == id_Dock)
			{
				nPlugName = _T("数据区窗口");
			}

			else if (2 == id_Dock)
			{
				nPlugName = _T("堆栈区窗口");
			}

			else if (3 == id_Dock)
			{
				nPlugName = _T("输出窗口");
			}
			
			//nPlugName.Format( "%s ",PlugName.data());
			LoadDockBarInPlugin(nParma,nPlugName,hmod);
		}
		/*m_wndDockBar.AdjustLayout();
		m_wndDockBar.AdjustSizeImmediate ();*/
	}

}

void CMainFrame::LoadMenuInPlugin(UINT id_Menu,string PlugName)
{		//////////////////////////////////////////////////////////////////////////

#define IDR_TOOLBAR2 60001
#define IDR_Menu2    60002

		//////////////////////////////////////////////////////////////////////////
		CMenu menu;		
		menu.LoadMenu(id_Menu);

		//USES_CONVERSION;
		//m_wndMenuBar.InsertButton (CBCGPToolbarMenuButton (0, menu, -1, A2W(PlugName.c_str())));
		m_wndMenuBar.InsertButton (CBCGPToolbarMenuButton (0, menu, -1, PlugName.c_str()));

}



void CMainFrame::LoadDockBarInPlugin(std::map<int,void*>& nParma,CString szName,HINSTANCE plInstance)
{
#define IDR_TOOLBAR2 60001
#define IDR_Menu2    60002

//#define Dock_OutputBar 1
//#define Dock_ViewBar   2
//#define Dock_ViewBar1  3	


#if 0
//#define PLUG_UI_CSIZE       0      //如果为坐标
//#define PLUG_UI_CRECT       1      //如果为矩形框
//#define PLUG_UI_CSTYTLE    2     //插件样式
//#define PLUG_UI_CDOCK_TYPE  3     //插件的类型
//#define PLUG_UI_CCTRL_ID    4     //控件ID

	/*UINT Dock_type1 = 30001;
	CRect nRSize1(0,0,150,150);
	CDeuSize nCSize1(150,150);
	UINT Ctrl_ID1 = ID_VIEW_OUTPUT;
	UINT nStyle1 = WS_CHILD | WS_VISIBLE | CBRS_BOTTOM;

    nParma.insert(make_pair(PLUG_UI_CSIZE,&nCSize1));
	nParma.insert(make_pair(PLUG_UI_CRECT,&nRSize1));
	nParma.insert(make_pair(PLUG_UI_CSTYTLE,(void*)nStyle1));
	nParma.insert(make_pair(PLUG_UI_CCTRL_ID,(void*)Ctrl_ID1));
	nParma.insert(make_pair(PLUG_UI_CDOCK_TYPE,(void*)Dock_type1));*/

#endif

	//////////////////////////////////////////////////////////////////////////

	//typedef void* (WINAPI * GetControlFunc)();

	//GetControlFunc lpproc;
	//lpproc = (GetControlFunc)GetProcAddress (hmod,"GetControl");
	
	CBCGPDockingControlBar* p_DockBar = NULL ;
	//////////////////////////////////////////////////////////////////////////
	//Dock_Id 和 DockCtrl 是一一 对应的。例如：Dock_ID=30001,对应着DockCtrl=COutputBar

	//////////////////////////////////////////////////////////////////////////
	 //Dock_type, szName,nSize,Ctrl_ID,nStyle
	//(UINT Dock_type,CString szName,CRect nSize,UINT Ctrl_ID,UINT nStyle);
	////////////////////////////////////////////////////////////////////////

	UINT Dock_type = 0;
	CRect *nRSize = 0;
    CDeuSize *nCSize = 0;
	UINT Ctrl_ID = 0;
	UINT nStyle = 0;

	std::map<int,void*>::iterator it = find_if(nParma.begin(),nParma.end(),map_find_func(PLUG_UI_CRECT));
	nRSize =(CRect*)it->second;

	it = find_if(nParma.begin(),nParma.end(),map_find_func(PLUG_UI_CSIZE));
	nCSize = (CDeuSize *)it->second;

	it = find_if(nParma.begin(),nParma.end(),map_find_func(PLUG_UI_CSTYTLE));
	nStyle =(UINT)it->second;

	it = find_if(nParma.begin(),nParma.end(),map_find_func(PLUG_UI_CDOCK_TYPE));
	Dock_type =(UINT)it->second;

	it = find_if(nParma.begin(),nParma.end(),map_find_func(PLUG_UI_CCTRL_ID));
	Ctrl_ID =(UINT)it->second;	
	
	switch(Dock_type)
	{
	case Dock_OutputBar:
		{
			p_DockBar = new COutputBar;
			CBCGPDockingControlBar &DockBar = *p_DockBar;
			m_vecDockCtrlBar.push_back(p_DockBar);

			if (!DockBar.Create(szName, this, *nCSize,TRUE ,Ctrl_ID,nStyle))
			{
				TRACE0("Failed to create DockBar\n");
				return ;      // fail to create
			}

			DockBar.EnableDocking(CBRS_ALIGN_ANY);
			EnableDocking(CBRS_ALIGN_ANY);
			DockControlBar(&DockBar);
			break;
		}
	case Dock_ViewBar1:
		{
			p_DockBar = new CWndDataCorral;
			CBCGPDockingControlBar &ViewBar1 = *p_DockBar;
			m_vecDockCtrlBar.push_back(p_DockBar);
			if (!ViewBar1.Create (szName, this, *nRSize,TRUE , Ctrl_ID,nStyle))
			{
				TRACE0("Failed to create ViewBar1\n");
				return ;      // fail to create
			}

			ViewBar1.EnableDocking(CBRS_ALIGN_ANY);
			EnableDocking(CBRS_ALIGN_ANY);
			DockControlBar(&ViewBar1);
			break;
		}

	case Dock_ViewBar:
		{
			p_DockBar = new CWndProject;
			CBCGPDockingControlBar &ViewBar = *p_DockBar;
			m_vecDockCtrlBar.push_back(p_DockBar);
			if (!ViewBar.Create (szName, this, *nRSize,TRUE , Ctrl_ID,nStyle))
			{
				TRACE0("Failed to create ViewBar\n");
				return ;      // fail to create
			}

			ViewBar.EnableDocking(CBRS_ALIGN_ANY);
			EnableDocking(CBRS_ALIGN_ANY);
			DockControlBar(&ViewBar);
			break;
		}

	}
}

void CMainFrame::OnViewAddmenu()
{
	// TODO: 在此添加命令处理程序代码
#if 0
	HINSTANCE hmod;
	hmod = ::LoadLibrary ("win32_dll2.dll");
	if(hmod==NULL)
	{
		AfxMessageBox("Fail");
	}

	//////////////////////////////////////////////////////////////////////////

	HINSTANCE m_hResOld =AfxGetResourceHandle(); 
	HINSTANCE m_hInstOld = AfxGetInstanceHandle();

	AfxSetResourceHandle(hmod); 

	UINT id_Menu = 60002;

	//////////////////////////////////////////////////////////////////////////
	CMenu menu;		
	menu.LoadMenu(id_Menu);

	m_wndMenuBar.InsertButton (CBCGPToolbarMenuButton (0, menu, -1, _T("123")));



	m_wndMenuBar.AdjustLayout();
	m_wndMenuBar.AdjustSizeImmediate ();
#endif
	//LoadPlugins();
}


void CMainFrame::OnMsgWnd()
{
	BOOL ret = m_wndOutput.IsVisible();
	if(ret)
		m_wndOutput.ShowControlBar(FALSE,TRUE,FALSE);
	else	
		m_wndOutput.ShowControlBar(TRUE,TRUE,FALSE);


	AdjustDockingLayout();
	return;
};

void CMainFrame::OnPrjWndUI(CCmdUI* pCmdUI)
{
	BOOL ret = m_wndProject.IsVisible();
	if (ret)
	{
		pCmdUI->SetCheck(1);
	}
	else
	{
		pCmdUI->SetCheck(0);
	}

	return;
}

void CMainFrame::OnDataWndUI(CCmdUI* pCmdUI)
{
	BOOL ret = m_wndDataCorral.IsVisible();
	if (ret)
	{
		pCmdUI->SetCheck(1);
	}
	else
	{
		pCmdUI->SetCheck(0);
	}


	return;
}


void CMainFrame::OnMsgWndUI(CCmdUI* pCmdUI)
{

	BOOL ret = m_wndOutput.IsVisible();
	if (ret)
	{
		pCmdUI->SetCheck(1);
	}
	else
	{
		pCmdUI->SetCheck(0);
	}

}

void CMainFrame::OnPrjWnd()
{
	BOOL ret = m_wndProject.IsVisible();

	if(ret)
		m_wndProject.ShowControlBar(FALSE,TRUE,FALSE);
	else	
		m_wndProject.ShowControlBar(TRUE,TRUE,FALSE);

	AdjustDockingLayout();
}

void CMainFrame::OnDataWnd()
{
	BOOL ret = m_wndDataCorral.IsVisible();
	if(ret)
		m_wndDataCorral.ShowControlBar(FALSE,TRUE,FALSE);
	else	
		m_wndDataCorral.ShowControlBar(TRUE,TRUE,FALSE);

	AdjustDockingLayout();
}

void CMainFrame::OnCSDef()
{
	CDeuEditSource dlg;
	dlg.DoModal();
}

void CMainFrame::OnDatumDef()
{

}

void CMainFrame::OnDatumTranDef()
{

}

void CMainFrame::OnLenDef()
{

}

void CMainFrame::OnEllDef()
{

}

void CMainFrame::OnAngDef()
{

}

//视图
void CMainFrame::OnAddData()
{
    CDeu2000Task &task =*g_Task2000;
	task.AddData();
}

void CMainFrame::OnZoomIn()
{
	CDeu2000Task &task =*g_Task2000;
	task.ZoomIn();

	btnViewCheck[_TOOL_ZOOMOUT] = 0;
	btnViewCheck[_TOOL_ZOOMIN] = 1;
	btnViewCheck[_TOOL_PAN] = 0 ;	
	btnViewCheck[_TOOL_SELECT] = 0 ;
	btnViewCheck[_TOOL_NONE] = 0 ;
	btnViewCheck[_TOOL_REMOVELAYERS] = 0 ;
}

void CMainFrame::OnZoomOut()
{
	CDeu2000Task &task =*g_Task2000;
	task.ZoomOut();

	btnViewCheck[_TOOL_ZOOMOUT] = 1;
	btnViewCheck[_TOOL_ZOOMIN] = 0;
	btnViewCheck[_TOOL_PAN] = 0 ;
	btnViewCheck[_TOOL_SELECT] = 0 ;
	btnViewCheck[_TOOL_NONE] = 0 ;
	btnViewCheck[_TOOL_REMOVELAYERS] = 0 ;
}

void CMainFrame::OnPan()
{
	CDeu2000Task &task =*g_Task2000;
	task.Pan();

	btnViewCheck[_TOOL_PAN] = 1;	
	btnViewCheck[_TOOL_ZOOMIN] = 0 ;
	btnViewCheck[_TOOL_ZOOMOUT] = 0 ;
	btnViewCheck[_TOOL_SELECT] = 0 ;
	btnViewCheck[_TOOL_NONE] = 0 ;
	btnViewCheck[_TOOL_REMOVELAYERS] = 0 ;
}

void CMainFrame::OnFullMap()
{
	CDeu2000Task &task =*g_Task2000;
	task.ZoomToMaxVisibleExtents();
}

void CMainFrame::OnZoomToPrev()
{
	CDeu2000Task &task =*g_Task2000;
	task.ZoomToPrev();
}

void CMainFrame::OnZoomToNext()
{
	CDeu2000Task &task =*g_Task2000;
	task.ZoomToNext();
}

void CMainFrame::OnSelect()
{
	CDeu2000Task &task =*g_Task2000;
	task.SelectFeatures();

	btnViewCheck[_TOOL_SELECT] = 1 ;
	btnViewCheck[_TOOL_PAN] = 0 ;	
	btnViewCheck[_TOOL_ZOOMIN] = 0 ;
	btnViewCheck[_TOOL_ZOOMOUT] = 0 ;
	btnViewCheck[_TOOL_NONE] = 0 ;
	btnViewCheck[_TOOL_REMOVELAYERS] = 0 ;
}

void CMainFrame::OnRemoveSelections()
{
	CDeu2000Task &task =*g_Task2000;
	task.RemoveSelections();
}

void CMainFrame::OnNone()
{
	CDeu2000Task &task =*g_Task2000;
	task.None();
	btnViewCheck[_TOOL_ZOOMOUT] = 0 ;
	btnViewCheck[_TOOL_ZOOMIN] = 0 ;
	btnViewCheck[_TOOL_PAN] = 0 ;	
	btnViewCheck[_TOOL_SELECT] = 0 ;
	btnViewCheck[_TOOL_NONE] = 1 ;
	btnViewCheck[_TOOL_REMOVELAYERS] = 0 ;
}

void CMainFrame::OnRemoveLayers()
{
	CDeu2000Task &task =*g_Task2000;
	task.RemoveAllLayers();
	/*btnViewCheck[_TOOL_REMOVELAYERS] = 1 ;*/
	btnViewCheck[_TOOL_ZOOMOUT] = 0 ;
	btnViewCheck[_TOOL_ZOOMIN] = 0 ;
	btnViewCheck[_TOOL_PAN] = 0 ;	
	btnViewCheck[_TOOL_SELECT] = 0 ;
	btnViewCheck[_TOOL_NONE] = 0 ;
}
void CMainFrame::OnCoordWndM()
{
	// TODO: 在此添加命令处理程序代码
	BOOL ret = m_wndCoordinateSystem.IsVisible();
	if (ret)
	{
		m_wndCoordinateSystem.ShowControlBar(false,true,false);
	} 
	else
	{
		m_wndCoordinateSystem.ShowControlBar(true,true,false);
	}
	AdjustDockingLayout();
}

void CMainFrame::OnUpdateCoordWndM(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	BOOL ret = m_wndCoordinateSystem.IsVisible();
	if (ret)
	{
		pCmdUI->SetCheck(1);
	} 
	else
	{
		pCmdUI->SetCheck(0);
	}	
}

void CMainFrame::OnCursorWndM()
{
	// TODO: 在此添加命令处理程序代码
	BOOL ret = m_wndCursorPosition.IsVisible();
	if (ret)
	{
		m_wndCursorPosition.ShowControlBar(false,true,false) ;
	}
	else
	{
		m_wndCursorPosition.ShowControlBar(true,true,false) ;
	}
	AdjustDockingLayout();
}

void CMainFrame::OnUpdateCursorWndM(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	BOOL ret = m_wndCursorPosition.IsVisible();
	if (ret)
	{
		pCmdUI->SetCheck(1);
	} 
	else
	{
		pCmdUI->SetCheck(0);
	}
}

void CMainFrame::OnEyeWndM()
{
	// TODO: 在此添加命令处理程序代码
	BOOL ret = m_wndEagleEye.IsVisible();
	if (ret)
	{
		m_wndEagleEye.ShowControlBar(false,true,false);
	} 
	else
	{
		m_wndEagleEye.ShowControlBar(true,true,false);
	}
	AdjustDockingLayout();
}

void CMainFrame::OnUpdateEyeWndM(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	BOOL ret =  m_wndEagleEye.IsVisible();
	if (ret)
	{
		pCmdUI->SetCheck(1);
	} 
	else
	{
		pCmdUI->SetCheck(0);
	}
}

void CMainFrame::OnFtsWndM()
{
	// TODO: 在此添加命令处理程序代码
	BOOL ret = m_wndSelectedFeatures.IsVisible();
	if (ret)
	{
		m_wndSelectedFeatures.ShowControlBar(false,true,false);
	} 
	else
	{
		m_wndSelectedFeatures.ShowControlBar(true,true,false);
	}
	AdjustDockingLayout();
}

void CMainFrame::OnUpdateFtsWndM(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	BOOL ret = m_wndSelectedFeatures.IsVisible();
	if (ret)
	{
		pCmdUI->SetCheck(1);
	} 
	else
	{
		pCmdUI->SetCheck(0);
	}
}

void CMainFrame::OnUpdateToolZoomIn(CCmdUI *pCmdUI)
{
	
	pCmdUI->SetCheck( btnViewCheck[_TOOL_ZOOMIN]  );
}


void CMainFrame::OnUpdateToolZoomOut(CCmdUI *pCmdUI)
{

	pCmdUI->SetCheck( btnViewCheck[_TOOL_ZOOMOUT] );
}

void CMainFrame::OnUpdateToolPan(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck( btnViewCheck[_TOOL_PAN]  );
	/*pCmdUI->SetText(_T("漫游") );*/
}
void CMainFrame::OnUpdateToolSelectFeature(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck( btnViewCheck[_TOOL_SELECT] );
}
void CMainFrame::OnUpdateToolNone(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck( btnViewCheck[_TOOL_NONE] );
}

void CMainFrame::OnUpdateToolRemoveAllLayers(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck( btnViewCheck[_TOOL_REMOVELAYERS] );
}


void CMainFrame::OnMenuUsersManager()
{
	CDeuDlgUsers m_UsersManage;
	m_UsersManage.DoModal();
}



void CMainFrame::OnMenuUsersGroup()
{
	CDeuDlgUsersGroup m_UserGroup;
	m_UserGroup.DoModal();
}


//单转
void CMainFrame::OnSingleRechange()
{
	CDeu2000View* p_view = (CDeu2000View*)GetActiveView();
	p_view->m_DlgContainer.AddTabForSingle();
}


//批转
void CMainFrame::OnBatRechange()
{
	AfxMessageBox("批转");
}