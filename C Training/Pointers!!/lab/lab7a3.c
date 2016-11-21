#include<string.h>
#include<ctype.h>
#include<stdio.h>

#define SIZE 20

void setAddresses(char string[], char *uppercase[], char *lowercase[]);
void printAddresses(char *uppercase[], char *lowercase[]);

int main (int argc, char *argv[]) {
	
	char *uppercase[SIZE], *lowercase[SIZE];
	char string[SIZE];
	char formatstring[15];

	sprintf(formatstring, "%%%ds", SIZE-1);
	printf("Enter string: ");
	scanf(formatstring, string);
	
	setAddresses(string,uppercase,lowercase);
	printAddresses(uppercase,lowercase);

	return 0;
			
}

/*
	setAddresses
	Parametroi: 
		- string: mia sumboloseira
		- uppercase: pinakas apo deiktes se xaraktira. Arxika adeios, kai
					tha arxikopoiithei entos tis sunartisis.
		- lowercase: pinakas apo deiktes se xaraktira. Arxika adeios, kai
					tha arxikopoiithei entos tis sunartisis.
	Timi epistrofis: Den epistrefei tipota
	Parenergeies : Meta to telos tis sunartisis, oi pinakes uppercase kai
		kai lowercase exoun arxikopoiithei.

	Leitourgia:
		Apothikeuei ston pinaka uppercase tis dieuthunseis sto string 
		opou emfanizontai kefalaia grammata sto string (me ti seira pou
		emfanizontai apo tin arxi pros to telos tou string).
		Apothikeuei ston pinaka lowercase tis dieuthunseis sto string 
		opou emfanizontai mikra grammata sto string (me ti seira pou
		emfanizontai apo tin arxi pros to telos tou string).

	Simeiwsi: Pithanws na uparxoun perissoteres theseis ston kathe pinaka
		apo oti emfaniseis mikrwn 'i kefalaiwn sto string. Prepei na 
		skeftite mia katallili arxikopoiisi tou pinaka gia autes tis 
		periptwsseis, kai na anaferete ti lusi sas stin parapanw 
		perigrafi tis leitourgias tis sunartisis. 
*/


void setAddresses(char string[], char *uppercase[], char *lowercase[]) {
	int i,j,k;
	for (i=0; i<SIZE; i++){
	  uppercase[i]=NULL;
	  lowercase[i]=NULL;
	}
	j=0;
	k=0;
	
	for(i=0; string[i]!= '\0'; i++){
	  
	  if(isupper(string[i])){
	   uppercase[j]=&string[i];
	   j++;
	  }
	  
	  if(islower(string[i])){
	    lowercase[k]=&string[i];
	    k++;
	  }
	  
	  
	}
}
	    
	    
	    
  
  


/*  printAddresses
    Parametroi: 
		- uppercase: pinakas apo deiktes pros kapoies theseis enos string.
		- lowercase: pinakas apo deiktes pros kapoies theseis enos string.
	Timi epistrofis: Den epistrefei tipota
	Parenergeies: Den uparxoun

	Leitourgia: Gia kathe thesi tou pinaka uppercase pou deixnei se 
		egkyri dieuthunsi ektupwnei ti thesi, ti dieuthunsi kai ta 
		periexomena se auti ti dieuthunsi. Akolouthws kanei to idio 
		kai gia ton pinaka lowercase. I morfi einai:
                    thesi: periexomena @ dieuthunsi allagi_grammis
        Gia paradeigma, an to arxiko string einai a1Bcd, mia pithani
		eksodos einai:
						0: B @ 0xbffff83e
						0: a @ 0xbffff83c
						1: c @ 0xbffff83f
						2: d @ 0xbffff840
*/
void printAddresses(char *uppercase[], char *lowercase[]) {
	int i;
	for(i=0; i<SIZE ; i++){
	  if(uppercase[i]!=NULL){
	    printf("%d: %c @ %p\n",i,*uppercase[i],&uppercase[i]);
	  }
	}
	for(i=0; i<SIZE ; i++){
	  if(lowercase[i]!=NULL){
	    printf("%d: %c @ %p\n",i,*lowercase[i],&lowercase[i]);
	  }
	}
}
	
	  

