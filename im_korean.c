/***************************************************************************
 * Terminal Input Method
 * (C) Denis Auroux, 2002-11-16
 * im_korean.c: korean (hangul) input method using transliteration
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

/* Korean (Hangul) input method for Western keyboards

  Hangul syllables are entered by typing their latin transliteration
  (in lowercase). Syllable breaks can be forced using any of /,-,|.
  E.g., try typing:  seoul  hangul  annyeong haseyo   kimch'i
  You can only enter valid syllables, not isolated Hangul elements.

  Most usual transliterations should be accepted. The KR_PAIRING tables
  can be modified; howver the code assumes (to detect syntax errors)
  that the only prefixes which are not valid transliterations themselves
  are 'c' for consonants and 'y', 'w' for vowels.
  If you change this, update the code accordingly.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "termim.h"

static void kr_init(void);
static void kr_feed(unsigned key, FILE *output);

typedef struct KR_PAIRING {
  const char *text;
  int code;
} KR_PAIRING;

/* initial consonants (19): (canonical form and alternate forms)
   0 k   (g)                      10 ss    (ssh,shsh)
   1 kk  (gg)                     11 empty
   2 n                            12 j     (ch,ts)
   3 d   (t)                      13 jj    (chch,tss)
   4 dd  (tt)                     14 j'    (ch',tch,tsh,jh)
   5 l   (r)                      15 k'    (g',kh)
   6 m                            16 t'    (th)
   7 p   (b)                      17 p'    (f,ph)
   8 pp  (bb)                     18 h
   9 s   (sh)
*/

static const struct KR_PAIRING kr_cons[] = {
    {"k",   0}, {"g",     0},
    {"kk",  1}, {"gg",    1},
    {"n",   2}, 
    {"d",   3}, {"t",     3},
    {"dd",  4}, {"tt",    4},
    {"l",   5}, {"r",     5}, 
    {"m",   6},
    {"p",   7}, {"b",     7},
    {"pp",  8}, {"bb",    8}, 
    {"s",   9}, {"sh",    9},
    {"ss", 10}, {"ssh",  10}, {"shsh", 10},
    {"",   11},
    {"j",  12}, {"ch",   12}, {"ts",   12},
    {"jj", 13}, {"chch", 13}, {"tss",  13},
    {"j'", 14}, {"ch'",  14}, {"tch",  14}, {"tsh", 14}, {"jh", 14},
    {"k'", 15}, {"g'",   15}, {"kh",   15},
    {"t'", 16}, {"th",   16},
    {"p'", 17}, {"f",    17}, {"ph",   17},
    {"h",  18},
    {NULL, -1}
};

/* vowels (21):
   0 a                           11 oe  (oi)
   1 ae                          12 yo  (io)
   2 ya   (ia)                   13 u
   3 yae  (iae)                  14 wo  (uo, weo, ueo)
   4 eo                          15 we  (ue)
   5 e                           16 wi  (ui)
   6 yeo  (ieo)                  17 yu  (iu)
   7 ye   (ie)                   18 eu
   8 o                           19 yi  (ee)
   9 wa   (oa)                   20 i
  10 wae  (oae)
*/

static const struct KR_PAIRING kr_vowels[] = {
    {"a",    0},
    {"ae",   1},
    {"ya",   2}, {"ia",   2},
    {"yae",  3}, {"iae",  3},
    {"eo",   4},
    {"e",    5},
    {"yeo",  6}, {"ieo",  6},
    {"ye",   7}, {"ie",   7},
    {"o",    8},
    {"wa",   9}, {"oa",   9},
    {"wae", 10}, {"oae", 10},
    {"oe",  11}, {"oi",  11},
    {"yo",  12}, {"io",  12},
    {"u",   13},
    {"wo",  14}, {"uo",  14}, {"weo", 14}, {"ueo", 14},
    {"we",  15}, {"ue",  15},
    {"wi",  16}, {"ui",  16},
    {"yu",  17}, {"iu",  17},
    {"eu",  18},
    {"yi",  19}, {"ee",  19},
    {"i",   20},
    {NULL, -1}
};

/* endings (28):
   0 empty                         14 lp' (rp', lf, rf, lph, rph)
   1 k   (g)                       15 lh  (rh, l', r')
   2 kk  (gg)                      16 m
   3 ks  (ksh, gs, gsh)            17 p   (b)
   4 n                             18 ps  (bs, psh, bsh)
   5 nj  (nch, nts)                19 s   (sh)
   6 nh  (n')                      20 ss  (ssh, shsh)
   7 d   (t)                       21 ng
   8 l   (r)                       22 j   (ch, ts)
   9 lk  (rk, lg, rg)              23 j'  (ch', tch, tsh, jh)
  10 lm  (rm)                      24 k'  (g', kh)
  11 lp  (rp, lb, rb)              25 t'  (th)
  12 ls  (rs, lsh, rsh)            26 p'  (f, ph)
  13 lt' (rt', lth, rth)           27 h
*/

