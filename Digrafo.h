#ifndef DIGRAFO_H
#define DIGRAFO_H

#include <list>
#include <iterator>
#include <iostream>

using std::list;
using std::cout;
using std::endl;

class Digrafo {
private:
	int vertices; // numero de vertices en este digrafo
	int aristas; // numero de aristas en este digrafo
	list<int> *adyacentes;
public:
	Digrafo(); // constructor
	Digrafo(const Digrafo &otro); // copy constructor
	~Digrafo(); // destructor
	int getVertices() const; // obtener el numero de vertices
	void setVertices(int vertices); // establecer el numero de vertices
	int getAristas() const; // obtener el numero de aristas
	list<int> getAdyacentes(int v) const; // obtener la lista de adyacentes
	void agregarArista(int v, int w); // agregar la arista v-w
	void imprimir(); // imprimir el grafo
};

Digrafo::Digrafo() : vertices(0), aristas(0), adyacentes(nullptr) {
// constructor vacio
}

Digrafo::Digrafo(const Digrafo &otro) {
	vertices = otro.vertices;
	aristas = otro.aristas;
	if (vertices == 0) {
		adyacentes = nullptr;
	}
	else {
		adyacentes = new list<int>[vertices];
		for (int i = 0; i < vertices; i++) {
			list<int>::iterator it;
			for (it = otro.adyacentes[i].begin(); it != otro.adyacentes[i].end(); it++)
				adyacentes[i].push_back(*it);
		}
	}
}

Digrafo::~Digrafo() {
	if (adyacentes != nullptr) {
		delete[] adyacentes;
	}
}

int Digrafo::getVertices() const {
	return vertices;
}

void Digrafo::setVertices(int vertices) {
	if (this->vertices == 0) {
		this->vertices = vertices;
		adyacentes = new list<int>[vertices];
	}	
}

int Digrafo::getAristas() const {
	return aristas;
}

void Digrafo:: agregarArista(int v, int w) {
	adyacentes[v].push_front(w);
	aristas++;
}
list<int> Digrafo::getAdyacentes(int v) const {
	return adyacentes[v];
}

void Digrafo:: imprimir() {
	for (int i = 0; i < vertices; i++) {
		cout << i << ": ";
		list<int>::iterator it;
		for (it = adyacentes[i].begin(); it != adyacentes[i].end(); it++)
			cout << *it <<  ' ';
		cout << endl;
	}
}
#endif // !DIGRAFO_H
