#ifndef __RESULTS_H__
#define __RESULTS_H__

#include "SimHash.h"

/////////////////////////////////////////////////////////////////////////////
// CResults
/* This class collects results of binary string matches on one file at a time.
It serves as a base class for any results-storage medium we care to implement.
OpenStore() would open the output file (db table, CSV file, etc).  NewFile()
starts a new "row" in the output and resets sum counts to zero.  IncrTag()
increments the indicated tag count on the current file.
The default implementation of this class writes results to console.
*/

class CResults
{
public:
	CResults(int nTags);
	~CResults();

	virtual bool OpenStore(char* szName) { return true; }
	virtual bool CommitStore() { return true; }

	virtual void NewFile(char* szFile);
	virtual void CloseFile();
	virtual void IncrTag(int nTag);

protected:
	int ComputeHashKey(CTags* pTags);
	void FormatRowBufferTxt();
	static void ExtractFilename(char* szPath, char* szFile);

	char   m_szStoreName[MAX_PATH];
	char   m_szFileName[MAX_PATH];

	int    m_nTags;
	DWORD* m_pnSumTable;
	char*  m_szRowBuffer;  // for writing text-formatted data
};


/////////////////////////////////////////////////////////////////////////////
// CResultsSQL
/* This derivation of CResults dumps the results into a SQL table
CAITLIN: Fill in these functions
*/

class CResultsSQL : public CResults
{
public:
	CResultsSQL(int nTags);
	~CResultsSQL();

	bool OpenStore(char* szName);
	bool CommitStore();
	void NewFile(char* szFile);
	void CloseFile();

protected:
	// TODO: db info
};


/////////////////////////////////////////////////////////////////////////////
// CResultsCSV
/* This derivation of CResults dumps the results into a CSV file
*/

class CResultsCSV : public CResults
{
public:
	CResultsCSV(int nTags);
	~CResultsCSV();

	bool OpenStore(char* szName);
	bool CommitStore();
	void CloseFile();

protected:
	FILE* m_fp;
};



#endif // __RESULTS_H__
