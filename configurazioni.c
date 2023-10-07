#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "configurazioni_utenti.h"
#include "azioni.h"

//creo una funzione per verificare che la lista sia vuota, ritorna 1 se ' vuota, 0 se non lo e'
int is_empty (configurazione conf, int tipo) {
	struct nodo_inventario* p = conf -> lista -> head;
	while ((p != NULL) && ( p-> type != tipo)){
		p = p -> next;
		}
	if (p -> componenti == NULL){
	return 1;
	}
	else
	return 0;
}



void cancella_comp_conf(struct nodo_inventario* p, struct nodo_componente* q){
//l'elemento da cancellare e' in testa
        if(q  == p -> componenti){
                q -> next -> prec = NULL;
                p -> componenti = q -> next;
                }
                //l'elemento da cancellare e' in coda
        else if(q -> next == NULL){
                q -> prec -> next = NULL;
                }
                //l'elemento da cancellare e' in posizione normale
        else{
                q -> next -> prec = q -> prec;
                q -> prec -> next = q -> next;
                }
        free (q);
        return;
}

//funzione che permette di selezionare un componente, farne la copia e ne scala la disponibilita'
componente* seleziona_e_copia_comp(inventario inventory){
	char t = 0; // variabile per copiare svuotare il buffer
	int scelta = 0; //variabile per il numero del componente scelto
	int counter = 1; //contatore per scorrere la lista di componenti
	int tipo = 1; //variabile per il tipo di componente da inserire
	struct nodo_inventario* p = NULL; //puntatore per scorrere l'inventario
	struct nodo_componente* q = NULL; //puntatore per scorrere la lista dei componenti
	componente* copia_comp = NULL; //puntatore a nuovo componente su cui fare la copia di quello scelto
	p = inventory -> head;
	printf(GREEN);
	printf("\nPerfetto, ora scegli i componenti da inserire!(MAX 1 per ogni tipo)\n");
	printf(RESET);
	tipo = stampa_componenti(inventory);
	//se non sono presenti componenti di quel tipo nell'inventario o se l'utente ha già inserito un componente di quel tipo do errore
	while (tipo == -1){
	        system("clear");
              	printf("\nComando non valido. Scegli un tipo differente. \n");
              	tipo = stampa_componenti(inventory);
              	while(t = getchar() != '\n' && t != EOF); //svuoto il buffer
	}
	printf(GREEN);
	printf("\nDigita il numero del componente che desideri inserire: ");
	printf(RESET);
	scelta = evita_caratteri_int();
//scorro l'inventario
	while(p-> type !=tipo)
		p= p-> next;
	        q = p -> componenti;
//scorro la lista dei componenti
        while((counter != scelta) && (q != NULL)){
                q = q-> next;
                counter++;
                }
//in caso l'utente dovesse inserire un numero superiore al numero di componenti presente
        if(q == NULL){
                printf("\nComando non valido!\n");
		return NULL;
                }
	copia_comp = copia_componente (q-> componente); //copia del componente da inserire
	q -> componente -> numero--; //diminuisco il numero di unita' in inventario del componente scelto
//se il numero del componente nell'inventario scende a 0 lo elimino
	if (q -> componente -> numero == 0){
		//l'elemento da cancellare e' l'unico in lista
		if((q -> next == NULL) && (q -> prec == NULL)){
			p-> componenti = NULL;
			}
		//l'elemento da cancellare e' in testa
		else if(q == p -> componenti){
			q -> next -> prec = NULL;
			p -> componenti = q -> next;
		}
		//l'elemento da cancellare e' in coda
		else if(q -> next == NULL){
			q -> prec -> next = NULL;
		}
			//l'elemento da cancellare e' in posizione normale
		else{
			q -> next -> prec = q -> prec;
			q -> prec -> next = q -> next;
		}
		free (q-> componente);
		free (q);
		}
return copia_comp;
}

