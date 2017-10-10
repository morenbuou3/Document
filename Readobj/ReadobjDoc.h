// ReadobjDoc.h : interface of the CReadobjDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_READOBJDOC_H__6217F43A_F88E_41F4_8AC1_76F18B7A20C8__INCLUDED_)
#define AFX_READOBJDOC_H__6217F43A_F88E_41F4_8AC1_76F18B7A20C8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include"mystruct.h"
#include"facestruct.h"
//#include "fstream.h"
#include <fstream> 
using namespace std;


class CReadobjDoc : public CDocument
{
protected: // create from serialization only
	CReadobjDoc();
	DECLARE_DYNCREATE(CReadobjDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReadobjDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	int f_num;
	int N_num;
	virtual ~CReadobjDoc();
	int num;
	void getNum(const char  *OBJFileName);
	int Readobjfile(const char  *OBJFileName);
	PTNODE *mpot;
	PTNODE *npot;
	FNODE *fpot;
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CReadobjDoc)
	afx_msg void OnFileOpen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_READOBJDOC_H__6217F43A_F88E_41F4_8AC1_76F18B7A20C8__INCLUDED_)
