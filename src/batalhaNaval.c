/* Trabalho de Programação
* Diaulas - 360091
*Igor - 352202
* Davi Varela - 354048
*/

#include "./batalhaNaval.h"

// Função criarNo, serve para quando iniciar a malha, chamarmos ela para fazer sua estrutura, ela retorna um ponteiro para nó
Node *criarNo()	{
	Node *Novo;
	Novo = (Node*)malloc(sizeof(Node));

	//Ponteiros
	Novo->cima = NULL;
	Novo->baixo= NULL;
	Novo->direito = NULL;
	Novo->esquerdo = NULL;

	//Espaços
	Novo->espacoHumano = 'O';
	Novo->espacoComputer = 'O';
	//
	Novo->showHumano = 0;
	Novo->showComputer = 0;
	Novo->identificadorHumano = -1;
	Novo->identificadorComputer = -1;
	Novo->atingido = 0;
	return Novo;
}

// A função buscar No, ela Busca uma celula da malha, na linha x e coluna y. A função retorna um ponteiro para a célula encontrada
Node *buscarNo(Node **jogo, int *posLinha, int *posColuna){

	int x, y;
	Node *pontAux;

	pontAux = *jogo;
	x = 1; y = 1;

	while( (pontAux != NULL) && (*posLinha != x) ){
			pontAux = pontAux->baixo;
			x++;
	}
	while( (pontAux != NULL) && (*posColuna != y) ){
			pontAux = pontAux->direito;
			y++;
	}

	return pontAux;
}

// Essa função serve, para que casa um dos dois jogadores acerte uma jangada do seu oponente, ele perde um submarino. Então percorremos a malha para irmos buscar uma célula que tenha um submarino, logo após, "destruímos" ele.
Node *buscarSubmarino(Node **jogo, int jogador){
	
	Node *pontAux1, *pontAux2;
	pontAux1 = *jogo;
	pontAux2 = pontAux1;
	
	while(pontAux1 != NULL){
		while(pontAux2 != NULL){
			if(jogador == HUMANO){
				if(pontAux2->espacoHumano == '@' && pontAux2->showHumano == 0){
					pontAux2->showHumano = 1;
					return pontAux2;
				}		
			}
			if(jogador == COMPUTADOR){
				if(pontAux2->espacoComputer == '@' && pontAux2->showComputer == 0){
					pontAux2->showComputer = 1;
					return pontAux2;
				}
					
			}
			pontAux2 = pontAux2->direito;
		}
		pontAux1 = pontAux1->baixo;
		pontAux2 = pontAux1;
	}
}

// Função que libera a malha na memória
void liberarMalha(Node **jogo){
	Node *pontAux1, *pontAux3;
	
	pontAux1 = *jogo;
	//pontAux2 = pontAux1;
	pontAux3 = pontAux1;
	
	while(pontAux1 != NULL){
		while(pontAux3 != NULL){
			Node *pontAux2;
			
			pontAux2 = pontAux3;
			pontAux3 = pontAux3->direito;
			free(pontAux2);	
		}
		
		pontAux1 = pontAux1->baixo;
		pontAux3 = pontAux1;
	}
	
}
// funcão para printar a Malha do jogo
void printMalha(Node **jogo, int NavioComputer [], int NavioHumano []){
	int i = 1;
	Node *pontAux1, *pontAux2, *pontAux3;

	pontAux1 = *jogo;
	pontAux2 = pontAux1;
	pontAux3 = pontAux1;

	//for (int j=0;j<9;j++)
	//	printf ("AAA %d\n\n", NavioComputer[j]);
	printf("\t  A B C D E F G H I J \t      A B C D E F G H I J\n");
	printf(" \t+---------------------+--------------------------+ \n");
	while (pontAux1 != NULL){

		printf(" %d \t|", i);

		while(pontAux2 != NULL){

			if(pontAux2->espacoHumano == 'O'){
				if (pontAux2->showHumano == 0)
					printf("  ");
				else
					printf (" O");
			}
			else{
				if (pontAux2->showHumano == 0)
					printf(" %c", pontAux2->espacoHumano);
				else
					printf (" *");
			}
				//printf("\t");

			pontAux2 = pontAux2->direito ;
		}

		//------------Condição para identar o mapa
		if(i != 10)
			printf(" +  %d  |", i);
		else
			printf(" +  %d |", i);
		// -----------------------------------

		while(pontAux3 != NULL){

			if(pontAux3->showComputer == 0)
				printf("  ");
			else{
				if (pontAux3->identificadorComputer != -1){
					//printf (" = %d\n", NavioComputer[pontAux3->identificadorComputer]);
					if (NavioComputer[pontAux3->identificadorComputer] == 0)
						printf(" %c", pontAux3->espacoComputer);
					else
						printf (" *");
				}
				else
					printf (" O");
			}
			pontAux3 = pontAux3->direito ;
		}

		printf("|");
		printf("\n");
		pontAux1 = pontAux1->baixo;
		pontAux2 = pontAux1;
		pontAux3 = pontAux1;
		i++;
	}
	printf(" \t+---------------------+--------------------------+ \n");
}

// Esta função foi feita para testar o tipo de embarcação na malha
void print_identificador (Node **Jogo)
{
	Node *Aux1, *Aux2;
	Aux1 = *Jogo;
	Aux2 = *Jogo;

	while ( Aux1 != NULL){
		while (Aux2 != NULL){
			if (Aux2->identificadorComputer == 0)
				printf ("   ");
			else
				printf ("%d   ", Aux2->identificadorComputer);
			Aux2 = Aux2->direito;
		}
		printf ("\n");
		Aux1 = Aux1->baixo;
		Aux2 = Aux1;
	}
}

// Função somente para teste, foi mais usada para printar os navios do COMPUTADOR, para que possamos analisar se está sendo acertado e destruido
void printNavio(Node **Jogo)
{
	Node *Aux1, *Aux2;
	Aux1 = *Jogo;
	Aux2 = *Jogo;

	int i = 1;

	printf("\t  A B C D E F G H I J \n" );
	printf(" \t+---------------------+ \n");
	while ( Aux1 != NULL){
		printf(" %d \t|", i);
		while (Aux2 != NULL){
			if (Aux2->espacoComputer == 'O')
				printf ("  ");
			else
				printf (" %c", Aux2->espacoComputer);
			Aux2 = Aux2->direito;
		}
		printf (" |\n");
		Aux1 = Aux1->baixo;
		Aux2 = Aux1;
		i++;
	}
	printf(" \t+---------------------+\n");
}



