/***********************************************************
yeah.net
***********************************************************/
function initHandler(handler){
  handler.name="yeah.net";
  handler.dataURL="http://entry.yeah.net/cgi/ntesdoor?funcid=getusrnewmsgcnt&fid=1&addSubFdrs=1&language=0&style=0&template=newmsgres_urs_2008.htm&username="+handler.user;
  handler.loginData=["https://reg.163.com/logins.jsp",
                      "username","password","product=163&type=1&ursname="];
  handler.mailURL="http://entry.yeah.net/cgi/ntesdoor?verifycookie=1&lightweight=1";

  handler.getData=function(aData){
    var fnd=aData.match(/var\s+res\s+=\s+(\d+);/);
    if(fnd){
      return fnd[1];
    }else{
      return -1;
    }
  };
  
  handler.onResponse=function(aHttpChannel){
    if(this.stage==ST_LOGIN_RES){
      var ioService = Components.classes["@mozilla.org/network/io-service;1"]
                        .getService(Components.interfaces.nsIIOService);
      var uri=ioService.newURI("http://entry.yeah.net/cgi/ntesdoor",null,null);
      var cookie = aHttpChannel.getResponseHeader("Set-Cookie");
      cookie = cookie.replace(/(domain=)\.163\.com/g,"$1.yeah.net");
      this.cookieManager.addCookies(uri,cookie);
      aHttpChannel.setResponseHeader("Set-Cookie", "", false);
    }else{
      this.cookieManager.addCookies(aHttpChannel.URI,cookie);
      aHttpChannel.setResponseHeader("Set-Cookie", "", false);
    }
  },


  handler.onError=function(desc){
    this.stage=this.initStage;
    this.webMailNotifier.setState(this.id,this.user,nsIWebMailNotifier.ST_RESET);
  };
}