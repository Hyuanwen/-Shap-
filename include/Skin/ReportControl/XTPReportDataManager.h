// XTPReportDataManager.h: interface for the CXTPReportDataManager class.
//
// This file is a part of the XTREME REPORTCONTROL MFC class library.
// (c)1998-2008 Codejock Software, All Rights Reserved.
//
// THIS SOURCE FILE IS THE PROPERTY OF CODEJOCK SOFTWARE AND IS NOT TO BE
// RE-DISTRIBUTED BY ANY MEANS WHATSOEVER WITHOUT THE EXPRESSED WRITTEN
// CONSENT OF CODEJOCK SOFTWARE.
//
// THIS SOURCE CODE CAN ONLY BE USED UNDER THE TERMS AND CONDITIONS OUTLINED
// IN THE XTREME TOOLKIT PRO LICENSE AGREEMENT. CODEJOCK SOFTWARE GRANTS TO
// YOU (ONE SOFTWARE DEVELOPER) THE LIMITED RIGHT TO USE THIS SOFTWARE ON A
// SINGLE COMPUTER.
//
// CONTACT INFORMATION:
// support@codejock.com
// http://www.codejock.com
//
/////////////////////////////////////////////////////////////////////////////

//{{AFX_CODEJOCK_PRIVATE
#if !defined(__XTPREPORTDATAMANAGER_H__)
#define __XTPREPORTDATAMANAGER_H__
//}}AFX_CODEJOCK_PRIVATE

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "XTPReportDefines.h"
#include "XTPReportADO.h"

class CXTPReportRecord;
class CXTPReportRecords;
class CXTPReportRecordItemVariant;
class CXTPReportDataManager;
class CXTPReportControl;

#define XTP_REPORTDATAMANAGER_MAX_LAST_COM_ERRORS 3

//===========================================================================
// Summary:
//     Basic set of parameters transferred to item handlers.
//     This structure groups together essential parameters used in
//     items processing activities. It is parent for all other structures:
//     XTP_REPORTRECORDITEM_DRAWARGS, XTP_REPORTRECORDITEM_CLICKARGS
// Example:
// <code>
// XTP_REPORTRECORDITEM_ARGS itemArgs(pControl, pRow, pColumn);
// pItem->OnBeginEdit(&itemArgs);
// </code>
// See Also: CXTPReportRecordItem::OnBeginEdit
//===========================================================================
struct XTP_REPORTDATAMANAGER_COM_ERROR
{
	HRESULT hResult;
	CString strMessage;
	CString strSource;

	XTP_REPORTDATAMANAGER_COM_ERROR()
	{
		hResult = 0;
		strMessage.Empty();
		strSource.Empty();
	}

	const XTP_REPORTDATAMANAGER_COM_ERROR& operator =(const XTP_REPORTDATAMANAGER_COM_ERROR& errorSrc)
	{
		this->hResult = errorSrc.hResult;
		this->strMessage = errorSrc.strMessage;
		this->strSource = errorSrc.strSource;

		return *this;
	}
};

//===========================================================================
// Summary:
// Example:
// <code>
// </code>
// See Also:
//===========================================================================
class CRstEvent : public XTPREPORTADODB::RecordsetEventsVt
{
private:
	ULONG m_cRef;
	CXTPReportDataManager* m_pDataManager;
public:
	CRstEvent(CXTPReportDataManager* pDataManager);
	~CRstEvent();

	STDMETHODIMP QueryInterface(REFIID riid, void ** ppv);
	STDMETHODIMP_(ULONG) AddRef(void);
	STDMETHODIMP_(ULONG) Release(void);

