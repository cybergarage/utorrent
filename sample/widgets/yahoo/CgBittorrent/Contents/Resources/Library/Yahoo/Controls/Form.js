/*---------------------------------------------------------------------*/
/// <copyright from='2005' to='2006' company='Yahoo! Inc.'>
/// (C) Copyright 2005-2006 Yahoo! Inc. All Rights Reserved.
/// </copyright>

/**
 * Form control.
 */
/*---------------------------------------------------------------------*/

/*---------------------------------------------------------------------*/
// Constructor
/*---------------------------------------------------------------------*/
/**
 * Default constructor.
 * @constructor
 * @param {Yahoo.Controls.Theme} theme The theme this control should use or null to create an instance of the default theme.
 */
Yahoo.Controls.Form = function(theme) {

	//log("Form.ctor()");
	if(arguments.length>0) {
		this.initialize(theme);
	}
}

/**
 * Define inheritance chain.
 */
Yahoo.Controls.Form.prototype = new Yahoo.Controls.Control();
Yahoo.Controls.Form.prototype.constructor = Yahoo.Controls.Form;
Yahoo.Controls.Form.prototype.baseclassForm = Yahoo.Controls.Control.prototype;

/*---------------------------------------------------------------------*/
// Public enums
/*---------------------------------------------------------------------*/
/**
 * Available return codes for a form.
 */
Yahoo.Controls.DialogResult = {
    None: 0,
    OK: 1,
    Cancel: 2,
    Abort: 3,
    Retry: 4,
    Ignore: 5,
    Yes: 6,
    No: 7
}

/**
 * Available border styles for forms.
 */
Yahoo.Controls.FormBorderStyle = {
    None: 0,
    FixedSingle: 1,
    Fixed: 2,
    Sizable: 4
}

