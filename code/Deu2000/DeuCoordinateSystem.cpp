#include "StdAfx.h"
#include "DeuCoordinateSystem.h"
#include "DeuGlobal.h"

IFFUNC(tag_name);
using namespace std;
typedef  std::list <CNode*> ::iterator   T_It;
#define FIND_NODE_IF(l,n) \
	*std::find_if(l.begin(),l.end(),IFFunctor_tag_name<CNode*,CString>(n));

namespace DeuCS
{
	CDeuCoordinateSystem::CDeuCoordinateSystem(void)
	{
	}

	CDeuCoordinateSystem::~CDeuCoordinateSystem(void)
	{
		return ;
	}

	CString CNodeObj::get_Name()
	{
		return m_strName;
	}

	CString CNodeObj::get_Type()
	{
		return m_strType;
	}

	CNode* CNodeObj::Obj2Node()
	{
		CNode * node = new CNode;

		node->tag_name = m_strType;
		node->ele_name = m_strName;

		return node;
	}

	CNodeObj* CNodeObj::Node2Obj(CNode * node)
	{
		m_strType = node->tag_name;
		m_strName = node->ele_name;
		m_strData = node->data;

		return this;
	}

	CNode* GeodeticPoint::Obj2Node()
	{
		CNode * node = new CNode;

		node->tag_name = m_strType;
		node->ele_name = m_strName;

		CNode * sub1 = m_Long.Obj2Node();
		node->_sub_nodes.push_back(sub1);

		CNode * sub2 = m_Lat.Obj2Node();
		node->_sub_nodes.push_back(sub2);

		return node;
	}

	GeodeticPoint* GeodeticPoint::Node2Obj(CNode * node)
	{
		m_strType = node->tag_name;
		m_strName = node->ele_name;

		CNode * node_Long = FIND_NODE_IF(node->_sub_nodes,SLONG);
		m_Long.Node2Obj(node_Long);

		CNode * node_Lat = FIND_NODE_IF(node->_sub_nodes,SLAT);
		m_Lat.Node2Obj(node_Lat);

		return this;
	}

	CNode* Envelope::Obj2Node()
	{
		CNode * node = new CNode;
		return node;
	}

	CNodeObj* Envelope::Node2Obj(CNode * node)
	{
		m_strType = node->tag_name;
		m_strName = node->ele_name;

		CNode * node_MinPoint = FIND_NODE_IF(node->_sub_nodes,MINPOINT);
		m_MinPoint.Node2Obj(node_MinPoint);

		CNode * node_MaxPoint = FIND_NODE_IF(node->_sub_nodes,MAXPOINT);
		m_MaxPoint.Node2Obj(node_MaxPoint);

		return this;
	}

	CNode* BaseUnitsLinear::Obj2Node()
	{
		return NULL;
	}

	CNodeObj* BaseUnitsLinear::Node2Obj(CNode * node)
	{
		m_strType = node->tag_name;
		m_strName = node->ele_name;

		CNode * node_ABBREVIATION = FIND_NODE_IF(node->_sub_nodes,ABBREVIATION);
		m_Abbreviation.Node2Obj(node_ABBREVIATION);

		CNode * node_PER_METER = FIND_NODE_IF(node->_sub_nodes,PER_METER);
		m_Per_Meter.Node2Obj(node_PER_METER);

		return this;
	}
	
	CNode* BaseUnitsAngular::Obj2Node()
	{
		return NULL;
	}

	CNodeObj* BaseUnitsAngular::Node2Obj(CNode * node)
	{
		m_strType = node->tag_name;

		m_strName = node->ele_name;

		CNode * node_ABBREVIATION = FIND_NODE_IF(node->_sub_nodes,ABBREVIATION);
		m_Abbreviation.Node2Obj(node_ABBREVIATION);


		CNode * node_Per_Degree = FIND_NODE_IF(node->_sub_nodes,PER_DEGREE);
		m_Per_Degree.Node2Obj(node_Per_Degree);

		return this;
	}

	CNode* East::Obj2Node()
	{
		return NULL;
	}

