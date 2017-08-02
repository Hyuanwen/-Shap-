#include "stdafx.h"
#include "CoverageParse.h"

AVCE00ReadPtr  ReadE00Ptr = NULL;
char*          pszLine;
AVCE00WritePtr hWriteInfo = NULL;

void CoverageParse(const char * FileIn, const char * FileOut)
{
	AVCCoverType    eCoverType = AVCCoverV7;

	LOGSTR("开始创建目标文件夹！");
	hWriteInfo = AVCE00WriteOpen(FileOut, eCoverType, AVC_DEFAULT_PREC);
	//如果第一次创建失败则考试是否是因为多重文件夹的原因导致 再次核对路径 创建文件夹后再创建具体的文件 begin
	/*
	if (hWriteInfo == NULL)
    {
		CString       strFileOut;
		CString       strFileName;
		CString       strFile;

		strFileOut.Format(_T("%s"), FileOut);
		strFileName = strFileOut.Mid(strFileOut.ReverseFind('\\')+1);

        strFile = strFileOut.Mid(0, strFileOut.GetLength()-strFileName.GetLength());
        CreateDirectory(strFile, NULL);

		hWriteInfo = AVCE00WriteOpen(FileOut, eCoverType, AVC_DEFAULT_PREC);
    }
	*/
	//如果第一次创建失败则考试是否是因为多重文件夹的原因导致 再次核对路径 创建文件夹后再创建具体的文件 end
	LOGSTR("已执行创建目标文件夹！");
	if (hWriteInfo==NULL)
	{
		LOGSTR("创建目标文件夹失败！");
		return ;
	}

    LOGSTR("开始读取目标文件夹！");
	ReadE00Ptr = AVCE00ReadOpen(FileIn);
	LOGSTR("已执行读取目标文件夹！");
	if (ReadE00Ptr==NULL)
	{
		LOGSTR("读取源文件失败！");
		return ;
	}

	pszLine =(char *)AVCE00ReadNextLine(ReadE00Ptr);
	while (pszLine!= NULL)
	{
		if (strnicmp(pszLine, "ARC  3", 6)==0)
		{
			CoverageParseARC3(FileIn,FileOut);
		}
		else if (strnicmp(pszLine, "ARC  2", 6)==0)
		{
		    CoverageParseARC2(FileIn,FileOut);
		}
		else if (strnicmp(pszLine, "LAB  3", 6)==0)
		{
			CoverageParseLAB3(FileIn,FileOut);
		}
		else if (strnicmp(pszLine, "LAB  2", 6)==0)
		{
			CoverageParseLAB2(FileIn,FileOut);
		}
		else if (strnicmp(pszLine, "CNT  3", 6)==0)
		{
		   CoverageParseCNT3(FileIn,FileOut);
		} 
		else if (strnicmp(pszLine, "CNT  2", 6)==0)
		{
		   CoverageParseCNT2(FileIn,FileOut);
		}
		else if (strnicmp(pszLine, "PAL  3", 6)==0)
		{
		   CoverageParsePAL3(FileIn,FileOut);			
		}
        else if (strnicmp(pszLine, "PAL  2", 6)==0)
		{
		   CoverageParsePAL2(FileIn,FileOut);
		}
		else if ((strnicmp(pszLine,"TX6  3",6)==0)||(strnicmp(pszLine,"TX7  3",6)==0))
		{
		   CoverageParseTX6_7_3(FileIn,FileOut);
		} 
		else if ((strnicmp(pszLine,"TX6  2",6)==0)||(strnicmp(pszLine,"TX7  2",6)==0))
		{
           CoverageParseTX6_7_2(FileIn,FileOut);
		}
		else if (strnicmp(pszLine, "TXT  3", 6)==0)
		{
			CoverageParseTXT3(FileIn,FileOut);			
		}
		else if (strnicmp(pszLine, "TXT  2", 6)==0)
		{
			CoverageParseTXT2(FileIn,FileOut);

		}
		else if (strlen(pszLine)==56)
		{
           CoverageParseBND(FileIn,FileOut);
		}
        else  if (strnicmp(pszLine, "XMIN", 4)==0)
		{
           CoverageParseEx(FileIn,FileOut);
	    }
		else if (strlen(pszLine)==39)
		{
			double x1=0;
			double y1=0;
			double z1=0;

			double dx1=0;
			double dy1=0;
			double dz1=0;

			string mystr;
			string mystr1;
			string mystr2;
			string mystr3;
			string mystr4;

			mystr3 = pszLine;
			mystr4 = mystr3.substr(0,11);

			x1=atof(pszLine+11);
			y1=atof(pszLine+25);
			p_transform(y1, x1, z1, dy1, dx1, dz1);
			DoubletoScientific_notation2(dx1,mystr1,15);
			DoubletoScientific_notation2(dy1,mystr2,15);
			mystr=mystr4+" "+mystr1.substr(0,9)+mystr1.substr(16,4)+" "+mystr2.substr(0,9)+mystr2.substr(16,4);
			strcpy(pszLine,mystr.c_str());
			AVCE00WriteNextLine(hWriteInfo,pszLine);
			pszLine =(char *) AVCE00ReadNextLine(ReadE00Ptr);
		}
		else
		{
			AVCE00WriteNextLine(hWriteInfo,pszLine);
			pszLine =(char *) AVCE00ReadNextLine(ReadE00Ptr);
		}

		/*
		AVCE00WriteNextLine(hWriteInfo,pszLine);
		FILE   *_pfile=fopen("C:\\log.txt","a+");
		fwrite(pszLine,strlen(pszLine),1,_pfile);
		fwrite("\r\n",2,1,_pfile);
		fclose(_pfile);
		pszLine = AVCE00ReadNextLine(ReadE00Ptr);
		*/
	}
	AVCE00ReadClose(ReadE00Ptr);
	AVCE00WriteClose(hWriteInfo);	
}

