/***************************************************************************
 * Terminal Input Method
 * (C) Nicolas George, 2002-11-16
 * im_compose.c: simple compose-like input method
 ***************************************************************************/

/*
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 *  1. Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *  3. The name of the author may not be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>
#include <string.h>

#include "termim.h"

typedef struct {
    const char *keys;
    const char *string;
} Compose;

typedef struct {
    unsigned key;
    const char *string;
} Transliteration; 

#include "compose_data.c"

typedef struct {
    const Compose *compose;
    const Transliteration *trans;
    unsigned short n_compose, n_trans;
} Language;

static const Language *lang;
static short min, max, compose;

/***************************************************************************/

static void
compose_init(void)
{
    compose = -1;
    min = 0;
}

static void
compose_feed(unsigned key, FILE *out)
{
    FILE *say;

    if(compose >= 0) {
	int d;

	for(d = min; d <= max && lang->compose[d].keys[compose] != key; d++);
	if(d > max) {
	    status_line_say("");
	    compose_init();
	    return;
	}
	min = d;
	for(; d <= max && lang->compose[d].keys[compose] == key; d++);
	max = d - 1;
	compose++;
	say = status_line();
	if(min == max && lang->compose[min].keys[compose] == 0) {
	    fputs(lang->compose[min].string, out);
	    compose_init();
	} else {
	    fputs("Compose-", say);
	    for(d = 0; d < compose; d++)
		fprintf(say, "%c-", lang->compose[min].keys[d]);
	}
	flush_status_line();
    } else if(key == SK_COMPOSE) {
	if(lang->compose == NULL) {
	    status_line_say("\a");
	} else {
	    compose = 0;
	    max = lang->n_compose - 1;
	    status_line_say("Compose-");
	}
    } else {
	if(lang->trans != NULL) {
	    int i;

	    for(i = 0; i < lang->n_trans; i++)
		if(lang->trans[i].key == key) {
		    fputs(lang->trans[i].string, out);
		    return;
		}
	}
	fputc(key, out);
    }
}

/***************************************************************************/

static const Language lang_western = {
    western_compose,
    NULL,
    sizeof(western_compose) / sizeof(Compose),
    0
};

static const Language lang_cyrillic = {
    NULL,
    cyrillic_transl,
    0,
    sizeof(cyrillic_transl) / sizeof(Transliteration)
};

static const Language lang_greek = {
    NULL,
    greek_transl,
    0,
    sizeof(greek_transl) / sizeof(Transliteration)
};

static const Language lang_thai = {
    NULL,
    thai_transl,
    0,
    sizeof(thai_transl) / sizeof(Transliteration)
};

static const Language lang_arabic = {
    NULL,
    arabic_transl,
    0,
    sizeof(arabic_transl) / sizeof(Transliteration)
};

static const Language lang_hebrew = {
    NULL,
    hebrew_transl,
    0,
    sizeof(hebrew_transl) / sizeof(Transliteration)
};

static void
compose_western_init(void)
{
    lang = &lang_western;
    compose_init();
}

static void
compose_cyrillic_init(void)
{
    lang = &lang_cyrillic;
    compose_init();
}

static void
compose_greek_init(void)
{
    lang = &lang_greek;
    compose_init();
}

static void
compose_thai_init(void)
{
    lang = &lang_thai;
    compose_init();
}

static void
compose_arabic_init(void)
{
    lang = &lang_arabic;
    compose_init();
}

static void
compose_hebrew_init(void)
{
    lang = &lang_hebrew;
    compose_init();
}

KeyHandler handler_western = { "western", compose_western_init, compose_feed };
KeyHandler handler_cyrillic = { "cyrillic", compose_cyrillic_init, compose_feed };
KeyHandler handler_greek = { "greek", compose_greek_init, compose_feed };
KeyHandler handler_thai = { "thai", compose_thai_init, compose_feed };
KeyHandler handler_arabic = { "arabic", compose_arabic_init, compose_feed };
KeyHandler handler_hebrew = { "hebrew", compose_hebrew_init, compose_feed };
