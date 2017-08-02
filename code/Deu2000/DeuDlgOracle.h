#pragma once

#include "resource.h"
#include "DeuVectorTranDlg.h"
#include "DeuRasterTranDlg.h"

class CDeuDlgOracle : public CDialog
{
	DECLARE_DYNAMIC(CDeuDlgOracle)

public:
	CDeuDlgOracle(TranformType _ParentType=VECTOR, CWnd* pParent=NULL, BOOL IsOut=FALSE);   // 标准构造函数
	virtual ~CDeuDlgOracle();

	// 对话框数据
	enum { IDD = IDD_DLG_ORACLE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedBtnOk();
	afx_msg void OnBnClickedBtnConntest();	
	DECLARE_MESSAGE_MAP()

public:
	BOOL IsConnectOracle(BOOL IsFill=FALSE);

public:	
	CEdit   m_ora_user;
	CEdit   m_ora_pwd;
	CEdit   m_ora_sid;
	CString strUser, strPwd, strSID;
	CString strConn;
	CDeuVectorTranDlg* p_Parent_Vector;
	CDeuRasterTranDlg* p_Parent_Raster;
	TranformType _TType;
	BOOL         _IsOut;
}; 
