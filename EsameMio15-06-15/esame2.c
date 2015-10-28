#include "header.h"
/*
Emanuele Munafò
Esame 15/06/15
Ingegneria Elettronica e Informatica
Da compilare con std c99 o c11
*/
int main(int argc, char const **argv){

	t_atleta *atleti = NULL;// Lista atleti
	t_salto *salti = NULL;// Lista salti
	t_classifica *classifica = NULL;// Lista classifica
	menu(&atleti, &salti, &classifica);
	return 0;
}

void menu(t_atleta **atleti, t_salto **salti, t_classifica **classifica){
	int scelta, nAtleti = 0;
	do {
		printf(" ------- Menu ------- \n");
		printf("Effettua una scelta:\n");
		printf("(1)  Per caricare i dati degli atleti dal file 'atleti.txt'\n      e i salti dal file 'salti.txt'\n");
		printf("(2)  Per caricare i dati manualmente\n");
		printf("(3)  Per visualizzare classifica in ordine\n");
		printf("(4)  Per visualizzare i primi 3\n");
		printf("(-1) Per terminare.\n");
		scanf(" %d", &scelta);

		switch(scelta){
			case 1:// Carica dati dai file
				if(nAtleti != 0){// Dati già caricati!
					fprintf(stderr, "Dati già caricati, eseguire un nuovo processo per un altro inserimento!\n\n");
					break;
				}
				nAtleti = caricaAtletiDaFile(atleti);
				caricaSaltiDaFile(salti, nAtleti);
				elaboraDati(classifica, atleti, salti, nAtleti);
				break;
			case 2:
				if(nAtleti != 0){// Dati già caricati!
					fprintf(stderr, "Dati già caricati, eseguire un nuovo processo per un altro inserimento!\n\n");
					break;
				}
				printf("Inserire il numero degli atleti\n:");
				scanf("%d", &nAtleti);
				caricaAtletiManualmente(atleti, nAtleti);
				caricaSaltiManualmente(salti, nAtleti);
				elaboraDati(classifica, atleti, salti, nAtleti);
				break;
			case 3:
				mostraClassifica(*classifica);
				break;
			case 4:
				mostraTop3(*classifica);
				break;
			case -1:
				exit(0);
				break;
			default:
				fprintf(stderr, "Scelta non corretta!\n");
				break;
		}
	}
	while(scelta != -1);
}

void aggiungiAtleta(t_atleta **atleti, int nPettorale, char *siglaNazione, char *cognome, char *nome){
	t_atleta *temp = malloc(sizeof(t_atleta));
	if(temp == NULL){
		fprintf(stderr, "Problema nell'allocazione di memoria!\n");
		return;// Problema nell'allocazione di memoria
	}
	temp->nPettorale = nPettorale;
	strcpy(temp->siglaNazione, siglaNazione);
	strcpy(temp->cognome, cognome);
	strcpy(temp->nome, nome);

	if((*atleti) == NULL){// Aggiungo primo elemento alla lista (vuota)
		(*atleti) = temp;
		(*atleti)->next = NULL;
	}
	else{
		temp->next = (*atleti);
		(*atleti) = temp;
	}
}
int caricaAtletiDaFile(t_atleta **atleti){
	printf("Carico atleti dal file 'atleti.txt'...\n");
	int nAtleti;
	t_atleta temp;
	FILE *fpi1 = fopen("atleti.txt", "r");
	if(fpi1 == NULL){
		fprintf(stderr, "Impossibile aprire il file atleti.txt\n");
		exit(2);
	}
	if(fscanf(fpi1, "%d", &nAtleti) == 1){
		for(int i = 0; i < nAtleti; ++i){
			fscanf(fpi1, "%d %3s %s %s", &temp.nPettorale, temp.siglaNazione, temp.cognome, temp.nome);
			aggiungiAtleta(atleti, temp.nPettorale, temp.siglaNazione, temp.cognome, temp.nome);
		}
	}
	fclose(fpi1);
	return nAtleti;
}

void mostraAtleti(t_atleta *atleti){
	t_atleta *temp = atleti;
	while(temp != NULL){
		printf("--------------------\n");
		printf("N.pettorale: %d\nSigla Nazione: %s\nCognome: %s\nNome: %s\n", temp->nPettorale, temp->siglaNazione, temp->cognome, temp->nome);
		temp = temp->next;
	}
}
void aggiungiSalto(t_salto **salti, int nPettorale, int lunghezza, char validita){
	t_salto *temp = malloc(sizeof(t_salto));
	if(temp == NULL){
		fprintf(stderr, "Problema nell'allocazione di memoria\n");
		return;
	}
	temp->nPettorale = nPettorale;
	temp->lunghezza = lunghezza;
	temp->validita = validita;

	if((*salti) == NULL){// Aggiungo primo elemento alla lista( vuota)
		(*salti) = temp;
		(*salti)->next = NULL;
	}
	else{
		temp->next = (*salti);
		(*salti) = temp;
	}
}
void caricaSaltiDaFile(t_salto **salti, int nAtleti){
	t_salto temp;
	char line[10];
	printf("Carico salti dal file 'salti.txt'...\n");
	FILE *fpi2 = fopen("salti.txt", "r");
	if(fpi2 == NULL){
		fprintf(stderr, "Impossibile aprire il file salti.txt\n");
		exit(2);
	}
	for (int i = 0; i < (nAtleti*3); ++i)
	{
		fgets(line, 10, fpi2);
		if(sscanf(line, "%d %c %3d", &temp.nPettorale, &temp.validita, &temp.lunghezza) == 2){
			aggiungiSalto(salti, temp.nPettorale, 0, temp.validita);
		}
		else{
			aggiungiSalto(salti, temp.nPettorale, temp.lunghezza, temp.validita);
		}
	}
	fclose(fpi2);
}
void mostraSalti(t_salto *salti){
	t_salto *temp = salti;
	while(temp != NULL){
		printf("--------------------\n");
		printf("N.pettorale: %d\nValidita': %c\nLunghezza: %d\n", temp->nPettorale, temp->validita, temp->lunghezza);
		temp = temp->next;
	}
}

