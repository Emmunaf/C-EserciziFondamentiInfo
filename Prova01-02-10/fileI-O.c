/*
@input : dStart, dEnd
@output medie.txt

*/

/*Il file di input ha 366 righe, 
File input: ricavi.txt con il seguente formato


noggettivenduti guadagno

*/
/*
File output: medie.txt con il seguente formato

giornoinizio fine statistiche
*/


#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
	int dStart = 0, dEnd = 0;
	float sum[2] = {0,0};// [0] = nOggettiVenduti, [1] = guadagnoTotGiorno
	int range = 0;
	int temp1,temp2;
	//Chiedo i dati di input e verifico soddisfino le condizioni di controllo eccezioni
	printf("Inserire il primo estremo dell'intervallo\nIntervallo consentito: [1,365]: ");
	while((scanf("%d", &dStart)) && !((dStart >0) && (dStart <366)));
	printf("Inserire il secondo estremo dell'intervallo\nIntervallo consentito: [2,366]: ");
	while((scanf("%d", &dEnd)) && !((dEnd >1) && (dEnd <367)));
	printf("L'intervallo inserito è: [%d - %d]\n", dStart, dEnd);
	//Apro file di input
	FILE* fpi = fopen("ricavi.txt", "r");
	if(fpi == NULL) //Controllo non ci siano problemi 
		exit(1);
	else{
		for(int i=1;i<dStart;++i){
			fscanf(fpi, "%d %d", &temp1, &temp2);
		}
		for(int j=dStart;j<=dEnd;++j){
			fscanf(fpi, "%d %d", &temp1, &temp2);
			if(temp1 != -1){
				++range;
				sum[0] += temp1;
				sum[1] += temp2;
			}
		}
		printf("La media giornaliera è:\nOggetti Venduti: %f\nGuadagno giornaliero:%f\nI giorni lavorativi %d\n", (sum[0]/range), (sum[1]/range), range);
		fclose(fpi);
		//Salvo l'output in apposito file
		FILE* fpo = fopen("medie.txt", "a+");
		if(fpo == NULL)
			exit(1);
		else{
			fprintf(fpo, "%d %d %f %f %d\n", dStart, dEnd, (sum[0]/range), (sum[1]/range), range);
			fclose(fpo);
		}

	}
	return 0;
}