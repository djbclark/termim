/***************************************************************************
 * Terminal Input Method
 * (C) Nicolas George, 2002-11-03
 * im_tonepy.c: tonepy input method
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

typedef unsigned short ushort;
typedef struct {
    const char *name;
    const ushort *code;
    int n;
} Tonepy;

#include "tonepy_data.inc"
#define tpd tonepy_data
#define ntpd (sizeof(tpd) / sizeof(*tpd))

static int offset, min, max, block;

static void
tonepy_init(void)
{
    offset = 0;
    min = 0;
    max = ntpd - 1;
    block = 0;
}

static void
print_choices(FILE *say)
{
    if(min == max) {
	const Tonepy *d;
	int i;
	char utf8[8];

	d = &tpd[min];
	fprintf(say, "%s %d/%d %c ", d->name, block / 10 + 1, (d->n + 9) / 10,
	    block == 0 ? ' ' : '<');
	for(i = 0; i < 10 && i + block < tpd[min].n; i++) {
	    to_utf8(d->code[block + i], utf8);
	    fprintf(say, "%c.%s ", '0' + (i + 1) % 10, utf8);
	}
	if(block + 10 < d->n)
	    fputc('>', say);
    } else {
	unsigned c, oc = 0, d;

	fwrite(tpd[min].name, 1, offset, say);
	fputc('[', say);
	for(d = min; d <= max; d++) {
	    c = tpd[d].name[offset];
	    if(c != oc) {
		fputc(c, say);
		oc = c;
	    }
	}
	fputc(']', say);
    }
}

static void
insert_char(unsigned c, FILE *out)
{
    char utf8[8];

    to_utf8(c, utf8);
    fputs(utf8, out);
    tonepy_init();
}

static void
tonepy_feed(unsigned key, FILE *out)
{
    FILE *say;
    int d;

    if(offset == 0 && (key < 'a' || key > 'z')) {
	fputc(key, out);
	return;
    }
    if(key == 27 || key == 3 || key == 4 || key == 7) {
	status_line_say("");
	tonepy_init();
	if(key == 27)
	    fputc(27, out);
	return;
    }
    if(key == 127 || key == 8) {
	offset--;
	while(min > 0 &&
	    strncmp(tpd[min - 1].name, tpd[min].name, offset) == 0)
	    min--;
	while(max < ntpd - 1 &&
	    strncmp(tpd[max + 1].name, tpd[max].name, offset) == 0)
	    max++;
	say = status_line();
	print_choices(say);
	flush_status_line();
	return;
    }
    say = status_line();
    if(max == min) {
	if(key == ' ')
	    key = '1';
	if(key == '<' || key == ',') {
	    block = block > 10 ? block - 10 : 0;
	    print_choices(say);
	} else if(key == '>' || key == '.' || key == '\t') {
	    if(block + 10 < tpd[min].n)
		block += 10;
	    print_choices(say);
	} else if(key >= '0' && key <= '9' &&
	    block + (key - '0' + 9) % 10 < tpd[min].n) {
	    insert_char(tpd[min].code[block + (key - '0' + 9) % 10], out);
	} else {
	    fputc('\a', say);
	    tonepy_init();
	}
    } else {
	for(d = min; d <= max; d++)
	    if(tpd[d].name[offset] == key)
		break;
	if(d > max) {
	    fputc('\a', say);
	    print_choices(say);
	} else {
	    min = d;
	    for(d++; d <= max && tpd[d].name[offset] == key; d++);
	    max = d - 1;
	    offset++;
	    if(min == max && tpd[min].n == 1)
		insert_char(tpd[min].code[0], out);
	    else
		print_choices(say);
	}
    }
    flush_status_line();
}

KeyHandler handler_tonepy = { "tonepy", tonepy_init, tonepy_feed };
