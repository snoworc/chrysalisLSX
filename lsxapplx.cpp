/*========================================================================*\

   Copyright Lotus Development Corp. 1995 - 1999

   The enclosed code created by Lotus Development Corporation, is
   sample code. This sample code is provided to you solely for the
   purpose of assisting you in the development of your LotusScript
   Extension (LSX) applications.

   File: lsxapplx.cpp

   Description:
      Chrysalis specific functions that are called from the "common"
      code in lsx\src\common

      This file has knowledge of the client's application, and
      should therefore be modified to implement application
      class functionality as required.

      The LSXBASE.CPP code will also be making calls to certain
      LSX... functions that must be implemented in an application
      specific way.  Examples of such functions are those for GUID
      and class id handling, registering and creating application
      classes, and loading class specific text strings.

\*========================================================================*/

#define INITGUID 1      // force GUIDs to be defined in the code

//{{LSX_AUTHOR_CODE_Include_1
//}}

#include "lsxapplx.h"
#include "lsxbase.hpp"
#include "textstr.h"
#include "lsxsess.hpp"

#include "CView.hpp"
#include "CVMRegistry.hpp"
#include "CAgent.hpp"

#include "iCView.tab"   // class registration tables for CView
#include "iCVMRegistry.tab"   // class registration tables for CVMRegistry
#include "iCAgent.tab"   // class registration tables for CAgent

//{{LSX_AUTHOR_CODE_Include_2
//}}

/* **********************************************************************
*
*  Globals
*/

/***
   Here is the table of full class ids. Offset 0 is empty,
   because the short ids start with 1, and we want to use
   those as a direct index.

   The easiest way to do this is to declare a static struct
   (using the standard macros) for each class/guid, then load
   pointers to those into a table.
***/

// The first one is all 0's and it's used to ref parent classes which don't exist

