/* I lusi tis askisis pou suzitithike simera sto frontistirio.
   
   Prosthikes: 
			- Ylopoiisi tis sunartisis multiply()
  			- Dimiourgia mias neas sunartisis i opoia analambanei
				na kanei olous tous elegxous egkurotitas tis eisodou.
			- Prosthiki sxoliwn pou epeksigoun ti leitourgia kathe
				mias sunartisis.
*/ 

#include<stdio.h>
#include<math.h>
#include<stdlib.h>

#define OK 0
#define INVALID_OPERATOR 1
#define INVALID_OPERAND 2

int verifyInput(int leftOp, int rightOp, char op);
int isValidOperator (char operator); 
int validOperands(int leftOp, int rightOp);
int add(int leftOp, int rightOp);
int multiply(int leftOp, int rightOp);
int numDigits(int number);

int main (int argc, char *argv[]) {

	int leftOp, rightOp;
	int result = 0;
	int errorCode;
	char op;

	
	do {
		scanf("%d%c%d", &leftOp, &op, &rightOp);
		errorCode = verifyInput(leftOp, rightOp, op);
		switch(errorCode) {
			case INVALID_OPERATOR: 
					printf("Unknown operator\n");
					continue;
			case INVALID_OPERAND:
					printf("Non-positive integers\n");
					continue;
		}
		switch(op)  {
			case '+': result = add(leftOp, rightOp);
					break;
			case '*': result = multiply(leftOp, rightOp);
					break;
		}

	} while (errorCode!=OK);
	printf("%d\n", result);
	return 0;
}

/************************************************
 * isValidOperator
 * Pairnei ws parametro ena xaraktira ki epistrefei
 * 1 an einai egkuros telestis (+ 'i *) diaforetika 0.
 ************************************************/
int isValidOperator (char operator) {
	return (operator == '+' || operator == '*');
}

/************************************************
 * validOperands
 * Pairnei ws parametrous duo akeraious telesteous
 * ki epistrefei 1 an einai kai oi duo thetikoi, 
 * diaforetika 0.
 ************************************************/
int validOperands(int leftOp, int rightOp) {
	return (leftOp > 0 && rightOp > 0);
}

/************************************************
 * add
 * Pairnei ws parametro duo thetikous akeraious
 * kai epistrefei ton akeraio pou prokuptei an 
 * epikolisoume to deutero akeraio sto telos tou
 * prwtou 
 ************************************************/
int add(int leftOp, int rightOp) {
	/* Enallaktiki ulopoiisi me xrisi strings
	char result[11]; // 11: gia na xwraei o megistos akeraios
	sprintf(result, "%d%d", leftOp, rightOp);
	return (atoi(result));
	*/
	return leftOp * pow(10, numDigits(rightOp)) + rightOp;
}

/************************************************
 * multiply
 * Pairnei ws parametro duo thetikous akeraious
 * kai epistrefei ton akeraio pou prokuptei an 
 * "prosthesoume" ton prwto akeraio ston eauto tou
 * toses fores oso einai i timi tou deuterou akeraiou.
 * I "prosthesi" metaksu duo akeraiwn orizetai ws
 * i epikolisi tou deuterou akeraiou sto telos tou prwtou
 ************************************************/
 
int multiply (int leftOp, int rightOp) {
	int i;
	int result = leftOp;
	for (i=0; i<rightOp-1; i++) {
		result = add(result, leftOp);
	}
	return result;
}

/************************************************
 * numDigits
 * Pairnei ws parametro enan akeraio kai epistrefei
 * to plithos psifiwn tou
 ************************************************/
int numDigits(int number) {
	return log10(number)+1;
}

/************************************************ 
 * verifyInput 
 * Pairnei ws parametrous ena telesti kai duo 
 * telesteous, ki epistrefei OK an einai egkyroi
 * 'i diaforetika kapoio kwdiko lathous:
 * INVALID_OPERATOR an den einai egkuros o telestis.
 * INVALID_OPERAND an den einai egkuroi oi telesteoi.
 ************************************************/
int verifyInput(int leftOp, int rightOp, char op) {
	if (!isValidOperator(op)) {
		return INVALID_OPERATOR;
	}
	if (!validOperands(leftOp, rightOp)) {
		return INVALID_OPERAND;
	}
	return OK;
}
