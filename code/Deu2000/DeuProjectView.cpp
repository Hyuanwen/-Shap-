// DeuProjectView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DeuProjectFrame.h"
#include "DeuGlobalMainFrm.h"
#include "DeuProjectView.h"

// CDeuProjectView
IMPLEMENT_DYNCREATE(CDeuProjectView, CView)
CDeuProjectView::CDeuProjectView()
{
	nTabHistoryIndex = 1;
}

CDeuProjectView::~CDeuProjectView()
{
}

BEGIN_MESSAGE_MAP(CDeuProjectView, CView)
	ON_WM_SIZE()
	ON_WM_CREATE()
	//ON_NOTIFY_REFLECT(NM_CLICK, &CTabCtrlEx::OnNMClick)
	//ON_MESSAGE(WM_LBUTTONDOWN, IDC_TAB1, &CDeuProjectView::OnTabClose)
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CDeuProjectView ��ͼ
void CDeuProjectView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���
}

// CDeuProjectView ���
#ifdef _DEBUG
void CDeuProjectView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CDeuProjectView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc); 
}
#endif
#endif //_DEBUG

CDeuProjectDoc* CDeuProjectView::GetDocument() const
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDeuProjectDoc)));
	return (CDeuProjectDoc*)m_pDocument;
}

// CDeuProjectView ��Ϣ�������
void CDeuProjectView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	if (m_wndTabControl.GetSafeHwnd())
	{
		m_wndTabControl.MoveWindow(0, 0, cx, cy);
	}
}

int CDeuProjectView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	//1. �������Ķ���ŵ��������Ա㽫�����Ҷ���
	_ViewRasterList.Add(this);

	//2. ����TabCtrl �л�ҳ
	m_wndTabControl.Create(WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS, CRect(0, 0, 0, 0), this, IDC_TAB1);	
	m_wndTabControl.SetOwner(this);
	m_wndTabControl.pPanelWnd = &((CDeuProjectFrame*)this->GetParentFrame())->m_PaneProject;
	lstrcpy(m_wndTabControl.sz_Type, "Raster");
	m_wndTabControl.GetPaintManager()->SetAppearance(xtpTabAppearancePropertyPage2003);
	//m_wndTabControl.GetPaintManager()->m_bHotTracking = TRUE;
	m_wndTabControl.GetPaintManager()->m_bShowIcons = TRUE;	
	m_wndTabControl.GetPaintManager()->DisableLunaColors(FALSE);
	m_wndTabControl.ShowCloseItemButton();

	return 0;
}

