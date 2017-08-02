/////////////////////////////////////////////////////////////////////
//     项目:		德毅智慧转换软件
//     描述:		sqlite接口向上封装类
//     版本:		v1.0 
//		CopyRight 2010 ljdy Corporation All Rights Reserved
/////////////////////////////////////////////////////////////////////
#ifndef _CppSQLite3_H_
#define _CppSQLite3_H_

#include "..\..\include\Sqlite\sqlite3.h"
#include <cstdio>
#include <cstring>



#define CPPSQLITE_ERROR 1000



/////////////////////////////////////////////////////////////////////
//     项目:	德毅智慧转换软件
//     描述:	sqlite 异常处理类
//		CopyRight 2010 ljdy Corporation All Rights Reserved
/////////////////////////////////////////////////////////////////////
class CDeuSQLite3Exception
{
public:

    CDeuSQLite3Exception(const int nErrCode,
                    char* szErrMess,
                    bool bDeleteMsg=true);

    CDeuSQLite3Exception(const CDeuSQLite3Exception&  e);

    virtual ~CDeuSQLite3Exception();

    const int errorCode() { return mnErrCode; }

    const char* errorMessage() { return mpszErrMess; }

    static const char* errorCodeAsString(int nErrCode);

private:

    int mnErrCode;
    char* mpszErrMess;
};




/////////////////////////////////////////////////////////////////////
//     项目:	德毅智慧转换软件
//     描述:	sqlite 缓冲处理类
//	   CopyRight 2010 ljdy Corporation All Rights Reserved
/////////////////////////////////////////////////////////////////////
class CDeuSQLite3Buffer
{
public:

    CDeuSQLite3Buffer();

    ~CDeuSQLite3Buffer();

    const char* format(const char* szFormat, ...);

    operator const char*() { return mpBuf; }

    void clear();

private:

    char* mpBuf;
};



/////////////////////////////////////////////////////////////////////
//     项目:	德毅智慧转换软件
//     描述:	sqlite 字节以及编码处理类
//		CopyRight 2010 ljdy Corporation All Rights Reserved
/////////////////////////////////////////////////////////////////////
class CDeuSQLite3Binary
{
public:

    CDeuSQLite3Binary();

    ~CDeuSQLite3Binary();

    void setBinary(const unsigned char* pBuf, int nLen);
    void setEncoded(const unsigned char* pBuf);

    const unsigned char* getEncoded();
    const unsigned char* getBinary();

    int getBinaryLength();

    unsigned char* allocBuffer(int nLen);

    void clear();

private:

    unsigned char* mpBuf;
    int mnBinaryLen;
    int mnBufferLen;
    int mnEncodedLen;
    bool mbEncoded;
};



/////////////////////////////////////////////////////////////////////
//     项目:	德毅智慧转换软件
//     描述:	sqlite 访问对象封装类
//		CopyRight 2010 ljdy Corporation All Rights Reserved
/////////////////////////////////////////////////////////////////////
class CDeuSQLite3Query
{
public:

    CDeuSQLite3Query();

    CDeuSQLite3Query(const CDeuSQLite3Query& rQuery);

    CDeuSQLite3Query(sqlite3* pDB,
				sqlite3_stmt* pVM,
                bool bEof,
                bool bOwnVM=true);

    CDeuSQLite3Query& operator=(const CDeuSQLite3Query& rQuery);

    virtual ~CDeuSQLite3Query();

    int numFields();

    int fieldIndex(const char* szField);
    const char* fieldName(int nCol);

    const char* fieldDeclType(int nCol);
    int fieldDataType(int nCol);

    const char* fieldValue(int nField);
    const char* fieldValue(const char* szField);

    int getIntField(int nField, int nNullValue=0);
    int getIntField(const char* szField, int nNullValue=0);

    double getFloatField(int nField, double fNullValue=0.0);
    double getFloatField(const char* szField, double fNullValue=0.0);

    const char* getStringField(int nField, const char* szNullValue="");
    const char* getStringField(const char* szField, const char* szNullValue="");

    const unsigned char* getBlobField(int nField, int& nLen);
    const unsigned char* getBlobField(const char* szField, int& nLen);

