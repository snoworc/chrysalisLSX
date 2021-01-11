
**CVMRegistry** 
  
I wrote this class to register an LSX on your machine. Feel free to use this class to register any LSXs you write.  
  
  
  
Methods:  
  
Addkey(keyname as string, keyvalue as string, optional byval keysection as integer) as integer  
  
Adds a new key.  
  
  
  
Deletekey(keyname as string, optional byval keysection as integer) as integer  
  
Removes a key.  
  
  
  
Example:  

```
' Use this to unregister this LSX.
Dim reg as New CVMRegistry
Dim reg_status as Integer
reg_status = CVMRegistry.Deletekey("Chrysalis")

```

  
  
Getkey(keyname as string, optional byval keysection as integer) as string  
  
Shows a key value.  
  
  
  
Example:  

```
' Prints --> "C:\Lotus\Notes\Chrysalis.dll"
Dim reg as New CVMRegistry
Dim Keyvalue as String
Keyvalue = CVMRegistry.Getkey("Chrysalis")
Print Keyvalue<br/>

```

  
  
Listsection(optional byval keysection as integer) as string  
  
Returns the Keys.  
  
  
  
Example:  

```
Dim reg as New CVMRegistry
Dim Keysection as String
Keysection = CVMRegistry.ListSection()
Print Keysection

```

  
  
Selfregister(keyname as string, keyvalue as string) as integer  
  
Registers a LSX.  
  
  
  
Example:  
  
Dim ex As String  
  
ex = |  

```
Uselsx "c:\lotus\notes\chrysalis.dll"
Dim reg as New CVMRegistry
Dim reg_status as Integer
reg_status = reg.SelfRegister("Chrysalis",  "c:\lotus\notes\chrysalis.dll")
```
|

Dim ex_status As Integer  
  
ex_status = Execute(ex)


**CView**  
  
To initialize, pass a NotesDocument to the constructor. This NotesDocument needs to be saved in the database where the work is to be performed. You may delete the NotesDocument when done.  
  
  
  
Example:  
  

    Dim parmDoc as New NotesDocument(db)  
      
    parmDoc.ViewName = "MyView"  
      
    parmDoc.Comment = "Changed the comment on : " & Now()  
      
    Call parmDoc.Save(False, True)  
      
    Dim view as New CView(parmDoc)  
      

  
  
**Methods:**  
  
BuildView() as Variant  
  
This method uses the parameter document (NotesDocument) you passed to the constructor. It inspects each of the Fields you set on the parameter document and applies them to the Agent.  
  
  
  
*Example:*  
  

    Dim parmDoc as New NotesDocument(db)  
      
    parmDoc.ViewName = "MyView"  
      
    parmDoc.Comment = "Changed the comment on : " & Now()  
      
    Call parmDoc.Save(False, True)  
      
    Dim view as New CView(parmDoc)  
      
    view.BuildView()  
      
    Call parmDoc.Remove(True)  

  
  
  
Parameter Document Fields:  
  
View parameters:  
  
ViewName - String. Name of the view to modify. This is the only required parameter.  
  
  
  
ViewSelection - String. The view's selection formula  
  
  
  
AltRowColorR - Integer. 1 - 255. Red [RGB] component of the alternating row color.  
  
  
  
AltRowColorG - Integer. 1 - 255. Green [RGB] component of the alternating row color.  
  
  
  
AltRowColorB - Integer. 1 - 255. Blue [RGB] component of the alternating row color.  
  
  
  
BGColorR - Integer. 1 - 255. Red [RGB] component of the background color.  
  
  
  
BGColorG - Integer. 1 - 255. Green [RGB] component of the background color.  
  
  
  
BGColorB - Integer. 1 - 255. Blue [RGB] component of the background color.  
  
  
  
Alias - String. Name of the view's alias.  
  
  
  
Comment - String. Comment of the view.  
  
  
  
ShrinkRows - Integer. 0 = Do not shrink rows. 1 = Shrink rows.  
  
  
  
ExtendLastColumn - Integer. 0 = Do not extend last column. 1 = Extend last column.  
  
  
  
HeadingDisplay - Integer. 0 - 2.  
  
Const LNVFHEADINGDISPLAY_NONE% = 0  
  
Const LNVFHEADINGDISPLAY_SIMPLE% = 1  
  
Const LNVFHEADINGDISPLAY_BEVELED% = 2  
  
  
  
ShowReplicationConflicts - Integer. 0 - 1. 0 = Do not show replication conficts. 1 = Show replication conflicts.  
  
  
  
Column parameters:  
  
ColTitles - String array. Name of the column titles.  
  
  
  
ColHidden - String array. Hides or Shows column. "0" = Hidden. "1" = Visible.  
  
  
  
