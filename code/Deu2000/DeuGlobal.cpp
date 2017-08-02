// Deu2000.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "DeuGlobal.h"
#include "DeuSQLProvider.h"

#ifdef _DEBUG
	#define new DEBUG_NEW
#endif

#include "DeuGlobalMainFrm.h"
#include "DeuViewerFrm.h"
#include "DeuViewerDoc.h"
#include "DeuViewView.h"
#include "DeuVectorView.h"
#include "DeuVectorFrame.h"
#include "DeuVectorDoc.h"
#include "DeuRasterView.h"
#include "DeuRasterFrame.h"
#include "DeuRasterDoc.h"
#include "DeuProjectView.h"
#include "DeuProjectFrame.h"
#include "DeuProjectDoc.h"
#include "DeuVectorProjectView.h"
#include "DeuVectorProjectFrame.h"
#include "DeuVectorProjectDoc.h"
#include "DeuDlgLogin.h"
#include "DEUCheck.h" //add by chenyong 2013-01-24

// CDeuGlobalApp
BEGIN_MESSAGE_MAP(CDeuGlobalApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CDeuGlobalApp::OnAppAbout)
	// 基于文件的标准文档命令
	ON_COMMAND(ID_VIEW, OnNewView)
	ON_COMMAND(ID_VECTOR, OnNewVector)
	ON_COMMAND(ID_RASTER, OnNewRaster)	
	ON_COMMAND(ID_VECTORPROJECT, OnNewVectorProject)
	ON_COMMAND(ID_RASTERPROJECT, OnNewProject)	
	ON_COMMAND(ID_GRIDSET, OnGridSet)
	ON_COMMAND(ID_FORMAT, OnFormatSet)
	// 标准打印设置命令
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinApp::OnFilePrintSetup)
	ON_COMMAND(ID_CONTEXT_HELP, &CDeuGlobalApp::OnContextHelp)
	ON_COMMAND(ID_FL_ADD, &CDeuGlobalApp::OnFlAdd)
END_MESSAGE_MAP()

// CDeuGlobalApp 构造
CDeuGlobalApp::CDeuGlobalApp()
{ 
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}

// 唯一的一个 CDeu2000App 对象
CDeuGlobalApp   theApp;
CDeuTaskProcess TaskProc;

//坐标系数据
_GeoDataXml    GeoDataMapping;
_GeoDataXml    CustDataMapping;
_StrFormatList GobalFormat;

//任务数据
_Tasks TasksMapping;
USERPOWER GobalUserInfo;

char p_cUserName[50];

static const CLSID clsid =
{ 0x7559fd90, 0x9b93, 0x11ce, { 0xb0, 0xf0, 0x0, 0xaa, 0x0, 0x6c, 0x28, 0xb3 } };

// CDeuGlobalApp 初始化
BOOL CDeuGlobalApp::InitInstance()
{
	//有狗版本和无狗版本的开关设置 begin
	//add by chenyong 2013-01-24 换成key加密
	#if defined(DEULIC) 
		#ifdef NDEBUG
			DEUCheck dc(98);
		#endif
	#endif

	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	//alter by chenyong 2015-3-14
	/*::AoInitialize(NULL);
	CArcGisAuthorization m_ArcGisAuthorization;
	m_ArcGisAuthorization.Init();
	m_ArcGisAuthorization.ArcGisLiscense();*/

	//add by chenyong 2015-3-17如果未安装ArcEngine Runtime时，程序启动时会崩溃
	#ifdef ARCSDE
		try
		{
			::AoInitialize(NULL);
		
			CArcGisAuthorization m_ArcGisAuthorization;
			m_ArcGisAuthorization.Init();
			m_ArcGisAuthorization.ArcGisLiscense();
		}
		catch(...)
		{
			//AfxMessageBox("ArcEngine Runtime检查失败!请检查ArcEngine Runtime是否已经正确安装");
		}
	#endif

	// 初始化 OLE 库
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();

	// 加载标准 INI 文件选项(包括 MRU)
	LoadStdProfileSettings(4);  

	m_BackDlg.Create(IDD_DLG_BACKGROUND, NULL);
	//加载标题
	char sz_tip[MAX_PATH];
	LoadString(AfxGetInstanceHandle(),IDR_MAINFRAME, sz_tip, sizeof(sz_tip));
	m_BackDlg.SetWindowText(sz_tip);
	m_BackDlg.SetWindowPos(&CWnd::wndTop, 0, 0, 421, 343, SWP_SHOWWINDOW);
	m_BackDlg.CenterWindow();
	
	LoadMapping();
	LoadFormatXml();

	//加载任务记录
	CDeuXmlReader m_XmlReader;
	m_XmlReader.LoadXml("Run.tmp");
	m_XmlReader.MappingTasks(&TasksMapping);
	m_XmlReader.Free();

	//登录
	CDeuDlgLogin m_dlg_login;
	if(m_dlg_login.DoModal() == IDCANCEL)
	{ 
		return FALSE;
	}

	m_BackDlg.DestroyWindow();
	
	//创建视图文档框架
	CMultiDocTemplate* pViewDocTemplate = new CMultiDocTemplate(
		IDR_DEU2000MENU,
		RUNTIME_CLASS(CDeuViewerDoc),
		RUNTIME_CLASS(CDeuViewerFrame),		//创建视图子框架
		RUNTIME_CLASS(CDeuViewView));
	if (!pViewDocTemplate)
	{
		return FALSE;
	}
	AddDocTemplate(pViewDocTemplate);

	//创建矢量文档框架
	CMultiDocTemplate* pVectorDocTemplate = new CMultiDocTemplate(
		IDR_VECTORDOC,
		RUNTIME_CLASS(CDeuVectorDoc),
		RUNTIME_CLASS(CDeuVectorFrame),		 //创建矢量子框架
		RUNTIME_CLASS(CDeuVectorView));
	if (!pVectorDocTemplate)
	{
		return FALSE;
	}
	AddDocTemplate(pVectorDocTemplate);

	//创建栅格文档框架
	CMultiDocTemplate* pRasterDocTemplate = new CMultiDocTemplate(
		IDR_RASTERDOC,
		RUNTIME_CLASS(CDeuRasterDoc),
		RUNTIME_CLASS(CDeuRasterFrame),		  //创建栅格子框架
		RUNTIME_CLASS(CDeuRasterView));
	if (!pRasterDocTemplate)
		return FALSE;
	AddDocTemplate(pRasterDocTemplate);

	//创建矢量投影文档框架
	CMultiDocTemplate* pVectorProjectDocTemplate = new CMultiDocTemplate(
		IDR_VECTORPROJECTDOC,
		RUNTIME_CLASS(CDeuVectorProjectDoc),
		RUNTIME_CLASS(CDeuVectorProjectFrame), //创建栅格子框架
		RUNTIME_CLASS(CDeuVectorProjectView));
	if (!pVectorProjectDocTemplate)
		return FALSE;
	AddDocTemplate(pVectorProjectDocTemplate);

	//创建栅格投影文档框架
	CMultiDocTemplate* pProjectDocTemplate = new CMultiDocTemplate(
		IDR_PROJECTDOC,
		RUNTIME_CLASS(CDeuProjectDoc),
		RUNTIME_CLASS(CDeuProjectFrame),	   //创建栅格子框架
		RUNTIME_CLASS(CDeuProjectView));
	if (!pProjectDocTemplate)
	{
		return FALSE;
	}
	AddDocTemplate(pProjectDocTemplate);

	// 创建主 MDI 框架窗口
	CDeuGlobalMainFrame* pMainFrame = new CDeuGlobalMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;

	// 分析标准外壳命令、DDE、打开文件操作的命令行
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// 调度在命令行中指定的命令。如果
	// 用 /RegServer、/Register、/Unregserver 或 /Unregister 启动应用程序，则返回 FALSE。
	if (!ProcessShellCommand(cmdInfo))
	{
		return FALSE;
	}

	// 主窗口已初始化，因此显示它并对其进行更新
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
class CAboutDlg : public CXTPDialog
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

CAboutDlg::CAboutDlg() : CXTPDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CXTPDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CXTPDialog)
END_MESSAGE_MAP()

