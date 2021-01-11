/*=============================================================================*\

   Copyright Lotus Development Corp. 1995 - 1999

   The enclosed code created by Lotus Development Corporation, is
   sample code. This sample code is provided to you solely for the
   purpose of assisting you in the development of your LotusScript
   Extension (LSX) applications.

   File: CAgent.cpp

   Description:
      Implementation of methods for the scriptable "CAgent" object

\*============================================================================*/

//{{LSX_AUTHOR_CODE_Include_1
//}}

#include "CAgent.hpp"

// includes for the objects defined in your LSX
#include "CView.hpp"
#include "CVMRegistry.hpp"

//{{LSX_AUTHOR_CODE_Include_2
//}}

#if defined (OS390) || (defined (OS400) && defined(__STRING_CODE_SET__))
/* This must be the last #include */
#include <_Ascii_a.h>
#endif

/*******************************************************************************
 *
 * Constructors/Destructors
 *
 ******************************************************************************/
// This constructor is called when the script 'new's one or calls
// CreateCAgent on the container class.

CAgent:: CAgent( LSPTR(LSXLsiSession) pContainer, NotesDocument& parmDoc)
   : LSXBase((LSPLTSTR)"CAgent", pContainer->LSXGetInstance(), CCHRYSALIS_CAGENT_ID, pContainer)
   //{{LSX_AUTHOR_CODE_Additional_Base_Class_Init1
   //}}

   //{{LSX_AUTHOR_CODE_Internal_Member_Init1
   //}}
{
   //{{LSX_AUTHOR_CODE_Constructor1
	m_noteHandle = (NOTEHANDLE)parmDoc.GetProp(CNOTES_NPROP_HANDLE).getLong();
//	m_LSXDB = parmDoc.GetProp(CNOTES_NPROP_PARENTDB).getForeignObject();
	NSFNoteGetInfo(m_noteHandle, _NOTE_DB, &m_DBHandle);	// handle to DB	
	NSFNoteGetInfo(m_noteHandle, _NOTE_ID, &m_nid);			// handle to NOTEID

	try {
		pContainer->GetLNNotesSession().GetDatabase(m_DBHandle, &m_LNDB);		
		m_LNDB.Open();				
	}
	catch (LNSTATUS Lnerror) {
		char errorBuf[128];
		LNGetErrorMessage(Lnerror, errorBuf, 128);
		LSXSetErrorCode(LSX_ERROR);
		#if defined (TRACE)
			LSXTraceString("Error during construction:");
			LSXTraceString((LSXString)errorBuf);
		#endif //TRACE
	}
   //}}

}

// ------------------------------------------------------------------------------

// This version of the constructor is called by a derived class for its 
// constructor initialization.

CAgent:: CAgent(LSUSHORT classId, LSPTR(LSXLsiSession) pContainer, NotesDocument& parmDoc )
   : LSXBase((LSPLTSTR)"CAgent", pContainer->LSXGetInstance(), classId, pContainer)
   //{{LSX_AUTHOR_CODE_Additional_Base_Class_Init2
   //}}

   //{{LSX_AUTHOR_CODE_Internal_Member_Init2
   //}}
{
   //{{LSX_AUTHOR_CODE_Constructor2
	assert(LSFALSE);
   //}}

}

//------------------------------------------------------------------------------
//{{LSX_AUTHOR_CODE_Additional_Constructors
//}}
//------------------------------------------------------------------------------

CAgent:: ~CAgent()
{
   //{{LSX_AUTHOR_CODE_Destructor
	m_DBHandle = m_noteHandle = 0;

	try {
   	// give up the database handle so that LotusScript thinks it is the sole owner
	// of this memory
		m_LNDB.GetDatabaseHandle();

		// close the C++ ln_db object - this will not cause Notes to free the memory
	// associated with the ln_db object
	// Note: This call cleans up all the C++ objects contained in the ln_db object
	//       and frees up lots of memory.  This could be done whenever you no longer
	//		   need the C++ represention of the database and it's contained objects
		m_LNDB.Close();
	}

	catch(LNSTATUS error) {
		char errorBuf[LNERROR_MESSAGE_LENGTH];
		LNGetErrorMessage(error, errorBuf);
		#if defined (TRACE)
			LSXTraceString((LSXString)errorBuf);
		#endif   // TRACE
	}

   //}}

   

}

