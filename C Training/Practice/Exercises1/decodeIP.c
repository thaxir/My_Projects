#include<stdio.h>
#include<stdlib.h>

char findCode(char map[], char c) ;

int main(int argc, char *argv[]) {
	FILE *charmap, *origText, *encodedText;
	char map[26], code, throw, c;
	int i;
	if (argc != 3) {
		printf("Incorrect number of command-line arguments.\n");
		return 1;
	}
	
	charmap = fopen(argv[1], "r");
	if (charmap == NULL) {
		printf("Could not open file \"%s\" for reading\n", argv[1]);
		return 2;
	}
	encodedText = fopen(argv[2], "r+");
	if (encodedText == NULL) {
		printf("Could not open file \"%s\" for reading\n", argv[2]);
		return 2;
	}

	// read charmap
	for (i=0; i<26; i++) {
		fscanf(charmap, " %c ", &map[i]);
	}
		
	// read encoded text and decode
	while(!feof(encodedText)) {
		fscanf(encodedText, "%c", &c);
		if (feof(encodedText)) break;
		if (isalpha(c)) {
			fseek(encodedText, -1, SEEK_CUR);
			fprintf(encodedText, "%c", findCode(map, c));
		}
	}
	fclose(charmap);
	fclose(encodedText);
	return 0;
}	

char findCode(char map[], char c) {
	int i;	
	for (i=0; i<26; i++) {
		if (map[i] == c)
			return (char)(i+'a');
	}
	printf("Error in findCode ; this point should not be reached.\n");
	exit(1);
}
