// DeuTmpDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DeuVectorProjectTranDlg.h"
#include "DeuDlgDataSrc.h"
#include "DeuDlgFiles.h"
#include "DeuDlgOraTables.h"
#include "DeuDlgOracle.h"
#include "DeuGlobalMainFrm.h"
#include "RasterSetting.h"

//add by chenyong 2013-11-25
//#include "DeuSDEConnectProperty.h"
//#include "ArcSDeVector.h"
//#include "SdeSelect.h"

IMPLEMENT_DYNCREATE(CDeuVectorProjectTranDlg, CDialog)
CDeuVectorProjectTranDlg::CDeuVectorProjectTranDlg()
: CDialog(CDeuVectorProjectTranDlg::IDD), m_Controlpoint_Dlg(VECTOR)
{
	//yzg  2012-9-3 开始的时候默认为高斯投影 而不是布尔莎  begin
	//iModel = MODEL_BURSA;
	iModel = MODEL_GAUSS;
	//yzg  2012-9-3 开始的时候默认为高斯投影 而不是布尔莎  end

	IsAdditional = FALSE;
}

CDeuVectorProjectTranDlg::~CDeuVectorProjectTranDlg()
{
}

void CDeuVectorProjectTranDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_INPUT, m_ComboInput);
	DDX_Control(pDX, IDC_COMBO_OUTPUT, m_ComboOutput);
	DDX_Control(pDX, IDC_COMBO_TRANMODEL, m_ComboTranModel);
	DDX_Control(pDX, IDC_EDIT_INPUT, m_edit_InputFile);
	DDX_Control(pDX, IDC_EDIT_OUTPUT, m_edit_OutputFile);
	DDX_Control(pDX, IDC_EDIT_COORINATE_INPUT, m_edit_InCoord);
	DDX_Control(pDX, IDC_EDIT_COORINATE_OUTPUT, m_edit_OutCoord);
	DDX_Control(pDX, IDC_PROGRESS1, m_Progress);
	DDX_Control(pDX, IDC_COMBO_RECOLLECT, m_ComboReCollect);
	DDX_Control(pDX, IDC_COMBO_TRANSFER, m_ComboTransfer);
}

BEGIN_MESSAGE_MAP(CDeuVectorProjectTranDlg, CDialog)
	ON_WM_SIZE()	
	ON_WM_CREATE()
	ON_EN_SETFOCUS(IDC_EDIT_COORINATE_INPUT, &CDeuVectorProjectTranDlg::OnCoordinateInput)
	ON_EN_SETFOCUS(IDC_EDIT_COORINATE_OUTPUT, &CDeuVectorProjectTranDlg::OnCoordinateOutput)
	ON_BN_CLICKED(IDC_BTN_INPUT, &CDeuVectorProjectTranDlg::OnBnClickedBtnInput)
	ON_BN_CLICKED(IDC_BTN_OUTPUT, &CDeuVectorProjectTranDlg::OnBnClickedBtnOutput)
	ON_CBN_SELCHANGE(IDC_COMBO_TRANMODEL, &CDeuVectorProjectTranDlg::OnCbnSelchangeComboTranmodel)
	ON_CBN_SELCHANGE(IDC_COMBO_INPUT, &CDeuVectorProjectTranDlg::OnCbnSelchangeComboInput)
	ON_CBN_SELCHANGE(IDC_COMBO_OUTPUT, &CDeuVectorProjectTranDlg::OnCbnSelchangeComboOutput)
	ON_MESSAGE(WM_PROGRESS, OnProgressStep)
	ON_WM_PAINT()	
	ON_BN_CLICKED(IDC_BUTTON1, &CDeuVectorProjectTranDlg::OnBnClickedButton1)
END_MESSAGE_MAP()

// CDeuVectorProjectTranDlg 诊断
//#ifdef _DEBUG
//void CDeuVectorProjectTranDlg::AssertValid() const
//{
//	CDialog::AssertValid();
//}
//
//#ifndef _WIN32_WCE
//void CDeuVectorProjectTranDlg::Dump(CDumpContext& dc) const
//{
//	CDialog::Dump(dc);
//}
//#endif
//#endif //_DEBUG

void CDeuVectorProjectTranDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	CRect rct,rctwnd, relRct;

	//控件自适应
	CStatic* p_static1		  = (CStatic*)GetDlgItem(IDC_STATIC_INPUTFIELD);
	CStatic* p_static2		  = (CStatic*)GetDlgItem(IDC_STATIC_OUTPUTFIELD);
	CStatic* p_static3		  = (CStatic*)GetDlgItem(IDC_STATIC_INPUT_TYPE);
	CStatic* p_static4		  = (CStatic*)GetDlgItem(IDC_STATIC_OUTPUT_TYPE);
	CStatic* p_static7		  = (CStatic*)GetDlgItem(IDC_STATIC_OUT_RULE);
	CStatic* p_static6		  = (CStatic*)GetDlgItem(IDC_STATIC_INPUT_RULE);
	CStatic* p_staticCS		  = (CStatic*)GetDlgItem(IDC_LABEL_COODINATE_INPUT);
	//CStatic* p_static8		  = (CStatic*)GetDlgItem(IDC_STATIC88);

	//CStatic* p_Proc			  = (CStatic*)GetDlgItem(IDC_STATIC_PROC);
	CEdit* p_edit1			  = (CEdit*)GetDlgItem(IDC_EDIT_INPUT);
	CEdit* p_edit2			  = (CEdit*)GetDlgItem(IDC_EDIT_OUTPUT);
	CButton* p_btn1			  = (CButton*)GetDlgItem(IDC_BTN_INPUT);
	CButton* p_btn2			  = (CButton*)GetDlgItem(IDC_BTN_OUTPUT);
	/*CButton* p_btnEXE		  = (CButton*)GetDlgItem(IDC_BTN_EXE);*/

	CComboBox* p_combox1	  = (CComboBox*)GetDlgItem(IDC_COMBO_INPUT);
	CComboBox* p_combox2	  = (CComboBox*)GetDlgItem(IDC_COMBO_OUTPUT);
	CComboBox* p_combox3	  = (CComboBox*)GetDlgItem(IDC_COMBO_TRANMODEL);	
	CComboBox* p_combox4	  = (CComboBox*)GetDlgItem(IDC_COMBO_INPUT_RULE);
	CComboBox* p_combox5	  = (CComboBox*)GetDlgItem(IDC_COMBO_OUT_RULE);

	CStatic* p_static5		  = (CStatic*)GetDlgItem(IDC_STATIC_MODEL);
	CProgressCtrl* p_progress = (CProgressCtrl*)GetDlgItem(IDC_PROGRESS1);

	if(p_progress->GetSafeHwnd()){

		/* 调整控件相对位置  */

		//当前窗口矩形
		this->GetWindowRect(&rctwnd);

		//1. 静态边框
		p_static1->GetWindowRect(&rct);
		rct.left = rctwnd.left+10;
		rct.right = rctwnd.right-10;
		ScreenToClient(&rct);
		p_static1->MoveWindow(&rct);

		p_static2->GetWindowRect(&rct);	
		rct.left = rctwnd.left+10;
		rct.right = rctwnd.right-10;
		ScreenToClient(&rct);
		p_static2->MoveWindow(&rct);

		ClientToScreen(&rct); //获取静态框的相对坐标

		int iTotalWidth = rct.Width();
		int iPerThreeWidth = iTotalWidth / 3 ;
		CRect rcstaticCS;
		p_staticCS->GetWindowRect(&rcstaticCS);
		int iScaleLeft = rcstaticCS.left + iPerThreeWidth ;

		//2. 文本框
		p_edit1->GetWindowRect(&relRct);
		relRct.right = rct.right-60;
		ScreenToClient(&relRct);
		p_edit1->MoveWindow(&relRct);

		p_edit2->GetWindowRect(&relRct);
		relRct.right = rct.right-60;
		ScreenToClient(&relRct);
		p_edit2->MoveWindow(&relRct);

		//3. 按钮		
		p_btn1->GetWindowRect(&relRct);
		relRct.left = rct.right - 55;
		relRct.right = rct.right - 5;
		ScreenToClient(&relRct);
		p_btn1->MoveWindow(&relRct);

		p_btn2->GetWindowRect(&relRct);
		relRct.left = rct.right - 55;
		relRct.right = rct.right - 5;
		ScreenToClient(&relRct);
		p_btn2->MoveWindow(&relRct);

		//输入类型下拉框
		// rc 实际记录的是文本框
		int nWidth,nHeight;		
		p_combox1->GetWindowRect(&relRct);
		relRct.left  = rct.right - 165;
		relRct.right = rct.right - 60;
		ScreenToClient(&relRct);
		p_combox1->MoveWindow(&relRct);

		p_static3->GetWindowRect(&relRct);
		nWidth = relRct.Width();
		relRct.left  = rct.right - nWidth -165;
		relRct.right = relRct.left + nWidth;
		ScreenToClient(&relRct);
		p_static3->MoveWindow(&relRct);

		int iScaleLeft1 = iScaleLeft + 60;
		p_combox4->GetWindowRect(&relRct);
		relRct.left = iScaleLeft1-15 ;
		relRct.right = iScaleLeft1 + 75;
		ScreenToClient(&relRct);
		p_combox4->MoveWindow(&relRct);

		p_static6->GetWindowRect(&relRct);
		relRct.left = iScaleLeft-10 ;
		relRct.right = iScaleLeft + 40;
		ScreenToClient(&relRct);
		p_static6->MoveWindow(&relRct);	

		//输出类型下拉框
		p_combox2->GetWindowRect(&relRct);
		relRct.left  = rct.right - 165;
		relRct.right = rct.right - 60;
		ScreenToClient(&relRct);
		p_combox2->MoveWindow(&relRct);

		p_static4->GetWindowRect(&relRct);
		nWidth = relRct.Width();
		relRct.left  = rct.right - nWidth - 165;
		relRct.right = relRct.left + nWidth;
		ScreenToClient(&relRct);
		p_static4->MoveWindow(&relRct);	

		int iScaleLeft2 = iScaleLeft + 60;
		p_combox5->GetWindowRect(&relRct);
		relRct.left = iScaleLeft2-15 ;
		relRct.right = iScaleLeft2 + 75;
		ScreenToClient(&relRct);
		p_combox5->MoveWindow(&relRct);	

		p_static7->GetWindowRect(&relRct);
		relRct.left = iScaleLeft-10 ;
		relRct.right = iScaleLeft + 40;
		ScreenToClient(&relRct);
		p_static7->MoveWindow(&relRct);	

		m_Controlpoint_Dlg.GetWindowRect(&relRct);
		int nTop_offset = relRct.Height();
		relRct.left  = rctwnd.left+10;
		relRct.right = rctwnd.right-10;
		relRct.top = rct.bottom + 10;
		relRct.bottom = relRct.top+nTop_offset;
		nTop_offset = relRct.bottom+10;
		ScreenToClient(&relRct);
		m_Controlpoint_Dlg.MoveWindow(&relRct);

		//5. 进度显示区域
		p_static5->GetWindowRect(&relRct);
		nHeight = relRct.Height();
		relRct.top = nTop_offset+3;
		relRct.bottom = relRct.top+nHeight;
		ScreenToClient(&relRct);
		p_static5->MoveWindow(&relRct);

		p_combox3->GetWindowRect(&relRct);
		nHeight = relRct.Height();
		relRct.top = nTop_offset;
		relRct.bottom = relRct.top+nHeight;
		ScreenToClient(&relRct);
		p_combox3->MoveWindow(&relRct);

		//进度条对应执行按钮
		/*p_btnEXE->GetWindowRect(&relRct);
		nWidth = relRct.Width();
		nHeight = relRct.Height();
		relRct.top = nTop_offset;
		relRct.bottom = relRct.top+nHeight;
		relRct.left = rct.right - 10 - nWidth;
		relRct.right = rct.right - 10;
		ScreenToClient(&relRct);
		p_btnEXE->MoveWindow(&relRct);*/

		//ScreenToClient(&rct);	
		//p_Proc->GetWindowRect(&relRct);
		//nWidth  = relRct.Width();
		////nHeight = relRct.Height();
		////relRct.top = nTop_offset+5;
		////relRct.bottom = relRct.top+nHeight;
		//relRct.left = rct.Width()/2-10;
		//relRct.right = relRct.left+nWidth;
		//ScreenToClient(&relRct);
		//p_Proc->MoveWindow(&relRct);

		p_progress->GetWindowRect(&relRct);
		nHeight = relRct.Height();
		relRct.top = nTop_offset+40;
		relRct.bottom = relRct.top+nHeight;
		relRct.right = rctwnd.right -10;
		ScreenToClient(&relRct);
		p_progress->MoveWindow(&relRct);
	}
}

//int CDeuVectorProjectTranDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
//{
//	if (CDialog::OnCreate(lpCreateStruct) == -1)
//		return -1;
//
//
//	
//	return 0;
//}

//void CDeuVectorProjectTranDlg::OnInitialUpdate()
//{
//	CDialog::OnInitialUpdate();
//
//
//}

BOOL CDeuVectorProjectTranDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//m_edit_InputFile.Initialize(this, BES_XT_CHOOSEFILE);
	//m_edit_InputFile.SetDlgTitle(_T("Browse"));
	//m_edit_InputFile.SetDlgFilter(_T("Shapefile(*.shp)|*.shp|位图(*.bmp)|*.bmp|JPEG(*.jpg)|*.jpg||"));

	//m_edit_OutputFile.Initialize(this, BES_XT_CHOOSEFILE);
	//m_edit_OutputFile.SetDlgTitle(_T("Browse"));
	//m_edit_OutputFile.SetDlgFilter(_T("Shapefile(*.shp)|*.shp|位图(*.bmp)|*.bmp|JPEG(*.jpg)|*.jpg||"));

	//CStatic* p_static6 = (CStatic*)GetDlgItem(IDC_STATIC_RECOLLECT);
	CButton* p_radio1		=	(CButton*)GetDlgItem(IDC_RADIO_resample);
	CButton* p_radio2		=	(CButton*)GetDlgItem(IDC_RADIO_transfer);
	CButton* p_btn_RasterSetting = (CButton*)GetDlgItem(IDC_BTN_SETTING);

	p_radio1->ShowWindow(SW_HIDE);
	p_radio2->ShowWindow(SW_HIDE);
	p_btn_RasterSetting->ShowWindow(SW_HIDE); 

	m_ComboReCollect.ShowWindow(SW_HIDE);
	m_ComboTransfer.ShowWindow(SW_HIDE);

	this->m_Progress.SetRange32(0, 100);
	this->m_Progress.SetTheme(xtpControlThemeOffice2000);

	m_Controlpoint_Dlg.Create(IDD_DLG_CONTROL_POINT, this);
	m_Controlpoint_Dlg.ShowWindow(SW_SHOW);

	/*for(int n=0; n<7; n++){
	m_ComboInput.InsertString(n, sz_TranType_Vector[n]);
	m_ComboOutput.InsertString(n, sz_TranType_Vector[n]);
	}*/

	InitTransFormat();

	m_ComboInput.SetCurSel(0);
	m_ComboOutput.SetCurSel(0);

	for(int n=0; n<_TranModel_Project_num; n++)
	{
		m_ComboTranModel.InsertString(n, sz_TranModel_Project[n]);
	}
	m_ComboTranModel.SetCurSel(0);

	CButton* m_chk_dem = (CButton*)this->GetDlgItem(IDC_CHK_DEM);
	m_chk_dem->ShowWindow(SW_HIDE);

	//屏蔽比例尺
	GetDlgItem(IDC_COMBO_INPUT_RULE)->ShowWindow(false);
	GetDlgItem(IDC_COMBO_OUT_RULE)->ShowWindow(false);

	GetDlgItem(IDC_STATIC_INPUT_RULE)->ShowWindow(false);
	GetDlgItem(IDC_STATIC_OUT_RULE)->ShowWindow(false);

	return TRUE;
}