/*******************************************************************************
 *
 * Method Definitions for methods that are exposed to LotusScript
 *
 *******************************************************************************/
LSXBool CAgent::BuildAgent()
{
   //{{LSX_AUTHOR_CODE_Method_BuildAgent
	//  C Core API Objects
	STATUS cstatus;
	char szAgentName[DESIGN_MACRO_MAX];
	char szComment[DESIGN_COMMENT_MAX];
	char szAsstFlags[DESIGN_FLAGS_MAX];
	char szMachineName[MAXUSERNAME+1];
	NOTEID agentid;    
	NOTEHANDLE hAgent;    	
	ODS_ASSISTSTRUCT AgentInfo;
	WORD starthr,startmin,endhr,endmin,intervaltype,interval,triggertype,searchtype,
		 isenabled,isprivate,ishidden,isnewcopy;
	DWORD odsflags=0;
	int iNumAsstFlags=0;

	// C++ Core API Objects
	LNSTATUS status;
	LNText agentName;
	LNString agentVal;
	LNAgent LNAgt;
	LNNumbers startHr,startMin,endHr,endMin,assistInterval,intervalType,odsFlags,
			  triggerType,searchType,isEnabled,isPrivate,isHidden,isNewCopy;
	LNDocument LNDoc;

	// LSX Core Objects
	LSXBool retVal = LSXFalse;
	
	try {
		if (m_LNDB.IsOpen()) {			
			m_LNDB.GetDocument(m_nid, &LNDoc);			
			LNDoc.Open();
			if (HasItem(FIELD_AGENTNAME)) {
				#if defined (TRACE)
					/*******/ LSXTraceString("Found agentname value");
				#endif
				LNDoc.GetItem(FIELD_AGENTNAME, &agentName);
				agentName.GetText(&agentVal);	
				if (m_LNDB.AgentExists(agentVal)) {
					#if defined (TRACE)
						/*******/ LSXTraceString("Agent exists.");
					#endif

					m_LNDB.GetAgent(agentVal, &LNAgt);
					if ((status=LNAgt.Open())==FALSE) {;
						#if defined (TRACE)
							/*******/ LSXTraceString("Agent Opened with C++ API");
						#endif
						agentid = LNAgt.GetNoteID();
						LNAgt.Close();
						strcpy(szAgentName, agentVal.GetTextPtr());
						#if defined (TRACE)
							/*******/ LSXTraceString(szAgentName);
						#endif
						cstatus = NSFNoteOpen(m_DBHandle, agentid,0, &hAgent);		
						#if defined (TRACE)
							/*******/ LSXTraceString("Agent Opened with C API");
						#endif				
	
						// *****************************
						// SET FIELDS (using C++ API to read parm fields)


						// -=-=-=-=-=-=-=-=-=-=-=-=-=
						// $COMMENT
						if (HasItem(FIELD_COMMENT)) {

							#if defined (TRACE)
							/*******/ LSXTraceString(FIELD_COMMENT);
							#endif			
							cstatus = GetText(FIELD_COMMENT, szComment);
							cstatus = SetAgentComment(hAgent, szComment);
						}
											

						// -=-=-=-=-=-=-=-=-=-=-=-=-=
						// $ASSISTINFO
						#if defined (TRACE)
						/*******/ LSXTraceString("Setting assist structure...");
						#endif
						// ++ Start Hour
						if (HasItem(FIELD_STARTHOUR)) {
							#if defined (TRACE)
							/*******/ LSXTraceString(FIELD_STARTHOUR);
							#endif							
							LNDoc.GetItem(FIELD_STARTHOUR, &startHr);
							starthr = (WORD)startHr[0];
							endhr = starthr; // default							
						}
						// ++ Start Minute
						if (HasItem(FIELD_STARTMINUTE)) {
							#if defined (TRACE)
							/*******/ LSXTraceString(FIELD_STARTMINUTE);
							#endif							
							LNDoc.GetItem(FIELD_STARTMINUTE, &startMin);
							startmin = (WORD)startMin[0];
							endmin = startmin; // default
						}
						// ++ End Hour
						if (HasItem(FIELD_ENDHOUR)) {
							#if defined (TRACE)
							/*******/ LSXTraceString(FIELD_ENDHOUR);
							#endif							
							LNDoc.GetItem(FIELD_ENDHOUR, &endHr);
							endhr = (WORD)endHr[0];							
						}
						// ++ End Minute
						if (HasItem(FIELD_ENDMINUTE)) {
							#if defined (TRACE)
							/*******/ LSXTraceString(FIELD_ENDMINUTE);
							#endif							
							LNDoc.GetItem(FIELD_ENDMINUTE, &endMin);
							endmin = (WORD)endMin[0];							
						}

						// ++ Assist Interval Type
						if (HasItem(FIELD_INTERVALTYPE)) {
							#if defined (TRACE)
							/*******/ LSXTraceString(FIELD_INTERVALTYPE);
							#endif							
							LNDoc.GetItem(FIELD_INTERVALTYPE, &intervalType);
							intervaltype = (WORD)intervalType[0];						
						}

						// ++ Assist Interval
						if (HasItem(FIELD_INTERVAL)) {
							#if defined (TRACE)
							/*******/ LSXTraceString(FIELD_INTERVAL);
							#endif							
							LNDoc.GetItem(FIELD_INTERVAL, &assistInterval);
							interval = (WORD)assistInterval[0];						
						}

						if (HasItem(FIELD_ODSFLAGS)) {
							#if defined (TRACE)
							/*******/ LSXTraceString(FIELD_ODSFLAGS);
							#endif							
							LNDoc.GetItem(FIELD_ODSFLAGS, &odsFlags);
							odsflags = (DWORD)odsFlags[0];						
						}

						if (HasItem(FIELD_ASSISTTRIGGER)) {
							#if defined (TRACE)
							/*******/ LSXTraceString(FIELD_ASSISTTRIGGER);
							#endif							
							LNDoc.GetItem(FIELD_ASSISTTRIGGER, &triggerType);
							triggertype = (WORD)triggerType[0];						
						}

						if (HasItem(FIELD_ASSISTSEARCH)) {
							#if defined (TRACE)
							/*******/ LSXTraceString(FIELD_ASSISTSEARCH);
							#endif							
							LNDoc.GetItem(FIELD_ASSISTSEARCH, &searchType);
							searchtype = (WORD)searchType[0];						
						}

						(void) memset (&AgentInfo, 0, sizeof(ODS_ASSISTSTRUCT)); 
						AgentInfo.wVersion = (WORD) 0;
						AgentInfo.wTriggerType = (WORD) triggertype;
						AgentInfo.wSearchType = (WORD) searchtype;
						AgentInfo.dwFlags = (DWORD) odsflags;
						AgentInfo.wIntervalType = (WORD) intervaltype;
						AgentInfo.wInterval = (WORD) interval;												
						AgentInfo.dwTime1 = (DWORD)((starthr * 60 + startmin) * TICKS_IN_MINUTE);
						AgentInfo.dwTime2 = (DWORD)((endhr * 60 + endmin) * TICKS_IN_MINUTE);
						cstatus = SetAgentInfo(hAgent, AgentInfo);


						// -=-=-=-=-=-=-=-=-=-=-=-=-=
						// $ASSISTTRIGGER
						cstatus = SetAgentTrigger((NOTEHANDLE) hAgent, (WORD) triggertype);


						// -=-=-=-=-=-=-=-=-=-=-=-=-=
						// $ASSISTTYPE
						// commenting out, already set in ODS_ASSISTSTRUCT
						//	cstatus = SetAgentType((NOTEHANDLE) hAgent, (WORD) triggertype);


						// -=-=-=-=-=-=-=-=-=-=-=-=-=
						// $ASSISTFLAGS
						//  I am not allowing users free reign over the assist flags
						//  Only a few options are allowed here
						if (HasItem(FIELD_ISENABLED)) {
							#if defined (TRACE)
							/*******/ LSXTraceString(FIELD_ISENABLED);
							#endif														
							LNDoc.GetItem(FIELD_ISENABLED, &isEnabled);
							isenabled = (WORD)isEnabled[0];	
							if (isenabled)
								szAsstFlags[iNumAsstFlags++] = ASSIST_FLAG_ENABLED;	
						}
						if (HasItem(FIELD_ISPRIVATE)) {
							#if defined (TRACE)
							/*******/ LSXTraceString(FIELD_ISPRIVATE);							
							#endif														
							LNDoc.GetItem(FIELD_ISPRIVATE, &isPrivate);
							isprivate = (WORD)isPrivate[0];	
							if (isprivate)
								szAsstFlags[iNumAsstFlags++] = ASSIST_FLAG_PRIVATE;	
						}
						if (HasItem(FIELD_ISHIDDEN)) {
							#if defined (TRACE)
							/*******/ LSXTraceString(FIELD_ISHIDDEN);
							#endif														
							LNDoc.GetItem(FIELD_ISHIDDEN, &isHidden);
							ishidden = (WORD)isHidden[0];	
							if (ishidden)
								szAsstFlags[iNumAsstFlags++] = ASSIST_FLAG_HIDDEN;	
						}
						if (HasItem(FIELD_ISNEWCOPY)) {
							#if defined (TRACE)
							/*******/ LSXTraceString(FIELD_ISNEWCOPY);
							#endif														
							LNDoc.GetItem(FIELD_ISNEWCOPY, &isNewCopy);
							isnewcopy = (WORD)isNewCopy[0];	
							if (isnewcopy)
								szAsstFlags[iNumAsstFlags++] = ASSIST_FLAG_NEWCOPY;	
						}
						if (triggertype == ASSISTTRIGGER_TYPE_SCHEDULED) {
							// I did not find this documented anywhere... but seems necessary - tbn
							#if defined (TRACE)
							/*******/ LSXTraceString("Adjusting assist trigger w/ trigger flag");
							#endif																
								szAsstFlags[iNumAsstFlags++] = 's';	
						}

						szAsstFlags[iNumAsstFlags] = '\0';
						cstatus = SetAgentAssistFlags(hAgent, szAsstFlags);
						

						// -=-=-=-=-=-=-=-=-=-=-=-=-=
						// $MachineName - Server to run on
						if (HasItem(FIELD_RUNONSERVER)) {
							#if defined (TRACE)
							/*******/ LSXTraceString("Setting $MachineName.");
							#endif
							cstatus = GetText(FIELD_RUNONSERVER, szMachineName);
							cstatus = SetAgentMachineName(hAgent, szMachineName);													
						}


						// -=-=-=-=-=-=-=-=-=-=-=-=-=
						// $AssistLastRun & $AssistDocCount - Clear out "Last Run" info
						#if defined (TRACE)
						/*******/ LSXTraceString("Clearing out last run info.");
						#endif														
						cstatus = SetAgentLastInfo(hAgent);


						// -=-=-=-=-=-=-=-=-=-=-=-=-=
						// $AGENTVERSION
						#if defined (TRACE)
						/*******/ LSXTraceString("Setting agent version.");
						#endif														
						cstatus = SetAgentVersion(hAgent);

						// -=-=-=-=-=-=-=-=-=-=-=-=-=
						// SIGN AGENT
						cstatus = NSFNoteSign((NOTEHANDLE)hAgent);
						#if defined (TRACE)
						/*******/ LSXTraceString("Finished NSFNoteSign");
						#endif

						// -=-=-=-=-=-=-=-=-=-=-=-=-=
						// SAVE AGENT
						cstatus = NSFNoteUpdate((NOTEHANDLE)hAgent, 0);
						#if defined (TRACE)
						/*******/ LSXTraceString("Finished NSFNoteUpdate");
						#endif


						// -=-=-=-=-=-=-=-=-=-=-=-=-=
						// CLOSE AGENT						
						cstatus = NSFNoteClose(hAgent);
						#if defined (TRACE)
						/*******/ LSXTraceString("Finished NSFNoteClose");
						#endif


					} else {
						#if defined (TRACE)
						/*******/ LSXTraceString("Agent could not be opened with the C++ API.");
						#endif
					}
				} else {
					#if defined (TRACE)
						/*******/ LSXTraceString("Agent does not exist.");
					#endif
				}
			}
		}
		LNDoc.Close();
	}
	catch(LNSTATUS error) {		
		char errorBuf[LNERROR_MESSAGE_LENGTH];
		LNGetErrorMessage(error, errorBuf);
		#if defined (TRACE)
			LSXTraceString((LSXString)errorBuf);			
		#endif   // TRACE
		retVal = LSXTrue;
	}	      

   return retVal;
   //}}
}
// -----------------------------------------------------------------------------
NotesDocument CAgent::ReadAgent(NotesAgent& nAgent)
{
   //{{LSX_AUTHOR_CODE_Method_ReadAgent
	return NotesDocument();
/*   
	try {
		#if defined (TRACE)
			LSXTraceString("ReadAgent");			
		#endif 

		NotesDocument parmDoc = m_LSXDB.CallFunction(CNOTES_DBMETH_CREATEDOC).getForeignObject();
		
		if (parmDoc.IsNull() == TRUE) {
			#if defined (TRACE)
				LSXTraceString("parmDoc is NULL");			
			#endif 
			return (NotesDocument());
		}
	
		//PLSVALUE pVal = LSNULL;
		LSXValue fldForm = LSXValue(LSI_DT_STRING, LsiInst);
		const LSXPltString C_FIELD_FORM = "Form";
		const LSXString C_FIELD_FORM_VAL = "FormValue";
		fldForm.set(C_FIELD_FORM);
		//LSXValue fldFormVal(LSI_DT_VARIANT, LsiInst);
		LSXValue fldFormVal = LSXValue(LSI_DT_ARRAYREF, LsiInst);
		LSXStringArray vals(1);
		vals[0] = C_FIELD_FORM_VAL;		
		fldFormVal.set((LSXStringArray&)vals);

	
		#if defined (TRACE)
			LSXTraceString("storing arg array");				
		#endif 
	
		LSXValue Args[] = 
		{
			fldForm,			
			fldFormVal,
			// additional argument would go here			
		};

		#if defined (TRACE)
			LSXTraceString("Args set... calling method");			
		#endif 

			
		NotesItem item = parmDoc.CallFunction(CNOTES_NMETH_REPLACEITEM, Args).getForeignObject();

			
		return (parmDoc);

	} catch(LNSTATUS error) {		
		char errorBuf[LNERROR_MESSAGE_LENGTH];
		LNGetErrorMessage(error, errorBuf);
		#if defined (TRACE)
			LSXTraceString((LSXString)errorBuf);			
		#endif   // TRACE
		return NotesDocument();
	}
*/
   //}}
}
/*******************************************************************************
 *
 * Internal Method Definitions
 *
 *******************************************************************************/
