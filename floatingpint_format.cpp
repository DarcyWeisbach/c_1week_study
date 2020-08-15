#include<stdio.h>
#include<string.h>
/*doubleの中身を二進数表示するためのわかりやすいプログラム*/
int main(){
  double a;
  double trial;
  char t[sizeof(trial)];
  char c[sizeof(a)];
  /*daubleだと8バイトでcharは１バイトだからsizeofでバイト数の整数倍ができる*/
  int i,j,k;
  printf("数字を入力してください：");
  scanf("%lf",&a);
  memcpy(c,&a,sizeof(a));
  for(i=7;i>=0;i--){
    printf("c[%d]=%d\n",i,c[i]);
  }
  printf("\n");
  printf("sEEEEEEE EEEEdddd dddddddd...\n");
  for(i=sizeof(a)-1;i>=0;i--){
    for(j=sizeof(c[i])*8-1;j>=0;j--){
      k=c[i]&(1<<j);/*1をｊ個左シフト*/
      /*計算過程のchar型変数は2進数で表示されるときに10進数になる*/
      printf("%d",k?1:0);/*kが０じゃなければ１、０なら０*/
    }
    printf(" ");
  }
  printf("\n");
  return 0;
}
