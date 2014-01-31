//Author Yue Liu @ BUPT firefox 2009-07-29
function initHandler(handler){
  handler.name = "buptsse";

  handler.dataURL = "http://student.buptsse.cn/cgi-bin/mailbox.cgi";
  handler.loginData = ["http://student.buptsse.cn/cgi-bin/mailbox.cgi",
			"username","password","mail_domain=student.buptsse.cn"];
  handler.mailURL = "http://student.buptsse.cn/cgi-bin/mailbox.cgi";

  handler.getData = function(aData){ //aData is a html source in dataURL
    var fnd = aData.match(/&nbsp;\u65B0\u90AE\u4EF6&nbsp;<font color=red>(\d+)\u5C01<\/font>/); //find mail count
    if(fnd){
      var num = fnd[1];
      //get mail count here
      return num;
    }else{
      return -1;//display 'not checked' message
    }
  };

  handler.process=function (aHttpChannel, aData) {
    switch(this.stage){
    case ST_LOGIN_RES:
    	var tmp=aData.match(/src="(\S+)"\ frameBorder=0\ scrolling=yes>/);
    	handler.dataURL="http://student.buptsse.cn"+tmp[1];
    	handler.mailURL="http://student.buptsse.cn"+tmp[1];
      this.stage=ST_DATA;
    }
    return WebMailHandler.prototype.process.call(this,aHttpChannel, aData);
  };
}