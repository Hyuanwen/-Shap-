// DeuDlgGeoDetic.cpp : 实现文件

#include "stdafx.h"
#include "DeuDlgGeoDetic.h"
#include "DeuGlobal.h"

// CDeuDlgGeoDetic 对话框
IMPLEMENT_DYNAMIC(CDeuDlgGeoDetic, CDialog)
CDeuDlgGeoDetic::CDeuDlgGeoDetic(BOOL _IsModify, CWnd* pParent /*=NULL*/)
	: CDialog(CDeuDlgGeoDetic::IDD, pParent)
{
	IsModify = _IsModify;
}

CDeuDlgGeoDetic::~CDeuDlgGeoDetic()
{
}

void CDeuDlgGeoDetic::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_NAME, m_Edit_Name);
	DDX_Control(pDX, IDC_EDIT_ENVELOPE_NAME, m_Edit_EnvelopeName);
	DDX_Control(pDX, IDC_EDIT_ENVELOPE_MIN_LONG, m_Edit_EnvelopeMinLong);
	DDX_Control(pDX, IDC_EDIT_ENVELOPE_MIN_FLAT, m_Edit_EnvelopeMinFlat);
	DDX_Control(pDX, IDC_EDIT_ENVELOPE_MAX_LONG, m_Edit_EnvelopeMaxLong);
	DDX_Control(pDX, IDC_EDIT_ENVELOPE_MAX_FLAT, m_Edit_EnvelopeMaxFlat);
	DDX_Control(pDX, IDC_EDIT_ELLIPSOID_NAME, m_Edit_EllipsoidName);
	DDX_Control(pDX, IDC_EDIT_ELLIPSOID_LONG, m_Edit_EllipsoidLong);
	DDX_Control(pDX, IDC_EDIT_ELLIPSOID_SHORT, m_Edit_EllipsoidFlat);
	DDX_Control(pDX, IIDC_EDIT_ELLIPSOID_PIANXIN, m_Edit_EllipsoidPianXin);
}

BEGIN_MESSAGE_MAP(CDeuDlgGeoDetic, CDialog)
	ON_BN_CLICKED(IDC_BTN_OK, &CDeuDlgGeoDetic::OnBnClickedBtnOk)
	ON_BN_CLICKED(IDC_BTN_CANCEL, &CDeuDlgGeoDetic::OnBnClickedBtnCancel)
END_MESSAGE_MAP()

