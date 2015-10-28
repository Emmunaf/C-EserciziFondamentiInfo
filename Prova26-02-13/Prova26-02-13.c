#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N_MAX 20

typedef struct paziente{
	char CF[17], nome[25], cognome[25];
	char stato;//R ricoverato, D dimesso
	struct paziente *next;
} t_paziente;

typedef struct reparto{
	int n;
	struct ricoverato
	{
		char CF[17];
		struct ricoverato *next;
	} *ricoverato;
} t_reparto;

typedef struct ricoverato t_ricoverato;
void caricaPazienti(t_paziente **pazienti);
void addOnTop(t_paziente **pazienti, char nome[25], char cognome[25],char CF[17], char stato);
void mostraPazienti(t_paziente *pazienti);
void caricaReparti(t_reparto *reparti);
void aggiungiAlReparto(t_reparto *reparti, int nReparto, char CF[17], int j);
void mostraReparti(t_reparto *reparti, int i);
void menu(t_paziente **pazienti, t_reparto *reparti);
void dimettiPaziente(t_reparto *reparti, t_paziente **pazienti, char CF[17]);
void salvaModifiche(t_reparto *reparti, t_paziente *pazienti);

int main(int argc, char **argv){
	t_paziente *pazienti = NULL;
	t_reparto reparti[4];
	caricaPazienti(&pazienti);
	caricaReparti(reparti);
	menu(&pazienti, reparti);
	//mostraPazienti(pazienti);
	return 0;
}

void menu(t_paziente **pazienti, t_reparto *reparti){
	while(1){
		int scelta = 0;
		printf("Cosa vuoi fare?\n1 per inserire un nuovo paziente.\n2 per dimettere un paziente.\n3 Per visualizzare i pazienti di un reparto\n4 Uscita con salvataggio.\n");
		scanf(" %d", &scelta);
		switch(scelta){
			case 1:
				printf("Immettere il numero del reparto\n");
				int nReparto;
				char nome[25], cognome[25], CF[17];
				scanf(" %d", &nReparto);
				if(reparti[nReparto].n >= N_MAX){
					fprintf(stderr, "Raggiunta quota pazienti massima.\n");
					break;
				}
				printf("Immettere i dati del paziente\nNome:\n");
				scanf("%24s", nome);
				printf("Cognome:\n");
				scanf("%24s", cognome);
				printf("CF. :\n");
				scanf("%16s", CF);
				addOnTop(pazienti, nome, cognome, CF, 'R');
				aggiungiAlReparto(reparti, nReparto, CF, (reparti[nReparto].n+1));
			break;
			case 2:
				printf("Inserire il CF del paziente da dimettere:\n");
				scanf("%16s", CF);
				printf("Codice inserito %s\n", CF);
				dimettiPaziente(reparti, pazienti, CF);
			break;
			case 3:
				printf("Immettere il numero del reparto\n");
				scanf(" %d", &nReparto);
				mostraReparti(reparti, nReparto);
			break;
			case 4:
				salvaModifiche(reparti, *pazienti);//Salva
				exit(0);//Esci senza codice di errore
			break;
			default:
				exit(1);
			break;
		}
	}
}

void caricaPazienti(t_paziente **pazienti){
	char CF[17], nome[25], cognome[25];
	char stato;
	FILE *fpi1 = fopen("pazienti.txt", "r");
	if(fpi1 == NULL){
		fprintf(stderr, "Problema in lettura\n");
		exit(1);
	}
	while(fscanf(fpi1, "%25s%25s%16s %c", nome, cognome,CF,&stato) == 4){
		addOnTop(pazienti, nome, cognome, CF, stato);
	}
	fclose(fpi1);
}

void caricaReparti(t_reparto *reparti){
	char temp[17];
	int nReparto;
	FILE * fpi2 = fopen("reparti.txt", "r");
	if(fpi2 == NULL)
		exit(1);//Problemi nell'apertura file in modalità lettura.
	while(fscanf(fpi2, "%s %d", temp, &nReparto) == 2){
		int j = 0;
		fscanf(fpi2, " %d", &j);
		for (int i = 0; i < j; ++i)
		{
			fscanf(fpi2, " %16s", temp);
			aggiungiAlReparto(reparti, nReparto, temp, j);
		}
	}
	fclose(fpi2);

}