/*-----------------------------------------------------------*/
// Control code
/*-----------------------------------------------------------*/
/**
 * Raises the onBackColorChanged event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.Form.prototype._onBackColorChanged = function(sender, e) {

	//log("Form._onBackColorChanged");

	// Override base class so we don't change the whole frame's background color
	//this.baseclassForm._onBackColorChanged.call(this, sender, e);
	Yahoo.raiseEvent(sender, sender._onBackColorChangedEventHandlers, e);
	
	this._clientFrame.style.backgroundColor = this._backColor;
}

/**
 * Raises the onBorderColorChanged event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.Form.prototype._onBorderColorChanged = function(sender, e) {

	//log("Form._onBorderColorChanged");

	this._imgBorderBottom.colorize = this._borderColor;
	this._imgBorderLeft.colorize = this._borderColor;
	this._imgBorderRight.colorize = this._borderColor;
	this._imgBorderTop.colorize = this._borderColor;

	Yahoo.raiseEvent(sender, sender._onBorderColorChangedEventHandlers, e);
}

/**
 * Raises the onClosing event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.Form.prototype._onClosing = function(sender, e) {

	//log("Form._onClosing");

	Yahoo.raiseEvent(sender, sender._onClosingEventHandlers, e);
}

/**
 * Raises the onClosed event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.Form.prototype._onClosed = function(sender, e) {

	//log("Form._onClosed");

	Yahoo.raiseEvent(sender, sender._onClosedEventHandlers, e);
}

/**
 * Raises the onResize event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.Form.prototype._onResize = function(sender, e) {

	//log("Form._onResize");

	var count;
	
	// sender = top level control that inherits from us
	// this = Form

	// Set client frame size
	if(this._disposing==false) {
	    this._form_setClientFrameSize();
	
		// Resize borders and background
        this._form_resizePaintBackground();
	}

	// Call base class
	this.baseclassForm._onResize.call(this, sender, e);
}

/**
 * Raises the onFormBorderStyleChanged event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.Form.prototype._onFormBorderStyleChanged = function(sender, e) {

	//log("Form._onFormBorderStyleChanged");
	
	this._form_loadTheme();

	// Default to movable
	this._imgBorderTop.onMouseDown = this._border_onMouseDown;
	this._imgBorderTop.onMouseDrag = this._borderTop_onMouseDrag;

	switch(this._formBorderStyle) {
		case Yahoo.Controls.FormBorderStyle.None:
		case Yahoo.Controls.FormBorderStyle.FixedSingle:
			this._imgBorderTop.onMouseDown = "";
			this._imgBorderTop.onMouseDrag = "";
			// Falls thru to the following
		case Yahoo.Controls.FormBorderStyle.Fixed:
			this._imgBorderBottom.onMouseDown = "";
			this._imgBorderBottom.onMouseDrag = "";
			this._imgBorderLeft.onMouseDown = "";
			this._imgBorderLeft.onMouseDrag = "";
			this._imgBorderRight.onMouseDown = "";
			this._imgBorderRight.onMouseDrag = "";
			this._imgCornerBottomLeft.onMouseDown = "";
			this._imgCornerBottomLeft.onMouseDrag = "";
			this._imgCornerBottomRight.onMouseDown = "";
			this._imgCornerBottomRight.onMouseDrag = "";
			this._imgCornerTopLeft.onMouseDown = "";
			this._imgCornerTopLeft.onMouseDrag = "";
			this._imgCornerTopRight.onMouseDown = "";
			this._imgCornerTopRight.onMouseDrag = "";
			break;
		case Yahoo.Controls.FormBorderStyle.Sizable:
			this._imgBorderBottom.onMouseDown = this._border_onMouseDown;
			this._imgBorderBottom.onMouseDrag = this._borderBottom_onMouseDrag;
			this._imgBorderLeft.onMouseDown = this._border_onMouseDown;
			this._imgBorderLeft.onMouseDrag = this._borderLeft_onMouseDrag;
			this._imgBorderRight.onMouseDown = this._border_onMouseDown;
			this._imgBorderRight.onMouseDrag = this._borderRight_onMouseDrag;
			this._imgBorderTop.onMouseDown = this._border_onMouseDown;
			this._imgBorderTop.onMouseDrag = this._borderTop_onMouseDrag;
			this._imgCornerBottomLeft.onMouseDown = this._border_onMouseDown;
			this._imgCornerBottomLeft.onMouseDrag = this._cornerBottomLeft_onMouseDrag;
			this._imgCornerBottomRight.onMouseDown = this._border_onMouseDown;
			this._imgCornerBottomRight.onMouseDrag = this._cornerBottomRight_onMouseDrag;
			this._imgCornerTopLeft.onMouseDown = this._border_onMouseDown;
			this._imgCornerTopLeft.onMouseDrag = this._cornerTopLeft_onMouseDrag;
			this._imgCornerTopRight.onMouseDown = this._border_onMouseDown;
			this._imgCornerTopRight.onMouseDrag = this._cornerTopRight_onMouseDrag;
			break;
	} // switch
	
	Yahoo.raiseEvent(sender, sender._onFormBorderStyleChangedEventHandlers, e);
	Yahoo.raiseEvent(sender, sender._onResizeEventHandlers, new Yahoo.EventArgs());
}

/**
 * Raises the onOpacityChanged event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.Form.prototype._onOpacityChanged = function(sender, e) {

	//log("Form._onOpacityChanged");

	// Call base class
	this.baseclassForm._onOpacityChanged.call(this, sender, e);

	this._window.opacity = this.opacity;
}

/**
 * Raises the onTextChanged event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.Form.prototype._onTextChanged = function(sender, e) {

	//log("Form._onTextChanged");

	// Call base class
	this.baseclassForm._onTextChanged.call(this, sender, e);

	this._lblCaption.text = this.text;
}

/**
 * Handles onMouseDown event for border elements that can move or resize the window.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.Form.prototype._border_onMouseDown = function() {

	//log("Form._border_onMouseDown");

	this.tag._sizeStartX = system.event.x;
	this.tag._sizeStartY = system.event.y;
}

/**
 * Handles onMouseDrag event for a border element.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.Form.prototype._borderBottom_onMouseDrag = function() {

	//log("Form._borderBottom_onMouseDrag");

	this.tag._form_setSize(this.tag.width, (this.tag._sizeStartY + system.event.vOffset));
}

/**
 * Handles onMouseDrag event for a border element.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.Form.prototype._borderLeft_onMouseDrag = function() {

	//log("Form._borderLeft_onMouseDrag");

	this.tag._form_setSize((this.tag.width - system.event.hOffset), this.tag.height);
	this.tag.left = this.tag.left + system.event.hOffset;
}

/**
 * Handles onMouseDrag event for a border element.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.Form.prototype._borderRight_onMouseDrag = function() {

	//log("Form._borderRight_onMouseDrag");

	this.tag._form_setSize((this.tag._sizeStartX + system.event.hOffset), this.tag.height);
}

/**
 * Handles onMouseDrag event for a border element.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.Form.prototype._borderTop_onMouseDrag = function() {

	//log("Form._borderTop_onMouseDrag");

	// Move window
	this.tag.left = this.tag.left + system.event.hOffset - this.tag._sizeStartX;
	this.tag.top = this.tag.top + system.event.vOffset - this.tag._sizeStartY;
}

/**
 * Handles onMouseDrag event for a border element.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.Form.prototype._cornerBottomLeft_onMouseDrag = function() {

	//log("Form._cornerBottomLeft_onMouseDrag");

	this.tag._form_setSize((this.tag.width - system.event.hOffset), (this.tag._sizeStartY + system.event.vOffset));
	this.tag.left = this.tag.left + system.event.hOffset;
}

/**
 * Handles onMouseDrag event for a border element.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.Form.prototype._cornerBottomRight_onMouseDrag = function() {

	//log("Form._cornerBottomRight_onMouseDrag");

	this.tag._form_setSize((this.tag._sizeStartX + system.event.hOffset), (this.tag._sizeStartY + system.event.vOffset));
}

/**
 * Handles onMouseDrag event for a border element.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.Form.prototype._cornerTopLeft_onMouseDrag = function() {

	//log("Form._cornerTopLeft_onMouseDrag");

	this.tag._form_setSize((this.tag.width - system.event.hOffset), (this.tag.height - system.event.vOffset));
	this.tag.top = this.tag.top + system.event.vOffset;
	this.tag.left = this.tag.left + system.event.hOffset;
}

/**
 * Handles onMouseDrag event for a border element.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.Form.prototype._cornerTopRight_onMouseDrag = function() {

	//log("Form._cornerTopRight_onMouseDrag");

	this.tag._form_setSize((this.tag._sizeStartX + system.event.hOffset), (this.tag.height - system.event.vOffset));
	this.tag.top = this.tag.top + system.event.vOffset;
}

/**
 * Handles onMouseEnter event for label.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.Form.prototype._form_lblCaption_onEnter = function(sender, e) {

	//log("Form._form_lblCaption_onEnter");

	sender.parent._onEnter.call(sender.parent, sender.parent, new Yahoo.EventArgs());
}

/**
 * Handles onMouseExit event for label.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.Form.prototype._form_lblCaption_onLeave = function(sender, e) {

	//log("Form._form_lblCaption_onLeave");
	
	// Don't forward this if we are still within the parent control
	if(sender.parent.displayRectangle.contains(system.event.x + sender.left + sender.parent.left, system.event.y + sender.top + sender.parent.top) == false) {
		sender.parent._onLeave.call(sender.parent, sender.parent, new Yahoo.EventArgs());
	}
}

/**
 * Handles onMouseDown event for label.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.Form.prototype._form_lblCaption_onMouseDown = function(sender, e) {

	//log("Form._form_lblCaption_onMouseDown");

	sender.parent._sizeStartX = system.event.x;
	sender.parent._sizeStartY = system.event.y;
}

/**
 * Handles onMouseDrag event for label.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.Form.prototype._form_lblCaption_onMouseDrag = function(sender, e) {

	//log("Form._form_lblCaption_onMouseDrag");
	
	// Move window
	sender.parent.left = sender.parent.left + system.event.hOffset - sender.parent._sizeStartX;
	sender.parent.top = sender.parent.top + system.event.vOffset - sender.parent._sizeStartY;
}

/**
 * Handles onClick event for button.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.Form.prototype._form_btnClose_onClick = function(sender, e) {

	//log("Form._form_btnClose_onClick");
	
	sender.parent.close();
}

/**
 * Raises the onThemeChanged event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.Form.prototype._onThemeChanged = function(sender, e) {

	//log("Form._onThemeChanged");

	// Call base class
	this.baseclassForm._onThemeChanged.call(this, sender, e);

    // Load style and theme
	this._onFormBorderStyleChanged(this, new Yahoo.EventArgs());

	// Loop all contained controls and set theme
	for(count=0; count<this._controls.length; count++) {
		if(this._controls[count].theme!=undefined) {
			this._controls[count].theme = this._theme;
		}
	}
}

/*-----------------------------------------------------------*/
// Private code
/*-----------------------------------------------------------*/
/**
 * Disposes native Widget Engine objects.
 * @private
 */
