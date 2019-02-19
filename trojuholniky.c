#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

struct triangle{
                double len_a;
                double len_b;
                double len_c;
               };

double max(double  a , double  b)
{
 double max= ( fabs(a - b) <__DBL_EPSILON__*10 ) ? a : b ;
 return max;
}
int input( struct triangle * a ) 
{
   double len_a=0,len_b=0,len_c=0,a_b=0;
   double b_c=0,a_c=0,a1=0,a2=0,b1=0,b2=0,c1=0,c2=0;
   char l_bracket,brace,r_bracket1,bracket,r_bracket,r_brace1;
   char s_collon1,s_collon3,s_collon2,r_bracket2,comma1;
   char comma2,l_bracket1,commam,bracism,commam1;

    if (scanf(" %c %c",&brace,&bracket)==2  && bracket !='[' && brace=='{'  ){
           ungetc(bracket,stdin);

           // Input type {A ,B ,C} && input validation && Triangle  validation

           if (scanf ("%lf %c %lf ",&len_a,&commam,&len_b )!=3 || commam !=',')
	   {
	    printf("Nespravny vstup.\n");
	    return 1;
	   }
		if(scanf("%c %lf %c",&commam1,&len_c,&bracism)!=3 || commam1 !=',' || bracism!='}'){
                      printf("Nespravny vstup.\n");
                      return 1;
                      }
        if (fabs(len_a+len_b-len_c)<=__DBL_EPSILON__*max(len_a,len_b)*100 ||len_a <0 
            ||fabs(len_b+len_c-len_a)<=__DBL_EPSILON__*max(len_b,len_c)*100 ||len_b<0 ||len_c <0 
            ||fabs(len_a+len_c-len_b) <=__DBL_EPSILON__*max(len_a,len_c)*100){
                      printf("Neplatny trojuhelnik.\n");
		      return 1;
                     }
                  a->len_a=len_a;a->len_b=len_b;a->len_c=len_c;
   }
    if (brace !='{'){
               printf("Nespravny vstup.\n");
               return  1 ;
              }   else if (bracket =='['){

                 //Input type {[x1,y2],[x2,y2],[x3,y3]} && Input validation && Triagle validation


              if(scanf("%lf %c %lf ",&a1,&s_collon1,&a2)!=3){
		      printf("Nespravny vstup.\n");
		      return 1;
	              }if(scanf(" %c %c %c",&r_bracket,&comma1,&l_bracket)!=3){
			      printf("Nespravny vstup.\n");
			      return 1;
		      }if(scanf(" %lf %c %lf ",&b1,&s_collon2,&b2)!=3){ 
			      printf("Nespravny vstup.\n");
			      return 1;
		      } if(scanf(" %c %c %c ",&r_bracket1,&comma2,&l_bracket1)!=3){
			      printf("Nespravny vstup.\n"); 
			      return 1;
		      }if(scanf(" %lf %c %lf ",&c1,&s_collon3,&c2)!=3){
                              printf("Nespravny vstup.\n");
                              return 1;
	              }if(scanf(" %c %c",&r_bracket2,&r_brace1)!=2){
                              printf("Nespravny vstup.\n");
                              return 1;
	              }if ( r_brace1 != '}' || s_collon1 !=';' || s_collon2 !=';' || s_collon3 !=';' || r_bracket != ']' || r_bracket1 !=']' ||
		            r_bracket2 !=']' || comma1 !=','  || comma2 !=',' || l_bracket != '[' || l_bracket1 !='['){
	 	              printf("Nespravny vstup.\n");
	                      return 1;		
       		       }

                  // Sides a,b,c


                  a_b=sqrt((b1-a1)*(b1-a1)+(b2-a2)*(b2-a2));
		  b_c=sqrt((c1-b1)*(c1-b1)+(c2-b2)*(c2-b2));
		  a_c=sqrt((c1-a1)*(c1-a1)+(c2-a2)*(c2-a2));
                    if(fabs(a_b+b_c-a_c)<= __DBL_EPSILON__*10*max(a_b,b_c) || fabs(a_b+a_c-b_c)<=__DBL_EPSILON__*10*max(a_b,a_c) || fabs(a_c+b_c-a_b)<=__DBL_EPSILON__*10*max(a_c,b_c)){
                  printf("Neplatny trojuhelnik.\n");
                  return 1 ;
             }

               //Values in the structure  are changed

               a->len_a=b_c;a->len_b=a_c;a->len_c=a_b;
	      }        
		   return 0;
                  }
void swap_comp(double * a,double* b)
{
 if (*a > *b)
 {
 double  temp;
 temp=*a;
 *a=*b;
 *b=temp;
  }
}
int main ( int argc, char * argv [] ){
   struct triangle troj1,troj2;
   printf("Trojuhelnik #1:\n");
   if (input(&troj1))              
       return 1;
   printf("Trojuhelnik #2:\n");
  if(input(&troj2))  
     return 1;

             // Function swap_comp compares sides and swaps them
               double obvod1,obvod2;
	       swap_comp(&troj2.len_a, &troj2.len_b);
	       swap_comp(&troj2.len_a, &troj2.len_c);
	       swap_comp(&troj2.len_b, &troj2.len_c);
	       swap_comp(&troj1.len_a, &troj1.len_b);
	       swap_comp(&troj1.len_a, &troj1.len_c);
               swap_comp(&troj1.len_b, &troj1.len_c);  
               obvod1=troj1.len_a+troj1.len_b+troj1.len_c;
	       obvod2=troj2.len_a+troj2.len_b+troj2.len_c;

	     // Sides are equal of  both triangles
  
	    if (fabs(troj2.len_a-troj1.len_a) <= __DBL_EPSILON__*10*max(troj2.len_a,troj1.len_a) &&
		fabs(troj2.len_b-troj1.len_b )<= __DBL_EPSILON__*10*max(troj2.len_b,troj1.len_b) &&
	        fabs( troj2.len_c-troj1.len_c) <= __DBL_EPSILON__*10*max(troj2.len_c,troj1.len_c)){		    
		    printf("Trojuhelniky jsou shodne.\n");
		    return 0;
	    }
	    if (fabs(obvod1-obvod2)<__DBL_EPSILON__*max(obvod1,obvod2)*10){
		     printf("Trojuhelniky nejsou shodne, ale maji stejny obvod.\n"); 
		     return 0; 
	    }

             // Radius  of one triangle is  bigger than the other one

	    else if (fabs(obvod2>obvod1)  ){

	             printf("Trojuhelnik #2 ma vetsi obvod.\n");
		     return 0;
	    }             
	    else if (obvod2 < obvod1){
	             printf("Trojuhelnik #1 ma vetsi obvod.\n");
	             return 0;
	    }
  #ifndef __PROGTEST__    
  #endif /* __PROGTEST__ */
    return 0;
   }
