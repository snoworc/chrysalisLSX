/*=============================================================================*\

   Copyright Lotus Development Corp. 1995 - 1999

   The enclosed code created by Lotus Development Corporation, is
   sample code. This sample code is provided to you solely for the
   purpose of assisting you in the development of your LotusScript
   Extension (LSX) applications.

   File: iCView.cpp

   Description:
      Class methods to support LSX architecture.

\*============================================================================*/

#include "CView.hpp"

#include "CVMRegistry.hpp"
#include "CAgent.hpp"

#if defined (OS390) || (defined (OS400) && defined(__STRING_CODE_SET__))
/* This must be the last #include */
#include <_Ascii_a.h>
#endif

/*******************************************************************************
 *
 *   Expanded class support (only if this class is expanded)
 *
 *******************************************************************************/

/*******************************************************************************
 *
 *   Containment support (only if this class is a container)
 *
 *******************************************************************************/

/*******************************************************************************
 *
 *   Collection support (only if this class is a collection)
 *
 *******************************************************************************/

/*******************************************************************************
 *
 *   Property Dispatching
 *
 *******************************************************************************/

LSSTATUS CView:: LSXGetProp(PLSADTINSTDESC pInstDesc, PLSADTMSGPROP param)
{
   LSSTATUS     stat = LSX_OK;
   LSADTPROPID  id   = param->idProp;

   LSXValue Val(param->valProp, LsiInst);

      stat = LSI_ERR_UNAVAIL;
      assert(LSFALSE);
   return stat;
}

//------------------------------------------------------------------------------

LSSTATUS CView:: LSXSetProp(PLSADTINSTDESC pInstDesc, PLSADTMSGPROP param)
{
   LSSTATUS     stat = LSX_OK;
   LSADTPROPID  id   = param->idProp;

   LSXValue Val(param->valProp, LsiInst);

      stat = LSI_ERR_UNAVAIL;
      assert(LSFALSE);
   return stat;
}

/*******************************************************************************
 *
 *   Method Dispatching and Argument Parsing
 *
 *******************************************************************************/
LSSTATUS CView:: LSXDispatchMethod(PLSADTMSGMETHOD args)
{
   LSSTATUS stat = LSX_OK;

   // using the given method id, call the appropriate class method

   switch (args->idMeth)
   {
   case CCHRYSALIS_CVIEWMETHOD_BUILDVIEW:
      { //Force a new scope so we can repeat variable names in each case

      //Initialize the args object
      LSXArgs ArgList(args, FUNCTION, LsiInst);

      
      
      //Execute the method
      LSXBool RetVal = BuildView();

      //Set return value
      ArgList.setRetVal(RetVal);
      
      }
      break;


   // list any other methods that you are exposing to the users of your LSX

   default:
      /*
      ** Either we have been passed
      **    (i) a bogus method id from LS, or,
      **   (ii) the method id of one of the parent class's methods (ie. this
      **        class is derived from a parent class).
      **
      ** If situation (i) then we need to determine why we have been passed
      ** the bad method id and fix the problem. This could occur if we changed
      ** the id's that we register with LS and did not tell LS at registration
      ** time that they had changed - by updating the version number.
      ** If you have changed the id's  you MUST recompile the script.
      **
      ** In that case, we should fail, thus:

         stat = LSI_RTE_SubOrFunctionNotDefined;
         assert (LSFALSE);

      ** If situation (ii) then we need to pass the method id on to the
      ** parent class dispatch method.  If the parent class is one of
      ** your own classes, you can code the call thus:

         stat = CView::LSXDispatchMethod(args);

      ** If the parent class is one of the Notes back-end classes, then
      ** we need to pass the method id and args block on to his dispatch
      ** method. ie. pretend we are LotusScript.

         stat = pADT->ClassControl(this->LSXGetInstance(),
                                  LSI_ADTMSG_METHOD,
                                  this->LSXGetADTInstDesc(),
                                  (LSPTR(void))args);

      ** In order to use this call successfully, we will need to have cached
      ** a pointer to the "real" corresponding Notes back-end object.
      ** For an example of how this is done, see the LSXBEPlus sample
      ** (NotesDbPlus.CPP & iNotesDbPlus.CPP)
      */

      stat = LSI_RTE_SubOrFunctionNotDefined;
      assert (LSFALSE);
      break;
   }

   return stat;
}
/*******************************************************************************
 *
 *   Event Raising Method Definitions
 *
 *******************************************************************************/

