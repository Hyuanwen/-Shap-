// XTPCalendarTimeLineViewTimeScale.h: interface for the
// CXTPCalendarTimeLineViewTimeScale class.
//

//{{AFX_CODEJOCK_PRIVATE
#ifndef _XTPCALENDARTIMELINEVIEWTIMESCALE_H__
#define _XTPCALENDARTIMELINEVIEWTIMESCALE_H__
//}}AFX_CODEJOCK_PRIVATE

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "Common/XTPDrawHelpers.h"

#include "XTPCalendarPaintManager.h"
#include "XTPCalendarPtrs.h"

struct XTPCALENDARHITTESTINFO_TIMELINE_VIEW;
class CXTPCalendarTimeLineView;
class CXTPCalendarTLV_TimeScaleParams;
class CXTPCalendarTimeLineViewTimeScalePart;


//============================================================================
enum XTPEnumCalendarDateItem
{
	xtpDTScale_Unknown  = 0, // Typed unknown value

	xtpDTScale_Sec      = 0x0001,
	xtpDTScale_Min      = 0x0002,
	xtpDTScale_Hour     = 0x0004,

	xtpDTScale_Day      = 0x0010,
	xtpDTScale_Week     = 0x0020,
	xtpDTScale_Month    = 0x0040,
	xtpDTScale_Year     = 0x0080,
};

struct XTP_CALENDAR_TIMELINE_VIEW_SCALE
{
	int m_eType;    // one of the values from enum XTPEnumCalendarDateItem
	int m_nValue;   //
};

//============================================================================
class _XTP_EXT_CLASS CXTPCalendarTimeLineViewTimeScale : public CXTPCmdTarget
{
public:
	CXTPCalendarTimeLineViewTimeScale(CXTPCalendarTimeLineView* pView);
	virtual ~CXTPCalendarTimeLineViewTimeScale();

	CXTPCalendarTimeLineView* GetView();

	virtual CXTPCalendarTLV_TimeScaleParams* GetTimeScaleParams();

	virtual void SetTimeScaleParams(int eTimeScaleParamsID);
	virtual void SetTimeScaleParams2(CXTPCalendarTLV_TimeScaleParams* pSParams);

	virtual COleDateTime GetStartViewDate();
	virtual void SetStartViewDate(COleDateTime dt);

	virtual void AdjustLayout(CRect rcParentRect);
	virtual CRect GetClientRect(int nYstart = 0);
	virtual CRect GetRect();

	virtual void Draw(CDC* pDC);

	virtual BOOL HitTestEx(CPoint pt, XTPCALENDARHITTESTINFO_TIMELINE_VIEW* pHitTest);

protected:
	//int _CalcUpperScaleHeigt

protected:
	CXTPCalendarTimeLineView* m_pParentView;
	COleDateTime    m_dtStartViewDate;

	CXTPEmptyRect   m_rcRect;
	CXTPEmptyRect   m_rcScale;

	CXTPCalendarTLV_TimeScaleParams* m_pTimeScaleParams;
};


//============================================================================
class _XTP_EXT_CLASS CXTPCalendarTLV_TimeScaleParams : public CXTPCmdTarget
{
	friend class CXTPCalendarTimeLineViewTimeScale;
public:
	CXTPCalendarTLV_TimeScaleParams(int nTimeScaleParamsID,
									CXTPCalendarTimeLineViewTimeScale* pTimeScale);

	virtual ~CXTPCalendarTLV_TimeScaleParams();

	CXTPCalendarTimeLineViewTimeScale* GetParentTimeScale();

	virtual int GetTimeScaleParamsID() const;

	virtual XTP_CALENDAR_TIMELINE_VIEW_SCALE GetScaleInterval() const;
	virtual COleDateTimeSpan GetScaleInterval();

	virtual int GetScaleIntervalWidth_px();

	virtual COleDateTimeSpan GetTimePerPixel();

	virtual COleDateTime CalcScaleIntervalBegin(COleDateTime dtStart);

//  virtual BOOL GetScrollBarInfoH(int& rnMaxPos_px, int& rnPage_px, int& rnStep_px)// = 0;
//  {
//      return FALSE;
//  };

	virtual CXTPCalendarTimeLineViewTimeScalePart* GetPart() = 0;

protected:
//  void SetParentTimeScale(CXTPCalendarTimeLineViewTimeScale* pTimeScale);

	void SetScaleInterval(int eType, int nValue);

