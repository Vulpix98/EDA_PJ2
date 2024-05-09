#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "Header.h"

void main() 
{
	Grafo* grafo = NULL;
	//Aresta* aresta = NULL;

	grafo = createGraph();

	grafo = insertLastEdge(grafo, 53, 0, 0);
	grafo = insertLastEdge(grafo, 99, 0, 0);

	listar(grafo);
}



void listar(Grafo* grafo) 
{
	while (grafo != NULL)
	{
		
		//printf("vertices: %d   x: %d   y: %d\n", grafo->vertice, grafo->x, grafo->y);
		printf("vertices: %d", grafo->vertice);

		Aresta* aresta = grafo->aresta;
		while (aresta != NULL)
		{
			printf(" aresta: %d ", aresta->valor);
			aresta = aresta->seguinte;
		}

		printf("\n");
		
		grafo = grafo->seguinte;
	}
}


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



Grafo* insertLastEdge(Grafo* grafo, int valor, int x, int y)
{
	Aresta* tempAresta = grafo->aresta;
	Aresta* novaAresta = malloc(sizeof(Aresta));

	// se o vertice nao tiver nenhum aresta, este vai receber endereçamento de memoria
	if (grafo->aresta == NULL)
	{
		grafo->aresta = novaAresta;
	}

	if (grafo == NULL) return (grafo);

	if ((grafo->x == x) && (grafo->y == y) )
	{
		while (tempAresta != NULL)
		{
			tempAresta = tempAresta->seguinte;
		}
			
		if (novaAresta != NULL)
		{
			tempAresta = novaAresta;

			novaAresta->valor = valor;
			novaAresta->seguinte = NULL;

			return (grafo);
		}
		else return (grafo);
		
	}
	else
	{
		grafo->seguinte = insertLastEdge(grafo->seguinte, valor, x, y);
		return (grafo);
	}
}