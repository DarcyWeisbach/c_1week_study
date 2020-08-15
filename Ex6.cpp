#include<stdio.h>
//cl /source-charset:utf-8 EX6.cpp /EHsc
int main(){
  double d_eps = 1.0;
  double d_tmp;
  for(d_tmp=d_eps+1.;d_tmp>1;){
    d_eps/=2.0;
    d_tmp=d_eps+1.0;
  }
  printf("double型のMachine epsilonは%-16e\n",2.0*d_eps);
  return 0;
}
