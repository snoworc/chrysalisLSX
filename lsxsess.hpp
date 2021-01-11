/*========================================================================*\

   Copyright Lotus Development Corp. 1995 - 1999


   The enclosed code created by Lotus Development Corporation, is
   sample code. This sample code is provided to you solely for the
   purpose of assisting you in the development of your LotusScript
   Extension (LSX) applications.

   File: lsxsess.hpp

   Description:
      Class definition for scriptable Session object

      A single instance of this class is instantiated upon execution of the USELSX
      statement.  It is destroyed when the LSX is unloaded.

\*========================================================================*/

#if !defined(LSXSESS_HPP)
#define LSXSESS_HPP

//{{LSX_AUTHOR_CODE_Include
#include "lsxapplx.h"
//}}

#if !defined(LSXBASE_HPP)
#include "lsxbase.hpp"
#endif

/*******************************************************************
*
*  Class definition for Chrysalis Session object
*/

// list forward references to other application classes used here

class CView;
class CVMRegistry;
class CAgent;

class LSXLsiSession : public LSXBase
{
   protected:

      //{{LSX_AUTHOR_CODE_Protected_Internal
      //}}

   private:

      // Keep track of all the classes that are contained by this
      // session, by default.  No need to destinguish their type
      // because the containment is not part of the object model, 
      // just an extra safety measure for cleanup purposes

      LSPTR(LSXBase)   ContainedObjectList;

      // These are private to prevent people from calling them

      LSXLsiSession & operator = (LSXLsiSession&);
      LSXLsiSession (const LSXLsiSession&);
      LSXLsiSession();

      //{{LSX_AUTHOR_CODE_Private_Internal
	  LNNotesSession m_LNSession;
      //}}

   public:

      LSXLsiSession(LShINSTANCE hinst);
      virtual ~LSXLsiSession();

      LSPTR(LSXLsiSession) LSXGetSession() { return this; }

      // These are methods of the base class that are being overridden

      virtual void ContainedObjectCreated(LSPTR(LSXBase) pContained)
      {
         LSXAddToList(pContained, (LSPTR(LSPTR(LSXBase))) &ContainedObjectList);
      }
      virtual void ContainedObjectDestroyed(LSPTR(LSXBase) pContained)
      {
         LSXRemoveFromList(pContained, (LSPTR(LSPTR(LSXBase))) &ContainedObjectList);
      }

      virtual LSSTATUS LSXDispatchMethod(PLSADTMSGMETHOD args){ return LSX_OK; }
      virtual LSSTATUS LSXGetProp(PLSADTINSTDESC pinstdesc, PLSADTMSGPROP param){ return LSX_OK; }
      virtual LSSTATUS LSXSetProp(PLSADTINSTDESC pinstdesc, PLSADTMSGPROP param){ return LSX_OK; }

     //{{LSX_AUTHOR_CODE_Public_Internal
	  LNNotesSession & GetLNNotesSession() { return m_LNSession; }
     //}}
};

//{{LSX_AUTHOR_CODE_Other
//}}

#endif   //   #if !defined (LSXSESS_HPP)

