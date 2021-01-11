
CVMRegistry  
  
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
