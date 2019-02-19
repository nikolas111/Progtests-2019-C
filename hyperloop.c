#ifndef __PROGTEST__
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#endif /* __PROGTEST__ */

/* Function  counts all possible combinations */
unsigned long long int non_duplicite_f(unsigned long long int length_h,unsigned int segment1,unsigned int segment2,unsigned int *c1,unsigned  int *c2)
{
 unsigned  int i=0;
 unsigned long long int combinations=0;
  while (i <= (length_h/segment1)) {
    if (((length_h-i*segment1)%segment2)==0) {
      ++combinations;
        *c1=i;
        *c2=(length_h-i*segment1)/segment2;
      }
    ++i;
  }
  return combinations;
}
unsigned long long int hyperloop ( unsigned long long int length,unsigned int s1, unsigned int s2,unsigned int bulkhead, unsigned int* c1,unsigned int * c2 )
{
 unsigned long long int length_of_hyperloop=length-bulkhead;
 unsigned int new_s1=s1+bulkhead;
 unsigned int new_s2=s2+bulkhead;
 unsigned long long int all_combination=0;

  /* Validation of  input */
  if ( length == bulkhead) {
   *c1=0;
   *c2=0;
   return 1;
      } 
  if (length <bulkhead) {
     return 0;
     }
  if (length==0) {
      return 0;
     }
  if(s1 > length && s2==0)return 0;
  if (s2 > length && s1==0)return 0;
  if (s1==0 && s2==0 ) return 0;
  if (s1>length && s2>length) return 0;
  if (s1==0 || s1 >length_of_hyperloop) {
  if((length_of_hyperloop%new_s2) !=0 ) return 0;
  *c2=length_of_hyperloop/new_s2;
  *c1=0;
  return 1;


}

  if (s1==s2) {
  if(length_of_hyperloop%new_s1==0){
    *c1=0;
    *c2=length_of_hyperloop/new_s1;
    return 1;
  }
  return 0;
}
  if (s2==0 || s2 >length_of_hyperloop) {
  if(length_of_hyperloop%new_s1 !=0) return 0;
     *c1=length_of_hyperloop/new_s1;
     *c2=0;
     return 1;
     }
  if ( s1 != 0 && s2 != 0 && s1 != s2 ) {
  all_combination=non_duplicite_f(length_of_hyperloop,new_s1,new_s2,c1,c2);
     }
  printf("%llu\n",all_combination );
  return all_combination;
}
#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
  unsigned int c1, c2;
  assert ( hyperloop ( 100, 4, 7, 0, &c1, &c2 ) == 4  && 4 * c1 + 7 * c2 + 0 * (c1 + c2 + 1) == 100 );
  assert ( hyperloop ( 123456, 8, 3, 3, &c1, &c2 ) == 1871 && 8 * c1 + 3 * c2 + 3 * (c1 + c2 + 1) == 123456 );
  assert ( hyperloop ( 127, 12, 8, 0, &c1, &c2 ) == 0 );
  assert ( hyperloop ( 127, 12, 4, 3, &c1, &c2 ) == 1 && 12 * c1 + 4 * c2 + 3 * (c1 + c2 + 1) == 127 );
  assert ( hyperloop ( 100, 35, 0, 10, &c1, &c2)== 1 && c2 == 0   && 35 * c1 + 10 * (c1 + 1) == 100 );
  assert ( hyperloop ( 110, 30, 30, 5, &c1, &c2 ) == 1   && 30 * c1 + 30 * c2 + 5 * (c1 + c2 + 1) == 110 );  c1 = 2;c2 = 7;
  assert ( hyperloop ( 110, 30, 30, 0, &c1, &c2 ) == 0 && c1 == 2 && c2 == 7 );  c1 = 4;c2 = 8;
  assert ( hyperloop ( 9, 1, 2, 10, &c1, &c2 ) == 0 && c1 == 4 && c2 == 8 );
  return 0;
}
#endif /* __PROGTEST__ */
