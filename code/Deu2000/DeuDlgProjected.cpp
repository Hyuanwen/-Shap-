// DeuDlgPtojected.cpp : 实现文件

#include "stdafx.h"
#include "DeuDlgProjected.h"
#include "DeuGlobal.h"

// CDeuDlgProjected 对话框
IMPLEMENT_DYNAMIC(CDeuDlgProjected, CDialog)
CDeuDlgProjected::CDeuDlgProjected(BOOL _IsModify,  CWnd* pParent /*=NULL*/)
	: CDialog(CDeuDlgProjected::IDD, pParent)
{
	IsModify = _IsModify;
}

CDeuDlgProjected::~CDeuDlgProjected()
{
}

void CDeuDlgProjected::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_NAME, m_Edit_Name);
	DDX_Control(pDX, IDC_EDIT_ENVELOPE_NAME, m_Edit_ENVELOPE_NAME);
	DDX_Control(pDX, IDC_EDIT_ENVELOPE_MIN_LONG, m_Edit_ENVELOPE_MIN_LONG);
	DDX_Control(pDX, IDC_EDIT_ENVELOPE_MIN_FLAT, m_Edit_ENVELOPE_MIN_FLAT);
	DDX_Control(pDX, IDC_EDIT_ENVELOPE_MAX_LONG, m_Edit_ENVELOPE_MAX_LONG);
	DDX_Control(pDX, IDC_EDIT_ENVELOPE_MAX_FLAT, m_Edit_ENVELOPE_MAX_FLAT);
	DDX_Control(pDX, IDC_EDIT_CM, m_Edit_CM);
	DDX_Control(pDX, IDC_EDIT_FE, m_Edit_FE);
	DDX_Control(pDX, IDC_COMBO_GP, m_combox);
}

BEGIN_MESSAGE_MAP(CDeuDlgProjected, CDialog)
	ON_BN_CLICKED(IDC_BTN_OK, &CDeuDlgProjected::OnBnClickedBtnOk)
	ON_BN_CLICKED(IDC_BTN_CANCEL, &CDeuDlgProjected::OnBnClickedBtnCancel)
END_MESSAGE_MAP()

// CDeuDlgProjected 消息处理程序
void CDeuDlgProjected::OnBnClickedBtnOk()
{
	m_Edit_Name.GetWindowText(m_strName);
	m_Edit_ENVELOPE_NAME.GetWindowText(m_strEnvelopeName);
	m_Edit_ENVELOPE_MIN_LONG.GetWindowText(m_strEnvelopeMinLong);
	m_Edit_ENVELOPE_MIN_FLAT.GetWindowText(m_strEnvelopeMinFlat);
	m_Edit_ENVELOPE_MAX_LONG.GetWindowText(m_strEnvelopeMaxLong);
	m_Edit_ENVELOPE_MAX_FLAT.GetWindowText(m_strEnvelopeMaxFlat);

	m_Edit_CM.GetWindowText(m_CM);
	m_Edit_FE.GetWindowText(m_FE);
	m_combox.GetWindowText(m_GeoDetic);

	for(int k=0; k<GeoDataMapping.ProjectedNode.pProjectedSeries.GetCount(); k++)
	{
		if(m_strName == GeoDataMapping.ProjectedNode.pProjectedSeries.GetAt(k)._name.text)
		{
			AfxMessageBox("已有此名称投影坐标系存在");
			return;
		}
	}

	if(IsModify)
	{
		for(int n=0; n<CustDataMapping.ProjectedNode.pProjectedSeries.GetCount(); n++)
		{
			if(m_strCoordName == CustDataMapping.ProjectedNode.pProjectedSeries.GetAt(n)._name.text)
			{
				CustDataMapping.ProjectedNode.pProjectedSeries.GetAt(n).name = m_strName;	
				CustDataMapping.ProjectedNode.pProjectedSeries.GetAt(n).type = "projected";
				CustDataMapping.ProjectedNode.pProjectedSeries.GetAt(n)._name.text = m_strName;	 //添加前缀

				CustDataMapping.ProjectedNode.pProjectedSeries.GetAt(n)._envelope._name.text = m_strEnvelopeName;
				CustDataMapping.ProjectedNode.pProjectedSeries.GetAt(n)._envelope._minpoint._long.text = m_strEnvelopeMinLong;
				CustDataMapping.ProjectedNode.pProjectedSeries.GetAt(n)._envelope._minpoint._lat.text  = m_strEnvelopeMinFlat;
				CustDataMapping.ProjectedNode.pProjectedSeries.GetAt(n)._envelope._maxpoint._long.text = m_strEnvelopeMaxLong;
				CustDataMapping.ProjectedNode.pProjectedSeries.GetAt(n)._envelope._maxpoint._lat.text  = m_strEnvelopeMaxFlat;

				CustDataMapping.ProjectedNode.pProjectedSeries.GetAt(n)._geodeticPointor.text = m_GeoDetic;
				CustDataMapping.ProjectedNode.pProjectedSeries.GetAt(n)._falseEasting._value.text = m_FE;
				CustDataMapping.ProjectedNode.pProjectedSeries.GetAt(n)._centralMeridian._value.text = m_CM;
			}
		}
	}
	else
	{
		_ProjectedSeries m_ProjectedSeries;
		Init_Projected(&m_ProjectedSeries); //初始必要数据

		m_ProjectedSeries.name = m_strName;	
		m_ProjectedSeries.type = "projected";
		m_ProjectedSeries._name.text = m_strName;	 //添加前缀

		m_ProjectedSeries._envelope.name = "Envelope";
		m_ProjectedSeries._envelope.type = "Envelope";		
		m_ProjectedSeries._envelope._name.text = m_strEnvelopeName;
		m_ProjectedSeries._envelope._minpoint._long.text = m_strEnvelopeMinLong;
		m_ProjectedSeries._envelope._minpoint._lat.text  = m_strEnvelopeMinFlat;
		m_ProjectedSeries._envelope._maxpoint._long.text = m_strEnvelopeMaxLong;
		m_ProjectedSeries._envelope._maxpoint._lat.text  = m_strEnvelopeMaxFlat;

		m_ProjectedSeries._geodeticPointor.text = m_GeoDetic;
		m_ProjectedSeries._falseEasting._value.text = m_FE;
		m_ProjectedSeries._centralMeridian._value.text = m_CM;

		CustDataMapping.ProjectedNode.pProjectedSeries.Add(m_ProjectedSeries);
	}
	
	CDeuXmlWriter m_writer;
	m_writer.BuildCustomDataXml(GetStylesPath()+"\\CustomData.xml", &CustDataMapping);

	this->OnOK();
}

