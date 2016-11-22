#include<stdio.h>

int main (int argc, char *argv[]) {
	int x = 3, y=0;
	if (y++) {
		printf("i sunthiki y++ einai alithis \n");
		printf("%d\n", y);
	}
	else if (y==0) {
		printf("i sunthiki y++ einai pseudis kai i sunthiki y==0 alithis\n");
		printf("%d\n", y);
	}
	else {
		printf("i sunthiki y++ einai pseudis kai i sunthiki y==0 pseudis\n");
		printf("%d\n", y);
	}
	return 0;
}
