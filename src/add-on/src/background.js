var debug = false;
var proto = "thunderbirdtoasts";
var mails = [];
let defaultPrefs = {
	"appid": "D78BF5DD33499EC2",
	"toastSubject": "@AUTHOR@",
	"toastBody": "@SUBJECT@",
	"toastFooter": "@RECIPIENTS@",
    "toastDuration": "long",
	"toastAudio": "ms-winsoundevent:Notification.Mail",
	"toastLoopAudio": "false",
	"toastDisplayMessage": "three_pane",
};
valinet.setDefaults(defaultPrefs);
var port = browser.runtime.connectNative("ThunderbirdToasts");
browser.messages.onNewMailReceived.addListener(async (folder, messagelist) => {
	for (var i = 0; i < messagelist.messages.length; i++)
	{
		if (messagelist.messages[i].folder.type === "inbox" && !mails.includes(messagelist.messages[i].id))
		{
			mails.push(messagelist.messages[i].id);
			let fullMsg = await messenger.messages.getFull(messagelist.messages[i].id);
			let messageId = fullMsg.headers["message-id"];
			toast.showToast(messagelist.messages[i], messageId[0].trim());
		}
	}
});
port.onMessage.addListener(async (response) => {
	let show_notif = false;
	if (response.m.startsWith("GET /demo HTTP/1.1"))
	{
		toast.showDemoToast();
		return;
	}
	else if (response.m.startsWith("GET "))
	{
		show_notif = true;
		response.m = response.m.replace("GET ", "/");
		response.m = response.m.replace(" HTTP", "");
	}
	else if (response.m.startsWith("POST "))
	{
		response.m = response.m.replace("POST ", "/");
		response.m = response.m.replace(" HTTP", "");
	}
	if (debug) console.log(response.m);
	if (response.m.includes("//"))
	{
		let data = response.m.split('//')[1];
		if (data.includes("/"))
		{
			let date_raw = data.split('/')[0].replaceAll("\"", "");
			if (debug) console.log(date_raw);
			let msgid_raw = data.split('/')[1].replaceAll("\"", "");
			if (debug) console.log(msgid_raw);
			let date = new Date(date_raw * 1000);
			if (debug) console.log(date);
			let question = {
				fromDate: date,
				toDate: date
			};
			let mail = await messenger.messages.query(question);
			if (debug) console.log(mail.messages.length);
			for (var i = 0; i < mail.messages.length; i++)
			{
				let fullMsg = await messenger.messages.getFull(mail.messages[i].id);
				if (debug) console.log(fullMsg);
				let messageId = fullMsg.headers["message-id"];
				if (debug) console.log(messageId[0].trim());
				if (debug) console.log(atob(msgid_raw).trim());
				if (debug) console.log(btoa(messageId[0].trim()));
				if (debug) console.log(btoa(atob(msgid_raw).trim()));
				if (debug) console.log(btoa(messageId[0]) === msgid_raw);
				if (show_notif)
				{
					toast.showToast(mail.messages[i], messageId[0].trim());
				}
				else if (messageId[0].trim() === atob(msgid_raw).trim() && mail.messages[i].folder.type === "inbox")
				{
					if (debug) console.log(mail.messages[i].id);
					messenger.cb_api.cb_show_message_from_api_id(
						mail.messages[i].id,
						await valinet.getPrefValue("toastDisplayMessage")
					);
				}
			}
		}
	}
});