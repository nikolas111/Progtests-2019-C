#include <stdlib.h>
#include <stdio.h>


int main ( int argc, char * argv [] )
{
int  value=0;
printf ("ml' nob:\n");
if (scanf ("%d",&value)!=1){
	printf("luj\n");
	return 1;
}
/*Only  usage of switch-case according to the  variable  value*/
switch (value)
{
	case 1 :
		printf("Qapla'\nnoH QapmeH wo' Qaw'lu'chugh yay chavbe'lu' 'ej wo' choqmeH may' DoHlu'chugh lujbe'lu'.\n");
		break;
	case 2 : 
		printf("Qapla'\nQu' buSHa'chugh SuvwI', batlhHa' vangchugh, qoj matlhHa'chugh, pagh ghaH SuvwI''e'.\n");
		break;
	case 3 : 
		printf("Qapla'\nqaStaHvIS wa' ram loS SaD Hugh SIjlaH qetbogh loD.\n");
		break;
	case 4 :
		printf("Qapla'\nHa'DIbaH DaSop 'e' DaHechbe'chugh yIHoHQo'.\n");
		break;
	case 5 :
		printf("Qapla'\nleghlaHchu'be'chugh mIn lo'laHbe' taj jej.\n");
		break;
	default :
		printf("luj\n");
		break;
}




#ifndef __PROGTEST__
#endif /* __PROGTEST__ */
  return 0;
} 

