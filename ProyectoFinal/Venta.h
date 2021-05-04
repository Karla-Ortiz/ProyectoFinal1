#pragma once
#include <iostream>
using namespace std;

class Venta{
//Atributos de la clase Venta
private: string idVenta, nofac, serie, fechafac, cliente, empleado, fechaingreso;

//Constructor
public:
	Venta(){}
	Venta(string idVenta,string nofac, string serie, string fechafac, string cliente, string empleado, string fechaingreso ) {
		this->idVenta = idVenta;
		this->nofac = nofac;
		this->serie = serie;
		this->fechafac = fechafac;
		this->cliente = cliente;
		this->empleado = empleado;
		this->fechaingreso = fechaingreso;
	}
};