void CDeuVectorProjectTranDlg::OnBnClickedBtnInput()
{
	/*CFileDialog m_FileDlg(true,"Shapefile", "*.shp",OFN_FILEMUSTEXIST|OFN_HIDEREADONLY, "Shapefile(*.shp)|*.shp|位图(*.bmp)|*.bmp|JPEG(*.jpg)|*.jpg||",NULL);
	m_FileDlg.m_ofn.lpstrTitle = _T("打开矢量文件");
	if(m_FileDlg.DoModal() == IDOK)
	{
	CEdit* p_edit1 = (CEdit*)GetDlgItem(IDC_EDIT_INPUT);
	p_edit1->SetWindowText(m_FileDlg.GetPathName());
	}*/

	CString m_str;
	m_ComboInput.GetWindowText(m_str);
	if(m_str == sz_TranType_Vector[4])	//数据库
	{
		CDeuDlgOraTables m_tables(VECTOR_PROJ, this);
		m_tables.m_oracle.strSID  = strDBSid_Src;
		m_tables.m_oracle.strUser = strDBUser_Src;
		m_tables.m_oracle.strPwd  = strDBPwd_Src;
		m_tables.StatusAction = "In";
		m_tables.DoModal();
	}
	else
	{
		CDeuDlgFiles m_file(VECTOR_PROJ, this);
		if(!strLastPath.IsEmpty())
		{
			m_file.strLastPath = strLastPath;
		}

		m_file.strFileType = m_str;
		if(m_file.DoModal() == IDOK)
		{
			strLastPath = m_file.strLastPath;
			m_edit_InputFile.SetWindowText(strLastPath);
		}
	}

}

void CDeuVectorProjectTranDlg::OnBnClickedBtnOutput()
{
	CString strType;
	m_ComboOutput.GetWindowText(strType);
	//Oracle
	if(strType == sz_TranType_Vector[4])
	{
		CDeuDlgOraTables m_tables(VECTOR_PROJ, this);
		m_tables.IsHideChkbox = TRUE;
		m_tables.m_oracle.strSID = this->strDBSid_Dest;
		m_tables.m_oracle.strUser = this->strDBUser_Dest;
		m_tables.m_oracle.strPwd = this->strDBPwd_Dest;		
		m_tables.StatusAction = "Out";
		m_tables.DoModal();
	}
	else
	{
		//alter by chenyong 2013-3-12
		/*char dir[MAX_PATH];
		AfxSelectDirDlg(dir);
		CEdit* p_edit2 = (CEdit*)GetDlgItem(IDC_EDIT_OUTPUT);
		if(strlen(dir) != 0)
		p_edit2->SetWindowText(dir);*/

		char							dir[MAX_PATH] = {0};
		CString							strOutPutDir = _T("");
		m_edit_OutputFile.GetWindowText(strOutPutDir);

		SelectDirDlg(strOutPutDir, dir);
		if (strlen(dir) > 0)
		{
			m_edit_OutputFile.SetWindowText(dir);
		}
	}
}



void CDeuVectorProjectTranDlg::OnCoordinateInput()
{
	/*
	CDeuDlgDataSrc m_DataSrcDlg;
	m_DataSrcDlg.DoModal();

	CEdit* p_edit = (CEdit*)GetDlgItem(IDC_EDIT_COORINATE_INPUT);
	if(!m_DataSrcDlg.m_strSelectItem.IsEmpty())
	p_edit->SetWindowText(m_DataSrcDlg.m_strSelectItem);


	//设置控制点的输入坐标系
	m_Controlpoint_Dlg.SetSrcCoorType(m_DataSrcDlg.m_strSelectItem);*/

	CString                                 strSelect;
	GetDlgItem(IDC_EDIT_COORINATE_INPUT)->GetWindowText(strSelect);

	CDeuDlgEllipManager m_DataSrcDlg;

	if (m_DataSrcDlg.DoModal() == IDOK)
	{
		CEdit* p_edit = (CEdit*)GetDlgItem(IDC_EDIT_COORINATE_INPUT);
		if(!m_DataSrcDlg.m_strEllipName.IsEmpty())
			p_edit->SetWindowText(m_DataSrcDlg.m_strEllipName);

		//设置控制点的输入坐标系
		m_Controlpoint_Dlg.SetSrcCoorType(m_DataSrcDlg.m_strEllipName);
	}
}

void CDeuVectorProjectTranDlg::OnCoordinateOutput()
{
	/*
	CDeuDlgDataSrc m_DataSrcDlg;
	m_DataSrcDlg.DoModal();

	CEdit* p_edit = (CEdit*)GetDlgItem(IDC_EDIT_COORINATE_OUTPUT);
	if(!m_DataSrcDlg.m_strSelectItem.IsEmpty())
	p_edit->SetWindowText(m_DataSrcDlg.m_strSelectItem);

	//设置控制点的输出坐标系
	m_Controlpoint_Dlg.SetDesCoorType(m_DataSrcDlg.m_strSelectItem);
	*/

	CDeuDlgEllipManager m_DataSrcDlg;

	if (m_DataSrcDlg.DoModal() == IDOK)
	{
		CEdit* p_edit = (CEdit*)GetDlgItem(IDC_EDIT_COORINATE_OUTPUT);
		if(!m_DataSrcDlg.m_strEllipName.IsEmpty())
			p_edit->SetWindowText(m_DataSrcDlg.m_strEllipName);

		//设置控制点的输入坐标系
		m_Controlpoint_Dlg.SetDesCoorType(m_DataSrcDlg.m_strEllipName);
	}
}


