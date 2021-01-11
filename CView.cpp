/*=============================================================================*\

   Copyright Lotus Development Corp. 1995 - 1999

   The enclosed code created by Lotus Development Corporation, is
   sample code. This sample code is provided to you solely for the
   purpose of assisting you in the development of your LotusScript
   Extension (LSX) applications.

   File: CView.cpp

   Description:
      Implementation of methods for the scriptable "CView" object

\*============================================================================*/

//{{LSX_AUTHOR_CODE_Include_1
//}}

#include "CView.hpp"

// includes for the objects defined in your LSX
#include "CVMRegistry.hpp"
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
// CreateCView on the container class.

CView:: CView( LSPTR(LSXLsiSession) pContainer, NotesDocument& parmDoc)
   : LSXBase((LSPLTSTR)"CView", pContainer->LSXGetInstance(), CCHRYSALIS_CVIEW_ID, pContainer)
   //{{LSX_AUTHOR_CODE_Additional_Base_Class_Init1
   //}}

   //{{LSX_AUTHOR_CODE_Internal_Member_Init1
   //}}
{
   //{{LSX_AUTHOR_CODE_Constructor1
	m_noteHandle = (NOTEHANDLE)parmDoc.GetProp(CNOTES_NPROP_HANDLE).getLong();
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

CView:: CView(LSUSHORT classId, LSPTR(LSXLsiSession) pContainer, NotesDocument& parmDoc )
   : LSXBase((LSPLTSTR)"CView", pContainer->LSXGetInstance(), classId, pContainer)
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

CView:: ~CView()
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
LSXBool CView::BuildView()
{
   //{{LSX_AUTHOR_CODE_Method_BuildView
	//  C Core API Objects
	LNSTATUS status;	

	// C++ Core API Objects
		// View
	LNText viewName,scopeName,vselName,cmtName,aliasName,frmfName;
	LNString viewVal,scopeVal,vselVal,cmtVal,aliasVal,frmfVal;
	LNNumbers altrowNameR,altrowNameG,altrowNameB,bgNameR,bgNameG, 
			  bgNameB,shrinkName,elcolName,hdName,showRepConsName;
	LNColor altRowColor,bgColor;
	LNViewFolder view,hsview;
	LNVFSHARINGOPTION scopeOpt = LNVFSHARINGOPTION_SHARED;
	LNDocument LNDoc;
	LNINT red,green,blue,extLastColumn,headingDisplay,shrinkrow,showrepcons;	
	LNFormula formula;

		// Columns
	LNVFColumn column;	 
	LNText colTitles,colHidden,colFormulae,colFieldNames,colResizable,
		   colShowTwisties,colShowAsLinks,colCategorized,colHSView,
		   colShowAsIcons,colSMValues,colHideDetailRows;
	LNNumbers colExactWidths,colCharWidths,colSeparators,colSort,colTJ,colJ,
			  colHSOption,colTotalsOption;
	LNINT colCount,colItems,i;

		// Actions

	// LSX Core Objects
	LSXBool retVal = LSXFalse;
	
	try {	
		// use the note handle to get the LNDocument object	
		if (m_LNDB.IsOpen()) {			
			m_LNDB.GetDocument(m_nid, &LNDoc);			
			LNDoc.Open();
			if (LNDoc.HasItem("ViewName")) {
				#if defined (TRACE)
					/*******/ LSXTraceString("Found view value");
				#endif
				LNDoc.GetItem("ViewName", &viewName);
				viewName.GetText(&viewVal);								
				if (LNDoc.HasItem("ViewScope")) {
					LNDoc.GetItem("ViewScope", &scopeName);
					scopeName.GetText(&scopeVal);				
					if (scopeVal == "2") scopeOpt = LNVFSHARINGOPTION_PRIVATE;
				}
				#if defined (TRACE)
					/*******/ LSXTraceString("Looking for view...");
				#endif
				if (m_LNDB.ViewFolderExists( viewVal ) == FALSE) {
					status = m_LNDB.CreateView(viewVal, scopeOpt);
					if (status == LNNOERROR) {
						#if defined (TRACE)
							/*******/ LSXTraceString("View creation successful.");
						#endif
						view.Close();
					} else {
						#if defined (TRACE)
						/*******/ LSXTraceString("View creation failed.");
						#endif
					}				
				} else {
					#if defined (TRACE)
						/*******/ LSXTraceString("View Found. Getting handle...");
					#endif
				} 
				
				status = m_LNDB.GetViewFolder( viewVal, &view ); 
				if (status == LNNOERROR) {
					#if defined (TRACE)
					/*******/ LSXTraceString("Handle retrieval successful.");
					#endif
				} else {
					#if defined (TRACE)
					/*******/ LSXTraceString("Unable to retrieve view/folder handle.");
					#endif
				}
					
				
				status = view.Open(LNVFOPENFLAGS_DESIGN_ONLY); // optimize performance

				if (status == LNNOERROR) {
					#if defined (TRACE)
						/*******/ LSXTraceString("View successfully opened.");
					#endif
				} else {
					#if defined (TRACE)
						/*******/ LSXTraceString("View failed to open.");
					#endif
				}
				

				if (LNDoc.HasItem("ViewSelection")) {
					#if defined (TRACE)
						/*******/ LSXTraceString("View Selection defined.");
					#endif
					LNDoc.GetItem("ViewSelection", &vselName);
					vselName.GetText(&vselVal);	
					formula.SetText(vselVal);				
				} else {
					#if defined (TRACE)
						/*******/ LSXTraceString("View Selection undefined.");
					#endif
					formula.SetText("SELECT @ALL");					
				}				
				view.SetSelectionFormula(formula);

				// TODO: ADD/MODIFY Action buttons

				if (LNDoc.HasItem("AltRowColorR") && LNDoc.HasItem("AltRowColorG") && LNDoc.HasItem("AltRowColorB")) {
					#if defined (TRACE)
						/*******/ LSXTraceString("Setting alternating row color.");
					#endif					
					LNDoc.GetItem("AltRowColorR", &altrowNameR);										
					LNDoc.GetItem("AltRowColorG", &altrowNameG);
					LNDoc.GetItem("AltRowColorB", &altrowNameB);
					
					red = (LNINT)altrowNameR[0];
					green = (LNINT)altrowNameG[0];
					blue = (LNINT)altrowNameB[0];

					altRowColor.SetColor((LNINT)red,(LNINT)green,(LNINT)blue);					
					view.SetAlternateRowColor(altRowColor);
				}

				if (LNDoc.HasItem("BGColorR") && LNDoc.HasItem("BGColorG") && LNDoc.HasItem("BGColorB")) {
					#if defined (TRACE)
						/*******/ LSXTraceString("Setting background color.");
					#endif					
					LNDoc.GetItem("BGColorR", &bgNameR);										
					LNDoc.GetItem("BGColorG", &bgNameG);
					LNDoc.GetItem("BGColorB", &bgNameB);
					
					red = (LNINT)bgNameR[0];
					green = (LNINT)bgNameG[0];
					blue = (LNINT)bgNameB[0];

					bgColor.SetColor((LNINT)red,(LNINT)green,(LNINT)blue);					
					view.SetBackgroundColor(bgColor);
				}

				if (LNDoc.HasItem("Alias")) {
					#if defined (TRACE)
						/*******/ LSXTraceString("Setting Alias.");
					#endif
					LNDoc.GetItem("Alias", &aliasName);
					aliasName.GetText(&aliasVal);		
					view.SetAlias(aliasVal);
				}

				if (LNDoc.HasItem("Comment")) {
					#if defined (TRACE)
						/*******/ LSXTraceString("Setting Comment.");
					#endif
					LNDoc.GetItem("Comment", &cmtName);
					cmtName.GetText(&cmtVal);		
					view.SetComment(cmtVal);
				}

				if (LNDoc.HasItem("FormFormula")) {
					#if defined (TRACE)
						/*******/ LSXTraceString("Setting Form Formula.");
					#endif
					LNDoc.GetItem("FormFormula", &frmfName);
					frmfName.GetText(&frmfVal);
					formula.SetText(frmfVal);
					view.SetFormFormula(formula);
				}
				
				if (LNDoc.HasItem("ShrinkRows")) {
					#if defined (TRACE)
						/*******/ LSXTraceString("Setting ShrinkRows.");
					#endif
					LNDoc.GetItem("ShrinkRows", &shrinkName);
					shrinkrow = (LNINT)shrinkName[0];
					if (shrinkrow == (LNINT)0) {
						view.SetShrinkRows(FALSE);
					} else {
						view.SetShrinkRows(TRUE);
					}
				}

				if (LNDoc.HasItem("ExtendLastColumn")) {
					#if defined (TRACE)
						/*******/ LSXTraceString("Setting ExtendLastColumn.");
					#endif
					LNDoc.GetItem("ExtendLastColumn", &elcolName);
					extLastColumn = (LNINT)elcolName[0];
					if (extLastColumn == (LNINT)0) {
						view.SetExtendLastColumn(FALSE);
					} else {
						view.SetExtendLastColumn(TRUE);
					}
				}

				if (LNDoc.HasItem("HeadingDisplay")) {
					#if defined (TRACE)
						/*******/ LSXTraceString("Setting HeadingDisplay.");
					#endif
					LNDoc.GetItem("HeadingDisplay", &hdName);
					headingDisplay = (LNINT)hdName[0];
					
					switch ((LNINT)headingDisplay) {
					case 0 : 
								view.SetHeadingDisplay(LNVFHEADINGDISPLAY_NONE);
								break;
							 
					case 1 : 
								view.SetHeadingDisplay(LNVFHEADINGDISPLAY_SIMPLE);
								break;
							 
					case 2 : 
								view.SetHeadingDisplay(LNVFHEADINGDISPLAY_BEVELED);
								break;
							 
					default : view.SetHeadingDisplay(LNVFHEADINGDISPLAY_BEVELED);														  
					}
				}

				if (LNDoc.HasItem("ShowReplicationConflicts")) {
					#if defined (TRACE)
						/*******/ LSXTraceString("Setting ShowReplicationConflicts.");
					#endif
					LNDoc.GetItem("ShowReplicationConflicts", &showRepConsName);
					showrepcons = (LNINT)showRepConsName[0];
					if (showrepcons == (LNINT)0) {
						view.SetShowReplicationConflicts(FALSE);
					} else {
						view.SetShowReplicationConflicts(TRUE);
					}
				}

				// TODO : Create Action Bars

				// Create View Columns
				if (LNDoc.HasItem("ColTitles")) {
					colCount = view.GetColumnCount();
					#if defined (TRACE)
						/*******/ LSXTraceString("Deleting existing columns.");
					#endif
					status = view.DeleteColumns((LNINT)0, colCount);
					if (status == LNNOERROR) {
						#if defined (TRACE)
							/*******/ LSXTraceString("View columns successfully deleted.");
						#endif
					} else {
						#if defined (TRACE)
							/*******/ LSXTraceString("View columns failed to delete.");
						#endif
					}

					#if defined (TRACE)
						/*******/ LSXTraceString("Setting ColTitles...");
					#endif
					status = LNDoc.GetItem("ColTitles", &colTitles);
					colItems = (LNINT) colTitles.GetCount();						
					for (i=0; i<colItems; i++) {
						status = view.AppendColumn(&column);
						column.SetTitle((LNString)colTitles[i]);
					}

					#if defined (TRACE)
						/*******/ LSXTraceString("Setting ColHidden...");
					#endif
					if (LNDoc.HasItem("ColHidden")) {
						status = LNDoc.GetItem("ColHidden", &colHidden);
						colItems = (LNINT) colHidden.GetCount();						
						for (i=0; i<colItems; i++) {
							status = view.GetColumn((LNINT)i, &column);
							column.SetHideColumn(((LNString)colHidden[i] == "1") ? TRUE : FALSE);
						}
					}

					#if defined (TRACE)
						/*******/ LSXTraceString("Setting ColFormulae...");
					#endif
					if (LNDoc.HasItem("ColFormulae")) {
						status = LNDoc.GetItem("ColFormulae", &colFormulae);
						colItems = (LNINT) colFormulae.GetCount();						
						for (i=0; i<colItems; i++) {
							status = view.GetColumn((LNINT)i, &column);
							if ((LNString)colFormulae[i] == (LNString)"") {
							} else {
								formula.SetText((LNString)colFormulae[i]);
								column.SetFormula(formula);							
							}
						}
					}

					#if defined (TRACE)
						/*******/ LSXTraceString("Setting ColFieldNames...");
					#endif
					if (LNDoc.HasItem("ColFieldNames")) {
						status = LNDoc.GetItem("ColFieldNames", &colFieldNames);
						colItems = (LNINT) colFieldNames.GetCount();						
						for (i=0; i<colItems; i++) {
							status = view.GetColumn((LNINT)i, &column);
							if ((LNString)colFieldNames[i] == (LNString)"") {
							} else {
								column.SetFieldName((LNString)colFieldNames[i]);								
							}
						}
					}

					// Use values in Exact Widths, unless on CharWidths avail
					if (LNDoc.HasItem("ColExactWidths")) {
						#if defined (TRACE)
							/*******/ LSXTraceString("Setting ColExactWidths...");
						#endif
						LNDoc.GetItem("ColExactWidths", &colExactWidths);
						colItems = (LNINT) colExactWidths.GetCount();						
						for (i=0; i<colItems; i++) {
							status = view.GetColumn((LNINT)i, &column);
							if ((LNINT)colExactWidths[i] == (LNINT)0) {
								// put default
								column.SetExactWidth((LNINT)80);
							} else {
								column.SetExactWidth((LNINT)colExactWidths[i]);								
							}
						}
						
					} else {

					#if defined (TRACE)
						/*******/ LSXTraceString("Setting ColCharWidths...");
					#endif
						if (LNDoc.HasItem("ColCharWidths")) {
							LNDoc.GetItem("ColCharWidths", &colCharWidths);
							colItems = (LNINT) colCharWidths.GetCount();						
							for (i=0; i<colItems; i++) {
								status = view.GetColumn((LNINT)i, &column);
								if ((LNINT)colCharWidths[i] == (LNINT)0) {
									// put default
									column.SetWidthInCharacters((LNINT)10);
								} else {
									column.SetWidthInCharacters((LNINT)colCharWidths[i]);								
								}
							}
						}
					}

					#if defined (TRACE)
						/*******/ LSXTraceString("Setting ColSeparators...");
					#endif
					if (LNDoc.HasItem("ColSeparators")) {
							LNDoc.GetItem("ColSeparators", &colSeparators);
							colItems = (LNINT) colSeparators.GetCount();						
							for (i=0; i<colItems; i++) {
								status = view.GetColumn((LNINT)i, &column);																			
								switch ((LNINT)colSeparators[i]) {
								case 0 : 
									column.SetSeparator(LNVFSEPARATOR_NONE);
									break;
							 
								case 1 : 
									column.SetSeparator(LNVFSEPARATOR_SPACE);
									break;
							 
								case 2 : 
									column.SetSeparator(LNVFSEPARATOR_COMMA);
									break;
							 
								case 3:
									column.SetSeparator(LNVFSEPARATOR_SEMICOLON);
									break;

								case 4:
									column.SetSeparator(LNVFSEPARATOR_NEWLINE);
									break;

								default : column.SetSeparator(LNVFSEPARATOR_NONE);														  
								}
							}
					}
					
					#if defined (TRACE)
						/*******/ LSXTraceString("Setting ColResizable...");
					#endif
					if (LNDoc.HasItem("ColResizable")) {
						status = LNDoc.GetItem("ColResizable", &colResizable);
						colItems = (LNINT) colResizable.GetCount();						
						for (i=0; i<colItems; i++) {
							status = view.GetColumn((LNINT)i, &column);
							column.SetIsResizable(((LNString)colResizable[i] == "1") ? TRUE : FALSE);
						}
					}

					#if defined (TRACE)
						/*******/ LSXTraceString("Setting ColShowTwistie...");
					#endif
					if (LNDoc.HasItem("ColShowTwistie")) {
						status = LNDoc.GetItem("ColShowTwistie", &colShowTwisties);
						colItems = (LNINT) colShowTwisties.GetCount();						
						for (i=0; i<colItems; i++) {
							status = view.GetColumn((LNINT)i, &column);
							column.SetShowTwistie(((LNString)colShowTwisties[i] == "1") ? TRUE : FALSE);
						}
					}

					#if defined (TRACE)
						/*******/ LSXTraceString("Setting ColShowAsLinks...");
					#endif
					if (LNDoc.HasItem("ColShowAsLinks")) {
						status = LNDoc.GetItem("ColShowAsLinks", &colShowAsLinks);
						colItems = (LNINT) colShowAsLinks.GetCount();						
						for (i=0; i<colItems; i++) {
							status = view.GetColumn((LNINT)i, &column);
							column.SetShowValuesAsLinks(((LNString)colShowAsLinks[i] == "1") ? TRUE : FALSE);
						}
					}

					#if defined (TRACE)
						/*******/ LSXTraceString("Setting ColCategorized...");
					#endif
					if (LNDoc.HasItem("ColCategorized")) {
						status = LNDoc.GetItem("ColCategorized", &colCategorized);
						colItems = (LNINT) colCategorized.GetCount();						
						for (i=0; i<colItems; i++) {
							status = view.GetColumn((LNINT)i, &column);
							column.SetIsCategorized(((LNString)colCategorized[i] == "1") ? TRUE : FALSE);
						}
					}

					#if defined (TRACE)
						/*******/ LSXTraceString("Setting ColTitleJustification...");
					#endif
					if (LNDoc.HasItem("ColTitleJustification")) {
						LNDoc.GetItem("ColTitleJustification", &colTJ);
						colItems = (LNINT) colTJ.GetCount();						
						for (i=0; i<colItems; i++) {
							status = view.GetColumn((LNINT)i, &column);																			
							switch ((LNINT)colTJ[i]) {
							case 0 : 
								column.SetTitleJustification(LNVFJUSTIFICATION_LEFT);
								break;
						 
							case 1 : 
								column.SetTitleJustification(LNVFJUSTIFICATION_CENTER);
								break;
						 
							case 2 : 
								column.SetTitleJustification(LNVFJUSTIFICATION_RIGHT);
								break;
						 
							default : column.SetTitleJustification(LNVFJUSTIFICATION_LEFT);
							}
						}
					}

					#if defined (TRACE)
						/*******/ LSXTraceString("Setting ColJustification...");
					#endif
					if (LNDoc.HasItem("ColJustification")) {
						LNDoc.GetItem("ColJustification", &colJ);
						colItems = (LNINT) colJ.GetCount();						
						for (i=0; i<colItems; i++) {
							status = view.GetColumn((LNINT)i, &column);																			
							switch ((LNINT)colJ[i]) {
							case 0 : 					
								column.SetJustification(LNVFJUSTIFICATION_LEFT);
								break;
						 
							case 1 : 
								column.SetJustification(LNVFJUSTIFICATION_CENTER);
								break;
							 
							case 2 : 
								column.SetJustification(LNVFJUSTIFICATION_RIGHT);
								break;
							 
							default : column.SetJustification(LNVFJUSTIFICATION_LEFT);
							}
						}
					}
					
					#if defined (TRACE)
						/*******/ LSXTraceString("Setting ColSort...");
					#endif
					if (LNDoc.HasItem("ColSort")) {
							LNDoc.GetItem("ColSort", &colSort);
							colItems = (LNINT) colSort.GetCount();						
							for (i=0; i<colItems; i++) {
								status = view.GetColumn((LNINT)i, &column);																			
								switch ((LNINT)colSort[i]) {
								case 0 : 
									column.SetSortOption(LNVFSORTOPTION_NONE);
									break;
							 
								case 1 : 
									column.SetSortOption(LNVFSORTOPTION_ASCENDING);
									break;
							 
								case 2 : 
									column.SetSortOption(LNVFSORTOPTION_DESCENDING);
									break;
							 
								default : column.SetSortOption(LNVFSORTOPTION_NONE);
								}
							}
					}

					#if defined (TRACE)
						/*******/ LSXTraceString("Setting ColHeadingSortOptions...");
					#endif
					if (LNDoc.HasItem("ColHeadingSortOptions")) {
							LNDoc.GetItem("ColHeadingSortOptions", &colHSOption);
							colItems = (LNINT) colHSOption.GetCount();						
							for (i=0; i<colItems; i++) {
								status = view.GetColumn((LNINT)i, &column);																			
								switch ((LNINT)colHSOption[i]) {
								case 0 : 
									column.SetHeadingSortOption(LNVFHEADINGSORTOPTION_NONE);
									break;
							 
								case 1 : 
									column.SetHeadingSortOption(LNVFHEADINGSORTOPTION_ASCENDING);
									break;
							 
								case 2 : 
									column.SetHeadingSortOption(LNVFHEADINGSORTOPTION_DESCENDING);
									break;
							 
								case 3 : 
									column.SetHeadingSortOption(LNVFHEADINGSORTOPTION_BOTH);
									break;

								case 4 : 
									column.SetHeadingSortOption(LNVFHEADINGSORTOPTION_CHANGE_VIEW_FOLDER);									

									LNDoc.GetItem("ColHeadingSortView", &colHSView);
									
									if (m_LNDB.ViewFolderExists((LNString)colHSView[i]) == TRUE) {
										status = m_LNDB.GetViewFolder( (LNString)colHSView[i], &hsview ); 
										if (status == LNNOERROR) {
											column.SetHeadingSortViewFolder(hsview);
										}										
									}
									break;

								default : column.SetHeadingSortOption(LNVFHEADINGSORTOPTION_NONE);
								}
							}
					}

					#if defined (TRACE)
						/*******/ LSXTraceString("Setting ColShowAsIcons...");
					#endif
					if (LNDoc.HasItem("ColShowAsIcons")) {
						status = LNDoc.GetItem("ColShowAsIcons", &colShowAsIcons);
						colItems = (LNINT) colShowAsIcons.GetCount();						
						for (i=0; i<colItems; i++) {
							status = view.GetColumn((LNINT)i, &column);
							column.SetDisplayValuesAsIcons(((LNString)colShowAsIcons[i] == "1") ? TRUE : FALSE);
						}
					}

					#if defined (TRACE)
						/*******/ LSXTraceString("Setting ColMultiValues...");
					#endif
					if (LNDoc.HasItem("ColMultiValues")) {
						status = LNDoc.GetItem("ColMultiValues", &colSMValues);
						colItems = (LNINT) colSMValues.GetCount();						
						for (i=0; i<colItems; i++) {
							status = view.GetColumn((LNINT)i, &column);
							column.SetSeparateMultipleValues(((LNString)colSMValues[i] == "1") ? TRUE : FALSE);
						}
					}

					#if defined (TRACE)
						/*******/ LSXTraceString("Setting ColHideDetailRows...");
					#endif
					if (LNDoc.HasItem("ColHideDetailRows")) {
						status = LNDoc.GetItem("ColHideDetailRows", &colHideDetailRows);
						colItems = (LNINT) colHideDetailRows.GetCount();						
						for (i=0; i<colItems; i++) {
							status = view.GetColumn((LNINT)i, &column);
							column.SetHideDetailRows(((LNString)colHideDetailRows[i] == "1") ? TRUE : FALSE);
						}
					}

					#if defined (TRACE)
						/*******/ LSXTraceString("Setting ColTotalsOption...");
					#endif
					if (LNDoc.HasItem("ColTotalsOption")) {
						LNDoc.GetItem("ColTotalsOption", &colTotalsOption);
						colItems = (LNINT) colTotalsOption.GetCount();						
						for (i=0; i<colItems; i++) {
							status = view.GetColumn((LNINT)i, &column);																			
							switch ((LNINT)colTotalsOption[i]) {
							case 0 : 
								column.SetTotalsOption(LNVFTOTALSOPTION_NONE);
								break;
						 
							case 1 : 
								column.SetTotalsOption(LNVFTOTALSOPTION_TOTAL);
								break;
						 
							case 2 : 
								column.SetTotalsOption(LNVFTOTALSOPTION_AVERAGE);
								break;
						 
							case 3 : 
								column.SetTotalsOption(LNVFTOTALSOPTION_AVERAGE_PER_CATEGORY);
								break;

							case 4 : 
								column.SetTotalsOption(LNVFTOTALSOPTION_PERCENT);
								break;

							case 5 : 
								column.SetTotalsOption(LNVFTOTALSOPTION_PERCENT_PER_CATEGORY);
								break;

							default : column.SetTotalsOption(LNVFTOTALSOPTION_NONE);
							}
						}
				}


				} else {
					#if defined (TRACE)
							/*******/ LSXTraceString("View columns will be preserved.");
					#endif				
				}

				#if defined (TRACE)
						/*******/ LSXTraceString("View columns rebuilt.");
				#endif	
				
				// Commit Changes
				view.Save(LNNOTESAVEFLAGS_FORCE);

				// Close the view item
				view.Close();
			}			
		}		
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
/*******************************************************************************
 *
 * Internal Method Definitions
 *
 *******************************************************************************/
//{{LSX_AUTHOR_CODE_Internal_Methods
//}}

