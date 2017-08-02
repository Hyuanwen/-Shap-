/*
	���ܣ�֧��ArcSDEդ�����ݼ�ת��
	ʱ�䣺2013-10-11

	˵��������RasterCatalogʱ���ֳ��������̣�
		  1. ����ԭʼRasterCatalog���ڱ�������ת������ļ���ʽ
		  2. ���ص�Ŀ����RasterCatalog��
*/

#ifndef _ARCSDE_RASTER_H
#define _ARCSDE_RASTER_H


class CDeuRasterTrans;

struct STR_ENVELOPE
{
	double			dXmin;
	double			dYmin;
	double			dXmax;
	double			dYmax;
};


struct STR_RASTERPARAM 
{
	VARTYPE				type;
	long				lBandCount;
	double				dPixelX;
	double				dPixelY;

	double				dPixelXDes;			//Ŀ��դ���ļ���X����ֱ���
	double				dPixelYDes;			//Ŀ��դ���ļ���Y����ֱ���

	double				dXminSrc;
	double				dYmaxSrc;
	double				dXminDes;
	double				dYmaxDes;
	long				lWidthSrc;
	long				lHeighSrc;
	long				lWidthDes;
	long				lHeighDes;

	STR_ENVELOPE		envSrc;
	STR_ENVELOPE		envDes;
	//long				lNoValue;
	VARIANT				lNoValue;

};



class CArcSDERaster
{
public:
	CArcSDERaster();
	explicit CArcSDERaster(IWorkspacePtr ipWorkspaceSrc);
	~CArcSDERaster(){}

public:
	void	SetTransParam(IWorkspacePtr pWorkspaceSrc, IWorkspacePtr pWorkspaceDes, const CDeuRasterTrans& trans, const string& strPrjFullPath);
	//���ܣ�����դ��ת����Ҫ����

	HRESULT GetAllRasterNameAndType(vector<STR_SDEINFO>& vecAll);
	//���ܣ���ȡ����դ�����Ƽ�����

	HRESULT	TransRasterDTType(STR_SDEINFO sdeInfo);
	//���ܣ���������ϵ��ת��

	HRESULT ProjectRasterDTType(STR_SDEINFO sdeInfo);
	//���ܣ�ͶӰ

	HRESULT RegisterWnd(HWND hwnd);

private:
	HRESULT CaComputeStatsAndHist(IRasterBandCollectionPtr ipRasterBandCol);

	HRESULT AlterSpatialReference(const string& strSpatialRef, IRasterDatasetPtr ipRasterDS);
	//���ܣ��޸Ŀռ�ο���Ϣ

	HRESULT	TransRasterDataset(const string& strDatasetName);
	//���ܣ�֧��RasterDatasetת��

	HRESULT TransRasterCatalog(const string& strCatalogName);
	//���ܣ�֧��RasterCatalogת��

	HRESULT	TransRasterByNearestBlock(IRasterPtr ipRasterSrc, IRasterPtr ipRasterDes, STR_RASTERPARAM param);
	//�ֿ鴦��(�����ݼ��������10000*10000,���÷ֿ���������֤�ڴ�����������)

	HRESULT TransRasterByNearest(IRasterPtr ipRasterSrc, IRasterPtr	ipRasterDes, STR_RASTERPARAM param);

	HRESULT CreateLocalRasteDataset(const string& strName, IRasterWorkspace2Ptr ipRasterWS, IRasterPtr ipRaster);
	//���ܣ���������ת������ļ�

	HRESULT	GetRasterByType(esriDatasetType type, vector<STR_SDEINFO>& vecDT);

	HRESULT ProjectRasterDataset(const string& strDatasetName);
	//���ܣ�֧��RasterDatasetͶӰ

	HRESULT ProjectRasterCatalog(const string& strCatalogName);
	//���ܣ�֧��RasterCatalogͶӰ

	HRESULT CreateLocalProjectRasterDataset(const string& strName, IRasterWorkspace2Ptr ipRasterWS, IRasterPtr ipRaster);
	//���ܣ���������ͶӰ����ļ�

	//add by chenyong 2013-14-2
	HRESULT TransRasterDatasetByLocal(const string& strDatasetName);
	HRESULT ProjectRasterByLocal(const string& strDatasetName);

private:

	IWorkspacePtr				m_WorkspaceSrc;
	IWorkspacePtr				m_WorkspaceDes;
	CDeuRasterTrans				m_DeuRasterTrans;
	string						m_strPrjFullPath;				//Ŀ�����ݿռ�ο���Ϣ
	HWND						m_hWnd;							//
};

#endif
