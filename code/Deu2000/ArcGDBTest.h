#ifndef _ARCGDBTEST_H_
#define _ARCGDBTEST_H_

class CDeuTrans;
class ArcGDBTest
{
public:
	ArcGDBTest();
	~ArcGDBTest();

public:
	HRESULT TransShpFile();

	HRESULT	TransGDBFile();
	
	HRESULT OpenFeatureDataset();

	HRESULT TransFeatureDataset(const string& strDSName);

	HRESULT OpenFeatureClass();

	HRESULT TransFeatureClass(enum esriDatasetType datasetType, IFeatureDatasetPtr pFeatureDS_Des, const string& featureName);

	HRESULT InsertFeature(IFeatureCursorPtr pFeatureCur, IFeatureBufferPtr pFeatureBuf, IFeaturePtr pFeature, IGeometryPtr pGeometry);

private:
	IWorkspacePtr			m_Workspace_Src;
	IWorkspacePtr			m_Workspace_Des;
	ISpatialReferencePtr	m_pSpatial;
	CDeuTrans				m_Trans;
};

#endif