#pragma once
#include <iostream>
using namespace std;

class Proveedor{
//Atributos de la clase Proveedor
private: int idProv;
	   string proveedor, nit, direccion, telefono;

//Constructor
public:
	Proveedor(){}
	Proveedor(int idProv, string proveedor, string nit, string direccion, string telefono) {
		this->idProv = idProv;
		this->proveedor = proveedor;
		this->nit = nit;
		this->direccion = direccion;
		this->telefono = telefono;
	}

	//Metodos setter
	void setIdprov(int idp) {
		idProv = idp;
	}
	void setProv(string prov) {
		proveedor = prov;
	}
	void setNit(string n) {
		nit = n;
	}
	void setDireccion(string dir) {
		direccion = dir;
	}
	void setTelefono(string tel) {
		telefono = tel;
	}

	//Metodos getter
	int getIdprov() {
		return idProv;
	}
	string getProv() {
		return proveedor;
	}
	string getNit() {
		return nit;
	}
	string getDireccion() {
		return direccion;
	}
	string getTelefono() {
		return telefono;
	}
};