// 用于运行对话框的应用程序命令
void CDeuGlobalApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CDeuGlobalApp 消息处理程序
/*=============================================
			功能: 创建视图
=============================================*/
void CDeuGlobalApp::OnNewView()
{
	if((!GobalUserInfo.IsVectorView) && (!GobalUserInfo.IsRasterView))
	{
		MessageBox(AfxGetMainWnd()->m_hWnd, PowerError, "系统提示", MB_OK|MB_ICONEXCLAMATION);
	}
	else
	{
		CString m_str;
		if(GobalUserInfo.IsVectorView && !GobalUserInfo.IsRasterView)
		{
			m_str = "Shapefile(*.shp)|*.shp|位图(*.bmp)|*.bmp|JPEG(*.jpg)|*.jpg|MapInfo(*.mif)|*.mif|MapInfo(*.tab)|*.tab|DXF(*.dxf)|*.dxf|AVCE00(*.e00)|*.e00|Excel(*.xlsx)|*.xlsx||";
		}
		else if(GobalUserInfo.IsRasterView && !GobalUserInfo.IsVectorView)
		{
			m_str = "Gtiff(*.tif)|*.tif|HFA(*.img)|*.img|EHdr(*.bil)|*.bil|AAIGrid(*.asc)|*.asc|BMP(*.bmp)|.bmp||";			
		}
		else
		{
			m_str = "Shapefile(*.shp)|*.shp|位图(*.bmp)|*.bmp|JPEG(*.jpg)|*.jpg|MapInfo(*.mif)|*.mif|MapInfo(*.tab)|*.tab|DXF(*.dxf)|*.dxf|AVCE00(*.e00)|*.e00|Gtiff(*.tif)|*.tif|HFA(*.img)|*.img|EHdr(*.bil)|*.bil|AAIGrid(*.asc)|*.asc|BMP(*.bmp)|.bmp||";
		}

		CFileDialog m_FileDlg(true,"Shapefile", "*.shp",OFN_FILEMUSTEXIST|OFN_HIDEREADONLY, m_str, NULL);
		m_FileDlg.m_ofn.lpstrTitle = _T("打开视图文件");
		if(m_FileDlg.DoModal() == IDOK)
		{		
			POSITION docpos = this->GetFirstDocTemplatePosition();
			if(docpos != NULL)
			{
				CDocTemplate *pdoc = this->GetNextDocTemplate(docpos);
				CString str_name;
				pdoc->GetDocString(str_name, CDocTemplate::docName);
				if(str_name == _T("视 图"))
				{
					CDocument* p_pdoc= pdoc->OpenDocumentFile(NULL);
					POSITION viewpos = p_pdoc->GetFirstViewPosition();
					if(viewpos != NULL)
					{
						CDeuViewView* p_view = (CDeuViewView*)p_pdoc->GetNextView(viewpos);
						p_view->OnZoomLoad(m_FileDlg.GetPathName());
					}
					return;
				}
			}
		}
	}
}

/*=============================================   
			功能: 创建矢量投影
=============================================*/
void CDeuGlobalApp::OnNewVectorProject()
{
	POSITION pos = this->GetFirstDocTemplatePosition();
	while(pos != NULL)
	{
		CDocTemplate *pDoc = GetNextDocTemplate(pos);
		CString strname;
		pDoc->GetDocString(strname, CDocTemplate::docName);
		if(strname == _T("矢量投影"))
		{
			pDoc->OpenDocumentFile(NULL);
		}
	}
}

/*=============================================   
			功能: 创建栅格投影
=============================================*/
void CDeuGlobalApp::OnNewProject()
{
	POSITION pos = this->GetFirstDocTemplatePosition();
	while(pos != NULL)
	{
		CDocTemplate *pDoc = GetNextDocTemplate(pos);
		CString strname;
		pDoc->GetDocString(strname, CDocTemplate::docName);
		if(strname == _T("栅格投影"))
		{
			pDoc->OpenDocumentFile(NULL);
		}
	}
}

/*=============================================   
			功能: 创建栅格转换
=============================================*/
void CDeuGlobalApp::OnNewRaster()
{
	POSITION pos = this->GetFirstDocTemplatePosition();
	while(pos != NULL)
	{
		CDocTemplate *pDoc = GetNextDocTemplate(pos);
		CString strname;
		pDoc->GetDocString(strname, CDocTemplate::docName);
		if(strname == _T("栅格转换"))
		{
			pDoc->OpenDocumentFile(NULL);
		}
	}
}

/*=============================================   
			功能: 创建矢量转换
=============================================*/
void CDeuGlobalApp::OnNewVector()
{	
	POSITION pos = this->GetFirstDocTemplatePosition();
	while(pos != NULL)
	{
		CDocTemplate *pdoc = this->GetNextDocTemplate(pos);
		CString strname;
		pdoc->GetDocString(strname, CDocTemplate::docName);
		if(strname == _T("矢量转换"))
		{
			pdoc->OpenDocumentFile(NULL);
		}
	}	
}

