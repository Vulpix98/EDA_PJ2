#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "Header.h"

void main() 
{
	Grafo* grafo = NULL;

	grafo = createGraph();

	// serve para testes
	grafo = insertEdgeToVertex(grafo, 3);

	listar(grafo);

	menu(grafo);

	//test to add Edges
	/*grafo = insertLastEdge(grafo, 53, 0, 0);
	grafo = insertLastEdge(grafo, 99, 0, 0);
	grafo = insertLastEdge(grafo, 98, 0, 0);
	grafo = insertLastEdge(grafo, 98, 4, 3);*/
}



void menu(Grafo* grafo)
{
	int option;

	do
	{
		printf("1) Menu Principal\n\n");
		printf("1- Orientacao do grafo\n");
		printf("2- Listar\n");
		printf("3- Procura em profundidade!\n");
		printf("0- Sair\n\n");
		printf("Opcao: ");
		scanf("%d", &option);
		printf("\n\n\n");


		switch (option)
		{
		case 0:
			return (0);
			break;

		case 1:
			grafo = menuOrientacao(grafo);
			break;
		
		case 2:
			listar(grafo);
			break;

		case 3:
		{
			int profundidade = 0;
			int* visitado = (int*)calloc(100, sizeof(int)); // Assume no máximo 100 vértices
			int* emProcessamento = (int*)calloc(100, sizeof(int)); // Status dos vértices em processamento

			printf("Procura em profundidade: ");
			scanf("%d", &profundidade);
			int temCiclo = procuraProfundidade(grafo, profundidade, visitado, emProcessamento); // Começar a partir do vértice apartir da variavel = profundidade
			if (temCiclo)
			{
				printf("O grafo possui ciclos.\n");
			}
			else
			{
				printf("O grafo nao possui ciclos.\n");
			}

			free(visitado);
			free(emProcessamento);
			break;
		}
			
		default:
			printf("Valor invalido");
			break;
		}
	} while (option != 0);
}



Grafo* menuOrientacao(Grafo* grafo) 
{
	int valor;

	do
	{
		printf("2) Menu Orientacao\n\n");
		printf("1- Direita e Baixo\n");
		printf("2- Esquerda e Cima\n");
		printf("3- Ambos as opcoes\n");
		printf("0- Sair\n\n");
		printf("Opcao: ");
		scanf("%d", &valor);
		printf("\n\n\n");

		if (valor != 0) 
		{
			//1º se o grafo possuir arestas
			//  remover as arestas do grafo
			//  mantem os vertices
			grafo = deleteEdge(grafo);

			// 2º inserir as arestas
			grafo = insertEdgeToVertex(grafo, valor);
		}


	} while (valor != 0);

	return (grafo);
}



void listar(Grafo* grafo) 
{
	while (grafo != NULL)
	{
		printf("V(%d, %d): %d    A", grafo->x, grafo->y, grafo->vertice);

		Aresta* aresta = grafo->aresta;

		while (aresta != NULL)
		{
			printf("->%d", aresta->valor);

			aresta = aresta->seguinte;
		}

		printf("\n");
		
		grafo = grafo->seguinte;
	}
	printf("\n\n\n");
}


// read file "matriz.txt"
// create the Vertex on linked-list
Grafo* createGraph() 
{
	FILE* fp;
	Grafo* grafo = NULL;
	Aresta* aresta = NULL;

	char line[1024];
	char* token;
	int valor, x=0, y=0;

	// Opening file in reading mode
	fp = fopen("matriz.txt", "r");

	if (fp != NULL) 
	{
		// Read each line of the file
		while (fgets(line, sizeof line, fp) != NULL) {
			//new line, set to default (null and zero)
			//linha = NULL;
			
			// Tokenize the line by semicolons
			token = strtok(line, ";");

			while (token != NULL) {
				// Convert token to integer and store in the matrix
				valor = atoi(token);

				grafo = insertLastVertex(grafo, valor, x, y, aresta);
				
				token = strtok(NULL, ";");
				x++;
			}
			y++;
			x = 0;
		}
	}
	else printf("file can't be opened \n"); //fail to open file

	// Closing the file
	fclose(fp);


	return (grafo);
}



Grafo* deleteEdge(Grafo* grafo)
{
	Grafo* aux = grafo;
	Aresta* aresta = grafo->aresta;
	Aresta* arestaSeguinte = NULL;

	
	while (aux != NULL) // percorre o grafo (lista ligada do vertice)
	{
		while (aresta != NULL) // percorre as arestas do vertice 'aux'
		{
			arestaSeguinte = aresta->seguinte; // guardar a aresta seguite

			free(aresta); // limpar a memoria da aresta

			aresta = arestaSeguinte; // atribuir a aresta seguite a aresta
				
		}
		aux->aresta = NULL; // no vertice, a aresta dele tem que ser NULL
		aux = aux->seguinte; // vertice seguinte
	}

	return (grafo);
}



