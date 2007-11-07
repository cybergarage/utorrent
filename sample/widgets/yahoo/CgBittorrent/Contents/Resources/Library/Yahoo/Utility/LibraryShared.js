/*---------------------------------------------------------------------*/
/// <copyright from='2005' to='2007' company='Yahoo! Inc.'>
/// (C) Copyright 2005-2007 Yahoo! Inc. All Rights Reserved.
/// </copyright>

/**
 * Library management class.
 */
/*---------------------------------------------------------------------*/
/*---------------------------------------------------------------------*/
// Constructor
/*---------------------------------------------------------------------*/
// Create namespace Yahoo.Utility if it doesn't already exist
if(Yahoo==undefined) { var Yahoo = new Object() }
if(Yahoo.Utility==undefined) { Yahoo.Utility = new Object() }

/**
 * Default constructor.
 * @constructor
 * @param {String} libraryPath The path to the library root folder.
 */
Yahoo.Utility.Library = function(libraryPath) {

	if(arguments.length > 0) {
		this.initialize(libraryPath);
	}  //arguments.length > 0
}

/*---------------------------------------------------------------------*/
// Global constants
/*---------------------------------------------------------------------*/
// These are defined here to provide hardcoded default settings to all items in the library
Yahoo.Utility.Library.prototype.defaultTheme = "Purple";

/*---------------------------------------------------------------------*/
// Private code
/*---------------------------------------------------------------------*/
/**
 * Recursively creates given directory structure.
 * @private
 * @param {String} path The path to directory to create.
 */
Yahoo.Utility.Library.prototype._createDirectory = function(path) {

	var count;
	var parts;
	var part;
	var currentPath = "";
	
	try {
		parts = path.split("/");
	
		for(count=0; count<parts.length; count++) {
			part = parts[count];
			currentPath += part;
			if(filesystem.itemExists(currentPath)==false) {
				runCommand("mkdir \"" + currentPath + "\"");
			}
			currentPath += "/";
		}  // for path part
	}
	catch(e) {
		log(e);
	}
}

/**
 * Compare function for numeric Array sort.
 * @private
 */
Yahoo.Utility.Library.prototype._numericCompare = function (val1, val2) {

	return val1 - val2;

}

/**
 * Returns the version string of a library file as a number.
 * @private
 */
Yahoo.Utility.Library.prototype._getVersion = function (filename) {

	var result;

	var reVersion = /.+\.v(\d+\.\d{1,2})\.js/;
	var match = reVersion.exec(filename);
	if (match != null && match.length > 1) {
		result = match[1] -0;
	} else {
		result = 0;
	}

	return result;
}

/*---------------------------------------------------------------------*/
// Public code
/*---------------------------------------------------------------------*/
/**
 * True constructor. Must be called if this class is overridden.
 * @param {String} libraryPath The path to the library root folder.
 */
Yahoo.Utility.Library.prototype.initialize = function(libraryPath) {

	if(libraryPath!="") {
		this._libraryPath = libraryPath;

	}  // libraryPath = ""
	else {
		throw new Error("Required parameter 'libraryPath' missing.");
	}  // libraryPath = ""

}

/**
 * Adds the given file as a shared class in the library.
 * @param {String} className The full name of the class to add to the library.
 * @param {String} version The version of the class to add to the library.
 * @param {String} fileName The file name of the class to add to the library.
 * @param {replace} replace A value indicating whether an existing class with the same name and version should be overwritten.
 * @returns
 * -1 = Unknown error.
 * 0 = Library added.
 * 1 = Library already exists.
 */

Yahoo.Utility.Library.prototype.addClass = function(className, version, filename, replace) {

	var count;
	var classPath;
	var names;
	var library;
	var destFilename;
	var skip = false;
	var result = -1;

	if(className!="" && version!="" && filename!="") {

		// Get full path to folder where this class should be located
		classPath = this._libraryPath;

		names = className.split(".");
		for(count=0; count<names.length-1; count++) {
			classPath += "/" + names[count];
		}
		
		// Check if path for this namespace exists
		if(filesystem.itemExists(classPath)==false) {
			// Create path for this namespace
			this._createDirectory(classPath);
		}

		// Get library name (without version or file extension)
		library = names[names.length-1];

		// Check if the library already exists
		destFilename = classPath + "/" + library + ".v" + version.toFixed(2) + ".js";
		if(filesystem.itemExists(destFilename)==true) {
		
			// replace may be undefined
			if(replace!=true) {
				skip = true;
				result = 1;
			}
			else {
				// Remove previous item with this name
				runCommand("rm \"" + destFilename + "\"");
			}  // if replace
			
		}  // if item exists

		if(skip==false) {
			// Copy given file to library
			filesystem.copy(filename, destFilename);
			result = 0;
		}

	}  // parameters != ""
	else {
		throw new Error("Required parameter missing.");
	}  // parameters != ""

}

/**
 * Includes the given class into the currently running widget.
 * @param {String} className The full name of the class to include into the currently running widget.
 * @param {String} version The version of the class to include into the currently running widget.
 * @param {Boolean} exactVersion A value indicating whether the exact version should be included. If false, the latest version will be used.
 */
Yahoo.Utility.Library.prototype.include = function(className, version, exactVersion) {

	var classPath;
	var classExists;

	if(className!="") {
		// Check if the given class has already been included
		try {
			if(eval(className)==undefined) {
				classExists = false
			}
			else {
				classExists = true;
			}  // className==undefined
		}  // try
		catch(e) {
			classExists = false;
		}
		
		if(classExists==false) {
		
			classPath = this.getClass(className, version, exactVersion)
			
			if(classPath!="") {
				include(classPath);
			}  // classPath!=""
			
		}  // class already included
	}  // className = ""
	else {
		throw new Error("Required parameter 'className' missing.");
	}  // className = ""
		
	return classPath;
}

