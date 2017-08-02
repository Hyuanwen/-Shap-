/*
	功能：支持ArcSDE栅格数据集转换
	时间：2013-10-11

	说明：处理RasterCatalog时，分成两步过程：
		  1. 遍历原始RasterCatalog，在本地生成转换后的文件格式
		  2. 加载到目标库的RasterCatalog中
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

	double				dPixelXDes;			//目标栅格文件的X方向分辨率
	double				dPixelYDes;			//目标栅格文件的Y方向分辨率

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
	//功能：设置栅格集转换需要参数

	HRESULT GetAllRasterNameAndType(vector<STR_SDEINFO>& vecAll);
	//功能：获取所有栅格集名称及类型

	HRESULT	TransRasterDTType(STR_SDEINFO sdeInfo);
	//功能：不周坐标系间转换

	HRESULT ProjectRasterDTType(STR_SDEINFO sdeInfo);
	//功能：投影

	HRESULT RegisterWnd(HWND hwnd);

private:
	HRESULT CaComputeStatsAndHist(IRasterBandCollectionPtr ipRasterBandCol);

	HRESULT AlterSpatialReference(const string& strSpatialRef, IRasterDatasetPtr ipRasterDS);
	//功能：修改空间参考信息

	HRESULT	TransRasterDataset(const string& strDatasetName);
	//功能：支持RasterDataset转换

	HRESULT TransRasterCatalog(const string& strCatalogName);
	//功能：支持RasterCatalog转换

	HRESULT	TransRasterByNearestBlock(IRasterPtr ipRasterSrc, IRasterPtr ipRasterDes, STR_RASTERPARAM param);
	//分块处理(大数据集，如大于10000*10000,采用分块来处理，保证内存能正常分配)

	HRESULT TransRasterByNearest(IRasterPtr ipRasterSrc, IRasterPtr	ipRasterDes, STR_RASTERPARAM param);

	HRESULT CreateLocalRasteDataset(const string& strName, IRasterWorkspace2Ptr ipRasterWS, IRasterPtr ipRaster);
	//功能：本地生成转换后的文件

	HRESULT	GetRasterByType(esriDatasetType type, vector<STR_SDEINFO>& vecDT);

	HRESULT ProjectRasterDataset(const string& strDatasetName);
	//功能：支持RasterDataset投影

	HRESULT ProjectRasterCatalog(const string& strCatalogName);
	//功能：支持RasterCatalog投影

	HRESULT CreateLocalProjectRasterDataset(const string& strName, IRasterWorkspace2Ptr ipRasterWS, IRasterPtr ipRaster);
	//功能：本地生成投影后的文件

	//add by chenyong 2013-14-2
	HRESULT TransRasterDatasetByLocal(const string& strDatasetName);
	HRESULT ProjectRasterByLocal(const string& strDatasetName);

private:

	IWorkspacePtr				m_WorkspaceSrc;
	IWorkspacePtr				m_WorkspaceDes;
	CDeuRasterTrans				m_DeuRasterTrans;
	string						m_strPrjFullPath;				//目标数据空间参考信息
	HWND						m_hWnd;							//
};

#endif
