// FileFormatSet.cpp : 实现文件
//

#include "stdafx.h"
#include "FileFormatSet.h"

// CFileFormatSet 对话框
IMPLEMENT_DYNAMIC(CFileFormatSet, CDialog)
CFileFormatSet::CFileFormatSet(CWnd* pParent /*=NULL*/)
	: CDialog(CFileFormatSet::IDD, pParent)
{
}

CFileFormatSet::~CFileFormatSet()
{
}

void CFileFormatSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_FROMAT, m_TabFormat);
	DDX_Control(pDX, IDC_LIST_VECTOR, m_ListVector);
	DDX_Control(pDX, IDC_LIST_RASTER, m_ListRaster);
}

BEGIN_MESSAGE_MAP(CFileFormatSet, CDialog)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_FROMAT, &CFileFormatSet::OnTcnSelchangeTabFromat)
	ON_BN_CLICKED(IDOK, &CFileFormatSet::OnBnClickedOk)
END_MESSAGE_MAP()

// CFileFormatSet 消息处理程序
BOOL CFileFormatSet::OnInitDialog()
{
	CDialog::OnInitDialog();

	//初始化Tab
	m_TabFormat.InsertItem(0, _T("矢量文件格式"));
	m_TabFormat.InsertItem(1, _T("栅格文件格式"));

	//初始化矢量list
	InitVectorList();

	//初始化矢量list	
	this->InitRasterList();

	m_ListVector.ShowWindow(SW_NORMAL);
	m_ListRaster.ShowWindow(SW_HIDE);

	return TRUE;
}

void CFileFormatSet::InitVectorList()
{
	m_ListVector.SetExtendedStyle(m_ListVector.GetExtendedStyle() | LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ListVector.InsertColumn(0, _T("是否选中"), LVCFMT_CENTER, 80);
	m_ListVector.InsertColumn(1, _T("文件格式"), LVCFMT_CENTER, 200);

	for (int i = 0; i < GobalFormat.FormatTypeList[0]->TypeList.size(); i++)
	{
		m_ListVector.InsertItem(i, _T(""));
		m_ListVector.SetItemText(i, 1, GobalFormat.FormatTypeList[0]->TypeList[i].text);
		if ( GobalFormat.FormatTypeList[0]->TypeList[i].type == _T("1"))
		{
			m_ListVector.SetCheck(i);
		}
	}
}

void CFileFormatSet::InitRasterList()
{
	m_ListRaster.SetExtendedStyle(m_ListRaster.GetExtendedStyle() | LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ListRaster.InsertColumn(0, _T("是否选中"), LVCFMT_CENTER, 80);
	m_ListRaster.InsertColumn(1, _T("文件格式"), LVCFMT_CENTER, 200);

	for (int i = 0; i < GobalFormat.FormatTypeList[1]->TypeList.size(); i++)
	{
		m_ListRaster.InsertItem(i, _T(""));
		m_ListRaster.SetItemText(i, 1, GobalFormat.FormatTypeList[1]->TypeList[i].text);
		if ( GobalFormat.FormatTypeList[1]->TypeList[i].type == _T("1"))
		{
			m_ListRaster.SetCheck(i);
		}
	}
}

void CFileFormatSet::OnTcnSelchangeTabFromat(NMHDR *pNMHDR, LRESULT *pResult)
{
	int iSel = m_TabFormat.GetCurSel();

	switch (iSel)
	{
	case 0:
		m_ListVector.ShowWindow(SW_NORMAL);
		m_ListRaster.ShowWindow(SW_HIDE);
		break;

	case 1:
		m_ListRaster.ShowWindow(SW_NORMAL);
		m_ListVector.ShowWindow(SW_HIDE);
		break;

	default:
		break;
	}
	*pResult = 0;
}

void CFileFormatSet::OnBnClickedOk()
{
	for (int i = 0; i < TasksMapping._task.GetCount(); i++)
	{
		//保存栅格格式
		if (TasksMapping._task.GetAt(i)->_type.text == _T("1"))
		{
			for (int k = 0; k < m_ListRaster.GetItemCount(); k++)
			{
				if (m_ListRaster.GetCheck(k))
				{
					//TasksMapping._task.GetAt(i)->_formats.m_Formats.GetAt(k).type = _T("1");
				}
				else
				{
					//TasksMapping._task.GetAt(i)->_formats.m_Formats.GetAt(k).type = _T("0");
				}
			}
		}
	}

	for (int k = 0; k < m_ListVector.GetItemCount(); k++)
	{
		if (m_ListVector.GetCheck(k))
		{
			GobalFormat.FormatTypeList[0]->TypeList[k].type = _T("1");
		}
		else
		{
			GobalFormat.FormatTypeList[0]->TypeList[k].type = _T("0");
		}
	}

	
	for (int k = 0; k < m_ListRaster.GetItemCount(); k++)
	{
		if (m_ListRaster.GetCheck(k))
		{
			GobalFormat.FormatTypeList[1]->TypeList[k].type = _T("1");
		}
		else
		{
			GobalFormat.FormatTypeList[1]->TypeList[k].type = _T("0");
		}
	}
	
	//写文件
	SaveFormatXml();
	
	OnOK();
}
