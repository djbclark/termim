static const Compose western_compose[] = {
    { "  ",   "\xc2\xa0" },	/* nobreakspace */
    { " '",   "'"        },	/* apostrophe */
    { " -",   "~"        },	/* asciitilde */
    { " >",   "^"        },	/* asciicircum */
    { " ^",   "^"        },	/* asciicircum */
    { " `",   "`"        },	/* grave */
    { " v",   "\xcb\x87" },	/* caron */
    { " ~",   "~"        },	/* asciitilde */
    { "!!",   "\xc2\xa1" },	/* exclamdown */
    { "!P",   "\xc2\xb6" },	/* paragraph */
    { "!S",   "\xc2\xa7" },	/* section */
    { "!^",   "\xc2\xa6" },	/* brokenbar */
    { "!p",   "\xc2\xb6" },	/* paragraph */
    { "!s",   "\xc2\xa7" },	/* section */
    { "\" ",  "\xcb\x9d" },	/* doubleacute */
    { "\"\"", "\xc2\xa8" },	/* diaeresis */
    { "\"A",  "\xc3\x84" },	/* Adiaeresis */
    { "\"E",  "\xc3\x8b" },	/* Ediaeresis */
    { "\"I",  "\xc3\x8f" },	/* Idiaeresis */
    { "\"O",  "\xc3\x96" },	/* Odiaeresis */
    { "\"U",  "\xc3\x9c" },	/* Udiaeresis */
    { "\"a",  "\xc3\xa4" },	/* adiaeresis */
    { "\"e",  "\xc3\xab" },	/* ediaeresis */
    { "\"i",  "\xc3\xaf" },	/* idiaeresis */
    { "\"o",  "\xc3\xb6" },	/* odiaeresis */
    { "\"u",  "\xc3\xbc" },	/* udiaeresis */
    { "\"y",  "\xc3\xbf" },	/* ydiaeresis */
    { "' ",   "'"        },	/* apostrophe */
    { "''",   "\xc2\xb4" },	/* acute */
    { "'A",   "\xc3\x81" },	/* Aacute */
    { "'E",   "\xc3\x89" },	/* Eacute */
    { "'I",   "\xc3\x8d" },	/* Iacute */
    { "'O",   "\xc3\x93" },	/* Oacute */
    { "'U",   "\xc3\x9a" },	/* Uacute */
    { "'Y",   "\xc3\x9d" },	/* Yacute */
    { "'a",   "\xc3\xa1" },	/* aacute */
    { "'e",   "\xc3\xa9" },	/* eacute */
    { "'i",   "\xc3\xad" },	/* iacute */
    { "'o",   "\xc3\xb3" },	/* oacute */
    { "'u",   "\xc3\xba" },	/* uacute */
    { "'y",   "\xc3\xbd" },	/* yacute */
    { "((",   "["        },	/* bracketleft */
    { "(-",   "{"        },	/* braceleft */
    { "))",   "]"        },	/* bracketright */
    { ")-",   "}"        },	/* braceright */
    { "*0",   "\xc2\xb0" },	/* degree */
    { "*A",   "\xc3\x85" },	/* Aring */
    { "*a",   "\xc3\xa5" },	/* aring */
    { "++",   "#"        },	/* numbersign */
    { "+-",   "\xc2\xb1" },	/* plusminus */
    { ",,",   "\xc2\xb8" },	/* cedilla */
    { ",-",   "\xc2\xac" },	/* notsign */
    { ",C",   "\xc3\x87" },	/* Ccedilla */
    { ",G",   "\xc4\xa2" },	/* Gcedilla */
    { ",K",   "\xc4\xb6" },	/* Kcedilla */
    { ",L",   "\xc4\xbb" },	/* Lcedilla */
    { ",N",   "\xc5\x85" },	/* Ncedilla */
    { ",R",   "\xc5\x96" },	/* Rcedilla */
    { ",S",   "\xc5\x9e" },	/* Scedilla */
    { ",T",   "\xc5\xa2" },	/* Tcedilla */
    { ",c",   "\xc3\xa7" },	/* ccedilla */
    { ",g",   "\xc4\xa3" },	/* gcedilla */
    { ",k",   "\xc4\xb7" },	/* kcedilla */
    { ",l",   "\xc4\xbc" },	/* lcedilla */
    { ",n",   "\xc5\x86" },	/* ncedilla */
    { ",r",   "\xc5\x97" },	/* rcedilla */
    { ",s",   "\xc5\x9f" },	/* scedilla */
    { ",t",   "\xc5\xa3" },	/* tcedilla */
    { "- ",   "~"        },	/* asciitilde */
    { "-(",   "{"        },	/* braceleft */
    { "-)",   "}"        },	/* braceright */
    { "-+",   "\xc2\xb1" },	/* plusminus */
    { "-,",   "\xc2\xac" },	/* notsign */
    { "--",   "\xc2\xad" },	/* hyphen */
    { "-:",   "\xc3\xb7" },	/* division */
    { "-A",   "\xc2\xaa" },	/* ordfeminine */
    { "-L",   "\xc2\xa3" },	/* sterling */
    { "-N",   "\xc3\x91" },	/* Ntilde */
    { "-O",   "\xc2\xba" },	/* masculine */
    { "-Y",   "\xc2\xa5" },	/* yen */
    { "-^",   "\xc2\xaf" },	/* macron */
    { "-a",   "\xc2\xaa" },	/* ordfeminine */
    { "-l",   "\xc2\xa3" },	/* sterling */
    { "-n",   "\xc3\xb1" },	/* ntilde */
    { "-o",   "\xc2\xba" },	/* masculine */
    { "-y",   "\xc2\xa5" },	/* yen */
    { "..",   "\xc2\xb7" },	/* periodcentered */
    { ".I",   "\xc4\xb0" },	/* Iabovedot */
    { ".U",   "\xc5\xae" },	/* Uring */
    { ".Z",   "\xc5\xbb" },	/* Zabovedot */
    { ".^",   "\xc2\xb7" },	/* periodcentered */
    { ".i",   "\xc4\xb1" },	/* idotless */
    { ".u",   "\xc5\xaf" },	/* uring */
    { ".z",   "\xc5\xbc" },	/* zabovedot */
    { "//",   "\\"       },	/* backslash */
    { "/<",   "\\"       },	/* backslash */
    { "/C",   "\xc2\xa2" },	/* cent */
    { "/D",   "\xc4\x90" },	/* Dstroke */
    { "/O",   "\xc3\x98" },	/* Ooblique */
    { "/U",   "\xc2\xb5" },	/* mu */
    { "/^",   "|"        },	/* bar */
    { "/c",   "\xc2\xa2" },	/* cent */
    { "/d",   "\xc4\x91" },	/* dstroke */
    { "/o",   "\xc3\xb8" },	/* oslash */
    { "/u",   "\xc2\xb5" },	/* mu */
    { "0*",   "\xc2\xb0" },	/* degree */
    { "0C",   "\xc2\xa9" },	/* copyright */
    { "0O",   "\xc2\xb0" },	/* degree */
    { "0S",   "\xc2\xa7" },	/* section */
    { "0X",   "\xc2\xa4" },	/* currency */
    { "0^",   "\xc2\xb0" },	/* degree */
    { "0c",   "\xc2\xa9" },	/* copyright */
    { "0s",   "\xc2\xa7" },	/* section */
    { "0x",   "\xc2\xa4" },	/* currency */
    { "12",   "\xc2\xbd" },	/* onehalf */
    { "14",   "\xc2\xbc" },	/* onequarter */
    { "1S",   "\xc2\xb9" },	/* onesuperior */
    { "1^",   "\xc2\xb9" },	/* onesuperior */
    { "1s",   "\xc2\xb9" },	/* onesuperior */
    { "2S",   "\xc2\xb2" },	/* twosuperior */
    { "2^",   "\xc2\xb2" },	/* twosuperior */
    { "2s",   "\xc2\xb2" },	/* twosuperior */
    { "34",   "\xc2\xbe" },	/* threequarters */
    { "3S",   "\xc2\xb3" },	/* threesuperior */
    { "3^",   "\xc2\xb3" },	/* threesuperior */
    { "3s",   "\xc2\xb3" },	/* threesuperior */
    { ":-",   "\xc3\xb7" },	/* division */
    { "</",   "\\"       },	/* backslash */
    { "<<",   "\xc2\xab" },	/* guillemotleft */
    { "=L",   "\xc2\xa3" },	/* sterling */
    { "=Y",   "\xc2\xa5" },	/* yen */
    { "=l",   "\xc2\xa3" },	/* sterling */
    { "=y",   "\xc2\xa5" },	/* yen */
    { "> ",   "^"        },	/* asciicircum */
    { ">>",   "\xc2\xbb" },	/* guillemotright */
    { ">A",   "\xc3\x82" },	/* Acircumflex */
    { ">E",   "\xc3\x8a" },	/* Ecircumflex */
    { ">I",   "\xc3\x8e" },	/* Icircumflex */
    { ">O",   "\xc3\x94" },	/* Ocircumflex */
    { ">U",   "\xc3\x9b" },	/* Ucircumflex */
    { ">a",   "\xc3\xa2" },	/* acircumflex */
    { ">e",   "\xc3\xaa" },	/* ecircumflex */
    { ">i",   "\xc3\xae" },	/* icircumflex */
    { ">o",   "\xc3\xb4" },	/* ocircumflex */
    { ">u",   "\xc3\xbb" },	/* ucircumflex */
    { "??",   "\xc2\xbf" },	/* questiondown */
    { "A\"",  "\xc3\x84" },	/* Adiaeresis */
    { "A'",   "\xc3\x81" },	/* Aacute */
    { "A*",   "\xc3\x85" },	/* Aring */
    { "A-",   "\xc2\xaa" },	/* ordfeminine */
    { "A>",   "\xc3\x82" },	/* Acircumflex */
    { "AA",   "@"        },	/* at */
    { "AE",   "\xc3\x86" },	/* AE */
    { "A^",   "\xc3\x82" },	/* Acircumflex */
    { "A_",   "\xc4\x80" },	/* Amacron */
    { "A`",   "\xc3\x80" },	/* Agrave */
    { "Aa",   "\xc4\x84" },	/* Aogonek */
    { "Au",   "\xc4\x82" },	/* Abreve */
    { "A~",   "\xc3\x83" },	/* Atilde */
    { "BV",   "\xc2\xa6" },	/* brokenbar */
    { "C'",   "\xc4\x86" },	/* Cacute */
    { "C,",   "\xc3\x87" },	/* Ccedilla */
    { "C/",   "\xc2\xa2" },	/* cent */
    { "C0",   "\xc2\xa9" },	/* copyright */
    { "CO",   "\xc2\xa9" },	/* copyright */
    { "Co",   "\xc2\xa9" },	/* copyright */
    { "Cv",   "\xc4\x8c" },	/* Ccaron */
    { "C|",   "\xc2\xa2" },	/* cent */
    { "D-",   "\xc3\x90" },	/* ETH */
    { "Dv",   "\xc4\x8e" },	/* Dcaron */
    { "E\"",  "\xc3\x8b" },	/* Ediaeresis */
    { "E'",   "\xc3\x89" },	/* Eacute */
    { "E.",   "\xc4\x96" },	/* Eabovedot */
    { "E>",   "\xc3\x8a" },	/* Ecircumflex */
    { "E^",   "\xc3\x8a" },	/* Ecircumflex */
    { "E_",   "\xc4\x92" },	/* Emacron */
    { "E`",   "\xc3\x88" },	/* Egrave */
    { "Ea",   "\xc4\x98" },	/* Eogonek */
    { "Ev",   "\xc4\x9a" },	/* Ecaron */
    { "G,",   "\xc4\xa2" },	/* Gcedilla */
    { "Gu",   "\xc4\x9e" },	/* Gbreve */
    { "I\"",  "\xc3\x8f" },	/* Idiaeresis */
    { "I'",   "\xc3\x8d" },	/* Iacute */
    { "I.",   "\xc4\xb0" },	/* Iabovedot */
    { "I>",   "\xc3\x8e" },	/* Icircumflex */
    { "I^",   "\xc3\x8e" },	/* Icircumflex */
    { "I_",   "\xc4\xaa" },	/* Imacron */
    { "I`",   "\xc3\x8c" },	/* Igrave */
    { "Ia",   "\xc4\xae" },	/* Iogonek */
    { "I~",   "\xc4\xa8" },	/* Itilde */
    { "K,",   "\xc4\xb6" },	/* Kcedilla */
    { "L'",   "\xc4\xb9" },	/* Lacute */
    { "L,",   "\xc4\xbb" },	/* Lcedilla */
    { "L-",   "\xc2\xa3" },	/* sterling */
    { "L/",   "\xc5\x81" },	/* Lstroke */
    { "L=",   "\xc2\xa3" },	/* sterling */
    { "L>",   "\xc4\xbd" },	/* Lcaron */
    { "LV",   "|"        },	/* bar */
    { "N'",   "\xc5\x83" },	/* Nacute */
    { "N,",   "\xc5\x85" },	/* Ncedilla */
    { "N-",   "\xc3\x91" },	/* Ntilde */
    { "NN",   "\xc5\x8a" },	/* ENG */
    { "Nv",   "\xc5\x87" },	/* Ncaron */
    { "N~",   "\xc3\x91" },	/* Ntilde */
    { "O\"",  "\xc3\x96" },	/* Odiaeresis */
    { "O'",   "\xc3\x93" },	/* Oacute */
    { "O-",   "\xc2\xba" },	/* masculine */
    { "O/",   "\xc3\x98" },	/* Ooblique */
    { "O>",   "\xc3\x94" },	/* Ocircumflex */
    { "OC",   "\xc2\xa9" },	/* copyright */
    { "OE",   "\xc5\x92" },
    { "OR",   "\xc2\xae" },	/* registered */
    { "OS",   "\xc2\xa7" },	/* section */
    { "OX",   "\xc2\xa4" },	/* currency */
    { "O^",   "\xc3\x94" },	/* Ocircumflex */
    { "O_",   "\xc5\x8c" },	/* Omacron */
    { "O`",   "\xc3\x92" },	/* Ograve */
    { "Oc",   "\xc2\xa9" },	/* copyright */
    { "Ox",   "\xc2\xa4" },	/* currency */
    { "O~",   "\xc3\x95" },	/* Otilde */
    { "P!",   "\xc2\xb6" },	/* paragraph */
    { "R'",   "\xc5\x94" },	/* Racute */
    { "R,",   "\xc5\x96" },	/* Rcedilla */
    { "RO",   "\xc2\xae" },	/* registered */
    { "Rv",   "\xc5\x98" },	/* Rcaron */
    { "S!",   "\xc2\xa7" },	/* section */
    { "S'",   "\xc5\x9a" },	/* Sacute */
    { "S,",   "\xc5\x9e" },	/* Scedilla */
    { "S0",   "\xc2\xa7" },	/* section */
    { "S1",   "\xc2\xb9" },	/* onesuperior */
    { "S2",   "\xc2\xb2" },	/* twosuperior */
    { "S3",   "\xc2\xb3" },	/* threesuperior */
    { "SO",   "\xc2\xa7" },	/* section */
    { "SV",   "\xc5\xa0" },	/* Scaron */
    { "Sv",   "\xc5\xa0" },	/* Scaron */
    { "T,",   "\xc5\xa2" },	/* Tcedilla */
    { "TH",   "\xc3\x9e" },	/* THORN */
    { "Tv",   "\xc5\xa4" },	/* Tcaron */
    { "T|",   "\xc5\xa6" },	/* Tslash */
    { "U\"",  "\xc3\x9c" },	/* Udiaeresis */
    { "U'",   "\xc3\x9a" },	/* Uacute */
    { "U*",   "\xc5\xae" },	/* Uring */
    { "U.",   "\xc5\xae" },	/* Uring */
    { "U/",   "\xc2\xb5" },	/* mu */
    { "U>",   "\xc3\x9b" },	/* Ucircumflex */
    { "U^",   "\xc3\x9b" },	/* Ucircumflex */
    { "U_",   "\xc5\xaa" },	/* Umacron */
    { "U`",   "\xc3\x99" },	/* Ugrave */
    { "Ua",   "\xc5\xb2" },	/* Uogonek */
    { "Uv",   "\xc5\xae" },	/* Uring */
    { "U~",   "\xc5\xa8" },	/* Utilde */
    { "VB",   "\xc2\xa6" },	/* brokenbar */
    { "VL",   "|"        },	/* bar */
    { "VS",   "\xc5\xa0" },	/* Scaron */
    { "Vs",   "\xc5\xa1" },	/* scaron */
    { "X0",   "\xc2\xa4" },	/* currency */
    { "XO",   "\xc2\xa4" },	/* currency */
    { "Xo",   "\xc2\xa4" },	/* currency */
    { "Y\"",  "\xc5\xb8" },
    { "Y'",   "\xc3\x9d" },	/* Yacute */
    { "Y-",   "\xc2\xa5" },	/* yen */
    { "Y=",   "\xc2\xa5" },	/* yen */
    { "Z'",   "\xc5\xb9" },	/* Zacute */
    { "Z.",   "\xc5\xbb" },	/* Zabovedot */
    { "Zv",   "\xc5\xbd" },	/* Zcaron */
    { "^ ",   "^"        },	/* asciicircum */
    { "^!",   "\xc2\xa6" },	/* brokenbar */
    { "^-",   "\xc2\xaf" },	/* macron */
    { "^.",   "\xc2\xb7" },	/* periodcentered */
    { "^/",   "|"        },	/* bar */
    { "^0",   "\xc2\xb0" },	/* degree */
    { "^1",   "\xc2\xb9" },	/* onesuperior */
    { "^2",   "\xc2\xb2" },	/* twosuperior */
    { "^3",   "\xc2\xb3" },	/* threesuperior */
    { "^A",   "\xc3\x82" },	/* Acircumflex */
    { "^E",   "\xc3\x8a" },	/* Ecircumflex */
    { "^I",   "\xc3\x8e" },	/* Icircumflex */
    { "^O",   "\xc3\x94" },	/* Ocircumflex */
    { "^U",   "\xc3\x9b" },	/* Ucircumflex */
    { "^_",   "\xc2\xaf" },	/* macron */
    { "^a",   "\xc3\xa2" },	/* acircumflex */
    { "^e",   "\xc3\xaa" },	/* ecircumflex */
    { "^i",   "\xc3\xae" },	/* icircumflex */
    { "^o",   "\xc3\xb4" },	/* ocircumflex */
    { "^u",   "\xc3\xbb" },	/* ucircumflex */
    { "_A",   "\xc4\x80" },	/* Amacron */
    { "_E",   "\xc4\x92" },	/* Emacron */
    { "_I",   "\xc4\xaa" },	/* Imacron */
    { "_O",   "\xc5\x8c" },	/* Omacron */
    { "_U",   "\xc5\xaa" },	/* Umacron */
    { "_^",   "\xc2\xaf" },	/* macron */
    { "__",   "\xc2\xaf" },	/* macron */
    { "_a",   "\xc4\x81" },	/* amacron */
    { "_d",   "\xc4\x91" },
    { "_e",   "\xc4\x93" },	/* emacron */
    { "_i",   "\xc4\xab" },	/* imacron */
    { "_o",   "\xc5\x8d" },	/* omacron */
    { "_u",   "\xc5\xab" },	/* umacron */
    { "` ",   "`"        },	/* grave */
    { "`A",   "\xc3\x80" },	/* Agrave */
    { "`E",   "\xc3\x88" },	/* Egrave */
    { "`I",   "\xc3\x8c" },	/* Igrave */
    { "`O",   "\xc3\x92" },	/* Ograve */
    { "`U",   "\xc3\x99" },	/* Ugrave */
    { "`a",   "\xc3\xa0" },	/* agrave */
    { "`e",   "\xc3\xa8" },	/* egrave */
    { "`i",   "\xc3\xac" },	/* igrave */
    { "`o",   "\xc3\xb2" },	/* ograve */
    { "`u",   "\xc3\xb9" },	/* ugrave */
    { "a ",   "\xcb\x9b" },	/* ogonek */
    { "a\"",  "\xc3\xa4" },	/* adiaeresis */
    { "a'",   "\xc3\xa1" },	/* aacute */
    { "a*",   "\xc3\xa5" },	/* aring */
    { "a-",   "\xc2\xaa" },	/* ordfeminine */
    { "a>",   "\xc3\xa2" },	/* acircumflex */
    { "aA",   "\xc4\x84" },	/* Aogonek */
    { "aI",   "\xc4\xae" },	/* Iogonek */
    { "a^",   "\xc3\xa2" },	/* acircumflex */
    { "a_",   "\xc4\x81" },	/* amacron */
    { "a`",   "\xc3\xa0" },	/* agrave */
    { "aa",   "\xc4\x85" },	/* aogonek */
    { "ae",   "\xc3\xa6" },	/* ae */
    { "ai",   "\xc4\xaf" },	/* iogonek */
    { "au",   "\xc4\x83" },	/* abreve */
    { "a~",   "\xc3\xa3" },	/* atilde */
    { "bv",   "\xc2\xa6" },	/* brokenbar */
    { "c'",   "\xc4\x87" },	/* cacute */
    { "c,",   "\xc3\xa7" },	/* ccedilla */
    { "c/",   "\xc2\xa2" },	/* cent */
    { "c0",   "\xc2\xa9" },	/* copyright */
    { "cO",   "\xc2\xa9" },	/* copyright */
    { "co",   "\xc2\xa9" },	/* copyright */
    { "cv",   "\xc4\x8d" },	/* ccaron */
    { "c|",   "\xc2\xa2" },	/* cent */
    { "d-",   "\xc3\xb0" },	/* eth */
    { "d_",   "\xc4\x91" },
    { "dv",   "\xc4\x8f" },	/* dcaron */
    { "e\"",  "\xc3\xab" },	/* ediaeresis */
    { "e'",   "\xc3\xa9" },	/* eacute */
    { "e.",   "\xc4\x97" },	/* eabovedot */
    { "e>",   "\xc3\xaa" },	/* ecircumflex */
    { "e^",   "\xc3\xaa" },	/* ecircumflex */
    { "e_",   "\xc4\x93" },	/* emacron */
    { "e`",   "\xc3\xa8" },	/* egrave */
    { "ea",   "\xc4\x99" },	/* eogonek */
    { "ev",   "\xc4\x9b" },	/* ecaron */
    { "g,",   "\xc4\xa3" },	/* gcedilla */
    { "gu",   "\xc4\x9f" },	/* gbreve */
    { "i\"",  "\xc3\xaf" },	/* idiaeresis */
    { "i'",   "\xc3\xad" },	/* iacute */
    { "i.",   "\xc4\xb1" },	/* idotless */
    { "i>",   "\xc3\xae" },	/* icircumflex */
    { "i^",   "\xc3\xae" },	/* icircumflex */
    { "i_",   "\xc4\xab" },	/* imacron */
    { "i`",   "\xc3\xac" },	/* igrave */
    { "ia",   "\xc4\xaf" },	/* iogonek */
    { "i~",   "\xc4\xa9" },	/* itilde */
    { "k,",   "\xc4\xb7" },	/* kcedilla */
    { "kk",   "\xc4\xb8" },	/* kra */
    { "l'",   "\xc4\xba" },	/* lacute */
    { "l,",   "\xc4\xbc" },	/* lcedilla */
    { "l-",   "\xc2\xa3" },	/* sterling */
    { "l/",   "\xc5\x82" },	/* lstroke */
    { "l=",   "\xc2\xa3" },	/* sterling */
    { "l>",   "\xc4\xbe" },	/* lcaron */
    { "lv",   "|"        },	/* bar */
    { "n'",   "\xc5\x84" },	/* nacute */
    { "n,",   "\xc5\x86" },	/* ncedilla */
    { "n-",   "\xc3\xb1" },	/* ntilde */
    { "nn",   "\xc5\x8b" },	/* eng */
    { "nv",   "\xc5\x88" },	/* ncaron */
    { "n~",   "\xc3\xb1" },	/* ntilde */
    { "o\"",  "\xc3\xb6" },	/* odiaeresis */
    { "o'",   "\xc3\xb3" },	/* oacute */
    { "o-",   "\xc2\xba" },	/* masculine */
    { "o/",   "\xc3\xb8" },	/* oslash */
    { "o>",   "\xc3\xb4" },	/* ocircumflex */
    { "oC",   "\xc2\xa9" },	/* copyright */
    { "oX",   "\xc2\xa4" },	/* currency */
    { "o^",   "\xc3\xb4" },	/* ocircumflex */
    { "o_",   "\xc5\x8d" },	/* omacron */
    { "o`",   "\xc3\xb2" },	/* ograve */
    { "oc",   "\xc2\xa9" },	/* copyright */
    { "oe",   "\xc5\x93" },
    { "oo",   "\xc2\xb0" },	/* degree */
    { "os",   "\xc2\xa7" },	/* section */
    { "ox",   "\xc2\xa4" },	/* currency */
    { "o~",   "\xc3\xb5" },	/* otilde */
    { "p!",   "\xc2\xb6" },	/* paragraph */
    { "r'",   "\xc5\x95" },	/* racute */
    { "r,",   "\xc5\x97" },	/* rcedilla */
    { "rv",   "\xc5\x99" },	/* rcaron */
    { "s!",   "\xc2\xa7" },	/* section */
    { "s'",   "\xc5\x9b" },	/* sacute */
    { "s,",   "\xc5\x9f" },	/* scedilla */
    { "s0",   "\xc2\xa7" },	/* section */
    { "s1",   "\xc2\xb9" },	/* onesuperior */
    { "s2",   "\xc2\xb2" },	/* twosuperior */
    { "s3",   "\xc2\xb3" },	/* threesuperior */
    { "sV",   "\xc5\xa1" },	/* scaron */
    { "so",   "\xc2\xa7" },	/* section */
    { "ss",   "\xc3\x9f" },	/* ssharp */
    { "sv",   "\xc5\xa1" },	/* scaron */
    { "t,",   "\xc5\xa3" },	/* tcedilla */
    { "th",   "\xc3\xbe" },	/* thorn */
    { "tv",   "\xc5\xa5" },	/* tcaron */
    { "t|",   "\xc5\xa7" },	/* tslash */
    { "u ",   "\xcb\x98" },	/* breve */
    { "u\"",  "\xc3\xbc" },	/* udiaeresis */
    { "u'",   "\xc3\xba" },	/* uacute */
    { "u*",   "\xc5\xaf" },	/* uring */
    { "u.",   "\xc5\xaf" },	/* uring */
    { "u/",   "\xc2\xb5" },	/* mu */
    { "u>",   "\xc3\xbb" },	/* ucircumflex */
    { "uG",   "\xc4\x9e" },	/* Gbreve */
    { "u^",   "\xc3\xbb" },	/* ucircumflex */
    { "u_",   "\xc5\xab" },	/* umacron */
    { "u`",   "\xc3\xb9" },	/* ugrave */
    { "ua",   "\xc5\xb3" },	/* uogonek */
    { "ug",   "\xc4\x9f" },	/* gbreve */
    { "uv",   "\xc5\xaf" },	/* uring */
    { "u~",   "\xc5\xa9" },	/* utilde */
    { "v ",   "\xcb\x87" },	/* caron */
    { "vC",   "\xc4\x8c" },	/* Ccaron */
    { "vD",   "\xc4\x8e" },	/* Dcaron */
    { "vE",   "\xc4\x9a" },	/* Ecaron */
    { "vN",   "\xc5\x87" },	/* Ncaron */
    { "vR",   "\xc5\x98" },	/* Rcaron */
    { "vS",   "\xc5\xa0" },	/* Scaron */
    { "vT",   "\xc5\xa4" },	/* Tcaron */
    { "vU",   "\xc5\xae" },	/* Uring */
    { "vZ",   "\xc5\xbd" },	/* Zcaron */
    { "vb",   "\xc2\xa6" },	/* brokenbar */
    { "vc",   "\xc4\x8d" },	/* ccaron */
    { "vd",   "\xc4\x8f" },	/* dcaron */
    { "ve",   "\xc4\x9b" },	/* ecaron */
    { "vl",   "|"        },	/* bar */
    { "vn",   "\xc5\x88" },	/* ncaron */
    { "vr",   "\xc5\x99" },	/* rcaron */
    { "vs",   "\xc5\xa1" },	/* scaron */
    { "vt",   "\xc5\xa5" },	/* tcaron */
    { "vu",   "\xc5\xaf" },	/* uring */
    { "vz",   "\xc5\xbe" },	/* zcaron */
    { "x0",   "\xc2\xa4" },	/* currency */
    { "xO",   "\xc2\xa4" },	/* currency */
    { "xo",   "\xc2\xa4" },	/* currency */
    { "xx",   "\xc3\x97" },	/* multiply */
    { "y\"",  "\xc3\xbf" },	/* ydiaeresis */
    { "y'",   "\xc3\xbd" },	/* yacute */
    { "y-",   "\xc2\xa5" },	/* yen */
    { "y=",   "\xc2\xa5" },	/* yen */
    { "z'",   "\xc5\xba" },	/* zacute */
    { "z.",   "\xc5\xbc" },	/* zabovedot */
    { "zv",   "\xc5\xbe" },	/* zcaron */
    { "|C",   "\xc2\xa2" },	/* cent */
    { "|T",   "\xc5\xa6" },	/* Tslash */
    { "|c",   "\xc2\xa2" },	/* cent */
    { "|t",   "\xc5\xa7" },	/* tslash */
    { "||",   "\xc2\xa6" },	/* brokenbar */
    { "~ ",   "~"        },	/* asciitilde */
    { "~A",   "\xc3\x83" },	/* Atilde */
    { "~I",   "\xc4\xa8" },	/* Itilde */
    { "~N",   "\xc3\x91" },	/* Ntilde */
    { "~O",   "\xc3\x95" },	/* Otilde */
    { "~U",   "\xc5\xa8" },	/* Utilde */
    { "~a",   "\xc3\xa3" },	/* atilde */
    { "~i",   "\xc4\xa9" },	/* itilde */
    { "~n",   "\xc3\xb1" },	/* ntilde */
    { "~o",   "\xc3\xb5" },	/* otilde */
    { "~u",   "\xc5\xa9" },	/* utilde */
};

