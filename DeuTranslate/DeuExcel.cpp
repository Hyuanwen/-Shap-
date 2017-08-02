#include "stdafx.h"
#include "DeuExcel.h"

char *	num2letter( char * l ,  const long n);//1-25×ª×ÖÄ¸
char * D2L(const long c , char * Letter);	  //Êý×Ö×ª×ÖÄ¸

char * Num2Letter (long r,long c,char * Letter)
{
	Letter = D2L( c ,Letter );

	char * sz_r = new char[200];
	sz_r = itoa( r , sz_r ,10 );

	strcat( Letter , sz_r);

	delete sz_r;

	return 0;
}

char * D2L(const long c , char * Letter)
{
	int c1 = 0;
	int *c2 = NULL;

	c1 = c;
	int pos = 0;
	while(c1>0)
	{
		c1 = c1/26;
		pos++;
	}	
	
	c1 = c;
	c2 = new int[pos];
	for(int i=0 ; i< pos ; i++)
	{		
		c2[i] = c1%26;
		c1 = c1/26;
	}
	
	char * l = new char[1];
	for(int i=pos ; i>0 ; i--  )
	{
		l = num2letter(l , c2[i-1]);
		strcpy( Letter + pos - i , l); 
	}

	return Letter;
}

char *	num2letter( char * l ,  const long n)
{
	if(n<1 || n>26 )
		return NULL;

	char* letter[26] = {"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"};

	strcpy( l , letter[n-1]);
	return l;
}

//int _tmain(int argc, _TCHAR* argv[])
//{
//	char Letter3[100]; 
//	
//	D2L( 358 ,Letter3);
//	
//	char Letter[100]; 
//	char *Letter2; 
//
//	Letter2 = itoa( 358, Letter , 25);
//	return 0;
//}