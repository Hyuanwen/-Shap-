#include "StdAfx.h"
#include "DeuGlobalParam.h"
#include "DeuXmlWriter.h"

namespace DeuXmlMapping
{
	const char* sz_Xml_Head = "<?xml version=\"1.0\" encoding=\"gbk\"?>\r\n";

	CDeuXmlWriter::CDeuXmlWriter(void)
	{
	}

	CDeuXmlWriter::~CDeuXmlWriter(void)
	{
	}

	void CDeuXmlWriter::BuildControlPointXml(LPCSTR sz_PathFile, _ControlPointPairs* pControlPointPairs)
	{
		CString strXml, strTmp;

		strXml = sz_Xml_Head;
		strXml += "<CControlPointPairs>\r\n";
		for(int n=0; n<pControlPointPairs->_controlPointPair.GetCount(); n++)
		{
			_ControlPointPair *pControlPointPair = (p_ControlPointPair)pControlPointPairs->_controlPointPair.GetAt(n);
			strXml += "		<CControlPointPair>\r\n";
			
			strTmp = pControlPointPair->X_SRC;
			strXml += "			<x1>"+strTmp+"</x1>\r\n";
			
			strTmp = pControlPointPair->Y_SRC;
			strXml += "			<y1>"+strTmp+"</y1>\r\n";
			
			strTmp = pControlPointPair->Z_SRC;
			strXml += "			<z1>"+strTmp+"</z1>\r\n";
			
			strTmp = pControlPointPair->X_DEST;
			strXml += "			<x2>"+strTmp+"</x2>\r\n";
			
			strTmp = pControlPointPair->Y_DEST;
			strXml += "			<y2>"+strTmp+"</y2>\r\n";

			strTmp = pControlPointPair->Z_DEST;
			strXml += "			<z2>"+strTmp+"</z2>\r\n";
			strXml += "		</CControlPointPair>\r\n";
		}
		
		strXml += "</CControlPointPairs>\r\n";

		HANDLE hFile = CreateFile(sz_PathFile, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_SYSTEM, NULL);
		if(hFile != NULL){
			CFile m_File(hFile);
			m_File.Write(strXml, strXml.GetLength());
			m_File.Close();
		}
	}