ColFieldNames - String array. ColFieldNames should be mutually exclusive from ColFormulae. Array of field names.  

```
           Use blank string if Forumula is to be used.<br/>

```

  
  
ColFormulae - String array. ColFormulae should be mutually exclusive from ColFieldNames.  

```
           Use blank string if FieldName is to be used .<br/>

```

  
  
ColExactWidths - Integer array. Use either ColExactWidths or ColCharWidths. If both exist, I take exact.  
  
  
  
ColCharWidths - Integer array.  
  
  
  
ColSeparators - Integer array. 0 - 4. Specifies the multi-value delimiter.  
  
Const LNVFSEPARATOR_NONE% = 0  
  
Const LNVFSEPARATOR_SPACE% = 1  
  
Const LNVFSEPARATOR_COMMA% = 2  
  
Const LNVFSEPARATOR_SEMICOLON% = 3  
  
Const LNVFSEPARATOR_NEWLINE% = 4  
  
  
  
ColResizable - String array. Indicates whether or not column is resizable. "0" = Fixed. "1" = Resizable.  
  
  
  
ColShowTwistie - String array. Indicates whether or not column has a "twistie". "0" = No twistie. "1" = twistie.  
  
  
  
ColShowAsLinks - String array. Indicates whether or not column is shown as a link.  

```
           &quot;0&quot; = Not shown as link.  &quot;1&quot; = Shown as link..<br/>

```

  
  
ColShowAsIcons - String array. Indicates whether or not to display the column value as an icon. "0" = No icon. "1" = Icon.  
  
  
  
ColCategorized - String array. Indicates whether or not to categorize the column . "0" = Not categorized. "1" = Categorized.  
  
  
  
ColSort - Integer array. 0 - 2. Type of column sorting.  
  
Const LNVFSORTOPTION_NONE% = 0  
  
Const LNVFSORTOPTION_ASCENDING% = 1  
  
Const LNVFSORTOPTION_DESCENDING% = 2  
  
  
  
ColTitleJustification - Integer array. 0 - 2. Type of column title justification.  
  
Const LNVFJUSTIFICATION_LEFT% = 0  
  
Const LNVFJUSTIFICATION_CENTER% = 1  
  
Const LNVFJUSTIFICATION_RIGHT% = 2  
  
  
  
ColJustification - Integer array. 0 - 2. Type of column justification.  
  
Const LNVFJUSTIFICATION_LEFT% = 0  
  
Const LNVFJUSTIFICATION_CENTER% = 1  
  
Const LNVFJUSTIFICATION_RIGHT% = 2  
  
  
  
ColHeadingSortOptions - Integer array. 0 - 4. Column heading sort options.  
  
Const LNVFHEADINGSORTOPTION_NONE% = 0  
  
Const LNVFHEADINGSORTOPTION_ASCENDING% = 1  
  
Const LNVFHEADINGSORTOPTION_DESCENDING% = 2  
  
Const LNVFHEADINGSORTOPTION_BOTH% = 3  
  
Const LNVFHEADINGSORTOPTION_CHANGE_VIEW_FOLDER% = 4  
  
  
  
ColHeadingSortView - String array. Applies to when ColHeadingSortOptions is set to 4  

```
          (LNVFHEADINGSORTOPTION_CHANGE_VIEW_FOLDER). This is the name of the view to change to.<br/>

```

  
  
ColMultiValues - String array. Indicates whether or not to show multi-values. "0" = not multi-value. "1" = multi-value.  
  
  
  
ColTotalsOption - Integer array. 0 - 5. Type of column totaling.  
  
Const LNVFTOTALSOPTION_NONE% = 0  
  
Const LNVFTOTALSOPTION_TOTAL% = 1  
  
Const LNVFTOTALSOPTION_AVERAGE% = 2  
  
Const LNVFTOTALSOPTION_AVERAGE_PER_CATEGORY% = 3  
  
Const LNVFTOTALSOPTION_PERCENT% = 4  
  
Const LNVFTOTALSOPTION_PERCENT_PER_CATEGORY% = 5  
  
  
  
ColHideDetailRows - String array. Indicates whether of not to hide row total details. "0" = Hide details. "1" = Show details.  
  
  
  
