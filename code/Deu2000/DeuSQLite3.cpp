
#include "stdafx.h"
#include "DeuSQLite3.h"
#include <cstdlib>


// Named constant for passing to CppSQLite3Exception when passing it a string
// that cannot be deleted.
static const bool DONT_DELETE_MSG=false;

////////////////////////////////////////////////////////////////////////////////
// Prototypes for SQLite functions not included in SQLite DLL, but copied below
// from SQLite encode.c
////////////////////////////////////////////////////////////////////////////////
int sqlite3_encode_binary(const unsigned char *in, int n, unsigned char *out);
int sqlite3_decode_binary(const unsigned char *in, unsigned char *out);

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

CDeuSQLite3Exception::CDeuSQLite3Exception(const int nErrCode,
									char* szErrMess,
									bool bDeleteMsg/*=true*/) :
									mnErrCode(nErrCode)
{
	mpszErrMess = sqlite3_mprintf("%s[%d]: %s",
								errorCodeAsString(nErrCode),
								nErrCode,
								szErrMess ? szErrMess : "");

	if (bDeleteMsg && szErrMess)
	{
		sqlite3_free(szErrMess);
	}
}

									
CDeuSQLite3Exception::CDeuSQLite3Exception(const CDeuSQLite3Exception&  e) :
									mnErrCode(e.mnErrCode)
{
	mpszErrMess = 0;
	if (e.mpszErrMess)
	{
		mpszErrMess = sqlite3_mprintf("%s", e.mpszErrMess);
	}
}


const char* CDeuSQLite3Exception::errorCodeAsString(int nErrCode)
{
	switch (nErrCode)
	{
		case SQLITE_OK          : return "SQLITE_OK";
		case SQLITE_ERROR       : return "SQLITE_ERROR";
		case SQLITE_INTERNAL    : return "SQLITE_INTERNAL";
		case SQLITE_PERM        : return "SQLITE_PERM";
		case SQLITE_ABORT       : return "SQLITE_ABORT";
		case SQLITE_BUSY        : return "SQLITE_BUSY";
		case SQLITE_LOCKED      : return "SQLITE_LOCKED";
		case SQLITE_NOMEM       : return "SQLITE_NOMEM";
		case SQLITE_READONLY    : return "SQLITE_READONLY";
		case SQLITE_INTERRUPT   : return "SQLITE_INTERRUPT";
		case SQLITE_IOERR       : return "SQLITE_IOERR";
		case SQLITE_CORRUPT     : return "SQLITE_CORRUPT";
		case SQLITE_NOTFOUND    : return "SQLITE_NOTFOUND";
		case SQLITE_FULL        : return "SQLITE_FULL";
		case SQLITE_CANTOPEN    : return "SQLITE_CANTOPEN";
		case SQLITE_PROTOCOL    : return "SQLITE_PROTOCOL";
		case SQLITE_EMPTY       : return "SQLITE_EMPTY";
		case SQLITE_SCHEMA      : return "SQLITE_SCHEMA";
		case SQLITE_TOOBIG      : return "SQLITE_TOOBIG";
		case SQLITE_CONSTRAINT  : return "SQLITE_CONSTRAINT";
		case SQLITE_MISMATCH    : return "SQLITE_MISMATCH";
		case SQLITE_MISUSE      : return "SQLITE_MISUSE";
		case SQLITE_NOLFS       : return "SQLITE_NOLFS";
		case SQLITE_AUTH        : return "SQLITE_AUTH";
		case SQLITE_FORMAT      : return "SQLITE_FORMAT";
		case SQLITE_RANGE       : return "SQLITE_RANGE";
		case SQLITE_ROW         : return "SQLITE_ROW";
		case SQLITE_DONE        : return "SQLITE_DONE";
		case CPPSQLITE_ERROR    : return "CPPSQLITE_ERROR";
		default: return "UNKNOWN_ERROR";
	}
}


CDeuSQLite3Exception::~CDeuSQLite3Exception()
{
	if (mpszErrMess)
	{
		sqlite3_free(mpszErrMess);
		mpszErrMess = 0;
	}
}


////////////////////////////////////////////////////////////////////////////////

CDeuSQLite3Buffer::CDeuSQLite3Buffer()
{
	mpBuf = 0;
}


CDeuSQLite3Buffer::~CDeuSQLite3Buffer()
{
	clear();
}


void CDeuSQLite3Buffer::clear()
{
	if (mpBuf)
	{
		sqlite3_free(mpBuf);
		mpBuf = 0;
	}

}


const char* CDeuSQLite3Buffer::format(const char* szFormat, ...)
{
	clear();
	va_list va;
	va_start(va, szFormat);
	mpBuf = sqlite3_vmprintf(szFormat, va);
	va_end(va);
	return mpBuf;
}


////////////////////////////////////////////////////////////////////////////////

