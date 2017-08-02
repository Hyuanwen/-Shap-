// DeuTmpDlg.cpp : ʵ���ļ�

#include "stdafx.h"
#include "resource.h"
#include "DeuRasterProjectTranDlg.h"
#include "DeuGlobalParam.h"
#include "DeuDlgDataSrc.h"
#include "DeuDlgFiles.h"
#include "DeuDlgOraTables.h"
#include "DeuDlgOracle.h"
#include "DeuGlobalMainFrm.h"

//add by chenyong 2013-11-26
//#include "DeuSDEConnectProperty.h"
//#include "ArcSDERaster.h"
//#include "SdeSelect.h"

IMPLEMENT_DYNCREATE(CDeuRasterProjectTranDlg, CDialog)
CDeuRasterProjectTranDlg::CDeuRasterProjectTranDlg()
	: CDialog(CDeuRasterProjectTranDlg::IDD), m_Controlpoint_Dlg(RASTER)
{
	//this->SetScrollSizes(MM_TEXT,CSize(800,800));
	iModel = MOD_AFFINE;			//Ĭ��ת��ģ��
	iReCollect=RESAMPLING_NEAREST;	//Ĭ���ز���
	IsExcuting = FALSE;
}

CDeuRasterProjectTranDlg::~CDeuRasterProjectTranDlg()
{
}

void CDeuRasterProjectTranDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_INPUT, m_ComboInput);
	DDX_Control(pDX, IDC_COMBO_OUTPUT, m_ComboOutput);
	DDX_Control(pDX, IDC_COMBO_TRANMODEL, m_ComboTranModel);
	DDX_Control(pDX, IDC_EDIT_INPUT, m_edit_InputFile);
	DDX_Control(pDX, IDC_EDIT_OUTPUT, m_edit_OutputFile);
	DDX_Control(pDX, IDC_EDIT_COORINATE_INPUT, m_edit_InCoord);
	DDX_Control(pDX, IDC_EDIT_COORINATE_OUTPUT, m_edit_OutCoord);
	DDX_Control(pDX, IDC_COMBO_RECOLLECT, m_ComboReCollect);
	DDX_Control(pDX, IDC_COMBO_TRANSFER, m_ComboTransfer);
	DDX_Control(pDX, IDC_PROGRESS1, m_Progress);
	DDX_Control(pDX, IDC_CHK_DEM, m_chk_dem);
}

BEGIN_MESSAGE_MAP(CDeuRasterProjectTranDlg, CDialog)
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_GETMINMAXINFO()
	ON_BN_CLICKED(IDC_BTN_INPUT, &CDeuRasterProjectTranDlg::OnBnClickedBtnInput)
	ON_BN_CLICKED(IDC_BTN_OUTPUT, &CDeuRasterProjectTranDlg::OnBnClickedBtnOutput)
	ON_EN_SETFOCUS(IDC_EDIT_COORINATE_INPUT, &CDeuRasterProjectTranDlg::OnCoordinateInput)
	ON_EN_SETFOCUS(IDC_EDIT_COORINATE_OUTPUT, &CDeuRasterProjectTranDlg::OnCoordinateOutput)
	ON_CBN_SELCHANGE(IDC_COMBO_TRANMODEL, &CDeuRasterProjectTranDlg::OnCbnSelchangeComboTranmodel)
	ON_CBN_SELCHANGE(IDC_COMBO_INPUT, &CDeuRasterProjectTranDlg::OnCbnSelchangeComboInput)
	ON_CBN_SELCHANGE(IDC_COMBO_OUTPUT, &CDeuRasterProjectTranDlg::OnCbnSelchangeComboOutput)
	ON_MESSAGE(WM_PROGRESS, OnProgressStep)
	ON_MESSAGE(WM_TASK_FINISH, OnTranformFinsh)
	ON_MESSAGE(WM_TASK_FINISH_ALL, OnTranformFinshAll)
	ON_CBN_SELCHANGE(IDC_COMBO_RECOLLECT, &CDeuRasterProjectTranDlg::OnCbnSelchangeComboRecollect)
	ON_MESSAGE(WM_LOADWAIT, OnLoadWait)
	ON_BN_CLICKED(IDC_BTN_SETTING, &CDeuRasterProjectTranDlg::OnBnClickedBtnSetting)
	ON_BN_CLICKED(IDC_RADIO_resample, &CDeuRasterProjectTranDlg::OnBnClickedRadioResample)
	ON_BN_CLICKED(IDC_RADIO_transfer, &CDeuRasterProjectTranDlg::OnBnClickedRadioTransfer)
END_MESSAGE_MAP()

// CDeuRasterProjectTranDlg ���
//#ifdef _DEBUG
//void CDeuRasterProjectTranDlg::AssertValid() const
//{
//	CDialog::AssertValid();
//}
//
//#ifndef _WIN32_WCE
//void CDeuRasterProjectTranDlg::Dump(CDumpContext& dc) const
//{
//	CDialog::Dump(dc);
//}
//#endif
//#endif //_DEBUG