	virtual HRESULT __stdcall raw_WillChangeField(
		long cFields,
		VARIANT Fields,
		enum XTPREPORTADODB::EventStatusEnum* adStatus,
		struct XTPREPORTADODB::_Recordset* pRecordset);
	virtual HRESULT __stdcall raw_FieldChangeComplete(
		long cFields,
		VARIANT Fields,
		struct XTPREPORTADODB::Error* pError,
		enum XTPREPORTADODB::EventStatusEnum* adStatus,
		struct XTPREPORTADODB::_Recordset* pRecordset);
	virtual HRESULT __stdcall raw_WillChangeRecord(
		enum XTPREPORTADODB::EventReasonEnum adReason,
		long cRecords,
		enum XTPREPORTADODB::EventStatusEnum* adStatus,
		struct XTPREPORTADODB::_Recordset* pRecordset);
	virtual HRESULT __stdcall raw_RecordChangeComplete(
		enum XTPREPORTADODB::EventReasonEnum adReason,
		long cRecords,
		struct XTPREPORTADODB::Error* pError,
		enum XTPREPORTADODB::EventStatusEnum* adStatus,
		struct XTPREPORTADODB::_Recordset* pRecordset);
	virtual HRESULT __stdcall raw_WillChangeRecordset(
		enum XTPREPORTADODB::EventReasonEnum adReason,
		enum XTPREPORTADODB::EventStatusEnum* adStatus,
		struct XTPREPORTADODB::_Recordset* pRecordset);
	virtual HRESULT __stdcall raw_RecordsetChangeComplete(
		enum XTPREPORTADODB::EventReasonEnum adReason,
		struct XTPREPORTADODB::Error* pError,
		enum XTPREPORTADODB::EventStatusEnum* adStatus,
		struct XTPREPORTADODB::_Recordset* pRecordset);
	virtual HRESULT __stdcall raw_WillMove(
		enum XTPREPORTADODB::EventReasonEnum adReason,
		enum XTPREPORTADODB::EventStatusEnum* adStatus,
		struct XTPREPORTADODB::_Recordset* pRecordset);
	virtual HRESULT __stdcall raw_MoveComplete(
		enum XTPREPORTADODB::EventReasonEnum adReason,
		struct XTPREPORTADODB::Error* pError,
		enum XTPREPORTADODB::EventStatusEnum* adStatus,
		struct XTPREPORTADODB::_Recordset* pRecordset);
	virtual HRESULT __stdcall raw_EndOfRecordset(
		VARIANT_BOOL* fMoreData,
		enum XTPREPORTADODB::EventStatusEnum* adStatus,
		struct XTPREPORTADODB::_Recordset* pRecordset);
	virtual HRESULT __stdcall raw_FetchProgress(
		long Progress,
		long MaxProgress,
		enum XTPREPORTADODB::EventStatusEnum* adStatus,
		struct XTPREPORTADODB::_Recordset* pRecordset);
	virtual HRESULT __stdcall raw_FetchComplete(
		struct XTPREPORTADODB::Error* pError,
		enum XTPREPORTADODB::EventStatusEnum* adStatus,
		struct XTPREPORTADODB::_Recordset* pRecordset);

protected:
	CArray<XTPREPORTADODB::EventReasonEnum, XTPREPORTADODB::EventReasonEnum&> m_adReasonStack;
};

//===========================================================================
// Summary:
//     Represents report data manager.
// Remarks:
// See Also:
//===========================================================================
class _XTP_EXT_CLASS CXTPReportDataManager : public CXTPCmdTarget
{
	//{{AFX_CODEJOCK_PRIVATE
	friend class CXTPReportControl;
	friend class CRstEvent;
	void AFX_CDECL TRACE_ComError(_com_error &e);
	void AFX_CDECL TRACE_ProviderError(XTPREPORTADODB::_Connection* pConnDB);
	//}}AFX_CODEJOCK_PRIVATE

public:

	//-----------------------------------------------------------------------
	// Summary:
	//     Constructs a CXTPReportDataManager object.
	// Parameters:
	// Remarks:
	// Example:
	// <code>
	// </code>
	//-----------------------------------------------------------------------
	CXTPReportDataManager(CXTPReportControl* pReportControl);

	//-----------------------------------------------------------------------
	// Summary:
	//     Destroys a CXTPReportDataManager object, handles cleanup and deallocation
	//-----------------------------------------------------------------------
	virtual ~CXTPReportDataManager();

	virtual void SetDataSource(XTPREPORTADODB::_RecordsetPtr pDataSource);
	virtual XTPREPORTADODB::_RecordsetPtr GetDataSource() const;
	virtual BOOL DataBind();
	virtual HRESULT CreateColumns();
	virtual HRESULT UpdateReportRecords(XTPREPORTADODB::_RecordsetPtr pRecordset);
	virtual HRESULT AddReportRecords(XTPREPORTADODB::_RecordsetPtr pRecordset, BOOL bAddNow);
	virtual HRESULT PrepareDeleteReportRecords(XTPREPORTADODB::_RecordsetPtr pRecordset);
	virtual void ClearDeleteReportRecords();
	virtual HRESULT DeleteReportRecords();
	virtual HRESULT DeleteReportRecords(XTPREPORTADODB::_RecordsetPtr pRecordset);
	virtual HRESULT UpdateField(CXTPReportRecordItemVariant* pItem);
	virtual HRESULT UpdateRecord(CXTPReportRecord* pRecord);
	virtual HRESULT AddRecord(CXTPReportRecord* pRecord, BOOL bAddToReport);
	virtual HRESULT CreateEmptyRecord(CXTPReportRecord** ppRecord);
	virtual HRESULT DeleteRecord(CXTPReportRecord* pRecord);
	virtual XTP_REPORTDATAMANAGER_COM_ERROR GetLastComError();

protected:
	void RemoveDataSource();
	void ClearReportControl();

protected:
	CXTPReportControl* m_pReportControl;
	XTPREPORTADODB::_ConnectionPtr m_pConnection;
	XTPREPORTADODB::_RecordsetPtr m_pDataSource;
	CRstEvent* m_pRstEvent;
	DWORD m_dwRstEvent;
	CXTPReportRecords* m_pDeleteRecords;
	volatile BOOL m_bLocalUpdate;
	CArray<XTP_REPORTDATAMANAGER_COM_ERROR*, XTP_REPORTDATAMANAGER_COM_ERROR*> m_LastComError;
public:

};


AFX_INLINE XTPREPORTADODB::_RecordsetPtr CXTPReportDataManager::GetDataSource() const{
	return m_pDataSource;
}

#endif //#if !defined(__XTPREPORTDATAMANAGER_H__)
