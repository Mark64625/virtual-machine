#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leggi.h"
#include "esegui.h"
#include "stampa.h"

int main(int argc, char* argv[]){
  int n;
  unsigned int sp=0, ip=0; /*Registri speciali sp e ip*/
  int registers[32]={0}; /*Registri da R0 a R31*/
  int stack[16384]={0}; /*Stack di 64 kB*/
  int *istructions=NULL; /*Puntatore all'array dove verranno salvate le istruzioni*/

  if(argc!=3){
    printf("Errore: numero di parametri scorretto.\n");
    return 1;
  }

  /*Lettura del numero di istruzioni dal file specificato a riga di comando, se minore di 1, viene lanciato un errore e chiuso il programma*/
  if((n=number_of_istructions(argv[2]))<1){
    printf("Errore: Numero di istruzioni insufficiente o file non trovato!");
    return 1;
  }

  /*Viene allocato l'array per le istruzioni di dimensione corretta, se fallito, lancia un errore*/
  istructions=(int*)malloc(sizeof(int)*n);
  if(!istructions){
    printf("Errore: array non allocato correttamente.\n");
    return 1;
  }
  
  /*Viene letto il file specificato nella shell e assegnati i valori all'array delle istruzioni*/
  if(from_file_to_array(argv[2], istructions)){
    if(!strcmp(argv[1],"esegui")) /* In caso di ESEGUI */
      execute(&sp, &ip, registers, stack, istructions);
    else if(!strcmp(argv[1],"stampa")) /* In caso di STAMPA */
      print_istructions(istructions, n);
    else{
        printf("Errore: comando non corretto. Scegliere tra \"esegui\" e \"stampa\"\n");
        free(istructions); /*Liberazione della memoria allocata*/
        return 1;
    }
    free(istructions); /*Liberazione della memoria allocata*/
  }
  else{
    printf("Errore: file non trovato o errato!\n");
    free(istructions); /*Liberazione della memoria allocata*/
    return 1;
  }
  return 0;
}
