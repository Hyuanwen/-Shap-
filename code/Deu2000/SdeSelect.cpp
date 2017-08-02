// SdeSelect.cpp : 实现文件

#include "stdafx.h"
#include "SdeSelect.h"

// CSdeSelect 对话框
IMPLEMENT_DYNAMIC(CSdeSelect, CDialog)

CSdeSelect::CSdeSelect(vector<STR_SDEINFO> vecAll, CWnd* pParent /*=NULL*/)
	: CDialog(CSdeSelect::IDD, pParent)
{
	m_vecSelectItem.clear();
	m_vecAll = vecAll;
}

CSdeSelect::~CSdeSelect()
{
}

void CSdeSelect::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SHOW, m_ListShow);
}

BEGIN_MESSAGE_MAP(CSdeSelect, CDialog)
	ON_BN_CLICKED(IDOK, &CSdeSelect::OnBnClickedOk)
END_MESSAGE_MAP()

// CSdeSelect 消息处理程序
BOOL CSdeSelect::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ListShow.SetExtendedStyle(m_ListShow.GetExtendedStyle() | LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ListShow.InsertColumn(0, _T("数据名称"), LVCFMT_CENTER, 150);
	m_ListShow.InsertColumn(1, _T("数据类型"), LVCFMT_CENTER, 100);

	InitShowData();

	UpdateData(TRUE);

	return TRUE;
}

void CSdeSelect::OnBnClickedOk()
{
	UpdateData();

	STR_SDEINFO				sdeInfo;
	for (int i = 0; i < m_ListShow.GetItemCount(); i++)
	{
		if (m_ListShow.GetCheck(i))
		{
			sdeInfo.strName = m_ListShow.GetItemText(i, 0);
			sdeInfo.Type = (enumDTType)m_ListShow.GetItemData(i);
			m_vecSelectItem.push_back(sdeInfo);
		}
	}

	OnOK();
}

vector<STR_SDEINFO> CSdeSelect::GetSelectItem() const
{
	return m_vecSelectItem;
}

void CSdeSelect::InitShowData()
{
	UpdateData(FALSE);

	STR_SDEINFO				sdeInfo;
	int						i = m_ListShow.GetItemCount();

	for (vector<STR_SDEINFO>::const_iterator itor =  m_vecAll.begin(); itor != m_vecAll.end(); itor++)
	{
		sdeInfo = *itor;
		m_ListShow.InsertItem(i, sdeInfo.strName.c_str());
		
		switch (sdeInfo.Type)
		{
		case deuRasterBand:
			m_ListShow.SetItemText(i, 1, "RasterBand");
			m_ListShow.SetItemData(i, (DWORD)sdeInfo.Type);
			break;

		case deuRasterDataset:
			m_ListShow.SetItemText(i, 1, "RasterDataset");
			m_ListShow.SetItemData(i, (DWORD)sdeInfo.Type);
			break;

		case deuRasterCatalog:
			m_ListShow.SetItemText(i, 1, "RasterCatalog");
			m_ListShow.SetItemData(i, (DWORD)sdeInfo.Type);
			break;

		case deuFeatureClass:
			m_ListShow.SetItemText(i, 1, "FeatureClass");
			m_ListShow.SetItemData(i, (DWORD)sdeInfo.Type);
			break;

		case deuFeatureDataset:
			m_ListShow.SetItemText(i, 1, "FeatureDataset");
			m_ListShow.SetItemData(i, (DWORD)sdeInfo.Type);
			break;

		default:
			m_ListShow.SetItemText(i, 1, "UnknownType");
			m_ListShow.SetItemData(i, (DWORD)0x0000);
			break;
		}
		i++;	
	}

	UpdateData(FALSE);
}
