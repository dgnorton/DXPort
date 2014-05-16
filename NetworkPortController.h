// NetworkPortController.h: interface for the cNetworkPortController class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NETWORKPORTCONTROLLER_H__C558707E_C909_41C6_9D91_B7BB80C90587__INCLUDED_)
#define AFX_NETWORKPORTCONTROLLER_H__C558707E_C909_41C6_9D91_B7BB80C90587__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class cNetworkPortController  
{
public:
	CString GetTcpResultStr() const;
	CString GetUdpResultStr() const;
	BOOL GetTcpResult() const;
	BOOL GetUdpResult() const;

   enum { NONE = 0,
          UDP = 1,
          TCP = 2,
          ALL = 3,
   };

	cNetworkPortController();
	virtual ~cNetworkPortController();
   
   CString  GetResult() const;
	void     ReleasePort( const UINT nPort, const int iFlags );
	void     ReleaseAllPorts( const int iFlags );
	BOOL     LockPort( const UINT nPort, const int iFlags );
	   
private:
	CString m_strTcpResult;
	CString m_strUdpResult;
	BOOL m_bTcpResult;
	BOOL m_bUdpResult;
	
	CString m_strResult;
	CMapWordToOb m_mOpenTcpPorts;
	CMapWordToOb m_mOpenUdpPorts;

   void SetResult( LPCTSTR lpszResult );
};

#endif // !defined(AFX_NETWORKPORTCONTROLLER_H__C558707E_C909_41C6_9D91_B7BB80C90587__INCLUDED_)
