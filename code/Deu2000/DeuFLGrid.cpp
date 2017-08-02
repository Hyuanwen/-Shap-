// DeuFLGrid.cpp : 实现文件

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

// DeuFLGrid 消息处理程序
void DeuFLGrid::OnBnClickedButtonBr()
{
	CFileDialog strOpenFile (TRUE,"","",OFN_FILEMUSTEXIST |OFN_HIDEREADONLY,"shp文件(*.shp)|*.shp||",NULL);
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
	/*                            获取扩展名                                */
	/************************************************************************/
	strExtName = strFileName.Mid(strFileName.ReverseFind('\\'), strFileName.GetLength());
	/************************************************************************/
	/*                        拼装新的文件名和全路径文件名                  */
	/************************************************************************/		
	strTmpPathName = strFileNamec+ strExtName;
	/************************************************************************/
	/*                             文件重命名                               */
	/************************************************************************/
}

void DeuFLGrid::OnclickFOK()
{
	double step = 1000;
	GeneralGridForShp((LPCSTR)_bstr_t(strFileName) ,(LPCSTR)_bstr_t(strTmpPathName) , step);
	OnOK();
}
