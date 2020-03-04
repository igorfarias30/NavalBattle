//#pragma warning(surpress: 4101)
/* Trabalho de Programação
*Diaulas Marcondes - 360091
*Igor Farias- 352202
*Davi Varela - 354048
*/

#include "./batalhaNaval.h"

int main(int argn, char *argv[]){

	Node *jogo;
	int placarHumano, placarComputer, Resposta = 1;
	
	placarHumano = 0;
	placarComputer = 0;
	jogo = NULL;
	printf ("oi1\n\n");

	
	while (Resposta == 1){
		iniciar(&jogo, &placarHumano, &placarComputer);
		printf ("\n\n\nPLACAR\n");
		printf ("Computador = %d\n", placarComputer);
		printf ("Humano     = %d\n", placarHumano);
		Resposta = 0;
		while(Resposta != 1 && Resposta != 2){
			printf ("\n Deseja continuar a jogar ? 1- SIM, 2 - Nao\n\n");
			scanf ("%d",&Resposta);
		}
		
    		
	}
	
	system("clear");
	printf ("\t--------PLACAR FINAL--------\n\n");
	printf ("\tComputador = %d\n", placarComputer);
	printf ("\tHumano     = %d\n", placarHumano);
	delay(1);
	printf("\n\n");
	creditos();
	return EXIT_SUCCESS;
}
