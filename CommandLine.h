//***************************************************************************
//
// FILENAME:     CommandLine.h    - header file for CommandLine.cpp
//
// DATE:         1/2/2002
//
// DESCRIPTION:  This header should be #included in order to use
//               the cCommandLine class
//
//***************************************************************************

#if !defined(AFX_COMMANDLINE_H__50FF33DD_0289_11D5_97D0_00A0CC3AE434__INCLUDED_)
#define AFX_COMMANDLINE_H__50FF33DD_0289_11D5_97D0_00A0CC3AE434__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class cCommandLine : public CCommandLineInfo  
{
public:
	
	cCommandLine();
	virtual ~cCommandLine();
	
	void     ParseParam( LPCTSTR lpszParam, BOOL bFlag, BOOL bLast );
	
	CString  GetParam( const int iIndex ) const;
	int      GetNumParams() const;
   BOOL     GetMinimized() const;
	
private:
	CStringArray   m_aParams;    // storage for the command line params
   BOOL           m_bMinimized;
};

#endif // !defined(AFX_COMMANDLINE_H__50FF33DD_0289_11D5_97D0_00A0CC3AE434__INCLUDED_)
