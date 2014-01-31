/**
 *	Web Mail Notifier For Sina
 * http://hi.baidu.com/matrix286/blog/
*/

function initHandler(handler)
{
	var isFirst = 0;
	handler.name = "Sina";
	handler.hostString = "sina.com";
	handler.loginData = ["http://mail.sina.com.cn/cgi-bin/login.cgi","u","psw"];

	handler.onResponse = function(aHttpChannel)
	{
		try 
		{
			var cookie = aHttpChannel.getResponseHeader("Set-Cookie");
			this.cookieManager.addCookies(aHttpChannel.URI,cookie);
			aHttpChannel.setResponseHeader("Set-Cookie", "", false);
		}
		catch(e)
		{
			// nothing
		}

		if (isFirst == 0)
		{
			var referer = aHttpChannel.getResponseHeader("Location");
			handler.mailURL = referer;
			var i = referer.indexOf("//");
			var dataURL = referer.substring(0, referer.indexOf("/", i + 2));
			dataURL = dataURL + "/classic/maillist.php";
			handler.dataURL = dataURL;
			isFirst = 1;
		}
	},
	handler.onError = function(desc)
	{
		this.stage = this.initStage;
		this.webMailNotifier.setState(this.id, this.user, nsIWebMailNotifier.ST_RESET);
	};

	handler.getData = function(aData)
	{
		var count = 0;
		var box = eval('(' + aData + ')');
		var data = box.data;
		var list = data.maillist;
		
		if (list == null || list.length < 1)
		{
			// dlog("empty");
			return 0;
		}
		
		for (var i = 0; i < list.length; i++)
		{
			var item = list[i];
			if (item.isread == false)
			{
				count++;
			}
		}
		return count;
	};
}