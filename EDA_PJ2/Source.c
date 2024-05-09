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

	listar(grafo);
}



void listar(Grafo* grafo) 
{
	while (grafo != NULL)
	{
		/*
		Future implemention

		Aresta* aresta = grafo->aresta;
		while (aresta != NULL)
		{
			printf("%d ", aresta->valor);
			aresta = aresta->seguinte;
		}*/
		printf("vertices: %d\n", grafo->vertice);
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
	int valor;

	// Opening file in reading mode
	fp = fopen("matriz.txt", "r");

	if (fp != NULL) 
	{
		// Read each line of the file
		while (fgets(line, sizeof line, fp) != NULL /*&& row < ROWS*/) {
			//new line, set to default (null and zero)
			//linha = NULL;
			
			// Tokenize the line by semicolons
			token = strtok(line, ";");

			while (token != NULL /*&& col < COLS*/) {
				// Convert token to integer and store in the matrix
				valor = atoi(token);

				grafo = insertVertex(grafo, valor, aresta);
				
				token = strtok(NULL, ";");

			}			
		}
	}
	else printf("file can't be opened \n"); //fail to open file

	// Closing the file
	fclose(fp);


	return (grafo);
}



Grafo* insertVertex(Grafo* grafo, int vertice, Aresta* aresta) 
{
	if (grafo == NULL) 
	{
		Grafo* novoGrafo = malloc(sizeof(Grafo));
		if (novoGrafo != NULL)
		{
			novoGrafo->vertice = vertice;
			novoGrafo->aresta = aresta;
			novoGrafo->seguinte = NULL;
			
			return (novoGrafo);
		}
		else return (grafo);
	}
	else
	{
		grafo->seguinte = insertVertex(grafo->seguinte, vertice, aresta);
		return (grafo);
	}
}