// MRUComboBox.cpp : implementation file
///////////////////////////////////////////////////////////////////////
//
//     项目: 德毅智慧转换软件
//
//     作者：   刘君
//
//     描述:	栅格转换操作窗口类
//
//     版本:	V1.0
//	   CopyRight 2010-2011 ljdy Corporation All Rights Reserved
///////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DeuGlobal.h"
#include "DeuComboBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MRUC_DEFAULT_MRU_SIZE   10

CMRUComboBox::CMRUComboBox() : CComboBox(),
    m_bRefreshAfterAdd   ( FALSE ),
    m_bSaveAfterAdd      ( FALSE ),
    m_bSaveOnDestroy     ( TRUE ),
    m_nMaxMRUSize        ( MRUC_DEFAULT_MRU_SIZE ),
    m_pMRU               ( NULL ),
    m_bParamsChanged     ( FALSE )
{
}

CMRUComboBox::~CMRUComboBox()
{
    if ( m_bSaveOnDestroy )
        {
        if ( !SaveMRU() )
            {
            TRACE0("CMRUComboBox -- Warning - SaveMRU() in destructor failed. MRU was not saved.\n");
            }
        }

                                        // Free up the CRecentFileList object.
    if ( NULL != m_pMRU )
        {
        delete m_pMRU;
        }
}


BEGIN_MESSAGE_MAP(CMRUComboBox, CComboBox)
	//{{AFX_MSG_MAP(CMRUComboBox)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CMRUComboBox::AddToMRU ( LPCTSTR szNewItem )
{
    ASSERT ( NULL != szNewItem );
    if ( NULL == m_pMRU )
    {
        if ( !AllocNewMRU() )
        {
            TRACE0("CMRUComboBox -- AllocNewMRU() failed in AddToMRU().\n");
            return FALSE;
        }
    }

    m_pMRU->Add( szNewItem );
    if ( m_bRefreshAfterAdd ) 
	{
        RefreshCtrl();
    }

    if ( m_bSaveAfterAdd )
    {
        SaveMRU();
    }

    return TRUE;
}

BOOL CMRUComboBox::LoadMRU()
{
    if ( !AllocNewMRU() )
    {
        TRACE0("CMRUComboBox -- AllocNewMRU() failed in LoadMRU().\n");
        return FALSE;
    }

    m_pMRU->ReadList();

    return TRUE;
}

BOOL CMRUComboBox::SaveMRU()
{
	if ( NULL == m_pMRU )
	{
		TRACE0("CMRUComboBox -- SaveMRU failed - no CRecentFileList created.\n");
		return FALSE;
	}

	if ( !VerifyMRUParams() )
	{
		TRACE0("CMRUComboBox -- SaveMRU() failed - params not set.\n");
		return FALSE;
	}

	if ( m_bParamsChanged )
	{
		if ( !AllocNewMRU() )
		{
			TRACE0("CMRUComboBox -- SaveMRU failed - couldn't reallocate CRecentFileList with new MRU params.\n");
			return FALSE;
		}
	}

	m_pMRU->WriteList();

	return TRUE;
}

void CMRUComboBox::RefreshCtrl()
{
	CString cstrComboText;

    GetWindowText ( cstrComboText );
    ResetContent();

    for ( int i = 0; i < m_pMRU->GetSize(); i++ )
    {
        if ( (*m_pMRU)[i].GetLength() > 0 )
        {
            if ( AddString ( (*m_pMRU)[i] ) < 0 )
                {
                TRACE1("CMRUComboBox -- Warning - RefreshCtrl() couldn't add MRU item %d to combobox.\n",
                       i );
                }
        }
    }

    SetWindowText ( cstrComboText );
}

int CMRUComboBox::SetMaxMRUSize ( int nMaxSize )
{
	int nRetVal = m_nMaxMRUSize;

    ASSERT ( nMaxSize >= 1 );
    if ( nMaxSize <= 0 )
	{
        return -1;
	}

    m_nMaxMRUSize = nMaxSize;

    if ( NULL == m_pMRU )
    {
        nRetVal = 0;                    
    }

    if ( !AllocNewMRU() )
    {
        nRetVal = -1;              
        TRACE0("CMRUComboBox -- SetMaxMRUSize() failed - couldn't allocate new CRecentFileList.\n");
    }

    return nRetVal;
}

int CMRUComboBox::GetMaxMRUSize() const
{
    return m_nMaxMRUSize;
}

BOOL CMRUComboBox::SetAutoSaveOnDestroy ( BOOL bAutoSave )
{
	BOOL bRetVal = m_bSaveOnDestroy;
    m_bSaveOnDestroy = bAutoSave;

    return bRetVal;
}

BOOL CMRUComboBox::SetAutoSaveAfterAdd ( BOOL bAutoSave )
{
	BOOL bRetVal = m_bSaveAfterAdd;
    m_bSaveAfterAdd = bAutoSave;

    return bRetVal;
}

