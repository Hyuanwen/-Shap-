/*
*Copyright (C) 2012 ,Juno
*All	rights	reserved.
*
*File Name:	GridMask.h.
*
*Function:	Interface of  base class
*
*Author:	Juno
*
*E-mail:	http://lyflxr@yahoo.cn
*
*Version:	0.1
*/
#pragma once

#ifdef GRIDMASK_EXPORTS
#define GRID_MASK_API __declspec(dllexport)
#else
#define GRID_MASK_API __declspec(dllimport)
#endif

GRID_MASK_API int GeneralGridForShp(const char *pszDSName, const char *pszGridDSName, /*const*/ double step);