int NavioDestruido (Node **jogo, Node *pont, Coordenada *pilha, int *topo, int NavioHumano[],int NavioComputer[], int jogador){
    	int i;
	Node *sub;
	
	//printf ("jogadooooooooooooooooooor == %d\n\n\n",NavioComputer[pont->identificadorComputer]);
	if (jogador == COMPUTADOR){
		if (NavioHumano[pont->identificadorHumano] == 0){
			if (pont->identificadorHumano == 0){
		    		for (i=0;i<5;i++){
		        		pilha[*topo].linha = 0;
		        		pilha[*topo].coluna = 0;
		        		*topo = *topo - 1;
		    		}
		    		printf ("\t UM PORTA-AVIOES DO HUMANO FOI DESTRUIDO ! \n");
			}
			else{
		    		if (pont->identificadorHumano == 1 || pont->identificadorHumano == 2){
		        		for (i=0; i<3;i++){
		            			pilha[*topo].linha = 0;
		            			pilha[*topo].coluna = 0;
		            			*topo = *topo - 1;
		        		}
		        	printf ("\t UM DESTROYER DO HUMANO FOI DESTRUIDO ! \n");
		    	}
		    	else{
		        	if (pont->identificadorHumano == 3 || pont->identificadorHumano == 4 || pont->identificadorHumano == 5){
		            		for (i=0; i<2;i++){
		                		pilha[*topo].linha = 0;
		                		pilha[*topo].coluna = 0;
		                		*topo = *topo - 1;
		            		}
		                printf ("\t UMA FRAGATA DO HUMANO FOI DESTRUIDO ! \n");

		        	}
		        	else {
		            		if (pont->identificadorHumano == 6 || pont->identificadorHumano == 7){
		          	  		pilha[*topo].linha = 0;
		         	   		pilha[*topo].coluna = 0;
		         	   		*topo = *topo - 1;
		          	  		if (pont->identificadorHumano == 6 || pont->identificadorHumano == 7)
		            	    			printf ("\t UM SUBMARINO DO HUMANO FOI DESTRUIDO ! \n");
		            		}
		            		else{
		            			printf ("\t UMA JANGADA DO HUMANO FOI DESTRUIDO ! \n");
		                			if(NavioComputer[6] == 1 || NavioComputer[7] ==1){
		                				// PROCURAR SUBMARINO DO COMPUTADOR
		                				sub = buscarSubmarino(jogo, COMPUTADOR);
		                				NavioComputer[sub->identificadorComputer] = NavioComputer[sub->identificadorComputer] - 1;
		                				printf ("\t COMPUTADOR PERDEU UM SUBMARINO ! \n");
		                				printf ("\t COMPUTADOR PERDEU A VEZ ! \n");
		                				return 1;
		                			}
		                			else
		                				printf ("\t COMPUTADOR NAO TEM MAIS SUBMARINOS PARA PERDER!\n");
		           
		                			return 1;
		            		}


		        	}
		    	}
		}
	    }
	}
	else{
		
		if (NavioComputer[pont->identificadorComputer] == 0){
			if (pont->identificadorComputer == 0){
		    		printf ("\t UM PORTA-AVIOES DO COMPUTADOR FOI DESTRUIDO ! \n");
			}
			else{
		    		if (pont->identificadorComputer == 1 || pont->identificadorComputer == 2){
		        		printf ("\t UM DESTROYER DO COMPUTADOR FOI DESTRUIDO ! \n");
		    		}
		    		else{
		        		if (pont->identificadorComputer == 3 || pont->identificadorComputer == 4 || pont->identificadorComputer == 5){
		                		printf ("\t UMA FRAGATA DO COMPUTADOR FOI DESTRUIDO ! \n");

		        		}
		        		else {
		            			if (pont->identificadorComputer == 6 || pont->identificadorComputer == 7)
		                			printf ("\t UM SUBMARINO DO COMPUTADOR FOI DESTRUIDO ! \n");
		            			else{
		                			printf ("\t UMA JANGADA DO COMPUTADOR FOI DESTRUIDO ! \n");
		                				if(NavioComputer[6] == 1 || NavioComputer[7] == 1){
		                					// PROCURAR SUBMARINO DO COMPUTADOR
		                					sub = buscarSubmarino(jogo, HUMANO);
		                					printf ("\t HUMANO PERDEU UM SUBMARINO !\n");
		                					printf ("\t HUMANO PERDEU A VEZ !\n");
		                					return 1;
		                				}
		                				else
		                					printf ("HUMANO NAO TEM MAIS SUBMARINOS PARA PERDER ! \n"); 
		                				return 1;
		            			}
		        		}
		    		}
			}
	    	}
	}
	
    	return 0;
}

//Esta função, gerencia a jogada do humano
//                             1 a 9          A a J
int jogadaHumano(Node **jogo, int *Linha, int *Coluna, int NavioHumano[], int NavioComputer[]){
	
	Node *celula;
	Node *sub;
	Coordenada pilha [2];
	int topo,i;
	
	//printf("Teste....L: %d C: %d \n", *posLinha, *posColuna);
	celula = buscarNo(jogo, Linha, Coluna);
	if (celula->showComputer == 0){
		// Se ele entrou aqui, ele não fez ainda essa jogada 
		celula->showComputer = 1; //mudo o show computer para 1, pois para quando printar a malha, inserir um *
		if(celula->espacoComputer != 'O'){
			system("clear");
			printf("\n \t VOCÊ ATINGIU UMA EMBARCACÃO ! \n\n");
			NavioComputer[celula->identificadorComputer] = NavioComputer[celula->identificadorComputer] - 1;
			printMalha(jogo, NavioComputer, NavioHumano);
			
			return NavioDestruido (jogo, celula, pilha, &topo, NavioHumano, NavioComputer, HUMANO);  // retorno 0, para continuar o laçõ na função executar, desse modo ele joga novamente
		
		}else
			return 1;
	}
	else{
		printf("\t Jogada já realizada ! \n");
		return 0;
	} 
	
	//printf("Car do Computador: %c \n", celula->espacoComputer);
}

