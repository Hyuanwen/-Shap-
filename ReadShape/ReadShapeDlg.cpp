// ReadShapeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ReadShape.h"
#include "ReadShapeDlg.h"
#include <string>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif
using namespace std;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CReadShapeDlg 对话框




CReadShapeDlg::CReadShapeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CReadShapeDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}



void CReadShapeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ShapeList);
	DDX_Control(pDX, IDC_LIST2, m_TranShapeList);
	DDX_Control(pDX, IDC_EDIT2, m_edit_OutputFile);
}

BEGIN_MESSAGE_MAP(CReadShapeDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_SELECT, &CReadShapeDlg::OnBnClickedSelect)
	ON_BN_CLICKED(IDC_BUTTON2, &CReadShapeDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CReadShapeDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CReadShapeDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CReadShapeDlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CReadShapeDlg 消息处理程序

BOOL CReadShapeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	m_ShapeList.SetExtendedStyle(m_ShapeList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);   
	DWORD dwStyle = m_ShapeList.GetExtendedStyle();   
	m_ShapeList.InsertColumn(0,_T("ID"),LVCFMT_CENTER,50,0);
	m_ShapeList.InsertColumn(1,_T("X坐标"),LVCFMT_CENTER,100,0);
	m_ShapeList.InsertColumn(2,_T("Y坐标"),LVCFMT_CENTER,100,0);

	m_TranShapeList.SetExtendedStyle(m_TranShapeList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);   
	DWORD dwStyle2 = m_TranShapeList.GetExtendedStyle();   
	m_TranShapeList.InsertColumn(0,_T("ID"),LVCFMT_CENTER,50,0);
	m_TranShapeList.InsertColumn(1,_T("X坐标"),LVCFMT_CENTER,100,0);
	m_TranShapeList.InsertColumn(2,_T("Y坐标"),LVCFMT_CENTER,100,0);


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CReadShapeDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CReadShapeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CReadShapeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CReadShapeDlg::OnBnClickedSelect()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog dlg(TRUE, _T("*.shp"), NULL, OFN_ALLOWMULTISELECT|OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, _T("shp文件(*.shp)|*.shp;|所有文件 (*.*)|*.*||"), NULL); 
	dlg.m_ofn.lpstrTitle = _T("选择shp文件");
	//dlg.DoModal();

	std::vector<CString> vecPicPaths;
	if(dlg.DoModal() == IDOK) 
	{ 
		POSITION fileNamesPosition = dlg.GetStartPosition(); 
		while(fileNamesPosition != NULL) 
		{ 
			infilename = dlg.GetNextPathName(fileNamesPosition); 
			vecPicPaths.push_back(infilename);
		}   
	}
	//编辑框获取文件路径
	GetDlgItem(IDC_EDIT1)->SetWindowText(infilename);

	////"C:\Users\Rkc\Desktop\point\point.shp"
	// CString outFileName;
	// outFileName=dlg.GetFileTitle();
	//readShape(infilename,outFilePath);

}
//清空列表及容器
void CReadShapeDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ShapeList.DeleteAllItems();
	m_TranShapeList.DeleteAllItems();
	m_value.clear();
}
//执行转换
void CReadShapeDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	//坐标转换
	readShape(infilename,outfilename);

	ViewShape(infilename);
	//将数据显示到列表中
	m_ShapeList.DeleteAllItems();
	for(long i=0;i<m_value.size();i++)
	{	
		m_ShapeList.InsertItem(i,"");
		CString List_id;
		List_id.Format(_T("%d"),m_value[i].id);
		m_ShapeList.SetItemText(i,0,List_id);

		CString List_x;
		List_x.Format(_T("%.3f"),m_value[i].x);
		m_ShapeList.SetItemText(i,1,List_x);

		CString List_y;
		List_y.Format(_T("%.3f"),m_value[i].y);
		m_ShapeList.SetItemText(i,2,List_y);
	}

	ViewShape(outfilename);
	//将数据显示到列表中
	m_TranShapeList.DeleteAllItems();
	for(long i=0;i<m_value.size();i++)
	{	
		m_TranShapeList.InsertItem(i,"");
		CString List_id;
		List_id.Format(_T("%d"),m_value[i].id);
		m_TranShapeList.SetItemText(i,0,List_id);

		CString List_x;
		List_x.Format(_T("%.3f"),m_value[i].x);
		m_TranShapeList.SetItemText(i,1,List_x);

		CString List_y;
		List_y.Format(_T("%.3f"),m_value[i].y);
		m_TranShapeList.SetItemText(i,2,List_y);
	}
}


