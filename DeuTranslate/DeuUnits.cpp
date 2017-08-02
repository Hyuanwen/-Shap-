#include "stdafx.h"
#include "DeuTranslate.h"
#include "DeuDef.h"

CDeuUnits::CDeuUnits()
{
	m_sUnit_x = _T("");
	m_sUnit_y = _T("");
	m_sUnit_Z = _T("");
	m_sUnit_des_x = _T("");
	m_sUnit_des_y = _T("");
	m_sUnit_des_z = _T("");
	m_unit_type = _T("");
}

CDeuUnits::~CDeuUnits()
{

}

void CDeuUnits::get_UnitType(CString& Val) const
{
	Val = m_unit_type;
}

void CDeuUnits::putref_UnitType(const CString& newVal)
{
	m_unit_type = newVal;
}

double CDeuUnits::TypeToUnit(double oriX, const CString& strType)
{
	if (strType != "M")
	{
		return oriX*DEG_TO_RAD;
	}
	else
	{
		return oriX;
	}
}

double CDeuUnits::UnitToType(double oriX, const CString& strType)
{
	if (strType != "M")
	{
		return oriX*RAD_TO_DEG;
	}
	else
	{
		return oriX;
	}
}

void CDeuUnits::get_Unit_X(CString& Val) const
{
	Val = m_sUnit_x;
}

void CDeuUnits::put_Unit_X(const CString& newVal)
{
	m_sUnit_x = newVal;
}

void CDeuUnits::get_Unit_Y(CString& Val) const
{
	Val = m_sUnit_y;
}

void CDeuUnits::put_Unit_Y(const CString& newVal)
{
	m_sUnit_y = newVal;
}

void CDeuUnits::get_Unit_Z(CString& Val) const
{
	Val = m_sUnit_Z;
}

void CDeuUnits::put_Unit_Z(const CString& newVal)
{
	m_sUnit_Z = newVal;
}

void CDeuUnits::get_Unit_desX(CString& Val) const
{
	Val = m_sUnit_des_x;
}

void CDeuUnits::put_Unit_desX(const CString& newVal)
{
	m_sUnit_des_x = newVal;
}

void CDeuUnits::get_Unit_desY(CString& Val) const
{
	Val = m_sUnit_des_y;
}

void CDeuUnits::put_Unit_desY(const CString& newVal)
{
	m_sUnit_des_y = newVal;
}

void CDeuUnits::get_Unit_desZ(CString& Val) const
{
	Val = m_sUnit_des_z;
}

void CDeuUnits::put_Unit_desZ(const CString& newVal)
{
	m_sUnit_des_z = newVal;
}