static const Transliteration cyrillic_transl[] = {
    { '"',  "\xd0\xad" },	/* Cyrillic_E */
    { '#',  "\xe2\x84\x96" },	/* numerosign */
    { '$',  "%"        },	/* percent */
    { '%',  ":"        },	/* colon */
    { '&',  "."        },	/* period */
    { '\'', "\xd1\x8d" },	/* Cyrillic_e */
    { '*',  ";"        },	/* semicolon */
    { ',',  "\xd0\xb1" },	/* Cyrillic_be */
    { '.',  "\xd1\x8e" },	/* Cyrillic_yu */
    { '/',  "\xd1\x91" },	/* Cyrillic_io */
    { ':',  "\xd0\x96" },	/* Cyrillic_GHE */
    { ';',  "\xd0\xb6" },	/* Cyrillic_ghe */
    { '<',  "\xd0\x91" },	/* Cyrillic_BE */
    { '>',  "\xd0\xae" },	/* Cyrillic_YU */
    { '?',  "\xd0\x81" },	/* Cyrillic_IO */
    { '@',  "\""       },	/* quotedbl */
    { 'A',  "\xd0\xa4" },	/* Cyrillic_EF */
    { 'B',  "\xd0\x98" },	/* Cyrillic_I */
    { 'C',  "\xd0\xa1" },	/* Cyrillic_ES */
    { 'D',  "\xd0\x92" },	/* Cyrillic_VE */
    { 'E',  "\xd0\xa3" },	/* Cyrillic_U */
    { 'F',  "\xd0\x90" },	/* Cyrillic_A */
    { 'G',  "\xd0\x9f" },	/* Cyrillic_PE */
    { 'H',  "\xd0\xa0" },	/* Cyrillic_ER */
    { 'I',  "\xd0\xa8" },	/* Cyrillic_SHA */
    { 'J',  "\xd0\x9e" },	/* Cyrillic_O */
    { 'K',  "\xd0\x9b" },	/* Cyrillic_EL */
    { 'L',  "\xd0\x94" },	/* Cyrillic_DE */
    { 'M',  "\xd0\xac" },	/* Cyrillic_SOFTSIGN */
    { 'N',  "\xd0\xa2" },	/* Cyrillic_TE */
    { 'O',  "\xd0\xa9" },	/* Cyrillic_SHCHA */
    { 'P',  "\xd0\x97" },	/* Cyrillic_ZE */
    { 'Q',  "\xd0\x99" },	/* Cyrillic_SHORTI */
    { 'R',  "\xd0\x9a" },	/* Cyrillic_KA */
    { 'S',  "\xd0\xab" },	/* Cyrillic_YERU */
    { 'T',  "\xd0\x95" },	/* Cyrillic_IE */
    { 'U',  "\xd0\x93" },	/* Cyrillic_GHE */
    { 'V',  "\xd0\x9c" },	/* Cyrillic_EM */
    { 'W',  "\xd0\xa6" },	/* Cyrillic_TSE */
    { 'X',  "\xd0\xa7" },	/* Cyrillic_CHE */
    { 'Y',  "\xd0\x9d" },	/* Cyrillic_EN */
    { 'Z',  "\xd0\xaf" },	/* Cyrillic_YA */
    { '[',  "\xd1\x85" },	/* Cyrillic_ha */
    { ']',  "\xd1\x8a" },	/* Cyrillic_hardsign */
    { '^',  ","        },	/* comma */
    { 'a',  "\xd1\x84" },	/* Cyrillic_ef */
    { 'b',  "\xd0\xb8" },	/* Cyrillic_i */
    { 'c',  "\xd1\x81" },	/* Cyrillic_es */
    { 'd',  "\xd0\xb2" },	/* Cyrillic_ve */
    { 'e',  "\xd1\x83" },	/* Cyrillic_u */
    { 'f',  "\xd0\xb0" },	/* Cyrillic_a */
    { 'g',  "\xd0\xbf" },	/* Cyrillic_pe */
    { 'h',  "\xd1\x80" },	/* Cyrillic_er */
    { 'i',  "\xd1\x88" },	/* Cyrillic_sha */
    { 'j',  "\xd0\xbe" },	/* Cyrillic_o */
    { 'k',  "\xd0\xbb" },	/* Cyrillic_el */
    { 'l',  "\xd0\xb4" },	/* Cyrillic_de */
    { 'm',  "\xd1\x8c" },	/* Cyrillic_softsign */
    { 'n',  "\xd1\x82" },	/* Cyrillic_te */
    { 'o',  "\xd1\x89" },	/* Cyrillic_shcha */
    { 'p',  "\xd0\xb7" },	/* Cyrillic_ze */
    { 'q',  "\xd0\xb9" },	/* Cyrillic_shorti */
    { 'r',  "\xd0\xba" },	/* Cyrillic_ka */
    { 's',  "\xd1\x8b" },	/* Cyrillic_yeru */
    { 't',  "\xd0\xb5" },	/* Cyrillic_ie */
    { 'u',  "\xd0\xb3" },	/* Cyrillic_ghe */
    { 'v',  "\xd0\xbc" },	/* Cyrillic_em */
    { 'w',  "\xd1\x86" },	/* Cyrillic_tse */
    { 'x',  "\xd1\x87" },	/* Cyrillic_che */
    { 'y',  "\xd0\xbd" },	/* Cyrillic_en */
    { 'z',  "\xd1\x8f" },	/* Cyrillic_ya */
    { '{',  "\xd0\xa5" },	/* Cyrillic_HA */
    /*'[',  "\xd0\xa5"   	 L-Cyrillic_HA */
    { '}',  "\xd0\xaa" },	/* Cyrillic_HARDSIGN */
    /*']',  "\xd0\xaa"   	 L-Cyrillic_HARDSIGN */
};