// Esta função foi proposta pelo Diaulas, ele arranjou um jeito de que o computador fosse sortear sua jogada sabiamente
Node *JogadaInteligenteComputer (Node **jogo, Coordenada *pilha, int *topo, int NavioHumano[], int *posColuna, int *posLinha){

    	int direcao,cont;
   	Node *pontAux1;

    	pontAux1 = *jogo;
    	cont = *topo;
                // SE ELE ACERTOU UMA EMBARCACAO NA PRIMEIRA LINHA
	while (cont >= 0){
    		if (pilha[cont].coluna == 1 ){
        		if (pilha[cont].linha == 1){

                    		direcao = rand () % 2 + 1; // DIRECAO = 1 DIREITA, = 2 BAIXO
                    		if (direcao == 1){ // ATIRAR NA DIREITA
                        		*posColuna = pilha[cont].coluna + 1;
                        		*posLinha = pilha[cont].linha;
                        	}
                        	else{
                        		*posColuna = pilha[cont].coluna;
                            		*posLinha = pilha[cont].linha + 1;
                        	}
			}
                	else{
                		if ( pilha[cont].linha == 10){
                            		direcao = rand () % 2 + 1; // 1 = CIMA, 2 - DIREITA

                            		if (direcao == 1){
                                		*posColuna = pilha[cont].coluna;
                                		*posLinha = pilha[cont].linha - 1;
                            		}
                            		else{
                                		*posColuna = pilha[cont].coluna + 1;
                                		*posLinha = pilha[cont].linha;
                            		}
                        	}
                        	else {
                            		direcao = rand () % 3 + 1; // 1 CIMA , 2 - BAIXO, 3 - DIREITA

                            		if (direcao == 1){ // ATIRAR NA DIREITA
                                		*posColuna = pilha[cont].coluna;
                                		*posLinha = pilha[cont].linha - 1;
                            		}
                            	/// OPA
                            		else{
                                		if ( direcao == 2){
                                    			*posColuna = pilha[cont].coluna;
                                    			*posLinha = pilha[cont].linha + 1;
                                		}
                                		else{
                                    			*posColuna = pilha[cont].coluna + 1;
                                    			*posLinha = pilha[cont].linha;
                                		}
                                ///OPA
                            		}
                        	}
                 	}
		}
                else{
                	if (pilha[cont].coluna == 10 ){
                        	if (pilha[cont].linha == 1){

                        		direcao = rand () % 2 + 1; // DIRECAO = 1 ESQUERDA, = 2 BAIXO

                        		if (direcao == 1){ // ATIRAR NA DIREITA
                            			*posColuna = pilha[cont].coluna - 1;
                            			*posLinha = pilha[cont].linha;
                        		}else{
                            			*posColuna = pilha[cont].coluna;
                            			*posLinha = pilha[cont].linha + 1;
                        		}
                   		}
                   		else{
                        		if ( pilha[cont].linha == 10){

                            			direcao = rand () % 2 + 1; // 1 = CIMA, 2 - ESQUERDA

                            			if (direcao == 1){
                                			*posColuna = pilha[cont].coluna;
                                			*posLinha = pilha[cont].linha - 1;
                            			}else{
                                			*posColuna = pilha[cont].coluna - 1;
                                			*posLinha = pilha[cont].linha;
                            			}
                        		}
                        		else {

                            			direcao = rand () % 3 + 1; // 1 CIMA , 2 - BAIXO, 3 - ESQUERDA

                            			if (direcao == 1){ // ATIRAR NA DIREITA
                                			*posColuna = pilha[cont].coluna;
                                			*posLinha = pilha[cont].linha - 1;
                            			}else{
                                			if ( direcao == 2){
                                    				*posColuna = pilha[cont].coluna;
                                    				*posLinha = pilha[cont].linha + 1;
                                			}else{
                                    				*posColuna = pilha[cont].coluna - 1;
                                    				*posLinha = pilha[cont].linha;
                                			}
                            			}
                        		}
                    		}
                	}else{
                    		if (pilha[*topo].linha == 1 ){
                            		direcao = rand () % 3 + 1; // 1 -  DIREITA , 2 - BAIXO, 3 - ESQUERDA

                            		if (direcao == 1){ // ATIRAR NA DIREITA
                                		*posColuna = pilha[cont].coluna + 1;
                                		*posLinha = pilha[cont].linha;
                            		}else{
                                		if ( direcao == 2){
                                    			*posColuna = pilha[cont].coluna;
                                    			*posLinha = pilha[cont].linha + 1;
                                		}else{
                                    			*posColuna = pilha[cont].coluna - 1;
                                    			*posLinha = pilha[cont].linha;
                            		}
                                		}
                        	}
                        	else{
                            		if (pilha[cont].linha == 10 ){
                                		direcao = rand () % 3 + 1; // 1 -  DIREITA , 2 - CIMA, 3 - ESQUERDA

                                		if (direcao == 1){ // ATIRAR NA DIREITA
                                    			*posColuna = pilha[cont].coluna + 1;
                                    			*posLinha = pilha[cont].linha;
                                		}else{
                                    			if ( direcao == 2){
                                        			*posColuna = pilha[cont].coluna;
                                        			*posLinha = pilha[cont].linha - 1;
                                    			}else{
                                        			*posColuna = pilha[cont].coluna - 1;
                                        			*posLinha = pilha[cont].linha;
                                    			}
                                		}
                            		}
                            		else{
                                		direcao = rand () % 4 + 1; // 1- CIMA, 2 - ESQUERDA, 3 - BAIXO, 4 - DIREITA
                                		if (direcao == 1){
                                    			*posColuna = pilha[cont].coluna;
                                    			*posLinha = pilha[cont].linha - 1;
                                		}else{
                                    			if (direcao == 2){
                                        			*posColuna = pilha[cont].coluna - 1;
                                        			*posLinha = pilha[cont].linha;
                                    			}
                                    			else{
                                        			if (direcao == 3){
                                            				*posColuna = pilha[cont].coluna;
                                            				*posLinha = pilha[cont].linha + 1;
                                        			}
                                        			else{
                                            				*posColuna = pilha[cont].coluna + 1;
                                            				*posLinha = pilha[cont].linha;
                                        			}
                                    			}
                                		}
                            		}
                        	}
                    	}
                }
            	pontAux1 = buscarNo(jogo, posLinha, posColuna);
            	
            	if(pontAux1->showHumano == 0)
                	return pontAux1;

               	if (pilha[cont].coluna != 10){
                	*posColuna = pilha[cont].coluna + 1;
                    	*posLinha = pilha[cont].linha;
                    	pontAux1 = buscarNo(jogo, posLinha, posColuna);
                    	if (pontAux1->showHumano != 0 || pontAux1 == NULL){
                       		if (pilha[cont].coluna != 1){
                       			*posColuna = pilha[cont].coluna - 1;
                        		*posLinha = pilha[cont].linha;
                        		pontAux1 = buscarNo(jogo, posLinha, posColuna);
                        		if (pontAux1->showHumano != 0 || pontAux1 == NULL){
                        			if (pilha[cont].linha != 10){
				          		*posColuna = pilha[cont].coluna;
				            		*posLinha = pilha[cont].linha + 1;
                            				pontAux1 = buscarNo(jogo, posLinha, posColuna);
                                			if (pontAux1->showHumano != 0 || pontAux1 == NULL){
                                				if (pilha[cont].coluna != 1){
						            		*posColuna = pilha[cont].coluna;
						            		*posLinha = pilha[cont].linha - 1;
						            		pontAux1 = buscarNo(jogo, posLinha, posColuna);
                                    					if (pontAux1->showHumano != 0 || pontAux1 == NULL){
                                        					cont--;
                                    					}
                                    					else
                                        					return pontAux1;
                                				}
                                				else
                                					cont --;
                                			}
                                			else
                                    				return pontAux1;
                        			}
                        			else{
                            				if (pilha[cont].coluna != 1){
						            		*posColuna = pilha[cont].coluna;
						            		*posLinha = pilha[cont].linha - 1;
						            		pontAux1 = buscarNo(jogo, posLinha, posColuna);
                                    					if (pontAux1->showHumano != 0 || pontAux1 == NULL){
                                        					cont--;
                                    					}
                                    					else
                                        					return pontAux1;
                                				}
                                				else
                                					cont --;
                                		}
                    			}
                   			else
                        			return pontAux1;
                       		}
                       	 	else{
                        		if (pilha[cont].linha != 10){
				          	*posColuna = pilha[cont].coluna;
				       		*posLinha = pilha[cont].linha + 1;
                            			pontAux1 = buscarNo(jogo, posLinha, posColuna);
                               			if (pontAux1->showHumano != 0 || pontAux1 == NULL){
                               				if (pilha[cont].coluna != 1){
					            		*posColuna = pilha[cont].coluna;
					            		*posLinha = pilha[cont].linha - 1;
					            		pontAux1 = buscarNo(jogo, posLinha, posColuna);
                               					if (pontAux1->showHumano != 0 || pontAux1 == NULL){
                                       					cont--;
                                   				}
                                    				else
                                       					return pontAux1;
                                			}
                               				else
                               					cont --;
                               			}
                               			else
                              				return pontAux1;
                       			}
                        		else{
                            			if (pilha[cont].coluna != 1){
					            		*posColuna = pilha[cont].coluna;
					            		*posLinha = pilha[cont].linha - 1;
					            		pontAux1 = buscarNo(jogo, posLinha, posColuna);
                               					if (pontAux1->showHumano != 0 || pontAux1 == NULL){
                                        				cont--;
                                    				}
                                    				else
                                       					return pontAux1;
                               				}
                               				else
                               					cont --;
                               		}
                    		}
                    	}
                   	else
                        	return pontAux1;  
                }
                else{
               		if (pilha[cont].coluna != 1){
                       			*posColuna = pilha[cont].coluna - 1;
                        		*posLinha = pilha[cont].linha;
                        		pontAux1 = buscarNo(jogo, posLinha, posColuna);
                        		if (pontAux1->showHumano != 0 || pontAux1 == NULL){
                        			if (pilha[cont].linha != 10){
				          		*posColuna = pilha[cont].coluna;
				            		*posLinha = pilha[cont].linha + 1;
                            				pontAux1 = buscarNo(jogo, posLinha, posColuna);
                                			if (pontAux1->showHumano != 0 || pontAux1 == NULL){
                                				if (pilha[cont].coluna != 1){
						            		*posColuna = pilha[cont].coluna;
						            		*posLinha = pilha[cont].linha - 1;
						            		pontAux1 = buscarNo(jogo, posLinha, posColuna);
                                    					if (pontAux1->showHumano != 0 || pontAux1 == NULL){
                                        					cont--;
                                    					}
                                    					else
                                        					return pontAux1;
                                				}
                                				else
                                					cont --;
                                			}
                                			else
                                    				return pontAux1;
                        			}
                        			else{
                            				if (pilha[cont].coluna != 1){
						            		*posColuna = pilha[cont].coluna;
						            		*posLinha = pilha[cont].linha - 1;
						            		pontAux1 = buscarNo(jogo, posLinha, posColuna);
                                    					if (pontAux1->showHumano != 0 || pontAux1 == NULL){
                                        					cont--;
                                    					}
                                    					else
                                        					return pontAux1;
                                				}
                                				else
                                					cont --;
                                		}
                    			}
                   			else
                        			return pontAux1;
                       	}
                       	else{
                        	if (pilha[cont].linha != 10){
				    	*posColuna = pilha[cont].coluna;
			  		*posLinha = pilha[cont].linha + 1;
                            		pontAux1 = buscarNo(jogo, posLinha, posColuna);
                               		if (pontAux1->showHumano != 0 || pontAux1 == NULL){
                       				if (pilha[cont].coluna != 1){
				            		*posColuna = pilha[cont].coluna;
				            		*posLinha = pilha[cont].linha - 1;
				            		pontAux1 = buscarNo(jogo, posLinha, posColuna);
                               				if (pontAux1->showHumano != 0 || pontAux1 == NULL){
                                       				cont--;
                                   			}
                               				else
                              					return pontAux1;
                               			}
                              			else
                              				cont --;
                              		}
                              		else
                              			return pontAux1;
                       		}
                        	else{
                            		if (pilha[cont].coluna != 1){
				      		*posColuna = pilha[cont].coluna;
			        		*posLinha = pilha[cont].linha - 1;
			            		pontAux1 = buscarNo(jogo, posLinha, posColuna);
                        			if (pontAux1->showHumano != 0 || pontAux1 == NULL){
                               				cont--;
                        			}
                        			else
                        				return pontAux1;
                        			}
                        		else
                               			cont --;
                               	}
                    	}
             	 }
             	 while (cont == -1){
             	 	*posColuna = rand () % 10 + 1;
             	 	*posLinha =  rand () % 10 + 1;
             	 	pontAux1 = buscarNo(jogo, posLinha, posColuna);
             	 	if (pontAux1->showHumano == 0 || pontAux1 != NULL)
                        	return pontAux1;
                 }
                        			
             	 //printf ("CONT = %d\n\n\n",cont);
	}
    	return pontAux1;	
}
// Esta função gera a jogado do computador
void jogadaComputer(Node **jogo, Coordenada *pilha, int *topo, int NavioHumano[], int NavioComputer []){

	//sortear a primeira jogada
	int posLinha, posColuna, acertou;
	Node *pontAux1;

        pontAux1 = *jogo;
		// A variável acertou informa que se na posicao sorteada do computador, for alguma parte da embarcação... o computador continua jogando
	
	acertou = 0;
	while(acertou != 1){

        	if(*topo == -1){
			// Primeiras jogadas são aleatórias
                	posColuna = (rand() % 10) + 1; // As colunas de A a J
                	posLinha = (rand() % 10) + 1; // As linhas são de 1 a 9
                
			// Eu fiz essa função aqui pra printar o mapa do navio a cada rodada, só pra ver o ki ta acontecenu, se ele ta jogando e la tem uma coisa e pah
                	//printf("Mapa do Computador:\n");
                	//printNavio(jogo);

            		// Diaulas, fiz uma função que busca a célula jogada, porque mais a frente precisamos sempre ir na celula pra ver se ela já foi jogada. Acho que assim, simplifica as coisas
                	pontAux1 = buscarNo(jogo, &posLinha, &posColuna);

                	//printf("Caractere nesta posição: %c \n", pontAux1->espacoHumano);
                	if (pontAux1->showHumano == 0)
                        	pontAux1->showHumano = 1; // Vou marcar aquela célula, para indentifica que ela já foi jogada
                    	else {
					// Se entrou nesta condição, a célula já foi jogada
                        	while(pontAux1->showHumano == 1){ // enquanto o computador jogar uma célula que ele já jogou, sorteio nova jogada
                            		posColuna = (rand() % 10) + 1 ;
                            		posLinha = (rand() % 10) + 1 ;
                            		pontAux1 = buscarNo(jogo, &posLinha, &posColuna);
                          		//printf ("\n\t Computador tinha acertado uma celula ja antes acertada !\n");
                            		//printf ("Nova celula %c %d", posColuna + 64, posLinha);
                        	}
                        	pontAux1->showHumano = 1;
                    	}

                	if(pontAux1->espacoHumano != 'O'){
				// Se ele entrou nesta condição, é porque o computador acertou alguma parte de alguma embarcação, então ele continua jogando
				// Printa com  * onde  acertou ---- Ok
				// decrementar no vetor do computador em um na posicao do numero do identificador do barco

				// Coloca na pilha a celula que ele acertou ------ Ok
                    		NavioHumano[pontAux1->identificadorHumano]= NavioHumano[pontAux1->identificadorHumano] - 1;
                    		
                    		*topo = *topo + 1;
                    		
                    		pilha[*topo].linha = posLinha;

                    		pilha[*topo].coluna = posColuna;

                    		acertou = NavioDestruido (jogo, pontAux1,pilha,topo,NavioHumano,NavioComputer, COMPUTADOR); // VERIFICA SE O NAVIO FOI TOTALMENTE DESTRUIDO.

                    		//getchar();
                	}
                	else
                    		acertou = 1;
            	}
            	else{
			pontAux1 = JogadaInteligenteComputer (jogo,pilha,topo,NavioHumano, &posColuna, &posLinha);

                	//printf("Caractere nesta posição: %c \n", pontAux1->espacoHumano);

                	pontAux1->showHumano = 1; // Vou marcar aquela célula, para indentifica que ela já foi jogada

                	if (pontAux1->espacoHumano != 'O'){
                        	
                    		NavioHumano[pontAux1->identificadorHumano]--;
                    		
                    		*topo = *topo + 1;
                    	
                    		pilha[*topo].linha = posLinha;

                    		pilha[*topo].coluna = posColuna;
                		
                    		acertou = NavioDestruido (jogo, pontAux1,pilha,topo,NavioHumano,NavioComputer,COMPUTADOR);
                    		
                        	
                	}else
                    		acertou = 1;
			
            		getchar();
            	}
            	printf("\nÚltima Jogada do Computador: %c%d \n", posColuna + 64, posLinha);
            	printf ("------------------------------------------\n");
            
    	}	
    	//getchar();
}