//funzione di modifica del prezzo della configurazione
float modifica_prezzo_config (float old_price){
	int scelta = -1; //variabile di controllo
	float prezzo = -1; //nuovo prezzo
	while ((scelta != 0) && (scelta != 1)){ 
		printf ("L'attuale prezzo e: %.2f€ Desideri modificarlo? Digita 1 per si, 0 per no\n", old_price);
		scelta = evita_caratteri_int();
		if (scelta == 1){
			printf(BLUE);
			printf("Inserisci il nuovo prezzo: ");
			printf(RESET);
			prezzo = evita_caratteri_float();
               	}
	}
	return prezzo; //ritorno il prezzo,  se -1 significa che non ha voluto cambiarlo
}

configurazione crea_configurazione (char nome[], float prezzo, componente* comp1, componente* comp2, componente* comp3, componente* comp4, componente* comp5, componente* comp6, componente* comp7){
//alloco la nuova configurazione
	configurazione new_config = (configurazione)malloc(sizeof(struct configurazione));
	if (new_config == NULL){
		free(new_config);
	        return NULL; //se va male esco
	}
	new_config -> lista = crea_inventario();
	new_config -> prezzo = prezzo;
	strcpy(new_config -> nome, nome);
//inserisco i componenti nella configurazione
	inserimento_ordinato_componenti(new_config -> lista, comp1);
	inserimento_ordinato_componenti(new_config -> lista, comp2);
	inserimento_ordinato_componenti(new_config -> lista, comp3);
	inserimento_ordinato_componenti(new_config -> lista, comp4);
	inserimento_ordinato_componenti(new_config -> lista, comp5);
	inserimento_ordinato_componenti(new_config -> lista, comp6);
	inserimento_ordinato_componenti(new_config -> lista, comp7);
	return new_config;
}


int ricerca_tipo(int v[], int dim, int elem){
	for (int i= 0; i <dim; i++){
		if(v[i] == elem)
			return 0;
	}			
	return -1;
}