/*=============================================   
			功能: 创建格网设置
=============================================*/
#include "DeuDlgFiles.h"
void CDeuGlobalApp::OnGridSet()
{
	//CDeuDlgGridSetting dlg ;
	//CDeuDlgDataSrc dlg;
	//CDeuDlgFiles dlg;

	m_GridSettingDlg.DoModal();
}

//常用文件格式设置
void CDeuGlobalApp::OnFormatSet()
{
	CFileFormatSet							FormatSet;
	FormatSet.DoModal();
}

int CDeuGlobalApp::ExitInstance()
{
	// TODO: 在此添加专用代码和/或调用基类
	//::CoUninitialize();
	Release_GeoXml(&GeoDataMapping);
	ReleaseFormatXml(GobalFormat);

	//释放任务指针
	int n;
	for(n=0; n<TasksMapping._task.GetCount(); n++)
	{
		TasksMapping._task.GetAt(n)->_parts.m_Part.RemoveAll();
		delete TasksMapping._task.GetAt(n);
		TasksMapping._task.RemoveAt(n);
	}	
	TasksMapping._task.RemoveAll();

	//m_ArcGisAuthorization.Shutdown();
	::CoUninitialize();

	return CWinApp::ExitInstance();
}

void CDeuGlobalApp::OnContextHelp()
{
	//1.获取运行程序的路径
	CString			strPath = _T("");
	int				nPos(0);

	::GetModuleFileName(NULL/*AfxGetApp()->m_hInstance*/, strPath.GetBufferSetLength(MAX_PATH+1), MAX_PATH);
	strPath.ReleaseBuffer();
	nPos = strPath.ReverseFind('\\');
	strPath = strPath.Left(nPos);

	//2.调用系统接口，打开帮助文档
	HINSTANCE hIn = ::ShellExecute(NULL, "open", "操作与使用手册.chm", NULL, strPath.GetBuffer(MAX_PATH), SW_SHOWNORMAL);
	if (hIn == NULL)
	{
		::MessageBox(NULL, _T("打开帮助文档失败!"), _T("提示信息"), MB_OK);
	}

	strPath.ReleaseBuffer();

	return;
}

void CDeuGlobalApp::OnFlAdd()
{
	m_FLGrid.DoModal();
}
/*
=============================================   
功能:	登陆用户权限数据加载
日期:	2010-11-9
=============================================
*/
void LoadPowerInfo(PUSERPOWER pUserInfo)
{
	CString m_strGroupId;
	CDeuSQLite3Query m_query;
	CDeuSQLProvider m_SqlProvider;
	m_SqlProvider.FromUserGetGroupId(pUserInfo->strName.GetBuffer(), &m_strGroupId);

	if(m_strGroupId.Find(",", 0) == -1)
	{
		m_query = m_SqlProvider.GetUserGroup("'"+m_strGroupId+"'");
	}
	else
	{
		CString m_strTmp, _m_strTmp;
		int _index = 0;
		int  _start = 0;
		while(_index != -1)
		{
			_index = m_strGroupId.Find(",",_index);
			if(_index != -1)
			{
				_m_strTmp = m_strGroupId.Mid(_start, _index-_start);
				_start = _index+1;
				_index++;
			}
			else
			{
				_m_strTmp = m_strGroupId.Mid(_start);
			}

			m_strTmp  += "'"+_m_strTmp+"',";
		}
		m_strTmp.TrimRight(",");
		m_query = m_SqlProvider.GetUserGroup(m_strTmp);
	}

	int n = 0;
	while(!m_query.eof())
	{
		if(n == 0)
		{
			if(lstrcmp((char*)m_query.fieldValue("usergroup_sl_explorer"), "×") == 0)
			{
				pUserInfo->IsVectorView = FALSE;
			}
			else
			{
				pUserInfo->IsVectorView = TRUE;
			}

			if(lstrcmp((char*)m_query.fieldValue("usergroup_sg_explorer"), "×") == 0)
			{
				pUserInfo->IsRasterView = FALSE;
			}
			else
			{
				pUserInfo->IsRasterView = TRUE;
			}

			if(lstrcmp((char*)m_query.fieldValue("usergroup_db_explorer"), "×") == 0)
			{
				pUserInfo->IsDataBaseView = FALSE;
			}
			else
			{
				pUserInfo->IsDataBaseView = TRUE;
			}

			if(lstrcmp((char*)m_query.fieldValue("usergroup_sl_conversion"), "×") == 0)
			{
				pUserInfo->IsVectorConvert = FALSE;
			}
			else
			{
				pUserInfo->IsVectorConvert = TRUE;
			}

			if(lstrcmp((char*)m_query.fieldValue("usergroup_sg_conversion"), "×") == 0)
			{
				pUserInfo->IsRasterConvert = FALSE;
			}
			else
			{
				pUserInfo->IsRasterConvert = TRUE;
			}

			if(lstrcmp((char*)m_query.fieldValue("usergroup_db_conversion"), "×") == 0)
			{
				pUserInfo->IsDataBaseConvert = FALSE;
			}
			else
			{
				pUserInfo->IsDataBaseConvert = TRUE;
			}
		}
		else
		{
			CString m_strT;

			//合并矢量浏览权限
			m_strT.Format("%s", m_query.getStringField("usergroup_sl_explorer"));
			if((pUserInfo->IsVectorView == FALSE) && m_strT == "√")
			{
				pUserInfo->IsVectorView = TRUE;
			}

			//合并栅格浏览权限
			m_strT.Format("%s", m_query.getStringField("usergroup_sg_explorer"));
			if((pUserInfo->IsRasterView == FALSE) && m_strT == "√")
			{
				pUserInfo->IsRasterView = TRUE;
			}

			//合并数据库浏览权限
			m_strT.Format("%s", m_query.getStringField("usergroup_db_explorer"));
			if((pUserInfo->IsDataBaseView == FALSE) && m_strT == "√")
			{
				pUserInfo->IsDataBaseView = TRUE;
			}


			//合并矢量转换权限
			m_strT.Format("%s", m_query.getStringField("usergroup_sl_conversion"));
			if((pUserInfo->IsVectorConvert == FALSE) && m_strT == "√")
			{
				pUserInfo->IsVectorConvert = TRUE;
			}

			//合并栅格转换权限
			m_strT.Format("%s", m_query.getStringField("usergroup_sg_conversion"));
			if((pUserInfo->IsRasterConvert == FALSE) && m_strT == "√")
			{
				pUserInfo->IsRasterConvert = TRUE;
			}


			//合并数据库转换权限
			m_strT.Format("%s", m_query.getStringField("usergroup_db_conversion"));
			if((pUserInfo->IsDataBaseConvert == FALSE) && (m_strT == "√"))
			{
				pUserInfo->IsDataBaseConvert = TRUE;
			}
		}	
		m_query.nextRow();
		n++;
	}
}

