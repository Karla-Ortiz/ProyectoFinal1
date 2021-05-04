#pragma once
#include <iostream>
using namespace std;

class Producto{
//Atributos de la clase Producto
private: string idProd, prod, marca, desc, imagen, precioC, precioV, existencia, fechaingreso;

//Constructor
public:
	Producto(){}
	Producto(string idProd, string prod, string marca, string desc, string imagen, string precioC, string precioV, string existencia, string fechaingreso) {
		this->idProd = idProd;
		this->prod = prod;
		this->marca = marca;
		this->desc = desc;
		this->imagen = imagen;
		this->precioC = precioC;
		this->precioV = precioV;
		this->existencia = existencia;
		this->fechaingreso = fechaingreso;
	}
};

