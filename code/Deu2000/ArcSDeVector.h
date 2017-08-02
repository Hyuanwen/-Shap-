/*
	���ܣ�֧��ArcSDEʸ�����ݼ�ת��
	ʱ�䣺2013-10-10
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
	//���ܣ�����ʸ�����ݼ�ת����Ҫ����

	HRESULT GetAllFeatureNameAndType(vector<STR_SDEINFO>& vecAll);
	//���ܣ���ȡ����ʸ�����ݼ����Ƽ�����

	HRESULT GetFeatureByType(esriDatasetType type, vector<STR_SDEINFO>& vecDT);

	HRESULT	TransFeatureDTType(STR_SDEINFO sdeInfo);

	HRESULT RegisterWnd(HWND hwnd);

private:
	HRESULT TransFeatureClass(const string& strFeatureName);
	HRESULT TransFeatureClass(IFeatureDatasetPtr pFeatureDS_Des, const string& strFeatureName);
	//���ܣ�֧��FeatureClassת��

	HRESULT TransFeatureDataset(const string& strDatasetName);
	//���ܣ�֧��FeatureDatasetת��

	HRESULT InsertFeature(IFeatureCursorPtr ipInsertCur, IFeatureBufferPtr ipFeatureBuf, IFeaturePtr ipFeature, IGeometryPtr ipGeom);
private:
	IWorkspacePtr			m_WorkspaceSrc;
	IWorkspacePtr			m_WorkspaceDes;
	CDeuTrans				m_Trans;
	string					m_strPrjFullPath;
	HWND					m_hWnd;						//���������� add by chenyong 2013-12-4
};

#endif
