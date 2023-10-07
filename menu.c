#include <stdio.h>
#include <stdlib.h>
#include "menu.h"

//definisco una funzione per il menu
int menu_principale(){
	system("clear");
	int scelta =0;
	char ch; //dichiaro una variabile per resettare il buffer
	printf("\n");
	titolo();
        printf("                                                        Benvenuto!                                               \n");
	printf(BLUE);
	printf("					 1 - Login                                     \n");
	printf("					 2 - Registrazione                             \n");
	printf("					 3 - Esci                                      \n");
	printf(GREEN);
        printf("					 Benvenuto nel nostro sito! Cosa desideri fare? ");
	scanf("%d", &scelta);
        printf(RESET);
        while(ch = getchar() != '\n' && ch != EOF); //resetto il buffer
	return scelta; //ritorno 1 per il login, 2 per la registrazione, 3 per uscire
	}

//definisco la funzione per il menu admin

int menu_admin(){
	system("clear");
	char ch; //dichiaro una variabile per resettare il buffer
	int scelta = 0;
	while ((scelta != 1) && (scelta != 2) && (scelta != 3) && (scelta != 4) && (scelta != 5)){
		system("clear");
		printf("\n");
		titolo();
	        printf("                                                        Benvenuto!                                               \n");
		printf(BLUE);
		printf("					 1 - Gestisci magazzino                        \n");
		printf("					 2 - Crea nuova configurazione                 \n");
                printf("                                         3 - Modifica configurazioni in vendita        \n");
		printf("					 4 - Gestisci utenti                           \n");
		printf("                                         5 - Esci                                      \n");
		printf(GREEN);
		printf("					 Cosa desideri fare? ");
	        printf(RESET);
		scanf("%d", &scelta);
		while(ch = getchar() != '\n' && ch != EOF); //resetto il buffer
	}
	return scelta;
	}
//definisco la funzione per il menu utente base

int menu_utente_base(){
	system("clear");
	char ch; //dichiaro una variabile per resettare il buffer
	int scelta = 0;
	while ((scelta != 1) && (scelta != 2) && (scelta != 3) && (scelta != 4) && (scelta != 5) && (scelta != 6)){
		system("clear");
		printf("\n");
		titolo();
	        printf("                                                        Benvenuto!                                               \n");
		printf(BLUE);
		printf("					 1 - Visualizza le mie configurazioni          \n");
		printf("					 2 - Modifica configurazioni                   \n");
		printf("					 3 - Crea configurazione                       \n");
		printf("					 4 - Configurazioni in vendita                 \n");
		printf("					 5 - Sfoglia inventario                        \n");
		printf("                                         6 - Esci                                      \n");
		printf(GREEN);
		printf("					 Cosa desideri fare? ");
		printf(RESET);
		scanf("%d", &scelta);
		while(ch = getchar() != '\n' && ch != EOF); //resetto il buffer
	}
	return scelta;
	}

//definisco una funzione per il menu magazzino
int menu_magazzino(){
	system("clear");
	char ch; //dichiaro una variabile per resettare il buffer
        int scelta = 0;
        while ((scelta != 1) && (scelta != 2) && (scelta != 3) && (scelta != 4)){
        	system("clear");
                printf("\n");
                titolo();
                printf(BLUE);
                printf("                                         1 - Visualizza inventario                     \n");
                printf("                                         2 - Aggiungi componente                       \n");
                printf("                                         3 - Cancella componente                       \n");
                printf("                                         4 - Indietro                                  \n");
                printf(GREEN);
                printf("                                         Cosa desideri fare? ");
                printf(RESET);
                scanf("%d", &scelta);
                while(ch = getchar() != '\n' && ch != EOF); //resetto il buffer
        }
        return scelta;
}


int menu_utenti() {
system("clear");
        char ch; //dichiaro una variabile per resettare il buffer
        int scelta = 0;
        while ((scelta != 1) && (scelta != 2) && (scelta != 3)){
        	system("clear");
                printf("\n");
                titolo();
                printf(BLUE);
                printf("                                         1 - Visualizza utenti                         \n");
                printf("                                         2 - Cancella utente                           \n");
                printf("                                         3 - Indietro                                  \n");
                printf(GREEN);
                printf("                                         Cosa desideri fare? ");
                printf(RESET);
                scanf("%d", &scelta);
                while(ch = getchar() != '\n' && ch != EOF); //resetto il buffer
        }
        return scelta;
}
