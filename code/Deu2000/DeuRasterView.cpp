// DeuRasterView.cpp : 实现文件
//

#include "stdafx.h"
#include "DeuRasterFrame.h"
#include "DeuGlobalMainFrm.h"
#include "DeuRasterView.h"

// CDeuRasterView
IMPLEMENT_DYNCREATE(CDeuRasterView, CView)
CDeuRasterView::CDeuRasterView()
{
	nTabHistoryIndex = 1;
}

CDeuRasterView::~CDeuRasterView()
{
}

BEGIN_MESSAGE_MAP(CDeuRasterView, CView)
	ON_WM_SIZE()
	ON_WM_CREATE()
	//ON_NOTIFY_REFLECT(NM_CLICK, &CTabCtrlEx::OnNMClick)
	//ON_MESSAGE(WM_LBUTTONDOWN, IDC_TAB1, &CDeuRasterView::OnTabClose)
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CDeuRasterView 绘图
void CDeuRasterView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
}

// CDeuRasterView 诊断
#ifdef _DEBUG
void CDeuRasterView::AssertValid() const
{
	CView::AssertValid();
}
#ifndef _WIN32_WCE
void CDeuRasterView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc); 
}
#endif
#endif //_DEBUG

CDeuRasterDoc* CDeuRasterView::GetDocument() const
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDeuRasterDoc)));
	return (CDeuRasterDoc*)m_pDocument;
}

// CDeuRasterView 消息处理程序
void CDeuRasterView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	if (m_wndTabControl.GetSafeHwnd())
	{
		m_wndTabControl.MoveWindow(0, 0, cx, cy);
	}
}

int CDeuRasterView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	//1. 将创建的对象放到数组中以便将来查找对象
	_ViewRasterList.Add(this);

	//2. 创建TabCtrl 切换页
	m_wndTabControl.Create(WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS, CRect(0, 0, 0, 0), this, IDC_TAB1);	
	m_wndTabControl.SetOwner(this);
	m_wndTabControl.pPanelWnd = &((CDeuRasterFrame*)this->GetParentFrame())->m_PaneRaster;
	lstrcpy(m_wndTabControl.sz_Type, "Raster");
	m_wndTabControl.GetPaintManager()->SetAppearance(xtpTabAppearancePropertyPage2003);
	//m_wndTabControl.GetPaintManager()->m_bHotTracking = TRUE;
	m_wndTabControl.GetPaintManager()->m_bShowIcons = TRUE;	
	m_wndTabControl.GetPaintManager()->DisableLunaColors(FALSE);
	m_wndTabControl.ShowCloseItemButton();

	return 0;
}

void CDeuRasterView::OnAddTab()
{
	//AddView(RUNTIME_CLASS(CDeuRasterTranDlg), strName, 0);
	//_TabRasterList.Add(p_RasterDlg);

	if(m_wndTabControl.GetSafeHwnd())
	{
		CString strName;		
		strName.Format("转换任务%d", nTabHistoryIndex);
		CDeuRasterTranDlg* p_RasterDlg = new CDeuRasterTranDlg;
		p_RasterDlg->Create(IDD_DLG_TASK, &m_wndTabControl);

		int nTab = m_wndTabControl.GetItemCount();
		CXTPTabManagerItem* p_CurTab = m_wndTabControl.InsertItem(nTab, (LPCTSTR)strName, p_RasterDlg->GetSafeHwnd(), 0);	
		m_wndTabControl.SetSelectedItem(p_CurTab);

		nTabHistoryIndex++;
	}
	
	return;
}

