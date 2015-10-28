#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct atleta{// Struttura per caricare file atleti.txt in memoria
	int nPettorale;
	char siglaNazione[4], cognome[25], nome[25];
	struct atleta *next;
} t_atleta;

typedef struct salto {// Struttura per caricare file salti.txt in memoria
	int nPettorale, lunghezza;
	char validita;
	struct salto *next;
} t_salto;

typedef struct s_classifica {// Struttura per la classifica
	int nPettorale;
	char siglaNazione[4], cognome[25], nome[25];
	int lunghezza;
	struct s_classifica *next;
} t_classifica;

// Prototipi funzioni
void menu();
void aggiungiAtleta(t_atleta **atleti, int nPettorale, char *siglaNazione, char *cognome, char *nome);
int caricaAtletiDaFile(t_atleta **atleti);
void mostraAtleti(t_atleta *atleti);
void caricaSaltiDaFile(t_salto **salti, int nAtleti);
void mostraSalti(t_salto *salti);
void aggiungiInClassifica(t_classifica **classifica, int nPettorale, char *siglaNazione, char *cognome, char *nome, int salto);
void mostraClassifica(t_classifica *classifica);
void mostraTop3(t_classifica *classifica);
void elaboraDati(t_classifica **classifica, t_atleta **atleti, t_salto **salti, int nAtleti);
void menu(t_atleta **atleti, t_salto **salti, t_classifica **classifica);
void caricaAtletiManualmente(t_atleta **atleti, int nAtleti);
void caricaSaltiManualmente(t_salto **salti, int nAtleti);
