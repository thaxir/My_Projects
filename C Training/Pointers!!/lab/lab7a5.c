#include<string.h>
#include<ctype.h>
#include<stdio.h>

#define SIZE 20

void setAddresses(char str1[], char str2[], char *addressTable[]);
void printAddresses(char *addressTable[]); 

int main (int argc, char *argv[]) {
	
	char *addressTable[2*SIZE];
	char str1[SIZE], str2[SIZE];
	char formatstring[15];

	sprintf(formatstring, "%%%ds %%%ds", SIZE-1, SIZE-1);
	printf("Enter two strings separated by space: ");
	scanf(formatstring, str1, str2);
	
	setAddresses(str1,str2,addressTable);
	printAddresses(addressTable);

	return 0;
			
}

/*
	setAddresses
	Parametroi: 
		- str1, str2: duo sumboloseires 
		- addressTable: pinakas apo deiktes se xaraktira. Arxika adeios, kai
					tha arxikopoiithei entos tis sunartisis.
	Timi epistrofis: Den epistrefei tipota
	Parenergeies : Meta to telos tis sunartisis, o pinakas addressTable
		exei arxikopoiithei.

	Leitourgia:
		Apothikeuei ston pinaka addressTable enallaks tis dieuthunseis 
		twn stoixeiwn twn str1 kai str2, ksekinwntas apo to str1.
		Gia paradeigma, an to str1 einai "abcd" kai to str2 einai "12"
		tote oi deiktes tou pinaka addressTable tha deixnoun sta 
		a, 1, b, 2, c, NULL, 3, NULL

	Simeiwsi: Oles oi upoloipes theseis tou pinaka addressTable prepei 
		na einai NULL
*/


void setAddresses(char str1[], char str2[], char *addressTable[]) {
	  int i ,j;
	  for (i=0;i<2*SIZE;i++){
	    addressTable[i]= NULL;
	  }
	 i=0;
	 j=0;
	 
	 while(str1[i]!='\0'){
	   
	    addressTable[j]=&str1[i];
	    i++;
	    j=i*2;
	  
	 }
	 i=0;
	 j=1;
	 while(str2[i]!='\0'){
	   
	   addressTable[j]=&str2[i];
	   i++;
	   j=j+2;
	   
	 }  
	  
	  
	  /*
	    else if((str1[i]=='\0') && (str2[i]!='\0')){
	      
		addressTable[i]=NULL;
		addressTable[i+1]=&str2[i];
		
	  }
	    else if((str1[i]!='\0') && (str2[i]=='\0')){
	    addressTable[i]=&str1[i];
	    addressTable[i+1]=NULL;
	    
	  }
	    else if((str1[i]=='\0') && (str2[i]=='\0')) {
	    addressTable[i]=NULL;
	    addressTable[i+1]=NULL;
	   
	  }*/
}

/*  printAddresses
    Parametroi: 
		- addressTable: pinakas apo deiktes pros kapoies theseis se string.
	Timi epistrofis: Den epistrefei tipota
	Parenergeies: Den uparxoun

	Leitourgia: Gia kathe thesi tou pinaka pou deixnei se 
		egkyri dieuthunsi ektupwnei ti thesi, ti dieuthunsi kai ta 
		periexomena se auti ti dieuthunsi. I morfi einai:
                    thesi: periexomena @ dieuthunsi allagi_grammis
        Gia paradeigma, an ta periexomena twn thesewn opou deixnoun oi
		deiktes tou pinaka einai a,1,b,2,c,NULL, d, mia pithani eksodos einai:
					0: a @ 0xbffff8e0
					1: 1 @ 0xbffff8cc
					2: b @ 0xbffff8e1
					3: 2 @ 0xbffff8cd
					4: c @ 0xbffff8e2
					6: d @ 0xbffff8e3
*/
void printAddresses(char *addressTable[]) {
	int i=0;
	while ( i<2*SIZE ){
	  if(addressTable[i]!=NULL){
	    printf("%d : %c @ %p \n",i,*addressTable[i],addressTable[i]);
	    i++;
	 }
	
	 else 
	   i=i+1;
	}
}