//creo una funzione per la creazione della propria configurazione
configurazione creazione_configurazione (inventario inventory, utente* user) {
	char ch = 0; //variabile per copiare il nome dell'array
	int i = 0;//variabile per il nome della configurazione
	char t = 0; // variabile per copiare svuotare il buffer
	int g = 0; //contatore per continuare a inserire componenti
	int c = 0; //contatore per riempire l'array
	char nome[51]; //nome config
	int controllo = 0; //variabile per controllare che tutti i componenti siano di tipo diverso
	float prezzo = 0; //prezzo della configurazione
	int tipi[7]; //array per salvare i tipi di componenti inseriti
	componente* comp_re = NULL;
	configurazione new_config = NULL;
	componente* comp1= NULL;
	componente* comp2= NULL;
	componente* comp3= NULL;
	componente* comp4= NULL;
	componente* comp5= NULL;
	componente* comp6= NULL;
	componente* comp7= NULL;
	if(user -> type == 0){
		user -> numero_conf ++;
	}
//riempio l'array per evitare errori di valgrind
        for(c=0; c<51; c++){
                nome [c] = '\0';
                }
	printf(GREEN);
	printf("Ciao! Inserisci un nome per la tua configurazione(MAX 50 caratteri): ");
	printf(RESET);
//inserisco il nome della configurazione
        ch=getchar();
        while(ch!='\n' && i<51){
               nome[i++] = ch;
                ch=getchar();
                }
//se l'utente inserisce un nome troppo lungo
        if(i >= 51){
                printf("\nInput non valido!\n");
                return NULL;
                }
			comp1 = seleziona_e_copia_comp(inventory);
			if (comp1 == NULL)
				return NULL;
			tipi[0] = comp1 -> type; //salvo il tipo del componente in un array
			comp2 = seleziona_e_copia_comp(inventory);
			if (comp2 == NULL)
				return NULL;
			//controllo che il componente selezionato non sia dello stesso tipo di uno dei precedenti
			controllo = ricerca_tipo(tipi, 1, comp2 -> type);
			while(controllo == 0){
				printf("Input non valido! Inserisci un tipo differente.\n");
				//reinserisco il componente nell'inventario
				comp_re = copia_componente(comp2);
				inserimento_ordinato_componenti(inventory, comp_re);
				free(comp2); //faccio la free per evitare memory leak
				comp2 = NULL;
				comp2 = seleziona_e_copia_comp(inventory); //seleziono il nuovo componente
				if (comp2 == NULL)
					return NULL;
				controllo = ricerca_tipo(tipi, 1, comp2 -> type); //ripeto il controllo
				}
			tipi[1] = comp2 -> type;
			comp3 = seleziona_e_copia_comp(inventory);
			if (comp3 == NULL)
				return NULL;
			controllo = ricerca_tipo(tipi, 2, comp3 -> type);
			while(controllo == 0){
				printf("Input non valido! Inserisci un tipo differente.\n");
				comp_re = copia_componente(comp3);
				inserimento_ordinato_componenti(inventory, comp_re);
				free(comp3);
				comp3= NULL;
				comp3 = seleziona_e_copia_comp(inventory);
				if (comp3 == NULL)
					return NULL;
				controllo = ricerca_tipo(tipi, 2, comp3 -> type);
				}
			tipi[2] = comp3 -> type;
			comp4 = seleziona_e_copia_comp(inventory);
			if (comp4 == NULL)
				return NULL;
			controllo = ricerca_tipo(tipi, 3, comp4 -> type);
			while(controllo == 0){
				printf("Input non valido! Inserisci un tipo differente.\n");
				comp_re = copia_componente(comp4);
				inserimento_ordinato_componenti(inventory, comp_re);
				free(comp4);
				comp4 = NULL;
				comp4 = seleziona_e_copia_comp(inventory);
				if (comp4 == NULL)
					return NULL;
				controllo = ricerca_tipo(tipi, 3, comp4 -> type);
				}
			tipi[3] = comp4 -> type;
			comp5 = seleziona_e_copia_comp(inventory);
			if (comp5 == NULL)
				return NULL;
			controllo = ricerca_tipo(tipi, 4, comp5 -> type);
			while(controllo == 0){
				comp_re = copia_componente(comp5);
				inserimento_ordinato_componenti(inventory, comp_re);
				free(comp5);
				comp5 = NULL;
				printf("Input non valido! Inserisci un tipo differente.\n");
				comp5 = seleziona_e_copia_comp(inventory);
				if (comp5 == NULL)
					return NULL;
				controllo = ricerca_tipo(tipi, 4, comp5 -> type);
				}
			tipi[4] = comp5 -> type;
			comp6 = seleziona_e_copia_comp(inventory);
			if (comp6 == NULL)
				return NULL;
			controllo = ricerca_tipo(tipi, 5, comp6 -> type);
			while(controllo == 0){
				comp_re = copia_componente(comp6);
				inserimento_ordinato_componenti(inventory, comp_re);
				free(comp6);
				comp6 = NULL;
				printf("Input non valido! Inserisci un tipo differente.\n");
				comp6 = seleziona_e_copia_comp(inventory);
				if (comp6 == NULL)
					return NULL;
				controllo = ricerca_tipo(tipi, 5, comp6 -> type);
				}
			tipi[5] = comp6 -> type;
			comp7 = seleziona_e_copia_comp(inventory);
			if (comp7 == NULL)
				return NULL;
			controllo = ricerca_tipo(tipi, 6, comp7 -> type);
			while(controllo == 0){
				comp_re = copia_componente(comp7);
				inserimento_ordinato_componenti(inventory, comp_re);
				free(comp7);
				comp7 = NULL;
				printf("Input non valido! Inserisci un tipo differente.\n");
				comp7 = seleziona_e_copia_comp(inventory);
				if (comp7 == NULL)
					return NULL;
				controllo = ricerca_tipo(tipi, 6, comp7 -> type);
				}
			tipi[6] = comp7 -> type;
			prezzo = comp1 -> prezzo + comp2 -> prezzo + comp3 -> prezzo + comp4 -> prezzo + comp5 -> prezzo + comp6 -> prezzo + comp7 -> prezzo;
//se l'utente e' un admin do la possibilità di cambiare il prezzo della configurazione
	if(user -> type == 1){
		float mod = 0;
		printf(BLUE);
		mod = modifica_prezzo_config(prezzo);
		if (mod != -1)
			prezzo = mod;
		}
	new_config = crea_configurazione(nome, prezzo, comp1, comp2, comp3, comp4, comp5, comp6, comp7);
return new_config;
}