static const Transliteration greek_transl[] = {
    { '#', "\xcf\x80" },	/* numerosign */
    { '$', "%"        },	/* percent */
    { '%', ":"        },	/* colon */
    { '&', "."        },	/* period */
    { '*', ";"        },	/* semicolon */
    { '<', ";"        },	/* semicolon */
    { '>', ":"        },	/* colon */
    { '?', "\xc2\xb7" },	/* periodcentered */
    { '@', "\""       },	/* quotedbl */
    { 'A', "\xce\x91" },	/* Greek_ALPHA */
    { 'B', "\xce\x92" },	/* Greek_BETA */
    { 'C', "\xce\xa8" },	/* Greek_PSI */
    { 'D', "\xce\x94" },	/* Greek_DELTA */
    { 'E', "\xce\x95" },	/* Greek_EPSILON */
    { 'F', "\xce\xa6" },	/* Greek_PHI */
    { 'G', "\xce\x93" },	/* Greek_GAMMA */
    { 'H', "\xce\x97" },	/* Greek_ETA */
    { 'I', "\xce\x99" },	/* Greek_IOTA */
    { 'J', "\xce\x9e" },	/* Greek_XI */
    { 'K', "\xce\x9a" },	/* Greek_KAPPA */
    { 'L', "\xce\x9b" },	/* Greek_LAMDA */
    { 'M', "\xce\x9c" },	/* Greek_MU */
    { 'N', "\xce\x9d" },	/* Greek_NU */
    { 'O', "\xce\x9f" },	/* Greek_OMICRON */
    { 'P', "\xce\xa0" },	/* Greek_PI */
    { 'Q', ":"        },	/* colon */
    { 'R', "\xce\xa1" },	/* Greek_RHO */
    { 'S', "\xce\xa3" },	/* Greek_SIGMA */
    { 'T', "\xce\xa4" },	/* Greek_TAU */
    { 'U', "\xce\x98" },	/* Greek_THETA */
    { 'V', "\xce\xa9" },	/* Greek_OMEGA */
    { 'W', "\xce\xa3" },	/* Greek_SIGMA */
    { 'X', "\xce\xa7" },	/* Greek_CHI */
    { 'Y', "\xce\xa5" },	/* Greek_UPSILON */
    { 'Z', "\xce\x96" },	/* Greek_ZETA */
    { '^', ","        },	/* comma */
    { 'a', "\xce\xb1" },	/* Greek_alpha */
    { 'b', "\xce\xb2" },	/* Greek_beta */
    { 'c', "\xcf\x88" },	/* Greek_psi */
    { 'd', "\xce\xb4" },	/* Greek_delta */
    { 'e', "\xce\xb5" },	/* Greek_epsilon */
    { 'f', "\xcf\x86" },	/* Greek_phi */
    { 'g', "\xce\xb3" },	/* Greek_gamma */
    { 'h', "\xce\xb7" },	/* Greek_eta */
    { 'i', "\xce\xb9" },	/* Greek_iota */
    { 'j', "\xce\xbe" },	/* Greek_xi */
    { 'k', "\xce\xba" },	/* Greek_kappa */
    { 'l', "\xce\xbb" },	/* Greek_lamda */
    { 'm', "\xce\xbc" },	/* Greek_mu */
    { 'n', "\xce\xbd" },	/* Greek_nu */
    { 'o', "\xce\xbf" },	/* Greek_omicron */
    { 'p', "\xcf\x80" },	/* Greek_pi */
    { 'q', ";"        },	/* semicolon */
    { 'r', "\xcf\x81" },	/* Greek_rho */
    { 's', "\xcf\x83" },	/* Greek_finalsmallsigma */
    { 't', "\xcf\x84" },	/* Greek_tau */
    { 'u', "\xce\xb8" },	/* Greek_theta */
    { 'v', "\xcf\x89" },	/* Greek_omega */
    { 'w', "\xcf\x82" },	/* Greek_sigma */
    { 'x', "\xcf\x87" },	/* Greek_chi */
    { 'y', "\xcf\x85" },	/* Greek_upsilon */
    { 'z', "\xce\xb6" },	/* Greek_zeta */
};

