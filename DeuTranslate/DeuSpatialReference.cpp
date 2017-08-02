#include "stdafx.h"
#include "DeuTranslate.h"

CDeuSpatialReference::CDeuSpatialReference()
{
	//m_ProjParm.clear();
	m_ProjParm = NULL;
	m_ProjCount = 0;
	m_Project = _T("");
	m_Datum = _T("");
	m_LinearUnit = _T("");
	m_AngularUnit = _T("");
	m_PrimeMeridian = _T("");
	m_BIsProject = FALSE;
	m_ProjCSName = _T("");
	m_GeogName = _T("");
}

CDeuSpatialReference::~CDeuSpatialReference()
{

}

//void CDeuSpatialReference::get_ProjParm(int&  ncount, std::vector<double>& parm) const
//{
//	ncount = m_ProjCount;
//	parm.assign(m_ProjParm.begin(), m_ProjParm.end());
//}
//
//void CDeuSpatialReference::putref_ProjParm(int ncount, const std::vector<double>& newParm)
//{
//	m_ProjCount = ncount;
//	m_ProjParm.assign(newParm.begin(), newParm.end());
//}

void CDeuSpatialReference::get_ProjParm(int&  ncount, double** parm) const
{
	ncount = m_ProjCount;
	*parm = m_ProjParm;
}

void CDeuSpatialReference::putref_ProjParm(int ncount, double* newParm)
{
	m_ProjCount = ncount;
	//m_ProjParm = newParm;

	if (m_ProjParm != NULL)
	{
		delete m_ProjParm;
	}

	m_ProjParm = new double[m_ProjCount];
	memcpy(m_ProjParm, newParm, sizeof(double)*m_ProjCount);
}

void CDeuSpatialReference::get_Projection(CString& Val) const
{
	Val = m_Project;
}

void CDeuSpatialReference::put_Projection(const CString& newVal)
{
	m_Project = newVal;
}

void CDeuSpatialReference::get_Datum(CString& Val) const
{
	Val = m_Datum;
}

void CDeuSpatialReference::put_Datum(const CString& newVal)
{
	m_Datum = newVal;
}

void CDeuSpatialReference::get_LinearUnit(CString& Val) const
{
	Val = m_LinearUnit;
}

void CDeuSpatialReference::put_LinearUnit(const CString& newVal)
{
	m_LinearUnit = newVal;
}

void CDeuSpatialReference::get_AngularUnit(CString& Val) const
{
	Val = m_AngularUnit;	
}

void CDeuSpatialReference::put_AngularUnit(const CString& newVal)
{
	m_AngularUnit = newVal;
}

void CDeuSpatialReference::get_PrimeMeridian(CString& Val) const
{
	Val = m_PrimeMeridian;
}

void CDeuSpatialReference::put_PrimeMeridian(const CString& newVal)
{
	m_PrimeMeridian = newVal;
}

void CDeuSpatialReference::get_IsProject(BOOL& Val) const
{
	Val = m_BIsProject;
}

void CDeuSpatialReference::put_IsProject(BOOL newVal)
{
	m_BIsProject = newVal;
}

void CDeuSpatialReference::get_ProjeCS(CString& Val) const
{
	Val = m_ProjCSName;
}

void CDeuSpatialReference::put_ProjeCS(const CString& newVal)
{
	m_ProjCSName = newVal;
}

void CDeuSpatialReference::get_GeogCS(CString& GeogName, CString& Datum, CString& EllipName, double& SemiMajor, double& InvFlattening) const
{
	GeogName = m_GeogName;
	Datum = m_Datum;
	m_Ellipse.get_Ellip_Name(EllipName);
	m_Ellipse.get_Major(SemiMajor);
	m_Ellipse.get_Flatening(InvFlattening);
}

void CDeuSpatialReference::put_GeogCS(const CString& GeogName, const CString& Datum, const CString& EllipName, double SemiMajor, double InvFlattening)
{
	m_GeogName = GeogName;
	m_Datum = Datum;
	m_Ellipse.putref_Ellip_Name(EllipName);
	m_Ellipse.putref_Major(SemiMajor);
	m_Ellipse.putref_Flatening(InvFlattening);
}