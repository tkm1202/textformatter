#include <stdio.h>
#include <stdlib.h>
#include "linemanage.h"
#include "ps.h"
#include "header.h"
#include "enum.h"
#include <string.h>
 
void Line_manage(ISRETURN re){
  static int LineCount=0;  //行数をカウントする静的変数
  static int LineNumber=0; //行番号を格納する静的変数
  static int PageCount=0;  //ページ数をカウントする静的変数
  char *header;            //ヘッダを格納する文字列ポインタ
  header=(char*)malloc(100*sizeof(char));
  char linenumber[7];      //行番号を格納する文字列配列
  char space[8]="      \0"; // 文が数行に渡る場合に行の初めをスペースで埋める
  char page[100];
  char no[4]="No.";
  int i;
  int Linenumber_a,PageCount_a;

  /*次ページの初期化を行う*/
  if(LineCount==0){        
    PageCount++;           //ページ数をインクリメント
    PS_newpage(PageCount); //次ページの初期化
    strcpy(header,Get_header());   //ヘッダを取り出す

    /*ページ数が100000を越えた場合の処理*/
    if(PageCount>99999){
      PageCount_a = PageCount%100000;
      sprintf(page,"%05d",PageCount_a);
    }
    /*ページ数が99999以下の場合の処理*/
    else{
      sprintf(page,"%d",PageCount);
    }

    strcat(header,"    ");  //ヘッダにページ数を追加
    strcat(header,no);
    strcat(header,page);
    PS_output(header,ENG_B,RETURN);  //ヘッダを出力
    PS_output("",ENG,RETURN); //1行スペースを空ける
  }
  LineCount++; //行数をインクリメント

  if(LineCount>58){
    /*1行が58文字を越えた場合改ページ処理*/
    PS_finishpage();
    LineCount=0;
    Line_manage(re);
  }
  else if(re==RETURN){
    /*改行した場合、行の初めに行番号を出力*/
    LineNumber++;

    /*行数が10000を越えた場合の処理*/
    if(LineNumber>9999){
      Linenumber_a = LineNumber % 10000;
      sprintf(linenumber,"%04d",Linenumber_a);
    }
    /*行数が9999以下の場合の処理*/
    else{
      sprintf(linenumber,"%4d",LineNumber);
    }

    strcat(linenumber,": ");
    PS_output(linenumber,ENG,NO_RETURN);
  }
  else{ 
    /*文が数行に渡る場合の処理*/
    PS_output(space,ENG,NO_RETURN);
  }
}
    
