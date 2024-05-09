// structs
typedef struct registo
{
    int valor;
    struct registo* seguinte;
} Aresta;

typedef struct registo2
{
    int vertice;
    Aresta* aresta;
    struct registo2* seguinte;
} Grafo;



Grafo* insertVertex(Grafo* grafo, int vertice, Aresta* aresta);
Grafo* createGraph();
