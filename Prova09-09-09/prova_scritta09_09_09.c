#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct catalogo
{
	char categorie[20], destinatario[40];
	int annoProduzione, disponibilita;
	float prezzo;
	struct catalogo *next;
} t_catalogo;

void menu(t_catalogo **listaCatalogo);
void aggiungiElementoACatalogo(t_catalogo **listaCatalogo, char *categorie, char *destinatario, int annoProduzione, int disponibilita, float prezzo);
void aggiungiASelezione(t_catalogo **listaCatalogo, t_catalogo **selezionatiCatalogo, char scelta);
void aggiungiElementoASelezione(t_catalogo **selezionatiCatalogo, char *categorie, char *destinatario, int annoProduzione, int disponibilita, float prezzo);
void rimuoviNonDisponibili(t_catalogo **listaCatalogo);
void riduciPrezzo(t_catalogo **listaCatalogo, int annoProduzione);
void selezionaProdotti(t_catalogo **listaCatalogo, t_catalogo **selezionatiCatalogo);
void visualizzaDettagli(t_catalogo *selezionatiCatalogo);
void salvaSuFile(t_catalogo *listaCatalogo);
void caricaProdotti(t_catalogo **listaCatalogo);

void showcatalogo(t_catalogo *listaCatalogo);
int main(int argc, char const **argv){
	t_catalogo *listaCatalogo = NULL;
	caricaProdotti(&listaCatalogo);
	//showcatalogo(listaCatalogo);
	menu(&listaCatalogo);
	return 0;
}

void menu(t_catalogo **listaCatalogo){
	int annoProduzione;
	int scelta;
	t_catalogo *selezionatiCatalogo = NULL;
	while(1){
		printf("Effettuare una scelta per indicare cosa si intende fare:\n");
		printf("1. Per ridurre il prezzo del 50%% dei prodotti con anno di produzione minore di uno specificato\n");
		printf("2. Per eliminare dal catalogo i prodotti non disponibili (disponibilita' = 0)\n");
		printf("3. Selezionare un insieme di prodotti\n");
		printf("4. Visualizzare i dati relativi ai prodotti selezionati\n");
		printf("5. Salvare su file\n");
		printf("Altro per uscire (si perderanno le modifiche non salvate!)\n");
		scanf("%d", &scelta);

		switch (scelta){
			case (1):
				printf("Inserire l'anno:\n");
				scanf("%d", &annoProduzione);
				riduciPrezzo(listaCatalogo, annoProduzione);
				break;
			case (2):
				rimuoviNonDisponibili(listaCatalogo);
				break;
			case (3):
				selezionaProdotti(listaCatalogo, &selezionatiCatalogo);
				break;
			case (4):
				visualizzaDettagli(selezionatiCatalogo);
				break;
			case (5):
				salvaSuFile(*listaCatalogo);
				break;
			default:
				exit(0);
				break;
		}
	}
}
/*void showcatalogo(t_catalogo *catalogo){
	t_catalogo *temp = catalogo;
	while(temp != NULL){
		printf("------------------------\n");
		printf("Categoria: %s\n", temp->categorie);
		printf("Anno di produzione: %d\n", temp->annoProduzione);
		printf("Destinatario : %s\n", temp->destinatario);
		printf("Disponibilita': %d\n", temp->disponibilita);
		printf("Prezzo: %f\n", temp->prezzo);
		temp = temp->next;
	}
	printf("------------------------\n");
}*/
void aggiungiElementoACatalogo(t_catalogo **listaCatalogo, char *categorie, char *destinatario, int annoProduzione, int disponibilita, float prezzo){
	t_catalogo *temp = malloc(sizeof(t_catalogo));
	strcpy(temp->categorie, categorie);
	strcpy(temp->destinatario, destinatario);
	temp->annoProduzione = annoProduzione;
	temp->disponibilita = disponibilita;
	temp->prezzo = prezzo;
	if(!(*listaCatalogo)){//La lista è vuota
		(*listaCatalogo) = temp;
		temp->next = NULL;
	}
	else{
		temp->next = (*listaCatalogo);
		(*listaCatalogo) = temp;
	}
}

void aggiungiASelezione(t_catalogo **listaCatalogo, t_catalogo **selezionatiCatalogo, char sceltaa){
	int annoProduzione = -1, categoria = -1, disponibilita = -1;
	t_catalogo *temp = *listaCatalogo;//Per scorrere Listacatalogo
	switch (sceltaa){
		case 'C':
			printf("Esprimere la preferenza su quale categoria selezionare:\n");
			printf("0. Professionale\n");
			printf("1. Sistema operativo\n");
			printf("2. Ufficio\n");
			scanf("%d", &categoria);
			break;
		case 'A':
			printf("Esprimere la preferenza su quale anno selezionare:\n");
			scanf("%d", &annoProduzione);
			break;
		case 'D':
			printf("Esprimere la preferenza su quale disponibilita' selezionare:\n");
			scanf("%d", &disponibilita);
			break;
		default:
			printf("Scelta non valida!\nUsare le lettere maiuscole C, A, D\n");
			break;
		}
	if(annoProduzione != -1){
		while(temp != NULL){
			if(temp->annoProduzione == annoProduzione){
				aggiungiElementoASelezione(selezionatiCatalogo, temp->categorie, temp->destinatario, temp->annoProduzione, temp->disponibilita, temp->prezzo);
			}
			temp = temp->next;
		}
	}
	else if(categoria != -1){
		while(temp != NULL){
			char *listaCategorie[3] = {"Professionale", "SistemaOperativo", "Ufficio"};
			if(strcmp(temp->categorie, listaCategorie[categoria]) == 0){
				aggiungiElementoASelezione(selezionatiCatalogo, temp->categorie, temp->destinatario, temp->annoProduzione, temp->disponibilita, temp->prezzo);
			}
			temp = temp->next;
		}
	}
	else if(disponibilita != -1){
		while(temp != NULL){
			if(temp->disponibilita == disponibilita){
				aggiungiElementoASelezione(selezionatiCatalogo, temp->categorie, temp->destinatario, temp->annoProduzione, temp->disponibilita, temp->prezzo);
			}
			temp = temp->next;
		}
	}
	else{
		fprintf(stderr, "Qualche problema nella scelta effettuata!\n");
		return;
	}
}

