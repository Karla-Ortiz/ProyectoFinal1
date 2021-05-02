#pragma once
#include <iostream>
using namespace std;

class Puesto{

//Atributos de la clase Puesto
private: int id;
	   string puesto;

//Constructor
public: 
	Puesto(){}
	Puesto(int id, string puesto) {
		this->id = id;
		this->puesto = puesto;
	}

	//Metodos setter
	void setId(int i) {
		id = i;
	}
	void setPuesto(string p) {
		puesto = p;
	}

	//Metodos getter
	int getId() {
		return id;
	}
	string getPuesto() {
		return puesto;
	}
};

