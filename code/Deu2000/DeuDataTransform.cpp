// DeuDataTransform.cpp : 实现文件
//
//  矢量窗口类

#include "stdafx.h"
#include "Deu2000.h"
#include "textprogressctrl.h"
#include "DeuDataTransform.h"
#include "DeuDataSource.h"
#include "DeuDataPaths.h"
#include "DeuTask.h"
#include "DeuFunction.h"
#include "DLGDBConnect.h"
#include "Deu2000Task.h"
#include "MainFrm.h"
#include "DeuDialog.h"

// CDeuDataTransform 对话框



IMPLEMENT_DYNAMIC(CDeuDataTransform, CDeuDialog)

CDeuDataTransform::CDeuDataTransform()
: CDeuDialog() //CDeuDataTransform::IDD
, m_in_FileName(_T(""))
, m_in_Type(_T(""))
, m_out_PathName(_T(""))
, m_in_System(_T(""))
, m_out_System(_T(""))
, m_dx(0)
, m_dy(0)
, m_dz(0)
, m_rx(0)
, m_ry(0)
, m_rz(0)
, m_m(0)
, m_bRunning(FALSE)
, m_in_band(_T(""))
, m_out_band(_T(""))
, m_cp_x1(_T(""))
, m_cp_y1(_T(""))
, m_cp_z1(_T(""))
, m_cp_x2(_T(""))
, m_cp_y2(_T(""))
, m_cp_z2(_T(""))
, m_model(_T(""))
{
	m_param = NULL;

	m_deuTask = new CDeuTask;

	m_deuTask->type = VECTOR_TRANS;

	g_lisTask->push_back(m_deuTask);

	//m_PageType = PAGE_VECTOR;

	this->nWndType = 2;

	/* 记录在容器中的索引位置，方便找准对象并释放 该参数只在栅格和矢量 中使用*/
	OrderIndex = 0;

}

void  CDeuDataTransform::SetDeuTask(CDeuTask * pTask)
{
	if(m_deuTask != NULL)
	{
		g_lisTask->remove(m_deuTask);

		delete(m_deuTask);
	}


	LIST_IT(CDeuTask *) ret= std::find(g_lisTask->begin(),g_lisTask->end(),pTask);
	if( *ret == NULL)
	{
		g_lisTask->push_back(pTask);
	}
	m_deuTask = pTask;
}

CDeuTask * CDeuDataTransform::GetDeuTask()
{
	return m_deuTask;
}

//CDeuDataTransform::CDeuDataTransform(UINT nIDCaption)
//	: CBCGPPropertyPage(CDeuDataTransform::IDD,nIDCaption)
//{
//	m_strCaption = L"123";
//	
//	m_param = new double[7];
//
//	pTask = new CDeuTask;
//}

CDeuDataTransform::~CDeuDataTransform()
{
	delete[] m_param;
}

void CDeuDataTransform::SetCaption(CString strCaption)
{
	//m_strCaption = strCaption;
}

void CDeuDataTransform::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IN_TYPE, m_Combo_in_type);
	DDX_Control(pDX, IDC_OUT_TYPE, m_Combo_out_type);

	//DDX_Control(pDX, IDC_COORTYPE, m_in_coordtype_Combo);
	//DDX_Control(pDX, IDC_COORTYPE1, m_out_coordtype_Combo);
	//DDX_Control(pDX, IDC_TYD, m_in_band_combo);
	//DDX_Control(pDX, IDC_TYD1, m_out_band_combo);
	//DDX_Control(pDX, IDC_COORTYPE2, m_CtrlPt_coordtype_Combo);

	DDX_Control(pDX, IDC_STATIC_X, m_static_7p_x);
	DDX_Control(pDX, IDC_STATIC_X1, m_static_7p_x2);
	DDX_Control(pDX, IDC_STATIC_Y, m_static_7p_y);
	DDX_Control(pDX, IDC_STATIC_Y2, m_static_7p_y2);
	DDX_Control(pDX, IDC_STATIC_Z1, m_static_7p_z);
	DDX_Control(pDX, IDC_STATIC_Z2, m_static_7p_z2);
	DDX_Text(pDX, IDC_EDIT_DATA, m_in_FileName);

	DDX_Control(pDX,IDC_EDIT_DATA,m_in_FileName_ed);
	DDX_Control(pDX,IDC_EDIT_DATA2,m_out_FileName_ed);

	DDX_CBString(pDX, IDC_IN_TYPE, m_in_Type);
	DDX_CBString(pDX,IDC_OUT_TYPE, m_out_Type);
	DDX_Text(pDX, IDC_EDIT_DATA2, m_out_PathName);

	DDX_CBString(pDX, IDC_CS_SRC, m_in_System);
	DDX_Control(pDX, IDC_CS_SRC, m_in_System_CB);
	DDX_Control(pDX, IDC_CS_DES, m_out_System_CB);
	DDX_CBString(pDX, IDC_CS_DES, m_out_System);
	
	DDX_CBString(pDX, IDC_CS_SRC_CP, m_in_System_cp);
	DDX_Control(pDX, IDC_CS_SRC_CP, m_in_System_CB_cp);
	DDX_Control(pDX, IDC_CS_DES_CP, m_out_System_CB_cp);
	DDX_CBString(pDX, IDC_CS_DES_CP, m_out_System_cp);

	//DDX_Control(pDX, IDC_EDIT1, m_7p_dx_ed);
	//DDX_Control(pDX, IDC_EDIT2, m_7p_dy_ed);
	//DDX_Control(pDX, IDC_EDIT3, m_7p_dz_ed);
	//DDX_Control(pDX, IDC_EDIT4, m_7p_rx_ed);
	//DDX_Control(pDX, IDC_EDIT5, m_7p_ry_ed);
	//DDX_Control(pDX, IDC_EDIT6, m_7p_rz_ed);
	//DDX_Control(pDX, IDC_EDIT13, m_7p_m_ed);

	DDX_Control(pDX, IDC_CP_ADDPT, m_btn_7p_addpt);
	DDX_Control(pDX, IDC_CP_DELPT, m_btn_7p_delpt);
	DDX_Control(pDX, IDC_CP_ADDFILE, m_btn_7p_addfile);
	DDX_Control(pDX, IDC_CP_DELALLPT, m_btn_7p_delall);
	//DDX_Text(pDX, IDC_EDIT1, m_dx);
	//DDX_Text(pDX, IDC_EDIT2, m_dy);
	//DDX_Text(pDX, IDC_EDIT3, m_dz);
	//DDX_Text(pDX, IDC_EDIT4, m_rx);
	//DDX_Text(pDX, IDC_EDIT5, m_ry);
	//DDX_Text(pDX, IDC_EDIT6, m_rz);
	//DDX_Text(pDX, IDC_EDIT13, m_m);

	DDX_Control(pDX, IDC_BTN_VIEW2, m_btn_view2);
	DDX_Control(pDX, IDC_PROGRESS1, m_Progress);

	DDX_Text(pDX, IDC_EDIT7, m_cp_x1);
	DDX_Text(pDX, IDC_EDIT8, m_cp_y1);
	DDX_Text(pDX, IDC_EDIT9, m_cp_z1);
	DDX_Text(pDX, IDC_EDIT10, m_cp_x2);
	DDX_Text(pDX, IDC_EDIT11, m_cp_y2);
	DDX_Text(pDX, IDC_EDIT12, m_cp_z2);
	DDX_Control(pDX, IDC_EDIT7, m_cp_x1_ed);
	DDX_Control(pDX, IDC_EDIT8, m_cp_y1_ed);
	DDX_Control(pDX, IDC_EDIT9, m_cp_z1_ed);
	DDX_Control(pDX, IDC_EDIT10, m_cp_x2_ed);
	DDX_Control(pDX, IDC_EDIT11, m_cp_y2_ed);
	DDX_Control(pDX, IDC_EDIT12, m_cp_z2_ed);
	DDX_Control(pDX, IDC_CP_MDF, m_btn_7p_modf);
	DDX_Control(pDX, IDC_CP_SAV, m_btn_7p_save);

	DDX_Control(pDX, IDC_COMBOMODEL,m_cb_model);
	DDX_CBString(pDX, IDC_COMBOMODEL, m_model);
}


