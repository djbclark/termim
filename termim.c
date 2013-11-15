/***************************************************************************
 * Terminal Input Method
 * (C) Nicolas George, 2002-11-03
 * termim.c: main program
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

#if __OpenBSD__ || __FreeBSD__ || __NetBSD__
# define OBSOLETE_TTY 1
#endif

#if linux
# define _XOPEN_SOURCE
#endif
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#ifndef OBSOLETE_TTY
# include <stropts.h>
#else
# if __OpenBSD__
#  include <util.h>
# elif __FreeBSD__
#  include <libutil.h>
# else
#  error Not tested
# endif
#endif
#include <poll.h>
#include <signal.h>
#include <string.h>
#if sun
# define _XPG4_2
#endif
#include <termios.h>

#include "termim.h"

KeyMap *key_maps = NULL;

KeyMap *current_map;
KeyBindings *current_bindings;

int screen_height = 1;
int screen_width = 1;

static struct termios term_attr;
static int master;
static int slave;
static int tty;
static volatile int keep = 1;
static FILE *master_file;
static FILE *tty_file;

unsigned *stack;
static int stack_pointer = 0;

KeyHandler *key_handlers[] = {
    &handler_copy,
    &handler_tonepy,
    &handler_korean,
    &handler_hangul,
    &handler_western,
    &handler_cyrillic,
    &handler_greek,
    &handler_thai,
    &handler_arabic,
    &handler_hebrew,
    &handler_japanese,
    NULL
};

static void
handler_copy_feed(unsigned key, FILE *out)
{
    fputc(key, out);
}

KeyHandler handler_copy = { "copy", NULL, handler_copy_feed };

int
to_utf8(unsigned c, unsigned char *u)
{
    int n, i;

    if(c < 0x80)
	n = 0;
    else if(c < 0x800)
	n = 1;
    else if(c < 0x10000)
	n = 2;
    else if(c < 0x200000)
	n = 3;
    else if(c < 0x4000000)
	n = 4;
    else
	n = 5;
    *(u++) = (c >> (6 * n)) | (n == 0 ? 0 : (0xFC << (5 - n)));
    for(i = n * 6 - 6; i >= 0; i -= 6)
	*(u++) = ((c >> i) & 0x3F) | 0x80;
    *u = 0;
    return(n + 1);
}

FILE *
status_line(void)
{
    fprintf(tty_file, "\033[s\033[%d;1H\033[J", screen_height);
    return(tty_file);
}

void
flush_status_line(void)
{
    fputs("\033[u", tty_file);
    fflush(tty_file);
}

void
status_line_say(const char *t)
{
    status_line();
    fputs(t, tty_file);
    flush_status_line();
}

static void
print_current_map(void)
{
    status_line();
    fprintf(tty_file, "Map: %s", current_map->name);
    flush_status_line();
}

static void
set_keymap(KeyMap *map)
{
    current_map = map;
    current_bindings = map->keys;
    print_current_map();
    if(current_map->def->init != NULL)
	current_map->def->init();
}

static void
filter(unsigned c, FILE *o)
{
    int i, j;
    KeyBinding *key;
    static short in_escape = 0;

    stack[stack_pointer++] = c;
    key = current_bindings->key;
    for(i = 0; i < current_bindings->n; i++, key++)
	if(c == key->key) {
	    switch(key->action) {
		case KEY_ACTION_STRING:
		    fwrite(key->arg.string->str, 1, key->arg.string->len, o);
		    current_bindings = current_map->keys;
		    stack_pointer = 0;
		    break;
		case KEY_ACTION_SUB_BINDING:
		    current_bindings = key->arg.binding;
		    break;
		case KEY_ACTION_CHANGE_MAP:
		    set_keymap(key->arg.keymap);
		    stack_pointer = 0;
		    break;
		case KEY_ACTION_KEY:
		    current_bindings = current_map->keys;
		    stack_pointer = 0;
		    filter(key->arg.key, o);
		    break;
		case KEY_ACTION_KEYS:
		    current_bindings = current_map->keys;
		    stack_pointer = 0;
		    for(j = 1; j <= key->arg.keys[0]; j++)
			filter(key->arg.keys[j], o);
		    break;
	    }
	    in_escape = 0;
	    return;
	}
    current_bindings = current_map->keys;
    c = stack[0];
    if(!in_escape && c != 27) {
	current_map->def->feed(c, o);
    } else {
	if(c == 27) {
	    in_escape = 1;
	} else if(in_escape == 1 && (c == '[' || c == 'O')) {
	    in_escape = 2;
	} else if(in_escape == 2 && ((c >= '0' && c <= '9') || c == ';' )) {
	    in_escape = 2;
	} else {
	    in_escape = 0;
	}
	fputc(c, o);
    }
    if(stack_pointer > 1) {
	int n;

	n = stack_pointer;
	stack_pointer = 0;
	for(i = 1; i < n; i++)
	    filter(stack[i], o);
    } else {
	stack_pointer = 0;
    }
}

static void
chld_handler(int n)
{
    keep = 0;
}

static void
winch_handler(int n)
{
    struct winsize ws;

    ioctl(tty, TIOCGWINSZ, &ws);
    screen_height = ws.ws_row;
    screen_width = ws.ws_col;
    if(ws.ws_row > 1)
	ws.ws_row--;
    ioctl(slave, TIOCSWINSZ, &ws);
}

int
main(void)
{
    struct pollfd fds[2];

    {
	int l;

	if((l = parse_config_file()) != 0) {
	    if(l > 0)
		fprintf(stderr, "termimrc:%d: error\n", l);
	    return(1);
	}
    }
    puts("\rTermim starting.");
    {
	struct sigaction act;

	act.sa_handler = chld_handler;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	sigaction(SIGCHLD, &act, NULL);

	act.sa_handler = winch_handler;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	sigaction(SIGWINCH, &act, NULL);
    }
    {
#ifdef OBSOLETE_TTY
	char name[] = "/dev/ptyXX";
#endif

#ifndef OBSOLETE_TTY
	tty = open("/dev/tty", O_RDWR);
	if(tty < 0) {
	    perror("tty");
	    exit(1);
	}
	master = open("/dev/ptmx", O_RDWR);
	if(master < 0) {
	    perror("ptmx");
	    exit(1);
	}
	if(grantpt(master)) {
	    perror("grantpt");
	    exit(1);
	}
	if(unlockpt(master)) {
	    perror("unlockpt");
	    exit(1);
	}
#else /* OBSOLETE_TTY */
	if(openpty(&master, &slave, name, NULL, NULL)) {
	    perror("openpty");
	    exit(1);
	}