// CDeuRasterProjectTranDlg ��Ϣ�������
void CDeuRasterProjectTranDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	CRect rct,rctwnd, relRct;

	//�ؼ�����Ӧ
	CStatic* p_static1		  = (CStatic*)GetDlgItem(IDC_STATIC_INPUTFIELD);
	CStatic* p_static2		  = (CStatic*)GetDlgItem(IDC_STATIC_OUTPUTFIELD);
	CStatic* p_static3		  = (CStatic*)GetDlgItem(IDC_STATIC_INPUT_TYPE);
	CStatic* p_static4		  = (CStatic*)GetDlgItem(IDC_STATIC_OUTPUT_TYPE);

	CStatic* p_static7		  = (CStatic*)GetDlgItem(IDC_STATIC_OUT_RULE);
	CStatic* p_static6		  = (CStatic*)GetDlgItem(IDC_STATIC_INPUT_RULE);
	CStatic* p_staticCS		  = (CStatic*)GetDlgItem(IDC_LABEL_COODINATE_INPUT);
	//CStatic* p_static8		  = (CStatic*)GetDlgItem(IDC_STATIC88);

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
	//CStatic* p_static6		  = (CStatic*)GetDlgItem(IDC_STATIC_RECOLLECT);

	CButton* p_radio1		  =	(CButton*)GetDlgItem(IDC_RADIO_resample);
	CButton* p_radio2		  =	(CButton*)GetDlgItem(IDC_RADIO_transfer);

	CProgressCtrl* p_progress    = (CProgressCtrl*)GetDlgItem(IDC_PROGRESS1);
	CButton* p_btn_RasterSetting = (CButton*)GetDlgItem(IDC_BTN_SETTING);
	int nWidth,nHeight;	

	if(p_progress->GetSafeHwnd())
	{
		//��ǰ���ھ���
		this->GetWindowRect(&rctwnd);

		//1. ��̬�߿�
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

		//��ȡ��̬����������
		ClientToScreen(&rct); 
		int iTotalWidth = rct.Width();
		int iPerThreeWidth = iTotalWidth / 3 ;

		//�������ϵ��λ��
		CRect rcstaticCS;
		p_staticCS->GetWindowRect(&rcstaticCS);

		//����� �����ߵ���ʼλ��
		int iScaleLeft = rcstaticCS.left + iPerThreeWidth ;

		//2. �ı���
		p_edit1->GetWindowRect(&relRct);
		relRct.right = rct.right-60;
		ScreenToClient(&relRct);
		p_edit1->MoveWindow(&relRct);

		p_edit2->GetWindowRect(&relRct);
		relRct.right = rct.right-60;
		ScreenToClient(&relRct);
		p_edit2->MoveWindow(&relRct);

		//3. ��ť		
		p_btn1->GetWindowRect(&relRct);
		relRct.left = rct.right - 55;
		relRct.right = rct.right -5;
		ScreenToClient(&relRct);
		p_btn1->MoveWindow(&relRct);

		m_chk_dem.GetWindowRect(&relRct);
		nWidth = relRct.Width();
		relRct.left = rct.right - 55;
		relRct.right = relRct.left+nWidth;
		ScreenToClient(&relRct);
		m_chk_dem.MoveWindow(&relRct);

		p_btn2->GetWindowRect(&relRct);
		relRct.left = rct.right - 55;
		relRct.right = rct.right -5;
		ScreenToClient(&relRct);
		p_btn2->MoveWindow(&relRct);


		//��������������
		// rc ʵ�ʼ�¼�����ı���
		p_combox1->GetWindowRect(&relRct);
		relRct.left  = rct.right - 165;
		relRct.right = rct.right - 60;
		ScreenToClient(&relRct);
		p_combox1->MoveWindow(&relRct);

		p_static3->GetWindowRect(&relRct);
		nWidth = relRct.Width();
		relRct.left  = rct.right - nWidth - 165;
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

		//�������������
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

		//5. ������ʾ����
		p_static5->GetWindowRect(&relRct);
		nHeight = relRct.Height();
		relRct.top = nTop_offset+3;
		relRct.bottom = relRct.top+nHeight;
		ScreenToClient(&relRct);
		p_static5->MoveWindow(&relRct);

		p_radio1->GetWindowRect(&relRct);
		nHeight = relRct.Height();
		relRct.top = nTop_offset+3;
		relRct.bottom = relRct.top+nHeight;
		ScreenToClient(&relRct);
		p_radio1->MoveWindow(&relRct);

		p_radio2->GetWindowRect(&relRct);
		nHeight = relRct.Height();
		relRct.top = nTop_offset+3;
		relRct.bottom = relRct.top+nHeight;
		ScreenToClient(&relRct);
		p_radio2->MoveWindow(&relRct);

		p_combox3->GetWindowRect(&relRct);
		nHeight = relRct.Height();
		relRct.top = nTop_offset;
		relRct.bottom = relRct.top+nHeight;
		ScreenToClient(&relRct);
		p_combox3->MoveWindow(&relRct);

		m_ComboReCollect.GetWindowRect(&relRct);
		nHeight = relRct.Height();
		relRct.top = nTop_offset;
		relRct.bottom = relRct.top+nHeight;
		ScreenToClient(&relRct);
		m_ComboReCollect.MoveWindow(&relRct);

		m_ComboTransfer.GetWindowRect(&relRct);
		nHeight = relRct.Height();
		relRct.top = nTop_offset;
		relRct.bottom = relRct.top+nHeight;
		ScreenToClient(&relRct);
		m_ComboTransfer.MoveWindow(&relRct);

		p_btn_RasterSetting->GetWindowRect(&relRct);
		nHeight = relRct.Height();		
		relRct.top = nTop_offset;
		relRct.bottom = relRct.top+nHeight;
		ScreenToClient(&relRct);
		p_btn_RasterSetting->MoveWindow(&relRct);	
		
		//��������Ӧִ�а�ť
		/*p_btnEXE->GetWindowRect(&relRct);
		nWidth = relRct.Width();
		nHeight = relRct.Height();
		relRct.top = nTop_offset;
		relRct.bottom = relRct.top+nHeight;
		relRct.left = rct.right - 10 - nWidth;
		relRct.right = rct.right - 10;
		ScreenToClient(&relRct);
		p_btnEXE->MoveWindow(&relRct);*/

		/*p_static8->GetWindowRect(&relRct);
		nHeight = relRct.Height();
		relRct.top = nTop_offset+25;
		relRct.bottom = relRct.top+nHeight;
		relRct.right = rctwnd.right -10;
		ScreenToClient(&relRct);
		p_static8->MoveWindow(&relRct);*/

		p_progress->GetWindowRect(&relRct);
		nHeight = relRct.Height();
		relRct.top = nTop_offset+40;
		relRct.bottom = relRct.top+nHeight;
		relRct.right = rctwnd.right -10;
		ScreenToClient(&relRct);
		p_progress->MoveWindow(&relRct);

		//MoveWindow(&relRct);
	}
}

//int CDeuRasterProjectTranDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
//{
//	if (CDialog::OnCreate(lpCreateStruct) == -1)
//		return -1;	
//
//	
//	
//	return 0;
//}

//void CDeuRasterProjectTranDlg::OnInitialUpdate()
//{
//	CDialog::OnInitialUpdate();
//	
//	
//}

void CDeuRasterProjectTranDlg::OnDestroy()
{
	CDialog::OnDestroy();
}

BOOL CDeuRasterProjectTranDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//�����ע�ǰ�ť
	//CButton* m_btn = (CButton*)GetDlgItem(IDC_BTN_ANNOTATION);
	//m_btn->ShowWindow(SW_HIDE);

	//m_edit_InputFile.Initialize(this, BES_XT_CHOOSEFILE);
	//m_edit_InputFile.SetDlgTitle(_T("Browse"));
	//m_edit_InputFile.SetDlgFilter(_T("Shapefile(*.shp)|*.shp|λͼ(*.bmp)|*.bmp|JPEG(*.jpg)|*.jpg||"));

	//m_edit_OutputFile.Initialize(this, BES_XT_CHOOSEFILE);
	//m_edit_OutputFile.SetDlgTitle(_T("Browse"));
	//m_edit_OutputFile.SetDlgFilter(_T("Shapefile(*.shp)|*.shp|λͼ(*.bmp)|*.bmp|JPEG(*.jpg)|*.jpg||"));
	this->m_Progress.SetRange32(0, 100);
	this->m_Progress.SetTheme(xtpControlThemeOffice2000);

	m_Controlpoint_Dlg.Create(IDD_DLG_CONTROL_POINT, this);
	m_Controlpoint_Dlg.ShowWindow(SW_SHOW);
	
	//for(int n=0; n<5; n++){
	//	m_ComboInput.InsertString(n, sz_TranType_Raster[n]);
	//	m_ComboOutput.InsertString(n, sz_TranType_Raster[n]);
	//}
	InitTransFormat();

	m_ComboInput.SetCurSel(0);
	m_ComboOutput.SetCurSel(0);

	//դ��ת��ģ��
	for(int n=0; n<_TranModel_Project_num; n++)
	{
		m_ComboTranModel.InsertString(n, sz_TranModel_Project[n]);
	}
	m_ComboTranModel.SetCurSel(0);

	//�ز���
	for(int n=0; n<_TranModel_ReCollect_num; n++)
	{
		m_ComboReCollect.InsertString(n, sz_TranModel_ReCollect[n]);
	}
	m_ComboReCollect.SetCurSel(0);

	//�ز���
	for(int n=0; n<_TranModel_Transfer_num; n++)
	{
		m_ComboTransfer.InsertString(n, sz_TranModel_Transfer[n]);
	}
	m_ComboTransfer.SetCurSel(0);

	m_bSpecified = FALSE;

	((CButton*)GetDlgItem(IDC_RADIO_resample))->SetCheck(TRUE);

	OnBnClickedRadioResample();

	//���α�����
	GetDlgItem(IDC_COMBO_INPUT_RULE)->ShowWindow(false);
	GetDlgItem(IDC_COMBO_OUT_RULE)->ShowWindow(false);

	GetDlgItem(IDC_STATIC_INPUT_RULE)->ShowWindow(false);
	GetDlgItem(IDC_STATIC_OUT_RULE)->ShowWindow(false);

	m_chk_dem.ShowWindow(SW_HIDE);//DemͶӰû��ʵ�֣���դ��ͶӰ��Dem��ѡ�����ε�20170526

	UpdateData(FALSE);

	return TRUE;
}

void CDeuRasterProjectTranDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	lpMMI-> ptMaxTrackSize.x   =   600; 
	lpMMI-> ptMaxTrackSize.y   =   600; 
	lpMMI-> ptMaxPosition.x    =   0;         //XXXXX 
	lpMMI-> ptMaxPosition.y    =   0;         //XXXXX 

	CDialog::OnGetMinMaxInfo(lpMMI);
}

LRESULT CDeuRasterProjectTranDlg::OnLoadWait(WPARAM wParam, LPARAM lParam)
{
	unsigned int i = (unsigned int)lParam;

	m_Progress.SetWindowText(_T("�ϴ���..."));
	this->m_Progress.SetPos(i);

	return Default();
}

BOOL CDeuRasterProjectTranDlg::CheckControl()
{
	//CEdit* p_edit_input			= (CEdit*)GetDlgItem(IDC_EDIT_INPUT);
	//CEdit* p_edit_output		    = (CEdit*)GetDlgItem(IDC_EDIT_OUTPUT);
	//CEdit* p_edit_incoord		    = (CEdit*)GetDlgItem(IDC_EDIT_COORINATE_INPUT);
	//CEdit* p_edit_outcoord		= (CEdit*)GetDlgItem(IDC_EDIT_COORINATE_OUTPUT);
	//CComboBox* p_combox_input 	= (CComboBox*)GetDlgItem(IDC_COMBO_INPUT);
	//CComboBox* p_combox_output	= (CComboBox*)GetDlgItem(IDC_COMBO_OUTPUT);
	//CComboBox* p_combox_model  	= (CComboBox*)GetDlgItem(IDC_COMBO_TRANMODEL);

	OnCbnSelchangeComboTranmodel();

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
		AfxMessageBox("��ѡ������·����");
		return FALSE;
	}
	else if(m_strOutputFile.IsEmpty())
	{
		AfxMessageBox("���趨�����·����");
		return FALSE;
	}
	else if(m_strInCoord.IsEmpty())
	{
		AfxMessageBox("��ѡ����������ϵ��");
		return FALSE;
	}
	else if(m_strOutCoord.IsEmpty())
	{
		AfxMessageBox("���趨���������ϵ��");
		return FALSE;
	}
	else if(this->m_Controlpoint_Dlg.m_List.GetItemCount() == 0)
	{
		if(iModel == MODEL_GRID)
			return TRUE;

		if(iModel == MODEL_TRANS_ALL_GRID)
			return TRUE;

		if(iModel == MODEL_GAUSS )
			return TRUE;

		if(iModel == MODEL_TM )
			return TRUE;

		if(iModel == MODEL_UTM )
			return TRUE;

		AfxMessageBox("���趨�����Ƶ㡱");
		return FALSE;
	}

	return TRUE;

	/*p_edit_output->GetWindowText(strTmp);
	strTmp = strTmp.Trim();
	if(strTmp.IsEmpty())
	{
		AfxMessageBox("������ת���������ļ�");
	}*/
}

void CDeuRasterProjectTranDlg::OnBnClickedBtnInput()
{
	/*CDeuDlgFiles m_file;
	m_ComboInput.GetWindowText(m_file.strFileType);
	m_file.DoModal();

	m_edit_InputFile.SetWindowText(strLastPath);*/

	CString m_str = _T("");	
	m_ComboInput.GetWindowText(m_str);
	//Ԥ�����ݿ����
	//if(m_str == sz_TranType_Raster[2])
	//{		
	//	CDeuDlgOraTables m_tables(RASTER, this);
	//	//m_tables.m_tables_ay = &this->_TablesList;
	//	m_tables.DoModal();		
	//}
	//else
	//{
		CDeuDlgFiles m_file(RASTER_PROJ, this);
		if(!strLastPath.IsEmpty())
		{
			m_file.strLastPath = strLastPath;
		}

		m_file.strFileType = m_str;
		if(m_file.DoModal() == IDOK)
		{
			strLastPath = m_file.strLastPath;
			m_edit_InputFile.SetWindowText(strLastPath);

			//����դ����Ϣ�����öԻ���
			//����������
			//���ֱ���
			if(_FilsList_selected.GetCount() > 0 )
			{
				VARIANT vFormat;
				CDeuRasterTrans trans;   
				trans.FetchRasterProperty( _FilsList_selected.GetAt(0) , &vFormat )  ;

				deuRasterShapeFormat *pFormat = (deuRasterShapeFormat*)vFormat.byref;
				m_dlgRasterSetting.m_dbLeft = pFormat->dbLeft ;
				m_dlgRasterSetting.m_dbTop = pFormat->dbTop ;
				m_dlgRasterSetting.m_SizeX = pFormat->lLenght ;
				m_dlgRasterSetting.m_SizeY = pFormat->lWidth ;
				m_dlgRasterSetting.m_PixX = pFormat->dbPixX ;
				m_dlgRasterSetting.m_PixY = -pFormat->dbPixY ;
			}
		}
	//}
}