BEGIN_MESSAGE_MAP(CDeuDataTransform, CDeuDialog)
	ON_BN_CLICKED(IDC_BUT_VIEW, &CDeuDataTransform::OnBnClickedButView)
	//ON_CBN_SELCHANGE(IDC_CS_SRC, &CDeuDataTransform::OnCbnSelchangeCoordinates)
	//ON_CBN_DBLCLK(IDC_CS_SRC, &CDeuDataTransform::OnCbnDblclkCoordinates)
	ON_CBN_DROPDOWN(IDC_CS_SRC, &CDeuDataTransform::OnCbnDropdownCoordinates)
	ON_CBN_DROPDOWN(IDC_CS_DES, &CDeuDataTransform::OnCbnDropdownComType6)

	ON_CBN_DROPDOWN(IDC_CS_SRC_CP, &CDeuDataTransform::OnCbnDropdownCS_SRC_CP)
	ON_CBN_DROPDOWN(IDC_CS_DES_CP, &CDeuDataTransform::OnCbnDropdownCS_DES_CP)


	ON_BN_CLICKED(IDC_BTN_VIEW2, &CDeuDataTransform::OnBnClickedButView2)
	ON_CBN_SELCHANGE(IDC_COORTYPE2, &CDeuDataTransform::OnCbnSelchangeCoortype2)
	ON_BN_CLICKED(IDC_BUTTON12, &CDeuDataTransform::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_RADIO1, &CDeuDataTransform::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CDeuDataTransform::OnBnClickedRadio2)


	ON_CBN_SELCHANGE(IDC_COORTYPE, &CDeuDataTransform::OnCbnSelchangeCoortype)
	ON_CBN_SELCHANGE(IDC_COORTYPE1, &CDeuDataTransform::OnCbnSelchangeCoortype1)
	ON_CBN_SELCHANGE(IDC_IN_TYPE, &CDeuDataTransform::OnCbnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_OUT_TYPE, &CDeuDataTransform::OnCbnSelchangeCBTypeOut)

	//////////////////////////////////////////////////////////////////////////
	ON_MESSAGE(WM_TASK_FINISH, OnTaskFinished)
	ON_MESSAGE(WM_PROGRESS, OnProgress)

	ON_CBN_SELCHANGE(IDC_TYD, &CDeuDataTransform::OnCbnSelchangeTyd)
	ON_CBN_SELCHANGE(IDC_TYD1, &CDeuDataTransform::OnCbnSelchangeTyd1)
	ON_EN_CHANGE(IDC_EDIT_DATA, &CDeuDataTransform::OnEnChangeEditData)

	//////////////////////////////////////////////////////////////////////////
	ON_BN_CLICKED(IDC_CP_ADDFILE, &CDeuDataTransform::OnBnClicked_cp_addfile)
	ON_BN_CLICKED(IDC_CP_ADDPT, &CDeuDataTransform::OnBnClicked_cp_addpt)
	ON_BN_CLICKED(IDC_CP_DELPT, &CDeuDataTransform::OnBnClicked_cp_delpt)
	ON_BN_CLICKED(IDC_CP_DELALLPT, &CDeuDataTransform::OnBnClicked_cp_delallpt)



	ON_BN_CLICKED(IDC_CP_MDF, &CDeuDataTransform::OnBnClickedCpMdf)
	ON_BN_CLICKED(IDC_CP_SAV, &CDeuDataTransform::OnBnClickedCpSav)

	ON_CBN_SELCHANGE(IDC_COMBOMODEL, &CDeuDataTransform::OnCbnSelchangeModel)

	//ON_CBN_SELCHANGE(IDC_CS_DES, &CDeuDataTransform::OnCbnSelchangeComType6)

END_MESSAGE_MAP()


// CDeuDataTransform 消息处理程序

LRESULT CDeuDataTransform::OnProgress(WPARAM, LPARAM _param)
{
	unsigned int i=(unsigned int)_param;
	LRESULT result = Default();

	m_Progress.SetPos(i);

	return result;
}

LRESULT CDeuDataTransform::OnTaskFinished(WPARAM, LPARAM)
{
	m_bRunning = FALSE;
	return Default();
}


void CDeuDataTransform::OnBnClickedButView()
{
	//输入文件按钮

	//////////////////////////////////////////////////////////////////////////
	//调出浏览对话框找到文件的路径
	//////////////////////////////////////////////////////////////////////////
	CDeuDataPaths DataPaths;
	m_Combo_in_type.GetWindowText(m_in_Type);
	DataPaths.m_Type = m_in_Type;

	CString strFilter;
	if( m_in_Type.Compare("ESRI Shapefile")==0)
	{		
		strFilter = "ESRI Shapefile (*.shp)|*.shp||";
	}
	else if(m_in_Type.Compare("MapInfo File")==0)
	{		
		strFilter = "MapInfo File(*.mif)|*.mif|MapInfo File(*.tab)|*.tab||";
	}
	else if (m_in_Type.Compare("DXF")==0)
	{	
		strFilter = "DXF(*.dxf)|*.dxf|DWG(*.dwg)|*.dwg||";
	}
	else if (m_in_Type.Compare("AVCE00")==0)
	{		
		strFilter = "AVCE00(*.e00)|*.e00||";
	}

	DataPaths.m_strFilter = strFilter;//"ESRI Shapefile (*.shp)|*.shp|DXF(*.dxf)|*.dxf|DWG(*.dwg)|*.dwg|MapInfo File(*.mif)|*.mif|MapInfo File(*.tab)|*.tab|AVCE00(*.e00)|*.e00|All Files (*.*)|*.*||";
	DataPaths.m_Path = m_in_FileName;
	DataPaths.m_vecOnlyFileName.assign(m_deuTask->TableList.begin(),m_deuTask->TableList.end());
	//DataPaths.pts = FilePath;
	DataPaths.DoModal();

	if (DataPaths.m_bInvalid == TRUE)
		return ;	

	m_in_FileName = DataPaths.m_Path;

	//CDeuData *pDeuData = DEUMAINFRM.m_deuData;
	//VEC(CDeuTask*) &vecTask = pDeuData->vecTask;

	/*
	CString strCaption;	
	strCaption=this->GetPSP().pszTitle;
	*/

	//CDeuTask *CurTask = NULL;
	//VEC(CDeuTask*)::iterator it;
	//for (it = vecTask.begin();it != vecTask.end(); it++)
	//{
	//	int ret = (*it)->TaskName.Compare(strCaption) ;
	//	
	//	if (ret == 0)
	//	{
	//		CurTask = *it;
	//		break;
	//	}
	//}
	CDeuTask *CurTask = m_deuTask;

	CurTask->PathName = DataPaths.m_Dir;
	CurTask->TableList.assign(DataPaths.m_vecOnlyFileName.begin(),DataPaths.m_vecOnlyFileName.end())  ;


	m_in_FileName_ed.SetReadOnly(TRUE);

	UpdateData(FALSE);


#if 0 
	std::vector<CString> FilePath;//在浏览时将单个或者多个文件的路径存入FilePath数组中去

	//////////////////////////////////////////////////////////////////////////
	//假设存入一下CString值，代表路径
	FilePath.push_back(_T("D\\ABC"));
	FilePath.push_back(_T("f\\ABC"));
	FilePath.push_back(_T("G\\ABC"));
	FilePath.push_back(_T("K\\ABC"));

	CString totalParh = _T("");

	int v_size = FilePath.size();

	if (v_size < 2)
	{
		totalParh = FilePath.at(0)+_T(";");

		((CEdit*)GetDlgItem(IDC_EDIT_DATA))->SetWindowText(totalParh);
		UpdateData(FALSE);
	}

	else
	{
		((CEdit*)GetDlgItem(IDC_EDIT_DATA))->EnableWindow(FALSE);
		CDeuDataPaths DataPaths;
		DataPaths.pts.clear();
		DataPaths.pts = FilePath;
		DataPaths.DoModal();
	}
#endif
}

