#include <stdio.h>

/* Esegue la macchina virtuale con le istruzioni specificate. Ritorna 0 in caso di successo, 1 in caso di errore. */
int execute(unsigned int* sp, unsigned int* ip, int* registers, int* stack, int* istructions){
  unsigned int i=0;
  while(1){
    switch(istructions[*ip]){
      case 0:{ /*HALT*/
        /*printf("•Case 0 - HALT\n");*/
        return 0;
      }
      case 1:{ /*DISPLAY*/ /*Stampa su console il valore del registro indicato*/
        /*printf("•Case 1 - DISPLAY\n");*/
        printf("%d\n",registers[istructions[(*ip)+1]]);
        *ip=(*ip)+2;
        break;
      }
      case 2:{ /*PRINT STACK*/ /*Stampo da SP-N a SP-1*/
        /*printf("•Case 2 - PRINT STACK\n");*/
        for(i=(*sp)-1;i>=(*sp)-istructions[(*ip)+1];--i){
          printf("[%d]: %d\n",i,stack[i]);
        }
        *ip=(*ip)+2;
        break;
      }
      case 10:{ /*PUSH*/ /*Inserisce nella prima cella disponibile, SP+1*/
        if((*sp)<16384){
          stack[*sp]=registers[istructions[(*ip)+1]]; /*Inserisce il contenuto del registro indicato nella posizione libera dello stack*/
          *sp=(*sp)+1; /*Incrementa lo stack pointer*/
          *ip=(*ip)+2;
          /*printf("•Case 10 - PUSH\n");
          printf("ip %d, ", *ip);
          printf("prossima instr %d, ", istructions[*ip]);
          printf("sp %d, ", *sp);
          printf("valore nello stack %d\n\n", stack[(*sp)-1]);*/
        }
        else{
          printf("Errore: Push su stack pieno!\n");
          return -1;
        }
        break;
      }
      case 11:{ /*POP*/ /*Toglie l'ultimo elemento dello stack e lo inserisce nel registro indicato*/
        if((*sp)>0){
          *sp=(*sp)-1;
          registers[istructions[(*ip)+1]]=stack[*sp]; 
          *ip=(*ip)+2;
          /*printf("•Case 11 - POP\n");
          printf("ip %d, ", *ip);
          printf("prossima instr %d, ", istructions[*ip]);
          printf("sp %d, ", *sp);
          printf("valore nello stack %d\n\n", stack[(*sp)-1]);*/
        }
        else{
          printf("Errore: Pop su stack vuoto!\n");
          return -1;
        }
        break;
      }
      case 12:{ /*MOVE*/ /*Copia il valore P2 nel registro indicato*/
        registers[istructions[(*ip)+1]]=istructions[(*ip)+2];
        *ip=(*ip)+3;
        /*printf("•Case 12 - MOVE\n");
        printf("ip %d, ", *ip);
        printf("instr %d, ", istructions[*ip]);
        printf("sp %d, ", *sp);
        printf("stack %d\n\n", stack[*sp]);*/
        break;
      }
      case 20:{ /*CALL a subroutine*/ /*Push ip e jmp alla posizione indicata*/
        if((*sp)<16384){
          stack[*sp]=((*ip)+2); /*Push ip successivo*/
          *sp=(*sp)+1;
          *ip=istructions[(*ip)+1]; /*Jump alla prossima istruzione*/
          /*printf("•Case 20 - CALL\n");
          printf("ip %d, ", *ip);
          printf("instr %d, ", istructions[*ip]);
          printf("sp %d, ", *sp);
          printf("stack %d\n\n", stack[*sp]);*/
        }
        else{
          printf("Errore: push su stack pieno!\n");
          return -1;
        }
        break;
      }
      case 21:{ /*RETURN*/ /*Ritorno da chiamata a subroutine. POP in IP.*/
        if((*sp)>0){
          *ip=stack[(*sp)-1];
          *sp=(*sp)-1;
          /*printf("•Case 21 - RETURN\n");*/
        }
        else{
          printf("Errore: pop su stack vuoto!\n");
          return -1;
        }
        break;
      }
      case 22:{ /*JUMP incondizionato*/ /*Sostituisce il valore di IP con il valore indicato*/
        *ip=istructions[(*ip)+1];
        /*printf("•Case 22 - JUMP\n");
        printf("ip %d, ", *ip);
        printf("instr %d, ", istructions[*ip]);
        printf("sp %d, ", *sp);
        printf("stack %d\n\n", stack[*sp]);*/
        break;
      }
      case 23:{ /*JUMP se 0*/ /*Sostituisce il valore di IP con il valore indicato , sp-1=0 -> sp-1*/
        if((*sp)>0){
          if(stack[(*sp)-1]==0){
            *ip=istructions[(*ip)+1];
          }
          else {
            *ip=(*ip)+2;
          }
          *sp=(*sp)-1;
        }
        else{
          printf("Errore: pop su stack vuoto!\n");
          return -1;
        }
        /*printf("•Case 23 - JUMP se 0\n");
        printf("ip %d, ", *ip);
        printf("instr %d, ", istructions[*ip]);
        printf("sp %d, ", *sp);
        printf("stack %d\n\n", stack[*sp]);*/
        break;
      }
      case 24:{ /*JUMP se positivo*/ /*Sostituisce il valore di IP con il valore indicato , sp-1>0 -> sp-1*/
        if((*sp)>0){
          if(stack[(*sp)-1]>0){
            *ip=istructions[(*ip)+1];
          }
          else {
            *ip=(*ip)+2;
          }
          *sp=(*sp)-1;
        }
        else{
          printf("Errore: pop su stack vuoto!\n");
          return -1;
        }
        /*printf("•Case 24 - jump se positivo\n");
        printf("ip %d, ", *ip);
        printf("instr %d, ", istructions[*ip]);
        printf("sp %d, ", *sp);
        printf("stack %d\n\n", stack[*sp]);*/
        break;
      }
      case 25:{ /*JUMP se negativo*/ /*Sostituisce il valore di IP con il valore indicato , sp-1<0 -> sp-1*/
        if((*sp)>0){
          if(stack[(*sp)-1]<0){
            *ip=istructions[(*ip)+1];
          }
          else {
            *ip=(*ip)+2;
          }
          *sp=(*sp)-1;
        }
        else{
          printf("Errore: pop su stack vuoto!\n");
          return -1;
        }
        /*printf("•Case 25 - jump se negativo\n");
        printf("ip %d, ", *ip);
        printf("instr %d, ", istructions[*ip]);
        printf("sp %d, ", *sp);
        printf("stack %d\n\n", stack[*sp]);*/
        break;
      }
      case 30:{ /*Addizione*/ /*P1+P2 viene inserito in SP, temina in caso di overflow*/
        stack[*sp]=registers[istructions[(*ip)+1]]+registers[istructions[(*ip)+2]];
			  if(registers[istructions[(*ip)+1]] < 0 && registers[istructions[(*ip)+2]] < 0 && stack [*sp] > 0){
          printf("Errore: overflow su addizione!\n");
          return -1;
        }
			  else if(registers[istructions[(*ip)+1]] > 0 && registers[istructions[(*ip)+2]] > 0 && stack [*sp] < 0){
          printf("Errore: overflow su addizione!\n");
          return -1;
        }
        *ip=(*ip)+3;
        *sp=(*sp)+1;
        /*printf("•Case 30 - addizione\n");
        printf("ip %d, ", *ip);
        printf("prossima instr %d, ", istructions[*ip]);
        printf("sp %d, ", *sp);
        printf("valore nello stack %d\n\n", stack[(*sp)-1]);*/
        break;
      }
      case 31:{ /*Sottrazione*/ /*P1-P2 viene inserito in SP, temina in caso di overflow*/
        stack[*sp]=registers[istructions[(*ip)+1]]-registers[istructions[(*ip)+2]];
        if(registers[istructions[(*ip)+1]] > 0 && registers[istructions[(*ip)+2]] < 0 && stack [*sp] < 0){
          printf("Errore: overflow su sottrazione!\n");
          return -1;
        }
        else if(registers[istructions[(*ip)+1]] < 0 && registers[istructions[(*ip)+2]] > 0 && stack [*sp] > 0){
          printf("Errore: overflow su sottrazione!\n");
          return -1;
        }
        *ip=(*ip)+3;
        *sp=(*sp)+1;
        /*printf("•Case 31 - sottrazione\n");
        printf("ip %d, ", *ip);
        printf("prossima instr %d, ", istructions[*ip]);
        printf("sp %d, ", *sp);
        printf("valore nello stack %d\n\n", stack[(*sp)-1]);*/
        break;
      }
      case 32:{ /*Moltiplicazione*/ /*P1*P2 viene inserito in SP, temina in caso di overflow*/
        stack[*sp]=registers[istructions[(*ip)+1]]*registers[istructions[(*ip)+2]];
        if(registers[istructions[(*ip)+1]] < 0 && registers[istructions[(*ip)+2]] < 0 && stack [*sp] < 0){
          printf("Errore: overflow su moltiplicazione!\n");
          return -1;
        }
        else if(registers[istructions[(*ip)+1]] > 0 && registers[istructions[(*ip)+2]] > 0 && stack [*sp] < 0){
          printf("Errore: overflow su moltiplicazione!\n");
          return -1;
        }
        else if(registers[istructions[(*ip)+1]] < 0 && registers[istructions[(*ip)+2]] > 0 && stack [*sp] > 0){
          printf("Errore: overflow su moltiplicazione!\n");
          return -1;
        }
        else if(registers[istructions[(*ip)+1]] > 0 && registers[istructions[(*ip)+2]] < 0 && stack [*sp] > 0){
          printf("Errore: overflow su moltiplicazione!\n");
          return -1;
        }
        *ip=(*ip)+3;
        *sp=(*sp)+1;
        /*printf("•Case 32 - moltiplicazione\n");
        printf("ip %d, ", *ip);
        printf("prossima instr %d, ", istructions[*ip]);
        printf("sp %d, ", *sp);
        printf("valore nello stack %d\n\n", stack[(*sp)-1]);*/
        break;
      }
      case 33:{ /*Divisione*/ /*P1/P2 viene inserito in SP, temina in caso di overflow*/
        if(registers[istructions[(*ip)+2]]!=0){
          stack[*sp]=registers[istructions[(*ip)+1]]/registers[istructions[(*ip)+2]];
          *ip=(*ip)+3;
          *sp=(*sp)+1;
          /*printf("•Case 33 - divisione\n");
          printf("ip %d, ", *ip);
          printf("prossima instr %d, ", istructions[*ip]);
          printf("sp %d, ", *sp);
          printf("valore nello stack %d\n\n", stack[(*sp)-1]);*/
        }
        else {
          /*In caso di divisione per 0*/
          printf("Errore! Divisione per 0\n");
          return -1;
        }
        break;
      }
    }
  }
}
