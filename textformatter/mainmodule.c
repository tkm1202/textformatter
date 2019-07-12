#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "enum.h"
#include "lex.h"
#include "header.h"
#include "ps.h"

enum FINISH{
  OK_EXIT,
  ERR_EXIT,
};


int main(int argc,char* argv[]){

  FILE *fp;
  char *filename;
  char *file_ex;//拡張子を判断する
  int filetype;
  int i,len;
  int chr;
  int f;
  int count=0;
  int j=0;
  int priod_count=0;

  if(argc==2){

    if((fp=fopen(argv[1],"r"))==NULL){
      
      fprintf(stderr,"error:no exist file\n");
      exit(ERR_EXIT);
    }    

    filename=argv[1];

    file_ex=strrchr(filename,'.');//.拡張子を得る
    
    //ファイル名に日本語(全角)含まれている場合 f=1とする
    for(i=0;i<strlen(filename);i++){
      if(32<=filename[i] && filename[i]<=122)
	f=0;
      else{
	fprintf(stderr,"error:filename is japanese\n");
	return ERR_EXIT;
      }
    }
    
    //拡張子.c
    if(file_ex!=NULL && strcmp(file_ex,".c")==0)
      filetype=CFILE;
    
    //拡張子.c以外
    else
      filetype=TXTFILE;
    
  }
  
  //ファイルなし
  else if(argc==1){
 
    filename="noname";
    filetype=TXTFILE;
    fp=stdin;
    
  }

  //ファイルが2個以上
    
  else{
    fprintf(stderr,"error:too many arguments\n");
    return ERR_EXIT;
  }

  //PS_start呼び出す
  PS_start();
  
  //Set_header関数を呼び出す
  Set_header(filename);
  
  //LEX関数を呼び出す
  LEX(fp,filetype);
  
  PS_finishpage();

  return OK_EXIT;
}
