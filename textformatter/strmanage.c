#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "enum.h"
#include "strmanage.h"
#include "linemanage.h"
#include "ps.h"

static int strcnt = 0;/*1行中の文字数をカウントする変数*/
void Str_manage(char *buf,STRTYPE strtype){
  static ISRETURN returnflag=RETURN;
  char *b=buf;
  int margin=80-strcnt;/*現在の行にあと何文字入力できるかを表す変数*/
  char array[margin+2];

  if(strcnt==0/*行の文字数が0*/){
     Line_manage(returnflag);
    }
  
  if(buf[0]=='\n'/*改行文字がきたら*/){
    returnflag=RETURN;
    PS_output("",strtype,RETURN);
    strcnt=0;
    }
  
  else if(strtype==ENG||strtype==ENG_B){/*半角文字のとき*/
    if((buf[0]=='\\' ? strlen(buf)-1 : strlen(buf)) <= margin){/*入力文字列が現在の行に収まりきるとき*/
      PS_output(buf,strtype,NO_RETURN);
      if(buf[0]=='\\') buf++;
      strcnt+=strlen(buf);
    }
    else{/*入力文字列が現在の行に収まりきらないとき*/
      returnflag=NO_RETURN;
      strncpy(array,buf,margin);//arrayに現在の行に入力できるだけコピー
      array[margin] = '\0';
      PS_output(array,strtype,RETURN);
      strcnt=0;
      Str_manage(b+margin,strtype);//再帰
    }
  }

  else if(strtype==JPN){/*全角文字のとき*/
    if(strlen(buf) <= margin){/*入力文字列が現在の行に収まりきるとき*/
      PS_output(buf,strtype,NO_RETURN);
      strcnt+=strlen(buf);
    }
    else{/*入力文字列が現在の行に収まりきらないとき*/
      if(margin%2==1)margin--;//現在の行に入れる残りの文字列が奇数だったら偶数にする
      returnflag=NO_RETURN;
      strncpy(array,buf,margin);//arrayに現在の行に入力できるだけコピー
      array[margin] = '\0';
      PS_output(array,strtype,RETURN);
      strcnt=0;
      Str_manage(b+margin,strtype);//再帰
    }
  }
  return;
}

int Get_strCount(){
  return strcnt;//現在の行の文字数を返す
}
