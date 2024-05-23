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


Grafo* menuOrientacao(Grafo* grafo);


void menu(Grafo* grafo);
void listar(Grafo* grafo);