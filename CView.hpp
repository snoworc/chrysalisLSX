/*=============================================================================*\

   Copyright Lotus Development Corp. 1995 - 1999


   The enclosed code created by Lotus Development Corporation, is
   sample code. This sample code is provided to you solely for the
   purpose of assisting you in the development of your LotusScript
   Extension (LSX) applications.

   File: CView.hpp

   Description:
      Class definition for scriptable "CView" object

\*==============================================================================*/
#if !defined (CVIEW_HPP)
#define CVIEW_HPP

//{{LSX_AUTHOR_CODE_Include1
//}}

#include "lsxapplx.h"
#include "lsxbase.hpp"
#include "lsxsess.hpp"

class CView;

typedef LSXObjectArray<CView, CCHRYSALIS_CVIEW_ID> CViewArray;

//{{LSX_AUTHOR_CODE_Include2
//}}

// forward references to other classes
class CVMRegistry;
class CAgent;

class CView : public LSXBase
//{{LSX_AUTHOR_CODE_Additional_Base_Classes
//}}
{
   protected:

      // Data members exposed to LotusScript via Get/Set Prop (access functions inlined below)


      //{{LSX_AUTHOR_CODE_Protected_Internal
      //}}

   private:

      //{{LSX_AUTHOR_CODE_Private_Internal
	  NOTEHANDLE m_noteHandle;	// READ ONLY!
	  NOTEHANDLE m_DBHandle;	// WRITE DBHANDLE	  	  
	  NOTEID m_nid;				// WRITE NOTEID
	  LNDatabase m_LNDB;
      //}}

      // These are private because they are unimplemented and we need to prevent
      // the compiler from creating default versions.
      CView & operator = (CView&);
      CView (const CView&);
      CView();

   public:

      // This constructor is called when the script "new"s one or calls
      // a function like "CreateCView" on the container class.
      CView( LSPTR(LSXLsiSession) pContainer, NotesDocument& parmDoc );

      // This constructor is used by a derived class to initialize its parent
      CView(LSUSHORT classId, LSPTR(LSXLsiSession) pContainer, NotesDocument& parmDoc  );

      virtual ~CView();


      // Methods exposed to LotusScript
      LSXBool BuildView (  );

      // Event-Raising methods

      
      // Helper functions - not exposed to LotusScript

      LSPTR(LSXLsiSession) LSXGetSession() const
      { 
         return ((LSPTR(LSXLsiSession)) pContainerObject)->LSXGetSession(); 
      }

      //{{LSX_AUTHOR_CODE_Public_Internal (not exposed to LotusScript)
      //}}

      // Low-level calls defined in iCView.CPP.
      virtual LSSTATUS LSXDispatchMethod(PLSADTMSGMETHOD args);
      virtual LSSTATUS LSXGetProp( PLSADTINSTDESC pinstdesc, PLSADTMSGPROP param);
      virtual LSSTATUS LSXSetProp( PLSADTINSTDESC pinstdesc, PLSADTMSGPROP param);


      // Property Gets and Sets for data members exposed to LotusScript


      //{{LSX_AUTHOR_CODE_Inlines
      //}}
};

//{{LSX_AUTHOR_CODE_Other
//}}

#endif   //   #if !defined (CVIEW_HPP)

