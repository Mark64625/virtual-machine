# Macchina virtuale MIPS-like

Progetto per il test finale del Corso di Programmazione 2018-2019 (Università Ca' Foscari Venezia).
Il programma simula il funzionamento di una macchina virtuale con un linguaggio assembly fittizio, simile nella logica al MIPS, ma più semplice.

## Funzionamento

La macchina virtuale utilizza:
- uno stack di 64 kB (array di interi) ad accesso LIFO;
- un registro speciale SP (Stack pointer) che punta al prossimo spazio libero dello stack;
- un registro speciale IP (Istruction pointer) che punta alla prossima istruzione da eseguire;
- 32 registri (array di interi).

Essa riceve in input un file .cvm composto da numeri interi a capo ed eventuali commenti preceduti dal carattere ```;```. Qualsiasi altro carattere estraneo genererà un errore.
La macchina interpreta i numeri del file come istruzioni e relativi operandi e il suo unico output è un numero intero, il risultato del problema fornito in output.
La macchina è in grado di effettuare chiamate a subroutine, tramite le apposite funzioni CALL e RET, e salti condizionati o incondizionati.
L'insieme delle istruzioni con il loro simbolo mnemonico, valore in codice macchina, numero di parametri e descrizione, è allegato nel file "istruction_set.pdf".

Ci sono inoltre 4 file di prova con programmi diversi da far eseguire alla macchina.
- "fattoriale.cvm": Calcola il fattoriale di 5.
- "somma.cvm": Calcola la somma dei primi 100 numeri.
- "checksign.cvm": Restituisce -1 se n è negativo, 1 se è positivo.
- "sumsquares.cvm": Somma i quadrati dei primi 5 numeri.

## Installazione

Eseguire il makefile:
```make```

## Esecuzione

```./VM "comando" "nome del file"```

Dove "comando" è "esegui" oppure "stampa".
"Esegui" eseguirà il programma fornito in input e terminerà scrivendo il risultato,
"Stampa" stamperà a schermo i numeri del file corredati dal loro significato in istruzione assembly.

### Esempio

Input:
```./VM "esegui" "fattoriale.cvm"```

Output:
```120```

## Autori

*Marco Biesso*
