#include "StdAfx.h"
#include "DeuFunction.h"

const double dbdetalXY[8][2] = {
							{6,4},
							{3,2},
							{1.5,1},
							{1.0/2.0,1.0/3.0},
							{1.0/4.0,1.0/6.0},
							{1.0/8.0,1.0/12.0},
							{1.0/16.0,1.0/24.0},
							{1.0/32.0,1.0/48.0},
						};

CDeuFunction::CDeuFunction(void)
{
}

CDeuFunction::~CDeuFunction(void)
{
}

CNode* getNodeFromName(std::list<CNode *> n, CString name)//根据标签名称取结点 曹欣
{
	std::list<CNode *>::iterator it;
	it = n.begin();
	while (it != n.end() && (*it)->tag_name != name)
	{
		it++;
	}
	return (*it);
}

CString getNodeName(std::list<CNode *> n, CString name)//获取各个结点的名字，初始化GRID时用 曹欣
{
	CNode * node = NULL;
	node = getNodeFromName(n, name);
	if (node->data == "")
	{
		CNode * nameNode = NULL;
		nameNode = getNodeFromName(node->_sub_nodes, "Name");
		return nameNode->data;
	}
	return node->data;
}

CString GetCurrentDir()
{   
	TCHAR   sDrive[_MAX_DRIVE];   
	TCHAR   sDir[_MAX_DIR];   
	TCHAR   sFilename[_MAX_FNAME],Filename[_MAX_FNAME];   
	TCHAR   sExt[_MAX_EXT];   
	GetModuleFileName(AfxGetInstanceHandle(),   Filename,   _MAX_PATH);   

	//debug_df
	_tsplitpath(Filename,   sDrive,   sDir,   sFilename,   sExt);   
	CString   homeDir(CString(sDrive)   +   CString(sDir));   
	int   nLen   =   homeDir.GetLength();   
	if(homeDir.GetAt(nLen-1)   !=   '\\')   
		homeDir   +=   '\\';   
	return   homeDir;   
}   

void   AfxSelectDirDlg(/*char Dir[256]*/char *Dir)     
{     
	BROWSEINFO   bi;     
	ITEMIDLIST   *pidl;     

	bi.hwndOwner             =   NULL;     
	bi.pidlRoot               =   NULL;     
	bi.pszDisplayName   =   Dir;  
	
	LPCSTR lpWTitle= "选择一个目录：";
	bi.lpszTitle   =  (LPCSTR)lpWTitle ;     
	bi.ulFlags       =  BIF_RETURNONLYFSDIRS;
	bi.lpfn             =   NULL;     
	bi.lParam         =   0;
	bi.iImage         =   0;

	pidl   =   SHBrowseForFolder(   &bi   );

	if   (pidl   ==   NULL)
		Dir[0]   =   '\0';     

	if   (!SHGetPathFromIDList(   pidl,  Dir   ))
		Dir[0]   =   '\0';
}   

//图幅号求西南
void CalculateWS(const char * tf, double & w ,double & s)
{
	char szA =tf[0] ;	
	char szB[2] ;

	szB[0] = tf[1];
	szB[1] = tf[2];

	char szScaleCode = tf[3];

	char szC[3]  ;

	memcpy( szC , tf+4 , 3); 

	char szD[3]  ;
	
	memcpy( szD , tf+7 , 3); 

	////////////////////////////

	double a(0),b(0),c(0),d(0),detalX(0),detalY(0);

	a = letter2num((const char )szA);

	b = atoi((const char *)&szB);

	c = atoi((const char *)&szC);

	d = atoi((const char *)&szD);

	int iScaleCode = letter2num( (const char)szScaleCode ) ;

	//GetDetalXY( int iScaleCode , double & detalX , double & detalY );
	GetDetalXY(  iScaleCode ,  detalY ,  detalX );


	////////////////////////////

	
	w = ( b - 31 ) * 6 + ( d - 1 ) * detalY ;

	s = ( a - 1 ) * 4 + ( 4 / detalX - c ) * detalX ;

}

int letter2num(const char l)
{
		
	const char letter[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

	for (int i=0; i<26 ; i++)
	{
		if(  l ==  letter[i] )
			return i+1;
	}
	return -1;
}

void GetDetalXY( int iScaleCode , double & detalX , double & detalY )
{

	detalX =  dbdetalXY[iScaleCode - 1][0];

	detalY =  dbdetalXY[iScaleCode - 1][1];

}

BOOL IsExistDirectory(const string& strPath)
{
	WIN32_FIND_DATA							filedate;
	BOOL									bResult = FALSE;
	HANDLE									hFind;

	hFind = FindFirstFile(strPath.c_str(), &filedate);

	if ((hFind != INVALID_HANDLE_VALUE) && (filedate.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
	{
		bResult = TRUE;
	}

	FindClose(hFind);

	return bResult;
}

int CALLBACK BrowseDirCallbackProc(HWND hwnd,UINT uMsg,LPARAM lParam,LPARAM lpData)
{
	if (uMsg == BFFM_INITIALIZED)
	{
		SendMessage(hwnd, BFFM_SETSELECTION, TRUE, lpData);
	}

	return 0;
}

void SelectDirDlg(const CString& strSelectDir, char* szDir)
{
	char							dir[MAX_PATH] = {0};
	char							Buffer[MAX_PATH] = {0};

	BROWSEINFO							br;
	br.hwndOwner = NULL;
	br.iImage = NULL;
	br.pszDisplayName = Buffer;
	br.lpszTitle = "选择一个目录：";
	br.ulFlags = BIF_RETURNONLYFSDIRS;
	br.pidlRoot = NULL;

	//判断目录是否存在
	if (IsExistDirectory(string(strSelectDir)))
	{
		br.lpfn = BrowseDirCallbackProc;
		br.lParam = (long)(LPCTSTR)strSelectDir;
	}
	else
	{
		br.lpfn = NULL;
		br.lParam = 0;
	}


	LPITEMIDLIST lpPath = SHBrowseForFolder(&br);

	if (SHGetPathFromIDList(lpPath, dir))
	{
		strcpy(szDir, dir);
	}

}