void CDeuRasterProjectTranDlg::OnBnClickedBtnOutput()
{	
	//CString m_str;
	//m_ComboOutput.GetWindowText(m_str);
	//��������ݿ�
	/*if(m_str == sz_TranType_Raster[2])
	{
		CDeuDlgOraTables m_tables(RASTER, this);
		m_tables.IsHideChkbox = TRUE;
		m_tables.DoModal();		
	}
	else
	{*/
		//alter by chenyong 2013-3-12
		/*char dir[MAX_PATH];
		AfxSelectDirDlg(dir);
		CEdit* p_edit2 = (CEdit*)GetDlgItem(IDC_EDIT_OUTPUT);
		if(strlen(dir) != 0){
			p_edit2->SetWindowText(dir);
		}*/
			
		char							dir[MAX_PATH] = {0};
		CString							strOutPutDir = _T("");
		m_edit_OutputFile.GetWindowText(strOutPutDir);

		SelectDirDlg(strOutPutDir, dir);
		if (strlen(dir) > 0)
		{
			m_edit_OutputFile.SetWindowText(dir);
		}

		UpdateData(FALSE);
	//}
}

void CDeuRasterProjectTranDlg::OnCoordinateInput()
{
	/*
	CDeuDlgDataSrc m_DataSrcDlg;
	m_DataSrcDlg.DoModal();

	CEdit* p_edit = (CEdit*)GetDlgItem(IDC_EDIT_COORINATE_INPUT);
	if(!m_DataSrcDlg.m_strSelectItem.IsEmpty())
		p_edit->SetWindowText(m_DataSrcDlg.m_strSelectItem);
        
	//���ÿ��Ƶ����������ϵ
	m_Controlpoint_Dlg.SetSrcCoorType(m_DataSrcDlg.m_strSelectItem);*/

	CString                                 strSelect;
    GetDlgItem(IDC_EDIT_COORINATE_INPUT)->GetWindowText(strSelect);

	CDeuDlgEllipManager m_DataSrcDlg;
	if (m_DataSrcDlg.DoModal() == IDOK)
	{
		CEdit* p_edit = (CEdit*)GetDlgItem(IDC_EDIT_COORINATE_INPUT);
		if(!m_DataSrcDlg.m_strEllipName.IsEmpty())
		{
			p_edit->SetWindowText(m_DataSrcDlg.m_strEllipName);
		}

		//���ÿ��Ƶ����������ϵ
		m_Controlpoint_Dlg.SetSrcCoorType(m_DataSrcDlg.m_strEllipName);
	}
}

void CDeuRasterProjectTranDlg::OnCoordinateOutput()
{
	/*
	CDeuDlgDataSrc m_DataSrcDlg;
	m_DataSrcDlg.DoModal();

	CEdit* p_edit = (CEdit*)GetDlgItem(IDC_EDIT_COORINATE_OUTPUT);
	if(!m_DataSrcDlg.m_strSelectItem.IsEmpty())
		p_edit->SetWindowText(m_DataSrcDlg.m_strSelectItem);

	//���ÿ��Ƶ���������ϵ
	m_Controlpoint_Dlg.SetDesCoorType(m_DataSrcDlg.m_strSelectItem);
	*/

	CDeuDlgEllipManager m_DataSrcDlg;

	if (m_DataSrcDlg.DoModal() == IDOK)
	{
		CEdit* p_edit = (CEdit*)GetDlgItem(IDC_EDIT_COORINATE_OUTPUT);
		if(!m_DataSrcDlg.m_strEllipName.IsEmpty())
		{
			p_edit->SetWindowText(m_DataSrcDlg.m_strEllipName);
		}

		//���ÿ��Ƶ����������ϵ
		m_Controlpoint_Dlg.SetDesCoorType(m_DataSrcDlg.m_strEllipName);
	}
}