BOOL CDeuDataTransform::OnInitDialog(void)
{
	CDialog::OnInitDialog();

	//m_Combo_in_type.ResetContent();
	m_Combo_in_type.AddString("ESRI Shapefile");
	m_Combo_in_type.AddString("MapInfo File");
	m_Combo_in_type.AddString("DXF");
	m_Combo_in_type.AddString("AVCE00");
	m_Combo_in_type.AddString("Oracle");
	m_Combo_in_type.SetCurSel(0);

	//m_Combo_out_type.ResetContent();
	m_Combo_out_type.AddString("ESRI Shapefile");
	m_Combo_out_type.AddString("MapInfo File");
	m_Combo_out_type.AddString("DXF");
	m_Combo_out_type.AddString("AVCE00");
	m_Combo_out_type.AddString("Oracle");
	m_Combo_out_type.SetCurSel(0);



	m_cb_model.AddString("布尔莎转换模型");
	m_cb_model.AddString("二维七参数转换模型");
	m_cb_model.AddString("三维七参数转换模型");
	m_cb_model.AddString("平面四参数转换模型");
	m_cb_model.SetCurSel(0);





	//////////////////////////////////////////////////////////////////////////

	RECT rectGrid;
	CWnd* wnd = GetDlgItem(IDC_STATIC_GRID);
	if(wnd != NULL)
	{
		wnd->GetWindowRect(&rectGrid);
		ScreenToClient(&rectGrid);

		if(!m_Grid.Create(WS_CHILD | WS_BORDER | WS_TABSTOP | WS_VISIBLE, rectGrid, this, 1))
		{
			ASSERT (FALSE);
			return -1;
		}
	}

	m_Grid.InsertColumn(0, _T("源X"), 100);
	m_Grid.InsertColumn(1, _T("源Y"), 100);
	m_Grid.InsertColumn(2, _T("源Z"), 100);
	m_Grid.InsertColumn(3, _T("目标X"), 100);
	m_Grid.InsertColumn(4, _T("目标Y"), 100);
	m_Grid.InsertColumn(5, _T("目标Z"), 100);
	m_Grid.InsertColumn(6, _T("残差X"), 100);
	m_Grid.InsertColumn(7, _T("残差Y"), 100);
	m_Grid.InsertColumn(8, _T("残差Z"), 100);
	m_Grid.InsertColumn(9, _T("残差"), 100);


	m_Grid.SetWholeRowSel (FALSE);
	m_Grid.EnableMarkSortedColumn (FALSE);
	m_Grid.EnableHeader (TRUE, 0);
	DWORD gridStyle=m_Grid.GetExStyle();
	gridStyle = LVS_EX_CHECKBOXES;


	m_Grid.AdjustLayout();

	//////////////////////////////////////////////////////////////////////////
	//Initialize by DeuTask
	m_in_FileName_ed.SetWindowText(m_deuTask->PathName);
	m_out_FileName_ed.SetWindowText(m_deuTask->out_PathName);

	//m_Combo_in_type.SetWindowText(m_deuTask->Driver);
	//m_Combo_out_type.SetWindowText(m_deuTask->out_Driver);

	//m_in_System_CB.SetWindowText(L"123");

	//////////////////////////////////////////////////////////////////////////
	int ret = m_deuTask->Driver.Compare("ESRI Shapefile");
	if( ret == 0)
	{
		m_Combo_in_type.SetCurSel(0);
	}

	ret = m_deuTask->Driver.Compare("MapInfo File");
	if( ret == 0)
	{
		m_Combo_in_type.SetCurSel(1);
	}
	ret = m_deuTask->Driver.Compare("DXF");
	if( ret == 0)
	{
		m_Combo_in_type.SetCurSel(2);
	}
	ret = m_deuTask->Driver.Compare("AVCE00");
	if( ret == 0)
	{
		m_Combo_in_type.SetCurSel(3);
	}
	ret = m_deuTask->Driver.Compare("Oracle");
	if( ret == 0)
	{
		m_Combo_in_type.SetCurSel(4);
	}


	//////////////////////////////////////////////////////////////////////////
	ret = m_deuTask->out_Driver.Compare("ESRI Shapefile");
	if( ret == 0)
	{
		m_Combo_in_type.SetCurSel(0);
	}

	ret = m_deuTask->out_Driver.Compare("MapInfo File");
	if( ret == 0)
	{
		m_Combo_in_type.SetCurSel(1);
	}
	ret = m_deuTask->out_Driver.Compare("DXF");
	if( ret == 0)
	{
		m_Combo_in_type.SetCurSel(2);
	}
	ret = m_deuTask->out_Driver.Compare("AVCE00");
	if( ret == 0)
	{
		m_Combo_in_type.SetCurSel(3);
	}
	ret = m_deuTask->out_Driver.Compare("Oracle");
	if( ret == 0)
	{
		m_Combo_in_type.SetCurSel(4);
	}


	//////////////////////////////////////////////////////////////////////////

	m_in_System_CB.ResetContent();
	m_in_System_CB.AddString(m_deuTask->SrcEllip);
	m_in_System_CB.SetCurSel(0);


	m_out_System_CB.ResetContent();
	m_out_System_CB.AddString(m_deuTask->DestEllip);
	m_out_System_CB.SetCurSel(0);

	//////////////////////////////////////////////////////////////////////////\






	//////////////////////////////////////////////////////////////////////////



	//////////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////////
	UpdateData(TRUE);
	return TRUE;
}