void aggiungiAlReparto(t_reparto *reparti, int nReparto, char CF[17], int j){
	if(reparti[nReparto].ricoverato == NULL){
		//printf("Creato reparto %d\n", nReparto);
		reparti[nReparto].ricoverato = malloc(sizeof(t_ricoverato));
		if(reparti[nReparto].ricoverato == NULL)
			exit(1); //memoria prob.
		reparti[nReparto].n = j;
		strcpy(reparti[nReparto].ricoverato->CF, CF);
		reparti[nReparto].ricoverato->next = NULL;
	}
	else{
		t_ricoverato *temp;
		temp = malloc(sizeof(t_ricoverato));
		if(temp == NULL)
			exit(1);
		strcpy(temp->CF, CF);
		temp->next = reparti[nReparto].ricoverato;
		reparti[nReparto].ricoverato = temp;
		reparti[nReparto].n = j;
	}

}

void addOnTop(t_paziente **pazienti, char nome[25], char cognome[25],char CF[17], char stato){
	if((*pazienti) == NULL){//Lista vuota
		(*pazienti) = malloc(sizeof(t_paziente));
		if((*pazienti) == NULL){
			exit(1);//non abb. memoria
		}
		strcpy((*pazienti)->CF, CF);
		strcpy((*pazienti)->nome, nome);
		strcpy((*pazienti)->cognome, cognome);
		(*pazienti)->stato = stato;
		(*pazienti)->next = NULL;
	}
	else{
		t_paziente *temp = NULL;
		temp = malloc(sizeof(t_paziente));
		if(temp == NULL){
			exit(1);
		}
		strcpy(temp->CF, CF);
		strcpy(temp->nome, nome);
		strcpy(temp->cognome, cognome);
		temp->stato = stato;
		temp->next = (*pazienti);
		(*pazienti) = temp; 
	}

}

void dimettiPaziente(t_reparto *reparti, t_paziente **pazienti, char CF[17]){
	int trovato = 0;
	t_ricoverato *temp, *tempp;
	for (int i = 1; (i <= 3) && (trovato == 0); ++i)
	{
		temp = reparti[i].ricoverato;
		while((temp->next != NULL) && (strcmp(temp->next->CF, CF) != 0)){
			temp = temp->next;
		}
		if(strcmp(temp->next->CF, CF) == 0){//Controllo che non sia il primo elemento
			trovato = 1;
			tempp = temp->next;
			temp->next = temp->next->next;
			free(tempp);
			reparti[i].n--;//Un paziente in meno nel reparto!
		}
		else if(strcmp(reparti[i].ricoverato->CF, CF) == 0){
			trovato = 1;
			tempp = reparti[i].ricoverato->next;
			reparti[i].ricoverato->next = reparti[i].ricoverato->next->next;
			free(tempp);
			reparti[i].n--;//Un paziente in meno nel reparto!
		}
	}
	if(!trovato){
		fprintf(stderr, "Paziente non trovato!\n");
		return;//Paziente non trovato
	}//Elimino nodo e svuoto memoria
	//Modifico lo stato del paziente a Dimesso
	t_paziente *temp2 = (*pazienti);
	while(strcmp(temp2->CF, CF) != 0){
		temp2=temp2->next;
	}
	temp2->stato = 'D';
}

void mostraReparti(t_reparto *reparti, int i){
	printf("Il reparto n° %d ha %d pazienti\n", i, reparti[i].n);
	t_ricoverato *temp = reparti[i].ricoverato;
	while(temp!=NULL){
		printf("%s\n", temp->CF);
		temp=temp->next;
	}
}

void mostraPazienti(t_paziente *pazienti){
	t_paziente *temp = pazienti;
	while(temp!=NULL){
		printf("%s\n", temp->CF);
		printf("%s\n", temp->nome);
		printf("%s\n", temp->cognome);
		printf("%c\n", temp->stato);
		temp=temp->next;
	}
}

void salvaModifiche(t_reparto *reparti, t_paziente *pazienti){
	FILE * fpi2 = fopen("reparti.txt", "w");
	if(fpi2 == NULL)
		exit(1);//Problemi nella scrittura del file.
	for (int i = 1; i <= 3; ++i)//Aaaa
	{
		t_ricoverato *temp = reparti[i].ricoverato;
		fprintf(fpi2, "Reparto %d\n", i);
		fprintf(fpi2, "%d\n", reparti[i].n);
		while(temp!=NULL){
			fprintf(fpi2, "%s\n", temp->CF);
			temp=temp->next;
		}
	}
	fclose(fpi2);

	t_paziente *temp2 = pazienti;
	FILE *fpi1 = fopen("pazienti.txt", "w");
	if(fpi1 == NULL){
		fprintf(stderr, "Problema in scrittura\n");
		exit(1);
	}
	while(temp2 != NULL){
		fprintf(fpi1, "%s\n%s\n%s\n%c\n", temp2->nome, temp2->cognome, temp2->CF, temp2->stato);
		temp2=temp2->next;
	}
	fclose(fpi1);
}