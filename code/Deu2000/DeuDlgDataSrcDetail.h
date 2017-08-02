#pragma once

#include "resource.h"

class CDeuDlgDataSrcDetail : public CXTResizeDialog
{
	DECLARE_DYNAMIC(CDeuDlgDataSrcDetail)

public:
	CDeuDlgDataSrcDetail(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDeuDlgDataSrcDetail();

	// 对话框数据
	enum { IDD = IDD_DLG_SOURCE_DETAIL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnClose();
	//void MouseOverCtrl(CPoint point, HWND hWnd);
	DECLARE_MESSAGE_MAP()

public:
	CString          m_Name;	
	CStatic          m_wndPlaceHolder;
	CoordinateType   _coordtype;
	CXTTabCtrl       m_TabCtrl;

private:
	int              nIndex;		
	CXTPPropertyGrid m_wndPropertyGrid;

	//CXTPPropertyGridItem m_ItemName;
	//CXTPPropertyGridItem m_ItemRemark;
	//CXTPPropertyGridItem m_ItemEnvelope;
	//CXTPPropertyGridItem m_ItemLatitude;
	//CXTPPropertyGridItem m_ItemLongitude;
	//CXTPPropertyGridItem m_ItemParamUnits;
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