void CoverageParseARC3(const char * FileIn, const char * FileOut)
{
	double x1=0;
	double y1=0;
	double z1=0;

	double dx1=0;
	double dy1=0;
	double dz1=0;

	string mystr;
	string mystr1;
	string mystr2;

	AVCE00WriteNextLine(hWriteInfo, pszLine);	
	pszLine = (char *)AVCE00ReadNextLine(ReadE00Ptr);
	while (strnicmp(pszLine,"        -1         0         0         0         0         0         0",70)!=0)
	{
		int nLen=strlen(pszLine);
		if(nLen==42)
		{
			x1=atof(pszLine);
			y1=atof(pszLine+21);
			p_transform(y1, x1, z1, dy1, dx1, dz1);
			DoubletoScientific_notation2(dx1,mystr1,15);
			DoubletoScientific_notation2(dy1,mystr2,15);
			mystr=" "+mystr1+" "+mystr2;
			strcpy(pszLine,mystr.c_str());
		}
		AVCE00WriteNextLine(hWriteInfo, pszLine);
		pszLine=(char *)AVCE00ReadNextLine(ReadE00Ptr);
}
}

void CoverageParseARC2(const char * FileIn, const char * FileOut)
{
	double x1=0;
	double y1=0;
	double z1=0;
	double x2=0;
	double y2=0;
	double z2=0;

	double dx1=0;
	double dy1=0;
	double dz1=0;
	double dx2=0;
	double dy2=0;
	double dz2=0;

	string mystr;
	string mystr1;
	string mystr2;
	string mystr3;
	string mystr4;
	
	AVCE00WriteNextLine(hWriteInfo, "ARC  3");	
    pszLine = (char *)AVCE00ReadNextLine(ReadE00Ptr);
	while (strnicmp(pszLine,"        -1         0         0         0         0         0         0",70)!=0)
	{
		int nLen=strlen(pszLine);
		if (nLen==56)
		{
			x1=atof(pszLine);
			y1=atof(pszLine+14);
			p_transform(y1, x1, z1, dy1, dx1, dz1);
			x2=atof(pszLine+28);
			y2=atof(pszLine+42);
			p_transform(y2, x2, z2, dy2, dx2, dz2);
			DoubletoScientific_notation2(dx1,mystr1,15);
			DoubletoScientific_notation2(dy1,mystr2,15);
			DoubletoScientific_notation2(dx2,mystr3,15);
			DoubletoScientific_notation2(dy2,mystr4,15);
			mystr=" "+mystr1+" "+mystr2;
			strcpy(pszLine,mystr.c_str());
			AVCE00WriteNextLine(hWriteInfo,pszLine);
			mystr=" "+mystr3+" "+mystr4;
			strcpy(pszLine,mystr.c_str());
			AVCE00WriteNextLine(hWriteInfo,pszLine);
		} 
		else if (nLen==28)
		{
			x1=atof(pszLine);
			y1=atof(pszLine+14);
			p_transform(y1, x1, z1, dy1, dx1, dz1);
			DoubletoScientific_notation2(dx1,mystr1,15);
			DoubletoScientific_notation2(dy1,mystr2,15);
			mystr=" "+mystr1+" "+mystr2;
			strcpy(pszLine,mystr.c_str());
			AVCE00WriteNextLine(hWriteInfo, pszLine);
		} 
		else
		{
			AVCE00WriteNextLine(hWriteInfo, pszLine);
		}
		pszLine = (char *)AVCE00ReadNextLine(ReadE00Ptr);
	}
}