//creo una funzione per la stampa della configurazione, ritorna 0 se va a buon fine, -1 altrimenti
int stampa_config (configurazione conf){
	printf("NOME: %s\n", conf -> nome);
        struct nodo_inventario* p = NULL; //puntatore per scorrere l'inventario
	p = conf -> lista -> head;
	printf("    1. Scheda video : %s \n", p -> componenti -> componente -> nome);
	p = p-> next;
        printf("    2. Processore : %s \n", p -> componenti -> componente -> nome);
        p = p-> next;
        printf("    3. Ram : %s \n", p -> componenti -> componente -> nome);
        p = p-> next;
        printf("    4. Scheda madre : %s \n", p -> componenti -> componente -> nome);
        p = p-> next;
        printf("    5. Hard disk : %s \n", p -> componenti -> componente -> nome);
        p = p-> next;
        printf("    6. Ssd : %s \n", p -> componenti -> componente -> nome);
        p = p-> next;
        printf("    7. Case : %s \n", p -> componenti -> componente -> nome);
	printf("Prezzo : %.2f€ \n", conf -> prezzo);
	return 0;
}


//creo una funzione per la creazione delle liste di configurazioni
lista_conf crea_lista_conf() {
lista_conf new_lista_conf = (lista_conf)malloc(sizeof(struct lista_conf));
if (new_lista_conf == NULL)
	return NULL;
new_lista_conf -> head = NULL;
new_lista_conf -> tail = NULL;
return new_lista_conf;
}


//definisco una funzione per l'inserimento ordinato
int inserimento_ordinato_conf (lista_conf lista_conf, configurazione conf){
	int g = 0; //contatore per reinserire i componenti
	struct nodo_inventario* q = NULL;
//inizializzo un nuovo nodo
        struct nodo_conf* p = NULL;
//inizializzo un puntatore d'appoggio che punta alla testa della lista di configurazioni
        struct nodo_conf* temp = lista_conf -> head;
//alloco il nuovo nodo
        p=(struct nodo_conf*)malloc(sizeof(struct nodo_conf));
//se qualcosa va storto ritorna 1
        if(p == NULL){
		free(p);
                return 1;
	}
//popolo p
        p -> conf = conf;
//caso in cui la lista e' vuota
        if(lista_conf -> head == NULL){ 
                p-> next = NULL;
                p-> prec = NULL;
                lista_conf -> head = p;
                lista_conf -> tail = p;
                return 0; //ritorno 0 se e' andata bene
        }
//cerco la posizione di inserimento
        while((temp != NULL) && (strcmp(p -> conf -> nome, temp -> conf -> nome)) > 0){
        temp = temp -> next;
	}
//inserimento in testa
        if(temp == lista_conf -> head){
                lista_conf -> head = p;
                temp -> prec = p;
                p -> next = temp;
                p -> prec = NULL;
        }
//inserimento in coda
        else if (temp == NULL){
                lista_conf -> tail -> next = p;
                p -> prec = lista_conf -> tail;
                p -> next = NULL;
                lista_conf -> tail = p;
        }
//inserimento normale
        else {
                p -> next = temp;
                p -> prec = temp -> prec;
                temp -> prec -> next = p;
        }
return 0; //ritorno 0 se e' andato a buon fine
}

