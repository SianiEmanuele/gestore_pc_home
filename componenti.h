#ifndef COMPONENTI_H
#define COMPONENTI_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct componente{
	int type;  //vale 1 per scheda video, 2 per processore, 3 per ram, 4 per scheda madre, 5 per hard disk, 6 per ssd, 7 per case
	char nome[51];
	float prezzo;
	int numero;
	};

typedef struct componente componente;


struct nodo_componente {
	componente* componente;
	struct nodo_componente* prec;
	struct nodo_componente* next;
	};

struct nodo_inventario {
        struct nodo_componente* componenti;
        int type;
        struct nodo_inventario* prec;
        struct nodo_inventario* next;
	};


struct inventario {
	struct nodo_inventario* head;
	struct nodo_inventario* tail;
	};


typedef struct inventario* inventario;

struct nodo_inventario* crea_nodo_inventario();

inventario crea_inventario();

componente* creazione_comp();

componente* crea_componente(char nome[51], float prezzo, int tipo, int numero);

int inserimento_ordinato_componenti (inventario inventario, componente* comp);

int stampa_componenti(inventario inventario);

int cancellazione_comp (inventario inventario);

int cancella_comp(inventario inventario, struct nodo_componente* t);

componente* copia_componente (componente* comp);

void salva_inventario (inventario inventario);

inventario carica_inventario ();

void libera_inventario (inventario inv);

#endif



