#pragma once
#include "Persona.h"
class Empleado : Persona{

//Atributos de clase Empleado
private: string direccion, dpi, fechanac, puesto, fechainilab;

//Constructor
public:
	Empleado(){}
	Empleado(string direccion, string dpi, string fechanac, string puesto, string fechainilab,
		string nombres, string apellidos, string telefono, string fechaingreso, int id, char genero) 
		: Persona(nombres, apellidos, telefono, fechaingreso, id, genero){
		this->direccion = direccion;
		this->dpi = dpi;
		this->fechanac = fechanac;
		this->puesto = puesto;
		this->fechainilab = fechainilab;
	}

	//Metodos setter
	void setDireccion(string dir) {
		direccion = dir;
	}
	void setDpi(string dato) {
		dpi = dato;
	}
	void setFechanac(string fn) {
		fechanac = fn;
	}
	void setPuesto(string pues) {
		puesto = pues;
	}
	void setFechaIniLab(string fechil) {
		fechainilab = fechil;
	}
	void setNombres(string nom) {
		nombres = nom;
	}
	void setApellidos(string ape) {
		apellidos = ape;
	}
	void setTelefono(string tel) {
		telefono = tel;
	}
	void setFechaing(string fechin) {
		fechaingreso = fechin;
	}
	void setId(int idCliente) {
		id = idCliente;
	}
	void setGenero(char gen) {
		genero = gen;
	}

	//Metodos getter
	string getDireccion() {
		return direccion;
	}
	string getDpi() {
		return dpi;
	}
	string getFechanac() {
		return fechanac;
	}
	string getPuesto() {
		return puesto;
	}
	string getFechainilab() {
		return fechainilab;
	}
	string getNombres() {
		return nombres;
	}
	string getApellidos() {
		return apellidos;
	}
	string getTelefono() {
		return telefono;
	}
	string getFechaing() {
		return fechaingreso;
	}
	int getIdcliente() {
		return id;
	}
	char getGenero() {
		return genero;
	}
};

