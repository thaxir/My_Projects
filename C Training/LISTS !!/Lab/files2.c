#include<stdio.h>

int main (int argc, char *argv[]) {
	int i, len, begin, end;
	char c, first , last;
	FILE *file;
	if (argc!=2) {
		printf("Missing filename\n");
		return 1;
	}

	file = fopen(argv[1], "r+");
	if (file == NULL) {
		printf("Could not open file \"%s\" for reading/writing\n", argv[1]);
		return 1;
	}
/*
	end = -3;
	fseek(file, end, SEEK_END);
	c = fgetc(file);
*/

	len = -1;
	do {
		len++;
		c = fgetc(file);
	} while (c!='\n');
/*	printf("%c\n", c); */

	begin = 0;
	end = -3;
	for (i=0; i<len/2; i++) {
		fseek(file, begin, SEEK_SET);
		first = fgetc(file);
		fseek(file, end, SEEK_END);
		last = fgetc(file);
		fseek(file, -1, SEEK_CUR);
		fputc(first, file);
		fseek(file, begin, SEEK_SET);
		fputc(last, file);
		begin++;
		end--;
	}
		
		
	fclose(file);
	return 0;
}
	