	CNodeObj* East::Node2Obj(CNode * node)
	{
		m_strType = node->tag_name;
		m_strName = node->ele_name;

		CNode * node_Label = FIND_NODE_IF(node->_sub_nodes,LABEL);
		m_Label.Node2Obj(node_Label);

		CNode * node_BaseUnits = FIND_NODE_IF(node->_sub_nodes,BASEUNITS);
		m_BaseUnits.Node2Obj(node_BaseUnits);

		return this;
	}

	CNode* Longitude::Obj2Node()
	{
		return NULL;
	}

	CNodeObj* Longitude::Node2Obj(CNode * node)
	{
		m_strType = node->tag_name;
		m_strName = node->ele_name;

		CNode * node_Label = FIND_NODE_IF(node->_sub_nodes,LABEL);
		m_Label.Node2Obj(node_Label);

		CNode * node_BaseUnits = FIND_NODE_IF(node->_sub_nodes,BASEUNITS);
		m_BaseUnits.Node2Obj(node_BaseUnits);

		return this;
	}
	
	ProjectPointStyle::ProjectPointStyle()
	{
		return ;
	}

	ProjectPointStyle::~ProjectPointStyle()
	{
		return ;
	}

	CNode* ProjectPointStyle::Obj2Node()
	{
		return NULL;
	}

	CNodeObj* ProjectPointStyle::Node2Obj(CNode * node)
	{
		m_strType = node->tag_name;
		m_strName = node->ele_name;

		CNode * node_Name = FIND_NODE_IF(node->_sub_nodes,NAME);
		m_Name.Node2Obj(node_Name);

		CNode * node_Remark = FIND_NODE_IF(node->_sub_nodes,REMARK);
		m_Remark.Node2Obj(node_Remark);

		CNode * node_Dimensions = FIND_NODE_IF(node->_sub_nodes,DIM);
		m_Dimensions.Node2Obj(node_Dimensions);

		CNode * node_East = FIND_NODE_IF(node->_sub_nodes,EAST);
		m_East.Node2Obj(node_East);

		CNode * node_North = FIND_NODE_IF(node->_sub_nodes,NORTH);
		m_North.Node2Obj(node_North);

		CNode * node_EllipH = FIND_NODE_IF(node->_sub_nodes,ELLIPSOIDHEIGHT);
		m_EllipH.Node2Obj(node_EllipH);

		return this;
	}
	
	GeodeticPointStyle::GeodeticPointStyle()
	{
	}

	GeodeticPointStyle::~GeodeticPointStyle()
	{
		return ;
	}

	CNode* GeodeticPointStyle::Obj2Node()
	{
		return NULL;
	}

	CNodeObj* GeodeticPointStyle::Node2Obj(CNode * node)
	{
		m_strType = node->tag_name;
		m_strName = node->ele_name;

		CNode * node_Name = FIND_NODE_IF(node->_sub_nodes,NAME);
		m_Name.Node2Obj(node_Name);

		CNode * node_Remark = FIND_NODE_IF(node->_sub_nodes,REMARK);
		m_Remark.Node2Obj(node_Remark);

		CNode * node_Dimensions = FIND_NODE_IF(node->_sub_nodes,DIM);
		m_Dimensions.Node2Obj(node_Dimensions);

		CNode * node_Long = FIND_NODE_IF(node->_sub_nodes,SLONG);
		m_Long.Node2Obj(node_Long);

		CNode * node_Lat = FIND_NODE_IF(node->_sub_nodes,SLAT);
		m_Lat.Node2Obj(node_Lat);

		CNode * node_EllipH = FIND_NODE_IF(node->_sub_nodes,ELLIPSOIDHEIGHT);
		m_EllipH.Node2Obj(node_EllipH);

		return this;
	}

	CNode*  Semi_Major_Axis::Obj2Node()
	{
		return NULL;
	}

