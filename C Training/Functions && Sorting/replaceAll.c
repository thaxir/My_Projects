/* Frontistirio 18/11
	Diabaste treis sumboloseires, epibebaiwste oti i deuteri kai i triti 
	exoun to idio mikos kai meta antikatastiste kathe emfanisi tis deuteris
	stin prwti me tin triti.
*/

#include<stdio.h>
#include<string.h>

#define SIZE 20

void replaceAll(char word[], char target[], char replace[]);

int main (int argc, char *argv[]) {
	char word[SIZE], target[SIZE], replace[SIZE];
	char format[15];
	sprintf(format, "%%%ds", SIZE-1);
	printf("Enter a word: ");
	scanf(format, word);
	printf("Enter the target substring: ");
	scanf(format, target);
	printf("Enter the replacement string: ");
	scanf(format, replace);

	if (strlen(replace) != strlen(target)) {
		printf("Error: target and replacement should have the same size\n");
		return 0;
	}
	
	replaceAll(word, target, replace);

	printf("The new string is %s\n", word);
	return 0;
}
	
void replaceAll(char word[], char target[], char replace[]) {
	char *location;

	location = strstr(word, target);
	while (location != NULL) {
		strncpy(location, replace, strlen(replace));
		location = strstr(location+strlen(replace), target);
	}
}
