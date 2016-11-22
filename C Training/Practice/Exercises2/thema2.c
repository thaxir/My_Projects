#include <stdio.h>
#include <stdlib.h>

int main(int argc,char*argv[]){
  int n,i;
  char **words;
  
  
  printf("vale poses protaseis tha boun \n");
  scanf("%d",&n);
  words=malloc(n);
  
  for(i=0;i<n;i++){
    
    printf("vale protash no %d \n",i);
    words[i]=(char*)malloc(10*sizeof(char));
    scanf("%9s",words[i]);
  }
  for(i=0;i<n;i++){
    printf("%s\n",words[i]);
  }
  return 0;
}
    