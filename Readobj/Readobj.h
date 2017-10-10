// Readobj.h : main header file for the READOBJ application
//

#if !defined(AFX_READOBJ_H__92E2C5E6_C70B_4336_9A32_267CA1D1C263__INCLUDED_)
#define AFX_READOBJ_H__92E2C5E6_C70B_4336_9A32_267CA1D1C263__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CReadobjApp:
// See Readobj.cpp for the implementation of this class
//

class CReadobjApp : public CWinApp
{
public:
	CReadobjApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReadobjApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CReadobjApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_READOBJ_H__92E2C5E6_C70B_4336_9A32_267CA1D1C263__INCLUDED_)