//设置转换模型参数
void CDeuVectorProjectTranDlg::OnCbnSelchangeComboTranmodel()
{
	CComboBox* p_combox3	  = (CComboBox*)GetDlgItem(IDC_COMBO_TRANMODEL);
	p_combox3->GetWindowText(m_Controlpoint_Dlg.m_strModel);



	if( m_Controlpoint_Dlg.m_strModel == "布尔莎转换模型")
	{		
		iModel=MODEL_BURSA;
	}
	else if(m_Controlpoint_Dlg.m_strModel == "二维七参数转换模型")
	{		
		iModel=MODEL_D2P7;
	}
	else if (m_Controlpoint_Dlg.m_strModel == "三维七参数转换模型")
	{	
		iModel=MODEL_D3P7;
	}
	else if (m_Controlpoint_Dlg.m_strModel == "平面四参数转换模型")
	{		
		iModel=MODEL_D2P4;
	}
	else if (m_Controlpoint_Dlg.m_strModel == "格网转换模型")
	{
		iModel=MODEL_GRID;
	}
	else if (m_Controlpoint_Dlg.m_strModel == "高斯投影"  )
	{
		iModel = MODEL_GAUSS;
	}
	else if (m_Controlpoint_Dlg.m_strModel == "横轴墨卡托投影")
	{
		iModel = MODEL_TM;
	}
	else if (m_Controlpoint_Dlg.m_strModel == "通用横轴墨卡托投影")
	{
		iModel = MODEL_UTM;
	}

	//this->SendMessage(WM_PROGRESS, NULL, NULL);
}



//下拉框事件
void CDeuVectorProjectTranDlg::OnCbnSelchangeComboInput()
{
	//ClearCache(FALSE);

	CString strType;
	m_ComboInput.GetWindowText(strType);
	if(strType == sz_TranType_Vector[4])
	{

		if(!GobalUserInfo.IsDataBaseConvert)
		{
			MessageBox(PowerError, "系统提示", MB_OK|MB_ICONWARNING);
			m_ComboInput.SetCurSel(0);
			return;
		}


		//配置oracle
		CDeuDlgOracle m_dlg(VECTOR, this, FALSE);
		if(m_dlg.DoModal() == IDOK)
		{
			this->m_edit_InputFile.SetWindowText(m_dlg.strConn);

			strDBSid_Src  = m_dlg.strSID;
			strDBUser_Src = m_dlg.strUser;
			strDBPwd_Src  = m_dlg.strPwd;

			CDeuDlgOraTables m_tables(VECTOR, this);
			m_tables.m_oracle.strSID  = strDBSid_Src;
			m_tables.m_oracle.strUser = strDBUser_Src;
			m_tables.m_oracle.strPwd  = strDBPwd_Src;

			m_tables.StatusAction = "In";
			m_tables.DoModal();
		}
	}
	else if (strType == _T("ArcSDE"))//add by chenyong for arcsde project 2013-11-25
	{

		CDeuSDEConnectProperty	conPro;

		//初始化ArcSDE配置
		CString			strRate = GetStylesPath() + _T("\\Rate.ini");
		STR_SDE_PARAM	param;

		::GetPrivateProfileString(_T("VECTORPROJSRC"), _T("SERVER"), _T(""), param.strServer.GetBuffer(MAX_PATH), MAX_PATH, (LPCTSTR)strRate);
		::GetPrivateProfileString(_T("VECTORPROJSRC"), _T("SERVICE"), _T(""), param.strService.GetBuffer(MAX_PATH), MAX_PATH, (LPCTSTR)strRate);
		::GetPrivateProfileString(_T("VECTORPROJSRC"), _T("DATABASE"), _T(""), param.strDatabase.GetBuffer(MAX_PATH), MAX_PATH, (LPCTSTR)strRate);
		::GetPrivateProfileString(_T("VECTORPROJSRC"), _T("USERNAME"), _T(""), param.strUsername.GetBuffer(MAX_PATH), MAX_PATH, (LPCTSTR)strRate);
		::GetPrivateProfileString(_T("VECTORPROJSRC"), _T("PASSWORD"), _T(""), param.strPassword.GetBuffer(MAX_PATH), MAX_PATH, (LPCTSTR)strRate);
		::GetPrivateProfileString(_T("VECTORPROJSRC"), _T("VERSION"), _T(""), param.strVersion.GetBuffer(MAX_PATH), MAX_PATH, (LPCTSTR)strRate);
		conPro.SetParam(param);

		if (conPro.DoModal() == IDOK)
		{
			m_pSrcWS = conPro.GetWorkspace();
			this->m_edit_InputFile.SetWindowText(conPro.GetConnString());

			CArcSDEVector				sdevec(m_pSrcWS);
			vector<STR_SDEINFO>			vecAll;


			sdevec.GetAllFeatureNameAndType(vecAll);
			CSdeSelect					sdeSel(vecAll);
			//sdeSel.InitShowData(vecAll);

			if (sdeSel.DoModal() == IDOK)
			{
				m_vecSelect = sdeSel.GetSelectItem();
			}

			//保存配置信息
			param = conPro.GetParam();
			::WritePrivateProfileString(_T("VECTORPROJSRC"), _T("SERVER"), param.strServer, strRate);
			::WritePrivateProfileString(_T("VECTORPROJSRC"), _T("SERVICE"), param.strService, strRate);
			::WritePrivateProfileString(_T("VECTORPROJSRC"), _T("DATABASE"), param.strDatabase, strRate);
			::WritePrivateProfileString(_T("VECTORPROJSRC"), _T("USERNAME"), param.strUsername, strRate);
			::WritePrivateProfileString(_T("VECTORPROJSRC"), _T("PASSWORD"), param.strPassword, strRate);
			::WritePrivateProfileString(_T("VECTORPROJSRC"), _T("VERSION"), param.strVersion, strRate);

		}

		((CButton*)GetDlgItem(IDC_BTN_INPUT))->EnableWindow(FALSE);

	}
	else
	{
		((CButton*)GetDlgItem(IDC_BTN_INPUT))->EnableWindow(TRUE);
	}

}



