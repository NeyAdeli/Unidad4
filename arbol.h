#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;

class ArbolBinarioBusqueda; // Arbol binario de busqueda

class NodoArbol {
	friend class ArbolBinarioBusqueda;
	private:
	string clave;		// Clave de busqueda
	int valor;			// Valor correspondiente a la clave
	NodoArbol *izq;	// Hijo izquierdo de este nodo
	NodoArbol *der;	// Hijo derecho de este nodo

	public:
		NodoArbol(string clave, int valor) : clave(clave), valor(valor), izq(0), der(0) {
			// constructor vacio
		}
};

class ArbolBinarioBusqueda {
	private:
		NodoArbol *raiz;		// Raiz del arbol binario de busqueda
		int numeroNodos;		// Numero de nodos en el arbol
		void auxiliarPoner(NodoArbol *&raizSubarbol, string clave, int valor);
		void auxiliarDestruir(NodoArbol *raizSubarbol);
		void auxiliarBorrar(NodoArbol *&raizSubarbol, string clave);
		void auxiliarEnOrden(NodoArbol *raizSubarbol, vector<string> &v);
		void auxiliarCopiar(NodoArbol *raizSubarbol);
		NodoArbol *desvincularMinimo(NodoArbol *&raizSubarbol);
	public:
		ArbolBinarioBusqueda(); 	// Constructor
		~ArbolBinarioBusqueda(); 	// Destructor
		ArbolBinarioBusqueda(const ArbolBinarioBusqueda &otro); // Constructor de copia
		int obtener(string clave); 	// Obtener el valor asociado a una clave
		void poner(string clave, int valor); // Agregar un par clave-valor al arbol
		bool contiene(const string &clave); // Verificar si la clave es parte del arbol
		void borrar(string clave); 	// Eliminar una clave (y su valor) del arbol
		bool estavacio();			// Verificar si el arbol esta vacio
		bool tamano();				// Cantidad de nodos del arbol
		vector<string> claves(); 	// Vector de las claves del arbol
};

// Verificar si la clave es parte del arbol
bool ArbolBinarioBusqueda::contiene(const string &clave) {
return this->obtener(clave) == -1;
}

// Obtener el valor asociado con una clave
int ArbolBinarioBusqueda::obtener(string clave) {
	NodoArbol *nodoActual = this->raiz;
	while (nodoActual != 0) {
		if (clave < nodoActual->clave)
			nodoActual = nodoActual->izq;
		else if (clave > nodoActual->clave)
			nodoActual = nodoActual->der;
		else
	return nodoActual->valor;
	}
	return -1;
}

// Agregar un par clave-valor al arbol
void ArbolBinarioBusqueda::poner(string clave, int valor) {
	this->auxiliarPoner(this->raiz, clave, valor);
}

// Metodo auxiliar para agregar un par clave-valor al arbol (metodo auxiliar)
void ArbolBinarioBusqueda::auxiliarPoner(NodoArbol *&raizSubarbol, string clave, int valor) {
	if (raizSubarbol == 0) {
	raizSubarbol = new NodoArbol(clave, valor);
	this->numeroNodos += 1;
	return;
}
	if (clave < raizSubarbol->clave)
		this->auxiliarPoner(raizSubarbol->izq, clave, valor);
	else if (clave > raizSubarbol->clave)
		this->auxiliarPoner(raizSubarbol->der, clave, valor);
	else
		raizSubarbol->valor = valor;
}

// Vector de las claves del arbol (recorrido en orden)
void ArbolBinarioBusqueda::auxiliarEnOrden (NodoArbol *raizSubarbol, vector<string> &v) {
	if (raizSubarbol == 0)
		return;
	auxiliarEnOrden(raizSubarbol->izq, v);
	v.push_back(raizSubarbol->clave);
	auxiliarEnOrden(raizSubarbol->der, v);
}

// Metodo auxiiar para obtener un vector de las claves del arbol (recorrido en orden)
vector<string> ArbolBinarioBusqueda::claves() {
	vector<string> v;
	this->auxiliarEnOrden(this->raiz, v);
	return v;
}

// Borra los enlaces al nodo min de un arbol y devuelve un puntero a ese nodo
NodoArbol * ArbolBinarioBusqueda::desvincularMinimo (NodoArbol *&raizSubarbol) {
	if (raizSubarbol == 0)
		return 0;
	
	if (raizSubarbol->izq == 0) {
		NodoArbol *min = raizSubarbol;
		raizSubarbol = raizSubarbol->der;
		return min;
	} else {
		this->desvincularMinimo(raizSubarbol->izq);
	}
}

// Remueve la clave (y su valor asociado) del arbol
void ArbolBinarioBusqueda::borrar(string clave) {
	this->auxiliarBorrar(this->raiz, clave);
}
// Metodo auxiliar que remueve la clave (y su valor asociado) del arbol
void ArbolBinarioBusqueda::auxiliarBorrar(NodoArbol *&raizSubarbol, string clave) {
	if (raizSubarbol == 0)								// la clave no existe, no hacer nada
	return;
	
	if (clave < raizSubarbol->clave)					// buscar la clave
		this->auxiliarBorrar(raizSubarbol->izq, clave);
	else if (clave > raizSubarbol->clave)
	this->auxiliarBorrar(raizSubarbol->der, clave);
	else {
		NodoArbol *temp = raizSubarbol;
		if (raizSubarbol->der == 0)							// sin hijo derecho
			raizSubarbol = raizSubarbol->izq;
		else if (raizSubarbol->izq == 0)					// sin hijo izquierdo
			raizSubarbol = raizSubarbol->der;
		else {
			raizSubarbol = desvincularMinimo (raizSubarbol->der);	// reemplaza con sucesor y actualiza enlaces
			raizSubarbol->der = temp->der;
			raizSubarbol->izq = temp->izq;
		}
		delete temp;										// libera la memoria
		this->numeroNodos -= 1;
	}
}

