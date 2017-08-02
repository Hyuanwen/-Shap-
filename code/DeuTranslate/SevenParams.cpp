#include "stdafx.h"
#include "DeuTranslate.h"

CSevenParams::CSevenParams()
{
	m_dx = 0;
	m_dy = 0;
	m_dz = 0;
	m_rx = 0;
	m_ry = 0;
	m_rz = 0;
	m_ScalM = 0;
}

CSevenParams::~CSevenParams()
{

}

void CSevenParams::get_DX(double& Val) const
{
	Val = m_dx;
}

void CSevenParams::putref_DX(double newVal)
{
	m_dx = newVal;
}

void CSevenParams::get_DY(double& Val) const
{
	Val = m_dy;
}

void CSevenParams::putref_DY(double newVal)
{
	m_dy = newVal;
}

void CSevenParams::get_DZ(double& Val) const
{
	Val = m_dz;
}

void CSevenParams::putref_DZ(double newVal)
{
	m_dz = newVal;
}

void CSevenParams::get_RX(double& Val) const
{
	Val = m_rx;
}

void CSevenParams::putref_RX(double newVal)
{
	m_rx = newVal;
}

void CSevenParams::get_RY(double& Val) const
{
	Val = m_ry;
}

void CSevenParams::putref_RY(double newVal)
{
	m_ry = newVal;
}

void CSevenParams::get_RZ(double& Val) const
{
	Val = m_rz;
}

void CSevenParams::putref_RZ(double newVal)
{
	m_rz = newVal;
}

void CSevenParams::get_ScalM(double& Val) const
{
	Val = m_ScalM;
}

void CSevenParams::putref_ScalM(double newVal)
{
	m_ScalM = newVal;
}
