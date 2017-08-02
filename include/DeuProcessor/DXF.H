#ifndef _DXF_H
#define _DXF_H


#ifdef DXF_EXPORTS
#define DXF_API __declspec(dllexport)
#else
#define DXF_API __declspec(dllimport)
#endif



DXF_API int fnDXF(void);

DXF_API int DXFTransform( const char * FileIn, const char * FileOut, void * transfun, HWND m_phwnd );

DXF_API int EooTransform( const char * FileIn, const char * FileOut, void * transfun, HWND m_phwnd );

DXF_API int CoverageTransform( const char * FileIn, const char * FileOut, void * transfun, HWND m_phwnd );

typedef  void  (__stdcall *TransFun)( double x , double y , double z , double & out_x ,double & out_y ,double & out_z );

extern TransFun p_transform ;


//add by chenyong 2013-5-14 Í¶Ó°×ª»»
DXF_API int DXFProject(const char *pFileIn, const char *pFileOut, bool bToPlane, void *ptransfun, HWND pHwnd);

/* -------------------------------------------------------------------- */
/*      Callback "progress" function.                                   */
/* -------------------------------------------------------------------- */

typedef int (__stdcall *DeuProgressFunc)(double,const char *, void *);

class DeuProgress
	{
	public:
		long hwnd;

		DeuProgressFunc _Progress;
	};

extern DXF_API DeuProgress* g_pProgress;

void  InvokeProgressFun();
#endif