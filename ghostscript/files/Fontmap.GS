% Copyright (C) 2001-2021 Artifex Software, Inc.
% All Rights Reserved.
%
% This software is provided AS-IS with no warranty, either express or
% implied.
%
% This software is distributed under license and may not be copied,
% modified or distributed except as expressly authorized under the terms
% of the license contained in the file LICENSE in this distribution.
%
% Refer to licensing information at http://www.artifex.com or contact
% Artifex Software, Inc.,  1305 Grant Avenue - Suite 200, Novato,
% CA 94945, U.S.A., +1(415)492-9861, for further information.
%

% Fontmap - standard font catalog for Ghostscript.

% ----------------------------------------------------------------

% This file is a catalog of fonts known to Ghostscript.  Any font
% that is to be loaded automatically when named must be in this catalog,
% except for fonts that Ghostscript finds automatically in directories
% named in the GS_FONTPATH environment variable.

% Each font has an entry consisting of three items:
%
%	- The name by which the font is known inside Ghostscript
%	(a Ghostscript name preceded by a `/', or a string enclosed
%	in parentheses).  This is used to find the file from which
%	a font of a given name should be loaded.
%
%	- Information depending on whether this is a real font or a
%	font alias:
%
%		- For real fonts, `PFA', `PFB', 'CFF', 'TTF,
%               'TTC' (see below) files are usable as fonts for
%               Ghostscript.
%
%		- For font aliases, the name of the font which should
%		be used when this one is requested, preceded by a
%		`/'.  See the entry for Charter below for an example.
%		Note that an alias name cannot be enclosed in parentheses.
%
%	- At least one space or tab, and a terminating semicolon.

%
%
%	There are three forms of record:
%		Substitute a font by name:
%			/FontName	/SubstituteFont ;
%		Substitute a font with a file:
%			/FontName	(/path/to/font/file) ;
%		Substitute a font with a font from a Truetype collection:
%			/FontName	<< /Path (/path/to/font/file) /SubfontID <ttc-index> >> ;
%
%	Substituting a font with a file can either use the full path form, for example:
%			/CenturySchL-Ital (/usr/share/fonts/type1/gsfonts/c059033l.pfb) ;
%	Or rely on the Ghostscript font search path:
%			/CenturySchL-Ital (c059033l.pfb) ;
%
%
%	The dictionary form can be used to substitute a font with an individual font from a Truetype
%	collection:
%			/NSimSun	<< /Path (/home/user/fonts/simsun.ttc) /SubfontID 1>> ;
%	If the target is not a TTC, the SubfontID entry is ignored.
%
%	NOTE: The font name (the entry in first column) must match the name of the TTC index. As
%	in the above example, index 0 in simsun.ttc must be /SimSun and index 1 must be /NSimSin.

% The following table is executed as a PostScript file.
% If you add new entries, be sure to copy the punctuation accurately;
% in particular, you must leave at least one space or tab between each
% field in the entry.  Also, please read fonts.doc for important information
% about font names.

% PDF interpreter evaluates hexadecimal escapes in PDF font names before
% looking up the font. When the resulting name cannot be represented using
% PostScript name syntax, the string can be used instead of the name.

% Note that .pfa and .pfb fonts are compatible with Adobe Type Manager
% and other programs that don't include full PostScript interpreters,
% as well as with PostScript interpreters; .gsf fonts are compatible with
% PostScript interpreters, but not with ATM or similar programs.

% NOTE: (as of 9.56.0) The use of Postscript operators in the cidfmap file is now deprecated, for
% compatibility with (and security of) the PDF interpreter implemented in C (rather than Postscript).
% Thus operations such as "getenv", "cvn" and ".concatstrings" are no longer supported.

%
%
% Fonts contributed by:
%	URW++ Design and Development Incorporated
%	Poppenbuetteler Bogen 29A
%	D-22399 Hamburg
%	Germany
%	tel. +49 (40) 60 60 50
%	fax +49 (40) 60 60 51 11
%	http://www.urwpp.de
% for distribution under the GNU License and Aladdin Free Public License.
% See the notice at the head of this Fontmap file for licensing terms.
% Each of these fonts is individually covered by the license:
% for licensing purposes, they are not "part of" any larger entity.
% The following notice applies to these fonts:
%
%	Copyright URW Software, Copyright 1994 by URW.
%

% Aliases

/AvantGarde-BookOblique		/URWGothic-BookOblique    ;
/AvantGarde-Book		/URWGothic-Book        ;
/AvantGarde-DemiOblique		/URWGothic-DemiOblique    ;
/AvantGarde-Demi		/URWGothic-Demi        ;
/Bookman-DemiItalic		/URWBookman-DemiItalic	;
/Bookman-Demi			/URWBookman-Demi	;
/Bookman-LightItalic		/URWBookman-LightItalic	;
/Bookman-Light			/URWBookman-Light	;
/Courier-Bold			/NimbusMonoPS-Bold	;
/Courier-BoldOblique		/NimbusMonoPS-BoldItalic	;
/Courier			/NimbusMonoPS-Regular	;
/Courier-Oblique		/NimbusMonoPS-Italic	;
/Helvetica-Bold			/NimbusSans-Bold ;
/Helvetica-BoldOblique		/NimbusSans-BoldItalic      ;
/Helvetica-Narrow-Bold		/NimbusSansNarrow-Bold    ;
/Helvetica-Narrow-BoldOblique	/NimbusSansNarrow-BoldOblique        ;
/Helvetica-Narrow		/NimbusSansNarrow-Regular    ;
/Helvetica-Narrow-Oblique	/NimbusSansNarrow-Oblique        ;
/Helvetica			/NimbusSans-Regular ;
/Helvetica-Oblique		/NimbusSans-Italic      ;
/NewCenturySchlbk-Bold		/C059-Bold	;
/NewCenturySchlbk-BoldItalic	/C059-BdIta	;
/NewCenturySchlbk-Italic	/C059-Italic	;
/NewCenturySchlbk-Roman		/C059-Roman	;
/Palatino-BoldItalic		/P052-BoldItalic	;
/Palatino-Bold			/P052-Bold	;
/Palatino-Italic		/P052-Italic	;
/Palatino-Roman			/P052-Roman	;
/Symbol				/StandardSymbolsPS	;
/Times-BoldItalic		/NimbusRoman-BoldItalic	;
/Times-Bold			/NimbusRoman-Bold	;
/Times-Italic			/NimbusRoman-Italic	;
/Times-Roman			/NimbusRoman-Regular	;
/ZapfChancery-MediumItalic	/Z003-MediumItalic	;
/ZapfDingbats			/D050000L	;

% 
%
% Fonts converted from Hershey outlines.  These are constructed and
% maintained manually.  These are also in the public domain.
%
% The suggested UniqueID's and filenames are constructed differently for
% these than for the ones above, because of the strange way that the Hershey
% fonts were constructed.  The scheme for these looks like:
%
% 42TTXY0
%
% TT = typeface, X = ``class'', Y = variation
%
% The typeface names and numbers are listed in fonts.mak.
%
% class:
% 0 = normal			= r
% 1 = simplex			= s
% 2 = complex			= c
% 3 = triplex			= t
% 4 = duplex			= d
%
% variation:
% 0 = normal			(omitted)
% 1 = oblique			= o
% 2 = italic			= i
% 3 = bold			= b
% 4 = bold oblique		= bo
% 5 = bold italic		= bi
%

/Arial					/ArialMT		;
/Arial,Bold				/Arial-BoldMT		;
/Arial,Italic				/Arial-ItalicMT		;
/Arial,BoldItalic			/Arial-BoldItalicMT	;

/TimesNewRoman				/TimesNewRomanPSMT		;
/TimesNewRoman,Bold			/TimesNewRomanPS-BoldMT		;
/TimesNewRoman,Italic			/TimesNewRomanPS-ItalicMT	;
/TimesNewRoman,BoldItalic		/TimesNewRomanPS-BoldItalicMT	;
