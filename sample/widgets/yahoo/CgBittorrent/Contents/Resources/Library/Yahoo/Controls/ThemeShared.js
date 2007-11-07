/*---------------------------------------------------------------------*/
/// <copyright from='2005' to='2006' company='Yahoo! Inc.'>
/// (C) Copyright 2005-2006 Yahoo! Inc. All Rights Reserved.
/// </copyright>

/**
 * Theme class.
 */
/*---------------------------------------------------------------------*/

/*---------------------------------------------------------------------*/
// Namespace
/*---------------------------------------------------------------------*/
// Create namespace if it doesn't already exist
if(Yahoo==undefined) { var Yahoo = new Object(); }
if(Yahoo.Controls==undefined) { Yahoo.Controls = new Object(); }

/*---------------------------------------------------------------------*/
// Constructor
/*---------------------------------------------------------------------*/
/**
 * Default constructor.
 * @constructor
 * @param {String} themePath The path to the theme folder.
 */
Yahoo.Controls.Theme = function(themePath) {

	if(arguments.length > 0) {
		this.initialize(themePath);
	}  //arguments.length > 0
}

/*---------------------------------------------------------------------*/
// Private code
/*---------------------------------------------------------------------*/
/**
 * Loads themes from given widgetPath into internal array.
 * @private
 */
Yahoo.Controls.Theme.prototype._theme_getThemes = function() {

	var contents;
	var count;
	
	this._themes = new Array();

	if(filesystem.itemExists(this._themePath) == true) {
		contents = filesystem.getDirectoryContents(this._themePath, false)
		for(count=0; count<contents.length; count++) {
			if(filesystem.isDirectory(this._themePath + "/" + contents[count]) == true) {
				if(filesystem.itemExists(this._themePath + "/" + contents[count] + "/" + contents[count] + ".xml") == true) {
					this._themes.push(contents[count]);
				}
			}
		}  // for(contents)
	}  // If themes-folder exists
	else {
		throw new Error("Specified Themes folder does not exist: '" + this._themePath + "'");
	}  // If themes-folder exists
}

/**
 * Returns a Widget Engine Image object based on given theme style.
 * @private
 * @param {DOMNode} itemNode The item node in the theme definition. Styles from this will override styleNode definitions.
 * @param {DOMNode} styleNode The item node in the theme definition.
 * @type Image
 */
Yahoo.Controls.Theme.prototype._theme_getImageObject = function(itemNode, styleNode) {

	var src;
	var result;
	
	if(itemNode!=null && styleNode!=null) {
		result = new Image();

		// Required properties from style
		src = styleNode.getAttribute("src");
		if(src!="") {
			if(src.substring(1,7)=="http://") {
				result.src = src
			}  // If have URL
			else {
				// Have a filename, prefix with themes folder path
				result.src = this._themePath + "/" + this.themeName + "/" + src;
			}  // If have URL
		}
		else {
			throw new Error("Missing src on style '" + styleNode.getAttribute("id") + "'");
		}

		// Set attributes from style
		this._theme_setImageAttributes(result, styleNode);
		
		// Override attributes from item, if any
		this._theme_setImageAttributes(result, itemNode);
		
	}
	else {
		throw new Error("Missing itemNode or styleNode.");
	}

	return result;
}

/**
 * Returns a Widget Engine Text object based on given theme style.
 * @private
 * @param {DOMNode} itemNode The item node in the theme definition. Styles from this will override styleNode definitions.
 * @param {DOMNode} styleNode The item node in the theme definition.
 * @type Text
 */
Yahoo.Controls.Theme.prototype._theme_getLabelObject = function(itemNode, styleNode) {

	var result;
	
	if(itemNode!=null && styleNode!=null) {
		result = new Text();

		// Set attributes from style
		this._theme_setLabelAttributes(result, styleNode);
		
		// Override attributes from item, if any
		this._theme_setLabelAttributes(result, itemNode);

	}
	else {
		throw new Error("Missing itemNode or styleNode.");
	}

	return result;
}

/**
 * Returns a Widget Engine TextArea object based on given theme style.
 * @private
 * @param {DOMNode} itemNode The item node in the theme definition. Styles from this will override styleNode definitions.
 * @param {DOMNode} styleNode The item node in the theme definition.
 * @type TextArea
 */
Yahoo.Controls.Theme.prototype._theme_getTextBoxObject = function(itemNode, styleNode) {

	var result;
	
	if(itemNode!=null && styleNode!=null) {
		result = new TextArea();

		// Set attributes from style
		this._theme_setTextBoxAttributes(result, styleNode);
		
		// Override attributes from item, if any
		this._theme_setTextBoxAttributes(result, itemNode);

	}
	else {
		throw new Error("Missing itemNode or styleNode.");
	}

	return result;
}

