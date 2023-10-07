#include "configurazioni_utenti.h"


//definisco una funzione per la creazione della lista
lista_utenti crea_lista_utenti() {
	lista_utenti new_lista = (lista_utenti)malloc(sizeof(struct lista_utenti));
	if (new_lista == NULL){
		free(new_lista);
		return NULL; //se va male ritorno NULL
	}
	new_lista -> head = NULL;
	new_lista -> tail = NULL;
	return new_lista;
}


//definisco una funzione per l'inserimento ordinato
int inserimento_ordinato_utenti (lista_utenti lista, utente* user){
//alloco un nuovo nodo
        struct nodo_utente* p = NULL;
//inizializzo un puntatore d'appoggio
        struct nodo_utente* temp = lista -> head;
        p=(struct nodo_utente*)malloc(sizeof(struct nodo_utente));
//se qualcosa va male ritorna 1
        if(p == NULL){
		free(p);
                return 1;
	}
//popolo p
        p -> utente = user;
//caso in cui la lista e' vuota
        if(lista -> head == NULL){ 
                p-> next = NULL;
                p-> prec = NULL;
                lista -> head = p;
                lista -> tail = p;
                return 0; //ritorno 0 se e' andata bene
        }
//cerco la posizione di inserimento
        while((temp != NULL) && (strcmp (p -> utente -> username, temp -> utente -> username) > 0))
        temp = temp -> next;
//inserimento in testa
        if(temp == lista -> head){
                lista -> head = p;
                temp -> prec = p;
                p -> next = temp;
                p -> prec = NULL;
        }
//inserimento in coda
        else if (temp == NULL){
                lista -> tail -> next = p;
                p -> prec = lista -> tail;
                p -> next = NULL;
                lista -> tail = p;
        }
//inserimento normale
        else {
                p -> next = temp;
                p -> prec = temp -> prec;
                temp -> prec -> next = p;
        }
return 0; //ritorno 0 se e' andato a buon fine
}


//definisco una funzione per la stampa
void stampa_utenti(lista_utenti lista) {
int i = 1; //contatore per il numero di utenti
struct nodo_utente* p = NULL;
p = lista -> head;
	while(p != NULL) {
		printf ("%d. %s\n",i, p -> utente -> username);
		p = p -> next;
		i++;
	}
printf ("\n");
return;
}

//funzione che richiede l'utente da cancellare
int cancellazione_utente(lista_utenti lista, utente* user){
	char ch = 0; //variabile per resettare il buffer
	int scelta = 0; //variabile per la scelta dell'utente da eliminare
	int counter = 1; //contatore per trovare l'utente da cancellare
	struct nodo_utente *q = lista -> head;
	stampa_utenti (lista);
	printf ("Quale desideri eliminare? ");
	scelta = evita_caratteri_int();
	while(counter < scelta){
// trova l'account da cancellare
                q = q->next;
		counter++;
		while (q == NULL){
			printf("Input non valido!\n");
			scelta = evita_caratteri_int();
			counter = 1;
			q = lista -> head; 
		}
	}

	if(strcmp(q->utente -> username , user -> username) == 0){
//impongo di non poter eliminare l'account in cui si e' loggati
		printf ("Non puoi eliminare il tuo stesso account!\nPremi invio per andare avanti\n");
		while(ch = getchar() != '\n' && ch != EOF); //svuoto il buffer
		return 1;
	}
	cancella_utente(lista, user, q);
	return 0;
}

//definisco una funzione per la cancellazione di un utente
int cancella_utente(lista_utenti lista, utente* user, struct nodo_utente* q){
        if(q== lista ->head){ //l'account da cancellare e' il primo
                lista -> head->next->prec=NULL;
                lista -> head= lista -> head ->next;
                }
        else if (q== lista -> tail){ //l'account da cancellare e' l'ultimo
                lista -> tail->prec->next=NULL;
                lista -> tail= lista -> tail->prec;
                }
        else{ //caso generico
                q->prec->next = q->next;
                q->next->prec = q->prec;
                }
	libera_lista_conf(q -> utente -> lista_conf); //dealloco la lista di configurazioni dell'utente
	free (q -> utente); //dealloco l'utente
	free(q); //dealloco il nodo utente
return 0;
}

//funzione per la copia di un utente
utente* copia_utente (utente* user){
	utente* new_user = NULL;
        new_user = (utente*)malloc(sizeof(utente)); //alloco un puntatore a utente
	new_user -> lista_conf = NULL;
	if (new_user == NULL)
		return NULL;
	strcpy(new_user -> username, user -> username);
	strcpy(new_user -> password, user -> password);
	new_user -> type = user -> type;
	new_user -> numero_conf = user -> numero_conf;
	return new_user;
}



