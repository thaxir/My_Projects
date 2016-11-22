#include "project.h"

int main(int argc,char *argv[]){
   
  FILE *f,*f2;

  int i,id,j=0,exists=0,N_non_terms;
  char temp[N],filename[50];
  
  if(argc!=2){									//to arxeio me th grammatikh deinetai san eisodos apo th konsola 
    printf("input error\nplease insert grammar file\n");			//opote to programma termatizei an den dw8ei
    exit(0);
  
  }else{
  
    f=fopen(argv[1],"r");							//anoigma tou arxeiou pou periexei th grammatikh
    
   for(i=0; argv[1][i]!='.'; i++){						//antigrafei tou onomatos xwris th katalh3h
	filename[i]=argv[1][i];
   }
   filename[i]='\0';
   id=find_outputID(filename);							//dhmiourgia tou onomatos tou arxeiou e3odou
   if(id==0){
      sprintf(filename,"%s.out",filename);
   }else{
      sprintf(filename,"%s%d.out",filename,id);
   }
   
   f2=fopen(filename,"w");							//anoigma tou arxeiou e3odou
    
  
  }
  
  N_non_terms=count_non_terms(f);						//upologismos tou plh8ous twn mh termatikwn
  f=fopen(argv[1],"r");
  struct gnode table[N_non_terms];						//kai dhmiourgia tou kurios pinaka
  
  
  while(!feof(f)){								
    
   fscanf(f,"%s",temp);  
    if(temp[0]=='<'){
	
	for(i=0;i<j;i++){
	  if(strcmp(table[i].non_term,temp)==0){
	    exists=1;
	  }
	}
	if(exists==0){
	
	  strcpy(table[j].non_term,temp);
	  table[j].parag=0;
	  table[j].roots[table[j].parag]=NULL;
	  do{
	       fscanf(f,"%s",temp);
	       if(temp[0]==';'){
		table[j].parag++;
		table[j].roots[table[j].parag]=NULL;
	       }else{
		 //printf("%s \n",temp);
		 table[j].roots[table[j].parag]=addtolist(table[j].roots[table[j].parag],temp);
	       
	       }
	  }while(temp[0]!='}');
	  
	  
	  
	  j++;
	
	  
	}
        exists=0;
    }
    
  }

  createAstory(0,N_non_terms,table,1,f2);							//paragwgh istorias
  deleteall(N_non_terms,table);									//apeleu8erwsh olhs ths dunamikhs mnhmhs
  fclose(f);											//kleisimo olwn ton anoixtwn arxeiwn
  fclose(f2);

return 0;
}
