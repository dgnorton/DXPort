// DXPortDlg.h : header file
//

#if !defined(AFX_DXPORTDLG_H__80C660A9_42DD_4657_9ECF_37CCED0843AE__INCLUDED_)
#define AFX_DXPORTDLG_H__80C660A9_42DD_4657_9ECF_37CCED0843AE__INCLUDED_

#include "NetworkPortController.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDXPortDlg dialog

class CDXPortDlg : public CDialog
{
// Construction
public:
	void SetPortRange( UINT nLow, UINT nHigh );
	void SetEndPort(LPCTSTR lpszEndPort);
	void SetStartPort(LPCTSTR lpszStartPort);
	CString m_strIpPort;
	CDXPortDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDXPortDlg)
	enum { IDD = IDD_DXPORT_DIALOG };
	CEdit	m_edtStartPort;
	CEdit	m_edtEndPort;
	CListBox	m_Display;
	CString	m_StartPort;
	CString	m_EndPort;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDXPortDlg)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDXPortDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnUpdate();
	afx_msg void OnHelpAbout();
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg void OnAppExit();
	afx_msg void OnAppHide();
	afx_msg void OnAppShow();
	afx_msg void OnRange1();
	afx_msg void OnRange2();
	afx_msg void OnRange3();
	afx_msg void OnRange4();
	afx_msg void OnRange5();
	afx_msg void OnRange6();
	afx_msg void OnRange7();
	afx_msg void OnRange8();
	afx_msg void OnRange9();
	afx_msg void OnRange10();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnAppStartMinimized();
	//}}AFX_MSG
   afx_msg void OnTrayMsg(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
private:
	void SaveSettings();
	void ShowHostIpAddrs();
	void UpdateMenu( CMenu &rMenu );
	BOOL m_bAppVisible;
	cNetworkPortController m_NPC;
	UINT m_nHighestPort;
	UINT m_nLowestPort;
	void CloseApp();
	BOOL TaskBarIcon(DWORD dwAction, UINT uID, HICON hicon, LPSTR lpszTip);
	void CloseAllSockets();
	CPtrArray m_aSockets;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DXPORTDLG_H__80C660A9_42DD_4657_9ECF_37CCED0843AE__INCLUDED_)