void CDeuDataTransform::OnCbnSelchangeCoordinates()
{
	// TODO: 在此添加控件通知处理程序代码
	CDeuDataSource Dataco;
	Dataco.DoModal();

}

void CDeuDataTransform::OnCbnDblclkCoordinates()
{
	// TODO: 在此添加控件通知处理程序代码
	CDeuDataSource Dataco;
	Dataco.DoModal();
}

void CDeuDataTransform::OnCbnDropdownCS_SRC_CP()
{
	//当CB下拉时，选择坐标系
	CDeuDataSource dlg;
	CDeuData *pDeuData = DEUMAINFRM.m_deuData;
	dlg.put_Ellip(pDeuData->m_Deu_ellipse);
	dlg.DoModal();

	CNode* node= dlg.m_Sel_Ellip;
	if (!node)
	{
		return;
	}
	m_in_System_cp=(getListItem(node->_sub_nodes,0)->data);


	m_in_System_CB_cp.ResetContent();
	m_in_System_CB_cp.AddString(m_in_System_cp);

	/*m_in_system_combo.ShowDropDown(FALSE);*/
	UpdateData(FALSE);
	
}

void CDeuDataTransform::OnCbnDropdownCS_DES_CP()
{
	//当CB下拉时，选择坐标系
	CDeuDataSource dlg;
	CDeuData *pDeuData = DEUMAINFRM.m_deuData;
	dlg.put_Ellip(pDeuData->m_Deu_ellipse);
	dlg.DoModal();

	CNode* node= dlg.m_Sel_Ellip;
	if (!node)
	{
		return;
	}
	m_out_System_cp=(getListItem(node->_sub_nodes,0)->data);


	m_out_System_CB_cp.ResetContent();
	m_out_System_CB_cp.AddString(m_out_System_cp);

	/*m_in_system_combo.ShowDropDown(FALSE);*/
	UpdateData(FALSE);

}

void CDeuDataTransform::OnCbnDropdownCoordinates()
{
	//当CB下拉时，选择坐标系
	CDeuDataSource dlg;
	CDeuData *pDeuData = DEUMAINFRM.m_deuData;
	dlg.put_Ellip(pDeuData->m_Deu_ellipse);
	dlg.DoModal();

	CNode* node= dlg.m_Sel_Ellip;
	if (!node)
	{
		return;
	}
	m_in_System=(getListItem(node->_sub_nodes,0)->data);


	m_in_System_CB.ResetContent();
	m_in_System_CB.AddString(m_in_System);

	/*m_in_system_combo.ShowDropDown(FALSE);*/
	UpdateData(FALSE);
}

void CDeuDataTransform::OnCbnDropdownComType6()
{
	// TODO: 在此添加控件通知处理程序代码
	CDeuDataSource dlg;
	CDeuData *pDeuData = DEUMAINFRM.m_deuData;
	dlg.put_Ellip(pDeuData->m_Deu_des_ellipse);
	dlg.DoModal();

	CNode* node= dlg.m_Sel_Ellip;
	if (!node)
	{
		return;
	}
	m_out_System=(getListItem(node->_sub_nodes,0)->data);


	m_out_System_CB.ResetContent();
	m_out_System_CB.AddString(m_out_System);

	/*m_in_system_combo.ShowDropDown(FALSE);*/
	UpdateData(FALSE);
}

void CDeuDataTransform::OnBnClickedButView2()
{
	//输出文件按钮
	BOOL bFinished = FALSE;

	m_btn_view2.EnableWindow(FALSE);

	m_Combo_out_type.GetWindowText(m_out_Type);

	int ret=m_out_Type.Compare("Oracle");
	if( m_out_Type.Compare("ESRI Shapefile")==0 || m_out_Type.Compare("MapInfo File")==0 || m_out_Type.Compare("DXF")==0 || m_out_Type.Compare("AVCE00")==0)
	{

		char dir[256];
		AfxSelectDirDlg(dir);

		CString strFileName;
		strFileName.Format(_T("%s"),dir);
		m_out_PathName=strFileName;
		UpdateData(FALSE);

		//Doc
		//doc->m_out_filename=m_out_filename;//文件夹路径
	}
	else if(m_out_Type.Compare("Oracle")==0)
	{
		DLGDBConnect dlg_conn;
		dlg_conn.DoModal();
		//doc->m_out_conn_string=dlg_conn._conn_string;
		m_out_FileName_ed.SetWindowText(dlg_conn.m_ConnString);

		m_out_PathName = dlg_conn.m_ConnString;
	}

	m_btn_view2.EnableWindow(TRUE);

	bFinished = TRUE;
}

void CDeuDataTransform::OnCbnSelchangeCoortype2()
{
	// TODO: 在此添加控件通知处理程序代码
	int count=m_CtrlPt_coordtype_Combo.GetCurSel();

	CString m_coordtype = _T("");

	m_CtrlPt_coordtype_Combo.GetLBText(count,m_coordtype);

	if("大地" == m_coordtype)
	{

		m_CtrlPt_CoordType = GEODETIC;

		m_static_7p_x.SetWindowText("B");
		m_static_7p_x2.SetWindowText("B");
		m_static_7p_y.SetWindowText("L");
		m_static_7p_y2.SetWindowText("L");
		m_static_7p_z.SetWindowText("H");
		m_static_7p_z2.SetWindowText("H");

	}

	if("平面" == m_coordtype)
	{
		m_CtrlPt_CoordType = PLANE;

		m_static_7p_x.SetWindowText("x");
		m_static_7p_x2.SetWindowText("x");
		m_static_7p_y.SetWindowText("y");
		m_static_7p_y2.SetWindowText("y");
		m_static_7p_z.SetWindowText("H");
		m_static_7p_z2.SetWindowText("H");
	}

	if("空间直角" == m_coordtype)
	{
		m_CtrlPt_CoordType = GEOCENTRIC;

		m_static_7p_x.SetWindowText("X");
		m_static_7p_x2.SetWindowText("X");
		m_static_7p_y.SetWindowText("Y");
		m_static_7p_y2.SetWindowText("Y");
		m_static_7p_z.SetWindowText("Z");
		m_static_7p_z2.SetWindowText("Z");
	}
}

