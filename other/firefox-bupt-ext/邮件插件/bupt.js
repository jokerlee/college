/***********************************************************
bupt
***********************************************************/
function initHandler(handler){
  handler.name="bupt";
  handler.dataURL="http://mail.bupt.cn/listMailbox.php";
  handler.loginData=["http://mail.bupt.cn/login.php",
                      "F_email","F_password","F_domain=bupt.cn"];
  handler.mailURL="http://mail.bupt.cn/listMailbox.php";

  handler.getData=function(aData){
    var fnd=aData.match(/color=red><b>(\d+)<\/b><\/font>/);
    dump(fnd[1]);
    if(fnd){
      return fnd[1];
    }else{
      return -1;
    }
  };
  
  handler.process=function (aHttpChannel, aData) {
    switch(this.stage){
    case ST_LOGIN_RES:
    	var tmp=aData.match(/F_sid=(\S+)\s+/);
    	var F_sid=tmp[1];
    	handler.dataURL="http://mail.bupt.cn/listMailbox.php?F_sid="+F_sid;
    	handler.mailURL="http://mail.bupt.cn/listMailbox.php?F_sid="+F_sid;
      this.stage=ST_DATA;
    }
    return WebMailHandler.prototype.process.call(this,aHttpChannel, aData);
  };
}
