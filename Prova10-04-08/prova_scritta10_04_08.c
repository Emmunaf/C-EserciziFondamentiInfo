#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Emanuele Munafò

Precisione float approssimata come I/O a 4 cifre!!!


*/

void scriviSuFile(FILE *fpo, float *vettoreA, float *vettoreB, float *vettoreAdd, float *vettoreSot, int dim);
void menu(float *vettoreA, float *vettoreB, float *vettoreAdd, float *vettoreSot, int dim);
void calcolaVettori(float *vettoreAdd, float *vettoreSot, float *vettoreA, float *vettoreB, int dim);
void inserisciValori(float *vettore, int dim);
void visualizzaMedie(float *vettoreA, float *vettoreB, float *vettoreAdd, float *vettoreSot, int dim);
void visualizzaInfMedie(float *vettoreA, float *vettoreB, float *vettoreAdd, float *vettoreSot, int dim);
void visualizzaInfMedia(float *vettore, int dim);
void calcolaVarianze(float *vettoreA, float *vettoreB, float *vettoreAdd, float *vettoreSot, int dim);
void calcolaVarianza(float *vettore, int dim);
void visualizzaVarianze(float *vettoreA, float *vettoreB, float *vettoreAdd, float *vettoreSot, int dim);

int main(int argc, char const **argv){
	int dim;//Numero COMPONENTI del vettore, non dimensione dell'array!!
	float *vettoreA = NULL, *vettoreB = NULL, *vettoreSot = NULL, *vettoreAdd = NULL;
	printf("Inserisci la dimensione dei due vettori:\n");
	scanf("%d", &dim);

	vettoreA = malloc((dim+2)*sizeof(float));
	vettoreB = malloc((dim+2)*sizeof(float));
	vettoreAdd = malloc((dim+2)*sizeof(float));
	vettoreSot = malloc((dim+2)*sizeof(float));
	if((!vettoreA) || (!vettoreB) || (!vettoreAdd) || (!vettoreSot))
		exit(1);//Problema nell'allocazione di memoria
	printf("Inserimento valori delle componenti del vettore A\n");
	inserisciValori(vettoreA, dim);
	printf("Inserimento valori delle componenti del vettore B\n");
	inserisciValori(vettoreB, dim);
	calcolaVettori(vettoreAdd, vettoreSot, vettoreA, vettoreB, dim);

	menu(vettoreA, vettoreB, vettoreAdd, vettoreSot, dim);
	return 0;
}

void calcolaVettori(float *vettoreAdd, float *vettoreSot, float *vettoreA, float *vettoreB, int dim){
	float tempMediaAdd = 0, tempMediaSot = 0;
	for (int i = 0; i < dim; ++i)
	{
		vettoreAdd[i] = vettoreA[i]+vettoreB[i];
		vettoreSot[i] = vettoreA[i]-vettoreB[i];
		tempMediaAdd += vettoreAdd[i];
		tempMediaSot += vettoreSot[i];
	}
	vettoreAdd[dim] = (tempMediaAdd/dim);
	vettoreSot[dim] = (tempMediaSot/dim);
}

void inserisciValori(float *vettore, int dim){
	float tempMedia = 0;
	for (int i = 0; i < dim; ++i)//Inserimento e memorizzazioni componenti Vettore A
	{
		printf("Inserisci la componente n. %d del vettore:\n", i);
		scanf("%f", &vettore[i]);
		tempMedia += vettore[i];//Calcolo somma
	}
	vettore[dim] = (tempMedia/dim);//Calcolo media  e memorizzo nell'elemento dim-iesimo
}

void menu(float *vettoreA, float *vettoreB, float *vettoreAdd, float *vettoreSot, int dim){
	while(1){
		int scelta;
		printf("  ---------- Menu --------\n");
		printf("Cosa vuoi fare? Seleziona:\n");
		printf("1. Per calcolo e visualizzazione medie\n");
		printf("2. Per calcolo e visualizzazione varianza\n");
		printf("3. Salvataggio su file di testo desiderato\n");
		printf("4. Visualizzazione elementi inferiori alla media\n");
		printf("Altro per uscire\n");
		scanf("%d", &scelta);
		switch(scelta){
			case 1:
				visualizzaMedie(vettoreA, vettoreB, vettoreAdd, vettoreSot, dim);
				break;
			case 2:
				calcolaVarianze(vettoreA, vettoreB, vettoreAdd, vettoreSot, dim);
				visualizzaVarianze(vettoreA, vettoreB, vettoreAdd, vettoreSot, dim);
				break;
			case 3:
				printf("Inserire un nome per il file di output (max 25 caratteri)\n");
				char nomeOutput[30];
				scanf("%25s", nomeOutput);
				strcat(nomeOutput, ".txt");
				FILE *fpo = fopen(nomeOutput, "w");
				if(!fpo){
					fprintf(stderr, "Problemi nell'apertura del file in scrittura\n");
					break;
				}
				scriviSuFile(fpo, vettoreA, vettoreB, vettoreAdd, vettoreSot, dim);
				fclose(fpo);
				break;
			case 4:
				visualizzaInfMedie(vettoreA, vettoreB, vettoreAdd, vettoreSot, dim);
				break;
			default:
				exit(0);
				break;
		}
	}
}