//解析shape文件
void CReadShapeDlg::readShape( CString inFileName,CString outFileName)
{
	//打开shape文件（绝对路径）
	OGRRegisterAll();
	OGRDataSource       *poDS = NULL;
	poDS = OGRSFDriverRegistrar::Open(inFileName, FALSE );

	if( poDS == NULL )
	{
		MessageBox( _T("转换文件失败！"),_T("提示") );
		exit(1);
	}

	MessageBox(_T("转换文件成功！"),_T("提示"));

	//创建目标数据源
	//const char *pszDriverNameOut = "ESRI Shapefile";

	CString inDriverName="ESRI Shapefile";
	CString outDriverName="ESRI Shapefile";
	OGRSFDriver *poDriverOut;
	//OGRRegisterAll();

	poDriverOut = OGRSFDriverRegistrar::GetRegistrar()->GetDriverByName(outDriverName);
	
	if( poDriverOut == NULL )
	{
		exit(1);
	}

	OGRDataSource *poDSOut;

	//for linux
	//如果存在就删除它

	//std::fstream _file;		
	//CString filenameout="C:\\Users\\Rkc\\Desktop\\OutputData\\OutputData.shp";
	//_bstr_t bstr_filename = filenameout;
	//char* strFileName = (LPSTR)bstr_filename;

	//BOOL ret= DeleteFileA(strFileName);			
	//创建空的输出图层
	poDSOut = poDriverOut->CreateDataSource(outFileName, NULL );
	if( poDSOut == NULL )
	{
		exit(1);
	}
	
	//layer to feature
	int lyrCount=0;
	lyrCount=poDS->GetLayerCount();//输入shape文件图层总数

	//声明输出图层
	OGRLayer  *TmppoLayer;
	//获得输入总地物个数，即总行数
	for (int i=0;i<lyrCount;i++)
	{
		TmppoLayer=poDS->GetLayer(i);//输出shape文件获取输入文件图层(空的)
		unsigned int _fea_count=TmppoLayer->GetFeatureCount();
		m_all_fea_count+=_fea_count;
	}

    //遍历shape文件
	OGRLayer  *poLayer;
	for (int i=0;i<lyrCount;i++)
	{
		poLayer=poDS->GetLayer(i);

		//获得图层范围
		//virtual OGRErr GetExtent(OGREnvelope *psExtent, int bForce = TRUE);
		//获得图层坐标xyz
		OGREnvelope extent;
		poLayer->GetExtent(&extent);


		OGRLayer *poLayerOut;
		OGRFeatureDefn * poFeaDef=poLayer->GetLayerDefn();
		//获取图层名称
		CString szlyrname=poFeaDef->GetName();
		CString res_lyrname;
		res_lyrname=szlyrname;	
		//获取几何类型
		OGRwkbGeometryType type=poLayer->GetLayerDefn()->GetGeomType();

		//创建输出shape图层		
		poLayerOut=poDSOut->CreateLayer(res_lyrname,NULL,type);
		if(poLayerOut==NULL)
		{
			//LOGSTR(":创建目标文件失败");
			MessageBox(_T("创建目标文件失败"),_T("提示"));
			continue;
		}

		//创建shape输出图层字段
		int _field_count= poFeaDef->GetFieldCount();  //获得每行字段总数 不包含前两个字段（FID、shaape类型）
		for (int i=0;i<_field_count;i++)
		{
			OGRFieldDefn *poField=poFeaDef->GetFieldDefn(i);
			//创建shape输出图层字段
			poLayerOut->CreateField(poField);
		}

		//poLayerOut = poDSOut->CreateLayer( "point_out", NULL, wkbPoint, NULL );
		if( poLayerOut == NULL )
		{
			exit(1);
		}

		OGRFeature *poFeature;
		//OGRFeature *poFeatureOut;
		unsigned int _this_fea_count=poLayer->GetFeatureCount();

		poLayer->ResetReading();

		//遍历每行的所有字段
		for (unsigned long  i=0;i<_this_fea_count;i++)
		{	
			m_fea_done++;

			poFeature = poLayer->GetNextFeature();
			if (poFeature ==NULL)
			{
				m_fea_null_count++;
				continue;
			}

			int fea_FID=poFeature->GetFID();
			OGRGeometry *poGeometry=NULL;//几何拓扑关系

			OGRLineString *poLine=NULL;
			OGRPoint *poPoint=NULL;
			OGRMultiPoint *poMultiPoint=NULL;
			OGRMultiLineString *poMultiLineString=NULL;
			OGRPolygon *poPolygon=NULL;
			OGRMultiPolygon *poMultiPolygon=NULL; 

			poGeometry = poFeature->GetGeometryRef();//获取几何拓扑关系
			//each geometry trans its coordinate
			if(poGeometry == NULL)
			{
				m_geo_null_count++;

				OGRErr _error =poLayerOut->CreateFeature( poFeature ) ;
				if( _error!= OGRERR_NONE )
				{
					//LOGSTR( "error:Failed to create feature in shapefile." );
					//return S_FALSE;
					m_fea_fail_count++;					
				}

				m_fea_create_count++;

				OGRFeature::DestroyFeature( poFeature );
				continue;
			}

			OGRwkbGeometryType type=poGeometry->getGeometryType();//获取几何类型

			double _oldX;
			double _oldY;
			double _oldZ;

			double _newX;
			double _newY;
			double _newZ;

			int _pt_count=0;
			int _ex_count;
			OGRLinearRing* _ex_ring=NULL;
			int _in_ring_count=0;
			int _geo_count=0;

			m_geo_done++;
			//判别shape 
			switch (type)
			{
				//点
			case wkbPoint:
			case wkbPoint25D:
				m_geo_point_count++;

				poPoint=(OGRPoint*)poGeometry;

				_oldX=poPoint->getX();//经度或东方向
				_oldY=poPoint->getY();//纬度或北方向
				_oldZ=poPoint->getZ();

				if(_oldX>extent.MaxX||_oldX<extent.MinX||_oldY>extent.MaxY||_oldY<extent.MinY)
				{
					m_geo_ori_error_count++;

					char *geo_Ori_Error=(char*)malloc(100);
					int fea_FID=poFeature->GetFID();
					itoa(fea_FID,geo_Ori_Error,10);
				}

				//_coordtransf( fea_FID , 1,&_oldX,&_oldY,&_oldZ,&_newX,&_newY,&_newZ);
				TransLate(_oldX,_oldY,_oldZ,_newX,_newY,_newZ);

				if(poPoint->getDimension()==0)
				{
					poPoint->setX(_newX);
					poPoint->setY(_newY);
				}
				else if(poPoint->getDimension()==1)
				{
					poPoint->setX(_newX);
					poPoint->setY(_newY);
					poPoint->setZ(_newZ);
				}

				break;
				//线
			case wkbLineString:
			case wkbLineString25D:
				m_geo_line_count++;
								
				poLine=(OGRLineString *) poGeometry;
				_pt_count=poLine->getNumPoints();

				for (int i=0;i<_pt_count;i++)
				{
					_oldX=poLine->getX(i);//经度或东方向
					_oldY=poLine->getY(i);//纬度或北方向
					_oldZ=poLine->getZ(i);

					if(_oldX>extent.MaxX||_oldX<extent.MinX||_oldY>extent.MaxY||_oldY<extent.MinY)
					{
						m_geo_ori_error_count++;

						char *geo_Ori_Error=(char*)malloc(100);
						int fea_FID=poFeature->GetFID();
						itoa(fea_FID,geo_Ori_Error,10);
					}

					//_coordtransf( fea_FID , 1,&_oldX,&_oldY,&_oldZ,&_newX,&_newY,&_newZ);
					TransLate(_oldX,_oldY,_oldZ,_newX,_newY,_newZ);

					if (poLine->getDimension()==0)
					{
						poLine->setPoint(i,_newX,_newY);
					}
					else if(poLine->getDimension()==1)
					{
						poLine->setPoint(i,_newX,_newY);
					}
					else if(poLine->getDimension()==2)
					{
						poLine->setPoint(i,_newX,_newY,_newZ);
					}
				}

				//_coordtransf(_pt_count,ori_x,ori_y,ori_z,Newx,Newy,Newz);
				//TransLate(ori_x,ori_y,ori_z,Newx,Newy,Newz);
				break;
				//点集合
			case wkbMultiPoint:
			case wkbMultiPoint25D:
				m_geo_multi_point_count++;

				poMultiPoint=(OGRMultiPoint *)poGeometry;
				poMultiPoint->getNumGeometries();
				_pt_count=poMultiPoint->getNumGeometries();

				for (int i=0;i<_pt_count;i++)
				{
					_oldX=((OGRPoint*)poMultiPoint->getGeometryRef(i))->getX();//经度或东方向
					_oldY=((OGRPoint*)poMultiPoint->getGeometryRef(i))->getY();//纬度或北方向
					_oldZ=((OGRPoint*)poMultiPoint->getGeometryRef(i))->getZ();

					if(_oldX>extent.MaxX||_oldX<extent.MinX||_oldY>extent.MaxY||_oldY<extent.MinY)
					{
						m_geo_ori_error_count++;

						char *geo_Ori_Error=(char*)malloc(100);
						int fea_FID=poFeature->GetFID();
						itoa(fea_FID,geo_Ori_Error,10);
					}

					//_coordtransf(fea_FID ,1,&_oldX,&_oldY,&_oldZ,&_newX,&_newY,&_newZ);
					TransLate(_oldX,_oldY,_oldZ,_newX,_newY,_newZ);
					
					OGRPoint* poPoint=((OGRPoint*)poMultiPoint->getGeometryRef(i));

					if(poPoint->getDimension()==0)
					{
						poPoint->setX(_newX);
						poPoint->setY(_newY);
					}
					else if(poPoint->getDimension()==1)
					{
						poPoint->setX(_newX);
						poPoint->setY(_newY);						
					}
				}

				//_coordtransf(_pt_count,ori_x,ori_y,ori_z,Newx,Newy,Newz);
				//TransLate(ori_x,ori_y,ori_z,Newx,Newy,Newz);
				break;
				//线集合
			case wkbMultiLineString:
			case wkbMultiLineString25D:
				m_geo_multi_line_count++;

				poMultiLineString=(OGRMultiLineString *)poGeometry;
				_geo_count= poMultiLineString->getNumGeometries();

				for (int i=0;i<_geo_count;i++)
				{
					OGRLineString* poLineString=(OGRLineString*)poMultiLineString->getGeometryRef(i);
					_pt_count=poLineString->getNumPoints();
					for (int j=0;j<_pt_count;j++)
					{
						_oldX=poLineString->getX(j);//经度或东方向
						_oldY=poLineString->getY(j);//纬度或北方向
						_oldZ=poLineString->getZ(j);

						if(_oldX>extent.MaxX||_oldX<extent.MinX||_oldY>extent.MaxY||_oldY<extent.MinY)
						{
							m_geo_ori_error_count++;

							char *geo_Ori_Error=(char*)malloc(100);
							int fea_FID=poFeature->GetFID();
							itoa(fea_FID,geo_Ori_Error,10);
						}

						//_coordtransf(fea_FID ,1,&_oldX,&_oldY,&_oldZ,&_newX,&_newY,&_newZ);
						TransLate(_oldX,_oldY,_oldZ,_newX,_newY,_newZ);

						if(poLineString->getDimension()==0)
						{
							poLineString->setPoint(j,_newX,_newY);
						}
						else if(poLineString->getDimension()==1)
						{
							poLineString->setPoint(j,_newX,_newY);
						}
						else if(poLineString->getDimension()==2)
						{
							poLineString->setPoint(i,_newX,_newY,_newZ);
						}					
					}
				}
				break;
				//面
			case wkbPolygon:
			case wkbPolygon25D:
				m_geo_polygon_count++;

				poPolygon=(OGRPolygon *)poGeometry;

				_in_ring_count=poPolygon->getNumInteriorRings();

				for (int i=0;i<_in_ring_count;i++)
				{
					OGRLinearRing* ring=poPolygon->getInteriorRing(i);
					int _ring_count=ring->getNumPoints();
					for (int j=0;j<_ring_count;j++)
					{
						_oldX= ring->getX(j);//经度或东方向
						_oldY= ring->getY(j);//纬度或北方向
						_oldZ= ring->getZ(j);

						if(_oldY>extent.MaxX||_oldY<extent.MinX||_oldX>extent.MaxY||_oldX<extent.MinY)
						{
							m_geo_ori_error_count++;

							char *geo_Ori_Error=(char*)malloc(100);
							int fea_FID=poFeature->GetFID();
							itoa(fea_FID,geo_Ori_Error,10);
						}

						//_coordtransf(fea_FID ,1,&_oldX,&_oldY,&_oldZ,&_newX,&_newY,&_newZ);
						TransLate(_oldX,_oldY,_oldZ,_newX,_newY,_newZ);

						if(poPolygon->getDimension()==0)
						{
							ring->setPoint(j,_newY,_newX);
						}
						else if(poPolygon->getDimension()==1)
						{
							ring->setPoint(j,_newY,_newX);
						}	
						else if(poPolygon->getDimension()==2)
						{
							ring->setPoint(j,_newY,_newX,_newZ);
						}		
					}
				}

				_ex_ring=poPolygon->getExteriorRing();
				_ex_count=_ex_ring->getNumPoints();
				for (int i=0;i<_ex_count;i++)
				{
					_oldX= _ex_ring->getX(i);//经度或东方向
					_oldY= _ex_ring->getY(i);//纬度或北方向
					_oldZ= _ex_ring->getZ(i);

					if(_oldX>extent.MaxX||_oldX<extent.MinX||_oldY>extent.MaxY||_oldY<extent.MinY)
					{
						m_geo_ori_error_count++;

						char *geo_Ori_Error=(char*)malloc(100);
						int fea_FID=poFeature->GetFID();
						itoa(fea_FID,geo_Ori_Error,10);

					}

					//_coordtransf(fea_FID ,1,&_oldX,&_oldY,&_oldZ,&_newX,&_newY,&_newZ);
					TransLate(_oldX,_oldY,_oldZ,_newX,_newY,_newZ);

					if(poPolygon->getDimension()==0)
					{
						_ex_ring->setPoint(i,_newX,_newY);
						//_ex_ring->setPoint(i,_oldY,_oldX);
					}
					else if(poPolygon->getDimension()==1)
					{
						_ex_ring->setPoint(i,_newX,_newY);
						//_ex_ring->setPoint(i,_oldY,_oldX);
					}	
					else if(poPolygon->getDimension()==2)
					{
						_ex_ring->setPoint(i,_newX,_newY,_newZ);
						//_ex_ring->setPoint(i,_oldY,_oldX,_oldZ);
					}	
				}
				break;
				//面集合
			case wkbMultiPolygon:
			case wkbMultiPolygon25D:
				m_geo_multi_polygon_count++;

				poMultiPolygon=(OGRMultiPolygon *)poGeometry;
				_geo_count=poMultiPolygon->getNumGeometries();

				for (int i=0;i<_geo_count;i++)
				{
					OGRPolygon* poPolygon=(OGRPolygon*)poMultiPolygon->getGeometryRef(i);
					if (NULL == poPolygon)
					{
						continue;
					}

					//内环
					_in_ring_count=poPolygon->getNumInteriorRings();

					for (int i=0;i<_in_ring_count;i++)
					{
						OGRLinearRing* ring=poPolygon->getInteriorRing(i);
						int _ring_count=ring->getNumPoints();
						for (int j=0;j<_ring_count;j++)
						{
							_oldX= ring->getX(j);//经度或东方向
							_oldX= ring->getY(j);//纬度或北方向
							_oldZ= ring->getZ(j);

							if(_oldX>extent.MaxX||_oldX<extent.MinX||_oldY>extent.MaxY||_oldY<extent.MinY)
							{
								m_geo_ori_error_count++;

								char *geo_Ori_Error=(char*)malloc(100);
								int fea_FID=poFeature->GetFID();
								itoa(fea_FID,geo_Ori_Error,10);
							}

							//_coordtransf(fea_FID ,1,&_oldX,&_oldY,&_oldZ,&_newX,&_newY,&_newZ);
							TransLate(_oldX,_oldY,_oldZ,_newX,_newY,_newZ);

							if(poPolygon->getDimension()==0)
							{
								ring->setPoint(j,_newX,_newY);
							}
							else if(poPolygon->getDimension()==1)
							{
								ring->setPoint(j,_newX,_newY);
							}
							else if(poPolygon->getDimension()==2)
							{
								ring->setPoint(j,_newX,_newY,_newZ);
							}
						}
					}

					//外环
					_ex_ring=poPolygon->getExteriorRing();
					_ex_count=_ex_ring->getNumPoints();
					for (int i=0;i<_ex_count;i++)
					{
						_oldX= _ex_ring->getX(i);//经度或东方向
						_oldY= _ex_ring->getY(i);//纬度或北方向
						_oldZ= _ex_ring->getZ(i);

						if(_oldX>extent.MaxX||_oldX<extent.MinX||_oldY>extent.MaxY||_oldY<extent.MinY)
						{
							m_geo_ori_error_count++;

							char *geo_Ori_Error=(char*)malloc(100);
							int fea_FID=poFeature->GetFID();
							itoa(fea_FID,geo_Ori_Error,10);
						}

						//_coordtransf(fea_FID ,1,&_oldX,&_oldY,&_oldZ,&_newX,&_newY,&_newZ);
						TransLate(_oldX,_oldY,_oldZ,_newX,_newY,_newZ);

						if(poPolygon->getDimension()==0)
						{
							_ex_ring->setPoint(i,_newX,_newY);
						}
						else if(poPolygon->getDimension()==1)
						{
							_ex_ring->setPoint(i,_newX,_newY);
						}
						else if(poPolygon->getDimension()==2)
						{
							_ex_ring->setPoint(i,_newX,_newY,_newZ);
						}					
					}
				}

				break;
				//混合类型
			case wkbGeometryCollection:
			case wkbGeometryCollection25D:
				m_error_count++;
				break;
			default:
				m_error_count++;
				break;
			}

			OGRErr _error =poLayerOut->CreateFeature( poFeature ) ;
			if( _error!= OGRERR_NONE )
			{
				printf( "Failed to create feature in shapefile.\n" );
				//return S_FALSE;
				m_fea_fail_count++;
				continue;
			}

			m_fea_create_count++;

			OGRFeature::DestroyFeature( poFeature );

		}//for each feature		
	}			
	OGRDataSource::DestroyDataSource( poDS );
	OGRDataSource::DestroyDataSource( poDSOut );
}


