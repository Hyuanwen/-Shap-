// XTPCalendarTimeLineView.h: interface for the CXTPCalendarTimeLineView class.
//
// This file is a part of the XTREME CALENDAR MFC class library.
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
#if !defined(_XTPCALENDARTIMELINEVIEW_H__)
#define _XTPCALENDARTIMELINEVIEW_H__
//}}AFX_CODEJOCK_PRIVATE

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning (disable: 4100)

#include "Common/XTPDrawHelpers.h"

#include "XTPCalendarView.h"
#include "XTPCalendarViewEvent.h"
#include "XTPCalendarTimeLineViewTimeScale.h"
#include "XTPCalendarTimeLineViewGroup.h"

class CXTPCalendarTimeLineView;

//============================================================================
enum XTPEnumCalendarTimeScaleParamsID
{
	xtpTSPID_Unknown    = 0,
	xtpTSPID_Day        = 1,
	xtpTSPID_Week       = 2,
	xtpTSPID_Month      = 3,
};

//===========================================================================
// Summary: Set of parameters transferred from calendar items to
//          mouse handlers.
// Remarks: This structure groups together all essential parameters used in
//          items processing activities. It is a basic structure for all
//          particular calendar's structures.
// See also: XTP_CALENDAR_HITTESTINFO
//===========================================================================
struct XTP_CALENDAR_HITTESTINFO_TIMELINE_VIEW : public XTP_CALENDAR_HITTESTINFO
{
};

//============================================================================
class _XTP_EXT_CLASS CXTPCalendarTimeLineView : public CXTPCalendarView
{
	friend class CXTPCalendarControl;
	DECLARE_DYNAMIC(CXTPCalendarTimeLineView)

public:
	typedef CXTPCalendarView TBase;

	CXTPCalendarTimeLineView(CXTPCalendarControl* pCalendarControl);
	virtual ~CXTPCalendarTimeLineView();

	virtual XTPCalendarViewType GetViewType() const;

	virtual void Populate();

	virtual void AdjustLayout(CDC* pDC, const CRect& rcView, BOOL bCallPostAdjustLayout = TRUE);

	virtual void Draw(CDC* pDC);

	virtual XTPCalendarViewType GetViewType() {
		return xtpCalendarTimeLineView;
	}

	virtual int GetViewDayCount(){
		return 0;
	};

	virtual CXTPCalendarViewDay* GetViewDay_(int nIndex) {return 0;};
	virtual COleDateTime GetViewDayDate(int nIndex) {
		return CXTPCalendarUtils::ResetTime(GetStartViewDate()); }; //COleDateTime(0.0);};

	virtual COleDateTime GetStartViewDate();
	virtual void SetStartViewDate(COleDateTime dt);

	virtual int GetTimeScaleID();
	virtual void SetTimeScaleID(int eTimeScaleParamsID);

	virtual CXTPCalendarTimeLineViewTimeScale* GetTimeScale();

	virtual BOOL HitTest(CPoint pt, XTP_CALENDAR_HITTESTINFO* pHitTest){return 0;};
	virtual BOOL HitTestEx(CPoint pt, XTP_CALENDAR_HITTESTINFO_TIMELINE_VIEW* pHitTest){return 0;};

	virtual CXTPCalendarEvents* RetrieveEvents(){return 0;};

	virtual BOOL GetScrollBarInfoV(SCROLLINFO* pSI, int* pnScrollStep = NULL);

	//virtual BOOL GetScrollBarInfoH(SCROLLINFO* pSI);
	virtual BOOL GetScrollBarInfoH(SCROLLINFO* pSI, int* pnScrollStep = NULL);

	virtual void ScrollH(int nPos, int nPos_raw);

	virtual void ShowDay(const COleDateTime& date, BOOL bSelect = TRUE)
	{
		SetStartViewDate(date);
	}

protected:
	//virtual void OnPostAdjustLayout();

	virtual void OnBeforeDestroy();

	//virtual BOOL OnTimer(UINT_PTR uTimerID){return 0;};

	virtual void OnScrollEnd(int nBar);

	virtual CXTPCalendarEventsPtr _GetEvents(COleDateTime dtStartDay, COleDateTime dtEndDay);

	CXTPCalendarTimeLineViewTimeScale*  m_pTimeScale;
//  CXTPCalendarTLV_GrObjectPtrArray    m_arChildren;

	int m_nHScrollPos;
	//UINT_PTR m_uRecalcHScrollTimerID;

private:
	CRect m_rcLastPopulate;

public:

	CXTPCalendarTimeLineViewGroups m_arGroups;

};

//===========================================================================
AFX_INLINE XTPCalendarViewType CXTPCalendarTimeLineView::GetViewType() const {
	return xtpCalendarTimeLineView;
}

AFX_INLINE COleDateTime CXTPCalendarTimeLineView::GetStartViewDate() {
	ASSERT(m_pTimeScale);
	return m_pTimeScale ? m_pTimeScale->GetStartViewDate() : COleDateTime::GetCurrentTime();
}

AFX_INLINE void CXTPCalendarTimeLineView::SetStartViewDate(COleDateTime dt) {
	ASSERT(m_pTimeScale);
	if(m_pTimeScale) {
		m_pTimeScale->SetStartViewDate(dt);
	}
	Populate();
}

AFX_INLINE CXTPCalendarTimeLineViewTimeScale* CXTPCalendarTimeLineView::GetTimeScale() {
	return m_pTimeScale;
}

#endif // !defined(_XTPCALENDARTIMELINEVIEW_H__)
