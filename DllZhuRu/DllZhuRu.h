// DllZhuRu.h : main header file for the DLLZHURU application
//

#if !defined(AFX_DLLZHURU_H__CB53F186_5123_43C3_911E_02D2DBF880B7__INCLUDED_)
#define AFX_DLLZHURU_H__CB53F186_5123_43C3_911E_02D2DBF880B7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDllZhuRuApp:
// See DllZhuRu.cpp for the implementation of this class
//

class CDllZhuRuApp : public CWinApp
{
public:
	CDllZhuRuApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDllZhuRuApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDllZhuRuApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLLZHURU_H__CB53F186_5123_43C3_911E_02D2DBF880B7__INCLUDED_)