/**
 * Sets label (Text) attributes from given node.
 * @private
 * @param {Text} label Text object which will be modified.
 * @param {DOMNode} node The style node used to set properties.
 */
Yahoo.Controls.Theme.prototype._theme_setLabelAttributes = function(label, node) {

		if(node.getAttribute("alignment") != "") {
			label.alignment = node.getAttribute("alignment");
		}
		if(node.getAttribute("background-color") != "") {
			label.style.backgroundColor = node.getAttribute("background-color");
		}
		if(node.getAttribute("bgColor") != "") {
			label.bgColor = node.getAttribute("bgColor");
		}
		if(node.getAttribute("bgOpacity") != "") {
			label.bgOpacity = node.getAttribute("bgOpacity");
		}
		if(node.getAttribute("color") != "") {
			label.color = node.getAttribute("color");
		}
		if(node.getAttribute("data") != "") {
			label.data = node.getAttribute("data");
		}
		if(node.getAttribute("font") != "") {
			label.font = node.getAttribute("font");
		}
		if(node.getAttribute("font-family") != "") {
			label.style.fontFamily = node.getAttribute("font-family");
		}
		if(node.getAttribute("font-size") != "") {
			label.style.fontSize = node.getAttribute("font-size");
		}
		if(node.getAttribute("font-weight") != "") {
			label.style.fontWeight = node.getAttribute("font-weight");
		}
		if(node.getAttribute("hAlign") != "") {
			label.hAlign = node.getAttribute("hAlign");
		}
		if(node.getAttribute("height") != "") {
			label.height = node.getAttribute("height");
		}
		if(node.getAttribute("hOffset") != "") {
			label.hOffset = node.getAttribute("hOffset");
		}
		if(node.getAttribute("opacity") != "") {
			label.opacity = node.getAttribute("opacity");
		}
		if(node.getAttribute("scrolling") != "") {
			label.scrolling = node.getAttribute("scrolling");
		}
		if(node.getAttribute("size") != "") {
			label.size = node.getAttribute("size");
		}
		if(node.getAttribute("tooltip") != "") {
			label.tooltip = node.getAttribute("tooltip");
		}
		if(node.getAttribute("visible") != "") {
			if(node.getAttribute("visible")=="true") {
				label.visible = true;
			}
			else {
				label.visible = false;
			}
		}
		if(node.getAttribute("vOffset") != "") {
			label.vOffset = node.getAttribute("vOffset");
		}
		if(node.getAttribute("width") != "") {
			label.width = node.getAttribute("width");
		}
		if(node.getAttribute("kon-text-truncation") != "") {
			label.style.KonTextTruncation = node.getAttribute("kon-text-truncation");
		}
		if(node.getAttribute("zOrder") != "") {
			label.zOrder = node.getAttribute("zOrder");
		}
}

/**
 * Sets textBox (TextArea) attributes from given node.
 * @private
 * @param {TextArea} textBox TextArea object which will be modified.
 * @param {DOMNode} node The style node used to set properties.
 */
