#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct candidato
{
	int superato;//Al momento dell'inserimento salvo se ha superato o no
	int valutazioni[4];
	char nome[25], CF[17];
	struct candidato *next;
} t_candidato;

void menu();
void aggiungiCandidato(t_candidato **candidati, char *nome, char *CF, int *valutazioni);
void mostraCandidato(t_candidato *candidati, char *CF);
void mostraCandidati(t_candidato *candidati);
void salvaFile(t_candidato *candidati);

int main(int argc, char const **argv){
	t_candidato *candidati = NULL;
	menu(&candidati);
	return 0;
}

void menu(t_candidato **candidati){
	int continuare = 1, scelta = 0;
	t_candidato temp;
	while(continuare){
		printf("Inserire il nome del candidato:\n");
		scanf("%24s", temp.nome);
		printf("Inserire il suo CF\n");
		scanf("%16s", temp.CF);
		printf("Inserire i voti delle prove nel formato v1-v2-v3-v4:\n");
		scanf("%d-%d-%d-%d", &(temp.valutazioni[0]), &(temp.valutazioni[1]), &(temp.valutazioni[2]), &(temp.valutazioni[3]));
		aggiungiCandidato(candidati, temp.nome, temp.CF, temp.valutazioni);
		printf("Vuoi effettuare un'altro inserimento?\nImmettere 0 per uscire, altro per continuare\n");
		scanf("%d", &continuare);
		/*int array1[] = {5,6,7,8};
		int array2[] = {3,4,2,8};
		int array3[] = {5,6,5,5};
		aggiungiCandidato(candidati, "Emanuele", "MNFAA", array1);
		aggiungiCandidato(candidati, "Marisa", "MNFMA", array2);
		aggiungiCandidato(candidati, "Pippo", "MNFBA", array3);
		mostraCandidati(*candidati);
		salvaFile(*candidati);*/
	}
	while(1){
		char CF[17];
		printf("----------------------------------------------------\n");
		printf("Cosa vuoi fare?\n");
		printf("1. Visualizza candidati che hanno superato l'esame\n");
		printf("2. Visualizza dettagli candidato per Codice Fiscale\n");
		printf("3. Salva i log su file (logEsami.txt)\n");
		printf("-1. Esci \n");
		scanf("%d", &scelta);
		switch(scelta){
			case 1:
				mostraCandidati(*candidati);
				break;
			case 2:
				printf("Inserire il CF del candidato:\n");
				scanf("%16s", CF);
				mostraCandidato(*candidati, CF);
				break;
			case 3:
				salvaFile(*candidati);
				break;
			case -1:
				exit(0);
				break;
			default:
				fprintf(stderr, "Scelta non valida!\nRiprova\n");
				break;
		}
	}
}

void aggiungiCandidato(t_candidato **candidati, char *nome, char *CF, int *valutazioni){
	//Copio i dati
	t_candidato *temp = malloc(sizeof(t_candidato));
	if(!temp) return;//Problema nell'allocazione di mem.
	strcpy(temp->nome, nome);
	strcpy(temp->CF, CF);
	int j = 0, totValutazione = 0;
	for (int i = 0; i < 4; ++i){
		temp->valutazioni[i] = valutazioni[i];
		totValutazione += valutazioni[i];//Calcolo totale per verificare 1° c.nec per passare
		if(valutazioni[i]>=7)//Controllo se ha avuto 2 o più 7, 2° cond.nec per passare
			++j;
	}
	//Verifico se ha superato 
	if((j >= 2) && (totValutazione >= 20))
		temp->superato = 1;
	else
		temp->superato = 0;

	if((*candidati) == NULL){//Lista vuota
		(*candidati) = temp;
		temp->next = NULL;
	}
	else{//Caso generico
		temp->next = (*candidati);
		(*candidati) = temp;
	}
}

void mostraCandidato(t_candidato *candidati, char *CF){
	t_candidato *temp = candidati;
	while(temp!=NULL){
		if(strcmp(temp->CF, CF) == 0){
			printf("------------------\n");
			printf("Nome: %s\nCF: %s\n", temp->nome, temp->CF);
			printf("Esiti prove:\n");
			printf("Prima: %d\nSeconda: %d\nTerza: %d\nQuarta: %d\n", temp->valutazioni[0], temp->valutazioni[1], temp->valutazioni[2], temp->valutazioni[3]);
			return;
		}
		temp = temp->next;
	}
	fprintf(stderr, "Candidato non trovato!\n");
}
//Mostra i candidati che hanno superato le prove
void mostraCandidati(t_candidato *candidati){
	t_candidato *temp = candidati;
	while(temp != NULL){
		if(temp->superato){
			printf("------------------\n");
			printf("Nome: %s\nCF: %s\n", temp->nome, temp->CF);
			//printf("Esiti prove:\n");
			//printf("Prima: %d\nSeconda: %d\nTerza: %d\nQuarta: %d\n", temp->valutazioni[0], temp->valutazioni[1], temp->valutazioni[2], temp->valutazioni[3]);
		}
		temp = temp->next;
	}
	printf("------------------\n");
}
/*
La funzione salva su file logEsami.txt nel formato:
[nomecandidato]
[CFcandidato]
[Superato?(1 o 0)]
[esitoPrimaValutazione]
[esitoSecondaValutazione]
[esitoTerzaValutazione]
[esitoQuartaValutazione]
..........
*/
void salvaFile(t_candidato *candidati){
	t_candidato *temp = candidati;
	FILE *fpo = fopen("logEsami.txt", "w");//Apro file in modalità scrittura
	if(!fpo){//Se fpo == NULL, errore
		fprintf(stderr, "Problemi nell'apertura del file in modalità scrittura!\n");
		return;
	}

	while(temp != NULL){//Scorro la lista e scrivo sul file di output
		fprintf(fpo, "%s\n%s\n", temp->nome, temp->CF);
		fprintf(fpo, "%d\n%d\n%d\n%d\n%d\n", temp->superato, temp->valutazioni[0], temp->valutazioni[1], temp->valutazioni[2], temp->valutazioni[3]);
		temp = temp->next;
	}
	printf("Salvataggio su file completato con successo!\n");
}
