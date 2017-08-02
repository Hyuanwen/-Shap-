// RasterSetting.cpp : 实现文件
//

#include "stdafx.h"
#include "RasterSetting.h"
#include "DeuFunction.h"
#include "DeuGlobalParam.h"

// CRasterSetting 对话框

IMPLEMENT_DYNAMIC(CRasterSetting, CDialog)

//各个比例尺下的经度差和纬度差
const double dbdetalXY[8][2] = {
							{6,4},
							{3,2},
							{1.5,1},
							{1.0/2.0,1.0/3.0},
							{1.0/4.0,1.0/6.0},
							{1.0/8.0,1.0/12.0},
							{1.0/16.0,1.0/24.0},
							{1.0/32.0,1.0/48.0},
						};

CRasterSetting::CRasterSetting(CWnd* pParent /*=NULL*/)
	: CDialog(CRasterSetting::IDD, pParent)
	, m_SizeX(0)
	, m_SizeY(0)
	, m_PixX(0)
	, m_PixY(0)
	, m_bSpecialFrame(FALSE)
	, m_dbLeft(0)
	, m_dbTop(0)
	, m_bStandardFrame(false)
	, m_bNonStandardFrame(false)
	, m_strFrameNo(_T(""))
	, m_dbBottom(0)
	, m_dbRight(0)
{
}

CRasterSetting::~CRasterSetting()
{
}

BOOL CRasterSetting::OnInitDialog()
{
	CDialog::OnInitDialog();

	((CButton*)GetDlgItem(IDC_RADIOSTD))->SetCheck(TRUE);
	OnBnClickedRadio2();
	
	m_cbUnit.InsertString( 0 , sz_Unit[0] );
	m_cbUnit.InsertString( 1 , sz_Unit[1] );
	m_cbUnit.SetCurSel( 0 );
	m_cbUnit.EnableWindow(TRUE);

	m_dbBottom = m_dbTop - m_PixY * m_SizeY ;
	m_dbRight  = m_dbLeft + m_PixX * m_SizeX ;

	UpdateData(FALSE);

	return TRUE;
}

void CRasterSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT6, m_PixX);
	DDX_Text(pDX, IDC_EDIT7, m_PixY);
	DDX_Text(pDX, IDC_EDIT2, m_dbLeft);
	DDX_Text(pDX, IDC_EDIT5, m_dbTop);
	DDX_Text(pDX, IDC_EDIT16, m_strFrameNo);
	DDX_Control(pDX, IDC_COMBO1, m_cbUnit);
	DDX_Text(pDX, IDC_EDIT15, m_dbBottom);
	DDX_Text(pDX, IDC_EDIT14, m_dbRight);
}

BEGIN_MESSAGE_MAP(CRasterSetting, CDialog)
	ON_BN_CLICKED(IDOK, &CRasterSetting::OnBnClickedOk)
	ON_BN_CLICKED(IDC_RADIOSTD, &CRasterSetting::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIONONSTD, &CRasterSetting::OnBnClickedRadio1)
	ON_EN_CHANGE(IDC_EDIT16, &CRasterSetting::OnEnChangeEdit16)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CRasterSetting::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()

// CRasterSetting 消息处理程序
void CRasterSetting::OnBnClickedOk()
{
	UpdateData();

	int ichkSTD , ichkNONSTD ;
	ichkSTD = ((CButton*)GetDlgItem(IDC_RADIOSTD))->GetCheck() ;
	ichkNONSTD = ((CButton*)GetDlgItem(IDC_RADIONONSTD))->GetCheck() ;
	double dbDetalX(0) , dbDetalY(0) ;

	if( ichkSTD == 1 )
	{
		//如果是标准分幅，则有图幅号计算出，左上角点，及长，宽。
		//void CalculateWS(const char * tf, double & w ,double & s);
		double w(0) , s(0) ;
		CalculateWS( m_strFrameNo , w , s );

		dbDetalX = dbdetalXY[3][0] ;
		dbDetalY = dbdetalXY[3][1] ;

		m_dbLeft = w ;
		m_dbTop = s + dbDetalY ;
		m_SizeX = dbDetalX / m_PixX ;
		m_SizeY = dbDetalY / m_PixY ;
	}
	else if( ichkNONSTD == 1 )
	{
		dbDetalX = m_dbRight - m_dbLeft ;
		dbDetalY = m_dbTop - m_dbBottom ;
		m_SizeX = dbDetalX / m_PixX ;
		m_SizeY = dbDetalY / m_PixY ;
	}

	OnOK();
}

void CRasterSetting::OnBnClickedRadio2()
{
	//标准分幅
	BOOL bEnableStandard = TRUE;
	BOOL bEnableNonStandard = FALSE;

	((CEdit*)GetDlgItem(IDC_EDIT16))->EnableWindow(bEnableStandard);
	((CEdit*)GetDlgItem(IDC_EDIT2))->EnableWindow(bEnableNonStandard);
	((CEdit*)GetDlgItem(IDC_EDIT5))->EnableWindow(bEnableNonStandard);
	//((CEdit*)GetDlgItem(IDC_EDIT6))->EnableWindow(bEnableNonStandard);
	//((CEdit*)GetDlgItem(IDC_EDIT7))->EnableWindow(bEnableNonStandard);
	((CEdit*)GetDlgItem(IDC_EDIT14))->EnableWindow(bEnableNonStandard);
	((CEdit*)GetDlgItem(IDC_EDIT15))->EnableWindow(bEnableNonStandard);
}

void CRasterSetting::OnBnClickedRadio1()
{
	//非标准分幅
	BOOL bEnableStandard = FALSE;
	BOOL bEnableNonStandard = TRUE;

	((CEdit*)GetDlgItem(IDC_EDIT16))->EnableWindow(bEnableStandard);
	((CEdit*)GetDlgItem(IDC_EDIT2))->EnableWindow(bEnableNonStandard);
	((CEdit*)GetDlgItem(IDC_EDIT5))->EnableWindow(bEnableNonStandard);
	//((CEdit*)GetDlgItem(IDC_EDIT6))->EnableWindow(bEnableNonStandard);
	//((CEdit*)GetDlgItem(IDC_EDIT7))->EnableWindow(bEnableNonStandard);
	((CEdit*)GetDlgItem(IDC_EDIT14))->EnableWindow(bEnableNonStandard);
	((CEdit*)GetDlgItem(IDC_EDIT15))->EnableWindow(bEnableNonStandard);
}

void CRasterSetting::OnEnChangeEdit16()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
}

void CRasterSetting::OnCbnSelchangeCombo1()
{
}