CDeuSQLite3Binary::CDeuSQLite3Binary() :
						mpBuf(0),
						mnBinaryLen(0),
						mnBufferLen(0),
						mnEncodedLen(0),
						mbEncoded(false)
{
}


CDeuSQLite3Binary::~CDeuSQLite3Binary()
{
	clear();
}


void CDeuSQLite3Binary::setBinary(const unsigned char* pBuf, int nLen)
{
	mpBuf = allocBuffer(nLen);
	memcpy(mpBuf, pBuf, nLen);
}


void CDeuSQLite3Binary::setEncoded(const unsigned char* pBuf)
{
	clear();

	mnEncodedLen = strlen((const char*)pBuf);
	mnBufferLen = mnEncodedLen + 1; // Allow for NULL terminator

	mpBuf = (unsigned char*)malloc(mnBufferLen);

	if (!mpBuf)
	{
		throw CDeuSQLite3Exception(CPPSQLITE_ERROR,
								"Cannot allocate memory",
								DONT_DELETE_MSG);
	}

	memcpy(mpBuf, pBuf, mnBufferLen);
	mbEncoded = true;
}


const unsigned char* CDeuSQLite3Binary::getEncoded()
{
	if (!mbEncoded)
	{
		unsigned char* ptmp = (unsigned char*)malloc(mnBinaryLen);
		memcpy(ptmp, mpBuf, mnBinaryLen);
		mnEncodedLen = sqlite3_encode_binary(ptmp, mnBinaryLen, mpBuf);
		free(ptmp);
		mbEncoded = true;
	}

	return mpBuf;
}


const unsigned char* CDeuSQLite3Binary::getBinary()
{
	if (mbEncoded)
	{
		// in/out buffers can be the same
		mnBinaryLen = sqlite3_decode_binary(mpBuf, mpBuf);

		if (mnBinaryLen == -1)
		{
			throw CDeuSQLite3Exception(CPPSQLITE_ERROR,
									"Cannot decode binary",
									DONT_DELETE_MSG);
		}

		mbEncoded = false;
	}

	return mpBuf;
}


int CDeuSQLite3Binary::getBinaryLength()
{
	getBinary();
	return mnBinaryLen;
}


unsigned char* CDeuSQLite3Binary::allocBuffer(int nLen)
{
	clear();

	// Allow extra space for encoded binary as per comments in
	// SQLite encode.c See bottom of this file for implementation
	// of SQLite functions use 3 instead of 2 just to be sure ;-)
	mnBinaryLen = nLen;
	mnBufferLen = 3 + (257*nLen)/254;

	mpBuf = (unsigned char*)malloc(mnBufferLen);

	if (!mpBuf)
	{
		throw CDeuSQLite3Exception(CPPSQLITE_ERROR,
								"Cannot allocate memory",
								DONT_DELETE_MSG);
	}

	mbEncoded = false;

	return mpBuf;
}


void CDeuSQLite3Binary::clear()
{
	if (mpBuf)
	{
		mnBinaryLen = 0;
		mnBufferLen = 0;
		free(mpBuf);
		mpBuf = 0;
	}
}


////////////////////////////////////////////////////////////////////////////////

CDeuSQLite3Query::CDeuSQLite3Query()
{
	mpVM = 0;
	mbEof = true;
	mnCols = 0;
	mbOwnVM = false;
}


CDeuSQLite3Query::CDeuSQLite3Query(const CDeuSQLite3Query& rQuery)
{
	mpVM = rQuery.mpVM;
	// Only one object can own the VM
	const_cast<CDeuSQLite3Query&>(rQuery).mpVM = 0;
	mbEof = rQuery.mbEof;
	mnCols = rQuery.mnCols;
	mbOwnVM = rQuery.mbOwnVM;
}


CDeuSQLite3Query::CDeuSQLite3Query(sqlite3* pDB,
							sqlite3_stmt* pVM,
							bool bEof,
							bool bOwnVM/*=true*/)
{
	mpDB = pDB;
	mpVM = pVM;
	mbEof = bEof;
	mnCols = sqlite3_column_count(mpVM);
	mbOwnVM = bOwnVM;
}


CDeuSQLite3Query::~CDeuSQLite3Query()
{
	try
	{
		finalize();
	}
	catch (...)
	{
	}
}


CDeuSQLite3Query& CDeuSQLite3Query::operator=(const CDeuSQLite3Query& rQuery)
{
	try
	{
		finalize();
	}
	catch (...)
	{
	}
	mpVM = rQuery.mpVM;
	// Only one object can own the VM
	const_cast<CDeuSQLite3Query&>(rQuery).mpVM = 0;
	mbEof = rQuery.mbEof;
	mnCols = rQuery.mnCols;
	mbOwnVM = rQuery.mbOwnVM;
	return *this;
}


int CDeuSQLite3Query::numFields()
{
	checkVM();
	return mnCols;
}


