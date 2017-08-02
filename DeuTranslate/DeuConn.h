#pragma once

#ifndef _DEUCONN_H
#define _DEUCONN_H
#include "stdafx.h"
#include "ogrsf_frmts.h"

//class OGRDataSource;
class CDeuConn
{
public:
	CDeuConn(){};
public:
	OGRDataSource*			DataSource;
	long					ConnId;
	CString					ConnString;
};

#endif