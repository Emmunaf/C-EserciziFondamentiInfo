#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct users
{
	char mail[30], password[25];
	long int id;
	struct users *next;
} t_users;

typedef struct message
{
	char title[25], content[181];
	long int senderId, reciperId;
	struct message *next;
} t_message;

void menu();
int addUser(t_users ** userList, char *mail, char *password);
void showUsers(t_users * userList);//
void sendMessage(t_message **messageList, char *title, char *content, long int senderId, long int reciperId);
long int userLogin(t_users * userList, char *l_mail, char *l_password);
long int existUser(t_users * userList, char *mail);
void readMessages(t_message *messageList, t_users *userList, long int userId);
void readMessage(t_message *messageList, t_users *userList, long int userId, int scelta);
char *findUsername(t_users * userList, long int id);

int main(int argc, char const **argv){
	menu();
	return 0;
}

void menu(){
	t_users *userList = NULL;
	t_message *messageList = NULL;
	int scelta=0;
	while(scelta != -1){
		printf("Benvenuto nel simulatore posta elettronica.\n");
		printf("Selezionare cosa si desidera fare:\n(1) Aggiungere un nuovo utente\n(2) Login\n");
		printf("(-1) Per uscire.\n");
		scanf("%d", &scelta);
		char mail[30], password[25];
		char l_mail[30], l_password[25];
		char title[25], content[181];
		long int l_userId, userId;
		switch (scelta){
			case (1):
				printf("\fLa mail creata sarà del tipo [nomeutente]@[dom].it\n");
				printf("Inserisci email (max 29 caratteri):\n");
				scanf("%24s", mail);
				printf("Inserisci password (max 24 caratteri):\n");
				scanf("%24s", password);
				if(addUser(&userList, mail, password))
					printf("Utente registrato correttamente!\n\n");
				else
					fprintf(stderr, "C'è stato un problema nella creazione del nuovo utente, riprova più tardi.\n");
			break;
			case (2):
				printf("\f(1) Invio messaggi\n");
				printf("(2) Lettura messaggi\n");
				scanf("%d", &scelta);
				printf("Per la seguente operazione è necessario autenticarsi:\n");
				printf("Inserire l'e-mail nel formato [username]@[dom].it:\n");
				scanf("%s", l_mail);
				printf("Inserire la password:\n");
				scanf("%24s", l_password);
				l_userId = userLogin(userList, l_mail, l_password);
				if(l_userId >= 0)
					printf("Login effettuato con successo...\n\f");
				else{
					fprintf(stderr, "Problemi di autenticazione!\n\f");
					break;
				}
				/*
					char title[25], content[181];
						long int senderId, reciperId;
						struct message *next;
					} t_message;
				*/
				if(scelta == 1){//Invio messaggio;
					printf("Inserire l'indirizzo del destinatario nel formato [username]@[dom].it:\n");
					scanf("%s", mail);
					userId = existUser(userList, mail);
					if(userId < 0){
						fprintf(stderr, "L'utente non esiste\n\f");//
						break;
					}
					printf("Inserire il titolo del messaggio:\n");
					scanf("%24s", title);
					printf("Inserire il contenuto del messaggio:\n");
					scanf("%180s", content);
					sendMessage(&messageList, title, content, l_userId, userId);
					printf("Messaggio inviato!\n");
				}
				else if(scelta == 2){
					printf("Benvenuto nel pannello per leggere le tue e-mail\n");
					readMessages(messageList, userList, l_userId);
				}
				else{
					fprintf(stderr, "\nSelezionare una scelta corretta.\n");
				}
			break;
			default:
				exit(0);
			break;
		}
	}

}
//Ritorna 1 se ok, 0 altrimenti
int addUser(t_users ** userList, char *mail, char *password){
	t_users *temp = malloc(sizeof(t_users));
	if(!temp)//malloc ha restituito null
		return 0;
	strcpy(temp->mail, mail);
	strcpy(temp->password, password);

	if(!(*userList)){//Lista vuota!
		printf("Lista vuota");
		temp->id = 0;
		temp->next = NULL;
		(*userList) = temp;

	}
	else {
		temp->id = ((*userList)->id)+1;
		temp->next = (*userList);
		(*userList) = temp;
	}
	return 1;
}
/*
void showUsers(t_users * userList){
	t_users * temp = userList;
	while(temp!=NULL){
		printf("Mail: %s\nId: %ld\n", temp->mail, temp->id);
	temp = temp->next;
	}
}*/

void sendMessage(t_message **messageList, char *title, char *content, long int senderId, long int reciperId){
	t_message * temp = malloc(sizeof(t_message));
	if(!temp)
		return;//Malloc fallito
	strcpy(temp->title, title);
	strcpy(temp->content, content);
	temp->senderId = senderId;
	temp->reciperId = reciperId;
	if(!(*messageList)) {//lista vuota
		temp->next = NULL;
		(*messageList) = temp;
	}
	else{
		temp->next = (*messageList);
		(*messageList) = temp;
	}
}

long int userLogin(t_users * userList, char *l_mail, char *l_password){
	t_users *temp = userList;
	while(temp!=NULL){
		if((strcmp(temp->mail, l_mail) == 0) && (strcmp(temp->password, l_password) == 0)){
			return temp->id;
		}
		temp = temp->next;
	}
	return -1;
}

long int existUser(t_users * userList, char *mail){
	t_users *temp = userList;
	while(temp!=NULL){
		if((strcmp(temp->mail, mail) == 0)){
			return temp->id;
		}
		temp = temp->next;
	}
	return -1;
}

char *findUsername(t_users * userList, long int id){
	t_users *temp = userList;
	while(temp!=NULL){
		if(temp->id == id){
			return temp->mail;
		}
		temp = temp->next;
	}
}

void readMessages(t_message *messageList, t_users *userList, long int userId){
	t_message *temp = messageList;
	char mail[30];
	int i = 1, scelta;
	while(temp!=NULL){
		if(temp->reciperId == userId){
			strcpy(mail, findUsername(userList, temp->senderId));
			printf("(%d) Titolo: %s\nMittente: %s\n", i, temp->title, mail);
			i++;
		}
		temp = temp->next;
	}
	printf("Quale mail vuoi aprire?\n[Immetti un numero negativo per uscire]\n");
	scanf("%d", &scelta);
	if(scelta < 0)
		return;
	else{
		readMessage(messageList, userList, userId, scelta);
	}
}

void readMessage(t_message *messageList, t_users *userList, long int userId, int scelta){
	t_message *temp = messageList;
	t_message * templ = messageList;
	char mail[30];
	int i = 1;
	while(temp!=NULL){
		if(temp->reciperId == userId){
			i++;
		}
		if(scelta == (i-1)){
			strcpy(mail, findUsername(userList, temp->senderId));
			printf("Titolo: %s\nMittente: %s\nContenuto: %s\n\n\n", temp->title, mail, temp->content);
			templ->next = temp->next;
			templ = temp;
			temp = temp->next;
			free(temp);
			return;
		}
	}
}