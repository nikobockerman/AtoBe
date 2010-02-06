///////////////////////////////////////////////////////////////////////////////
// RSS Reader example widget that demonstrates use of the WRTKit UI toolkit
// in a real-world widget.

// Feed update frequency.
var updateFrequencyOptions = [
    { value: -1, text: "never" },
    { value: (1000 * 60 * 5), text: "every 5 min" },
    { value: (1000 * 60 * 15), text: "every 15 min" },
    { value: (1000 * 60 * 60), text: "every 60 min" },
];

// Feed update broker.
var feedUpdateBroker = null;

// Reference to current feed items controls.
var feedItemControls = [];

// Feed item control pool.
var feedItemControlPool = [];

// Time when the feed was last modified.
var feedLastModified = null;

// Flag that tracks if a feed update is commanded or automatic.
var feedUpdateCommanded = false;

// Reference to the WRTKit user interface manager and views.
var uiManager;
var mainView;
var settingsView;

// Reference to settings controls.
var feedNameText;
var feedUrlText;
var feedSelection;
var feedUpdateFrequencySelection;
var settingsSaveButton;
var settingsCancelButton;

// Constants for menu item identifiers.
var MENU_ITEM_SETTINGS = 0;
var MENU_ITEM_REFRESH = 1;
var MENU_ITEM_ABOUT = 2;

// Feed update timer identifier.
var updateTimerId = null;

//About menu lable
var aboutLabel;

// Feed name, URL and update frequency (in milliseconds; -1 if no auto update).
var feedName = "CNN Top Stories";
var feedURL = "http://rss.cnn.com/rss/cnn_topstories.rss";
//var feedURL = "feed.xml";
var feedUpdateFrequency = -1;

// Next scheduled update time; -1 if never.
var feedUpdateTime = -1;

// Called from the onload event handler to initialize the widget.
function init() {
    if (window.widget) {
        // set tab-navigation mode and show softkeys
        widget.setNavigationEnabled(false);
        window.menu.showSoftkeys();
        
        // create menu
        var settingsMenuItem = new MenuItem("Settings", MENU_ITEM_SETTINGS);
        settingsMenuItem.onSelect = menuItemSelected;
        menu.append(settingsMenuItem);
        var refreshMenuItem = new MenuItem("Refresh", MENU_ITEM_REFRESH);
        refreshMenuItem.onSelect = menuItemSelected;
        menu.append(refreshMenuItem);
		var aboutMenuItem = new MenuItem("About", MENU_ITEM_ABOUT);
		aboutMenuItem.onSelect = menuItemSelected;
		menu.append(aboutMenuItem);
    }
    
	// load preferences
	loadPreferences();

    // create UI manager
    uiManager = new UIManager();
    
    // create main view
    mainView = new ListView();
    
    // create settings view
    settingsView = new ListView(null, "Settings");
	
	//Create about view
	aboutView = new ListView(null, "RSS Reader");
    
    // feed name control
    feedNameText = new TextField('feedNameText', "Feed name", feedName);
    settingsView.addControl(feedNameText);
	
    // feed url control
    feedUrlText = new TextField('feedUrlText', "Feed URL", feedURL);
    settingsView.addControl(feedUrlText);

	// About lable control
	aboutLabel = new Label();
	aboutView.addControl(aboutLabel);
	
    // feed update frequency selection control
    feedUpdateFrequencySelection = new SelectionList(null, "Check for updates", updateFrequencyOptions);
    settingsView.addControl(feedUpdateFrequencySelection);
    
    // save settings button
    settingsSaveButton = new FormButton(null, "Save");
    settingsSaveButton.addEventListener("ActionPerformed", saveSettingsClicked);
    settingsView.addControl(settingsSaveButton);
    
    // cancel settings button
    settingsCancelButton = new FormButton(null, "Cancel");
    settingsCancelButton.addEventListener("ActionPerformed", showMainView);
    settingsView.addControl(settingsCancelButton);
    
    // display the main view if a feed has been configured
    // otherwise show the settings view
	if (feedURL != null) {
        showMainView();
        updateFeed();
    } else {
        showSettings();
    }
    // start feed update timer (called once every second)
    updateTimerId = setInterval(updateFeedTimerFunc, 1000);
}

