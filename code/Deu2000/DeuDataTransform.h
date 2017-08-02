#pragma once
#include "afxwin.h"
//#include "afxwin.h"

#include "CellTypesGridCtrl.h"

#include "textprogressctrl.h"
#include "DeuDialog.h"

// CDeuDataTransform 对话框
extern CDeu2000Task *g_Task2000;


class CDeuDataTransform : public CDeuDialog
{
	DECLARE_DYNAMIC(CDeuDataTransform)

public:
	CDeuDataTransform();
	//CDeuDataTransform(UINT nIDCaption);
	virtual ~CDeuDataTransform();

// 对话框数据
	enum { IDD = IDD_DATA_TRANSFORM };
public:
	void SetCaption(CString strCaption);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButView();
public:
	CEdit m_in_FileName_ed;
	CEdit m_out_FileName_ed;

	CComboBox m_Combo_in_type;
	BOOL OnInitDialog(void);
	CComboBox m_Combo_out_type;
	CComboBox m_in_coordtype_Combo;
	CComboBox m_out_coordtype_Combo;
	CComboBox m_in_band_combo;
	CComboBox m_out_band_combo;

public:
	afx_msg void OnCbnSelchangeCoordinates();
	afx_msg void OnCbnDblclkCoordinates();
	afx_msg void OnCbnDropdownCoordinates();
	afx_msg void OnCbnDropdownComType6();
	afx_msg void OnCbnDropdownCS_SRC_CP();
	afx_msg void OnCbnDropdownCS_DES_CP();

public:
	CComboBox m_CtrlPt_coordtype_Combo;
	afx_msg void OnBnClickedButView2();
	afx_msg void OnCbnSelchangeCoortype2();
	CStatic m_static_7p_x;
	CStatic m_static_7p_x2;
	CStatic m_static_7p_y;
	CStatic m_static_7p_y2;
	CStatic m_static_7p_z;
	CStatic m_static_7p_z2;

public:
	afx_msg void OnBnClickedButton12();

	CString m_in_FileName;
	CString m_in_Type;
	CString m_out_Type;
	CString m_out_PathName;
	CString m_in_System;
	CComboBox m_in_System_CB;
	CComboBox m_out_System_CB;
	CString m_out_System;

//////////////////////////////////////////////////////////////////////////
public:
	CString m_in_System_cp;
	CComboBox m_in_System_CB_cp;
	CComboBox m_out_System_CB_cp;
	CString m_out_System_cp;



public:
	CEdit m_7p_dx_ed;
	CEdit m_7p_dy_ed;
	CEdit m_7p_dz_ed;
	CEdit m_7p_rx_ed;
	CEdit m_7p_ry_ed;
	CEdit m_7p_rz_ed;
	CEdit m_7p_m_ed;
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	CButton m_btn_7p_addpt;
	CButton m_btn_7p_delpt;
	CButton m_btn_7p_addfile;
	CButton m_btn_7p_delall;
	CButton m_btn_view2;
	CCellTypesGridCtrl m_Grid;

public:
	afx_msg void OnBnClickedButton11();
	void AddOneCtrlPt(CString x,CString y,CString z,CString x2 ,CString y2,CString z2);
	
public:
	//void UpdateDoc();
	void UpdateDlg();
	void PrepareData();
	void Calculate7Param();


public:
	ISevenParams* m_seven_param;
	IDeuCoordType* m_Deu_coord_type;
	IDeuEllipse* m_Deu_ellipse;
	IDeuEllipse* m_Deu_des_ellipse;
	IDeuUnits* m_Deu_units;
	IDeuSpatialReference* m_Deu_SRS;
	IDeuConnPool* m_ConnPool;
	//IDeuTrans* m_DY_Trans;
	HWND m_hwnd;	

public:
	SHORT m_in_CoordType;//坐标类型（曹欣）
	SHORT m_out_CoordType;
	SHORT m_in_UnitType;
	SHORT m_out_UnitType;


public:
	SHORT m_CtrlPt_CoordType;
	SHORT m_UnitType;
	BSTR  in_unit_x;
	BSTR  in_unit_y;
	BSTR  in_unit_z;
	BSTR  out_unit_x;
	BSTR  out_unit_y;
	BSTR  out_unit_z;
	//////////////////////////////////////////////////////////////////////////
	int		m_CtrlPtCount ;
	double	*m_x;
	double	*m_y;
	double  *m_z;
	double	*m_x2;
	double	*m_y2;
	double	*m_z2;
	double	*m_res_x;
	double	*m_res_y;
	double	*m_res_z;
	double	*m_res;
	double	*m_param;
	ULONG	m_npara;

public:
	afx_msg void OnBnClickedButton13();
	
	double m_dx;
	double m_dy;
	double m_dz;
	double m_rx;
	double m_ry;
	double m_rz;
	double m_m;

public:
	void  SetDeuTask(CDeuTask * pTask);
	CDeuTask * GetDeuTask();
	CDeuTask *m_deuTask;
	afx_msg void OnCbnSelchangeCoortype();
	afx_msg void OnCbnSelchangeCoortype1();
	afx_msg void OnCbnSelchangeInType();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnCbnSelchangeCBTypeOut();

public:
	BOOL m_bRunning;

public:	
	afx_msg LRESULT OnTaskFinished(WPARAM, LPARAM);
	afx_msg LRESULT OnProgress(WPARAM, LPARAM);
	CTextProgressCtrl  m_Progress;
	afx_msg void OnCbnSelchangeTyd();
	CString m_in_band;
	CString m_out_band;

	afx_msg void OnCbnSelchangeTyd1();
	afx_msg void OnEnChangeEditData();
	afx_msg void OnBnClicked_cp_addfile();
	afx_msg void OnBnClicked_cp_addpt();
	afx_msg void OnBnClicked_cp_delpt();
	afx_msg void OnBnClicked_cp_delallpt();

public:
	CString m_cp_x1;
	CString m_cp_y1;
	CString m_cp_z1;
	CString m_cp_x2;
	CString m_cp_y2;
	CString m_cp_z2;
	CEdit m_cp_x1_ed;
	CEdit m_cp_y1_ed;
	CEdit m_cp_z1_ed;
	CEdit m_cp_x2_ed;
	CEdit m_cp_y2_ed;
	CEdit m_cp_z2_ed;

	afx_msg void OnBnClickedCpMdf();
	afx_msg void OnBnClickedCpSav();
	CButton m_btn_7p_modf;
	CButton m_btn_7p_save;
	CComboBox m_cb_model;
	CString m_model;

	afx_msg void OnCbnSelchangeModel();
	afx_msg void OnCbnSelchangeComType6();

	void DoTask();
};