//转换函数
void CReadShapeDlg::TransLate( double oldX, double oldY, double oldZ,
							   double &newX, double &newY, double &newZ)
{
	CTransTool TransTool;

	double dX[10] = {2821335.355,
		2886004.956,
		2775692.14,
		2948511.313,
		2951824.635,
		2815528.447,
		2756094.445,
		2907804.872,
		2707046.301,
		2712758.269};
	double dY[10] = {625027.1208,
		731142.0929,
		503429.095,
		615525.5199,
		750926.5092,
		701732.3303,
		660798.9258,
		563355.9092,
		610950.7251,
		566582.894};
	double dZ[10] = {587.613,
		114.135,
		420.892,
		280.195,
		139.036,
		99.249,
		110.59,
		223.145,
		102.63,
		139.956};
	double dX1[10] = {2821278.379,
		2885949.178,
		2775634.127,
		2948455.832,
		2951769.739,
		2815471.702,
		2756036.823,
		2907748.684,
		2706987.899,
		2712699.76};
	double dY1[10] = {625097.8893,
		731213.8857,
		503498.5999,
		615595.6594,
		750998.2801,
		701804.0441,
		660870.3817,
		563425.5896,
		611021.7807,
		566653.4029};
	double dZ1[10] = {534.7121,
		61.6113,
		367.4465,
		226.4292,
		86.2654,
		46.9519,
		58.3849,
		169.2562,
		50.4038,
		87.3759};
	//先调用SetTransPara设置转换参数，再使用转换函数TransDot
	TransTool.SetTransPara(dX, dY, dZ, dX1, dY1, dZ1, 10);
	TransTool.TransDot(oldX, oldY, oldZ, newX, newY,newZ );
}