// insert all the Edge to their respective Vertex
// condiction of Edge: horizontal and vertical
// will create the Graph (linked-list of linked-list)
Grafo* insertEdgeToVertex(Grafo* grafo, int orientacao)
{
	Grafo* grf1 = grafo;
	Grafo* grf2 = grafo;

	while (grf1 != NULL)
	{
		grf2 = grafo;
		while (grf2 != NULL)
		{
			switch (orientacao)
			{
			case 1:
				grafo = testEdgeRight(grafo, grf1, grf2);
				grafo = testEdgeDown(grafo, grf1, grf2);
				break;
			case 2:
				grafo = testEdgeLeft(grafo, grf1, grf2);
				grafo = testEdgeUp(grafo, grf1, grf2);
				break;
			case 3:
				grafo = testEdgeRight(grafo, grf1, grf2);
				grafo = testEdgeLeft(grafo, grf1, grf2);
				grafo = testEdgeDown(grafo, grf1, grf2);
				grafo = testEdgeUp(grafo, grf1, grf2);
			default:
				break;
			}

			grf2 = grf2->seguinte;
		}

		grf1 = grf1->seguinte;
	}

	return (grafo);
}



Grafo* testEdgeRight(Grafo* grafo, Grafo* grf1, Grafo* grf2)
{
	if ((grf1->x + 1 == grf2->x) && (grf1->y == grf2->y)) return (grafo = insertLastEdge(grafo, grf2->vertice, grf1->x, grf1->y));
	else return (grafo);
}



Grafo* testEdgeLeft(Grafo* grafo, Grafo* grf1, Grafo* grf2)
{
	if ((grf1->x - 1 == grf2->x) && (grf1->y == grf2->y)) return (grafo = insertLastEdge(grafo, grf2->vertice, grf1->x, grf1->y));
	else return (grafo);	
}



Grafo* testEdgeUp(Grafo* grafo, Grafo* grf1, Grafo* grf2)
{
	if ((grf1->x == grf2->x) && (grf1->y - 1 == grf2->y)) return (grafo = insertLastEdge(grafo, grf2->vertice, grf1->x, grf1->y));
	return (grafo);
}



Grafo* testEdgeDown(Grafo* grafo, Grafo* grf1, Grafo* grf2)
{
	if ((grf1->x == grf2->x) && (grf1->y + 1 == grf2->y)) return (grafo = insertLastEdge(grafo, grf2->vertice, grf1->x, grf1->y));
	else return (grafo);
}



Grafo* insertLastVertex(Grafo* grafo, int vertice, int x, int y, Aresta* aresta)
{
	if (grafo == NULL) 
	{
		Grafo* novoGrafo = malloc(sizeof(Grafo));
		if (novoGrafo != NULL)
		{
			novoGrafo->vertice = vertice;
			novoGrafo->aresta = aresta;
			novoGrafo->x = x;
			novoGrafo->y = y;
			novoGrafo->seguinte = NULL;
			
			return (novoGrafo);
		}
		else return (grafo);
	}
	else
	{
		grafo->seguinte = insertLastVertex(grafo->seguinte, vertice, x, y, aresta);
		return (grafo);
	}
}



Aresta* insertEdge(Aresta* aresta, int valor)
{
	if (aresta == NULL)
	{
		Aresta* novaAresta = malloc(sizeof(Aresta));

		if (novaAresta != NULL)
		{
			novaAresta->valor = valor;
			novaAresta->seguinte = NULL;

			return (novaAresta);
		}
		else return (aresta);
	}
	else
	{
		aresta->seguinte = insertEdge(aresta->seguinte, valor);
		return (aresta);
	}
}



Grafo* insertLastEdge(Grafo* grafo, int valor, int x, int y)
{
	Aresta* aresta = grafo->aresta;

	if (grafo == NULL) return (grafo);

	if ((grafo->x == x) && (grafo->y == y) )
	{
		aresta = insertEdge(aresta, valor);

		grafo->aresta = aresta;

		return (grafo);		
	}
	else
	{
		grafo->seguinte = insertLastEdge(grafo->seguinte, valor, x, y);
		return (grafo);
	}
}



// Procura em Profundidade
int procuraProfundidade(Grafo* grafo, int vertice, int* visitado, int* emProcessamento)
{
	Grafo* v = encontrarVertice(grafo, vertice);
	if (!v) return 0; // Se o vértice não for encontrado, retorna 0

	if (emProcessamento[vertice])
		return 1; // Encontrou um ciclo, pois o vértice já está em processamento

	if (visitado[vertice])
		return 0; // Se o vértice já foi visitado e não está em processamento, não há ciclo

	visitado[vertice] = 1; // Marca o vértice como visitado
	emProcessamento[vertice] = 1; // Marca o vértice como em processamento

	Aresta* aresta = v->aresta;
	while (aresta)
	{
		if (DFS(grafo, aresta->valor, visitado, emProcessamento))
			return 1; // Se encontrar um ciclo em alguma aresta, retorna 1
		aresta = aresta->seguinte; // Move para a próxima aresta
	}

	emProcessamento[vertice] = 0; // Marca o vértice como não estando mais em processamento
	return 0; // Não encontrou ciclo
}



// Vai encontrar o vertice para o procuraProfundidade
Grafo* encontrarVertice(Grafo* grafo, int vertice)
{
	while (grafo)
	{
		if (grafo->vertice == vertice)
			return grafo; // Retorna o vértice se for encontrado
		grafo = grafo->seguinte; // Move para o próximo vértice
	}
	return NULL; // Retorna NULL se o vértice não for encontrado
}