static const Transliteration thai_transl[] = {
    { '!',  "+"            },
    { '"',  "."            },
    { '#',  "\xe0\xb9\x92" },
    { '$',  "\xe0\xb9\x93" },
    { '%',  "\xe0\xb9\x94" },
    { '&',  "\xe0\xb8\xbf" },
    { '\'', "\xe0\xb8\x87" },
    { '(',  "\xe0\xb9\x96" },
    { ')',  "\xe0\xb9\x97" },
    { '*',  "\xe0\xb9\x95" },
    { '+',  "\xe0\xb9\x99" },
    { ',',  "\xe0\xb8\xa1" },
    { '-',  "\xe0\xb8\x82" },
    { '.',  "\xe0\xb9\x83" },
    { '/',  "\xe0\xb8\x9d" },
    { '0',  "\xe0\xb8\x88" },
    { '1',  "\xe0\xb9\x85" },
    { '2',  "/"            },
    { '3',  "-"            },
    { '4',  "\xe0\xb8\xa0" },
    { '5',  "\xe0\xb8\x96" },
    { '6',  "\xe0\xb8\xb8" },
    { '7',  "\xe0\xb8\xb6" },
    { '8',  "\xe0\xb8\x84" },
    { '9',  "\xe0\xb8\x95" },
    { ':',  "\xe0\xb8\x8b" },
    { ';',  "\xe0\xb8\xa7" },
    { '<',  "\xe0\xb8\x92" },
    { '=',  "\xe0\xb8\x8a" },
    { '>',  "\xe0\xb8\xac" },
    { '?',  "\xe0\xb8\xa6" },
    { '@',  "\xe0\xb9\x91" },
    { 'A',  "\xe0\xb8\xa4" },
    { 'B',  "\xe0\xb8\xba" },
    { 'C',  "\xe0\xb8\x89" },
    { 'D',  "\xe0\xb8\x8f" },
    { 'E',  "\xe0\xb8\x8e" },
    { 'F',  "\xe0\xb9\x82" },
    { 'G',  "\xe0\xb8\x8c" },
    { 'H',  "\xe0\xb9\x87" },
    { 'I',  "\xe0\xb8\x93" },
    { 'J',  "\xe0\xb9\x8b" },
    { 'K',  "\xe0\xb8\xa9" },
    { 'L',  "\xe0\xb8\xa8" },
    { 'M',  "?"            },
    { 'N',  "\xe0\xb9\x8c" },
    { 'O',  "\xe0\xb8\xaf" },
    { 'P',  "\xe0\xb8\x8d" },
    { 'Q',  "\xe0\xb9\x90" },
    { 'R',  "\xe0\xb8\x91" },
    { 'S',  "\xe0\xb8\x86" },
    { 'T',  "\xe0\xb8\x98" },
    { 'U',  "\xe0\xb9\x8a" },
    { 'V',  "\xe0\xb8\xae" },
    { 'W',  "\""           },
    { 'X',  ")"            },
    { 'Y',  "\xe0\xb9\x8d" },
    { 'Z',  "("            },
    { '[',  "\xe0\xb8\x9a" },
    { '\\', "_"            },
    { ']',  "\xe0\xb8\xa5" },
    { '^',  "\xe0\xb8\xb9" },
    { '_',  "\xe0\xb9\x98" },
    { '`',  "\xe0\xb8\x83" },
    { 'a',  "\xe0\xb8\x9f" },
    { 'b',  "\xe0\xb8\xb4" },
    { 'c',  "\xe0\xb9\x81" },
    { 'd',  "\xe0\xb8\x81" },
    { 'e',  "\xe0\xb8\xb3" },
    { 'f',  "\xe0\xb8\x94" },
    { 'g',  "\xe0\xb9\x80" },
    { 'h',  "\xe0\xb9\x89" },
    { 'i',  "\xe0\xb8\xa3" },
    { 'j',  "\xe0\xb9\x88" },
    { 'k',  "\xe0\xb8\xb2" },
    { 'l',  "\xe0\xb8\xaa" },
    { 'm',  "\xe0\xb8\x97" },
    { 'n',  "\xe0\xb8\xb7" },
    { 'o',  "\xe0\xb8\x99" },
    { 'p',  "\xe0\xb8\xa2" },
    { 'q',  "\xe0\xb9\x86" },
    { 'r',  "\xe0\xb8\x9e" },
    { 's',  "\xe0\xb8\xab" },
    { 't',  "\xe0\xb8\xb0" },
    { 'u',  "\xe0\xb8\xb5" },
    { 'v',  "\xe0\xb8\xad" },
    { 'w',  "\xe0\xb9\x84" },
    { 'x',  "\xe0\xb8\x9b" },
    { 'y',  "\xe0\xb8\xb1" },
    { 'z',  "\xe0\xb8\x9c" },
    { '{',  "\xe0\xb8\x90" },
    { '|',  "%"            },
    { '}',  ","            },
    { '~',  "\xe0\xb8\x85" },
};

