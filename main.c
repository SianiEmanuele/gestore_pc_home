#include "login.h"
#include "menu.h"
#include <stdio.h>
#include <stdlib.h>


int main(){
int azione = 0; //variabile per il valore di ritorno del menu
utente* user= NULL; //puntatore a utente
int scelta = 0; //scelta varuavuke oer per i sottomenu
inventario inventario = carica_inventario(); //carico l'inventario da file
lista_utenti lista_utenti = carica_utenti(); //carico la lista utenti da file
lista_conf lista_conf_inventario = carica_lista_conf(); //carico la lista configurazioni da file
int mag = 0; //variabile per menu magazzino admin
int ut = 0; //variabile per menu utenti admin
char ch = 0; //variabile per svuotare il buffer
int controllo = 0; //variabile di controllo per uscire dal programma in caso di errori
int scelta_conf = 0; //variabile di controllo per eliminare o modificare una configurazione
int controllo_canc_conf = 0; //variabile per controllare la cancella configurazione
azione = menu_principale(); //lancio il menu principale

switch (azione) {
	case 1:
		user = login(lista_utenti);
		if(user == NULL){
		        finale(inventario, lista_utenti, lista_conf_inventario);
			exit(0);
			}
		printf("\nPremi invio per continuare");
		while(ch = getchar() != '\n' && ch != EOF);
		break;
	case 2: ;
		user = registrazione(lista_utenti);
		if(user == NULL) {
		        finale(inventario, lista_utenti, lista_conf_inventario);
			exit(0);
			break;
			}
		printf("\nPremi invio per continuare");
                while(ch = getchar() != '\n' && ch != EOF);
		break;
	case 3:
		printf("                                         Arrivederci!");
		while(ch = getchar() != '\n' && ch != EOF);
	        finale(inventario, lista_utenti, lista_conf_inventario);
		exit(0);
		break;
	default: 
		printf("Comando non valido!\n");
	        finale(inventario, lista_utenti, lista_conf_inventario);
                exit(0);
	}
switch (user -> type) {
	case 0: //utente base
		while (scelta != 6) {
			scelta = menu_utente_base();
			switch (scelta) {
				case 1 : //visualizza conf
					stampa_lista_conf (user -> lista_conf);
                                        printf("\nPremi invio per continuare");
                                        while(ch = getchar() != '\n' && ch != EOF);
                                        break;
				case 2 : //modifica conf
					scelta_conf = 0;
					if (user -> numero_conf == 0){
						printf("Non hai configurazioni da modificare. Premi invio per continuare\n");
						while(ch = getchar() != '\n' && ch != EOF);
						break;
					}
					printf("Digita 1 per modificare le tue configurazioni, 2 per eliminarne una\n");
					while ((scelta_conf != 1) && (scelta_conf != 2)){
						scelta_conf = evita_caratteri_int();
						if((scelta_conf != 1) && (scelta_conf != 2))
							printf("Input non valido!\n");
					}
					if (scelta_conf == 1) {
						controllo = modificare_conf(user -> lista_conf, inventario, user);
						if (controllo == 1)
							break;
					}
					else {
						controllo_canc_conf = cancellare_conf (user -> lista_conf);
 				                while(ch = getchar() != '\n' && ch != EOF);
						 if (controllo_canc_conf == 0) //se la cancellazione e' andata a buon fine diminuisco il numero di configurazioni
						 	user -> numero_conf--;
					}
					break;
				case 3: ; //crea conf
					configurazione conf = creazione_configurazione (inventario, user);
					if (conf == NULL){
						user -> numero_conf--;
						break;
					}
					inserimento_ordinato_conf (user -> lista_conf, conf);
					printf(GREEN);
					printf("\nEcco la tua nuova configurazione!\n");
					printf(RESET);
					stampa_config (conf);
					printf("\nPremi invio per continuare");
					while(ch = getchar() != '\n' && ch != EOF);
					break;
				case 4: //conf in vendita
					stampa_lista_conf (lista_conf_inventario);
					printf("\nPremi invio per continuare");
                                        while(ch = getchar() != '\n' && ch != EOF);
                                        while(ch = getchar() != '\n' && ch != EOF);
					break;
				case 5: //inventario
					stampa_componenti (inventario);
					printf("\nPremi invio per continuare");
                                        while(ch = getchar() != '\n' && ch != EOF);
					break;	
				case 6: //esci
					break;
					}	
		}
		break;
	case 1: //admin
		while (scelta != 5) {
			scelta = menu_admin();
			switch (scelta) {
				case 1: //apri menu magazzino
					mag = 0;
					while (mag != 4){
						mag = menu_magazzino();
						switch (mag) {
							case 1: //visualizza inventario
								stampa_componenti(inventario);
                                                                printf("Premi invio per continuare\n");
                                                                while(ch = getchar() != '\n' && ch != EOF);
								break;
							case 2: ; //crea comp
								componente* new_comp = NULL;
								new_comp = creazione_comp();
								if (new_comp == NULL)
									break;
								inserimento_ordinato_componenti(inventario, new_comp);
                                                              printf("\nPremi invio per continuare\n");
                                                              while(ch = getchar() != '\n' && ch != EOF);
								break;
							case 3:; //cancella comp
								cancellazione_comp(inventario);
								printf("Premi invio per continuare\n");
                                                              while(ch = getchar() != '\n' && ch != EOF);
								while(ch = getchar() != '\n' && ch != EOF);
								break;
							case 4:
								break;
						}
					}
					break;
				case 2: ; //crea conf in vendita
					configurazione new_conf = NULL;
					new_conf = creazione_configurazione(inventario, user);
					if(new_conf == NULL)
						break;
					inserimento_ordinato_conf(lista_conf_inventario, new_conf);
					break;
				case 3: //modifica conf
					controllo = modificare_conf (lista_conf_inventario, inventario, user);
					if (controllo == 1){ //se va male esco
					        finale(inventario, lista_utenti, lista_conf_inventario);
						exit(0);
					}
					break;
				case 4: //menu utenti
					ut = 0;
					while (ut != 3){
						ut = menu_utenti();
						switch (ut) {
							case 1: //visualizza utenti
								stampa_utenti (lista_utenti);
								printf ("Premi invio per continuare\n");
								while(ch = getchar() != '\n' && ch != EOF);
								break;
							case 2: //cancella utente
								cancellazione_utente (lista_utenti, user);
								break;
							case 3: //esci
								break;
						}
					}
					break;
				case 5: //esci
					break;
			}

		}
	break;
		default:
			break;
	}
	finale(inventario, lista_utenti, lista_conf_inventario); //funzione che salva i dati e libera la memoria
}


