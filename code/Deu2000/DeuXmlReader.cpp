#include "StdAfx.h"
#include "DeuGlobalParam.h"
#include "DeuXmlReader.h"

//BSTR bstr;
//_nodePtr->get_xml(&bstr);
//TRACE("%s", _com_util::ConvertBSTRToString(bstr));

namespace DeuXmlMapping
{
	CDeuXmlReader::CDeuXmlReader()
	{	
	}

	CDeuXmlReader::~CDeuXmlReader(void)
	{
	}

	//填充映射结构
	void CDeuXmlReader::MappingGeoData(p_GeoDataXml pGeoDataXml)
	{
		pGeoDataXml->name = "";
		GetAllProjected(&pGeoDataXml->ProjectedNode);
		GetAllGeoDetic(&pGeoDataXml->GeodeticNode);
		GetUnits(&pGeoDataXml->UnitsNode);
	}

	//追加填充映射结构
	void CDeuXmlReader::AppendMappingGeoData(p_GeoDataXml pGeoDataXml, CString strFile)
	{
		MSXML2::IXMLDOMDocumentPtr _pDoc;

		CString strXml;
		strXml = GetStylesPath();
		strXml = strXml+"\\";
		strXml.Append(strFile);
		
		HRESULT	hr;
		hr = _pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument60));
		if(FAILED(hr))
		{  
			//MessageBox("无法创建DOMDocument对象，请检查是否安装了MS XML Parser 运行库!"); 
			return ;
		}

		_pDoc->load((_bstr_t)strXml);
		pGeoDataXml->name = "";

		MSXML2::IXMLDOMNodePtr _pNode;
		MSXML2::IXMLDOMNodePtr _pChildNode;
		_pNode = _pDoc->selectSingleNode("//projected");

		RemoveComment(_pNode); //过滤注释

		this->GetAttrValue(_pNode, "name", &pGeoDataXml->ProjectedNode.name);
		this->GetAttrValue(_pNode, "type", &pGeoDataXml->ProjectedNode.name);

		int k=0;
		//填充54
		for(k=0; k<_pNode->childNodes->length; k++)
		{		
			_ProjectedSeries m_ProjectedSeries;

			_pChildNode = _pNode->childNodes->Getitem(k);
			RemoveComment(_pChildNode);

			this->GetAttrValue(_pChildNode, "name", &m_ProjectedSeries.name);
			this->GetAttrValue(_pChildNode, "type", &m_ProjectedSeries.type);

			m_ProjectedSeries._coordinateType = GeoProjected;
			m_ProjectedSeries._tranStandard   = Peking54;

			//1. Name 节点		
			FillName(_pChildNode->childNodes->Getitem(0), &(m_ProjectedSeries._name));

			//2. Remark 节点	
			FillRemark(_pChildNode->childNodes->Getitem(1), &(m_ProjectedSeries._remark));

			//3. Envelope		
			FillEnvelope(_pChildNode->childNodes->Getitem(2), &(m_ProjectedSeries._envelope));

			//4. PointStyle
			FillProjectionPointStyle(_pChildNode->childNodes->Getitem(3), &(m_ProjectedSeries._pointStyle));

			//5. GeodeticPointor
			FillGeodeticPointor(_pChildNode->childNodes->Getitem(4), &(m_ProjectedSeries._geodeticPointor));

			//6.Projection
			FillProjection(_pChildNode->childNodes->Getitem(5), &(m_ProjectedSeries._projection));

			//7. CentralMeridian		
			FillCentralMeridian(_pChildNode->childNodes->Getitem(6), &(m_ProjectedSeries._centralMeridian));

			//8. FalseEasting
			FillFalseEasting(_pChildNode->childNodes->Getitem(7), &(m_ProjectedSeries._falseEasting));

			//9. FalseNorthing
			FillFalseNorthing(_pChildNode->childNodes->Getitem(8), &(m_ProjectedSeries._falseNorthing));

			//10. LatitudeOfOrigin
			FillLatitudeOfOrigin(_pChildNode->childNodes->Getitem(9), &(m_ProjectedSeries._latitudeOfOrigin));

			//11. ScaleFactor
			FillScaleFactor(_pChildNode->childNodes->Getitem(10), &(m_ProjectedSeries._scaleFactor));

			//12.FillCSType
			FillCSType(_pChildNode->childNodes->Getitem(11), &(m_ProjectedSeries._csType));

			pGeoDataXml->ProjectedNode.pProjectedSeries.Add(m_ProjectedSeries);
		}

		_pNode = _pDoc->selectSingleNode("//geodetic");
		RemoveComment(_pNode); //过滤注释

		/*if(_pNode == 0x00000000) return;*/
		char sz_Tmp[MAX_PATH];
		ZeroMemory(sz_Tmp, sizeof(sz_Tmp));
		this->GetAttrValue(_pNode, "name", &pGeoDataXml->GeodeticNode.name);
		this->GetAttrValue(_pNode, "type", &pGeoDataXml->GeodeticNode.type);

		int pp = _pNode->childNodes->length;
		for(int k=0; k<pp; k++)
		{		
			_GeodeticSeries mGeodeticSeries;
			_pChildNode = _pNode->childNodes->Getitem(k);
			RemoveComment(_pChildNode); //过滤注释

			//BSTR bstr;
			//_pChildNode->get_xml(&bstr);		

			this->GetAttrValue(_pChildNode, "name", &mGeodeticSeries.name);
			this->GetAttrValue(_pChildNode, "type", &mGeodeticSeries.type);

			mGeodeticSeries._coordinateType = GeoDetic;
			//pGeodeticSeries->_tranStandard   = Peking54;

			//1. Name 节点
			FillName(_pChildNode->childNodes->Getitem(0), &(mGeodeticSeries._name));

			//2. Remark 节点
			FillRemark(_pChildNode->childNodes->Getitem(1), &(mGeodeticSeries._remark));

			//3. Envelope
			FillEnvelope(_pChildNode->childNodes->Getitem(2), &(mGeodeticSeries._envelope));

			//4. PointStyle
			FillGeoDeticPointStyle(_pChildNode->childNodes->Getitem(3), &(mGeodeticSeries._pointStyle));

			//5.Datum		
			FillDatum(_pChildNode->childNodes->Getitem(4), &(mGeodeticSeries._datum));

			//6.FillCSType
			FillCSType(_pChildNode->childNodes->Getitem(5), &(mGeodeticSeries._csType));

			pGeoDataXml->GeodeticNode.pGeodeticSeries.Add(mGeodeticSeries);
		}
	}

	//填充映射结构
	void CDeuXmlReader::MappingGustomData(p_GeoDataXml pGeoDataXml)
	{
		pGeoDataXml->name = "";
		this->GetCustomProjected(&pGeoDataXml->ProjectedNode);
		this->GetCustomGeoDetic(&pGeoDataXml->GeodeticNode);
	}

	//const char *sz_path
	void CDeuXmlReader::LoadXml(LPCSTR sz_FileName)
	{
		CString strXml;
		strXml = GetStylesPath();
		strXml = strXml+"\\";
		strXml.Append(sz_FileName);

		HRESULT	hr;
		hr = pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument60));
		if(FAILED(hr))
		{  
			//MessageBox("无法创建DOMDocument对象，请检查是否安装了MS XML Parser 运行库!"); 
			return ;
		}
		pDoc->load((_bstr_t)strXml);

		return;
	}

	//const char *sz_path
	bool CDeuXmlReader::LoadFile(LPCSTR sz_FileName)
	{
		HRESULT	hr;
		hr = pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument60));
		if(FAILED(hr))
		{  
			//AfxMessageBox("无法创建DOMDocument对象，请检查是否安装了MS XML Parser 运行库!"); 
			return false;
		}

		VARIANT_BOOL aa = pDoc->load((_bstr_t)sz_FileName); //False = 0; True = -1
		if (!aa )
		{
			//AfxMessageBox("加载控制点文件失败!"); 
			return false;
		}

		return true;
	}

	void CDeuXmlReader::Free()
	{
		pDoc.Release();
	}

	//清除结构
	void CDeuXmlReader::ReleaseGeoDataMapping(p_GeoDataXml pGeoDataXml)
	{
		//清除大地
		int n = 0;
		for(n=0; n<pGeoDataXml->GeodeticNode.pGeodeticSeries.GetCount(); n++)
		{	
			//delete pGeoDataXml->GeodeticNode.pGeodeticSeries.GetAt(n);
			pGeoDataXml->GeodeticNode.pGeodeticSeries.RemoveAt(n);		
		}	
		pGeoDataXml->GeodeticNode.pGeodeticSeries.RemoveAll();

		//清除投影
		for(n=0; n<pGeoDataXml->ProjectedNode.pProjectedSeries.GetCount(); n++)
		{
			pGeoDataXml->ProjectedNode.pProjectedSeries.RemoveAt(n);
		}
		pGeoDataXml->ProjectedNode.pProjectedSeries.RemoveAll();
	}

	void CDeuXmlReader::ReleseTaskMapping(p_Tasks pTasks)
	{
		//释放任务指针
		while( pTasks->_task.GetCount()>0 )
		{
			_Task* pTask = pTasks->_task.GetAt(0) ;
			pTasks->_task.RemoveAt(0);
			pTask->_parts.m_Part.RemoveAll();

			delete pTask;
		}	
	}

	void CDeuXmlReader::GetAttrValue(MSXML2::IXMLDOMNodePtr &p_Node, LPCSTR sz_name,  CString *strOutput)
	{
		_variant_t	variantValue;
		//属性映射
		MSXML2::IXMLDOMNamedNodeMapPtr pAttrMap;
		//属性映射节点
		MSXML2::IXMLDOMNodePtr pNodeAttr;

		//映射属性
		p_Node->get_attributes(&pAttrMap);
		pNodeAttr = pAttrMap->getNamedItem(sz_name);
		pNodeAttr->get_nodeTypedValue(&variantValue);
		strOutput->Format((_bstr_t)variantValue);
	}

	void CDeuXmlReader::GetElemText(MSXML2::IXMLDOMNodePtr &p_Node, CString *strOutput)
	{
		BSTR bTmp;
		p_Node->get_text(&bTmp);
		strOutput->Format((_bstr_t)bTmp);
	}

	//获取大地坐标节点
	void CDeuXmlReader::GetAllGeoDetic(_Geodetic* pGeodetic)
	{
		MSXML2::IXMLDOMNodeListPtr pList;
		MSXML2::IXMLDOMNodePtr _pNode;
		MSXML2::IXMLDOMNodePtr _pChildNode;
		_pNode = pDoc->selectSingleNode("//geodetic");

		RemoveComment(_pNode); //过滤注释

		/*if(_pNode == 0x00000000) return;*/

		this->GetAttrValue(_pNode, "name", &pGeodetic->name);
		this->GetAttrValue(_pNode, "type", &pGeodetic->type);

		int pp = _pNode->childNodes->length;
		for(int k=0; k<pp; k++)
		{		
			_GeodeticSeries m_GeodeticSeries;
			_pChildNode = _pNode->childNodes->Getitem(k);
			RemoveComment(_pChildNode); //过滤注释
			
			this->GetAttrValue(_pChildNode, "name", &m_GeodeticSeries.name);
			this->GetAttrValue(_pChildNode, "type", &m_GeodeticSeries.type);

			m_GeodeticSeries._coordinateType = GeoDetic;
			//pGeodeticSeries->_tranStandard   = Peking54;

			//1. Name 节点
			FillName(_pChildNode->childNodes->Getitem(0), &(m_GeodeticSeries._name));

			//2. Remark 节点
			FillRemark(_pChildNode->childNodes->Getitem(1), &(m_GeodeticSeries._remark));

			//3. Envelope
			FillEnvelope(_pChildNode->childNodes->Getitem(2), &(m_GeodeticSeries._envelope));

			//4. PointStyle
			FillGeoDeticPointStyle(_pChildNode->childNodes->Getitem(3), &(m_GeodeticSeries._pointStyle));

			//5.Datum		
			FillDatum(_pChildNode->childNodes->Getitem(4), &(m_GeodeticSeries._datum));

			//6.FillCSType
			FillCSType(_pChildNode->childNodes->Getitem(5), &(m_GeodeticSeries._csType));

			pGeodetic->pGeodeticSeries.Add(m_GeodeticSeries);
		}
	}

	//获取投影坐标节点
	// 备注：分开循环，留出扩展，防止以后各自的xml段有自身的结构变化
	void CDeuXmlReader::GetAllProjected(Projected* pProjected)
	{
		MSXML2::IXMLDOMNodeListPtr pList;
		MSXML2::IXMLDOMNodePtr _pNode;
		MSXML2::IXMLDOMNodePtr _pChildNode;
		_pNode = pDoc->selectSingleNode("//projected");

		RemoveComment(_pNode); //过滤注释

		this->GetAttrValue(_pNode, "name", &pProjected->name);
		this->GetAttrValue(_pNode, "type", &pProjected->type);

		int k=0;
		//填充54
		for(k=0; k<_pNode->childNodes->length; k++)
		{		
			_ProjectedSeries m_ProjectedSeries;

			_pChildNode = _pNode->childNodes->Getitem(k);

			RemoveComment(_pChildNode);

			this->GetAttrValue(_pChildNode, "name", &m_ProjectedSeries.name);
			this->GetAttrValue(_pChildNode, "type", &m_ProjectedSeries.type);

			m_ProjectedSeries._coordinateType = GeoProjected;

			if(m_ProjectedSeries.name.Compare("beijing54") == 0  )
				m_ProjectedSeries._tranStandard   = Peking54;
			else if(m_ProjectedSeries.name.Compare("XiAn80") == 0  )
				m_ProjectedSeries._tranStandard   = XiAn80;
			else if(m_ProjectedSeries.name.Compare("WGS 84") == 0  )
				m_ProjectedSeries._tranStandard   = WGS84;
			else if(m_ProjectedSeries.name.Compare("cgcs2000") == 0  )
				m_ProjectedSeries._tranStandard   = CGCS2000;

			//1. Name 节点		
			FillName(_pChildNode->childNodes->Getitem(0), &(m_ProjectedSeries._name));

			//2. Remark 节点	
			FillRemark(_pChildNode->childNodes->Getitem(1), &(m_ProjectedSeries._remark));

			//3. Envelope		
			FillEnvelope(_pChildNode->childNodes->Getitem(2), &(m_ProjectedSeries._envelope));

			//4. PointStyle
			FillProjectionPointStyle(_pChildNode->childNodes->Getitem(3), &(m_ProjectedSeries._pointStyle));

			//5. GeodeticPointor
			FillGeodeticPointor(_pChildNode->childNodes->Getitem(4), &(m_ProjectedSeries._geodeticPointor));

			//6.Projection
			FillProjection(_pChildNode->childNodes->Getitem(5), &(m_ProjectedSeries._projection));

			//7. CentralMeridian		
			FillCentralMeridian(_pChildNode->childNodes->Getitem(6), &(m_ProjectedSeries._centralMeridian));

			//8. FalseEasting
			FillFalseEasting(_pChildNode->childNodes->Getitem(7), &(m_ProjectedSeries._falseEasting));

			//9. FalseNorthing
			FillFalseNorthing(_pChildNode->childNodes->Getitem(8), &(m_ProjectedSeries._falseNorthing));

			//10. LatitudeOfOrigin
			FillLatitudeOfOrigin(_pChildNode->childNodes->Getitem(9), &(m_ProjectedSeries._latitudeOfOrigin));

			//11. ScaleFactor
			FillScaleFactor(_pChildNode->childNodes->Getitem(10), &(m_ProjectedSeries._scaleFactor));

			//12.FillCSType
			FillCSType(_pChildNode->childNodes->Getitem(11), &(m_ProjectedSeries._csType));

			pProjected->pProjectedSeries.Add(m_ProjectedSeries);
		}
	}

	//获取用户自定义大地坐标
	void CDeuXmlReader::GetCustomGeoDetic(_Geodetic* pGeodetic)
	{
		MSXML2::IXMLDOMNodeListPtr pList;
		MSXML2::IXMLDOMNodePtr _pNode;
		MSXML2::IXMLDOMNodePtr _pChildNode;
		_pNode = pDoc->selectSingleNode("//geodetic");

		RemoveComment(_pNode); //过滤注释

		/*if(_pNode == 0x00000000) return;*/

		this->GetAttrValue(_pNode, "name", &pGeodetic->name);
		this->GetAttrValue(_pNode, "type", &pGeodetic->type);

		int pp = _pNode->childNodes->length;
		for(int k=0; k<pp; k++)
		{		
			_GeodeticSeries pGeodeticSeries;
			
			_pChildNode = _pNode->childNodes->Getitem(k);

			RemoveComment(_pChildNode); //过滤注释

			this->GetAttrValue(_pChildNode, "name", &pGeodeticSeries.name);
			this->GetAttrValue(_pChildNode, "type", &pGeodeticSeries.type);
			pGeodeticSeries._coordinateType = GeoDetic;
			//pGeodeticSeries->_tranStandard   = Peking54;

			//1. Name 节点
			FillName(_pChildNode->childNodes->Getitem(0), &(pGeodeticSeries._name));

			//2. Remark 节点
			FillRemark(_pChildNode->childNodes->Getitem(1), &(pGeodeticSeries._remark));
			
			//3. Envelope
			FillEnvelope(_pChildNode->childNodes->Getitem(2), &(pGeodeticSeries._envelope));

			//4. PointStyle
			FillGeoDeticPointStyle(_pChildNode->childNodes->Getitem(3), &(pGeodeticSeries._pointStyle));
			
			//5.Datum		
			FillDatum(_pChildNode->childNodes->Getitem(4), &(pGeodeticSeries._datum));

			//6.FillCSType
			FillCSType(_pChildNode->childNodes->Getitem(5), &(pGeodeticSeries._csType));

			pGeodetic->pGeodeticSeries.Add(pGeodeticSeries);
		}
	}

	////获取用户自定义投影坐标
	// 备注：分开循环，留出扩展，防止以后各自的xml段有自身的结构变化
	void CDeuXmlReader::GetCustomProjected(Projected* pProjected)
	{
		MSXML2::IXMLDOMNodeListPtr pList;
		MSXML2::IXMLDOMNodePtr _pNode;
		MSXML2::IXMLDOMNodePtr _pChildNode;
		_pNode = pDoc->selectSingleNode("//projected");
		
		RemoveComment(_pNode); //过滤注释

		this->GetAttrValue(_pNode, "name", &pProjected->name);
		this->GetAttrValue(_pNode, "type", &pProjected->type);

		int k=0;
		//填充54
		for(k=0; k<_pNode->childNodes->length; k++)
		{		
			_ProjectedSeries m_ProjectedSeries;

			_pChildNode = _pNode->childNodes->Getitem(k);

			RemoveComment(_pChildNode);

			this->GetAttrValue(_pChildNode, "name", &m_ProjectedSeries.name);
			this->GetAttrValue(_pChildNode, "type", &m_ProjectedSeries.type);
			m_ProjectedSeries._coordinateType = GeoProjected;
			
			if(m_ProjectedSeries.name.Find("beijing54") == 0  )
				m_ProjectedSeries._tranStandard   = Peking54;
			else if(m_ProjectedSeries.name.Find("XiAn80") == 0  )
				m_ProjectedSeries._tranStandard   = XiAn80;
			else if(m_ProjectedSeries.name.Find("WGS 84") == 0  )
				m_ProjectedSeries._tranStandard   = WGS84;
			else if(m_ProjectedSeries.name.Find("cgcs2000") == 0  )
				m_ProjectedSeries._tranStandard   = CGCS2000;

			//1. Name 节点		
			FillName(_pChildNode->childNodes->Getitem(0), &(m_ProjectedSeries._name));

			//2. Remark 节点	
			FillRemark(_pChildNode->childNodes->Getitem(1), &(m_ProjectedSeries._remark));

			//3. Envelope		
			FillEnvelope(_pChildNode->childNodes->Getitem(2), &(m_ProjectedSeries._envelope));

			//4. PointStyle
			FillProjectionPointStyle(_pChildNode->childNodes->Getitem(3), &(m_ProjectedSeries._pointStyle));

			//5. GeodeticPointor
			FillGeodeticPointor(_pChildNode->childNodes->Getitem(4), &(m_ProjectedSeries._geodeticPointor));

			//6.Projection
			FillProjection(_pChildNode->childNodes->Getitem(5), &(m_ProjectedSeries._projection));

			//7. CentralMeridian		
			FillCentralMeridian(_pChildNode->childNodes->Getitem(6), &(m_ProjectedSeries._centralMeridian));

			//8. FalseEasting
			FillFalseEasting(_pChildNode->childNodes->Getitem(7), &(m_ProjectedSeries._falseEasting));

			//9. FalseNorthing
			FillFalseNorthing(_pChildNode->childNodes->Getitem(8), &(m_ProjectedSeries._falseNorthing));

			//10. LatitudeOfOrigin
			FillLatitudeOfOrigin(_pChildNode->childNodes->Getitem(9), &(m_ProjectedSeries._latitudeOfOrigin));

			//11. ScaleFactor
			FillScaleFactor(_pChildNode->childNodes->Getitem(10), &(m_ProjectedSeries._scaleFactor));

			//12.FillCSType
			FillCSType(_pChildNode->childNodes->Getitem(11), &(m_ProjectedSeries._csType));

			pProjected->pProjectedSeries.Add(m_ProjectedSeries);
		}
	}
	
	void CDeuXmlReader::GetUnits(_Units* pUnits)
	{
		//CString strTemp;
		_variant_t	variantValue;

		MSXML2::IXMLDOMNodePtr pNode, pChildNode;
		MSXML2::IXMLDOMNodeListPtr pNodeList;

		_UnitsGeodetic _unitsGeodetic;
		pNode = pDoc->selectSingleNode("//UnitGeodetic");

		//if(pNode == 0x00000000) return;
		pNodeList = pNode->GetchildNodes();
		if(pNodeList->length > 0)
		{		
			pChildNode = pNodeList->Getitem(0);
			this->GetElemText(pChildNode, &_unitsGeodetic.X);

			pChildNode = pNodeList->Getitem(1);
			this->GetElemText(pChildNode, &_unitsGeodetic.Y );

			pChildNode = pNodeList->Getitem(2);
			this->GetElemText(pChildNode, &_unitsGeodetic.Z);
		}

		_UnitsGeocentric _unitsGeocentric;
		pNode = pDoc->selectSingleNode("//UnitGeocentric");
		pNodeList = pNode->GetchildNodes();
		if(pNodeList->length > 0)
		{		
			pChildNode = pNodeList->Getitem(0);
			this->GetElemText(pChildNode, &_unitsGeocentric.X);

			pChildNode = pNodeList->Getitem(1);
			this->GetElemText(pChildNode, &_unitsGeocentric.Y );

			pChildNode = pNodeList->Getitem(2);
			this->GetElemText(pChildNode, &_unitsGeocentric.Z);
		}
		
		_UnitsPlane _unitsPlane;
		pNode = pDoc->selectSingleNode("//UnitPlane");
		pNodeList = pNode->GetchildNodes();
		if(pNodeList->length > 0)
		{		
			pChildNode = pNodeList->Getitem(0);
			this->GetElemText(pChildNode, &_unitsPlane.X);

			pChildNode = pNodeList->Getitem(1);
			this->GetElemText(pChildNode, &_unitsPlane.Y);

			pChildNode = pNodeList->Getitem(2);
			this->GetElemText(pChildNode, &_unitsPlane.Z);
		}

		pUnits->Geocentric  = _unitsGeocentric;
		pUnits->Geodetic	= _unitsGeodetic;
		pUnits->Plane		= _unitsPlane;
	}

	void CDeuXmlReader::FillUnit(MSXML2::IXMLDOMNodePtr &pCurrNode, _Unit* pUnit)
	{
		RemoveComment(pCurrNode); //过滤注释
		
		this->GetAttrValue(pCurrNode, "name", &pUnit->name);
		this->GetAttrValue(pCurrNode, "type", &pUnit->type);
		this->GetElemText(pCurrNode, &pUnit->text);
	}

	//填充投影坐标元素节点
	void CDeuXmlReader::FillProjectedBeking54(int nIndex, _ProjectedSeries* _pProjectedSeries)
	{
		MSXML2::IXMLDOMNodePtr pNode, pChildNode;
		MSXML2::IXMLDOMNodeListPtr pNodeList;
		//MSXML2::IXMLDOMDocument p_doc;
		//pNode = pDoc->selectSingleNode("//geodetic");
		
		pNodeList =  pDoc->selectNodes("//projectedbeijing54");
		if((pNodeList->length > 0) && (pNodeList->length > nIndex))
		{
			pNode = pNodeList->Getitem(nIndex);
			RemoveComment(pNode);
			
			int n = pNode->childNodes->length;

			this->GetAttrValue(pNode, "name", &_pProjectedSeries->name);
			this->GetAttrValue(pNode, "type", &_pProjectedSeries->type);

			_pProjectedSeries->_coordinateType = GeoProjected;
			_pProjectedSeries->_tranStandard   = Peking54;
		
			//1. Name 节点		
			FillName(pNode->childNodes->Getitem(0), &(_pProjectedSeries->_name));
			
			//2. Remark 节点	
			FillRemark(pNode->childNodes->Getitem(1), &(_pProjectedSeries->_remark));
			
			//3. Envelope		
			FillEnvelope(pNode->childNodes->Getitem(2), &(_pProjectedSeries->_envelope));

			//4. PointStyle
			FillProjectionPointStyle(pNode->childNodes->Getitem(3), &(_pProjectedSeries->_pointStyle));
			
			//5. GeodeticPointor
			FillGeodeticPointor(pNode->childNodes->Getitem(4), &(_pProjectedSeries->_geodeticPointor));

			//6.Projection
			FillProjection(pNode->childNodes->Getitem(5), &(_pProjectedSeries->_projection));

			//7. CentralMeridian		
			FillCentralMeridian(pNode->childNodes->Getitem(6), &(_pProjectedSeries->_centralMeridian));

			//8. FalseEasting
			FillFalseEasting(pNode->childNodes->Getitem(7), &(_pProjectedSeries->_falseEasting));

			//9. FalseNorthing
			FillFalseNorthing(pNode->childNodes->Getitem(8), &(_pProjectedSeries->_falseNorthing));

			//10. LatitudeOfOrigin
			FillLatitudeOfOrigin(pNode->childNodes->Getitem(9), &(_pProjectedSeries->_latitudeOfOrigin));

			//11. ScaleFactor
			FillScaleFactor(pNode->childNodes->Getitem(10), &(_pProjectedSeries->_scaleFactor));

			//12.FillCSType
			FillCSType(pNode->childNodes->Getitem(11), &(_pProjectedSeries->_csType));

			pNode = NULL;
		}
	}

	void CDeuXmlReader::FillProjectedXiAn80(int nIndex, _ProjectedSeries* _pProjectedSeries)
	{
		MSXML2::IXMLDOMNodePtr pNode, pChildNode;
		MSXML2::IXMLDOMNodeListPtr pNodeList;

		//pNode = pDoc->selectSingleNode("//geodetic");

		pNodeList =  pDoc->selectNodes("//projectedXiAn80");
		if((pNodeList->length > 0) && (pNodeList->length > nIndex))
		{
			pNode = pNodeList->Getitem(nIndex);
			RemoveComment(pNode); //过滤注释
			
			this->GetAttrValue(pNode, "name", &_pProjectedSeries->name);
			this->GetAttrValue(pNode, "type", &_pProjectedSeries->type);
			
			_pProjectedSeries->_coordinateType = GeoProjected;
			_pProjectedSeries->_tranStandard   = XiAn80;

			//1. Name 节点		
			FillName(pNode->childNodes->Getitem(0), &(_pProjectedSeries->_name));

			//2. Remark 节点	
			FillRemark(pNode->childNodes->Getitem(1), &(_pProjectedSeries->_remark));

			//3. Envelope		
			FillEnvelope(pNode->childNodes->Getitem(2), &(_pProjectedSeries->_envelope));

			//4. PointStyle
			FillProjectionPointStyle(pNode->childNodes->Getitem(3), &(_pProjectedSeries->_pointStyle));

			//5. GeodeticPointor
			FillGeodeticPointor(pNode->childNodes->Getitem(4), &(_pProjectedSeries->_geodeticPointor));

			//6.Projection
			FillProjection(pNode->childNodes->Getitem(5), &(_pProjectedSeries->_projection));

			//7. CentralMeridian
			FillCentralMeridian(pNode->childNodes->Getitem(6), &(_pProjectedSeries->_centralMeridian));

			//8. FalseEasting
			FillFalseEasting(pNode->childNodes->Getitem(7), &(_pProjectedSeries->_falseEasting));

			//9. FalseNorthing
			FillFalseNorthing(pNode->childNodes->Getitem(8), &(_pProjectedSeries->_falseNorthing));

			//10. LatitudeOfOrigin
			FillLatitudeOfOrigin(pNode->childNodes->Getitem(9), &(_pProjectedSeries->_latitudeOfOrigin));

			//11. ScaleFactor
			FillScaleFactor(pNode->childNodes->Getitem(10), &(_pProjectedSeries->_scaleFactor));

			//12.FillCSType
			FillCSType(pNode->childNodes->Getitem(11), &(_pProjectedSeries->_csType));
		}
	}

	void CDeuXmlReader::FillProjectedWGS84(int nIndex, _ProjectedSeries* _pProjectedSeries)
	{
		MSXML2::IXMLDOMNodePtr pNode, pChildNode;
		MSXML2::IXMLDOMNodeListPtr pNodeList;

		//pNode = pDoc->selectSingleNode("//geodetic");
		pNodeList =  pDoc->selectNodes("//projectedWGS84");
		if((pNodeList->length > 0) && (pNodeList->length > nIndex))
		{
			pNode = pNodeList->Getitem(nIndex);
			RemoveComment(pNode); //过滤注释
			
			this->GetAttrValue(pNode, "name", &_pProjectedSeries->name);
			this->GetAttrValue(pNode, "type", &_pProjectedSeries->type);
			
			_pProjectedSeries->_coordinateType = GeoProjected;
			_pProjectedSeries->_tranStandard   = WGS84;

			//1. Name 节点		
			FillName(pNode->childNodes->Getitem(0), &(_pProjectedSeries->_name));

			//2. Remark 节点	
			FillRemark(pNode->childNodes->Getitem(1), &(_pProjectedSeries->_remark));

			//3. Envelope		
			FillEnvelope(pNode->childNodes->Getitem(2), &(_pProjectedSeries->_envelope));

			//4. PointStyle
			FillProjectionPointStyle(pNode->childNodes->Getitem(3), &(_pProjectedSeries->_pointStyle));

			//5. GeodeticPointor
			FillGeodeticPointor(pNode->childNodes->Getitem(4), &(_pProjectedSeries->_geodeticPointor));

			//6.Projection
			FillProjection(pNode->childNodes->Getitem(5), &(_pProjectedSeries->_projection));

			//7. CentralMeridian
			FillCentralMeridian(pNode->childNodes->Getitem(6), &(_pProjectedSeries->_centralMeridian));

			//8. FalseEasting
			FillFalseEasting(pNode->childNodes->Getitem(7), &(_pProjectedSeries->_falseEasting));

			//9. FalseNorthing
			FillFalseNorthing(pNode->childNodes->Getitem(8), &(_pProjectedSeries->_falseNorthing));

			//10. LatitudeOfOrigin
			FillLatitudeOfOrigin(pNode->childNodes->Getitem(9), &(_pProjectedSeries->_latitudeOfOrigin));

			//11. ScaleFactor
			FillScaleFactor(pNode->childNodes->Getitem(10), &(_pProjectedSeries->_scaleFactor));

			//12.FillCSType
			FillCSType(pNode->childNodes->Getitem(11), &(_pProjectedSeries->_csType));
		}
	}

	void CDeuXmlReader::FillProjectedCGCS2000(int nIndex, _ProjectedSeries* _pProjectedSeries)
	{
		MSXML2::IXMLDOMNodePtr pNode, pChildNode;
		MSXML2::IXMLDOMNodeListPtr pNodeList;

		//pNode = pDoc->selectSingleNode("//geodetic");
		pNodeList =  pDoc->selectNodes("//projectedcgcs2000");
		if((pNodeList->length > 0) && (pNodeList->length > nIndex))
		{
			pNode = pNodeList->Getitem(nIndex);
			RemoveComment(pNode); //过滤注释
			
			this->GetAttrValue(pNode, "name", &_pProjectedSeries->name);
			this->GetAttrValue(pNode, "type", &_pProjectedSeries->type);
			
			_pProjectedSeries->_coordinateType = GeoProjected;
			_pProjectedSeries->_tranStandard   = CGCS2000;

			//1. Name 节点		
			FillName(pNode->childNodes->Getitem(0), &(_pProjectedSeries->_name));

			//2. Remark 节点	
			FillRemark(pNode->childNodes->Getitem(1), &(_pProjectedSeries->_remark));

			//3. Envelope		
			FillEnvelope(pNode->childNodes->Getitem(2), &(_pProjectedSeries->_envelope));

			//4. PointStyle
			FillProjectionPointStyle(pNode->childNodes->Getitem(3), &(_pProjectedSeries->_pointStyle));

			//5. GeodeticPointor
			FillGeodeticPointor(pNode->childNodes->Getitem(4), &(_pProjectedSeries->_geodeticPointor));

			//6.Projection
			FillProjection(pNode->childNodes->Getitem(5), &(_pProjectedSeries->_projection));

			//7. CentralMeridian
			FillCentralMeridian(pNode->childNodes->Getitem(6), &(_pProjectedSeries->_centralMeridian));

			//8. FalseEasting
			FillFalseEasting(pNode->childNodes->Getitem(7), &(_pProjectedSeries->_falseEasting));

			//9. FalseNorthing
			FillFalseNorthing(pNode->childNodes->Getitem(8), &(_pProjectedSeries->_falseNorthing));

			//10. LatitudeOfOrigin
			FillLatitudeOfOrigin(pNode->childNodes->Getitem(9), &(_pProjectedSeries->_latitudeOfOrigin));

			//11. ScaleFactor
			FillScaleFactor(pNode->childNodes->Getitem(10), &(_pProjectedSeries->_scaleFactor));

			//12.FillCSType
			FillCSType(pNode->childNodes->Getitem(11), &(_pProjectedSeries->_csType));
		}
	}

	void CDeuXmlReader::FillGeoDeticBeking54(int nIndex, _GeodeticSeries* pBeking54)
	{
		MSXML2::IXMLDOMNodePtr pNode, pChildNode;
		MSXML2::IXMLDOMNodeListPtr pNodeList;

		pNodeList =  pDoc->selectNodes("//geodeticbeijing54");
		if((pNodeList->length > 0) && (pNodeList->length > nIndex))
		{
			pNode = pNodeList->Getitem(nIndex);
			RemoveComment(pNode); //过滤注释
			
			this->GetAttrValue(pNode, "name", &pBeking54->name);
			this->GetAttrValue(pNode, "type", &pBeking54->type);
			
			pBeking54->_coordinateType = GeoDetic;
			pBeking54->_tranStandard   = Peking54;

			//1. Name 节点
			FillName(pNode->childNodes->Getitem(0), &(pBeking54->_name));

			//2. Remark 节点
			FillRemark(pNode->childNodes->Getitem(1), &(pBeking54->_remark));
			
			//3. Envelope
			FillEnvelope(pNode->childNodes->Getitem(2), &(pBeking54->_envelope));

			//4. PointStyle
			FillGeoDeticPointStyle(pNode->childNodes->Getitem(3), &(pBeking54->_pointStyle));
			
			//5.Datum		
			FillDatum(pNode->childNodes->Getitem(4), &(pBeking54->_datum));

			//6.FillCSType
			FillCSType(pNode->childNodes->Getitem(5), &(pBeking54->_csType));

			/*pChildNode = pNode->selectSingleNode("//FalseEasting");
			pChildNode = pNode->selectSingleNode("//FalseNorthing");
			pChildNode = pNode->selectSingleNode("//LatitudeOfOrigin");
			pChildNode = pNode->selectSingleNode("//ScaleFactor");*/
		}
	}

	void CDeuXmlReader::FillGeoDeticXiAn80(int nIndex, _GeodeticSeries* pXiAn80)
	{
		MSXML2::IXMLDOMNodePtr pNode, pChildNode;
		MSXML2::IXMLDOMNodeListPtr pNodeList;

		pNodeList =  pDoc->selectNodes("//geodeticXiAn80");
		if((pNodeList->length > 0) && (pNodeList->length > nIndex))
		{
			pNode = pNodeList->Getitem(nIndex);
			RemoveComment(pNode); //过滤注释
			
			this->GetAttrValue(pNode, "name", &pXiAn80->name);
			this->GetAttrValue(pNode, "type", &pXiAn80->type);	

			pXiAn80->_coordinateType = GeoDetic;
			pXiAn80->_tranStandard   = XiAn80;

			//1. Name 节点
			FillName(pNode->childNodes->Getitem(0), &(pXiAn80->_name));

			//2. Remark 节点
			FillRemark(pNode->childNodes->Getitem(1), &(pXiAn80->_remark));

			//3. Envelope
			FillEnvelope(pNode->childNodes->Getitem(2), &(pXiAn80->_envelope));

			//4. PointStyle
			FillGeoDeticPointStyle(pNode->childNodes->Getitem(3), &(pXiAn80->_pointStyle));

			//5.Datum		
			FillDatum(pNode->childNodes->Getitem(4), &(pXiAn80->_datum));

			//6.FillCSType
			FillCSType(pNode->childNodes->Getitem(5), &(pXiAn80->_csType));
		}
	}

	void CDeuXmlReader::FillGeoDeticWGS84(int nIndex, _GeodeticSeries* pWGS84)
	{
		MSXML2::IXMLDOMNodePtr pNode, pChildNode;
		MSXML2::IXMLDOMNodeListPtr pNodeList;

		pNodeList =  pDoc->selectNodes("//geodeticwgs1984");
		if((pNodeList->length > 0) && (pNodeList->length > nIndex))
		{
			pNode = pNodeList->Getitem(nIndex);
			RemoveComment(pNode); //过滤注释
			
			this->GetAttrValue(pNode, "name", &pWGS84->name);
			this->GetAttrValue(pNode, "type", &pWGS84->type);
			
			pWGS84->_coordinateType = GeoDetic;
			pWGS84->_tranStandard   = WGS84;

			//1. Name 节点
			FillName(pNode->childNodes->Getitem(0), &(pWGS84->_name));

			//2. Remark 节点
			FillRemark(pNode->childNodes->Getitem(1), &(pWGS84->_remark));

			//3. Envelope
			FillEnvelope(pNode->childNodes->Getitem(2), &(pWGS84->_envelope));

			//4. PointStyle
			FillGeoDeticPointStyle(pNode->childNodes->Getitem(3), &(pWGS84->_pointStyle));

			//5.Datum		
			FillDatum(pNode->childNodes->Getitem(4), &(pWGS84->_datum));

			//6.FillCSType
			FillCSType(pNode->childNodes->Getitem(5), &(pWGS84->_csType));
		}
	}

	void CDeuXmlReader::FillGeoDeticCGCS2000(int nIndex, _GeodeticSeries* pCGCS2000)
	{
		MSXML2::IXMLDOMNodePtr pNode, pChildNode;
		MSXML2::IXMLDOMNodeListPtr pNodeList;

		pNodeList =  pDoc->selectNodes("//geodeticcgcs2000");
		if((pNodeList->length > 0) && (pNodeList->length > nIndex))
		{
			pNode = pNodeList->Getitem(nIndex);
			RemoveComment(pNode); //过滤注释
			
			this->GetAttrValue(pNode, "name", &pCGCS2000->name);
			this->GetAttrValue(pNode, "type", &pCGCS2000->type);

			pCGCS2000->_coordinateType = GeoDetic;
			pCGCS2000->_tranStandard   = CGCS2000;

			//1. Name 节点
			FillName(pNode->childNodes->Getitem(0), &(pCGCS2000->_name));

			//2. Remark 节点
			FillRemark(pNode->childNodes->Getitem(1), &(pCGCS2000->_remark));

			//3. Envelope
			FillEnvelope(pNode->childNodes->Getitem(2), &(pCGCS2000->_envelope));

			//4. PointStyle
			FillGeoDeticPointStyle(pNode->childNodes->Getitem(3), &(pCGCS2000->_pointStyle));

			//5.Datum		
			FillDatum(pNode->childNodes->Getitem(4), &(pCGCS2000->_datum));

			//6.FillCSType
			FillCSType(pNode->childNodes->Getitem(5), &(pCGCS2000->_csType));
		}
	}

	void CDeuXmlReader::FillName(MSXML2::IXMLDOMNodePtr &pChildNode, _Name* _name)
	{
		RemoveComment(pChildNode); //过滤注释
		
		this->GetAttrValue(pChildNode, "name", &_name->name);
		this->GetAttrValue(pChildNode, "type", &_name->type);
		this->GetElemText(pChildNode, &_name->text);
	}

	void CDeuXmlReader::FillRemark(MSXML2::IXMLDOMNodePtr &pCurrNode, _Remark* remark)
	{
		RemoveComment(pCurrNode); //过滤注释
		
		this->GetAttrValue(pCurrNode, "name", &remark->name);
		this->GetAttrValue(pCurrNode, "type", &remark->type);
		this->GetElemText(pCurrNode, &remark->text);
	}

	void CDeuXmlReader::FillCSType(MSXML2::IXMLDOMNodePtr &pCurrNode, _CSType* csType)
	{
		RemoveComment(pCurrNode); //过滤注释
	
		this->GetAttrValue(pCurrNode, "name", &csType->name);
		this->GetAttrValue(pCurrNode, "type", &csType->type);
		this->GetElemText(pCurrNode, &csType->text);
	}

	void CDeuXmlReader::FillLabel(MSXML2::IXMLDOMNodePtr &pCurrNode, _Label* label)
	{
		RemoveComment(pCurrNode); //过滤注释
		
		this->GetAttrValue(pCurrNode, "name", &label->name);
		this->GetAttrValue(pCurrNode, "type", &label->type);
		this->GetElemText(pCurrNode, &label->text);
	}

	void CDeuXmlReader::FillValueStyle(MSXML2::IXMLDOMNodePtr &pCurrNode, _Value* _value)
	{
		RemoveComment(pCurrNode); //过滤注释
		
		this->GetAttrValue(pCurrNode, "name", &_value->name);
		this->GetAttrValue(pCurrNode, "type", &_value->type);
		this->GetElemText(pCurrNode, &_value->text);
	}

	void CDeuXmlReader::FillMinPoint(MSXML2::IXMLDOMNodePtr &pCurrNode, _MinPoint* _minPoint)
	{
		RemoveComment(pCurrNode); //过滤注释

		//TRACE("%s", _com_util::ConvertBSTRToString(bstr));
		this->GetAttrValue(pCurrNode, "name", &_minPoint->name);
		this->GetAttrValue(pCurrNode, "type", &_minPoint->type);
		
		//Long
		FillLong(pCurrNode->childNodes->Getitem(0), &(_minPoint->_long));
		//Lat
		FillLat(pCurrNode->childNodes->Getitem(1), &(_minPoint->_lat));
	}

	void CDeuXmlReader::FillMaxPoint(MSXML2::IXMLDOMNodePtr &pCurrNode, _MaxPoint* _maxPoint)
	{
		RemoveComment(pCurrNode); //过滤注释
		
		this->GetAttrValue(pCurrNode, "name", &_maxPoint->name);
		this->GetAttrValue(pCurrNode, "type", &_maxPoint->type);
		
		//Long
		FillLong(pCurrNode->childNodes->Getitem(0), &(_maxPoint->_long));
		//Lat
		FillLat(pCurrNode->childNodes->Getitem(1), &(_maxPoint->_lat));
	}

	void CDeuXmlReader::FillLong(MSXML2::IXMLDOMNodePtr &pCurrNode, _Long* _long)
	{
		RemoveComment(pCurrNode); //过滤注释
		
		this->GetAttrValue(pCurrNode, "name", &_long->name);
		this->GetAttrValue(pCurrNode, "type", &_long->type);
		this->GetElemText(pCurrNode, &_long->text);
	}

	void CDeuXmlReader::FillLat(MSXML2::IXMLDOMNodePtr &pCurrNode, _Lat* _lat)
	{
		RemoveComment(pCurrNode); //过滤注释

		this->GetAttrValue(pCurrNode, "name", &_lat->name);
		this->GetAttrValue(pCurrNode, "type", &_lat->type);
		this->GetElemText(pCurrNode, &_lat->text);
	}

	void CDeuXmlReader::FillDimensions(MSXML2::IXMLDOMNodePtr &pCurrNode, _Dimensions* _dimensions)
	{
		RemoveComment(pCurrNode); //过滤注释
		
		this->GetAttrValue(pCurrNode, "name", &_dimensions->name);
		this->GetAttrValue(pCurrNode, "type", &_dimensions->type);
		this->GetElemText(pCurrNode, &_dimensions->text);
	}

	void CDeuXmlReader::FillAbbreviation(MSXML2::IXMLDOMNodePtr &pCurrNode, _Abbreviation* _abbreviation)
	{
		RemoveComment(pCurrNode); //过滤注释
		
		this->GetAttrValue(pCurrNode, "name", &_abbreviation->name);
		this->GetAttrValue(pCurrNode, "type", &_abbreviation->type);
		this->GetElemText(pCurrNode, &_abbreviation->text);
	}

	void CDeuXmlReader::FillPer_Meter(MSXML2::IXMLDOMNodePtr &pCurrNode, _Per_Meter* _per_Meter)
	{
		RemoveComment(pCurrNode); //过滤注释
		
		this->GetAttrValue(pCurrNode, "name", &_per_Meter->name);
		this->GetAttrValue(pCurrNode, "type", &_per_Meter->type);
		this->GetElemText(pCurrNode, &_per_Meter->text);
	}

	void CDeuXmlReader::FillPer_Degree(MSXML2::IXMLDOMNodePtr &pCurrNode, _Per_Degree* _per_Degree)
	{
		RemoveComment(pCurrNode); //过滤注释
		
		this->GetAttrValue(pCurrNode, "name", &_per_Degree->name);
		this->GetAttrValue(pCurrNode, "type", &_per_Degree->type);
		this->GetElemText(pCurrNode, &_per_Degree->text);
	}

	void CDeuXmlReader::Fill_Unit_1_Struct(MSXML2::IXMLDOMNodePtr &pCurrNode, _Unit_1* _unit_1)
	{
		RemoveComment(pCurrNode); //过滤注释

		this->GetAttrValue(pCurrNode, "name", &_unit_1->name);
		this->GetAttrValue(pCurrNode, "type", &_unit_1->type);
		
		//Name
		FillName(pCurrNode->childNodes->Getitem(0), &(_unit_1->_name));
		//Remark
		FillRemark(pCurrNode->childNodes->Getitem(1), &(_unit_1->_remark));
		//Abbreviation
		FillAbbreviation(pCurrNode->childNodes->Getitem(2), &(_unit_1->_abbreviation));
		//Per_Meter
		FillPer_Meter(pCurrNode->childNodes->Getitem(3), &(_unit_1->_per_Meter));
	}

	void CDeuXmlReader::Fill_Unit_2_Struct(MSXML2::IXMLDOMNodePtr &pCurrNode, _Unit_2* _unit_2)
	{
		RemoveComment(pCurrNode); //过滤注释

		this->GetAttrValue(pCurrNode, "name", &_unit_2->name);
		this->GetAttrValue(pCurrNode, "type", &_unit_2->type);
		
		//Name
		FillName(pCurrNode->childNodes->Getitem(0), &(_unit_2->_name));
		//Remark
		FillRemark(pCurrNode->childNodes->Getitem(1), &(_unit_2->_remark));	
		//Abbreviation
		FillAbbreviation(pCurrNode->childNodes->Getitem(2), &(_unit_2->_abbreviation));
		//Per_Degree
		FillPer_Degree(pCurrNode->childNodes->Getitem(3), &(_unit_2->_per_Degree));
	}

	void CDeuXmlReader::Fill_GeoDeticLong(MSXML2::IXMLDOMNodePtr &pCurrNode, _GeoDeticLong* _geoDeticLong)
	{
		RemoveComment(pCurrNode); //过滤注释

		this->GetAttrValue(pCurrNode, "name", &_geoDeticLong->name);
		this->GetAttrValue(pCurrNode, "type", &_geoDeticLong->type);

		//Value
		FillValueStyle(pCurrNode->childNodes->Getitem(0), &(_geoDeticLong->_value));
		//Units
		Fill_Unit_2_Struct(pCurrNode->childNodes->Getitem(1), &(_geoDeticLong->_unit_2));
	}

	void CDeuXmlReader::Fill_GeoDeticLat(MSXML2::IXMLDOMNodePtr &pCurrNode, _GeoDeticLat* _geoDeticLat)
	{
		RemoveComment(pCurrNode); //过滤注释

		this->GetAttrValue(pCurrNode, "name", &_geoDeticLat->name);
		this->GetAttrValue(pCurrNode, "type", &_geoDeticLat->type);

		//Value
		FillValueStyle(pCurrNode->childNodes->Getitem(0), &(_geoDeticLat->_value));
		//Units
		Fill_Unit_2_Struct(pCurrNode->childNodes->Getitem(1), &(_geoDeticLat->_unit_2));	
	}

	void CDeuXmlReader::Fill_GeoDeticLongForPs(MSXML2::IXMLDOMNodePtr &pCurrNode, _GeoDeticLongForPS* _geoDeticLong)
	{
		RemoveComment(pCurrNode); //过滤注释

		this->GetAttrValue(pCurrNode, "name", &_geoDeticLong->name);
		this->GetAttrValue(pCurrNode, "type", &_geoDeticLong->type);

		//Label
		FillLabel(pCurrNode->childNodes->Getitem(0), &(_geoDeticLong->_label));
		//Units
		Fill_Unit_2_Struct(pCurrNode->childNodes->Getitem(1), &(_geoDeticLong->_unit_2));
	}

	void CDeuXmlReader::Fill_GeoDeticLatForPs(MSXML2::IXMLDOMNodePtr &pCurrNode, _GeoDeticLatForPS* _geoDeticLat)
	{
		RemoveComment(pCurrNode); //过滤注释

		this->GetAttrValue(pCurrNode, "name", &_geoDeticLat->name);
		this->GetAttrValue(pCurrNode, "type", &_geoDeticLat->type);

		//Label
		FillLabel(pCurrNode->childNodes->Getitem(0), &(_geoDeticLat->_label));
		//Units
		Fill_Unit_2_Struct(pCurrNode->childNodes->Getitem(1), &(_geoDeticLat->_unit_2));
	}

	void CDeuXmlReader::FillEast(MSXML2::IXMLDOMNodePtr &pCurrNode, _East* _east)
	{
		RemoveComment(pCurrNode); //过滤注释

		this->GetAttrValue(pCurrNode, "name", &_east->name);
		this->GetAttrValue(pCurrNode, "type", &_east->type);

		//Label
		FillLabel(pCurrNode->childNodes->Getitem(0), &(_east->_label));
		//Units
		Fill_Unit_1_Struct(pCurrNode->childNodes->Getitem(1), &(_east->_unit_1));
	}

	void CDeuXmlReader::FillNorth(MSXML2::IXMLDOMNodePtr &pCurrNode, _North* _north)
	{
		RemoveComment(pCurrNode); //过滤注释

		this->GetAttrValue(pCurrNode, "name", &_north->name);
		this->GetAttrValue(pCurrNode, "type", &_north->type);
		
		//Label
		FillLabel(pCurrNode->childNodes->Getitem(0), &(_north->_label));
		//Units
		Fill_Unit_1_Struct(pCurrNode->childNodes->Getitem(1), &(_north->_unit_1));
	}

	void CDeuXmlReader::FillEllipsoidHeight(MSXML2::IXMLDOMNodePtr &pCurrNode, _EllipsoidHeight* _ellipsoidHeight)
	{
		RemoveComment(pCurrNode); //过滤注释

		this->GetAttrValue(pCurrNode, "name", &_ellipsoidHeight->name);
		this->GetAttrValue(pCurrNode, "type", &_ellipsoidHeight->type);

		//Label
		FillLabel(pCurrNode->childNodes->Getitem(0), &(_ellipsoidHeight->_label));
		//Units
		Fill_Unit_1_Struct(pCurrNode->childNodes->Getitem(1), &(_ellipsoidHeight->_unit_1));
	}

	void CDeuXmlReader::FillGeoDeticPointStyle(MSXML2::IXMLDOMNodePtr &pCurrNode, _GeoDeticPointStyle* _geoDeticPointStyle)
	{
		RemoveComment(pCurrNode); //过滤注释

		this->GetAttrValue(pCurrNode, "name", &_geoDeticPointStyle->name);
		this->GetAttrValue(pCurrNode, "type", &_geoDeticPointStyle->type);

		FillName(pCurrNode->childNodes->Getitem(0), &(_geoDeticPointStyle->_name));
		FillRemark(pCurrNode->childNodes->Getitem(1), &(_geoDeticPointStyle->_remark));
		FillDimensions(pCurrNode->childNodes->Getitem(2), &(_geoDeticPointStyle->_dimensions));

		Fill_GeoDeticLongForPs(pCurrNode->childNodes->Getitem(3), &(_geoDeticPointStyle->_geoDeticLongForPS));
		Fill_GeoDeticLatForPs(pCurrNode->childNodes->Getitem(4), &(_geoDeticPointStyle->_geoDeticLatForPS));

		FillEllipsoidHeight(pCurrNode->childNodes->Getitem(5), &(_geoDeticPointStyle->_ellipsoidHeight));
		
		//FillName(pCurrNode->selectSingleNode("//Name"), &(_geoDeticPointStyle->_name));
		//FillRemark(pCurrNode->selectSingleNode("//Remark"), &(_geoDeticPointStyle->_remark));
		//FillDimensions(pCurrNode->selectSingleNode("//Dimensions"), &(_geoDeticPointStyle->_dimensions));
		//FillEast(pCurrNode->selectSingleNode("//East"), &(_geoDeticPointStyle->_east));
		//FillNorth(pCurrNode->selectSingleNode("//North"), &(_geoDeticPointStyle->_north));
		//FillEllipsoidHeight(pCurrNode->selectSingleNode("//EllipsoidHeight"), &(_geoDeticPointStyle->_ellipsoidHeight));
	}

	void CDeuXmlReader::FillProjectionPointStyle(MSXML2::IXMLDOMNodePtr &pCurrNode, _ProjectionPointStyle* _projectionPointStyle)
	{
		RemoveComment(pCurrNode); //过滤注释

		this->GetAttrValue(pCurrNode, "name", &_projectionPointStyle->name);
		this->GetAttrValue(pCurrNode, "type", &_projectionPointStyle->type);
		
		//Name
		FillName(pCurrNode->childNodes->Getitem(0), &(_projectionPointStyle->_name));
		//Remark
		FillRemark(pCurrNode->childNodes->Getitem(1), &(_projectionPointStyle->_remark));
		//Dimensions
		FillDimensions(pCurrNode->childNodes->Getitem(2), &(_projectionPointStyle->_dimensions));
		//East
		FillEast(pCurrNode->childNodes->Getitem(3), &(_projectionPointStyle->_east));
		//North
		FillNorth(pCurrNode->childNodes->Getitem(4), &(_projectionPointStyle->_north));
		//EllipsoidHeight
		FillEllipsoidHeight(pCurrNode->childNodes->Getitem(5), &(_projectionPointStyle->_ellipsoidHeight));
	}

	void CDeuXmlReader::FillCentralMeridian(MSXML2::IXMLDOMNodePtr &pCurrNode, _CentralMeridian* _centralMeridian)
	{
		RemoveComment(pCurrNode); //过滤注释

		this->GetAttrValue(pCurrNode, "name", &_centralMeridian->name);
		this->GetAttrValue(pCurrNode, "type", &_centralMeridian->type);
		
		//Name
		FillName(pCurrNode->childNodes->Getitem(0),  &(_centralMeridian->_name));

		//Value
		FillValueStyle(pCurrNode->childNodes->Getitem(1), &(_centralMeridian->_value));

		//Units
		FillUnit(pCurrNode->childNodes->Getitem(2), &(_centralMeridian->_uint));
	}

	void CDeuXmlReader::FillFalseEasting(MSXML2::IXMLDOMNodePtr &pCurrNode, _FalseEasting* _falseEasting)
	{
		RemoveComment(pCurrNode); //过滤注释

		this->GetAttrValue(pCurrNode, "name", &_falseEasting->name);
		this->GetAttrValue(pCurrNode, "type", &_falseEasting->type);
		
		//Name
		FillName(pCurrNode->childNodes->Getitem(0),  &(_falseEasting->_name));

		//Value
		FillValueStyle(pCurrNode->childNodes->Getitem(1), &(_falseEasting->_value));

		//Units
		FillUnit(pCurrNode->childNodes->Getitem(2), &(_falseEasting->_uint));
	}

	void CDeuXmlReader::FillFalseNorthing(MSXML2::IXMLDOMNodePtr &pCurrNode, _FalseNorthing* _falseNorthing)
	{
		RemoveComment(pCurrNode); //过滤注释

		this->GetAttrValue(pCurrNode, "name", &_falseNorthing->name);
		this->GetAttrValue(pCurrNode, "type", &_falseNorthing->type);

		//Name
		FillName(pCurrNode->childNodes->Getitem(0),  &(_falseNorthing->_name));

		//Value
		FillValueStyle(pCurrNode->childNodes->Getitem(1), &(_falseNorthing->_value));

		//Units
		FillUnit(pCurrNode->childNodes->Getitem(2), &(_falseNorthing->_uint));
	}

	void CDeuXmlReader::FillLatitudeOfOrigin(MSXML2::IXMLDOMNodePtr &pCurrNode, _LatitudeOfOrigin* _latitudeOfOrigin)
	{
		RemoveComment(pCurrNode); //过滤注释

		this->GetAttrValue(pCurrNode, "name", &_latitudeOfOrigin->name);
		this->GetAttrValue(pCurrNode, "type", &_latitudeOfOrigin->type);

		//Name
		FillName(pCurrNode->childNodes->Getitem(0),  &(_latitudeOfOrigin->_name));

		//Value
		FillValueStyle(pCurrNode->childNodes->Getitem(1), &(_latitudeOfOrigin->_value));

		//Units
		FillUnit(pCurrNode->childNodes->Getitem(2), &(_latitudeOfOrigin->_uint));
	}

	void CDeuXmlReader::FillScaleFactor(MSXML2::IXMLDOMNodePtr &pCurrNode, _ScaleFactor* _scaleFactor)
	{
		RemoveComment(pCurrNode); //过滤注释

		this->GetAttrValue(pCurrNode, "name", &_scaleFactor->name);
		this->GetAttrValue(pCurrNode, "type", &_scaleFactor->type);
		
		//Name
		FillName(pCurrNode->childNodes->Getitem(0),  &(_scaleFactor->_name));

		//Value
		FillValueStyle(pCurrNode->childNodes->Getitem(1), &(_scaleFactor->_value));

		//Units
		FillUnit(pCurrNode->childNodes->Getitem(2), &(_scaleFactor->_uint));
	}

	void CDeuXmlReader::FillSemi_Minor_Axis(MSXML2::IXMLDOMNodePtr &pCurrNode, _Semi_Minor_Axis* _semi_Minor_Axis)
	{	
		RemoveComment(pCurrNode); //过滤注释

		this->GetAttrValue(pCurrNode, "name", &_semi_Minor_Axis->name);
		this->GetAttrValue(pCurrNode, "type", &_semi_Minor_Axis->type);
		
		//Value
		FillValueStyle(pCurrNode->childNodes->Getitem(0), &(_semi_Minor_Axis->_value));

		//Units
		Fill_Unit_1_Struct(pCurrNode->childNodes->Getitem(1), &(_semi_Minor_Axis->_unit_1));
	}

	void CDeuXmlReader::FillSemi_Major_Axis(MSXML2::IXMLDOMNodePtr &pCurrNode, _Semi_Major_Axis* _semi_Major_Axis)
	{
		RemoveComment(pCurrNode); //过滤注释

		this->GetAttrValue(pCurrNode, "name", &_semi_Major_Axis->name);
		this->GetAttrValue(pCurrNode, "type", &_semi_Major_Axis->type);

		//Value
		FillValueStyle(pCurrNode->childNodes->Getitem(0), &(_semi_Major_Axis->_value));

		//Units
		Fill_Unit_1_Struct(pCurrNode->childNodes->Getitem(1), &(_semi_Major_Axis->_unit_1));
	}

	void CDeuXmlReader::FillInverseFlattening(MSXML2::IXMLDOMNodePtr &pCurrNode, _InverseFlattening* _inverseFlattening)
	{
		RemoveComment(pCurrNode); //过滤注释

		this->GetAttrValue(pCurrNode, "name", &_inverseFlattening->name);
		this->GetAttrValue(pCurrNode, "type", &_inverseFlattening->type);
		this->GetElemText(pCurrNode, &_inverseFlattening->text);
	}

	void CDeuXmlReader::FillEllipsoid(MSXML2::IXMLDOMNodePtr &pCurrNode, _Ellipsoid* _ellipsoid)
	{
		RemoveComment(pCurrNode); //过滤注释

		this->GetAttrValue(pCurrNode, "name", &_ellipsoid->name);
		this->GetAttrValue(pCurrNode, "type", &_ellipsoid->type);
		
		//Name
		FillName(pCurrNode->childNodes->Getitem(0), &(_ellipsoid->_name));

		//Remark
		FillRemark(pCurrNode->childNodes->Getitem(1), &(_ellipsoid->_remark));

		//Semi-Major-Axis
		FillSemi_Major_Axis(pCurrNode->childNodes->Getitem(2), &(_ellipsoid->_semi_Major_Axis));

		//Semi-Minor-Axis
		FillSemi_Minor_Axis(pCurrNode->childNodes->Getitem(3), &(_ellipsoid->_semi_Minor_Axis));

		//InverseFlattening
		FillInverseFlattening(pCurrNode->childNodes->Getitem(4), &(_ellipsoid->_inverseFlattening));
	}

	void CDeuXmlReader::FillPrimeMeridian(MSXML2::IXMLDOMNodePtr &pCurrNode, _PrimeMeridian* _primeMeridian)
	{
		RemoveComment(pCurrNode); //过滤注释

		this->GetAttrValue(pCurrNode, "name", &_primeMeridian->name);
		this->GetAttrValue(pCurrNode, "type", &_primeMeridian->type);
		
		//Name
		FillName(pCurrNode->childNodes->Getitem(0), &(_primeMeridian->_name));
		//Long
		Fill_GeoDeticLong(pCurrNode->childNodes->Getitem(1), &(_primeMeridian->_geoDeticLong));
	}

	void CDeuXmlReader::FillDatum(MSXML2::IXMLDOMNodePtr &pCurrNode, _Datum* _datum)
	{
		RemoveComment(pCurrNode); //过滤注释

		this->GetAttrValue(pCurrNode, "name", &_datum->name);
		this->GetAttrValue(pCurrNode, "type", &_datum->type);
		
		/*FillName(pCurrNode->selectSingleNode("//Name"), &(_datum->_name));
		FillRemark(pCurrNode->selectSingleNode("//Remark"), &(_datum->_remark));

		FillEllipsoid(pCurrNode->selectSingleNode("//Ellipsoid"), &(_datum->_ellipsoid));
		FillPrimeMeridian(pCurrNode->selectSingleNode("//PrimeMeridian"), &(_datum->_primeMeridian));*/

		//Name
		FillName(pCurrNode->childNodes->Getitem(0), &(_datum->_name));

		//Remark
		FillRemark(pCurrNode->childNodes->Getitem(1), &(_datum->_remark));

		//Ellipsoid
		FillEllipsoid(pCurrNode->childNodes->Getitem(2), &(_datum->_ellipsoid));

		//PrimeMeridian
		FillPrimeMeridian(pCurrNode->childNodes->Getitem(3), &(_datum->_primeMeridian));
	}

	void CDeuXmlReader::FillProjection(MSXML2::IXMLDOMNodePtr &pCurrNode, _Projection* _projection)
	{
		RemoveComment(pCurrNode);

		this->GetAttrValue(pCurrNode, "name", &_projection->name);
		this->GetAttrValue(pCurrNode, "type", &_projection->type);
		this->GetElemText(pCurrNode, &_projection->text);
	}

	void CDeuXmlReader::FillGeodeticPointor(MSXML2::IXMLDOMNodePtr &pCurrNode, _GeodeticPointor* _geodeticPointor)
	{
		RemoveComment(pCurrNode);

		this->GetAttrValue(pCurrNode, "name", &_geodeticPointor->name);
		this->GetAttrValue(pCurrNode, "type", &_geodeticPointor->type);
		this->GetElemText(pCurrNode, &_geodeticPointor->text);
	}

	void CDeuXmlReader::FillEnvelope(MSXML2::IXMLDOMNodePtr &pCurrNode, _Envelope* _envelope)
	{
		RemoveComment(pCurrNode); //过滤注释

		MSXML2::IXMLDOMNodeListPtr p_nlist;
		MSXML2::IXMLDOMNodePtr p_node;

		this->GetAttrValue(pCurrNode, "name", &_envelope->name);
		this->GetAttrValue(pCurrNode, "type", &_envelope->type);

		p_nlist = pCurrNode->childNodes;
		//p_node = p_nlist->Getitem(0);
		FillName(p_nlist->Getitem(0), &_envelope->_name);
		FillRemark(p_nlist->Getitem(1), &(_envelope->_remark));
		FillMinPoint(p_nlist->Getitem(2), &(_envelope->_minpoint));
		FillMaxPoint(p_nlist->Getitem(3), &(_envelope->_maxpoint));
	}

	void CDeuXmlReader::RemoveComment(MSXML2::IXMLDOMNodePtr &pCurrNode)
	{	
		MSXML2::IXMLDOMNodeListPtr _nodeListPtr;
		MSXML2::IXMLDOMNodePtr _nodePtr;
		_nodeListPtr = pCurrNode->GetchildNodes();
		int n = _nodeListPtr->length;
		
		/*
		BSTR bstr;
		pCurrNode->get_xml(&bstr);
		*/

		int m=0;
		BOOL Islast = FALSE;
		while(Islast == FALSE)
		{
			_nodePtr = _nodeListPtr->nextNode();
			if(_nodePtr != NULL)
			{
				if(_nodePtr->nodeType == NODE_COMMENT)
				{
					pCurrNode->removeChild(_nodePtr);
				}
				if(pCurrNode->GetlastChild() == _nodePtr)
				{
					Islast = TRUE;
				}
			}
			else
			{
				Islast = TRUE;
			}
		}
	}

	void CDeuXmlReader::GetControlPoint(p_ControlPointPairs m_pCP)
	{
		MSXML2::IXMLDOMNodePtr p_Node;
		p_Nodelist = pDoc->selectNodes("//CControlPointPair");	
		BSTR _bstr;
		pDoc->get_xml(&_bstr);
		int  nLen = p_Nodelist->length;
		if( p_Nodelist->length > 0 )
		{
			for(int n=0; n<p_Nodelist->length; n++)
			{	
				p_Node = p_Nodelist->Getitem(n);
				RemoveComment(p_Node);  //过滤注释
						
				p_ControlPointPair pControlPointPair = new ControlPointPair;
				FillChildPoint(p_Node, pControlPointPair);
				m_pCP->_controlPointPair.Add(pControlPointPair);
			}
		}
	}

	void CDeuXmlReader::FillChildPoint(MSXML2::IXMLDOMNodePtr &pCurrNode, p_ControlPointPair pControlPointPair)
	{
		RemoveComment(pCurrNode);  //过滤注释
	
		this->GetElemText(pCurrNode->childNodes->Getitem(0), &pControlPointPair->X_SRC);
		this->GetElemText(pCurrNode->childNodes->Getitem(1), &pControlPointPair->Y_SRC);
		this->GetElemText(pCurrNode->childNodes->Getitem(2), &pControlPointPair->Z_SRC);
		this->GetElemText(pCurrNode->childNodes->Getitem(3), &pControlPointPair->X_DEST);
		this->GetElemText(pCurrNode->childNodes->Getitem(4), &pControlPointPair->Y_DEST);
		this->GetElemText(pCurrNode->childNodes->Getitem(5), &pControlPointPair->Z_DEST);
	}

	void CDeuXmlReader::MappingTasks(p_Tasks pTasks)
	{
		MSXML2::IXMLDOMNodePtr pnode;
		MSXML2::IXMLDOMNodeListPtr pList;
		
		pnode = pDoc->selectSingleNode("//TaskList");
		
		BSTR bstr;
		pnode->get_xml(&bstr);
	
		GetAttrValue(pnode, "name", &pTasks->name);	
		GetAttrValue(pnode, "type", &pTasks->type);	

		pList = pDoc->selectNodes("//CDeuTask");
		if(pList->length > 0)
		{
			for(int k=0; k<pList->length; k++)
			{
				p_Task m_Task = new _Task;
				FillTask(pList->Getitem(k),m_Task);
				pTasks->_task.Add(m_Task);			
			}
		}
		//TRACE("%d", pList->length);
	}

	void CDeuXmlReader::FillTask(MSXML2::IXMLDOMNodePtr &pCurrNode, _Task* pTask)
	{
		RemoveComment(pCurrNode);

		this->GetAttrValue(pCurrNode, "id", &pTask->id);
		this->GetAttrValue(pCurrNode, "name", &pTask->name);
		this->GetAttrValue(pCurrNode, "type", &pTask->type);

		//IN_PATH
		GetAttrValue(pCurrNode->childNodes->Getitem(0), "name", &pTask->_inpath.name);
		GetAttrValue(pCurrNode->childNodes->Getitem(0), "type", &pTask->_inpath.type);
		GetElemText(pCurrNode->childNodes->Getitem(0), &pTask->_inpath.text);

		//OUT_PATH
		GetAttrValue(pCurrNode->childNodes->Getitem(1), "name", &pTask->_outpath.name);	
		GetAttrValue(pCurrNode->childNodes->Getitem(1), "type", &pTask->_outpath.type);	
		GetElemText(pCurrNode->childNodes->Getitem(1), &pTask->_outpath.text);	

		//IN_DRIVER
		GetAttrValue(pCurrNode->childNodes->Getitem(2), "name", &pTask->_inDriver.name);	
		GetAttrValue(pCurrNode->childNodes->Getitem(2), "type", &pTask->_inDriver.type);	
		GetElemText(pCurrNode->childNodes->Getitem(2), &pTask->_inDriver.text);

		//OUT_DRIVER
		GetAttrValue(pCurrNode->childNodes->Getitem(3), "name", &pTask->_outDriver.name);
		GetAttrValue(pCurrNode->childNodes->Getitem(3), "type", &pTask->_outDriver.type);
		GetElemText(pCurrNode->childNodes->Getitem(3), &pTask->_outDriver.text);

		//IN_ELLIPSE
		GetAttrValue(pCurrNode->childNodes->Getitem(4), "name", &pTask->_inEllipse.name);
		GetAttrValue(pCurrNode->childNodes->Getitem(4), "type", &pTask->_inEllipse.type);
		GetElemText(pCurrNode->childNodes->Getitem(4), &pTask->_inEllipse.text);

		//OUT_ELLIPSE
		GetAttrValue(pCurrNode->childNodes->Getitem(5), "name", &pTask->_outEllipse.name);	
		GetAttrValue(pCurrNode->childNodes->Getitem(5), "type", &pTask->_outEllipse.type);
		GetElemText(pCurrNode->childNodes->Getitem(5), &pTask->_outEllipse.text);

		//IN_COORDTYPE
		GetAttrValue(pCurrNode->childNodes->Getitem(6), "name", &pTask->_inCoordType.name);		
		GetAttrValue(pCurrNode->childNodes->Getitem(6), "type", &pTask->_inCoordType.type);		
		GetElemText(pCurrNode->childNodes->Getitem(6), &pTask->_inCoordType.text);

		//OUT_COORDTYPE
		GetAttrValue(pCurrNode->childNodes->Getitem(7), "name", &pTask->_outCoordType.name);	
		GetAttrValue(pCurrNode->childNodes->Getitem(7), "type", &pTask->_outCoordType.type);		
		GetElemText(pCurrNode->childNodes->Getitem(7), &pTask->_outCoordType.text);

		//IN_CentralMeridian
		GetAttrValue(pCurrNode->childNodes->Getitem(8), "name", &pTask->_inCentralMeridian.name);	
		GetAttrValue(pCurrNode->childNodes->Getitem(8), "type", &pTask->_inCentralMeridian.type);
		GetElemText(pCurrNode->childNodes->Getitem(8), &pTask->_inCentralMeridian.text);

		//OUT_CentralMeridian
		GetAttrValue(pCurrNode->childNodes->Getitem(9), "name", &pTask->_outCentralMeridian.name);
		GetAttrValue(pCurrNode->childNodes->Getitem(9), "type", &pTask->_outCentralMeridian.type);
		GetElemText(pCurrNode->childNodes->Getitem(9), &pTask->_outCentralMeridian.text);

		//TYPE
		GetAttrValue(pCurrNode->childNodes->Getitem(10), "name", &pTask->_type.name);	
		GetAttrValue(pCurrNode->childNodes->Getitem(10), "type", &pTask->_type.type);	
		GetElemText(pCurrNode->childNodes->Getitem(10), &pTask->_type.text);

		//STATUS
		GetAttrValue(pCurrNode->childNodes->Getitem(11), "name", &pTask->_status.name);	
		GetAttrValue(pCurrNode->childNodes->Getitem(11), "type", &pTask->_status.type);	
		GetElemText(pCurrNode->childNodes->Getitem(11), &pTask->_status.text);

		//CURPART
		GetAttrValue(pCurrNode->childNodes->Getitem(12), "name", &pTask->_curPart.name);	
		GetAttrValue(pCurrNode->childNodes->Getitem(12), "type", &pTask->_curPart.type);	
		GetElemText(pCurrNode->childNodes->Getitem(12), &pTask->_curPart.text);

		//PARTS
		GetAttrValue(pCurrNode->childNodes->Getitem(13), "name", &pTask->_parts.name);		
		GetAttrValue(pCurrNode->childNodes->Getitem(13), "type", &pTask->_parts.type);

		MSXML2::IXMLDOMNodeListPtr pNodelist;
		pNodelist = pCurrNode->childNodes->Getitem(13)->childNodes;
		if(pNodelist->length > 0)
		{
			for(int n=0; n<pNodelist->length; n++)
			{
				_Part __path;
				GetAttrValue(pNodelist->Getitem(n), "name", &__path.name);

				GetAttrValue(pNodelist->Getitem(n), "type", &__path.type);

				GetElemText(pNodelist->Getitem(n), &__path.text);

				pTask->_parts.m_Part.Add(__path);
			}
		}

		//读取控制点文件路径add by chenyong 2013-3-28
		GetAttrValue(pCurrNode->childNodes->Getitem(14), "name", &pTask->_controlPath.name);

		GetAttrValue(pCurrNode->childNodes->Getitem(14), "type", &pTask->_controlPath.type);

		GetElemText(pCurrNode->childNodes->Getitem(14), &pTask->_controlPath.text);

		GetAttrValue(pCurrNode->childNodes->Getitem(15), "name", &pTask->_transModel.name);

		GetAttrValue(pCurrNode->childNodes->Getitem(15), "type", &pTask->_transModel.type);

		GetElemText(pCurrNode->childNodes->Getitem(15), &pTask->_transModel.text);
	}

	//读文件格式名
	void CDeuXmlReader::ReadFormat(_StrFormatList& Tasks)
	{
		MSXML2::IXMLDOMNodePtr pnode;
		MSXML2::IXMLDOMNodeListPtr pList;

		pnode = pDoc->selectSingleNode("//FormatList");

		BSTR bstr;
		pnode->get_xml(&bstr);

		GetAttrValue(pnode, "name", &Tasks.name);
		GetAttrValue(pnode, "type", &Tasks.type);

		pList = pDoc->selectNodes("//Formats");
		if(pList->length > 0)
		{
			for(int k=0; k<pList->length; k++)
			{
				
				p_StrFormatTypeList pFormatTypeList = new _StrFormatTypeList;
				GetFormat(pList->Getitem(k),pFormatTypeList);

				Tasks.FormatTypeList.push_back(pFormatTypeList);
			}
		}
	}

	void CDeuXmlReader::GetFormat(MSXML2::IXMLDOMNodePtr &pCurrNode, _StrFormatTypeList* pTask)
	{
		RemoveComment(pCurrNode);

		this->GetAttrValue(pCurrNode, "name", &pTask->name);
		this->GetAttrValue(pCurrNode, "type", &pTask->type);

		MSXML2::IXMLDOMNodeListPtr pNodelist;
		pNodelist = pCurrNode->childNodes;
		if(pNodelist->length > 0)
		{
			for(int n=0; n<pNodelist->length; n++)
			{
				_StrFormatType				_FormatType;
				GetAttrValue(pNodelist->Getitem(n), "name", &_FormatType.name);

				GetAttrValue(pNodelist->Getitem(n), "type", &_FormatType.type);

				GetElemText(pNodelist->Getitem(n), &_FormatType.text);

				bool bexist = true;
				if (strcmp(_FormatType.text, _T("ArcSDE")) == 0)
				{
					#ifdef ARCSDE
						bexist = true;
					#else
						bexist = false;
					#endif
				}
				if (bexist)
				{
					pTask->TypeList.push_back(_FormatType);
				}
			}
		}
	}
}	