// DeuFLGrid.cpp : ʵ���ļ�

#include "stdafx.h"
#include "DeuFLGrid.h"
#include "GridMask.h"
#include "DeuFunction.h"

IMPLEMENT_DYNAMIC(DeuFLGrid, CDialog)
DeuFLGrid::DeuFLGrid(CWnd* pParent /*=NULL*/)
		 : CDialog(DeuFLGrid::IDD, pParent)
{
	m_EditPath = _T("");
}

DeuFLGrid::~DeuFLGrid()
{
}

void DeuFLGrid::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PATH, m_EditPath);
	DDX_Text(pDX, IDC_EDIT_PATHC, m_EditPathc);
}

BEGIN_MESSAGE_MAP(DeuFLGrid, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_BR, &DeuFLGrid::OnBnClickedButtonBr)
	ON_BN_CLICKED(IDC_BUTTON_BRC, &DeuFLGrid::OnBnClickedButtonBrc)
	ON_COMMAND(ID_OK, OnclickFOK)
END_MESSAGE_MAP()

// DeuFLGrid ��Ϣ�������
void DeuFLGrid::OnBnClickedButtonBr()
{
	CFileDialog strOpenFile (TRUE,"","",OFN_FILEMUSTEXIST |OFN_HIDEREADONLY,"shp�ļ�(*.shp)|*.shp||",NULL);
	if(strOpenFile.DoModal() == IDOK)
	{
		strFileName=strOpenFile.GetPathName();
	}

	m_EditPath=strFileName;
	UpdateData(FALSE);
}

void DeuFLGrid::OnBnClickedButtonBrc()
{
	char									dir[MAX_PATH] = {0};
	AfxSelectDirDlg(dir);

	CEdit* pf_edit2 = (CEdit*)GetDlgItem(IDC_EDIT_PATHC);
	if(strlen(dir) != 0)
	{
		pf_edit2->SetWindowText(dir);
	}	
	strFileNamec = dir;

	/************************************************************************/
	/*                            ��ȡ��չ��                                */
	/************************************************************************/
	strExtName = strFileName.Mid(strFileName.ReverseFind('\\'), strFileName.GetLength());
	/************************************************************************/
	/*                        ƴװ�µ��ļ�����ȫ·���ļ���                  */
	/************************************************************************/		
	strTmpPathName = strFileNamec+ strExtName;
	/************************************************************************/
	/*                             �ļ�������                               */
	/************************************************************************/
}

void DeuFLGrid::OnclickFOK()
{
	double step = 1000;
	GeneralGridForShp((LPCSTR)_bstr_t(strFileName) ,(LPCSTR)_bstr_t(strTmpPathName) , step);
	OnOK();
}
