#include "stdafx.h"
#include "DeuPaneProject.h"

CDeuPaneProject::CDeuPaneProject(CWnd* pParent /*=NULL*/):CXTPDialog(CDeuPaneProject::IDD, pParent)
{
	nListIndex = 0;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDeuPaneProject::DoDataExchange(CDataExchange* pDX)
{
	CXTPDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
}

BEGIN_MESSAGE_MAP(CDeuPaneProject, CXTPDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BTN_TASK_REMOVE, &CDeuPaneProject::OnBnClickedTaskRemove)
	ON_BN_CLICKED(IDC_BTN_TASK_REMOVEALL, &CDeuPaneProject::OnBnClickedTaskRemoveAll)
	ON_BN_CLICKED(IDC_BTN_TASK_ADD, &CDeuPaneProject::OnBnClickedTaskAdd)
	ON_BN_CLICKED(IDC_BTN_TASK_BATADD, &CDeuPaneProject::OnBnClickedTaskBatAdd)
	ON_BN_CLICKED(IDC_BTN_TASK_PROCESS, &CDeuPaneProject::OnBnClickedTaskProcess)
	ON_LBN_SELCHANGE(IDC_LIST1, &CDeuPaneProject::OnLbnSelchange)
END_MESSAGE_MAP()

// CDeuPaneProperty message handlers
BOOL CDeuPaneProject::OnInitDialog()
{
	CXTPDialog::OnInitDialog();
	
	//InsertListItem((LPCSTR)"栅格转换任务1");
	//nListIndex++;

	return 1;
}

void CDeuPaneProject::OnSysCommand(UINT nID, LPARAM lParam)
{	
	CXTPDialog::OnSysCommand(nID, lParam);	
}

void CDeuPaneProject::OnPaint() 
{
	/*if (IsIconic())
	{
		CPaintDC dc(this);
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		
	}*/

	CXTPDialog::OnPaint();
}

HCURSOR CDeuPaneProject::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDeuPaneProject::OnSize(UINT nType, int cx, int cy) 
{
	CXTPDialog::OnSize(nType, cx, cy);

	if(m_ListBox.GetSafeHwnd())
	{
		CRect rect;
		this->GetClientRect(&rect);
		m_ListBox.SetWindowPos(&wndTop, 0, 0, rect.Width(), rect.bottom-100, SWP_SHOWWINDOW);
		m_ListBox.Invalidate(TRUE);

		CButton* p_btn_process	  = (CButton*)this->GetDlgItem(IDC_BTN_TASK_PROCESS);
		CButton* p_btn_remove	  = (CButton*)this->GetDlgItem(IDC_BTN_TASK_REMOVE);
		CButton* p_btn_removeall  = (CButton*)this->GetDlgItem(IDC_BTN_TASK_REMOVEALL);
		CButton* p_add			  = (CButton*)this->GetDlgItem(IDC_BTN_TASK_ADD);
		CButton* p_batadd		  = (CButton*)this->GetDlgItem(IDC_BTN_TASK_BATADD);

		p_add->MoveWindow(rect.Width()/2-85, rect.bottom-90, 80, 25);
		p_add->Invalidate(TRUE);
		
		p_batadd->MoveWindow(rect.Width()/2+5, rect.bottom-90, 80, 25);
		p_batadd->Invalidate(TRUE);
		
		p_btn_remove->MoveWindow(rect.Width()/2-85, rect.bottom-60, 80, 25);
		p_btn_remove->Invalidate(TRUE);
		
		p_btn_removeall->MoveWindow(rect.Width()/2+5, rect.bottom-60, 80, 25);
		p_btn_removeall->Invalidate(TRUE);
		
		p_btn_process->MoveWindow(rect.Width()/2-85, rect.bottom-30, 170, 25);
		p_btn_process->Invalidate(TRUE);
	}

	Invalidate(TRUE);
}

void CDeuPaneProject::OnBnClickedTaskAdd()
{
	//1. 通知对应视图添加Tab页
	p_View->OnAddTab();

	//2. 插入List内容
	CString strName;
	strName.Format("栅格投影任务%d", nListIndex+1);
	this->InsertListItem((LPCSTR)strName);
	nListIndex++;
}

void CDeuPaneProject::OnBnClickedTaskBatAdd()
{
}

void CDeuPaneProject::OnBnClickedTaskRemove()
{
	//int m = m_ListBox.GetSelCount();
	int n = m_ListBox.GetCurSel();
	if(n >= 0)
	{				
		p_View->DelTab(n);
		m_ListBox.DeleteString(n);
		m_ListBox.SetCurSel(n-1);
	}
	else
	{
		AfxMessageBox("请选择删除的任务！");
	}
}

void CDeuPaneProject::OnBnClickedTaskRemoveAll()
{	
	while(m_ListBox.GetCount() > 0)
	{
		m_ListBox.DeleteString(0);
	}
	p_View->DelTabAll();
}

void CDeuPaneProject::OnBnClickedTaskProcess()
{
	if(g_ThreadFinished)
	{
		p_View->ProcessTask();		
	}
	else
	{
		AfxMessageBox("正在执行转换...");
	}
}

//写入List内容
void CDeuPaneProject::InsertListItem(const char *p_ItemName)
{	
	int nIndex = m_ListBox.GetCount();
	m_ListBox.InsertString(nIndex, p_ItemName);
	m_ListBox.SetItemData(nIndex, nListIndex);
}

/*
	此函数供Tab的CloseButton调用
	Tab -> Panel
*/
void CDeuPaneProject::DelTaskItem(int nIndex)
{
	p_View->DelTab(nIndex);
	this->m_ListBox.DeleteString(nIndex);
}

void CDeuPaneProject::OnLbnSelchange()
{
	p_View->TabSelectSel(m_ListBox.GetCurSel());
}
