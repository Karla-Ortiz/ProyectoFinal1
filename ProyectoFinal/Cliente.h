#pragma once
#include "Persona.h"
using namespace std;

class Cliente : Persona{

//Atributos de clase Cliente
private: string nit, email;

//constructor
public: 
	Cliente(){}
	Cliente(string nit, string email, string nombres, string apellidos, 
		string telefono, string fechaingreso, int id, char genero) : 
		Persona(nombres, apellidos, telefono, fechaingreso,id,genero){
		this->nit = nit;
		this->email = email;
	}

	//Métodos setter
	void setNit(string n) {
		nit = n;
	}
	void setEmail(string em) {
		email = em;
	}
	void setNombres(string nom) {
		nombres = nom;
	}
	void setApellidos(string ape) {
		apellidos = ape;
	}
	void setTelefono(string tel) {
		telefono =  tel;
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
	string getNit() {
		return nit;
	}
	string getEmail() {
		return email;
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