const char* CDeuSQLite3Query::fieldValue(int nField)
{
	checkVM();

	if (nField < 0 || nField > mnCols-1)
	{
		throw CDeuSQLite3Exception(CPPSQLITE_ERROR,
								"Invalid field index requested",
								DONT_DELETE_MSG);
	}

	return (const char*)sqlite3_column_text(mpVM, nField);
}


const char* CDeuSQLite3Query::fieldValue(const char* szField)
{
	int nField = fieldIndex(szField);
	return (const char*)sqlite3_column_text(mpVM, nField);
}


int CDeuSQLite3Query::getIntField(int nField, int nNullValue/*=0*/)
{
	if (fieldDataType(nField) == SQLITE_NULL)
	{
		return nNullValue;
	}
	else
	{
		return sqlite3_column_int(mpVM, nField);
	}
}


int CDeuSQLite3Query::getIntField(const char* szField, int nNullValue/*=0*/)
{
	int nField = fieldIndex(szField);
	return getIntField(nField, nNullValue);
}


double CDeuSQLite3Query::getFloatField(int nField, double fNullValue/*=0.0*/)
{
	if (fieldDataType(nField) == SQLITE_NULL)
	{
		return fNullValue;
	}
	else
	{
		return sqlite3_column_double(mpVM, nField);
	}
}


double CDeuSQLite3Query::getFloatField(const char* szField, double fNullValue/*=0.0*/)
{
	int nField = fieldIndex(szField);
	return getFloatField(nField, fNullValue);
}


const char* CDeuSQLite3Query::getStringField(int nField, const char* szNullValue/*=""*/)
{
	if (fieldDataType(nField) == SQLITE_NULL)
	{
		return szNullValue;
	}
	else
	{
		return (const char*)sqlite3_column_text(mpVM, nField);
	}
}


const char* CDeuSQLite3Query::getStringField(const char* szField, const char* szNullValue/*=""*/)
{
	int nField = fieldIndex(szField);
	return getStringField(nField, szNullValue);
}


const unsigned char* CDeuSQLite3Query::getBlobField(int nField, int& nLen)
{
	checkVM();

	if (nField < 0 || nField > mnCols-1)
	{
		throw CDeuSQLite3Exception(CPPSQLITE_ERROR,
								"Invalid field index requested",
								DONT_DELETE_MSG);
	}

	nLen = sqlite3_column_bytes(mpVM, nField);
	return (const unsigned char*)sqlite3_column_blob(mpVM, nField);
}


const unsigned char* CDeuSQLite3Query::getBlobField(const char* szField, int& nLen)
{
	int nField = fieldIndex(szField);
	return getBlobField(nField, nLen);
}


bool CDeuSQLite3Query::fieldIsNull(int nField)
{
	return (fieldDataType(nField) == SQLITE_NULL);
}


bool CDeuSQLite3Query::fieldIsNull(const char* szField)
{
	int nField = fieldIndex(szField);
	return (fieldDataType(nField) == SQLITE_NULL);
}


int CDeuSQLite3Query::fieldIndex(const char* szField)
{
	checkVM();

	if (szField)
	{
		for (int nField = 0; nField < mnCols; nField++)
		{
			const char* szTemp = sqlite3_column_name(mpVM, nField);

			if (strcmp(szField, szTemp) == 0)
			{
				return nField;
			}
		}
	}

	throw CDeuSQLite3Exception(CPPSQLITE_ERROR,
							"Invalid field name requested",
							DONT_DELETE_MSG);
}


const char* CDeuSQLite3Query::fieldName(int nCol)
{
	checkVM();

	if (nCol < 0 || nCol > mnCols-1)
	{
		throw CDeuSQLite3Exception(CPPSQLITE_ERROR,
								"Invalid field index requested",
								DONT_DELETE_MSG);
	}

	return sqlite3_column_name(mpVM, nCol);
}


const char* CDeuSQLite3Query::fieldDeclType(int nCol)
{
	checkVM();

	if (nCol < 0 || nCol > mnCols-1)
	{
		throw CDeuSQLite3Exception(CPPSQLITE_ERROR,
								"Invalid field index requested",
								DONT_DELETE_MSG);
	}

	return sqlite3_column_decltype(mpVM, nCol);
}


int CDeuSQLite3Query::fieldDataType(int nCol)
{
	checkVM();

	if (nCol < 0 || nCol > mnCols-1)
	{
		throw CDeuSQLite3Exception(CPPSQLITE_ERROR,
								"Invalid field index requested",
								DONT_DELETE_MSG);
	}

	return sqlite3_column_type(mpVM, nCol);
}


bool CDeuSQLite3Query::eof()
{
	checkVM();
	return mbEof;
}


void CDeuSQLite3Query::nextRow()
{
	checkVM();

	int nRet = sqlite3_step(mpVM);

	if (nRet == SQLITE_DONE)
	{
		// no rows
		mbEof = true;
	}
	else if (nRet == SQLITE_ROW)
	{
		// more rows, nothing to do
	}
	else
	{
		nRet = sqlite3_finalize(mpVM);
		mpVM = 0;
		const char* szError = sqlite3_errmsg(mpDB);
		throw CDeuSQLite3Exception(nRet,
								(char*)szError,
								DONT_DELETE_MSG);
	}
}


