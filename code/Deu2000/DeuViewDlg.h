#pragma once


#include "Resource.h"
#include "afxcmn.h"

class CDeuViewDlg : public CXTPDialog
{
	DECLARE_DYNAMIC(CDeuViewDlg)

public:
	CDeuViewDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDeuViewDlg();

// �Ի������� 
	enum { IDD = IDD_DLG_VIEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	DECLARE_MESSAGE_MAP()
	

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);	
};
