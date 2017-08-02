#pragma once

#include "DeuGlobal.h"

namespace DeuXmlMapping
{
	class CDeuXmlWriter
	{
	public:
		CDeuXmlWriter(void);
		~CDeuXmlWriter(void);

	public:
		//控制点
		void BuildControlPointXml(LPCSTR sz_PathFile,_ControlPointPairs* pControlPointPairs);
		//系统坐标系数据
		void BuildGeoDataXml(LPCSTR sz_PathFile, _GeoDataXml* pGeoDataXml);
		//用户自定义数据
		void BuildCustomDataXml(LPCSTR sz_PathFile, _GeoDataXml* pGeoDataXml);
		//返回投影数据Xml
		void OuputProjectedXml(CArray<_ProjectedSeries> *pPeking54, CString& strXml);
		//返回大地数据Xml
		void OuputGeoDeticXml(CArray<_GeodeticSeries> *pGeodeticSeries, CString& strXml);
	
		void OutUnits(_Units &pUnit, CString& strXml);

		void BuildTaskXml(LPCSTR sz_PathFile, p_Tasks pTasks);
		void BuildFormatXml(LPCSTR sz_PathFile, p_StrFormatList pTasks);
	};
}