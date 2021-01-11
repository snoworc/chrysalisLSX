/*=============================================================================*\

   Copyright Lotus Development Corp. 1995 - 1999


   The enclosed code created by Lotus Development Corporation, is
   sample code. This sample code is provided to you solely for the
   purpose of assisting you in the development of your LotusScript
   Extension (LSX) applications.

   File: CAgent.hpp

   Description:
      Class definition for scriptable "CAgent" object

\*==============================================================================*/
#if !defined (CAGENT_HPP)
#define CAGENT_HPP

//{{LSX_AUTHOR_CODE_Include1
// PARM DOC FIELDS
#define FIELD_AGENTNAME "AgentName"
#define FIELD_ASSISTSEARCH "AssistSearch"
#define FIELD_ASSISTTRIGGER "AssistTrigger"
#define FIELD_COMMENT "Comment"
#define FIELD_ENDHOUR "EndHour"
#define FIELD_ENDMINUTE "EndMinute"
#define FIELD_INTERVAL "Interval"
#define FIELD_INTERVALTYPE "IntervalType"
#define FIELD_ISENABLED "IsEnabled"
#define FIELD_ISHIDDEN "IsHidden"
#define FIELD_ISNEWCOPY "IsNewCopy"
#define FIELD_ISPRIVATE "IsPrivate"
#define FIELD_ODSFLAGS "ODSFlags"
#define FIELD_RUNONSERVER "RunOnServer"
#define FIELD_STARTHOUR "StartHour"
#define FIELD_STARTMINUTE "StartMinute"
//}}

#include "lsxapplx.h"
#include "lsxbase.hpp"
#include "lsxsess.hpp"

class CAgent;

typedef LSXObjectArray<CAgent, CCHRYSALIS_CAGENT_ID> CAgentArray;

//{{LSX_AUTHOR_CODE_Include2
//}}

// forward references to other classes
class CView;
class CVMRegistry;

class CAgent : public LSXBase
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
//	  NotesDatabase m_LSXDB;
      //}}

      // These are private because they are unimplemented and we need to prevent
      // the compiler from creating default versions.
      CAgent & operator = (CAgent&);
      CAgent (const CAgent&);
      CAgent();

   public:

      // This constructor is called when the script "new"s one or calls
      // a function like "CreateCAgent" on the container class.
      CAgent( LSPTR(LSXLsiSession) pContainer, NotesDocument& parmDoc );

      // This constructor is used by a derived class to initialize its parent
      CAgent(LSUSHORT classId, LSPTR(LSXLsiSession) pContainer, NotesDocument& parmDoc  );

      virtual ~CAgent();


      // Methods exposed to LotusScript
      LSXBool BuildAgent (  );
      NotesDocument ReadAgent ( NotesAgent& nAgent  );

      // Event-Raising methods

      
      // Helper functions - not exposed to LotusScript

      LSPTR(LSXLsiSession) LSXGetSession() const
      { 
         return ((LSPTR(LSXLsiSession)) pContainerObject)->LSXGetSession(); 
      }

      //{{LSX_AUTHOR_CODE_Public_Internal (not exposed to LotusScript)
	  BOOL HasItem( char *szItemName );
	  STATUS GetText( char *szItemName, char *retValue );	  
	  STATUS SetAgentInfo( NOTEHANDLE hAgent, ODS_ASSISTSTRUCT AgentInfo );
	  STATUS SetAgentTrigger( NOTEHANDLE hAgent, WORD wTrigger );
	  STATUS SetAgentAssistFlags( NOTEHANDLE hAgent, char *szFlags );
	  STATUS SetAgentLastInfo( NOTEHANDLE hAgent );
	  STATUS SetAgentVersion( NOTEHANDLE hAgent );
	  STATUS SetAgentType ( NOTEHANDLE hAgent, WORD wActionType );
	  STATUS SetAgentMachineName( NOTEHANDLE hAgent );
	  STATUS SetAgentMachineName( NOTEHANDLE hAgent, char *szMachineName );
	  STATUS SetAgentComment( NOTEHANDLE hAgent, char *szComment );
      //}}

      // Low-level calls defined in iCAgent.CPP.
      virtual LSSTATUS LSXDispatchMethod(PLSADTMSGMETHOD args);
      virtual LSSTATUS LSXGetProp( PLSADTINSTDESC pinstdesc, PLSADTMSGPROP param);
      virtual LSSTATUS LSXSetProp( PLSADTINSTDESC pinstdesc, PLSADTMSGPROP param);


      // Property Gets and Sets for data members exposed to LotusScript


      //{{LSX_AUTHOR_CODE_Inlines
      //}}
};

//{{LSX_AUTHOR_CODE_Other
//}}

#endif   //   #if !defined (CAGENT_HPP)