//����ת��ģ�Ͳ���
void CDeuRasterProjectTranDlg::OnCbnSelchangeComboTranmodel()
{	
	//m_ComboReCollect.GetWindowText(m_Controlpoint_Dlg.m_strModel);
	CComboBox* p_combox3	  = (CComboBox*)GetDlgItem(IDC_COMBO_TRANMODEL);
	p_combox3->GetWindowText(m_Controlpoint_Dlg.m_strModel);

	if( m_Controlpoint_Dlg.m_strModel == "����ת��ģ���ز�����")
	{		
		iModel=MOD_AFFINE;
	}
	else if(m_Controlpoint_Dlg.m_strModel == "һ�׶���ʽת��ģ��")
	{		
		iModel=MOD_POLYNOMIAL1;
	}
	else if (m_Controlpoint_Dlg.m_strModel == "���׶���ʽת��ģ���ز�����")
	{	
		iModel=MOD_POLYNOMIAL2;
	}
	else if (m_Controlpoint_Dlg.m_strModel == "���׶���ʽת��ģ���ز�����")
	{		
		iModel=MOD_POLYNOMIAL3;
	}
	else if (m_Controlpoint_Dlg.m_strModel == "�Ľ׶���ʽת��ģ���ز�����")
	{		
		iModel=MOD_POLYNOMIAL4;
	}
	else if (m_Controlpoint_Dlg.m_strModel == "����ת��ģ��ȫͼ��ƽ�Ʒ�")
	{
		iModel=MODEL_TRANS_ALL_AFFINE;
	}
	else if (m_Controlpoint_Dlg.m_strModel == "����ת��ģ���ز�����")
	{
		iModel=MODEL_GRID;
	}
	else if(m_Controlpoint_Dlg.m_strModel == "����ת��ģ��ȫͼ��ƽ�Ʒ�")
	{
		iModel=MODEL_TRANS_ALL_GRID;
	}
	else if(m_Controlpoint_Dlg.m_strModel == "��˹ͶӰ")
	{
		iModel = MODEL_GAUSS ;
	}
	else if(m_Controlpoint_Dlg.m_strModel == "����ī����ͶӰ")
	{
		iModel = MODEL_TM ;
	}
	else if(m_Controlpoint_Dlg.m_strModel == "ͨ�ú���ī����ͶӰ")
	{
		iModel = MODEL_UTM ;
	}
}

//�������¼�
void CDeuRasterProjectTranDlg::OnCbnSelchangeComboInput()
{
	//ClearCache(FALSE);

	//CString strType;
	//m_ComboInput.GetWindowText(strType);
	//if(strType == sz_TranType_Raster[2])
	//{
	//	//����oracle
	//	CDeuDlgOracle m_dlg(RASTER, this);
	//	if(m_dlg.DoModal() == IDOK)
	//	{
	//		this->m_edit_InputFile.SetWindowText(m_dlg.strUser);
	//		strDBSid_Src  = m_dlg.strSID;
	//		strDBUser_Src = m_dlg.strUser;
	//		strDBPwd_Src  = m_dlg.strPwd;

	//		CDeuDlgOraTables m_tables(RASTER, this);
	//		m_tables.DoModal();
	//	}
	//}

	CString				strType;
	m_ComboInput.GetWindowText(strType);

	if (strType == _T("ArcSDE"))
	{
		CDeuSDEConnectProperty			conPro;
		
		//��ʼ��ArcSDE����
		CString			strRate = GetStylesPath() + _T("\\Rate.ini");
		STR_SDE_PARAM	param;

		::GetPrivateProfileString(_T("RASTERPROJSRC"), _T("SERVER"), _T(""), param.strServer.GetBuffer(MAX_PATH), MAX_PATH, (LPCTSTR)strRate);
		::GetPrivateProfileString(_T("RASTERPROJSRC"), _T("SERVICE"), _T(""), param.strService.GetBuffer(MAX_PATH), MAX_PATH, (LPCTSTR)strRate);
		::GetPrivateProfileString(_T("RASTERPROJSRC"), _T("DATABASE"), _T(""), param.strDatabase.GetBuffer(MAX_PATH), MAX_PATH, (LPCTSTR)strRate);
		::GetPrivateProfileString(_T("RASTERPROJSRC"), _T("USERNAME"), _T(""), param.strUsername.GetBuffer(MAX_PATH), MAX_PATH, (LPCTSTR)strRate);
		::GetPrivateProfileString(_T("RASTERPROJSRC"), _T("PASSWORD"), _T(""), param.strPassword.GetBuffer(MAX_PATH), MAX_PATH, (LPCTSTR)strRate);
		::GetPrivateProfileString(_T("RASTERPROJSRC"), _T("VERSION"), _T(""), param.strVersion.GetBuffer(MAX_PATH), MAX_PATH, (LPCTSTR)strRate);
		conPro.SetParam(param);

		if (conPro.DoModal() == IDOK)
		{
			m_pSrcWS = conPro.GetWorkspace();
			this->m_edit_InputFile.SetWindowText(conPro.GetConnString());

			//��ʾ����դ������
			CArcSDERaster					sdeRaster(m_pSrcWS);
			vector<STR_SDEINFO>				vecRasAll;
			sdeRaster.GetAllRasterNameAndType(vecRasAll);

			CSdeSelect						sdeSel(vecRasAll);
			//sdeSel.InitShowData(vecRasAll);
			if (sdeSel.DoModal() == IDOK)
			{
				m_vecSelect = sdeSel.GetSelectItem();				
			}

			//����������Ϣ
			param = conPro.GetParam();
			::WritePrivateProfileString(_T("RASTERPROJSRC"), _T("SERVER"), param.strServer, strRate);
			::WritePrivateProfileString(_T("RASTERPROJSRC"), _T("SERVICE"), param.strService, strRate);
			::WritePrivateProfileString(_T("RASTERPROJSRC"), _T("DATABASE"), param.strDatabase, strRate);
			::WritePrivateProfileString(_T("RASTERPROJSRC"), _T("USERNAME"), param.strUsername, strRate);
			::WritePrivateProfileString(_T("RASTERPROJSRC"), _T("PASSWORD"), param.strPassword, strRate);
			::WritePrivateProfileString(_T("RASTERPROJSRC"), _T("VERSION"), param.strVersion, strRate);
		}

		((CButton*)GetDlgItem(IDC_BTN_INPUT))->EnableWindow(FALSE);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_BTN_INPUT))->EnableWindow(TRUE);
	}
}

