#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"tab.h"
#include"strmanage.h"

char *Tab(){
  int count;
  char c[10];
  int i = 0;
  for(i = 0;i<10;i++){
    c[i]='\0';
  }
  count=Get_strCount();

  switch(count%8){
    
  case 0:
    return "        ";
    
  case 1:
    return "       ";
  case 2:
    return "      ";
  case 3:
    return "     ";
  case 4:
    return "    ";
  case 5:
    return "   ";
  case 6:
    return "  ";
  case 7:
    return " ";
  default:
    return "";
  }
}