//{{LSX_AUTHOR_CODE_Internal_Methods
/************************************************************************

    FUNCTION:   HasItem

    PURPOSE:    Checks if item exists

    INPUTS:     char		*szItemName - name of item
               
	OUTPUTS:    returns BOOL
*************************************************************************/
BOOL CAgent::HasItem( char *szItemName ) {
	return (NSFItemIsPresent(m_noteHandle,szItemName,strlen(szItemName)));
}

/************************************************************************

    FUNCTION:   GetText

    PURPOSE:    Get the text value of a field

    INPUTS:     char		*szItemName - name of item
               
	OUTPUTS:    char		*retValue
				returns WORD Status
*************************************************************************/
STATUS CAgent::GetText( char *szItemName, char *retValue ) {
	return (NSFItemGetText(m_noteHandle,szItemName,retValue,strlen(retValue)));
}

/************************************************************************

    FUNCTION:   SetAgentInfo

    PURPOSE:    Append the $AssistInfo field for the Agent note being 
                created.  This value must be set to properly configured
                ODS_ASSISTSTRUCT record for the agent type.   This structure
                contains control information for the agent trigger type, 
                document search type, time interval and type and other 
                information.

    INPUTS:     NOTEHANDLE          hAgent      - handle to open agent note
                ODS_ASSISTSTRUCT    AgentInfo   - configured agent info 
                                                  structure
                                  
*************************************************************************/
STATUS CAgent::SetAgentInfo( NOTEHANDLE hAgent, ODS_ASSISTSTRUCT AgentInfo )
{
        STATUS          error = NOERROR;
        char            *pBuffer;
        HANDLE          hItem;
        DWORD           dwItemLen;
        BLOCKID         bhValue;
 
        /* Allocate an object to hold the ods object and its TYPE */
 
        dwItemLen = sizeof(WORD) + ODSLength(_ODS_ASSISTSTRUCT);
 
        if (error = OSMemAlloc(MEM_GROWABLE, dwItemLen, &hItem))
                return (error);
 
        pBuffer = (char *)OSLockObject(hItem);
 
        /* Set the TYPE word in HOST format */
 
        *((WORD *)pBuffer) = TYPE_ASSISTANT_INFO;
        pBuffer += sizeof(WORD);
 
        /* Now write out the structure */
 
        ODSWriteMemory(&pBuffer, _ODS_ASSISTSTRUCT, &AgentInfo, 1);
        OSUnlockObject(hItem);
 
        /* Create a BLOCKID and fill it */
 
        bhValue.pool = hItem;
        bhValue.block = NULLBLOCK;
 
		/*      Purge old structure  */
		NSFItemDelete(hAgent,
					  ASSIST_INFO_ITEM,
					  (WORD)strlen(ASSIST_INFO_ITEM));

        /*      Save the item to the note */
 
        if (error = NSFItemAppendByBLOCKID(hAgent, /* handle to note to append*/
                        ITEM_SIGN,                 /* item flags */
                        ASSIST_INFO_ITEM,          /* item name: "$AssistInfo" */
                       sizeof(ASSIST_INFO_ITEM)-1,/* item length */
                        bhValue,                   /* BLOCKID with value */
                        dwItemLen, NULL))          /* value length */
                {
                OSMemFree(hItem);
                return (error);
                }

    if (error)
    {
        printf("Error: unable to append AgentInfo item to Agent note.\n");
    }
    return (error);
}

