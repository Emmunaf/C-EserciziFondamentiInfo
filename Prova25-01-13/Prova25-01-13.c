#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
	
*/
typedef struct data{
	int giorno, mese, anno;//Nel formato 01 12 2015
}t_data;

typedef struct appalto{
	char luogo[50], committenteCF[17];//committenteCF = c.f o P.iva del committente
	float valore;
	int durataPrevista, durataEffettiva;//In giorni.
	t_data data;//Accedo con appalto->data.[giorno]...
	struct appalto *next;
} t_appalto;

typedef struct cliente{
	char rSociale[35], CF[17];//CF o P.iva (11char)
	struct cliente *next;
} t_cliente;

//Prototipi funzioni
void aggiungiCliente(t_cliente **clienti, char *rSociale, char *CF);
void mostraClienti(t_cliente *clienti);
int cercaCliente(t_cliente *clienti, char *CF);
void aggiungiAppalto(t_cliente **clienti, t_appalto **appalti, char *luogo, char *committenteCF, float valore, int durataPrevista);
void menuScelta(t_cliente **clienti, t_appalto **appalti);
void mostraAppalti(t_appalto *appalti, int anno);
void aggiornaData(t_appalto **appalti, char *committenteCF, t_data data);
void aggiornaDurata(t_appalto **appalti, char *committenteCF, int durataEffettiva, t_data data);

int main(int argc, char **argv){
	t_appalto *appalti = NULL;
	t_cliente *clienti = NULL;
	menuScelta(&clienti, &appalti);
	return 0;
}

void menuScelta(t_cliente **clienti, t_appalto **appalti){
	int scelta;
	printf("Scegli l'operazione da effettuare:.\n");
	printf("1 Inserimento di un nuovo cliente.\n");
	printf("2 Inserimento di un nuovo appalto.\n");
	printf("3 Aggiornamento di un appalto (data inizio lavori).\n");
	printf("4 Aggiornamento di un appalto (durata effettiva lavori).\n");
	printf("5 Stampa statistiche annuali.\n");
	printf("Altro per uscire.\n");
	scanf("%d", &scelta);
	switch(scelta){
		case 1:
			printf("Inserire i dettagli del nuovo cliente.\n");
			char rSociale[35], CF[17];
			printf("Inserire la ragione sociale (senza spazi):\n");
			scanf("%34s", rSociale);
			printf("Inserire il CF o la P.Iva:\n");
			scanf(" %16s", CF);
			aggiungiCliente(clienti, rSociale, CF);
		break;
		case 2:
			printf("Inserire i dettagli del nuovo appalto.\n");
			char luogo[50], committenteCF[17];
			float valore;
			int durataPrevista;

			printf("Inserire il luogo\n");
			scanf("%50s", luogo);
			printf("Inserire il CF o la P.Iva:\n");
			scanf(" %16s", committenteCF);
			printf("Inserire il valore:\n");
			scanf(" %f", &valore);
			printf("Inserire la durata prevista (in giorni):\n");
			scanf(" %d", &durataPrevista);
			aggiungiAppalto(clienti, appalti, luogo, committenteCF, valore, durataPrevista);
		break;
		case 3:
			printf("Inserire il CF o la P.Iva:\n");
			t_data data;
			scanf(" %16s", committenteCF);
			printf("Immettere la data nel formato gg/mm/aaaa:\n");
			scanf("%d/%d/%d",&data.giorno, &data.mese, &data.anno);
			aggiornaData(appalti, committenteCF, data);
		break;
		case 4:
			printf("Inserire il CF o la P.Iva:\n");
			scanf(" %16s", committenteCF);
			printf("Per una ricerca accurata è necessario immettere la data di inizio lavori nel formato gg/mm/aaaa:\n");
			scanf("%d/%d/%d",&data.giorno, &data.mese, &data.anno);
			printf("Inserire la durata effettiva dei lavori\n");
			int durataEffettiva;
			scanf("%d", &durataEffettiva);
			aggiornaDurata(appalti, committenteCF, durataEffettiva, data);
		break;

		case 5:
			printf("Inserire l'anno: \n");
			int anno;
			scanf("%d", &anno);
			mostraAppalti(*appalti, anno);
		break;
		default:
			exit(0);
		break;
	}
	menuScelta(clienti, appalti);
}

