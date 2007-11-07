/*---------------------------------------------------------------------*/
/// <copyright from='2006' to='2006' company='Yahoo! Inc.'>
/// (C) Copyright 2006 Yahoo! Inc. All Rights Reserved.
/// </copyright>

/**
 * ImageComboBox control.
 */
/*---------------------------------------------------------------------*/

/*---------------------------------------------------------------------*/
// Constructor
/*---------------------------------------------------------------------*/
/**
 * Default constructor.
 * @constructor
 * @param {Yahoo.Controls.Theme} theme The theme this control should use or null to create an instance of the default theme.
 * @param {String} themePrefix The prefix used to retrieve styles from the theme for this control.
 */
Yahoo.Controls.ImageComboBox = function(theme, themePrefix) {

	//log("ImageComboBox.ctor()");
	if(arguments.length>0) {
		this.initialize(theme, themePrefix);
	}
}

/**
 * Define inheritance chain.
 */
Yahoo.Controls.ImageComboBox.prototype = new Yahoo.Controls.Control();
Yahoo.Controls.ImageComboBox.prototype.constructor = Yahoo.Controls.ImageComboBox;
Yahoo.Controls.ImageComboBox.prototype.baseclassImageComboBox = Yahoo.Controls.Control.prototype;

/*-----------------------------------------------------------*/
// Control code
/*-----------------------------------------------------------*/
/**
 * Raises the onEnabledChanged event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.ImageComboBox.prototype._onEnabledChanged = function(sender, e) {

	//log("ImageComboBox._onEnabledChanged");

	// Call baseclass
	this.baseclassImageComboBox._onEnabledChanged.call(this, sender, e);

	this._btnDropDown.enabled = this.enabled;
}

/**
 * Raises the onToolTipChanged event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.ImageComboBox.prototype._onToolTipChanged = function(sender, e) {

	//log("ImageComboBox._onToolTipChanged");

	// Call baseclass
	this.baseclassImageComboBox._onToolTipChanged.call(this, sender, e);
	
	// Set tooltip
	this._btnDropDown.toolTip = this.toolTip;
}

/**
 * Raises the onSelectedIndexChanged event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.ImageComboBox.prototype._onSelectedIndexChanged = function(sender, e) {

	//log("ImageComboBox._onSelectedIndexChanged");

	if(this._selectedIndex!=-1) {
		this._text = this._items.item(this._selectedIndex).toString();
	}
	else {
		this._text = "";
	}

	// Raise event
	Yahoo.raiseEvent(sender, sender._onSelectedIndexChangedEventHandlers, e);
}

/**
 * Raises the onThemeChanged event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.ImageComboBox.prototype._onThemeChanged = function(sender, e) {

	//log("ImageComboBox._onThemeChanged");

	// Call base class
	this.baseclassImageComboBox._onThemeChanged.call(this, sender, e);

	this._imageComboBox_loadTheme();
}

/**
 * Handles onMouseEnter event for image.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.ImageComboBox.prototype._imageComboBox_btnDropDown_onEnter = function(sender, e) {

	//log("ImageComboBox._imageComboBox_btnDropDown_onEnter");

	sender.parent._onEnter.call(sender.parent, sender.parent, new Yahoo.EventArgs());
}

/**
 * Handles onMouseExit event for imagebutton.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.ImageComboBox.prototype._imageComboBox_btnDropDown_onLeave = function(sender, e) {

	//log("ImageComboBox._imageComboBox_btnDropDown_onLeave");
	
	// Don't forward this if we are still within the parent control
	if(sender.parent.displayRectangle.contains(system.event.x + sender.left + sender.parent.left, system.event.y + sender.top + sender.parent.top) == false) {
		sender.parent._onLeave.call(sender.parent, sender.parent, new Yahoo.EventArgs());
	}
}

/**
 * Handles onMouseDown event for imagebutton.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.ImageComboBox.prototype._imageComboBox_btnDropDown_onMouseDown = function(sender, e) {

	//log("ImageComboBox._imageComboBox_btnDropDown_onMouseDown");
	sender.parent._onMouseDown.call(sender.parent, sender.parent, new Yahoo.EventArgs());
	// Opening the menu will mess with the buttons mouse state flags, reset them here
	sender.parent._btnDropDown._isMouseOver = false;
	sender.parent._btnDropDown._isMouseDown = false;
	sender.parent._btnDropDown._imageButton_setButtonState();
	sender.parent._imageComboBox_showMenu.call(sender.parent);
}

/**
 * Handles onMouseUp event for imagebutton.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.ImageComboBox.prototype._imageComboBox_btnDropDown_onMouseUp = function(sender, e) {

	//log("ImageComboBox._imageComboBox_btnDropDown_onMouseUp");
	sender.parent._onMouseUp.call(sender.parent, sender.parent, new Yahoo.EventArgs());
}

/**
 * Handles click event for comboitem.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.ImageComboBox.prototype._imageComboBox_item_onClick = function() {

	//log("ComboBox._imageComboBox_item_onClick");
    this.tag.selectedIndex = this.index;
}

/*---------------------------------------------------------------------*/
// Private code
/*---------------------------------------------------------------------*/
/**
 * Disposes native Widget Engine objects.
 * @private
 */
