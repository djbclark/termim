/***************************************************************************
 * Terminal Input Method
 * (C) Nicolas George, 2002-11-03
 * config_file.c: config file parser
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
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>

#include "termim.h"
#include "config.h"

#ifndef TERMIMRC
# define TERMIMRC "/etc/termimrc"
#endif

typedef struct {
    SpecialKey key;
    const char *name;
} SpecialKeyName;

static const SpecialKeyName special_keys[] = {
    { SK_COMPOSE, "compose" }
};

static void
skip_spaces(unsigned char **p)
{
    while(isspace(**p))
	(*p)++;
}

static int
is_word(const unsigned char *w, unsigned char **p)
{
    int l;

    skip_spaces(p);
    l = strlen(w);
    if(strncmp(w, *p, l) != 0)
	return(0);
    if(!isspace((*p)[l]))
	return(0);
    *p += l;
    skip_spaces(p);
    return(1);
}

static int
hex_digit(unsigned char c)
{
    c |= 32;
    return(c >= '0' && c <= '9' ? c - '0' :
	c >= 'a' && c <= 'f' ? c - 'a' + 10 : -1);
}

static unsigned char *
get_string(unsigned char **p, int *l)
{
    unsigned char *r, *q;
    *l = 0;

    r = q = *p;
    skip_spaces(p);
    if(**p != '"')
	return(NULL);
    (*p)++;
    while(**p != '"') {
	switch(**p) {
	    case 0:
		return(NULL);

	    case '\\':
		(*p)++;
		switch(**p) {
		    case 'e': case 'E':
			*(q++) = '\033';
			(*l)++;
			(*p)++;
			break;
		    case 'n': case 'N':
			*(q++) = '\n';
			(*l)++;
			(*p)++;
			break;
		    case 'r': case 'R':
			*(q++) = '\r';
			(*l)++;
			(*p)++;
			break;
		    case 't': case 'T':
			*(q++) = '\t';
			(*l)++;
			(*p)++;
			break;
		    case '\\':
			*(q++) = '\\';
			(*l)++;
			(*p)++;
			break;
		    case '"':
			*(q++) = '"';
			(*l)++;
			(*p)++;
			break;
		    case 'x': case 'X':
			if(hex_digit((*p)[1]) < 0 || hex_digit((*p)[2]) < 0)
			    fprintf(stderr, "Invalid \\x sequence.\n");
			*(q++) = hex_digit((*p)[1]) * 16 + hex_digit((*p)[2]);
			(*l)++;
			(*p) += 3;
			break;
		    case 'u': case 'U':
			{
			    unsigned u = 0, lu;

			    for((*p)++; hex_digit(**p) >= 0; (*p)++)
				u = u * 16 + hex_digit(**p);
			    if(**p == '\\')
				(*p)++;
			    lu = to_utf8(u, q);
			    q += lu;
			    (*l) += lu;
			}
			break;
		    default:
			fprintf(stderr, "Unknown escape sequence.\n");
			return(NULL);
		}
		break;

	    default:
		*(q++) = *((*p)++);
		(*l)++;
		break;
	}
    }
    *q = 0;
    (*p)++;
    skip_spaces(p);
    return(r);
}

static unsigned
get_key(unsigned char **p)
{
    char *endl;
    unsigned char *end;
    unsigned key;
    int i;

    skip_spaces(p);
    for(end = *p; *end != 0 && !isspace(*end); end++);
    key = strtol(*p, &endl, 0);
    if((unsigned char *)endl != *p) {
	if(end != (unsigned char *)endl)
	    return((unsigned)-1);
	*p = end;
	skip_spaces(p);
	return(key);
    }
    for(i = 0; i < sizeof(special_keys) / sizeof(*special_keys); i++) {
	if(end - *p == strlen(special_keys[i].name) &&
	    memcmp(*p, special_keys[i].name, end - *p) == 0) {
	    *p = end;
	    skip_spaces(p);
	    return(special_keys[i].key);
	}
    }
    return((unsigned)-1);
}

static int
end_of_line(unsigned char **p)
{
    skip_spaces(p);
    return(**p == 0 || **p == '#');
}

static KeyHandler *
handler_by_name(const char *n)
{
    int i;
	
    for(i = 0; key_handlers[i] != NULL; i++)
	if(strcmp(key_handlers[i]->name, n) == 0)
	    break;
    return(key_handlers[i]);
}

static KeyBinding *
find_binding(KeyBindings *keys, unsigned key)
{
    int i;

    for(i = 0; i < keys->n; i++)
	if(keys->key[i].key == key)
	    return(&keys->key[i]);
    return(NULL);
}

static KeyBinding *
insert_key(KeyMap *map, const unsigned char *key, unsigned lkey)
{
    KeyBindings *bindings, **bindings_p;
    KeyBinding *bind;
    int i;

    bindings_p = &map->keys;
    bindings = *bindings_p;
    for(i = 0; i < lkey; i++) {
	bind = find_binding(bindings, key[i]);
	if(bind == NULL)
	    break;
	if(bind->action != KEY_ACTION_SUB_BINDING) {
	    fprintf(stderr, "Old prefix of length %d.\n", i);
	    return(NULL);
	}
	bindings_p = &bind->arg.binding;
	bindings = *bindings_p;
    }
    if(i == lkey) {
	fprintf(stderr, "New prefix of length %d.\n", i);
	return(NULL);
    }
    bindings = realloc(bindings,
	sizeof(KeyBindings) + bindings->n * sizeof(KeyBinding));
    *bindings_p = bindings;
    bind = &bindings->key[bindings->n];
    bindings->n++;
    for(; i < lkey; i++) {
	bind->key = key[i];
	if(i == lkey - 1)
	    continue;
	bind->action = KEY_ACTION_SUB_BINDING;
	bind->arg.binding = malloc(sizeof(KeyBindings));
	bind->arg.binding->n = 1;
	bind = &bind->arg.binding->key[0];
    }
    return(bind);
}

static KeyMap *
map_by_name(const char *name)
{
    KeyMap *m;

    for(m = key_maps; m != NULL; m = m->next)
	if(strcmp(m->name, name) == 0)
	    return(m);
    return(NULL);
}

static int
find_map_references(int l, KeyBindings *bindings)
{
    int i;
    KeyMap *m;

    for(i = 0; i < bindings->n; i++) {
	switch(bindings->key[i].action) {
	    case KEY_ACTION_SUB_BINDING:
		if(find_map_references(l + 1, bindings->key[i].arg.binding))
		    return(-1);
		break;
	    case KEY_ACTION_STRING:
		break;
	    case KEY_ACTION_KEY:
		break;
	    case KEY_ACTION_KEYS:
		break;
	    case KEY_ACTION_CHANGE_MAP:
		m = map_by_name(bindings->key[i].arg.ptr);
		if(m == NULL) {
		    fprintf(stderr, "Unknown map: %s\n",
			bindings->key[i].arg.ptr);
		    return(1);
		}
		free((char *)bindings->key[i].arg.string);
		bindings->key[i].arg.keymap = m;
		break;
	}
    }
    return(0);
}

static String *
alloc_string(const unsigned char *s, unsigned l)
{
    String *r;

    r = malloc(sizeof(String) + l);
    r->len = l;
    memcpy(r->str, s, l);
    r->str[l] = 0;
    return(r);
}

int
parse_config_file(void)
{
    FILE *config = NULL;
    unsigned char buffer[LINE_MAX], *p;
    int l, line = 0;
    KeyMap *map = NULL;
    int max = 0;

    {
	char file_name[PATH_MAX];
	char *home, *rc;

	rc = getenv("TERMIMRC");
	if(rc != NULL) {
	    config = fopen(rc, "rt");
	    if(config == NULL) {
		perror("$TERMIMRC");
		return(-1);
	    }
	} else {
	    home = getenv("HOME");
	    if(home == NULL) {
		fprintf(stderr, "$HOME not defined, using common config.\n");
	    } else {
		snprintf(file_name, sizeof(file_name), "%s/.termimrc", home);
		config = fopen(file_name, "rt");
		if(config == NULL)
		    perror("~/.termimrc");
		
	    }
	    if(config == NULL) {
		config = fopen(TERMIMRC, "rt");
		if(config == NULL) {
		    perror(TERMIMRC);
		    return(-1);
		}
	    }
	}
    }
    while(1) {
	line++;
	if(fgets(buffer, sizeof(buffer), config) == NULL)
	    break;
	l = strlen(buffer);
	if(l == 0 || buffer[l - 1] != '\n') {
	    fprintf(stderr, "termimrc:%d: line too long\n", line);
	    return(-1);
	}
	buffer[l - 1] = 0;
	p = buffer;
	if(end_of_line(&p))
	    continue;
	if(is_word("map", &p)) {
	    unsigned char *name;
	    int lname;
	    
	    name = get_string(&p, &lname);
	    if(name == NULL || !end_of_line(&p))
		return(line);
	    map = malloc(sizeof(KeyMap));
	    map->name = strdup(name);
	    map->def = NULL;
	    map->keys = malloc(sizeof(KeyBindings));
	    map->keys->n = 0;
	    map->next = key_maps;
	    key_maps = map;

	} else if(is_word("key", &p)) {
	    unsigned char *key;
	    int lkey;
	    KeyBinding *bind;
	    int l;

	    if(map == NULL) {
		fprintf(stderr, "Not in a map.\n");
		return(line);
	    }
	    key = get_string(&p, &lkey);
	    if(key == NULL)
		return(line);
	    l = strlen(key);
	    if(l > max)
		max = l;
	    bind = insert_key(map, key, lkey);
	    if(bind == NULL)
		return(line);
	    if(is_word("set_map", &p)) {
		unsigned char *n;
		int ln;

		n = get_string(&p, &ln);
		if(n == NULL || !end_of_line(&p))
		    return(line);
		bind->action = KEY_ACTION_CHANGE_MAP;
		bind->arg.ptr = strdup(n);
	    } else if(is_word("string", &p)) {
		unsigned char *s;
		int ls;

		s = get_string(&p, &ls);
		if(s == NULL || !end_of_line(&p))
		    return(line);
		bind->action = KEY_ACTION_STRING;
		bind->arg.string = alloc_string(s, ls);
	    } else if(is_word("macro", &p)) {
		unsigned *keys, key;

		keys = malloc(sizeof(unsigned));
		keys[0] = 0;
		while(!end_of_line(&p)) {
		    key = get_key(&p);
		    if(key == (unsigned)-1) {
			fprintf(stderr, "Unknown key.\n");
			return(line);
		    }
		    keys[0]++;
		    keys = realloc(keys, (keys[0] + 1) * sizeof(unsigned));
		    keys[keys[0]] = key;
		}
		if(keys[0] == 1) {
		    bind->action = KEY_ACTION_KEY;
		    bind->arg.key = keys[1];
		    free(keys);
		} else {
		    bind->action = KEY_ACTION_KEYS;
		    bind->arg.keys = keys;
		}
	    } else {
		return(line);
	    }

	} else if(is_word("default", &p)) {
	    unsigned char *d;
	    int ld;

	    d = get_string(&p, &ld);
	    if(d == NULL || !end_of_line(&p))
		return(line);
	    if(map == NULL) {
		fprintf(stderr, "Not in a map.\n");
		return(line);
	    }
	    if(map->def != NULL) {
		fprintf(stderr, "Several defaults.\n");
		return(line);
	    }
	    map->def = handler_by_name(d);
	    if(map->def == NULL) {
		fprintf(stderr, "Unknown handler: %s\n", d);
		return(line);
	    }

	} else {
	    return(line);
	}
    }
    fclose(config);

    for(map = key_maps; map != NULL; map = map->next) {
	if(map->def == NULL) {
	    fprintf(stderr, "No default for map %s.\n", map->name);
	    return(-1);
	}
	if(find_map_references(1, map->keys))
	    return(-1);
    }
    if(key_maps == NULL) {
	fprintf(stderr, "No keymaps.\n");
	return(-1);
    }
    stack = malloc((max + 1) * sizeof(unsigned));

    return(0);
}
