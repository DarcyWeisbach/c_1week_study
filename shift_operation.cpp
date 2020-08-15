#include<stdio.h>

int main(){
  unsigned char x=1,y;
  y=x<<6;
  /*xを二進数表示して左シフトしたあと10進数に変換*/
  printf("x=%d,y=%d\n",x,y);
}