Yahoo.Controls.ImageComboBox.prototype._imageComboBox_disposeNativeObjects = function() {

	//log("ImageComboBox._imageComboBox_disposeNativeObjects");

	// These aren't native objects, but we still dispose them here
	if(this._btnDropDown!=null) { this._btnDropDown.dispose(); this._btnDropDown = null; }
}

/**
 * Loads control elements based on current theme.
 * @private
 */
Yahoo.Controls.ImageComboBox.prototype._imageComboBox_loadTheme = function() {

	// Remove any current objects
	this._imageComboBox_disposeNativeObjects();

	this._btnDropDown = new Yahoo.Controls.ImageButton(this._theme, this._themePrefix + "Normal", this._themePrefix + "Over", this._themePrefix + "Down", this._themePrefix + "Disabled");
	this._btnDropDown.addEventHandler(this._imageComboBox_btnDropDown_onEnter, "Enter");
	this._btnDropDown.addEventHandler(this._imageComboBox_btnDropDown_onLeave, "Leave");
	this._btnDropDown.addEventHandler(this._imageComboBox_btnDropDown_onMouseDown, "MouseDown");
	this._btnDropDown.addEventHandler(this._imageComboBox_btnDropDown_onMouseUp, "MouseUp");
	this._btnDropDown.zOrder = 5;
	this.addControl(this._btnDropDown);
}

/**
 * Displays menu.
 * @private
 */
Yahoo.Controls.ImageComboBox.prototype._imageComboBox_showMenu = function() {

	var count;
	var menu = new Array();
	var point;

	for(count=0; count<this._items.count; count++) {
		menu[count] = new MenuItem();
		menu[count].title = this._items.item(count).toString();
		menu[count].index = count;
		menu[count].tag = this;
		menu[count].onSelect = this._imageComboBox_item_onClick;
		
		if(this._showCheckmark == true) {
		    if(count == this._selectedIndex) {
		        menu[count].checked = true;
		    }
		}
	}  // for items
	
	if(menu.length>0) {
		point = this.pointToClient(new Yahoo.Drawing.Point(0, this.height));
		popupMenu(menu, point.x, point.y);
	}
}

/*---------------------------------------------------------------------*/
// Public code
/*---------------------------------------------------------------------*/
/**
 * True constructor. Must be called if this class is overridden.
 * @param {Yahoo.Controls.Theme} theme The theme this control should use or null to create an instance of the default theme.
 * @param {String} themePrefix The prefix used to retrieve styles from the theme for this control.
 */