    bool fieldIsNull(int nField);
    bool fieldIsNull(const char* szField);

    bool eof();

    void nextRow();

    void finalize();

private:

    void checkVM();

	sqlite3* mpDB;
    sqlite3_stmt* mpVM;
    bool mbEof;
    int mnCols;
    bool mbOwnVM;
};


/////////////////////////////////////////////////////////////////////
//     项目:	德毅智慧转换软件
//     描述:	sqlite 访问结果表封装类
//		CopyRight 2010 ljdy Corporation All Rights Reserved
/////////////////////////////////////////////////////////////////////
class CDeuSQLite3Table
{
public:

    CDeuSQLite3Table();

    CDeuSQLite3Table(const CDeuSQLite3Table& rTable);

    CDeuSQLite3Table(char** paszResults, int nRows, int nCols);

    virtual ~CDeuSQLite3Table();

    CDeuSQLite3Table& operator=(const CDeuSQLite3Table& rTable);

    int numFields();

    int numRows();

    const char* fieldName(int nCol);

    const char* fieldValue(int nField);
    const char* fieldValue(const char* szField);

    int getIntField(int nField, int nNullValue=0);
    int getIntField(const char* szField, int nNullValue=0);

    double getFloatField(int nField, double fNullValue=0.0);
    double getFloatField(const char* szField, double fNullValue=0.0);

    const char* getStringField(int nField, const char* szNullValue="");
    const char* getStringField(const char* szField, const char* szNullValue="");

    bool fieldIsNull(int nField);
    bool fieldIsNull(const char* szField);

    void setRow(int nRow);

    void finalize();

private:

    void checkResults();

    int mnCols;
    int mnRows;
    int mnCurrentRow;
    char** mpaszResults;
};

/////////////////////////////////////////////////////////////////////
//     项目:	德毅智慧转换软件
//     描述:	sqlite 访问结果处理类
//		CopyRight 2010 ljdy Corporation All Rights Reserved
/////////////////////////////////////////////////////////////////////
class CDeuSQLite3Statement
{
public:

    CDeuSQLite3Statement();

    CDeuSQLite3Statement(const CDeuSQLite3Statement& rStatement);

    CDeuSQLite3Statement(sqlite3* pDB, sqlite3_stmt* pVM);

    virtual ~CDeuSQLite3Statement();

    CDeuSQLite3Statement& operator=(const CDeuSQLite3Statement& rStatement);

    int execDML();

    CDeuSQLite3Query execQuery();

    void bind(int nParam, const char* szValue);
    void bind(int nParam, const int nValue);
    void bind(int nParam, const double dwValue);
    void bind(int nParam, const unsigned char* blobValue, int nLen);
    void bindNull(int nParam);

    void reset();

    void finalize();

private:

    void checkDB();
    void checkVM();

    sqlite3* mpDB;
    sqlite3_stmt* mpVM;
};


/////////////////////////////////////////////////////////////////////
//     项目:	德毅智慧转换软件
//     描述:	sqlite 库对象处理类
//		CopyRight 2010 ljdy Corporation All Rights Reserved
/////////////////////////////////////////////////////////////////////
class CDeuSQLite3DB
{
public:

    CDeuSQLite3DB();

    virtual ~CDeuSQLite3DB();

    void open(const char* szFile, char* encrypt);

    void close();

	bool tableExists(const char* szTable);

    int execDML(const char* szSQL);

    CDeuSQLite3Query execQuery(const char* szSQL);

    int execScalar(const char* szSQL);

    CDeuSQLite3Table getTable(const char* szSQL);

    CDeuSQLite3Statement compileStatement(const char* szSQL);

    sqlite_int64 lastRowId();

    void interrupt() { sqlite3_interrupt(mpDB); }

    void setBusyTimeout(int nMillisecs);

    static const char* SQLiteVersion() { return SQLITE_VERSION; }

private:

    CDeuSQLite3DB(const CDeuSQLite3DB& db);
    CDeuSQLite3DB& operator=(const CDeuSQLite3DB& db);

    sqlite3_stmt* compile(const char* szSQL);

    void checkDB();

    sqlite3* mpDB;
    int mnBusyTimeoutMs;
};

#endif
