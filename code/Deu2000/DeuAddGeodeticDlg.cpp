// DeuAddGeodeticDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DeuAddGeodeticDlg.h"


// CDeuAddGeodeticDlg 对话框

IMPLEMENT_DYNAMIC(CDeuAddGeodeticDlg, CDialog)

CDeuAddGeodeticDlg::CDeuAddGeodeticDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDeuAddGeodeticDlg::IDD, pParent)
	, m_dA(0)
	, m_dB(0)
	, m_dK(0)
	, m_dUnitData(0)
	, m_szName(_T(""))
{
	m_pdA[0] = 6378245;
	m_pdA[1] = 6378140;
	m_pdA[2] = 6378137;
	m_pdA[3] = 6378137;
	m_pdB[0] = 6356863.01877305;
	m_pdB[1] = 6356755.28815753;
	m_pdB[2] = 6356752.31414036;
	m_pdB[3] = 6356752.31424518;
	m_pdK[0] = 0.0033523298692587;
	m_pdK[1] = 0.00335281317789667;
	m_pdK[2] = 0.00335281068118169;
	m_pdK[3] = 0.00335281066474737;
}

CDeuAddGeodeticDlg::~CDeuAddGeodeticDlg()
{
}

void CDeuAddGeodeticDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_ELLIPSOID_NAME, m_ctlComEllipsodi);
	DDX_Text(pDX, IDC_EDIT_ELLIPSOID_a, m_dA);
	DDX_Text(pDX, IDC_EDIT_ELLIPSOID_b, m_dB);
	DDX_Text(pDX, IDC_EDIT_ELLIPSOID_k, m_dK);
	DDX_Control(pDX, IDC_COMBO_unit, m_ctlComUnit);
	DDX_Text(pDX, IDC_EDIT_unit_data, m_dUnitData);
	DDX_Text(pDX, IDC_EDIT_NAME, m_szName);
	DDX_Control(pDX, IDC_EDIT_ELLIPSOID_a, m_ctlA);
	DDX_Control(pDX, IDC_EDIT_ELLIPSOID_b, m_ctlB);
	DDX_Control(pDX, IDC_EDIT_ELLIPSOID_k, m_ctlK);
	DDX_Control(pDX, IDC_EDIT_unit_data, m_ctlUnitData);
}


BEGIN_MESSAGE_MAP(CDeuAddGeodeticDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CDeuAddGeodeticDlg::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBO_ELLIPSOID_NAME, &CDeuAddGeodeticDlg::OnCbnSelchangeComboEllipsoidName)
	ON_CBN_SELCHANGE(IDC_COMBO_unit, &CDeuAddGeodeticDlg::OnCbnSelchangeCombounit)
//	ON_CBN_EDITCHANGE(IDC_COMBO_ELLIPSOID_NAME, &CDeuAddGeodeticDlg::OnCbnEditchangeComboEllipsoidName)
ON_CBN_EDITUPDATE(IDC_COMBO_ELLIPSOID_NAME, &CDeuAddGeodeticDlg::OnCbnEditupdateComboEllipsoidName)
ON_CBN_EDITCHANGE(IDC_COMBO_ELLIPSOID_NAME, &CDeuAddGeodeticDlg::OnCbnEditchangeComboEllipsoidName)
END_MESSAGE_MAP()


// CDeuAddGeodeticDlg 消息处理程序

BOOL CDeuAddGeodeticDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	UpdateData(FALSE);
	m_ctlComEllipsodi.AddString(_T("北京54/克拉索夫斯基(1940年)椭球"));
	m_ctlComEllipsodi.AddString(_T("西安80/1975年I.U.G.G推荐椭球"));
	m_ctlComEllipsodi.AddString(_T("中国2000国家大地坐标系"));
	m_ctlComEllipsodi.AddString(_T("WGS-84"));
	m_ctlComEllipsodi.AddString(_T("自定义"));


	m_ctlComUnit.AddString(_T("弧度"));
	m_ctlComUnit.AddString(_T("度"));
	m_ctlComUnit.AddString(_T("分"));
	m_ctlComUnit.AddString(_T("秒"));
	//m_ctlComUnit.AddString(_T("梯度"));

	m_ctlComEllipsodi.SetCurSel(0);
	m_ctlComUnit.SetCurSel(1);

	OnCbnSelchangeComboEllipsoidName();
	OnCbnSelchangeCombounit();

	m_ctlA.EnableWindow(FALSE);
	m_ctlB.EnableWindow(FALSE);
	m_ctlK.EnableWindow(FALSE);
	m_ctlUnitData.EnableWindow(FALSE);
	
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDeuAddGeodeticDlg::OnBnClickedOk()
{
	UpdateData(TRUE);

	std::string      strPathName;
	std::string       szsysPath;
	char         szFilePath[MAX_PATH+1] = {0};
	BOOL         bExit;
	::GetModuleFileName(NULL, szFilePath, MAX_PATH);\
	
	szsysPath = szFilePath;
	int ipos = szsysPath.rfind(_T("\\"), szsysPath.length()-1);
	szsysPath = szsysPath.substr(0, ipos);

	int iCursel = m_ctlComEllipsodi.GetCurSel();

	if(iCursel == 3)
		strPathName = szsysPath+_T("\\CoordinateSystems\\Geographic Coordinate Systems\\World\\");
	else
		strPathName = szsysPath+_T("\\CoordinateSystems\\Geographic Coordinate Systems\\Asia\\");

	strPathName = strPathName + m_szName.GetBuffer(0) + _T(".") + _T("prj");


	bExit = PathFileExists(strPathName.c_str());
	if(bExit == TRUE)
	{
		AfxMessageBox("此坐标系已经存在，请重新命名！");
		return;
	}

	SetRSR(strPathName.c_str());
	OnOK();
}

