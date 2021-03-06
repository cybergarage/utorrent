/*---------------------------------------------------------------------*/
/// <copyright from='2005' to='2006' company='Yahoo! Inc.'>
/// (C) Copyright 2005-2006 Yahoo! Inc. All Rights Reserved.
/// </copyright>

/**
 * stripHtml function.
 */
/*---------------------------------------------------------------------*/

/*---------------------------------------------------------------------*/
// Namespace
/*---------------------------------------------------------------------*/
// Create namespace Yahoo if it doesn't already exist
if(Yahoo==undefined) { var Yahoo = new Object(); }
if(Yahoo.Utility==undefined) { Yahoo.Utility = new Object(); }

Yahoo.Utility.HtmlEntities = {'nbsp':160,'iexcl':161,'cent':162,'pound':163,'curren':164,'yen':165,'brvbar':166,'sect':167,
		'uml':168,'copy':169,'ordf':170,'laquo':171,'not':172,'shy':173,'reg':174,'macr':175,'deg':176,'plusmn':177,
		'sup2':178,'sup3':179,'acute':180,'micro':181,'para':182,'middot':183,'cedil':184,'sup1':185,'ordm':186,
		'raquo':187,'frac14':188,'frac12':189,'frac34':190,'iquest':191,'agrave':192,'aacute':193,'acirc':194,
		'atilde':195,'auml':196,'aring':197,'aelig':198,'ccedil':199,'egrave':200,'eacute':201,'ecirc':202,
		'euml':203,'igrave':204,'iacute':205,'icirc':206,'iuml':207,'eth':208,'ntilde':209,'ograve':210,'oacute':211,
		'ocirc':212,'otilde':213,'ouml':214,'times':215,'oslash':216,'ugrave':217,'uacute':218,'ucirc':219,'uuml':220,
		'yacute':221,'thorn':222,'szlig':223,'agrave':224,'aacute':225,'acirc':226,'atilde':227,'auml':228,'aring':229,
		'aelig':230,'ccedil':231,'egrave':232,'eacute':233,'ecirc':234,'euml':235,'igrave':236,'iacute':237,'icirc':238,
		'iuml':239,'eth':240,'ntilde':241,'ograve':242,'oacute':243,'ocirc':244,'otilde':245,'ouml':246,'divide':247,
		'oslash':248,'ugrave':249,'uacute':250,'ucirc':251,'uuml':252,'yacute':253,'thorn':254,'yuml':255,'lt':38,'gt':62,
		'amp':38,'apos':39,'quot':34,'oelig':338,'oelig':339,'scaron':352,'scaron':353,'yuml':376,'circ':710,'tilde':732,
		'ensp':8194,'emsp':8195,'thinsp':8201,'zwnj':8204,'zwj':8205,'lrm':8206,'rlm':8207,'ndash':8211,'mdash':8212,
		'lsquo':8216,'rsquo':8217,'sbquo':8218,'ldquo':8220,'rdquo':8221,'bdquo':8222,'dagger':8224,'dagger':8225,
		'permil':8240,'lsaquo':8249,'rsaquo':8250,'euro':8364,'fnof':402,'alpha':913,'beta':914,'gamma':915,'delta':916,
		'epsilon':917,'zeta':918,'eta':919,'theta':920,'iota':921,'kappa':922,'lambda':923,'mu':924,'nu':925,'xi':926,
		'omicron':927,'pi':928,'rho':929,'sigma':931,'tau':932,'upsilon':933,'phi':934,'chi':935,'psi':936,'omega':937,
		'alpha':945,'beta':946,'gamma':947,'delta':948,'epsilon':949,'zeta':950,'eta':951,'theta':952,'iota':953,
		'kappa':954,'lambda':955,'mu':956,'nu':957,'xi':958,'omicron':959,'pi':960,'rho':961,'sigmaf':962,'sigma':963,
		'tau':964,'upsilon':965,'phi':966,'chi':967,'psi':968,'omega':969,'thetasym':977,'upsih':978,'piv':982,
		'bull':8226,'hellip':8230,'prime':8242,'prime':8243,'oline':8254,'frasl':8260,'weierp':8472,'image':8465,
		'real':8476,'trade':8482,'alefsym':8501,'larr':8592,'uarr':8593,'rarr':8594,'darr':8595,'harr':8596,
		'crarr':8629,'larr':8656,'uarr':8657,'rarr':8658,'darr':8659,'harr':8660,'forall':8704,'part':8706,
		'exist':8707,'empty':8709,'nabla':8711,'isin':8712,'notin':8713,'ni':8715,'prod':8719,'sum':8721,
		'minus':8722,'lowast':8727,'radic':8730,'prop':8733,'infin':8734,'ang':8736,'and':8743,'or':8744,
		'cap':8745,'cup':8746,'int':8747,'there4':8756,'sim':8764,'cong':8773,'asymp':8776,'ne':8800,
		'equiv':8801,'le':8804,'ge':8805,'sub':8834,'sup':8835,'nsub':8836,'sube':8838,'supe':8839,'oplus':8853,
		'otimes':8855,'perp':8869,'sdot':8901,'lceil':8968,'rceil':8969,'lfloor':8970,'rfloor':8971,'lang':9001,
		'rang':9002,'loz':9674,'spades':9824,'clubs':9827,'hearts':9829,'diams':9830} 

/**
 * Strips all HTML code and returns a plain text string.
 * @param {String} text The HTML string to convert into plain text.
 * @param {Boolean} brToLineFeed A value indicating whether BR tags should be converted into line feeds.
 * @param {Boolean} doublePass A value indicating whether a double pass of HTML decoding should be done.
 */
Yahoo.Utility.stripHtml = function(text, brToLineFeed, doublePass) {

	var result;
	
	result = text;
	
	// Remove any newline characters
	result = result.replace(/[\r]+/, "");

	// Convert <br> tags to linefeeds \n
	if(brToLineFeed==true) {
		result = result.replace(/<\/?br[^<>]*>/g, "\n");
	}
	
	// Strip HTML tags
	result = result.replace(/<\/?[a-z][a-z0-9]*[^<>]*>/g, "");

	// Convert HTML entities
	result = Yahoo.Utility.decodeHtmlEntities(result);	
	if(doublePass==true) {
		result = Yahoo.Utility.decodeHtmlEntities(result);	
	}

	// Remove double whitespaces
	result = result.replace(/[ \t]{2,}/g, " ");

	// Remove whitespaces from start and end of string
	result = result.replace(/^[ \t]+|[ \t]+$/mg, "");

	return result;
}

/**
 * Converts HTML entities into text.
 * @param {String} text The HTML string that contains encoded HTML entities that should be decoded.
 * @type String
 */
Yahoo.Utility.decodeHtmlEntities = function(text) { 

	var charRegEx = /&(?:(\w{2,7})|#(\d{2,4}));/g;
	var hit;
	var charCode;
	var lastHit = 0; 
	var result = "";

	while((hit=charRegEx.exec(text))!=null) {
		// Decimal values are always in group 2
		charCode = new Number(hit[2]);

		if(isNaN(charCode)==true) {
			// Not a decimal number, get from entity map
			charCode = Yahoo.Utility.HtmlEntities[hit[1].toLowerCase()];
		}

		result += text.substring(lastHit, hit.index) + String.fromCharCode(charCode);
		lastHit = hit.index + hit[0].length;
	} 

	result += text.substring(lastHit);

	return result;
} 

