#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 50
#define R 3

struct vivlia{
  char title[N];
  float price;
  struct vivlia *next_vivlia;
  struct vivlia *next_price;
};
typedef struct vivlia vivliaT;


void init_vivlia(vivliaT *pinakas[]){
  int i;
  for(i=0;i<26;i++){
    pinakas[i]=NULL;
  }
}
void init_prices(vivliaT *prices[]){
  int i;
  for(i=0;i<10;i++){
    prices[i]=NULL;
  }
}
void sort_titles(vivliaT *onomata[]){
  vivliaT *curr,*run,*min;
  int i=0;
  
  while(i<R){
    if(onomata[i]==NULL){
      i++;
    }
    curr=onomata[i];
    if(curr->next_vivlia==NULL){
      i++;
    }
    for(curr=onomata[i];curr->next!=NULL;curr=curr->next){
      min=curr;
      for(run=curr->next
    
      
  
  

void insert(vivliaT *titloi[],vivliaT *times[],char vivlio[],float timh){
  vivliaT *curr,*runner,*runner1,*prev;
  int i,j;
  
  curr=(vivliaT*)malloc(sizeof(vivliaT));
  
  strcpy(curr->title,vivlio);
  curr->price=timh;
  curr->next_vivlia=NULL;
  curr->next_price=NULL;
  
  i=vivlio[0]-'A';
  if(titloi[i]==NULL){
    titloi[i]=curr;
  }
  else{
    for(runner=titloi[i];runner->next_vivlia!=NULL;runner=runner->next_vivlia);
    runner->next_vivlia=curr;
  }
  
  j=timh/10;
  if(times[j]==NULL){
    times[j]=curr;
  }
  else{
    for(runner1=times[j];runner1->next_price!=NULL;runner1=runner1->next_price);
    runner1->next_price=curr;
  }
}
  
      


void save(FILE *fp,vivliaT *titloi[],int n){
 int i;
 
  vivliaT*node;
  for(i=0;i<n;i++){
    node=titloi[i];
    while(node!=NULL){
      fprintf(fp," %s\n",node->title);
      node=node->next_vivlia;
      
    }
  }
}
    

void save1(FILE *fp,vivliaT *times[],int n){
int i;
 
  vivliaT*node;
  for(i=0;i<n;i++){
    node=times[i];
    while(node!=NULL){
      fprintf(fp," %f\n",node->price);
      node=node->next_price;
      fflush(fp);
    }
  }
}

int main (int argc,char *argv[]){
  
  FILE *f1,*f2,*f3;ur !=
  char str[30];
  char str1[30];
  char voithitiko_vivlia[N];
  float voithitiko_price;
  vivliaT *onomata[26];
  vivliaT *times[10];
  
  int epilog;
  

  init_prices(times);
  init_vivlia(onomata);
  
  
  f1=fopen(argv[1],"r");
  if(f1==NULL){
    printf("file not found! \n");
    exit(1);
  }
  strcpy(str,argv[1]);
  strcat(str,".title");
  f2=fopen(str,"w");
  if(f2==NULL){
    printf("file is not created! \n");
    exit(1);
  }
  strcpy(str1,argv[1]);
  strcat(str1,".prices");
  f3=fopen(str1,"w");
    if(f3==NULL){
    printf("file is not created! \n");
    exit(1);
  }
  
  
  while(!feof(f1)){
    fscanf(f1,"%s",voithitiko_vivlia);
    fgetc(f1);
    fscanf(f1,"%f",&voithitiko_price);
    fgetc(f1);
    if(feof(f1))break;
    insert(onomata,times,voithitiko_vivlia,voithitiko_price);
  }
  
  printf("thes ektypwsh timwn pata 2 thes ektypwsh titlwn pata 1 \n");
  scanf("%d",&epilog);
   switch (epilog){
     case 1 :
        save(f2,onomata,26);
	break;
     case 2 : 
       save1(f3,times,10);
       break;
   }
  fclose(f1);
  fclose(f2);
  fclose(f3);
  
  
  return 0;
}