	CNodeObj* Semi_Major_Axis::Node2Obj(CNode * node)
	{
		m_strType = node->tag_name;
		m_strName = node->ele_name;

		CNode * node_Value = FIND_NODE_IF(node->_sub_nodes,VALUE);
		m_Value.Node2Obj(node_Value);

		CNode * node_BaseUnits = FIND_NODE_IF(node->_sub_nodes,BASEUNITS);
		m_BaseUnits.Node2Obj(node_BaseUnits);

		return this;
	}

	CNode*  Ellipsoid::Obj2Node()
	{
		return NULL;
	}

	CNodeObj* Ellipsoid::Node2Obj(CNode * node)
	{
		m_strType = node->tag_name;
		m_strName = node->ele_name;

		CNode * node_Name = FIND_NODE_IF(node->_sub_nodes,NAME);
		m_Name.Node2Obj(node_Name);

		CNode * node_Remark = FIND_NODE_IF(node->_sub_nodes,REMARK);
		m_Remark.Node2Obj(node_Remark);

		CNode * node_Major = FIND_NODE_IF(node->_sub_nodes,MAJOR);
		m_Semi_Major_Axis.Node2Obj(node_Major);

		CNode * node_Minor = FIND_NODE_IF(node->_sub_nodes,MINOR);
		m_Semi_Minor_Axis.Node2Obj(node_Minor);

		CNode * node_InverseFlattening = FIND_NODE_IF(node->_sub_nodes,INVERSEFLATTENING);
		m_InverseFlattening.Node2Obj(node_InverseFlattening);

		return this;
	}

	CNode*  LongObj::Obj2Node()
	{
		return NULL;
	}

	CNodeObj* LongObj::Node2Obj(CNode * node)
	{
		m_strType = node->tag_name;
		//
		//	m_strName = node->ele_name;
		//
		//	CNode * node_Name = FIND_NODE_IF(node->_sub_nodes,NAME);
		//	m_Name.Node2Obj(node_Name);
		//
		//	CNode * node_Units = FIND_NODE_IF(node->_sub_nodes,BASEUNITS);
		//	m_Units.Node2Obj(node_Units);
		//
		//	return this;
		//}

		m_strName = node->ele_name;

		CNode * node_Value = FIND_NODE_IF(node->_sub_nodes,VALUE);
		m_Value.Node2Obj(node_Value);

		CNode * node_Units = FIND_NODE_IF(node->_sub_nodes,BASEUNITS);
		m_Units.Node2Obj(node_Units);

		return this;
	}

	CNode* PrimeMeridian::Obj2Node()
	{
		return NULL;
	}

	CNodeObj* PrimeMeridian::Node2Obj(CNode * node)
	{
		m_strType = node->tag_name;

		m_strName = node->ele_name;

		CNode * node_Name = FIND_NODE_IF(node->_sub_nodes,NAME);
		m_Name.Node2Obj(node_Name);

		CNode * node_LongObj = FIND_NODE_IF(node->_sub_nodes,SLONG);
		m_LongObj.Node2Obj(node_LongObj);

		return this;
	}

	CNode* Datum::Obj2Node()
	{
		return NULL;
	}

	CNodeObj* Datum::Node2Obj(CNode * node)
	{
		m_strType = node->tag_name;
		m_strName = node->ele_name;

		CNode * node_Name = FIND_NODE_IF(node->_sub_nodes,NAME);
		m_Name.Node2Obj(node_Name);

		CNode * node_Remark = FIND_NODE_IF(node->_sub_nodes,REMARK);
		m_Remark.Node2Obj(node_Remark);

		CNode * node_Ellipsoid = FIND_NODE_IF(node->_sub_nodes,ELLIPSOID);
		m_Ellipsoid.Node2Obj(node_Ellipsoid);

		CNode * node_PrimeMeridian = FIND_NODE_IF(node->_sub_nodes,PRIMEMERIDIAN);
		m_PrimeMeridian.Node2Obj(node_PrimeMeridian);

		return this;
	}

	CNode* UnitsObj::Obj2Node()
	{
		return NULL;
	}

