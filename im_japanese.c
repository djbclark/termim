/***************************************************************************
 * Terminal Input Method
 * (C) Jean Marot, 2002-11-27
 * im_jp.c: Japanese input method
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

#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "termim.h"
#include "japanese_data.h"
#include "japanese_kanjitab.c"

#define HIRAGANA_BASE 0x3040
#define KATAKANA_BASE 0x30a0

static char keybuf[4];
static unsigned int kana_base;
static char mode;
#define KANA_MODE 0
#define KANJI_MODE 1
#define KANJI_SELECT 2
static unsigned int kanabuf[32];
static unsigned int input_off;
static unsigned int current_entry, current_sub;
static char match;
#define MATCH_NONE 0
#define MATCH_PARTIAL 1
#define MATCH_FULL 2

#define FLUSH keybuf[0]=keybuf[1]=keybuf[2]=keybuf[3]=0;

static void
init_jp(void)
{
  FLUSH;
  kana_base=HIRAGANA_BASE;
  mode=KANA_MODE;
  input_off=0;
  current_entry=0;
  current_sub=0;
}

static int
kanafeed(unsigned int *out, unsigned int key, unsigned char allhira)
{
  static const char vowels[]="aiueo";
  char *tmp;
  int lc=allhira || islower(key);
  if (!keybuf[0])
    kana_base=lc ? HIRAGANA_BASE : KATAKANA_BASE;
  key=tolower(key);

  if ((tmp=strchr(vowels, key)))
  {
    int v=tmp-vowels;
    if (!keybuf[1] && (keybuf[0] != 'j'))
    {
      switch(keybuf[0])
      { 
	case 0:
          out[0] =kana_base + 0x2 + 2*v; FLUSH; return 1;
	case 'x': // small vowels - apparently this is traditional in most IMEs
          out[0] =kana_base + 0x1 + 2*v; FLUSH; return 1;
        case 'k':
          out[0] =kana_base + 0xb + 2*v; FLUSH; return 1;
        case 'g':
          out[0] =kana_base + 0xc + 2*v; FLUSH; return 1;
        case 's':
          out[0] =kana_base + 0x15 + 2*v; FLUSH; return 1;
        case 'z':
          out[0] =kana_base + 0x16 + 2*v; FLUSH; return 1;
        case 't':
          out[0] =kana_base + 0x1f + 2*v + ((v>1)?1:0); FLUSH; return 1;
        case 'd':
          out[0] =kana_base + 0x20 + 2*v + ((v>1)?1:0); FLUSH; return 1;
        case 'n':
          out[0] =kana_base + 0x2a + v; FLUSH; return 1;
        case 'h':
          out[0] =kana_base + 0x2f + 3*v; FLUSH; return 1;
        case 'b':
          out[0] =kana_base + 0x30 + 3*v; FLUSH; return 1;
        case 'p':
          out[0] =kana_base + 0x31 + 3*v; FLUSH; return 1;
        case 'm':
          out[0] =kana_base + 0x3e + v; FLUSH; return 1;
        case 'r':
        case 'l':
          out[0] =kana_base + 0x49 + v; FLUSH; return 1;
        case 'y':  // kludge ;)
          if (!(v%2)) { out[0] =kana_base + 0x44 + v ; FLUSH; return 1; }
          else return -1;
        case 'w': 
          switch(v)
          {
            case 0: out[0] =kana_base + 0x4f; FLUSH; return 1;
            case 1: out[0] =kana_base + 0x50; FLUSH; return 1;
            case 2: return -1;
            case 3: out[0] =kana_base + 0x51; FLUSH; return 1;
            case 4: out[0] =kana_base + 0x52; FLUSH; return 1;
          }
        case 'f':
          if (v==2) { out[0] =kana_base + 0x35; FLUSH; return 1; } else return -1;
        default: 
          return -1;
      }
    } 
    else   // keybuf[1] 
    {
      char first=keybuf[0]; // kludge to handle Hepburn romanizations
      if ((keybuf[0] == 't') && (keybuf[1] == 's'))
      {
        if (v==2) { out[0] =kana_base + 0x24; FLUSH; return 1 ; } else return -1;
      }
      if ((keybuf[0] == 'd') && (keybuf[1] == 'z'))
      {
        if (v==2) { out[0] =kana_base + 0x25; FLUSH; return 1 ; } else return -1;
      }
      if (keybuf[1] != 'y')
      {
        if ((keybuf[0] == 's') && (keybuf[1] == 'h')) first='s';
        else if ((keybuf[0] == 'j') && (keybuf[1] == 0)) first='z';
        else if ((keybuf[0] == 'c') && (keybuf[1] == 'h')) first='t';
        else if ((keybuf[0] == 'd') && (keybuf[1] == 'j')) first='d';
      }
      if (v==3) return -1;
      switch(first)
      {
        case 'k': out[0] =kana_base + 0x0d; break;
        case 'g': out[0] =kana_base + 0x0e; break;
        case 's': out[0] =kana_base + 0x17; break;
        case 'z': out[0] =kana_base + 0x18; break;
        case 't': out[0] =kana_base + 0x21; break;
        case 'd': out[0] =kana_base + 0x22; break;
        case 'n': out[0] =kana_base + 0x2b; break;
        case 'h': out[0] =kana_base + 0x32; break;
        case 'b': out[0] =kana_base + 0x33; break;
        case 'p': out[0] =kana_base + 0x34; break;
        case 'm': out[0] =kana_base + 0x3f; break;
	case 'l':
	case 'r': out[0] =kana_base + 0x4a; break;
      }
      switch(v)
      {
        case 0: out[1] = kana_base + 0x43; break; 
        case 2: out[1] = kana_base + 0x45; break; 
        case 4: out[1] = kana_base + 0x47; break; 
      }
      FLUSH;
      return (v==1)?1:2;
    }
  }
  else // not a vowel
  {
    if (keybuf[1]) return -1;
    if (!keybuf[0])
    {
      if (strchr("kgsztdnhbpmyrwjfcxl", key))
      { 
        keybuf[0]=key;
        return 0;
      }
      return -1;
    }
    if (((key=='y') && strchr("kgsztdnhbpmrl", keybuf[0]))
        || (key=='h' && (keybuf[0]=='s' || keybuf[0]=='c'))
        || ((key=='j' || key=='z') && keybuf[0]=='d')
        || (key=='s' && keybuf[0]=='t'))
    { 
      keybuf[1]=key;
      return 0;
    }
    if ((keybuf[0]=='n' || keybuf[0]=='m') && strchr("kgsztdnhbpmyrwjfc'", key))
    { 
      out[0] =kana_base + 0x53;
      keybuf[0]=(key=='\'')?0:key;
      kana_base=lc ? HIRAGANA_BASE : KATAKANA_BASE;
      return 1;
    }
    if ((keybuf[0]==key) || (keybuf[0]=='t' && key=='c'))
    {
      out[0] =kana_base + 0x23;
      keybuf[0]=key;
      kana_base=lc ? HIRAGANA_BASE : KATAKANA_BASE;
      return 1;
    }
    return -1;
  }
  return -1; // just for paranoia's sake
} 

static void
kanjimode_feed(unsigned int key, FILE *out)
{
  char buf[8];
  FILE *stat;
  unsigned int i;
  int r=0;
  switch(key)
  {
    case 0x1b:
      fputc(0x1b, out); 
      // fallthrough
    case 3:
    case 7:
      FLUSH; goto abort_exit;
    case ' ':
    case '\r':
      if (match == MATCH_FULL) 
      {
        const unsigned short *w=japanese_kanjitab +
	    (japanese_dict[current_entry].kanjioff & 0x7fffff);
	unsigned int i=current_sub;
	while (i--) do {} while (!(*(++w) & 0x8000));
	do
	{
	  to_utf8(0x3000 + (*w & 0x7fff), buf);
	  fputs(buf, out);
	} while (!(*(++w) & 0x8000));
        goto abort_exit;
      }
      // fallthrough
    case '\t':
      {
	unsigned int i;
	for (i=0; i<input_off; i++) { to_utf8(kanabuf[i], buf); fputs(buf, out); }
        goto abort_exit;
      }
    case '>':
      if (match == MATCH_FULL)
	current_sub=(current_sub+1) % (japanese_dict[current_entry].kanjioff>>24);
      goto stat_exit;
    case '<':
      if (match == MATCH_FULL)
	current_sub=(current_sub+ (japanese_dict[current_entry].kanjioff>>24) -1)
	  		% (japanese_dict[current_entry].kanjioff>>24);
      goto stat_exit;
    case '\b':
    case 127:
      if (keybuf[1]) { keybuf[1]=0; goto stat_exit; }
      else if (keybuf[0]) { keybuf[0]=0; goto stat_exit; }
      else if (input_off)
      { 
	current_sub=0;
	input_off--; 
	if (input_off)
	{
	  if (match != MATCH_NONE)
	  {
	    while ( japanese_kanatab[japanese_dict[current_entry].kanaoff ] >= input_off )
	      current_entry--;
	  }
	  else 
	  {  // we still point to the first entry that has a common prefix
	    unsigned const char *c=japanese_kanatab +
		japanese_dict[current_entry].kanaoff;
	    unsigned int i;
	    match=MATCH_PARTIAL;
	    for (i=c[0]; i<input_off; i++)
	      if (c[1+i-c[0]] != (kanabuf[i] & 0xff)) match=MATCH_NONE;
	  }
	}
	else
	{
	  current_entry=0; match=MATCH_PARTIAL; 
	}
	goto stat_exit;
      }
      else goto abort_exit;
  }

  r= (input_off < 30) ? kanafeed(kanabuf+input_off, key, 1) : -1;

  if (r>0) current_sub=0;
  while (r>0)
  {
    unsigned const char *c;
    c=japanese_kanatab+japanese_dict[current_entry].kanaoff;
    if (match!=MATCH_NONE && c[1 + input_off - c[0]] != (kanabuf[input_off] & 0xff))
    {
      unsigned int oldce=current_entry;
      for (;;)
      {
        c=japanese_kanatab+japanese_dict[++current_entry].kanaoff;
        if ((c[0] < input_off) || c[0]==0x3f) break;
        if (c[0]==input_off && c[1]==(kanabuf[input_off] & 0xff)) break;
      }
      if (c[0] != input_off) { match=MATCH_NONE; current_entry=oldce; } }
    input_off++; r--;
  }

      
stat_exit:
  stat=status_line();
  if (match!=MATCH_NONE)
  {
    unsigned const char *c=japanese_kanatab+japanese_dict[current_entry].kanaoff;
    match=(c[1 + input_off - c[0]] > 0x3f) ? MATCH_PARTIAL : MATCH_FULL;
    if (keybuf[0]) match=MATCH_PARTIAL;
  } 
  fputc('`', stat);
  for (i=0; i<input_off; i++) { to_utf8(kanabuf[i], buf); fputs(buf, stat); }
  fputs(keybuf, stat);
  switch (match)
  {
    case MATCH_NONE: 
      fputs(" (***)", stat);
      break;
    case MATCH_PARTIAL: 
      if (input_off) fputs("...", stat);
      break;
    case MATCH_FULL:
      {
        const unsigned short *w=japanese_kanjitab + (japanese_dict[current_entry].kanjioff & 0x7fffff);
	unsigned int i=current_sub;
	fprintf(stat, " (%d/%d:", current_sub+1, japanese_dict[current_entry].kanjioff>>24);
	while (i--) do {} while (!(*(++w) & 0x8000));
	do
	{
	  to_utf8(0x3000 + (*w & 0x7fff), buf);
	  fputs(buf, stat);
	} while (!(*(++w) & 0x8000));
	fputc(')', stat);
      }
      break;
  }
  // DEBUG
  // fprintf(stat, " [%d:%d]", current_entry, current_sub);
  if (r<0) fputc('\a', stat);
  flush_status_line();
  return;

abort_exit:
  mode=KANA_MODE;
  input_off=0;
  status_line_say(keybuf);
  current_entry=0;
  current_sub=0;
  return;
}

static void
kselect_feed(unsigned int key, FILE *out)
{
  FILE *stat;
  char buf[8];
  unsigned int i;
  switch(key)
  {
    case '<':
      current_sub += (kindex[current_entry].num-1)/10;
      current_sub %= 1+(kindex[current_entry].num-1)/10;
      break;
    case '>':
      current_sub++;
      current_sub %= 1+(kindex[current_entry].num-1)/10;
      break;
    case '[':
      {
	int r=(kindex[current_entry].rad-1);
	if (r==0) r=214;
	current_entry=0;
	while (kindex[current_entry].rad<r) current_entry++;
	current_sub=0;
      }
      break;
    case ']':
      {
	int r=(kindex[current_entry].rad+1);
	if (r==215) r=1;
	current_entry=0;
	while (kindex[current_entry].rad<r) current_entry++;
	current_sub=0;
      }
      break;
    case '{':
      {
	int r=(kindex[current_entry].rad-10);
	if (r<1) r+=214;
	current_entry=0;
	while (kindex[current_entry].rad<r) current_entry++;
	current_sub=0;
      }
      break;
    case '}':
      {
	int r=(kindex[current_entry].rad+10);
	if (r>214) r-=214;
	current_entry=0;
	while (kindex[current_entry].rad<r) current_entry++;
	current_sub=0;
      }
      break;
    case '-':
    case '_':
      if (current_entry>0 && kindex[current_entry-1].rad == kindex[current_entry].rad)
      {
	current_entry--;
	current_sub=0;
      }
      break;
    case '+':
    case '=':
      if (current_entry<n_kindex-1 && kindex[current_entry+1].rad == kindex[current_entry].rad)
      {
	current_entry++;
        current_sub=0;
      }
      break;
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      {
        unsigned int i=(key=='0') ? 9 : (key-'1');
        if (i >= kindex[current_entry].num - 10*current_sub) goto status;
	to_utf8(kanjis[kindex[current_entry].off+10*current_sub+i], buf);
	fputs(buf, out);
      }
      // fallthrough
    case 0x1b:
    case ' ':
    case 3:
    case 7:
      if (key==0x1b) fputc(0x1b, out);
      mode=KANA_MODE;
      status_line_say("");
      return;
    case '\r':
      if ((kindex[current_entry].num - 10*current_sub) == 1)
      {
	to_utf8(kanjis[kindex[current_entry].off+10*current_sub], buf);
	fputs(buf, out);
	mode=KANA_MODE;
	status_line_say("");
	return;
      }
      status_line_say("\a");
      break;      
  }
  
status:
  stat=status_line();
  to_utf8(0x2f00+kindex[current_entry].rad-1, buf);
  fprintf(stat, "R%d(%s) S+%d (%d/%d):",
           kindex[current_entry].rad,
	   buf,
	   kindex[current_entry].strokes,
	   current_sub+1,
	   (kindex[current_entry].num-1)/10+1
	 );
  for (i=0; i<10; i++)
    if (current_sub*10+i < kindex[current_entry].num)
    {
      to_utf8(kanjis[kindex[current_entry].off + 10*current_sub + i], buf);
      fprintf(stat, "%d.%s ", (i+1)%10, buf);
    }
  flush_status_line();
  return; 
}


static void
feed_jp(unsigned int key, FILE *out)
{
  static unsigned int kanabuf[2];
  int r;
  char buf[8];
  FILE *stat;
  
  switch(mode)
  {
    case KANJI_MODE: return kanjimode_feed(key, out);
    case KANJI_SELECT: return kselect_feed(key, out);
  } 
  if (!keybuf[0]) // handle punctuation and the like
  {
    switch (key)
    {
      case '`':
        mode=KANJI_MODE; match=MATCH_PARTIAL; status_line_say("`"); return;
      case '~':
        mode=KANJI_SELECT; current_entry=0; current_sub=0; return kselect_feed(0,out);
      case '-': 
        to_utf8(0x30fc, buf); fputs(buf, out); return;
      case '*': 
        to_utf8(0x30fb, buf); fputs(buf, out); return;
      case '.': 
        to_utf8(0x3002, buf); fputs(buf, out); return;
      case ',': 
        to_utf8(0x3001, buf); fputs(buf, out); return;
      case '(': 
        to_utf8(0x300c, buf); fputs(buf, out); return;
      case ')': 
        to_utf8(0x300d, buf); fputs(buf, out); return;
      case '[': 
        to_utf8(0x300e, buf); fputs(buf, out); return;
      case ']': 
        to_utf8(0x300f, buf); fputs(buf, out); return;
      case '<': 
        to_utf8(0x3008, buf); fputs(buf, out); return;
      case '>': 
        to_utf8(0x3009, buf); fputs(buf, out); return;
      case '{': 
        to_utf8(0x300a, buf); fputs(buf, out); return;
      case '}': 
        to_utf8(0x300b, buf); fputs(buf, out); return;
      case '\'': 
        to_utf8(0x309a, buf); fputs(buf, out); return;
      case '"': 
        to_utf8(0x3099, buf); fputs(buf, out); return;
      case '+': 
        to_utf8(0x3005, buf); fputs(buf, out); return;
    }
    // anything with no special handling is sent verbatim ?
    if (!isalpha(key)) { fputc(key, out); return; }
  }
  else // when keybuf isn't empty
  {
    if (key==127 || key=='\b')
    {
      if (keybuf[1]) keybuf[1]=0; else keybuf[0]=0;
      status_line_say(keybuf);
      return;
    }
    else if (key==3 || key==7 || key==0x1b)
    {
      if (key==0x1b) fputc(0x1b, out);
      FLUSH;
      status_line_say(keybuf);
      return;
    }
  }
  
  r=kanafeed(kanabuf, key, 0);
  if (r>0)
  {
    unsigned int i;
    for (i=0; i<r; i++)
    {
      to_utf8(kanabuf[i], buf);
      fputs(buf, out);
    }
  }
  stat=status_line();
  fputs(keybuf, stat);
  if (r<0) fputc('\a', stat);
  flush_status_line();
  return;
}

KeyHandler handler_japanese = { "japanese", init_jp, feed_jp };