//输出路径
void CReadShapeDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	//CString outFileName=NULL;
	CFileDialog dlg2(FALSE, _T("*.shp"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("shp文件(*.shp)|*.shp;|所有文件 (*.*)|*.*||"), NULL); 
	dlg2.m_ofn.lpstrTitle = _T("导出shp文件");
	//CString outfilename; 
	std::vector<CString> vecPicPaths;
	if(dlg2.DoModal() == IDOK) 
	{ 
		POSITION fileNamesPosition = dlg2.GetStartPosition(); 
		while(fileNamesPosition != NULL) 
		{ 
			outfilename = dlg2.GetNextPathName(fileNamesPosition); //获取绝对路径
			vecPicPaths.push_back(outfilename);
			//outFileName=dlg2.GetFileName();//获取文件名及后缀名
		}   	
	}
	//CString CString strOutPath = _T("");
	////编辑框获取文件路径
	GetDlgItem(IDC_EDIT2)->SetWindowText(outfilename);

////////////////////////////将//////////////////////////////////////////////

 //   CString writeStr;
	//CString writeStr1;
	//FILE *_PFile = fopen(filePathName.GetBuffer(),"w"); 
	////writeStr.Format("%d\n", m_value[3].id);  
	//writeStr.Format(_T("%d\t"),m_value[0].y);
	//fwrite(writeStr, writeStr.GetLength(), 1, _PFile);   
	//fclose(_PFile);//关闭文件

/////////////////////////保存转换的shape文件数据////////////////////////////////////////////////
	//OGRRegisterAll();
	//const char *pszDriverName="ESRI Shapefile";
	//OGRSFDriver *poDriver;
	//poDriver=OGRSFDriverRegistrar::GetRegistrar()->GetDriverByName(pszDriverName);
	////if (poDriver==NULL)
	////{
	//	//cout<<pszDriverName<<" driver not available."<<endl;
	//	//exit(1);
	////}
	////"C:\\Users\\Rkc\\Desktop\\OutputData\\point_out1.shp"
	//OGRDataSource *poDS;
	//poDS=poDriver->CreateDataSource(filePathName,NULL);//获取输出路径
	//if (poDS==NULL)
	//{
	//	//cout<<"Creation of point_out.shp file failed."<<endl;
	//	MessageBox(_T("保存失败"),_T("提示"));
	//	exit(1);
	//}
	//OGRLayer *poLayer;

	//poLayer=poDS->CreateLayer("point_out",NULL,wkbPoint,NULL);
	//OGRFieldDefn firstField("faci_code",OFTInteger);
	//OGRFieldDefn secondField("X",OFTReal);
	//OGRFieldDefn thirdField("Y",OFTReal);
	//firstField.SetWidth(32);
	//secondField.SetWidth(32);
	//thirdField.SetWidth(32);
	//poLayer->CreateField(&firstField);
	//poLayer->CreateField(&secondField);
	//poLayer->CreateField(&thirdField);
	//double x,y;
	//int ID;
	//for(int i=0;i<m_value.size();i++)
	//{
	//	ID=i+1;
	//	x=m_TransValue[i].x;
	//	y=m_TransValue[i].y;
	//	OGRFeature *poFeature;
	//	poFeature=OGRFeature::CreateFeature(poLayer->GetLayerDefn());
	//	poFeature->SetField("faci_code",ID);
	//	poFeature->SetField("X",x);
	//	poFeature->SetField("Y",y);
	//	OGRPoint pt;
	//	pt.setX(x);
	//	pt.setY(y);
	//	poFeature->SetGeometry(&pt);
	//	OGRFeature::DestroyFeature(poFeature);
	//}
	//OGRDataSource::DestroyDataSource(poDS);
}


void CReadShapeDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
}

//显示坐标信息到列表中
void CReadShapeDlg::ViewShape( CString fileName )
{
	m_value.clear();
	//打开shape文件（绝对路径）
	OGRRegisterAll();
	OGRDataSource       *poDS = NULL;
	poDS = OGRSFDriverRegistrar::Open(fileName, FALSE );

	//if( poDS == NULL )
	//{
	//	MessageBox( _T("打开文件失败！"),_T("提示") );
	//	exit(1);
	//}

	//MessageBox(_T("打开源文件成功！"),_T("提示"));

	//统计图层数目
	int lyrCount=0;
	lyrCount=poDS->GetLayerCount();

	//获得总的地物个数，即总行数
	OGRLayer  *TmppoLayer;
	for (int i=0;i<lyrCount;i++)
	{
		TmppoLayer=poDS->GetLayer(i);
		unsigned int _fea_count=TmppoLayer->GetFeatureCount();
		m_all_fea_count+=_fea_count;  //总要素个数
	}

	OGRLayer  *poLayer;

	//遍历shape文件
	for (int i=0;i<lyrCount;i++)
	{
		poLayer=poDS->GetLayer(i);
		OGRwkbGeometryType type=poLayer->GetLayerDefn()->GetGeomType();
		//统计字段
		OGRFeatureDefn * poFeaDef=poLayer->GetLayerDefn();
		int _field_count= poFeaDef->GetFieldCount();  //获得每行字段总数 不包含前两个字段（FID、shaape类型）

		OGRFeature *poFeature;
		//统计行的总数
		unsigned int _this_fea_count=poLayer->GetFeatureCount();

		//LOGSTR("=====================================================================");
		//char *geo_lyr_name=(char*)malloc(200);		
		////strcpy(geo_lyr_name,szlyrname);		

		//free(geo_lyr_name);

		poLayer->ResetReading();
		ShapeData data;
		//遍历每行的所有字段	   行的总数
		for (unsigned long  i=0;i<_this_fea_count;i++)
		{	
			m_fea_done++;  //已处理的feature
				       //图层
			poFeature = poLayer->GetNextFeature();
			if (poFeature ==NULL)
			{
				m_fea_null_count++;  //空要素个数
				continue;
			}

			int fea_FID=poFeature->GetFID();
			OGRGeometry *poGeometry=NULL;
			OGRLineString *poLine=NULL;
			OGRPoint *poPoint=NULL;
			OGRMultiPoint *poMultiPoint=NULL;
			OGRMultiLineString *poMultiLineString=NULL;
			OGRPolygon *poPolygon=NULL;
			OGRMultiPolygon *poMultiPolygon=NULL; 

			poGeometry = poFeature->GetGeometryRef();
			OGRwkbGeometryType type=poGeometry->getGeometryType();
			//type=poGeometry->getGeometryType();

			int _pt_count=0;
			int _ex_count;
			OGRLinearRing* _ex_ring=NULL;
			int _in_ring_count=0;
			int _geo_count=0;

			int       id;
			double _oldX;
			double _oldY;

			CString List_id;
			CString List_x;
			CString List_y;

			//m_geo_done++;
			//判别shape 
			switch (type)
			{
				//点
			case wkbPoint:
			case wkbPoint25D:
				//m_geo_point_count++;    //点类型个数

				poPoint=(OGRPoint*)poGeometry;
				data.id=poFeature->GetFID();
				data.x=poPoint->getX();
				data.y=poPoint->getY();

				break;
				//线
			case wkbLineString:
			case wkbLineString25D:
				//m_geo_line_count++;     //线类型个数
								
				poLine=(OGRLineString *) poGeometry;
				_pt_count=poLine->getNumPoints();

				for (int i=0;i<_pt_count;i++)
				{
					data.id=poFeature->GetFID();
					data.x=poLine->getX(i);
					data.y=poLine->getY(i);
				}

				break;
				//点集合
			case wkbMultiPoint:
			case wkbMultiPoint25D:
				//m_geo_multi_point_count++;    //多点类型个数

				poMultiPoint=(OGRMultiPoint *)poGeometry;
				poMultiPoint->getNumGeometries();
				_pt_count=poMultiPoint->getNumGeometries();

				for (int i=0;i<_pt_count;i++)
				{
					data.id=poFeature->GetFID();
					data.x=((OGRPoint*)poMultiPoint->getGeometryRef(i))->getX();
					data.y=((OGRPoint*)poMultiPoint->getGeometryRef(i))->getY();
				}
				break;
				//线集合
			case wkbMultiLineString:
			case wkbMultiLineString25D:
				//m_geo_multi_line_count++;     //多线类型个数
				poMultiLineString=(OGRMultiLineString *)poGeometry;
				_geo_count= poMultiLineString->getNumGeometries();

				for (int i=0;i<_geo_count;i++)
				{
					OGRLineString* poLineString=(OGRLineString*)poMultiLineString->getGeometryRef(i);
					_pt_count=poLineString->getNumPoints();
					for (int j=0;j<_pt_count;j++)
					{
					    data.id=poFeature->GetFID();
						data.x=poLineString->getX(j);
						data.y=poLineString->getY(j);
					}
				}
				break;
				//面
			case wkbPolygon:
			case wkbPolygon25D:
				//m_geo_polygon_count++;     //面类型个数
				poPolygon=(OGRPolygon *)poGeometry;

				_in_ring_count=poPolygon->getNumInteriorRings();

				for (int i=0;i<_in_ring_count;i++)
				{
					OGRLinearRing* ring=poPolygon->getInteriorRing(i);
					int _ring_count=ring->getNumPoints();
					for (int j=0;j<_ring_count;j++)
					{
						data.id=poFeature->GetFID();
						data.x=ring->getX(j);
						data.y=ring->getY(j);
					}
				}

				_ex_ring=poPolygon->getExteriorRing();
				_ex_count=_ex_ring->getNumPoints();
				for (int i=0;i<_ex_count;i++)
				{
					data.id=poFeature->GetFID();
					data.x=_ex_ring->getX(i);
					data.y=_ex_ring->getY(i);
					//int fea_FID=poFeature->GetFID();
				}
				break;
				//面集合
			case wkbMultiPolygon:
			case wkbMultiPolygon25D:
				//m_geo_multi_polygon_count++;    //多面类型个数

				poMultiPolygon=(OGRMultiPolygon *)poGeometry;
				_geo_count=poMultiPolygon->getNumGeometries();

				for (int i=0;i<_geo_count;i++)
				{
					OGRPolygon* poPolygon=(OGRPolygon*)poMultiPolygon->getGeometryRef(i);
					if (NULL == poPolygon)
					{
						continue;
					}
					//内环
					_in_ring_count=poPolygon->getNumInteriorRings();

					for (int i=0;i<_in_ring_count;i++)
					{
						OGRLinearRing* ring=poPolygon->getInteriorRing(i);
						int _ring_count=ring->getNumPoints();
						for (int j=0;j<_ring_count;j++)
						{
							//data.id=poFeature->GetFieldAsInteger( 0 );
							data.id=poFeature->GetFID();
							data.x=ring->getX(j);
							data.y=ring->getY(j);
							//int fea_FID=poFeature->GetFID();
						}
					}

					//外环
					_ex_ring=poPolygon->getExteriorRing();
					_ex_count=_ex_ring->getNumPoints();
					for (int i=0;i<_ex_count;i++)
					{
						data.id=poFeature->GetFID();
						data.x=_ex_ring->getX(i);
						data.y=_ex_ring->getY(i);
						//int fea_FID=poFeature->GetFID();
					}
				}
				break;
			default:
				//m_error_count++;
				break;
			}
			m_fea_create_count++;
			OGRFeature::DestroyFeature( poFeature );
		m_value.push_back(data);
		}//for each feature	
	}
}