#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <limits.h>
#include "Header.h"

void main() 
{
	Grafo* grafo = NULL;

	grafo = createGraph();

	// serve para testes
	//grafo = insertEdgeToVertex(grafo, 3);

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
	int maxSum;

	do
	{
		printf("1) Menu Principal\n\n");
		printf("1- Orientacao do grafo\n");
		printf("2- Listar\n");
		printf("3- Procura em profundidade!\n");
		printf("4- Soma dos valores dado um caminho!\n");
		printf("5- Selecionar vertice\n");
		printf("6- Encontrar soma maxima\n");
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

		case 4:
		{
			int verticeOrigem, verticeDestino;
			printf("Digite o vertice de origem: ");
			scanf("%d", &verticeOrigem);
			printf("Digite o vertice de destino: ");
			scanf("%d", &verticeDestino);

			int somaCaminho = calcularSomaCaminho(grafo, verticeOrigem, verticeDestino);
			if (somaCaminho != 0) {
				printf("A soma dos valores ao longo do caminho do vertice %d ao vertice %d e: %d\n\n", verticeOrigem, verticeDestino, somaCaminho);
			}
			else {
				printf("Nao existe um caminho entre os vertices de origem e destino.\n\n");
			}
			break;
		}
		case 5:
			grafo = selectVertexMenu(grafo);
			break;
		case 6:
			maxSum = findMaxSum(grafo);
			//printf("Maximum sum without repeating x/y coordinates: %d\n", maxSum);
			break;
			
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
		printf("0- Voltar ao menu principal\n\n");
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



Grafo* selectVertexMenu(Grafo* grafo)
{
	int x, y;
	int subOption;

	printf("Digite as coordenadas do vertice (x y): ");
	scanf("%d %d", &x, &y);

	Grafo* vertice = grafo;

	// Find the vertex x, y
	while (vertice != NULL && (vertice->x != x || vertice->y != y)) {
		vertice = vertice->seguinte;
	}

	if (vertice == NULL) {
		printf("Vertice nao encontrado.\n");
		return grafo;
	}

	do {
		printf("Vertice selecionado (%d, %d)\n", x, y);
		printf("1- Remover vertice\n");
		printf("2- Remover aresta\n");
		printf("0- Voltar\n\n");
		printf("Opcao: ");
		scanf("%d", &subOption);

		switch (subOption)
		{
		case 0:
			return grafo;

		case 1:
			grafo = removeVertex(grafo, x, y);
			return grafo;

		case 2:
			grafo = RemoveSingleEdge(grafo, x, y);
			break;

		default:
			printf("Valor invalido");
			break;
		}
	} while (subOption != 0);

	return grafo;
}


Grafo* RemoveSingleEdge(Grafo* grafo, int x, int y) {
	Grafo* current = grafo;

	// Find the vertex x, y
	while (current != NULL && (current->x != x || current->y != y)) {
		current = current->seguinte;
	}

	if (current == NULL) {
		printf("Vertice nao encontrado.\n");
		return grafo;
	}

	printf("Arestas conectadas ao vertice (%d, %d): ", x, y);
	Aresta* aresta = current->aresta;
	while (aresta != NULL) {
		printf("%d ", aresta->valor);
		aresta = aresta->seguinte;
	}
	printf("\n");

	int edgeToRemove;
	printf("Digite o valor da aresta a ser removida: ");
	scanf("%d", &edgeToRemove);

	// Remove the edge from the origin vertex
	Aresta* prevAresta = NULL;
	aresta = current->aresta;
	while (aresta != NULL) {
		if (aresta->valor == edgeToRemove) {
			if (prevAresta == NULL) {
				current->aresta = aresta->seguinte;
			}
			else {
				prevAresta->seguinte = aresta->seguinte;
			}
			free(aresta);
			printf("Aresta removida com sucesso.\n");
			break;
		}
		prevAresta = aresta;
		aresta = aresta->seguinte;
	}

	// Now remove the corresponding edge from the destination vertex
	Grafo* destVertex = grafo;
	while (destVertex != NULL && destVertex->vertice != edgeToRemove) {
		destVertex = destVertex->seguinte;
	}

	if (destVertex != NULL) {
		Aresta* destAresta = destVertex->aresta;
		Aresta* prevDestAresta = NULL;
		while (destAresta != NULL) {
			if (destAresta->valor == current->vertice) {
				if (prevDestAresta == NULL) {
					destVertex->aresta = destAresta->seguinte;
				}
				else {
					prevDestAresta->seguinte = destAresta->seguinte;
				}
				free(destAresta);
				printf("Aresta correspondente removida do vertice destino.\n");
				break;
			}
			prevDestAresta = destAresta;
			destAresta = destAresta->seguinte;
		}
	}

	return grafo;
}


Grafo* removeVertex(Grafo* grafo, int x, int y) {
	if (grafo == NULL) {
		return NULL;
	}

	Grafo* current = grafo;
	Grafo* prev = NULL;

	// Find the vertex to be removed
	while (current != NULL && (current->x != x || current->y != y)) {
		prev = current;
		current = current->seguinte;
	}

	// If the vertex is not found, return the graph as is
	if (current == NULL) {
		return grafo;
	}

	// Remove all edges pointing to this vertex
	Grafo* temp = grafo;
	while (temp != NULL) {
		Aresta* aresta = temp->aresta;
		Aresta* prevAresta = NULL;
		while (aresta != NULL) {
			if (aresta->valor == current->vertice) {
				if (prevAresta == NULL) {
					temp->aresta = aresta->seguinte;
				}
				else {
					prevAresta->seguinte = aresta->seguinte;
				}
				free(aresta);
				break;
			}
			prevAresta = aresta;
			aresta = aresta->seguinte;
		}
		temp = temp->seguinte;
	}

	// Remove the vertex and its edges
	if (prev == NULL) {
		grafo = current->seguinte;
	}
	else {
		prev->seguinte = current->seguinte;
	}

	Aresta* aresta = current->aresta;
	while (aresta != NULL) {
		Aresta* tempAresta = aresta;
		aresta = aresta->seguinte;
		free(tempAresta);
	}

	free(current);
	return grafo;
}

void maxSumRecursive(Grafo* node, int* xSelected, int* ySelected, int currentSum, int* maxSum, int* path, int* maxPath, int depth, int* maxDepth) {
	if (node == NULL) {
		if (currentSum > *maxSum) {
			*maxSum = currentSum;
			*maxDepth = depth;
			memcpy(maxPath, path, depth * sizeof(int));
		}
		return;
	}

	// Recursive call without selecting the current node
	maxSumRecursive(node->seguinte, xSelected, ySelected, currentSum, maxSum, path, maxPath, depth, maxDepth);

	// Recursive call with selecting the current node if x and y are not selected
	if (!xSelected[node->x] && !ySelected[node->y]) {
		xSelected[node->x] = 1;
		ySelected[node->y] = 1;
		path[depth] = node->vertice; // Add current node to the path
		maxSumRecursive(node->seguinte, xSelected, ySelected, currentSum + node->vertice, maxSum, path, maxPath, depth + 1, maxDepth);
		xSelected[node->x] = 0;
		ySelected[node->y] = 0;
	}
}

int findMaxSum(Grafo* grafo) {
	int maxSum = 0;
	int maxDepth = 0;

	// This assumes the graph can have up to 100 nodes on x and y axis
	int* xSelected = (int*)calloc(100, sizeof(int));
	int* ySelected = (int*)calloc(100, sizeof(int));

	// Allocate space for paths
	int* path = (int*)malloc(100 * sizeof(int)); // Assume max path length is 100
	int* maxPath = (int*)malloc(100 * sizeof(int));

	if (xSelected == NULL || ySelected == NULL || path == NULL || maxPath == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
		exit(1);
	}

	maxSumRecursive(grafo, xSelected, ySelected, 0, &maxSum, path, maxPath, 0, &maxDepth);

	// Print the maximum sum and the path
	printf("Maximum sum without repeating x/y coordinates: %d\n", maxSum);
	printf("Path taken: ");
	for (int i = 0; i < maxDepth; i++) {
		printf("%d ", maxPath[i]);
	}
	printf("\n\n");

	free(xSelected);
	free(ySelected);
	free(path);
	free(maxPath);

	return maxSum;
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
		if (procuraProfundidade(grafo, aresta->valor, visitado, emProcessamento))
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



// Função para calcular a Soma dado Caminho
int calcularSomaCaminho(Grafo* grafo, int verticeOrigem, int verticeDestino) {
	// Verifica se os vértices de origem e destino estão presentes no grafo
	Grafo* origem = encontrarVertice(grafo, verticeOrigem);
	Grafo* destino = encontrarVertice(grafo, verticeDestino);

	if (origem == NULL || destino == NULL) {
		printf("Pelo menos um dos vértices não foi encontrado no grafo.\n");
		return 0; // Retorna 0 se um dos vértices não for encontrado
	}

	// Array para marcar os vértices visitados durante a busca em profundidade
	int* visitado = (int*)calloc(100, sizeof(int)); // Assume no máximo 100 vértices
	if (visitado == NULL) {
		printf("Erro de alocação de memória.\n");
		return 0;
	}

	// Verifica se há um caminho entre os vértices de origem e destino usando busca em profundidade
	int* emProcessamento = (int*)calloc(100, sizeof(int)); // Array para marcar os vértices em processamento
	if (emProcessamento == NULL) {
		printf("Erro de alocação de memória.\n");
		free(visitado); // Libera a memória alocada para o array de visitados
		return 0;
	}

	int caminhoExiste = procuraProfundidade(grafo, verticeOrigem, visitado, emProcessamento);
	free(visitado); // Libera a memória alocada para o array de visitados
	free(emProcessamento); // Libera a memória alocada para o array de emProcessamento

	if (!caminhoExiste) {
		printf("Não existe um caminho entre os vértices de origem e destino.\n");
		return 0; // Retorna 0 se não há um caminho entre os vértices
	}

	// Realiza a soma dos valores ao longo do caminho
	int soma = 0;
	caminhoExiste = calcularSomaRecursiva(grafo, verticeOrigem, verticeDestino, &soma, visitado);

	if (!caminhoExiste) {
		printf("Erro ao calcular a soma do caminho.\n");
		return 0; // Retorna 0 se houver um erro ao calcular a soma do caminho
	}

	return soma; // Retorna a soma dos valores ao longo do caminho
}



// Função auxiliar para calcular a soma recursivamente
int calcularSomaRecursiva(Grafo* grafo, int verticeAtual, int verticeDestino, int* soma, int* visitado) {
	// Caso base: se o vértice atual for igual ao vértice de destino, a soma é concluída
	if (verticeAtual == verticeDestino) {
		return 1; // Indica que a soma foi concluída com sucesso
	}

	// Marca o vértice atual como visitado
	visitado[verticeAtual] = 1;

	// Percorre as arestas do vértice atual
	Grafo* v = encontrarVertice(grafo, verticeAtual);
	if (!v) return 0; // Retorna 0 se o vértice não for encontrado

	Aresta* aresta = v->aresta;
	while (aresta) {
		// Verifica se o vértice adjacente ainda não foi visitado
		int caminhoExiste = !visitado[aresta->valor];
		if (caminhoExiste) {
			// Incrementa a soma com o valor da aresta
			*soma += aresta->valor;

			// Realiza a chamada recursiva para o vértice adjacente
			caminhoExiste = calcularSomaRecursiva(grafo, aresta->valor, verticeDestino, soma, visitado);
			if (caminhoExiste) {
				return 1; // Se um caminho foi encontrado, retorna 1
			}

			// Se não encontrar um caminho a partir deste vértice adjacente, subtrai o valor da aresta da soma
			*soma -= aresta->valor;
		}
		aresta = aresta->seguinte; // Move para a próxima aresta
	}

	return 0; // Retorna 0 se não encontrar um caminho
}