void salva_utenti(lista_utenti lista){
	int counter1 = 0; //contatore per il numero di configurazioni
        struct nodo_componente* g = NULL; //puntatore per scorrere la lista dei componenti
        struct nodo_inventario* d = NULL; //puntatore per scorrere l'inventario
//inizializzo un puntatore d'appoggio
        struct nodo_utente* p = lista -> head; //puntatore alla testa della lista di utenti
	FILE * f =fopen("utenti.txt", "w"); //apro il file in scrittura
	if (f == NULL){
		perror("\nErrore nella scrittura su file\n");
		exit(1); //esco se va male
	}
	while(p != NULL){
		fprintf(f, "%d %d %s %s\n", p -> utente -> type, p -> utente -> numero_conf, p -> utente -> username, p -> utente -> password);
		struct nodo_conf* t = p -> utente -> lista_conf -> head;
		counter1 = 0;
		while(counter1 != p -> utente -> numero_conf){
			int counter2 = 1; //contatore per leggere i 7 componenti della configurazione
				fprintf(f, "%.2f\n%s\n", t -> conf -> prezzo, t -> conf -> nome);
				d = t -> conf -> lista -> head;
				while(counter2 != 8) {
					g = d -> componenti;
//scrivo su file i campi della mia struct isolando il nome
					fprintf(f, "%d %.2f %d\n%s\n",g -> componente -> type, g -> componente -> prezzo, g -> componente -> numero, g -> componente -> nome);
					d= d-> next; //scorro nodo inventario
					counter2++;
				}
			t = t -> next; //scorro nodo conf
			counter1++;
		}
		p = p -> next; //scorro nodo utente
	}
	fclose(f);
	return;
}


lista_utenti carica_utenti(){
	int counter1 = 0; //contatore per il numero di configurazioni
	lista_utenti new_list = crea_lista_utenti(); 
	utente* user =(utente*)malloc(sizeof(utente)); //alloco un puntatore a utente
        componente* comp =(componente*)malloc(sizeof(componente)); //alloco un puntatore a componente
	FILE *f = fopen("utenti.txt", "r"); //apro in scrittura il file
	if(f == NULL){
		perror("Errore nella scrittura del file\n");
		exit(1);
	}
	while(fscanf(f,"%d %d %s %s\n", &user -> type, &user -> numero_conf, user -> username, user -> password) != EOF){
		int counter2 = 1; //counter per i componenti
		utente* user_copia  = copia_utente (user); //copio l'utente
		user_copia -> lista_conf = crea_lista_conf(); //creo una lista di configurazioni vuota nell'utente
		counter1 =0; 
		while(counter1 != user_copia -> numero_conf){
			configurazione new_config = (configurazione)malloc(sizeof(struct configurazione));
			fscanf(f, "%f\n", & new_config -> prezzo); //leggo il prezzo
			fgets(new_config -> nome, 51 , f); //leggo il nome
			fgets_newline_kill(new_config->nome); //levo il \n
			new_config -> lista = crea_inventario(); //creo la lista di componenti
			counter2 =1;
			while(counter2 != 8){
				fscanf(f,"%d %f %d\n", &comp -> type, &comp -> prezzo, &comp -> numero); //leggo caratteristica del componente
				fgets(comp -> nome, 51 , f); //leggo nome del componente
				fgets_newline_kill(comp->nome); //levo il \n
				componente* comp_copia  = copia_componente (comp); //copio il componente 
				inserimento_ordinato_componenti(new_config-> lista, comp_copia); //inserisco la copia
				counter2++;
			}
			counter1++;
			inserimento_ordinato_conf (user_copia -> lista_conf, new_config); //inserisco la configurazione
		}
		inserimento_ordinato_utenti (new_list, user_copia); //inserisco l'utente
	}
	free(user); //libero l'utente d'appoggio
	free(comp); //libero componente d'appoggio
	fclose(f); 
	return new_list; //ritorno la lista di utenti
}

//funzione per deallocare la lista di utenti
void libera_utenti(lista_utenti list){
	struct nodo_utente* a = NULL; //precedente
	struct nodo_utente* b = NULL; //successivo
	lista_conf c = NULL;
	a = list -> head;
	b = list -> head;
	while(b != NULL){
		c = a -> utente -> lista_conf;
		libera_lista_conf(c); //libero la lista di configurazione dell'utente
		b = b -> next; //succ va avanti
		free(a -> utente); //libero la memroia
		free(a);
		a = b; //prec raggiunge succ
	}
	free(a); //cancello l'ultimo nodo
	free(list); //cancello la lista
	return;
}



