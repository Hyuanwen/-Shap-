// ReadShapeDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ReadShape.h"
#include "ReadShapeDlg.h"
#include <string>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif
using namespace std;

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CReadShapeDlg �Ի���




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


// CReadShapeDlg ��Ϣ�������

BOOL CReadShapeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	m_ShapeList.SetExtendedStyle(m_ShapeList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);   
	DWORD dwStyle = m_ShapeList.GetExtendedStyle();   
	m_ShapeList.InsertColumn(0,_T("ID"),LVCFMT_CENTER,50,0);
	m_ShapeList.InsertColumn(1,_T("X����"),LVCFMT_CENTER,100,0);
	m_ShapeList.InsertColumn(2,_T("Y����"),LVCFMT_CENTER,100,0);

	m_TranShapeList.SetExtendedStyle(m_TranShapeList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);   
	DWORD dwStyle2 = m_TranShapeList.GetExtendedStyle();   
	m_TranShapeList.InsertColumn(0,_T("ID"),LVCFMT_CENTER,50,0);
	m_TranShapeList.InsertColumn(1,_T("X����"),LVCFMT_CENTER,100,0);
	m_TranShapeList.InsertColumn(2,_T("Y����"),LVCFMT_CENTER,100,0);


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CReadShapeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CReadShapeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CReadShapeDlg::OnBnClickedSelect()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileDialog dlg(TRUE, _T("*.shp"), NULL, OFN_ALLOWMULTISELECT|OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, _T("shp�ļ�(*.shp)|*.shp;|�����ļ� (*.*)|*.*||"), NULL); 
	dlg.m_ofn.lpstrTitle = _T("ѡ��shp�ļ�");
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
	//�༭���ȡ�ļ�·��
	GetDlgItem(IDC_EDIT1)->SetWindowText(infilename);

	////"C:\Users\Rkc\Desktop\point\point.shp"
	// CString outFileName;
	// outFileName=dlg.GetFileTitle();
	//readShape(infilename,outFilePath);

}
//����б�����
void CReadShapeDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_ShapeList.DeleteAllItems();
	m_TranShapeList.DeleteAllItems();
	m_value.clear();
}
//ִ��ת��
void CReadShapeDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//����ת��
	readShape(infilename,outfilename);

	ViewShape(infilename);
	//��������ʾ���б���
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
	//��������ʾ���б���
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