void SaveRunTask()
{
	//保存当前正在执行的任务
	CDeuXmlWriter m_WriterTask;
	CString m_strpath = GetStylesPath()+"\\Run.tmp";
	m_WriterTask.BuildTaskXml(m_strpath, &TasksMapping);
}

void SaveFormatXml()
{
	CDeuXmlWriter m_WriterTask;
	CString m_strpath = GetStylesPath()+"\\TransFormat.xml";
	m_WriterTask.BuildFormatXml(m_strpath, &GobalFormat);
}

void LoadFormatXml()
{
	CDeuXmlReader m_XmlReader;
	m_XmlReader.LoadXml("TransFormat.xml");
	m_XmlReader.ReadFormat(GobalFormat);
	m_XmlReader.Free();
}

void ReleaseFormatXml(_StrFormatList& Tasks)
{
	for (std::vector<p_StrFormatTypeList>::const_iterator itor = Tasks.FormatTypeList.begin(); itor != Tasks.FormatTypeList.end(); itor++)
	{
		delete (*itor);
	}

	Tasks.FormatTypeList.clear();
}

void LoadMapping()
{
	//加载XML并映射到结构实体中
	Release_GeoXml(&GeoDataMapping);

	CDeuXmlReader m_XmlReader;
	m_XmlReader.LoadXml("geodata.xml");
	m_XmlReader.MappingGeoData(&GeoDataMapping);
	m_XmlReader.LoadXml("CustomData.xml");
	m_XmlReader.MappingGustomData(&GeoDataMapping);
	m_XmlReader.Free();
}

