/*---------------------------------------------------------------------*/
/// <copyright from='2005' to='2006' company='Yahoo! Inc.'>
/// (C) Copyright 2005-2006 Yahoo! Inc. All Rights Reserved.
/// </copyright>

/**
 * EventArgs.
 */
/*---------------------------------------------------------------------*/

/*---------------------------------------------------------------------*/
// Namespace
/*---------------------------------------------------------------------*/
// Create namespace if it doesn't already exist
if(Yahoo==undefined) { var Yahoo = new Object(); }

/*---------------------------------------------------------------------*/
// Constructor
/*---------------------------------------------------------------------*/
/**
 * Default constructor for EventArgs.
 * @constructor
 */
Yahoo.EventArgs = function() {

	this.initialize();
}

/*---------------------------------------------------------------------*/
// Public code
/*---------------------------------------------------------------------*/
/**
 * True constructor. Must be called when this class is overridden.
 */
Yahoo.EventArgs.prototype.initialize = function() {

	this.cancel = false;
}

/*---------------------------------------------------------------------*/
/// <copyright from='2005' to='2006' company='Yahoo! Inc.'>
/// (C) Copyright 2005-2006 Yahoo! Inc. All Rights Reserved.
/// </copyright>

/**
 * raiseEvent function.
 */
/*---------------------------------------------------------------------*/

/**
 * Raises an event to all subscribed listeners.
 * @param {Object} sender The object that raised this event.
 * @param {Array} eventHandlers The array of event handlers to call.
 * @param {Yahoo.EventArgs} e The event details.
 */
Yahoo.raiseEvent = function(sender, eventHandlers, e) {

	var count;
	
	if(eventHandlers!=null) {
		for(count=0;count<eventHandlers.length;count++) {
			if(e.cancel==false) {
				try {
					eventHandlers[count](sender, e);
				}  // try
				catch(e) {
					log(e);
				}  // catch
			} // if(e.cancel==false)
		} // for
	} // if(eventHandlers!=null)
}