	void CDeuXmlWriter::BuildGeoDataXml(LPCSTR sz_PathFile, _GeoDataXml* pGeoDataXml)
	{
		CString strXml;
		strXml = sz_Xml_Head;
		
		strXml += "<dy>\r\n";

		strXml += " <projected>\r\n";
		OuputProjectedXml(&pGeoDataXml->ProjectedNode.pProjectedSeries, strXml);
		strXml += " </projected>\r\n";

		strXml += " <geodetic>\r\n";
		OuputGeoDeticXml(&pGeoDataXml->GeodeticNode.pGeodeticSeries, strXml);
		strXml += " </geodetic>\r\n";

		strXml += "<Units>\r\n";
		OutUnits(pGeoDataXml->UnitsNode, strXml);
		strXml += "</Units>\r\n";

		strXml += "</dy>\r\n";

		HANDLE hFile = CreateFile(sz_PathFile, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if(hFile != NULL){
			CFile m_File(hFile);
			m_File.Write(strXml, strXml.GetLength());
			m_File.Close();
		}
	}

	void CDeuXmlWriter::BuildCustomDataXml(LPCSTR sz_PathFile, _GeoDataXml* pGeoDataXml)
	{
		CString strXml;
		strXml = sz_Xml_Head;

		strXml += "<dy>\r\n";
				
		strXml += " <projected type=\"projected\" name=\"projectedCoordinateSystem\">\r\n";
		OuputProjectedXml(&pGeoDataXml->ProjectedNode.pProjectedSeries, strXml);
		strXml += " </projected>\r\n";

		strXml += " <geodetic type=\"geodetic\" name=\"geodeticCoordinateSystem\">\r\n";
		OuputGeoDeticXml(&pGeoDataXml->GeodeticNode.pGeodeticSeries, strXml);
		strXml += " </geodetic>\r\n";

		strXml += "</dy>\r\n";

		HANDLE hFile = CreateFile(sz_PathFile, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if(hFile != NULL){
			CFile m_File(hFile);
			m_File.Write(strXml, strXml.GetLength());
			m_File.Close();
		}
	}

	void CDeuXmlWriter::OuputProjectedXml(CArray<_ProjectedSeries>  *_pProjectedSeries, CString& strXml)		//84
	{
		for(int n=0; n<_pProjectedSeries->GetCount(); n++)
		{
			_ProjectedSeries pProjectedSeries = _pProjectedSeries->GetAt(n);

			strXml +="    <!--投影坐标系统-->\r\n";	

			strXml +="    <!--"+pProjectedSeries._geodeticPointor.text+"投影坐标系统-->\r\n";
			strXml +="    <CustomProjected type=\""+pProjectedSeries.type+"\" name=\""+pProjectedSeries.name+"\">\r\n";
			
			strXml +="      <!--描述-->\r\n";
			strXml +="      <Name type=\""+pProjectedSeries._name.type +"\" name=\""+pProjectedSeries._name.name+"\">"+pProjectedSeries._name.text+"</Name>\r\n";

			strXml +="      <!--名称-->\r\n";
			strXml +="      <!--zhangjingyu 名称-->\r\n";
			strXml +="      <Remark type=\""+pProjectedSeries._remark.type+"\" name=\""+pProjectedSeries._remark.name+"\">"+pProjectedSeries._remark.text+"</Remark>\r\n";

			strXml +="      <!--备注描述-->\r\n";
			strXml +="      <!--数据定义-->\r\n";
			strXml +="      <Envelope type=\""+pProjectedSeries._envelope.type+"\" name=\""+pProjectedSeries._envelope.name+"\">\r\n";

			strXml +="        <!--envelope-->\r\n";
			strXml +="        <Name type=\""+pProjectedSeries._envelope._name.type+"\" name=\""+pProjectedSeries._envelope._name.name+"\">"+pProjectedSeries._envelope._name.text+"</Name>\r\n";

			strXml +="        <!--zhangjingyu 25-->\r\n";
			strXml +="        <Remark type=\""+pProjectedSeries._envelope._remark.type+"\" name=\""+pProjectedSeries._envelope._remark.name+"\">"+pProjectedSeries._envelope._remark.text+"</Remark>\r\n";
			strXml +="        <MinPoint type=\""+pProjectedSeries._envelope._minpoint.type+"\" name=\""+pProjectedSeries._envelope._minpoint.name+"\">\r\n";
			strXml +="          <!--zhangjingyu 最小点经度-->\r\n";
			strXml +="          <Long type=\""+pProjectedSeries._envelope._minpoint._long.type+"\" name=\""+pProjectedSeries._envelope._minpoint._long.name+"\">"+pProjectedSeries._envelope._minpoint._long.text+"</Long>\r\n";
			strXml +="          <!--zhangjingyu 最小点纬度-->\r\n";
			strXml +="          <Lat type=\""+pProjectedSeries._envelope._minpoint._lat.type+"\" name=\""+pProjectedSeries._envelope._minpoint._lat.name+"\">"+pProjectedSeries._envelope._minpoint._lat.text+"</Lat>\r\n";
			strXml +="        </MinPoint>\r\n";
			strXml +="        <MaxPoint type=\""+pProjectedSeries._envelope._maxpoint.type+"\" name=\""+pProjectedSeries._envelope._maxpoint.name+"\">\r\n";
			strXml +="          <!--zhangjingyu 最小点经度-->\r\n";
			strXml +="          <Long type=\""+pProjectedSeries._envelope._maxpoint._long.type+"\" name=\""+pProjectedSeries._envelope._maxpoint._long.name+"\">"+pProjectedSeries._envelope._maxpoint._long.text+"</Long>\r\n";
			strXml +="          <!--zhangjingyu 最小点纬度-->\r\n";
			strXml +="          <Lat type=\""+pProjectedSeries._envelope._maxpoint._lat.type+"\" name=\""+pProjectedSeries._envelope._maxpoint._lat.name+"\">"+pProjectedSeries._envelope._maxpoint._lat.text+"</Lat>\r\n";			
			strXml +="        </MaxPoint>\r\n";
			strXml +="      </Envelope>\r\n";

			strXml +="      <PointStyle type=\""+pProjectedSeries._pointStyle.type+"\" name=\""+pProjectedSeries._pointStyle.name+"\">\r\n";
			strXml +="        <!--点类型-->\r\n";
			strXml +="        <Name type=\""+pProjectedSeries._pointStyle._name.type+"\" name=\""+pProjectedSeries._pointStyle._name.name+"\">"+pProjectedSeries._pointStyle._name.text+"</Name>\r\n";
			strXml +="        <Remark type=\""+pProjectedSeries._pointStyle._remark.type+"\" name=\""+pProjectedSeries._pointStyle._remark.name+"\">"+pProjectedSeries._pointStyle._remark.text+"</Remark>\r\n";
			strXml +="        <Dimensions type=\""+pProjectedSeries._pointStyle._dimensions.type+"\" name=\""+pProjectedSeries._pointStyle._dimensions.name+"\">"+pProjectedSeries._pointStyle._dimensions.text+"</Dimensions>\r\n";
			strXml +="        <East type=\""+pProjectedSeries._pointStyle._east.type+"\" name=\""+pProjectedSeries._pointStyle._east.name+"\">\r\n";
			strXml +="          <Label type=\""+pProjectedSeries._pointStyle._east._label.type+"\" name=\""+pProjectedSeries._pointStyle._east._label.name+"\">"+pProjectedSeries._pointStyle._east._label.text+"</Label>\r\n";
			strXml +="          <Units type=\""+pProjectedSeries._pointStyle._east._unit_1.type+"\" name=\""+pProjectedSeries._pointStyle._east.name+"\">\r\n";
			strXml +="            <Name type=\""+pProjectedSeries._pointStyle._east._unit_1._name.type+"\" name=\""+pProjectedSeries._pointStyle._east._unit_1._name.name+"\">"+pProjectedSeries._pointStyle._east._unit_1._name.text+"</Name>\r\n";
			strXml +="            <Remark type=\""+pProjectedSeries._pointStyle._east._unit_1._remark.type+"\" name=\""+pProjectedSeries._pointStyle._east._unit_1._remark.name+"\">"+pProjectedSeries._pointStyle._east._unit_1._remark.text+"</Remark>\r\n";
			strXml +="            <Abbreviation type=\""+pProjectedSeries._pointStyle._east._unit_1._abbreviation.type+"\" name=\""+pProjectedSeries._pointStyle._east._unit_1._abbreviation.name+"\">"+pProjectedSeries._pointStyle._east._unit_1._abbreviation.text+"</Abbreviation>\r\n";
			strXml +="            <Per_Meter type=\""+pProjectedSeries._pointStyle._east._unit_1._per_Meter.type+"\" name=\""+pProjectedSeries._pointStyle._east._unit_1._per_Meter.name+"\">"+pProjectedSeries._pointStyle._east._unit_1._per_Meter.text+"</Per_Meter>\r\n";
			strXml +="          </Units>\r\n";
			strXml +="        </East>\r\n";
			strXml +="        <North type=\""+pProjectedSeries._pointStyle._north.type+"\" name=\""+pProjectedSeries._pointStyle._north.name+"\">\r\n";
			strXml +="          <Label type=\""+pProjectedSeries._pointStyle._north._label.type+"\" name=\""+pProjectedSeries._pointStyle._north._label.name+"\">"+pProjectedSeries._pointStyle._north._label.text+"</Label>\r\n";
			strXml +="          <Units type=\""+pProjectedSeries._pointStyle._north._unit_1.type+"\" name=\""+pProjectedSeries._pointStyle._north._unit_1.name+"\">\r\n";
			strXml +="            <Name type=\""+pProjectedSeries._pointStyle._north._unit_1._name.type+"\" name=\""+pProjectedSeries._pointStyle._north._unit_1._name.name+"\">"+pProjectedSeries._pointStyle._north._unit_1._name.text+"</Name>\r\n";
			strXml +="            <Remark type=\""+pProjectedSeries._pointStyle._north._unit_1._remark.type+"\" name=\""+pProjectedSeries._pointStyle._north._unit_1._remark.name+"\">"+pProjectedSeries._pointStyle._north._unit_1._remark.text+"</Remark>\r\n";
			strXml +="            <Abbreviation type=\""+pProjectedSeries._pointStyle._north._unit_1._abbreviation.type+"\" name=\""+pProjectedSeries._pointStyle._north._unit_1._abbreviation.name+"\">"+pProjectedSeries._pointStyle._north._unit_1._abbreviation.text+"</Abbreviation>\r\n";
			strXml +="            <Per_Meter type=\""+pProjectedSeries._pointStyle._north._unit_1._per_Meter.type+"\" name=\""+pProjectedSeries._pointStyle._north._unit_1._per_Meter.name+"\">"+pProjectedSeries._pointStyle._north._unit_1._per_Meter.text+"</Per_Meter>\r\n";
			strXml +="          </Units>\r\n";
			strXml +="        </North>\r\n";
			strXml +="        <EllipsoidHeight type=\""+pProjectedSeries._pointStyle._ellipsoidHeight.type+"\" name=\""+pProjectedSeries._pointStyle._ellipsoidHeight.name+"\">\r\n";
			strXml +="          <Label type=\""+pProjectedSeries._pointStyle._ellipsoidHeight._label.type+"\" name=\""+pProjectedSeries._pointStyle._ellipsoidHeight._label.name+"\">"+pProjectedSeries._pointStyle._ellipsoidHeight._label.text+"</Label>\r\n";
			strXml +="          <Units type=\""+pProjectedSeries._pointStyle._ellipsoidHeight._unit_1.type+"\" name=\""+pProjectedSeries._pointStyle._ellipsoidHeight._unit_1.name+"\">\r\n";
			strXml +="            <Name type=\""+pProjectedSeries._pointStyle._ellipsoidHeight._unit_1._name.type+"\" name=\""+pProjectedSeries._pointStyle._ellipsoidHeight._unit_1._name.name+"\">"+pProjectedSeries._pointStyle._ellipsoidHeight._unit_1._name.text+"</Name>\r\n";
			strXml +="            <Remark type=\""+pProjectedSeries._pointStyle._ellipsoidHeight._unit_1._remark.type+"\" name=\""+pProjectedSeries._pointStyle._ellipsoidHeight._unit_1._remark.name+"\">"+pProjectedSeries._pointStyle._ellipsoidHeight._unit_1._remark.text+"</Remark>\r\n";
			strXml +="            <Abbreviation type=\""+pProjectedSeries._pointStyle._ellipsoidHeight._unit_1._abbreviation.type+"\" name=\""+pProjectedSeries._pointStyle._ellipsoidHeight._unit_1._abbreviation.name+"\">"+pProjectedSeries._pointStyle._ellipsoidHeight._unit_1._abbreviation.text+"</Abbreviation>\r\n";
			strXml +="            <Per_Meter type=\""+pProjectedSeries._pointStyle._ellipsoidHeight._unit_1._per_Meter.type+"\" name=\""+pProjectedSeries._pointStyle._ellipsoidHeight._unit_1._per_Meter.name+"\">"+pProjectedSeries._pointStyle._ellipsoidHeight._unit_1._per_Meter.text+"</Per_Meter>\r\n";
			strXml +="          </Units>\r\n";
			strXml +="        </EllipsoidHeight>\r\n";
			strXml +="      </PointStyle>\r\n";

			strXml +="      <!--大地指针-->\r\n";
			strXml +="      <GeodeticPointor type=\""+pProjectedSeries._geodeticPointor.type+"\" name=\""+pProjectedSeries._geodeticPointor.name+"\">"+pProjectedSeries._geodeticPointor.text+"</GeodeticPointor>\r\n";

			strXml +="      <Projection type=\""+pProjectedSeries._projection.type+"\" name=\""+pProjectedSeries._projection.name+"\">"+pProjectedSeries._projection.text+"</Projection>\r\n";

			strXml +="      <!--参数-->\r\n";
			strXml +="      <CentralMeridian type=\""+pProjectedSeries._centralMeridian.type+"\" name=\""+pProjectedSeries._centralMeridian.name+"\">\r\n";
			strXml +="        <Name type =\""+pProjectedSeries._centralMeridian._name.type+"\" name=\""+pProjectedSeries._centralMeridian._name.name+"\">"+pProjectedSeries._centralMeridian._name.text+"</Name>\r\n";
			strXml +="        <Value type=\""+pProjectedSeries._centralMeridian._value.type+"\" name=\""+pProjectedSeries._centralMeridian._value.name+"\">"+pProjectedSeries._centralMeridian._value.text+"</Value>\r\n";
			strXml +="        <!--zhangjingyu 中央子午线-->\r\n";
			strXml +="        <Units type=\""+pProjectedSeries._centralMeridian._uint.type+"\" name=\""+pProjectedSeries._centralMeridian._uint.name+"\">"+pProjectedSeries._centralMeridian._uint.text+"</Units>\r\n";
			strXml +="      </CentralMeridian>\r\n";

			strXml +="      <FalseEasting type=\""+pProjectedSeries._falseEasting.type+"\" name=\""+pProjectedSeries._falseEasting.name+"\">\r\n";
			strXml +="        <Name type =\""+pProjectedSeries._falseEasting._name.type+"\" name=\""+pProjectedSeries._falseEasting._name.name+"\">"+pProjectedSeries._falseEasting._name.text+"</Name>\r\n";
			strXml +="        <Value type=\""+pProjectedSeries._falseEasting._value.type+"\" name=\""+pProjectedSeries._falseEasting._value.name+"\">"+pProjectedSeries._falseEasting._value.text+"</Value>\r\n";
			strXml +="        <!--zhangjingyu 东假值-->\r\n";
			strXml +="        <Units type=\""+pProjectedSeries._falseEasting._uint.type+"\" name=\""+pProjectedSeries._falseEasting._uint.type+"\">"+pProjectedSeries._falseEasting._uint.text+"</Units>\r\n";
			strXml +="      </FalseEasting>\r\n";

			strXml +="      <FalseNorthing type=\""+pProjectedSeries._falseNorthing.type+"\" name=\""+pProjectedSeries._falseNorthing.name+"\">\r\n";
			strXml +="        <Name type =\""+pProjectedSeries._falseNorthing._name.type+"\" name=\""+pProjectedSeries._falseNorthing._name.name+"\">"+pProjectedSeries._falseNorthing._name.text+"</Name>\r\n";
			strXml +="        <Value type=\""+pProjectedSeries._falseNorthing._value.type+"\" name=\""+pProjectedSeries._falseNorthing._value.name+"\">"+pProjectedSeries._falseNorthing._value.text+"</Value>\r\n";
			strXml +="        <Units type=\""+pProjectedSeries._falseNorthing._uint.type+"\" name=\""+pProjectedSeries._falseNorthing._uint.name+"\">"+pProjectedSeries._falseNorthing._uint.text+"</Units>\r\n";
			strXml +="      </FalseNorthing>\r\n";

			strXml +="      <LatitudeOfOrigin type=\""+pProjectedSeries._latitudeOfOrigin.type+"\" name=\""+pProjectedSeries._latitudeOfOrigin.name+"\">\r\n";
			strXml +="        <Name type =\""+pProjectedSeries._latitudeOfOrigin._name.type+"\" name=\""+pProjectedSeries._latitudeOfOrigin._name.name+"\">"+pProjectedSeries._latitudeOfOrigin._name.text+"</Name>\r\n";
			strXml +="        <Value type=\""+pProjectedSeries._latitudeOfOrigin._value.type+"\" name=\""+pProjectedSeries._latitudeOfOrigin._value.name+"\">"+pProjectedSeries._latitudeOfOrigin._value.text+"</Value>\r\n";
			strXml +="        <Units type=\""+pProjectedSeries._latitudeOfOrigin._uint.type+"\" name=\""+pProjectedSeries._latitudeOfOrigin._uint.type+"\">"+pProjectedSeries._latitudeOfOrigin._uint.text+"</Units>\r\n";
			strXml +="      </LatitudeOfOrigin>\r\n";

			strXml +="      <ScaleFactor type=\""+pProjectedSeries._scaleFactor.type+"\" name=\""+pProjectedSeries._scaleFactor.name+"\">\r\n";
			strXml +="        <Name type =\""+pProjectedSeries._scaleFactor._name.type+"\" name=\""+pProjectedSeries._scaleFactor._name.name+"\">"+pProjectedSeries._scaleFactor._name.text+"</Name>\r\n";
			strXml +="        <Value type=\""+pProjectedSeries._scaleFactor._value.type+"\" name=\""+pProjectedSeries._scaleFactor._value.name+"\">"+pProjectedSeries._scaleFactor._value.text+"</Value>\r\n";
			strXml +="        <Units type=\""+pProjectedSeries._scaleFactor._uint.type+"\" name=\""+pProjectedSeries._scaleFactor._uint.name+"\">"+pProjectedSeries._scaleFactor._uint.text+"</Units>\r\n";
			strXml +="      </ScaleFactor>\r\n";

			strXml +="      <CSType type=\""+pProjectedSeries._csType.type+"\" name=\""+pProjectedSeries._csType.name+"\">"+pProjectedSeries._csType.text+"</CSType>\r\n";

			strXml +="    </CustomProjected>\r\n";
			
		}
	}

	//返回大地数据Xml
	void CDeuXmlWriter::OuputGeoDeticXml(CArray<_GeodeticSeries> *pGeodeticSeries, CString& strXml)	//54
	{
		for(int n=0; n<pGeodeticSeries->GetCount(); n++)
		{
			_GeodeticSeries m_GeodeticSeries = pGeodeticSeries->GetAt(n);

			/*switch(_pGeodeticSeries->_tranStandard)
			{
			case Peking54:
				strXml +="    <!--beijing54投影坐标系统-->\r\n";	
				strXml +="    <geodeticbeijing54 type=\""+_pGeodeticSeries->type+"\" name=\""+_pGeodeticSeries->name+"\">\r\n";
				break;
			case XiAn80:
				strXml +="    <!--XiAn80投影坐标系统-->\r\n";	
				strXml +="    <geodeticXiAn80 type=\""+_pGeodeticSeries->type+"\" name=\""+_pGeodeticSeries->name+"\">\r\n";
				break;
			case WGS84:
				strXml +="    <!--WGS84投影坐标系统-->\r\n";
				strXml +="    <geodeticwgs1984 type=\""+_pGeodeticSeries->type+"\" name=\""+_pGeodeticSeries->name+"\">\r\n";
				break;
			case CGCS2000:
				strXml +="    <!--CGCS2000投影坐标系统-->\r\n";
				strXml +="    <geodeticcgcs2000 type=\""+_pGeodeticSeries->type+"\" name=\""+_pGeodeticSeries->name+"\">\r\n";
				break;
			}*/
			
			strXml +="    <!--"+m_GeodeticSeries._name.text+"大地坐标系统-->\r\n";
			strXml +="    <CustomGeodetic type=\""+m_GeodeticSeries.type+"\" name=\""+m_GeodeticSeries.name+"\">\r\n";

			strXml +="      <!--描述-->\r\n";
			strXml +="      <Name type=\""+m_GeodeticSeries._name.type+"\" name=\""+m_GeodeticSeries._name.name+"\">"+m_GeodeticSeries._name.text+"</Name>\r\n";
			strXml +="      <Remark type=\""+m_GeodeticSeries._remark.type+"\" name=\""+m_GeodeticSeries._remark.name+"\">"+m_GeodeticSeries._remark.text+"</Remark>\r\n";
			strXml +="      <!--数据定义-->\r\n";

			strXml +="      <Envelope type=\""+m_GeodeticSeries._envelope.type+"\" name=\""+m_GeodeticSeries._envelope.name+"\">\r\n";
			strXml +="        <!--Geodetic_Envelope-->\r\n";
			strXml +="        <Name type=\""+m_GeodeticSeries._envelope._name.type+"\" name=\""+m_GeodeticSeries._envelope._name.name+"\">"+m_GeodeticSeries._envelope._name.text+"</Name>\r\n";
			strXml +="        <Remark type=\""+m_GeodeticSeries._envelope._remark.type+"\" name=\""+m_GeodeticSeries._envelope._remark.name+"\">"+m_GeodeticSeries._envelope._remark.text+"</Remark>\r\n";
			strXml +="        <MinPoint type=\""+m_GeodeticSeries._envelope._minpoint.type+"\" name=\""+m_GeodeticSeries._envelope._minpoint.name+"\">\r\n";			
			strXml +="          <Long type=\""+m_GeodeticSeries._envelope._minpoint._long.type+"\" name=\""+m_GeodeticSeries._envelope._minpoint._long.name+"\">"+m_GeodeticSeries._envelope._minpoint._long.text+"</Long>\r\n";
			strXml +="          <Lat type=\""+m_GeodeticSeries._envelope._minpoint._lat.type+"\" name=\""+m_GeodeticSeries._envelope._minpoint._lat.name+"\">"+m_GeodeticSeries._envelope._minpoint._lat.text+"</Lat>\r\n";
			strXml +="        </MinPoint>\r\n";
			strXml +="        <MaxPoint type=\""+m_GeodeticSeries._envelope._maxpoint.type+"\" name=\""+m_GeodeticSeries._envelope._maxpoint.name+"\">\r\n";			
			strXml +="          <Long type=\""+m_GeodeticSeries._envelope._maxpoint._long.type+"\" name=\""+m_GeodeticSeries._envelope._maxpoint._long.name+"\">"+m_GeodeticSeries._envelope._maxpoint._long.text+"</Long>\r\n";
			strXml +="          <Lat type=\""+m_GeodeticSeries._envelope._maxpoint._lat.type+"\" name=\""+m_GeodeticSeries._envelope._maxpoint._lat.name+"\">"+m_GeodeticSeries._envelope._maxpoint._lat.text+"</Lat>\r\n";
			strXml +="        </MaxPoint>\r\n";
			strXml +="      </Envelope>\r\n";

			strXml +="      <PointStyle type=\""+m_GeodeticSeries._pointStyle.type+"\" name=\""+m_GeodeticSeries._pointStyle.name+"\">\r\n";
			strXml +="        <!--大地点类型-->\r\n";
			strXml +="        <Name type=\""+m_GeodeticSeries._pointStyle._name.type+"\" name=\""+m_GeodeticSeries._pointStyle._name.name+"\">"+m_GeodeticSeries._pointStyle._name.text+"</Name>\r\n";
			strXml +="        <Remark type=\""+m_GeodeticSeries._pointStyle._remark.type+"\" name=\""+m_GeodeticSeries._pointStyle._remark.name+"\">"+m_GeodeticSeries._pointStyle._remark.text+"</Remark>\r\n";
			strXml +="        <Dimensions type=\""+m_GeodeticSeries._pointStyle._dimensions.type+"\" name=\""+m_GeodeticSeries._pointStyle._dimensions.name+"\">"+m_GeodeticSeries._pointStyle._dimensions.text+"</Dimensions>\r\n";
			strXml +="        <Long type=\""+m_GeodeticSeries._pointStyle._geoDeticLongForPS.type+"\" name=\""+m_GeodeticSeries._pointStyle._geoDeticLongForPS.name+"\">\r\n";
			strXml +="          <Label type=\""+m_GeodeticSeries._pointStyle._geoDeticLongForPS._label.type+"\" name=\""+m_GeodeticSeries._pointStyle._geoDeticLongForPS._label.name+"\">"+m_GeodeticSeries._pointStyle._geoDeticLongForPS._label.text+"</Label>\r\n";
			strXml +="          <Units type=\""+m_GeodeticSeries._pointStyle._geoDeticLongForPS._unit_2.type+"\" name=\""+m_GeodeticSeries._pointStyle._geoDeticLongForPS._unit_2.name+"\">\r\n";
			strXml +="            <Name type=\""+m_GeodeticSeries._pointStyle._geoDeticLongForPS._unit_2._name.type+"\" name=\""+m_GeodeticSeries._pointStyle._geoDeticLongForPS._unit_2._name.name+"\">"+m_GeodeticSeries._pointStyle._geoDeticLongForPS._unit_2._name.text+"</Name>\r\n";
			strXml +="            <Remark type=\""+m_GeodeticSeries._pointStyle._geoDeticLongForPS._unit_2._remark.type+"\" name=\""+m_GeodeticSeries._pointStyle._geoDeticLongForPS._unit_2._remark.name+"\">"+m_GeodeticSeries._pointStyle._geoDeticLongForPS._unit_2._remark.text+"</Remark>\r\n";
			strXml +="            <Abbreviation type=\""+m_GeodeticSeries._pointStyle._geoDeticLongForPS._unit_2._abbreviation.type+"\" name=\""+m_GeodeticSeries._pointStyle._geoDeticLongForPS._unit_2._abbreviation.name+"\">"+m_GeodeticSeries._pointStyle._geoDeticLongForPS._unit_2._abbreviation.text+"</Abbreviation>\r\n";
			strXml +="            <Per_Degree type=\""+m_GeodeticSeries._pointStyle._geoDeticLongForPS._unit_2._per_Degree.type+"\" name=\""+m_GeodeticSeries._pointStyle._geoDeticLongForPS._unit_2._per_Degree.name+"\">"+m_GeodeticSeries._pointStyle._geoDeticLongForPS._unit_2._per_Degree.text+"</Per_Degree>\r\n";
			strXml +="          </Units>\r\n";
			strXml +="        </Long>\r\n";
			strXml +="        <Lat type=\""+m_GeodeticSeries._pointStyle._geoDeticLatForPS.type+"\" name=\""+m_GeodeticSeries._pointStyle._geoDeticLatForPS.name+"\">\r\n";
			strXml +="          <Label type=\""+m_GeodeticSeries._pointStyle._geoDeticLatForPS._label.type+"\" name=\""+m_GeodeticSeries._pointStyle._geoDeticLatForPS._label.name+"\">"+m_GeodeticSeries._pointStyle._geoDeticLatForPS._label.text+"</Label>\r\n";
			strXml +="          <Units type=\""+m_GeodeticSeries._pointStyle._geoDeticLatForPS._unit_2.type+"\" name=\""+m_GeodeticSeries._pointStyle._geoDeticLatForPS._unit_2.name+"\">\r\n";
			strXml +="            <Name type=\""+m_GeodeticSeries._pointStyle._geoDeticLatForPS._unit_2._name.type+"\" name=\""+m_GeodeticSeries._pointStyle._geoDeticLatForPS._unit_2._name.name+"\">"+m_GeodeticSeries._pointStyle._geoDeticLatForPS._unit_2._name.text+"</Name>\r\n";
			strXml +="            <Remark type=\""+m_GeodeticSeries._pointStyle._geoDeticLatForPS._unit_2._remark.type+"\" name=\""+m_GeodeticSeries._pointStyle._geoDeticLatForPS._unit_2._remark.name+"\">"+m_GeodeticSeries._pointStyle._geoDeticLatForPS._unit_2._remark.text+"</Remark>\r\n";
			strXml +="            <Abbreviation type=\""+m_GeodeticSeries._pointStyle._geoDeticLatForPS._unit_2._abbreviation.type+"\" name=\""+m_GeodeticSeries._pointStyle._geoDeticLatForPS._unit_2._abbreviation.name+"\">"+m_GeodeticSeries._pointStyle._geoDeticLatForPS._unit_2._abbreviation.text+"</Abbreviation>\r\n";
			strXml +="            <Per_Degree type=\""+m_GeodeticSeries._pointStyle._geoDeticLatForPS._unit_2._per_Degree.type+"\" name=\""+m_GeodeticSeries._pointStyle._geoDeticLatForPS._unit_2._per_Degree.name+"\">"+m_GeodeticSeries._pointStyle._geoDeticLatForPS._unit_2._per_Degree.text+"</Per_Degree>\r\n";
			strXml +="          </Units>\r\n";
			strXml +="        </Lat>\r\n";
			strXml +="        <EllipsoidHeight type=\""+m_GeodeticSeries._pointStyle._ellipsoidHeight.type+"\" name=\""+m_GeodeticSeries._pointStyle._ellipsoidHeight.name+"\">\r\n";
			strXml +="           <Label type=\""+m_GeodeticSeries._pointStyle._ellipsoidHeight._label.type+"\" name=\""+m_GeodeticSeries._pointStyle._ellipsoidHeight._label.name+"\">"+m_GeodeticSeries._pointStyle._ellipsoidHeight._label.text+"</Label>\r\n";
			strXml +="           <Units type=\""+m_GeodeticSeries._pointStyle._ellipsoidHeight._unit_1.type+"\" name=\""+m_GeodeticSeries._pointStyle._ellipsoidHeight._unit_1.name+"\">\r\n";
			strXml +="            <Name type=\""+m_GeodeticSeries._pointStyle._ellipsoidHeight._unit_1._name.type+"\" name=\""+m_GeodeticSeries._pointStyle._ellipsoidHeight._unit_1._name.name+"\">"+m_GeodeticSeries._pointStyle._ellipsoidHeight._unit_1._name.text+"</Name>\r\n";
			strXml +="            <Remark type=\""+m_GeodeticSeries._pointStyle._ellipsoidHeight._unit_1._remark.type+"\" name=\""+m_GeodeticSeries._pointStyle._ellipsoidHeight._unit_1._remark.name+"\">"+m_GeodeticSeries._pointStyle._ellipsoidHeight._unit_1._remark.text+"</Remark>\r\n";
			strXml +="            <Abbreviation type=\""+m_GeodeticSeries._pointStyle._ellipsoidHeight._unit_1._abbreviation.type+"\" name=\""+m_GeodeticSeries._pointStyle._ellipsoidHeight._unit_1._abbreviation.name+"\">"+m_GeodeticSeries._pointStyle._ellipsoidHeight._unit_1._abbreviation.text+"</Abbreviation>\r\n";
			strXml +="            <Per_Meter type=\""+m_GeodeticSeries._pointStyle._ellipsoidHeight._unit_1._per_Meter.type+"\" name=\""+m_GeodeticSeries._pointStyle._ellipsoidHeight._unit_1._per_Meter.name+"\">"+m_GeodeticSeries._pointStyle._ellipsoidHeight._unit_1._per_Meter.text+"</Per_Meter>\r\n";
			strXml +="          </Units>\r\n";
			strXml +="        </EllipsoidHeight>\r\n";
			strXml +="      </PointStyle>\r\n";

			strXml +="      <Datum type=\""+m_GeodeticSeries._datum.type+"\" name=\""+m_GeodeticSeries._datum.name+"\">\r\n";
			strXml +="        <!--大地基准-->\r\n";
			strXml +="        <Name type=\""+m_GeodeticSeries._datum._name.type+"\" name=\""+m_GeodeticSeries._datum._name.name+"\">"+m_GeodeticSeries._datum._name.text+"</Name>\r\n";
			strXml +="        <Remark type=\""+m_GeodeticSeries._datum._remark.type+"\" name=\""+m_GeodeticSeries._datum._remark.name+"\">"+m_GeodeticSeries._datum._remark.text+"</Remark>\r\n";
			strXml +="        <Ellipsoid type=\""+m_GeodeticSeries._datum._ellipsoid.type+"\" name=\""+m_GeodeticSeries._datum._ellipsoid.name+"\">\r\n";
			strXml +="          <Name type=\""+m_GeodeticSeries._datum._ellipsoid._name.type+"\" name=\""+m_GeodeticSeries._datum._ellipsoid._name.name+"\">"+m_GeodeticSeries._datum._ellipsoid._name.text+"</Name>\r\n";

			strXml +="          <Remark type=\""+m_GeodeticSeries._datum._ellipsoid._remark.type+"\" name=\""+m_GeodeticSeries._datum._ellipsoid._remark.name+"\">"+m_GeodeticSeries._datum._ellipsoid._remark.text+"</Remark>\r\n";

			strXml +="          <Semi-Major-Axis type=\""+m_GeodeticSeries._datum._ellipsoid._semi_Major_Axis.type+"\" name=\""+m_GeodeticSeries._datum._ellipsoid._semi_Major_Axis.name+"\">\r\n";
			strXml +="            <Value type=\""+m_GeodeticSeries._datum._ellipsoid._semi_Major_Axis._value.type+"\" name=\""+m_GeodeticSeries._datum._ellipsoid._semi_Major_Axis._value.name+"\">"+m_GeodeticSeries._datum._ellipsoid._semi_Major_Axis._value.text+"</Value>\r\n";
			strXml +="            <Units type=\""+m_GeodeticSeries._datum._ellipsoid._semi_Major_Axis._unit_1.type+"\" name=\""+m_GeodeticSeries._datum._ellipsoid._semi_Major_Axis._unit_1.name+"\">\r\n";
			strXml +="              <Name type=\""+m_GeodeticSeries._datum._ellipsoid._semi_Major_Axis._unit_1.type+"\" name=\""+m_GeodeticSeries._datum._ellipsoid._semi_Major_Axis._unit_1._name.name+"\">"+m_GeodeticSeries._datum._ellipsoid._semi_Major_Axis._unit_1._name.text+"</Name>\r\n";
			strXml +="              <Remark type=\""+m_GeodeticSeries._datum._ellipsoid._semi_Major_Axis._unit_1._remark.type+"\" name=\""+m_GeodeticSeries._datum._ellipsoid._semi_Major_Axis._unit_1._remark.name+"\">"+m_GeodeticSeries._datum._ellipsoid._semi_Major_Axis._unit_1._remark.text+"</Remark>\r\n";
			strXml +="              <Abbreviation type=\""+m_GeodeticSeries._datum._ellipsoid._semi_Major_Axis._unit_1._abbreviation.type+"\" name=\""+m_GeodeticSeries._datum._ellipsoid._semi_Major_Axis._unit_1._abbreviation.name+"\">"+m_GeodeticSeries._datum._ellipsoid._semi_Major_Axis._unit_1._abbreviation.text+"</Abbreviation>\r\n";
			strXml +="              <Per_Meter type=\""+m_GeodeticSeries._datum._ellipsoid._semi_Major_Axis._unit_1._per_Meter.type+"\" name=\""+m_GeodeticSeries._datum._ellipsoid._semi_Major_Axis._unit_1._per_Meter.name+"\">"+m_GeodeticSeries._datum._ellipsoid._semi_Major_Axis._unit_1._per_Meter.text+"</Per_Meter>\r\n";
			strXml +="            </Units>\r\n";
			strXml +="          </Semi-Major-Axis>\r\n";
			strXml +="          <Semi-Minor-Axis type=\""+m_GeodeticSeries._datum._ellipsoid._semi_Minor_Axis.type+"\" name=\""+m_GeodeticSeries._datum._ellipsoid._semi_Minor_Axis.name+"\">\r\n";
			strXml +="            <Value type=\""+m_GeodeticSeries._datum._ellipsoid._semi_Minor_Axis._value.type+"\" name=\""+m_GeodeticSeries._datum._ellipsoid._semi_Minor_Axis._value.name+"\">"+m_GeodeticSeries._datum._ellipsoid._semi_Minor_Axis._value.text+"</Value>\r\n";
			strXml +="            <Units type=\""+m_GeodeticSeries._datum._ellipsoid._semi_Minor_Axis._unit_1.type+"\" name=\""+m_GeodeticSeries._datum._ellipsoid._semi_Minor_Axis._unit_1.name+"\">\r\n";
			strXml +="              <Name type=\""+m_GeodeticSeries._datum._ellipsoid._semi_Minor_Axis._unit_1._name.type+"\" name=\""+m_GeodeticSeries._datum._ellipsoid._semi_Minor_Axis._unit_1._name.name+"\">"+m_GeodeticSeries._datum._ellipsoid._semi_Minor_Axis._unit_1._name.text+"</Name>\r\n";
			strXml +="              <Remark type=\""+m_GeodeticSeries._datum._ellipsoid._semi_Minor_Axis._unit_1._remark.type+"\" name=\""+m_GeodeticSeries._datum._ellipsoid._semi_Minor_Axis._unit_1._remark.name+"\">"+m_GeodeticSeries._datum._ellipsoid._semi_Minor_Axis._unit_1._remark.text+"</Remark>\r\n";
			strXml +="              <Abbreviation type=\""+m_GeodeticSeries._datum._ellipsoid._semi_Minor_Axis._unit_1._abbreviation.type+"\" name=\""+m_GeodeticSeries._datum._ellipsoid._semi_Minor_Axis._unit_1._abbreviation.name+"\">"+m_GeodeticSeries._datum._ellipsoid._semi_Minor_Axis._unit_1._abbreviation.text+"</Abbreviation>\r\n";
			strXml +="              <Per_Meter type=\""+m_GeodeticSeries._datum._ellipsoid._semi_Minor_Axis._unit_1._per_Meter.type+"\" name=\""+m_GeodeticSeries._datum._ellipsoid._semi_Minor_Axis._unit_1._per_Meter.name+"\">"+m_GeodeticSeries._datum._ellipsoid._semi_Minor_Axis._unit_1._per_Meter.text+"</Per_Meter>\r\n";
			strXml +="            </Units>\r\n";
			strXml +="          </Semi-Minor-Axis>\r\n";
			strXml +="          <InverseFlattening type=\""+m_GeodeticSeries._datum._ellipsoid._inverseFlattening.type+"\" name=\""+m_GeodeticSeries._datum._ellipsoid._inverseFlattening.name+"\">"+m_GeodeticSeries._datum._ellipsoid._inverseFlattening.text+"</InverseFlattening>\r\n";
			strXml +="        </Ellipsoid>\r\n";
			strXml +="        <PrimeMeridian type=\""+m_GeodeticSeries._datum._primeMeridian.type+"\" name=\""+m_GeodeticSeries._datum._primeMeridian._name.name+"\">\r\n";
			strXml +="          <Name type=\""+m_GeodeticSeries._datum._primeMeridian._name.type+"\" name=\""+m_GeodeticSeries._datum._primeMeridian._name.name+"\">"+m_GeodeticSeries._datum._primeMeridian._name.text+"</Name>\r\n";
			strXml +="          <Long type=\""+m_GeodeticSeries._datum._primeMeridian._geoDeticLong.type+"\" name=\""+m_GeodeticSeries._datum._primeMeridian._geoDeticLong.name+"\">\r\n";
			strXml +="            <Value type=\""+m_GeodeticSeries._datum._primeMeridian._geoDeticLong._value.type+"\" name=\""+m_GeodeticSeries._datum._primeMeridian._geoDeticLong._value.name+"\">"+m_GeodeticSeries._datum._primeMeridian._geoDeticLong._value.text+"</Value>\r\n";
			strXml +="            <Units type=\""+m_GeodeticSeries._datum._primeMeridian._geoDeticLong._unit_2.type+"\" name=\""+m_GeodeticSeries._datum._primeMeridian._geoDeticLong._unit_2.name+"\">\r\n";
			strXml +="              <Name type=\""+m_GeodeticSeries._datum._primeMeridian._geoDeticLong._unit_2._name.type+"\" name=\""+m_GeodeticSeries._datum._primeMeridian._geoDeticLong._unit_2._name.name+"\">"+m_GeodeticSeries._datum._primeMeridian._geoDeticLong._unit_2._name.text+"</Name>\r\n";
			strXml +="              <Remark type=\""+m_GeodeticSeries._datum._primeMeridian._geoDeticLong._unit_2._remark.type+"\" name=\""+m_GeodeticSeries._datum._primeMeridian._geoDeticLong._unit_2._remark.name+"\">"+m_GeodeticSeries._datum._primeMeridian._geoDeticLong._unit_2._remark.text+"</Remark>\r\n";
			strXml +="              <Abbreviation type=\""+m_GeodeticSeries._datum._primeMeridian._geoDeticLong._unit_2._abbreviation.type+"\" name=\""+m_GeodeticSeries._datum._primeMeridian._geoDeticLong._unit_2._abbreviation.name+"\">"+m_GeodeticSeries._datum._primeMeridian._geoDeticLong._unit_2._abbreviation.text+"</Abbreviation>\r\n";
			strXml +="              <Per_Degree type=\""+m_GeodeticSeries._datum._primeMeridian._geoDeticLong._unit_2._per_Degree.type+"\" name=\""+m_GeodeticSeries._datum._primeMeridian._geoDeticLong._unit_2._per_Degree.name+"\">"+m_GeodeticSeries._datum._primeMeridian._geoDeticLong._unit_2._per_Degree.text+"</Per_Degree>\r\n";
			strXml +="            </Units>\r\n";
			strXml +="          </Long>\r\n";
			strXml +="        </PrimeMeridian>\r\n";
			strXml +="      </Datum>\r\n";

			strXml +="      <CSType type=\""+m_GeodeticSeries._csType.type+"\" name=\""+m_GeodeticSeries._csType.name+"\">"+m_GeodeticSeries._csType.text+"</CSType>\r\n";
			
			strXml +="    </CustomGeodetic>\r\n";

			/*switch(m_GeodeticSeries._tranStandard)
			{
			case Peking54:
				
				break;
			case XiAn80:
				strXml +="    </geodeticXiAn80>\r\n";
				break;
			case WGS84:
				strXml +="    </geodeticwgs1984>\r\n";
				break;
			case CGCS2000:
				strXml +="    </geodeticcgcs2000>\r\n";
				break;
			}*/
		}
	}

	void CDeuXmlWriter::OutUnits(_Units &pUnit, CString& strXml)
	{
		strXml += "	<UnitGeocentric>\r\n";
		strXml += "	 <X>"+pUnit.Geocentric.X+"</X>\r\n";
		strXml += "	 <Y>"+pUnit.Geocentric.Y+"</Y>\r\n";
		strXml += "	 <Z>"+pUnit.Geocentric.Z+"</Z>\r\n";
		strXml += "	</UnitGeocentric>\r\n";
		strXml += "	<UnitGeodetic>\r\n";
		strXml += "	  <X>"+pUnit.Geodetic.X+"</X>\r\n";
		strXml += "	  <Y>"+pUnit.Geodetic.Y+"</Y>\r\n";
		strXml += "	  <Z>"+pUnit.Geodetic.Z+"</Z>\r\n";
		strXml += "	</UnitGeodetic>\r\n";
		strXml += "	<UnitPlane>\r\n";
		strXml += "	  <X>"+pUnit.Plane.X+"</X>\r\n";
		strXml += "	  <Y>"+pUnit.Plane.Y+"</Y>\r\n";
		strXml += "	  <Z>"+pUnit.Plane.Z+"</Z>\r\n";
		strXml += "	</UnitPlane>\r\n";
	}

	void CDeuXmlWriter::BuildTaskXml(LPCSTR sz_PathFile, p_Tasks pTasks)
	{
		CString strXml, strId;
		strXml = sz_Xml_Head;
		strXml += "<TaskList type=\""+pTasks->type+"\" name=\""+pTasks->name+"\">\r\n";
		
		for(int n=0; n<pTasks->_task.GetCount(); n++)
		{
			p_Task ptask = pTasks->_task.GetAt(n);
			strId.Format("%s", newGUID());//每次都换新的GUID
			
			strXml += "	<CDeuTask id=\""+strId+"\" type=\""+ptask->type+"\" name=\""+ptask->name+"\">\r\n";
			strXml += "		<IN_PATH type=\""+ptask->_inpath.type+"\" name=\""+ptask->_inpath.name+"\">"+ptask->_inpath.text+"</IN_PATH>\r\n";
			strXml += "		<OUT_PATH type=\""+ptask->_outpath.type+"\" name=\""+ptask->_outpath.name+"\">"+ptask->_outpath.text+"</OUT_PATH>\r\n";
			
			strXml += "		<IN_DRIVER type=\""+ptask->_inDriver.type+"\" name=\""+ptask->_inDriver.name+"\">"+ptask->_inDriver.text+"</IN_DRIVER>\r\n";
			strXml += "		<OUT_DRIVER type=\""+ptask->_outDriver.type+"\" name=\""+ptask->_outDriver.name+"\">"+ptask->_outDriver.text+"</OUT_DRIVER>\r\n";
			
			strXml += "		<IN_ELLIPSE type=\""+ptask->_inEllipse.type+"\" name=\""+ptask->_inEllipse.name+"\">"+ptask->_inEllipse.text+"</IN_ELLIPSE>\r\n";
			strXml += "		<OUT_ELLIPSE type=\""+ptask->_outEllipse.type+"\" name=\""+ptask->_outEllipse.name+"\">"+ptask->_outEllipse.text+"</OUT_ELLIPSE>\r\n";

			strXml += "		<IN_COORDTYPE type=\""+ptask->_inCoordType.type+"\" name=\""+ptask->_inCoordType.name+"\">"+ptask->_inCoordType.text+"</IN_COORDTYPE>\r\n";
			strXml += "		<OUT_COORDTYPE type=\""+ptask->_outCoordType.type+"\" name=\""+ptask->_outCoordType.name+"\">"+ptask->_outCoordType.text+"</OUT_COORDTYPE>\r\n";

			strXml += "		<InCentr_long type=\""+ptask->_inCentralMeridian.type+"\" name=\""+ptask->_inCentralMeridian.name+"\">"+ptask->_inCentralMeridian.text+"</InCentr_long>\r\n";
			strXml += "		<OutCentr_long type=\""+ptask->_outCentralMeridian.type+"\" name=\""+ptask->_outCentralMeridian.name+"\">"+ptask->_outCentralMeridian.text+"</OutCentr_long>\r\n";

			strXml += "		<Type type=\""+ptask->_type.type+"\" name=\""+ptask->_type.name+"\">"+ptask->_type.text+"</Type>\r\n";
			strXml += "		<Status type=\""+ptask->_status.type+"\" name=\""+ptask->_status.name+"\">"+ptask->_status.text+"</Status>\r\n";

			strXml += "		<CurTable type=\""+ptask->_curPart.type+"\" name=\""+ptask->_curPart.name+"\">"+ptask->_curPart.text+"</CurTable>\r\n";

			strXml += "		<TableList type=\""+ptask->_parts.type+"\" name=\""+ptask->_parts.name+"\">\r\n";
			for(int m=0; m<ptask->_parts.m_Part.GetCount();m++)
			{
				_Part pPart = ptask->_parts.m_Part.GetAt(m);
				strXml += "			<tab type=\""+pPart.type+"\" name=\""+pPart.name+"\">"+pPart.text+"</tab>\r\n";
			}
			strXml += "		</TableList>\r\n";

			//增加控制点路径 add by chenyong 2013-3-28
			strXml += "		<ControlPath type=\""+ptask->_controlPath.type+"\" name=\""+ptask->_controlPath.name+"\">"+ptask->_controlPath.text+"</ControlPath>\r\n";
			strXml += "		<TransModel type=\""+ptask->_transModel.type+"\" name=\""+ptask->_transModel.name+"\">"+ptask->_transModel.text+"</TransModel>\r\n";
			
			strXml += "	</CDeuTask>\r\n";
		}
		
		strXml += "</TaskList>\r\n";

		HANDLE hFile = CreateFile(sz_PathFile, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if(hFile != NULL){
			CFile m_File(hFile);
			m_File.Write(strXml, strXml.GetLength());
			m_File.Close();
		}
	}

	//写文件格式名
	void CDeuXmlWriter::BuildFormatXml(LPCSTR sz_PathFile, p_StrFormatList pTasks)
	{
		CString strXml, strId;
		strXml = sz_Xml_Head;
		strXml += "<FormatList type=\""+pTasks->type+"\" name=\""+pTasks->name+"\">\r\n";

		for(int n=0; n<pTasks->FormatTypeList.size(); n++)
		{
			p_StrFormatTypeList ptask = pTasks->FormatTypeList[n];
	
			strXml += "	<Formats type=\""+ptask->type+"\" name=\""+ptask->name+"\">\r\n";
			
			for(int m=0; m<ptask->TypeList.size(); m++)
			{
				_StrFormatType pPart = ptask->TypeList[m];
				strXml += "			<Format type=\""+pPart.type+"\" name=\""+pPart.name+"\">"+pPart.text+"</Format>\r\n";
			}
			strXml += "	</Formats>\r\n";
		}

		strXml += "</FormatList>\r\n";

		HANDLE hFile = CreateFile(sz_PathFile, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if(hFile != NULL){
			CFile m_File(hFile);
			m_File.Write(strXml, strXml.GetLength());
			m_File.Close();
		}
	}
}
