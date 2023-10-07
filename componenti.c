#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "componenti.h"
#include "azioni.h"

//definisco una funzione per la creazione di un nodo dell'inventario
struct nodo_inventario* crea_nodo_inventario() {
	struct nodo_inventario* p = (struct nodo_inventario*)malloc(sizeof(struct nodo_inventario));
	if (p == NULL){
		free(p);
		return NULL;
	}
	p -> type = 1;
	p -> prec = NULL;
	p -> next = NULL;
	p -> componenti = NULL;
	return p;
	}


//definisco una funzione per la creazione dell'inventario
inventario crea_inventario() {
int i= 2; //faccio partire da 2 perche' il primo lo sto gia' creando
inventario new_inventario = (inventario)malloc(sizeof(struct inventario));
if (new_inventario == NULL){
	free(new_inventario);
	return NULL;
	}
struct nodo_inventario* p = crea_nodo_inventario();
new_inventario -> head = p;
new_inventario -> tail = p;
//creo i nodi dell'inventario per le tipologie di componenti
while (i != 8){
	struct nodo_inventario* new_node = crea_nodo_inventario();
	new_inventario -> tail -> next = new_node;
	new_node -> prec = new_inventario -> tail;
	new_node -> next = NULL;
	new_inventario -> tail = new_node;
	new_node -> type = i;
	new_node -> componenti = NULL;
	i++;
	}

return new_inventario;
}

//definisco una funzione per la creazione del componente
componente* crea_componente(char nome[51], float prezzo, int tipo, int numero){
	componente* comp = NULL;
	comp = (componente*)malloc(sizeof(componente)); //alloco un puntatore a componente
	if (comp == NULL){
		printf("Errore nella creazione del componente\n");
		return NULL;
		}
	comp -> prezzo = prezzo;
	comp -> numero = numero;
	comp -> type = tipo;
	strcpy(comp -> nome, nome);
	return comp;
}


componente* creazione_comp(){
	char ch = 0; //variabile per prendere il nome del componente
	char t = 0;  //variabile d'appoggio per svuotare il buffer
	int i=0; //definisco un counter
	int c = 0; //contatore per inizializzare l'array
	char nome [51]; //nome del componente
	int numero = 0; //numero del componente
	float prezzo = 0; //prezzo
	int tipo = 0; //tipo
	componente* comp = NULL;
	//ciclo che riempie l'array per evitare errore con valgrind
	for(c=0; c<51; c++){
		nome [c] = '\0';
		}
	printf ("Di che tipo di componente si tratta? \n1.Scheda video \n2.Processore \n3.RAM \n4.Scheda madre \n5.Hard disk \n6.SSD \n7.Case \n\n");
	tipo = evita_caratteri_int();
//se l'utente inserisce un valore non valido stampo un messaggio d'errore
        while ((tipo != 1) && (tipo != 2) && (tipo != 3) && (tipo != 4) && (tipo != 5) && (tipo != 6) && (tipo != 7)){ 
                printf("Input non valido! Inserisci un input corretto: "); 
                tipo = evita_caratteri_int();
                }
	printf(GREEN);
	printf ("\nDigita il nome del componente (MAX 50 caratteri) \n");
	printf(RESET);
	ch=getchar();
	while(ch!='\n' && i<51){
		nome[i++]=ch;
		ch=getchar();
		}
//se l'utente inserisce un nome troppo lungo stampo un messaggio d'errore
	if(i >= 51){
		printf("Input non valido!\n");
		return NULL;
		}
//chiedo il prezzo
	printf(GREEN);
	printf("\nInserisci il prezzo \n");
	printf(RESET);
	prezzo = evita_caratteri_float();
	printf(GREEN);
	printf("\nQuante unita' desideri inserirne? \n");
	printf(RESET);
//chiedo il numero
	numero = evita_caratteri_int();
	comp = crea_componente(nome, prezzo, tipo, numero);
	if (comp == NULL){
		printf("Errore nella creazione del componente\n");
		return NULL;
		}
	return comp;
	}

