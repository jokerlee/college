// The Warp Connection for our application
var connection;
 // A text field used for displaying our status
var statusField;
var gStationCount = 0;

var color = ["#88AA00","#55AA00","#00AA55","#00AA88","#00AAAA","#0088A8","#003C9D"];

// Application initialisation
function init() 
 {
  statusField = document.getElementById('statusField');
 
  // Create a new resource for this application
  connection = new Warp.RootResource("busonline");           //can change
 
  // When the root resource becomes connected,
  // it will be assigned a URI it is accessible at.
  connection.onconnect = function(evt) 
   {
    // The luid is the local identifier at the Warp Gateway,
    // and the path is relative to that identifier.
    statusField.value = connection.luid + connection.path;
    for (var i=1; i <= 10; i++)
        {
        var varItem = new Option(i, i);      
        document.getElementById('select').options.add(varItem); 
         }
    };
 
  // When the root resource disconnects, the URI is no longer valid.
  connection.ondisconnect = function(evt) 
    {
    statusField.value = "disconnected";
     };
 // When a message is received on this connection, we just append the HTML in the "messages" div       ######################################################
    connection.onmessage = function(evt) 
    {
    evt.data=unescape(evt.data);
    var pro_message=evt.data.split("#");
    if (pro_message[0] == "RN")
        { show_station(pro_message); }
    else if (pro_message[0] == "RE")
        { 
        pro_message=evt.data.split("#");
        show_state(pro_message); 
        }
    else 
        alert("The reply is wrong!");
    };
  // Attempt to connect the resource.
    connection.open();
}

function clearTable(table) {
    for ( ; table.rows.length; )
        table.deleteRow(0);
}

 
//<!--查询车站信息-->
function send_QN() 
{
 
    
   if (document.getElementById('select').value != "s")
   {
       var msg =  "QN#"+document.getElementById('select').value; 
       connection.sendTo( document.getElementById('dst').value, "POST",msg);  
   }
   else{alert("Please select the bus number!");}
}

//<!--查询公交位置信息-->
function send_QE() 
  {
   if (document.getElementById('select').value != "s" && document.getElementById('direction').value != "s" && document.getElementById('target_station').value != "s" )
   {
       var msg =   "QE#" + document.getElementById('select').value + "#"
			+ document.getElementById('direction').value + "#"
			+ document.getElementById('target_station').value + "#"
			+ document.getElementById('query_quantity').value;
       connection.sendTo( document.getElementById('dst').value, "POST", msg);
   }
   else
       {alert("Please check the input!");}
}


//<!--显示车站查询的表-->
function show_station(pro_message) {

    document.getElementById("dir").style.visibility = "visible";
   
    gStationCount = pro_message.length - 2;
    var table = document.getElementById("station");
    clearTable(table); 
    var row = table.insertRow(table.rows.length);
    for (var i = 2 ;i < pro_message.length ; ++i)
        {
          addCell(row, pro_message[i]);
          if (i == pro_message.length -1)  break;
          //addCell(row, "&nbsp&nbsp&nbsp&nbsp");
          var cell = row.insertCell(row.cells.length);
          cell.innerHTML = "&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp";
          cell.id = (i-2).toString();
          cell.bgColor="#DDDDDD";
        }

                                                        //    <!--显示目标车站让用户选择-->
 
    for (var i=2; i < pro_message.length; i++)
        {
        var varItem = new Option(pro_message[i], i-2);      
        document.getElementById("target_station").options.add(varItem); 
         }

}

function addCell(row, txt) {
    var cell = row.insertCell(row.cells.length);
    cell.innerHTML = "<b>"+txt+"</b>";
    cell.align="center"; 
    cell.bgColor="#8FBC8B";
    cell.style.color="#FFFFFF";                        
    return cell;
}

//<!--显示查询最终结果的表-->
function show_state(pro_message){
    alert("cond_target");
     var cond_target = document.getElementById("target_station").value;
   // var cond_target = parseInt(document.getElementById("target_station").value-"站点");
    alert(cond_target);
    var cond_dir    = document.getElementById("direction").value;
    alert(cond_dir);

    document.getElementById("qu_result").style.visibility = "visible";
    for (var i = 0; i < gStationCount - 1; ++i) {
        document.getElementById(i.toString()).setAttribute("bgColor", "#DDDDDD");
    }     


    var dir = pro_message[2] == "0" ? 0 : -1;
    for (var i = 0; i < parseInt(pro_message[3]); ++i) {
        var idx = parseInt(pro_message[ 3 + (i+1) * 4]) + dir;
        document.getElementById(idx.toString()).setAttribute("bgColor", color[i%7]);
    }
     
     var table = document.getElementById("query_info");
     clearTable(table);
     var row = table.insertRow(table.rows.length);


     //addCell(row, "Bus NO");
     var cell = row.insertCell(row.cells.length);
     cell.innerHTML = "<b>Plate NO</b>";
     cell.bgColor = "#666666";
     cell.style.color = "#FFFFFF";
    // cell.style.face="arial";

     //addCell(row, "State");
     var cell = row.insertCell(row.cells.length);
     cell.innerHTML = "<b>State</b>";
     cell.bgColor="#666666";
     cell.style.color="#FFFFFF"; 

     //addCell(row, "Time");
     var cell = row.insertCell(row.cells.length);
     cell.innerHTML = "<b>Time</b>";
     cell.align="center";          
     cell.bgColor="#666666";
     cell.style.color="#FFFFFF"; 

     //addCell(row, "Station");
     var cell = row.insertCell(row.cells.length);
     cell.innerHTML = "<b>Station</b>";
     cell.bgColor="#666666";
     cell.style.color="#FFFFFF"; 

     alert(pro_message);
     var limit = 0;
     for (var i = 4; i < pro_message.length; i++)
         {
            var row;
            if ((i-4) % 4  == 0 )
                 {
                  alert("pro_message[i+3]");
                  alert(pro_message[i+3]);
                  alert(cond_target-pro_message[i+3]);
                  if (!((cond_dir ===0 && pro_message[i+3] < cond_target) || (cond_dir ==1 && pro_message[i+3] > cond_target))) i+=4;
                  row = table.insertRow(table.rows.length);
                  limit++;
                  }
            if (limit > document.getElementById("query_quantity").value)  return ;
            var cell = addCell(row, pro_message[i]);
	     cell.bgColor = color[Math.floor((i/4-1))%7];
          }
}

window.onwarpready = function() {
  init();
};