//输出下拉框事件
void CDeuVectorProjectTranDlg::OnCbnSelchangeComboOutput()
{
	//ClearCache(TRUE);

	CString strType;
	m_ComboOutput.GetWindowText(strType);
	if(strType == sz_TranType_Vector[4])
	{
		if(!GobalUserInfo.IsDataBaseConvert)
		{
			MessageBox(PowerError, "系统提示", MB_OK|MB_ICONWARNING);
			m_ComboOutput.SetCurSel(0);
			return;
		}


		//配置oracle
		CDeuDlgOracle m_dlg(VECTOR, this, TRUE);
		if(m_dlg.DoModal() == IDOK)
		{
			this->m_edit_OutputFile.SetWindowText(m_dlg.strConn);

			strDBSid_Dest  = m_dlg.strSID;
			strDBUser_Dest = m_dlg.strUser;
			strDBPwd_Dest  = m_dlg.strPwd;
		}
	}
	else if (strType == _T("ArcSDE")) //add by chenyong 2013-11-25
	{

		CDeuSDEConnectProperty	conDesPro;

		//初始化ArcSDE配置
		CString			strRate = GetStylesPath() + _T("\\Rate.ini");
		STR_SDE_PARAM	param;

		::GetPrivateProfileString(_T("VECTORPROJDES"), _T("SERVER"), _T(""), param.strServer.GetBuffer(MAX_PATH), MAX_PATH, (LPCTSTR)strRate);
		::GetPrivateProfileString(_T("VECTORPROJDES"), _T("SERVICE"), _T(""), param.strService.GetBuffer(MAX_PATH), MAX_PATH, (LPCTSTR)strRate);
		::GetPrivateProfileString(_T("VECTORPROJDES"), _T("DATABASE"), _T(""), param.strDatabase.GetBuffer(MAX_PATH), MAX_PATH, (LPCTSTR)strRate);
		::GetPrivateProfileString(_T("VECTORPROJDES"), _T("USERNAME"), _T(""), param.strUsername.GetBuffer(MAX_PATH), MAX_PATH, (LPCTSTR)strRate);
		::GetPrivateProfileString(_T("VECTORPROJDES"), _T("PASSWORD"), _T(""), param.strPassword.GetBuffer(MAX_PATH), MAX_PATH, (LPCTSTR)strRate);
		::GetPrivateProfileString(_T("VECTORPROJDES"), _T("VERSION"), _T(""), param.strVersion.GetBuffer(MAX_PATH), MAX_PATH, (LPCTSTR)strRate);
		conDesPro.SetParam(param);

		if (conDesPro.DoModal() == IDOK)
		{
			m_pDesWS = conDesPro.GetWorkspace();
			this->m_edit_OutputFile.SetWindowText(conDesPro.GetConnString());

			//保存配置信息
			param = conDesPro.GetParam();
			::WritePrivateProfileString(_T("VECTORPROJDES"), _T("SERVER"), param.strServer, strRate);
			::WritePrivateProfileString(_T("VECTORPROJDES"), _T("SERVICE"), param.strService, strRate);
			::WritePrivateProfileString(_T("VECTORPROJDES"), _T("DATABASE"), param.strDatabase, strRate);
			::WritePrivateProfileString(_T("VECTORPROJDES"), _T("USERNAME"), param.strUsername, strRate);
			::WritePrivateProfileString(_T("VECTORPROJDES"), _T("PASSWORD"), param.strPassword, strRate);
			::WritePrivateProfileString(_T("VECTORPROJDES"), _T("VERSION"), param.strVersion, strRate);

		}

		((CButton*)GetDlgItem(IDC_BTN_OUTPUT))->EnableWindow(FALSE);

	}
	else
	{
		((CButton*)GetDlgItem(IDC_BTN_OUTPUT))->EnableWindow(TRUE);
	}
}




void CDeuVectorProjectTranDlg::LoadExistData(CString m_str[6])
{
	CEdit* p_edit_input			= (CEdit*)GetDlgItem(IDC_EDIT_INPUT);
	CEdit* p_edit_output		= (CEdit*)GetDlgItem(IDC_EDIT_OUTPUT);
	CEdit* p_edit_incoord		= (CEdit*)GetDlgItem(IDC_EDIT_COORINATE_INPUT);
	CEdit* p_edit_outcoord		= (CEdit*)GetDlgItem(IDC_EDIT_COORINATE_OUTPUT);	

	p_edit_input->SetWindowText(m_str[0]);
	p_edit_output->SetWindowText(m_str[1]);
	p_edit_incoord->SetWindowText(m_str[2]);
	p_edit_outcoord->SetWindowText(m_str[3]);

	m_Controlpoint_Dlg.m_Edit_Src.SetWindowText(m_str[4]);
	m_Controlpoint_Dlg.m_Edit_Dest.SetWindowText(m_str[5]);
}



void CDeuVectorProjectTranDlg::ClearCache(BOOL IsOut)
{	
	if(!IsOut)
	{
		this->_FilsList.RemoveAll();
		this->_FilsList_selected.RemoveAll();
		this->_TablesList.RemoveAll();
		this->_TablesList_selected.RemoveAll();
		this->m_edit_InputFile.SetWindowText("");
		this->strLastPath.Empty();
	}
	else
	{
		this->m_edit_OutputFile.SetWindowText("");
	}
}


//转换结束通知消息面板
void CDeuVectorProjectTranDlg::TranFinish(const char* strTimeMsg)
{

}


