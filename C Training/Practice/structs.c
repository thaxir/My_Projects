#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define TRUE 1
#define FALSE 0

#define NUM_BOOKS 5

typedef struct {
	int minute;	// lepto 0-59
	int hour;	// wra, 0-23
} timeT;

// bookRecord einai i eggrafi gia ena biblio.
// Ta pedia perigrafontai parakatw

typedef struct {
	char title[50]; 	// o titlos tou bibliou
	char author[50]; 	// to onoma tou suggrafea
	int year; 			// i xronia ekdosis
	int isOut; 			// boolean metabliti: TRUE an to biblio einai daneismeno
						// FALSE an den einai
	timeT time; 		// wra epistrofis
	int isBlank; 		// TRUE an i eggrafi einai adeia, FALSE an antistoixei se biblio
} bookRecord;


// stacks einai enas pinakas apo eggrafes. Oles oi theseis tou pinaka
// exoun mia eggrafi alla mono oi duo prwtes einai egkures (to isValid
// einai TRUE). Oi upoloipes einai akures kai den antistoixoun se biblia.



bookRecord stacks[NUM_BOOKS]=
    {
    {"C How To Program", "Deitel", 2006, FALSE, {0,  0}, TRUE} ,
    {"The Old Capital", "Yasunari Kawabata", 1996, FALSE, { 0, 0}, TRUE},
	{"", "", 0, FALSE, {0,0}, FALSE},
	{"", "", 0, FALSE, {0,0}, FALSE},
	{"", "", 0, FALSE, {0,0}, FALSE}
    };

    
int request_book(char titlos[],char sygrafea[]){
  int i;
  for(i=0;i<NUM_BOOKS;i++){
    if((strcmp(stacks[i].title,titlos)==0) && (strcmp(stacks[i].author,sygrafea)==0)){
      return 1;
    }
  }
    return 0;
}


int main () {
  char str1[50],str2[50];
  int vre;
  
  printf("dwse titlo vivliou kai sygrafea \n");
  fgets (str1, 50, stdin);
  str1[strlen(str1) -1]='\0';
  printf("dwse titlo vivliou kai sygrafea \n");
  fgets (str2, 50, stdin);
  str2[strlen(str2) -1]='\0';
  vre=request_book(str1,str2);
  if(vre==1){
    printf("vrethike\n");
  }
  else
    printf("den vrethike\n");
 
  return 0;
 }

