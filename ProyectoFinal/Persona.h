#pragma once
#include <iostream>
using namespace std;

class Persona{

//Atributos de clase Persona
protected: 
		 string nombres, apellidos, telefono, fechaingreso,id;
		 char genero;

//constructor
protected:
	Persona(){}
	Persona(string nombres, string apellidos, string telefono, string fechaingreso, string id, char genero) {
		this->nombres = nombres;
		this->apellidos = apellidos;
		this->telefono = telefono;
		this->fechaingreso = fechaingreso;
		this->id = id;
		this->genero = genero;
	}
};