/************************************************************************

    FUNCTION:   SetAgentTrigger

    PURPOSE:    Append the $AssistTrigger field for the Agent note being 
                created.  This value can be set to one of the following 
                constants based on the agent's event trigger.

                        ASSISTTRIGGER_TYPE_MANUAL       
                        ASSISTTRIGGER_TYPE_PASTED       
                        ASSISTTRIGGER_TYPE_DOCUPDATE
                        ASSISTTRIGGER_TYPE_NEWMAIL      
                        ASSISTTRIGGER_TYPE_SCHEDULED
                        ASSISTTRIGGER_TYPE_NONE         

    INPUTS:     NOTEHANDLE  hAgent      - handle to open agent note
                WORD        wTrigger    - trigger  type: must be one of the 
                                          above constants
                                  
*************************************************************************/
STATUS CAgent::SetAgentTrigger( NOTEHANDLE hAgent, WORD wTrigger )
{
	STATUS      error;
    char        cType;

    cType = (char)('0' + wTrigger);
    if (error = NSFItemSetText(
                hAgent,
                ASSIST_TRIGGER_ITEM,   /* "$AssistTrigger" */
                &cType, 
                (WORD)1))
    {
        printf("Error: unable to set AssistTrigger field in Agent note.\n");
    }
    return(error);    
}