//转换结束通知消息面板
void CDeuVectorProjectTranDlg::ShowStatusPanel(CString str)
{

	//((CDeuGlobalMainFrame*)::AfxGetMainWnd())->
	((CDeuGlobalMainFrame*)theApp.m_pMainWnd)->SendMessage(WM_VEC_MSGPANEL, NULL, (LPARAM)str.GetBuffer());

	/*CString strDescript;
	m_Progress.GetWindowText(strDescript);
	strDescript += "  "+str;
	this->m_Progress.SetWindowText(strDescript);
	m_Progress.Invalidate();*/



}


BOOL CDeuVectorProjectTranDlg::CheckControl()
{

	//CEdit* p_edit_input			= (CEdit*)GetDlgItem(IDC_EDIT_INPUT);
	//CEdit* p_edit_output		= (CEdit*)GetDlgItem(IDC_EDIT_OUTPUT);
	//CEdit* p_edit_incoord		= (CEdit*)GetDlgItem(IDC_EDIT_COORINATE_INPUT);
	//CEdit* p_edit_outcoord		= (CEdit*)GetDlgItem(IDC_EDIT_COORINATE_OUTPUT);
	//CComboBox* p_combox_input	= (CComboBox*)GetDlgItem(IDC_COMBO_INPUT);
	//CComboBox* p_combox_output	= (CComboBox*)GetDlgItem(IDC_COMBO_OUTPUT);
	//CComboBox* p_combox_model	= (CComboBox*)GetDlgItem(IDC_COMBO_TRANMODEL);


	CString m_strInputFile;
	CString m_strOutputFile;
	CString m_strInCoord;
	CString m_strOutCoord; 

	m_edit_InputFile.GetWindowText(m_strInputFile);
	m_strInputFile = m_strInputFile.Trim();

	m_edit_OutputFile.GetWindowText(m_strOutputFile);
	m_strOutputFile = m_strOutputFile.Trim();

	m_edit_InCoord.GetWindowText(m_strInCoord);
	m_strInCoord = m_strInCoord.Trim();

	m_edit_OutCoord.GetWindowText(m_strOutCoord);
	m_strOutCoord = m_strOutCoord.Trim();

	if(m_strInputFile.IsEmpty())
	{
		AfxMessageBox("请选择“输入路径”");
		return FALSE;
	}
	else if(m_strOutputFile.IsEmpty())
	{
		AfxMessageBox("请设定“输出路径”");
		return FALSE;
	}
	else if(m_strInCoord.IsEmpty())
	{
		AfxMessageBox("请选择“输入坐标系”");
		return FALSE;
	}
	else if(m_strOutCoord.IsEmpty())
	{
		AfxMessageBox("请设定“输出坐标系”");
		return FALSE;
	}
	else if(this->m_Controlpoint_Dlg.m_List.GetItemCount() == 0)
	{
		if(iModel == MODEL_GRID)
			return TRUE;

		if(iModel == MODEL_GAUSS )
			return TRUE;

		if(iModel == MODEL_TM )
			return TRUE;

		if(iModel == MODEL_UTM )
			return TRUE;

		AfxMessageBox("请设定“控制点”");
		return FALSE;
	}

	return TRUE;

	/*else
	{

	}*/

	/*p_edit_output->GetWindowText(strTmp);
	strTmp = strTmp.Trim();
	if(strTmp.IsEmpty())
	{
	AfxMessageBox("请输入转换后的输出文件");
	}*/
}


LRESULT CDeuVectorProjectTranDlg::OnProgressStep(WPARAM wParam, LPARAM lParam)
{
	unsigned int i=(unsigned int)lParam;
	LRESULT result = Default();

	//juno
	/*if(i==0){
	KillTimer(1);
	SetTimer(2,1000,NULL);
	}
	if(i>=20){
	KillTimer(2);
	CWnd *pWnd;
	pWnd = GetDlgItem(IDC_STATIC88);
	pWnd->ShowWindow(SW_HIDE);
	}*/

	CString strDescript;
	strDescript.Format("%d%%", i);	
	m_Progress.SetWindowText(strDescript);
	this->m_Progress.SetPos(i);

	return result;
}




void CDeuVectorProjectTranDlg::DisableAllController()
{
	CButton* p_btn1			  = (CButton*)GetDlgItem(IDC_BTN_INPUT);
	CButton* p_btn2			  = (CButton*)GetDlgItem(IDC_BTN_OUTPUT);

	p_btn1->EnableWindow(FALSE);
	p_btn2->EnableWindow(FALSE);
	m_ComboInput.EnableWindow(FALSE);
	m_ComboOutput.EnableWindow(FALSE);
	m_ComboTranModel.EnableWindow(FALSE);
	m_ComboReCollect.EnableWindow(FALSE);
	m_edit_InCoord.EnableWindow(FALSE);
	m_edit_OutCoord.EnableWindow(FALSE);

	m_Controlpoint_Dlg.DisableAllController();

}


void CDeuVectorProjectTranDlg::EnbleAllController()
{
	CButton* p_btn1			  = (CButton*)GetDlgItem(IDC_BTN_INPUT);
	CButton* p_btn2			  = (CButton*)GetDlgItem(IDC_BTN_OUTPUT);

	p_btn1->EnableWindow(TRUE);
	p_btn2->EnableWindow(TRUE);
	m_ComboInput.EnableWindow(TRUE);
	m_ComboOutput.EnableWindow(TRUE);
	m_ComboTranModel.EnableWindow(TRUE);
	m_ComboReCollect.EnableWindow(TRUE);
	m_edit_InCoord.EnableWindow(TRUE);
	m_edit_OutCoord.EnableWindow(TRUE);

	m_Controlpoint_Dlg.EnbleAllController();
}


