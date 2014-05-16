//***************************************************************************
//
// FILENAME:     CommandLine.cpp - implementation of the cCommandLine class
//
// DATE:         1/2/2002
//
// DESCRIPTION:  This class is used to parse and store the command line
//               parameters for later use
//
//***************************************************************************

#include "stdafx.h"
#include "CommandLine.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


//*****************************************************************************
// METHOD:      cCommandLine - constructs a cCommandLine object
// 	
// PARAMETERS:  NONE
//
// RETURN:      NONE
//*****************************************************************************
cCommandLine::cCommandLine()
{
   m_aParams.RemoveAll();
   m_bMinimized = FALSE;
}


//*****************************************************************************
// METHOD:      ~cCommandLine - destructs a cCommandLine object
// 	
// PARAMETERS:  NONE
//
// RETURN:     	NONE
//*****************************************************************************
cCommandLine::~cCommandLine()
{

}


//////////////////////////////////////////////////////////////////////
// Overrides
//////////////////////////////////////////////////////////////////////


//***************************************************************************
// METHOD:        ParseParam  - called by the base class (CCommandLineInfo)
//                              once for each command line parameter
// 	
// PARAMETERS:    See CCommandLineInfo documentation in MSDN
//
// RETURN:     	  NONE
//***************************************************************************
void cCommandLine::ParseParam( LPCTSTR lpszParam, BOOL bFlag, BOOL bLast )
{
   if ( !bFlag )
      m_aParams.Add( lpszParam );
   else if ( *lpszParam == 'M' || *lpszParam == 'm' )
      m_bMinimized = TRUE;

   CCommandLineInfo::ParseParam(lpszParam, bFlag, bLast);
}


//////////////////////////////////////////////////////////////////////
// Methods
//////////////////////////////////////////////////////////////////////


//*****************************************************************************
// METHOD:   	GetParam  - Retrieves a command line parameter stored at the
//                          given index.  This method combined with the
//                          GetNumParams() method allow for itteration
//                          through the parameters.
// 	
// PARAMETERS:  const int iIndex - [in] returns the command line parameter
//                                 at the specified index.
//                                 NOTE:  This index is NOT gaurenteed to
//                                 be the same as the parameters location
//                                 in the command line.  It is a zero based
//                                 index into the cCommandLine class.
//
// RETURN:     	CString  - The command line parameter if successfull
//                         An empty string if an invalid index is passed
//*****************************************************************************
CString  cCommandLine::GetParam( const int iIndex ) const
{
   if ( iIndex >= 0 && iIndex < m_aParams.GetSize() )
      return m_aParams.GetAt( iIndex );
   
   return _T("");
}


//*****************************************************************************
// METHOD:      GetNumParams  - Retrieves the number of parameters stored
//                                in the cCommandLine class
// 	
// PARAMETERS:  NONE
//
// RETURN:      int  - The number of command line parameters stored in the
//                     class.  NOTE: Parameter indexs are zero based.
//*****************************************************************************
int cCommandLine::GetNumParams() const
{
   return m_aParams.GetSize();
}


//*****************************************************************************
// METHOD:    GetMinimized  - Gets the flag that tells the app if it should
//                            start minimized or not
// 	
// PARAMETERS: NONE
//
// RETURN:     BOOL  - if TRUE, app should run minimized. FALSE, app should
//                     be displayed normal.
//*****************************************************************************
BOOL cCommandLine::GetMinimized() const
{
   return m_bMinimized;
}