void executar (Node **jogo, int *placarHumano, int *placarComputer){

	int i, j, aux[7], contLetra = 0,contNumero = 0,posHorizontalHumano,posVerticalHumano,topo;
	char jogada[7], Continuar;
	int *NavioHumano, *NavioComputer;
	int leitura = 0, auxiliar = 0, jogaHumano, contComputer = 0, contHumano = 0,auxNumero = 0;
	Coordenada pilha[20];

	NavioHumano = malloc (9 * sizeof (int));
    	NavioComputer = malloc (9 * sizeof (int));
	
	// criar uma pilha, nesta pilha guarda as jogadas do computador
    	topo = -1;

	for (i=0; i<20; i++){
        	pilha[i].linha = 0;
        	pilha[i].coluna = 0;
	}

	// Cada posição do navioHumano[i] = n;
	// onde i é o tipo de embarcação, e n o numero de espaços que ele ocupa na malha
	NavioHumano[0] = 5;
	NavioComputer[0] = 5;
	NavioHumano[1] = 3;
	NavioComputer[1] = 3;
	NavioHumano[2] = 3;
	NavioComputer[2] = 3;
	NavioHumano[3] = 2;
	NavioComputer[3] = 2;
	NavioHumano[4] = 2;
	NavioComputer[4] = 2;
	NavioHumano[5] = 2;
	NavioComputer[5] = 2;
	NavioHumano[6] = 1;
	NavioComputer[6] = 1;
	NavioHumano[7] = 1;
	NavioComputer[7] = 1;
	NavioHumano[8] = 1;
	NavioComputer[8] = 1;

    	while (contComputer < 8 && contHumano < 8){
        	system("clear");
        	printMalha(jogo, NavioComputer, NavioHumano);
        	
        	jogaHumano = 0;
        	contComputer = 0;
        	contHumano = 0;
        	while(leitura != 1){
        		//printf("ENTROU NO WHILE !");
        		while (jogaHumano == 0){
            			printf ("\nEntre a sua jogada: ");
            			fgets(jogada,7,stdin);

            			for (i=0;i<7;i++)
                			aux[i] = (int) jogada[i];

            			for (i=0;i<7;i++){

                			if (aux[i] >= 65 && aux[i] <= 74){
                    				posHorizontalHumano = aux[i] - 64;
                    				contLetra++;
                			}
                			else{
                    				if (aux[i] >= 97 && aux[i] <= 106){
                        				posHorizontalHumano = aux[i] - 96;
                        				contLetra++;
                    				}
                    				else{
                        				if (aux[i] >= 50 && aux[i] <= 57){
                            					posVerticalHumano = aux[i] - 48;
                            					contNumero++;
                        				}
                        				else{
                            					if (aux[i] == 49){
                                					for (j=i;j<7;j++){
                                    						if (aux[j] == 48){
                                        						posVerticalHumano = 10;
                                        						contNumero++;
                                        						break;
                                    						}

                                					}
                                					if (contNumero == 0){
                                    						posVerticalHumano = 1;
                                    						contNumero++;
                                					}
                            					}
                        				}
                    				}
                			}
            			}
				
				for (j=0;j<7;j++){
                                   if (aux[j] == 48)
                                   	auxNumero++;
                                }
            			if (contLetra != 1 || contNumero != 1 || auxNumero > 1){
                			
                			printf ("JOGADA: %d %d\n\n", posHorizontalHumano, posVerticalHumano);
                			
                			// Saída secreta do jogo
                			if( (posHorizontalHumano + 64) == 115 || posVerticalHumano == 5) 
                			{
                				liberarMalha(jogo);
                				return;
                			}
                			
                			printf ("JOGADA INVÁLIDA :P \n");
                			contLetra = 0;
                			contNumero = 0;
                			auxNumero = 0;
                			jogaHumano = 0;
            			}
            			else{
            				//printf ("JOGADA: %d %d\n\n", posHorizontalHumano, posVerticalHumano);
                			leitura = 1;
                			contLetra = 0;
                			contNumero = 0;
                			auxNumero = 0;	
            				jogaHumano = jogadaHumano(jogo, &posVerticalHumano, &posHorizontalHumano, NavioHumano, NavioComputer);
            			}
            			

        		}		
        	}
                			
        	
        	printf("\nÚltima jogada do humano: %c%d \n", posHorizontalHumano + 64, posVerticalHumano);
        	
        	jogadaComputer(jogo, pilha, &topo, NavioHumano, NavioComputer);
        	auxiliar++;
        	leitura = 0;

        	getchar();
        	
        	for (i=0;i<8;i++){
        		if (NavioComputer[i] == 0)
        			contComputer++;
        		if (NavioHumano[i] == 0)
        			contHumano++;
        	}
        	
    	}

    	if (contComputer == 8 && contHumano == 8)
    		printf ("\n\n O JOGO EMPATOU\n\n");
    	else{
    		if (contHumano == 8){
    			printf ("\t O COMPUTADOR VENCEU O JOGO\n");
    			*placarComputer = *placarComputer + 1;
    		}
    		else{
    			printf ("\t O HUMANO VENCEU O JOGO !\n");
    			*placarHumano = *placarHumano + 1;
    			//printf ("%d",*	placarHumano);
    		}
    	}
    	
    	getchar ();
    	liberarMalha(jogo);
	// até aqui ta tudo filé
}