// Callback for when menu items are selected.
function menuItemSelected(id) {
    switch (id) {
        case MENU_ITEM_SETTINGS:
            showSettings();
            break;
        case MENU_ITEM_REFRESH:
            updateFeed();
            break;
		case MENU_ITEM_ABOUT:
			showAboutView();
			break;
    }
}

// Loads widget preferences.
function loadPreferences() {
    if (window.widget) {
        // read feed URL, name and update frequency from the widget settings
		
		if (typeof widget.preferenceForKey("FeedURL") != 'undefined' && typeof widget.preferenceForKey("FeedName") != 'undefined') {
			feedURL = widget.preferenceForKey("FeedURL");
			feedName = widget.preferenceForKey("FeedName");
			var feedUpdateFrequencyStr = widget.preferenceForKey("FeedUpdateFrequency");
			feedUpdateFrequency = (feedUpdateFrequencyStr == null) ? -1 : parseInt(feedUpdateFrequencyStr);
		}
    }
}

// Loads widget preferences.
function savePreferences() {
    if (window.widget) {
        // save settings in widget preferences store
        widget.setPreferenceForKey(feedURL, "FeedURL");
        widget.setPreferenceForKey(feedName, "FeedName");
        widget.setPreferenceForKey(feedUpdateFrequency.toString(), "FeedUpdateFrequency");
    }
}

// Callback for settings view save button.
function saveSettingsClicked() {
    // remember old URL
    var oldURL = feedURL;
    
    // update feed name and URL
    var selectedFeed = feedUrlText.getText();

    if (selectedFeed != null) {
        feedURL = selectedFeed;
        feedName = feedNameText.getText();
    } else {
        feedURL = null;
        feedName = null;
    }
    
    // update frequency
    var selectedFrequency = feedUpdateFrequencySelection.getSelected();
    feedUpdateFrequency = (selectedFrequency != null) ? selectedFrequency.value : -1;
    
    // save preferences
    savePreferences();
    
    // return to main view
    showMainView();
    
    // update the feed if the feed URL has changed
    if (feedURL != oldURL) {
        feedLastModified = null;
        removeFeedItems();
        updateFeed();
    }
}

// Show main view.
function showMainView() {
    // set main view caption from feed name
    var mainViewCaption = (feedName == null) ? null : feedName;
    mainView.setCaption(mainViewCaption);
    
    // set right softkey to "exit"
    if (window.widget) {
        menu.setRightSoftkeyLabel("", null);
    }
    
    // show the main view
    uiManager.setView(mainView);
}

// Show settings view.
function showSettings() {
    // Feed Name
    feedNameText.setText(feedName);

    // URL
    feedUrlText.setText(feedURL);
		
    // frequency
    var feedUpdateFrequencyOption = feedUpdateFrequencySelection.getOptionForValue(feedUpdateFrequency);
    feedUpdateFrequencySelection.setSelected(feedUpdateFrequencyOption);
    
    if (feedURL == null) {
        // no valid configuration
        // disable cancel button - set right softkey to "exit"
        settingsCancelButton.setEnabled(false);
        if (window.widget) {
            menu.setRightSoftkeyLabel("", null);
        }
    } else {
        // we have a valid configuration
        // enable cancel button - set right softkey to "cancel"
        settingsCancelButton.setEnabled(true);
        if (window.widget) {
            menu.setRightSoftkeyLabel("Cancel", showMainView);
        }
    }
    
    // show the settings view
    uiManager.setView(settingsView);
}

//Displays the About view
function showAboutView(){
	aboutLabel.setText("This Widget includes software licensed from Nokia &copy 2008");
	
	setAboutViewSoftkeys();
	uiManager.setView(aboutView);
}

// Sets the softkeys for about view.
function setAboutViewSoftkeys() {
    if (window.widget) {
        // set right softkey to "Ok" (returns to main view)
        menu.setRightSoftkeyLabel("Ok", showMainView);
    }
}

// Schedules an immediate feed update.
function updateFeed() {
    feedUpdateTime = 0;
    feedUpdateCommanded = true;
}