//进行大地用户自定义新坐标基本必要数据的初始化操作
void Init_Geodetic(p_GeodeticSeries pGeodeticSeries)
{		
	//pGeodeticSeries->name = "#";	
	pGeodeticSeries->type = "geodetic";	

	pGeodeticSeries->_name.name = "Name";	
	pGeodeticSeries->_name.type = "type";

	pGeodeticSeries->_remark.name = "Remark";
	pGeodeticSeries->_remark.type = "type";
	pGeodeticSeries->_remark.text = "#";

	//_envelope
	pGeodeticSeries->_envelope.name = "Envelope";
	pGeodeticSeries->_envelope.type = "Name";
	pGeodeticSeries->_envelope._name.name = "Envelope";
	pGeodeticSeries->_envelope._name.type = "Envelope";	
	pGeodeticSeries->_envelope._remark.name = "Remark";
	pGeodeticSeries->_envelope._remark.type = "Envelope Remark";
	pGeodeticSeries->_envelope._minpoint.name = "Minimum Point";
	pGeodeticSeries->_envelope._minpoint.type = "MinPoint";
	pGeodeticSeries->_envelope._minpoint._long.name = "Longitude";
	pGeodeticSeries->_envelope._minpoint._long.type = "Long";
	pGeodeticSeries->_envelope._minpoint._lat.name = "Latitude";
	pGeodeticSeries->_envelope._minpoint._lat.type = "Lat";
	pGeodeticSeries->_envelope._maxpoint.name = "Minimum Point";
	pGeodeticSeries->_envelope._maxpoint.type = "MinPoint";
	pGeodeticSeries->_envelope._maxpoint._long.name = "Longitude";
	pGeodeticSeries->_envelope._maxpoint._long.type = "Long";
	pGeodeticSeries->_envelope._maxpoint._lat.name = "Latitude";
	pGeodeticSeries->_envelope._maxpoint._lat.type = "Lat";

	//_pointStyle
	pGeodeticSeries->_pointStyle.name = "PointStyle";
	pGeodeticSeries->_pointStyle.type = "PointStyle";
	pGeodeticSeries->_pointStyle._name.name = "PointStyle";
	pGeodeticSeries->_pointStyle._name.type = "Name";
	pGeodeticSeries->_pointStyle._name.text = "Geodetic 2D";
	pGeodeticSeries->_pointStyle._remark.name = "PointStyle Remark";
	pGeodeticSeries->_pointStyle._remark.type = "Remark";
	pGeodeticSeries->_pointStyle._remark.text = "#";
	pGeodeticSeries->_pointStyle._dimensions.name = "Dimensions";
	pGeodeticSeries->_pointStyle._dimensions.type = "Dimensions";
	pGeodeticSeries->_pointStyle._geoDeticLatForPS.name = "Latitude";
	pGeodeticSeries->_pointStyle._geoDeticLatForPS.type = "Lat";
	pGeodeticSeries->_pointStyle._geoDeticLatForPS._label.name = "Label";
	pGeodeticSeries->_pointStyle._geoDeticLatForPS._label.type = "Label";
	pGeodeticSeries->_pointStyle._geoDeticLatForPS._label.text = "Geodetic Longitude";
	pGeodeticSeries->_pointStyle._geoDeticLatForPS._unit_2.name = "Units";
	pGeodeticSeries->_pointStyle._geoDeticLatForPS._unit_2.type = "Units";
	pGeodeticSeries->_pointStyle._geoDeticLatForPS._unit_2._name.name = "Name";
	pGeodeticSeries->_pointStyle._geoDeticLatForPS._unit_2._name.type = "Name";
	pGeodeticSeries->_pointStyle._geoDeticLatForPS._unit_2._name.text = "Degree";
	pGeodeticSeries->_pointStyle._geoDeticLatForPS._unit_2._remark.name = "Units Remark";
	pGeodeticSeries->_pointStyle._geoDeticLatForPS._unit_2._remark.type = "Remark";
	pGeodeticSeries->_pointStyle._geoDeticLatForPS._unit_2._remark.text = "#";
	pGeodeticSeries->_pointStyle._geoDeticLatForPS._unit_2._abbreviation.name = "Abbreviation";
	pGeodeticSeries->_pointStyle._geoDeticLatForPS._unit_2._abbreviation.type = "Abbreviation";
	pGeodeticSeries->_pointStyle._geoDeticLatForPS._unit_2._abbreviation.text = "deg";	
	pGeodeticSeries->_pointStyle._geoDeticLatForPS._unit_2._per_Degree.name = "Per_Degree";
	pGeodeticSeries->_pointStyle._geoDeticLatForPS._unit_2._per_Degree.type = "Per_Degree";
	pGeodeticSeries->_pointStyle._geoDeticLatForPS._unit_2._per_Degree.text = "1";
	pGeodeticSeries->_pointStyle._geoDeticLongForPS.name = "Longitude";
	pGeodeticSeries->_pointStyle._geoDeticLongForPS.type = "Long";
	pGeodeticSeries->_pointStyle._geoDeticLongForPS._label.name = "Label";
	pGeodeticSeries->_pointStyle._geoDeticLongForPS._label.type = "Label";
	pGeodeticSeries->_pointStyle._geoDeticLongForPS._label.text = "Geodetic Longitude";
	pGeodeticSeries->_pointStyle._geoDeticLongForPS._unit_2.name = "Units";
	pGeodeticSeries->_pointStyle._geoDeticLongForPS._unit_2.type = "Units";
	pGeodeticSeries->_pointStyle._geoDeticLongForPS._unit_2._name.name = "Name";
	pGeodeticSeries->_pointStyle._geoDeticLongForPS._unit_2._name.type = "Name";
	pGeodeticSeries->_pointStyle._geoDeticLongForPS._unit_2._name.text = "Degree";
	pGeodeticSeries->_pointStyle._geoDeticLongForPS._unit_2._remark.name = "Units Remark";
	pGeodeticSeries->_pointStyle._geoDeticLongForPS._unit_2._remark.type = "Remark";
	pGeodeticSeries->_pointStyle._geoDeticLongForPS._unit_2._remark.text = "#";
	pGeodeticSeries->_pointStyle._geoDeticLongForPS._unit_2._abbreviation.name = "Abbreviation";
	pGeodeticSeries->_pointStyle._geoDeticLongForPS._unit_2._abbreviation.type = "Abbreviation";
	pGeodeticSeries->_pointStyle._geoDeticLongForPS._unit_2._abbreviation.text = "deg";	
	pGeodeticSeries->_pointStyle._geoDeticLongForPS._unit_2._per_Degree.name = "Per_Degree";
	pGeodeticSeries->_pointStyle._geoDeticLongForPS._unit_2._per_Degree.type = "Per_Degree";
	pGeodeticSeries->_pointStyle._geoDeticLongForPS._unit_2._per_Degree.text = "1";
	pGeodeticSeries->_pointStyle._ellipsoidHeight.name = "Ellipsoid Height";
	pGeodeticSeries->_pointStyle._ellipsoidHeight.type = "EllipsoidHeight";
	pGeodeticSeries->_pointStyle._ellipsoidHeight._label.name = "Label";
	pGeodeticSeries->_pointStyle._ellipsoidHeight._label.type = "Label";
	pGeodeticSeries->_pointStyle._ellipsoidHeight._label.text = "Height";
	pGeodeticSeries->_pointStyle._ellipsoidHeight._unit_1.name = "Units";
	pGeodeticSeries->_pointStyle._ellipsoidHeight._unit_1.type = "Units";
	pGeodeticSeries->_pointStyle._ellipsoidHeight._unit_1._name.name = "Name";
	pGeodeticSeries->_pointStyle._ellipsoidHeight._unit_1._name.type = "Name";
	pGeodeticSeries->_pointStyle._ellipsoidHeight._unit_1._name.text = "Meter";
	pGeodeticSeries->_pointStyle._ellipsoidHeight._unit_1._remark.name = "Units Remark";
	pGeodeticSeries->_pointStyle._ellipsoidHeight._unit_1._remark.type = "Remark";
	pGeodeticSeries->_pointStyle._ellipsoidHeight._unit_1._remark.text = "#";
	pGeodeticSeries->_pointStyle._ellipsoidHeight._unit_1._abbreviation.name = "Abbreviation";
	pGeodeticSeries->_pointStyle._ellipsoidHeight._unit_1._abbreviation.type = "Abbreviation";
	pGeodeticSeries->_pointStyle._ellipsoidHeight._unit_1._abbreviation.text = "m";
	pGeodeticSeries->_pointStyle._ellipsoidHeight._unit_1._per_Meter.name = "Per_Meter";
	pGeodeticSeries->_pointStyle._ellipsoidHeight._unit_1._per_Meter.type = "Per_Meter";
	pGeodeticSeries->_pointStyle._ellipsoidHeight._unit_1._per_Meter.text = "1";

	//Datum
	pGeodeticSeries->_datum.name = "Datum";
	pGeodeticSeries->_datum.type = "Datum";
	pGeodeticSeries->_datum._name.name = "Datum";
	pGeodeticSeries->_datum._name.type = "Type";
	pGeodeticSeries->_datum._remark.name = "Datum Remark";
	pGeodeticSeries->_datum._remark.type = "Remark";
	pGeodeticSeries->_datum._remark.text = "#";
	pGeodeticSeries->_datum._primeMeridian.name = "PrimeMeridian";
	pGeodeticSeries->_datum._primeMeridian.type = "PrimeMeridian";
	pGeodeticSeries->_datum._primeMeridian._name.name = "Name";
	pGeodeticSeries->_datum._primeMeridian._name.type = "Prime Meridian";
	pGeodeticSeries->_datum._primeMeridian._name.text = "Greenwich";
	pGeodeticSeries->_datum._primeMeridian._geoDeticLong.name = "Longitude";
	pGeodeticSeries->_datum._primeMeridian._geoDeticLong.type = "Long";
	pGeodeticSeries->_datum._primeMeridian._geoDeticLong._value.name = "Value";
	pGeodeticSeries->_datum._primeMeridian._geoDeticLong._value.type = "Value";
	pGeodeticSeries->_datum._primeMeridian._geoDeticLong._unit_2.name = "Units";
	pGeodeticSeries->_datum._primeMeridian._geoDeticLong._unit_2.type = "Units";
	pGeodeticSeries->_datum._primeMeridian._geoDeticLong._unit_2._name.name = "Name";
	pGeodeticSeries->_datum._primeMeridian._geoDeticLong._unit_2._name.type = "Type";
	pGeodeticSeries->_datum._primeMeridian._geoDeticLong._unit_2._remark.name = "Units Remark";
	pGeodeticSeries->_datum._primeMeridian._geoDeticLong._unit_2._remark.type = "Remark";
	pGeodeticSeries->_datum._primeMeridian._geoDeticLong._unit_2._remark.text = "#";
	pGeodeticSeries->_datum._primeMeridian._geoDeticLong._unit_2._per_Degree.name = "Per_Degree";
	pGeodeticSeries->_datum._primeMeridian._geoDeticLong._unit_2._per_Degree.type = "Per_Degree";
	pGeodeticSeries->_datum._primeMeridian._geoDeticLong._unit_2._per_Degree.text = "1";
	pGeodeticSeries->_datum._primeMeridian._geoDeticLong._unit_2._abbreviation.name = "Abbreviation";
	pGeodeticSeries->_datum._primeMeridian._geoDeticLong._unit_2._abbreviation.type = "Abbreviation";
	pGeodeticSeries->_datum._primeMeridian._geoDeticLong._unit_2._abbreviation.text = "m";

	//_ellipsoid
	pGeodeticSeries->_datum._ellipsoid.name = "Ellipsoid";
	pGeodeticSeries->_datum._ellipsoid.type = "Ellipsoid";
	pGeodeticSeries->_datum._ellipsoid._name.name = "Ellipsoid";
	pGeodeticSeries->_datum._ellipsoid._name.type = "Ellipsoid";
	pGeodeticSeries->_datum._ellipsoid._remark.name = "Ellipsoid Remark";
	pGeodeticSeries->_datum._ellipsoid._remark.type = "Remark";
	pGeodeticSeries->_datum._ellipsoid._remark.text = "#";
	pGeodeticSeries->_datum._ellipsoid._inverseFlattening.name = "InverseFlattening";
	pGeodeticSeries->_datum._ellipsoid._inverseFlattening.type = "InverseFlattening";
	pGeodeticSeries->_datum._ellipsoid._semi_Major_Axis.name = "Semi-Major-Axis";
	pGeodeticSeries->_datum._ellipsoid._semi_Major_Axis.type = "Semi-Major-Axis";
	pGeodeticSeries->_datum._ellipsoid._semi_Major_Axis._value.name = "Semi-Major-Axis Value";
	pGeodeticSeries->_datum._ellipsoid._semi_Major_Axis._value.type = "Value";
	pGeodeticSeries->_datum._ellipsoid._semi_Major_Axis._unit_1.name = "Semi-Major-Axis Units";
	pGeodeticSeries->_datum._ellipsoid._semi_Major_Axis._unit_1.type = "Units";
	pGeodeticSeries->_datum._ellipsoid._semi_Major_Axis._unit_1._name.name = "Units";
	pGeodeticSeries->_datum._ellipsoid._semi_Major_Axis._unit_1._name.type = "Units";
	pGeodeticSeries->_datum._ellipsoid._semi_Major_Axis._unit_1._name.text = "Meter";
	pGeodeticSeries->_datum._ellipsoid._semi_Major_Axis._unit_1._remark.name = "Units Remark";
	pGeodeticSeries->_datum._ellipsoid._semi_Major_Axis._unit_1._remark.type = "Remark";
	pGeodeticSeries->_datum._ellipsoid._semi_Major_Axis._unit_1._remark.text = "#";
	pGeodeticSeries->_datum._ellipsoid._semi_Major_Axis._unit_1._abbreviation.name = "Abbreviation";
	pGeodeticSeries->_datum._ellipsoid._semi_Major_Axis._unit_1._abbreviation.type = "Abbreviation";
	pGeodeticSeries->_datum._ellipsoid._semi_Major_Axis._unit_1._abbreviation.text = "m";
	pGeodeticSeries->_datum._ellipsoid._semi_Major_Axis._unit_1._per_Meter.name = "Per_Meter";
	pGeodeticSeries->_datum._ellipsoid._semi_Major_Axis._unit_1._per_Meter.type = "Per_Meter";
	pGeodeticSeries->_datum._ellipsoid._semi_Major_Axis._unit_1._per_Meter.text = "1";
	pGeodeticSeries->_datum._ellipsoid._semi_Minor_Axis.name = "Semi-Minor-Axis";
	pGeodeticSeries->_datum._ellipsoid._semi_Minor_Axis.type = "Semi-Minor-Axis";
	pGeodeticSeries->_datum._ellipsoid._semi_Minor_Axis._value.name = "Semi-Minor-Axis Value";
	pGeodeticSeries->_datum._ellipsoid._semi_Minor_Axis._value.type = "Value";
	pGeodeticSeries->_datum._ellipsoid._semi_Minor_Axis._unit_1.name = "Semi-Minor-Axis Units";
	pGeodeticSeries->_datum._ellipsoid._semi_Minor_Axis._unit_1.type = "Units";
	pGeodeticSeries->_datum._ellipsoid._semi_Minor_Axis._unit_1._name.name = "Units";
	pGeodeticSeries->_datum._ellipsoid._semi_Minor_Axis._unit_1._name.type = "Name";
	pGeodeticSeries->_datum._ellipsoid._semi_Minor_Axis._unit_1._name.text = "Meter";
	pGeodeticSeries->_datum._ellipsoid._semi_Minor_Axis._unit_1._remark.name = "Units Remark";
	pGeodeticSeries->_datum._ellipsoid._semi_Minor_Axis._unit_1._remark.type = "Remark";
	pGeodeticSeries->_datum._ellipsoid._semi_Minor_Axis._unit_1._remark.text = "#";
	pGeodeticSeries->_datum._ellipsoid._semi_Minor_Axis._unit_1._abbreviation.name = "Abbreviation";
	pGeodeticSeries->_datum._ellipsoid._semi_Minor_Axis._unit_1._abbreviation.type = "Abbreviation";
	pGeodeticSeries->_datum._ellipsoid._semi_Minor_Axis._unit_1._abbreviation.text = "m";
	pGeodeticSeries->_datum._ellipsoid._semi_Minor_Axis._unit_1._per_Meter.name = "Per_Meter";
	pGeodeticSeries->_datum._ellipsoid._semi_Minor_Axis._unit_1._per_Meter.type = "Per_Meter";
	pGeodeticSeries->_datum._ellipsoid._semi_Minor_Axis._unit_1._per_Meter.text = "1";	

	//_csType
	pGeodeticSeries->_csType.name = "CSType";
	pGeodeticSeries->_csType.type = "CSType";
	pGeodeticSeries->_csType.text = "geodetic";
}

