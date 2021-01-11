/* ======================================================================== *\

   Copyright Lotus Development Corp. 1995 - 1999

   The enclosed code created by Lotus Development Corporation, is
   sample code.  This sample code is provided to you solely for the
   purpose of assisting you in the development of your Lotus Software
   Extension (LSX) applications.

   File: textstr.h

   Description:
      The contents of this file will be very different for each different
      client application (LSX).  It contains client application specific
      definitions.
      However, the structure of the file will essentially be the same.
      The file contains #define's for each of the clients class elements
      (class names, property names, method names, event names, etc.).

\*========================================================================*/

#if !defined (TEXTSTR_H)
#define TEXTSTR_H

/*
   These constants segment the address space for string ids.  If two LSXs
   are being used in the same script and the ids for the elements overlap,
   you will get a USELSX error when the LotusScript host attempts to load
   the 2nd LSX.  Use the Project document in the Wizard to change this
   number.  Also, keep in mind that whenever this number is changed, all
   scripts that use the LSX must be recompiled.
*/

const LSUSHORT LSXBASE_NAMES = 300; // Where to start numbering ids for this LSX


const LSUSHORT CCHRYSALIS_NOCLASS_ID = CNOTES_CLASS_LAST_ID;

// even though we don't expose the SESSION object, it needs an ID

const LSUSHORT CCHRYSALIS_SESSION_ID = CCHRYSALIS_NOCLASS_ID+1;

const LSUSHORT CCHRYSALIS_CVIEW_ID = (CCHRYSALIS_NOCLASS_ID+2);
const LSUSHORT CCHRYSALIS_CVMREGISTRY_ID = (CCHRYSALIS_NOCLASS_ID+3);
const LSUSHORT CCHRYSALIS_CAGENT_ID = (CCHRYSALIS_NOCLASS_ID+4);


const LSUSHORT LSX_FIRST_CLASS = CNOTES_CLASS_FIRST_ID;
const LSUSHORT LSX_LAST_CLASS  = CCHRYSALIS_CAGENT_ID;

#if defined (OLE_PLATFORM)

// this class id is for the hidden OLE Session object

const LSUSHORT LSX_OLE_CLASS = LSX_LAST_CLASS +1;

// since we don't expose the SESSION object, we need to use the top-level
// class ID for OLE automation

const LSUSHORT LSX_OLEMAIN_CLASS = CCHRYSALIS_CVIEW_ID;

#endif   // (OLE_PLATFORM)



/* for methods/properties which return objects */
#define LSX_CLASS_RET(x)        (DT_CLIENT_OBJECT(x))

/* for methods which take adt arguments        */
#define LSX_CLASS_ARG(x)        (LSX_CLASS_RET(x))

/* for collection class registration           */
#define LSX_COLL_CLASS_ITEM(x)  (LSX_CLASS_RET(x))

/*
*  Class method/property/event etc names are #define'd beginning
*  with CCHRYSALIS, and are incremented up from LSXBASE_NAMES.
*
*/

#define CCHRYSALIS_CVIEWMETHOD_BUILDVIEW       (LSXBASE_NAMES+2)
#define CCHRYSALIS_CVIEWMETHOD_NEW       (LSXBASE_NAMES+1)
#define CCHRYSALIS_CVMREGISTRYMETHOD_ADDKEY       (LSXBASE_NAMES+15)
#define CCHRYSALIS_CVMREGISTRYMETHOD_DELETEKEY       (LSXBASE_NAMES+14)
#define CCHRYSALIS_CVMREGISTRYMETHOD_GETKEY       (LSXBASE_NAMES+13)
#define CCHRYSALIS_CVMREGISTRYMETHOD_LISTSECTION       (LSXBASE_NAMES+11)
#define CCHRYSALIS_CVMREGISTRYMETHOD_NEW       (LSXBASE_NAMES+9)
#define CCHRYSALIS_CVMREGISTRYMETHOD_SELFREGISTER       (LSXBASE_NAMES+10)
#define CCHRYSALIS_CAGENTMETHOD_BUILDAGENT       (LSXBASE_NAMES+17)
#define CCHRYSALIS_CAGENTMETHOD_NEW       (LSXBASE_NAMES+16)
#define CCHRYSALIS_CAGENTMETHOD_READAGENT       (LSXBASE_NAMES+18)


#define CCHRYSALIS_CONST_LS_EXTENSION           (LSXBASE_NAMES+19)
#define CCHRYSALIS_CONST_LS_SERVICES           (LSXBASE_NAMES+20)


#endif   // #if !defined (TEXTSTR_H)