void CDeuSQLite3Query::finalize()
{
	if (mpVM && mbOwnVM)
	{
		int nRet = sqlite3_finalize(mpVM);
		mpVM = 0;
		if (nRet != SQLITE_OK)
		{
			const char* szError = sqlite3_errmsg(mpDB);
			throw CDeuSQLite3Exception(nRet, (char*)szError, DONT_DELETE_MSG);
		}
	}
}


void CDeuSQLite3Query::checkVM()
{
	if (mpVM == 0)
	{
		throw CDeuSQLite3Exception(CPPSQLITE_ERROR,
								"Null Virtual Machine pointer",
								DONT_DELETE_MSG);
	}
}


////////////////////////////////////////////////////////////////////////////////

CDeuSQLite3Table::CDeuSQLite3Table()
{
	mpaszResults = 0;
	mnRows = 0;
	mnCols = 0;
	mnCurrentRow = 0;
}


CDeuSQLite3Table::CDeuSQLite3Table(const CDeuSQLite3Table& rTable)
{
	mpaszResults = rTable.mpaszResults;
	// Only one object can own the results
	const_cast<CDeuSQLite3Table&>(rTable).mpaszResults = 0;
	mnRows = rTable.mnRows;
	mnCols = rTable.mnCols;
	mnCurrentRow = rTable.mnCurrentRow;
}


CDeuSQLite3Table::CDeuSQLite3Table(char** paszResults, int nRows, int nCols)
{
	mpaszResults = paszResults;
	mnRows = nRows;
	mnCols = nCols;
	mnCurrentRow = 0;
}


CDeuSQLite3Table::~CDeuSQLite3Table()
{
	try
	{
		finalize();
	}
	catch (...)
	{
	}
}


CDeuSQLite3Table& CDeuSQLite3Table::operator=(const CDeuSQLite3Table& rTable)
{
	try
	{
		finalize();
	}
	catch (...)
	{
	}
	mpaszResults = rTable.mpaszResults;
	// Only one object can own the results
	const_cast<CDeuSQLite3Table&>(rTable).mpaszResults = 0;
	mnRows = rTable.mnRows;
	mnCols = rTable.mnCols;
	mnCurrentRow = rTable.mnCurrentRow;
	return *this;
}


void CDeuSQLite3Table::finalize()
{
	if (mpaszResults)
	{
		sqlite3_free_table(mpaszResults);
		mpaszResults = 0;
	}
}


int CDeuSQLite3Table::numFields()
{
	checkResults();
	return mnCols;
}


int CDeuSQLite3Table::numRows()
{
	checkResults();
	return mnRows;
}


const char* CDeuSQLite3Table::fieldValue(int nField)
{
	checkResults();

	if (nField < 0 || nField > mnCols-1)
	{
		throw CDeuSQLite3Exception(CPPSQLITE_ERROR,
								"Invalid field index requested",
								DONT_DELETE_MSG);
	}

	int nIndex = (mnCurrentRow*mnCols) + mnCols + nField;
	return mpaszResults[nIndex];
}


const char* CDeuSQLite3Table::fieldValue(const char* szField)
{
	checkResults();

	if (szField)
	{
		for (int nField = 0; nField < mnCols; nField++)
		{
			if (strcmp(szField, mpaszResults[nField]) == 0)
			{
				int nIndex = (mnCurrentRow*mnCols) + mnCols + nField;
				return mpaszResults[nIndex];
			}
		}
	}

	throw CDeuSQLite3Exception(CPPSQLITE_ERROR,
							"Invalid field name requested",
							DONT_DELETE_MSG);
}


int CDeuSQLite3Table::getIntField(int nField, int nNullValue/*=0*/)
{
	if (fieldIsNull(nField))
	{
		return nNullValue;
	}
	else
	{
		return atoi(fieldValue(nField));
	}
}


int CDeuSQLite3Table::getIntField(const char* szField, int nNullValue/*=0*/)
{
	if (fieldIsNull(szField))
	{
		return nNullValue;
	}
	else
	{
		return atoi(fieldValue(szField));
	}
}


double CDeuSQLite3Table::getFloatField(int nField, double fNullValue/*=0.0*/)
{
	if (fieldIsNull(nField))
	{
		return fNullValue;
	}
	else
	{
		return atof(fieldValue(nField));
	}
}


double CDeuSQLite3Table::getFloatField(const char* szField, double fNullValue/*=0.0*/)
{
	if (fieldIsNull(szField))
	{
		return fNullValue;
	}
	else
	{
		return atof(fieldValue(szField));
	}
}


const char* CDeuSQLite3Table::getStringField(int nField, const char* szNullValue/*=""*/)
{
	if (fieldIsNull(nField))
	{
		return szNullValue;
	}
	else
	{
		return fieldValue(nField);
	}
}


