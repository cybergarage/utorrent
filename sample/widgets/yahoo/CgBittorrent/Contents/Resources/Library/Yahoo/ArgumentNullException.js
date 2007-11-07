/*---------------------------------------------------------------------*/
/// <copyright from='2005' to='2006' company='Yahoo! Inc.'>
/// (C) Copyright 2005-2006 Yahoo! Inc. All Rights Reserved.
/// </copyright>

/**
 * The exception that is thrown when a null reference is passed as a required argument.
 */
/*---------------------------------------------------------------------*/

/*---------------------------------------------------------------------*/
// Namespace
/*---------------------------------------------------------------------*/
// Create namespace Yahoo if it doesn't already exist
if(Yahoo==undefined) { var Yahoo = new Object() }

/*---------------------------------------------------------------------*/
// Constructor
/*---------------------------------------------------------------------*/
/**
 * Default constructor.
 * @constructor
 * @param {String} paramName The name of the parameter.
 * @param {String} message The error text for this exception.
 */
Yahoo.ArgumentNullException = function(paramName, message) {

	this.initialize(paramName, message);
}

/**
 * Define inheritance chain.
 */
Yahoo.ArgumentNullException.prototype = new Error();
Yahoo.ArgumentNullException.prototype.constructor = Yahoo.ArgumentNullException;
Yahoo.ArgumentNullException.prototype.baseclass = Error.prototype;

/*---------------------------------------------------------------------*/
// Public code
/*---------------------------------------------------------------------*/
/**
 * True constructor. Must be called if this class is overridden.
 * @param {String} paramName The name of the parameter.
 * @param {String} message The error text for this exception.
 */
Yahoo.ArgumentNullException.prototype.initialize = function(paramName, message) {

	this.paramName = paramName;
	if(message!=null && message!="") {
		this.message = message;
	}
	else {
		this.message = paramName;
	}
	this.name = "ArgumentNullException";
}