void aggiungiInClassifica(t_classifica **classifica, int nPettorale, char *siglaNazione, char *cognome, char *nome, int maxsalto){
	// Creo elemento
	t_classifica *tempp = malloc(sizeof(t_classifica));
	if(tempp == NULL){
		fprintf(stderr, "Problema nell'allocazione di memoria\n");
		return;
	}
	tempp->nPettorale = nPettorale;
	strcpy(tempp->siglaNazione, siglaNazione);
	strcpy(tempp->cognome, cognome);
	strcpy(tempp->nome, nome);
	tempp->lunghezza = maxsalto;

	if((*classifica) == NULL){// Aggiungo primo elemento alla lista( vuota)
		(*classifica) = tempp;
		(*classifica)->next = NULL;
	}
	else{
		t_classifica *temp = *classifica;
		t_classifica *l = *classifica;
		// Cerco la posizione corretta in classifica
		while((temp != NULL) && (temp->lunghezza > maxsalto)){
			l = temp;
			temp = temp->next;
		}
		if(temp == *classifica){// Inserisco in testa
			*classifica = tempp;
			tempp->next = l;
		}
		else{
			l->next = tempp;
			tempp->next = temp;
		}
	}
}
void mostraClassifica(t_classifica *classifica){
	if(classifica == NULL){
		fprintf(stderr, "Caricare prima i dati!\n");
		return;
	}

	t_classifica *temp = classifica;
	printf("Di seguito verranno mostrati i risultati in ordine di posto crescente:\n");
	int i = 0;
	while(temp != NULL){
		printf("----------------------\n");
		printf("Posto classifica: %d°\n", ++i);
		printf("N.pettorale: %d\nSigla Nazione: %s\nCognome: %s\nNome: %s\nLunghezza Salto:%d cm\n", temp->nPettorale, temp->siglaNazione, temp->cognome, temp->nome, temp->lunghezza);
		temp = temp->next;
	}
	printf("----------------------\n");
}

void mostraTop3(t_classifica *classifica){
	if(classifica == NULL){
		fprintf(stderr, "Caricare prima i dati!\n");
		return;
	}

	t_classifica *temp = classifica;
	printf("Di seguito verranno mostrati i risultati degli atleti sul podio:\n");
	int i = 0;
	while(temp != NULL && i < 3){
		printf("----------------------\n");
		printf("Posto classifica: %d°\n", ++i);
		printf("N.pettorale: %d\nSigla Nazione: %s\nCognome: %s\nNome: %s\nLunghezza Salto:%d cm\n", temp->nPettorale, temp->siglaNazione, temp->cognome, temp->nome, temp->lunghezza);
		temp = temp->next;
	}
	printf("----------------------\n");
}

void elaboraDati(t_classifica **classifica, t_atleta **atleti, t_salto **salti, int nAtleti){
	t_atleta *temp = *atleti;
	t_salto *temp2 = *salti;
	for (int i = 0; i < nAtleti; ++i){
		int max = 0;
		temp2 = *salti;
		while(temp2 != NULL){
			if((temp2->nPettorale == temp->nPettorale) && (max < temp2->lunghezza)){
				max = (temp2->lunghezza);
			}
			temp2 = temp2->next;
		}
		aggiungiInClassifica(classifica, temp->nPettorale, temp->siglaNazione, temp->cognome, temp->nome, max);
		temp = temp->next;
	}
}

void caricaAtletiManualmente(t_atleta **atleti, int nAtleti){
	t_atleta temp;
	printf("Caricamento manuale dei salti:\n");

	for (int i = 0; i < (nAtleti); ++i)
	{
		printf("Inserire dati del %d° partecipante:\n", i+1);
		printf("N. Pettorale:\n");
		scanf("%d", &temp.nPettorale);
		printf("Sigla Nazione:\n");
		scanf("%3s", temp.siglaNazione);
		printf("Cognome:\n");
		getchar();// Fix for \n
		fgets(temp.cognome, 24, stdin);// Possono esservi spazi
		printf("Nome:\n");// Possibili spazi
		fgets(temp.nome, 24, stdin);
		aggiungiAtleta(atleti, temp.nPettorale, temp.siglaNazione, temp.cognome, temp.nome);
	}
}

void caricaSaltiManualmente(t_salto **salti, int nAtleti){
	t_salto temp;
	printf("Caricamento manuale dei salti:\n");

	for (int i = 0; i < (nAtleti); ++i)
	{
		printf("Inserire dati del %d° partecipante:\n", i+1);
		printf("N. Pettorale:\n");
		scanf("%d", &temp.nPettorale);
		for(int k=0;k<3;k++){
			printf("%d° salto\n", k+1);
			printf("Validita': (V o N)\n");
			scanf(" %c", &temp.validita);
			printf("Lunghezza:\n");
			scanf("%d", &temp.lunghezza);

			if(temp.validita == 'N'){
				aggiungiSalto(salti, temp.nPettorale, 0, temp.validita);
			}
			else if (temp.validita == 'V'){
				aggiungiSalto(salti, temp.nPettorale, temp.lunghezza, temp.validita);
			}
			else{
				fprintf(stderr, "Validita' deve assumere valore V per valido o N per nullo\n");
				fprintf(stderr, "L'inserimento è considerato non valido, riprovare\n");
			}
		}
	}
}
