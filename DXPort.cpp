// DXPort.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "DXPort.h"
#include "DXPortDlg.h"
#include "CommandLine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDXPortApp

BEGIN_MESSAGE_MAP(CDXPortApp, CWinApp)
	//{{AFX_MSG_MAP(CDXPortApp)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDXPortApp construction

CDXPortApp::CDXPortApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CDXPortApp object

CDXPortApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CDXPortApp initialization

BOOL CDXPortApp::InitInstance()
{
//#define ALLOW_MULTI
#ifndef ALLOW_MULTI
   if ( !LockApp() )
   {
      AfxMessageBox( "DXPort is already running" );
      return FALSE;
   }
#endif
   
   if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
      ReleaseApp();
		return FALSE;
	}

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CDXPortDlg dlg;

   // get the command line
   cCommandLine CmdLine;

   ParseCommandLine( CmdLine );

   char FileName[2048];
   char drive[128];
   char dir[2048];
   char fname[256];

   GetModuleFileName( AfxGetInstanceHandle(), &FileName[0], sizeof(FileName) );

   _splitpath( FileName, &drive[0], &dir[0], &fname[0], NULL );

   CString strDXPortIni = drive;
   strDXPortIni += dir;
   strDXPortIni += "DXPort.ini";
   
   if ( CmdLine.GetParam(0) == "" & CmdLine.GetParam(1) == "" )
   {
      int iPort = GetPrivateProfileInt( "SETTINGS", "StartPort", 0, strDXPortIni );

      CString strPort;

      if ( iPort > 0 )
         strPort.Format( "%i", iPort );
      else
         strPort = "";

      dlg.SetStartPort( strPort );

      iPort = GetPrivateProfileInt( "SETTINGS", "EndPort", 0, strDXPortIni );

      if ( iPort > 0 )
         strPort.Format( "%i", iPort );
      else
         strPort = "";

      dlg.SetEndPort( strPort );
   }
   else
   {
      dlg.SetStartPort( CmdLine.GetParam(0) );
      dlg.SetEndPort( CmdLine.GetParam(1) );
   }

   dlg.Create( IDD_DXPORT_DIALOG );

	m_pMainWnd = &dlg;

   if ( !CmdLine.GetMinimized() && !GetPrivateProfileInt("SETTINGS", "RunMinimized", 0, strDXPortIni) )
   {
      CMenu *pMenu = dlg.GetMenu();

      pMenu->CheckMenuItem( ID_APP_START_MINIMIZED, MF_UNCHECKED );

      dlg.ShowWindow( SW_SHOW );
      dlg.UpdateWindow();
   }

   MSG msg;
   BOOL bRet; 

   while( (bRet = GetMessage( &msg, NULL, 0, 0 )) != 0)
    { 
        if (bRet == -1)
        {
            // handle the error and possibly exit
        }
        else
        {
            TranslateMessage(&msg); 
            DispatchMessage(&msg); 
        }
    } 

   /*
   int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
   */

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
#ifndef ALLOW_MULTI
   ReleaseApp();
#endif

	return FALSE;
}

BOOL CDXPortApp::LockApp()
{
   m_hDXPortInstance = CreateMutex( NULL, FALSE, "DXPortInstance" );

   if ( WaitForSingleObject(m_hDXPortInstance, 500) != WAIT_OBJECT_0 )
      return FALSE;

   return TRUE;
}

void CDXPortApp::ReleaseApp()
{
   ReleaseMutex( m_hDXPortInstance );
}

