#ifndef DEULIB_H
#define DEULIB_H

#include "stdafx.h"

using namespace std;

vector<vector<string>> DeuReadFile(const char *szfn);


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

char num2letter(const int n)
{
	if( n <= 0 || n >26)
		return -1;
		
	const char letter[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	
	return letter[n-1];
	
}

double DMS2D(double D,double M,double S)
{
	double Dm = M/60;

	double Ds = S/3600;

	return D + Dm + Ds;
}

#endif