// DXPort.h : main header file for the DXPORT application
//

#if !defined(AFX_DXPORT_H__C3B378F8_6D94_418E_810B_761DF5AE1CB8__INCLUDED_)
#define AFX_DXPORT_H__C3B378F8_6D94_418E_810B_761DF5AE1CB8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDXPortApp:
// See DXPort.cpp for the implementation of this class
//

class CDXPortApp : public CWinApp
{
public:
	CDXPortApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDXPortApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDXPortApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void ReleaseApp();
	BOOL LockApp();
	HANDLE m_hDXPortInstance;
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DXPORT_H__C3B378F8_6D94_418E_810B_761DF5AE1CB8__INCLUDED_)
