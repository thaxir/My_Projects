#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc,char *argv[]){
  FILE *f1,*f2,*f3;
  char str1[26];
  char c;
  int i;
  
  if(argc!=3){
    return (-1);
  }
  
  f1=fopen(argv[1],"r");
  if(f1==NULL){
    printf("arxeio1 dn vrethike \n");
    return (-1);
  }
  f2=fopen(argv[2],"r+");
  if(f2==NULL){
    printf("arxeio2 dn vrethike \n");
    return (-1);
  }
  /*f3=fopen(argv[3],"w");
  if(f3==NULL){
    printf("arxeio3 dn vrethike \n");
    return (-1);
  }*/
 for(i=0;i<26;i++){
   fscanf(f1," %c",&str1[i]);
  }
  while(!feof(f2)){
    fscanf(f2,"%c",&c);
    if(feof(f2))break;
    if(isalpha(c)){
      for(i=0;i<26;i++){
	if(c==str1[i]){
	  break;
	}
      }
      fseek(f2,-1,SEEK_CUR);
      c=(char)'a'+i;
      fprintf(f2,"%c",c);
    }
    
  }
  fclose(f2);
  fclose(f1);
  printf("sto arxeio tha bei %s \n",str1);
  return 0;
}