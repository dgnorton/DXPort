// DXPortDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DXPort.h"
#include "DXPortDlg.h"
//#include "ServerSocket.h"
#include "NetworkPortController.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
   CAboutDlg();

// Dialog Data
   //{{AFX_DATA(CAboutDlg)
   enum { IDD = IDD_ABOUTBOX };
   //}}AFX_DATA

   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CAboutDlg)
   protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:
   //{{AFX_MSG(CAboutDlg)
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
   //{{AFX_DATA_INIT(CAboutDlg)
   //}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CAboutDlg)
   //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
   //{{AFX_MSG_MAP(CAboutDlg)
      // No message handlers
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDXPortDlg dialog

CDXPortDlg::CDXPortDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDXPortDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDXPortDlg)
	m_StartPort = _T("");
	m_EndPort = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	
   m_hIcon = AfxGetApp()->LoadIcon(IDI_DXPMAIN);
   m_nLowestPort = 2300;
   m_nHighestPort = 2400;
   
}

void CDXPortDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDXPortDlg)
	DDX_Control(pDX, IDC_STARTPORT, m_edtStartPort);
	DDX_Control(pDX, IDC_ENDPORT, m_edtEndPort);
	DDX_Control(pDX, IDC_DISPLAY, m_Display);
	DDX_Text(pDX, IDC_STARTPORT, m_StartPort);
	DDV_MaxChars(pDX, m_StartPort, 4);
	DDX_Text(pDX, IDC_ENDPORT, m_EndPort);
	DDV_MaxChars(pDX, m_EndPort, 4);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDXPortDlg, CDialog)
	//{{AFX_MSG_MAP(CDXPortDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_UPDATE, OnUpdate)
	ON_COMMAND(ID_HELP_ABOUT, OnHelpAbout)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_COMMAND(ID_APP_EXIT, OnAppExit)
	ON_COMMAND(ID_APP_HIDE, OnAppHide)
	ON_COMMAND(ID_APP_SHOW, OnAppShow)
	ON_COMMAND(ID_RANGE1, OnRange1)
	ON_COMMAND(ID_RANGE2, OnRange2)
	ON_COMMAND(ID_RANGE3, OnRange3)
	ON_COMMAND(ID_RANGE4, OnRange4)
	ON_COMMAND(ID_RANGE5, OnRange5)
	ON_COMMAND(ID_RANGE6, OnRange6)
	ON_COMMAND(ID_RANGE7, OnRange7)
	ON_COMMAND(ID_RANGE8, OnRange8)
	ON_COMMAND(ID_RANGE9, OnRange9)
	ON_COMMAND(ID_RANGE10, OnRange10)
	ON_WM_SHOWWINDOW()
	ON_COMMAND(ID_APP_START_MINIMIZED, OnAppStartMinimized)
	//}}AFX_MSG_MAP
   ON_MESSAGE(DXP_TRAYMSG, OnTrayMsg)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDXPortDlg message handlers

