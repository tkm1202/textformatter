#include <stdio.h>
#include <string.h>
#include "enum.h"
#include "ps.h"

void PS_output(char *buf, STRTYPE strtype, ISRETURN isreturn){
  if(strcmp(buf,"")){
    fprintf(stdout, "(%s) ", buf);

    switch(strtype){
    case ENG:
      fprintf(stdout, "C s ");
      break;
    case ENG_B:
      fprintf(stdout, "B s ");
      break;
    case JPN:
      fprintf(stdout, "K s ");
      break;
    }
  }

  if(isreturn == RETURN){
    fprintf(stdout, "n");
  }

  fprintf(stdout, "\n");
}

void PS_newpage(int pagenum){
  fprintf(stdout, "%%%%Page: %d %d\n", pagenum, pagenum);
  fprintf(stdout, "b\n");
}

void PS_finishpage(){
  fprintf(stdout, "f\n");
}

void PS_start(){
  fprintf(stdout,"%%!PS-Adobe-1.0");
  fprintf(stdout,"\n%%%%Pages: (atend)");
  fprintf(stdout,"\n%%%%BoundingBox: (atend)");
  fprintf(stdout,"\n%%%%EndComments");
  fprintf(stdout,"\n");
  fprintf(stdout,"\n%%");
  fprintf(stdout,"\n%% $Id: prologue.ps,v 1.7 1994/04/10 08:33:40 yamamoto Exp yamamoto $");
  fprintf(stdout,"\n%%");
  fprintf(stdout,"\n");
  fprintf(stdout,"\n%% General macros.");
  fprintf(stdout,"\n/curx {currentpoint pop} def");
  fprintf(stdout,"\n/cury {currentpoint exch pop} def");
  fprintf(stdout,"\n");
  fprintf(stdout,"\n%% Constans.		%% Japanese character scale factor.");
  fprintf(stdout,"\n/jscale 0.94 def");
  fprintf(stdout,"\n");
  fprintf(stdout,"\n%% Commands.");
  fprintf(stdout,"\n/n {			%% - n -");
  fprintf(stdout,"\n	sx cury dy sub moveto");
  fprintf(stdout,"\n} def");
  fprintf(stdout,"\n");
  fprintf(stdout,"\n/f {			%% - f -");
  fprintf(stdout,"\n	showpage");
  fprintf(stdout,"\n} def");
  fprintf(stdout,"\n");
  fprintf(stdout,"\n/s {			%% string font s -");
  fprintf(stdout,"\n	dup K eq");
  fprintf(stdout,"\n	{js}");
  fprintf(stdout,"\n	{setfont show}");
  fprintf(stdout,"\n	ifelse");
  fprintf(stdout,"\n} def");
  fprintf(stdout,"\n");
  fprintf(stdout,"\n/js {			%% string font js -");
  fprintf(stdout,"\n	setfont");
  fprintf(stdout,"\n	dw 0 rmoveto");
  fprintf(stdout,"\n	dw 2 mul exch 0 exch ashow");
  fprintf(stdout,"\n	dw neg 0 rmoveto");
  fprintf(stdout,"\n} def");
  fprintf(stdout,"\n");
  fprintf(stdout,"\n%% Initialization.");
  fprintf(stdout,"\n/init {			%% sx sy pt dy init -");
  fprintf(stdout,"\n	gsave");
  fprintf(stdout,"\n");
  fprintf(stdout,"\n	/dy exch def");
  fprintf(stdout,"\n	/pt exch def");
  fprintf(stdout,"\n	/sy exch def");
  fprintf(stdout,"\n	/sx exch def");
  fprintf(stdout,"\n");
  fprintf(stdout,"\n	fonts {");
  fprintf(stdout,"\n		findfont pt scalefont def");
  fprintf(stdout,"\n	} forall");
  fprintf(stdout,"\n	jfonts {");
  fprintf(stdout,"\n		findfont pt jscale mul scalefont def");
  fprintf(stdout,"\n	} forall");
  fprintf(stdout,"\n");
  fprintf(stdout,"\n	%% Dummy.");
  fprintf(stdout,"\n	0 0 moveto");
  fprintf(stdout,"\n");
  fprintf(stdout,"\n	%% Set character width.");
  fprintf(stdout,"\n	C setfont");
  fprintf(stdout,"\n	/asciiwidth (AA) stringwidth pop def");
  fprintf(stdout,"\n	K setfont");
  fprintf(stdout,"\n	/japanesewidth <2422> stringwidth pop def");
  fprintf(stdout,"\n	/dw asciiwidth japanesewidth sub 2 div def");
  fprintf(stdout,"\n");
  fprintf(stdout,"\n	grestore");
  fprintf(stdout,"\n} def");
  fprintf(stdout,"\n");
  fprintf(stdout,"\n%% Default fonts.");
  fprintf(stdout,"\n/fonts 3 dict def");
  fprintf(stdout,"\nfonts begin");
  fprintf(stdout,"\n	/B /Courier-Bold def			%% Bold");
  fprintf(stdout,"\n	/C /Courier def					%% Courier");
  fprintf(stdout,"\nend");
  fprintf(stdout,"\n/jfonts 3 dict def");
  fprintf(stdout,"\njfonts begin");
  fprintf(stdout,"\n	/K /Ryumin-Light-EUC-H def		%% Kanji (Mincho-tai)");
  fprintf(stdout,"\nend");
  fprintf(stdout,"\n");
  fprintf(stdout,"\n25 768 10 12 init");
  fprintf(stdout,"\n/b {sx sy moveto} def");
  fprintf(stdout,"\n%%EndProlog");
  fprintf(stdout,"\n");
}