/************************************************************************

    FUNCTION:   SetAgentAssistFlags

    PURPOSE:    Append the "$AssistFlags" field for the Agent note being 
                created.  The value can a combination of none to any of the 
                following flag constants.

                        ASSIST_FLAG_ENABLED
                        ASSIST_FLAG_HIDDEN      
                        ASSIST_FLAG_PRIVATE

    INPUTS:     NOTEHANDLE  hAgent      - handle to open agent note
                char        *szFlags    - zero-terminated string containing the
                                          appropriate combination of the above
                                          flags.

*************************************************************************/
STATUS CAgent::SetAgentAssistFlags( NOTEHANDLE hAgent, char *szFlags )
{
    STATUS      error;

	/*      Purge old structure  */
	NSFItemDelete(hAgent,
				  ASSIST_FLAGS_ITEM,
				  (WORD)strlen(ASSIST_FLAGS_ITEM));


    error = NSFItemAppend(
                hAgent,                             /* handle to note to append to */
                ITEM_SIGN | ITEM_SUMMARY,           /* item flags */
                ASSIST_FLAGS_ITEM,                  /* "$AssistFlags" */
                (WORD) strlen(ASSIST_FLAGS_ITEM),
                TYPE_TEXT,                          /* item type */
                szFlags,                            /* item value */
                (DWORD) strlen(szFlags));           /* value length */

    if (error)
    {
        printf("Error: unable to set AssistFlags field in Agent note.\n"); 
    }
    return (error);
}