//definisco una funzione per l'inserimento ordinato
int inserimento_ordinato_componenti (inventario inventario, componente* comp){
//alloco un nuovo nodo
        struct nodo_componente* p = NULL;
	p=(struct nodo_componente*)malloc(sizeof(struct nodo_componente));
//inizializzo un puntatore d'appoggio
        struct nodo_inventario* temp1 = inventario -> head;
//popolo p
	p -> next = NULL;
	p -> prec = NULL;
	p -> componente = comp;
//cerco la posizione di inserimento tra i nodi dell'inventario
        while(p -> componente -> type != temp1 -> type)
        temp1 = temp1 -> next;
//inizializzo un secondo puntatore di appoggio per scorrere la lista di componenti
	struct nodo_componente* temp2;
	temp2 = temp1 -> componenti;
//caso in cui la lista e' vuota
        if(temp2 == NULL){ 
                p-> next = NULL;
                p-> prec = NULL;
                temp1 -> componenti = p;
                return 0; //ritorno 0 se e' andata bene
        }
//inserimento in testa
        if((strcmp(comp -> nome, temp1 -> componenti -> componente -> nome)) < 0) {
                temp1 -> componenti = p;
                temp2 -> prec = p;
                p -> next = temp2;
                p -> prec = NULL;
		return 0;
        }
//cerco la posizione di inserimento nella lista di componenti
	while((strcmp(comp -> nome, temp2 -> componente -> nome) > 0) && (temp2 -> next != NULL)) {
		temp2 = temp2 -> next;
		}
//inserimento in coda
        if ((temp2 -> next == NULL) && (strcmp(comp -> nome, temp2 -> componente -> nome) > 0)){
                temp2 -> next = p;
                p -> prec = temp2;
                p -> next = NULL;
        return 0;
        }
//verifico che il componente non sia gia' presente nella lista
	if(strcmp(comp -> nome, temp2 -> componente -> nome) == 0) {
		temp2 -> componente -> numero += comp -> numero;
		free(comp);
		free(p);
		return 0; //ritorno 0 se tutto e' andato a buon fine
		}

//inserimento normale
	else{
		p -> next = temp2;
                p -> prec = temp2 -> prec;
                temp2 -> prec -> next = p;
	}

return 0; //ritorno 0 se e' andato a buon fine

}

//definisco una funzione per la stampa, ritorna il tipo di componente, oppure un valore negativo se la lista e' vuota o da' errore
int stampa_componenti(inventario inventario){
	int tipo = 0; //variabile per il tipo di componente
	char ch = 0;
	int i= 1; //variabile per stampare i componenti
	struct nodo_inventario* p = NULL; //puntatore per scorrere l'inventario
	struct nodo_componente* t = NULL; //puntatore per scorrere la lista di componenti
	p = inventario -> head; //faccio puntare p alla testa
	printf("Che tipo di componenti desideri visualizzare? \n1.Scheda video \n2.Processore \n3.RAM \n4.Scheda madre \n5.Hard disk \n6.SSD \n7.Case\n\n");
	scanf("%d", &tipo);
	printf("\n");
        while(ch = getchar() != '\n' && ch != EOF); //svuoto il buffer
//se l'utente inserisce un valore non valido stampo un messaggio d'errore
        while ((tipo != 1) && (tipo != 2) && (tipo != 3) && (tipo != 4) && (tipo != 5) && (tipo != 6) && (tipo != 7)){ 
                printf("\nInput non valido! Inserisci un input corretto: "); 
                scanf("%d", &tipo);
                while(ch = getchar() != '\n' && ch != EOF); //svuoto il buffer
                }
        while(p -> type != tipo)
        p = p -> next;
	t = p -> componenti;
//se la lista di componenti fosse vuota
	if(t== NULL){
		printf("Non sono presenti componenti di questo tipo!\n");
		return -1;
	}
//stampo i componenti
	printf("\n");
	while(t != NULL){
		printf("%d. %s, Prezzo: %.2f€, Disponibilita' %d pezzi\n",i, t -> componente -> nome, t -> componente -> prezzo, t -> componente -> numero);
		t = t -> next;
		i++;
		}
	return tipo;
}


//definisco una funzione per cancellare un componente
int cancella_comp(inventario inventario, struct nodo_componente* t){
	struct nodo_inventario* p = NULL;
	p = inventario -> head;
	while (p -> type != t -> componente -> type){
		p = p -> next;
	}
//l'elemento da cancellare e' in testa
	if(p -> componenti == t){
		if(t-> next == NULL){ //l'elemento e' l'unico presente
			p -> componenti = NULL;
			}
		else{
			t -> next -> prec = NULL;
			p -> componenti = t -> next;
		}
	}
//l'elemento da cancellare e' in coda
	else if(t -> next == NULL){
		t -> prec -> next = NULL;
		}
//l'elemento da cancellare e' in posizione normale
	else{
	t -> next -> prec = t -> prec;
	t -> prec -> next = t -> next;
	}
free(t-> componente); //dealloco il componente
free (t); //dealloco il nodo
return 0; //ritorno 0 se e' andata a buon fine
}



