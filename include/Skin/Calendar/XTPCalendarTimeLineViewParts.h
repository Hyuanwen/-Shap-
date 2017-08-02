// XTPCalendarTimeLineViewParts.h: interface for the CXTPCalendarTimeLineView
// internal classes.

#ifndef _XTPCALENDAR_TIMELINEVIEWPARTS_H__
#define _XTPCALENDAR_TIMELINEVIEWPARTS_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Common\XTPDrawHelpers.h"
#include "XTPCalendarViewPart.h"

class CXTPCalendarTimeLineView;
class CXTPCalendarTimeLineViewEvent;

class _XTP_EXT_CLASS CXTPCalendarTimeLineViewTimeScalePart : public CXTPCalendarViewPart
{
public:
	CXTPCalendarTimeLineViewTimeScalePart(CXTPCalendarViewPart* pParentPart = NULL);

	virtual void RefreshMetrics();

	virtual int CalcHeigt(CDC* pDC);
	virtual void Draw(CDC* pDC, const CRect& rcRect, CXTPCalendarTimeLineView* pView);

	virtual int GetHeaderHeight() {
		return m_nHeaderHeight;
	};

	virtual CString GetHeaderDateFormat(int nLabelInterval);
	virtual void DrawHeader(CDC* pDC, const CRect& rcRect, CXTPCalendarTimeLineView* pView, int nLabelInterval);

public:
	CXTPCalendarViewPartFontValue m_fntScaleHeaderText; // Time scale header text font.

protected:
	int m_nHeaderHeight;
};

class _XTP_EXT_CLASS CXTPCalendarTimeLineViewPart : public CXTPCalendarViewPart
{
public:
	CXTPCalendarTimeLineViewPart(CXTPCalendarViewPart* pParentPart = NULL) : CXTPCalendarViewPart(pParentPart) {};
	//virtual int CalcHeigt(CDC* pDC);
	virtual void Draw(CDC* /*pDC*/, const CRect& /*rcRect*/, CXTPCalendarTimeLineView* /*pView*/){};

	//virtual int CalcEventHeigt(CDC* pDC){return 20;};

	virtual CSize CalcEventSize(CDC* /*pDC*/, CXTPCalendarTimeLineViewEvent* /*pEventView*/){return CSize(0, 0);};

	virtual void DrawEvent(CDC* /*pDC*/, const CRect& /*rcEvents*/, CXTPCalendarTimeLineViewEvent* /*pEventView*/){};

	//CXTPCalendarTimeLineViewTimeScalePart* GetTimeScalePart();
};

//===========================================================================
/*
class CXTPCalendarTLV_GroupFilter : public CXTPCmdTarget
{
public:
	CXTPCalendarTLV_GroupFilter(CXTPCalendarTLV_GroupFilter* pParent);
	virtual ~CXTPCalendarTLV_GroupFilter();

	virtual void RemoveAllChildren();

	virtual CString GetFilterTitle();

	virtual CXTPCalendarEventsPtr FilterEvents(CXTPCalendarEvents* pSource);

	virtual int GetChildrenCount() const;
	virtual CXTPCalendarTLV_GroupFilter* GetChild(int nIndex);
protected:
	typedef CArray<CXTPCalendarTLV_GroupFilter*, CXTPCalendarTLV_GroupFilter*>
		CXTPCalendarTLV_GroupFilters;

	CXTPCalendarTLV_GroupFilterPtrArray m_arChildren;
};

//============================================================================
class CXTPCalendarTLV_GrObject : public CXTPCmdTarget

{
	DECLARE_DYNAMIC(CXTPCalendarTLV_GrObject)
public:
	CXTPCalendarTLV_GrObject(CXTPCalendarTimeLineView* pView, CXTPCalendarTLV_GrObject* pParent = NULL);
	virtual ~CXTPCalendarTLV_GrObject();

	virtual void AdjustLayout(CRect rcParentRect);

	virtual CRect GetClientRect(int nYstart = 0);

	virtual int GetChildren(CXTPCalendarTLV_GrObjectPtrArray& rarChildren) = 0;
	virtual void RemoveAllChildren() = 0;

	virtual CXTPCalendarEventsPtr GetEvents();
	virtual void SetEvents( CXTPCalendarEvents* pSource,
							CXTPCalendarTLV_GroupFilter* pFilter);


protected:
	CXTPCalendarTLV_GrObject*   m_ptrParent;
	CXTPCalendarEvents          m_arEvents;
	CXTPCalendarTLV_GroupFilter*    m_ptrFilter;

	CXTPEmptyRect m_rcClientRect;
};

//============================================================================
class CXTPCalendarTLV_GroupObject : public CXTPCalendarTLV_GrObject

{
	DECLARE_DYNAMIC(CXTPCalendarTLV_GroupObject)
public:
	CXTPCalendarTLV_GroupObject(CXTPCalendarTLV_GrObject* pParent);
	virtual ~CXTPCalendarTLV_GroupObject();

	virtual void AdjustLayout(CRect rcParentRect);

	virtual CRect GetClientRect(int nYstart = 0);

	virtual int GetChildren(CXTPCalendarTLV_GrObjectPtrArray& rarChildren) = 0;
	virtual void RemoveAllChildren() = 0;

	virtual CXTPCalendarEventsPtr GetEvents();
	virtual void SetEvents( CXTPCalendarEvents* pSource,
		CXTPCalendarTLV_GroupFilter* pFilter);


protected:
};

//============================================================================
class CXTPCalendarTLV_EventsViewObject : public CXTPCalendarTLV_GrObject

{
	DECLARE_DYNAMIC(CXTPCalendarTLV_EventsViewObject)
public:
	CXTPCalendarTLV_EventsViewObject(CXTPCalendarTLV_GrObject* pParent);
	virtual ~CXTPCalendarTLV_EventsViewObject();

	virtual void AdjustLayout(CRect rcParentRect);

	virtual CRect GetClientRect(int nYstart = 0);

	virtual int GetChildren(CXTPCalendarTLV_GrObjectPtrArray& rarChildren);
	virtual void RemoveAllChildren();

	virtual CXTPCalendarEventsPtr GetEvents();
	virtual void SetEvents(CXTPCalendarEvents* pSource,
		CXTPCalendarTLV_GroupFilter* pFilter);


protected:
};
*/
//============================================================================
#endif // (_XTPCALENDAR_TIMELINEVIEWPARTS_H__)