/************************************************************************

    FUNCTION:   SetAgentLastInfo

    PURPOSE:    Append the initial "$AssistLastRun" and $AssistDocCount" 
                fields for the agent note being created.  The values get 
                updated by Domino and Notes after the agent has been executed 
				to the time date of the run and number of documents modified, 
                respectively.

    INPUTS:     NOTEHANDLE  hAgent      - handle to open agent note

*************************************************************************/
STATUS CAgent::SetAgentLastInfo(NOTEHANDLE hAgent)
{
    STATUS      error;
    TIMEDATE    EmptyTimeDate;
    NUMBER      DocCount = 0;

	/*      Purge old structure  */
	NSFItemDelete(hAgent,
				  ASSIST_LASTRUN_ITEM,
				  (WORD)strlen(ASSIST_LASTRUN_ITEM));

    /* set empty Last Run info */
    EmptyTimeDate.Innards[0] = (DWORD) 0;
    EmptyTimeDate.Innards[1] = (DWORD) 0;
    error = NSFItemAppend(
                hAgent,                             /* handle to note to append to */
                ITEM_SIGN | ITEM_SUMMARY,           /* item flags */
                ASSIST_LASTRUN_ITEM,                /* $AssistLastRun */
                (WORD) strlen(ASSIST_LASTRUN_ITEM),
                TYPE_TIME,                          /* item type */
                &EmptyTimeDate,                     /* item value */
                (DWORD) sizeof(EmptyTimeDate));     /* value length */

    if (error)
    {
        printf("Error: unable to set LastRun field of Agent note.\n");
    }


	/*      Purge old structure  */
	NSFItemDelete(hAgent,
				  ASSIST_DOCCOUNT_ITEM,
				  (WORD)strlen(ASSIST_DOCCOUNT_ITEM));

    /* set empty DocCountRun info */
    error = NSFItemAppend(
                hAgent,                             /* handle to note to append to */
                ITEM_SIGN | ITEM_SUMMARY,           /* item flags */
                ASSIST_DOCCOUNT_ITEM,               /* "$AssistDocCount" */
                (WORD) strlen(ASSIST_DOCCOUNT_ITEM),
                TYPE_NUMBER,                        /* item type */
                &DocCount,                          /* item value */
                (DWORD) sizeof(DocCount));          /* value length */

    if (error)
    {
        printf("Error: unable to set DocCount field of Agent note.\n");
    }
    return(error);
}
/************************************************************************

    FUNCTION:   SetAgentVersion

    PURPOSE:    Append the initial "$AssistVersion" field for the agent note
                being created.  The value is the current time date.

    INPUTS:     NOTEHANDLE  hAgent      - handle to open agent note

*************************************************************************/
STATUS CAgent::SetAgentVersion(NOTEHANDLE hAgent)
{
    STATUS      error;
    TIMEDATE        CurrTimeDate;

    OSCurrentTIMEDATE(&CurrTimeDate);
    if (error = NSFItemSetTime(hAgent, 
                      ASSIST_VERSION_ITEM,        /* "$AssistVersion" */
                      &CurrTimeDate))
    {
        printf("Error: unable to set Version field of Agent note.\n");
    }
    return(error);
}

