#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//rewind(infile);
typedef struct articolo
{
	char tipologia[11], marca[11];
	float prezzo;
	int numVenduti;
}t_articolo;

t_articolo* articoli(FILE* listino, FILE* venduti, char* tipologia, int* len);

int main(int argc, char **argv){
	int *len = malloc(sizeof(int));
	char tipologia[11];
	FILE *listino = fopen("listino.txt", "r");
	FILE *venduti = fopen("venduti.txt", "r");
	if(!listino || !venduti){
		fprintf(stderr, "Impossibile aprire i file\n");
		exit(1);
	}
	printf("Inserire la tipologia di interesse:\n");
	scanf("%10s", tipologia);
	t_articolo *listaArticoli = articoli(listino, venduti, tipologia, len);
	for(int i = 0; i < (*len); i++){
		printf("-----------------\n");
		printf("Tipologia: %s\nMarca: %s\nPrezzo: %f\nQ.ta venduta: %d\n", listaArticoli[i].tipologia, listaArticoli[i].marca, listaArticoli[i].prezzo, listaArticoli[i].numVenduti);
	}
	printf("-----------------\n");
	return 0;
}

t_articolo* articoli(FILE* listino, FILE* venduti, char* tipologia, int* len){
	char ttipologia[11], tmarca[11];
	float tprezzo;
	*len = 0;
	while((fscanf(listino, "%s %s %f", ttipologia, tmarca, &tprezzo) == 3)){
		if(strcmp(ttipologia, tipologia) == 0){
			++(*len);
		}
	}
	t_articolo *listaArticoli = malloc((*len)*sizeof(t_articolo));
	rewind(listino);
	int count = 0;
	while((fscanf(listino, "%s %s %f", ttipologia, tmarca, &tprezzo) == 3)){
		if(strcmp(ttipologia, tipologia) == 0){
			strcpy(listaArticoli[count].tipologia, tipologia);
			strcpy(listaArticoli[count].marca, tmarca);
			listaArticoli[count].prezzo = tprezzo;
			listaArticoli[count].numVenduti = 0;
			++count;
		}
	}
	while(fscanf(venduti, "%s %s", ttipologia, tmarca) == 2){
		if(strcmp(ttipologia, tipologia) == 0){
			int count = 0;
			while((strcmp(listaArticoli[count].marca, tmarca) != 0) && count < (*len))
				++count;
			if(count != (*len)){
				++listaArticoli[count].numVenduti;
			}
		}
	}
	return listaArticoli;
}