Yahoo.Controls.Theme.prototype._theme_setTextBoxAttributes = function(textBox, node) {

		if(node.getAttribute("alignment") != "") {
			textBox.alignment = node.getAttribute("alignment");
		}
		if(node.getAttribute("background-color") != "") {
			textBox.style.backgroundColor = node.getAttribute("background-color");
		}
		if(node.getAttribute("bgColor") != "") {
			textBox.bgColor = node.getAttribute("bgColor");
		}
		if(node.getAttribute("bgOpacity") != "") {
			textBox.bgOpacity = node.getAttribute("bgOpacity");
		}
		if(node.getAttribute("color") != "") {
			textBox.color = node.getAttribute("color");
		}
		if(node.getAttribute("columns") != "") {
			textBox.columns = node.getAttribute("columns");
		}
		if(node.getAttribute("data") != "") {
			textBox.data = node.getAttribute("data");
		}
		if(node.getAttribute("editable") != "") {
			if(node.getAttribute("editable")=="true") {
				textBox.editable = true;
			}
			else {
				textBox.editable = false;
			}
		}
		if(node.getAttribute("font") != "") {
			textBox.font = node.getAttribute("font");
		}
		if(node.getAttribute("font-family") != "") {
			textBox.style.fontFamily = node.getAttribute("font-family");
		}
		if(node.getAttribute("font-size") != "") {
			textBox.style.fontSize = node.getAttribute("font-size");
		}
		if(node.getAttribute("font-weight") != "") {
			textBox.style.fontWeight = node.getAttribute("font-weight");
		}
		if(node.getAttribute("hAlign") != "") {
			textBox.hAlign = node.getAttribute("hAlign");
		}
		if(node.getAttribute("height") != "") {
			textBox.height = node.getAttribute("height");
		}
		if(node.getAttribute("hOffset") != "") {
			textBox.hOffset = node.getAttribute("hOffset");
		}
		if(node.getAttribute("opacity") != "") {
			textBox.opacity = node.getAttribute("opacity");
		}
		if(node.getAttribute("scrollbar") != "") {
			if(node.getAttribute("scrollbar")=="true") {
				textBox.scrollbar = true;
			}
			else {
				textBox.scrollbar = false;
			}
		}
		if(node.getAttribute("secure") != "") {
			if(node.getAttribute("secure")=="true") {
				textBox.secure = true;
			}
			else {
				textBox.secure = false;
			}
		}
		if(node.getAttribute("size") != "") {
			textBox.size = node.getAttribute("size");
		}
		if(node.getAttribute("spellcheck") != "") {
			if(node.getAttribute("spellcheck")=="true") {
				textBox.spellcheck = true;
			}
			else {
				textBox.spellcheck = false;
			}
		}
		if(node.getAttribute("thumbColor") != "") {
			textBox.thumbColor = node.getAttribute("thumbColor");
		}
		if(node.getAttribute("tooltip") != "") {
			textBox.tooltip = node.getAttribute("tooltip");
		}
		if(node.getAttribute("visible") != "") {
			if(node.getAttribute("visible")=="true") {
				textBox.visible = true;
			}
			else {
				textBox.visible = false;
			}
		}
		if(node.getAttribute("vAlign") != "") {
			textBox.vAlign = node.getAttribute("vAlign");
		}
		if(node.getAttribute("vOffset") != "") {
			textBox.vOffset = node.getAttribute("vOffset");
		}
		if(node.getAttribute("width") != "") {
			textBox.width = node.getAttribute("width");
		}
		if(node.getAttribute("zOrder") != "") {
			textBox.zOrder = node.getAttribute("zOrder");
		}
}

/**
 * Sets image attributes from given node.
 * @private
 * @param {Image} image Image object which will be modified.
 * @param {DOMNode} node The style node used to set properties.
 */
Yahoo.Controls.Theme.prototype._theme_setImageAttributes = function(image, node) {

		if(node.getAttribute("colorize") != "") {
			image.colorize = node.getAttribute("colorize");
		}
		if(node.getAttribute("fillMode") != "") {
			image.fillMode = node.getAttribute("fillMode");
		}
		if(node.getAttribute("height") != "") {
			image.height = node.getAttribute("height");
		}
		if(node.getAttribute("hOffset") != "") {
			image.hOffset = node.getAttribute("hOffset");
		}
		if(node.getAttribute("hRegistrationPoint") != "") {
			image.hRegistrationPoint = node.getAttribute("hRegistrationPoint");
		}
		if(node.getAttribute("hslAdjustment") != "") {
			image.hslAdjustment = node.getAttribute("hslAdjustment");
		}
		if(node.getAttribute("hslTinting") != "") {
			image.hslTinting = node.getAttribute("hslTinting");
		}
		if(node.getAttribute("opacity") != "") {
			image.opacity = node.getAttribute("opacity");
		}
		if(node.getAttribute("rotation") != "") {
			image.rotation = node.getAttribute("rotation");
		}
		if(node.getAttribute("tileOrigin") != "") {
			image.tileOrigin = node.getAttribute("tileOrigin");
		}
		if(node.getAttribute("tooltip") != "") {
			image.tooltip = node.getAttribute("tooltip");
		}
		if(node.getAttribute("tracking") != "") {
			image.tracking = node.getAttribute("tracking");
		}
		if(node.getAttribute("visible") != "") {
			if(node.getAttribute("visible")=="true") {
				image.visible = true;
			}
			else {
				image.visible = false;
			}
		}
		if(node.getAttribute("vOffset") != "") {
			image.vOffset = node.getAttribute("vOffset");
		}
		if(node.getAttribute("vRegistrationPoint") != "") {
			image.vRegistrationPoint = node.getAttribute("vRegistrationPoint");
		}
		if(node.getAttribute("width") != "") {
			image.width = node.getAttribute("width");
		}
		if(node.getAttribute("zOrder") != "") {
			image.zOrder = node.getAttribute("zOrder");
		}
}

