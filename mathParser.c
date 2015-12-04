//#include <stdio.h>
//#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 60

typedef struct node{
	float number;
	struct node *next;
	struct node *previous;
}operand;

typedef struct node2{
	char character;
	struct node2 *next;
	struct node2 *previous;
}operator;

char* isOperator(char);
char* calculate(char *);
void separate(char *, char *);
void toPostfix(char *, char *);
int priority(char);
void pushOperator(operator **, char);
void pushOperand(operand **, float);
void popOperator(operator **);
void popOperand(operand **);
float evaluateExpresion(char *);
int testParenthesis(char *);
void operate(char, float, operand**);
//Operaciones
int factorial(int);

char *operators = "*-+/!()^qsct?";

//descomentar para debugear el parser!

//int main_math(int argc, char const *argv[]){ //nombrar math para probar independientemente
//	
//	char *string = NULL;
//	char *result = malloc( MAX );
//
//	string = (char*)malloc(sizeof(char)*MAX);
//
//	printf("Submit your infix expresion: \n");
//	scanf("%s",string);
//	result = calculate(string);
//	printf("%s\n",result);
//	
//	free(string);
//
//	return 0;
//}

char* isOperator(char character){
	return strchr(operators, character);
}

char* calculate(char string[MAX]){
	
	if(string[0] == '='){

		char separated[MAX], postfix[MAX], *newString = NULL;
		char* result_str = malloc( MAX );
		float result;

		newString = strtok(string,"=");
		separate(newString, separated);
		toPostfix(separated, postfix);

		result = evaluateExpresion(postfix);
		sprintf( result_str, "%3.2f", result );
		
		return result_str;
	}
	
	else
		return string;
}

void separate(char original[MAX], char separated[MAX]){

	int i = 0,j = 0;

	for(i=0; i<=strlen(original); i++){
		if(isOperator(original[i])){
			if(original[i]== '-' ){
				if(i == 0 || isOperator(original[i-1]))
					separated[j++] = '?';
				else
					separated[j++] = original[i];
			}

			else{
				if(original[i]=='s'){
					if(original[i+1] == 'q')
						separated[j++] = 'q';
						i+=3; //From now on we ignore the remaining cause we'll eval sqrt
				}

				if(original[i]== 's'){
					separated[j++] = original[i];
					i+=2; //sin
				}

				if(original[i]== 'c'){
					separated[j++] = original[i];
					i+=2; //sin
				}

				if(original[i]== 't'){
					separated[j++] = original[i];
					i+=2; //tan
				}
			}
			
			separated[j++] = ' ';	
		}

		else{
			separated[j++] = original[i];
			if(isOperator(original[i+1]))
				separated[j++] = ' ';
		}
	}

}

void toPostfix(char string[MAX], char postfix[MAX]){

	int i = 0;
	char *aux = NULL;
	aux = strtok(string," ");

	operator *stack = NULL;

	do{
		if ( isOperator(aux[0]) ) {
			switch ( aux[0] ) {
				case '(':
					pushOperator(&stack , aux[0]);
					break;
					case ')':
while ( stack->character != '(' ) {
	postfix[i++] = stack->character;
	postfix[i++] = ' ';
	popOperator(&stack);
}
popOperator(&stack);
break;
default:

while(stack && priority(aux[0]) < priority(stack->character)){
	postfix[i++] = stack->character;
	postfix[i++] = ' ';
	popOperator(&stack);
}
pushOperator(&stack, aux[0]);
break;
}
}
else{
	postfix[i++] = '\0';

	if(aux[0]== 'e')
		strcat(postfix, "2.7182818");
	else
		strcat(postfix, aux);

	strcat(postfix, " ");
	i = strlen(postfix);
}
}while((aux = strtok(NULL, " ")) !=NULL);

while( stack ) {
	postfix[i++] = stack->character;
	postfix[i++] = ' ';
	popOperator(&stack);
}
postfix[i] = '\0';
}

int priority(char operator) {
	switch (operator) {
		case '+': case '-': return 1;
		case '*': case '/': return 2;
		case '^': case '!': case 's': case '?': case 'q': case 'c': case 't':return 3;
		case '(': return 0;
	}
}

void pushOperator(operator **head, char character){
	operator *new = (operator *)malloc(sizeof(operator));
	new->character = character;
	new->previous = NULL;
	
	if(*head){
		new->next = (*head);
		(*head)->previous = new;
		(*head) = new;
	}
	else{
		(*head)= new;
		new->next = NULL;
	}
}

void pushOperand(operand **head, float num){
	operand *new = (operand *)malloc(sizeof(operand));
	new->number = num;
	new->previous = NULL;
	
	if(*head){
		new->next = (*head);
		(*head)->previous = new;
		(*head) = new;
	}
	else{
		(*head)= new;
		new->next = NULL;
	}
}

void popOperator(operator **head){
	if((*head)->next){
		(*head)= (*head)->next;
		free((*head)->previous);
	}
	else{
		operator *temp = (*head);
		(*head)= NULL;
		free(temp);
	}
}

void popOperand(operand **head){
	if((*head)->next){
		(*head)= (*head)->next;
		free((*head)->previous);
	}
	else{
		operand *temp = (*head);
		(*head)= NULL;
		free(temp);
	}
}

float evaluateExpresion(char string[MAX]){
	char *aux = NULL, space[2] = " ";
	//operator * operators = NULL; //calla al compilador
	operand * operands = NULL;
	float temp;

	aux = strtok(string, space);	
	do{
		if(isOperator(aux[0])){
			temp = operands->number;
			popOperand(&operands);
			operate(aux[0], temp, &operands);
		}
		else
			pushOperand(&operands, atof(aux));

	}while((aux = strtok(NULL, space)) != NULL);
	
	
	return operands->number;
	
}

int testParenthesis(char string[MAX]){
	int i;
	int counter =0;
	
	for(i=0; string[i] != '\0'; i++){
		if(string[i] == '(')
			counter++;
			if(string[i] == ')')
				counter--;
		}
		if(counter == 0)
			return 1;
		else
			return 0;
	}

	void operate(char character, float op1, operand** head){
		switch(character){
			case '+':
			(*head)->number += op1;
			break;
			case '-':
			(*head)->number -= op1;
			break;
			case '*':
			(*head)->number *= op1;
			break;
			case '/':
			(*head)->number /= op1;
			break;
			case '^':
			(*head)->number = pow((*head)->number, op1);
			break;
			case '!':
			pushOperand(head, factorial((int)op1));
			break;
			case 'q': 
			pushOperand(head, sqrt((int)op1));
			break;
			case 's': 
			pushOperand(head, sin((double)op1));
			break;
			case 'c': 
			pushOperand(head, cos((double)op1));
			break;
			case 't': 
			pushOperand(head, tan((double)op1));
			break;
			case '?':
			pushOperand(head, op1*-1);
			break;
		}
	}

	int factorial(int n){
		if(n<=1)
			return 1;
		else
			return (n*factorial(n-1));
	}
