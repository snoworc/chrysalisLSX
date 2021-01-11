/*=============================================================================*\

   Copyright Lotus Development Corp. 1995 - 1999

   The enclosed code created by Lotus Development Corporation, is
   sample code. This sample code is provided to you solely for the
   purpose of assisting you in the development of your LotusScript
   Extension (LSX) applications.

   File: CVMRegistry.cpp

   Description:
      Implementation of methods for the scriptable "CVMRegistry" object

\*============================================================================*/

//{{LSX_AUTHOR_CODE_Include_1
//}}

#include "CVMRegistry.hpp"

// includes for the objects defined in your LSX
#include "CView.hpp"
#include "CAgent.hpp"

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
// CreateCVMRegistry on the container class.

CVMRegistry:: CVMRegistry( LSPTR(LSXLsiSession) pContainer)
   : LSXBase((LSPLTSTR)"CVMRegistry", pContainer->LSXGetInstance(), CCHRYSALIS_CVMREGISTRY_ID, pContainer)
   //{{LSX_AUTHOR_CODE_Additional_Base_Class_Init1
   //}}

   //{{LSX_AUTHOR_CODE_Internal_Member_Init1
   //}}
{
   //{{LSX_AUTHOR_CODE_Constructor1
	pSRVMGR	= LSICALL(Services->pSRVMGR);
	pPLAT	= LSICALL(Services->pPLAT);
   //}}

}

// ------------------------------------------------------------------------------

// This version of the constructor is called by a derived class for its 
// constructor initialization.

CVMRegistry:: CVMRegistry(LSUSHORT classId, LSPTR(LSXLsiSession) pContainer )
   : LSXBase((LSPLTSTR)"CVMRegistry", pContainer->LSXGetInstance(), classId, pContainer)
   //{{LSX_AUTHOR_CODE_Additional_Base_Class_Init2
   //}}

   //{{LSX_AUTHOR_CODE_Internal_Member_Init2
   //}}
{
   //{{LSX_AUTHOR_CODE_Constructor2
   //}}

}

//------------------------------------------------------------------------------
//{{LSX_AUTHOR_CODE_Additional_Constructors
//}}
//------------------------------------------------------------------------------

CVMRegistry:: ~CVMRegistry()
{
   //{{LSX_AUTHOR_CODE_Destructor
	pSRVMGR	= LSNULL;
	pPLAT	= LSNULL;
   //}}

   

}

/*******************************************************************************
 *
 * Method Definitions for methods that are exposed to LotusScript
 *
 *******************************************************************************/
