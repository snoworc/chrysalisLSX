/*=============================================================================*\

   Copyright Lotus Development Corp. 1995 - 1999


   The enclosed code created by Lotus Development Corporation, is
   sample code. This sample code is provided to you solely for the
   purpose of assisting you in the development of your LotusScript
   Extension (LSX) applications.

   File: CVMRegistry.hpp

   Description:
      Class definition for scriptable "CVMRegistry" object

\*==============================================================================*/
#if !defined (CVMREGISTRY_HPP)
#define CVMREGISTRY_HPP

//{{LSX_AUTHOR_CODE_Include1
#if defined(WIN32)
	#if !defined W32
		#define W32
	#endif
#endif
//}}

#include "lsxapplx.h"
#include "lsxbase.hpp"
#include "lsxsess.hpp"

class CVMRegistry;

typedef LSXObjectArray<CVMRegistry, CCHRYSALIS_CVMREGISTRY_ID> CVMRegistryArray;

//{{LSX_AUTHOR_CODE_Include2
/*********************************************************************/

#define MAX_VALUE_NAME           128
#define MAX_DATA_LEN             1024

#define ERROR_ILLEGAL_SWITCH		-1
#define ERROR_ILLEGAL_KEYVAL		-2
#define ERROR_ILLEGAL_SECTION		-3

#define SECTION_EXTENSION			"LotusScriptExtensions\\2.0"
#if LSAPI_OS2
#define SECTION_COMPONENT			"LotusSystemServices\\4.0"
#else
#define SECTION_COMPONENT			"SystemServices\\4.0"
#endif
#define SECTION_DEFAULT				SECTION_EXTENSION
#define SECTION_DEFAULT_CODE		"x"

//---------------------------------------------------------------------------
//
// PROTOTYPES
//
//---------------------------------------------------------------------------

typedef LSPTR(struct LSXREGINFO) PLSXREGINFO;
typedef struct LSXREGINFO
{
	int bAdd;
	int bDelete;
	int bGet;
	int bList;
	int bHelp;
	char section[MAX_VALUE_NAME];
	char key[MAX_VALUE_NAME];
	char val[MAX_DATA_LEN];
} LSXREGINFO;
//}}

// forward references to other classes
class CView;
class CAgent;

class CVMRegistry : public LSXBase
//{{LSX_AUTHOR_CODE_Additional_Base_Classes
//}}
{
   protected:

      // Data members exposed to LotusScript via Get/Set Prop (access functions inlined below)


      //{{LSX_AUTHOR_CODE_Protected_Internal
      //}}

   private:

      //{{LSX_AUTHOR_CODE_Private_Internal
	  PLSSSRVMGR			pSRVMGR;	//	system services manager
	  PLSSPLAT  			pPLAT;		//  system platform manager
      //}}

      // These are private because they are unimplemented and we need to prevent
      // the compiler from creating default versions.
      CVMRegistry & operator = (CVMRegistry&);
      CVMRegistry (const CVMRegistry&);
      CVMRegistry();

   public:

      // This constructor is called when the script "new"s one or calls
      // a function like "CreateCVMRegistry" on the container class.
      CVMRegistry( LSPTR(LSXLsiSession) pContainer);

      // This constructor is used by a derived class to initialize its parent
      CVMRegistry(LSUSHORT classId, LSPTR(LSXLsiSession) pContainer );

      virtual ~CVMRegistry();


      // Methods exposed to LotusScript
      LSSSHORT AddKey ( LSXString& KeyName , LSXString& KeyValue , LSSSHORT KeySection = LS_EXTENSION );
      LSSSHORT DeleteKey ( LSXString& KeyName , LSSSHORT KeySection = LS_EXTENSION );
      LSXString GetKey ( LSXString& KeyName , LSSSHORT KeySection = LS_EXTENSION );
      LSXString ListSection ( LSSSHORT KeySection = LS_EXTENSION );
      LSSSHORT SelfRegister ( LSXString& KeyName , LSXString& KeyValue  );

      // Event-Raising methods

      
      // Helper functions - not exposed to LotusScript

      LSPTR(LSXLsiSession) LSXGetSession() const
      { 
         return ((LSPTR(LSXLsiSession)) pContainerObject)->LSXGetSession(); 
      }

      //{{LSX_AUTHOR_CODE_Public_Internal (not exposed to LotusScript)
      //}}

      // Low-level calls defined in iCVMRegistry.CPP.
      virtual LSSTATUS LSXDispatchMethod(PLSADTMSGMETHOD args);
      virtual LSSTATUS LSXGetProp( PLSADTINSTDESC pinstdesc, PLSADTMSGPROP param);
      virtual LSSTATUS LSXSetProp( PLSADTINSTDESC pinstdesc, PLSADTMSGPROP param);


      // Property Gets and Sets for data members exposed to LotusScript


      //{{LSX_AUTHOR_CODE_Inlines
      //}}
};

//{{LSX_AUTHOR_CODE_Other
//}}

#endif   //   #if !defined (CVMREGISTRY_HPP)

