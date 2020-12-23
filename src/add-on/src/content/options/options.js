document.addEventListener('DOMContentLoaded', () => {
	valinet.load(document);
	document.getElementById("demobtn").addEventListener("click", function(event) {
		var xhr = new XMLHttpRequest();
		xhr.open("GET", "http://127.0.0.1:46578/demo", true);
		xhr.send();
	});
	document.getElementById("uninstallbtn").addEventListener("click", function(event) {
		if (confirm(messenger.i18n.getMessage("lang.UninstallQuestion"))) {
			var xhr = new XMLHttpRequest();
			xhr.open("DELETE", "http://127.0.0.1:46578/", true);
			xhr.send();
		} else {
		}		
	});
	document.getElementById("aboutbtn").addEventListener("click", function(event) {
		alert(messenger.i18n.getMessage("lang.AboutText"));
	});
}, { once: true });