void CoverageParseLAB3(const char * FileIn, const char * FileOut)
{
	double x1=0;
	double y1=0;
	double z1=0;

	double dx1=0;
	double dy1=0;
	double dz1=0;

	string mystr;
	string mystr1;
	string mystr2;
	string mystr3;
	string mystr4;

	AVCE00WriteNextLine(hWriteInfo, pszLine);	
    pszLine =(char *) AVCE00ReadNextLine(ReadE00Ptr);
	while (strnicmp(pszLine,"        -1         0 0.00000000000000E+00 0.00000000000000E+00",62)!=0)
	{
		int nlen=strlen(pszLine);
		if (nlen==62)
		{			
			x1=atof(pszLine+20);
			y1=atof(pszLine+41);
			p_transform(y1, x1, z1, dy1, dx1, dz1);
			DoubletoScientific_notation2(dx1,mystr1,15);
			DoubletoScientific_notation2(dy1,mystr2,15);
			mystr3=pszLine;
			mystr4=mystr3.substr(0,20);
			mystr=mystr4+" "+mystr1+" "+mystr2;
			strcpy(pszLine,mystr.c_str());
		} 
		AVCE00WriteNextLine(hWriteInfo, pszLine);
	    pszLine =(char *) AVCE00ReadNextLine(ReadE00Ptr);
	}
}

void CoverageParseLAB2(const char * FileIn, const char * FileOut)
{
	double x1=0;
	double y1=0;
	double z1=0;
	double x2=0;
	double y2=0;
	double z2=0;

	double dx1=0;
	double dy1=0;
	double dz1=0;
	double dx2=0;
	double dy2=0;
	double dz2=0;

	string mystr;
	string mystr1;
	string mystr2;
	string mystr3;
	string mystr4;

	AVCE00WriteNextLine(hWriteInfo,"LAB  3");
    pszLine = (char *)AVCE00ReadNextLine(ReadE00Ptr);
	while (strnicmp(pszLine,"        -1         0 0.0000000E+00 0.0000000E+00",48)!=0)
	{
		int nlen=strlen(pszLine);
		if(nlen==48)
		{
			x1=atof(pszLine+20);
			y1=atof(pszLine+34);
			p_transform(y1, x1, z1, dy1, dx1, dz1);
			DoubletoScientific_notation2(dx1,mystr1,15);
			DoubletoScientific_notation2(dy1,mystr2,15);
			mystr3=pszLine;
			mystr4=mystr3.substr(0,20);
			mystr=mystr4+" "+mystr1+" "+mystr2;
			strcpy(pszLine,mystr.c_str());
			AVCE00WriteNextLine(hWriteInfo, pszLine);
		}	
		else if (nlen==56)
		{
			x1=atof(pszLine);
			y1=atof(pszLine+14);
			p_transform(y1, x1, z1, dy1, dx1, dz1);
			x2=atof(pszLine+28);
			y2=atof(pszLine+42);
			p_transform(y2, x2, z2, dy2, dx2, dz2);
			DoubletoScientific_notation2(dx1,mystr1,15);
			DoubletoScientific_notation2(dy1,mystr2,15);
			DoubletoScientific_notation2(dx2,mystr3,15);
			DoubletoScientific_notation2(dy2,mystr4,15);
			mystr=" "+mystr1+" "+mystr2;
			strcpy(pszLine,mystr.c_str());
			AVCE00WriteNextLine(hWriteInfo,pszLine);
			mystr=" "+mystr3+" "+mystr4;
			strcpy(pszLine,mystr.c_str());
			AVCE00WriteNextLine(hWriteInfo,pszLine);
		}
		else
		{
			AVCE00WriteNextLine(hWriteInfo, pszLine);
		}
        pszLine =(char *) AVCE00ReadNextLine(ReadE00Ptr);
	}
}

