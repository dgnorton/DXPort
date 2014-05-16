#if !defined(AFX_DATASOCKET_H__4023735F_5F57_11D5_97ED_00A0CC3AE434__INCLUDED_)
#define AFX_DATASOCKET_H__4023735F_5F57_11D5_97ED_00A0CC3AE434__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DataSocket.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// cDataSocket command target

class cDataSocket : public CAsyncSocket
{
// Attributes
public:

// Operations
public:
	cDataSocket( CWnd *pDataHandlerWnd );
	virtual ~cDataSocket();

// Overrides
public:
	BOOL IsConnected();
	void SetConnected( BOOL bConnected );
	BOOL IsOnConnectComplete();
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(cDataSocket)
	public:
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(cDataSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
private:
	BOOL m_bOnConnectComplete;
	BOOL m_bConnected;
	CWnd * m_pDataHandlerWnd;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATASOCKET_H__4023735F_5F57_11D5_97ED_00A0CC3AE434__INCLUDED_)