void CDeuProjectView::OnAddTab()
{
	if(m_wndTabControl.GetSafeHwnd())
	{
		CString strName;		
		strName.Format("ת������%d", nTabHistoryIndex);
		CDeuRasterProjectTranDlg* p_RasterDlg = new CDeuRasterProjectTranDlg;
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
 ����:	����TabCtrlҳ����
 ����:	pViewClass
	    lpszTitle
		nIcon

 ����:	BOOL 
 ����:  2010-12-29
 ��ע:  Add by hushichen
=============================================
*/
BOOL CDeuProjectView::AddView(CRuntimeClass* pViewClass, LPCTSTR lpszTitle, int nIcon)
{
	CCreateContext contextT;
	contextT.m_pCurrentDoc     = GetDocument();
	contextT.m_pNewViewClass   = pViewClass;
	contextT.m_pNewDocTemplate = GetDocument()->GetDocTemplate();

	CWnd* pWnd;
	
	TRY
	{
		pWnd = (CWnd*)pViewClass->CreateObject();
		
		if (pWnd == NULL)
		{
			AfxThrowMemoryException();
		}
	}
	CATCH_ALL(e)
	{
		TRACE0( "������ͼ�ڴ����.\n" );
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

/* ������ */
void CDeuProjectView::ActiveParentFrm()
{
	this->GetParentFrame()->ActivateFrame();
	this->UpdateWindow();
}

/*
=============================================   
 ����:	ɾ��ָ��tab�����ͷŴ���ָ��
 ����:  int nTabIndex	 Tab����
		int nArrayIndex  ��������
		
 ��ע:	TabCtrl���������Զ�ά������������������
		�Զ�ά��.����Ҫ����������
		
 ����:	2010-12-29
=============================================
*/
void CDeuProjectView::DelTab(int nTabIndex)
{	

	//�ͷ�ָ��,��һ��ӿ��Ƿ���׼ȷ�ͷ��ڴ棬������ڴ�й¶�д���֤��Ŀǰ��ʱû�з�����й¶
	delete (CDeuRasterProjectTranDlg*)CWnd::FromHandle(m_wndTabControl.GetItem(nTabIndex)->GetHandle());
	m_wndTabControl.DeleteItem(nTabIndex);

	//delete p_wnd;
	//delete _TabRasterList.GetAt(nTabIndex);
	
	RefreshTaskXml();
	SaveRunTask();
}

/*
	ɾ������item
*/
void CDeuProjectView::DelTabAll()
{
	while(m_wndTabControl.GetItemCount() > 0)
	{		
		DelTab(0);
	}
	RefreshTaskXml();
	SaveRunTask();
}

/*
	���ٿ����ͼ
		֪ͨ�������ؼ�Ĩȥ��Ӧ�ڵ�

	��ע��������ֻ��һ����ͼ������¿���ʹ�ã���
		  һ��N����ͼ�¾�Ҫ���ӿ�������ڵ�Ĩȥ������
*/
void CDeuProjectView::OnDestroy()
{	
	CView::OnDestroy();

	for(int n=0; n<_ViewRasterList.GetCount(); n++)
	{
		if(_ViewRasterList.GetAt(n) == this)
		{
			//Ĩȥ�ڵ�			
			_ViewRasterList.RemoveAt(n);
			((CDeuGlobalMainFrame*)AfxGetMainWnd())->m_wndTaskPanel.OnDeleteNode(RASTER, n);
			break;
		}
	}
}

void CDeuProjectView::TabSelectSel(int nIndex)
{
	m_wndTabControl.SetCurSel(nIndex);
}

/* 
	
	դ��ִ��ת������

*/
void CDeuProjectView::ProcessTask()
{
	if(!GobalUserInfo.IsRasterConvert)
	{
		MessageBox(PowerError,"ϵͳ��ʾ", MB_OK|MB_ICONWARNING);
		return;
	}

	int ncount = m_wndTabControl.GetItemCount();
	if(ncount == 0)
	{
		MessageBox("��ת������ִ��","ϵͳ��ʾ", MB_OK|MB_ICONWARNING);
		return;
	}

	int curIndex = m_wndTabControl.GetCurSel();
	CDeuRasterProjectTranDlg* p_Dlg = (CDeuRasterProjectTranDlg*)CWnd::FromHandle(m_wndTabControl.GetItem(curIndex)->GetHandle());
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

			//���忪ʼʱ��
			p_Dlg->StartTickTime = ::GetTickCount();
			
			if(p_Dlg->m_chk_dem.GetCheck())
			{
			//	TaskProc.Task_RasterTransFormDEM(p_Dlg);
			}
			else
			{
				TaskProc.Task_RasterProjectTransForm(p_Dlg);
			}
		}*/

		p_Dlg->DisableAllController();
		CString strTmp;
		p_Dlg->m_ComboInput.GetWindowText(strTmp);

		//���忪ʼʱ��
		p_Dlg->StartTickTime = ::GetTickCount();

		if(p_Dlg->m_chk_dem.GetCheck())
		{
			//	TaskProc.Task_RasterTransFormDEM(p_Dlg);
		}
		else
		{
			TaskProc.Task_RasterProjectTransForm(p_Dlg);
		}
	}
}

void CDeuProjectView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	if(TasksMapping._task.GetCount() > 0)
	{
		for(int n=0; n<TasksMapping._task.GetCount(); n++)
		{
			//�ж��Ƿ�դ��
			if(TasksMapping._task.GetAt(n)->_type.text == "1")
			{
				((CDeuProjectFrame*)this->GetParentFrame())->m_PaneProject.OnBnClickedTaskAdd();
				CDeuRasterProjectTranDlg* p = (CDeuRasterProjectTranDlg*)CWnd::FromHandle(m_wndTabControl.GetItem(m_wndTabControl.GetItemCount()-1)->GetHandle());
				CString m_str[6];
				m_str[0] = TasksMapping._task.GetAt(n)->_inpath.text;
				m_str[1] = TasksMapping._task.GetAt(n)->_outpath.text;
				m_str[2] = TasksMapping._task.GetAt(n)->_inCoordType.text;
				m_str[3] = TasksMapping._task.GetAt(n)->_outCoordType.text;
				m_str[4] = TasksMapping._task.GetAt(n)->_inEllipse.text;
				m_str[5] = TasksMapping._task.GetAt(n)->_outEllipse.text;

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
		((CDeuProjectFrame*)this->GetParentFrame())->m_PaneProject.OnBnClickedTaskAdd();
	}
}

/*
	ˢ��������Xml	
*/
void CDeuProjectView::RefreshTaskXml()
{
	int ncount = m_wndTabControl.GetItemCount();

	//����������������ͷ��ڴ棬��ֹ�ڴ�й©
	//��ΪCArray���Զ�ά���������������ݵĽ���ҪС��

	//1. ɸ���դ��ת�����������
	int nTotal = 0;
	for(int n=0; n<TasksMapping._task.GetCount(); n++)
	{
		if(TasksMapping._task.GetAt(n)->_type.text == "1")
		{
			nTotal++;	
		}
	}

	//�������������Ƴ�ָ��������դ��ת������
	while(nTotal > 0)
	{
		for(int n=0; n<TasksMapping._task.GetCount(); n++)
		{
			if(TasksMapping._task.GetAt(n)->_type.text == "1")
			{
				(TasksMapping._task.GetAt(n))->_parts.m_Part.RemoveAll();
				
				delete TasksMapping._task.GetAt(n);
				//�Ƴ�һ����������һ��
				TasksMapping._task.RemoveAt(n);
				nTotal--;
			}
		}
	}

	//����Ҫ�̳߳ش�������ת������
	for(int m=0; m<ncount; m++)
	{
		//��������XML
		CDeuRasterProjectTranDlg *p = ((CDeuRasterProjectTranDlg*)CWnd::FromHandle(m_wndTabControl.GetItem(m)->GetHandle()));
		
		//����ת������		
		p_Task p_task = new _Task;
		p->m_edit_InputFile.GetWindowText(p_task->_inpath.text);	//����ʵ�ʱ������ʵ�ʵ�����·��
		p->m_edit_OutputFile.GetWindowText(p_task->_outpath.text);	//����ʵ�ʱ������ʵ�ʵ����·��
		p->m_edit_InCoord.GetWindowText(p_task->_inCoordType.text);
		p->m_edit_OutCoord.GetWindowText(p_task->_outCoordType.text);
		p->m_ComboInput.GetWindowText(p_task->_inDriver.text);
		p->m_ComboOutput.GetWindowText(p_task->_outDriver.text);
		p->m_Controlpoint_Dlg.m_Edit_Src.GetWindowText(p_task->_inEllipse.text);
		p->m_Controlpoint_Dlg.m_Edit_Dest.GetWindowText(p_task->_outEllipse.text);

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