Yahoo.Controls.Form.prototype._form_disposeNativeObjects = function() {

	//log("Form._form_disposeNativeObjects");

	if(this._imgBackground!=null) { this._imgBackground.removeFromSuperview(); this._imgBackground = null; }
	if(this._imgCornerTopLeft!=null) { this._imgCornerTopLeft.removeFromSuperview(); this._imgCornerTopLeft = null; }
	if(this._imgCornerTopRight!=null) { this._imgCornerTopRight.removeFromSuperview(); this._imgCornerTopRight = null; }
	if(this._imgCornerBottomLeft!=null) { this._imgCornerBottomLeft.removeFromSuperview(); this._imgCornerBottomLeft = null; }
	if(this._imgCornerBottomRight!=null) { this._imgCornerBottomRight.removeFromSuperview(); this._imgCornerBottomRight = null; }
	if(this._imgBorderTop!=null) { this._imgBorderTop.removeFromSuperview(); this._imgBorderTop = null; }
	if(this._imgBorderBottom!=null) { this._imgBorderBottom.removeFromSuperview(); this._imgBorderBottom = null; }
	if(this._imgBorderLeft!=null) { this._imgBorderLeft.removeFromSuperview(); this._imgBorderLeft = null; }
	if(this._imgBorderRight!=null) { this._imgBorderRight.removeFromSuperview(); this._imgBorderRight = null; }

	// These aren't native objects, but we still dispose them here
	if(this._lblCaption!=null) { this._lblCaption.dispose(); this._lblCaption = null; }
	if(this._btnClose!=null) { this._btnClose.dispose(); this._btnClose = null; }
}

/**
 * Loads control elements based on current theme.
 * @private
 */