//definisco una funzione per stampare la lista di configurazioni
int stampa_lista_conf (lista_conf lista_conf){
	int i = 1;
	int ch = 0; //variabile per resettare il buffer
	int counter = 1; //contatore per scorrere la lista di componenti
	struct nodo_conf* p = NULL;
	int scelta = 0; //intero per salvare la scelta dell'utente
	p = lista_conf -> head;
	if (p == NULL){
		printf("La lista e' vuota!\n");
		return -1;
		}
	printf("Ciao! Ecco la tua lista di configurazioni!\n");
	while ( p != NULL){
		printf("%d. %s\n", i, p -> conf -> nome);
		p = p -> next;
		i++;
		}
	printf ("Quale desideri visualizzare? ");
	scanf ("%d", &scelta);
	while(ch = getchar() != '\n' && ch != EOF);
	p = lista_conf -> head;
	while((counter < scelta) && (p != NULL)){
		p= p-> next;
		counter++;
		}
	while (p == NULL){
		printf("Input non valido, inserirne uno corretto: ");
		scanf("%d", &scelta);
		while(ch = getchar() != '\n' && ch != EOF);
		p = lista_conf -> head;
		counter = 1;
		 while((counter < scelta) && (p != NULL)){
	                p= p-> next;
        	        counter++;
                	}
	}
	stampa_config( p -> conf);
return 0;
}

//definisco un'altra variente della funzione per stampare la lista di configurazioni
int stampa_lista_conf_per_cancella (lista_conf lista_conf){
        int i = 1;
        int counter = 1;
        struct nodo_conf* p = NULL;
        int scelta = 0;
        p = lista_conf -> head;
        if (p == NULL){
                printf("La lista e' vuota!\n");
                return -1;
                }
        printf("Ciao! Ecco la tua lista di configurazioni!\n");
        while ( p != NULL){
                printf("%d. %s\n", i, p -> conf -> nome);
                p = p -> next;
                i++;
                }
return 0;
}

//funzione che mi permette di scegliere quale configurazione cancellare
int cancellare_conf(lista_conf lista_conf){
	int controllo = 0;
	int scelta = 0;
	int i = 1;
	struct nodo_conf* q = lista_conf -> head;
//se l'utente non ha configurazioni da cancellare esco
	controllo = stampa_lista_conf_per_cancella (lista_conf);
	if (controllo == -1) 
		return -1; //torna -1 se va male
	printf("\nQuale desideri cancellare? ");
	scelta = evita_caratteri_int(); 
	printf("\nSei sicuro? Premi invio per confermare");
	// trova la config da cancellare
        while ((q != NULL) && (i < scelta)){
                q = q->next;
		i++;
	        while (q == NULL || scelta < 1){ //input non valido
        	        printf("Input non valido! Inserirne uno corretto: ");
			scelta = evita_caratteri_int();
			}
		}
	cancella_conf(lista_conf, q);
	return 0; //ritorna la scelta fatta
}

//funzione che mi permette di scegliere quale configurazione modificare
int scelta_config_per_modifica(lista_conf lista_conf){
	int controllo = 0;
	int scelta = 0;
//se l'utente non ha configurazioni da cancellare esco
	controllo = stampa_lista_conf_per_cancella (lista_conf);
	if (controllo == -1) 
		return -1; //torna -1 se va male
	printf("\nQuale desideri modificare? ");
	scelta = evita_caratteri_int(); 
	return scelta; //ritorna la scelta fatta
}