BOOL CMRUComboBox::SetAutoRefreshAfterAdd ( BOOL bAutoSave )
{
	BOOL bRetVal = m_bRefreshAfterAdd;
    m_bRefreshAfterAdd = bAutoSave;

    return bRetVal;
}

BOOL CMRUComboBox::VerifyMRUParams() const
{
	BOOL bRetVal = TRUE;

    // 1. The registry key string must be non-empty.
    if ( m_cstrRegKey.IsEmpty() || 0 == m_cstrRegKey.GetLength() )
    {
        TRACE0("CMRUComboBox -- VerifyMRUParams() - registry key name not set.\n");
        bRetVal = FALSE;
    }

    // 2. The reg value must be non-empty and contain "%d"
    if ( m_cstrRegValueFormat.IsEmpty() || 0 == m_cstrRegValueFormat.GetLength() )
    {
        TRACE0("CMRUComboBox -- VerifyMRUParams() - registry value format not set.\n");
        bRetVal = FALSE;
    }
    else if ( -1 == m_cstrRegValueFormat.Find ( _T("%d") ) )
    {
        TRACE0("CMRUComboBox -- VerifyMRUParams() - registry value format doesn't contain \"%d\"\n");
        bRetVal = FALSE;
    }

    // 3. The Max MRU size must be > 0.
    if ( m_nMaxMRUSize <= 0 )
    {
        TRACE0("CMRUComboBox -- VerifyMRUParams() - max MRU size is set to <= 0\n");
        bRetVal = FALSE;
    }

    return bRetVal;
}

BOOL CMRUComboBox::AllocNewMRU()
{
	CString* acstrOldList = NULL;
	int      nItemsToCopy;
	int      i;

    // Make sure the MRU params are OK.
    if ( !VerifyMRUParams() )
    {
        TRACE0("CMRUComboBox -- AllocNewMRU() returning FALSE - MRU list params invalid or not set.\n");
        return FALSE;
    }

    try
    {
        // Figuring out how many strings to
        // copy: The lesser of the new MRU size and the previous MRU's size.
        // Of course, if there was no previous MRU, then nothing will be copied.
        nItemsToCopy = m_nMaxMRUSize;

        if ( NULL != m_pMRU )
        {
            nItemsToCopy = __min ( m_nMaxMRUSize, m_pMRU->GetSize() );
			
			// Save the contents of the old MRU list.
            acstrOldList = new CString [ nItemsToCopy ];
            for ( i = 0; i < nItemsToCopy; i++ )
            {
                acstrOldList[i] = (*m_pMRU)[i];
            }

            // Nuke the old CRecentFileList object...
            delete m_pMRU;
        }

        // and make a new one!
        m_pMRU = new CRecentFileList ( 1, m_cstrRegKey, m_cstrRegValueFormat, m_nMaxMRUSize );
        if ( NULL != acstrOldList )
        {
            for ( i = nItemsToCopy - 1; i >= 0; i-- )
            {
                m_pMRU->Add ( acstrOldList[i] );
            }

            delete [] acstrOldList;
        }
    }
    catch ( CMemoryException )
    {
        TRACE0("CMRUComboBox -- Memory exception in AllocNewMRU()!\n");
        if ( NULL != m_pMRU )
        {
            delete m_pMRU;
        }

        throw;
    }

    // Reset the changed flag.
    m_bParamsChanged = FALSE;

    return TRUE;
}

void CMRUComboBox::SetMRURegKey ( LPCTSTR szRegKey )
{
    // The key name can't be a null string.
    ASSERT ( NULL != szRegKey );

    try
    {
        // Store the reg key name & set the changed flag.
        m_cstrRegKey = szRegKey;
        m_bParamsChanged = TRUE;
    }
    catch ( CMemoryException )
    {
        TRACE0("CMRUComboBox -- Memory exception in CMRUComboBox::SetMRURegKey()!\n");
        throw;
    }
}

const CString& CMRUComboBox::GetMRURegKey() const
{
    return m_cstrRegKey;
}

BOOL CMRUComboBox::SetMRUValueFormat ( LPCTSTR szValueFormat )
{
	BOOL bRetVal = FALSE;

    // The key name can't be a null string.
    ASSERT ( NULL != szValueFormat );
	
	// Check that the format strings contains "%d"
    if ( NULL == _tcsstr ( szValueFormat, _T("%d") ) )
    {
        TRACE0("CMRUComboBox -- SetMRUValueFormat() returning FALSE - argument didn't contain \"%d\"\n");
        return FALSE;
    }
    else
    {
        try
        {
            // Save the format string and set the changed flag.
            m_cstrRegValueFormat = szValueFormat;
            m_bParamsChanged = TRUE;
            bRetVal = TRUE;
        }
        catch ( CMemoryException )
        {
            TRACE0("CMRUComboBox -- Memory exception in CMRUComboBox::SetMRUValueFormat()!\n");
            throw;
        }
    }

    return bRetVal;
}

const CString& CMRUComboBox::GetMRUValueFormat() const
{
    return m_cstrRegValueFormat;
}

