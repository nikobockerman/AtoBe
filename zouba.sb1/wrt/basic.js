///////////////////////////////////////////////////////////////////////////////
// The FeedUpdateBroker class implements a simple RSS fetcher and parser.

var username = "zouba";
var password = "caf9r3ee";

var homeKey = "taivaanvuohentie%207%2Chelsinki";
var workKey = "it%E4merenkatu%2011%2Chelsinki";

var work = {
    x: 2551042,
    y: 6672829
};
var home = {
    x: 2549183,
    y: 6672570
};

var keyA = work;
var keyB = home;

// Feed update broker.
var feedUpdateBroker = null;

// Constructor.
function FeedUpdateBroker()
{
    this.httpReq = null;
    this.callback = null;
}

// Fetches a feed from the specified URL and calls the callback when the feed
// has been fetched and parsed, or if the process results in an error.
FeedUpdateBroker.prototype.fetchFeed = function(feedURL, callback)
{
    // remember callback
    this.callback = callback;
    
    // create new XML HTTP request
    this.httpReq = new Ajax();
    
    // set callback
    var self = this;
    this.httpReq.onreadystatechange = function()
    {
        self.readyStateChanged();
    };
    
    // append the current time after the URL to bypass caches
    var fullURL = feedURL;
    if (fullURL.indexOf("?") == -1) {
        fullURL += "?";
    }
    else {
        fullURL += "&";
    }
    fullURL += "nocache=" + (new Date().getTime());
    
    // initiate the request
    this.httpReq.open("GET", fullURL, true);
    this.httpReq.send(null);
}

// Callback for ready-state change events in the XML HTTP request.
FeedUpdateBroker.prototype.readyStateChanged = function()
{
    // complete request?
    if (this.httpReq.readyState == 4) {
        // attempt to get response status
        var responseStatus = null;
        try {
            responseStatus = this.httpReq.status;
        } 
        catch (noStatusException) {
        }
        
        this.callback(responseStatus, this.httpReq.responseXML);
    }
}

function parseRouteXML(responseStatus, xmlDoc)
{
  if (responseStatus == 200 && xmlDoc != null) {
    var routes = xmlDoc.getElementsByTagName("ROUTE");

    for (var i = routes.length - 1; i >= 0; i--){
      var lines = routes[i].getElementsByTagName("LINE");
      var firstLine = lines[0];
      var joreCode = firstLine.getAttribute("code");

      var stop = firstLine.getElementsByTagName("STOP")[0];
      var arrival = stop.getElementsByTagName("ARRIVAL")[0];
      var arrivalTime = arrival.getAttribute("time");
      addRow( joreCode, arrivalTime );
    };		
  }
}

function addRow( joreCode, timeAtStop )
{
  var timeTable = document.getElementById("timeTable");

  var newRow = timeTable.insertRow(0);
  var codeCell       = newRow.insertCell(0);
  var timeAtStopCell = newRow.insertCell(1);
  codeCell.innerHTML       = parseJORECode(joreCode);
  timeAtStopCell.innerHTML = timeAtStop;
}


function parseHomeXML(responseStatus, xmlDoc)
{
    if (responseStatus == 200 && xmlDoc != null) {
        var location = xmlDoc.getElementsByTagName("LOC");
        var firstLocation = location[0];
        
        home.x = firstLocation.getAttribute("x");
        home.y = firstLocation.getAttribute("y");
    }
}

function parseWorkXML(responseStatus, xmlDoc)
{
    if (responseStatus == 200 && xmlDoc != null) {
        var location = xmlDoc.getElementsByTagName("LOC");
        var firstLocation = location[0];
        
        work.x = firstLocation.getAttribute("x");
        work.y = firstLocation.getAttribute("y");
    }
}

function getRoute()
{
    var feedURL = "http://api.reittiopas.fi/public-ytv/fi/api/?a=" + keyA.x + "," + keyA.y + "&b=" + keyB.x + "," + keyB.y + "&user=" + username + "&pass=" + password;
    feedUpdateBroker.fetchFeed(feedURL, parseRouteXML);
}

function parseJORECode(joreCode)
{
    var areaTransportTypeCode = joreCode.substring(0, 1);
    var lineCode = joreCode.substring(1, 5);
    var letterVariant = joreCode.substring(5, 6);
    var letterNumberVariant = joreCode.substring(6, 7);
    var direction = joreCode.substring(7, 8);
    
    return "" + lineCode + letterVariant;
}

function emptyTable()
{
  var table = document.getElementById("timeTable");
  var rows = table.rows;
  for (var i = rows.length - 1; i >= 0; i--){
    table.deleteRow(i);
  }
  document.getElementById("debug").innerHTML = "";
}

function takeMeHome()
{
    emptyTable();

    keyA = work;
    keyB = home;
    
    getRoute();
}

function takeMeToWork()
{
    emptyTable();

    keyA = home;
    keyB = work;
    
    getRoute();
}

var so;

try {
    //Retrieves the Service object to the ILocation interface
    so = device.getServiceObject("Service.Location", "ILocation");
    document.getElementById("debug").innerHTML = "after so";
} catch (e) {
    document.getElementById("debug").innerHTML = ' ' +e;
    //alert(' ' +e);
}
 
// Gets the GPS position
function getLocationAsync()
{
    document.getElementById("debug").innerHTML = "getLocationAsync()";
    // This specifies update option used while retrieving location estimation. 
    var updateoptions = new Object();
    // Setting PartialUpdates to 'FALSE' ensures that user get atleast 
    // BasicLocationInformation (Longitude, Lattitude, and Altitude.) is the default when no LocationInformationClass criteria is given.
    updateoptions.PartialUpdates = false;
 
    var criteria = new Object();
 
    criteria.Updateoptions = updateoptions;
 
    try {
    //Executes the GetLocation method and sets the callbackLocation as the callback function to be called.
    so.ILocation.GetLocation(criteria,callbackLocation);
    } catch (e) {
        document.getElementById("debug").innerHTML = "getLocationAsync: " + e;
        //alert ("getLocationAsync: " + e);
    }
}

//Callback function that receives the result as parameter.
function callbackLocation(transId, eventCode, result)
{
    var latitude = result.ReturnValue.Latitude;
    var longitude = result.ReturnValue.Longitude;
    document.getElementById("debug").innerHTML = latitude+":"+longitude;
}

function init()
{
    feedUpdateBroker = new FeedUpdateBroker();
    
    var homeURL = "http://api.reittiopas.fi/public-ytv/fi/api/?key=" + homeKey + "&user=" + username + "&pass=" + password;
    feedUpdateBroker.fetchFeed(homeURL, parseHomeXML);
    
    var workURL = "http://api.reittiopas.fi/public-ytv/fi/api/?key=" + workKey + "&user=" + username + "&pass=" + password;
    feedUpdateBroker.fetchFeed(workURL, parseWorkXML);

    //getLocationAsync();
}