//creo una funzione per cancellare una configurazione dalla lista
int cancella_conf(lista_conf lista_conf, struct nodo_conf* q){
//unica configurazione in lista
        if ((q -> next == NULL) && (q-> prec == NULL)){
		libera_inventario(q -> conf -> lista);
		free(q -> conf);
                free(q);
		lista_conf -> head = NULL;
		lista_conf -> tail = NULL;
                return 0;
                }
        if(q== lista_conf ->head){ //la configurazione cancellare è la prima
                lista_conf -> head->next->prec=NULL;
                lista_conf -> head= lista_conf -> head ->next;
                }
        else if (q== lista_conf -> tail){ //la configurazione da cancellare è l'ultima
                lista_conf -> tail->prec->next=NULL;
                lista_conf -> tail= lista_conf -> tail->prec;
                }
        else{ //caso generico
                q->prec->next = q->next;
                q->next->prec = q->prec;
                }
//dealloco la memoria per la configurazione da cancellare
libera_inventario(q -> conf -> lista);
free(q -> conf);
free (q);
return 0;
}


//funzione di selezione per un nuovo componente da mettere nella modifica
int scelta_comp_nuovo(inventario inventario, int scelta){
	char t = 0; //variabile per svuotare il buffer
	int tipo = 0; //tipo del componente
	printf(GREEN);
	printf("\nPerfetto, ora scegli il componente da inserire!(stesso tipo di quello eliminato)\n");
	printf(RESET);
	tipo = stampa_componenti(inventario);
	//se non sono presenti componenti di quel tipo nell'inventario o se il nuovo tipo non coincide con quello del componente rimosso do errore
	while ((tipo == -1) || (tipo != scelta)){
		system("clear");
              	printf("\nComando non valido. Scegli un tipo differente. \n");
              	tipo = stampa_componenti(inventario);
              	while(t = getchar() != '\n' && t != EOF); //svuoto il buffer
     	}
	printf(GREEN);
	printf("Digita il numero del componente che desideri inserire: ");
	printf(RESET);
	scelta = evita_caratteri_int();
	return scelta; //ritorno il numero del componente

}


//funzione di modifica configurazione, ritorna 0 se va bene, 1 in caso di errore
int modifica_conf (lista_conf lista_conf, inventario inventario, utente* user, int scelta0, int scelta1, int scelta2, float new_price){
	char ch = 0; //variabile per inizializzare le stringhe
	char t = 0; //variabile per resettare il buffer
	int tipo = 0; //tipo del componente cambiato
	int counter = 1; //contatore per trovare la configurazione da modificare
//inizializzo i puntatori
	struct nodo_conf* p = NULL;
	struct nodo_inventario* q = NULL;
	struct nodo_componente* g = NULL;
	struct nodo_inventario* w = NULL;
	componente* copia_comp = NULL;
	componente* copia_comp2 = NULL;
	p = lista_conf -> head;
//raggiungo la configurazione desiderata
	        while(counter < scelta0){
	                p= p-> next;
        	        counter++;
                }
		w = p -> conf -> lista -> head; //faccio puntare w alla testa della lista di componenti della configurazione
		while ( (w -> type) != (scelta1)){ //scorro i nodi fino al tipo di componente richiesto
			w = w -> next;
		}
//faccio puntare q alla testa dell'invetario
			q = inventario -> head;
//scorro i nodi componente fino ad arrivare al tipo scelto dall'utente
			while ((q -> type != scelta1) && (q != NULL)){
				q = q -> next;
			}
			g = q -> componenti;
//cerco nell'inventario il componente rimosso dalla configurazione
			while((g != NULL) && (strcmp(g -> componente -> nome, w -> componenti -> componente -> nome) != 0)){
			g = g -> next;
			}
			if ( g == NULL){
				copia_comp = copia_componente(w -> componenti -> componente); //se il componente non e' piu' presente nell'inventario lo riaggiunge
				inserimento_ordinato_componenti (inventario, copia_comp);
			}
			else {
				g -> componente -> numero++; //aumento di uno il numero del componente rimosso dalla configurazione
			}
			p -> conf -> prezzo -= w -> componenti -> componente -> prezzo; //scalo il prezzo del componente rimosso da quello della configurazione
			printf(GREEN);
			tipo = scelta1; //salvo il tipo di componente appena eliminato
			q= inventario -> head;
//scorro l'inventario
	        	while(q-> type !=tipo)
	                	q= q-> next;
	        	g = q -> componenti;
			counter = 1;
//scorro la lista dei componenti
		        while((counter != scelta2) && (g != NULL)){
		                g = g-> next;
	        	        counter++;
	                	}
//in caso l'utente dovesse inserire un numero superiore al numero di componenti presente
	        	if(g == NULL){
	                	printf("\nComando non valido!\n");
	                	p -> conf -> prezzo += w -> componenti -> componente -> prezzo;
	                	while(t = getchar() != '\n' && t != EOF);
	                	return 1;
	                	}
			strcpy(w -> componenti -> componente -> nome, g -> componente -> nome); //modifico il nome del componente che era nella configurazione
			w -> componenti -> componente -> prezzo = g -> componente -> prezzo; //aggiorno il prezzo del componente
			p -> conf -> prezzo += w -> componenti -> componente -> prezzo ; //aumento il prezzo della configurazione
			g -> componente -> numero--; //diminuisco il numero di unita' in inventario del componente scelto
//termina la disponibilità del componente inserito
			if (g -> componente -> numero == 0){
				//l'elemento da cancellare e' l'unico in lista
				if((g -> next == NULL) && (g -> prec == NULL)){
				q-> componenti = NULL;
				}
			//l'elemento da cancellare e' in testa
			else if(g == q -> componenti){
			g -> next -> prec = NULL;
			q -> componenti = g -> next;
			}
			//l'elemento da cancellare e' in coda
			else if(g -> next == NULL){
			g -> prec -> next = NULL;
			}
			//l'elemento da cancellare e' in posizione normale
			else{
			g -> next -> prec = g -> prec;
			g -> prec -> next = g -> next;
			}
			free(g->componente);
			free(g);
			}
			if (new_price != -1)
				p -> conf -> prezzo = new_price;
return 0;
}



