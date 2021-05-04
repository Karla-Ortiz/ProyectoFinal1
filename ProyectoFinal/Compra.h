#pragma once
#include <iostream>
using namespace std;
class Compra{
//Atributos de clase Compra
private: string fechaorden, fechaingreso, prov, idCompra, orden;

//Constructor
public: 
	Compra(){}
	Compra(string idCompra,string orden, string fechaorden, string fechaingreso, string prov) {
		this->idCompra = idCompra;
		this->orden = orden;
		this->fechaorden = fechaorden;
		this->fechaingreso = fechaingreso;
		this->prov = prov;
	}
};