void CoverageParseCNT3(const char * FileIn, const char * FileOut)
{
	double x1=0;
	double y1=0;
	double z1=0;

	double dx1=0;
	double dy1=0;
	double dz1=0;

	string mystr;
	string mystr1;
	string mystr2;
	string mystr3;
	string mystr4;

	AVCE00WriteNextLine(hWriteInfo, pszLine);	
    pszLine =(char *) AVCE00ReadNextLine(ReadE00Ptr);
	while (strnicmp(pszLine,"        -1         0         0         0         0         0         0",70)!=0)
	{
		int nlen=strlen(pszLine);
		if (nlen==52)
		{				
			x1=atof(pszLine+10);
			y1=atof(pszLine+31);
			p_transform(y1, x1, z1, dy1, dx1, dz1);
			DoubletoScientific_notation2(dx1,mystr1,15);
			DoubletoScientific_notation2(dy1,mystr2,15);
			mystr3=pszLine;
			mystr4=mystr3.substr(0,10);
			mystr=mystr4+" "+mystr1+" "+mystr2;
			strcpy(pszLine,mystr.c_str());
		} 
		AVCE00WriteNextLine(hWriteInfo, pszLine);
		pszLine = (char *)AVCE00ReadNextLine(ReadE00Ptr);
	}
}

void CoverageParseCNT2(const char * FileIn, const char * FileOut)
{
	double x1=0;
	double y1=0;
	double z1=0;

	double dx1=0;
	double dy1=0;
	double dz1=0;

	string mystr;
	string mystr1;
	string mystr2;
	string mystr3;
	string mystr4;
	AVCE00WriteNextLine(hWriteInfo,"CNT  3");
	pszLine = (char *)AVCE00ReadNextLine(ReadE00Ptr);
	while (strnicmp(pszLine,"        -1         0         0         0         0         0         0",70)!=0)
	{
		int nlen=strlen(pszLine);
		if(nlen==38)
		{
			x1=atof(pszLine+10);
			y1=atof(pszLine+24);
			p_transform(y1, x1, z1, dy1, dx1, dz1);
			DoubletoScientific_notation2(dx1,mystr1,15);
			DoubletoScientific_notation2(dy1,mystr2,15);
			mystr3=pszLine;
			mystr4=mystr3.substr(0,10);
			mystr=mystr4+" "+mystr1+" "+mystr2;
			strcpy(pszLine,mystr.c_str());
		}	
		AVCE00WriteNextLine(hWriteInfo, pszLine);
		pszLine = (char *)AVCE00ReadNextLine(ReadE00Ptr);
	}
}