Yahoo.Controls.ImageComboBox.prototype.initialize = function(theme, themePrefix) {

	//log("ImageComboBox.initialize()");
	
	// Call baseclass constructor
	this.baseclassImageComboBox.initialize.call(this, theme, "comboBox");

	this._themePrefix = themePrefix;
	this._showCheckmark = true;

	// Includes handled by baseclass
	//lib.include("Yahoo.ArgumentNullException");
	//lib.include("Yahoo.ArgumentOutOfRangeException");
	//lib.include("Yahoo.Controls.Theme");
	//lib.include("Yahoo.Drawing.Rectangle");

	// Includes
	lib.include("Yahoo.Controls.ImageButton");

	// Initialize variables/controls
	this._items = new Yahoo.Controls.ImageComboBox.ObjectCollection();
	this._selectedIndex = -1
	
	this._onSelectedIndexChangedEventHandlers = new Array();

	this._imageComboBox_loadTheme();
}

/**
 * Adds an event handler. Supported events are: SelectedIndexChanged.
 * @param {Function} eventHandler The function that is to be called when the event is raised.
 * @param {String} eventName The name of the event that is being listened to.
 */
Yahoo.Controls.ImageComboBox.prototype.addEventHandler = function(eventHandler, eventName) {

	// Call baseclass
	this.baseclassImageComboBox.addEventHandler.call(this, eventHandler, eventName)

	switch(eventName) {
		case "SelectedIndexChanged":
			this._onSelectedIndexChangedEventHandlers.push(eventHandler);
			break;
	}
}

/**
 * Disposes control's resources.
 */
Yahoo.Controls.ImageComboBox.prototype.dispose = function() {
	
	this._imageComboBox_disposeNativeObjects();

	// Call baseclass
	this.baseclassImageComboBox.dispose.call(this);

	// Baseclass disposes our custom controls
}

/*---------------------------------------------------------------------*/
// Public properties
/*---------------------------------------------------------------------*/
/**
 * Gets the collection of items in the combobox.
 * @type Yahoo.Controls.ImageComboBox.ObjectCollection
 */
Yahoo.Controls.ImageComboBox.prototype.items getter = function() {

	return this._items;
}

Yahoo.Controls.ImageComboBox.prototype.items setter = function(value) {
	
	throw new Error("items is read-only");
}

/**
 * Gets or sets the selected item index.
 * @type Integer
 */
Yahoo.Controls.ImageComboBox.prototype.selectedIndex getter = function() {

	return this._selectedIndex;
}

Yahoo.Controls.ImageComboBox.prototype.selectedIndex setter = function(value) {

	if(value!=null) {
		if(this._selectedIndex!=value) {
			if(value<-1 || value>=this._items.count) {
				throw new Yahoo.ArgumentOutOfRangeException("value");
			}
			else {
				this._selectedIndex = value;
				this._onSelectedIndexChanged(this, new Yahoo.EventArgs());
			}
		}
	}
	else {
		throw new Yahoo.ArgumentNullException("value");
	}
}

/**
 * Gets or sets a value indicating whether the selected item will have a checkmark.
 * @type Boolean
 */
Yahoo.Controls.ImageComboBox.prototype.showCheckmark getter = function() {

	return this._showCheckmark;
}

Yahoo.Controls.ImageComboBox.prototype.showCheckmark setter = function(value) {

	if(value!=null) {
		this._showCheckmark = value;
	}
	else {
		throw new Yahoo.ArgumentNullException("value");
	}
}

/*---------------------------------------------------------------------*/
/// <copyright from='2005' to='2006' company='Yahoo! Inc.'>
/// (C) Copyright 2005-2006 Yahoo! Inc. All Rights Reserved.
/// </copyright>

/**
 * ImageComboBoxCollection control.
 */
/*---------------------------------------------------------------------*/