Yahoo.Controls.Form.prototype._form_loadTheme = function() {

	var prefix;

	// Remove any current objects
	this._form_disposeNativeObjects();

	switch(this._formBorderStyle) {
		case Yahoo.Controls.FormBorderStyle.None:
			// NOTE: We use a single border, but set the sizes/visibility to zero
			prefix = "Single";
			break;
		case Yahoo.Controls.FormBorderStyle.FixedSingle:
			prefix = "Single";
			break;
		case Yahoo.Controls.FormBorderStyle.Fixed:
		case Yahoo.Controls.FormBorderStyle.Sizable:
			prefix = "";
			break;
		default:
		    throw new Yahoo.InvalidEnumArgumentException("FormBorderStyle", "", "Form.FormBorderStyle");
	} // switch

	// Load objects using current theme
	this._imgBackground = this._theme.getItem("formBackground");
	this._imgBackground.tag = this;
	this._imgBackground.zOrder = 0;
	this._frame.addSubview(this._imgBackground);
	this._imgCornerTopLeft = this._theme.getItem("form" + prefix + "CornerTopLeft");
	this._imgCornerTopLeft.tag = this;
	this._frame.addSubview(this._imgCornerTopLeft);
	this._imgCornerTopRight = this._theme.getItem("form" + prefix + "CornerTopRight");
	this._imgCornerTopRight.tag = this;
	this._frame.addSubview(this._imgCornerTopRight);
	this._imgCornerBottomLeft = this._theme.getItem("form" + prefix + "CornerBottomLeft");
	this._imgCornerBottomLeft.tag = this;
	this._frame.addSubview(this._imgCornerBottomLeft);
	this._imgCornerBottomRight = this._theme.getItem("form" + prefix + "CornerBottomRight");
	this._imgCornerBottomRight.tag = this;
	this._frame.addSubview(this._imgCornerBottomRight);
	this._imgBorderTop = this._theme.getItem("form" + prefix + "BorderTop");
	this._imgBorderTop.tag = this;
	this._frame.addSubview(this._imgBorderTop);
	this._imgBorderBottom = this._theme.getItem("form" + prefix + "BorderBottom");
	this._imgBorderBottom.tag = this;
	this._frame.addSubview(this._imgBorderBottom);
	this._imgBorderLeft = this._theme.getItem("form" + prefix + "BorderLeft");
	this._imgBorderLeft.tag = this;
	this._frame.addSubview(this._imgBorderLeft);
	this._imgBorderRight = this._theme.getItem("form" + prefix + "BorderRight");
	this._imgBorderRight.tag = this;
	this._frame.addSubview(this._imgBorderRight);

	// Titlebar related
	this._titlebarMargins = this._theme.getParameter("form" + prefix + "TitlebarMargins");

	// Create caption and add it to the non-client frame
	this._lblCaption = new Yahoo.Controls.Label(this._theme);
	this._lblCaption.fromTextObject(this._theme.getItem("form" + prefix + "Caption"));
	this._lblCaption.addEventHandler(this._form_lblCaption_onEnter, "Enter");
	this._lblCaption.addEventHandler(this._form_lblCaption_onLeave, "Leave");
	this._lblCaption.addEventHandler(this._form_lblCaption_onMouseDown, "MouseDown");
	this._lblCaption.addEventHandler(this._form_lblCaption_onMouseDrag, "MouseDrag");
	this._lblCaption.parent = this;
	this._lblCaption.text = this.text;
	this._frame.addSubview(this._lblCaption.frame);
	this._lblCaption.zOrder = 9000;
	this._captionMargins = this._theme.getParameter("form" + prefix + "CaptionMargins");

	// Buttons
	this._buttonMargins = this._theme.getParameter("form" + prefix + "ButtonMargins");

	this._btnClose = new Yahoo.Controls.ImageButton(this._theme, "form" + prefix + "ButtonCloseNormal", "form" + prefix + "ButtonCloseOver", "form" + prefix + "ButtonCloseDown", "form" + prefix + "ButtonCloseDisabled");
	this._btnClose.addEventHandler(this._form_btnClose_onClick, "Click");
	this._btnClose.parent = this;
	this._btnClose.width = -1;
	this._btnClose.height = -1;
	this._btnClose.zOrder = 9001;
	this._frame.addSubview(this._btnClose.frame);
	this._buttonCloseLocation = this._theme.getParameter("formButtonCloseLocation");

	// Check if borderstyle set to "None"
	if(this._formBorderStyle==Yahoo.Controls.FormBorderStyle.None) {
		this._imgCornerTopLeft.width = 0; this._imgCornerTopLeft.height = 0; this._imgCornerTopLeft.visible = false;
		this._imgCornerTopRight.width = 0; this._imgCornerTopRight.height = 0; this._imgCornerTopRight.visible = false;
		this._imgCornerBottomLeft.width = 0; this._imgCornerBottomLeft.height = 0; this._imgCornerBottomLeft.visible = false;
		this._imgCornerBottomRight.width = 0; this._imgCornerBottomRight.height = 0; this._imgCornerBottomRight.visible = false;
		this._imgBorderTop.width = 0; this._imgBorderTop.height = 0; this._imgBorderTop.visible = false;
		this._imgBorderBottom.width = 0; this._imgBorderBottom.height = 0; this._imgBorderBottom.visible = false;
		this._imgBorderLeft.width = 0; this._imgBorderLeft.height = 0; this._imgBorderLeft.visible = false;
		this._imgBorderRight.width = 0; this._imgBorderRight.height = 0; this._imgBorderRight.visible = false;
		this._lblCaption.visible = false;
	}
	else if(this._formBorderStyle==Yahoo.Controls.FormBorderStyle.FixedSingle) {
		this._lblCaption.visible = false;
		this._onBorderColorChanged(this, new Yahoo.EventArgs());
	}
	else {
		this._lblCaption.visible = true;
	}

    // Set client frame location
	this._clientFrame.hOffset = this._imgBorderLeft.width;
	this._clientFrame.vOffset = this._imgBorderTop.height;

    this._form_setClientFrameSize();
    this._form_resizePaintBackground();
	this._form_paintBackground();
}