void CDeuRasterProjectTranDlg::OnCbnSelchangeComboOutput()
{
	//ClearCache(TRUE);

	//CString strType;
	//m_ComboOutput.GetWindowText(strType);
	//if(strType == sz_TranType_Raster[2])
	//{
	//	//����oracle
	//	CDeuDlgOracle m_dlg(RASTER, this);
	//	if(m_dlg.DoModal() == IDOK)
	//	{
	//		this->m_edit_OutputFile.SetWindowText(m_dlg.strUser);
	//		strDBSid_Dest  = m_dlg.strSID;
	//		strDBUser_Dest = m_dlg.strUser;
	//		strDBPwd_Dest  = m_dlg.strPwd;
	//	}
	//}

	CString strType;
	m_ComboOutput.GetWindowText(strType);

	if (strType == _T("ArcSDE"))
	{
		CDeuSDEConnectProperty		conPro;

		//��ʼ��ArcSDE����
		CString			strRate = GetStylesPath() + _T("\\Rate.ini");
		STR_SDE_PARAM	param;

		::GetPrivateProfileString(_T("RASTERPROJDES"), _T("SERVER"), _T(""), param.strServer.GetBuffer(MAX_PATH), MAX_PATH, (LPCTSTR)strRate);
		::GetPrivateProfileString(_T("RASTERPROJDES"), _T("SERVICE"), _T(""), param.strService.GetBuffer(MAX_PATH), MAX_PATH, (LPCTSTR)strRate);
		::GetPrivateProfileString(_T("RASTERPROJDES"), _T("DATABASE"), _T(""), param.strDatabase.GetBuffer(MAX_PATH), MAX_PATH, (LPCTSTR)strRate);
		::GetPrivateProfileString(_T("RASTERPROJDES"), _T("USERNAME"), _T(""), param.strUsername.GetBuffer(MAX_PATH), MAX_PATH, (LPCTSTR)strRate);
		::GetPrivateProfileString(_T("RASTERPROJDES"), _T("PASSWORD"), _T(""), param.strPassword.GetBuffer(MAX_PATH), MAX_PATH, (LPCTSTR)strRate);
		::GetPrivateProfileString(_T("RASTERPROJDES"), _T("VERSION"), _T(""), param.strVersion.GetBuffer(MAX_PATH), MAX_PATH, (LPCTSTR)strRate);
		conPro.SetParam(param);

		if (conPro.DoModal() == IDOK)
		{
			m_pDesWS = conPro.GetWorkspace();
			this->m_edit_OutputFile.SetWindowText(conPro.GetConnString());

			//����������Ϣ
			param = conPro.GetParam();
			::WritePrivateProfileString(_T("RASTERPROJDES"), _T("SERVER"), param.strServer, strRate);
			::WritePrivateProfileString(_T("RASTERPROJDES"), _T("SERVICE"), param.strService, strRate);
			::WritePrivateProfileString(_T("RASTERPROJDES"), _T("DATABASE"), param.strDatabase, strRate);
			::WritePrivateProfileString(_T("RASTERPROJDES"), _T("USERNAME"), param.strUsername, strRate);
			::WritePrivateProfileString(_T("RASTERPROJDES"), _T("PASSWORD"), param.strPassword, strRate);
			::WritePrivateProfileString(_T("RASTERPROJDES"), _T("VERSION"), param.strVersion, strRate);
		}

		((CButton*)GetDlgItem(IDC_BTN_OUTPUT))->EnableWindow(FALSE);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_BTN_OUTPUT))->EnableWindow(TRUE);
	}
}

//���ش��ڵĲ���
void CDeuRasterProjectTranDlg::LoadExistData(CString m_str[6])
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

void CDeuRasterProjectTranDlg::ClearCache(BOOL IsOut)
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

void CDeuRasterProjectTranDlg::TranFinish(const char* strTimeMsg)
{
	//MessageBox("ת����ϣ�", "��ʾ", MB_OK | MB_ICONINFORMATION);
}

//ת������֪ͨ��Ϣ���
void CDeuRasterProjectTranDlg::ShowStatusPanel(CString str)
{
	((CDeuGlobalMainFrame*)theApp.m_pMainWnd)->SendMessage(WM_VEC_MSGPANEL, NULL, (LPARAM)str.GetBuffer());
}

LRESULT CDeuRasterProjectTranDlg::OnProgressStep(WPARAM wParam, LPARAM lParam)
{
	unsigned int i=(unsigned int)lParam;
	LRESULT result = Default();

	CString strDescript;
	strDescript.Format("%d%%", i);
	m_Progress.SetWindowText(strDescript);
	this->m_Progress.SetPos(i);

	return result;
}