static const struct KR_PAIRING kr_endings[] = {
    {"",     0},
    {"k",    1}, {"g",    1},
    {"kk",   2}, {"gg",   2}, 
    {"ks",   3}, {"ksh",  3}, {"gs",    3}, {"gsh",  3},
    {"n",    4},
    {"nj",   5}, {"nch",  5}, {"nts",   5},
    {"nh",   6}, {"n'",   6},
    {"d",    7}, {"t",    7},
    {"l",    8}, {"r",    8}, 
    {"lk",   9}, {"rk",   9}, {"lg",    9}, {"rg",   9},
    {"lm",  10}, {"rm",  10},
    {"lp",  11}, {"rp",  11}, {"lb",   11}, {"rb",  11},
    {"ls",  12}, {"rs",  12}, {"lsh",  12}, {"rsh", 12},
    {"lt'", 13}, {"rt'", 13}, {"lth",  13}, {"rth", 13},
    {"lp'", 14}, {"rp'", 14}, {"lf",   14}, {"rf",  14}, {"lph", 14},
    {"rph", 14}, {"lh",  15}, {"rh",   15}, {"l'",  15}, {"r'",  15},
    {"m",   16},
    {"p",   17}, {"b",   17},
    {"ps",  18}, {"bs",  18}, {"psh",  18}, {"bsh", 18},
    {"s",   19}, {"sh",  19},
    {"ss",  20}, {"ssh", 20}, {"shsh", 20}, 
    {"ng",  21},
    {"j",   22}, {"ch",  22}, {"ts",   22},
    {"j'",  23}, {"ch'", 23}, {"tch",  23}, {"tsh", 23}, {"jh",  23},
    {"k'",  24}, {"g'",  24}, {"kh",   24},
    {"t'",  25}, {"th",  25},
    {"p'",  26}, {"f",   26}, {"ph",   26},
    {"h",   27},
    {NULL, -1}
};

/* unicode values of the various elements */
static const int kr_jamo[3][28] = {
  { 0x3131, 0x3132, 0x3134, 0x3137, 0x3138, 0x3139, 0x3141, 0x3142,
    0x3143, 0x3145, 0x3146, 0x3147, 0x3148, 0x3149, 0x314A, 0x314B,
    0x314C, 0x314D, 0x314E,      0,      0,      0,      0,      0,
         0,      0,      0,      0 },
  { 0x314F, 0x3150, 0x3151, 0x3152, 0x3153, 0x3154, 0x3155, 0x3156,
    0x3157, 0x3158, 0x3159, 0x315A, 0x315B, 0x315C, 0x315D, 0x315E,
    0x315F, 0x3160, 0x3161, 0x3162, 0x3163,      0,      0,      0,
         0,      0,      0,      0 },
  {      0, 0x3131, 0x3132, 0x3133, 0x3134, 0x3135, 0x3136, 0x3137,
    0x3139, 0x313A, 0x313B, 0x313C, 0x313D, 0x313E, 0x313F, 0x3140,
    0x3141, 0x3142, 0x3144, 0x3145, 0x3146, 0x3147, 0x3148, 0x314A,
    0x314B, 0x314C, 0x314D, 0x314E }
 };    

/* partially recorded keystrokes - up to 2 syllables */
static char kr_buffer[20]; 
static int kr_buflen;
static int kr_elements[6];

static void
kr_init(void)
{
  kr_buflen = 0;
  kr_buffer[0] = 0;
}