/**
 * Resizes client frame.
 * @private
 */
Yahoo.Controls.Form.prototype._form_setClientFrameSize = function() {

	this._clientFrame.width = this._frame.width - (this._imgBorderLeft.width + this._imgBorderRight.width);
	this._clientFrame.height = this._frame.height - (this._imgBorderTop.height + this._imgBorderBottom.height);
}

/**
 * Resizes window border elements.
 * @private
 */
Yahoo.Controls.Form.prototype._form_resizePaintBackground = function() {

	var showButtonClose;
	var itemCountLeft;
	var itemCountRight;
	var itemPaddingLeft;
	var itemPaddingRight;

	var width = this.width;
	var height = this.height;

	this._imgBackground.hOffset = this._imgBorderLeft.width;
	this._imgBackground.vOffset = this._imgBorderTop.height;
	this._imgBackground.width = width - this._imgBorderLeft.width - this._imgBorderRight.width;
	this._imgBackground.height = height - (this._imgBorderTop.height + this._imgBorderBottom.height);

	this._imgCornerTopRight.hOffset = width - this._imgCornerTopRight.width;
	this._imgCornerBottomLeft.vOffset = height - this._imgCornerBottomLeft.height;
	this._imgCornerBottomRight.hOffset = width - this._imgCornerBottomRight.width;
	this._imgCornerBottomRight.vOffset = height - this._imgCornerBottomRight.height;
	// Size from image

	this._imgBorderTop.hOffset = this._imgCornerTopLeft.hOffset + this._imgCornerTopLeft.width;
	this._imgBorderTop.width = width - (this._imgCornerTopLeft.width + this._imgCornerTopRight.width);

	this._imgBorderLeft.height = height - (this._imgCornerTopLeft.height + this._imgCornerBottomLeft.height);

	this._imgBorderRight.hOffset = width - this._imgBorderRight.width;
	this._imgBorderRight.height = height - (this._imgCornerTopRight.height + this._imgCornerBottomRight.height);

	// Bottom border width is width - (corner widths)
	this._imgBorderBottom.hOffset = this._imgCornerBottomLeft.hOffset + this._imgCornerBottomLeft.width;
	this._imgBorderBottom.vOffset = height - this._imgBorderBottom.height;
	this._imgBorderBottom.width = width - (this._imgCornerBottomLeft.width + this._imgCornerBottomRight.width);
	// Height from image

	// Icon and buttons
	itemCountLeft = 0;
	itemCountRight = 0;
	itemPaddingLeft = parseInt(this._titlebarMargins.left);
	itemPaddingRight = parseInt(this._titlebarMargins.right);

	showButtonClose = this._closeBox==true && this._formBorderStyle!=Yahoo.Controls.FormBorderStyle.None && this._formBorderStyle!=Yahoo.Controls.FormBorderStyle.FixedSingle;
	this._btnClose.visible = showButtonClose;

    // TODO: Some of these values should be stored and not calculated on every resize event
	if(showButtonClose==true) {
		this._btnClose.top = parseInt(this._titlebarMargins.top) + parseInt(this._buttonMargins.top);
		if(this._buttonCloseLocation.alignment=="left" || (this._buttonCloseLocation.alignment=="auto" && system.platform=="macintosh")) {
			if(itemCountLeft>0) { itemPaddingLeft += parseInt(this._buttonMargins.left); }
			this._btnClose.left = itemPaddingLeft;
			itemPaddingLeft += this._btnClose.width + parseInt(this._buttonMargins.right);
			itemCountLeft +=1;
		}
		else {
			if(itemCountRight>0) { itemPaddingRight += parseInt(this._buttonMargins.right); }
			this._btnClose.left = width - this._btnClose.width - itemPaddingRight;
			itemPaddingRight += this._btnClose.width + parseInt(this._buttonMargins.left);
			itemCountRight +=1;
		}  // alignment
		
	}  //showButtonClose

	// Caption
	this._lblCaption.left = itemPaddingLeft;
	this._lblCaption.top = parseInt(this._titlebarMargins.top) + parseInt(this._captionMargins.top);
	this._lblCaption.width = width - (itemPaddingLeft + itemPaddingRight);
	this._lblCaption.height = this._imgBorderTop.height - (parseInt(this._titlebarMargins.top) + parseInt(this._captionMargins.top)) - (parseInt(this._titlebarMargins.bottom) + parseInt(this._captionMargins.bottom));
}

/**
 * Resizes window border elements.
 * @private
 */