/**
 * Gets the path to the class to include.
 * @param {String} className The full name of the class to get the file name for.
 * @param {String} version The version of the class to get the file name for
 */
Yahoo.Utility.Library.prototype.getClass = function(className, version) {

	var count;
	var classPath;
	var names;
	var library;
	var fullPath = "";
	var dirContents;
	var file;
	var versions;
	var result = "";

	if(className!="") {

		// Get full path to folder where this class should be located
		classPath = this._libraryPath;

		names = className.split(".");
		for(count=0; count<names.length-1; count++) {
			classPath += "/" + names[count];
		}
		
		// Check if path for this namespace exists
		if(filesystem.itemExists(classPath)==true) {
		
			// Get library name (without version or file extension)
			library = names[names.length-1];
			
			// If asked for exact version, check for correct file
			if(version!=null) {

				fullPath = classPath + "/" + library + ".v" + version.toFixed(2) + ".js";

			}  // if version!=null
			else {
	
				// Not asked for exact version, get newest available version
				dirContents = filesystem.getDirectoryContents(classPath);
				
				// Get version number for each file and add to an array
				versions = new Array();
				
				for(count=0; count<dirContents.length; count++) {
	
					file = dirContents[count];
	
					// Put version numbers into an array
					if(filesystem.isDirectory(classPath + "/" + file)==false) {
						versions.push(this._getVersion(file));
					}  // if file
	
					if(versions.length > 0) {
						// Sort array
						versions.sort(this._numericCompare);
		
						// Get path to the library
						fullPath = classPath + "/" + library + ".v" + versions[versions.length-1].toFixed(2) + ".js";
					}  // if versions.length > 0	

				}  // for dirContents
			} // if version!=null
			
			// Check if library file exists
			if(filesystem.itemExists(fullPath) == true) {
				result = fullPath;
			}
		}  // if classPath exists

	}  // className = ""
	else {
		throw new Error("Required parameter 'className' missing.");
	}  // className = ""

	return result;
}

/**
 * Adds a resources path for the class.
 * @param {String} className The full name of the class to add to resources to.
 * @param {String} version The version of the class to add to resources to.
 * @returns
 * -1 = Unknown error.
 * 0 = Path added.
 * 1 = Path already exists.
 */

Yahoo.Utility.Library.prototype.addClassResourcePath = function(className, version) {

	var count;
	var classPath;
	var names;
	var library;
	var result = -1;

	if(className!="" && version!="") {

		// Get full path to folder where the resources for this class should be located
		classPath = this._libraryPath + "/" + className.replace(/\./g, "/") + "/res/" + version.toFixed(2);
		
		// Check if path for this namespace exists
		if(filesystem.itemExists(classPath)==false) {
			// Create path for this namespace
			this._createDirectory(classPath);

			// Check if we succeeded
			if(filesystem.itemExists(classPath)==true) {
				result = 0;
			}  // If success
			else {
				result = -1;
			}  // If success
		}  // If exists already
		else {
			result = 1;
		}  // If exists already

	}  // parameters != ""
	else {
		throw new Error("Required parameter missing.");
	}  // parameters != ""

}

/**
 * Gets the path to the class resources.
 * @param {String} className The full name of the class to get the path to resources.
 * @param {String} version The version of the class to get the path to resources.
 */
Yahoo.Utility.Library.prototype.getClassResourcePath = function(className, version) {

	var count;
	var classPath;
	var fullPath = "";
	var dirContents;
	var folder;
	var versions;
	var result = "";

	if(className!="") {

		// Get full path to folder where the resources for this class should be located
		classPath = this._libraryPath + "/" + className.replace(/\./g, "/") + "/res";
		
		// Check if path for this namespace exists
		if(filesystem.itemExists(classPath)==true) {
		
			// If asked for exact version, check for correct file
			if(version!=null) {

				// Path is in the form "library/my/name/space/res/1.00"
				fullPath = classPath + "/" + version.toFixed(2);

			}  // if version!=null
			else {
	
				// Not asked for exact version, get newest available version
				dirContents = filesystem.getDirectoryContents(classPath);
				
				// Get version number for each folder and add to an array
				versions = new Array();
				
				for(count=0; count<dirContents.length; count++) {
	
					folder = dirContents[count];
	
					// Put version numbers into an array
					if(filesystem.isDirectory(classPath + "/" + folder)==true) {
						versions.push(folder - 0);
					}  // if folder
	
					if(versions.length > 0) {
						// Sort array
						versions.sort(this._numericCompare);
		
						// Get path to the library
						fullPath = classPath + "/" + versions[versions.length-1].toFixed(2);
					}  // if versions.length > 0	

				}  // for dirContents
			} // if exactVersion==false
			
			// Check if library folder exists
			if(filesystem.itemExists(fullPath) == true) {
				result = fullPath;
			}
		}  // if classPath exists

	}  // className = ""
	else {
		throw new Error("Required parameter 'className' missing.");
	}  // className = ""

	return result;
}

/*---------------------------------------------------------------------*/
// Public properties
/*---------------------------------------------------------------------*/
/**
 * Gets the base path for libraries.
 * @type String
 */
Yahoo.Utility.Library.prototype.libraryPath getter = function() {

	return this._libraryPath;
}

Yahoo.Utility.Library.prototype.libraryPath setter = function() {

	throw new Error("libraryPath is read-only.");
	
}

