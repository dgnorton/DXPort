#if !defined(AFX_SERVERSOCKET_H__4023735D_5F57_11D5_97ED_00A0CC3AE434__INCLUDED_)
#define AFX_SERVERSOCKET_H__4023735D_5F57_11D5_97ED_00A0CC3AE434__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ServerSocket.h : header file
//

class cDataSocket;

/////////////////////////////////////////////////////////////////////////////
// cServerSocket command target

class cServerSocket : public CAsyncSocket
{
// Attributes
public:

// Operations
public:
	cServerSocket( CWnd *pOwner );
	virtual ~cServerSocket();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(cServerSocket)
	public:
	virtual void OnAccept(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(cServerSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
private:
	cDataSocket * m_pDataSocket;
	CWnd * m_pOwner;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERVERSOCKET_H__4023735D_5F57_11D5_97ED_00A0CC3AE434__INCLUDED_)