Yahoo.Controls.Form.prototype._form_paintBackground = function() {

	var width = this.width;
	var height = this.height;

	this._imgCornerTopLeft.hOffset = 0;
	this._imgCornerTopLeft.vOffset = 0;
	// Size from image

	this._imgCornerTopRight.vOffset = 0;
	// Size from image

	this._imgCornerBottomLeft.hOffset = 0;
	// Size from image

	// Top border width is width - (corner widths)
	this._imgBorderTop.vOffset = 0;
	// Height from image

	// Left border height is height - (corner heights)
	this._imgBorderLeft.hOffset = 0;
	this._imgBorderLeft.vOffset = this._imgCornerTopLeft.height;
	// Width from image
	
	// Right border height is height - (corner heights)
	this._imgBorderRight.vOffset = this._imgCornerTopRight.height;
	// Width from image
	
    this._form_resizePaintBackground();
}

/**
 * Changes the control size.
 * @private
 * @param {Integer} width The width of the form.
 * @param {Integer} height The height of the form.
 */
Yahoo.Controls.Form.prototype._form_setSize = function(width, height) {

	// NOTE: This function overrides baseclass
	var notify = false;

	//log("Form._form_setSize()");

	// Check against constraints
	if(this._minimumWidth != -1) {
		if(width < this._minimumWidth) { width = this._minimumWidth }
	}
	if(this._minimumHeight != -1) {
		if(height < this._minimumHeight) { height = this._minimumHeight }
	}
	if(this._maximumWidth != -1) {
		if(width > this._maximumWidth) { width = this._maximumWidth }
	}
	if(this._maximumHeight != -1) {
		if(height > this._maximumHeight) { height = this._maximumHeight }
	}

	if(width!=this._frame.width) {
		this._window.width = width;
		this._frame.width = width;
		notify = true;
	}

	if(height!=this._window.height) {
		this._window.height = height;
		this._frame.height = height;
		notify = true;
	}

	if(notify==true) {
		this._onResize(this, new Yahoo.EventArgs());
	}
}

/**
 * Changes the control location.
 * @private
 * @param {Integer} left The left edge of the form.
 * @param {Integer} top The top edge of the form.
 */
Yahoo.Controls.Form.prototype._form_setLocation = function(left, top) {

	// NOTE: This function overrides baseclass
	var notify = false;

	//log("Form._form_setLocation()");

	if(left!=this._window.hOffset) {
		this._window.hOffset = left;
		notify = true;
	}

	if(top!=this._window.vOffset) {
		this._window.vOffset = top;
		notify = true;
	}

	if(notify==true) {
		this._onLocationChanged(this, new Yahoo.EventArgs());
	}
}
/*-----------------------------------------------------------*/
// Public code
/*-----------------------------------------------------------*/
/**
 * Initializes control.
 * @param {Yahoo.Controls.Theme} theme The theme this control should use or null to create an instance of the default theme.
 */
Yahoo.Controls.Form.prototype.initialize = function(theme) {

	//log("Form.initialize()");
	
	// Call base class
	this.baseclassForm.initialize.call(this, theme);

	// Includes
	lib.include("Yahoo.InvalidEnumArgumentException");
	lib.include("Yahoo.Controls.Label");
	lib.include("Yahoo.Controls.ImageButton");

	// Internal objects
	this._window = new Window();
	// There is a bug in the Mac version and weird things happen if you try to set options to a window that is not visible
	//this._window.visible = false;
	this._window.locked = true;
	this._window.alignment = "left";
	this._window.shadow = false;
	
	// Move base controls frame into our window
	this._frame.window = this._window;
	this._frame.zOrder = 0;
	
	// Create a frame for the client area
	this._clientFrame = new Frame();
	this._clientFrame.zOrder = 1000;
	this._frame.addSubview(this._clientFrame);

	// Misc
	this._sizeStartX = 0;
	this._sizeStartX = 0;

	// Form properties
	this._backColor = null;
    this._clientFrame.style.backgroundColor = this._backColor;
	this._borderColor = "#000000";
	this._formBorderStyle = Yahoo.Controls.FormBorderStyle.Sizable;
	this._minimumWidth = -1;
	this._minimumHeight = -1;
	this._maximumWidth = -1;
	this._maximumHeight = -1;
	this._closeBox = true;
	this._dialogResult = Yahoo.Controls.DialogResult.None;

	// Events
	this._onBorderColorChangedEventHandlers = new Array();
	this._onClosingEventHandlers = new Array();
	this._onClosedEventHandlers = new Array();

	// Load image objects
	this._form_loadTheme();
	
	// Update styles and theme
	this._onFormBorderStyleChanged(this, new Yahoo.EventArgs());

	// Resize window to position all elements
	this._form_setSize(300,300);
}

/**
 * Adds a control to the controls collection.
 * @param {Yahoo.Controls.Control} value The control to add to this form.
 */
Yahoo.Controls.Form.prototype.addControl = function(value) {

	//log("Form.addControl");

	// NOTE: Overrides baseclass
	if(value!=null) {
		value.parent = this;
		this._controls.push(value);
		this._clientFrame.addSubview(value.frame);
	} // if(null)
}