void CDeuDataTransform::OnBnClickedButton12()
{
	//执行~！

	if(m_bRunning == TRUE)
		return;

	if( m_out_PathName.Compare("") == 0)
	{
		AfxMessageBox("输出路径不能为空。",MB_OK | MB_ICONINFORMATION);
		return ; 
	}

	if( m_in_FileName.Compare("") == 0)
	{
		AfxMessageBox("输入路径不能为空。",MB_OK | MB_ICONINFORMATION);
		return ;
	}


	if(m_deuTask->TaskStatus.Compare( FINISHED ) == 0)
	{/////////////////////////////////////////wang///////////////////////////////////
		int ret = MessageBox("上次转换已经完成！确定要再次转换？","询问",MB_YESNO | MB_ICONQUESTION);

		if( ret == IDYES )	
		{
			m_deuTask->TaskStatus = BEFOREBEGIN;
		}
		else if(ret == IDNO)
		{
			m_bRunning = FALSE;
			return ;
		}
	}

	if(m_deuTask->TaskStatus.Compare( RUNNING ) == 0)
	{
		int ret = MessageBox("上次转换没有完成！是-断点续转；否-重新转换。","询问",MB_YESNO | MB_ICONQUESTION);

		if( ret == IDNO )	
		{
			m_deuTask->TaskStatus = BEFOREBEGIN;
		}
	}


	UpdateData();

	//获得所有数据和参数
	CDeuData *pdeuData = DEUMAINFRM.m_deuData;

	m_deuTask->hWnd = (LONGLONG)this->m_hWnd;

	//CString TaskName;	
	//TaskName=GetPSP().pszTitle;

	//m_deuTask->TaskName = TaskName;


	//ellipse
	m_deuTask->SrcEllip = m_in_System;
	m_deuTask->DestEllip = m_out_System;

	//in,out filename
	//m_deuTask->TableList.clear();

	//m_deuTask->PathName = m_in_FileName;
	m_deuTask->out_PathName = m_out_PathName;
	int retFind = m_in_FileName.Find(".") ;
	if ( retFind > 0)
	{
		retFind = m_in_FileName.ReverseFind('\\') ;
		m_deuTask->PathName = m_in_FileName.Left(retFind);
	}
	else
	{
		m_deuTask->PathName = m_in_FileName;
	}



	//CentrLong

	m_deuTask->InCentr_long  = g_Task2000->get_PrimeMeridian(m_in_System);
	m_deuTask->OutCentr_long = g_Task2000->get_PrimeMeridian(m_out_System);

	//获得驱动
	//doc->m_in_driver= m_in_type;
	//doc->m_out_driver= m_out_type;

	//////////////////////////////////////////////////////////////////////////

	if( m_in_Type.Compare("ESRI Shapefile")==0)
	{		
		m_deuTask->Driver="ESRI Shapefile";
	}
	else if(m_in_Type.Compare("MapInfo File")==0)
	{		
		m_deuTask->Driver="MapInfo File";
	}
	else if (m_in_Type.Compare("DXF")==0)
	{	
		m_deuTask->Driver="DXF";
	}
	else if (m_in_Type.Compare("AVCE00")==0)
	{		
		m_deuTask->Driver="AVCE00";
	}
	else if(m_in_Type.Compare("Oracle")==0)
	{	
		m_deuTask->Driver="OCI";
	}
	//////////////////////////////////////////////////////////////////////////
	if( m_out_Type.Compare("ESRI Shapefile")==0)
	{		
		m_deuTask->out_Driver="ESRI Shapefile";
	}
	else if(m_out_Type.Compare("MapInfo File")==0)
	{		
		m_deuTask->out_Driver="MapInfo File";
	}
	else if (m_out_Type.Compare("DXF")==0)
	{	
		m_deuTask->out_Driver="DXF";
	}
	else if (m_out_Type.Compare("AVCE00")==0)
	{		
		m_deuTask->out_Driver="AVCE00";
	}
	else if(m_out_Type.Compare("Oracle")==0)
	{	
		m_deuTask->out_Driver="OCI";
	}


	//////////////////////////////////////////////////////////////////////////
	//model
	//#define MODEL_D3P7	1
	//#define MODEL_D2P4	2
	//#define MODEL_BURSA	3
	//#define MODEL_D2P7	4
	
		if( m_model.Compare("布尔莎转换模型")==0)
		{		
			m_deuTask->iModel=MODEL_BURSA;
		}
		else if(m_model.Compare("二维七参数转换模型")==0)
		{		
			m_deuTask->iModel=MODEL_D2P7;
		}
		else if (m_model.Compare("三维七参数转换模型")==0)
		{	
			m_deuTask->iModel=MODEL_D3P7;
		}
		else if (m_model.Compare("平面四参数转换模型")==0)
		{		
			m_deuTask->iModel=MODEL_D2P4;
		}


	//////////////////////////////////////////////////////////////////////////

	m_deuTask->Param = m_param;
	
	m_deuTask->nPara = m_npara;






#if 1
	//m_DY_units

	m_in_UnitType = m_in_CoordType ;

	m_out_UnitType =  m_out_CoordType;

	m_deuTask->InCoordType = g_Task2000->get_CoordType(m_in_System);
	m_deuTask->OutCoordType = g_Task2000->get_CoordType(m_out_System); 

#endif	

	//加载空间参考	
	g_Task2000->LoadSRS();


	//向COM组件注册窗口句柄

	g_Task2000->Task_RegisterWnd(this->m_hWnd);



	//调用转换模块	

	//_task.Task_RasterTransForm();

	m_bRunning = g_Task2000->Task_TransForm(m_deuTask);

	//////////////////////////////////////////////////////////////////////////
	//写转换任务描述文件	
	//m_deuTask->_7param
	g_Task2000->UpdateTaskList(g_lisTask);
	//////////////////////////////////////////////////////////////////////////
}

void CDeuDataTransform::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	//可用
	m_7p_dx_ed.SetReadOnly(FALSE);
	m_7p_dy_ed.SetReadOnly(FALSE);
	m_7p_dz_ed.SetReadOnly(FALSE);
	m_7p_rx_ed.SetReadOnly(FALSE);
	m_7p_ry_ed.SetReadOnly(FALSE);
	m_7p_rz_ed.SetReadOnly(FALSE);
	m_7p_m_ed.SetReadOnly(FALSE);

	//不可用
	m_btn_7p_addpt.EnableWindow(FALSE);
	m_btn_7p_delpt.EnableWindow(FALSE);
	m_btn_7p_addfile.EnableWindow(FALSE);
	m_btn_7p_delall.EnableWindow(FALSE);
}

void CDeuDataTransform::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
	//不可用
	m_7p_dx_ed.SetReadOnly(TRUE);
	m_7p_dy_ed.SetReadOnly(TRUE);
	m_7p_dz_ed.SetReadOnly(TRUE);
	m_7p_rx_ed.SetReadOnly(TRUE);
	m_7p_ry_ed.SetReadOnly(TRUE);
	m_7p_rz_ed.SetReadOnly(TRUE);
	m_7p_m_ed.SetReadOnly(TRUE);

	//可用
	m_btn_7p_addpt.EnableWindow(TRUE);
	m_btn_7p_delpt.EnableWindow(TRUE);
	m_btn_7p_addfile.EnableWindow(TRUE);
	m_btn_7p_delall.EnableWindow(TRUE);
	m_btn_7p_modf.EnableWindow(TRUE);
	m_btn_7p_save.EnableWindow(TRUE);
}

void CDeuDataTransform::OnBnClicked_cp_addpt()
{

	m_cp_x1_ed.GetWindowText(m_cp_x1);
	m_cp_y1_ed.GetWindowText(m_cp_y1);
	m_cp_z1_ed.GetWindowText(m_cp_z1);
	m_cp_x2_ed.GetWindowText(m_cp_x2);
	m_cp_y2_ed.GetWindowText(m_cp_y2);
	m_cp_z2_ed.GetWindowText(m_cp_z2);

	AddOneCtrlPt(m_cp_x1,\
		m_cp_y1,\
		m_cp_z1,\
		m_cp_x2,\
		m_cp_y2,\
		m_cp_z2);

	//////////////////////////////////////////////////////////////////////////
	//
	int _row_count=m_Grid.GetRowCount();
	//int _fix_row_count=m_Grid.Get .GetFixedRowCount();
	_row_count=m_Grid.GetRowCount();
	if (_row_count<StartCalcu7Pamam)
		return;

	//计算7参数和残差	
	Calculate7Param();

	UpdateDlg();

	UpdateData(FALSE);
	InvalidateRect(NULL);
	UpdateWindow();
}