void CoverageParsePAL3(const char * FileIn, const char * FileOut)
{
	double x1=0;
	double y1=0;
	double z1=0;

	double dx1=0;
	double dy1=0;
	double dz1=0;

	string mystr;
	string mystr1;
	string mystr2;
	string mystr3;
	string mystr4;

	AVCE00WriteNextLine(hWriteInfo, pszLine);	
    pszLine =(char *) AVCE00ReadNextLine(ReadE00Ptr);
	while (strnicmp(pszLine,"        -1         0         0         0         0         0         0",70)!=0)
	{
		int nLen=strlen(pszLine);
		if(nLen==52)
		{
			x1=atof(pszLine+10);
			y1=atof(pszLine+31);
			p_transform(y1, x1, z1, dy1, dx1, dz1);
			DoubletoScientific_notation2(dx1,mystr1,15);
			DoubletoScientific_notation2(dy1,mystr2,15);
			mystr3=pszLine;
			mystr4=mystr3.substr(0,10);
			mystr=mystr4+" "+mystr1+" "+mystr2;
			strcpy(pszLine,mystr.c_str());
		}
		else if(nLen==42)
		{
			x1=atof(pszLine);
			y1=atof(pszLine+21);
			p_transform(y1, x1, z1, dy1, dx1, dz1);
			DoubletoScientific_notation2(dx1,mystr1,15);
			DoubletoScientific_notation2(dy1,mystr2,15);
			mystr=" "+mystr1+" "+mystr2;
			strcpy(pszLine,mystr.c_str());
		}
		AVCE00WriteNextLine(hWriteInfo, pszLine);
		pszLine =(char *) AVCE00ReadNextLine(ReadE00Ptr);
	}
}

void CoverageParsePAL2(const char * FileIn, const char * FileOut)
{
	double x1=0;
	double y1=0;
	double z1=0;
	double x2=0;
	double y2=0;
	double z2=0;

	double dx1=0;
	double dy1=0;
	double dz1=0;
	double dx2=0;
	double dy2=0;
	double dz2=0;

	string mystr;
	string mystr1;
	string mystr2;
	string mystr3;
	string mystr4;
	string mystr5;
	string mystr6;

	AVCE00WriteNextLine(hWriteInfo,"PAL  3");
	pszLine = (char *)AVCE00ReadNextLine(ReadE00Ptr);
	while (strnicmp(pszLine,"        -1         0         0         0         0         0         0",70)!=0)
	{
		int nLen=strlen(pszLine);
		if(nLen==66)
		{
			x1=atof(pszLine+10);
			y1=atof(pszLine+24);
			p_transform(y1, x1, z1, dy1, dx1, dz1);
			x2=atof(pszLine+38);
			y2=atof(pszLine+52);
			p_transform(y2, x2, z2, dy2, dx2, dz2);
			DoubletoScientific_notation2(dx1,mystr1,15);
			DoubletoScientific_notation2(dy1,mystr2,15);
			DoubletoScientific_notation2(dx2,mystr5,15);
			DoubletoScientific_notation2(dy2,mystr6,15);
			mystr3=pszLine;
			mystr4=mystr3.substr(0,10);
			mystr=mystr4+" "+mystr1+" "+mystr2+" "+mystr5+" "+mystr6;
			strcpy(pszLine,mystr.c_str());
			AVCE00WriteNextLine(hWriteInfo, pszLine);
			mystr=" "+mystr5+" "+mystr6;
			strcpy(pszLine,mystr.c_str());
			AVCE00WriteNextLine(hWriteInfo, pszLine);
		}
		else
		{
			AVCE00WriteNextLine(hWriteInfo, pszLine);
		}
	        pszLine = (char *)AVCE00ReadNextLine(ReadE00Ptr);
	}
}

void CoverageParseTX6_7_3(const char * FileIn, const char * FileOut)
{
	double x1=0;
	double y1=0;
	double z1=0;

	double dx1=0;
	double dy1=0;
	double dz1=0;

	string mystr;
	string mystr1;
	string mystr2;

	AVCE00WriteNextLine(hWriteInfo, pszLine);	
	pszLine =(char *) AVCE00ReadNextLine(ReadE00Ptr);
	while (strnicmp(pszLine,"JABBERWOCKY",11)!=0)
	{
		int nlen=strlen(pszLine);
		if (nlen==42)
		{				
			x1=atof(pszLine);
			y1=atof(pszLine+21);
			p_transform(y1, x1, z1, dy1, dx1, dz1);
			DoubletoScientific_notation2(dx1,mystr1,15);
			DoubletoScientific_notation2(dy1,mystr2,15);
			mystr=" "+mystr1+" "+mystr2;
			strcpy(pszLine,mystr.c_str());
		} 
		AVCE00WriteNextLine(hWriteInfo, pszLine);
		pszLine = (char *)AVCE00ReadNextLine(ReadE00Ptr);
	}
}