// função para iniciar a malha
//A ideia desta função é simples, eh como se fossemos preencher uma matriz R^_{n x n}, porem sempre devemos guarda o ponteiro da primeira celula da "linha", para que, quando fossemos preencher a da próxima linha, a primeira célula desta aponte para a primeira da linha superior, assim, sucessivamente.

void iniciar(Node **jogo, int* placarHumano, int* placarComputer)	{

	int i, j = 0;
	Node *pontAux1, *pontAux2, *pontAux3, *novo;


	// célula A1
	novo = criarNo();

	*jogo = novo;

	pontAux1 = *jogo;
	pontAux2 = *jogo;
	pontAux3 = *jogo;


	for(i = 1; i <= 10; i++ )	{

		for(j = 1; j <= 9; j++)	{

			// Parte de cima da malha, todos os nós desta 1 linha, no->cima são nulos
			if(i == 1){
				novo = criarNo();
				pontAux2->direito = novo;
				novo->esquerdo = pontAux2;
				pontAux2 = novo;
			}
			else{

				novo = criarNo();
				pontAux3->direito = novo;
				novo->esquerdo = pontAux3;
				pontAux2 = pontAux2->direito;
				pontAux3 = novo;

				pontAux3->cima = pontAux2;
				pontAux2->baixo = pontAux3;

			}
		}

		if(i != 10){
			pontAux2 = pontAux1;
			novo = criarNo();
			pontAux1 = novo;
			pontAux3 = pontAux1;
			pontAux2->baixo = pontAux3;
			pontAux3->cima = pontAux2;
		}
	}
	//printMalha(jogo);
	//printf ("oi2\n\n");
	
	sorteio(jogo, placarHumano, placarComputer);
}

// Esta função preenche a malha com os equipamentos de ambos os jogadores. São inseridos os caracteres para representar o porta-conteiner, destroyers, fragata, submarino. Sempre antes tentarPreenchar, sortemaos aleatóriamente a orientação da embarcação, se é horizontal ou vertical, por exemplo