	CNodeObj* UnitsObj::Node2Obj(CNode * node)
	{
		m_strType = node->tag_name;

		m_strName = node->ele_name;

		CNode * node_Name = FIND_NODE_IF(node->_sub_nodes,NAME);
		m_Name.Node2Obj(node_Name);

		CNode * node_Value = FIND_NODE_IF(node->_sub_nodes,VALUE);
		m_Value.Node2Obj(node_Value);

		CNode * node_Units = FIND_NODE_IF(node->_sub_nodes,UNITS);
		m_Units.Node2Obj(node_Units);

		return this;
	}

	CNode* CDeuCoordinateSystem::Obj2Node()
	{
		return NULL;
	}

	CNodeObj* CDeuCoordinateSystem::Node2Obj(CNode * node)
	{
		m_strType = node->tag_name;

		m_strName = node->ele_name;

		CNode * node_Name = FIND_NODE_IF(node->_sub_nodes,NAME);
		m_Name.Node2Obj(node_Name);

		CNode * node_Remark = FIND_NODE_IF(node->_sub_nodes,REMARK);
		m_Remark.Node2Obj(node_Remark);

		CNode * node_Envelope = FIND_NODE_IF(node->_sub_nodes,ENVELOPE);
		m_Envelope.Node2Obj(node_Envelope);

		CNode * node_CSType = FIND_NODE_IF(node->_sub_nodes,CSTYPE);
		m_CSType.Node2Obj(node_CSType);

		return this;
	}

	CDeuGeodeticCS::CDeuGeodeticCS()
	{

	}

	CDeuGeodeticCS::~CDeuGeodeticCS()
	{
		return ;
	}

	CNode* CDeuGeodeticCS::Obj2Node()
	{
		return NULL;
	}

	CNodeObj* CDeuGeodeticCS::Node2Obj(CNode * node)
	{
		CDeuCoordinateSystem::Node2Obj(node);

		CNode * node_Datum = FIND_NODE_IF(node->_sub_nodes,DATUM);
		m_Datum.Node2Obj(node_Datum);

		CNode * node_PointStyle = FIND_NODE_IF(node->_sub_nodes,POINTSTYLE);
		m_PointStyle.Node2Obj(node_PointStyle);
		return this;
	}

	CDeuProjectCS::CDeuProjectCS()
	{

	}

	CDeuProjectCS::~CDeuProjectCS()
	{
		return ;
	}

	CNode* CDeuProjectCS::Obj2Node()
	{
		return NULL;
	}

	CNodeObj* CDeuProjectCS::Node2Obj(CNode * node)
	{
		CDeuCoordinateSystem::Node2Obj(node);

		CNode * node_GeodeticPointor = FIND_NODE_IF(node->_sub_nodes,GEODETICPOINTOR);
		m_GeodeticPointor.Node2Obj(node_GeodeticPointor);

		CNode * node_Projection = FIND_NODE_IF(node->_sub_nodes,PROJECTION);
		m_Projection.Node2Obj(node_Projection);

		CNode * node_CM = FIND_NODE_IF(node->_sub_nodes,CENTRALMERIDIAN);
		m_CM.Node2Obj(node_CM);

		CNode * node_FalseEasting = FIND_NODE_IF(node->_sub_nodes,FALSEEASTING);
		m_FalseEasting.Node2Obj(node_FalseEasting);

		CNode * node_FalseNorthing = FIND_NODE_IF(node->_sub_nodes,FALSENORTHING);
		m_FalseNorthing.Node2Obj(node_FalseNorthing);

		CNode * node_LatitudeOfOrigin = FIND_NODE_IF(node->_sub_nodes,LATITUDEOFORIGIN);
		m_LatitudeOfOrigin.Node2Obj(node_LatitudeOfOrigin);

		CNode * node_ScaleFactor = FIND_NODE_IF(node->_sub_nodes,SCALEFACTOR);
		m_ScaleFactor.Node2Obj(node_ScaleFactor);

		CNode * node_PointStyle = FIND_NODE_IF(node->_sub_nodes,POINTSTYLE);
		m_PointStyle.Node2Obj(node_PointStyle);
		return this;
	}
}
