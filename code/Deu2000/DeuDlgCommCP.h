/////////////////////////////////////////////////////////////////////
//     项目: 德毅智慧转换软件  控制点公共类
//     作者：   
//     修改者：
//     描述:
//     主要函数：
//     版本: 
//     修改: 
//	   CopyRight 2010 ljdy Corporation All Rights Reserved
/////////////////////////////////////////////////////////////////////

#pragma once

#include "resource.h"
#include "DeuGlobal.h"
#include "DeuTaskProcess.h"

class CDeuDlgCommCP : public CDialog
{
	DECLARE_DYNAMIC(CDeuDlgCommCP)

public:
	CDeuDlgCommCP(TranformType __Type=VECTOR, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDeuDlgCommCP();

	// 对话框数据
	enum { IDD = IDD_DLG_CONTROL_POINT };

protected:
	afx_msg void OnSize(UINT nType, int cx, int cy);	
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnNMRClickListControlPt(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnSetfocusEditSrc();
	afx_msg void OnEnSetfocusEditDest();
	afx_msg void OnNMDblclkListControlPt(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnKeydownListControlPt(NMHDR *pNMHDR, LRESULT *pResult);
	//virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnClose();
	afx_msg void OnLvnColumnclickListControlPt(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedListControlPt(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonInstall();
	afx_msg void OnBnClickedOutPutPara();
	afx_msg void OnBnClickedBtnGrid();
	afx_msg void OnBnClickedBtnInputparam();

	void OnCreateData();
	void OnImportData();
	void OnExportData();
	void OnDelRow();
	void OnDelAll();
	void ClearDataPackage();
	void ReLoadList();
	//afx_msg void OnListHotKey(WPARAM wParam, LPARAM lParam);
	void CalcResidual();  //Residual:the word mean "残差"
	DECLARE_MESSAGE_MAP()

public:	
	void DisableAllController();
	void EnbleAllController();	

	//add by chenyong 2013-3-26 
	void SetSrcCoorType(const CString& strSrcCoorType);
	void SetDesCoorType(const CString& strDesCoorType);

	//add by yzg
 	HRESULT GetControlPointByExcel(CString strPath);
 	char *  GetLetter( int iRow , char * szCol);
 	double  GetDoubleCellVal(Excel::_WorksheetPtr _sheet, char * szRowCol);
 	void    OnLoadControlData(const CString& strControlPath, const CString& strTransModel);

public:
	CDeuTaskProcess    	  m_TaskProcess;
	CMenu              	  m_menu;
	CListCtrl          	  m_List;
	CBitmap            	  m_bmp_import;
	CBitmap            	  m_bmp_save;
	CBitmap            	  m_bmp_del;
	CString            	  m_strModel;	
	CEdit              	  m_Edit_Src;
	CEdit              	  m_Edit_Dest;
	CDeuXmlReader      	  m_XmlCP;	
	_ControlPointPairs 	  _controlPointPairs;
	TranformType       	  _Type;

	int					  m_CtrlPtCount ;
	double				  *m_x;
	double				  *m_y;
	double  			  *m_z;
	double				  *m_x2;
	double				  *m_y2;
	double				  *m_z2;
	double				  *m_res_x;
	double				  *m_res_y;
	double				  *m_res_z;
	double				  *m_res;
	double				  *m_7param;
	double				  *m_Invpara;
	int     			  m_imodel;    //修改by潘万坤，2012 11 30
    CString				  m_strControlPath;

	//用于设置Excel
	deuExcelFormat        m_format;
	deuColumnFormatLetter m_ColumnFormat;
	_variant_t            m_t_format;
	string                ori_x;
	string                ori_y;
	string                ori_z;
	string                des_x;
	string                des_y;
	string                des_z;
	int                   lbt;
	BOOL                  m_install;
	BOOL				  IsInputParams; //add by chenyong 2013-12-20
	std::string			  m_GridParameter;
};