void aggiungiElementoASelezione(t_catalogo **selezionatiCatalogo, char *categorie, char *destinatario, int annoProduzione, int disponibilita, float prezzo){
	t_catalogo *temp = malloc(sizeof(t_catalogo));
	printf("Malloc!\n");
	strcpy(temp->categorie, categorie);
	strcpy(temp->destinatario, destinatario);
	temp->annoProduzione = annoProduzione;
	temp->disponibilita = disponibilita;
	temp->prezzo = prezzo;
	if(!(*selezionatiCatalogo)){//La lista è vuota
		(*selezionatiCatalogo) = temp;
		temp->next = NULL;
	}
	else{
		temp->next = (*selezionatiCatalogo);
		(*selezionatiCatalogo) = temp;
	}
}

void rimuoviNonDisponibili(t_catalogo **listaCatalogo){
	t_catalogo *temp = *listaCatalogo;
	t_catalogo *l = *listaCatalogo;
	if(!temp)//Lista vuota?!?
		return;
	while(temp != NULL){
		if(temp->disponibilita == 0){//Devo eliminare
			if(temp->next != NULL)
				l->next = temp->next;
			else
				l->next = NULL;
			free(temp);
		}
		l = temp;
		temp = temp->next;
	}
}
void riduciPrezzo(t_catalogo **listaCatalogo, int annoProduzione){
	t_catalogo *temp = *listaCatalogo;
	while(temp != NULL){
		if(temp->annoProduzione < annoProduzione)
			temp->prezzo = (temp->prezzo /2);
		temp = temp->next;
	}
}
void selezionaProdotti(t_catalogo **listaCatalogo, t_catalogo **selezionatiCatalogo){
	char sceltaa;
	printf("E' possibile selezionare i prodotti attraverso i loro campi.\n");
	printf("Selezionare il campo con cui effettuare la selezione:\n");
	printf("C per Categoria\n");
	printf("A per Anno di produzione\n");
	printf("D per Disponibilità\n");
	scanf(" %c", &sceltaa);
	aggiungiASelezione(listaCatalogo, selezionatiCatalogo, sceltaa);
}

void visualizzaDettagli(t_catalogo *selezionatiCatalogo){
	t_catalogo *temp = selezionatiCatalogo;
	if(temp == NULL){
		fprintf(stderr, "Nessun prodotto selezionato!\nSelezionare il prodotto usando la scelta n. 3 nel menu principale\n");
		return;
	}
	while(temp != NULL){
		printf("------------------------\n");
		printf("Categoria: %s\n", temp->categorie);
		printf("Anno di produzione: %d\n", temp->annoProduzione);
		printf("Destinatario : %s\n", temp->destinatario);
		printf("Disponibilita': %d\n", temp->disponibilita);
		printf("Prezzo: %.2f\n", temp->prezzo);
		temp = temp->next;
	}
	printf("------------------------\n");
}
void salvaSuFile(t_catalogo *listaCatalogo){
	FILE *fpo = fopen("catalogo.txt", "w");
	t_catalogo *temp = listaCatalogo;
	while(temp!=NULL){
		fprintf(fpo, "%s\n", temp->categorie);
		fprintf(fpo, "%s\n", temp->destinatario);
		fprintf(fpo, "%d\n", temp->annoProduzione);
		fprintf(fpo, "%d\n", temp->disponibilita);
		fprintf(fpo, "%.2f\n", temp->prezzo);
		temp = temp->next;
	}
	if(fpo == NULL)//problema apertura
		return;

	fclose(fpo);
}

void caricaProdotti(t_catalogo **listaCatalogo){
	t_catalogo *temp = malloc(sizeof(t_catalogo));
	if(!temp)
		return;//prob malloc
	FILE *fpi = fopen("catalogo.txt", "r");
	if(fpi == NULL)//problema apertura
		return;
	while(fscanf(fpi, "%s", temp->categorie) == 1){
		fscanf(fpi, "%s", temp->destinatario);
		fscanf(fpi, "%d", &temp->annoProduzione);
		fscanf(fpi, "%d", &temp->disponibilita);
		fscanf(fpi, "%f", &temp->prezzo);
		printf("%s\n%s\n%d", temp->categorie, temp->destinatario, temp->annoProduzione);
		aggiungiElementoACatalogo(listaCatalogo, temp->categorie, temp->destinatario, temp->annoProduzione, temp->disponibilita, temp->prezzo);
	}
	fclose(fpi);
}

