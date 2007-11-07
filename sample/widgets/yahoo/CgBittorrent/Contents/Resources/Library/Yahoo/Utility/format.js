/*---------------------------------------------------------------------*/
/// <copyright from='2005' to='2006' company='Yahoo! Inc.'>
/// (C) Copyright 2005-2006 Yahoo! Inc. All Rights Reserved.
/// </copyright>

/**
 * format function.
 */
/*---------------------------------------------------------------------*/

/*---------------------------------------------------------------------*/
// Namespace
/*---------------------------------------------------------------------*/
// Create namespace Yahoo if it doesn't already exist
if(Yahoo==undefined) { var Yahoo = new Object(); }
if(Yahoo.Utility==undefined) { Yahoo.Utility = new Object(); }

/**
 * Replaces the format item in the given string with the text equivalent of the corresponding object instance in the array.
 * Replaces "{n}" with arguments[n]. Currently does not do any formatting on the values.
 * @param {String} text The template text to format.
 * @param {Object} args The content to fill the template with.
 */
Yahoo.Utility.format = function(text, args) {

	var result;
	
	// Do format
	result = text.replace(/\{(\d+)\}/g,
			function(match, count) {
				return args[count];
			});

	return result;
}

