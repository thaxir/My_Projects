#include<stdio.h>

#define N 20
#define M 4
int main (int argc, char *argv[]) {
	int m1, m2, a, y, j, z, i, p, w;
	char str1[N], str2[M], str[24];

	do {
    a=0;
		printf("Enter word: \n");
	scanf(" %20s", str1);
	for (i=0; i<24; i++) {
		if ((str1[i]='-')) {
                a++; }	
	}} while (a!=1);
	
	printf("Enter inset:\n");
	scanf("%3s", str2);
	for (m1=0; str1[m1]!='\0'; m1++) {}
	for (j=0; j!='-'; j++) {}
	for (m2=0; str2[m2]!='\0'; m2++){}
	for (z=0; z<j; z++) {
	str[z]=str1[z];
	}
	w=0;
	for (y=z; y==(z+i); y++) {
		str2[z]=str[w];
		w++;
	}






	for (p=y; p==(m1+m2); p++) {
		str[p]=str1[j];
		j++;
	}
		
		
		
		
	printf("%s\n", str);
	
	
	
	
	
	return (0);
		
}
		