const char* CDeuSQLite3Table::getStringField(const char* szField, const char* szNullValue/*=""*/)
{
	if (fieldIsNull(szField))
	{
		return szNullValue;
	}
	else
	{
		return fieldValue(szField);
	}
}


bool CDeuSQLite3Table::fieldIsNull(int nField)
{
	checkResults();
	return (fieldValue(nField) == 0);
}


bool CDeuSQLite3Table::fieldIsNull(const char* szField)
{
	checkResults();
	return (fieldValue(szField) == 0);
}


const char* CDeuSQLite3Table::fieldName(int nCol)
{
	checkResults();

	if (nCol < 0 || nCol > mnCols-1)
	{
		throw CDeuSQLite3Exception(CPPSQLITE_ERROR,
								"Invalid field index requested",
								DONT_DELETE_MSG);
	}

	return mpaszResults[nCol];
}


void CDeuSQLite3Table::setRow(int nRow)
{
	checkResults();

	if (nRow < 0 || nRow > mnRows-1)
	{
		throw CDeuSQLite3Exception(CPPSQLITE_ERROR,
								"Invalid row index requested",
								DONT_DELETE_MSG);
	}

	mnCurrentRow = nRow;
}


void CDeuSQLite3Table::checkResults()
{
	if (mpaszResults == 0)
	{
		throw CDeuSQLite3Exception(CPPSQLITE_ERROR,
								"Null Results pointer",
								DONT_DELETE_MSG);
	}
}


////////////////////////////////////////////////////////////////////////////////

CDeuSQLite3Statement::CDeuSQLite3Statement()
{
	mpDB = 0;
	mpVM = 0;
}


CDeuSQLite3Statement::CDeuSQLite3Statement(const CDeuSQLite3Statement& rStatement)
{
	mpDB = rStatement.mpDB;
	mpVM = rStatement.mpVM;
	// Only one object can own VM
	const_cast<CDeuSQLite3Statement&>(rStatement).mpVM = 0;
}


CDeuSQLite3Statement::CDeuSQLite3Statement(sqlite3* pDB, sqlite3_stmt* pVM)
{
	mpDB = pDB;
	mpVM = pVM;
}


CDeuSQLite3Statement::~CDeuSQLite3Statement()
{
	try
	{
		finalize();
	}
	catch (...)
	{
	}
}


CDeuSQLite3Statement& CDeuSQLite3Statement::operator=(const CDeuSQLite3Statement& rStatement)
{
	mpDB = rStatement.mpDB;
	mpVM = rStatement.mpVM;
	// Only one object can own VM
	const_cast<CDeuSQLite3Statement&>(rStatement).mpVM = 0;
	return *this;
}


int CDeuSQLite3Statement::execDML()
{
	checkDB();
	checkVM();

	const char* szError=0;

	int nRet = sqlite3_step(mpVM);

	if (nRet == SQLITE_DONE)
	{
		int nRowsChanged = sqlite3_changes(mpDB);

		nRet = sqlite3_reset(mpVM);

		if (nRet != SQLITE_OK)
		{
			szError = sqlite3_errmsg(mpDB);
			throw CDeuSQLite3Exception(nRet, (char*)szError, DONT_DELETE_MSG);
		}

		return nRowsChanged;
	}
	else
	{
		nRet = sqlite3_reset(mpVM);
		szError = sqlite3_errmsg(mpDB);
		throw CDeuSQLite3Exception(nRet, (char*)szError, DONT_DELETE_MSG);
	}
}


CDeuSQLite3Query CDeuSQLite3Statement::execQuery()
{
	checkDB();
	checkVM();

	int nRet = sqlite3_step(mpVM);

	if (nRet == SQLITE_DONE)
	{
		// no rows
		return CDeuSQLite3Query(mpDB, mpVM, true/*eof*/, false);
	}
	else if (nRet == SQLITE_ROW)
	{
		// at least 1 row
		return CDeuSQLite3Query(mpDB, mpVM, false/*eof*/, false);
	}
	else
	{
		nRet = sqlite3_reset(mpVM);
		const char* szError = sqlite3_errmsg(mpDB);
		throw CDeuSQLite3Exception(nRet, (char*)szError, DONT_DELETE_MSG);
	}
}


void CDeuSQLite3Statement::bind(int nParam, const char* szValue)
{
	checkVM();
	int nRes = sqlite3_bind_text(mpVM, nParam, szValue, -1, SQLITE_TRANSIENT);

	if (nRes != SQLITE_OK)
	{
		throw CDeuSQLite3Exception(nRes,
								"Error binding string param",
								DONT_DELETE_MSG);
	}
}


void CDeuSQLite3Statement::bind(int nParam, const int nValue)
{
	checkVM();
	int nRes = sqlite3_bind_int(mpVM, nParam, nValue);

	if (nRes != SQLITE_OK)
	{
		throw CDeuSQLite3Exception(nRes,
								"Error binding int param",
								DONT_DELETE_MSG);
	}
}