*Example:*  
  

    uselsx "*Chrysalis"  
      
      
      
    Const LNVFSEPARATOR_NONE% = 0  
      
    Const LNVFSEPARATOR_SPACE% = 1  
      
    Const LNVFSEPARATOR_COMMA% = 2  
      
    Const LNVFSEPARATOR_SEMICOLON% = 3  
      
    Const LNVFSEPARATOR_NEWLINE% = 4  
      
      
      
    Const LNVFHEADINGDISPLAY_NONE% = 0  
      
    Const LNVFHEADINGDISPLAY_SIMPLE% = 1  
      
    Const LNVFHEADINGDISPLAY_BEVELED% = 2  
      
      
      
    Const LNVFSORTOPTION_NONE% = 0  
      
    Const LNVFSORTOPTION_ASCENDING% = 1  
      
    Const LNVFSORTOPTION_DESCENDING% = 2  
      
      
      
    Const LNVFJUSTIFICATION_LEFT% = 0  
      
    Const LNVFJUSTIFICATION_CENTER% = 1  
      
    Const LNVFJUSTIFICATION_RIGHT% = 2  
      
      
      
    Const LNVFHEADINGSORTOPTION_NONE% = 0  
      
    Const LNVFHEADINGSORTOPTION_ASCENDING% = 1  
      
    Const LNVFHEADINGSORTOPTION_DESCENDING% = 2  
      
    Const LNVFHEADINGSORTOPTION_BOTH% = 3  
      
    Const LNVFHEADINGSORTOPTION_CHANGE_VIEW_FOLDER% = 4  
      
      
      
    Const LNVFTOTALSOPTION_NONE% = 0  
      
    Const LNVFTOTALSOPTION_TOTAL% = 1  
      
    Const LNVFTOTALSOPTION_AVERAGE% = 2  
      
    Const LNVFTOTALSOPTION_AVERAGE_PER_CATEGORY% = 3  
      
    Const LNVFTOTALSOPTION_PERCENT% = 4  
      
    Const LNVFTOTALSOPTION_PERCENT_PER_CATEGORY% = 5  
      
      
      
    Dim view as CView  
      
    Dim s as New NotesSession  
      
    Dim db as New NotesDatabase("", "")  
      
    Dim doc as NotesDocument  
      
      
      
    Call db.open("Your server", "tbn\lsxtest.nsf") ' Use your own database  
      
    Set doc = New NotesDocument(db)  
      
      
      
    doc.Form = "ParmDoc"  
      
    doc.ViewName = "View11bb" ' This is the only necessary parm. Defaults will be used for all other parms that do not exist.  
      
    doc.ViewSelection = {SELECT Form = "ParmDoc"}  
      
    doc.AltRowColorR = 192 ' 1..255  
      
    doc.AltRowColorG = 192 ' 1..255  
      
    doc.AltRowColorB = 255 ' 1..255  
      
    doc.BGColorR = 222 ' 1..255  
      
    doc.BGColorG = 226 ' 1..255  
      
    doc.BGColorB = 226 ' 1..255  
      
    doc.Alias = "BV1bb"  
      
    doc.Comment = "My test view…"  
      
    doc.ShrinkRows = 1 ' 1 or 0  
      
    doc.ExtendLastColumn = 1 ' 1 or 0  
      
    doc.HeadingDisplay = LNVFHEADINGDISPLAY_BEVELED  
      
    doc.ShowReplicationConflicts = 1 ' 1 or 0  
      
      
      
    ' As far as setting columns go, defaults will be preserved if you do NOT include  
      
    ' the field in the parm doc. So, you only need to add the fields you want to customize.  
      
    Dim arColTitles(2) as String  
      
    Dim arColHidden(2) as String ' "0" or "1"  
      
    Dim arColFormulae(2) as String  
      
    Dim arColFieldNames(2) as String  
      
    Dim arColExactWidths(2) as Integer ' 1..255 (exact width)  
      
    Dim arColCharWidths(2) as Integer ' 1..255 (width in characters)  
      
    Dim arColSeparators(2) as Integer  
      
    Dim arColResizable(2) as String ' "0" or "1"  
      
    Dim arColShowTwistie(2) as String ' "0" or "1"  
      
    Dim arColShowAsLinks(2) as String ' "0" or "1"  
      
    Dim arColCategorized(2) as String ' "0" or "1"  
      
    Dim arColSort(2) as Integer  
      
    Dim arColTitleJustification(2) As Integer  
      
    Dim arColJustification(2) As Integer  
      
    Dim arColHeadingSortOptions(2) As Integer  
      
    Dim arColHeadingSortViewFolder(2) as String  
      
    Dim arColShowAsIcons(2) As String  
      
    Dim arMultiValues(2) As String  
      
    Dim arHideDetailRows(2) as String  
      
    Dim arTotalsOption(2) As Integer  
      
      
      
    arColTitles(0) = "Column #1"  
      
    arColTitles(1) = "Column #2"  
      
    arColTitles(2) = "Column #3"  
      
    arColHidden(0) = "0"  
      
    arColHidden(1) = "0"  
      
    arColHidden(2) = "0"  
      
    arColFormulae(0) = ""  
      
    arColFormulae(1) = {x := 133; x}  
      
    arColFormulae(2) = {x := @Text(@DocumentUniqueID); x}  
      
    arColFieldNames(0) = {Form}  
      
    arColFieldNames(1) = ""  
      
    arColFieldNames(2) = ""  
      
    arColExactWidths(0) = 80 ' same as 0. default is 80, using 0 will also set to 80  
      
    arColExactWidths(1) = 120  
      
    arColExactWidths(2) = 120  
      
    arColCharWidths(0) = 10  
      
    arColCharWidths(1) = 20  
      
    arColCharWidths(2) = 30  
      
    arColSeparators(0) = LNVFSEPARATOR_NONE  
      
    arColSeparators(1) = LNVFSEPARATOR_NEWLINE  
      
    arColSeparators(2) = LNVFSEPARATOR_SEMICOLON  
      
    arColResizable(0) = "1"  
      
    arColResizable(1) = "1"  
      
    arColResizable(2) = "1"  
      
    arColShowTwistie(0) = "1"  
      
    arColShowTwistie(1) = "0"  
      
    arColShowTwistie(2) = "0"  
      
    arColShowAsLinks(0) = "0"  
      
    arColShowAsLinks(1) = "0"  
      
    arColShowAsLinks(2) = "0"  
      
    arColShowAsIcons(0) = "0" ' "1" == make this an icon  
      
    arColShowAsIcons(1) = "0"  
      
    arColShowAsIcons(2) = "0"  
      
    arColCategorized(0) = "1"  
      
    arColCategorized(1) = "0"  
      
    arColCategorized(2) = "0"  
      
    arColSort(0) = LNVFSORTOPTION_ASCENDING  
      
    arColSort(1) = LNVFSORTOPTION_ASCENDING  
      
    arColSort(2) = LNVFSORTOPTION_NONE  
      
    arColTitleJustification(0) = LNVFJUSTIFICATION_CENTER  
      
    arColTitleJustification(1) = LNVFJUSTIFICATION_CENTER  
      
    arColTitleJustification(2) = LNVFJUSTIFICATION_CENTER  
      
    arColJustification(0) = LNVFJUSTIFICATION_LEFT  
      
    arColJustification(1) = LNVFJUSTIFICATION_LEFT  
      
    arColJustification(2) = LNVFJUSTIFICATION_LEFT  
      
    arColHeadingSortOptions(0) = LNVFHEADINGSORTOPTION_NONE  
      
    arColHeadingSortOptions(1) = LNVFHEADINGSORTOPTION_NONE  
      
    arColHeadingSortOptions(2) = LNVFHEADINGSORTOPTION_CHANGE_VIEW_FOLDER  
      
    arColHeadingSortViewFolder(0) = ""  
      
    arColHeadingSortViewFolder(1) = ""  
      
    arColHeadingSortViewFolder(2) = "View1"  
      
    arMultiValues(0) = "0"  
      
    arMultiValues(1) = "1"  
      
    arMultiValues(2) = "0"  
      
      
      
    ' totals  
      
    arTotalsOption(0) = LNVFTOTALSOPTION_NONE  
      
    arTotalsOption(1) = LNVFTOTALSOPTION_TOTAL  
      
    arTotalsOption(2) = LNVFTOTALSOPTION_TOTAL  
      
    arHideDetailRows(0) = "0"  
      
    arHideDetailRows(1) = "1"  
      
    arHideDetailRows(2) = "0"  
      
      
      
    doc.ColTitles = arColTitles$()  
      
    doc.ColHidden = arColHidden$()  
      
    doc.ColFieldNames = arColFieldNames$()  
      
    doc.ColFormulae = arColFormulae$()  
      
    doc.ColExactWidths = arColExactWidths%() ' use exact or char, but if both exist, I take exact.  
      
    'doc.ColCharWidths = arColCharWidths%()  
      
    doc.ColSeparators = arColSeparators%()  
      
    doc.ColResizable = arColResizable$()  
      
    doc.ColShowTwistie = arColShowTwistie$()  
      
    doc.ColShowAsLinks = arColShowAsLinks$()  
      
    doc.ColCategorized = arColCategorized$()  
      
    doc.ColSort = arColSort%()  
      
    doc.ColTitleJustification = arColTitleJustification%()  
      
    doc.ColJustification = arColJustification%()  
      
    doc.ColHeadingSortOptions = arColHeadingSortOptions%()  
      
    doc.ColHeadingSortView = arColHeadingSortViewFolder$()  
      
    doc.ColShowAsIcons = arColShowAsIcons$()  
      
    doc.ColMultiValues = arMultiValues$()  
      
    doc.ColTotalsOption = arTotalsOption%()  
      
    doc.ColHideDetailRows = arHideDetailRows$()  
      
      
      
    doc.Save False, True, True  
      
      
      
    Set view = New CView(doc)  
      
    Call view.BuildView()