void Init_Projected(p_ProjectedSeries pProjectedSeries)
{
	pProjectedSeries->name = "";
	pProjectedSeries->type = "";
	pProjectedSeries->_name.name = "Name";	
	pProjectedSeries->_name.type = "type";

	pProjectedSeries->_remark.name = "Remark";
	pProjectedSeries->_remark.type = "type";
	pProjectedSeries->_remark.text = "#";

	//_envelope
	pProjectedSeries->_envelope.name = "Envelope";
	pProjectedSeries->_envelope.type = "Name";
	pProjectedSeries->_envelope._name.name = "Envelope";
	pProjectedSeries->_envelope._name.type = "Envelope";	
	pProjectedSeries->_envelope._remark.name = "Remark";
	pProjectedSeries->_envelope._remark.type = "Envelope Remark";
	pProjectedSeries->_envelope._minpoint.name = "Minimum Point";
	pProjectedSeries->_envelope._minpoint.type = "MinPoint";
	pProjectedSeries->_envelope._minpoint._long.name = "Longitude";
	pProjectedSeries->_envelope._minpoint._long.type = "Long";
	pProjectedSeries->_envelope._minpoint._lat.name = "Latitude";
	pProjectedSeries->_envelope._minpoint._lat.type = "Lat";
	pProjectedSeries->_envelope._maxpoint.name = "Minimum Point";
	pProjectedSeries->_envelope._maxpoint.type = "MinPoint";
	pProjectedSeries->_envelope._maxpoint._long.name = "Longitude";
	pProjectedSeries->_envelope._maxpoint._long.type = "Long";
	pProjectedSeries->_envelope._maxpoint._lat.name = "Latitude";
	pProjectedSeries->_envelope._maxpoint._lat.type = "Lat";

	//_pointStyle
	pProjectedSeries->_pointStyle.name = "PointStyle";
	pProjectedSeries->_pointStyle.type = "PointStyle";
	pProjectedSeries->_pointStyle._name.name = "Geodetic Point in Degree";
	pProjectedSeries->_pointStyle._name.type = "Name";
	pProjectedSeries->_pointStyle._remark.name = "PointStyle Remark";
	pProjectedSeries->_pointStyle._remark.type = "Remark";
	pProjectedSeries->_pointStyle._remark.text = "#";
	pProjectedSeries->_pointStyle._dimensions.name = "Dimensions";
	pProjectedSeries->_pointStyle._dimensions.type = "Dimensions";
	pProjectedSeries->_pointStyle._east.name = "Latitude";
	pProjectedSeries->_pointStyle._east.type = "Lat";
	pProjectedSeries->_pointStyle._east._label.name = "Label";
	pProjectedSeries->_pointStyle._east._label.type = "Label";
	pProjectedSeries->_pointStyle._east._label.text = "Easting";
	pProjectedSeries->_pointStyle._east._unit_1.name = "Units";
	pProjectedSeries->_pointStyle._east._unit_1.type = "Units";
	pProjectedSeries->_pointStyle._east._unit_1._name.name = "Name";
	pProjectedSeries->_pointStyle._east._unit_1._name.type = "Name";
	pProjectedSeries->_pointStyle._east._unit_1._name.text = "Degree";
	pProjectedSeries->_pointStyle._east._unit_1._remark.name = "Units Remark";
	pProjectedSeries->_pointStyle._east._unit_1._remark.type = "Remark";
	pProjectedSeries->_pointStyle._east._unit_1._remark.text = "#";
	pProjectedSeries->_pointStyle._east._unit_1._abbreviation.name = "Abbreviation";
	pProjectedSeries->_pointStyle._east._unit_1._abbreviation.type = "Abbreviation";
	pProjectedSeries->_pointStyle._east._unit_1._abbreviation.text = "deg";	
	pProjectedSeries->_pointStyle._east._unit_1._per_Meter.name = "Per_Meter";
	pProjectedSeries->_pointStyle._east._unit_1._per_Meter.type = "Per_Meter";
	pProjectedSeries->_pointStyle._east._unit_1._per_Meter.text = "1";
	pProjectedSeries->_pointStyle._north.name = "Longitude";
	pProjectedSeries->_pointStyle._north.type = "Long";
	pProjectedSeries->_pointStyle._north._label.name = "Label";
	pProjectedSeries->_pointStyle._north._label.type = "Label";
	pProjectedSeries->_pointStyle._north._label.text = "Northing";
	pProjectedSeries->_pointStyle._north._unit_1.name = "Units";
	pProjectedSeries->_pointStyle._north._unit_1.type = "Units";
	pProjectedSeries->_pointStyle._north._unit_1._name.name = "Name";
	pProjectedSeries->_pointStyle._north._unit_1._name.type = "Name";
	pProjectedSeries->_pointStyle._north._unit_1._name.text = "Degree";
	pProjectedSeries->_pointStyle._north._unit_1._remark.name = "Units Remark";
	pProjectedSeries->_pointStyle._north._unit_1._remark.type = "Remark";
	pProjectedSeries->_pointStyle._north._unit_1._remark.text = "#";
	pProjectedSeries->_pointStyle._north._unit_1._abbreviation.name = "Abbreviation";
	pProjectedSeries->_pointStyle._north._unit_1._abbreviation.type = "Abbreviation";
	pProjectedSeries->_pointStyle._north._unit_1._abbreviation.text = "m";	
	pProjectedSeries->_pointStyle._north._unit_1._per_Meter.name = "Per_Degree";
	pProjectedSeries->_pointStyle._north._unit_1._per_Meter.type = "Per_Degree";
	pProjectedSeries->_pointStyle._north._unit_1._per_Meter.text = "1";
	pProjectedSeries->_pointStyle._ellipsoidHeight.name = "Ellipsoid Height";
	pProjectedSeries->_pointStyle._ellipsoidHeight.type = "EllipsoidHeight";
	pProjectedSeries->_pointStyle._ellipsoidHeight._label.name = "Label";
	pProjectedSeries->_pointStyle._ellipsoidHeight._label.type = "Label";
	pProjectedSeries->_pointStyle._ellipsoidHeight._label.text = "Height";
	pProjectedSeries->_pointStyle._ellipsoidHeight._unit_1.name = "Units";
	pProjectedSeries->_pointStyle._ellipsoidHeight._unit_1.type = "Units";
	pProjectedSeries->_pointStyle._ellipsoidHeight._unit_1._name.name = "Name";
	pProjectedSeries->_pointStyle._ellipsoidHeight._unit_1._name.type = "Name";
	pProjectedSeries->_pointStyle._ellipsoidHeight._unit_1._name.text = "Meter";
	pProjectedSeries->_pointStyle._ellipsoidHeight._unit_1._remark.name = "Units Remark";
	pProjectedSeries->_pointStyle._ellipsoidHeight._unit_1._remark.type = "Remark";
	pProjectedSeries->_pointStyle._ellipsoidHeight._unit_1._remark.text = "#";
	pProjectedSeries->_pointStyle._ellipsoidHeight._unit_1._abbreviation.name = "Abbreviation";
	pProjectedSeries->_pointStyle._ellipsoidHeight._unit_1._abbreviation.type = "Abbreviation";
	pProjectedSeries->_pointStyle._ellipsoidHeight._unit_1._abbreviation.text = "m";
	pProjectedSeries->_pointStyle._ellipsoidHeight._unit_1._per_Meter.name = "Per_Meter";
	pProjectedSeries->_pointStyle._ellipsoidHeight._unit_1._per_Meter.type = "Per_Meter";
	pProjectedSeries->_pointStyle._ellipsoidHeight._unit_1._per_Meter.text = "1";

	//pProjectedSeries->_projection.name = "";
	pProjectedSeries->_projection.type = "projected";
	pProjectedSeries->_projection.text = "高斯投影";

	pProjectedSeries->_geodeticPointor.name = "Geodetic";
	pProjectedSeries->_geodeticPointor.type = "GeodeticPointor";
	//pProjectedSeries->_geodeticPointor.text = "";

	//偏心率 _centralMeridian
	pProjectedSeries->_centralMeridian.name = "Central Meridian";
	pProjectedSeries->_centralMeridian.type = "CentralMeridian";
	pProjectedSeries->_centralMeridian._name.name = "name";
	pProjectedSeries->_centralMeridian._name.type = "name";
	pProjectedSeries->_centralMeridian._name.text = "CentralMeridian";
	pProjectedSeries->_centralMeridian._uint.name = "Units";
	pProjectedSeries->_centralMeridian._uint.type = "Units";
	pProjectedSeries->_centralMeridian._uint.text = "Degree";
	pProjectedSeries->_centralMeridian._value.name = "Value";
	pProjectedSeries->_centralMeridian._value.type = "Value";

	//东假值 _falseEasting
	pProjectedSeries->_falseEasting.name = "False Easting";
	pProjectedSeries->_falseEasting.type = "FalseEasting";
	pProjectedSeries->_falseEasting._name.name = "name";
	pProjectedSeries->_falseEasting._name.type = "name";
	pProjectedSeries->_falseEasting._name.text = "FalseEasting";
	pProjectedSeries->_falseEasting._uint.name = "Units";
	pProjectedSeries->_falseEasting._uint.type = "Units";
	pProjectedSeries->_falseNorthing._uint.text = "Meter";
	pProjectedSeries->_falseEasting._value.name = "Value";
	pProjectedSeries->_falseEasting._value.type = "Value";

	//北假值 _falseNorthing
	pProjectedSeries->_falseNorthing.name = "False Northing";
	pProjectedSeries->_falseNorthing.type = "FalseNorthing";
	pProjectedSeries->_falseNorthing._name.name = "name";
	pProjectedSeries->_falseNorthing._name.type = "name";
	pProjectedSeries->_falseNorthing._name.text = "FalseNorthing";
	pProjectedSeries->_falseNorthing._uint.name = "Units";
	pProjectedSeries->_falseNorthing._uint.type = "Units";
	pProjectedSeries->_falseNorthing._uint.text = "Meter";
	pProjectedSeries->_falseNorthing._value.name = "Value";
	pProjectedSeries->_falseNorthing._value.type = "Value";

	//_latitudeOfOrigin
	pProjectedSeries->_latitudeOfOrigin.name = "LatitudeOfOrigin";
	pProjectedSeries->_latitudeOfOrigin.type = "LatitudeOfOrigin";
	pProjectedSeries->_latitudeOfOrigin._name.name = "name";
	pProjectedSeries->_latitudeOfOrigin._name.type = "name";
	pProjectedSeries->_latitudeOfOrigin._name.text = "LatitudeOfOrigin";
	pProjectedSeries->_latitudeOfOrigin._uint.name = "Units";
	pProjectedSeries->_latitudeOfOrigin._uint.type = "Units";
	pProjectedSeries->_latitudeOfOrigin._uint.text = "Degree";
	pProjectedSeries->_latitudeOfOrigin._value.name = "Value";
	pProjectedSeries->_latitudeOfOrigin._value.type = "Value";

	// _scaleFactor
	pProjectedSeries->_scaleFactor.name = "Scale Factor";
	pProjectedSeries->_scaleFactor.type = "ScaleFactor";
	pProjectedSeries->_scaleFactor._name.name = "name";
	pProjectedSeries->_scaleFactor._name.type = "name";
	pProjectedSeries->_scaleFactor._name.text = "ScaleFactor";
	pProjectedSeries->_scaleFactor._uint.name = "Units";
	pProjectedSeries->_scaleFactor._uint.type = "Units";
	pProjectedSeries->_scaleFactor._value.name = "Value";
	pProjectedSeries->_scaleFactor._value.type = "Value";
	//_csType
	pProjectedSeries->_csType.name = "CSType";
	pProjectedSeries->_csType.type = "CSType";
	pProjectedSeries->_csType.text = "projected";
}


