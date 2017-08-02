/*
	功能：支持ArcSDE矢量数据集转换
	时间：2013-10-10
*/


#ifndef _ARCSDEVECTOR_H_
#define _ARCSDEVECTOR_H_


class CDeuTrans;

class CArcSDEVector
{
public:
	CArcSDEVector();
	explicit CArcSDEVector(IWorkspacePtr	pWorkspace);
	~CArcSDEVector();
protected:

public:
	void	SetTransParam(IWorkspacePtr pWorkspaceSrc, IWorkspacePtr pWorkspaceDes, const CDeuTrans& trans, const string& strPrjFullPath);
	//功能：设置矢量数据集转换需要参数

	HRESULT GetAllFeatureNameAndType(vector<STR_SDEINFO>& vecAll);
	//功能：获取所有矢量数据集名称及类型

	HRESULT GetFeatureByType(esriDatasetType type, vector<STR_SDEINFO>& vecDT);

	HRESULT	TransFeatureDTType(STR_SDEINFO sdeInfo);

	HRESULT RegisterWnd(HWND hwnd);

private:
	HRESULT TransFeatureClass(const string& strFeatureName);
	HRESULT TransFeatureClass(IFeatureDatasetPtr pFeatureDS_Des, const string& strFeatureName);
	//功能：支持FeatureClass转换

	HRESULT TransFeatureDataset(const string& strDatasetName);
	//功能：支持FeatureDataset转换

	HRESULT InsertFeature(IFeatureCursorPtr ipInsertCur, IFeatureBufferPtr ipFeatureBuf, IFeaturePtr ipFeature, IGeometryPtr ipGeom);
private:
	IWorkspacePtr			m_WorkspaceSrc;
	IWorkspacePtr			m_WorkspaceDes;
	CDeuTrans				m_Trans;
	string					m_strPrjFullPath;
	HWND					m_hWnd;						//操作进度条 add by chenyong 2013-12-4
};

#endif
