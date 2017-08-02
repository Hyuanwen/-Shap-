// DeuVectorView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DeuVectorView.h"
#include "DeuVectorFrame.h"
#include "DeuGlobalMainFrm.h"

/*************************************

		CDeuVectorView

**************************************/
IMPLEMENT_DYNCREATE(CDeuVectorView, CView)

CDeuVectorView::CDeuVectorView()
			   :CView()
{
	nTabHistoryIndex = 1;
}

CDeuVectorView::~CDeuVectorView()
{
}

BEGIN_MESSAGE_MAP(CDeuVectorView, CView)
	ON_WM_SIZE()
	ON_WM_CREATE()	
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CDeuVectorView ��ͼ
void CDeuVectorView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���
}

// CDeuVectorView ���
#ifdef _DEBUG
void CDeuVectorView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CDeuVectorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG

CDeuVectorDoc* CDeuVectorView::GetDocument() const
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDeuVectorDoc)));
	return (CDeuVectorDoc*)m_pDocument;
}
 
// CDeuVectorView ��Ϣ�������
void CDeuVectorView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	
	/*if(m_vdlg.GetSafeHwnd())
	{
		m_vdlg.SetWindowPos(&wndTop, 3, 3, cx-6, cy-6, SWP_SHOWWINDOW);
	}*/

	if (m_wndTabControl.GetSafeHwnd())
	{
		m_wndTabControl.MoveWindow(0, 0, cx, cy);
	}
}

void CDeuVectorView::DoDataExchange(CDataExchange* pDX)
{
	CView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDeuPaneProperty)
	//}}AFX_DATA_MAP
}

int CDeuVectorView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	CView::OnInitialUpdate();	
		
	//1. �������Ķ���ŵ��������Ա㽫�����Ҷ���
	_ViewVectorList.Add(this);
		
	//2. ����TabCtrl
	m_wndTabControl.Create(WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS, CRect(0, 0, 0, 0), this, IDC_TAB1);
	m_wndTabControl.SetOwner(this);
	lstrcpy(m_wndTabControl.sz_Type, "Vector");
	m_wndTabControl.pPanelWnd = &((CDeuVectorFrame*)this->GetParentFrame())->m_PaneVector;
	m_wndTabControl.GetPaintManager()->SetAppearance(xtpTabAppearancePropertyPage2003);
	m_wndTabControl.GetPaintManager()->m_bHotTracking = TRUE;
	m_wndTabControl.GetPaintManager()->m_bShowIcons = TRUE;	
	m_wndTabControl.GetPaintManager()->DisableLunaColors(FALSE);
	m_wndTabControl.ShowCloseItemButton();

	//AddView(RUNTIME_CLASS(CDeuVectorTranDlg), "ת������1", 0);
	//this->OnAddTab();

	return 0;
}

void CDeuVectorView::OnAddTab()
{
	if(m_wndTabControl.GetSafeHwnd())
	{
		CString strName;
		strName.Format("ת������%d", nTabHistoryIndex);

		CDeuVectorTranDlg* p_RasterDlg = new CDeuVectorTranDlg;
		p_RasterDlg->Create(IDD_DLG_TASK, &m_wndTabControl);
		//::_TabVectorList.Add(p_RasterDlg);
		
		int nTab = m_wndTabControl.GetItemCount();
		CXTPTabManagerItem* p_CurTab = m_wndTabControl.InsertItem(nTab, (LPCTSTR)strName, p_RasterDlg->GetSafeHwnd(), 0);	
		m_wndTabControl.SetSelectedItem(p_CurTab);
		nTabHistoryIndex++;

		//AddView(RUNTIME_CLASS(CDeuVectorTranDlg), strName, 0);
	}
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
BOOL CDeuVectorView::AddView(CRuntimeClass* pViewClass, LPCTSTR lpszTitle, int nIcon)
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
		TRACE0( "Out of memory creating a view.\n" );
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
		TRACE0( "Warning: ���ܴ����ͻ�����ͼ.\n" );		
		return NULL;
	}
	
	//::_TabVectorList.Add(pWnd);

	CXTPTabManagerItem* p_CurTab = m_wndTabControl.InsertItem(nTab, lpszTitle, pWnd->GetSafeHwnd(), nIcon);
	m_wndTabControl.SetSelectedItem(p_CurTab);

	pWnd->SetOwner(this);

	return TRUE;
}