void CDeuSQLite3Statement::bind(int nParam, const double dValue)
{
	checkVM();
	int nRes = sqlite3_bind_double(mpVM, nParam, dValue);

	if (nRes != SQLITE_OK)
	{
		throw CDeuSQLite3Exception(nRes,
								"Error binding double param",
								DONT_DELETE_MSG);
	}
}


void CDeuSQLite3Statement::bind(int nParam, const unsigned char* blobValue, int nLen)
{
	checkVM();
	int nRes = sqlite3_bind_blob(mpVM, nParam,
								(const void*)blobValue, nLen, SQLITE_TRANSIENT);

	if (nRes != SQLITE_OK)
	{
		throw CDeuSQLite3Exception(nRes,
								"Error binding blob param",
								DONT_DELETE_MSG);
	}
}

	
void CDeuSQLite3Statement::bindNull(int nParam)
{
	checkVM();
	int nRes = sqlite3_bind_null(mpVM, nParam);

	if (nRes != SQLITE_OK)
	{
		throw CDeuSQLite3Exception(nRes,
								"Error binding NULL param",
								DONT_DELETE_MSG);
	}
}


void CDeuSQLite3Statement::reset()
{
	if (mpVM)
	{
		int nRet = sqlite3_reset(mpVM);

		if (nRet != SQLITE_OK)
		{
			const char* szError = sqlite3_errmsg(mpDB);
			throw CDeuSQLite3Exception(nRet, (char*)szError, DONT_DELETE_MSG);
		}
	}
}


void CDeuSQLite3Statement::finalize()
{
	if (mpVM)
	{
		int nRet = sqlite3_finalize(mpVM);
		mpVM = 0;

		if (nRet != SQLITE_OK)
		{
			const char* szError = sqlite3_errmsg(mpDB);
			throw CDeuSQLite3Exception(nRet, (char*)szError, DONT_DELETE_MSG);
		}
	}
}


void CDeuSQLite3Statement::checkDB()
{
	if (mpDB == 0)
	{
		throw CDeuSQLite3Exception(CPPSQLITE_ERROR,
								"Database not open",
								DONT_DELETE_MSG);
	}
}


void CDeuSQLite3Statement::checkVM()
{
	if (mpVM == 0)
	{
		throw CDeuSQLite3Exception(CPPSQLITE_ERROR,
								"Null Virtual Machine pointer",
								DONT_DELETE_MSG);
	}
}


////////////////////////////////////////////////////////////////////////////////

CDeuSQLite3DB::CDeuSQLite3DB()
{
	mpDB = 0;
	mnBusyTimeoutMs = 60000; // 60 seconds
}


CDeuSQLite3DB::CDeuSQLite3DB(const CDeuSQLite3DB& db)
{
	mpDB = db.mpDB;
	mnBusyTimeoutMs = 60000; // 60 seconds
}


CDeuSQLite3DB::~CDeuSQLite3DB()
{
	close();
}


CDeuSQLite3DB& CDeuSQLite3DB::operator=(const CDeuSQLite3DB& db)
{
	mpDB = db.mpDB;
	mnBusyTimeoutMs = 60000; // 60 seconds
	return *this;
}


void CDeuSQLite3DB::open(const char* szFile, char* encrypt)
{
	int nRet = sqlite3_open(szFile, &mpDB);

	if (nRet != SQLITE_OK)
	{
		const char* szError = sqlite3_errmsg(mpDB);
		throw CDeuSQLite3Exception(nRet, (char*)szError, DONT_DELETE_MSG);
	}
	else
	{	
		sqlite3_key(mpDB, encrypt, sizeof(encrypt));
	}
	
	setBusyTimeout(mnBusyTimeoutMs);
}


void CDeuSQLite3DB::close()
{
	if (mpDB)
	{
		sqlite3_close(mpDB);
		mpDB = 0;
	}
}


CDeuSQLite3Statement CDeuSQLite3DB::compileStatement(const char* szSQL)
{
	checkDB();

	sqlite3_stmt* pVM = compile(szSQL);
	return CDeuSQLite3Statement(mpDB, pVM);
}


bool CDeuSQLite3DB::tableExists(const char* szTable)
{
	char szSQL[128];
	sprintf(szSQL,
			"select count(*) from sqlite_master where type='table' and name='%s'",
			szTable);
	int nRet = execScalar(szSQL);
	return (nRet > 0);
}


int CDeuSQLite3DB::execDML(const char* szSQL)
{
	checkDB();

	char* szError=0;

	int nRet = sqlite3_exec(mpDB, szSQL, 0, 0, &szError);

	if (nRet == SQLITE_OK)
	{
		return sqlite3_changes(mpDB);
	}
	else
	{
		throw CDeuSQLite3Exception(nRet, szError);
	}
}