//获取大地坐标结构
_GeodeticSeries* GetGeoDeticObject(CString m_strName)
{	
	for(int n=0; n<GeoDataMapping.GeodeticNode.pGeodeticSeries.GetCount(); n++)
	{
		if(GeoDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._name.text == m_strName)
		{
			return &GeoDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n);
		}
	}

	return NULL;
}

//获取平面坐标结构 
_ProjectedSeries* GetProjectedObject(CString m_strName)
{	
	for(int n=0; n<GeoDataMapping.ProjectedNode.pProjectedSeries.GetCount(); n++)
	{
		if(GeoDataMapping.ProjectedNode.pProjectedSeries.GetAt(n)._name.text == m_strName)
		{
			return &GeoDataMapping.ProjectedNode.pProjectedSeries.GetAt(n);
		}
	}

	return NULL;
}

//释放指针--坐标系数据
void Release_GeoXml(p_GeoDataXml pGeoXml)
{
	int n;
	pGeoXml->name.Empty();
	for(n=0; n<pGeoXml->GeodeticNode.pGeodeticSeries.GetCount(); n++)
	{	
		//delete pGeoXml->GeodeticNode.pGeodeticSeries.GetAt(n);
		pGeoXml->GeodeticNode.pGeodeticSeries.RemoveAt(n);
	}
	pGeoXml->GeodeticNode.name.Empty();
	pGeoXml->GeodeticNode.type.Empty();
	pGeoXml->GeodeticNode.pGeodeticSeries.RemoveAll();

	for(n=0; n<pGeoXml->ProjectedNode.pProjectedSeries.GetCount(); n++)
	{	
		//delete pGeoXml->ProjectedNode.pProjectedSeries.GetAt(n);		
		pGeoXml->ProjectedNode.pProjectedSeries.RemoveAt(n);
	}
	pGeoXml->ProjectedNode.name.Empty();
	pGeoXml->ProjectedNode.type.Empty();
	pGeoXml->ProjectedNode.pProjectedSeries.RemoveAll();
}

/*
=============================================   
功能:	生成GUID
日期:	2010-10-27	add by hushichen
=============================================
*/
const char* newGUID()
{
	static char buf[64] = {0};
	GUID guid;
	
	if (S_OK == ::CoCreateGuid(&guid))
	{
		_snprintf(buf, sizeof(buf),
			"%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
			guid.Data1,
			guid.Data2,
			guid.Data3,
			guid.Data4[0], guid.Data4[1],
			guid.Data4[2], guid.Data4[3],
			guid.Data4[4], guid.Data4[5],
			guid.Data4[6], guid.Data4[7]);
	}
	
	return (const char*)buf;
}