void CoverageParseTX6_7_2(const char * FileIn, const char * FileOut)
{
	double x1=0;
	double y1=0;
	double z1=0;

	double dx1=0;
	double dy1=0;
	double dz1=0;

	string mystr;
	string mystr1;
	string mystr2;

	mystr=pszLine;
	mystr1=mystr.substr(0,5);
	mystr2=mystr1+"3";
	strcpy(pszLine,mystr2.c_str());

	AVCE00WriteNextLine(hWriteInfo,pszLine);
	pszLine = (char *)AVCE00ReadNextLine(ReadE00Ptr);
	while (strnicmp(pszLine,"JABBERWOCKY",11)!=0)
	{
		int nlen=strlen(pszLine);
		if(nlen==28)
		{
			x1=atof(pszLine);
			y1=atof(pszLine+14);
			p_transform(y1, x1, z1, dy1, dx1, dz1);
			DoubletoScientific_notation2(dx1,mystr1,15);
			DoubletoScientific_notation2(dy1,mystr2,15);
			mystr=" "+mystr1+" "+mystr2;
			strcpy(pszLine,mystr.c_str());
		}	
		AVCE00WriteNextLine(hWriteInfo, pszLine);
		pszLine =(char *) AVCE00ReadNextLine(ReadE00Ptr);
	}
}

void CoverageParseBND(const char * FileIn, const char * FileOut)
{
	string mystr;
	string mystr1;
	string mystr2;

	mystr=pszLine;
	if ( mystr.find("BND")<20)
	{
		mystr1=mystr.substr(0,44);
		mystr2=mystr.substr(46);
		mystr=mystr1+"32"+mystr2;
		strcpy(pszLine,mystr.c_str());
		AVCE00WriteNextLine(hWriteInfo, pszLine);
	}
	else
	{
		AVCE00WriteNextLine(hWriteInfo, pszLine);
	}
	pszLine =(char *) AVCE00ReadNextLine(ReadE00Ptr);
}

