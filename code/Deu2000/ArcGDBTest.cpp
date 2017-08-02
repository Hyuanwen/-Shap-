#include "StdAfx.h"
#include "ArcGDBTest.h"

#define M_PI 3.141592653589793

ArcGDBTest::ArcGDBTest()
{
}

ArcGDBTest::~ArcGDBTest()
{
}

HRESULT ArcGDBTest::TransShpFile()
{
	CString filePath = _T("E:\\Code\\jwd54");
	BSTR bpath = filePath.AllocSysString();

	CoInitialize(NULL);

	//IWorkspaceFactoryPtr pWSFactory(CLSID_ShapefileWorkspaceFactory);
	CLSID clsid;
	CLSIDFromProgID(OLESTR("esriDataSourcesFile.ShapefileWorkspaceFactory"), &clsid);
	CComPtr<IWorkspaceFactory> pWSFactory;
	HRESULT hr = pWSFactory.CoCreateInstance(clsid);
	CComPtr<IWorkspace> pWS;
	hr = pWSFactory->OpenFromFile(bpath, NULL, &pWS);
	
	SysFreeString(bpath);
	CoUninitialize();

	return S_OK;
}

HRESULT ArcGDBTest::TransGDBFile()
{
	string  filePath_Src = "C:\\Users\\chenyong\\Documents\\ArcGIS\\aaa.gdb";  
	string  filePath_Des = "C:\\Users\\chenyong\\Desktop\\dxfdata\\deutrans";
	string  fileName_Des = "aaa.gdb";
	HRESULT hr;

	CoInitialize(NULL);

	//打开源文件
	IWorkspaceFactoryPtr pWSFactory_Src(CLSID_FileGDBWorkspaceFactory);
	hr = pWSFactory_Src->OpenFromFile(_bstr_t(filePath_Src.c_str()), 0, &m_Workspace_Src);
	if (FAILED(hr))
	{
		return S_FALSE;
	}

	//创建目标文件
	IWorkspaceFactoryPtr pWSFactory_Des(CLSID_FileGDBWorkspaceFactory);
	IWorkspaceNamePtr    pWSName;
	esriINamePtr         pName;
	IUnknownPtr			 pUnk;
	hr = pWSFactory_Des->Create(_bstr_t(filePath_Des.c_str()), _bstr_t(fileName_Des.c_str()), NULL, 0, &pWSName);
	if (FAILED(hr))
	{
		return S_FALSE;
	}
	pName = (esriINamePtr)pWSName;
	pName->Open(&pUnk);
	m_Workspace_Des = (IWorkspacePtr)pUnk;

	//创建空间参考
	ISpatialReferenceFactoryPtr pSpatialFac(CLSID_SpatialReferenceEnvironment);
	string strPrjFullPath = _T("E:\\1.code\\1.Deu2000\\Deu2000_Merger\\bin\\Debug\\CoordinateSystems\\Projected Coordinate Systems\\Gauss Kruger\\Xian 1980\\Xian 1980 3 Degree GK CM 117E.prj");
	hr = pSpatialFac->CreateESRISpatialReferenceFromPRJFile(_bstr_t(strPrjFullPath.c_str()), &m_pSpatial);
	//ISpatialReferenceFactory2Ptr pSpatialFactory(CLSID_SpatialReferenceEnvironment);
	//hr = pSpatialFactory->CreateSpatialReference(esriSRGeoCS_WGS1984, &m_pSpatial);
	if (FAILED(hr))
	{
		return hr;
	}

	//打开并转换Dataset
	OpenFeatureDataset();

	//打开并转换FeatureClass
	OpenFeatureClass();

	CoUninitialize();

	return S_OK;
}