static int
kr_attempt_decode(char *input, int howfar, int *shiftby, int greedy)
{
  int match, matchlen, matchscore, i, j, k, l, ll;
  char *p=input, *q;

  /* match a consonant -- can't fail ! */
  match = -1; matchlen = -1;
  for (i=0; kr_cons[i].code>=0 ; i++) {
    l = strlen(kr_cons[i].text);
    if ((l > matchlen) && !strncmp(p, kr_cons[i].text, l))
      { match = kr_cons[i].code; matchlen = l; }
  }
  kr_elements[howfar] = match;
  p += matchlen;
  *shiftby = matchlen;
  
  /* then a vowel -- can fail ! */
  match = -1; matchlen = -1;
  for (i=0; kr_vowels[i].code>=0 ; i++) {
    l = strlen(kr_vowels[i].text);
    if ((l > matchlen) && !strncmp(p, kr_vowels[i].text, l))
      { match = kr_vowels[i].code; matchlen = l; }
  }
  if (match<0) return (howfar+1);
  kr_elements[howfar+1] = match;
  p += matchlen;
  *shiftby += matchlen;

  /* if we're in lookahead, we're satisfied - let's stop */
  if (howfar>0) return (howfar+2);
  
  /* look for a final consonant -- cannot fail, but don't be greedy ! */
  /* find the shortest final that gives a parsable remainder, or if there
     is no parsable remainder, the longest final */

  match = -1;  matchlen = -1; matchscore = 3;
  for (i=0; kr_endings[i].code>=0 ; i++) {
    l = strlen(kr_endings[i].text);
    if (!strncmp(p, kr_endings[i].text, l)) {
      j = kr_endings[i].code;
      k = kr_attempt_decode(p+l, 3, &ll, greedy);
      q=p+l+ll;
      if (*q==0 || (q[1]==0 && (*q=='y' || *q=='w' || *q=='c'))) {
        /* matched everything or almost-everything */
        if (greedy && k==4) k=-1; /* we don't like this at all */
        if (k > matchscore || (k == matchscore && l < matchlen))
          { match = j; matchlen = l; matchscore = k; }
      } 
      if (matchscore == 3) /* no good continuation, be greedy */
        if (l > matchlen) { match = j; matchlen = l; }
    }
  }
  kr_elements[2] = match;
  p += matchlen;
  *shiftby += matchlen;
  kr_attempt_decode(p, 3, &ll, greedy);
  return matchscore;
    /* 5 means we have 2 syllables and we can flush the first happily;
       4 means we're non-greedy, feed is clean, but no 2nd syllable yet
       3 means either we're greedy, or there's a syntax error at the end
    */
}

static void
kr_feed(unsigned key, FILE *output)
{
  int howfar, force_flush, shiftby, ucs, i;
  FILE *status;

  if (kr_buflen == 0 && (key < 'a' || key > 'z')) {
    fputc(key, output);
    return;
  }
  
  if (key == 3 || key == 4 || key == 7) {
    kr_buflen = 0;
    kr_buffer[0] = 0;
    status_line_say("");
    return;
  }
  
  force_flush = 0;
  if (key == 127 || key == 8) kr_buflen--;
  else if ((key < 'a' || key > 'z') && key!='\'') force_flush = 1;
  else kr_buffer[kr_buflen++] = (char)key;
  
  kr_buffer[kr_buflen] = 0;
  howfar = kr_attempt_decode(kr_buffer, 0, &shiftby, force_flush);
  
  if (force_flush && howfar < 3) { /* not a syllable !! */
    kr_buflen = 0;
    kr_buffer[0] = 0;
    status_line_say("\a");
    if (key!='/' && key!='|' && key!='-') fputc(key, output);
    return;
  }

  /* check for a syntax error causing a vowel not to be found: only OK cases
     are if the remainder is either empty, or "y", or "w", or "c" */
  if (howfar == 1 && shiftby<kr_buflen) {
    if (kr_buflen!=shiftby+1 ||
        (kr_buffer[shiftby]!='y' && kr_buffer[shiftby]!='w' && 
         kr_buffer[shiftby]!='c'))
    {
      kr_buflen = 0;
      kr_buffer[0] = 0;
      status_line_say("\a");
      return;
    }  
  }  

  if (force_flush || howfar == 3 || howfar == 5) { /* output a character */
    ucs = 0xAC00 + (21*28)*kr_elements[0] + 28*kr_elements[1] + kr_elements[2];
    fprintf(output, "%c%c%c", 
      0xE0+(ucs>>12), 0x80+((ucs>>6)&0x3F), 0x80+(ucs&0x3F));
    memmove(kr_buffer, kr_buffer + shiftby, kr_buflen+1-shiftby);
    kr_buflen -= shiftby;
    howfar -= 3;
    kr_elements[0] = kr_elements[3];
    kr_elements[1] = kr_elements[4];
  }
  
  if (force_flush) {
    if (kr_buflen == 0) { /* we're done */
      status_line_say("");
      if (key!='/' && key!='|' && key!='-') fputc(key, output);
      return;
    } 
    kr_feed(key, output); /* we try again */
    return;
  } 
  
  /* we may have a partial syllable: build a status line */
  status = status_line();
  if (howfar%3 == 1 && kr_elements[howfar-1] == 11) howfar--; /* empty ! */
  if (kr_buflen>0) {
    fprintf(status, "%-12s : ", kr_buffer);
    for (i=0;i<howfar;i++) if (kr_elements[i]>=0) {
      ucs = kr_jamo[i%3][kr_elements[i]];
      if (ucs)
        fprintf(status, "%c%c%c", 
          0xE0+(ucs>>12), 0x80+((ucs>>6)&0x3F), 0x80+(ucs&0x3F));
    }
  }
  flush_status_line();
}

KeyHandler handler_korean = {"korean", kr_init, kr_feed};