void CoverageParseEx(const char * FileIn, const char * FileOut)
{
	double x1=0;
	double y1=0;
	double z1=0;
	double x2=0;
	double y2=0;
	double z2=0;

	double dx1=0;
	double dy1=0;
	double dz1=0;
	double dx2=0;
	double dy2=0;
	double dz2=0;

	string mystr;
	string mystr1;
	string mystr2;
	string mystr3;
	string mystr4;
	string mystr5;
	string mystr6;

	mystr=pszLine;
	mystr1=mystr.substr(0,18);
	mystr2=mystr.substr(19,11);
	mystr3=mystr.substr(35);
	mystr=mystr1+"8"+mystr2+"18 5 "+mystr3;
	strcpy(pszLine,mystr.c_str());
	AVCE00WriteNextLine(hWriteInfo, pszLine);
	pszLine = (char *)AVCE00ReadNextLine(ReadE00Ptr);

	mystr=pszLine;
	mystr1=mystr.substr(0,18);
	mystr2=mystr.substr(19,11);
	mystr3=mystr.substr(35);
	mystr=mystr1+"8"+mystr2+"18 5 "+mystr3;
	strcpy(pszLine,mystr.c_str());
	AVCE00WriteNextLine(hWriteInfo, pszLine);
	pszLine = (char *)AVCE00ReadNextLine(ReadE00Ptr);

	mystr=pszLine;
	mystr1=mystr.substr(0,18);
	mystr2=mystr.substr(19,11);
	mystr3=mystr.substr(35);
	mystr=mystr1+"8"+mystr2+"18 5 "+mystr3;
	strcpy(pszLine,mystr.c_str());
	AVCE00WriteNextLine(hWriteInfo, pszLine);
	pszLine = (char *)AVCE00ReadNextLine(ReadE00Ptr);

	mystr=pszLine;
	mystr1=mystr.substr(0,18);
	mystr2=mystr.substr(19,11);
	mystr3=mystr.substr(35);
	mystr=mystr1+"8"+mystr2+"18 5 "+mystr3;
	strcpy(pszLine,mystr.c_str());
	AVCE00WriteNextLine(hWriteInfo, pszLine);
	pszLine =(char *) AVCE00ReadNextLine(ReadE00Ptr);

	int nlen=strlen(pszLine);
	if (nlen==56)
	{		
		x1=atof(pszLine);
		y1=atof(pszLine+14);
		p_transform(y1, x1, z1, dy1, dx1, dz1);
		x2=atof(pszLine+28);
		y2=atof(pszLine+42);
		p_transform(y2, x2, z2, dy2, dx2, dz2);
		DoubletoScientific_notation2(dx1,mystr1,18);
		DoubletoScientific_notation2(dy1,mystr2,18);
		DoubletoScientific_notation2(dx2,mystr3,18);
		DoubletoScientific_notation2(dy2,mystr4,18);
		mystr=" "+mystr1+" "+mystr2+" "+mystr3+" "+mystr4;
		mystr5=mystr.substr(0,80);
		strcpy(pszLine,mystr5.c_str());
		AVCE00WriteNextLine(hWriteInfo,pszLine);
		mystr6=mystr.substr(80);
		strcpy(pszLine,mystr6.c_str());
		AVCE00WriteNextLine(hWriteInfo,pszLine);
	}
	else if (nlen==80)
	{
		mystr1=pszLine;
	    pszLine =(char *) AVCE00ReadNextLine(ReadE00Ptr);
		mystr2=pszLine;
		mystr=mystr1+mystr2;
	    strcpy(pszLine,mystr.c_str());

		x1=atof(pszLine);
		y1=atof(pszLine+24);
		p_transform(y1, x1, z1, dy1, dx1, dz1);
		x2=atof(pszLine+48);
		y2=atof(pszLine+72);
		p_transform(y2, x2, z2, dy2, dx2, dz2);
		DoubletoScientific_notation2(dx1,mystr1,18);
		DoubletoScientific_notation2(dy1,mystr2,18);
		DoubletoScientific_notation2(dx2,mystr3,18);
		DoubletoScientific_notation2(dy2,mystr4,18);
		mystr=" "+mystr1+" "+mystr2+" "+mystr3+" "+mystr4;
		mystr5=mystr.substr(0,80);
		strcpy(pszLine,mystr5.c_str());
		AVCE00WriteNextLine(hWriteInfo,pszLine);
		mystr6=mystr.substr(80);
		strcpy(pszLine,mystr6.c_str());
		AVCE00WriteNextLine(hWriteInfo,pszLine);
	}	
	else
	{
		AVCE00WriteNextLine(hWriteInfo,pszLine);
	}
	pszLine =(char *) AVCE00ReadNextLine(ReadE00Ptr);
}

void CoverageParseTXT3(const char * FileIn, const char * FileOut)
{
	double x1=0;
	double y1=0;
	double z1=0;
	double x2=0;
	double y2=0;
	double z2=0;

	double dx1=0;
	double dy1=0;
	double dz1=0;
	double dx2=0;
	double dy2=0;
	double dz2=0;

	string mystr;
	string mystr1;
	string mystr2;
	string mystr3;
	string mystr4;
	string mystr5;
	string mystr6;

	AVCE00WriteNextLine(hWriteInfo, pszLine);	
	pszLine = (char *)AVCE00ReadNextLine(ReadE00Ptr);

	while (strnicmp(pszLine,"        -1         0         0         0         0         0         0",70)!=0)
	{
		int nLen=strlen(pszLine);
		if(nLen==63)
		{
			x1=atof(pszLine+1);
			x2=atof(pszLine+22);

			p_transform(y1, x1, z1, dy1, dx1, dz1);
			pszLine = (char *)AVCE00ReadNextLine(ReadE00Ptr);

			y1=atof(pszLine+22);

			y2=atof(pszLine+43);
			p_transform(y2, x2, z2, dy2, dx2, dz2);

			DoubletoScientific_notation2(dx1,mystr1,15);
			DoubletoScientific_notation2(dy1,mystr2,15);
			DoubletoScientific_notation2(dx2,mystr5,15);
			DoubletoScientific_notation2(dy2,mystr6,15);

			pszLine = (char *)AVCE00ReadNextLine(ReadE00Ptr);

			mystr=" "+mystr1+" "+mystr5+" "+"0.00000000000000E+00";
			strcpy(pszLine,mystr.c_str());
			AVCE00WriteNextLine(hWriteInfo, pszLine);

			mystr=" 0.00000000000000E+00 "+mystr2+" "+mystr6;
			strcpy(pszLine,mystr.c_str());
			AVCE00WriteNextLine(hWriteInfo, pszLine);

			pszLine = (char *)AVCE00ReadNextLine(ReadE00Ptr);
			AVCE00WriteNextLine(hWriteInfo, pszLine);

			pszLine = (char *)AVCE00ReadNextLine(ReadE00Ptr);
			AVCE00WriteNextLine(hWriteInfo, pszLine);

			pszLine = (char *)AVCE00ReadNextLine(ReadE00Ptr);
			AVCE00WriteNextLine(hWriteInfo, pszLine);
		}
		else
		{
			AVCE00WriteNextLine(hWriteInfo, pszLine);
		}
		pszLine = (char *)AVCE00ReadNextLine(ReadE00Ptr);
	}
}