void CDeuDataTransform::OnBnClicked_cp_delpt()
{
	int iRowCount = m_Grid.GetRowCount();
	for( int i = 0 ; i < iRowCount ; i++ )
	{
		BOOL ret = m_Grid.IsRowSelected(i);

		if ( ret == TRUE)
		{
			m_Grid.RemoveRow(i);
		}

	}

	m_Grid.AdjustLayout();

	//////////////////////////////////////////////////////////////////////////
	//
	int _row_count=m_Grid.GetRowCount();
	//int _fix_row_count=m_Grid.Get .GetFixedRowCount();
	/*_row_count=m_Grid.GetRowCount();*/
	if (_row_count<StartCalcu7Pamam)
		return;

	//计算7参数和残差	
	Calculate7Param();

	UpdateDlg();

	UpdateData(FALSE);
	InvalidateRect(NULL);
	UpdateWindow();
}

void CDeuDataTransform::OnBnClicked_cp_addfile()
{//从文件加控制点

	// TODO: 在此添加控件通知处理程序代码
	//从文件加控制点
	CString strFilter;
	HRESULT hResult;
	strFilter="ControlPoint File (*.cp)|*.cp||"; //|All Files (*.*)|*.*||";


	CFileDialog dlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST, strFilter);	
	hResult = (int)dlg.DoModal();
	if(FAILED(hResult)) {
		return;
	}

	//UI
	CString strFileName;
	strFileName=dlg.GetPathName();

	
	//CString path;
	//path=GetCurrentDir();

	CXmlOperate xmlOp;
	xmlOp.LoadFile(strFileName);

	CNode* node=new CNode;
	xmlOp.LoadNode(node);

	CNode* ctrl_pts=NULL;
	//std::list<CNode*>::iterator it = node->_sub_nodes.begin(); 
	ctrl_pts=node;

	int ret = ctrl_pts->tag_name.Compare("CControlPointPairs");
	if(ret==TRUE)//wang
		return;//wang
	
	for (int i=0;i<ctrl_pts->_sub_nodes.size();i++)
	{
		CNode* ctrl_pt=getListItem(ctrl_pts->_sub_nodes,i);

		if (ctrl_pt->_sub_nodes.size() != 6)
			continue;

		AddOneCtrlPt(getListItem(ctrl_pt->_sub_nodes,0)->data,\
			getListItem(ctrl_pt->_sub_nodes,1)->data,\
			getListItem(ctrl_pt->_sub_nodes,2)->data,\
			getListItem(ctrl_pt->_sub_nodes,3)->data,\
			getListItem(ctrl_pt->_sub_nodes,4)->data,\
			getListItem(ctrl_pt->_sub_nodes,5)->data);
	}

	//
	int _row_count=m_Grid.GetRowCount();
	//int _fix_row_count=m_Grid.Get .GetFixedRowCount();
	/*_row_count=m_Grid.GetRowCount();*/
	if (_row_count<StartCalcu7Pamam)
		return;

	//计算7参数和残差	
	Calculate7Param();

	UpdateDlg();

	UpdateData(FALSE);
	InvalidateRect(NULL);
	UpdateWindow();
}

void CDeuDataTransform::Calculate7Param()
{
	PrepareData();

	CString SrcEllip;
	CString DestEllip;

	m_in_System_CB_cp.GetWindowText(SrcEllip);
	m_out_System_CB_cp.GetWindowText(DestEllip);

	int iModel = -1;

	if( m_model.Compare("布尔莎转换模型")==0)
	{		
		iModel=MODEL_BURSA;
	}
	else if(m_model.Compare("二维七参数转换模型")==0)
	{		
		iModel=MODEL_D2P7;
	}
	else if (m_model.Compare("三维七参数转换模型")==0)
	{	
		iModel=MODEL_D3P7;
	}
	else if (m_model.Compare("平面四参数转换模型")==0)
	{		
		iModel=MODEL_D2P4;
	}


	m_res_x = new double[m_CtrlPtCount];
	m_res_y = new double[m_CtrlPtCount];
	m_res_z = new double[m_CtrlPtCount];
	m_res	= new double[m_CtrlPtCount];


	IDeuEllipse *pSrcEllip = g_Task2000->GetEllipse(SrcEllip);
	IDeuEllipse *pDesEllip = g_Task2000->GetEllipse(DestEllip);

	//get PrimeMeridian	
	//m_in_band_combo.GetWindowText(m_in_band);
	//m_out_band_combo.GetWindowText(m_out_band);

	//pSrcEllip->putref_Centrol_Long(CSTR2DB(m_in_band));
	//pDesEllip->putref_Centrol_Long(CSTR2DB(m_out_band));

	//控制点坐标类型

	int iCtrlSrc_CP = g_Task2000->get_CoordType(SrcEllip);
	int iCtrlDes_CP = g_Task2000->get_CoordType(DestEllip);


	if( iCtrlSrc_CP != iCtrlDes_CP)
	{
		AfxMessageBox("控制点坐标类型不一致！",MB_OK | MB_ICONINFORMATION);
		return ; 
	}

	m_CtrlPt_CoordType = iCtrlSrc_CP;


	//单位
	
	m_UnitType = m_CtrlPt_CoordType ;


	int _np =  g_Task2000->GetParaCount(iModel);

	if (m_param)
	{
		delete m_param;
	}
	m_param = new double[_np];

	


	//CDeu2000Task _task;
	g_Task2000->Task_Calculate7Param(iModel,\
		m_CtrlPt_CoordType,\
		m_UnitType,\
		pSrcEllip,\
		pDesEllip,\
		m_CtrlPtCount,\
		m_x,\
		m_y,\
		m_z,\
		m_x2,\
		m_y2,\
		m_z2,\
		m_res_x,\
		m_res_y,\
		m_res_z,\
		m_res,\
		m_param,\
		&m_npara
		);

}


void CDeuDataTransform::AddOneCtrlPt(CString x,CString y,CString z,CString x2 ,CString y2,CString z2)
{
	CBCGPGridRow *pRow = m_Grid.addEmptyRow();

	CBCGPGridItem* pItem = pRow->GetItem(0);
	const _variant_t & v=(_variant_t)x;
	pItem->SetValue(v);
	pRow->GetItem(1)->SetValue((_variant_t)y);
	pRow->GetItem(2)->SetValue((_variant_t)z);
	pRow->GetItem(3)->SetValue((_variant_t)x2);
	pRow->GetItem(4)->SetValue((_variant_t)y2);
	pRow->GetItem(5)->SetValue((_variant_t)z2);

	m_Grid.AdjustLayout();
}