LSSSHORT CVMRegistry::AddKey(LSXString& KeyName, LSXString& KeyValue, LSSSHORT KeySection)
{
   //{{LSX_AUTHOR_CODE_Method_AddKey
	PLSXREGINFO	pInfo = (PLSXREGINFO)malloc(sizeof(LSXREGINFO));
	LSSSHORT		retcode = 0;

	memset(pInfo, 0, sizeof(LSXREGINFO));

	//	Copy registry Key name
	strcpy(pInfo->key, KeyName);

	// Copy full pathname of the LSX DLL location
	strcpy(pInfo->val, KeyValue);

	// OPTIONAL: LSX Registry Section
	switch (KeySection)
	{
	  case LS_SERVICES:
         strcpy(pInfo->section, SECTION_COMPONENT);
         break;
      case LS_EXTENSION:
         strcpy(pInfo->section, SECTION_EXTENSION);
         break;
      default:
         strcpy(pInfo->section, SECTION_DEFAULT);		
	}
	
	retcode = pSRVMGR->ServiceSetRegistryString(
											pInfo->section, pInfo->key, pInfo->val);

   //Set the function return value here.
	LSSSHORT retVal = (LSSSHORT) (retcode) ? LS_VAL_TRUE : LS_VAL_FALSE;
   
	free(pInfo);

//	if (retcode == 0)
//		LSXRaiseError(ERR_REGISTRY_OPEN_REGISTRY_FAILED);

   return retVal;
   //}}
}
// -----------------------------------------------------------------------------
LSSSHORT CVMRegistry::DeleteKey(LSXString& KeyName, LSSSHORT KeySection)
{
   //{{LSX_AUTHOR_CODE_Method_DeleteKey
	PLSXREGINFO pInfo = (PLSXREGINFO)malloc(sizeof(LSXREGINFO));
	LSSSHORT	retcode = 0;

	// Copy Key name	
	strcpy(pInfo->key, KeyName);

	// OPTIONAL: LSX Registry Section
    switch (KeySection)
    {
      case LS_SERVICES:
         strcpy(pInfo->section, SECTION_COMPONENT);
         break;
      case LS_EXTENSION:
         strcpy(pInfo->section, SECTION_EXTENSION);
         break;
      default:
         strcpy(pInfo->section, SECTION_DEFAULT);		
	}

	retcode = pSRVMGR->ServiceSetRegistryString(
												pInfo->section, pInfo->key, 0);

	memset(pInfo, 0, sizeof(LSXREGINFO));

   //Set the function return value here.
	LSSSHORT retVal = (LSSSHORT)(retcode) ? LS_VAL_TRUE : LS_VAL_FALSE;
   
	free(pInfo);

//	if (retcode == 0)
//		this->LSXRaiseError(ERR_REGISTRY_DELETE_REGISTRY_KEY_FAILED);
   
   return retVal;
   //}}
}
// -----------------------------------------------------------------------------
LSXString CVMRegistry::GetKey(LSXString& KeyName, LSSSHORT KeySection)
{
   //{{LSX_AUTHOR_CODE_Method_GetKey
  	LSXString	strTempBuffer;
	PLSXREGINFO pInfo = (PLSXREGINFO)malloc(sizeof(LSXREGINFO));
	
	memset(pInfo, 0, sizeof(LSXREGINFO));

	// Arg 1 is Key name	
	strcpy(pInfo->key, KeyName);

	// OPTIONAL: LSX Registry Section
    switch (KeySection)
    {
      case LS_SERVICES:
         strcpy(pInfo->section, SECTION_COMPONENT);
         break;
      case LS_EXTENSION:
         strcpy(pInfo->section, SECTION_EXTENSION);
         break;
      default:
         strcpy(pInfo->section, SECTION_DEFAULT);		
	}

	pSRVMGR->ServiceGetRegistryString(pInfo->section, pInfo->key, "", pInfo->val, LSS_MAX_REGISTRY_VAL_LEN);

	strTempBuffer = "Key ";
	strTempBuffer += pInfo->key;
	strTempBuffer += "-> ";
	strTempBuffer += pInfo->val;
   
	free(pInfo);

   return strTempBuffer; 
   //}}
}
// -----------------------------------------------------------------------------
LSXString CVMRegistry::ListSection(LSSSHORT KeySection)
{
   //{{LSX_AUTHOR_CODE_Method_ListSection
   LSXString	strTempBuffer;
   PLSXREGINFO pInfo = (PLSXREGINFO)malloc(sizeof(LSXREGINFO));
 
   memset(pInfo, 0, sizeof(LSXREGINFO));
	// OPTIONAL: LSX Registry Section
   switch (KeySection)
   {
      case LS_SERVICES:
         strcpy(pInfo->section, SECTION_COMPONENT);
         break;
      case LS_EXTENSION:
         strcpy(pInfo->section, SECTION_EXTENSION);
         break;
      default:
         strcpy(pInfo->section, SECTION_DEFAULT);		
	}

	LSPLTSTR section = pInfo->section;
	
	ENUMINFO info;
	LSREGISTRYENUMHANDLE handle =
				pSRVMGR->ServiceEnumRegistryBegin(section);

	if (!handle)
	{
		strTempBuffer = "Error opening section: ";
		strTempBuffer += section;
		strTempBuffer += ".  Section may not exist yet.";
	}
	else
	{
		strTempBuffer = "List of Section: ";
		strTempBuffer += section;
		strTempBuffer += "\n";

		while (pSRVMGR->ServiceEnumRegistryNext(handle, &info))
		{
			strTempBuffer += info.key;
			strTempBuffer += ":";
			strTempBuffer += info.val;
			strTempBuffer += "\n";
		}
		pSRVMGR->ServiceEnumRegistryEnd(handle);
	}

	#if 0
		//Output the registry in a messagebox
		pPLAT->MsgBox (strTempBuffer, 0, "LSX System Register");
	#endif

	free(pInfo);

   return strTempBuffer;
   //}}
}
// -----------------------------------------------------------------------------
LSSSHORT CVMRegistry::SelfRegister(LSXString& KeyName, LSXString& KeyValue)
{
   //{{LSX_AUTHOR_CODE_Method_SelfRegister
	LSSSHORT status = (LSSSHORT)0;	
	LSXString tkey = this->GetKey(KeyName);
	if (tkey.getLength() > 0) { 
		// Key was found. Remove old mapping.
		status = this->DeleteKey(KeyName);
	}

	status = this->AddKey(KeyName, KeyValue);

	return status;
   //}}
}
/*******************************************************************************
 *
 * Internal Method Definitions
 *
 *******************************************************************************/
//{{LSX_AUTHOR_CODE_Internal_Methods
//}}

