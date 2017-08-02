#include "stdafx.h"
#include "DeuTranslate.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDeuEllipse::CDeuEllipse()
{
	m_strEllipName = _T("");	//椭球名称
	m_SemiMajor = 0;			//椭球长半轴半径
	m_SemiMinor = 0;			//椭球短半轴半径
	m_Flatening = 0;			//椭球扁率倒数
	m_strProjectName = _T("");	//投影名称
	m_strProjectType = _T("");	//种类
	m_CentrolLong = 0;			//中央子午线经度
	m_We = _T("");				//中央子午线经度
	m_OriginalLat = 0;			//原点所在的纬度
	m_Ns = _T("");				//原点所在的纬度
	m_FalseN = 0;				//北坐标假值
	m_FalseE = 0;				//东坐标假值
	m_BLScale = 0;				//中央子午线/原点纬度比例因子
	m_SLat = 0;					//南标准纬线
	m_NLat = 0;					//北标准纬线
}

CDeuEllipse::~CDeuEllipse()
{
}

void CDeuEllipse::get_Ellip_Name(CString& strEllipName) const
{
	strEllipName = m_strEllipName;
}

void CDeuEllipse::putref_Ellip_Name(const CString& newEllipName)
{
	m_strEllipName = newEllipName;
}

void CDeuEllipse::get_Major(double& MajorVal) const
{
	MajorVal = m_SemiMajor;
}

void CDeuEllipse::putref_Major(double newVal)
{
	m_SemiMajor = newVal;
}

void CDeuEllipse::get_Minor(double& MinorVal) const
{
	MinorVal = m_SemiMinor;
}

void CDeuEllipse::putref_Minor(double newVal)
{
	m_SemiMinor = newVal;
}

void  CDeuEllipse::get_Flatening(double& FlatenVal) const
{
	FlatenVal = m_Flatening;
}

void CDeuEllipse::putref_Flatening(double newVal)
{
	m_Flatening = newVal;
}

void CDeuEllipse::get_Prj_Name(CString& strPrjName) const
{
	strPrjName = m_strProjectName;
}

void CDeuEllipse::putref_Prj_Name(const CString& newPrjName)
{
	m_strProjectName = newPrjName;
}

void CDeuEllipse::get_Prj_Type(CString& strPrjType) const
{
	strPrjType = m_strProjectType;
}

void CDeuEllipse::putref_Prj_Type(const CString& newVal)
{
	m_strProjectType = newVal;
}

void CDeuEllipse::get_Centrol_Long(double& Val) const
{
	Val = m_CentrolLong;
}

void CDeuEllipse::putref_Centrol_Long(double newVal)
{
	m_CentrolLong = newVal;
}

void CDeuEllipse::get_We(CString& Val) const
{
	Val = m_We;
}

void CDeuEllipse::putref_We(const CString& newVal)
{
	m_We = newVal;
}

void CDeuEllipse::get_Original_Lat(double& Val) const
{
	Val = m_OriginalLat;
}

void CDeuEllipse::putref_Original_Lat(DOUBLE newVal)
{
	m_OriginalLat = newVal;
}

void CDeuEllipse::get_Ns(CString& Val) const
{
	Val = m_Ns;
}

void CDeuEllipse::putref_Ns(const CString& newVal)
{
	m_Ns = newVal;
}

void CDeuEllipse::get_False_N(double& Val) const
{
	Val = m_FalseN;
}

void CDeuEllipse::putref_False_N(double newVal)
{
	m_FalseN = newVal;
}

void CDeuEllipse::get_False_E(double& Val) const
{
	Val = m_FalseE;
}

void CDeuEllipse::putref_False_E(double newVal)
{
	m_FalseE = newVal;
}

void CDeuEllipse::get_BL_scale(double& Val) const
{
	Val = m_BLScale;
}

void CDeuEllipse::putref_BL_scale(double newVal)
{
	m_BLScale = newVal;
}

void CDeuEllipse::get_S_Lat(double& Val) const
{
	Val = m_SLat;
}

void CDeuEllipse::putref_S_Lat(double newVal)
{
	m_SLat = newVal;
}

void CDeuEllipse::get_N_Lat(double& Val) const
{
	Val = m_NLat;
}

void CDeuEllipse::putref_N_Lat(double newVal)
{
	m_NLat = newVal;
}