#include <stdlib.h> 
#include <stdio.h>

  void analyze_function(long long int LO, long long int HI, int base, char c) {
    long long int  all_zero=0, ciphre=0, seq_zero=0, seq=0, remainder=0;
    for (int i = LO; i <= HI; ++i) {
      int temp = i;
      if (!i ) //i==0
        ++ciphre, ++all_zero,++seq_zero;
      while (temp ) { // temp !=0
        remainder = temp % base;
        temp /= base;
        if (!remainder ) { // remainder==0
          ++seq;
          ++all_zero;
        }
        if (remainder ) { // remainder !=0
          if (seq > seq_zero) {
            seq_zero = seq;
          }
          seq = 0;
        }
        ++ciphre;
      }
    }
    if (c == 'l')
      printf("Cifer: %lld\n", ciphre);
    if (c == 'z')
      printf("Nul: %lld\n", all_zero);
    if (c == 's')
      printf("Sekvence: %lld\n", seq_zero);
  }
int main() {
  long long int LO=0, HI=0;
  int base=0;
  char s_collon, ra_bracket, f_char, collon, ch, la_bracket;
  printf("Zadejte intervaly:\n");
  while (scanf(" %c", &ch) == 1) {
    if (ch == '<') {

     // Input  validation input  <from;to> function_character && 
     //printing out according to the  function_character the  number  of  all_zero in a  number,all ciphres or the longest sequence of zeros  

      if (scanf("%lld %c %lld ", &LO, &s_collon, &HI) != 3 || s_collon != ';' || LO > HI || LO<0 || HI <0) {
        printf("Nespravny vstup.\n");
        return 1;
      }
      if (scanf(" %c %c", &ra_bracket, &f_char) != 2 || ra_bracket != '>') {
        printf("Nespravny vstup.\n");
        return 1;
      }
      if (f_char == 'l' || f_char == 'z' || f_char == 's')
        analyze_function(LO, HI, 10, f_char);
      else {
        printf("Nespravny vstup.\n");
        return 1;
      }
    }
    else if (ch == 'r') {
      if (scanf(" %d %c %c %lld %c %lld %c %c",&base,&collon ,&la_bracket, &LO, &s_collon, &HI, &ra_bracket,&f_char) != 8 || la_bracket != '<' || s_collon != ';' || ra_bracket != '>' || base < 2 || base > 36 || LO > HI || LO<0 || HI<0|| collon !=':') {
        printf("Nespravny vstup.\n");
        return 1;
      }
      if (f_char == 'l' || f_char == 'z' || f_char == 's') {
        analyze_function(LO, HI, base, f_char);
      } else {
        printf("Nespravny vstup.\n");
        return 1;
      }
    } else {
      printf("Nespravny vstup.\n");
      return 1;
    }
  }
   #ifndef __PROGTEST__
  #endif /* __PROGTEST__ */
  return 0;
}
