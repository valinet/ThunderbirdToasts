If InStr(1, WScript.FullName, "wscript.exe", vbTextCompare) > 0 Then
    With CreateObject("WScript.Shell")
        WScript.Quit .Run("cscript.exe """ & WScript.ScriptFullName & """", 0, True)
    End With
End If

Set FSO = CreateObject("Scripting.FileSystemObject")

appID = "PowerShell -Command ""Get-StartApps | Where-Object Name -Eq Thunderbird | Select -Expand AppID"""

Set WshShell = CreateObject("WScript.Shell")
Set WshShellExec = WshShell.Exec(appID)

Select Case WshShellExec.Status
   Case WshFinished
       appID = WshShellExec.StdOut.ReadAll
End Select
appID = Replace(appID, vbCr, "")
appID = Replace(appID, vbLf, "")

cmd = "PowerShell -Command ""echo 'C:\Windows\System32\wscript.exe," & _
	FSO.GetParentFolderName(WScript.ScriptFullName) & "\spawn.vbs," & _	
	"PowerShell,-ExecutionPolicy,Bypass,-File," & _
	FSO.GetParentFolderName(WScript.ScriptFullName) & "\toast.ps1," & _
	"-appid," & appID & "," & _
	"-proto,imsprevn://,-data1,@DATEINSECONDS@/,-data2,@AUTHOR@," & _
	"-title,@AUTHOR@,-text,@SUBJECT@,-to,To: @RECIPIENTS@,-cc, Cc: @CCLIST@" & _
	"-duration,short,-audio,ms-winsoundevent:Notification.Mail' | Clip"""

Set WshShellExec = WshShell.Exec(cmd)
	
confirm = "PowerShell -ExecutionPolicy Bypass -File """ & _
	FSO.GetParentFolderName(WScript.ScriptFullName) & _
	"\toast.ps1"" -appid " & appID & " -proto imsprevn:// " & _
	"-data1 """" -data2 """" -title ""Command copied to Clipboard"" " & _
	"-text ""Paste this command in the field of the Run program action filter that you are setting up."" " & _
	"-to ""Thunderbird Toasts"" -cc """" -duration long " & _ 
	"-audio ms-winsoundevent:Notification.Default"

Set WshShellExec = WshShell.Exec(confirm)