	XTP_CALENDAR_TIMELINE_VIEW_SCALE m_scaleInterval;
	int m_nScaleIntervalWidth_px;
private:
	CXTPCalendarTimeLineViewTimeScale* m_pTimeScale;
	int m_nTimeScaleParamsID;
};

//============================================================================
class _XTP_EXT_CLASS CXTPCalendarTLV_TimeScaleParams_Day :
								public CXTPCalendarTLV_TimeScaleParams
{
public:
	CXTPCalendarTLV_TimeScaleParams_Day(CXTPCalendarTimeLineViewTimeScale* pTimeScale);
	virtual ~CXTPCalendarTLV_TimeScaleParams_Day();

//  virtual BOOL GetScrollBarInfoH(int& rnMaxPos_px, int& rnPage_px, int& rnStep_px)
//  {
//      return FALSE;
//  };

	virtual CXTPCalendarTimeLineViewTimeScalePart* GetPart();

};

//============================================================================
class _XTP_EXT_CLASS CXTPCalendarTLV_TimeScaleParams_Week :
								public CXTPCalendarTLV_TimeScaleParams
{
public:
	CXTPCalendarTLV_TimeScaleParams_Week(CXTPCalendarTimeLineViewTimeScale* pTimeScale);
	virtual ~CXTPCalendarTLV_TimeScaleParams_Week();

	virtual CXTPCalendarTimeLineViewTimeScalePart* GetPart();

	//virtual CString FormatLowerScaleLabel(COleDateTime dtDateTime);
	//virtual void DrawLowerScale(CDC* pDC, DATE dtStart, const CRect& rcRect);
};

//============================================================================
class _XTP_EXT_CLASS CXTPCalendarTLV_TimeScaleParams_Month :
								public CXTPCalendarTLV_TimeScaleParams
{
public:
	CXTPCalendarTLV_TimeScaleParams_Month(CXTPCalendarTimeLineViewTimeScale* pTimeScale);
	virtual ~CXTPCalendarTLV_TimeScaleParams_Month();

	virtual CXTPCalendarTimeLineViewTimeScalePart* GetPart();

	//virtual CString FormatLowerScaleLabel(COleDateTime dtDateTime);
	//virtual void DrawLowerScale(CDC* pDC, DATE dtStart, const CRect& rcRect);
};

////////////////////////////////////////////////////////////////////////////
AFX_INLINE CXTPCalendarTimeLineView* CXTPCalendarTimeLineViewTimeScale::GetView() {
	return m_pParentView;
}

AFX_INLINE CXTPCalendarTLV_TimeScaleParams*
					CXTPCalendarTimeLineViewTimeScale::GetTimeScaleParams() {
	return m_pTimeScaleParams;
}

AFX_INLINE COleDateTime CXTPCalendarTimeLineViewTimeScale::GetStartViewDate() {
	return m_dtStartViewDate;
}

AFX_INLINE void CXTPCalendarTimeLineViewTimeScale::SetStartViewDate(COleDateTime dt) {
	m_dtStartViewDate = dt;
}
AFX_INLINE CRect CXTPCalendarTimeLineViewTimeScale::GetRect() {
	return m_rcRect;
}

AFX_INLINE CXTPCalendarTimeLineViewTimeScale*
						CXTPCalendarTLV_TimeScaleParams::GetParentTimeScale() {
	return m_pTimeScale;
}


AFX_INLINE XTP_CALENDAR_TIMELINE_VIEW_SCALE CXTPCalendarTLV_TimeScaleParams::GetScaleInterval() const {
	return m_scaleInterval;
}

AFX_INLINE int CXTPCalendarTLV_TimeScaleParams::GetScaleIntervalWidth_px() {
	return m_nScaleIntervalWidth_px;
}

AFX_INLINE COleDateTimeSpan CXTPCalendarTLV_TimeScaleParams::GetTimePerPixel()
{
	ASSERT(m_nScaleIntervalWidth_px > 0);
	COleDateTimeSpan spSInterval = GetScaleInterval();
	COleDateTimeSpan spTimePerPixel = (DATE)((double)GetScaleInterval() / max(m_nScaleIntervalWidth_px, 1));
	return spTimePerPixel;
}

AFX_INLINE int CXTPCalendarTLV_TimeScaleParams::GetTimeScaleParamsID() const {
	return m_nTimeScaleParamsID;
}

//AFX_INLINE BOOL CXTPCalendarTimeLineViewTimeScale::GetScrollBarInfoH(int& rnMaxPos_px, int& rnPage_px, int& rnStep_px)
//{
//  return FALSE;
//}

//============================================================================
#endif // (_XTPCALENDARTIMELINEVIEWTIMESCALE_H__)
