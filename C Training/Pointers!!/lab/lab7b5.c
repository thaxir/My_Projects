#include<string.h>
#include<stdio.h>

#define SIZE 20

char * reverse (char*string){
  int i,j;
  char str1[SIZE];
  char str2[SIZE];
 
  for(i=0;i<SIZE;i++){
    str1[i]='\0';
    str2[i]='\0';
  }
  
  for(i=0; string[i]!='-'; i++){
    str1[i]=string[i];
  }
  
  i=i+1;
  
  for (j=0; string[i] != '\0'; j++){
    str2[j]=string[i];
    i++;
  }
  
  return strcpy(string,strcat(strcat(str2,"-"),str1));
  
}
  


int main (int argc, char *argv[]) {
	
	char string[SIZE];
	char formatstring[15];
	

	printf("Enter string: ");
	sprintf(formatstring, "%%%ds", SIZE-1);
	scanf(formatstring, string);
	
	

	printf("%s\n", reverse (string));
	return 0;
}
