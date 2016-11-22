#include <stdio.h>
#include <string.h>

struct test_struct{
    char firstName[20];
    char lastName[25];
    int aem;
};

union test_union{
    char firstName[20];
    char lastName[25];
    int aem;
};


typedef struct test_struct struct_T;
typedef union test_union union_T;

int main(int argc, char *argv[]) {
    struct_T student1, student2;
	union_T studentU1, studentU2;
    
	printf("Testing structs\n");
	
    strcat(student1.firstName, "Christos"); /* This is wrong. Find why with the debugger */
    strcat(student1.lastName, "Antonopoulos"); /* This is wrong. Find why with the debugger */
    student1.aem = 1976;
    
    student2 = student1;
    student2.aem = 1000;
    
    printf("Student 1 First name:%s\n", student1.firstName);
    printf("Student 1 Last name:%s\n", student1.lastName);    
    printf("Student 1 AEM:%d\n", student1.aem);

    printf("Student 2 First name:%s\n", student2.firstName);
    printf("Student 2 Last name:%s\n", student2.lastName);    
    printf("Student 2 AEM:%d\n\n\n", student2.aem);

    printf("Size of individual fields: %u + %u + %u\n", 20*sizeof(char), 25*sizeof(char), sizeof(int));
    printf("Size of struct test_struct: %u\n\n\n", sizeof(struct_T)); /* This may be different from the 
																	   sum of the lengths of all fields */
    printf("student1.firstName %p\n", student1.firstName); /* Observe that fields are with the same order in */
    printf("student1.lastName %p\n", student1.lastName);   /* memory as they are in the struct. However there*/ 
    printf("&student1.aem %p\n", &student1.aem);		   /* may be padding (gaps) between them, induced  */
														   /* by the compiler to align fields properly in mem */

	printf("\n\nTesting unions\n");
	/* Now let's do the same with unions */

	/* Use the debugger to observe what happens on each field when one of the fields changes */
	strcat(studentU1.firstName, "Christos"); /* This is wrong. Find why with the debugger */
    strcat(studentU1.lastName, "Antonopoulos"); /* This is wrong. Find why with the debugger */
    studentU1.aem = 1976;
    
    studentU2 = studentU1;
    studentU2.aem = 1000;
    
    printf("Student 1 First name:%s\n", studentU1.firstName);
    printf("Student 1 Last name:%s\n", studentU1.lastName);    
    printf("Student 1 AEM:%d\n", studentU1.aem);

    printf("Student 2 First name:%s\n", studentU2.firstName);
    printf("Student 2 Last name:%s\n", studentU2.lastName);    
    printf("Student 2 AEM:%d\n\n\n", studentU2.aem);

    printf("Size of individual fields: %u, %u, %u\n", 20*sizeof(char), 25*sizeof(char), sizeof(int));
    printf("Size of struct test_union: %u\n\n\n", sizeof(union_T)); /* One would expect this to be equal to the
																	   length of the larger field. However it 
																	   may be larger due to compiler induced
																	   padding (gaps) for alignment */
    printf("student1.firstName %p\n", studentU1.firstName); /* Observe that fields correspond to the same address */
    printf("student1.lastName %p\n", studentU1.lastName);   
    printf("&student1.aem %p\n", &studentU1.aem);		    

		
    return(0);
}
