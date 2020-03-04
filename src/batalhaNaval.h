/* Trabalho de Programação
* Diaulas, Davi e Igor
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

// definindo variáveis para o tipo de posicionamento dos elementos
#define HORIZONTAL	0
#define	VERTICAL	1

//definindo variáveis para o tipo de elemento
#define	PORTA_AVIAO 	1
#define	DESTROYER	2
#define	FRAGATA		3
#define	SUBMARINO	4
#define JANGADA		5

//definindo macro para o tipo de jogador
#define	HUMANO		1
#define COMPUTADOR	2

//estrutura da célula da malha
typedef struct Node {

	struct Node *cima;
	struct Node *baixo;
	struct Node *direito;
	struct Node *esquerdo;
	char espacoHumano, espacoComputer;
	int showHumano, showComputer, identificadorHumano,identificadorComputer, atingido;

}Node;


typedef struct Coordenada {

	int linha;
	int coluna;
}Coordenada;


Node *criarNo(void);
Node *criarPilha(void);
Node *buscarNo(Node **, int *, int *); // função criada 30/01
Node *buscarSubmarino(Node **, int);
void printNavio(Node **);
int jogadaHumano(Node **jogo, int *, int *, int [], int []);
void iniciar(Node **, int*, int*);
void print_identificador (Node **);
int TentarPreencher(Node **, int, int, int, int, int, int);
void printMalha(Node **, int [], int []);
void sorteio(Node **, int *, int *);
void executar(Node**, int*, int*);
void jogadaComputer(Node **, Coordenada *, int*, int [], int []);
int NavioDestruido (Node **, Node *, Coordenada *, int *, int [],int [], int);
Node *JogadaInteligenteComputer (Node **, Coordenada *, int *, int [], int*, int*);
void liberarMalha(Node **);
void delay(int);
void creditos();