void CDeuAddGeodeticDlg::OnCbnSelchangeComboEllipsoidName()
{
	UpdateData(FALSE);
	int iCursel = -1;
	iCursel = m_ctlComEllipsodi.GetCurSel();
	if(iCursel > -1 && iCursel < 4)
	{
		m_dA = m_pdA[iCursel];
		m_dB = m_pdB[iCursel];
		m_dK = m_pdK[iCursel];
				
		m_ctlA.EnableWindow(FALSE);
		m_ctlB.EnableWindow(FALSE);
		m_ctlK.EnableWindow(FALSE);
		UpdateData(FALSE);
	}
	if(iCursel == 4)
	{
		m_ctlA.EnableWindow(TRUE);
		m_ctlB.EnableWindow(TRUE);
		m_ctlK.EnableWindow(TRUE);
	}
}

void CDeuAddGeodeticDlg::OnCbnSelchangeCombounit()
{
	double duintData[4] = {1,0.0174532925199433, 0.00029088820866572,0.000004848136811095/*,0.015707963267949*/};
	int iCursel = -1;

	iCursel = m_ctlComUnit.GetCurSel();
	if(iCursel > -1 && iCursel < 4)
		m_dUnitData = duintData[iCursel];
	UpdateData(FALSE);
}


void CDeuAddGeodeticDlg::SetRSR(CString szFilePath)
{		
	OGRSpatialReference* poRSR= new OGRSpatialReference();
	CString  szUint[4] = {"Radian", "Degree", "Minute", "Second"};
	CString  szDatum[4] = {"D_Beijing_1954", "D_Xian_1980", "D_China_2000", "D_WGS_1984"};
	CString  szEllipName[4] = {"Krasovsky_1940", "Xian_1980", "CGCS2000", "WGS_1984"};
	double dvK[4] = {298.3, 298.257, 298.2572220960422, 298.257223563};

	if(poRSR)
	{
		//设置大地坐标系
		CString dfGeogName = m_szName;
		CString dfDatum = _T("DATUM");
		CString dfEllipName = "";
		double dfSemiMajor;
		double dfInvFlattening;

		int iCursel = -1;
		iCursel = m_ctlComEllipsodi.GetCurSel();
		if(iCursel > -1 && iCursel < 4)
		{
			dfEllipName     = szEllipName[iCursel];
			dfDatum         = szDatum[iCursel]; 
			dfInvFlattening = dvK[iCursel];
		}
		else
		{
			CString  szElliName;			
			m_ctlComEllipsodi.GetWindowText(szElliName);
			
			dfEllipName     = szElliName;
			dfDatum         = szElliName; 
			dfInvFlattening = 1/m_dK;
		}
			 
		dfSemiMajor = m_dA;

		//地理坐标系、大地基准面、椭球名称、长轴、扁率倒数	
		poRSR->SetGeogCS(/*(LPCSTR)_bstr_t(*/dfGeogName/*)*/,(LPCSTR)_bstr_t(dfDatum),(LPCSTR)_bstr_t(dfEllipName),dfSemiMajor,dfInvFlattening);

		CString dfLinearUnits = "Greenwich";
		double fLinearUnits = 0.0;

		//dfLinearUnits = m_dK
		//投影坐标系单位、坐标系单位数值
		poRSR->SetLinearUnits(dfLinearUnits.GetBuffer(),fLinearUnits);


		CString dfAngularUnits = "";
		double fAngularUnit;

		iCursel = m_ctlComUnit.GetCurSel();
		if(iCursel > -1 && iCursel < 4)
			dfAngularUnits = szUint[iCursel];
		fAngularUnit = m_dUnitData;
		//地理坐标系单位、坐标系单位数值
		poRSR->SetAngularUnits(dfAngularUnits.GetBuffer(),fAngularUnit);
	}

	CFile                                File;
	char *                               chWkt;
	const char *                         pDatum = NULL;

	//CString  strPath;
	//strPath = m_szName + _T(".") + _T("prj");
	//FindFile(szsysPath, strPath, &StrResult);

	if (!File.Open(szFilePath, CFile::modeCreate|CFile::modeWrite))
	{
		return ;
	}

	
	chWkt = new char[1000];
	memset(chWkt, 0, sizeof(char)*1000);


	poRSR->exportToWkt(&chWkt);
	CString  szTring = chWkt;
	int      iLen;
	iLen = szTring.GetLength();
	File.Write(chWkt, iLen);
	File.Close();

	//delete poRSR;
	//delete [] chWkt;
}


//void CDeuAddGeodeticDlg::OnCbnEditchangeComboEllipsoidName()
//{	
//}

void CDeuAddGeodeticDlg::OnCbnEditupdateComboEllipsoidName()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CDeuAddGeodeticDlg::OnCbnEditchangeComboEllipsoidName()
{
	// TODO: 在此添加控件通知处理程序代码
}
