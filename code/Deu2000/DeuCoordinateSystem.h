#pragma once

#include <vector>
#include "Node.h"

namespace DeuCS
{
	class CNodeObj;
	typedef CNodeObj Name;
	typedef CNodeObj Remark;
	typedef CNodeObj Projection;
	typedef CNodeObj Long;
	typedef CNodeObj Lat;
	typedef CNodeObj Dimensions;
	typedef CNodeObj Label;
	typedef CNodeObj Abbreviation;
	typedef CNodeObj Per_Meter;
	typedef CNodeObj Per_Degree;
	typedef CNodeObj Units;
	typedef CNodeObj CSType;
	typedef CNodeObj InverseFlattening;
	typedef CNodeObj Value;
	typedef CNodeObj GeodeticPointor;

	class CNodeObj 
	{
	// Ù–‘
	public:
		CString get_Type();
		CString get_Name();

	public:
		CString m_strType;
		CString m_strName;
		CString m_strData;

	public:
		virtual	CNode* Obj2Node();
		virtual	CNodeObj* Node2Obj(CNode *);
	};

	class GeodeticPoint : public CNodeObj
	{
	public:
		DeuCS::Long		m_Long;
		DeuCS::Lat		m_Lat;

	public:
		virtual	CNode* Obj2Node();
		virtual	GeodeticPoint* Node2Obj(CNode *);
	};

	typedef GeodeticPoint MinPoint;
	typedef GeodeticPoint MaxPoint;

	class Envelope : public CNodeObj
	{
	public:
		DeuCS::Name					Name;
		DeuCS::Remark				Remark;
		DeuCS::MinPoint				m_MinPoint;
		DeuCS::MaxPoint				m_MaxPoint;

	public:		
		virtual	CNode* Obj2Node();
		virtual	CNodeObj* Node2Obj(CNode *);
	};

	class BaseUnitsAngular : public CNodeObj
	{
	public:
		DeuCS::Name					m_Name;
		DeuCS::Remark				m_Remark;
		DeuCS::Abbreviation			m_Abbreviation;
		DeuCS::Per_Degree			m_Per_Degree;

	public:		
		virtual	CNode* Obj2Node();
		virtual	CNodeObj* Node2Obj(CNode *);
	};

	class BaseUnitsLinear : public CNodeObj
	{
	public:
		DeuCS::Name					m_Name;
		DeuCS::Remark				m_Remark;
		DeuCS::Abbreviation			m_Abbreviation;
		DeuCS::Per_Meter			m_Per_Meter;

	public:
		virtual	CNode* Obj2Node();
		virtual	CNodeObj* Node2Obj(CNode *);
	};

	class East : public CNodeObj
	{
	public:
		DeuCS::Label					m_Label;
		DeuCS::BaseUnitsLinear			m_BaseUnits;

	public:
		virtual	CNode* Obj2Node();
		virtual	CNodeObj* Node2Obj(CNode *);
	};

	typedef East North ;
	typedef East EllipsoidHeight ;

	class Longitude : public CNodeObj
	{
	public:
		DeuCS::Label					m_Label;
		DeuCS::BaseUnitsAngular			m_BaseUnits;

	public:
		virtual	CNode* Obj2Node();
		virtual	CNodeObj* Node2Obj(CNode *);
	};

	typedef Longitude Latitude ;

	class ProjectPointStyle : public CNodeObj
	{
	public:
		ProjectPointStyle();
		virtual ~ProjectPointStyle();

	public:
		DeuCS::Name					m_Name;
		DeuCS::Remark				m_Remark;
		DeuCS::Dimensions			m_Dimensions;
		DeuCS::East					m_East;
		DeuCS::North				m_North;
		DeuCS::EllipsoidHeight		m_EllipH;

	public:
		virtual	CNode* Obj2Node();
		virtual	CNodeObj* Node2Obj(CNode *);
	};

	class GeodeticPointStyle : public CNodeObj
	{
	public:
		GeodeticPointStyle();
		virtual ~GeodeticPointStyle();

	public:
		DeuCS::Name					m_Name;
		DeuCS::Remark				m_Remark;
		DeuCS::Dimensions			m_Dimensions;
		DeuCS::Longitude			m_Long;
		DeuCS::Latitude				m_Lat;
		DeuCS::EllipsoidHeight		m_EllipH;

