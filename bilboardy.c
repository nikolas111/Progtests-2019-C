#include <stdlib.h>
#include <stdio.h>

void quick(int number[],int first,int last){
    int i, j, pivot, temp;
    if(first<last){
        pivot=first;
        i=first;
        j=last;
        while(i<j){
            while(number[i]<=number[pivot]&&i<last)
                i++;
            while(number[j]>number[pivot])
                j--;
            if(i<j){
                temp=number[i];
                number[i]=number[j];
                number[j]=temp;
            }
        }
        temp=number[pivot];
        number[pivot]=number[j];
        number[j]=temp;
        quick(number,first,j-1);
        quick(number,j+1,last);
    }
}
void  billboard(int positions[],int dist , int  i,int range)
{
    int j=0;
    int  counter=0;int current_dist=dist;
    for ( j=1;j<=i;j++){
        if( (current_dist-positions[j])<=0  ){
            if(current_dist != positions[j]) current_dist=positions[j-1];
            ++counter;
            --j;
            if(current_dist+dist >range-1)break;
            if(current_dist < range && current_dist >range-dist){++counter;break;}
            current_dist+=dist;
        }
        if(j==i && current_dist <range)
            ++counter;
    }
    printf("Billboardu: %d\n",counter );
}

int main()
{

    char comma_o_r_bracket,bracket,semicollon;
    int i=1;
    int range;
    int position;
    int max=0;
    int positions[1000000];
    positions[0]=0;
    printf("Mozna umisteni:\n");
    if (scanf("%d %c %c",&range,&semicollon,&bracket )!=3 || range <= 0 || semicollon !=':' || bracket !='{'){
        printf("Nespravny vstup.\n");
        return 1;
    }
    while(scanf(" %d %c",&position,&comma_o_r_bracket)==2 ){

        // Validation of input && Insertion of  input

        if ( (comma_o_r_bracket=='}') && ( position>0) && position < range) {
            if(position<1 || position>range-1)
            {
                printf("Nespravny vstup.\n");
                return 1;
            }
            positions[i]=position;
            break;
        }
        if(( comma_o_r_bracket!=','&& comma_o_r_bracket !='}')  || position<0 || position >range ){
            printf("Nespravny vstup.\n");
            return 1;
        }
        if(position<1 || position>range-1)
        {
            printf("Nespravny vstup.\n");
            return 1;
        }

        positions[i]=position;
        ++i;
        if(i>1000000){
            printf("Nespravny vstup.\n");
            return 1;
        }
    }
    if (comma_o_r_bracket!='}') {
        printf("Nespravny vstup.\n");
        return 1;
    }
    int  diff=0;
    int  dist=0;

  // Quicksorting  the  array called positions
    quick(positions,1,i);
    for (int  k=1;k<=i;k++){
        diff=(positions[k]-positions[k-1]);
        if (diff > max ){
            max=diff;
        }
    }
    int scan=0;

    printf("Vzdalenosti:\n");
    while ((scan = scanf("%d",&dist)) == 1) {
        if (dist < 0 || dist==0  ) {
            printf("Nespravny vstup.\n");
            return 1;
        }
        if (dist < max  || range-positions[i]>dist )printf("N/A\n");
        else
          // Printing out the number  of  bilboards  that can be  placed in that length.
            billboard(positions,dist,i,range);
    }
    if(scan==0 ){printf("Nespravny vstup.\n");return 1;}

    return 0;
}