/************************************************************************

    FUNCTION:   SetAgentType

    PURPOSE:    Append the "$AssistType" field for the agent note being 
                created.  This value can be one of the following signature
                constants, based on the the desired agent action.
    
                    ASSIST_SIG_ACTION_NONE
                    SIG_ACTION_FORMULA  
                    SIG_ACTION_LOTUSSCRIPT

    INPUTS:     NOTEHANDLE  hAgent      - handle to the open Agent note
                WORD        wActionType - one of the above actions

*************************************************************************/
STATUS CAgent::SetAgentType (NOTEHANDLE hAgent, WORD wActionType)
{
    STATUS      error;
    NUMBER      TempNumber;

	/*      Purge old structure  */
	NSFItemDelete(hAgent,
				  ASSIST_TYPE_ITEM,
				  (WORD)strlen(ASSIST_TYPE_ITEM));

    TempNumber = (NUMBER) wActionType;
    error = NSFItemAppend(
                hAgent,                        /* handle to note to append to */
                ITEM_SIGN | ITEM_SUMMARY,      /* item flags */
                ASSIST_TYPE_ITEM,              /* item name: "$AssistType" */
                (WORD) strlen(ASSIST_TYPE_ITEM),
                TYPE_NUMBER,                   /* item type */
                &TempNumber,                   /* item value */
                (DWORD) sizeof(TempNumber));   /* value length */

    if (error)
    {
        printf("Error: unable to set AssistType field in Agent note.\n");
    }
    return(error);
}
/************************************************************************

    FUNCTION:   SetAgentMachineName

    PURPOSE:    Append the "$MachineName" field for the Scheduled Agent note
                and set to the local machine.  For local, scheduled agents, 
                this value is the user name in canonical format.   
                
                Note that this item is used by scheduled and mail triggered 
                agents only.  This routine needs to be modified if supporting
                server names (e.g. mail triggered).

    INPUTS:     NOTEHANDLE  hAgent    - handle to the open Agent note
				(Optional) szMachineName - Value of the Run On Server

*************************************************************************/
STATUS CAgent::SetAgentMachineName( NOTEHANDLE hAgent )
{
    STATUS      error;
    char        szUserName[MAXUSERNAME+1];
      
    /* get local machine name */
    if (error = SECKFMGetUserName(szUserName))
    {
        printf("Error: unable to get user name from ID file.\n");
        return(error);
    }

	/*      Purge old structure  */
	NSFItemDelete(hAgent,
				  FILTER_MACHINE_ITEM,
				  (WORD)strlen(FILTER_MACHINE_ITEM));

    error = NSFItemAppend(
                hAgent,                             /* handle to note to append to */
                ITEM_SIGN | ITEM_SUMMARY,           /* item flags */
                FILTER_MACHINE_ITEM,                /* "$MachineName" */
                (WORD) strlen(FILTER_MACHINE_ITEM),
                TYPE_TEXT,                          /* item type */
                szUserName,                         /* item value */
                (DWORD) strlen(szUserName));        /* value length */

    if (error)
    {
        printf("Error: unable to set Machine Name field in Agent note.\n");
    }

    return(error);
}