/**
 * Adds an item to the cache.
 * @private
 * @param {Object} item Object to add to the cache.
 * @param {String} itemName The item name of this object. It is used as the key in the cache.
 * @param {String} type The type name of the object.
 */
Yahoo.Controls.Theme.prototype._theme_addToCache = function(item, itemName, type) {

	var prop;
	var result = new Object();
	result.style = new Object();
	
	//log("Theme._theme_addToCache");
	result.___cacheType = type;
	
	for(prop in item) {
		if((item[prop]!="" && item[prop]!=null)) {
			switch(prop.toLowerCase()) {
				case "colour":
				case "columns":
				case "id":
				case "lines":
				case "name":
				case "window":
				case "srcheight":
				case "srcwidth":
				case "superview":
					break;
				case "style":
                    if(item.style!=null) {
					        for(style in item.style) {
					            if((item.style[style]!="" && item.style[style]!=null)) {
                                    result.style[style] = item.style[style];
					            }
                            }
                    }
                    break;
				default:
					result[prop] = item[prop];
					break;
			}  // switch
		}  // if value != null
	}  // for prop

	this._cache[itemName] = result;
}

/**
 * Gets an item from the cache.
 * @private
 * @param {String} itemName The item name of the object to retrieve.
 * @type Object
 */
Yahoo.Controls.Theme.prototype._theme_getFromCache = function(itemName) {

	var prop;
	var propItem;
	var result;
	
	//log("Theme._theme_getFromCache");

	propItem = this._cache[itemName];
	
	if(propItem!=null) {
		//log("** Got item from cache");
		switch(propItem.___cacheType) {
			case "image":
				result = new Image();
				break;
			case "label":
				result = new Text();
				break;
			case "textBox":
				result = new TextArea();
				break;
		}

		//log("getting from cache");
		if(result!=null) {
			// Copy properties from cached item
			for(prop in propItem) {
				switch(prop.toLowerCase()) {
					case "___cachetype":
						break;
					case "style":
				        for(style in propItem.style) {
                            result.style[style] = propItem.style[style];
                        }
					    break;
					default:
						try {
							//log(prop + "=" + propItem[prop]);
							result[prop] = propItem[prop];
						}
						catch(e) {
							log(e);
						}
						break;
				}  // switch
			}
		}  // if result!=null

	}  // if propItem!=null

	return result;
}

/*---------------------------------------------------------------------*/
// Public code
/*---------------------------------------------------------------------*/
/**
 * Initializes component.
 * @param {string} themePath The path to the theme folder.
 */
Yahoo.Controls.Theme.prototype.initialize = function(themePath) {

	// Includes
	lib.include("Yahoo.ArgumentNullException");
	lib.include("Yahoo.EventArgs");

	// Events
	this._onThemeChangedEventHandlers = new Array();

	if(themePath!="") {
		// Private variables
		this._themePath = themePath;
		this._themes = null;
		this._themeName = null;
		this._themeDoc = null;

		// Load available themes
		this._theme_getThemes();
		
	}  // themePath = ""
	else {
		throw new Yahoo.ArgumentNullException("themePath");
	}  // themePath = ""
}

/**
 * Adds an event handler. Supported events are: ThemeChanged.
 * @param {Function} eventHandler The function that is to be called when the event is raised.
 * @param {String} eventName The name of the event that is being listened to.
 */
Yahoo.Controls.Theme.prototype.addEventHandler = function(eventHandler, eventName) {

	// Validate input
	if(eventHandler==null) { throw new Yahoo.ArgumentNullException("eventHandler"); return; }
	if(eventName==null) { throw new Yahoo.ArgumentNullException("eventName"); return; }

	switch(eventName) {
		case "ThemeChanged":
			this._onThemeChangedEventHandlers.push(eventHandler);
			break;
		default:
			throw new Error("Invalid eventName.");
			break;
	}
}

/**
 * Loads the given theme.
 * @param {String} themeName The name of the theme to load.
 */
Yahoo.Controls.Theme.prototype.loadTheme = function(themeName) {

	var file;

	this._themeName = themeName;

	try {
	    // Clear cache
	    for(item in this._cache) {
	    	this._cache[item] = null;
    	}
    	this._cache = null;
	
		// Load the file
		file = filesystem.readFile(this._themePath + "/" + this._themeName + "/" + this._themeName + ".xml");
		this._themeDoc = XMLDOM.parse(file);
		this._cache = new Object();
	}
	catch(e) {
		this._themeName = null;
		this._themeDoc = null;
	}
	
	// Raise event
	Yahoo.raiseEvent(this, this._onThemeChangedEventHandlers, new Yahoo.EventArgs());
}

