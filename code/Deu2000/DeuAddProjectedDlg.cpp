// DeuAddProjectedDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DeuAddProjectedDlg.h"


// CDeuAddProjectedDlg 对话框

IMPLEMENT_DYNAMIC(CDeuAddProjectedDlg, CDialog)

CDeuAddProjectedDlg::CDeuAddProjectedDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDeuAddProjectedDlg::IDD, pParent)
	, m_szName(_T(""))
	, m_dFalseEasting(0)
	, m_dFalseNorthing(0)
	, m_dCentralMeridia(0)
	, m_dA(0)
	, m_dB(0)
	, m_dK(0)
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

CDeuAddProjectedDlg::~CDeuAddProjectedDlg()
{
}

void CDeuAddProjectedDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_Project_Type, m_ctlProjectType);
	DDX_Text(pDX, IDC_EDIT_NAME, m_szName);
	DDX_Text(pDX, IDC_EDIT_False_Easting, m_dFalseEasting);
	DDX_Text(pDX, IDC_EDIT_False_Northing, m_dFalseNorthing);
	DDX_Text(pDX, IDC_EDIT_Central_Meridian, m_dCentralMeridia);
	DDX_Control(pDX, IDC_COMBO_Coordinate_Name, m_ctlCoordinateName);
	DDX_Text(pDX, IDC_EDIT_ELLIPSOID_a, m_dA);
	DDX_Text(pDX, IDC_EDIT_ELLIPSOID_b, m_dB);
	DDX_Text(pDX, IDC_EDIT_ELLIPSOID_k, m_dK);
	DDX_Control(pDX, IDC_EDIT_ELLIPSOID_a, m_ctlA);
	DDX_Control(pDX, IDC_EDIT_ELLIPSOID_b, m_ctlB);
	DDX_Control(pDX, IDC_EDIT_ELLIPSOID_k, m_ctlK);
}


BEGIN_MESSAGE_MAP(CDeuAddProjectedDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CDeuAddProjectedDlg::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBO_Coordinate_Name, &CDeuAddProjectedDlg::OnCbnSelchangeComboCoordinateName)
END_MESSAGE_MAP()


// CDeuAddProjectedDlg 消息处理程序

BOOL CDeuAddProjectedDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	UpdateData(FALSE);
	m_ctlProjectType.AddString(_T("高斯投影"));
	m_ctlProjectType.AddString(_T("横轴墨卡托投影"));
	m_ctlProjectType.AddString(_T("通用横轴墨卡托投影"));

	m_ctlCoordinateName.AddString(_T("GCS_Beijing_1954"));
	m_ctlCoordinateName.AddString(_T("GCS_Xian_1980"));
	m_ctlCoordinateName.AddString(_T("GCS_CGCS_2000"));
	m_ctlCoordinateName.AddString(_T("GCS_WGS_1984"));

	m_ctlCoordinateName.SetCurSel(0);
	m_ctlProjectType.SetCurSel(0);
	OnCbnSelchangeComboCoordinateName();

	m_ctlA.EnableWindow(FALSE);
	m_ctlB.EnableWindow(FALSE);
	m_ctlK.EnableWindow(FALSE);


	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDeuAddProjectedDlg::OnBnClickedOk()
{
	UpdateData(TRUE);
	std::string      strPathName;
	std::string       szsysPath;
	char         szFilePath[MAX_PATH+1] = {0};
	BOOL         bExit;
	std::string  szDatum[3] = {"Beijing 1954", "Xian 1980", "CGCS2000"};
	::GetModuleFileName(NULL, szFilePath, MAX_PATH);\

		szsysPath = szFilePath;
	int ipos = szsysPath.rfind(_T("\\"), szsysPath.length()-1);
	szsysPath = szsysPath.substr(0, ipos);

	int iCursel = m_ctlCoordinateName.GetCurSel();

	if(iCursel == 3)
		strPathName = szsysPath+_T("\\CoordinateSystems\\Projected Coordinate Systems\\UTM\\WGS 1984\\");
	else
	{
		strPathName = szsysPath + _T("\\CoordinateSystems\\Projected Coordinate Systems\\Gauss Kruger\\") + 
			          szDatum[iCursel] + _T("\\");
	}

	strPathName = strPathName + m_szName.GetBuffer(0) + _T(".") + _T("prj");


	bExit = PathFileExists(strPathName.c_str());
	if(bExit == TRUE)
	{
		AfxMessageBox("此坐标系已经存在，请重新命名！");
		return;
	}

	SetSRS2(strPathName.c_str());

	OnOK();
}