int TentarPreencher(Node **jogo, int Orientacao, int posH, int posV, int navio, int jogador, int identificador){
	Node *Aux,*Inicial;
	int i, cont = 0;

	Aux = *jogo;
	for (i=1;i<posH;i++)
		Aux = Aux->direito;


	for (i=1;i<posV;i++)
		Aux = Aux->baixo;

	Inicial = Aux;

	if (Orientacao == HORIZONTAL)	{
		if (navio == PORTA_AVIAO)	{
			if (jogador == HUMANO)	{
				while (cont < 5)	{
					if (Aux->espacoHumano == 'O')	{
						Aux = Aux->direito;
						cont++;
					}
				}
			}

			if (jogador == COMPUTADOR){
				while (cont < 5){
					if (Aux->espacoComputer == 'O'){
						Aux = Aux->direito;
						cont++;
					}
				}

			}

			if (cont == 5 && jogador == HUMANO){
				while (cont != 0)	{

					//inicio do porta-aviao
					if (cont == 5){
						Inicial->espacoHumano = '<';
						Inicial->identificadorHumano = identificador;
					}

					else{
						if(cont == 1){
							Inicial->espacoHumano = '>';
							Inicial->identificadorHumano = identificador;
						}
						else{
							Inicial->espacoHumano = '#';
							Inicial->identificadorHumano = identificador;
						}
					}
					Inicial = Inicial->direito;
					cont--;
				}
				return 1;
			}

			if (cont == 5 && jogador == COMPUTADOR){
				while (cont != 0)	{
					if (cont == 5){
						Inicial->espacoComputer = '<';
						Inicial->identificadorComputer = identificador;
					}

					else{
						if(cont == 1){
							Inicial->espacoComputer = '>';
							Inicial->identificadorComputer = identificador;
						}
						else{
							Inicial->espacoComputer = '#';
							Inicial->identificadorComputer = identificador;
						}
					}
					Inicial = Inicial->direito;
					cont--;
				}
				return 1;
			}
			return 0;
		}

		if (navio == DESTROYER){
			if (jogador == HUMANO){
				while (cont < 3){
					if (Aux->espacoHumano == 'O'){
						Aux = Aux->direito;
						cont++;
					}
					else
						break; //mudei aqui (inclui break)
				}

			}

			if (jogador == COMPUTADOR){
				while (cont < 3){
					if (Aux->espacoComputer == 'O'){
						Aux = Aux->direito;
						cont++;
					}
					else
						break; //mudei aqui (inclui break)
				}

			}

			if (cont == 3 && jogador == HUMANO){
				while (cont != 0){
					if (cont == 3){
						Inicial->espacoHumano = '<';
						Inicial->identificadorHumano = identificador;
					}

					else{
						if(cont == 1){
							Inicial->espacoHumano = '>';
							Inicial->identificadorHumano = identificador;
						}
						else{
							Inicial->espacoHumano = '#';
							Inicial->identificadorHumano = identificador;
						}
					}

					Inicial = Inicial->direito;
					cont--;
				}
				return 1;
			}
			if (cont == 3 && jogador == COMPUTADOR){
				while (cont != 0){
					if (cont == 3){
						Inicial->espacoComputer = '<';
						Inicial->identificadorComputer = identificador;
					}

					else{
						if(cont == 1){
							Inicial->espacoComputer = '>';
							Inicial->identificadorComputer = identificador;
						}
						else{
							Inicial->espacoComputer = '#';
							Inicial->identificadorComputer = identificador;
						}
					}
					Inicial = Inicial->direito;
					cont--;
				}
				return 1;
			}
			return 0;
		}

		if (navio == FRAGATA){
			if (jogador == HUMANO){
				while (cont < 2){
					if (Aux->espacoHumano == 'O'){
						Aux = Aux->direito;
						cont++;
					}
					else
						break;
				}
			}

			if (jogador == COMPUTADOR){
				while (cont < 2){
					if (Aux->espacoComputer == 'O'){
						Aux = Aux->direito;
						cont++;
					}else
						break;
				}
			}

			if (cont == 2 && jogador == HUMANO){
				while (cont != 0){

					if (cont == 2){
						Inicial->espacoHumano = '<';
						Inicial->identificadorHumano = identificador;
					}
					if (cont == 1){
						Inicial->espacoHumano = '>';
						Inicial->identificadorHumano = identificador;
					}

					Inicial = Inicial->direito;
					cont--;
				}
				return 1;
			}
			if (cont == 2 && jogador == COMPUTADOR){
				while (cont != 0){
					if (cont == 2){
						Inicial->espacoComputer = '<';
						Inicial->identificadorComputer = identificador;
					}

					if (cont == 1){
						Inicial->espacoComputer = '>';
						Inicial->identificadorComputer = identificador;
					}

					Inicial = Inicial->direito;
					cont--;
				}
				return 1;
			}
			return 0;

		}

		if (navio == SUBMARINO){
			if (jogador == HUMANO){
				while (cont < 1){
					if (Aux->espacoHumano == 'O'){
						Aux = Aux->direito;
						cont++;
					}else
						break;
				}

			}

			if (jogador == COMPUTADOR){
				while (cont < 1){
					if (Aux->espacoComputer == 'O'){
						Aux = Aux->direito;
						cont++;
					}else
						break;
				}

			}

			if (cont == 1 && jogador == HUMANO){
				Inicial->espacoHumano = '@';
				Inicial->identificadorHumano = identificador;
				return 1;
			}
			if (cont == 1 && jogador == COMPUTADOR){
				Inicial->espacoComputer = '@';
				Inicial->identificadorComputer = identificador;
				return 1;
			}
			return 0;
		}

		// ALOCANDO AS JANGADAS NA POSIÇÃO HORIZONTAL
		if (navio == JANGADA){
			if (jogador == HUMANO){
				while (cont < 1){
					if (Aux->espacoHumano == 'O'){
						Aux = Aux->direito;
						cont++;
					}else
						break;
				}

			}

			if (jogador == COMPUTADOR){
				while (cont < 1){
					if (Aux->espacoComputer == 'O'){
						Aux = Aux->direito;
						cont++;
					}else
						break;
				}

			}

			if (cont == 1 && jogador == HUMANO)	{
				Inicial->espacoHumano = '&';
				Inicial->identificadorHumano = identificador;
				return 1;
			}
			if (cont == 1 && jogador == COMPUTADOR){
				Inicial->espacoComputer = '&';
				Inicial->identificadorComputer = identificador;
				return 1;
			}
			return 0;
		}
	}

	if (Orientacao == VERTICAL)	{
		if (navio == PORTA_AVIAO)	{
			if (jogador == HUMANO){
				while (cont < 5){
					if (Aux->espacoHumano == 'O'){
						Aux = Aux->baixo;
						cont++;
					}
				}

			}

			if (jogador == COMPUTADOR){
				while (cont < 5){
					if (Aux->espacoComputer == 'O'){
						Aux = Aux->baixo;
						cont++;
					}
				}

			}

			if (cont == 5 && jogador == HUMANO){
				while (cont != 0){
					//inicio do porta-aviao
					if (cont == 5){
						Inicial->espacoHumano = '^';
						Inicial->identificadorHumano = identificador;
					}

					else{
						if(cont == 1){
							Inicial->espacoHumano = 'v';
							Inicial->identificadorHumano = identificador;
						}
						else{
							Inicial->espacoHumano = '#';
							Inicial->identificadorHumano = identificador;
						}
					}
					Inicial = Inicial->baixo;
					cont--;
				}
				return 1;
			}
			if (cont == 5 && jogador == COMPUTADOR){
				while (cont != 0){
					if (cont == 5){
						Inicial->espacoComputer = '^';
						Inicial->identificadorComputer = identificador;
					}

					else{
						if(cont == 1){
							Inicial->espacoComputer = 'v';
							Inicial->identificadorComputer = identificador;
						}
						else{
							Inicial->espacoComputer = '#';
							Inicial->identificadorComputer = identificador;
						}
					}
					Inicial = Inicial->baixo;
					cont--;
				}
				return 1;
			}
			return 0;

		}

		if (navio == DESTROYER)	{
			if (jogador == HUMANO){
				while (cont < 3){
					if (Aux->espacoHumano == 'O'){
						Aux = Aux->baixo;
						cont++;
					}
					else
						break;
				}

			}

			if (jogador == COMPUTADOR){
				while (cont < 3){
					if (Aux->espacoComputer == 'O'){
						Aux = Aux->baixo;
						cont++;
					}
					else
						break;
				}

			}

			if (cont == 3 && jogador == HUMANO){
				while (cont != 0){
					if (cont == 3){
						Inicial->espacoHumano = '^';
						Inicial->identificadorHumano = identificador;
					}

					else{
						if(cont == 1){
							Inicial->espacoHumano = 'v';
							Inicial->identificadorHumano = identificador;
						}
						else{
							Inicial->espacoHumano = '#';
							Inicial->identificadorHumano = identificador;
						}
					}
					Inicial = Inicial->baixo;
					cont--;
				}
				return 1;
			}

			if (cont == 3 && jogador == COMPUTADOR){
				while (cont != 0){
					if (cont == 3){
						Inicial->espacoComputer = '^';
						Inicial->identificadorComputer = identificador;
					}

					else{
						if(cont == 1){
							Inicial->espacoComputer = 'v';
							Inicial->identificadorComputer = identificador;
						}
						else{
							Inicial->espacoComputer = '#';
							Inicial->identificadorComputer = identificador;
						}
					}
					Inicial = Inicial->baixo;
					cont--;
				}
				return 1;
			}
			return 0;
		}

		// alocação de embarcação: FRAGATA
		if (navio == FRAGATA){
			if (jogador == HUMANO){
				while (cont < 2){
					if (Aux->espacoHumano == 'O'){
						Aux = Aux->baixo;
						cont++;
					}else
						break;
				}
			}

			if (jogador == COMPUTADOR){
				while (cont < 2){
					if (Aux->espacoComputer == 'O'){
						Aux = Aux->baixo;
						cont++;
					}else
						break;
				}
			}

			if (cont == 2 && jogador == HUMANO){
				while (cont != 0){
					if (cont == 2){
						Inicial->espacoHumano = '^';
						Inicial->identificadorHumano = identificador;
					}
					if (cont == 1){
						Inicial->espacoHumano = 'v';
						Inicial->identificadorHumano = identificador;
					}

					Inicial = Inicial->baixo;
					cont--;
				}
				return 1;
			}
			if (cont == 2 && jogador == COMPUTADOR){
				while (cont != 0){
					if (cont == 2){
						Inicial->espacoComputer = '^';
						Inicial->identificadorComputer = identificador;
					}

					if (cont == 1){
						Inicial->espacoComputer = 'v';
						Inicial->identificadorComputer = identificador;
					}

					Inicial = Inicial->baixo;
					cont--;
				}
				return 1;
			}
			return 0;

		} // fim do caso navio == 3

		if (navio == SUBMARINO)	{
			if (jogador == HUMANO){
				while (cont < 1){
					if (Aux->espacoHumano == 'O'){
						Aux = Aux->baixo;
						cont++;
					}else
						break;
				}

			}

			if (jogador == COMPUTADOR){
				while (cont < 1){
					if (Aux->espacoComputer == 'O'){
						Aux = Aux->baixo;
						cont++;
					}else
						break;
				}

			}

			if (cont == 1 && jogador == HUMANO){
				Inicial->espacoHumano = '@';
				Inicial->identificadorHumano = identificador;
				return 1;
			}
			if (cont == 1 && jogador == COMPUTADOR){
				Inicial->espacoComputer = '@';
				Inicial->identificadorComputer = identificador;
				return 1;
			}
			return 0;
		} // fim do caso navio == 4

		if (navio == JANGADA)	{
			if (jogador == HUMANO){
				while (cont < 1){
					if (Aux->espacoHumano == 'O'){
						Aux = Aux->baixo;
						cont++;
					}else
						break;
				}

			}

			if (jogador == COMPUTADOR){
				while (cont < 1){
					if (Aux->espacoComputer == 'O'){
						Aux = Aux->baixo;
						cont++;
					}else
						break;
				}

			}

			if (cont == 1 && jogador == HUMANO){
				Inicial->espacoHumano = '&';
				Inicial->identificadorHumano = identificador;
				return 1;
			}
			if (cont == 1 && jogador == COMPUTADOR){
				Inicial->espacoComputer = '&';
				Inicial->identificadorComputer = identificador;
				return 1;
			}
			return 0;
		}
	}
	return 0;
}

