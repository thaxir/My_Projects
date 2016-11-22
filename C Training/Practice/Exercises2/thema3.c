#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define L 6
#define MAX 5

typedef struct{
  char stoixeio[L];
  int atom;
}chem;


void sort(chem pinakas[],int number){
  int i,j,temp,min;
  for(i=0;i<number;i++){
    min=i;
    for(j=i+1;j<number;j++){
      if(pinakas[j].atom<pinakas[min].atom){
	min=j;
      }
    }
      if(min!=i){
	temp=pinakas[i].atom;
	pinakas[i].atom=pinakas[min].atom;
	pinakas[min].atom=temp;
      }
   }
}	
    



int main(int argc,char*argv[]){
  FILE *fp;
  int i;
  chem pinakas[MAX];
  char str1[L];
  int am,number;
  
  if(argc!=2){
    exit(1);
  }
  
  fp=fopen(argv[1],"r");
  if(fp==NULL){
    printf("file not found \n");
    exit(1);
  }
  i=0;
  fscanf(fp,"%5s",str1);
  while(!feof(fp) && strcmp(str1,"XX")!=0 && i<MAX){
    fscanf(fp,"%d",&am);
    strcpy(pinakas[i].stoixeio,str1);
    pinakas[i].atom=am;
    fscanf(fp,"%5s",str1);
    i++;
  }
  number=i;
  for(i=0;i<number;i++){
    printf("%5s - %3d\n",pinakas[i].stoixeio,pinakas[i].atom);
  }
  sort(pinakas,number);
   for(i=0;i<number;i++){
    printf("%5s - %3d\n",pinakas[i].stoixeio,pinakas[i].atom);
  }
  return 0;
}
    