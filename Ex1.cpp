#include<stdio.h>

int main(void) {
  int i;
  for(i=1;i<=100;i++){
    if(i%35==0){
      printf("FizzBuzz ");
    }
    else if(i%7==0){
      printf("Buzz ");
    }
    else if(i%5==0){
      printf("Fizz ");
    }
    else{
      printf("%d ",i);
    }
  }
  return 0;
}