	public:
		virtual	CNode* Obj2Node();
		virtual	CNodeObj* Node2Obj(CNode *);
	};

	class Semi_Major_Axis : public CNodeObj
	{
	public:
		DeuCS::Value					m_Value;
		DeuCS::BaseUnitsLinear			m_BaseUnits;

	public:
		virtual	CNode* Obj2Node();
		virtual	CNodeObj* Node2Obj(CNode *);
	};

	typedef Semi_Major_Axis Semi_Minor_Axis;
	class Ellipsoid : public CNodeObj
	{
	public:
		DeuCS::Name					m_Name;
		DeuCS::Remark				m_Remark;	
		DeuCS::Semi_Major_Axis		m_Semi_Major_Axis;
		DeuCS::Semi_Minor_Axis		m_Semi_Minor_Axis;
		DeuCS::InverseFlattening	m_InverseFlattening;

	public:
		virtual	CNode* Obj2Node();
		virtual	CNodeObj* Node2Obj(CNode *);
	};

	class LongObj : public CNodeObj
	{
	public:
		DeuCS::Value					m_Value;
		DeuCS::BaseUnitsAngular			m_Units;

	public:
		virtual	CNode* Obj2Node();
		virtual	CNodeObj* Node2Obj(CNode *);
	};

	class PrimeMeridian : public CNodeObj
	{
	public:
		DeuCS::Name					m_Name;
		DeuCS::LongObj				m_LongObj;

	public:
		virtual	CNode* Obj2Node();
		virtual	CNodeObj* Node2Obj(CNode *);
	};

	class Datum : public CNodeObj
	{
	public:
		DeuCS::Name					m_Name;
		DeuCS::Remark				m_Remark;
		DeuCS::Ellipsoid			m_Ellipsoid;
		DeuCS::PrimeMeridian		m_PrimeMeridian;

	public:
		virtual	CNode* Obj2Node();
		virtual	CNodeObj* Node2Obj(CNode *);
	};

	class UnitsObj : public CNodeObj
	{
	public:
		DeuCS::Name				m_Name;
		DeuCS::Value			m_Value;
		DeuCS::Units			m_Units;

	public:
		virtual	CNode* Obj2Node();
		virtual	CNodeObj* Node2Obj(CNode *);
	};

	typedef UnitsObj CentralMeridian ;

	typedef UnitsObj FalseEasting ;

	typedef UnitsObj FalseNorthing ;

	typedef UnitsObj LatitudeOfOrigin ;

	typedef UnitsObj ScaleFactor ;

	class CDeuCoordinateSystem : public CNodeObj
	{
	public:
		CDeuCoordinateSystem(void);
		virtual	~CDeuCoordinateSystem(void);


	public:
		DeuCS::Name			m_Name;
		DeuCS::Remark		m_Remark;
		DeuCS::Envelope		m_Envelope;
		DeuCS::CSType		m_CSType;

	public:
		virtual	CNode* Obj2Node();
		virtual CNodeObj* Node2Obj(CNode *);
	};

	class CDeuGeodeticCS : public CDeuCoordinateSystem
	{
	public:
		CDeuGeodeticCS(void);
		virtual ~CDeuGeodeticCS(void);

		// Ù–‘
	public:
		DeuCS::GeodeticPointStyle	m_PointStyle;
		DeuCS::Datum				m_Datum;

	public:
		virtual	CNode* Obj2Node();
		virtual	CNodeObj* Node2Obj(CNode *);
	};

	class CDeuProjectCS : public CDeuCoordinateSystem
	{
	public:
		CDeuProjectCS(void);
		virtual ~CDeuProjectCS(void);

		// Ù–‘
	public:
		DeuCS::GeodeticPointor			m_GeodeticPointor;
		DeuCS::Projection				m_Projection;
		DeuCS::CentralMeridian			m_CM;
		DeuCS::FalseEasting				m_FalseEasting;
		DeuCS::FalseNorthing			m_FalseNorthing;
		DeuCS::LatitudeOfOrigin			m_LatitudeOfOrigin;
		DeuCS::ScaleFactor				m_ScaleFactor;
		DeuCS::ProjectPointStyle		m_PointStyle;

	public:
		virtual	CNode* Obj2Node();
		virtual	CNodeObj* Node2Obj(CNode *);
	};
}