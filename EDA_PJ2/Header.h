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



Grafo* insertLastVertex(Grafo* grafo, int vertice, int x, int y, Aresta* aresta);
Grafo* createGraph();


void listar(Grafo* grafo);