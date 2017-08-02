#pragma once

#include "resource.h"
#include "afxwin.h"

class CDeuDlgDataSrcCustomDetail : public CXTResizeDialog
{
	DECLARE_DYNAMIC(CDeuDlgDataSrcCustomDetail)

public:
	CDeuDlgDataSrcCustomDetail(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDeuDlgDataSrcCustomDetail();

// �Ի�������
	enum { IDD = IDD_DLG_SOURCE_CUSTOM_DETAIL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnClose();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedBtnOk();
	//void  MouseOverCtrl(CPoint point, HWND hWnd);
	DECLARE_MESSAGE_MAP()

public:
	CString          m_Name;	
	CStatic          m_wndPlaceHolder;
	CoordinateType   _coordtype;
private:
	int              nIndex;		
	CXTPPropertyGrid m_wndPropertyGrid;
	CXTTabCtrl       m_TabCtrl;
	CButton          m_btnOk;   // ���水ť

	//CString m_strTipText;
	//CString m_strTipTitle;
	//int     m_nMillisecs;
	//int     m_nDelayMillisecs;
	//int     m_cx;
	//int     m_cy;
	//int     m_nLineSpacing;
	//BOOL    m_bThickBorder;
	//BOOL    m_bAlphaShadow;
	//BOOL    m_bDropShadow;
	//BOOL    m_bMoveTipBelowCursor;
	//DWORD   m_dwTipStyle;
};