#endif /* OBSOLETE_TTY */
	if(fork() == 0) {
#ifndef OBSOLETE_TTY
	    char *name;
#endif
	    int fd;
	    char *shell, *shell_base;

	    close(STDIN_FILENO);
	    close(STDOUT_FILENO);
	    close(STDERR_FILENO);
	    close(tty);
#ifndef OBSOLETE_TTY
	    setsid();
	    name = ptsname(master);
	    fd = open(name, O_RDWR);
#else
	    fd = slave;
#endif
	    close(master);
#ifndef OBSOLETE_TTY
	    ioctl(fd, I_PUSH, "ptem");
	    ioctl(fd, I_PUSH, "ldterm");
	    ioctl(fd, I_PUSH, "ttcompat");
	    dup2(fd, STDIN_FILENO);
	    dup2(fd, STDOUT_FILENO);
	    dup2(fd, STDERR_FILENO);
#else
	    login_tty(slave);
#endif
	    if(fd != STDIN_FILENO && fd != STDOUT_FILENO && fd != STDERR_FILENO)
		close(fd);
	    shell = getenv("SHELL");
	    if(shell == NULL)
		shell = "/bin/sh";
	    shell_base = strrchr(shell, '/');
	    if(shell_base == NULL)
		shell_base = shell;
	    else
		shell_base++;
	    /*sleep(10);*/
	    execl(shell, shell_base, NULL);
	    exit(1);
	} else {
	    struct termios attr;
#ifndef OBSOLETE_TTY
	    char *name;
#endif

#ifndef OBSOLETE_TTY
	    name = ptsname(master);
	    slave = open(name, O_RDWR);
#endif

	    tcgetattr(tty, &attr);
	    term_attr = attr;
	    attr.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP |
		INLCR | IGNCR | ICRNL | IXON);
	    attr.c_oflag &= ~OPOST;
	    attr.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
	    attr.c_cflag &= ~(CSIZE | PARENB);
	    attr.c_cflag |= CS8;
	    attr.c_cc[VMIN] = 1;
	    tcsetattr(tty, TCSADRAIN, &attr);

	    winch_handler(0);
	}
    }

    master_file = fdopen(master, "wb");
    tty_file = fdopen(tty, "wb");
    fds[0].fd = tty;
    fds[1].fd = master;
    fds[0].events = fds[1].events = POLLIN | POLLHUP;
    {
	KeyMap *m;

	for(m = key_maps; m->next != NULL; m = m->next);
	set_keymap(m);
    }
    while(keep) {
	if(poll(fds, 2, -1) <= 0)
	    continue;
	if((fds[0].revents & POLLHUP) || (fds[1].revents & POLLHUP))
	    break;
	if(fds[0].revents & POLLIN) {
	    unsigned char b[4096];
	    int l, i;

	    l = read(tty, b, sizeof(b));
	    if(l < 0)
		exit(1);
	    for(i = 0; keep && i < l; i++)
		filter(b[i], master_file);
	    fflush(master_file);
	}
	if(fds[1].revents & POLLIN) {
	    unsigned char b[4096];
	    int l;

	    l = read(master, b, sizeof(b));
	    if(l < 0)
		exit(1);
	    if(l > 0)
		write(tty, b, l);
	}
    }
    tcsetattr(tty, TCSADRAIN, &term_attr);
    puts("\rTermim exiting.");

    return(0);
}