CDeuSQLite3Query CDeuSQLite3DB::execQuery(const char* szSQL)
{
	checkDB();

	sqlite3_stmt* pVM = compile(szSQL);

	int nRet = sqlite3_step(pVM);

	if (nRet == SQLITE_DONE)
	{
		// no rows
		return CDeuSQLite3Query(mpDB, pVM, true/*eof*/);
	}
	else if (nRet == SQLITE_ROW)
	{
		// at least 1 row
		return CDeuSQLite3Query(mpDB, pVM, false/*eof*/);
	}
	else
	{
		nRet = sqlite3_finalize(pVM);
		const char* szError= sqlite3_errmsg(mpDB);
		throw CDeuSQLite3Exception(nRet, (char*)szError, DONT_DELETE_MSG);
	}
}


int CDeuSQLite3DB::execScalar(const char* szSQL)
{
	CDeuSQLite3Query q = execQuery(szSQL);

	if (q.eof() || q.numFields() < 1)
	{
		throw CDeuSQLite3Exception(CPPSQLITE_ERROR,
								"Invalid scalar query",
								DONT_DELETE_MSG);
	}

	return atoi(q.fieldValue(0));
}


CDeuSQLite3Table CDeuSQLite3DB::getTable(const char* szSQL)
{
	checkDB();

	char* szError=0;
	char** paszResults=0;
	int nRet;
	int nRows(0);
	int nCols(0);

	nRet = sqlite3_get_table(mpDB, szSQL, &paszResults, &nRows, &nCols, &szError);

	if (nRet == SQLITE_OK)
	{
		return CDeuSQLite3Table(paszResults, nRows, nCols);
	}
	else
	{
		throw CDeuSQLite3Exception(nRet, szError);
	}
}


sqlite_int64 CDeuSQLite3DB::lastRowId()
{
	return sqlite3_last_insert_rowid(mpDB);
}


void CDeuSQLite3DB::setBusyTimeout(int nMillisecs)
{
	mnBusyTimeoutMs = nMillisecs;
	sqlite3_busy_timeout(mpDB, mnBusyTimeoutMs);
}


void CDeuSQLite3DB::checkDB()
{
	if (!mpDB)
	{
		throw CDeuSQLite3Exception(CPPSQLITE_ERROR,
								"Database not open",
								DONT_DELETE_MSG);
	}
}


sqlite3_stmt* CDeuSQLite3DB::compile(const char* szSQL)
{
	checkDB();

	char* szError=0;
	const char* szTail=0;
	sqlite3_stmt* pVM;

	int nRet = sqlite3_prepare(mpDB, szSQL, -1, &pVM, &szTail);

	if (nRet != SQLITE_OK)
	{
		throw CDeuSQLite3Exception(nRet, szError);
	}

	return pVM;
}


////////////////////////////////////////////////////////////////////////////////
// SQLite encode.c reproduced here, containing implementation notes and source
// for sqlite3_encode_binary() and sqlite3_decode_binary() 
////////////////////////////////////////////////////////////////////////////////

/*
** 2002 April 25
**
** The author disclaims copyright to this source code.  In place of
** a legal notice, here is a blessing:
**
**    May you do good and not evil.
**    May you find forgiveness for yourself and forgive others.
**    May you share freely, never taking more than you give.
**
*************************************************************************
** This file contains helper routines used to translate binary data into
** a null-terminated string (suitable for use in SQLite) and back again.
** These are convenience routines for use by people who want to store binary
** data in an SQLite database.  The code in this file is not used by any other
** part of the SQLite library.
**
** $Id: encode.c,v 1.10 2004/01/14 21:59:23 drh Exp $
*/