static const Transliteration arabic_transl[] = {
    { '"',  "\xd8\xa2" },
    { '\'', "\xd8\xa3" },
    { '.',  "\xd8\x8c" },
    { '0',  "\xd9\xa0" },
    { '1',  "\xd9\xa1" },
    { '2',  "\xd9\xa2" },
    { '3',  "\xd9\xa3" },
    { '4',  "\xd9\xa4" },
    { '5',  "\xd9\xa5" },
    { '6',  "\xd9\xa6" },
    { '7',  "\xd9\xa7" },
    { '8',  "\xd9\xa8" },
    { '9',  "\xd9\xa9" },
    { ';',  "\xd9\x83" },
    { '?',  "\xd8\x9f" },
    { 'A',  "\xd9\x90" },
    { 'D',  "\xd8\xa6" },
    { 'E',  "\xd9\x8f" },
    { 'G',  "\xd8\xa5" },
    { 'H',  "\xd8\xa1" },
    { 'J',  "\xd8\xa9" },
    { 'K',  "\xd9\x89" },
    { 'M',  "\xd8\xa4" },
    { 'N',  "\xd8\x9b" },
    { 'Q',  "\xd9\x8e" },
    { 'R',  "\xd9\x8c" },
    { 'S',  "\xd9\x8d" },
    { 'W',  "\xd9\x8b" },
    { 'X',  "\xd9\x92" },
    { '[',  "\xd8\xac" },
    { ']',  "\xd9\x80" },
    { 'a',  "\xd8\xb4" },
    { 'b',  "\xd8\xb2" },
    { 'c',  "\xd8\xb0" },
    { 'd',  "\xd9\x8a" },
    { 'e',  "\xd8\xab" },
    { 'f',  "\xd8\xa8" },
    { 'g',  "\xd9\x84" },
    { 'h',  "\xd8\xa7" },
    { 'i',  "\xd9\x87" },
    { 'j',  "\xd8\xaa" },
    { 'k',  "\xd9\x86" },
    { 'l',  "\xd9\x85" },
    { 'm',  "\xd9\x88" },
    { 'n',  "\xd8\xb1" },
    { 'o',  "\xd8\xae" },
    { 'p',  "\xd8\xad" },
    { 'q',  "\xd8\xb6" },
    { 'r',  "\xd9\x82" },
    { 's',  "\xd8\xb3" },
    { 't',  "\xd9\x81" },
    { 'u',  "\xd8\xb9" },
    { 'v',  "\xd8\xaf" },
    { 'w',  "\xd8\xb5" },
    { 'x',  "\xd8\xb7" },
    { 'y',  "\xd8\xba" },
    { 'z',  "\xd8\xb8" },
    { '~',  "\xd9\x91" },
};