//����shape�ļ�
void CReadShapeDlg::readShape( CString inFileName,CString outFileName)
{
	//��shape�ļ�������·����
	OGRRegisterAll();
	OGRDataSource       *poDS = NULL;
	poDS = OGRSFDriverRegistrar::Open(inFileName, FALSE );

	if( poDS == NULL )
	{
		MessageBox( _T("ת���ļ�ʧ�ܣ�"),_T("��ʾ") );
		exit(1);
	}

	MessageBox(_T("ת���ļ��ɹ���"),_T("��ʾ"));

	//����Ŀ������Դ
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
	//������ھ�ɾ����

	//std::fstream _file;		
	//CString filenameout="C:\\Users\\Rkc\\Desktop\\OutputData\\OutputData.shp";
	//_bstr_t bstr_filename = filenameout;
	//char* strFileName = (LPSTR)bstr_filename;

	//BOOL ret= DeleteFileA(strFileName);			
	//�����յ����ͼ��
	poDSOut = poDriverOut->CreateDataSource(outFileName, NULL );
	if( poDSOut == NULL )
	{
		exit(1);
	}
	
	//layer to feature
	int lyrCount=0;
	lyrCount=poDS->GetLayerCount();//����shape�ļ�ͼ������

	//�������ͼ��
	OGRLayer  *TmppoLayer;
	//��������ܵ����������������
	for (int i=0;i<lyrCount;i++)
	{
		TmppoLayer=poDS->GetLayer(i);//���shape�ļ���ȡ�����ļ�ͼ��(�յ�)
		unsigned int _fea_count=TmppoLayer->GetFeatureCount();
		m_all_fea_count+=_fea_count;
	}

    //����shape�ļ�
	OGRLayer  *poLayer;
	for (int i=0;i<lyrCount;i++)
	{
		poLayer=poDS->GetLayer(i);

		//���ͼ�㷶Χ
		//virtual OGRErr GetExtent(OGREnvelope *psExtent, int bForce = TRUE);
		//���ͼ������xyz
		OGREnvelope extent;
		poLayer->GetExtent(&extent);


		OGRLayer *poLayerOut;
		OGRFeatureDefn * poFeaDef=poLayer->GetLayerDefn();
		//��ȡͼ������
		CString szlyrname=poFeaDef->GetName();
		CString res_lyrname;
		res_lyrname=szlyrname;	
		//��ȡ��������
		OGRwkbGeometryType type=poLayer->GetLayerDefn()->GetGeomType();

		//�������shapeͼ��		
		poLayerOut=poDSOut->CreateLayer(res_lyrname,NULL,type);
		if(poLayerOut==NULL)
		{
			//LOGSTR(":����Ŀ���ļ�ʧ��");
			MessageBox(_T("����Ŀ���ļ�ʧ��"),_T("��ʾ"));
			continue;
		}

		//����shape���ͼ���ֶ�
		int _field_count= poFeaDef->GetFieldCount();  //���ÿ���ֶ����� ������ǰ�����ֶΣ�FID��shaape���ͣ�
		for (int i=0;i<_field_count;i++)
		{
			OGRFieldDefn *poField=poFeaDef->GetFieldDefn(i);
			//����shape���ͼ���ֶ�
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

		//����ÿ�е������ֶ�
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
			OGRGeometry *poGeometry=NULL;//�������˹�ϵ

			OGRLineString *poLine=NULL;
			OGRPoint *poPoint=NULL;
			OGRMultiPoint *poMultiPoint=NULL;
			OGRMultiLineString *poMultiLineString=NULL;
			OGRPolygon *poPolygon=NULL;
			OGRMultiPolygon *poMultiPolygon=NULL; 

			poGeometry = poFeature->GetGeometryRef();//��ȡ�������˹�ϵ
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

			OGRwkbGeometryType type=poGeometry->getGeometryType();//��ȡ��������

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
			//�б�shape 
			switch (type)
			{
				//��
			case wkbPoint:
			case wkbPoint25D:
				m_geo_point_count++;

				poPoint=(OGRPoint*)poGeometry;

				_oldX=poPoint->getX();//���Ȼ򶫷���
				_oldY=poPoint->getY();//γ�Ȼ򱱷���
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
				//��
			case wkbLineString:
			case wkbLineString25D:
				m_geo_line_count++;
								
				poLine=(OGRLineString *) poGeometry;
				_pt_count=poLine->getNumPoints();

				for (int i=0;i<_pt_count;i++)
				{
					_oldX=poLine->getX(i);//���Ȼ򶫷���
					_oldY=poLine->getY(i);//γ�Ȼ򱱷���
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
				//�㼯��
			case wkbMultiPoint:
			case wkbMultiPoint25D:
				m_geo_multi_point_count++;

				poMultiPoint=(OGRMultiPoint *)poGeometry;
				poMultiPoint->getNumGeometries();
				_pt_count=poMultiPoint->getNumGeometries();

				for (int i=0;i<_pt_count;i++)
				{
					_oldX=((OGRPoint*)poMultiPoint->getGeometryRef(i))->getX();//���Ȼ򶫷���
					_oldY=((OGRPoint*)poMultiPoint->getGeometryRef(i))->getY();//γ�Ȼ򱱷���
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
				//�߼���
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
						_oldX=poLineString->getX(j);//���Ȼ򶫷���
						_oldY=poLineString->getY(j);//γ�Ȼ򱱷���
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
				//��
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
						_oldX= ring->getX(j);//���Ȼ򶫷���
						_oldY= ring->getY(j);//γ�Ȼ򱱷���
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
					_oldX= _ex_ring->getX(i);//���Ȼ򶫷���
					_oldY= _ex_ring->getY(i);//γ�Ȼ򱱷���
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
				//�漯��
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

					//�ڻ�
					_in_ring_count=poPolygon->getNumInteriorRings();

					for (int i=0;i<_in_ring_count;i++)
					{
						OGRLinearRing* ring=poPolygon->getInteriorRing(i);
						int _ring_count=ring->getNumPoints();
						for (int j=0;j<_ring_count;j++)
						{
							_oldX= ring->getX(j);//���Ȼ򶫷���
							_oldX= ring->getY(j);//γ�Ȼ򱱷���
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

					//�⻷
					_ex_ring=poPolygon->getExteriorRing();
					_ex_count=_ex_ring->getNumPoints();
					for (int i=0;i<_ex_count;i++)
					{
						_oldX= _ex_ring->getX(i);//���Ȼ򶫷���
						_oldY= _ex_ring->getY(i);//γ�Ȼ򱱷���
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
				//�������
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


//ת������
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
	//�ȵ���SetTransPara����ת����������ʹ��ת������TransDot
	TransTool.SetTransPara(dX, dY, dZ, dX1, dY1, dZ1, 10);
	TransTool.TransDot(oldX, oldY, oldZ, newX, newY,newZ );
}


//���·��
void CReadShapeDlg::OnBnClickedButton5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CString outFileName=NULL;
	CFileDialog dlg2(FALSE, _T("*.shp"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("shp�ļ�(*.shp)|*.shp;|�����ļ� (*.*)|*.*||"), NULL); 
	dlg2.m_ofn.lpstrTitle = _T("����shp�ļ�");
	//CString outfilename; 
	std::vector<CString> vecPicPaths;
	if(dlg2.DoModal() == IDOK) 
	{ 
		POSITION fileNamesPosition = dlg2.GetStartPosition(); 
		while(fileNamesPosition != NULL) 
		{ 
			outfilename = dlg2.GetNextPathName(fileNamesPosition); //��ȡ����·��
			vecPicPaths.push_back(outfilename);
			//outFileName=dlg2.GetFileName();//��ȡ�ļ�������׺��
		}   	
	}
	//CString CString strOutPath = _T("");
	////�༭���ȡ�ļ�·��
	GetDlgItem(IDC_EDIT2)->SetWindowText(outfilename);

////////////////////////////��//////////////////////////////////////////////

 //   CString writeStr;
	//CString writeStr1;
	//FILE *_PFile = fopen(filePathName.GetBuffer(),"w"); 
	////writeStr.Format("%d\n", m_value[3].id);  
	//writeStr.Format(_T("%d\t"),m_value[0].y);
	//fwrite(writeStr, writeStr.GetLength(), 1, _PFile);   
	//fclose(_PFile);//�ر��ļ�

/////////////////////////����ת����shape�ļ�����////////////////////////////////////////////////
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
	//poDS=poDriver->CreateDataSource(filePathName,NULL);//��ȡ���·��
	//if (poDS==NULL)
	//{
	//	//cout<<"Creation of point_out.shp file failed."<<endl;
	//	MessageBox(_T("����ʧ��"),_T("��ʾ"));
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

//��ʾ������Ϣ���б���
void CReadShapeDlg::ViewShape( CString fileName )
{
	m_value.clear();
	//��shape�ļ�������·����
	OGRRegisterAll();
	OGRDataSource       *poDS = NULL;
	poDS = OGRSFDriverRegistrar::Open(fileName, FALSE );

	//if( poDS == NULL )
	//{
	//	MessageBox( _T("���ļ�ʧ�ܣ�"),_T("��ʾ") );
	//	exit(1);
	//}

	//MessageBox(_T("��Դ�ļ��ɹ���"),_T("��ʾ"));

	//ͳ��ͼ����Ŀ
	int lyrCount=0;
	lyrCount=poDS->GetLayerCount();

	//����ܵĵ����������������
	OGRLayer  *TmppoLayer;
	for (int i=0;i<lyrCount;i++)
	{
		TmppoLayer=poDS->GetLayer(i);
		unsigned int _fea_count=TmppoLayer->GetFeatureCount();
		m_all_fea_count+=_fea_count;  //��Ҫ�ظ���
	}

	OGRLayer  *poLayer;

	//����shape�ļ�
	for (int i=0;i<lyrCount;i++)
	{
		poLayer=poDS->GetLayer(i);
		OGRwkbGeometryType type=poLayer->GetLayerDefn()->GetGeomType();
		//ͳ���ֶ�
		OGRFeatureDefn * poFeaDef=poLayer->GetLayerDefn();
		int _field_count= poFeaDef->GetFieldCount();  //���ÿ���ֶ����� ������ǰ�����ֶΣ�FID��shaape���ͣ�

		OGRFeature *poFeature;
		//ͳ���е�����
		unsigned int _this_fea_count=poLayer->GetFeatureCount();

		//LOGSTR("=====================================================================");
		//char *geo_lyr_name=(char*)malloc(200);		
		////strcpy(geo_lyr_name,szlyrname);		

		//free(geo_lyr_name);

		poLayer->ResetReading();
		ShapeData data;
		//����ÿ�е������ֶ�	   �е�����
		for (unsigned long  i=0;i<_this_fea_count;i++)
		{	
			m_fea_done++;  //�Ѵ����feature
				       //ͼ��
			poFeature = poLayer->GetNextFeature();
			if (poFeature ==NULL)
			{
				m_fea_null_count++;  //��Ҫ�ظ���
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
			//�б�shape 
			switch (type)
			{
				//��
			case wkbPoint:
			case wkbPoint25D:
				//m_geo_point_count++;    //�����͸���

				poPoint=(OGRPoint*)poGeometry;
				data.id=poFeature->GetFID();
				data.x=poPoint->getX();
				data.y=poPoint->getY();

				break;
				//��
			case wkbLineString:
			case wkbLineString25D:
				//m_geo_line_count++;     //�����͸���
								
				poLine=(OGRLineString *) poGeometry;
				_pt_count=poLine->getNumPoints();

				for (int i=0;i<_pt_count;i++)
				{
					data.id=poFeature->GetFID();
					data.x=poLine->getX(i);
					data.y=poLine->getY(i);
				}

				break;
				//�㼯��
			case wkbMultiPoint:
			case wkbMultiPoint25D:
				//m_geo_multi_point_count++;    //������͸���

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
				//�߼���
			case wkbMultiLineString:
			case wkbMultiLineString25D:
				//m_geo_multi_line_count++;     //�������͸���
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
				//��
			case wkbPolygon:
			case wkbPolygon25D:
				//m_geo_polygon_count++;     //�����͸���
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
				//�漯��
			case wkbMultiPolygon:
			case wkbMultiPolygon25D:
				//m_geo_multi_polygon_count++;    //�������͸���

				poMultiPolygon=(OGRMultiPolygon *)poGeometry;
				_geo_count=poMultiPolygon->getNumGeometries();

				for (int i=0;i<_geo_count;i++)
				{
					OGRPolygon* poPolygon=(OGRPolygon*)poMultiPolygon->getGeometryRef(i);
					if (NULL == poPolygon)
					{
						continue;
					}
					//�ڻ�
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

					//�⻷
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