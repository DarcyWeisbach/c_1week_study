#include<stdio.h>
double product(double x,double y);
double average(double s,double t);
double minValue(double u,double v);
int main(){
  double a,b,mul,min,ave;
  a=33.33;
  b=44.44;
  mul = product(a,b);
  printf("a=%f b=%f mul=%f\n",a,b,mul);
  ave = average(a,b);
  printf("a=%f b=%f average=%f\n",a,b,ave);
  min = minValue(a,b);
  printf("a=%f b=%f min=%f\n",a,b,min);
  return 0;
}
double product(double x, double y){
  return x*y;
}
double average(double s,double t){
  return (s+t)/2;
}
double minValue(double u,double v){
  double min;
  min = u;
  if(min>v){
    min = v;
  }
  return min;
}
