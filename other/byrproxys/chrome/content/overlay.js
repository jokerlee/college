var gMenuCount = 2;

function byr_proxy() {
}

byr_proxy.prototype.onload = function() {
    if (document.getElementById("status-bar")) {
        window.setTimeout(gByrProxy.getProxys, 5*1000);
        window.setInterval(gByrProxy.getProxys, 120*1000);
    }
}


byr_proxy.prototype.onClickIcon = function() {
    document.getElementById("menu-root").showPopup(
            document.getElementById("menu-main"), 
            -1, -1, "popup", "topleft", "bottomleft"
            );
}


byr_proxy.prototype.getProxys = function() {

    var root = document.getElementById("menu-root");

    while (root.childNodes.length > gMenuCount) {
        root.removeChild(root.firstChild);
    }
    var point = document.createElement("menuseparator");
    root.insertBefore(point, root.firstChild);

    var aURL = "http://forum.byr.edu.cn/classic/bbscon.php?board=NetResources&id=45980&ftype=11";
    var req = new XMLHttpRequest();
    var result;
    req.open("GET", aURL, true);
    req.onreadystatechange = function() {
        if (req.readyState == 4 && req.status == 200) {
            var text = req.responseText;
            var regex = /[0-9]+\.[0-9]+\.[0-9]+\.[0-9]+:[0-9]+/gm;
            var ips = text.match(regex);
            for (var i=0; i<ips.length; ++i) {
                menu = document.createElement("menuitem");
                menu.setAttribute("label", ips[i]);
                menu.setAttribute("oncommand", 'gByrProxy.setProxy("'+ips[i]+'");');
                root.insertBefore(menu, point);
            }
        }
    }
    req.send(null);
}

byr_proxy.prototype.setProxy = function(addr) {
    var ip = addr.split(":");
    try {
        var prefs = Components.classes["@mozilla.org/preferences-service;1"] .getService(Components.interfaces.nsIPrefBranch);
        prefs.setIntPref("network.proxy.type", 1);
        prefs.setCharPref("network.proxy.http", ip[0]);
        prefs.setIntPref("network.proxy.http_port", ip[1]);
    } catch (e) {
        alert(e);
    }
}

byr_proxy.prototype.disableProxy = function() {
    try {
        var prefs = Components.classes["@mozilla.org/preferences-service;1"] .getService(Components.interfaces.nsIPrefBranch);
        prefs.setIntPref("network.proxy.type", 0);
    } catch (e) {
        alert(e);
    }
}



var gByrProxy = new byr_proxy();

window.addEventListener("load", gByrProxy.onload, false);