void  CDeuAddProjectedDlg::SetSRS2(CString szFilePath)
{		
	OGRSpatialReference* poRSR= new OGRSpatialReference();

	double dA[4] = {6378245, 6378140, 6378137, 6378137};
	double dB[4] = {6356863.01877305, 6356755.28815753, 6356752.31414036, 6356752.31424518};
	double dK[4] = {0.0033523298692587, 0.00335281317789667, 0.00335281068118169, 0.00335281066474737};
	double dvK[4] = {298.3, 298.257, 298.2572220960422, 298.257223563};

	CString  szUint[4] = {"Radian", "Degree", "Minute", "Second"};
	CString  szDatum[4] = {"D_Beijing_1954", "D_Xian_1980", "D_China_2000", "D_WGS_1984"};
	CString  szEllipName[4] = {"Krasovsky_1980", "Xian_1980", "CGCS2000", "WGS_1984"};
	CString  szPrjType[3] = {"Gauss_Kruger", "Transverse_Mercator", "Mercator"};

	if(poRSR)
	{
		//设置投影坐标系
		BOOL    vb_IsProj =TRUE  ;
		CString ProjName ; 
		CString Proj ;

		//设置大地坐标系
		CString dfGeogName;
		CString dfDatum = _T("DATUM");
		CString dfEllipName = "";
		double dfSemiMajor;
		double dfInvFlattening;

		//if( ProjName )
		poRSR->SetProjCS((LPCSTR)_bstr_t(m_szName));

		int iCursel = m_ctlProjectType.GetCurSel();
		if(iCursel>-1 && iCursel < 3)
			poRSR->SetProjection(szPrjType[iCursel]);

		//设置参数：	PARAMETER["False_Easting",500000.0],
		poRSR->SetProjParm("False_Easting",m_dFalseEasting);

		//设置参数：	PARAMETER["False_Northing",0.0],
		poRSR->SetProjParm("False_Northing",m_dFalseNorthing);

		//设置参数：	PARAMETER["Central_Meridian",118.5],
		poRSR->SetProjParm("Central_Meridian",m_dCentralMeridia);

		//设置参数：	PARAMETER["Scale_Factor",1.0],
		double dScaleFactor = 1.0;
		poRSR->SetProjParm("Scale_Factor",dScaleFactor);

		//设置参数：	PARAMETER["Latitude_Of_Origin",0.0],
		double m_dLatitudeOfOrigin = 0.0;
		poRSR->SetProjParm("Latitude_Of_Origin", m_dLatitudeOfOrigin);

		iCursel = -1;
		iCursel = m_ctlCoordinateName.GetCurSel();
		if(iCursel > -1 && iCursel < 4)
		{
			dfEllipName = szEllipName[iCursel];
			dfDatum     = szDatum[iCursel]; 
			dfSemiMajor = dA[iCursel];
			dfInvFlattening = dvK[iCursel]; 
			m_ctlCoordinateName.GetLBText(iCursel, dfGeogName);
		}

		poRSR->SetGeogCS((LPCSTR)_bstr_t(dfGeogName),(LPCSTR)_bstr_t(dfDatum),(LPCSTR)_bstr_t(dfEllipName),dfSemiMajor,dfInvFlattening);

		CString dfLinearUnits = "Meter";
		double fLinearUnits = 1.0;


		poRSR->SetLinearUnits(dfLinearUnits.GetBuffer(),fLinearUnits);

		CString dfAngularUnits = "Degree";
		double fAngularUnit = 0.0174532925199433;

		poRSR->SetAngularUnits(dfAngularUnits.GetBuffer(),fAngularUnit);
	}

	CFile                                File;
	char *                               chWkt;
	const char *                         pDatum = NULL;

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

	return;
}



void CDeuAddProjectedDlg::OnCbnSelchangeComboCoordinateName()
{
	UpdateData(TRUE);
	int iCursel = -1;
	iCursel = m_ctlCoordinateName.GetCurSel();
	if(iCursel > -1 && iCursel < 4)
	{
		m_dA = m_pdA[iCursel];
		m_dB = m_pdB[iCursel];
		m_dK = m_pdK[iCursel];
		UpdateData(FALSE);
	}
}
