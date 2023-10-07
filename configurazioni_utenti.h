#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "componenti.h"
#include "azioni.h"

struct configurazione{
        inventario lista;
        char nome[51];
        float prezzo;
        };

typedef struct configurazione* configurazione;

struct nodo_conf {
	configurazione conf;
	struct nodo_conf* prec;
	struct nodo_conf* next;
	};

struct lista_conf {
	struct nodo_conf* head;
	struct nodo_conf* tail;
	};

typedef struct lista_conf* lista_conf;


struct utente{
	char username[21];
	char password[11];
	int type;  //vale 1 se admin, 0 al contrario
	lista_conf lista_conf;
	int numero_conf;
	};


typedef struct utente utente; 



struct nodo_utente {
	utente* utente;
	struct nodo_utente* prec;
	struct nodo_utente* next;
};


struct lista_utenti {
struct nodo_utente* head;
struct nodo_utente* tail;
};

typedef struct lista_utenti* lista_utenti;


int is_empty (configurazione conf, int tipo);

componente* seleziona_e_copia_comp(inventario inventory);

float modifica_prezzo_config (float old_price);

configurazione crea_configurazione (char nome[], float prezzo, componente* comp1, componente* comp2, componente* comp3, componente* comp4, componente* comp5, componente* comp6, componente* comp7);

configurazione creazione_configurazione (inventario inventory, utente* user);

int stampa_config (configurazione conf);

lista_conf crea_lista_conf();

int inserimento_ordinato_conf (lista_conf lista_conf, configurazione conf);

int stampa_lista_conf (lista_conf lista_conf);

int stampa_lista_conf_per_cancella (lista_conf lista_conf);

int scelta_config_per_cancella(lista_conf lista_conf);

int scelta_config_per_modifica(lista_conf lista_conf);

int cancellare_conf(lista_conf lista_conf);

int cancella_conf(lista_conf lista_conf, struct nodo_conf* q);

int scelta_nuovo_comp(inventario inventario, int scelta);

int scelta_comp_da_modificare(configurazione conf);

int modificare_conf(lista_conf lista_conf, inventario inventario, utente* user);

int modifica_conf (lista_conf lista_conf, inventario inventario, utente* user, int scelta0, int scelta1, int scelta2, float new_price);

void salva_lista_conf (lista_conf lista_conf);

lista_conf carica_lista_conf ();

void libera_lista_conf(lista_conf list);

lista_utenti crea_lista_utenti();

int inserimento_ordinato_utenti (lista_utenti lista, utente* user);

void stampa_utenti(lista_utenti lista);

int seleziona_utente_da_eliminare(lista_utenti lista);

int cancellazione_utente(lista_utenti lista, utente* user);

int cancella_utente(lista_utenti lista, utente* user, struct nodo_utente* q);

utente* copia_utente (utente* user);

void salva_utenti (lista_utenti lista);

lista_utenti carica_utenti();

void libera_utenti (lista_utenti lista);

void finale (inventario inventario, lista_utenti lista_utenti, lista_conf lista_conf_inventario);