void CDeuDataTransform::PrepareData()
{
	//为求7参数准备数据
#if 1

	int _row_count=m_Grid.GetRowCount();

	double* x=new double[_row_count];
	double* y=new double[_row_count];
	double* z=new double[_row_count];

	double* x_2=new double[_row_count];
	double* y_2=new double[_row_count];
	double* z_2=new double[_row_count];

	CString _cstr_x;
	CString _cstr_y;
	CString _cstr_z;
	CString _cstr_x_2;
	CString _cstr_y_2;
	CString _cstr_z_2;



	for (int i=0;i<_row_count;i++)
	{
		int _row_index=i;
		CBCGPGridRow *pRow = m_Grid.GetRow(_row_index);

		_cstr_x = (CString)pRow->GetItem(0)->GetValue();
		_cstr_y = (CString)pRow->GetItem(1)->GetValue();
		_cstr_z = (CString)pRow->GetItem(2)->GetValue();
		_cstr_x_2 = (CString)pRow->GetItem(3)->GetValue();
		_cstr_y_2 = (CString)pRow->GetItem(4)->GetValue();
		_cstr_z_2 = (CString)pRow->GetItem(5)->GetValue();


		x[i]= _tstof(_cstr_x);
		y[i]= _tstof(_cstr_y);
		z[i]= _tstof(_cstr_z);
		x_2[i]= _tstof(_cstr_x_2);
		y_2[i]= _tstof(_cstr_y_2);
		z_2[i]= _tstof(_cstr_z_2);

	}
#endif
#if 0
	int _row_count=4;
	double* x=new double[4];
	double* y=new double[4];
	double* z=new double[4];

	double* x_2=new double[4];
	double* y_2=new double[4];
	double* z_2=new double[4];
	y[0]= 124.5421479 ;
	y[1]= 124.4116255 ;
	y[2]= 124.3614856 ;
	y[3]= 124.3208351 ;

	x[0]=46.1910731 ;
	x[1]=46.1941301 ;
	x[2]=46.2059616  ;
	x[3]=46.1629672  ;

	z[0]=145.48 ;
	z[1]=147.04 ;
	z[2]=  152.87;
	z[3]=  167.08;

	y_2[0]= 124.5419307;
	y_2[1]= 124.4114062 ;
	y_2[2]= 124.3612655 ;
	y_2[3]= 124.3206147 ;

	x_2[0]=46.1912544 ;
	x_2[1]=46.1943110  ;
	x_2[2]=46.2101431  ;
	x_2[3]=46.1631476  ;

	z_2[0]= 145.48;
	z_2[1]=  147.04;
	z_2[2]=  152.87;
	z_2[3]= 167.08 ;


#endif // _DEBUG

	//CDeuData *pdeuData = DEUMAINFRM.m_deuData;
	m_CtrlPtCount = _row_count;
	m_x=x;
	m_y=y;
	m_z=z;
	m_x2=x_2;
	m_y2=y_2;
	m_z2=z_2;

	//
#if 0
	//m_DY_ellipse
	doc->m_DY_ellipse->putref_BL_scale(1);
	doc->m_DY_ellipse->putref_Centrol_Long(117);

	doc->m_DY_ellipse->putref_Ellip_Name(L"Beijing1954");
	doc->m_DY_ellipse->putref_Flatening(298.257);
	doc->m_DY_ellipse->putref_Major(6378140.0);
	doc->m_DY_ellipse->putref_False_E(500000);
	doc->m_DY_ellipse->putref_False_N(0);
	doc->m_DY_ellipse->putref_Minor(6356755.3);
	doc->m_DY_ellipse->putref_N_Lat(0);
	doc->m_DY_ellipse->putref_Ns('n');
	doc->m_DY_ellipse->putref_Original_Lat(0);
	doc->m_DY_ellipse->putref_Prj_Name(L"高斯投影117");
	doc->m_DY_ellipse->putref_Prj_Type(L"高斯投影");
	doc->m_DY_ellipse->putref_S_Lat(0);
	doc->m_DY_ellipse->putref_We('e');

	//m_DY_des_ellipse
	doc->m_DY_des_ellipse->putref_BL_scale(1);
	doc->m_DY_des_ellipse->putref_Centrol_Long(117);

	doc->m_DY_des_ellipse->putref_Ellip_Name(L"Xian1980");
	doc->m_DY_des_ellipse->putref_Flatening(298.3);
	doc->m_DY_des_ellipse->putref_Major(6378245.0);
	doc->m_DY_des_ellipse->putref_False_E(500000);
	doc->m_DY_des_ellipse->putref_False_N(0);
	doc->m_DY_des_ellipse->putref_Minor(6356863.0);
	doc->m_DY_des_ellipse->putref_N_Lat(0);
	doc->m_DY_des_ellipse->putref_Ns('n');
	doc->m_DY_des_ellipse->putref_Original_Lat(0);
	doc->m_DY_des_ellipse->putref_Prj_Name(L"高斯投影117");
	doc->m_DY_des_ellipse->putref_Prj_Type(L"高斯投影");
	doc->m_DY_des_ellipse->putref_S_Lat(0);
	doc->m_DY_des_ellipse->putref_We('e');
#endif	

#if 1
	//m_DY_units
	//SHORT _coord_type;
	//m_Deu_coord_type->get_CtrlPtCoordType(&_coord_type);

	//BSTR _in_unit_x;
	//BSTR _in_unit_y;
	//BSTR _in_unit_z;
	//BSTR _out_unit_x;
	//BSTR _out_unit_y;
	//BSTR _out_unit_z;

	m_UnitType = m_CtrlPt_CoordType;//根据坐标类型设置单位类型



#endif	
	return ;
}

void CDeuDataTransform::UpdateDlg()
{
	//

	//7param
	//m_dx=m_param[0];
	//m_dy=m_param[1];
	//m_dz=m_param[2];

	//m_rx=m_param[3];
	//m_ry=m_param[4];
	//m_rz=m_param[5];

	//m_m=m_param[6];

	//
	CString _cstr_res;
	CString _cstr_res_x;
	CString _cstr_res_y;
	CString _cstr_res_z;

	for (int i=0;i<m_CtrlPtCount;i++)
	{
		//
		CBCGPGridRow *pRow = m_Grid.GetRow(i);

		_cstr_res_x.Format(_T("%.12f"), m_res_x[i]);
		pRow->GetItem(6)->SetValue((_variant_t)_cstr_res_x);

		_cstr_res_y.Format(_T("%.12f"), m_res_y[i]);
		pRow->GetItem(7)->SetValue((_variant_t)_cstr_res_y);

		_cstr_res_z.Format(_T("%.12f"), m_res_z[i]);
		pRow->GetItem(8)->SetValue((_variant_t)_cstr_res_z);

		_cstr_res.Format(_T("%.12f"), m_res[i]);
		pRow->GetItem(9)->SetValue((_variant_t)_cstr_res);
	}

	//////////////////////////////////////////////////////////////////////////


	m_Grid.AdjustLayout();

	UpdateData(FALSE);
	return;

}
void CDeuDataTransform::OnBnClicked_cp_delallpt()
{
	//删除所有点
	m_Grid.RemoveAll();

	m_Grid.AdjustLayout();
}

void CDeuDataTransform::OnCbnSelchangeCoortype()
{
	// TODO: 在此添加控件通知处理程序代码

	int count=m_in_coordtype_Combo.GetCurSel();
	CString txtCoordType;
	m_in_coordtype_Combo.GetLBText(count,txtCoordType);

	//  GEODETIC
	//	GEOCENTRIC
	//	PLANE
	int ret ;
	ret=txtCoordType.Compare("大地");

	if(ret==0)
	{
		m_in_CoordType = GEODETIC;
		return;
	}

	ret=txtCoordType.Compare("空间直角");

	if(ret==0)
	{
		m_in_CoordType = GEOCENTRIC;

		return;
	}

	ret=txtCoordType.Compare("平面");

	if(ret==0)
	{
		m_in_CoordType = PLANE;

		return;
	}
}

