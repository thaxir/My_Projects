#include<stdio.h>
#define SHAPE_LENGTH 10
#define SHAPE_HEIGHT 10

int main (int argc, char *argv[]) {
	
	FILE *infile, *outfile;
	int i, j, times, where;
	char c;

	if (argc != 3) {
		printf("Incorrect number of arguments\n");
		return 1;
	}
	infile = fopen(argv[1], "r");
	if (infile == NULL) {
		printf("Could not open file \"%s\"\n", argv[1]);
		return 1;
	}

	outfile = fopen(argv[2], "w");
	if (outfile == NULL) {
		printf("Could not open file \"%s\"\n", argv[2]);
		fclose(infile);
		return 1;
	}
	for (i=0; i<SHAPE_HEIGHT; i++) {
		for (j=0; j<SHAPE_LENGTH; j++) {
			c = fgetc(infile);
			fputc(c, outfile);
			fseek(outfile, SHAPE_LENGTH-1, SEEK_CUR);
			fputc(c, outfile);
			fseek(outfile, -SHAPE_LENGTH, SEEK_CUR);
		}
		fgetc(infile);
		fseek(outfile, SHAPE_LENGTH, SEEK_CUR);
		fputc('\n', outfile);
	}
	fclose(infile);
	fclose(outfile);
	return 0;

}