void CDeuDlgProjected::OnBnClickedBtnCancel()
{
	this->OnCancel();
}

BOOL CDeuDlgProjected::OnInitDialog()
{
	CDialog::OnInitDialog();

	for(int n=0; n<CustDataMapping.GeodeticNode.pGeodeticSeries.GetCount(); n++)
	{
		m_combox.InsertString(n, CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._name.text);
	}
	
	if(IsModify)
	{
		this->SetWindowText("修改投影坐标");
		
		for(int n=0; n<CustDataMapping.ProjectedNode.pProjectedSeries.GetCount(); n++)
		{
			if(m_strCoordName == CustDataMapping.ProjectedNode.pProjectedSeries.GetAt(n)._name.text)
			{
				m_Edit_Name.SetWindowText(CustDataMapping.ProjectedNode.pProjectedSeries.GetAt(n)._name.text);
				m_Edit_ENVELOPE_NAME.SetWindowText(CustDataMapping.ProjectedNode.pProjectedSeries.GetAt(n)._envelope._name.text);
				m_Edit_ENVELOPE_MIN_LONG.SetWindowText(CustDataMapping.ProjectedNode.pProjectedSeries.GetAt(n)._envelope._minpoint._long.text);
				m_Edit_ENVELOPE_MIN_FLAT.SetWindowText(CustDataMapping.ProjectedNode.pProjectedSeries.GetAt(n)._envelope._minpoint._lat.text);
				m_Edit_ENVELOPE_MAX_LONG.SetWindowText(CustDataMapping.ProjectedNode.pProjectedSeries.GetAt(n)._envelope._maxpoint._long.text);
				m_Edit_ENVELOPE_MAX_FLAT.SetWindowText(CustDataMapping.ProjectedNode.pProjectedSeries.GetAt(n)._envelope._maxpoint._lat.text);

				m_Edit_CM.SetWindowText(CustDataMapping.ProjectedNode.pProjectedSeries.GetAt(n)._centralMeridian._value.text);
				m_Edit_FE.SetWindowText(CustDataMapping.ProjectedNode.pProjectedSeries.GetAt(n)._falseEasting._value.text);


				for(int m=0; m<m_combox.GetCount(); m++)
				{
					if(m_combox.FindString(m, CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._name.text) != -1)
					{
						m_combox.SetCurSel(m);
					}
				}
			}
		}
	}
	else
	{
		m_combox.SetCurSel(0);
	}

	return TRUE;
}
