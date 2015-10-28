/*
 * @author     Emanuele Munafò
 * @input	   char *nome, int *pezziricambio
 * @outpur     Costo riparazione, tempo riparazione, controllo errori
 * @version    
 * @comment    Prova d'esame 27/05/15 Fondamenti di Informatica
 */
#define N 10//Max. numero veicoli che è possibile riparare
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Struct per i pezzi di ricambio
typedef struct ricambi{
	char descrizione[101];
	int giorniOrdine, oreSostituzione;
	unsigned long int id;
	float prezzo;
} t_ricambi;
//Definizione array listaRicambi contenente tutti i pezzi di ricambio.
t_ricambi listaRicambi[100];

//Struct per il listino contenente tutti i possibili veicoli da riparare
typedef struct listino {
	char tipoVeicolo[10], nomeModello[31];
	int cilindrataVeicolo;
	int idRicambi[10];
} t_listino;
//Definizione listino veicoli come array
t_listino listinoVeicoli[N];

//Prototipi funzioni
void caricaListaRicambi(t_ricambi *listaRicambi);
void caricaListinoVeicoli(t_listino *listinoVeicoli);
void calcolaCostoeTempo(char *nome, int *pezziRicambio, int numeroPezzi);
int controllaErrori(char *nome, int *pezziRicambio, int numeroPezzi);

int main(int argc, char **argv){
	int pezzo;//Temporanea per id pezzi ricambi [opz]
	int numeroPezzi=0;
	int pezziRicambio[10];
	char nome[31];

	caricaListaRicambi(listaRicambi);
	caricaListinoVeicoli(listinoVeicoli);
	printf("Inserisci nome modello\n");
	scanf("%s", nome);
	printf("Inserisci i codici dei pezzi da sostituire separati dal carattere Invio.\nQuando hai finito digita una lettera e premi invio\n");
	while((scanf("%d", &pezzo) == 1) && (numeroPezzi<10)){
		pezziRicambio[numeroPezzi] = pezzo;
		++numeroPezzi;
	}
	calcolaCostoeTempo(nome, pezziRicambio, numeroPezzi);
	printf("Ricerca completata.\nReturn Code 1\n");
	return 1;
}

void calcolaCostoeTempo(char *nome, int *pezziRicambio, int numeroPezzi){
	controllaErrori(nome, pezziRicambio,numeroPezzi);
	float costoTot=0.0;
	int giorni=1;
	for(int i=0;i<numeroPezzi;i++){
		int j=0;
		while(listaRicambi[j].id < pezziRicambio[i]){
			++j;
		}
		costoTot += listaRicambi[j].prezzo + (listaRicambi[j].oreSostituzione * 20);
		if(giorni < listaRicambi[j].giorniOrdine){
			giorni = listaRicambi[j].giorniOrdine;
		}
	}
	printf("Il costo totale è %.2f.\n", costoTot);
	printf("Il tempo d'attesa totale è %d giorni.\n", giorni);
}

//La funzione verifica se i pezzi da sostituire sono compatibili con il mezzo: 1 se si, 0 altrimenti
int controllaErrori(char *nome, int *pezziRicambio, int numeroPezzi){
	int j=0;
	while(strcmp(listinoVeicoli[j].nomeModello, nome) != 0){
		if(j==N){
			fprintf (stderr, "Veicolo non trovato.\nReturn Code: 0\n");
			exit(0);
		}
		j++;
	}

	for(int i=0;i<numeroPezzi;i++){
		int k = 0;
		while(listinoVeicoli[j].idRicambi[k] != pezziRicambio[i]){
			if(k>=N){//se arriva al 11-esimo elemento, significa che il pezzo di ricambio NON è adatto al veicolo.
				fprintf (stderr, "Pezzo non compatibile con il veicolo.\nReturn Code: 0\n");
				exit(0);
			}
			++k;
		}
	}
	return 1;//Ok, tutti i pezzi sono compatibili e presente nella lista.
}

void caricaListaRicambi(t_ricambi *listaRicambi){
	/* Creo la lista ricambi... */
	strcpy(listaRicambi[0].descrizione, "Pasticche freni");
	listaRicambi[0].id = 1111111110;
	listaRicambi[0].giorniOrdine = 1;
	listaRicambi[0].oreSostituzione = 1;
	listaRicambi[0].prezzo = 30.65;

	strcpy(listaRicambi[1].descrizione, "Tergicristalli");
	listaRicambi[1].id = 1111111111;
	listaRicambi[1].giorniOrdine = 1;
	listaRicambi[1].oreSostituzione = 1;
	listaRicambi[1].prezzo = 20.15;

	strcpy(listaRicambi[2].descrizione, "Copertoni anteriori");
	listaRicambi[2].id = 1111111112;
	listaRicambi[2].giorniOrdine = 2;
	listaRicambi[2].oreSostituzione = 1;
	listaRicambi[2].prezzo = 90.25;

	strcpy(listaRicambi[3].descrizione, "Fanale Moto");
	listaRicambi[3].id = 1111111113;
	listaRicambi[3].giorniOrdine = 3;
	listaRicambi[3].oreSostituzione = 1;
	listaRicambi[3].prezzo = 23.25;
	/* ........................................ */
}

void caricaListinoVeicoli(t_listino *listinoVeicoli){
	// Creo la lista con i veicoli correllati ai pezzi COMPATIBILI... 
	strcpy(listinoVeicoli[0].tipoVeicolo, "moto");
	strcpy(listinoVeicoli[0].nomeModello, "sst125");
	listinoVeicoli[0].cilindrataVeicolo = 125;
	listinoVeicoli[0].idRicambi[0] = 1111111110; //Possibile ricambio per moto sst125 
	listinoVeicoli[0].idRicambi[1] = 1111111113; //Altro ricambio disponibile per sst125

	strcpy(listinoVeicoli[1].tipoVeicolo, "furgone");
	strcpy(listinoVeicoli[1].nomeModello, "fiorino");
	listinoVeicoli[1].cilindrataVeicolo = 1200;
	listinoVeicoli[1].idRicambi[0] = 1111111111; 
	listinoVeicoli[1].idRicambi[1] = 1111111112;

	/* ........................................ */
}