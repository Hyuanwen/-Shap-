#pragma once

//#include "DeuGlobal.h"
//#import "../../dll/msxml6.dll"
#include "DeuXmlStruct.h"
#import <msxml6.dll>

namespace DeuXmlMapping
{
	class CDeuXmlReader
	{
	public:
		CDeuXmlReader(void);
		~CDeuXmlReader(void);

	protected:
		MSXML2::IXMLDOMDocumentPtr pDoc;
		MSXML2::IXMLDOMNodeListPtr p_Nodelist;
		
		//获取指定属性
		void GetAttrValue(MSXML2::IXMLDOMNodePtr &p_Node, LPCSTR sz_name, CString *strOutput);

		//获取指定节点包含的文本
		void GetElemText(MSXML2::IXMLDOMNodePtr &p_Node, CString *strOutput);

	public:
		//加载xml		
		void LoadXml(LPCSTR sz_FileName);  //自动寻找默认的路径加载	
		bool LoadFile(LPCSTR sz_FileName); //传入完整路径加载

		void Free();
		//删除注释
		void RemoveComment(MSXML2::IXMLDOMNodePtr &pCurrNode);

		//清除结构
		void ReleaseGeoDataMapping(p_GeoDataXml pGeoDataXml);

		//填充映射结构
		void MappingGeoData(p_GeoDataXml pGeoDataXml);
		void AppendMappingGeoData(p_GeoDataXml pGeoDataXml, CString strPathFile);//追加映射
		void MappingGustomData(p_GeoDataXml pGeoDataXml);

		//获取系统大地坐标
		void GetAllGeoDetic(_Geodetic* pGeodetic);

		//void AppendGetAllGeoDetic(_Geodetic* pGeodetic);

		//获取系统投影坐标
		void GetAllProjected(Projected* pProjected);
		//获取系统单位
		void GetUnits(_Units* pUnits);

		//获取用户自定义大地坐标
		void GetCustomGeoDetic(_Geodetic* pGeodetic);
		//获取用户自定义投影坐标
		void GetCustomProjected(Projected* pProjected);

		//填充投影坐标元素节点
		void FillProjectedBeking54(int nIndex, _ProjectedSeries* _pProjectedSeries);
		void FillProjectedXiAn80(int nIndex, _ProjectedSeries* _pProjectedSeries);
		void FillProjectedWGS84(int nIndex, _ProjectedSeries* _pProjectedSeries);
		void FillProjectedCGCS2000(int nIndex, _ProjectedSeries* _pProjectedSeries);
		
		//填充大地坐标元素节点
		void FillGeoDeticBeking54(int nIndex, _GeodeticSeries* p54);
		void FillGeoDeticXiAn80(int nIndex, _GeodeticSeries* p80);
		void FillGeoDeticWGS84(int nIndex, _GeodeticSeries* pWGS84);
		void FillGeoDeticCGCS2000(int nIndex, _GeodeticSeries* p2000);

		void FillUnit(MSXML2::IXMLDOMNodePtr &pCurrNode, _Unit* pUnit);
		
		//如下为基础嵌套结构的填充
		void FillName(MSXML2::IXMLDOMNodePtr &pCurrNode, _Name* _name);
		void FillRemark(MSXML2::IXMLDOMNodePtr &pCurrNode, _Remark* remark);
		void FillCSType(MSXML2::IXMLDOMNodePtr &pCurrNode, _CSType* csType);
		void FillLabel(MSXML2::IXMLDOMNodePtr &pCurrNode, _Label* label);
		void FillValueStyle(MSXML2::IXMLDOMNodePtr &pCurrNode, _Value* _value);

		void FillMinPoint(MSXML2::IXMLDOMNodePtr &pCurrNode, _MinPoint* _minPoint);
		void FillMaxPoint(MSXML2::IXMLDOMNodePtr &pCurrNode, _MaxPoint* _maxPoint);
		
		void FillEnvelope(MSXML2::IXMLDOMNodePtr &pCurrNode, _Envelope* _envelope);

		void FillLong(MSXML2::IXMLDOMNodePtr &pCurrNode, _Long* _long);
		
		void FillLat(MSXML2::IXMLDOMNodePtr &pCurrNode, _Lat* _lat);
		void FillDimensions(MSXML2::IXMLDOMNodePtr &pCurrNode, _Dimensions* _dimensions);
		void FillAbbreviation(MSXML2::IXMLDOMNodePtr &pCurrNode, _Abbreviation* _abbreviation);
		void FillPer_Meter(MSXML2::IXMLDOMNodePtr &pCurrNode, _Per_Meter* _per_Meter);
		void FillPer_Degree(MSXML2::IXMLDOMNodePtr &pCurrNode, _Per_Degree* _per_Degree);