/*---------------------------------------------------------------------*/
// Namespace
/*---------------------------------------------------------------------*/
// Create namespace Yahoo.Controls if it doesn't already exist
if(Yahoo==undefined) { var Yahoo = new Object(); }
if(Yahoo.Windows==undefined) { Yahoo.Windows = new Object(); }
if(Yahoo.Controls==undefined) { Yahoo.Controls = new Object(); }

/*---------------------------------------------------------------------*/
// Constructor
/*---------------------------------------------------------------------*/
/**
 * Default constructor.
 */
Yahoo.Controls.ImageComboBox.ObjectCollection = function() {

	//log("ImageComboBox.ObjectCollection.ctor()");
	this.initialize();
}

/*---------------------------------------------------------------------*/
// Private code
/*---------------------------------------------------------------------*/

/*---------------------------------------------------------------------*/
// Public code
/*---------------------------------------------------------------------*/
/**
 * True constructor. Must be called if this class is overridden.
 */
Yahoo.Controls.ImageComboBox.ObjectCollection.prototype.initialize = function() {

	//log("ImageComboBox.ObjectCollection.initialize()");

	this._items = new Array();	
}

/**
 * Adds an item to the collection.
 * @param {Object} item The item to add to the collection.
 */
Yahoo.Controls.ImageComboBox.ObjectCollection.prototype.add = function(item) {
	
	var result = -1;
	
	if(item!=null) {
		result = this._items.push(item) - 1;
	}
	else {
		throw new Yahoo.ArgumentNullException("item");
	}

	return result;	
}

/**
 * Removes all items from the collection.
 */
Yahoo.Controls.ImageComboBox.ObjectCollection.prototype.clear = function() {
	
	delete this._items;
	this._items = new Array();
}

/**
 * Gets the index of the given item.
 * @param {Object} item The item to to find in the collection.
 */
Yahoo.Controls.ImageComboBox.ObjectCollection.prototype.indexOf = function(item) {
	
	var count;
	var result = -1;

	if(item!=null) {

		// Find the item
		for(count=0; count<this._items.length; count++) {
			if(this._items[count] == item) {
				result = count;
				break;
			} //if(items[count]==item)
		}
	}

	return result;
}

/**
 * Gets the item at the given index.
 * @param {Integer} index The index of the item to retrieve from the collection.
 */
Yahoo.Controls.ImageComboBox.ObjectCollection.prototype.item = function(index) {

	if(index>=0 && index<this._items.length) {
		return this._items[index];
	}
	else {
		throw new Yahoo.ArgumentOutOfRange("index");
	}
}

/**
 * Removes the given item from the collection.
 * @param {Object} item The item to remove from the collection.
 */
Yahoo.Controls.ImageComboBox.ObjectCollection.prototype.remove = function(item) {

	var position = -1;

	if(item!=null) {

		// Find the item
		position = this._items.indexOf(item);

		// Make sure we found the item
		if(position != -1) {
			// Remove the item
			this._items.splice(position, 1);
		}  // position != -1

	}
	else {
		throw new Yahoo.ArgumentNullException("item");
	}
}

/**
 * Removes the item at the given index from the collection.
 * @param {Integer} index The index of the item to remove from the collection.
 */
Yahoo.Controls.ImageComboBox.ObjectCollection.prototype.removeAt = function(index) {

	var position = -1;

	if(index>=0 && index<this._items.length) {
		// Remove the item
		this._items.splice(index, 1);
	}
	else {
		throw new Yahoo.ArgumentOutOfRange("index");
	}
}

/*---------------------------------------------------------------------*/
// Public properties
/*---------------------------------------------------------------------*/
/**
 * Gets the number of items in the collection.
 * @type Integer
 */
Yahoo.Controls.ImageComboBox.ObjectCollection.prototype.count getter = function() {

	return this._items.length;
}

Yahoo.Controls.ImageComboBox.ObjectCollection.prototype.count setter = function(value) {

	throw new Error("count is read-only");
}