/**
 * Adds an event handler. Supported events are: BorderColorChanged, Closing, Closed.
 * @param {Function} eventHandler The function that is to be called when the event is raised.
 * @param {String} eventName The name of the event that is being listened to.
 */
Yahoo.Controls.Form.prototype.addEventHandler = function(eventHandler, eventName) {

	// Call baseclass
	this.baseclassForm.addEventHandler.call(this, eventHandler, eventName)

	switch(eventName) {
		case "BorderColorChanged":
			this._onBorderColorChangedEventHandlers.push(eventHandler);
			break;
		case "Closing":
			this._onClosingEventHandlers.push(eventHandler);
			break;
		case "Closed":
			this._onClosedEventHandlers.push(eventHandler);
			break;
	}
}

/**
 * Closes the form.
 */
Yahoo.Controls.Form.prototype.close = function() {

	var cancelEventArgs = new Yahoo.EventArgs();

	this._onClosing.call(this, this, cancelEventArgs);
	
	if(cancelEventArgs.cancel==false) {
		this.dispose();
		this._onClosed.call(this, this, new Yahoo.EventArgs());
	}
}

/**
 * Disposes control's resources.
 */
Yahoo.Controls.Form.prototype.dispose = function() {
	
	// Dispose native items
	this._form_disposeNativeObjects();
	
	// Call base class, removes all native items from _frame, too
	this.baseclassForm.dispose.call(this);

	// Clean up other items
	if(this._clientFrame!=null) { this._clientFrame = null; }
	this._window.visible = false;
	// DEBUG: This will crash Widget Engine
	//this._window = null;
}

/**
 * Hides the control.
 */
Yahoo.Controls.Form.prototype.hide = function() {

	// NOTE: Overrides baseclass
	this._window.visible = false;
}

/**
 * Displays the control.
 */
Yahoo.Controls.Form.prototype.show = function() {

	// NOTE: Overrides baseclass
	if(this._window.opacity==0) { this._window.opacity = 255; }
	this._window.visible = true;
}

/*-----------------------------------------------------------*/
// Public properties
/*-----------------------------------------------------------*/
/**
 * Gets or sets the form border color.
 * @type String
 */
Yahoo.Controls.Form.prototype.borderColor getter = function() {
	return this._borderColor;
}

Yahoo.Controls.Form.prototype.borderColor setter = function(value) {

	if(value!=this._bordercolor) {
		this._borderColor = value;
		this._onBorderColorChanged(this, new Yahoo.EventArgs());
	}

}

/**
 * Gets or sets the height and width of the client area.
 * @type Yahoo.Drawing.Size
 */
Yahoo.Controls.Form.prototype.clientSize getter = function() {

	// NOTE: Overrides base class
	if(this._disposing==false) {
		return new Yahoo.Drawing.Size(this._clientFrame.width, this._clientFrame.height);
	}
}

Yahoo.Controls.Form.prototype.clientSize setter = function(value) {

	// NOTE: Overrides base class
	throw new Error("clientSize is read-only");
}

/**
 * Gets or sets a value indicating whether the close button is displayed.
 * @type Boolean
 */
Yahoo.Controls.Form.prototype.closeBox getter = function() {

	return this._closeBox;
}

Yahoo.Controls.Form.prototype.closeBox setter = function(value) {

	if(this._closeBox!=value) {
		this._closeBox = value;
		this._form_paintBackground();
	}
}

/**
 * Gets or sets the style of the form border.
 * @type Yahoo.Controls.FormBorderStyle
 */
Yahoo.Controls.Form.prototype.formBorderStyle getter = function() {

	return this._formBorderStyle;
}

Yahoo.Controls.Form.prototype.formBorderStyle setter = function(value) {

	// TODO: Check input for valid type / compare to enum
	this._formBorderStyle = value;

	// Tell form to update its style
	this._onFormBorderStyleChanged(this, new Yahoo.EventArgs());
}

/**
 * Gets or sets the dialog result for the form.
 * @type Integer
 */
Yahoo.Controls.Form.prototype.dialogResult getter = function() {

	return this._dialogResult;
}

Yahoo.Controls.Form.prototype.dialogResult setter = function(value) {

	this._dialogResult = value;
}

/**
 * Gets the the frame of the control.
 * @type Frame
 */
Yahoo.Controls.Form.prototype.frame getter = function() {
	
	// NOTE: Overrides baseclass
	return this._clientFrame;
}

Yahoo.Controls.Form.prototype.frame setter = function(value) {

	// NOTE: Overrides baseclass
	throw new Error("frame is read-only");
}

/**
 * Gets or sets the height of the control.
 * @type Integer
 */
Yahoo.Controls.Form.prototype.height getter = function() {

	// NOTE: Overrides baseclass
	if(this._disposing==false) {
		return this._window.height;
	}
}

Yahoo.Controls.Form.prototype.height setter = function(value) {

	// NOTE: Overrides baseclass
	if(value!=null) {
	    if(this._window.height != value) {
    		this._form_setSize(this._window.width, value);
    	}
	}
	else {
		throw new Yahoo.ArgumentNullException("value");
	}
}

