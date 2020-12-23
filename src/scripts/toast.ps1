param ($appid, $proto, $data1, $data2, $title, $text, $to, $cc, $duration, $audio)

[Windows.UI.Notifications.ToastNotificationManager, Windows.UI.Notifications, ContentType = WindowsRuntime] | Out-Null
[Windows.UI.Notifications.ToastNotification, Windows.UI.Notifications, ContentType = WindowsRuntime] | Out-Null
[Windows.Data.Xml.Dom.XmlDocument, Windows.Data.Xml.Dom.XmlDocument, ContentType = WindowsRuntime] | Out-Null

$data2Bytes = [System.Text.Encoding]::UTF8.GetBytes($data2)
Write-Host($data2);
$data2 =[Convert]::ToBase64String($data2Bytes)
Write-Host($data2);
$action = -join("$proto", "$data1", "$data2");
$APP_ID = $appid
Write-Host("$title" | Out-String);
pause

$template = @"
<toast activationType="protocol" launch="$action" duration="$duration">
    <visual>
        <binding template="ToastGeneric">
            
            
            <text><![CDATA[$title]]></text>
            
            
            <text><![CDATA[$text]]></text>
			
			
            <text placement="attribution"><![CDATA[$to]]><![CDATA[$cc]]></text>
        </binding>
    </visual>
    
	<audio src="$audio" loop="false" />
	
    
</toast>
"@

$xml = New-Object Windows.Data.Xml.Dom.XmlDocument
$xml.LoadXml($template)
$toast = New-Object Windows.UI.Notifications.ToastNotification $xml
$toast.Tag = $APP_ID
$toast.Group = $APP_ID

[Windows.UI.Notifications.ToastNotificationManager]::CreateToastNotifier($APP_ID).Show($toast)
    