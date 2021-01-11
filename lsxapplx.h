/*========================================================================*\

   Copyright Lotus Development Corp. 1995 - 1999

   The enclosed code created by Lotus Development Corporation, is
   sample code.  This sample code is provided to you solely for the
   purpose of assisting you in the development of your LotusScript
   Extension (LSX) applications.

   File: lsxapplx.h

   Description:
      Definitions for application specific items

\*========================================================================*/

#if !defined(LSXAPPLX_H)
#define LSXAPPLX_H

//{{LSX_AUTHOR_CODE_Include1
#include "lncppapi.h"
//}}

// Changing the character set in the Wizard will comment/uncomment this 
// line to toggle between UNICODE and PLATFORM strings.  
// However, UNICODE is not supported on OS390 - so force the use of ASCII

#if !defined(OS390)   /* only if NOT OS390 */
//#define UNICODE_STRINGS
#endif

#include "lsxstrtm.hpp"
#include "lsxarray.hpp"
#include "lsxvalue.hpp"
#include "lsxforeign.hpp"
#include "textstr.h"

//{{LSX_AUTHOR_CODE_Include2
//}}

// Although these would ideally be defined in LSXCOMM, 
// they need to be here in case a single Common is 
// shared with multiple LSXs with different string types.

#if defined(UNICODE_STRINGS)

   typedef LSXUniString             LSXString;
   typedef LSXUniStringArray        LSXStringArray;
   #define CHARSET                  LSI_REGNAME_UNICODE
   #define CHARTYPE                 LSUNICHAR
   #define getString()              getUniString()
   #define getStringArray           getUniStringArray

   // On platforms where a wide character is 2 bytes, you can specify a 
   // literal string by prefixing an 'L'.  On other platforms, you need to 
   // do an actual conversion from a wide character down to a UNICODE 
   // character.

   #if defined(UNIX) || defined(OS2)
      #define LIT_STR(x)            LSXUniString(L##x)
   #else
      #define LIT_STR(x)            L##x  // On Unix, a long is 4 bytes 
   #endif                                 //   not 2, so this doesn't work

#else

   typedef LSXPltString             LSXString;
   typedef LSXPltStringArray        LSXStringArray;
   #define CHARSET                  LSI_REGNAME_PLATFORM
   #define CHARTYPE                 LSPLTCHAR
   #define getString()              getPltString()
   #define getStringArray           getPltStringArray
   #define LIT_STR(x)               (LSPLTSTR) x  // Some compilers give 
                                                  // a warning if no cast
#endif

/*********************************************************************/
/*   These defines segment the address space for string ids - your choice      */

//{{LSX_AUTHOR_CODE_Min_Error_Code
#define LSXBASE_MIN_ERROR_CODE  20001   /* your choice >20000 */
//}}

#define LSX_FIRST_USER_ERROR_CODE   (LSXBASE_MIN_ERROR_CODE+1)

// #define's for your error messages go here, following this model:

//{{LSX_AUTHOR_CODE_Error_Messages
#define ERR_CHRYSALIS_INIT_CHRYSALIS_FAILED     (LSX_FIRST_USER_ERROR_CODE+2)
#define LSXBASE_ERR_MAX_ERROR_CODE  (LSX_FIRST_USER_ERROR_CODE+2)
//}}



/*********************************************************************/

#define N_CVIEW_BUILDVIEW_ARGS         1
#define N_CVIEW_NEW_ARGS         2


#define N_CVMREGISTRY_ADDKEY_ARGS         4
#define N_CVMREGISTRY_DELETEKEY_ARGS         3
#define N_CVMREGISTRY_GETKEY_ARGS         3
#define N_CVMREGISTRY_LISTSECTION_ARGS         2
#define N_CVMREGISTRY_NEW_ARGS         1
#define N_CVMREGISTRY_SELFREGISTER_ARGS         3


#define N_CAGENT_BUILDAGENT_ARGS         1
#define N_CAGENT_NEW_ARGS         2
#define N_CAGENT_READAGENT_ARGS         2



/*********************************************************************/
/*   Constants Exposed to LotusScript                                */

   #define  LS_EXTENSION   100
   #define  LS_SERVICES   200

/*********************************************************************/

//{{LSX_AUTHOR_CODE_Global_Functions
//}}

#endif   // #if !defined (LSXAPPLX_H)

