#include <stdio.h>
#define MAXVALUE 1024

/*Funzione che legge la prima riga del file e ritorna il numero di istruzioni*/
/* Return 0 in caso di fallimento */
int number_of_istructions(char *namefile){
  FILE *input;
  int n=0;
  char buf[MAXVALUE]; /*Array abbastanza grande da contenere 1024 caratteri per riga*/
  char* str;
  /*Apro il file e controllo che esista*/
  input = fopen(namefile, "r");
  if(!input){
  	printf("File non trovato");
    	return 0;
  }
  /*Acquisisco riga per riga finché arrivo a quella contenente il primo numero intero*/
  str = fgets(buf, MAXVALUE, input);
  while(buf[0]==';'){
    if(buf[0]=='\n' || buf[0]==' '){
      printf("Errore: file con errori al suo interno!\n");
      return 0;
    }
    str = fgets(buf, MAXVALUE, input);
  }
  /*Leggo da str l'intero che rappresenta il numero di istruzioni, assegnandolo a n*/
  sscanf(str, "%d", &n);
  return n;
}

/*Leggo riga per riga il file, salvando le istruzioni nell'array passato come parametro*/
/* Return 0 in caso di fallimento, 1 in caso di successo */
int from_file_to_array(char *namefile, int* istructions){
  FILE *input;
  int i=0;
  int prova;
  char buf[MAXVALUE];
  char* str;
  /*Apro il file e controllo che esista*/
  input = fopen(namefile, "r");
  if(!input){
    printf("File non trovato!\n");
    return 0;
  }
  /*Salto la/le prime righe (il primo numero (letto nella funzione precedente) ed eventuali commenti)*/
  str = fgets(buf, MAXVALUE, input);
  while(!sscanf(str, "%d", &prova))
    str = fgets(buf, MAXVALUE, input);
  /*Leggo finché non raggiungo la fine del file e SE leggo un intero lo assegno, altrimenti passo alla prossima riga*/
  str = fgets(buf, MAXVALUE, input);
  while(str){
    if(buf[0]=='\n' || buf[0]==' '){
      printf("Errore: file con errori al suo interno!\n");
      return 0;
    }
    if (sscanf(str, "%d", istructions+i))
      i++;
    str = fgets(buf, MAXVALUE, input);
  }
  /*Chiudo il file*/
  fclose(input);
  return 1;
}
