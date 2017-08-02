#include "stdafx.h"
#include "DeuTranslate.h"

CDeuCoordType::CDeuCoordType()
{
	m_iCoordType = 0;
	m_CtrlPt_CoordType = 0;
	m_out_CoordType = 0;
}

CDeuCoordType::~CDeuCoordType()
{

}

void CDeuCoordType::get_CoordType(short& Val) const
{
	Val = m_iCoordType;
}

void CDeuCoordType::putref_CoordType(short newVal)
{
	m_iCoordType = newVal;
}

void CDeuCoordType::get_DestCoordType(short& Val) const
{
	Val = m_out_CoordType;
}

void CDeuCoordType::putref_DestCoordType(short newVal)
{
	m_out_CoordType = newVal;
}

void CDeuCoordType::get_CtrlPtCoordType(short& Val) const
{
	Val = m_CtrlPt_CoordType;
}

void CDeuCoordType::putref_CtrlPtCoordType(short newVal)
{
	m_CtrlPt_CoordType = newVal;
}