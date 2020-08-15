#include<stdio.h>
//cl /source-charset:utf-8 machine_epsilon.cpp /EHsc
int main(){
  double d_eps=1.0;
  double d_tmp;
  float f_eps=1.0;
  float f_tmp;
  /*while eps + 1 > 1 , deps /= 2 */
  for(d_tmp=d_eps+1;d_tmp>1;d_eps/=2,d_tmp=d_eps+1.0);
  printf("double型のMachine epsilonは%-16g\n",2.0*d_eps);
  printf("double型のUnit roundoffは%-16g\n",d_eps);

  for(f_tmp=f_eps+1;f_tmp>1;f_eps/=2,f_tmp=f_eps+1.0);
  printf("float型のMachine epsilonは%-16g\n",2.0*f_eps);
  printf("float型のUnit roundoffは%-16g\n",f_eps);
  printf("finish");
  return 0;
}