// essa função preenche a malha com os equipamentos dos jogadores (humano, computador): porta-aviao, destroyers, fragata, submarino, jangada
void sorteio(Node **jogo, int *placarHumano, int *placarComputer){

	int posHorizontal, posVertical, escolha,identificador = 0, colocouNoMarHumano = 0, colocouNoMarComputer = 0;
	int NumeroDestroyers = 0, NumeroFragatas = 0, NumeroSubmarino = 0, Navio = PORTA_AVIAO;

	//printf("DEU CERTO !! \n\n");
	srand( time(NULL) );

	while (Navio <=5){
		if (Navio == PORTA_AVIAO){
			escolha = rand() %2;

			if (escolha == HORIZONTAL){
				while(colocouNoMarHumano != 1){
					posHorizontal = (rand() % 6) + 1;
					posVertical = (rand() % 10) + 1;
					colocouNoMarHumano = TentarPreencher (jogo, HORIZONTAL,posHorizontal,posVertical,PORTA_AVIAO,1, identificador);
				}
			}
			else{
				while(colocouNoMarHumano != 1){
					posHorizontal = (rand() % 10) + 1;
					posVertical = (rand() % 6) + 1;
					colocouNoMarHumano = TentarPreencher (jogo, VERTICAL,posHorizontal,posVertical,PORTA_AVIAO,1,identificador);
				}
			}

			escolha = rand() % 2;

			if (escolha == HORIZONTAL){
				while(colocouNoMarComputer != 1){
					posHorizontal = (rand() % 6) + 1;
					posVertical = (rand() % 10) + 1;
					colocouNoMarComputer = TentarPreencher (jogo, HORIZONTAL,posHorizontal,posVertical,PORTA_AVIAO,2,identificador);
				}
			}
			else{
				while(colocouNoMarComputer != 1){
					posHorizontal = (rand() % 10) + 1;
					posVertical = (rand() % 6) + 1;
					colocouNoMarComputer = TentarPreencher (jogo, VERTICAL,posHorizontal,posVertical,PORTA_AVIAO,2,identificador);
				}
			}
		}

		colocouNoMarHumano = 0;
		colocouNoMarComputer = 0;
		//printf ("AAAAAAAAAAAAAAAAAAAAAa %d\n\n", identificador);
		if (Navio == DESTROYER){
			identificador++;
			while (NumeroDestroyers != 2){
				escolha = rand() % 2;
				if (escolha == HORIZONTAL){
					while (colocouNoMarHumano != 1){
						posHorizontal = (rand () % 8) + 1;
						posVertical   = (rand () % 10) + 1;
						colocouNoMarHumano = TentarPreencher (jogo, HORIZONTAL, posHorizontal, posVertical, DESTROYER, 1,identificador);
					}
					NumeroDestroyers++;
					identificador++;
					colocouNoMarHumano = 0;
				}
				else{
					while (colocouNoMarHumano != 1){
						posHorizontal = (rand () % 10) + 1;
						posVertical   = (rand () % 8) + 1;
						colocouNoMarHumano = TentarPreencher (jogo, VERTICAL, posHorizontal, posVertical, DESTROYER, 1,identificador);
					}
					NumeroDestroyers++;
					identificador++;
					colocouNoMarHumano = 0;
				}
			}

			identificador = 1;
			NumeroDestroyers = 0;

			while (NumeroDestroyers != 2){
				escolha = rand() % 2;
				if (escolha == HORIZONTAL){
					while (colocouNoMarComputer != 1){
						posHorizontal = (rand () % 8) + 1;
						posVertical   = (rand () % 10) + 1;
						colocouNoMarComputer = TentarPreencher (jogo, HORIZONTAL, posHorizontal, posVertical, DESTROYER, 2, identificador);
					}
					NumeroDestroyers++;
					identificador++;
					colocouNoMarComputer = 0;
				}
				else{
					while (colocouNoMarComputer != 1){
						posHorizontal = (rand () % 10) + 1;
						posVertical   = (rand () % 8) + 1;
						colocouNoMarComputer = TentarPreencher (jogo, VERTICAL, posHorizontal, posVertical, DESTROYER, 2, identificador);
					}
					NumeroDestroyers++;
					identificador++;
					colocouNoMarComputer = 0;
				}
			}
		}

		colocouNoMarHumano = 0;
		colocouNoMarComputer = 0;
		
		if (Navio == FRAGATA){
			while (NumeroFragatas != 3){
				escolha = rand () % 2;
				if (escolha == HORIZONTAL){
					while (colocouNoMarHumano != 1){
						posHorizontal = (rand() % 9) + 1;
						posVertical   = (rand() % 10) + 1;
						colocouNoMarHumano = TentarPreencher (jogo, HORIZONTAL, posHorizontal, posVertical, FRAGATA, 1, identificador);
					}
					NumeroFragatas++;
					identificador++;
					colocouNoMarHumano = 0;
				}
				else{
					while (colocouNoMarHumano != 1){
						posHorizontal = (rand() % 10) + 1;
						posVertical   = (rand() % 9) + 1;
						colocouNoMarHumano = TentarPreencher (jogo, VERTICAL, posHorizontal, posVertical, FRAGATA, 1, identificador);
					}
					NumeroFragatas++;
					identificador++;
					colocouNoMarHumano = 0;
				}
			}

			identificador = 3;
			NumeroFragatas = 0;

			while (NumeroFragatas != 3){
				escolha = rand () % 2;
				if (escolha == HORIZONTAL){
					while (colocouNoMarComputer != 1){
						posHorizontal = (rand() % 9) + 1;
						posVertical   = (rand() % 10) + 1;
						colocouNoMarComputer = TentarPreencher (jogo, HORIZONTAL, posHorizontal, posVertical, FRAGATA, 2, identificador);
					}
					NumeroFragatas++;
					identificador++;
					colocouNoMarComputer = 0;
				}
				else{
					while (colocouNoMarComputer != 1){
						posHorizontal = (rand() % 10) + 1;
						posVertical   = (rand() % 9) + 1;
						colocouNoMarComputer = TentarPreencher (jogo, VERTICAL, posHorizontal, posVertical, FRAGATA, 2, identificador);
					}
					NumeroFragatas++;
					identificador++;
					colocouNoMarComputer = 0;
				}
			}
		}

		colocouNoMarHumano = 0;
		colocouNoMarComputer = 0;
		
		if (Navio == SUBMARINO){
			while (NumeroSubmarino != 2){
				while (colocouNoMarHumano != 1){
					posHorizontal = (rand() % 10) + 1;
					posVertical = (rand() % 10) + 1;
					colocouNoMarHumano = TentarPreencher (jogo, HORIZONTAL, posHorizontal, posVertical, SUBMARINO, 1, identificador);
				}
				NumeroSubmarino++;
				identificador++;
				colocouNoMarHumano = 0;
			}

			NumeroSubmarino = 0;
			identificador = 6;

			while (NumeroSubmarino != 2){
				while (colocouNoMarComputer != 1){
					posHorizontal = (rand() % 10) + 1;
					posVertical = (rand() % 10) + 1;
					colocouNoMarComputer = TentarPreencher (jogo, VERTICAL, posHorizontal, posVertical, SUBMARINO, 2, identificador);
				}
				NumeroSubmarino++;
				identificador++;
				colocouNoMarComputer = 0;
			}
		}

		colocouNoMarHumano = 0;
		colocouNoMarComputer = 0;
		
		if (Navio == JANGADA){
			//printf ("%d \n",identificador);
			while(colocouNoMarHumano != 1){
				posHorizontal = (rand() % 10) + 1;
				posVertical = (rand() % 10) + 1;
				colocouNoMarHumano = TentarPreencher (jogo, HORIZONTAL,posHorizontal,posVertical,JANGADA,1, identificador);
			}

			while(colocouNoMarComputer != 1){
				posHorizontal = (rand() % 10) + 1;
				posVertical = (rand() % 10) + 1;
				colocouNoMarComputer = TentarPreencher (jogo, HORIZONTAL,posHorizontal,posVertical,JANGADA,2, identificador);
			}
		}
		Navio++;
	}
	executar (jogo, placarHumano, placarComputer);	
}

