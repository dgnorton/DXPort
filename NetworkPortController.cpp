// NetworkPortController.cpp: implementation of the cNetworkPortController class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DXPort.h"
#include "NetworkPortController.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

cNetworkPortController::cNetworkPortController()
{

}

cNetworkPortController::~cNetworkPortController()
{

}



BOOL cNetworkPortController::LockPort(const UINT nPort, const int iFlags)
{
   m_strResult = "";
   
   m_bTcpResult = FALSE;
   m_bUdpResult = FALSE;
   m_strTcpResult = "";
   m_strUdpResult = "";
   
   if ( iFlags == NONE )
   {
      m_strResult = "No socket type specified";
      return FALSE;
   }
   else if ( iFlags > ALL )
   {
      m_strResult = "Invalid socket type specified";
      return FALSE;
   }
   
   CAsyncSocket *pSocket = NULL;
   CString strSocketType;
   CMapWordToOb *pMap = NULL;
   BOOL *pbResult = NULL;
   CString *pstrResult = NULL;

   int iSocketType;

   if ( iFlags & UDP )
   {
      strSocketType = "UDP";
      pMap = &m_mOpenUdpPorts;
      iSocketType = SOCK_DGRAM;
      pbResult = &m_bUdpResult;
      pstrResult = &m_strUdpResult;
   }
   else
   {
      strSocketType = "TCP";
      pMap = &m_mOpenTcpPorts;
      iSocketType = SOCK_STREAM;
      pbResult = &m_bTcpResult;
      pstrResult = &m_strTcpResult;
   }
   
   CString strTemp;

   while ( iSocketType )
   {     
      pSocket = new CAsyncSocket();

      // check for successfull construction socket
      if ( !AfxIsValidAddress( pSocket, 1, FALSE ) || pSocket <= 0 )
      {
         m_strResult = "Error while allocating memory";
         return FALSE;
      }

      // create the socket
      if ( !pSocket->Create( nPort, iSocketType, 0 ) )
      {
         DWORD dwErr = GetLastError();
         delete pSocket;

         if ( dwErr == WSAEADDRINUSE )
            *pstrResult = "In use by another app";
         else
            *pstrResult = "Not locked";

         return FALSE;
      }
      else
      {
         // save ptr to new socket for cleanup later
         pMap->SetAt( nPort, pSocket );

         *pbResult = TRUE;
         *pstrResult = "Locked";
      }

      if ( (iSocketType == SOCK_DGRAM) && (iFlags & TCP) )
      {
         iSocketType = SOCK_STREAM;
         pMap = &m_mOpenTcpPorts;
         pbResult = &m_bTcpResult;
         pstrResult = &m_strTcpResult;
      }
      else
      {
         iSocketType = 0;
         pMap = NULL;
         pbResult = NULL;
         pstrResult = NULL;
      }
   }
   
   return TRUE;
}

void cNetworkPortController::ReleaseAllPorts(const int iFlags)
{
   POSITION Pos;
   CAsyncSocket *pSocket = NULL;
   unsigned short nPort = 0;

   if ( iFlags & UDP )
   {
      Pos = m_mOpenUdpPorts.GetStartPosition();

      while ( Pos )
      {
         m_mOpenUdpPorts.GetNextAssoc( Pos, nPort, (CObject*&)pSocket );
         
         if ( pSocket > 0 )
         {
            pSocket->Close();
            delete pSocket;
         }
      }
      m_mOpenUdpPorts.RemoveAll();
   }

   if ( iFlags & TCP )
   {
      Pos = m_mOpenTcpPorts.GetStartPosition();

      while ( Pos )
      {
         m_mOpenTcpPorts.GetNextAssoc( Pos, nPort, (CObject*&)pSocket );

         if ( pSocket > 0 )
         {
            pSocket->Close();
            delete pSocket;
         }
      }
      m_mOpenTcpPorts.RemoveAll();
   }
}


void cNetworkPortController::ReleasePort(const UINT nPort, const int iFlags)
{
   CAsyncSocket *pSocket = NULL;

   if ( iFlags & UDP )
   {
      m_mOpenUdpPorts.Lookup( nPort, (CObject*&)pSocket );

      if ( pSocket > 0 )
      {
         pSocket->Close();
         delete pSocket;

         m_mOpenUdpPorts.RemoveKey( nPort );
      }
   }

   pSocket = NULL;

   if ( iFlags & TCP )
   {
      m_mOpenTcpPorts.Lookup( nPort, (CObject*&)pSocket );

      if ( pSocket > 0 )
      {
         pSocket->Close();
         delete pSocket;

         m_mOpenTcpPorts.RemoveKey( nPort );
      }
   }
}

void cNetworkPortController::SetResult(LPCTSTR lpszResult)
{
   m_strResult = lpszResult;
}

CString cNetworkPortController::GetResult() const
{
   return m_strResult;
}

BOOL cNetworkPortController::GetUdpResult() const
{
   return m_bUdpResult;
}

BOOL cNetworkPortController::GetTcpResult() const
{
   return m_bTcpResult;
}

CString cNetworkPortController::GetUdpResultStr() const
{
   return m_strUdpResult;
}

CString cNetworkPortController::GetTcpResultStr() const
{
   return m_strTcpResult;
}
