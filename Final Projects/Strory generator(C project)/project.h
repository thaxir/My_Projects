#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PARAG 10
#define N 60

struct node{

  char str[N];
  struct node *nxt;

};

struct gnode{

  char non_term[N];
  int parag;
  struct node *roots[MAX_PARAG];

};

extern void createAstory(int i,int K,struct gnode table[],int out,FILE *outfile);
extern int find_outputID(char filename[]);
extern int count_non_terms(FILE *f);
extern struct node *addtolist(struct node *root,char str[N]);
extern struct node *deletelist(struct node *d);
extern void list_printer(struct node *root);
extern void deleteall(int K,struct gnode table[]);