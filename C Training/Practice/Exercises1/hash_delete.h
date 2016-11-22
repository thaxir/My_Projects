#ifndef _HASHTABLE_
#define _HASHTABLE_

#define SIZE 13  /* To megethos tou pinaka apo listes */

/* Orismos kombou listas. */
typedef struct node {
	char word[27];  	/* Periexomena kombou */
	struct node * next;	/* Epomenos kombos sti lista */
} hashNode;

hashNode* table[SIZE];	/* Orismos pinaka listwn. Kathe stoixeio tou pinaka
			   einai deiktis pros ton prwto kombo tis listas. */

/*
 * hash(word)
 * Parametros: Mia sumboloseira.
 * Epistrefei: Enan akeraio anamesa sto 0 kai to SIZE-1.
 * Perigrafi: I sunartisi auti xrisimopoieitai gia na brethei se poio 
 *		keli tou pinaka prepei na topothetithei i sumboloseira.
 */
int hash(char word[]) ;

/* 
 * initTable()
 * Parametros: Den uparxei
 * Epistrefei: Tipota
 * Perigrafi: Arxikopoiei ton pinaka
 */
void iniTable();

/* 
 * printTable()
 * Parametros: Den uparxei
 * Epistrefei: Tipota
 * Perigrafi: Ektupwnei tis lekseis pou periexontai ston pinaka apo listes.
 */
void printTable();

/*
 * insert(word)
 * Parametros: Mia sumboloseira
 * Epistrefei: Tipota
 * Perigrafi: Xrisimopoiei ti sunartisi hash gia na brei ti thesi (lista)
 * 		tou pinaka opou prepei na eisaxthei i leksi word kai 
 *		tin eisagei.
 *		An uparksei opoiodipote problima, ektupwnetai ena sxetiko
 *		minuma lathous kai i insert epistrefei.
 */
void insert(char word[]);

#endif