//funzione per modificare le configurazioni
int modificare_conf(lista_conf lista_conf, inventario inventario, utente* user){
//inizializzo i puntatori
	struct nodo_inventario* w = NULL;
	struct nodo_conf* p = NULL;
	struct nodo_componente* g = NULL;
	int counter0 = 1; //contatore
	int scelta0 = 0; //configurazione da modificare
	int scelta1 = -1; //variabile per scegliere il nuovo componente
	float new_price = -1; //nuovo prezzo
	int controllo = 0; //variabile per controllare che la modifica sia andata a buon fine
	int tipo = 0; //tipo di componente da cambiare
	char t = 0; //variabile per resettare il buffer
	stampa_lista_conf_per_cancella (lista_conf);
	printf("Quale desideri modificare?\n ");
	while(scelta0 < 1) 
		scelta0 = evita_caratteri_int();
		p = lista_conf -> head;
//raggiungo la configurazione desiderata
	        while(counter0 < scelta0){
	                p= p-> next;
        	        counter0++;
                }
                if (p == NULL)
                	return 1;
//stampo la configurazione
        stampa_config(p -> conf);
        if (user -> type == 1)
		new_price = modifica_prezzo_config(p -> conf -> prezzo); //invoco la funzione per la modifica della configurazione
	printf("\nCosa desideri modificare?\n");
	printf("Digita il numero del componente da cambiare: ");
	tipo = evita_caratteri_int();
//forzo l'utente a inserire un input corretto
		while ((tipo != 1) && (tipo != 2) && (tipo != 3) && (tipo != 4) && (tipo != 5) && (tipo != 6) && (tipo != 7)){ 
                	printf("\nInput non valido! Inserisci un input corretto: "); 
                	tipo = evita_caratteri_int();
                }			
	scelta1 = scelta_comp_nuovo(inventario, tipo);
	controllo = modifica_conf(lista_conf, inventario, user, scelta0, tipo, scelta1, new_price);
	if(controllo == 1)
		return 1; //se andata male ritorno 1 
	printf("Modifica andata a buon fine!\n");
	while(t = getchar() != '\n' && t != EOF); //lascio attendere
	return 0;
}

