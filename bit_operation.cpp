#include<stdio.h>

int main(void){
  char x=123,y;
  /*元々char型は1byteの整数型で文字を数字として扱っていただけintでも*/
  y= x & 0b11110000;
  /*今のC言語は二進数表記できてしまう
  教科書ではy=x&0xf0
  1111=f,0000=0である（2進数と16進数の対応*/
  printf("x=%d, y=%d",x,y);
  return 0;
}