DEFINE_GUID(c_NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

/**
   the GUID definitions for the Notes LSX back-end classes are in lsxnotes.hpp
**/
#include "lsxnotes.hpp"          // GUIDs for Notes LSX back-end classes

/**
   the other GUIDs come from your guidfile.h

   only #include this file once for each LSX
**/
#include "guidfile.h"            // There is a guidfile.h for each LSX.

static const GUID * guidTable[] =
{
   &c_NULL,

   // list Notes LSXBE GUIDs first

   /**
      GUID table items for the Notes LSX back-end classes are in lsxnotes.inc
   **/

#include "lsxnotes.inc"          // GUIDs for Notes LSX back-end classes

   // list your GUIDs here

   &c_Session,
   &c_CView,
   &c_CVMRegistry,
   &c_CAgent,
};

#if defined (OS390) || (defined (OS400) && defined(__STRING_CODE_SET__))
/* This must be the last #include */
#include <_Ascii_a.h>
#endif

LSULONG LSXGetGUIDBase()
{
   return (LSULONG) (LSX_YOUR_GUID_BASE_UL);
}

LSUSHORT LSXGetGUIDOffset()
{
   return (LSUSHORT) (LSX_YOUR_GUID_OFFSET_US);
}


/*
*  This routine takes a client class id (#defined in textstr.h),
*  and returns a pointer to a GUID struct, containing the full
*  16-byte id used to register the class with Script (and ole).
*  The pointer returned is static (read-only) storage, and can
*  safely be passed back to Script (or ole) as a class id.
*/

LSPTR(GUID) LSXGetFullClassID(LSUSHORT id)
{
   LSUSHORT inx = LSX_CLASS_ORDINAL(id);  // index into GUID table

   if (id < ::LSXGetFirstClassId() || id > ::LSXGetLastClassId())
      return (LSPTR(GUID))LSNULL;

   else return (LSPTR(GUID))guidTable[inx];
}

LSPTR(GUID) LSXGetClassIDRef(LSADTCLASSID FullId)
{
   LSUSHORT elems = sizeof(guidTable)/sizeof(LSPTR(GUID));

   for (LSUSHORT i = 0; i < elems; i++)
   {
      if ( memcmp(&FullId, guidTable[i], sizeof(GUID)) == 0 )
         return (LSPTR(GUID))guidTable[i];
   }

   assert(LSFALSE);
   return LSNULL;
}
/*
*  This routine gets a pointer to the entire static table. The
*  table is used in some of the registration and array routines.
*/

LSPTR(LSPTR(GUID)) LSXGetClassIDTable()
{
   return (LSPTR(LSPTR(GUID))) guidTable;
}

LSPTR(LSXLsiSession) LSXCreateLSISession(LShINSTANCE hInst)
{
   return(new (hInst) LSXLsiSession(hInst));
}

void LSXDeleteLSISession(LSPTR(LSXLsiSession) pSession)
{
   delete pSession;
}

LSREGNAMETYPE LSXGetStringType()
{
   return CHARSET;
}
/* **********************************************************************
*
*  Class, property, method and const names
*/
static TEXTTABLE gChrysalisNames[] =
{
   {CCHRYSALIS_CVIEW_ID,   (LSPLTSTR)"CView"},
   {CCHRYSALIS_CVMREGISTRY_ID,   (LSPLTSTR)"CVMRegistry"},
   {CCHRYSALIS_CAGENT_ID,   (LSPLTSTR)"CAgent"},


   {CCHRYSALIS_CVIEWMETHOD_BUILDVIEW,   (LSPLTSTR)"BuildView"},
   {CCHRYSALIS_CVIEWMETHOD_NEW,   (LSPLTSTR)"New"},
   {CCHRYSALIS_CVMREGISTRYMETHOD_ADDKEY,   (LSPLTSTR)"AddKey"},
   {CCHRYSALIS_CVMREGISTRYMETHOD_DELETEKEY,   (LSPLTSTR)"DeleteKey"},
   {CCHRYSALIS_CVMREGISTRYMETHOD_GETKEY,   (LSPLTSTR)"GetKey"},
   {CCHRYSALIS_CVMREGISTRYMETHOD_LISTSECTION,   (LSPLTSTR)"ListSection"},
   {CCHRYSALIS_CVMREGISTRYMETHOD_NEW,   (LSPLTSTR)"New"},
   {CCHRYSALIS_CVMREGISTRYMETHOD_SELFREGISTER,   (LSPLTSTR)"SelfRegister"},
   {CCHRYSALIS_CAGENTMETHOD_BUILDAGENT,   (LSPLTSTR)"BuildAgent"},
   {CCHRYSALIS_CAGENTMETHOD_NEW,   (LSPLTSTR)"New"},
   {CCHRYSALIS_CAGENTMETHOD_READAGENT,   (LSPLTSTR)"ReadAgent"},


   {CCHRYSALIS_CONST_LS_EXTENSION,   (LSPLTSTR)"LS_EXTENSION"},
   {CCHRYSALIS_CONST_LS_SERVICES,   (LSPLTSTR)"LS_SERVICES"},


//{{LSX_AUTHOR_CODE_Constant_Strings
//}}

};

#define NumChrysalisNames ((sizeof(gChrysalisNames)) / (sizeof(TEXTTABLE)))

static CONST_REG_DATA constArgs[] =
{
      {CCHRYSALIS_CONST_LS_EXTENSION,   LS_EXTENSION},
   {CCHRYSALIS_CONST_LS_SERVICES,   LS_SERVICES},

};

#define  N_CHRYSALIS_CONST  ((sizeof(constArgs)) / (sizeof(CONST_REG_DATA)))

/*********************************************************************
*
*   Chrysalis specific error messages
*/
static TEXTTABLE gChrysalisErrorMessages[] =
{

// Put your error message strings here, following this model
//
//{{LSX_AUTHOR_CODE_Error_Messages
   {ERR_CHRYSALIS_INIT_CHRYSALIS_FAILED,   (LSPLTSTR) "LSXChrysalis: Could not initialize Chrysalis"},
//}}
};

#define NumChrysalisErrors ((sizeof(gChrysalisErrorMessages)) / (sizeof(TEXTTABLE)))

/* **********************************************************************
*
*  Class version information
*/
static CLASS_VERSION_INFO gClassVersions[] =
{
   {CCHRYSALIS_CVIEW_ID,     100},   // version 1.00
   {CCHRYSALIS_CVMREGISTRY_ID,     100},   // version 1.00
   {CCHRYSALIS_CAGENT_ID,     100},   // version 1.00

};

#define NumClasses ((sizeof(gClassVersions)) / (sizeof(CLASS_VERSION_INFO)))

/*
*  All client's must implement these functions.
*/

/*
*  The base class needs to be able to find out the values of the
*  LSX_FIRST_CLASS and the LSX_LAST_CLASS id's and, for OLE automation,
*  the class id's for the OLE Session class and the LSX_OLEMAIN_CLASS.
*/

LSUSHORT LSXGetFirstClassId()
{
   return (LSX_FIRST_CLASS);
}

LSUSHORT LSXGetLastClassId()
{
   return (LSX_LAST_CLASS);
}

#if defined (OLE_PLATFORM)

LSUSHORT LSXGetOleMainClassId()
{
   return (LSX_OLEMAIN_CLASS);
}

LSUSHORT LSXGetOleClassId()
{
   return (LSX_OLE_CLASS);
}

#endif   // (OLE_PLATFORM)

/*
*  The client needs to describe how to load a text string representing a
*  class name, a property name, or the name of a method.
*  For example, strings may be loaded from a static table (as here) or
*  from an external resource file, as is common in Windows and in PM.
*/

LSSSHORT LSXGetTextString(LSUSHORT id, LSPLTSTR buffer, LSUSHORT max_len)
{
   register    int i = 0;
   LPTEXTTABLE pTableItem=LSNULL;
   LSBOOL      found=LSFALSE;

   memset(buffer, 0x00, max_len);
   while ((!found) && (i < NumChrysalisNames))
   {
      pTableItem= &gChrysalisNames[i];

      if (pTableItem->iTextId == id)
      {
         strcpy(buffer, (const char *) pTableItem->cTextStr);
         found=LSTRUE;
      }
      i++;
   }
   assert (found==LSTRUE);
   return strlen(buffer);
}

/*
*  The client needs to describe how to load a text string representing an
*  error message.
*  For example, strings may be loaded from a static table (as here) or
*  from an external resource file, as is common in Windows and in PM.
*/

LSSSHORT LSXGetErrorText(LSUSHORT id, LSPLTSTR buffer, LSUSHORT max_len)
{
   register    int i = 0;
   LPTEXTTABLE pTableItem=LSNULL;
   LSBOOL      found=LSFALSE;

   memset(buffer, 0x00, max_len);
   while ((!found) && (i < NumChrysalisErrors))
   {
      pTableItem= &gChrysalisErrorMessages[i];

      if (pTableItem->iTextId == id)
      {
         strcpy(buffer, (const char *) pTableItem->cTextStr);
         found=LSTRUE;
      }
      i++;
   }
   assert (found==LSTRUE);
   return strlen(buffer);
}

/*
*  The class registration code needs to be told the "version" level of the
*  class being registered.  It is important to update the version number
*  whenever there is a change to the class registration information -
*  particularly with regard to the id's of methods, properties, etc.
*  If the id's changed and you do not tell LS this at registration time,
*  the LS run-time is likely to send messages to the LSX which have the
*  obsolete method/property etc. id information.  This will cause the LSX
*  to behave unpredictably.
*/

/*  Revision:
 *
 *  It turns out that the functionality in the above explanation is not
 *  actually implemented in LotusScript yet.  The best practice is to not
 *  modify the ids of your classes, methods, etc. once the script has been
 *  compiled.  This way, old scripts will still work.  If you add new
 *  methods, etc, with new ids, the script code will be new as well, so
 *  the compile will happen automatically.
*/

LSADTVERSION LSXGetClassVersion(LSUSHORT class_id)
{
   LSSSHORT       i=0;
   LPVERSION_INFO pVersionItem=LSNULL;
   LSBOOL         found=LSFALSE;
   LSADTVERSION   version=100;   // default is version 1.00 (arbitrary choice)

   while ((!found) && (i < NumClasses))
   {
      pVersionItem = &gClassVersions[i];

      if (pVersionItem->iClassId == class_id)
      {
         version = pVersionItem->iVersion;
         found=LSTRUE;
      }
      i++;
   }
   assert (found==LSTRUE);
   return version;
}

LS_CPP_PASCAL_LINKAGE_BEGIN

/*********************************************************************
*
*  Register all of this dll's objects with LSI
*
*  Registration tables are in the *.TAB etc. files
*/

//{{LSX_AUTHOR_CODE_Register_Tables_Globals
//}}

LSICLI(LSSTATUS)  RegisterClientClasses(
   LShINSTANCE hInst, LShMODULE hMod, LSPLTSTR pLSXDLLName)
{
   LSSTATUS status = LSX_OK;

   if (status == LSX_OK)
   {
      // register Chrysalis CView class

      status = ::LSXRegisterOneClass(hInst, CCHRYSALIS_CVIEW_ID, LSNULL,
         LSNULL, LSNULL, N_CVIEW_PROPS,
         CView_methodnameids, CView_gmethods, N_CVIEW_METHODS,
         LSNULL, LSNULL, N_CVIEW_EVENTS,
         CHARSET,     // Class name string type
         CHARSET,     // string type for Class Control Procedure
         pLSXDLLName, (LSPLTSTR)LSX_CLASS_CONTROL_NAME, hMod,
         LSI_ADT_REFERENCED );
   }

   if (status == LSX_OK)
   {
      // register Chrysalis CVMRegistry class

      status = ::LSXRegisterOneClass(hInst, CCHRYSALIS_CVMREGISTRY_ID, LSNULL,
         LSNULL, LSNULL, N_CVMREGISTRY_PROPS,
         CVMRegistry_methodnameids, CVMRegistry_gmethods, N_CVMREGISTRY_METHODS,
         LSNULL, LSNULL, N_CVMREGISTRY_EVENTS,
         CHARSET,     // Class name string type
         CHARSET,     // string type for Class Control Procedure
         pLSXDLLName, (LSPLTSTR)LSX_CLASS_CONTROL_NAME, hMod,
         LSI_ADT_REFERENCED );
   }

   if (status == LSX_OK)
   {
      // register Chrysalis CAgent class

      status = ::LSXRegisterOneClass(hInst, CCHRYSALIS_CAGENT_ID, LSNULL,
         LSNULL, LSNULL, N_CAGENT_PROPS,
         CAgent_methodnameids, CAgent_gmethods, N_CAGENT_METHODS,
         LSNULL, LSNULL, N_CAGENT_EVENTS,
         CHARSET,     // Class name string type
         CHARSET,     // string type for Class Control Procedure
         pLSXDLLName, (LSPLTSTR)LSX_CLASS_CONTROL_NAME, hMod,
         LSI_ADT_REFERENCED );
   }

   if (status == LSX_OK)
   {
      LSPLTCHAR   buffer[LSX_MAX_BUFF_LEN];
      LSSSHORT i, len;

      for (i = 0; i < N_CHRYSALIS_CONST; i++)
      {
         len = ::LSXGetTextString(constArgs[i].resid, buffer, (LSX_MAX_BUFF_LEN-1));
         status = hInst->ConstRegister(
                           CHARSET,           // string type
                           (LSPLTSTR)buffer,
                           LSI_DT_SHORT,
                           LSVAR_SCOPE_PUBLIC,
                           &constArgs[i].value,
                           LSNULL,
                           hMod);             // module to register into
      }
   }

  //{{LSX_AUTHOR_CODE_Register_Globals
  //}}

   return status;
}

LS_CPP_PASCAL_LINKAGE_END

LSSTATUS CreateClientObjects( LShINSTANCE     hInst,
                              PLSADTINSTDESC  pInstDesc,
                              LSADTMSGPARAM   param)
{
   LSPTR(LSXLsiSession)   pAppSession=LSNULL;
   LSPTR(CView)      pCView=LSNULL;
   LSPTR(CVMRegistry)      pCVMRegistry=LSNULL;
   LSPTR(CAgent)      pCAgent=LSNULL;
   LSSTATUS               retval = LSX_OK;

   /*
      There's no object yet, of course.
      Here's an interesting situation: we have all these objects
      which need to be created in the context of some container
      but we want to support users just doing New "object" in
      LotusScript. So, we make them pass the containing object
      as an argument (we don't make them pass a containing Session
      for creating a client object; since there is only one session,
      we just find it).

      Note that until we 'New' the object in C++ there's no way to
      invoke a constructor. We could pass the container into the
      constructor, and have the constructor call the container to
      insert the new thing into the container's list. Or, we could
      unpack the arg list, parse out the container object, and
      invoke a create method on the container for the new object.
      The first is more code in the objects, the second is more
      code right here.

      For now, we go with the first choice (pass the container
      object to the constructor of the new object, which needs
      to have a back-pointer anyway)
   */

   pAppSession =
      (LSPTR(LSXLsiSession))::LSXFindSession(hInst, LSX_OBJTYPE_LSISESS);

   if (pAppSession == LSNULL)
   {
      pAppSession = new (hInst) LSXLsiSession(hInst);
      /*
         If the creation of the Session object failed, return an error to LS
      */
      retval= (pAppSession)   ? pAppSession->LSXGetErrorCode()
                                 : LSI_ERR_ABORT;
   }
   assert (pAppSession);

   //Initialize the args object
   LSXArgs ArgList(param.mpCreate, hInst);

   if (retval == LSX_OK)
   {
      switch (LSX_GETCLASSID(pInstDesc->idClass))
      {
      case CCHRYSALIS_CVIEW_ID:
      {
         // force a new scope so we can use the same variable names
         // in different cases.
         
      //Extract the arguments
      NotesDocument& parmDoc =  (NotesDocument&) ArgList.getArg(1).getForeignObject();

         pCView = new (hInst) CView(pAppSession, parmDoc);
         pInstDesc->hdlClient =(pCView) ? pCView->GetInterfacePtr() : LSNULL;
         

         // If the creation of the CView object failed, return an error to LS.
         retval = (pCView) ? pCView->LSXGetErrorCode() : LSI_ERR_ABORT;
      }  
      break;

      case CCHRYSALIS_CVMREGISTRY_ID:
      {
         // force a new scope so we can use the same variable names
         // in different cases.
         
         pCVMRegistry = new (hInst) CVMRegistry(pAppSession);
         pInstDesc->hdlClient =(pCVMRegistry) ? pCVMRegistry->GetInterfacePtr() : LSNULL;
         

         // If the creation of the CVMRegistry object failed, return an error to LS.
         retval = (pCVMRegistry) ? pCVMRegistry->LSXGetErrorCode() : LSI_ERR_ABORT;
      }  
      break;

      case CCHRYSALIS_CAGENT_ID:
      {
         // force a new scope so we can use the same variable names
         // in different cases.
         
      //Extract the arguments
      NotesDocument& parmDoc =  (NotesDocument&) ArgList.getArg(1).getForeignObject();

         pCAgent = new (hInst) CAgent(pAppSession, parmDoc);
         pInstDesc->hdlClient =(pCAgent) ? pCAgent->GetInterfacePtr() : LSNULL;
         

         // If the creation of the CAgent object failed, return an error to LS.
         retval = (pCAgent) ? pCAgent->LSXGetErrorCode() : LSI_ERR_ABORT;
      }  
      break;


      default:
         assert (LSFALSE);
         retval = LSI_ERR_INVALADT;
         break;
      }
   }
   return retval;
}

//{{LSX_AUTHOR_CODE_OtherCode
//}}