void CoverageParseTXT2(const char * FileIn, const char * FileOut)
{
	double x1=0;
	double y1=0;
	double z1=0;
	double x2=0;
	double y2=0;
	double z2=0;

	double dx1=0;
	double dy1=0;
	double dz1=0;
	double dx2=0;
	double dy2=0;
	double dz2=0;

	string mystr;
	string mystr1;
	string mystr2;
	string mystr3;
	string mystr4;
	string mystr5;
	string mystr6;

	AVCE00WriteNextLine(hWriteInfo, "TXT  3");	
	pszLine = (char *)AVCE00ReadNextLine(ReadE00Ptr);

	while (strnicmp(pszLine,"        -1         0         0         0         0         0         0",70)!=0)
	{
		int nLen=strlen(pszLine);
		if(nLen==70)
		{
			x1=atof(pszLine+1);
			x2=atof(pszLine+15);

			p_transform(y1, x1, z1, dy1, dx1, dz1);

			y1=atof(pszLine+57);
		    pszLine = (char *)AVCE00ReadNextLine(ReadE00Ptr);
			y2=atof(pszLine+1);
			p_transform(y2, x2, z2, dy2, dx2, dz2);

			DoubletoScientific_notation2(dx1,mystr1,15);
			DoubletoScientific_notation2(dy1,mystr2,15);
			DoubletoScientific_notation2(dx2,mystr5,15);
			DoubletoScientific_notation2(dy2,mystr6,15);

		    pszLine = (char *)AVCE00ReadNextLine(ReadE00Ptr);

			mystr=" "+mystr1+" "+mystr5+" "+"0.00000000000000E+00";
			strcpy(pszLine,mystr.c_str());
			AVCE00WriteNextLine(hWriteInfo, pszLine);
			
			mystr=" 0.00000000000000E+00 "+mystr2+" "+mystr6;
			strcpy(pszLine,mystr.c_str());
			AVCE00WriteNextLine(hWriteInfo, pszLine);

			mystr=" 0.00000000000000E+00 0.00000000000000E+00 0.00000000000000E+00";
			strcpy(pszLine,mystr.c_str());
			AVCE00WriteNextLine(hWriteInfo, pszLine);

			mystr=" 0.00000000000000E+00 0.00000000000000E+00 0.00000000000000E+00";
			strcpy(pszLine,mystr.c_str());
			AVCE00WriteNextLine(hWriteInfo, pszLine);

			mystr=" 0.00000000000000E+00 0.00000000000000E+00 3.00000000000000E+00";
			strcpy(pszLine,mystr.c_str());
			AVCE00WriteNextLine(hWriteInfo, pszLine);
		}
		else
		{
			AVCE00WriteNextLine(hWriteInfo, pszLine);
		}
		pszLine = (char *)AVCE00ReadNextLine(ReadE00Ptr);
	}
}