/* ������ */
void CDeuVectorView::ActiveParentFrm()
{
	this->GetParentFrame()->ActivateFrame();
	this->UpdateWindow();
}

void CDeuVectorView::OnDestroy()
{
	CView::OnDestroy();

	for(int n=0; n<_ViewVectorList.GetCount(); n++)
	{
		if(_ViewVectorList.GetAt(n) == this)
		{
			_ViewVectorList.RemoveAt(n);
			((CDeuGlobalMainFrame*)AfxGetMainWnd())->m_wndTaskPanel.OnDeleteNode(VECTOR, n);
			break;
		}
	}

	//DelTabAll
	while(m_wndTabControl.GetItemCount() > 0)
	{				
		delete ((CDeuVectorTranDlg*)CWnd::FromHandle(m_wndTabControl.GetItem(0)->GetHandle()));
		m_wndTabControl.DeleteItem(0);
	}
}

void CDeuVectorView::DelTab(int nIndex)
{
	/*
	((CDeuVectorTranDlg*)CWnd::FromHandle(m_wndTabControl.GetItem(nIndex)->GetHandle()))->DestroyWindow();
	delete (CDeuVectorTranDlg*)CWnd::FromHandle(m_wndTabControl.GetItem(nIndex)->GetHandle());
	m_wndTabControl.DeleteItem(nIndex);*/

	//�ͷ�ָ��
	delete ((CDeuVectorTranDlg*)CWnd::FromHandle(m_wndTabControl.GetItem(nIndex)->GetHandle()));
	m_wndTabControl.DeleteItem(nIndex);
	RefreshTaskXml();
	SaveRunTask();
}

void CDeuVectorView::DelTabAll()
{
	while(m_wndTabControl.GetItemCount() > 0)
	{				
		DelTab(0);
	}
	RefreshTaskXml();
	SaveRunTask();
}

void CDeuVectorView::TabSelectSel(int nIndex)
{
	m_wndTabControl.SetCurSel(nIndex);
}

void CDeuVectorView::ProcessTask()
{

	if(!GobalUserInfo.IsRasterConvert)
	{
		MessageBox(PowerError,"ϵͳ��ʾ", MB_OK|MB_ICONWARNING);
		return;
	}

	//�������ﻹҪ�����̳߳�ת���������̵�����
	//Ŀǰ���������߳������߳�

	int ncount = m_wndTabControl.GetItemCount();
	if(ncount == 0)
	{
		MessageBox("��ת������ִ��","ϵͳ��ʾ", MB_OK|MB_ICONWARNING);
		return;
	}

	int curIndex = m_wndTabControl.GetCurSel();
	CDeuVectorTranDlg* p_Dlg = (CDeuVectorTranDlg*)CWnd::FromHandle(m_wndTabControl.GetItem(curIndex)->GetHandle());
	if(p_Dlg->CheckControl())
	{
		RefreshTaskXml();
		SaveRunTask();

		/*
		if(p_Dlg->CheckCoord()) //yzg 2013-4-26 ��ʱ��������ϵ�Ƿ���ڵļ�鹦��
		{
			p_Dlg->DisableAllController();
			//TaskProc ȫ�ֶ������
			g_ThreadFinished = TRUE;
			TaskProc.Task_VectorTransForm(p_Dlg);
		}*/

		p_Dlg->DisableAllController();
		//TaskProc ȫ�ֶ������
		g_ThreadFinished = TRUE;
		TaskProc.Task_VectorTransForm(p_Dlg);
	}
}