/*
** How This Encoder Works
**
** The output is allowed to contain any character except 0x27 (') and
** 0x00.  This is accomplished by using an escape character to encode
** 0x27 and 0x00 as a two-byte sequence.  The escape character is always
** 0x01.  An 0x00 is encoded as the two byte sequence 0x01 0x01.  The
** 0x27 character is encoded as the two byte sequence 0x01 0x03.  Finally,
** the escape character itself is encoded as the two-character sequence
** 0x01 0x02.
**
** To summarize, the encoder works by using an escape sequences as follows:
**
**       0x00  ->  0x01 0x01
**       0x01  ->  0x01 0x02
**       0x27  ->  0x01 0x03
**
** If that were all the encoder did, it would work, but in certain cases
** it could double the size of the encoded string.  For example, to
** encode a string of 100 0x27 characters would require 100 instances of
** the 0x01 0x03 escape sequence resulting in a 200-character output.
** We would prefer to keep the size of the encoded string smaller than
** this.
**
** To minimize the encoding size, we first add a fixed offset value to each 
** byte in the sequence.  The addition is modulo 256.  (That is to say, if
** the sum of the original character value and the offset exceeds 256, then
** the higher order bits are truncated.)  The offset is chosen to minimize
** the number of characters in the string that need to be escaped.  For
** example, in the case above where the string was composed of 100 0x27
** characters, the offset might be 0x01.  Each of the 0x27 characters would
** then be converted into an 0x28 character which would not need to be
** escaped at all and so the 100 character input string would be converted
** into just 100 characters of output.  Actually 101 characters of output - 
** we have to record the offset used as the first byte in the sequence so
** that the string can be decoded.  Since the offset value is stored as
** part of the output string and the output string is not allowed to contain
** characters 0x00 or 0x27, the offset cannot be 0x00 or 0x27.
**
** Here, then, are the encoding steps:
**
**     (1)   Choose an offset value and make it the first character of
**           output.
**
**     (2)   Copy each input character into the output buffer, one by
**           one, adding the offset value as you copy.
**
**     (3)   If the value of an input character plus offset is 0x00, replace
**           that one character by the two-character sequence 0x01 0x01.
**           If the sum is 0x01, replace it with 0x01 0x02.  If the sum
**           is 0x27, replace it with 0x01 0x03.
**
**     (4)   Put a 0x00 terminator at the end of the output.
**
** Decoding is obvious:
**
**     (5)   Copy encoded characters except the first into the decode 
**           buffer.  Set the first encoded character aside for use as
**           the offset in step 7 below.
**
**     (6)   Convert each 0x01 0x01 sequence into a single character 0x00.
**           Convert 0x01 0x02 into 0x01.  Convert 0x01 0x03 into 0x27.
**
**     (7)   Subtract the offset value that was the first character of
**           the encoded buffer from all characters in the output buffer.
**
** The only tricky part is step (1) - how to compute an offset value to
** minimize the size of the output buffer.  This is accomplished by testing
** all offset values and picking the one that results in the fewest number
** of escapes.  To do that, we first scan the entire input and count the
** number of occurances of each character value in the input.  Suppose
** the number of 0x00 characters is N(0), the number of occurances of 0x01
** is N(1), and so forth up to the number of occurances of 0xff is N(255).
** An offset of 0 is not allowed so we don't have to test it.  The number
** of escapes required for an offset of 1 is N(1)+N(2)+N(40).  The number
** of escapes required for an offset of 2 is N(2)+N(3)+N(41).  And so forth.
** In this way we find the offset that gives the minimum number of escapes,
** and thus minimizes the length of the output string.
*/

/*
** Encode a binary buffer "in" of size n bytes so that it contains
** no instances of characters '\'' or '\000'.  The output is 
** null-terminated and can be used as a string value in an INSERT
** or UPDATE statement.  Use sqlite3_decode_binary() to convert the
** string back into its original binary.
**
** The result is written into a preallocated output buffer "out".
** "out" must be able to hold at least 2 +(257*n)/254 bytes.
** In other words, the output will be expanded by as much as 3
** bytes for every 254 bytes of input plus 2 bytes of fixed overhead.
** (This is approximately 2 + 1.0118*n or about a 1.2% size increase.)
**
** The return value is the number of characters in the encoded
** string, excluding the "\000" terminator.
*/
int sqlite3_encode_binary(const unsigned char *in, int n, unsigned char *out){
  int i, j, e, m;
  int cnt[256];
  if( n<=0 ){
    out[0] = 'x';
    out[1] = 0;
    return 1;
  }
  memset(cnt, 0, sizeof(cnt));
  for(i=n-1; i>=0; i--){ cnt[in[i]]++; }
  m = n;
  for(i=1; i<256; i++){
    int sum;
    if( i=='\'' ) continue;
    sum = cnt[i] + cnt[(i+1)&0xff] + cnt[(i+'\'')&0xff];
    if( sum<m ){
      m = sum;
      e = i;
      if( m==0 ) break;
    }
  }
  out[0] = e;
  j = 1;
  for(i=0; i<n; i++){
    int c = (in[i] - e)&0xff;
    if( c==0 ){
      out[j++] = 1;
      out[j++] = 1;
    }else if( c==1 ){
      out[j++] = 1;
      out[j++] = 2;
    }else if( c=='\'' ){
      out[j++] = 1;
      out[j++] = 3;
    }else{
      out[j++] = c;
    }
  }
  out[j] = 0;
  return j;
}

/*
** Decode the string "in" into binary data and write it into "out".
** This routine reverses the encoding created by sqlite3_encode_binary().
** The output will always be a few bytes less than the input.  The number
** of bytes of output is returned.  If the input is not a well-formed
** encoding, -1 is returned.
**
** The "in" and "out" parameters may point to the same buffer in order
** to decode a string in place.
*/
int sqlite3_decode_binary(const unsigned char *in, unsigned char *out){
  int i, c, e;
  e = *(in++);
  i = 0;
  while( (c = *(in++))!=0 ){
    if( c==1 ){
      c = *(in++);
      if( c==1 ){
        c = 0;
      }else if( c==2 ){
        c = 1;
      }else if( c==3 ){
        c = '\'';
      }else{
        return -1;
      }
    }
    out[i++] = (c + e)&0xff;
  }
  return i;
}