/**
 * Gets or sets the x-coordinate of the left edge of this control.
 * @type Integer
 */
Yahoo.Controls.Form.prototype.left getter = function() {

	// NOTE: Overrides baseclass
	if(this._disposing==false) {
		return this._window.hOffset;
	}
}

Yahoo.Controls.Form.prototype.left setter = function(value) {

	// NOTE: Overrides baseclass
	if(value!=null) {
		this._form_setLocation(value, this.top);
	}
	else {
		throw new Yahoo.ArgumentNullException("value");
	}
}

/**
 * Gets or sets the form maximum height.
 * @type Integer
 */
Yahoo.Controls.Form.prototype.maximumHeight getter = function() {

	return this._maximumHeight;
}

Yahoo.Controls.Form.prototype.maximumHeight setter = function(value) {

	this._maximumHeight = value;

	// Make sure the form size is within bounds
	if(this.height > value) {
		this.height = value;
	}
}

/**
 * Gets or sets the form maximum size.
 * @type Yahoo.Drawing.Size
 */
Yahoo.Controls.Form.prototype.maximumSize getter = function() {

	return new Yahoo.Drawing.Size(this._maximumWidth, this._maximumHeight);
}

Yahoo.Controls.Form.prototype.maximumSize setter = function(value) {

	this._maximumWidth = value.width;
	this._maximumHeight = value.height;
	
	// Make sure the form size is within bounds
	if(this.width > value.width || this.height > value.height) {
		// Check which value we need to modify (the logic is a little reversed)
		if(this.width < value.width) { value.width = this.width; }
		if(this.height < value.height) { value.height = this.height; }
		this._form_setSize(value.width, value.height);
	}
}

/**
 * Gets or sets the form maximum width.
 * @type Integer
 */
Yahoo.Controls.Form.prototype.maximumWidth getter = function() {

	return this._maximumWidth;
}

Yahoo.Controls.Form.prototype.maximumWidth setter = function(value) {

	this._maximumWidth = value;

	// Make sure the form size is within bounds
	if(this.width > value) {
		this.width = value;
	}
}

/**
 * Gets or sets the form minimum height.
 * @type Integer
 */
Yahoo.Controls.Form.prototype.minimumHeight getter = function() {

	return this._minimumHeight;
}

Yahoo.Controls.Form.prototype.minimumHeight setter = function(value) {

	this._minimumHeight = value;

	// Make sure the form size is within bounds
	if(this.height < value) {
		this.height = value;
	}
}

/**
 * Gets or sets the form minimum size.
 * @type Yahoo.Drawing.Size
 */
Yahoo.Controls.Form.prototype.minimumSize getter = function() {

	return new Yahoo.Drawing.Size(this._minimumWidth, this._minimumHeight);
}

Yahoo.Controls.Form.prototype.minimumSize setter = function(value) {

	this._minimumWidth = value.width;
	this._minimumHeight = value.height;

	// Make sure the form size is within bounds
	if(this.width < value.width || this.height < value.height) {
		// Check which size we need to modify
		if(this.width > value.width) { value.width = this.width; }
		if(this.height > value.height) { value.height = this.height; }
		this._form_setSize(value.width, value.height);
	}
}

/**
 * Gets or sets the form minimum width.
 * @type Integer
 */
Yahoo.Controls.Form.prototype.minimumWidth getter = function() {

	return this._minimumWidth;
}

Yahoo.Controls.Form.prototype.minimumWidth setter = function(value) {

	this._minimumWidth = value;
	
	// Make sure the form size is within bounds
	if(this.width <= value) {
		this.width = value;
	}
}

/**
 * Gets or sets the y-coordinate of the top edge of this control.
 * @type Integer
 */
Yahoo.Controls.Form.prototype.top getter = function() {

	// NOTE: Overrides baseclass
	if(this._disposing==false) {
		return this._window.vOffset;
	}
}

Yahoo.Controls.Form.prototype.top setter = function(value) {

	// NOTE: Overrides baseclass
	if(value!=null) {
		this._form_setLocation(this.left, value);
	}
	else {
		throw new Yahoo.ArgumentNullException("value");
	}
}

/**
 * Gets or sets the width of the control.
 * @type Integer
 */
Yahoo.Controls.Form.prototype.width getter = function() {

	// NOTE: Overrides baseclass
	if(this._disposing==false) {
		return this._window.width;
	}
}

Yahoo.Controls.Form.prototype.width setter = function(value) {

	// NOTE: Overrides baseclass
	if(value!=null) {
	    if(this._window.width != value) {
    		this._form_setSize(value, this._window.height);
    	}
	}
	else {
		throw new Yahoo.ArgumentNullException("value");
	}
}

/**
 * Gets the Window of this form.
 * @type Window
 */
Yahoo.Controls.Form.prototype.window getter = function() {

	if(this._disposing==false) {
		return this._frame.window;
	}
}

Yahoo.Controls.Form.prototype.window setter = function(value) {

	throw new Error("window is read-only");
}