HRESULT ArcGDBTest::OpenFeatureDataset()
{
	IEnumDatasetPtr pEDataset;
	IDatasetPtr     pDataset;
	BSTR            name;
	HRESULT         hr;

	m_Workspace_Src->get_Datasets(esriDTFeatureDataset, &pEDataset);
	pEDataset->Reset();
	hr = pEDataset->Next(&pDataset);
	if (FAILED(hr))
	{
		return S_FALSE;
	}

	while(pDataset != NULL)
	{
		pDataset->get_Name(&name);
		TransFeatureDataset(_com_util::ConvertBSTRToString(name));

		pEDataset->Next(&pDataset);
	}

	SysFreeString(name);

	return S_OK;
}

HRESULT ArcGDBTest::TransFeatureDataset(const string& strDSName)
{
	IFeatureWorkspacePtr pFeatureWS_Src = m_Workspace_Src;
	IFeatureWorkspacePtr pFeatureWS_Des = m_Workspace_Des;
	IFeatureDatasetPtr   pFeatureDS_Src;
	IFeatureDatasetPtr   pFeatureDS_Des;
	HRESULT			     hr;

	//1.打开源数据集
	hr = pFeatureWS_Src->OpenFeatureDataset(_bstr_t(strDSName.c_str()), &pFeatureDS_Src);
	if (FAILED(hr))
	{
		return S_FALSE;
	}

	//2.创建创建要素集
	hr = pFeatureWS_Des->CreateFeatureDataset(_bstr_t(strDSName.c_str()), m_pSpatial, &pFeatureDS_Des);
	if (FAILED(hr))
	{
		return hr;
	}

	//3.获取源数据集
	IEnumDatasetPtr pEDataset;
	IDatasetPtr     pDataset;
	BSTR            name;
	esriDatasetType	esriDSType = esriDTAny;

	pFeatureDS_Src->get_Subsets(&pEDataset);
	pEDataset->Reset();
	hr = pEDataset->Next(&pDataset);
	if (FAILED(hr))
	{
		return hr;
	}

	while (pDataset != NULL)
	{
		pDataset->get_Name(&name);
		pDataset->get_Type(&esriDSType);
		if (esriDSType == esriDTFeatureClass)
		{
			hr = TransFeatureClass(esriDTFeatureDataset, pFeatureDS_Des, _com_util::ConvertBSTRToString(name));
			if(hr == S_FALSE)
			{
				//pWorkspaceEdit->StopEditOperation();
				//pWorkspaceEdit->StopEditing(VARIANT_FALSE);
			}
		}

		pEDataset->Next(&pDataset);
	}

	return S_OK;
}

HRESULT ArcGDBTest::OpenFeatureClass()
{
	IEnumDatasetPtr    pEFclass;
	IDatasetPtr        pFclass;
	BSTR               name;

	m_Workspace_Src->get_Datasets(esriDTFeatureClass, &pEFclass);
	while(pEFclass->Next(&pFclass) == S_OK)
	{
		pFclass->get_Name(&name);
		TransFeatureClass(esriDTFeatureClass, m_Workspace_Des, _com_util::ConvertBSTRToString(name));
	}

	SysFreeString(name);

	return S_OK;
}

