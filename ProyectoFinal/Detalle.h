#pragma once
#include <iostream>
using namespace std;

class Detalle{
//Atributos clase Detalle
private: int id, idOpe, cantidad;
		 double precioU;
		 string producto;

//Constructor
public:
	Detalle(){}
	Detalle(int id, int idope,string producto, int cantidad, double precio) {
		this->id = id;
		this->idOpe = idope;
		this->producto = producto;
		this->cantidad = cantidad;
		precioU = precio;
	}

	//Metodos setter
	void setId(int i) {
		id = i;
	}
	void setIdOperacion(int idv) {
		idOpe = idv;
	}
	void setProd(string prod) {
		producto = prod;
	}
	void setCantidad(int cant) {
		cantidad = cant;
	}
	void setPrecioU(int prec) {
		precioU = prec;
	}

	//Metodos getter
	int getId() {
		return id;
	}
	int getIdOperacion() {
		return idOpe;
	}
	string getProd() {
		return producto;
	}
	int getCantidad() {
		return cantidad;
	}
	double getPrecioU() {
		return precioU;
	}
};

