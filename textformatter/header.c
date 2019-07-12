#include <stdio.h>
#include <stdlib.h>
#include "header.h"
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <pwd.h>
#include <string.h>
#define N 256 //日付の要素を格納する文字列ポインタの最大要素数

char *makeheader(char *filename,char *date,char *username){
  char *header;
  int len_f,len_u;
  len_f=strlen(filename);
  len_u=strlen(username);
  header=(char*)malloc(100*sizeof(char));    //ヘッダーを格納する文字列ポインタ
  char space[5]="    \0";  //ファイル名と日付、日付とユーザ名の間のスペース
  
  if(len_f>30){
    strncpy(header,filename,10);
    header[10]='\0';
    strcat(header,"...");
    strcat(header,(filename+(len_f-10)));
  }else{
    strcpy(header,filename);
  }
  
  strcat(header,space);
  strcat(header,date);
  strcat(header,space);

  if(len_u>30){
    strncat(header,username,10);
    header[strlen(header)+10]='\0';
    strcat(header,"...");
    strcat(header,(username+(len_u-10)));
  }else{
    strcat(header,username);
  }

  return header;
}

static char *headername;
void Set_header(char* filename){
  char *date=(char*)malloc(100*sizeof(char));  //日付を格納する文字列ポインタ
  char year[N]={'\0'},month[N]={'\0'},day[N]={'\0'}; //日付の要素を格納する文字列ポインタ
  struct passwd *pwd;  //ユーザ名を取り出すための構造体
  time_t clock;        //時間
  struct tm *tm;       //日付を取り出すための構造体
  headername=(char*)malloc(100*sizeof(char));    //ヘッダーを格納する文字列ポインタ
  
  if(time(&clock) != -1){
    tm = localtime(&clock);
    sprintf(year,"%d",tm->tm_year+1900);  //日付の要素(数値)をchar型に変換する
    sprintf(month,"%d",tm->tm_mon+1);
    sprintf(day,"%d",tm->tm_mday);
    strcpy(date,year);
    strcat(date,"/");
    strcat(date,month);
    strcat(date,"/");
    strcat(date,day);
    if((pwd = getpwuid(getuid())) != NULL){
      headername = makeheader(filename,date,pwd->pw_gecos);
    }
  }  
}

char *Get_header(){
  return headername; //ヘッダーを返す
}
