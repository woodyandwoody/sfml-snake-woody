
set q=createobject("scripting.filesystemobject") 
set a=WScript.CreateObject("WScript.Shell") 
currentpath = createobject("Scripting.FileSystemObject").GetFolder(".").Path
a.run "%Comspec% /c "&currentpath&"\a >>log.txt" ,0
