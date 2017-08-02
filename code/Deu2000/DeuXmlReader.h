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
		
		//��ȡָ������
		void GetAttrValue(MSXML2::IXMLDOMNodePtr &p_Node, LPCSTR sz_name, CString *strOutput);

		//��ȡָ���ڵ�������ı�
		void GetElemText(MSXML2::IXMLDOMNodePtr &p_Node, CString *strOutput);

	public:
		//����xml		
		void LoadXml(LPCSTR sz_FileName);  //�Զ�Ѱ��Ĭ�ϵ�·������	
		bool LoadFile(LPCSTR sz_FileName); //��������·������

		void Free();
		//ɾ��ע��
		void RemoveComment(MSXML2::IXMLDOMNodePtr &pCurrNode);

		//����ṹ
		void ReleaseGeoDataMapping(p_GeoDataXml pGeoDataXml);

		//���ӳ��ṹ
		void MappingGeoData(p_GeoDataXml pGeoDataXml);
		void AppendMappingGeoData(p_GeoDataXml pGeoDataXml, CString strPathFile);//׷��ӳ��
		void MappingGustomData(p_GeoDataXml pGeoDataXml);

		//��ȡϵͳ�������
		void GetAllGeoDetic(_Geodetic* pGeodetic);

		//void AppendGetAllGeoDetic(_Geodetic* pGeodetic);

		//��ȡϵͳͶӰ����
		void GetAllProjected(Projected* pProjected);
		//��ȡϵͳ��λ
		void GetUnits(_Units* pUnits);

		//��ȡ�û��Զ���������
		void GetCustomGeoDetic(_Geodetic* pGeodetic);
		//��ȡ�û��Զ���ͶӰ����
		void GetCustomProjected(Projected* pProjected);

		//���ͶӰ����Ԫ�ؽڵ�
		void FillProjectedBeking54(int nIndex, _ProjectedSeries* _pProjectedSeries);
		void FillProjectedXiAn80(int nIndex, _ProjectedSeries* _pProjectedSeries);
		void FillProjectedWGS84(int nIndex, _ProjectedSeries* _pProjectedSeries);
		void FillProjectedCGCS2000(int nIndex, _ProjectedSeries* _pProjectedSeries);
		
		//���������Ԫ�ؽڵ�
		void FillGeoDeticBeking54(int nIndex, _GeodeticSeries* p54);
		void FillGeoDeticXiAn80(int nIndex, _GeodeticSeries* p80);
		void FillGeoDeticWGS84(int nIndex, _GeodeticSeries* pWGS84);
		void FillGeoDeticCGCS2000(int nIndex, _GeodeticSeries* p2000);

		void FillUnit(MSXML2::IXMLDOMNodePtr &pCurrNode, _Unit* pUnit);
		
		//����Ϊ����Ƕ�׽ṹ�����
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
		
		//==============================����TaskInfoXml=====================
		void MappingTasks(p_Tasks pTasks);
		void FillTask(MSXML2::IXMLDOMNodePtr &pCurrNode, p_Task pTask);
		void ReleseTaskMapping(p_Tasks pTasks);

		void ReadFormat(_StrFormatList& Tasks);
		void GetFormat(MSXML2::IXMLDOMNodePtr &pCurrNode, _StrFormatTypeList* pTask);
	};

}
