#include <stdio.h>
#include <stdlib.h>
struct charges{
 // arr is  an array of double and  indexes are characters in the  way of 'A'-65==0 
    double arr[26];
    long long int road;
};
 /* Multiplying  the  structure  of charges by distance*/
void multiply(const struct charges arr[],double *write_arr,int distance,int  j){
    for(int i=0;i<26;i++){
        write_arr[i]+=(distance*arr[j].arr[i]);
    }
}
void route_planner(double *write_arr, const struct charges sections[],long long int k,long long int from1,long long int to1 ){
    unsigned int j = 0;
    long long  int curr_dist=0,distance=0;
 // Initialization
    for(int nuller=0;nuller<26;nuller++){
        write_arr[nuller]=0;
    }
    if(from1==0){

        if(k==1) {
            multiply(sections,write_arr,to1,j);
        }

        // All whole sections are being  summed up and  as it  goes through the  sections it  multiplies those  charges that it concerns  of.  
        while(curr_dist<to1 && j<k ){
            curr_dist+=sections[j].road;
            multiply(sections,write_arr,sections[j].road,j);
            ++j;
        }
        --j;

        // The whole distance  is  counted then complement of  the  last section and the  whole distance from the beginning 
        unsigned int distance=curr_dist-to1;
        multiply(sections,write_arr,distance,j);
    }
    else{
        curr_dist=0,distance=0;
        while (j<k){
            curr_dist+=sections[j].road;
            ++j;
            if(curr_dist>from1)break;
        }
        --j;
        if(from1<curr_dist && to1<curr_dist && j<k){distance=to1-from1;
            multiply(sections,write_arr,distance,j);
        }
        else {
            distance = curr_dist - from1;
            multiply(sections, write_arr, distance, j);

            while (curr_dist  < to1 ) {
                ++j;
                curr_dist += sections[j ].road;
                if(curr_dist>to1){distance=sections[j].road-(curr_dist-to1);   multiply(sections,write_arr,distance,j);break;}
                multiply(sections,write_arr,sections[j].road,j);
                if(j+1==k)break;
            }
        }
    }
}

int main()
{
    char brace=' ', com_brace=' ',colon=' ',bracket=' ',letter=' ',comma=' ',op=' '; 
    double  value=0;
    long long int counter=0;
    long long int sum=0; 
    long long int  from,to; 
    double write_in_array[26];
    int scan=0;
    long long int comma_printer=0,from1=0,to1=0;

    printf("Myto:\n");
    if(scanf(" %c",&brace )!=1 || brace !='{'){ printf("Nespravny vstup.\n" );return 1; }
    long long  int size=10;
    long long int i=0;
    long long int length=0;
// Allocating  memory for an array of structures && Validating  the  input && Inserting the input
    struct charges *poplatky=(struct charges*)calloc(size,sizeof(struct charges));
    while (scanf(" %c %lld %c",&bracket,&length,&colon )==3 && colon ==':') {
        if (bracket !='[' || length <=0 ) {
            printf("Nespravny vstup.\n");free(poplatky);
            return 1;
        }
        while(scanf(" %c %c %lf %c",&letter,&op,&value,&comma )==4  ) {
            if(((int)letter)<65 || ((int)letter)>90 || op != '=' ){
                printf("Nespravny vstup.\n");
                free(poplatky);
                return 1;
            }
            if(i+3==size){ size*=2;
               poplatky=(struct charges*)realloc(poplatky,size*sizeof(struct charges)); }
            if(comma !=',')break;
            poplatky[i].arr[letter - 65] = value;poplatky[i].road = length;
        }
        if(comma !=']') {
            printf("Nespravny vstup.\n");
            free(poplatky);return 1;
        }
        if(comma==']'){
            poplatky[i].arr[letter - 65] = value;
            poplatky[i].road = length;++i;
            ++counter;
            if(i+3==size){
                size*=2;poplatky=(struct charges*)realloc(poplatky,size*sizeof(struct charges));
            }

             //Copying  the  charges  that were in the last sections to the  new ones  if there  are not those  types of charges
            for(int  m=0;m<26;m++) {
                poplatky[i].arr[m] = poplatky[i-1].arr[m]; }
        }
        if (scanf(" %c",&com_brace )!=1  ||  (com_brace !='}' && com_brace !=',')){
            printf("Nespravny vstup.\n");
            free(poplatky);
            return 1;
        }
        if(com_brace=='}')break;
    }
    if(com_brace!='}' || colon != ':'){
        printf("Nespravny vstup.\n");
        free(poplatky);
        return 1;
    }
   // The length of the whole road
    for(int f=0;f<counter;f++){ 
        sum+=poplatky[f].road; 
        }  
    printf("Hledani:\n");
    while((scan=scanf(" %lld %lld",&from,&to))==2){

       // Validation of input
        if(from==to || to>sum || from>sum || from <0 || to<0){
            printf("Nespravny vstup.\n");free(poplatky);return 1;
        }
        if(from>to){to1=from;from1=to;}
        else{
            to1=to;from1=from;
        }
        route_planner(write_in_array,poplatky,counter,from1,to1);
        printf("%lld - %lld: ",from,to);
        for(unsigned int printer=0;printer<26;printer++){
    
           // To prevent  the case when the  comma  will be  misplaced at the  end of output
            if(write_in_array[printer]>0) {
                if(comma_printer!=0)
                    printf(",");
                printf(" %c=%lf",printer + 65, write_in_array[printer]);++comma_printer; }
        }
        comma_printer=0;
        printf("\n"); }
    if(scan==0) { printf("Nespravny vstup.\n");free(poplatky);return 1; }
    free(poplatky);
    return 0;
}





