// DeuDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DeuDlg.h"


// CDeuDlg �Ի���

IMPLEMENT_DYNAMIC(CDeuDlg, CDialog)

CDeuDlg::CDeuDlg(CWnd* pParent /*=NULL*/)
		: CDialog(CDeuDlg::IDD, pParent)
{

}

CDeuDlg::~CDeuDlg()
{
}

void CDeuDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDeuDlg, CDialog)


END_MESSAGE_MAP()


// CDeuDlg ��Ϣ�������

BOOL CDeuDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_paneManager.InstallDockingPanes(this);
	m_paneManager.SetTheme(xtpPaneThemeDefault);
	m_paneManager.UseSplitterTracker(FALSE);
	m_paneManager.SetShowContentsWhileDragging(TRUE);
	m_paneManager.SetAlphaDockingContext(TRUE);

	//����
	CXTPDockingPane* pwndTaskPane = m_paneManager.CreatePane(
		IDR_DATA, CRect(0, 0,250, 120), xtpPaneDockLeft);

	CXTPDockingPaneLayout layout(&m_paneManager);
	if (layout.Load(_T("NormalLayout"))) 
	{
		m_paneManager.SetLayout(&layout);
	}

	return TRUE;
}