void aggiungiCliente(t_cliente **clienti, char *rSociale, char *CF){//Aggiunge in cima in lista (LIFO)
	if((*clienti) == NULL){//Lista ancora vuota, primo elemento
		(*clienti) = malloc(sizeof(t_cliente));
		if((*clienti) == NULL)
			exit(1);//Non abbastanza memoria
		strcpy((*clienti)->rSociale, rSociale);
		strcpy((*clienti)->CF, CF);
		(*clienti)->next = NULL;
	}
	else{
		t_cliente *temp;
		temp = malloc(sizeof(t_cliente));
		if(temp == NULL)
			exit(1);//Non abbastanza mem.
		strcpy(temp->rSociale, rSociale);
		strcpy(temp->CF, CF);
		temp->next = (*clienti);
		(*clienti) = temp;
	}
}

void aggiungiAppalto(t_cliente **clienti, t_appalto **appalti, char *luogo, char *committenteCF, float valore, int durataPrevista){//Aggiunge in cima in lista (LIFO)
	if(!cercaCliente((*clienti), committenteCF)){//Il cliente non esiste => aggiungo
		printf("Il cliente non esiste!\nInserire i dettagli del nuovo cliente:\n");
		char rSociale[35];
		printf("Inserire la ragione sociale (senza spazi)\n");
		scanf("%34s", rSociale);
		aggiungiCliente(clienti, rSociale, committenteCF);
	}
	if((*appalti) == NULL){//Lista ancora vuota, primo elemento
		(*appalti) = malloc(sizeof(t_appalto));
		if((*appalti) == NULL)
			exit(1);//Non abbastanza memoria
		strcpy((*appalti)->luogo, luogo);
		strcpy((*appalti)->committenteCF, committenteCF);
		(*appalti)->valore = valore;
		(*appalti)->durataPrevista = durataPrevista;
		(*appalti)->durataEffettiva = 0;
		(*appalti)->next = NULL;
	}
	else{
		t_appalto *temp;
		temp = malloc(sizeof(t_appalto));
		if(temp == NULL)
			exit(1);//Non abbastanza mem.
		strcpy(temp->luogo, luogo);
		strcpy(temp->committenteCF, committenteCF);
		temp->valore = valore;
		temp->durataPrevista = durataPrevista;
		temp->durataEffettiva = 0;
		temp->next = (*appalti);
		(*appalti) = temp;
	}
}

void mostraAppalti(t_appalto *appalti, int anno){
	t_appalto *temp = appalti;
	while(temp != NULL){
		if((temp->data.anno == anno) && (temp->durataEffettiva != 0)){//Se il lavoro è stato compelato
			printf("---------------------\n");
			printf("Committente: %s\nLuogo: %s\nValore: %.2f\nDurata prevista: %d\nDurata effettiva: %d\n",temp->committenteCF, temp->luogo, temp->valore, temp->durataPrevista, temp->durataEffettiva);
		}
		temp = temp->next;
	}
	printf("Ricerca terminata\n");
}

void aggiornaData(t_appalto **appalti, char *committenteCF, t_data data){
	t_appalto *temp = *appalti;
	while(temp != NULL){
		if(strcmp(temp->committenteCF, committenteCF) == 0){
			temp->data = data;
			return;
		}
		temp = temp->next;
	}
}

void aggiornaDurata(t_appalto **appalti, char *committenteCF, int durataEffettiva, t_data data){
	t_appalto *temp = *appalti;
	while(temp != NULL){
		if((strcmp(temp->committenteCF, committenteCF) == 0) && (temp->data.giorno == data.giorno) && (temp->data.mese == data.mese) && (temp->data.anno == data.anno)){
			temp->durataEffettiva = durataEffettiva;
			return;
		}
		temp = temp->next;
	}
}

void mostraClienti(t_cliente *clienti){
	t_cliente *temp = clienti;
	while(temp != NULL){
		printf("CF: %s\nRagione sociale: %s\n",temp->CF, temp->rSociale);
		temp = temp->next; 
	}
}

int cercaCliente(t_cliente *clienti, char *CF){//Restituisce 1 se il cliente esiste.
	t_cliente *temp = clienti;
	while(temp != NULL){
		if(strcmp(temp->CF, CF) == 0){
			return 1;//se Trova restituisce 1 (vero)
		}
		temp = temp->next;
	}
	return 0;
}