int cancellazione_comp (inventario inventario) {
	int tipo = 0; //variabile per memorizzare il tipo di componente da cancellare
	int i = 0; //contatore
	int counter = 1; //contatore
	struct nodo_inventario* p = NULL; //puntatore per scorrere l'inventario
	struct nodo_componente* t = NULL; //puntatore per scorrere la lista dei componenti
	p = inventario -> head;
	tipo = stampa_componenti(inventario);
	if (tipo == -1){
		return -1; //se va male ritorno NULL
		}
	printf(GREEN);
	printf("\nInserisci il numero del componente che desideri eliminare\n");
	printf(RESET);
	scanf("%d", &i);
//scorro l'inventario
	while(p-> type !=tipo)
		p= p-> next;
	t = p -> componenti;
//scorro la lista dei componenti
	while((counter != i) && (t != NULL)){
		t = t-> next;
		counter++;
		}
//in caso l'utente dovesse inserire un numero superiore al numero di componenti presente
	if(t == NULL){
		printf("Comando non valido!\n");
		return -1;
		}
		cancella_comp(inventario, t);
return 0;
}



//creo una funzione per copiare un componente
componente* copia_componente (componente* comp){
	componente* new_comp = NULL;
        new_comp = (componente*)malloc(sizeof(componente)); //alloco un puntatore a componente
	if (new_comp == NULL){
		free(new_comp);
		return NULL; //se va male ritorno null
	}
//copio i campi del componente
	strcpy(new_comp -> nome, comp -> nome);
	new_comp -> type = comp -> type;
	new_comp -> prezzo = comp -> prezzo;
	new_comp -> numero = 1; //metto il numero pari a 1 perche' voglio la copia di un singolo componente
	return new_comp;
}

void salva_inventario (inventario inventario){
        struct nodo_inventario* p = NULL; //puntatore per scorrere l'inventario
        struct nodo_componente* t = NULL; //puntatore per scorrere la lista dei componenti
	p= inventario -> head; //faccio puntare il puntatore alla testa dell'invetario
	int counter = 1; //contatore per scorrere i 7 nodi della lista
	FILE * f =fopen("inventario.txt", "w"); //apro il file in scrittura
	if (f == NULL){
		perror("\nErrore nella scrittura su file\n");
		exit(1);
	}
//faccio ciclare 7 volte per scorrere i 7 nodi della lista
	while((counter != 8) &&(p -> componenti != NULL)){
		t= p -> componenti;
		while( t != NULL){
//scrivo su file i campi della mia struct isolando il nome
			fprintf(f, "%d %.2f %d\n%s\n", t -> componente -> type,t -> componente -> prezzo, t -> componente -> numero, t -> componente -> nome);
			t = t -> next;
		}
		p = p-> next; //scorro la lista
		counter++;
	}
	fclose(f);
	return;
}

inventario carica_inventario (){
	inventario new_inv = crea_inventario(); //creo il nuovo inventario
        componente* comp =(componente*)malloc(sizeof(componente)); //alloco un puntatore a componente
	FILE *f = fopen("inventario.txt", "r"); //apro in scrittura il file
	if(f == NULL){
		perror("Errore nella scrittura del file\n");
		exit(1);
	}
//leggo la prima riga del file salvando tipo, prezzo e numero di componenti nel puntatore a componente
	while(fscanf(f,"%d %f %d\n", &comp -> type,&comp -> prezzo, &comp -> numero) != EOF){
		fgets(comp -> nome, 51 , f); 
//prendo il nome del componente alla riga successiva
		fgets_newline_kill(comp->nome); 
//funzione che elimina il \n memorizzato dalla fgets
		componente* comp_copia  = copia_componente (comp); 
//creo una copia del componente per l'inserimento
		comp_copia -> numero = comp -> numero;
//inserisco il componente all'interno dell'inventario creato
		inserimento_ordinato_componenti(new_inv, comp_copia);
	}
	fclose(f);
free(comp);
//ritorno il puntatore all'inventario
return new_inv;
}


//creo una funzione che deallochi la memoria in chiusura
void libera_inventario (inventario inv){
	int counter1 = 1; //contatore per svuotare i 7 nodi
	struct nodo_inventario* a = NULL; //precedente
	struct nodo_inventario* b = NULL; //successivo
	struct nodo_componente* c = NULL; //precedente
	struct nodo_componente* d = NULL; //successivo
//faccio puntare i puntatori alla testa della lista
	a = inv -> head; 
	b = inv -> head;
	while (counter1 != 8){
		c = a -> componenti; //faccio puntare i puntatori a componente alla testa della sottolista
		d = b -> componenti;
		while (d != NULL){
			d = d-> next; //porto avanti il successivo
			free(c -> componente); //dealloco il componente
			free(c); //dealloco il nodo componente
			c = d; //precedente raggiunge il successivo
		}
		free(c); //dealloco l'ultimo nodo componente
	b = b -> next; //porto avanti il successivo
	free(a); //dealloco il nodo inventario
	a = b; //precedente raggiunge il successivo
	counter1++;
	}
	free(a); //dealloco il nodo
	free(inv); //dealloco la lista
	return;
}