void delay(int tempo){
	
	clock_t time[2];
	
	time[0] = clock();
	for( ; ; ){
		time[1] = clock();
		if( ( (time[1] - time[0] ) / CLOCKS_PER_SEC ) == tempo)
			break;
	}
}

void creditos(){
	//system("clear");
	delay(1);
	printf("\t------ TRABALHO DE PROGRAMAÇÃO -------\n");
	printf("\n");
	delay(1);
	
	printf("\t-- UNIVIDERSIDADE FEDERAL DO CEARÁ ---\n");
	printf("\n");
	delay(1);
	
	printf("\t------- JOGO DE BATALHA NAVAL --------\n");
	printf("\n");
	delay(1);
	
	printf("\t------ PROF MIGUEL FRANKLYN ----------\n");
	
	delay(1);
	
	printf("\n");
	printf("\t--------- PROGRAMADORES --------------\n");
	printf("\n");
	delay(1);
	
	printf("\tDiaulas Murize S. V Marcondes - 360091\n");
	
	printf("\n");
	delay(1);
	
	printf("\tIgor Farias Souza - 352202\n");
	delay(1);
	
	printf("\n");
	printf("\t--------- COLABORADORES --------------\n");
	printf("\n");
	delay(1);
	
	printf("\tGoogle \n");
	delay(1);
	printf("\tLinux \n");
	delay(1);
	printf("\tJackson Magalhões - M.I. \n");
	delay(1);
	printf("\n");
	printf("\t-------------- Good Bye --------------\n");
	printf("\n");
	delay(1);
}
