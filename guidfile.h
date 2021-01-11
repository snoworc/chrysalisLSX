/*========================================================================*\

   Copyright Lotus Development Corp. 1995 - 1999

   The enclosed code created by Lotus Development Corporation, is
   sample code.  This sample code is provided to you solely for the
   purpose of assisting you in the development of your LotusScript
   Extension (LSX) applications.

   File: guidfile.h

   Description:
      This file contains YOUR GUID for use in your LSX.

      After acquiring the GUID, you should identify its constituent
      components as shown below.

\*========================================================================*/

#if !defined (GUIDFILE_H)
#define GUIDFILE_H

/*
   Suppose you have  4FA5BD6E-DB84-4c7d-BA81-A05B3C52C3F8  as your GUID
*/

/* ---------------------------------------------------------------------------
   GUIDs - Globally Unique IDs
   --------------------------------------------------------------------------

   NOTE: If you use the macro

         DEFINE_GUID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8)

         supplied by the OLE header files, the mapping of parameters to
         ordering in the GUID string you see in the Registry is:

            l        w1   w2   b1b2 b3b4b5b6b7b8
            |        |    |    | |  | | | | | |
            4FA5BD6E-DB84-4c7d-BA81-A05B3C52C3F8

   ---------------------------------------------------------------------------
*/
/* ---------------------------------------------------------------------------
   #defines for the pieces of a GUID
*/

// your GUID is 4FA5BD6E-DB84-4c7d-BA81-A05B3C52C3F8

#define LSX_YOUR_GUID_BASE_UL     ((unsigned long) 0x4FA50000)
#define LSX_YOUR_GUID_OFFSET_US   0xBD6E

#define LSX_GUID_D2  0xDB84
#define LSX_GUID_D3  0x4c7d
#define LSX_GUID_D41 0xBA
#define LSX_GUID_D42 0x81
#define LSX_GUID_D43 0xA0
#define LSX_GUID_D44 0x5B
#define LSX_GUID_D45 0x3C
#define LSX_GUID_D46 0x52
#define LSX_GUID_D47 0xC3
#define LSX_GUID_D48 0xF8

//
// Note: these all refer to YOUR GUID base - which MUST not conflict !!!
//                        ********               ********

// even though we don't expose the Session class we still need a GUID for it

DEFINE_LSX_GUID(c_Session, LSX_ID_LSXBase + CCHRYSALIS_SESSION_ID);
DEFINE_LSX_GUID(c_CView, LSX_ID_LSXBase + CCHRYSALIS_CVIEW_ID);
DEFINE_LSX_GUID(c_CVMRegistry, LSX_ID_LSXBase + CCHRYSALIS_CVMREGISTRY_ID);
DEFINE_LSX_GUID(c_CAgent, LSX_ID_LSXBase + CCHRYSALIS_CAGENT_ID);

#endif   //   #if !defined (GUIDFILE_H)