		void Fill_Unit_1_Struct(MSXML2::IXMLDOMNodePtr &pCurrNode, _Unit_1* _unit_1);
		void Fill_Unit_2_Struct(MSXML2::IXMLDOMNodePtr &pCurrNode, _Unit_2* _unit_2);

		void Fill_GeoDeticLong(MSXML2::IXMLDOMNodePtr &pCurrNode, _GeoDeticLong* _geoDeticLong);
		void Fill_GeoDeticLat(MSXML2::IXMLDOMNodePtr &pCurrNode, _GeoDeticLat* _geoDeticLat);

		void Fill_GeoDeticLatForPs(MSXML2::IXMLDOMNodePtr &pCurrNode, _GeoDeticLatForPS* _geoDeticLat);
		void Fill_GeoDeticLongForPs(MSXML2::IXMLDOMNodePtr &pCurrNode, _GeoDeticLongForPS* _geoDeticLong);

		void FillEast(MSXML2::IXMLDOMNodePtr &pCurrNode, _East* _east);
		void FillNorth(MSXML2::IXMLDOMNodePtr &pCurrNode, _North* _north);
		void FillEllipsoidHeight(MSXML2::IXMLDOMNodePtr &pCurrNode, _EllipsoidHeight* _ellipsoidHeight);

		void FillGeoDeticPointStyle(MSXML2::IXMLDOMNodePtr &pCurrNode, _GeoDeticPointStyle* _geoDeticPointStyle);
		void FillProjectionPointStyle(MSXML2::IXMLDOMNodePtr &pCurrNode, _ProjectionPointStyle* _projectionPointStyle);

		void FillCentralMeridian(MSXML2::IXMLDOMNodePtr &pCurrNode, _CentralMeridian* _centralMeridian);
		void FillFalseEasting(MSXML2::IXMLDOMNodePtr &pCurrNode, _FalseEasting* _falseEasting);
		void FillFalseNorthing(MSXML2::IXMLDOMNodePtr &pCurrNode, _FalseNorthing* _falseNorthing);
		void FillLatitudeOfOrigin(MSXML2::IXMLDOMNodePtr &pCurrNode, _LatitudeOfOrigin* _latitudeOfOrigin);
		void FillScaleFactor(MSXML2::IXMLDOMNodePtr &pCurrNode, _ScaleFactor* _scaleFactor);

		void FillSemi_Minor_Axis(MSXML2::IXMLDOMNodePtr &pCurrNode, _Semi_Minor_Axis* _semi_Minor_Axis);
		void FillSemi_Major_Axis(MSXML2::IXMLDOMNodePtr &pCurrNode, _Semi_Major_Axis* _semi_Major_Axis);
		void FillInverseFlattening(MSXML2::IXMLDOMNodePtr &pCurrNode, _InverseFlattening* _inverseFlattening);

		void FillEllipsoid(MSXML2::IXMLDOMNodePtr &pCurrNode, _Ellipsoid* _ellipsoid);
		void FillPrimeMeridian(MSXML2::IXMLDOMNodePtr &pCurrNode, _PrimeMeridian* _primeMeridian);
		void FillDatum(MSXML2::IXMLDOMNodePtr &pCurrNode, _Datum* _datum);

		void FillProjection(MSXML2::IXMLDOMNodePtr &pCurrNode, _Projection* _projection);
		void FillGeodeticPointor(MSXML2::IXMLDOMNodePtr &pCurrNode, _GeodeticPointor* _geodeticPointor);

		void GetControlPoint(p_ControlPointPairs m_pCP);
		void FillChildPoint(MSXML2::IXMLDOMNodePtr &pCurrNode, p_ControlPointPair pControlPointPair);
		
		//==============================处理TaskInfoXml=====================
		void MappingTasks(p_Tasks pTasks);
		void FillTask(MSXML2::IXMLDOMNodePtr &pCurrNode, p_Task pTask);
		void ReleseTaskMapping(p_Tasks pTasks);

		void ReadFormat(_StrFormatList& Tasks);
		void GetFormat(MSXML2::IXMLDOMNodePtr &pCurrNode, _StrFormatTypeList* pTask);
	};

}
