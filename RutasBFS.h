#ifndef RUTA_BFS_H
#define RUTA_BFS_H
#include <limits>
#include <list>
#include <iterator>

#include "Digrafo.h"

using std::list;

class RutaBFS {
private:
	const int INFINITO = std:: numeric_limits <int>::max();
	int vertices; // numero de vertices del grafo origen
	bool *marcado; // marcado[v] - hay un camino entre s-u?
	int *aristaHacia; // aristatacia[v] - ultima arista en la ruta 5-v mas corta
	int *distanciaHacia; // distanciatacio[v] = longitud de la ruta s-v mas corta
	void bfs(const Digrafo &G, int s); // algoritmo BFS recursivo
public:
	RutaBFS(const Digrafo &G, int s); // constructor
	RutaBFS(const RutaBFS &otra); // copy constructor
	~RutaBFS(); // destructor
	bool existeCaminoHacia(int v);
	int getDistanciaHacia(int v);
	list <int> getRutaHacia(int v);
};

RutaBFS:: RutaBFS(const Digrafo &G, int s) {
	vertices = G.getVertices();
	marcado = new bool[vertices];
	distanciaHacia = new int[vertices];
	aristaHacia = new int[vertices];
	for (int v = 0; v < vertices; v++) {
		marcado[v] = false;
		distanciaHacia[v] = INFINITO;
	}	
	bfs(G, s);
}

void RutaBFS::bfs(const Digrafo &G, int s) {
	list<int> q;
	marcado[s] = true;
	distanciaHacia[s] = 0;
	q.push_back(s);
	while (!q.empty()) {
		int v = q.front();
		q.pop_front();
		list<int>::iterator it;
		list <int> ady = G.getAdyacentes(v);
		for (it = ady.begin(); it != ady.end(); it++) {
			int w = *it;
			if (! marcado[w]) {
				aristaHacia[w] = v;
				distanciaHacia[w] = distanciaHacia[v] + 1;
				marcado[w] = true;
				q.push_back(w);
			}
		}	
	}
}

RutaBFS::RutaBFS(const RutaBFS &otra) {
	vertices = otra.vertices;
	marcado = new bool[vertices];
	distanciaHacia = new int[vertices];
	aristaHacia = new int[vertices];
	for (int v = 0; v < vertices; v++) {
		marcado[v] = otra.marcado[v];
		distanciaHacia[v] = otra.distanciaHacia[v];
		aristaHacia[v] = otra.aristaHacia[v];
	}
}

RutaBFS::~RutaBFS() {
	delete[] marcado;
	delete[] distanciaHacia;
	delete[] aristaHacia;
}

bool RutaBFS::existeCaminoHacia(int v) {
	return marcado[v];
}

int RutaBFS::getDistanciaHacia(int v) {
	return distanciaHacia[v];
}

list<int> RutaBFS::getRutaHacia(int v) {
	list<int> ruta;
	if (existeCaminoHacia(v)) {
		int x;
		for (x = v; distanciaHacia[x] != 0; x = aristaHacia[x])  
			ruta.push_front(x);
		ruta.push_front(x);
	}
	return ruta;
}

#endif // !RUTA_BFS_H


