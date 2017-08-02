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
		//���Ƶ�
		void BuildControlPointXml(LPCSTR sz_PathFile,_ControlPointPairs* pControlPointPairs);
		//ϵͳ����ϵ����
		void BuildGeoDataXml(LPCSTR sz_PathFile, _GeoDataXml* pGeoDataXml);
		//�û��Զ�������
		void BuildCustomDataXml(LPCSTR sz_PathFile, _GeoDataXml* pGeoDataXml);
		//����ͶӰ����Xml
		void OuputProjectedXml(CArray<_ProjectedSeries> *pPeking54, CString& strXml);
		//���ش������Xml
		void OuputGeoDeticXml(CArray<_GeodeticSeries> *pGeodeticSeries, CString& strXml);
	
		void OutUnits(_Units &pUnit, CString& strXml);

		void BuildTaskXml(LPCSTR sz_PathFile, p_Tasks pTasks);
		void BuildFormatXml(LPCSTR sz_PathFile, p_StrFormatList pTasks);
	};
}