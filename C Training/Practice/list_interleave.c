#include <stdio.h>
#include <stdlib.h>

typedef struct list_node {
    int val;
    struct list_node *prev;
    struct list_node *next;
} list_t;

list_t *head1, *head2;



/* Mhn asxoleiste me ayto to tmhma - Begin */
list_t sentinel1, sentinel2;

void initialize() {
    head1 = &sentinel1;
    head2 = &sentinel2;
    head1->next = head1->prev = head1;
    head2->next = head2->prev = head2;
}
/* Mhn asxoleiste me ayto to tmhma - end */



int insert_front(list_t *list, int elem) {
    list_t *new_node;
    
    new_node=(list_t*)malloc(sizeof(list_t));
    if(new_node==NULL){
      return 1;
    }
    new_node->val=elem;
    new_node->next=list->next;
    new_node->prev=list;
    new_node->next->prev=new_node;
    new_node->prev->next=new_node;
    
    return 0;
    

}



void interleave(list_t *list1, list_t *list2) {
   list_t *curr1,*curr2,*temp;
   curr1=list1->next;
   curr2=list2->next;
   
   while(curr2!=list2){
     temp=curr2;
     curr2=curr2->next;
     curr2->prev=list2;
     list2->next=curr2;
     
     temp->next=curr1->next;
     temp->prev=curr1;
     temp->next->prev=temp;
     curr1=curr1->next->next;
   }
}
void print(list_t *list1){
  list_t *curr;
  
  curr=list1;
  while(curr!=NULL){
    printf("%d",curr->val);
    curr=curr->next;
  }
}

int main(int argc, char* argv[]) {

/* Mhn asxoleiste me ayto to tmhma - Begin */
    initialize();
/* Mhn asxoleiste me ayto to tmhma - End */
    
    insert_front(head1, 4);
    insert_front(head1, 6);
    insert_front(head1, 2);
    insert_front(head2, 3);
    insert_front(head2, 5);
    insert_front(head2, 1);
    print(head2);
}
