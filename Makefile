###########################################################################
# Terminal Input Method
# (C) Nicolas George, 2002-11-03
# Makefile: guess what
###########################################################################

#
# Edit here to choose your favorite compiler options.
#

CC=gcc
CFLAGS=-Wall -g -O2
LDFLAGS=
LIBS=

RM=rm
INSTALL=install

#
# Edit here to choose your options.
#

# Common directory for all the program components.
PREFIX=/usr/local

#
# Edit here to fine tune your options.
#

BINDIR=$(PREFIX)/bin
MANDIR=$(PREFIX)/man
ETCDIR=$(PREFIX)/etc
DEFAULT_TERMIMRC=$(ETCDIR)/termimrc
DESTDIR=


###########################################################################

#
# Do not edit here
#

OBJECTS=termim.o config_file.o im_compose.o \
	im_tonepy.o \
	im_korean.o im_hangul.o im_japanese.o \
	japanese_data.o

all: termim

.c.o:
	$(CC) -c $(CFLAGS) $<

termim: $(OBJECTS)
	$(CC) -o $@ $(LDFLAGS) $(OBJECTS) $(LIBS)

termim.o: termim.c termim.h
config_file.o: config_file.c termim.h config.h
im_tonepy.o: im_tonepy.c termim.h tonepy_data.inc
im_korean.o: im_korean.c termim.h
im_compose.o: im_compose.c termim.h compose_data.c
im_japanese.o: im_japanese.c termim.h japanese_kanjitab.c

config.h: Makefile
	( \
	  echo "/* Auto-generated file. Do not edit. Edit Makefile. */"; \
	  echo "#define TERMIMRC \"$(DEFAULT_TERMIMRC)\""; \
	) > config.h

tonepy_data.inc: tonepy_data_to_c tonepy_data
	perl -w tonepy_data_to_c tonepy_data > tonepy_data.inc

japanese_data.c: japanese_data-ucs-2 japanese_data_toc
	perl -w japanese_data_toc < japanese_data-ucs-2 > japanese_data.c

japanese_data.o: japanese_data.c japanese_data.h

install: all
	$(INSTALL) -d $(DESTDIR)$(BINDIR)
	$(INSTALL) -m 755 -s termim $(DESTDIR)$(BINDIR)/termim
	$(INSTALL) -d $(DESTDIR)$(MANDIR)/man1
	$(INSTALL) -m 644 termim.1 $(DESTDIR)$(MANDIR)/man1/termim.1
	$(INSTALL) -d $(DESTDIR)$(ETCDIR)
	$(INSTALL) -m 644 termimrc $(DESTDIR)$(ETCDIR)/termimrc

clean:
	$(RM) -f termim $(OBJECTS) tonepy_data.inc japanese_data.c config.h
