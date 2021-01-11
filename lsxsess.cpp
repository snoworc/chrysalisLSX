/*========================================================================*\

   Copyright Lotus Development Corp. 1995 - 1999

   The enclosed code created by Lotus Development Corporation, is
   sample code. This sample code is provided to you solely for the
   purpose of assisting you in the development of your LotusScript
   Extension (LSX) applications.

   File: LSXSESS.CPP

   Description:
      Implementation of scriptable Session object

      A single instance of this class is instantiated upon execution of the USELSX
      statement.  It is destroyed when the LSX is unloaded.

\*========================================================================*/

//{{LSX_AUTHOR_CODE_Includes
//}}

#include "lsxsess.hpp"
#include "lsxapplx.h"
#include "textstr.h"

#include "CView.hpp"
#include "CVMRegistry.hpp"
#include "CAgent.hpp"

#if defined (OS390) || (defined (OS400) && defined(__STRING_CODE_SET__))
/* This must be the last #include */
#include <_Ascii_a.h>
#endif

/***********************************************************************
*
* LSXLsiSession class methods
*
*/

LSXLsiSession:: LSXLsiSession(LShINSTANCE hInst)
   :  LSXBase((LSPLTSTR)"Chrysalis", hInst, CCHRYSALIS_SESSION_ID),
ContainedObjectList(LSNULL)
//{{LSX_AUTHOR_CODE_Internal_Member_Init1
//}}
{
   //{{LSX_AUTHOR_CODE_Constructor
	LNSetThrowAllErrors (TRUE);	// only required once

	try
	{
      m_LNSession.Init();	
	}
	catch (LNSTATUS Lnerror)
	{
		char ErrorBuf[128];
		LNGetErrorMessage(Lnerror, ErrorBuf, 128);
		LSXSetErrorCode(LSX_ERROR);
	}
	catch (...)
	{		
		LSXSetErrorCode(LSX_ERROR);
	}
   //}}

   // Set the object type as LSI Session
   LSXSetObjectType(LSX_OBJTYPE_LSISESS);

   // Add the LSXLsiSession object to the global list
   ::LSXAddSession((LSPTR(LSXBase))this);
}

//***********************************************************************

LSXLsiSession:: ~LSXLsiSession()
{
   //{{LSX_AUTHOR_CODE_Destructor
	m_LNSession.Term();
   //}}

   LSXDeleteList(ContainedObjectList);

   // remove from global list
   ::LSXRemoveSession((LSPTR(LSXBase))this);
}

//***********************************************************************

//{{LSX_AUTHOR_CODE_OtherCode
//}}