//ͨ������XML��ԭ������״̬
void CDeuVectorView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	if(TasksMapping._task.GetCount() > 0)
	{
		for(int n=0; n<TasksMapping._task.GetCount(); n++)
		{
			if(TasksMapping._task.GetAt(n)->_type.text != "0") continue;

			((CDeuVectorFrame*)this->GetParentFrame())->m_PaneVector.OnBnClickedTaskAdd();
			CDeuVectorTranDlg* p = (CDeuVectorTranDlg*)CWnd::FromHandle(m_wndTabControl.GetItem(m_wndTabControl.GetItemCount()-1)->GetHandle());
			CString m_str[10];	

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

			//��������ݿ�����
			if(TasksMapping._task.GetAt(n)->_inDriver.text == sz_TranType_Vector[4])
			{
				ORACLEINFO m_Oracle;
				PasterDBConn(TasksMapping._task.GetAt(n)->_inpath.text, &m_Oracle);
				//m_str[0].Format("Provider=OraOLEDB.Oracle;Data Source=%s;user id=%s;password=%s", m_Oracle.strSID, m_Oracle.strUser,m_Oracle.strPwd);
				m_str[0].Format(_T("Provider=oraoledb.oracle.1; Data Source=%s; User Id=%s; Password=%s; persist security info=false"), m_Oracle.strSID, m_Oracle.strUser,m_Oracle.strPwd);

				p->strDBSid_Src = m_Oracle.strSID;
				p->strDBUser_Src = m_Oracle.strUser;
				p->strDBPwd_Src  = m_Oracle.strPwd;

				p->m_ComboInput.SetCurSel(4);
				for(int k=0; k<TasksMapping._task.GetAt(n)->_parts.m_Part.GetCount(); k++)
				{
					p->_TablesList_selected.Add(TasksMapping._task.GetAt(n)->_parts.m_Part.GetAt(k).text);
				}	
			}// end ��������ݿ�����
			else
			{
				//��������������	
				m_str[0] = TasksMapping._task.GetAt(n)->_inpath.text;

				int nItem = 0, nIndex=0;
				while(nIndex = (p->m_ComboInput.FindString(nItem, TasksMapping._task.GetAt(n)->_inDriver.text)))
				{
					nItem++;
					if(nIndex == -1) 
					{
						if(nItem > p->m_ComboInput.GetCount()) break;
					}
					else
					{
						p->m_ComboInput.SetCurSel(nIndex);break;
					}
				}
				for(int k=0; k<TasksMapping._task.GetAt(n)->_parts.m_Part.GetCount(); k++)
				{
					p->_FilsList_selected.Add(TasksMapping._task.GetAt(n)->_parts.m_Part.GetAt(k).text);
				}
			}// end if �������������

			//��������ݿ������ж�
			if(TasksMapping._task.GetAt(n)->_outDriver.text == sz_TranType_Vector[4])
			{
				ORACLEINFO m_Oracle;										
				PasterDBConn(TasksMapping._task.GetAt(n)->_outpath.text, &m_Oracle);
				//m_str[1].Format(_T("Provider=OraOLEDB.Oracle;Data Source=%s;user id=%s;password=%s"), m_Oracle.strSID, m_Oracle.strUser,m_Oracle.strPwd);
				m_str[1].Format(_T("Provider=oraoledb.oracle.1; Data Source=%s; User Id=%s; Password=%s; persist security info=false"), m_Oracle.strSID, m_Oracle.strUser,m_Oracle.strPwd);

				p->strDBSid_Dest  = m_Oracle.strSID;
				p->strDBUser_Dest = m_Oracle.strUser;
				p->strDBPwd_Dest  = m_Oracle.strPwd;

				p->m_ComboOutput.SetCurSel(4);
			}
			else
			{	
				m_str[1] = TasksMapping._task.GetAt(n)->_outpath.text;

				int nItem = 0, nIndex=0;
				while(nIndex = (p->m_ComboOutput.FindString(nItem, TasksMapping._task.GetAt(n)->_outDriver.text)))
				{				
					nItem++;
					if(nIndex == -1) 
					{
						if(nItem > p->m_ComboOutput.GetCount()) break;
					}
					else
					{
						p->m_ComboOutput.SetCurSel(nIndex); break;
					}
				}
			}
			p->LoadExistData(m_str);
		}// end for each  TasksMapping._task
	}
	else
	{
		((CDeuVectorFrame*)this->GetParentFrame())->m_PaneVector.OnBnClickedTaskAdd();
	}
}