LRESULT CDeuRasterProjectTranDlg::OnTranformFinsh(WPARAM wParam, LPARAM lParam)
{	
	//CString strDescript, str;
	//m_Progress.GetWindowText(str);
	////strDescript += ;
	//
	//EndTickTime = GetTickCount();
	//double Result = (EndTickTime - StartTickTime)*0.001;
	//strDescript.Format(_T("%s%.2lf%s"), _T("ת����ϣ���ʱ:"), Result, _T("��"));
	//m_Progress.SetWindowText(str+"  "+strDescript);

	//m_Progress.Invalidate();

	//char *szTip = "������������������������������������ʸ���ļ�ת��������������������������������������\r\n";
	
	//MessageBox("ת����ϣ�", "��ʾ",MB_OK | MB_ICONINFORMATION);
	EnbleAllController();
	return 0;
}

LRESULT CDeuRasterProjectTranDlg::OnTranformFinshAll(WPARAM wParam, LPARAM lParam)
{	
	EnbleAllController();
	MessageBox("ת����ϣ�", "��ʾ",MB_OK | MB_ICONINFORMATION);

	m_Progress.SetPos(100);
	return 0;
}

//ת������������Ҫ���ݴ�����̵߳�����
void CDeuRasterProjectTranDlg::TranformOver()
{
	MessageBox("ת����ϣ�", "��ʾ",MB_OK | MB_ICONINFORMATION);

	m_Progress.SetPos(100);
	EnbleAllController();
}

void CDeuRasterProjectTranDlg::OnCbnSelchangeComboRecollect()
{
	CString m_strReCollect;
	m_ComboReCollect.GetWindowText(m_strReCollect);

	if(m_strReCollect == "���ڽ���")
	{		
		iReCollect=RESAMPLING_NEAREST;
	}
	else if(m_strReCollect == "˫�����ڲ巨")
	{		
		iReCollect=RESAMPLING_BILINEAR;
	}
	else if(m_strReCollect == "˫���ξ����")
	{	
		iReCollect=RESAMPLING_BICUBIC;
	}
}

void CDeuRasterProjectTranDlg::DisableAllController()
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

void CDeuRasterProjectTranDlg::EnbleAllController()
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

//�жϴ�������Ƿ����
BOOL CDeuRasterProjectTranDlg::CheckCoord()
{
	BOOL Input=TRUE, Output=TRUE;
	CString strInput, strOutput;
	m_edit_InCoord.GetWindowText(strInput);
	m_edit_OutCoord.GetWindowText(strOutput);

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
			if(strOutput == GeoDataMapping.ProjectedNode.pProjectedSeries.GetAt(n)._name.text)
			{
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

	if(Input && Output)
	{
		return TRUE;
	}
	else if(!Input && Output)
	{
		AfxMessageBox("��������ϵ�����ڣ��޷�ִ��ת��");
		return FALSE;
	}
	else if(Input && !Output)
	{
		AfxMessageBox("�������ϵ�����ڣ��޷�ִ��ת��");
		return FALSE;
	}
	else if(!Input || !Output)
	{
		AfxMessageBox("�����������ϵ�����ڣ��޷�ִ��ת��");
		return FALSE;
	}

	return TRUE;
}

void CDeuRasterProjectTranDlg::OnBnClickedBtnSetting()
{
	m_dlgRasterSetting.DoModal();

	m_bSpecified = m_dlgRasterSetting.m_bSpecialFrame ;

	m_dbLeft = m_dlgRasterSetting.m_dbLeft ;
	m_dbTop  = m_dlgRasterSetting.m_dbTop ; 

	m_lSizeX = m_dlgRasterSetting.m_SizeX ;
	m_lSizeY = m_dlgRasterSetting.m_SizeY ;
	m_dbPixX = m_dlgRasterSetting.m_PixX ;
	m_dbPixY = m_dlgRasterSetting.m_PixY ;

	return;
}

void CDeuRasterProjectTranDlg::OnBnClickedRadioResample()
{
	m_bResample = TRUE ;

	m_ComboReCollect.EnableWindow(TRUE);
	m_ComboTransfer.EnableWindow(FALSE);
}

void CDeuRasterProjectTranDlg::OnBnClickedRadioTransfer()
{
	m_bResample = FALSE ;	
	m_ComboReCollect.EnableWindow(FALSE);
	m_ComboTransfer.EnableWindow(TRUE);
}

int CDeuRasterProjectTranDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
	{
	   return -1;
	}

	return 0;
}

void CDeuRasterProjectTranDlg::InitTransFormat()
{
	for (int i = 0; i < GobalFormat.FormatTypeList[1]->TypeList.size(); i++)
	{
		if (GobalFormat.FormatTypeList[1]->TypeList[i].type == _T("1"))
		{
			m_ComboInput.AddString(GobalFormat.FormatTypeList[1]->TypeList[i].text);
			m_ComboOutput.AddString(GobalFormat.FormatTypeList[1]->TypeList[i].text);
		}
	}
}
