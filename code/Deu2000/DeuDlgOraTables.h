#pragma once

#include "resource.h"
#include "afxwin.h"
#include "DeuVectorTranDlg.h"
#include "DeuRasterTranDlg.h"
#include "DeuGlobalParam.h"

class CDeuDlgOraTables : public CDialog
{
	DECLARE_DYNAMIC(CDeuDlgOraTables)

public:
	CDeuDlgOraTables(TranformType _ParentType=VECTOR, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDeuDlgOraTables();

	// �Ի�������
	enum { IDD = IDD_DLG_ORA_TABLES };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnOk();
	afx_msg void OnBnClickedCheck1();
	DECLARE_MESSAGE_MAP()

public:
	void SaveSelectFiles();
	
public:
	CDeuVectorTranDlg* p_Parent_Vector;
	CDeuRasterTranDlg* p_Parent_Raster;
	TranformType       _TType;
	CListCtrl		   m_list;
	CButton            m_chk_select;
	CButton            m_chk_addtional;
	BOOL			   IsHideChkbox;
	char*              StatusAction;  //��¼�������ѡ���������ѡ��
	CString            strConn;
	ORACLEINFO         m_oracle;
};
