#include <stdio.h>
#include "azioni.h"


//funzione che evita l'immissione di caratteri ed accetta solo float
float evita_caratteri_float(){
	int c=0;
	float risposta = 0;
	char ch = 0;
	//ciclo per evitare risposte errate
	while(c==0){
		c = scanf("%f", &risposta);
		//svuoto il buffer
		while ((ch = getchar()) != '\n' && ch != EOF);
		//evito l'immissione di caratteri
		if(c==0)
			printf("\nI caratteri non sono validi. Inserire un numero.");
	}
	return risposta;
}


//funzione che evita l'immissione di caratteri ed accetta solo int
int evita_caratteri_int(){
	int c=0;
	int risposta = 0;
	char ch = 0;
	//ciclo per evitare risposte errate
	while(c==0){
		c = scanf("%d", &risposta);
		//svuoto il buffer
		while ((ch = getchar()) != '\n' && ch != EOF);
		//evito l'immissione di caratteri
		if(c==0)
			printf("\nI caratteri non sono validi. Inserire un numero.");
	}
	return risposta;
}


//funzione che elimina il \n scansionato dalla fgets
void fgets_newline_kill(char a[]){
    size_t sl = strlen(a);

    if(sl > 0 && a[sl - 1] == '\n')
    {
       a[sl - 1] = '\0';
    }
}





