'If WScript.Arguments.length = 0 Then
'	Set objShell = CreateObject("Shell.Application")
'	objShell.ShellExecute "wscript.exe", Chr(34) & _
'		WScript.ScriptFullName & Chr(34) & " uac", "", "runas", 1
'Else
	Set WshShell = CreateObject("WScript.Shell")
	Set FSO = CreateObject("Scripting.FileSystemObject")
	
	exe = """" & FSO.GetParentFolderName(WScript.ScriptFullName) & "\thunderbird_toasts.exe"" ""%1"""
	manifest = FSO.GetParentFolderName(WScript.ScriptFullName) & "\native.json"

	WshShell.RegWrite "HKEY_CURRENT_USER\Software\Classes\imsprevn\","URL:imsprevn protocol","REG_SZ"
	WshShell.RegWrite "HKEY_CURRENT_USER\Software\Classes\imsprevn\EditFlags",2162688,"REG_DWORD"
	WshShell.RegWrite "HKEY_CURRENT_USER\Software\Classes\imsprevn\URL Protocol","","REG_SZ"
	
	WshShell.RegWrite "HKEY_CURRENT_USER\Software\Classes\imsprevn\shell\open\command\",exe,"REG_SZ"
	
	WshShell.RegWrite "HKEY_CURRENT_USER\Software\Mozilla\NativeMessagingHosts\ThunderbirdToasts\",manifest,"REG_SZ"
	
	confirm = "PowerShell -ExecutionPolicy Bypass -File """ & _
		FSO.GetParentFolderName(WScript.ScriptFullName) & _
		"\toast.ps1"" -appid D78BF5DD33499EC2 -proto imsprevn:// " & _
		"-data1 """" -data2 """" -title ""Registration succeeded"" " & _
		"-text ""Tap here to open Thunderbird and continue configuring the client."" " & _
		"-to ""Thunderbird Toasts"" -cc """" -duration long " & _ 
		"-audio ms-winsoundevent:Notification.Default"
	
	Const HIDDEN_WINDOW = 0
	strComputer = "."
	Set objWMIService = GetObject("winmgmts:\\" & strComputer & "\root\cimv2")
	Set objStartup = objWMIService.Get("Win32_ProcessStartup")
	Set objConfig = objStartup.SpawnInstance_
	objConfig.ShowWindow = HIDDEN_WINDOW
	Set objProcess = GetObject("winmgmts:\\" & strComputer & "\root\cimv2:Win32_Process")
	objProcess.Create confirm, null, objConfig, intProcessID	
'End If