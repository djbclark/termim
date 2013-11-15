/***************************************************************************
 * Terminal Input Method
 * (C) Nicolas George, 2002-11-03
 * termim.h: common header
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

typedef struct KeyMap KeyMap;
typedef struct KeyHandler KeyHandler;
typedef struct KeyBinding KeyBinding;
typedef struct KeyBindings KeyBindings;
typedef struct String String;
typedef enum KeyAction KeyAction;
typedef enum SpecialKey SpecialKey;

struct KeyMap {
    KeyMap *next;
    const char *name;
    KeyHandler *def;
    KeyBindings *keys;
};

enum KeyAction {
    KEY_ACTION_SUB_BINDING,
    KEY_ACTION_CHANGE_MAP,
    KEY_ACTION_STRING,
    KEY_ACTION_KEY,
    KEY_ACTION_KEYS,
};

struct String {
    unsigned len;
    unsigned char str[1];
};

struct KeyBinding {
    unsigned key;
    KeyAction action;
    union {
	const char *ptr;
	String *string;
	KeyMap *keymap;
	KeyBindings *binding;
	unsigned key;
	unsigned *keys;
    } arg;
};

struct KeyBindings {
    int n;
    KeyBinding key[1];
};

struct KeyHandler {
    const char *name;
    void (*init)(void);
    void (*feed)(unsigned, FILE *);
};

enum SpecialKey {
    SK_BASE = 0x10F000,
    SK_COMPOSE
};

/* termim.c */
extern KeyMap *key_maps;
extern KeyHandler *key_handlers[];
extern unsigned *stack;
extern int screen_height;
extern int screen_width;
extern FILE *status_line(void);
extern void flush_status_line(void);
extern void status_line_say(const char *);
extern int to_utf8(unsigned, unsigned char *);

/* config_file.h */
extern int parse_config_file(void);

/* handlers */

extern KeyHandler handler_copy;
extern KeyHandler handler_tonepy;
extern KeyHandler handler_hangul;
extern KeyHandler handler_korean;
extern KeyHandler handler_western;
extern KeyHandler handler_cyrillic;
extern KeyHandler handler_greek;
extern KeyHandler handler_thai;
extern KeyHandler handler_arabic;
extern KeyHandler handler_hebrew;
extern KeyHandler handler_japanese;
