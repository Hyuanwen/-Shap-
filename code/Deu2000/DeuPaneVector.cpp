#include "stdafx.h"
#include "DeuPaneVector.h"

CDeuPaneVector::CDeuPaneVector(CWnd* pParent /*=NULL*/):CXTPDialog(CDeuPaneVector::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	nListIndex = 1;
}

void CDeuPaneVector::DoDataExchange(CDataExchange* pDX)
{
	CXTPDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
}

BEGIN_MESSAGE_MAP(CDeuPaneVector, CXTPDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BTN_TASK_REMOVE, &CDeuPaneVector::OnBnClickedTaskRemove)
	ON_BN_CLICKED(IDC_BTN_TASK_REMOVEALL, &CDeuPaneVector::OnBnClickedTaskRemoveAll)
	ON_BN_CLICKED(IDC_BTN_TASK_ADD, &CDeuPaneVector::OnBnClickedTaskAdd)
	ON_BN_CLICKED(IDC_BTN_TASK_BATADD, &CDeuPaneVector::OnBnClickedTaskBatAdd)
	ON_BN_CLICKED(IDC_BTN_TASK_PROCESS, &CDeuPaneVector::OnBnClickedTaskProcess)
	ON_LBN_SELCHANGE(IDC_LIST1, &CDeuPaneVector::OnLbnSelchange)
END_MESSAGE_MAP()

BOOL CDeuPaneVector::OnInitDialog()
{
	CXTPDialog::OnInitDialog();

	return TRUE;
}

void CDeuPaneVector::OnSysCommand(UINT nID, LPARAM lParam)
{	
	CXTPDialog::OnSysCommand(nID, lParam);	
}

void CDeuPaneVector::OnPaint() 
{
	if (IsIconic())
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
	}

	CXTPDialog::OnPaint();
}

HCURSOR CDeuPaneVector::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDeuPaneVector::OnSize(UINT nType, int cx, int cy) 
{
	CXTPDialog::OnSize(nType, cx, cy);

	if(m_ListBox.GetSafeHwnd())
	{
		CRect rect;
		this->GetClientRect(&rect);
		m_ListBox.SetWindowPos(&wndTop, 0, 0, rect.Width(), rect.bottom-100, SWP_SHOWWINDOW);

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

void CDeuPaneVector::OnBnClickedTaskAdd()
{
	p_View->OnAddTab();

	CString strName;	 
	strName.Format("矢量转换任务%d", nListIndex);
	InsertListItem(strName);
	nListIndex++;
}

/*
	批量增加
*/
void CDeuPaneVector::OnBnClickedTaskBatAdd()
{
	//AfxMessageBox("OnBnClickedTaskBatAdd");
}

/*
	删除转换任务
*/
void CDeuPaneVector::OnBnClickedTaskRemove()
{
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

/*
	移除所有
*/
void CDeuPaneVector::OnBnClickedTaskRemoveAll()
{
	while(m_ListBox.GetCount() > 0)
	{
		m_ListBox.DeleteString(0);
	}
	p_View->DelTabAll();
}

/*
	矢量执行
*/
void CDeuPaneVector::OnBnClickedTaskProcess()
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

void CDeuPaneVector::InsertListItem(const char *p_ItemName)
{
	int nIndex = m_ListBox.GetCount();
	m_ListBox.InsertString(nIndex, p_ItemName);	
}

void CDeuPaneVector::DelTaskItem(int nIndex)
{	
	this->m_ListBox.DeleteString(nIndex);
	p_View->DelTab(nIndex);
}

void CDeuPaneVector::OnLbnSelchange()
{
	p_View->TabSelectSel(m_ListBox.GetCurSel());
}
