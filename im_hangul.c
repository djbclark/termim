/***************************************************************************
 * Terminal Input Method
 * (C) Denis Auroux, 2002-11-16
 * im_hangul.c: korean (hangul) input method using korean keyboard layout
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

/* Korean (Hangul) input method using Korean keyboard layout
   'Z' escapes the next character (to be entered verbatim)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "termim.h"

static void han_init(void);
static void han_feed(unsigned key, FILE *output);

/*   A   B   C   D   E   F   G   H   I   J   K   L   M   N   O
                    dd                                      yae 
     P   Q   R   S   T   U   V   W   X   Y   Z
    ye  pp  kk      ss          jj
     a   b   c   d   e   f   g   h   i   j   k   l   m   n   o
     m  yu  j'  ng   d   l   h   o  ya  eo   a   i  eu   u  ae
     p   q   r   s   t   u   v   w   x   y   z  
     e   p   k   n   s  yeo  p'  j   t' yo   k'                     */

/* the consonants, vowels and endings in alphabetical order */
static const char han_cons[] =
  "r.R.s.e.E.f.a.q.Q.t.T.d.w.W.c.z.x.v.g.";
static const char han_vowels[] =
  "k.o.i.O.j.p.u.P.h.hkhohly.n.njnpnlb.m.mll.";
static const char han_endings[] =
  "..r.R.rts.swsge.f.frfafqftfxfvfga.q.qtt.T.d.w.c.z.x.v.g.";

/* unicode values of the various keys from 64 to 127 */
static const int han_jamo[64] = {
         0,      0,      0,      0,      0, 0x3138,      0,      0,
         0,      0,      0,      0,      0,      0,      0, 0x3152,
    0x3156, 0x3143, 0x3132,      0, 0x3146,      0,      0, 0x3149,
         0,      0,      0,      0,      0,      0,      0,      0,
         0, 0x3141, 0x3160, 0x314A, 0x3147, 0x3137, 0x3139, 0x314E,
    0x3157, 0x3151, 0x3153, 0x314F, 0x3163, 0x3161, 0x315C, 0x3150,
    0x3154, 0x3142, 0x3131, 0x3134, 0x3145, 0x3155, 0x314D, 0x3148,
    0x314C, 0x315B, 0x314B,      0,      0,      0,      0,      0 };

#define HAN_LAST_CONSONANT  0x314E

/* partially recorded keystrokes - up to 2 syllables */
static char han_buffer[10]; 
static int han_buflen;
static int han_esc_status; 
  /* 0 = no, 1 = got ^[, 2 = got ^[O or Z, 3 = got ^[[, 4 = terminating */

static int
han_find(char c1, char c2, const char *str)
{
  const char *p;
  int i;
  
  for (p=str, i=0; *p!=0; p+=2, i++)
    if (*p==c1 && p[1]==c2) return i;
  return -1;
}

static void
han_init(void)
{
  han_buflen = 0;
  han_buffer[0] = 0;
  han_esc_status = 0;
}

static void
han_putc(int ucs, FILE *f)
{
  fprintf(f, "%c%c%c", 0xE0+(ucs>>12), 0x80+((ucs>>6)&0x3F), 0x80+(ucs&0x3F));
}

