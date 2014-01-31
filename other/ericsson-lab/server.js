 
 // The Warp Connection for our application
var connection;
 // A text field used for displaying our status
var statusField;

var gBusStates = new Object();
var gBusStations = new Object();

var color = ["#88AA00","#55AA00","#00AA55","#00AA88","#00AAAA","#0088A8","#003C9D"];

var stations = [
    ["387", "站点0", "站点1", "站点2", "站点3", "站点4", "站点5", "站点6", "站点7"],
    ["604", "站点0", "站点1", "站点2", "站点3", "站点4", "站点5", "站点6", "站点7"],
    ["645", "站点0", "站点1", "站点2", "站点3", "站点4", "站点5", "站点6", "站点7"]
];


function BusInfo() {
    this.no = "";
    this.state = "0";
    this.time = "0";
    this.station = "";
}

function clone(myObj) {
  if(typeof(myObj) != 'object') return myObj;warp://erlabs:gateway/460/busserver
  if(myObj == null) return myObj;
  
  var myNewObj = new Object();
  
  for(var i in myObj)
    myNewObj[i] = clone(myObj[i]);
  
  return myNewObj;bgcolor="#F0FFF0"
}

function initData() {

    for (var i = 0; i < stations.length; ++i) {
        gBusStations[stations[i][0]] = new Array();
        for (var j = 1; j < stations[i].length; ++j)
            gBusStations[stations[i][0]].push(stations[i][j]);

        gBusStates[stations[i][0]] = new Array();
        var bus = new BusInfo();
        bus.state = "0";
        bus.time = "11:20:21";
        bus.station = "0";
        for (var j = 0; j < 5; j++) {
            bus = clone(bus);            
            bus.no = j.toString();
            gBusStates[stations[i][0]].push(bus);
        }
    }

    setInterval(updateData, 2000);

}





// Application initialisation
function initWarp() {
    statusField = document.getElementById('statusField');
 
    // Create a new resource for this application
    connection = new Warp.RootResource("busserver");
 
    connection.onconnect = function(evt) {
        // The luid is the local identifier at the Warp Gateway,
        // and the path is relative to that identifier.
        statusField.value = connection.luid + connection.path;
    };
 
    // When the root resource disconnects, the URI is no longer valid.
    connection.ondisconnect = function(evt) {
        statusField.value = "disconnected";

    };
    
    connection.onmessage = function(evt) {
        processRequest(evt.origin, evt.data);
     msgId++
    }; 
    
    // Attempt to connect the resource.
    connection.open();
}
 
window.onwarpready = function() {
    initWarp();
    initData();
    showData();
    
};
    
function showData() {
    var table = document.getElementById("info");
    var title = addTitle(table);
    title.bgColor = "#666666";
    title.style.color = "#FFFFFF";
    var i = 0;
    for (var o in gBusStates) {
        var c = color[i%7];
        for (var j = 0; j < gBusStates[o].length; ++j) {
            var row = addRow(table, o, gBusStates[o][j]);
            row.bgColor = c;
            row.style.color = "#FFFFFF";
        }
        i++;
    }
}

function addTitle(table) {
    
    var row = table.insertRow(table.rows.length);
    
    addCell(row, "车次");
    addCell(row, "编号");
    addCell(row, "方向");
    addCell(row, "状态");
    addCell(row, "更新时间");
    addCell(row, "站点");

    return row;
}

function addCell(row, txt) {
    var cell = row.insertCell(row.cells.length);
    cell.innerHTML = txt;
}

function changeRow(row, no, bus) {
    row.cells[2].innerHTML = (bus.state == "0") ? ("上行") : ("下行");
    row.cells[3].innerHTML = bus.state;
    row.cells[4].innerHTML = bus.time;
    row.cells[5].innerHTML = gBusStations[no][bus.station];
}

function addRow(table, no, bus) {
    var row = table.insertRow(table.rows.length);
    row.setAttribute("id", no+"-"+bus.no);

    addCell(row, no);
    addCell(row, bus.no);
    addCell(row, (bus.state == "0") ? ("上行") : ("下行"));
    addCell(row, bus.state);
    addCell(row, bus.time);
    addCell(row, gBusStations[no][bus.station]);

    return row;
}

function clearTable(table) {
    for ( ; table.rows.length; )
        table.deleteRow(0);
}

function updateData() {
    for (var o in gBusStates) {
        for (var j = 0; j < gBusStates[o].length; ++j) {
            if (Math.round(Math.random()) == 1) {
                var bus = gBusStates[o][j];
                var t = new Date();
                bus.time = t.getHours() + ":" + t.getMinutes() + ":" + t.getSeconds();
                if (bus.station == (gBusStations[o].length-2).toString()
                        && bus.state == "0")
                    bus.state = "1";
                else if (bus.station == "1" && bus.state == "1") 
                    bus.state = "0";
                
                var tmp = parseInt(bus.station);
                tmp += (bus.state == "0") ? (1) : (-1);
                bus.station = tmp.toString();
                

                changeRow(document.getElementById(o+"-"+bus.no), o, bus);
                return;
            }
        }
    }    
}

function random(from, to) {
    return Math.round(Math.random()*10000) % (to - from + 1) + from;
}


function processRequest(src, rqst) {
    rqst = unescape(rqst);
    var args = rqst.split('#');
    var msg = "";
    switch (args[0]) {
    case "QN":
        msg = "RN" + "#" + args[1] + "#" + gBusStations[args[1]].join("#");
        sendResponse(src, msg);
        break;
    case "QE":
        var buses = gBusStates[args[1]];
        var cnt = 0;
        var info = "";
        msg = "RE" + "#" + args[1] + "#" + args[2];
        for (var i = 0; i < buses.length; ++i) {
            if (buses[i].state == args[2]) {
                if ((buses[i].state == "0" && parseInt(buses[i].station) <= parseInt(args[3])) 
                    || (buses[i].state == "1" && parseInt(buses[i].station) >= parseInt(args[3]))) {
                    info += "#" + buses[i].no + "#" + buses[i].state + "#" + buses[i].time + "#" + buses[i].station;
                    cnt ++;
                }
            }
        }
        msg += "#" + cnt.toString() + info;
        sendResponse(src, msg);
        break;
    default: break;
    }
}


var msgId = 1;
function sendResponse(dst, msg)
{
    //alert(msg);
    connection.sendTo(dst, "POST", escape(msg));
}