BOOL CDXPortDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

   char Buffer[128];

   LoadString( AfxGetApp()->m_hInstance, IDS_VERSION, (char*)&Buffer[0], sizeof(Buffer) );

   SetWindowText( Buffer );

   TaskBarIcon( NIM_ADD, 1, m_hIcon, "DXPort" );
	
	if ( m_StartPort != "" && m_EndPort == "" )
         m_EndPort = m_StartPort;

   if ( m_StartPort != "" )
   {
      m_edtStartPort.SetWindowText( m_StartPort );
      m_edtEndPort.SetWindowText( m_EndPort );
      
      OnUpdate();
   }

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDXPortDlg::OnPaint() 
{     
   if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDXPortDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void CDXPortDlg::OnUpdate() 
{
   CString Msg;
   
   UpdateData();

   m_Display.ResetContent();

   ShowHostIpAddrs();
   
   if ( m_StartPort == "" )
   {
      if ( m_EndPort == "" )
      {
         MessageBox( "At least one port must be entered" );
         return;
      }
      else
         m_StartPort = m_EndPort;
   }
   else if ( m_EndPort == "" )
      m_EndPort = m_StartPort;

   UINT iStartPort = atoi( m_StartPort );
   UINT iEndPort = atoi( m_EndPort );

   if ( iStartPort < m_nLowestPort || iStartPort > m_nHighestPort )
   {
      Msg.Format( "StartPort must be between %u and %u", m_nLowestPort, m_nHighestPort );
      MessageBox( Msg );
      return;
   }

   if ( iEndPort < m_nLowestPort || iEndPort > m_nHighestPort )
   {
      Msg.Format( "EndPort must be between %u and %u", m_nLowestPort, m_nHighestPort );
      MessageBox( Msg );
      return;
   }

   // release all ports currently open
   //CloseAllSockets();
   m_NPC.ReleaseAllPorts( cNetworkPortController::ALL );

   // if user entered ports in wrong order, swap them
   if ( iStartPort > iEndPort )
   {
      UINT iTemp = iStartPort;
      iStartPort = iEndPort;
      iEndPort = iTemp;
   }
   
   BOOL bResult = FALSE;

	for ( UINT iNewPort = m_nLowestPort; iNewPort <= m_nHighestPort; iNewPort++ )
   {      
      bResult = m_NPC.LockPort( iNewPort, cNetworkPortController::ALL );

      if ( bResult )
      {
         if ( iNewPort >= iStartPort && iNewPort <= iEndPort )
         {
            m_NPC.ReleasePort( iNewPort, cNetworkPortController::ALL );
            Msg.Format( "%i Available UDP/TCP", iNewPort );
            m_Display.AddString( Msg );
         }
         else
            Msg.Format( "%i Locked UDP/TCP", iNewPort);  
      }
      else
      {
         if ( iNewPort >= iStartPort && iNewPort <= iEndPort )
         {
            if ( !m_NPC.GetUdpResult() )
               Msg.Format( "%i %s", iNewPort, m_NPC.GetUdpResultStr() );
            else if ( !m_NPC.GetTcpResult() )
               Msg.Format( "%i %s", iNewPort, m_NPC.GetTcpResultStr() );
            else
               Msg.Format( "%i Port error", iNewPort );

            m_Display.AddString( Msg );
         }
      }
   }

   Msg = "DXPort";

   if ( m_StartPort != "" ) Msg = Msg + "  " + m_StartPort;

   if ( m_EndPort != "" )
   {
      if ( Msg == "DXPort" )
         Msg = Msg + "  " + m_EndPort;
      else
         Msg = Msg + " - " + m_EndPort;
   }

   LPCTSTR pMsg = (LPCTSTR)Msg;

   TaskBarIcon( NIM_MODIFY, 1, m_hIcon, (LPTSTR)pMsg );

   SaveSettings();
}

void CDXPortDlg::CloseAllSockets()
{
   CAsyncSocket *pSocket;

   // delete old sockets if there are any
   for ( int i = 0; i <= m_aSockets.GetUpperBound(); i++ )
   {      
      pSocket = (CAsyncSocket*) m_aSockets.GetAt(i);

      if ( pSocket > 0 ) delete pSocket;
   }

   // clear the socket pointer array
   m_aSockets.RemoveAll();
}

void CDXPortDlg::OnHelpAbout() 
{
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();	
}

void CDXPortDlg::SetStartPort(LPCTSTR lpszStartPort)
{
   if ( AfxIsValidAddress(lpszStartPort, 1, FALSE) )
      m_StartPort = lpszStartPort;
}

void CDXPortDlg::SetEndPort(LPCTSTR lpszEndPort)
{
   if ( AfxIsValidAddress(lpszEndPort, 1, FALSE) )
      m_EndPort = lpszEndPort;
}

void CDXPortDlg::OnTrayMsg(WPARAM wParam, LPARAM lParam) 
{
   CMenu TempMenu;
   CMenu *pContextMenu;
   POINT pPoint;
   
   switch ( lParam )
   {
   case WM_CONTEXTMENU:
   case WM_RBUTTONUP:
      ::GetCursorPos( &pPoint );
      //TempMenu.LoadMenu( IDR_DXPMAIN );
      //pContextMenu = TempMenu.GetSubMenu( 0 );
      pContextMenu = GetMenu()->GetSubMenu( 0 );

      UpdateMenu( *pContextMenu );

      pContextMenu->TrackPopupMenu( 0, pPoint.x, pPoint.y, this, NULL);
      break;

   case WM_LBUTTONDBLCLK:
      ShowWindow(SW_SHOW);
      break;
   }
}


// TaskBarIcon - adds/edits/deletes an icon to the taskbar status area. 
// Returns TRUE if successful, or FALSE otherwise.  
// uID - identifier of the icon. 
// hicon - handle to the icon to add. 
// lpszTip - ToolTip text. 
BOOL CDXPortDlg::TaskBarIcon(DWORD dwAction, UINT uID, HICON hicon, LPSTR lpszTip)
{
   HWND hWnd = m_hWnd;
   BOOL res; 
   NOTIFYICONDATA tnid; 
 
   tnid.cbSize = sizeof(NOTIFYICONDATA); 
   tnid.hWnd = hWnd; 
   tnid.uID = uID; 
   tnid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP; 
   tnid.uCallbackMessage = DXP_TRAYMSG; 
   tnid.hIcon = hicon; 
   if (lpszTip) 
      lstrcpyn(tnid.szTip, lpszTip, sizeof(tnid.szTip)); 
   else 
      tnid.szTip[0] = '\0'; 
 
   res = Shell_NotifyIcon(dwAction, &tnid); 
 
   if (hicon) 
      DestroyIcon(hicon); 
 
   return res;
}

void CDXPortDlg::OnClose() 
{	
	ShowWindow(SW_HIDE);
}


void CDXPortDlg::OnDestroy() 
{
	SaveSettings();
   
   TaskBarIcon( NIM_DELETE, 1, m_hIcon, "");
   
   CDialog::OnDestroy();
}

void CDXPortDlg::CloseApp()
{   
   PostMessage(WM_DESTROY);
   PostMessage(WM_QUIT);
}

void CDXPortDlg::SetPortRange(UINT nLow, UINT nHigh)
{
   m_nLowestPort = nLow;
   m_nHighestPort = nHigh;
}

void CDXPortDlg::OnAppExit() 
{
	CloseApp();
}

void CDXPortDlg::OnAppHide() 
{
	ShowWindow(SW_HIDE);
}

void CDXPortDlg::OnAppShow() 
{
	ShowWindow(SW_SHOW);
}

void CDXPortDlg::OnRange1() 
{
	m_edtStartPort.SetWindowText( "2302" );
   m_edtEndPort.SetWindowText( "2311" );

   UpdateData();

   OnUpdate();
}

void CDXPortDlg::OnRange2() 
{
	m_edtStartPort.SetWindowText( "2312" );
   m_edtEndPort.SetWindowText( "2321" );

   UpdateData();

   OnUpdate();
}

void CDXPortDlg::OnRange3() 
{
	m_edtStartPort.SetWindowText( "2322" );
   m_edtEndPort.SetWindowText( "2331" );

   UpdateData();

   OnUpdate();
}

void CDXPortDlg::OnRange4() 
{
	m_edtStartPort.SetWindowText( "2332" );
   m_edtEndPort.SetWindowText( "2341" );

   UpdateData();

   OnUpdate();
}

void CDXPortDlg::OnRange5() 
{
	m_edtStartPort.SetWindowText( "2342" );
   m_edtEndPort.SetWindowText( "2351" );

   UpdateData();

   OnUpdate();
}

void CDXPortDlg::OnRange6() 
{
	m_edtStartPort.SetWindowText( "2352" );
   m_edtEndPort.SetWindowText( "2361" );

   UpdateData();

   OnUpdate();
}

void CDXPortDlg::OnRange7() 
{
	m_edtStartPort.SetWindowText( "2362" );
   m_edtEndPort.SetWindowText( "2371" );

   UpdateData();

   OnUpdate();
}

void CDXPortDlg::OnRange8() 
{
	m_edtStartPort.SetWindowText( "2372" );
   m_edtEndPort.SetWindowText( "2381" );

   UpdateData();

   OnUpdate();
}

void CDXPortDlg::OnRange9() 
{
	m_edtStartPort.SetWindowText( "2382" );
   m_edtEndPort.SetWindowText( "2391" );

   UpdateData();

   OnUpdate();
}

void CDXPortDlg::OnRange10() 
{
	m_edtStartPort.SetWindowText( "2392" );
   m_edtEndPort.SetWindowText( "2400" );

   UpdateData();

   OnUpdate();
}

void CDXPortDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{   
   m_bAppVisible = bShow;

   CMenu *pMenu = GetMenu();

   UpdateMenu( *pMenu );

   CDialog::OnShowWindow(bShow, nStatus);	
}



void CDXPortDlg::UpdateMenu(CMenu &rMenu)
{
   if ( m_bAppVisible )
   {
      rMenu.EnableMenuItem( ID_APP_SHOW, MF_GRAYED );
      rMenu.EnableMenuItem( ID_APP_HIDE, MF_ENABLED );
   }
   else
   {
      rMenu.EnableMenuItem( ID_APP_SHOW, MF_ENABLED );
      rMenu.EnableMenuItem( ID_APP_HIDE, MF_GRAYED );
   }
}

void CDXPortDlg::OnAppStartMinimized() 
{
	CMenu *pMenu = GetMenu();
   
   // toggle menu check mark
   if ( pMenu->CheckMenuItem(ID_APP_START_MINIMIZED, MF_UNCHECKED) == MF_UNCHECKED )
      pMenu->CheckMenuItem( ID_APP_START_MINIMIZED, MF_CHECKED );
}

void CDXPortDlg::ShowHostIpAddrs()
{
   char HostName[256] = {"/0"};
   int iResult = 0;

   if ( gethostname(&HostName[0], sizeof(HostName)) )
   {
      m_Display.AddString( "Unable to get host name");
      m_Display.AddString( " " );
      return;
   }
   
   m_Display.AddString( HostName );

   HOSTENT *pHostEnt = gethostbyname( &HostName[0] );

   if ( pHostEnt == NULL )
   {
      m_Display.AddString( "Uable to get IP address" );
      m_Display.AddString( " " );
   }

   int i = 0;
   char *lpszAddr = NULL;

   while(pHostEnt->h_addr_list[i])
   {
      lpszAddr = inet_ntoa(*(LPIN_ADDR)*(&pHostEnt->h_addr_list[i++]));

      m_Display.AddString( lpszAddr );
   }

   m_Display.AddString( " " );
}

void CDXPortDlg::SaveSettings()
{
   char FileName[2048];
   char drive[128];
   char dir[2048];
   char fname[256];

   GetModuleFileName( AfxGetInstanceHandle(), &FileName[0], sizeof(FileName) );

   _splitpath( FileName, &drive[0], &dir[0], &fname[0], NULL );

   CString strDXPortIni = drive;
   strDXPortIni += dir;
   strDXPortIni += "DXPort.ini";

   CMenu *pMenu = GetMenu();
   
   // get checked state
   UINT nState = pMenu->CheckMenuItem(ID_APP_START_MINIMIZED, MF_UNCHECKED);
   
   CString strRunMinimized;

   // set it back to previous state if we changed it
   if ( nState != MF_UNCHECKED )
   {
      pMenu->CheckMenuItem( ID_APP_START_MINIMIZED, MF_CHECKED );
      strRunMinimized = "1";
   }
   else
      strRunMinimized = "0";
      

   WritePrivateProfileString( "SETTINGS", "StartPort", m_StartPort, strDXPortIni );
   WritePrivateProfileString( "SETTINGS", "EndPort", m_EndPort, strDXPortIni );
   WritePrivateProfileString( "SETTINGS", "RunMinimized", strRunMinimized, strDXPortIni );
}