// Timer function for feed updates - called once every second.
function updateFeedTimerFunc() {
    var now = new Date().getTime();
    
    // check if a feed update has been scheduled, if it's time to update now,
    // and if there's no update currently in progress and if we're in the main view
    if ((feedURL != null) &&
                (feedUpdateTime != -1) &&
                (now > feedUpdateTime) &&
                (feedUpdateBroker == null) && 
                (uiManager.getView() == mainView)) {
        // show progress dialog if this is a commanded feed update
        if (feedUpdateCommanded) {
            // no auto hiding, wait-type notification, unknown progress
            uiManager.showNotification(-1, "wait", "Loading feed...", -1);
        }
        
        // fetch the feed from the specified URL
        feedUpdateBroker = new FeedUpdateBroker();
        feedUpdateBroker.fetchFeed(feedURL, feedUpdateCompleted);
        
        if (feedUpdateFrequency != -1) {
            // schedule next update
            feedUpdateTime = now + feedUpdateFrequency;
        } else {
            // feed update frequency is "never"
            feedUpdateTime = -1;
        }
    }
}

// Callback function that gets called when a feed update has completed.
function feedUpdateCompleted(event) {
    if (event.status == "ok") {
        // if there aren't any feed items yet, we'll hide the progress dialog
        if (feedUpdateCommanded) {
            uiManager.hideNotification();
        }
        
        // check if the feed has updated
        if (event.lastModified != feedLastModified) {
            // remember the last modified timestamp
            feedLastModified = event.lastModified;
            
            // feed fetched and parsed successfully
            setFeedItems(event.items);
            
            // focus the first feed item control
            // (but only if we are in the main view)
            if (uiManager.getView() == mainView) {
                feedItemControls[0].setFocused(true);
            }
        }
    } else {
        // show error message
        uiManager.showNotification(3000, "warning", "Error while updating feed!<br/>(check network settings)");
    }
    
    // null the broker reference to indicate that there's no current
    // update in progress
    feedUpdateBroker = null;
    
    // reset commanded feed update flag
    feedUpdateCommanded = false;
}

// Removes feed items.
function removeFeedItems() {
    // remove all current feed items from the main view
    for (var i = 0; i < feedItemControls.length; i++) {
        mainView.removeControl(feedItemControls[i]);
    }
    
    // reset feed item control array
    feedItemControls = [];
}

// Sets feed items.
function setFeedItems(items) {
    // start by removing all current feed items
    removeFeedItems();
    
    // create new feed items and add them to the main view
    // use feed item pool to recycle controls
    for (var i = 0; i < items.length; i++) {
        // get a feed item control from the pool or create one and
        // place it in the pool if there aren't enough feed item controls
        var feedItemControl;
        if (i == feedItemControlPool.length) {
            feedItemControl = new ContentPanel(null, null, null, true);
            feedItemControlPool.push(feedItemControl);
        } else {
            feedItemControl = feedItemControlPool[i];
        }
        
        // initialize feed item control
        var item = items[i];
        feedItemControl.setCaption(item.title);
        feedItemControl.setContent(getContentHTMLForFeedItem(item));
        feedItemControl.setExpanded(false);
        
        // add the feed item control to the main view
        feedItemControls.push(feedItemControl);
        mainView.addControl(feedItemControl);
    }
}

// Returns the content HTML for a feed item.
function getContentHTMLForFeedItem(item) {
    var buf = "";
    
    // item date
    if (item.date != null) {
        buf += "<div class=\"FeedItemDate\">" + item.date + "</div>";
    }
    
    // item description
    if (item.description != null) {
        buf += "<div class=\"FeedItemDescription\">" + item.description + "</div>";
    }
    
    // item URL
    if (item.url != null) {
        buf += "<div class=\"FeedItemLink\">";
            buf += "<a href=\"JavaScript:void(0)\" onclick=\"openURL('" + item.url + "'); return false;\">";
            buf += "Read more...";
            buf += "</a>";
        buf += "</div>";
    }
    
    return buf;
}

// Opens a URL.
function openURL(url) {
    if (window.widget) {
        // in WRT
        widget.openURL(url);
    } else {
        // outside WRT
        window.open(url, "NewWindow");
    }
}
