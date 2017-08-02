// DeuViewDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DeuViewDlg.h"


// CDeuViewDlg 对话框

IMPLEMENT_DYNAMIC(CDeuViewDlg, CXTPDialog)

CDeuViewDlg::CDeuViewDlg(CWnd* pParent /*=NULL*/)
	: CXTPDialog(CDeuViewDlg::IDD, pParent)
{

}

CDeuViewDlg::~CDeuViewDlg()
{
}

void CDeuViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CXTPDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDeuViewDlg, CXTPDialog)
		ON_WM_SIZE()
END_MESSAGE_MAP()


// CDeuViewDlg 消息处理程序

BOOL CDeuViewDlg::OnInitDialog()
{
	CXTPDialog::OnInitDialog();

	VERIFY(InitCommandBars());
	CXTPCommandBars* pCommandBars = GetCommandBars();

	CXTPToolBar* pToolBar = pCommandBars->Add(_T("视图工具条"), xtpBarTop);
	pToolBar->LoadToolBar(IDR_TOOLBAR1);

	//*((CXTPControlButton*)pToolBar->GetControls()->FindControl(xtpControlButton, ID_BUTTON_PLAY, TRUE, FALSE))->SetStyle(xtpButtonIconAndCaption);
	//((CXTPControlButton*)pToolBar->GetControls()->FindControl(xtpControlButton, ID_BUTTON_STOP, TRUE, FALSE))->SetStyle(xtpButtonIconAndCaption);
	//((CXTPControlButton*)pToolBar->GetControls()->FindControl(xtpControlButton, ID_BUTTON_PAUSE, TRUE, FALSE))->SetStyle(xtpButtonIconAndCaption);*/
	pToolBar->GetControls()->CreateOriginalControls();
	pCommandBars->GetToolTipContext()->SetStyle(xtpToolTipOffice);
	

	return TRUE;
}


void CDeuViewDlg::OnSize(UINT nType, int cx, int cy)
{
	CXTPDialog::OnSize(nType, cx, cy);

	CRect rcClient(0, 0, cx, cy);
	RepositionBars(0, 0xffff, AFX_IDW_PANE_FIRST, 0, 0, &rcClient);
	RepositionBars(0, 0xffff, AFX_IDW_PANE_FIRST, reposQuery, &rcClient, &rcClient);

	CListBox* p_listbox = (CListBox*)GetDlgItem(IDC_LIST1);
	if(p_listbox->GetSafeHwnd())
	if(cx < 500 && cy < 500){
		p_listbox->MoveWindow(0, 35, 500, 500-35);
	}
	else{
		p_listbox->MoveWindow(0, 35, cx, cy-35);
	}

}
