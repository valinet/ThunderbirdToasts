var toast = {
	_prepareString: async function(m, string, id)
	{
		let recp = "";
		for (var j = 0; j < m.recipients.length; j++)
		{
			recp += m.recipients[j];
			if (j != m.recipients.length - 1)
			{
				recp += ", ";
			}
		}
		let bcc = "";
		for (var j = 0; j < m.bccList.length; j++)
		{
			bcc += m.bccList[j];
			if (j != m.bccList.length - 1)
			{
				bcc += ", ";
			}
		}
		let cc = "";
		for (var j = 0; j < m.ccList.length; j++)
		{
			cc += m.ccList[j];
			if (j != m.ccList.length - 1)
			{
				cc += ", ";
			}
		}
		return string.replaceAll("@AUTHOR@", m.author)
					 .replaceAll("@BCCLIST@", bcc)
					 .replaceAll("@CCLIST@", cc)
					 .replaceAll("@DATE@", m.date)
					 .replaceAll("@FOLDERACCOUNT@", m.folder.accountId)
					 .replaceAll("@FOLDERNAME@", m.folder.name)
					 .replaceAll("@FOLDERPATH@", m.folder.path)
					 .replaceAll("@FOLDERTYPE@", m.folder.type)
					 .replaceAll("@RECIPIENTS@", recp)
					 .replaceAll("@SUBJECT@", m.subject)
					 .replaceAll("@MESSAGEID@", id);
	},
	showToast: async function(mail, id)
	{
		let extra = "";
		let audio = await valinet.getPrefValue("toastAudio");
		let silent = "false";
		if (audio == "silent") silent = "true";
		let duration = await valinet.getPrefValue("toastDuration");
		let scenario = "";
		if (duration == "persist") 
		{
			scenario = "reminder";
			extra = extra + "<actions><action content=\"" + messenger.i18n.getMessage("lang.Dismiss") + "\" arguments=\"\" activationType=\"foreground\" /></actions>";
		}
		var json = JSON.stringify(
		{
			"id": await valinet.getPrefValue("appid"),
			"date": "" + mail.date.toISOString(),
			"scenario": scenario,
			"launch": proto + "://" + (mail.date.getTime() / 1000) + "/" + btoa(id),
			"duration": duration === "persist" ? "long" : duration,
			"subject": await this._prepareString(mail, await valinet.getPrefValue("toastSubject"), id),
			"body": await this._prepareString(mail, await valinet.getPrefValue("toastBody"), id),
			"attr": await this._prepareString(mail, await valinet.getPrefValue("toastFooter"), id),
			"loop": await valinet.getPrefValue("toastLoopAudio"),
			"audio": silent === "true" ? "ms-winsoundevent:Notification.Mail" : audio,
			"silent": silent,
			"extra": extra
		});
		port.postMessage(json);
	},
	showDemoToast: async function()
	{
		let mail = await messenger.messages.query({});
		let i = Math.floor(Math.random() * mail.messages.length);
		while (mail.messages[i].folder.type !== "inbox")
		{
			i = Math.floor(Math.random() * mail.messages.length);
		}
		let fullMsg = await messenger.messages.getFull(mail.messages[i].id);
		let messageId = fullMsg.headers["message-id"];
		toast.showToast(mail.messages[i], messageId[0].trim());
	}
}