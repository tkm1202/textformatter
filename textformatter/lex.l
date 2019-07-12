%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "enum.h"
#include "lex.h"
#include "tab.h"
#include "strmanage.h"

%}

PRESERVED  (void|char|short|int|long|float|double|auto|static|const|signed|unsigned|extern|volatile|register|return|goto|if|else|switch|case|default|break|for|while|do|continue|typedef|struct|enum|union|sizeof)
DOUBLE_Q  (\")
SINGLE_Q  (\')
DOUBLE_Q_ESC  (\\\")
SINGLE_Q_ESC  (\\\')
COMMENT1_START  (\/\*)
COMMENT1_END    (\*\/)
COMMENT2_START  (\/\/)
ENGWORD  (({ENGLISH}|{SIGN}|{SPACE})+)
C_ENGWORD (({ENGLISH}|{SPACE})+)
ENGLISH  ([a-zA-Z0-9])
C_ENGLISH ({ENGLISH}+|{SPACE}+)
SIGN          ({SIGNITURE}|{DOUBLE_Q}|{SINGLE_Q})
SIGNITURE     ([,-.!?#$%&=~^\|\{\}\[\]<>_/\+\;:\*@`])
JAPANESE ([\200-\377]+)
SPACE    ([ ])
TAB      (\t)
RETURN   (\n)
EXTRA    ([\(\)\\])

%Start     C_FILE TXT_FILE C_DOUBLE C_SINGLE C_COMMENT1 C_COMMENT2

%%

<TXT_FILE>{RETURN} {
   Str_manage(yytext, ENG);
}

<TXT_FILE>{TAB} {
   Str_manage(Tab(), ENG);
}

<TXT_FILE>{EXTRA} {
   char buf[10];
   sprintf(buf,"\\%s",yytext);
   Str_manage(buf, ENG);
}

<TXT_FILE>{ENGWORD} {
   Str_manage(yytext, ENG);
}

<TXT_FILE>{JAPANESE} {
   Str_manage(yytext, JPN);
}

<C_FILE>{DOUBLE_Q} {
   BEGIN(C_DOUBLE);
   Str_manage(yytext, ENG);
}

<C_FILE>{SINGLE_Q} {
   BEGIN(C_SINGLE);
   Str_manage(yytext, ENG);
}

<C_FILE>{SIGNITURE} {
   Str_manage(yytext, ENG);
}

<C_FILE>{TAB} {
   Str_manage(Tab(), ENG);
}

<C_FILE>{RETURN} {
   Str_manage(yytext, ENG);
}

<C_FILE>{EXTRA} {
   char buf[10];
   sprintf(buf,"\\%s",yytext);
   Str_manage(buf, ENG);
}

<C_FILE>{COMMENT1_START} {
   BEGIN(C_COMMENT1);
   Str_manage(yytext, ENG);
}

<C_FILE>{COMMENT2_START} {
   BEGIN(C_COMMENT2);
   Str_manage(yytext, ENG);
}

<C_FILE>{PRESERVED} {
   Str_manage(yytext, ENG_B);
}

<C_FILE>{C_ENGLISH} {
   Str_manage(yytext, ENG);
}

<C_FILE>{JAPANESE} {
   Str_manage(yytext, JPN);
}

<C_DOUBLE>{DOUBLE_Q} {
   BEGIN(C_FILE);
   Str_manage(yytext, ENG);
}

<C_DOUBLE>{SINGLE_Q} {
   Str_manage(yytext, ENG);
}

<C_DOUBLE>{TAB} {
   Str_manage(Tab(), ENG);
}

<C_DOUBLE>{RETURN} {
   Str_manage(yytext, ENG);
}

<C_DOUBLE>{EXTRA} {
   char buf[10];
   sprintf(buf,"\\%s",yytext);
   Str_manage(buf, ENG);
}

<C_DOUBLE>{SIGNITURE} {
   Str_manage(yytext, ENG);
}

<C_DOUBLE>{DOUBLE_Q_ESC} {
   char buf[10];
   sprintf(buf,"\\%s",yytext);
   Str_manage(buf, ENG);
}

<C_DOUBLE>{C_ENGWORD} {
   Str_manage(yytext, ENG);
}

<C_DOUBLE>{JAPANESE} {
   Str_manage(yytext, JPN);
}

<C_SINGLE>{SINGLE_Q} {
   BEGIN(C_FILE);
   Str_manage(yytext, ENG);
}

<C_SINGLE>{DOUBLE_Q} {
   Str_manage(yytext, ENG);
}

<C_SINGLE>{TAB} {
   Str_manage(Tab(), ENG);
}

<C_SINGLE>{RETURN} {
   Str_manage(yytext, ENG);
}

<C_SINGLE>{EXTRA} {
   char buf[10];
   sprintf(buf,"\\%s",yytext);
   Str_manage(buf, ENG);
}

<C_SINGLE>{SIGNITURE} {
   Str_manage(yytext, ENG);
}

<C_SINGLE>{SINGLE_Q_ESC} {
   char buf[10];
   sprintf(buf,"\\%s",yytext);
   Str_manage(buf, ENG);
}

<C_SINGLE>{C_ENGWORD} {
   Str_manage(yytext, ENG);
}

<C_SINGLE>{JAPANESE} {
   Str_manage(yytext, JPN);
}

<C_COMMENT1>{TAB} {
   Str_manage(Tab(), ENG);
}

<C_COMMENT1>{RETURN} {
   Str_manage(yytext, ENG);
}

<C_COMMENT1>{EXTRA} {
   char buf[10];
   sprintf(buf,"\\%s",yytext);
   Str_manage(buf, ENG);
}

<C_COMMENT1>{SIGN} {
   Str_manage(yytext, ENG);
}

<C_COMMENT1>{COMMENT1_END} {
   BEGIN(C_FILE);
   Str_manage(yytext, ENG);
}

<C_COMMENT1>{C_ENGWORD} {
   Str_manage(yytext, ENG);
}

<C_COMMENT1>{JAPANESE} {
   Str_manage(yytext, ENG_B);
}

<C_COMMENT2>{TAB} {
   Str_manage(Tab(), ENG);
}

<C_COMMENT2>{RETURN} {
   BEGIN(C_FILE);
   Str_manage(yytext, ENG);
}

<C_COMMENT2>{EXTRA} {
   char buf[10];
   sprintf(buf,"\\%s",yytext);
   Str_manage(buf, ENG);
}

<C_COMMENT2>{SIGN} {
   Str_manage(yytext, ENG);
}

<C_COMMENT2>{C_ENGWORD} {
   Str_manage(yytext, ENG);
}

<C_COMMENT2>{JAPANESE} {
   Str_manage(yytext, JPN);
}

%%

void LEX(FILE *fp, FILETYPE filetype){
   yyin = fp;

   if(filetype == CFILE){
      BEGIN(C_FILE);
   }else{
      BEGIN(TXT_FILE);
   }
   yylex();
}
