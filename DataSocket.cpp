// DataSocket.cpp : implementation file
//

#include "stdafx.h"
#include "DataSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// cDataSocket

cDataSocket::cDataSocket( CWnd *pDataHandlerWnd )
{
   m_pDataHandlerWnd = pDataHandlerWnd;
   m_bConnected = FALSE;
   m_bOnConnectComplete = FALSE;
}

cDataSocket::~cDataSocket()
{
   if ( m_bConnected )
      Close();
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(cDataSocket, CAsyncSocket)
	//{{AFX_MSG_MAP(cDataSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// cDataSocket member functions

BOOL cDataSocket::IsOnConnectComplete()
{
   return m_bOnConnectComplete;
}

void cDataSocket::SetConnected(BOOL bConnected)
{
   m_bConnected = bConnected;
}

BOOL cDataSocket::IsConnected()
{
   return m_bConnected;
}

void cDataSocket::OnReceive(int nErrorCode) 
{
   DWORD DataLen = 0;
   
   // see how many bytes are available to receive
   IOCtl(FIONREAD,&DataLen);

   // if no data we are done
   if ( DataLen <= 0 )
      return;

   // allocate data buffer to receive data
   char *pBuffer = (char *) calloc( DataLen + 1, sizeof(char) );

   // check for allocation error
   if ( !pBuffer )
   {
      AfxMessageBox( _T("Out of memory!!!") );
      return;
   }
   
   if ( Receive( pBuffer, DataLen ) == SOCKET_ERROR )
   {
      free( pBuffer );
      return;
   }

   // null terminate the data just in case
   // the owner forgets to check and does
   // some string manipulation
   pBuffer[DataLen + 1] = '\0';

   // check for a valid data handling window
   if ( !AfxIsValidAddress( m_pDataHandlerWnd, 1, FALSE ) )
   {
      free( pBuffer );
      return;
   }

   if ( m_pDataHandlerWnd > 0 && AfxIsValidAddress( m_pDataHandlerWnd, 1, FALSE ) )
   {
      // post pointer to the data
      // NOTE:  the memory allocated here will be freed in the data handler
      m_pDataHandlerWnd->PostMessage( WM_USER + 1,
                                      (WPARAM) pBuffer,
                                      (LPARAM) DataLen );
   }
		
	CAsyncSocket::OnReceive(nErrorCode);
}

void cDataSocket::OnClose(int nErrorCode) 
{
   m_bConnected = FALSE;
   
	CAsyncSocket::OnClose(nErrorCode);
}
