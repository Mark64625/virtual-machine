#include <stdio.h>

/* Stampa le istruzioni in formato mnemonico */
void print_istructions(int* istructions, int n){
    int i=0;
    while(i<n){
        switch(istructions[i]){
            case 0:{
                printf("[%d] HALT\n", i);
                i++;
                break;
            }
            case 1:{
                printf("[%d] DISPLAY R%d\n", i, istructions[i+1]);
                i+=2;
                break;
            }
            case 2:{
                printf("[%d] PRINT_STACK %d\n", i, istructions[i+1]);
                i+=2;
                break;
            }
            case 10:{
                printf("[%d] PUSH R%d\n", i, istructions[i+1]);
                i+=2;
                break;
            }
            case 11:{
                printf("[%d] POP R%d\n", i, istructions[i+1]);
                i+=2;
                break;
            }
            case 12:{
                printf("[%d] MOV R%d %d\n", i, istructions[i+1], istructions[i+2]);
                i+=3;
                break;
            }
            case 20:{
                printf("[%d] CALL %d\n", i, istructions[i+1]);
                i+=2;
                break;
            }
            case 21:{
                printf("[%d] RET\n", i);
                i++;
                break;
            }
            case 22:{
                printf("[%d] JMP %d\n", i, istructions[i+1]);
                i+=2;
                break;
            }
            case 23:{
                printf("[%d] JZ %d\n", i, istructions[i+1]);
                i+=2;
                break;
            }
            case 24:{
                printf("[%d] JPOS %d\n", i, istructions[i+1]);
                i+=2;
                break;
            }
            case 25:{
		printf("[%d] JNEG %d\n", i ,istructions[i+1]);
		i+=2;
                break;
            }
            case 30:{
		printf("[%d] ADD R%d R%d\n", i ,istructions[i+1],istructions[i+2] );
		i+=3;
                break;
            }
            case 31:{
		printf("[%d] SUB R%d R%d\n", i ,istructions[i+1],istructions[i+2] );
		i+=3;
                break;
            }
            case 32:{
		printf("[%d] MUL R%d R%d\n", i ,istructions[i+1],istructions[i+2] );
		i+=3;
                break;
            }
            case 33:{
		printf("[%d] DIV R%d R%d\n", i ,istructions[i+1],istructions[i+2] );
		i+=3;
                break;
            }
        }
    }
}
