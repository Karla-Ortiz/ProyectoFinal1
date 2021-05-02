#pragma once
#include <iostream>
using namespace std;

class Persona{

//Atributos de clase Persona
protected: int id;
		 string nombres, apellidos, telefono, fechaingreso;
		 char genero;

//constructor
protected:
	Persona(){}
	Persona(string nombres, string apellidos, string telefono, string fechaingreso, int id, char genero) {
		this->nombres = nombres;
		this->apellidos = apellidos;
		this->telefono = telefono;
		this->fechaingreso = fechaingreso;
		this->id = id;
		this->genero = genero;
	}
};