void CDeuDataTransform::OnCbnSelchangeCoortype1()
{
	// TODO: 在此添加控件通知处理程序代码

	int count=m_out_coordtype_Combo.GetCurSel();
	CString txtCoordType;
	m_out_coordtype_Combo.GetLBText(count,txtCoordType);

	//  GEODETIC
	//	GEOCENTRIC
	//	PLANE
	int ret ;
	ret=txtCoordType.Compare("大地");

	if(ret==0)
	{
		m_out_CoordType = GEODETIC;
		return;
	}

	ret=txtCoordType.Compare("空间直角");

	if(ret==0)
	{
		m_out_CoordType = GEOCENTRIC;

		return;
	}

	ret=txtCoordType.Compare("平面");

	if(ret==0)
	{
		m_out_CoordType = PLANE;

		return;
	}
}

void CDeuDataTransform::OnCbnSelchangeCombo1()
{
	int count=m_Combo_in_type.GetCurSel();
	m_Combo_in_type.GetLBText(count,m_in_Type);
}

void CDeuDataTransform::OnCbnSelchangeCBTypeOut()
{
	int count=m_Combo_out_type.GetCurSel();
	m_Combo_out_type.GetLBText(count,m_out_Type);
}
void CDeuDataTransform::OnCbnSelchangeTyd()
{
	// TODO: 在此添加控件通知处理程序代码
	int count=m_in_band_combo.GetCurSel();
	m_in_band_combo.GetLBText(count,m_in_band);

}

void CDeuDataTransform::OnCbnSelchangeTyd1()
{
	// TODO: 在此添加控件通知处理程序代码
	int count=m_out_band_combo.GetCurSel();
	m_out_band_combo.GetLBText(count,m_out_band);
}

void CDeuDataTransform::OnCbnSelchangeModel()
{

	int count=m_cb_model.GetCurSel();
	m_cb_model.GetLBText(count,m_model);
}

void CDeuDataTransform::OnEnChangeEditData()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CBCGPPropertyPage::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}



void CDeuDataTransform::OnBnClickedCpMdf()
{
	// TODO: 在此添加控件通知处理程序代码
	int iRowCount = m_Grid.GetRowCount();
	if(iRowCount==0)return;
	CBCGPGridRow *m_selRow;
	CString str1,str2,str3,str4,str5,str6;

	for( int i = 0 ; i < iRowCount ; i++ )
	{
		BOOL ret = m_Grid.IsRowSelected(i);

		if ( ret == TRUE)
		{
			m_selRow=m_Grid.GetRow(i);

			str1=m_selRow->GetItem(0)->GetValue();

			str2=m_selRow->GetItem(1)->GetValue();
			str3=m_selRow->GetItem(2)->GetValue();
			str4=m_selRow->GetItem(3)->GetValue();
			str5=m_selRow->GetItem(4)->GetValue();
			str6=m_selRow->GetItem(5)->GetValue();

			//////////////////////////将获取到的值添加到edit框///////////////
			m_cp_x1_ed.SetWindowText(str1);
			m_cp_y1_ed.SetWindowText(str2);
			m_cp_z1_ed.SetWindowText(str3);
			m_cp_x2_ed.SetWindowText(str4);
			m_cp_y2_ed.SetWindowText(str5);
			m_cp_z2_ed.SetWindowText(str6);
			m_Grid.RemoveRow(i);//wang
			m_Grid.AdjustLayout();//wang
		}
	}



	return;



}

void CDeuDataTransform::OnBnClickedCpSav()
{
	// TODO: 在此添加控件通知处理程序代码
	int iRowCount=m_Grid.GetRowCount();
	if(iRowCount==0)return;
	CBCGPGridRow *m_selRow;
	CString str1,str2,str3,str4,str5,str6;
	CNode *node=new CNode;
	node->tag_name=L"CControlPointPairs";
	node->ele_name=L"CControlPointPairs";
	node->parent=NULL;

	for(int i=0;i<iRowCount;i++)
	{
		//子节点
		CNode *m_node=new CNode;
		CString str;
		str.Format("CControlPointPairs%d",i);
		m_node->tag_name="CControlPointPairs";
		m_node->ele_name=str;
		m_node->parent=node;
		//获取grid中的数据,读数据到node结构

		m_selRow=m_Grid.GetRow(i);
		//x1
		CNode *node0=new CNode;
		str1=m_selRow->GetItem(0)->GetValue();
		node0->tag_name="x1";
		node0->ele_name="x1";
		node0->data=str1;
		node0->parent=m_node;
		m_node->_sub_nodes.push_back(node0);
		//y1
		str2=m_selRow->GetItem(1)->GetValue();
		CNode *node1=new CNode;
		node1->tag_name="y1";
		node1->ele_name="y1";
		node1->data=str2;
		node1->parent=m_node;
		m_node->_sub_nodes.push_back(node1);
		//z1
		str3=m_selRow->GetItem(2)->GetValue();
		CNode *node2=new CNode;
		node2->tag_name="z1";
		node2->ele_name="z1";
		node2->data=str3;
		node2->parent=m_node;
		m_node->_sub_nodes.push_back(node2);
		//x2
		str4=m_selRow->GetItem(3)->GetValue();
		CNode *node3=new CNode;
		node3->tag_name="x2";
		node3->ele_name="x2";
		node3->parent=m_node;
		node3->data=str4;
		m_node->_sub_nodes.push_back(node3);
		//y2
		str5=m_selRow->GetItem(4)->GetValue();
		CNode *node4=new CNode;
		node4->tag_name="y2";
		node4->ele_name="y2";
		node4->data=str5;
		node4->parent=m_node;
		m_node->_sub_nodes.push_back(node4);
		//z2
		str6=m_selRow->GetItem(5)->GetValue();
		CNode *node5=new CNode;
		node5->tag_name="z2";
		node5->ele_name="z2";
		node5->data=str6;
		node5->parent=m_node;
		m_node->_sub_nodes.push_back(node5);


		node->_sub_nodes.push_back(m_node);	

	}

	CString m_path;
	CString strFilename;

	CFileDialog hFileDlg(false,NULL,NULL,OFN_FILEMUSTEXIST |OFN_PATHMUSTEXIST,TEXT("控制点文件(*.cp) |*.cp|所有文件(*.*)|*.*|"),NULL);
	if(hFileDlg.DoModal()==IDOK)
	{
		m_path=hFileDlg.GetPathName();
		strFilename=hFileDlg.GetFileName();

		CXmlOperate *m_ctrlFile=new CXmlOperate; 
		m_ctrlFile->CreateFile(strFilename,node);

		m_ctrlFile->Save();

		UpdateData(FALSE);
	}


	return;




}


void CDeuDataTransform::OnCbnSelchangeComType6()
{
	// TODO: 在此添加控件通知处理程序代码
}
void CDeuDataTransform::DoTask()
{
	OnBnClickedButton12();
}