// CDeuDlgGeoDetic 消息处理程序
void CDeuDlgGeoDetic::OnBnClickedBtnOk()
{	
	m_Edit_Name.GetWindowText(m_strName);
	m_Edit_EnvelopeName.GetWindowText(m_strEnvelopeName);
	m_Edit_EnvelopeMinLong.GetWindowText(m_strEnvelopeMinLong);
	m_Edit_EnvelopeMinFlat.GetWindowText(m_strEnvelopeMinFlat);
	m_Edit_EnvelopeMaxLong.GetWindowText(m_strEnvelopeMaxLong);
	m_Edit_EnvelopeMaxFlat.GetWindowText(m_strEnvelopeMaxFlat);

	m_Edit_EllipsoidName.GetWindowText(m_strEllipsoidName);
	m_Edit_EllipsoidLong.GetWindowText(m_strEllipsoidLong);
	m_Edit_EllipsoidFlat.GetWindowText(m_strEllipsoidFlat);
	m_Edit_EllipsoidPianXin.GetWindowText(m_strEllipsoidPianXin);

	for(int k=0; k<GeoDataMapping.GeodeticNode.pGeodeticSeries.GetCount(); k++)
	{
		if(m_strName == GeoDataMapping.GeodeticNode.pGeodeticSeries.GetAt(k)._name.text)
		{
			AfxMessageBox("已有此名称大地坐标系存在");
			return;
		}
	}

	//修改
	if(IsModify)
	{
		for(int n=0; n<CustDataMapping.GeodeticNode.pGeodeticSeries.GetCount(); n++)
		{
			if(m_strCoordName == CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._name.text)
			{
				CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n).name = m_strName;	
				CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n).type = "geodetic";
				CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._name.text = "geodetic"+m_strName;	 //添加前缀

				CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._envelope.name = "Envelope";
				CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._envelope.type = "Envelope";		
				CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._envelope._name.text = m_strEnvelopeName;
				CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._envelope._minpoint._long.text = m_strEnvelopeMinLong;
				CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._envelope._minpoint._lat.text  = m_strEnvelopeMinFlat;
				CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._envelope._maxpoint._long.text = m_strEnvelopeMaxLong;
				CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._envelope._maxpoint._lat.text  = m_strEnvelopeMaxFlat;

				CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._datum._name.text = m_strName;
				CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._datum._ellipsoid.name = "Ellipsoid";
				CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._datum._ellipsoid.type = "Ellipsoid";
				CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._datum._ellipsoid._name.text = m_strEllipsoidName;
				CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._datum._ellipsoid._name.name = "Ellipsoid";
				CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._datum._ellipsoid._name.type = "Ellipsoid";

				CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._datum._ellipsoid._semi_Major_Axis._value.text = m_strEllipsoidLong;
				CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._datum._ellipsoid._semi_Minor_Axis._value.text = m_strEllipsoidFlat;

				CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._datum._ellipsoid._inverseFlattening.text = m_strEllipsoidPianXin;
			}
		}
	}
	//增加
	else
	{
		_GeodeticSeries mGeodeticSeries;
		Init_Geodetic(&mGeodeticSeries); //初始必要数据

		mGeodeticSeries.name = m_strName;	
		mGeodeticSeries.type = "geodetic";
		mGeodeticSeries._name.text = "geodetic"+m_strName;	 //添加前缀

		mGeodeticSeries._envelope.name = "Envelope";
		mGeodeticSeries._envelope.type = "Envelope";		
		mGeodeticSeries._envelope._name.text = m_strEnvelopeName;
		mGeodeticSeries._envelope._minpoint._long.text = m_strEnvelopeMinLong;
		mGeodeticSeries._envelope._minpoint._lat.text  = m_strEnvelopeMinFlat;
		mGeodeticSeries._envelope._maxpoint._long.text = m_strEnvelopeMaxLong;
		mGeodeticSeries._envelope._maxpoint._lat.text  = m_strEnvelopeMaxFlat;

		mGeodeticSeries._datum._name.text = m_strName;
		mGeodeticSeries._datum._ellipsoid.name = "Ellipsoid";
		mGeodeticSeries._datum._ellipsoid.type = "Ellipsoid";
		mGeodeticSeries._datum._ellipsoid._name.text = m_strEllipsoidName;
		mGeodeticSeries._datum._ellipsoid._name.name = "Ellipsoid";
		mGeodeticSeries._datum._ellipsoid._name.type = "Ellipsoid";

		mGeodeticSeries._datum._ellipsoid._semi_Major_Axis._value.text = m_strEllipsoidLong;
		mGeodeticSeries._datum._ellipsoid._semi_Minor_Axis._value.text = m_strEllipsoidFlat;

		mGeodeticSeries._datum._ellipsoid._inverseFlattening.text = m_strEllipsoidPianXin;

		CustDataMapping.GeodeticNode.pGeodeticSeries.Add(mGeodeticSeries);
	}

	CDeuXmlWriter m_writer;
	m_writer.BuildCustomDataXml(GetStylesPath()+"\\CustomData.xml", &CustDataMapping);

	this->OnOK();
}

void CDeuDlgGeoDetic::OnBnClickedBtnCancel()
{
	this->OnCancel();
}

BOOL CDeuDlgGeoDetic::OnInitDialog()
{
	CDialog::OnInitDialog();

	if(IsModify)
	{
		this->SetWindowText("修改大地坐标");

		for(int n=0; n<CustDataMapping.GeodeticNode.pGeodeticSeries.GetCount(); n++)
		{
			if(m_strCoordName == CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._name.text)
			{
				m_Edit_Name.SetWindowText(CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._name.text);
				m_Edit_EnvelopeName.SetWindowText(CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._envelope._name.text);
				m_Edit_EnvelopeMinLong.SetWindowText(CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._envelope._minpoint._long.text);
				m_Edit_EnvelopeMinFlat.SetWindowText(CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._envelope._minpoint._lat.text);
				m_Edit_EnvelopeMaxLong.SetWindowText(CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._envelope._maxpoint._long.text);
				m_Edit_EnvelopeMaxFlat.SetWindowText(CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._envelope._maxpoint._lat.text);

				m_Edit_EllipsoidName.SetWindowText(CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._datum._ellipsoid._name.text);
				m_Edit_EllipsoidLong.SetWindowText(CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._datum._ellipsoid._semi_Major_Axis._value.text);
				m_Edit_EllipsoidFlat.SetWindowText(CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._datum._ellipsoid._semi_Minor_Axis._value.text);
				m_Edit_EllipsoidPianXin.SetWindowText(CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._datum._primeMeridian._geoDeticLong._value.text);

			}
		}
	}

	return TRUE;  // return TRUE unless you set the focus to a control。异常: OCX 属性页应返回 FALSE
}