STATUS CAgent::SetAgentMachineName( NOTEHANDLE hAgent, char *szMachineName )
{
    STATUS      error;
          
	/*      Purge old structure  */
	NSFItemDelete(hAgent,
				  FILTER_MACHINE_ITEM,
				  (WORD)strlen(FILTER_MACHINE_ITEM));

    error = NSFItemAppend(
                hAgent,                             /* handle to note to append to */
                ITEM_SIGN | ITEM_SUMMARY,           /* item flags */
                FILTER_MACHINE_ITEM,                /* "$MachineName" */
                (WORD) strlen(FILTER_MACHINE_ITEM),
                TYPE_TEXT,                          /* item type */
                szMachineName,                         /* item value */
                (DWORD) strlen(szMachineName));        /* value length */

    if (error)
    {
        printf("Error: unable to set Machine Name field in Agent note.\n");
    }

    return(error);
}

/************************************************************************

    FUNCTION:   SetAgentComment

    PURPOSE:    Append the "$Comment" field for the agent note being created.
                The value is a short description of the agent.

    INPUTS:     NOTEHANDLE  hAgent      - handle to open agent note
                char        *szComment  - agent description comment

*************************************************************************/
STATUS CAgent::SetAgentComment( NOTEHANDLE hAgent, char *szComment )
{
	STATUS error;
							
	error = NSFItemDelete((NOTEHANDLE)hAgent,
						  FILTER_COMMENT_ITEM,
						  (WORD ) strlen(FILTER_COMMENT_ITEM));

	error = NSFItemAppend((NOTEHANDLE)hAgent,
						  ITEM_SIGN | ITEM_SUMMARY,
						  FILTER_COMMENT_ITEM,
						  (WORD) strlen(FILTER_COMMENT_ITEM),
						  TYPE_TEXT,
						  szComment,
						  (DWORD) strlen(szComment));

	if (error)
    {
        printf("Error: unable to set Machine Name field in Agent note.\n");
    }

	return(error);
}
//}}

