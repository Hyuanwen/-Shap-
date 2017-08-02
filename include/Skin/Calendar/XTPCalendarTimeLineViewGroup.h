// XTPCalendarTimeLineViewGroup.h: interface for the CXTPCalendarTimeLineViewGroup class.
//


#if !defined(_XTPCALENDARTIMELINEVIEWGROUP_H__)
#define _XTPCALENDARTIMELINEVIEWGROUP_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning (disable: 4100)

#include "Common/XTPDrawHelpers.h"

#include "XTPCalendarView.h"
#include "XTPCalendarViewEvent.h"
#include "XTPCalendarViewDay.h"
//#include "XTPCalendarTimeLineViewTimeScale.h"

class CXTPCalendarEvent;
class CXTPCalendarTimeLineView;
class CXTPCalendarTimeLineViewGroup;
class CXTPCalendarTimeLineViewGroups;
class CXTPCalendarTimeLineViewEvent;
//============================================================================


//////////////////////////////////////////////////////////////////////////
class _XTP_EXT_CLASS CXTPCalendarTimeLineViewEvent : public CXTPCalendarViewEvent // CXTPCalendarViewEventT
{
public:
	CXTPCalendarTimeLineViewEvent(CXTPCalendarEvent* pEvent, CXTPCalendarTimeLineViewGroup* pGroup);

	//void AdjustLayout()
	void CalcRect(CDC* pDC);

	CXTPCalendarTimeLineView* GetView();

	CXTPCalendarTimeLineViewGroup* GetViewGroup() const {
		return m_pGroup;
	}
	virtual CXTPCalendarViewGroup* GetViewGroup_() const;

	virtual BOOL HitTest(CPoint pt, XTP_CALENDAR_HITTESTINFO* pHitTest) { return FALSE; };

	virtual BOOL IsVisible() { return NULL; };
	virtual BOOL IsSelected() const;

	virtual void AdjustLayout(CDC* pDC, const CRect& rcEventMax, int nEventPlaceNumber);
	virtual void AdjustLayout2(CDC* pDC, const CRect& rcEventMax, int nEventPlaceNumber) {};

	virtual void Draw(CDC* pDC);

	virtual void ChangeEventPlace(int nNewPlace);

	virtual CXTPCalendarTimeLineViewPart* GetPart();

	virtual int GetEventDurationInPixels();
protected:
	CXTPCalendarTimeLineViewGroup * m_pGroup;
	int m_nEventDurationInPixels;
};

//////////////////////////////////////////////////////////////////////////
class _XTP_EXT_CLASS CXTPCalendarTimeLineViewGroup : public CXTPCalendarViewGroup
{
public:
	typedef CXTPCalendarViewGroup TBase;

	CXTPCalendarTimeLineViewGroup(CXTPCalendarTimeLineView* pView,
								  CXTPCalendarTimeLineViewGroup* pParentGroup = NULL);

	virtual ~CXTPCalendarTimeLineViewGroup();

	virtual void Populate(COleDateTime dtDayDate) {};
	virtual void Populate(CXTPCalendarEvents* pEvents);

	virtual void AdjustLayout(CDC* pDC, const CRect& rcGroup);
//  virtual void AdjustLayout2(CDC* pDC, const CRect& rcGroup); //<COMBINE AdjustLayout>

	virtual void Draw(CDC* pDC);

	virtual BOOL HitTest(CPoint pt, XTP_CALENDAR_HITTESTINFO* pHitTest) {return 0; };

	CXTPCalendarTimeLineView* GetView() const {
		return m_pView;
	}

	virtual int GetViewEventsCount() {
		return m_arEvents.GetCount();
	}

	virtual CXTPCalendarViewEvent* GetViewEvent_(int nIndex) {
		return m_arEvents.GetAt(nIndex);
	}

	virtual CXTPCalendarTimeLineViewEvent* GetViewEvent(int nIndex) {
		return m_arEvents.GetAt(nIndex);
	}

	virtual CXTPCalendarViewDay* GetViewDay_() const {
		ASSERT(FALSE);
		return 0; };

	//-----------------------------------------------------------------------
	// Summary:
	//     Call this member function to obtain a pointer to the calendar control
	//     object.
	// Returns:
	//     A pointer to a CXTPCalendarControl object.
	//-----------------------------------------------------------------------
	virtual CXTPCalendarControl* GetCalendarControl();

protected:
	typedef CXTPCalendarPtrCollectionT<CXTPCalendarTimeLineViewEvent> TViewEventsCollection;

	CXTPCalendarTimeLineView* m_pView;
	CXTPCalendarTimeLineViewGroup* m_pParentGroup;

	TViewEventsCollection           m_arEvents;
	CXTPCalendarTimeLineViewGroups* m_pChildren;


};

class _XTP_EXT_CLASS CXTPCalendarTimeLineViewGroups : public CXTPCalendarPtrCollectionT<CXTPCalendarTimeLineViewGroup>
{
};

/////////////////////////////////////////////////////////////////////////////
AFX_INLINE CXTPCalendarViewGroup* CXTPCalendarTimeLineViewEvent::GetViewGroup_() const {
	return m_pGroup;
}

AFX_INLINE int CXTPCalendarTimeLineViewEvent::GetEventDurationInPixels() {
	return m_nEventDurationInPixels;
}
//===========================================================================

#endif // !defined(_XTPCALENDARTIMELINEVIEWGROUP_H__)