/*
	ˢ��������Xml	
*/
void CDeuVectorView::RefreshTaskXml()
{
	int ncount = m_wndTabControl.GetItemCount();

	//����������������ͷ��ڴ棬��ֹ�ڴ�й©
	//��ΪCArray���Զ�ά���������������ݵĽ���ҪС��

	//1. ɸ���դ��ת�����������
	int nTotal = 0;
	for(int n=0; n<TasksMapping._task.GetCount(); n++)
	{
		if(TasksMapping._task.GetAt(n)->_type.text == "0")
		{
			nTotal++;
		}
	}

	//�������������Ƴ�ָ��������դ��ת������
	while(nTotal > 0)
	{
		for(int n=0; n<TasksMapping._task.GetCount(); n++)
		{
			if(TasksMapping._task.GetAt(n)->_type.text == "0")
			{
				TasksMapping._task.GetAt(n)->_parts.m_Part.RemoveAll();

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
		CDeuVectorTranDlg *p = ((CDeuVectorTranDlg*)CWnd::FromHandle(m_wndTabControl.GetItem(m)->GetHandle()));
		
		p_Task _task = new _Task;
		p->m_ComboInput.GetWindowText(_task->_inDriver.text);
		p->m_ComboOutput.GetWindowText(_task->_outDriver.text);
		
		p->m_edit_InCoord.GetWindowText(_task->_inCoordType.text);
		p->m_edit_OutCoord.GetWindowText(_task->_outCoordType.text);

		if(_task->_inDriver.text == sz_TranType_Vector[4]){
			_task->_inpath.text = p->strDBSid_Src + ","+p->strDBUser_Src+","+p->strDBPwd_Src;
		}
		else{
			p->m_edit_InputFile.GetWindowText(_task->_inpath.text);		//����ʵ�ʱ������ʵ�ʵ�����·��
		}

		if(_task->_outDriver.text == sz_TranType_Vector[4] ){
			_task->_outpath.text = p->strDBSid_Dest + ","+p->strDBUser_Dest+","+p->strDBPwd_Dest;
		}
		else{
			p->m_edit_OutputFile.GetWindowText(_task->_outpath.text);	//����ʵ�ʱ������ʵ�ʵ����·��	
		}
		
		p->m_Controlpoint_Dlg.m_Edit_Src.GetWindowText(_task->_inEllipse.text);
		p->m_Controlpoint_Dlg.m_Edit_Dest.GetWindowText(_task->_outEllipse.text);

		//������Ƶ�·�� add by chenyong 2013-3-28
		_task->_controlPath.text = p->m_Controlpoint_Dlg.m_strControlPath;
		_task->_transModel.text = p->m_Controlpoint_Dlg.m_strModel;

		_task->_status.text		  = RUNNING;
		_task->_type.text		  = VECTOR_TRANS;

		//Oracle
		if(_task->_inDriver.text == sz_TranType_Vector[4])
		{
			for(int n=0; n<p->_TablesList_selected.GetCount(); n++)
			{
				_Part _P;
				_P.text.Format("%s", p->_TablesList_selected.GetAt(n));
				_task->_parts.m_Part.Add(_P);
			}
		}
		//�ļ�
		else
		{
			for(int n=0; n<p->_FilsList_selected.GetCount(); n++)
			{
				_Part _P;
				_P.text.Format("%s", p->_FilsList_selected.GetAt(n));
				_task->_parts.m_Part.Add(_P);
			}
		}

		//����ת������
		TasksMapping._task.Add(_task);
		//delete _task;
	}	
}