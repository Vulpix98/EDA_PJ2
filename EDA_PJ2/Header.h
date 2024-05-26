// structs
typedef struct registo
{
    int valor;
    struct registo* seguinte;
} Aresta;

typedef struct registo2
{
    int vertice;
    int x;
    int y;
    Aresta* aresta;
    struct registo2* seguinte;
} Grafo;




Aresta* insertEdge(Aresta* aresta, int valor);
Grafo* insertLastEdge(Grafo* grafo, int valor, int x, int y);



Grafo* insertEdgeToVertex(Grafo* grafo, int orientacao);


Grafo* testEdgeRight(Grafo* grafo, Grafo* grf1, Grafo* grf2);
Grafo* testEdgeLeft(Grafo* grafo, Grafo* grf1, Grafo* grf2);
Grafo* testEdgeUp(Grafo* grafo, Grafo* grf1, Grafo* grf2);
Grafo* testEdgeDown(Grafo* grafo, Grafo* grf1, Grafo* grf2);

Grafo* insertLastVertex(Grafo* grafo, int vertice, int x, int y, Aresta* aresta);
Grafo* createGraph();
Grafo* deleteEdge(Grafo* grafo);
Grafo* selectVertexMenu(Grafo* grafo);
Grafo* removeVertex(Grafo* grafo, int vertice);
Grafo* RemoveSingleEdge(Grafo* grafo, int x, int y);
void maxSumRecursive(Grafo* node, int* xSelected, int* ySelected, int currentSum, int* maxSum);
int findMaxSum(Grafo* grafo);


Grafo* menuOrientacao(Grafo* grafo);


int procuraProfundidade(Grafo* grafo, int vertice, int* visitado, int* emProcessamento);
Grafo* encontrarVertice(Grafo* grafo, int vertice);


int calcularSomaCaminho(Grafo* grafo, int verticeOrigem, int verticeDestino);
int calcularSomaRecursiva(Grafo* grafo, int verticeAtual, int verticeDestino, int* soma, int* visitado);


void menu(Grafo* grafo);
void listar(Grafo* grafo);