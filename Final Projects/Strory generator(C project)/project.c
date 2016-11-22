#include "project.h"

int num_of_chars=0;

//h sunarthsh pou paragei thn istoria
void createAstory(int i,int K,struct gnode table[],int out,FILE *outfile){

  // i = h 8esh tou mh termatikou ston kuriws pinaka
  
  struct node *s;
  int j,k;
  srand(time(NULL));
  k=rand()%table[i].parag;				//epilegetai tuxaia mia apo tis dia8esimes paragwges
  
  for(s=table[i].roots[k];s!=NULL;s=s->nxt){		//diatrexetai h lista ths paragwghs pou epilex8hke
    if(s->str[0]=='<'){					//an o komvos periexei mh termatiko stoixeio
      for(j=0;j<K;j++){					//vriskoume th 8esh tou ston kuriws pinaka
	if(strcmp(s->str,table[j].non_term)==0){
	    createAstory(j,N,table,out,outfile);	//kai 3anakaloume anadromika th sunarthsh paragwghs istorias
	}
      }
    }else{						//ean einai termatiko stoixeio ektypwnetai eite sthn konsola eite sto arxeio analoga me th metavlhth out
      if(out==0){
	printf("%s ",s->str);
      }else{
	num_of_chars+=fprintf(outfile,"%s ",s->str);	//h fprintf epistrefei to plh8os ton charakthrwn pou egrapse sto arxeio
	if(num_of_chars>60){				//opote xrhsimopoiontas mia ka8olikh metavlhth 3eroume ka8e pote prepei
	    fprintf(outfile,"\n");			//na alla3oume grammh
	    num_of_chars=0;
	}
      }
    }
  }
}

//epistrefei to id tou onomatos tou arxeiou e3odou kai pairnei san eisodo to onoma string prin th teleia
int find_outputID(char filename[]){

	  FILE *tmp=NULL;
	  char outputfile[50];
	  int id=0;

          do{  //dimiourgeia output simfona me tis prodiagrafes
	    
		if(id==0){
		
		    sprintf(outputfile,"%s.out",filename); 		//dhmiourgria tou output filename     
		    tmp=fopen(outputfile,"r"); 				//elegxos gia upar3h
   
		    if(tmp!=NULL){ 						// an ola phgan kala kai anoi3e to arxeio gia anagnwsh
			  fclose(tmp);					//to kleinoume kai dokimazoume gia id++
			  id++;
		    }
		
		}else{
		
		    sprintf(outputfile,"%s%d.out",filename,id); 		//dhmiourgria tou output filename     
		    tmp=fopen(outputfile,"r"); 				//elegxos gia upar3h
      
		    if(tmp!=NULL){ 						// an ola phgan kala kai anoi3e to arxeio gia anagnwsh
			  fclose(tmp);					//to kleinoume kai dokimazoume gia id++
			  id++;
		    }
		}
		
   
	}while(tmp!=NULL);    
  
	return id;
}

//epistrefei to plh8os twn mh termatikwn stoixeiwn mias grammatikhs pou deinatai san eisodos
int count_non_terms(FILE *f){

  char temp[N];
  int x=0;
  
  while(!feof(f)){
  
    fscanf(f,"%s",temp);  
    if(temp[0]=='{'){
	x++;
    }
    
  }
  fclose(f);
  return x;
}


//eisagei ena neo komvo sto telos ths listas
struct node *addtolist(struct node *root,char tmp[N]){

  struct node *l,*l1;
  for(l=root,l1=NULL;l!=NULL;l1=l,l=l->nxt);
  
  l=(struct node *)malloc(sizeof(struct node));
  strcpy(l->str,tmp);
  l->nxt=NULL;
  
  if(l1==NULL){		//prwth eisagwgh
    root=l;
  }
  else{
    l1->nxt=l;
  }

return root;
}


//apeleu8erwnei olh th mnhmh pou exei desmeutei gia mia lista (paragwgh)
struct node *deletelist(struct node *d){

  if(d->nxt!=NULL){
    return deletelist(d->nxt);
    free(d);
    
  }else{
    free(d);
    return NULL;
  }
  
}

//apeleu8erwnei olh th desmeumenh mnhmh
void deleteall(int K,struct gnode table[]){
  int i,j;
   for(i=0;i<K;i++){
  
    for(j=0;j<table[i].parag;j++){	//gia ka8e paragwgh kaleitai h deletelist 
	table[i].roots[j]=deletelist(table[i].roots[j]);
    }
  } 
  
}


//pernei san orisma ton root mias listas (mia paragwgh) kai thn ektypwnei (voh8htikh)
void list_printer(struct node *root){

  struct node *pr;
  if(root!=NULL){
    for(pr=root;pr!=NULL;pr=pr->nxt){
    
      printf("%s -> ",pr->str);
    
    }
    printf("\n");
  }
}