/*
=============================================
 功能:	创建TabCtrl页内容
 参数:	pViewClass
	    lpszTitle
		nIcon

 返回:	BOOL 
 日期:  2010-12-29
 备注:  Add by hushichen
=============================================
*/
BOOL CDeuRasterView::AddView(CRuntimeClass* pViewClass, LPCTSTR lpszTitle, int nIcon)
{
	CCreateContext contextT;
	contextT.m_pCurrentDoc     = GetDocument();
	contextT.m_pNewViewClass   = pViewClass;
	contextT.m_pNewDocTemplate = GetDocument()->GetDocTemplate();

	CWnd* pWnd;
	//CDeuRasterTranDlg* p_RasterDlg;
	TRY
	{
		pWnd = (CWnd*)pViewClass->CreateObject();
		//p_RasterDlg = new CDeuRasterTranDlg;
		if (pWnd == NULL)
		{
			AfxThrowMemoryException();
		}
	}
	CATCH_ALL(e)
	{
		TRACE0( "创建视图内存溢出.\n" );
		return FALSE;
	}
	END_CATCH_ALL

	DWORD dwStyle = AFX_WS_DEFAULT_VIEW; 
	dwStyle &= ~WS_BORDER;

	int nTab = m_wndTabControl.GetItemCount();
	
	CRect rect(0,0,0,0);
	if (!pWnd->Create(NULL, NULL, dwStyle,
		rect, &m_wndTabControl, (AFX_IDW_PANE_FIRST + nTab), &contextT))
	{
		TRACE0( "Warning: couldn't create client tab for view.\n" );
		return NULL;
	}
	
	CXTPTabManagerItem* p_CurTab = m_wndTabControl.InsertItem(nTab, lpszTitle, pWnd->GetSafeHwnd(), nIcon);	
	m_wndTabControl.SetSelectedItem(p_CurTab);
	pWnd->SetOwner(this);

	return TRUE;
}

/* 激活父框架 */
void CDeuRasterView::ActiveParentFrm()
{
	this->GetParentFrame()->ActivateFrame();
	this->UpdateWindow();
}

/*
=============================================   
 功能:	删除指定tab，并释放窗口指针
 参数:  int nTabIndex	 Tab索引
		int nArrayIndex  数组索引
		
 备注:	TabCtrl的索引会自动维护，而数组索引不会
		自动维护.故需要传两个索引
		
 日期:	2010-12-29
=============================================
*/
void CDeuRasterView::DelTab(int nTabIndex)
{	

	//释放指针,这一句接口是否能准确释放内存，不造成内存泄露有待验证，目前暂时没有发现有泄露
	delete (CDeuRasterTranDlg*)CWnd::FromHandle(m_wndTabControl.GetItem(nTabIndex)->GetHandle());
	m_wndTabControl.DeleteItem(nTabIndex);

	//delete p_wnd;
	//delete _TabRasterList.GetAt(nTabIndex);
	//((CDeuRasterTranDlg*)CWnd::FromHandle(m_wndTabControl.GetItem(nTabIndex)->GetHandle()))->DestroyWindow();
	RefreshTaskXml();
	SaveRunTask();
}

/*
	删除所有item
*/
void CDeuRasterView::DelTabAll()
{
	while(m_wndTabControl.GetItemCount() > 0)
	{		
		DelTab(0);
	}
	RefreshTaskXml();
	SaveRunTask();
}

/*
	销毁框架视图
		通知任务数控件抹去对应节点

	备注：这里在只含一个视图的情况下可以使用，若
		  一对N的视图下就要在子框架下做节点抹去操作。
*/
void CDeuRasterView::OnDestroy()
{	
	CView::OnDestroy();

	for(int n=0; n<_ViewRasterList.GetCount(); n++)
	{
		if(_ViewRasterList.GetAt(n) == this)
		{
			//抹去节点			
			_ViewRasterList.RemoveAt(n);
			((CDeuGlobalMainFrame*)AfxGetMainWnd())->m_wndTaskPanel.OnDeleteNode(RASTER, n);
			break;
		}
	}
}

void CDeuRasterView::TabSelectSel(int nIndex)
{
	m_wndTabControl.SetCurSel(nIndex);
}

