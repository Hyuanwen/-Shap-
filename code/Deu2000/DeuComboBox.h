/////////////////////////////////////////////////////////////////////
//
//     项目: 德毅智慧转换软件
//
//     作者：   刘君
//
//     描述:	栅格转换操作窗口类
//
//     版本:	V1.0
//	   CopyRight 2010-2011 ljdy Corporation All Rights Reserved
//
/////////////////////////////////////////////////////////////////////

#if !defined(AFX_MRUCOMBOBOX_H__EB1BCF79_B9DC_41A2_8579_33BDEBB32792__INCLUDED_)
#define AFX_MRUCOMBOBOX_H__EB1BCF79_B9DC_41A2_8579_33BDEBB32792__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "afxpriv.h"  

class CMRUComboBox : public CComboBox
{
public:
	CMRUComboBox();
	virtual ~CMRUComboBox();

public:	
	void           SetMRURegKey ( LPCTSTR szRegKey );
    const CString& GetMRURegKey() const;

    BOOL           SetMRUValueFormat ( LPCTSTR szValueFormat );
    const CString& GetMRUValueFormat() const;

    int            SetMaxMRUSize ( int nMaxSize );
    int            GetMaxMRUSize() const;

    BOOL		   SetAutoSaveOnDestroy   ( BOOL bAutoSave );
    BOOL		   SetAutoSaveAfterAdd    ( BOOL bAutoSave );
    BOOL           SetAutoRefreshAfterAdd ( BOOL bAutoRefresh );

public:
    CRecentFileList*    m_pMRU;
    CString             m_cstrRegKey;
    CString             m_cstrRegValueFormat;
    int                 m_nMaxMRUSize;
    BOOL                m_bSaveOnDestroy;
    BOOL                m_bSaveAfterAdd;
    BOOL                m_bRefreshAfterAdd;

public:
	BOOL AddToMRU ( LPCTSTR szNewItem );
    void EmptyMRU();
    void RefreshCtrl();
    BOOL LoadMRU();
    BOOL SaveMRU();

protected:
    BOOL AllocNewMRU();
    BOOL VerifyMRUParams() const;
    BOOL m_bParamsChanged;

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MRUCOMBOBOX_H__EB1BCF79_B9DC_41A2_8579_33BDEBB32792__INCLUDED_)
