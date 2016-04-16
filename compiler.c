#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
void folding(int argc, char* argv[]);

int main(int argc, char* argv[]) {
	int i = 0; 
	int digCount = 0; // number of digits (+) and (-)
	int opCount = 0; // number of ops
	int foundError = 0; // stores if error found
	int variableFound = 0; // sees if a variable (x, y, z) is part of RPN

	for(i=1; i<argc; i++) { // traverses through string and sorts operators and digits into arrays
		if(strcmp(argv[i], "+")==0 | strcmp(argv[i], "*")==0 | strcmp(argv[i], "-")==0) { 
			opCount++;
			/* this finds a way to see if at the current state, the RPN expression is valid
			note to self: you look to see if the next thing is an operator, if so, ignore this as the next
			operator could balance the equation - however, if it isn't an operator, then you see if the # of
			ops is greater than digits - 1 - which will cause a problem like in 2 "*" 2. Also ensures next 
			element in array is not null */
			if(argv[i+1] && opCount > digCount - 1 && !((strcmp(argv[i+1], "+")==0) || (strcmp(argv[i+1], "*")==0) || 
				(strcmp(argv[i+1], "-")==0))) {
				fprintf(stderr, "Error: You may have too many or too few operators.\n");
				foundError = 1;
				break;
			}
		
		} else if((isdigit(*argv[i])) || (atoll(argv[i]) < 0)) // input is digit (+) or (-)
			digCount++; 
		
		else if(strcmp(argv[i], "x")==0) { // checks if value is x
			digCount++;
			variableFound = 1;
		}

		else if(strcmp(argv[i], "y")==0) { // check if value is y
			digCount++;		
			variableFound = 1;
		}
 		
 		else if(strcmp(argv[i], "z")==0) { // check if value is z
 			digCount++;
 			variableFound = 1;
 		}

		else  { // invalid input
			fprintf(stderr, "Error: %s is not a valid input\n", argv[i]); 
			foundError = 1;
			break;
		}
	}

	if(opCount != digCount - 1 && !foundError) { // checks if the number of digits corresponds correctly with number of ops
		fprintf(stderr, "Error: There are not enough operators, or too many operators.\n");
		foundError = 1;
	}

	//assembly starts here
	if(!foundError && !variableFound) { // if there are no variables in RPN & no error
		folding(argc, argv);
	}

	if(!foundError && variableFound) { // this will only print as long as an error isn't found in the input
	printf("\t.global compute\n");
	printf("compute:\n"); 
	
	for(i=1; i<argc; i++) { 		
		if(strcmp(argv[i], "+")==0 | strcmp(argv[i], "*")==0 | strcmp(argv[i], "-")==0) { // checks for operator
			printf("\tpopq %%r10\n");
			printf("\tpopq %%r11\n");
			if(strcmp(argv[i], "+")==0) { // if addition
				printf("\taddq %%r10, %%r11\n");
	 		}
			else if(strcmp(argv[i], "-")==0) { // subtraction
				printf("\tsubq %%r10, %%r11\n");
			}
			else if(strcmp(argv[i], "*")==0) { // multiplication
				printf("\timul %%r10, %%r11\n");
			}
			printf("\tpushq %%r11\n");
		}	

		else if((isdigit(*argv[i])) || (atoll(argv[i]) < 0)) // input is positive digit
			printf("\tpushq $%s\n", argv[i]);

		else if(strcmp(argv[i], "x")==0) // checks if value is x
			printf("\tpushq %%rdi\n");

		else if(strcmp(argv[i], "y")==0) // check if value is y
			printf("\tpushq %%rsi\n");			
 		
 		else if(strcmp(argv[i], "z")==0) // check if value is z
 			printf("\tpushq %%rdx\n");
		}	
	}

	if(!foundError & variableFound) { // this prints as long as an error is not found
	printf("\tpopq %%rax\n");
	printf("\tretq\n"); }
	return 0;
}

// folding method if there are no variables
void folding (int argc, char* argv[]) {
		int i = 0;
        int sp = 1; // stack pointer 
        long long stack[argc - 1]; // "stack"
        stack[0] = 0; // piece of stack to manipulate

        for(i=1 ; i<argc ; i++) {
            if((isdigit(*argv[i])) || (atoll(argv[i]) < 0)) { // if digit (+) or (-), assign to stack
                stack[sp] = atoll(argv[i]);
                sp++;
                } 
            else if(strcmp(argv[i], "+")==0 | strcmp(argv[i], "*")==0 | strcmp(argv[i], "-")==0) { // if operator
                sp--; 
                if(strcmp(argv[i],"+")==0) { 
                    long long result = stack[sp] + stack[sp-1]; // does addition if op = +
                    sp--;
                    stack[sp] = result;
                    sp++; }

                else if(strcmp(argv[i],"*")==0) { // multiplies if op = *
                    long long result = stack[sp] * stack[sp-1];
                    sp--;
                  	stack[sp] = result;
                    sp++; }

                else if(strcmp(argv[i],"-")==0) {
                    long long result = stack[sp-1] - stack[sp]; // subtracts if op = -
                    sp--;
                    stack[sp] = result;
                    sp++; }    
                }
        }
        printf("\t.global compute\n");
        printf("compute:\n");
        printf("\tmovq $%lld, %%rax\n", stack[1]);
        printf("\tretq\n");
}
