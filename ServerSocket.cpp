// ServerSocket.cpp : implementation file
//

#include "stdafx.h"
//#include "Delphi.h"
#include "ServerSocket.h"
#include "DataSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// cServerSocket

cServerSocket::cServerSocket( CWnd *pOwner )
{
   m_pOwner = pOwner;
   m_pDataSocket = NULL;
}

cServerSocket::~cServerSocket()
{
   if ( AfxIsValidAddress( m_pDataSocket, 1, FALSE ) )
      delete m_pDataSocket;
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(cServerSocket, CAsyncSocket)
	//{{AFX_MSG_MAP(cServerSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// cServerSocket member functions

void cServerSocket::OnAccept(int nErrorCode) 
{
   // already connected?
   if ( AfxIsValidAddress( m_pDataSocket, 1, FALSE ) )
   {
      if ( m_pDataSocket->IsConnected() )   
         return;

      // not connected...need to cleanup
      delete m_pDataSocket;

      m_pDataSocket = NULL;
   }
	
   m_pDataSocket = new cDataSocket( m_pOwner );

   // failed to create new worker socket?
   if ( !AfxIsValidAddress( m_pDataSocket, 1, FALSE ) )
      return;

   // accept the connection request
   if ( !Accept( *m_pDataSocket ) )
   {
      // if we faild to accept, clean up and return
      delete m_pDataSocket;
      return;
   }
   
   m_pDataSocket->SetConnected( TRUE );

   CAsyncSocket::OnAccept(nErrorCode);
}