void salva_lista_conf (lista_conf lista_conf){
        struct nodo_componente* g = NULL; //puntatore per scorrere la lista dei componenti
        struct nodo_conf* t = NULL; //puntatore per scorrere la lista di configurazioni
        struct nodo_inventario* d = NULL; //puntatore per scorrere l'inventario
	t = lista_conf -> head;
	FILE * f =fopen("configurazioni.txt", "w"); //apro il file in scrittura
	if (f == NULL){
		perror("\nErrore nella scrittura su file\n");
		exit(1);
	}
	while(t != NULL){
		fprintf(f, "%.2f\n%s\n", t -> conf -> prezzo, t -> conf -> nome);
		d = t -> conf -> lista -> head;
			int counter = 1;
			while(counter != 8) {
				g = d -> componenti;
//scrivo su file i campi della mia struct isolando il nome
				fprintf(f, "%d %.2f %d\n%s\n",g -> componente -> type, g -> componente -> prezzo, g -> componente -> numero, g -> componente -> nome);
				d= d-> next;
				counter++;
			}
		t = t -> next;
	}
fclose(f);
return;
}


lista_conf carica_lista_conf (){
	lista_conf new_list = crea_lista_conf();
        componente* comp =(componente*)malloc(sizeof(componente)); //alloco un puntatore a componente
	float prezzo = 0;
        FILE * f =fopen("configurazioni.txt", "r"); //apro il file in scrittura
        if (f == NULL){
                perror("\nErrore nella scrittura su file\n");
                exit(1);
	}
//leggo il prezzo della configurazione
	while(fscanf(f, "%f\n", &prezzo) != EOF){
//alloco la nuova configurazione
		configurazione new_config = (configurazione)malloc(sizeof(struct configurazione));
		new_config -> lista = crea_inventario(); //alloco la lista di componenti per la configurazione
		new_config -> prezzo = prezzo; //aggiorno il prezzo
		fgets(new_config -> nome, 51 , f); //leggo il nome da file e lo metto nell'array
		fgets_newline_kill(new_config->nome); //elimino il \n dal nome dellla configurazione
		int counter = 1;
//ciclo per ogni componente
		while(counter != 8){
//leggo i componenti da file
			fscanf(f,"%d %f %d\n", &comp -> type, &comp -> prezzo, &comp -> numero);
			fgets(comp -> nome, 51 , f); 
			fgets_newline_kill(comp->nome);//elimino il \n 
			componente* comp_copia  = copia_componente (comp); //copio il componente 
			inserimento_ordinato_componenti(new_config-> lista, comp_copia); //inserisco la copia nella configurazione
			counter++;
			}
//inserisco la configurazione nella lista
	inserimento_ordinato_conf (new_list, new_config);
	}
fclose(f);
free(comp);
return new_list;
}


void libera_lista_conf(lista_conf list){
	struct nodo_conf* a = NULL; //precedente
	struct nodo_conf* b = NULL; //successivo
	configurazione c;
	a = list -> head;
	b = list -> head;
	while (a != NULL){
		c = a -> conf;
		libera_inventario (c -> lista);
		free(c);
		b = b -> next;
		free(a);
		a = b;
	}
	free(a);
	free(list);
	return;
}

//funzione di finale che richiama le funzioni di salvataggio e liberazione della memoria
void finale (inventario inventario, lista_utenti lista_utenti, lista_conf lista_conf_inventario){
                salva_inventario (inventario);
                salva_utenti (lista_utenti);
                salva_lista_conf (lista_conf_inventario);
                libera_inventario(inventario);
                libera_lista_conf (lista_conf_inventario);
                libera_utenti (lista_utenti);
                return;
}