/* 
	
	栅格执行转换操作

*/
void CDeuRasterView::ProcessTask()
{
	if(!GobalUserInfo.IsRasterConvert)
	{
		MessageBox(PowerError,"系统提示", MB_OK|MB_ICONWARNING);
		return;
	}

	int ncount = m_wndTabControl.GetItemCount();
	if(ncount == 0)
	{
		MessageBox("无转换任务执行","系统提示", MB_OK|MB_ICONWARNING);
		return;
	}

	int curIndex = m_wndTabControl.GetCurSel();
	CDeuRasterTranDlg* p_Dlg = (CDeuRasterTranDlg*)CWnd::FromHandle(m_wndTabControl.GetItem(curIndex)->GetHandle());
	if(p_Dlg->CheckControl())
	{
		RefreshTaskXml();
		SaveRunTask();
		g_ThreadFinished = TRUE;
		
		/*
		if(p_Dlg->CheckCoord())
		{
			p_Dlg->DisableAllController();
			CString strTmp;
			p_Dlg->m_ComboInput.GetWindowText(strTmp);

			//定义开始时间
			p_Dlg->StartTickTime = ::GetTickCount();
			
			if(p_Dlg->m_chk_dem.GetCheck())
			{
				TaskProc.Task_RasterTransFormDEM(p_Dlg);
			}
			else
			{
				TaskProc.Task_RasterTransForm(p_Dlg);
			}
		}*/

		p_Dlg->DisableAllController();
		CString strTmp;
		p_Dlg->m_ComboInput.GetWindowText(strTmp);

		//定义开始时间
		p_Dlg->StartTickTime = ::GetTickCount();

		if(p_Dlg->m_chk_dem.GetCheck())
		{
			TaskProc.Task_RasterTransFormDEM(p_Dlg);
		}
		else
		{
			TaskProc.Task_RasterTransForm(p_Dlg);
		}
	}
}

void CDeuRasterView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	if(TasksMapping._task.GetCount() > 0)
	{
		for(int n=0; n<TasksMapping._task.GetCount(); n++)
		{
			//判断是否栅格
			if(TasksMapping._task.GetAt(n)->_type.text == "1")
			{
				((CDeuRasterFrame*)this->GetParentFrame())->m_PaneRaster.OnBnClickedTaskAdd();
				CDeuRasterTranDlg* p = (CDeuRasterTranDlg*)CWnd::FromHandle(m_wndTabControl.GetItem(m_wndTabControl.GetItemCount()-1)->GetHandle());
				CString m_str[10];
				m_str[0] = TasksMapping._task.GetAt(n)->_inpath.text;
				m_str[1] = TasksMapping._task.GetAt(n)->_outpath.text;
				m_str[2] = TasksMapping._task.GetAt(n)->_inCoordType.text;
				m_str[3] = TasksMapping._task.GetAt(n)->_outCoordType.text;
				m_str[4] = TasksMapping._task.GetAt(n)->_inEllipse.text;
				m_str[5] = TasksMapping._task.GetAt(n)->_outEllipse.text;
				m_str[6] = TasksMapping._task.GetAt(n)->_controlPath.text;
				m_str[7] = TasksMapping._task.GetAt(n)->_transModel.text;
				m_str[8] = TasksMapping._task.GetAt(n)->_inDriver.text;
				m_str[9] = TasksMapping._task.GetAt(n)->_outDriver.text;

				p->strGuid = TasksMapping._task.GetAt(n)->id;
				p->strLastPath = TasksMapping._task.GetAt(n)->_inpath.text;
				
				CString str;
				str = TasksMapping._task.GetAt(n)->_inDriver.text;
							
				int kk=0, nIndex=0;
				for(kk=0; kk<p->m_ComboInput.GetCount(); kk++)
				{
					nIndex = p->m_ComboInput.FindString(kk, TasksMapping._task.GetAt(n)->_inDriver.text);
					if(nIndex == -1){
						if(kk > p->m_ComboInput.GetCount()) break;
					}
					else{
						p->m_ComboInput.SetCurSel(kk);
					}
				}
				
				for(kk=0; kk<p->m_ComboOutput.GetCount(); kk++)
				{
					nIndex = p->m_ComboOutput.FindString(kk, TasksMapping._task.GetAt(n)->_outDriver.text);
					if(nIndex == -1){
						if(kk > p->m_ComboOutput.GetCount()) break;
					}
					else{
						p->m_ComboOutput.SetCurSel(kk);
					}
				}

				for(int k=0; k<TasksMapping._task.GetAt(n)->_parts.m_Part.GetCount(); k++)
				{
					p->_FilsList_selected.Add((TasksMapping._task.GetAt(n))->_parts.m_Part.GetAt(k).text);
				}
				p->LoadExistData(m_str);
			}
		}
	}
	else
	{
		((CDeuRasterFrame*)this->GetParentFrame())->m_PaneRaster.OnBnClickedTaskAdd();
	}
}

