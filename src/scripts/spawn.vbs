' https://stackoverflow.com/questions/18006236/vbscript-how-to-join-wscript-arguments
ReDim arr(WScript.Arguments.Count-1)
For i = 0 To WScript.Arguments.Count-1
	If InStr(WScript.Arguments(i), " ") Then
		arr(i) = """" + WScript.Arguments(i) + """"
	Else
		arr(i) = WScript.Arguments(i)
	End If
Next
' https://devblogs.microsoft.com/scripting/how-can-i-start-a-script-in-a-hidden-window/
Const HIDDEN_WINDOW = 0
strComputer = "."
Set objWMIService = GetObject("winmgmts:\\" & strComputer & "\root\cimv2")
Set objStartup = objWMIService.Get("Win32_ProcessStartup")
Set objConfig = objStartup.SpawnInstance_
'objConfig.ShowWindow = HIDDEN_WINDOW
Set objProcess = GetObject("winmgmts:\\" & strComputer & "\root\cimv2:Win32_Process")
objProcess.Create Join(arr), null, objConfig, intProcessID