static void
han_feed(unsigned key, FILE *output)
{
  int force_flush, cons1, vow1, cons2, cons3, pos;
  FILE *status;
  
  /* are we in an escape sequence ? */
  switch (han_esc_status) {
    case 1: if (key=='O') han_esc_status = 2;
            else if (key=='[') han_esc_status = 3;
            else han_esc_status = 0;
            break;
    case 2: han_esc_status = 4;  /* Esc O waits for only 1 char */
            break;
    case 3: if (key<'0' || key>';') han_esc_status = 4;
                                 /* Esc [ waits for first non-[0-9;:] */
            break;
  }
  if (han_esc_status) {
    fputc(key, output);
    if (han_esc_status == 4) han_esc_status = 0;
    return;
  }
  
  if (han_buflen == 0 && (key < 'A' || key > 'z' || !han_jamo[key-'@'])) 
  {
    if (key == 'Z') han_esc_status = 2;
    else {
      if (key == 27) han_esc_status = 1;
      fputc(key, output);
    }
    return;
  }
  
  if (key == 3 || key == 4 || key == 7) {
    han_buflen = 0;
    han_buffer[0] = 0;
    status_line_say("");
    return;
  }
  if (key == 27) han_esc_status = 1; /* will force_flush and then output Esc */
  
  force_flush = 0;
  if (key == 127 || key == 8) han_buflen--;
  else if (key < 'A' || key > 'z' || !han_jamo[key-'@']) force_flush = 1;
  else han_buffer[han_buflen++] = (char)key;
  han_buffer[han_buflen] = 0;
  
  while (han_buflen > 0) {
    /* eliminate faulty vowels at beginning, or pairs of consonants */
    while (han_buflen > 0 && han_jamo[han_buffer[0]-'@'] > HAN_LAST_CONSONANT)
    {
      /* we can't start with a vowel, flush it away */
      han_putc(han_jamo[han_buffer[0]-'@'], output);
      memmove(han_buffer, han_buffer+1, han_buflen--);
      status_line_say("\a");
    }
    while (han_buflen > 1 && han_jamo[han_buffer[1]-'@'] <= HAN_LAST_CONSONANT)
    {
      /* we can't start with two consonants, flush one away */
      han_putc(han_jamo[han_buffer[0]-'@'], output);
      memmove(han_buffer, han_buffer+1, han_buflen--);
      status_line_say("\a");
    }
    if (han_buflen == 0) break;
    cons1 = han_find(han_buffer[0], '.', han_cons);
    if (han_buflen == 1) {
      if (force_flush) {
        han_putc(han_jamo[han_buffer[0]-'@'], output);
        han_buffer[0]=0; han_buflen=0;
        status_line_say("\a");
      }
      break;
    }
    vow1 = han_find(han_buffer[1], han_buffer[2], han_vowels);
    if (vow1>=0) pos=3;
    else { vow1 = han_find(han_buffer[1], '.', han_vowels); pos=2; }
    /* after this vowel we want a consonant */
    if (pos < han_buflen) {
      cons2 = han_find(han_buffer[pos], '.', han_endings); 
      if (han_buflen > pos+1 &&
          han_jamo[han_buffer[pos+1]-'@'] > HAN_LAST_CONSONANT) cons2 = -1;
    }
    else cons2 = -1;
    if (cons2 < 0) { /* buffer is finished, or not a final consonant */
      if (han_buflen == pos && !force_flush) break; /* out of input */
      han_putc(0xAC00 + (21*28)*cons1 + 28*vow1, output);
      han_buflen-=pos;
      memmove(han_buffer, han_buffer+pos, han_buflen+1);
      continue; /* loop */
    }
    /* we have three elements, but final consonant may extend further */
    if (han_buflen == pos+1) {
      if (!force_flush) break; /* out of input */
      han_putc(0xAC00 + (21*28)*cons1 + 28*vow1 + cons2, output);
      han_buffer[0]=0; han_buflen=0;
      break;
    }
    /* CLAIM: han_buflen >= pos+2, and pos, pos+1 are consonants */
    cons3 = han_find(han_buffer[pos], han_buffer[pos+1], han_endings);
    if (cons3 >=0 && han_buflen == pos+2 && !force_flush) break;
                                 /* out of input, can't decide yet */
    if (cons3 >=0) {
      if (han_buflen == pos+2 || 
          han_jamo[han_buffer[pos+2]-'@'] <= HAN_LAST_CONSONANT)
        { cons2 = cons3; pos+= 2; }
      else pos++;
    } else pos++;

    han_putc(0xAC00 + (21*28)*cons1 + 28*vow1 + cons2, output);
    han_buflen-=pos;
    memmove(han_buffer, han_buffer+pos, han_buflen+1);
  }
  
  if (force_flush) {
    if (key == 'Z') han_esc_status = 2;
    else fputc(key, output);
    status_line_say("");
    return;
  }

  status = status_line();
  for (pos = 0; pos < han_buflen; pos++)
    han_putc(han_jamo[han_buffer[pos]-'@'], status);
  flush_status_line();
}

KeyHandler handler_hangul = {"hangul", han_init, han_feed};