/*
	刷新新任务Xml	
*/
void CDeuRasterView::RefreshTaskXml()
{
	int ncount = m_wndTabControl.GetItemCount();

	//先清空数据容器，释放内存，防止内存泄漏
	//因为CArray会自动维护索引，所以数据的进出要小心

	//1. 筛查出栅格转换任务的总数
	int nTotal = 0;
	for(int n=0; n<TasksMapping._task.GetCount(); n++)
	{
		if(TasksMapping._task.GetAt(n)->_type.text == "1")
		{
			nTotal++;	
		}
	}

	//根据索引总数移除指定数量的栅格转换任务
	while(nTotal > 0)
	{
		for(int n=0; n<TasksMapping._task.GetCount(); n++)
		{
			if(TasksMapping._task.GetAt(n)->_type.text == "1")
			{
				(TasksMapping._task.GetAt(n))->_parts.m_Part.RemoveAll();
				
				delete TasksMapping._task.GetAt(n);
				//移除一个，总数减一个
				TasksMapping._task.RemoveAt(n);
				nTotal--;
			}
		}
	}

	//这里要线程池处理批量转换过程
	for(int m=0; m<ncount; m++)
	{
		//任务描述XML
		CDeuRasterTranDlg *p = ((CDeuRasterTranDlg*)CWnd::FromHandle(m_wndTabControl.GetItem(m)->GetHandle()));
		
		//更新转换任务		
		p_Task p_task = new _Task;
		p->m_edit_InputFile.GetWindowText(p_task->_inpath.text);	//这里实际保存的是实际的输入路径
		p->m_edit_OutputFile.GetWindowText(p_task->_outpath.text);	//这里实际保存的是实际的输出路径
		p->m_edit_InCoord.GetWindowText(p_task->_inCoordType.text);
		p->m_edit_OutCoord.GetWindowText(p_task->_outCoordType.text);
		p->m_ComboInput.GetWindowText(p_task->_inDriver.text);
		p->m_ComboOutput.GetWindowText(p_task->_outDriver.text);
		p->m_Controlpoint_Dlg.m_Edit_Src.GetWindowText(p_task->_inEllipse.text);
		p->m_Controlpoint_Dlg.m_Edit_Dest.GetWindowText(p_task->_outEllipse.text);

		p_task->_controlPath.text = p->m_Controlpoint_Dlg.m_strControlPath;
		p_task->_transModel.text = p->m_Controlpoint_Dlg.m_strModel;

		p_task->_status.text		  = RUNNING;
		p_task->_type.text		  = RASTER_TRANS;

		for(int n=0; n<p->_FilsList_selected.GetCount(); n++)
		{
			_Part _P;
			_P.text.Format("%s", p->_FilsList_selected.GetAt(n));
			p_task->_parts.m_Part.Add(_P);
		}

		TasksMapping._task.Add(p_task);
		//delete p_task;
	}
}