/**
 * Returns the given GUI element based on the currently loaded theme.
 * @param {String} itemName The item name to retrieve.
 * @param {Window} window The window object to add the returned item to or null.
 * @type Object
 */
Yahoo.Controls.Theme.prototype.getItem = function(itemName, window) {

	var nodes;
	var styleName;
	var styleNode;
	var itemNode;
	var result;

	if(this._themeDoc!=null) {
	
		result = this._theme_getFromCache(itemName)
		
		if(result==null) {
	
			// Find the element that describe the GUI item requested
			nodes = this._themeDoc.evaluate("/theme/items/" + itemName);
	
			if(nodes.length==1) {
				itemNode = nodes.item(0);
				
				// Get the style definition for the item
				styleName = itemNode.getAttribute("style");
				nodes = this._themeDoc.evaluate("/theme/styles/*[@id='" + styleName + "']");
	
				if(nodes.length==1) {
					styleNode = nodes.item(0);
					if(styleNode!=null) {
						// Get the style and create a Widget Engine object populated with correct properties
						switch(styleNode.nodeName) {
							case "image":
								result = this._theme_getImageObject(itemNode, styleNode);
								this._theme_addToCache(result, itemName, "image");
								break;
							case "label":
								result = this._theme_getLabelObject(itemNode, styleNode);
								this._theme_addToCache(result, itemName, "label");
								break;
							case "textBox":
								result = this._theme_getTextBoxObject(itemNode, styleNode);
								this._theme_addToCache(result, itemName, "textBox");
								break;
						} // switch
					}
					else {
						throw new Error("Theme error: Style '" + styleName + "' not found for element '" + itemName + "'.");
					}  //node!=null
				}
				else {
					throw new Error("Theme error: Incorrect number of styles of the type '" + styleName + "' (" + nodes.length + ").");
				}  // nodes.length==1 (styles)
			}
			else {
				throw new Error("Theme error: Incorrect number of elements of the type '" + itemName + "' (" + nodes.length + ").");
			}  // nodes.length==1 (items)

		}  // result == null (from cache)
	}
	else {
		throw new Error("Theme not loaded.");
	}

	if(window!=null) {
		result.window = window;
	}

	return result;
}

/**
 * Returns the parameter as an object based on the currently loaded theme.
 * @param {String} itemName The parameter item name to retrieve.
 */
Yahoo.Controls.Theme.prototype.getParameter = function(itemName) {

	var nodes;
	var itemNode;
	var itemAttrib;
	var attribCount;
	var result;

	if(this._themeDoc!=null) {
		// Find the element that describe the GUI item requested
		nodes = this._themeDoc.evaluate("/theme/parameters/" + itemName);

		if(nodes.length==1) {
			itemNode = nodes.item(0);

			// Create new object
			result = new Object();
			result["itemName"] = itemNode.nodeName;

			// Loop all attributes in this element
			for(attribCount=0; attribCount<itemNode.attributes.length ; attribCount++) {
				itemAttrib = itemNode.attributes.item(attribCount);

				if(itemAttrib.value!="itemName") {
					result[itemAttrib.name] = itemAttrib.value;
				}
				
			}  // for(attribCount)

		}
		else {
			throw new Error("Theme error: Incorrect number of elements of the type '" + itemName + "' (" + nodes.length + ").");
		}  // nodes.length==1 (items)

	}
	else {
		throw new Error("Theme not loaded.");
	}

	return result;
}

/*---------------------------------------------------------------------*/
// Public properties
/*---------------------------------------------------------------------*/
/**
 * Gets the path where this control looks for themes and theme files.
 * @type String
 */
Yahoo.Controls.Theme.prototype.themePath getter = function() {
	return this._themePath;
}
Yahoo.Controls.Theme.prototype.themePath setter = function() {
	throw new Error("themePath is read-only.");
}

/**
 * Gets an array containing the available themes.
 * @type Array
 */
Yahoo.Controls.Theme.prototype.themes getter = function() {
	return this._themes;
}
Yahoo.Controls.Theme.prototype.themes setter = function() {
	throw new Error("themes is read-only.");
}

/**
 * Gets the name of the current theme.
 * @type String
 */
Yahoo.Controls.Theme.prototype.themeName getter = function() {
	return this._themeName;
}
Yahoo.Controls.Theme.prototype.themeName setter = function() {
	throw new Error("themeName is read-only.");
}