//判断大地坐标是否存在
BOOL CDeuVectorProjectTranDlg::CheckCoord()
{

	BOOL Input=TRUE, Output=TRUE;
	CString strInput, strOutput;
	m_edit_InCoord.GetWindowText(strInput);
	m_edit_OutCoord.GetWindowText(strOutput);

	//检查输入数据
	char* sz_result = TaskProc.FindCoordType(strInput);
	if(lstrcmp(sz_result, "0") == 0)
	{

		Input= FALSE;
	}
	else if(lstrcmp(sz_result, "1")  == 0) //GEODETIC 
	{
		Input = TRUE;
	}
	else if(lstrcmp(sz_result, "3")  == 0)
	{
		for(int n=0; n<GeoDataMapping.ProjectedNode.pProjectedSeries.GetCount(); n++)
		{
			if(strInput == GeoDataMapping.ProjectedNode.pProjectedSeries.GetAt(n)._name.text){
				for(int m=0; m<GeoDataMapping.GeodeticNode.pGeodeticSeries.GetCount(); m++)
				{
					if(GeoDataMapping.ProjectedNode.pProjectedSeries.GetAt(n)._geodeticPointor.text == GeoDataMapping.GeodeticNode.pGeodeticSeries.GetAt(m)._name.text){
						Input = TRUE;
						break;	
					}
					else
						Input = FALSE;
				}
			}
		}
	}


	//检查输出数据
	char* sz_result_out = TaskProc.FindCoordType(strOutput);
	if(lstrcmp(sz_result_out, "0")  == 0 )
	{
		Output= FALSE;
	}
	else if(lstrcmp(sz_result_out, "1") == 0 ) //GEODETIC 
	{
		Output = TRUE;
	}
	else if(lstrcmp(sz_result_out, "3") == 0)
	{
		for(int n=0; n<GeoDataMapping.ProjectedNode.pProjectedSeries.GetCount(); n++)
		{
			if(strOutput == GeoDataMapping.ProjectedNode.pProjectedSeries.GetAt(n)._name.text){
				for(int m=0; m<GeoDataMapping.GeodeticNode.pGeodeticSeries.GetCount(); m++)
				{
					if(GeoDataMapping.ProjectedNode.pProjectedSeries.GetAt(n)._geodeticPointor.text == GeoDataMapping.GeodeticNode.pGeodeticSeries.GetAt(m)._name.text){
						Output = TRUE;
						break;
					}
					else{
						Output = FALSE;
					}
				}
			}
		}
	}
	if(Input && Output){
		return TRUE;
	}
	else if(!Input && Output){
		AfxMessageBox("输入坐标系不存在，无法执行转换");
		return FALSE;
	}
	else if(Input && !Output){
		AfxMessageBox("输出坐标系不存在，无法执行转换");
		return FALSE;
	}
	else if(!Input || !Output){
		AfxMessageBox("输入输出坐标系不存在，无法执行转换");
		return FALSE;
	}

	return TRUE;

}


void CDeuVectorProjectTranDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()
}



void CDeuVectorProjectTranDlg::OnBnClickedButton1()
{

}


void CDeuVectorProjectTranDlg::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
}

//juno
//void CDeuVectorProjectTranDlg::OnTimer(UINT nIDEvent) 
//{
//	// TODO: Add your message handler code here and/or call default
//	//OnButtonShapedAnimation();
//    CWnd *pwnd= GetDlgItem(IDC_STATIC88);
//	pwnd->ShowWindow(SW_SHOW);
// //   int len = str.GetLength();
// //   CString  str1= str.Left(8);
//	//CString  str2 = str.Right(len-8);
//	//str= str2 +str1;
//	//pwnd->SetWindowText(str); 
// //   //Invalidate();
//	//UpdateWindow();
//	 if(nIDEvent==1){
//          int len = str4.GetLength();
//    CString  str1= str4.Left(8);
//	CString  str2 = str4.Right(len-8);
//	str4= str2 +str1;
//	pwnd->SetWindowText(str4); 
//    //Invalidate();
//	UpdateWindow();
//	
//     }
//	 else if(nIDEvent==2){
//           int len = str5.GetLength();
//    CString  str1= str5.Left(8);
//	CString  str2 = str5.Right(len-8);
//	str5= str2 +str1;
//	pwnd->SetWindowText(str5); 
//    //Invalidate();
//	UpdateWindow();
//	
//	 }
//	CDialog::OnTimer(nIDEvent); 
//}

int CDeuVectorProjectTranDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	//SetTimer(1,1000,NULL);
	// TODO: Add your specialized creation code here
	return 0;
}

void CDeuVectorProjectTranDlg::InitTransFormat()
{
	for (int i = 0; i < GobalFormat.FormatTypeList[0]->TypeList.size(); i++)
	{
		if (GobalFormat.FormatTypeList[0]->TypeList[i].type == _T("1"))
		{
			m_ComboInput.AddString(GobalFormat.FormatTypeList[0]->TypeList[i].text);
			m_ComboOutput.AddString(GobalFormat.FormatTypeList[0]->TypeList[i].text);
		}
	}
}


IWorkspacePtr CDeuVectorProjectTranDlg::GetSrcWorkspace() const
{
	return m_pSrcWS;
}

IWorkspacePtr CDeuVectorProjectTranDlg::GetDesWorkspace() const
{
	return  m_pDesWS;
}


vector<STR_SDEINFO> CDeuVectorProjectTranDlg::GetSelVec() const
{
	return m_vecSelect;
}