static const Transliteration hebrew_transl[] = {
    { '\'', ","        },
    { ',',  "\xd7\xaa" },
    { '.',  "\xd7\xa5" },
    { '/',  "/"        },
    { ';',  "\xd7\xa3" },
    { '`',  ";"        },
    { 'a',  "\xd7\xa9" },
    { 'b',  "\xd7\xa0" },
    { 'c',  "\xd7\x91" },
    { 'd',  "\xd7\x92" },
    { 'e',  "\xd7\xa7" },
    { 'f',  "\xd7\x9b" },
    { 'g',  "\xd7\xa2" },
    { 'h',  "\xd7\x99" },
    { 'i',  "\xd7\x9f" },
    { 'j',  "\xd7\x97" },
    { 'k',  "\xd7\x9c" },
    { 'l',  "\xd7\x9a" },
    { 'm',  "\xd7\xa6" },
    { 'n',  "\xd7\x9e" },
    { 'o',  "\xd7\x9d" },
    { 'p',  "\xd7\xa4" },
    { 'q',  "/"        },
    { 'r',  "\xd7\xa8" },
    { 's',  "\xd7\x93" },
    { 't',  "\xd7\x90" },
    { 'u',  "\xd7\x95" },
    { 'v',  "\xd7\x94" },
    { 'w',  "'"        },
    { 'x',  "\xd7\xa1" },
    { 'y',  "\xd7\x98" },
    { 'z',  "\xd7\x96" },
};