void visualizzaMedie(float *vettoreA, float *vettoreB, float *vettoreAdd, float *vettoreSot, int dim){
	printf("\n\nVisualizzazione medie:\n");
	printf("Vettore A: %.4f\n", vettoreA[dim]);
	printf("Vettore B: %.4f\n", vettoreB[dim]);
	printf("Vettore A+B: %.4f\n", vettoreAdd[dim]);
	printf("Vettore A-B: %.4f\n", vettoreSot[dim]);
}

void visualizzaInfMedie(float *vettoreA, float *vettoreB, float *vettoreAdd, float *vettoreSot, int dim){
	printf("\n\n+----------------------------------------------------+\n");
	printf("Componenti inferiori alla media (%.4f) del vettore A:\n", vettoreA[dim]);
	visualizzaInfMedia(vettoreA, dim);
	printf("+----------------------------------------------------+\n");
	printf("Componenti inferiori alla media (%.4f) del vettore B:\n", vettoreB[dim]);
	visualizzaInfMedia(vettoreB, dim);
	printf("+----------------------------------------------------+\n");
	printf("Componenti inferiori alla media (%.4f) del vettore A+B:\n", vettoreAdd[dim]);
	visualizzaInfMedia(vettoreAdd, dim);
	printf("+----------------------------------------------------+\n");
	printf("Componenti inferiori alla media (%.4f) del vettore A-B:\n", vettoreSot[dim]);
	visualizzaInfMedia(vettoreSot, dim);
	printf("+----------------------------------------------------+\n");
}
void visualizzaInfMedia(float *vettore, int dim){
	int j = 0;
	for (int i = 0; i < dim; ++i)
	{
		if(vettore[i] < vettore[dim]){
			++j;
			printf("Componente n. %d = %.4f\n", i, vettore[i]);
		}
	}
	if(j==0)
		printf("Nessuna componente minore della media, tutti le componenti sono uguali alla media\n");
}

void calcolaVarianze(float *vettoreA, float *vettoreB, float *vettoreAdd, float *vettoreSot, int dim){
	calcolaVarianza(vettoreA, dim);
	calcolaVarianza(vettoreB, dim);
	calcolaVarianza(vettoreAdd, dim);
	calcolaVarianza(vettoreSot, dim);
}


void calcolaVarianza(float *vettore, int dim){
	float tempVar = 0;
	for (int i = 0; i < dim; ++i)
	{
		tempVar += (vettore[i]-vettore[dim])*(vettore[i]-vettore[dim]);
	}
	vettore[dim+1] = (tempVar/dim);
}

void visualizzaVarianze(float *vettoreA, float *vettoreB, float *vettoreAdd, float *vettoreSot, int dim){
	printf("\n\nVisualizzazione varianze:\n");
	printf("Vettore A: %.4f\n", vettoreA[dim+1]);
	printf("Vettore B: %.4f\n", vettoreB[dim+1]);
	printf("Vettore A+B: %.4f\n", vettoreAdd[dim+1]);
	printf("Vettore A-B: %.4f\n", vettoreSot[dim+1]);
}
void scriviSuFile(FILE *fpo, float *vettoreA, float *vettoreB, float *vettoreAdd, float *vettoreSot, int dim){
	for (int i = 0; i <= dim+1; ++i)
	{
		fprintf(fpo, "%.4f\n", vettoreA[i]);
	}
	for (int i = 0; i <= dim+1; ++i)
	{
		fprintf(fpo, "%.4f\n", vettoreB[i]);
	}
	for (int i = 0; i <= dim+1; ++i)
	{
		fprintf(fpo, "%.4f\n", vettoreAdd[i]);
	}
	for (int i = 0; i <= dim+1; ++i)
	{
		fprintf(fpo, "%.4f\n", vettoreSot[i]);
	}
	printf("Il file è stato scritto correttamente.\nTuttavia se la varianza non era stata ancora calcolata sarà 0.\n");
}