HRESULT ArcGDBTest::TransFeatureClass(enum esriDatasetType datasetType, IFeatureDatasetPtr pFeatureDS_Des, const string& featureName)
{
	IFeatureWorkspacePtr pFeatureWS_Src = m_Workspace_Src;
	IFeatureWorkspacePtr pFeatureWS_Des = m_Workspace_Des;
	IFeatureClassPtr     pFeatureCL_Src;
	IFeatureClassPtr     pFeatureCL_Des;
	HRESULT			     hr;

	//打开源要素类
	hr = pFeatureWS_Src->OpenFeatureClass(_bstr_t(featureName.c_str()), &pFeatureCL_Src);
	if (FAILED(hr))
	{
		return S_FALSE;
	}

	IFieldsPtr		pFlds;
	esriFeatureType	FeatureType;
	CComBSTR		shapeName;
	IUIDPtr			uid;
	IUIDPtr			uid2;

	pFeatureCL_Src->get_Fields(&pFlds);
	pFeatureCL_Src->get_FeatureType(&FeatureType);
	pFeatureCL_Src->get_ShapeFieldName(&shapeName);
	pFeatureCL_Src->get_CLSID(&uid);
	pFeatureCL_Src->get_EXTCLSID(&uid2);

	//创建目标要素类
	if (datasetType == esriDTFeatureDataset)
	{
		hr = pFeatureDS_Des->CreateFeatureClass(_bstr_t(featureName.c_str()), pFlds, uid, uid2, FeatureType, shapeName, _bstr_t(""), &pFeatureCL_Des);
	}
	else if (datasetType == esriDTFeatureClass)
	{
		hr = pFeatureWS_Des->CreateFeatureClass(_bstr_t(featureName.c_str()), pFlds, uid, uid2, FeatureType, shapeName, _bstr_t(""), &pFeatureCL_Des);
	}
	else
	{
		return S_FALSE;
	}
	if (FAILED(hr))
	{
		return S_FALSE;
	}

	//设置空间参考
	IGeoDatasetPtr pGeoDs = pFeatureCL_Des;
	IGeoDatasetSchemaEditPtr pGeoDSe = pGeoDs;
	pGeoDSe->AlterSpatialReference(m_pSpatial);

	//添加目标要素类记录
	IFeatureCursorPtr pFeatureCur_Src;
	IFeaturePtr		  pFeature_Src;
	IGeometryPtr	  pGeometry;
	VARIANT_BOOL	  varIsExist = VARIANT_TRUE;
	IFeatureCursorPtr pFeatureCur_Des;
	IFeatureBufferPtr pFeatureBuf_Des;

	pFeatureCL_Des->Insert(VARIANT_TRUE, &pFeatureCur_Des);
	pFeatureCL_Des->CreateFeatureBuffer(&pFeatureBuf_Des);

	hr = pFeatureCL_Src->Search(NULL, VARIANT_FALSE, &pFeatureCur_Src);
	if (FAILED(hr))
	{
		return S_FALSE;
	}
	pFeatureCur_Src->NextFeature(&pFeature_Src);
	while(pFeature_Src != NULL)
	{
		pFeature_Src->get_Shape(&pGeometry);
		pGeometry->get_IsEmpty(&varIsExist);
		if (varIsExist == VARIANT_TRUE)
		{
			continue;
		}

		esriGeometryType      iGeometryType = esriGeometryNull;
		esriGeometryType      GeometryType = esriGeometryNull;
		long				  lCount = 0;
		IPointCollectionPtr   pPointColl;
		IPointPtr			  pPoint;
		double				  dX_Src = 0;
		double				  dY_Src = 0;
		double				  dX_Des = 0;
		double				  dY_Des = 0;
		double				  dZ_Des = 0;
		double				  dXTo_Src = 0;
		double				  dYTo_Src = 0;
		double				  dXFrom_Src = 0;
		double				  dYFrom_Src = 0;
		ISegmentCollectionPtr pSegColl;
		ISegmentPtr           pSegment;
		ICircularArcPtr       pCircularArc;
		IEllipticArcPtr       pEllipticArc;
		IPointPtr		      centerPnt(CLSID_Point);
		IPointPtr			  fromPnt(CLSID_Point);
		IPointPtr			  toPnt(CLSID_Point);
		double				  dRadius = 0;
		double				  rotationAngle= 0;
		double                minorMajorRatio= 0;
		VARIANT_BOOL          isCCW = VARIANT_FALSE;
		VARIANT_BOOL          minor = VARIANT_FALSE;
		long                  lPntCount = 0;
		esriArcOrientation    arcOrientation = esriArcClockwise;
		double				  fromAngle = 0;
		double                centralAngle = 0;
		double                semiMajor = 0;
		double                semiMinor = 0;
		VARIANT_BOOL		  isCircular = VARIANT_FALSE;

		long oid = 0;
		pFeature_Src->get_OID(&oid);

		pGeometry->get_GeometryType(&iGeometryType);
		switch (iGeometryType)
		{
		case esriGeometryPoint:
		case esriGeometryMultipoint:

			pPointColl = pGeometry;
			pPointColl->get_PointCount(&lCount);

			for (int i = 0; i < lCount; i++)
			{
				pPointColl->get_Point(i, &pPoint);
				pPoint->get_X(&dX_Src);
				pPoint->get_Y(&dY_Src);

				//转换处理
				m_Trans.TransSDEVector(dY_Src, dX_Src, 0, dY_Des, dX_Des, dZ_Des);
				pPoint->put_X(dX_Des);
				pPoint->put_Y(dY_Des);
				pPointColl->UpdatePoint(i, pPoint);
			}

			break;

		case esriGeometryLine:
		case esriGeometryPolyline:
		case esriGeometryPolygon:

			pSegColl = pGeometry;
			pSegColl->get_SegmentCount(&lCount);
			for (int i = 0; i < lCount; i++)
			{
				pSegColl->get_Segment(i, &pSegment);
				pSegment->get_GeometryType(&GeometryType);
				switch (GeometryType)
				{
				case esriGeometryCircularArc:

					pCircularArc = pSegment;
					pCircularArc->QueryCoords(centerPnt, fromPnt, toPnt, &isCCW, &minor);

					//判断方向
					pCircularArc->get_CentralAngle(&centralAngle);
					dX_Des = fabs(centralAngle);
					if (fabs(centralAngle) == M_PI || fabs(centralAngle) == 2*M_PI)
					{
						arcOrientation = (isCCW == VARIANT_TRUE) ? esriArcCounterClockwise : esriArcClockwise;
					}
					else
					{
						arcOrientation = (minor == VARIANT_TRUE) ? esriArcMinor : esriArcMajor;
					}

					//转换处理
					centerPnt->get_X(&dX_Src);
					centerPnt->get_Y(&dY_Src);
					m_Trans.TransSDEVector(dY_Src, dX_Src, 0, dY_Des, dX_Des, dZ_Des);
					centerPnt->put_X(dX_Des);
					centerPnt->put_Y(dY_Des);

					fromPnt->get_X(&dX_Src);
					fromPnt->get_Y(&dY_Src);
					m_Trans.TransSDEVector(dY_Src, dX_Src, 0, dY_Des, dX_Des, dZ_Des);
					fromPnt->put_X(dX_Des);
					fromPnt->put_Y(dY_Des);

					toPnt->get_X(&dX_Src);
					toPnt->get_Y(&dY_Src);
					m_Trans.TransSDEVector(dY_Src, dX_Src, 0, dY_Des, dX_Des, dZ_Des);
					toPnt->put_X(dX_Des);
					toPnt->put_Y(dY_Des);

					pCircularArc->PutCoords(centerPnt, fromPnt, toPnt, arcOrientation);

					break;

				case esriGeometryEllipticArc:

					pEllipticArc = pSegment;
					pEllipticArc->QueryCoords(true, centerPnt, fromPnt, toPnt, &rotationAngle, &minorMajorRatio, &isCCW, &minor);

					//判断方向
					pEllipticArc->get_CentralAngle(&centralAngle);
					//if (fabs(centralAngle) == M_PI || fabs(centralAngle) == 2*M_PI)
					//{
					//	arcOrientation = (isCCW == VARIANT_TRUE) ? esriArcCounterClockwise : esriArcClockwise;
					//}
					//else
					//{
					//	arcOrientation = (minor == VARIANT_TRUE) ? esriArcMinor : esriArcMajor;
					//}

					//转换处理
					dX_Src = 0;
					dY_Src = 0;
					dX_Des = 0;
					dY_Des = 0;
					centerPnt->get_X(&dX_Src);
					centerPnt->get_Y(&dY_Src);
					m_Trans.TransSDEVector(dY_Src, dX_Src, 0, dY_Des, dX_Des, dZ_Des);
					centerPnt->put_X(dX_Des);
					centerPnt->put_Y(dY_Des);

					//dXFrom_Src = 0;
					//dYFrom_Src = 0;
					//dX_Des = 0;
					//dY_Des = 0;
					//fromPnt->get_X(&dXFrom_Src);
					//fromPnt->get_Y(&dYFrom_Src);
					//m_Trans.TransSDEVector(dYFrom_Src, dXFrom_Src, 0, dY_Des, dX_Des, dZ_Des);
					//fromPnt->put_X(dX_Des);
					//fromPnt->put_Y(dY_Des);

					//dXTo_Src = 0;
					//dYTo_Src = 0;
					//dX_Des = 0;
					//dY_Des = 0;
					//toPnt->get_X(&dXTo_Src);
					//toPnt->get_Y(&dYTo_Src);
					//m_Trans.TransSDEVector(dYTo_Src, dXTo_Src, 0, dY_Des, dX_Des, dZ_Des);
					//toPnt->put_X(dX_Des);
					//toPnt->put_Y(dY_Des);

					//if ((dXFrom_Src == dXTo_Src && dYFrom_Src == dYTo_Src) || (iGeometryType == esriGeometryPolygon))
					//{
						pEllipticArc->get_FromAngle(true, &fromAngle);
						pEllipticArc->GetAxes(&semiMajor, &semiMinor, &minorMajorRatio);
						hr = pEllipticArc->PutCoordsByAngle(true, centerPnt, fromAngle, centralAngle, rotationAngle, semiMajor, minorMajorRatio);
					//}
					//else
					//{
					//	hr = pEllipticArc->PutCoords(true, centerPnt, fromPnt, toPnt, rotationAngle, minorMajorRatio, arcOrientation);
					//}

					break;

				default: 
					pSegment->get_FromPoint(&fromPnt);

					//转换处理
					fromPnt->get_X(&dX_Src);
					fromPnt->get_Y(&dY_Src);
					m_Trans.TransSDEVector(dY_Src, dX_Src, 0, dY_Des, dX_Des, dZ_Des);
					fromPnt->put_X(dX_Des);
					fromPnt->put_Y(dY_Des);
					pSegment->put_FromPoint(fromPnt);

					if (i == lCount-1)
					{
						pSegment->get_ToPoint(&toPnt);

						//转换处理
						toPnt->get_X(&dX_Src);
						toPnt->get_Y(&dY_Src);
						m_Trans.TransSDEVector(dY_Src, dX_Src, 0, dY_Des, dX_Des, dZ_Des);
						toPnt->put_X(dX_Des);
						toPnt->put_Y(dY_Des);
						pSegment->put_ToPoint(toPnt);
					}

					break;
				}
			}

			break;

		default:
			break;
		}

		pGeometry->putref_SpatialReference(m_pSpatial);
		InsertFeature(pFeatureCur_Des, pFeatureBuf_Des, pFeature_Src, pGeometry);

		pFeatureCur_Src->NextFeature(&pFeature_Src);
	}

	pFeatureCur_Des->Flush();

	return S_OK;
}

HRESULT ArcGDBTest::InsertFeature(IFeatureCursorPtr pFeatureCur, IFeatureBufferPtr pFeatureBuf, IFeaturePtr pFeature, IGeometryPtr pGeometry)
{
	IFieldsPtr pFields;
	pFeature->get_Fields(&pFields);

	long	   fieldCount = 0;
	pFields->get_FieldCount(&fieldCount);

	for (long i = 0; i < fieldCount; ++i) //skip OID and geometry fields
	{
		IFieldPtr     pField;
		pFields->get_Field(i, &pField);

		esriFieldType esriField;
		pField->get_Type(&esriField);

		VARIANT_BOOL  varboolEdit;
		pField->get_Editable(&varboolEdit);

		if ((esriField != esriFieldTypeGeometry) && (esriField != esriFieldTypeOID) && (varboolEdit))
		{
			CComVariant		origValue;
			pFeature->get_Value(i, &origValue);
			pFeatureBuf->put_Value(i, origValue);
		}
	}

	pFeatureBuf->putref_Shape(pGeometry);

	CComVariant varID;
	HRESULT hr = pFeatureCur->InsertFeature(pFeatureBuf, &varID);
	if (FAILED(hr))
	{
		return S_FALSE;
	}

	return S_OK;
}