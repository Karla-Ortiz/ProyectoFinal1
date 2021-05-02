#pragma once
#include <iostream>
using namespace std;

class Marca{
//Atributos de la clase Marca
private: int id;
	   string marca;
	   
//Constructor
public:
	Marca() {}
	Marca(int id, string marca) {
		this->id = id;
		this->marca = marca;
	}

	//Metodos setter
	void setId(int i) {
		id = i;
	}
	void setMarca(string m) {
		marca = m;
	}

	//Metodos getter
	int getId() {
		return id;
	}
	string getMarca() {
		return marca;
	}
};

