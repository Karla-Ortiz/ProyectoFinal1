#pragma once
#include <iostream>
#include "ConexionDB.h"
using namespace std;

class Puesto{

//Atributos de la clase Puesto
private: string id, puesto;

//Constructor
public: 
	Puesto(){}
	Puesto(string id, string puesto) {
		this->id = id;
		this->puesto = puesto;
	}

	void dataPuestos() {
		int q_estado;
		ConexionDB con = ConexionDB();
		MYSQL_ROW fila;
		MYSQL_RES* res;
		con.abrirConexion();
		if (con.getConectar()) {
			string query = "SELECT * FROM PUESTOS";
			const char* c = query.c_str();
			q_estado = mysql_query(con.getConectar(), c);
			if (!q_estado) {
				res = mysql_store_result(con.getConectar());
				cout << "\n\n\t**************** PUESTOS *******************" << endl;
				cout << "\tID    |  PUESTO\n" << endl;
				while (fila = mysql_fetch_row(res)) {
					cout << "\t" << fila[0] << " | " << fila[1] << endl;
				}
			}
		}
		else {
			cout << " -- Error en conexion --" << endl;
		}
		con.cerrarConexion();
	}

	void crearPuesto() {
		int q_estado;
		ConexionDB con = ConexionDB();
		con.abrirConexion();
		if (con.getConectar()) {
			string query = "INSERT INTO PUESTOS(PUESTO) VALUES ('" + puesto +"')";
			const char* i = query.c_str();
			q_estado = mysql_query(con.getConectar(), i);
			if (!q_estado) {
				cout << " --- Ingreso exitoso ---" << endl;
			}
			else {
				cout << " --- Error al ingresar la informacion ---" << endl;
			}
		}
		else {
			cout << " --- Error en conexion ---" << endl;
		}
		con.cerrarConexion();
	}

	void modificarPuesto() {
		int q_estado;
		ConexionDB con = ConexionDB();
		con.abrirConexion();
		if (con.getConectar()) {
			string query = "UPDATE PUESTOS SET PUESTO='" + puesto + "' WHERE IDPUESTO=" + id;
			const char* i = query.c_str();
			q_estado = mysql_query(con.getConectar(), i);
			if (!q_estado) {
				cout << " --- Modificacion exitoso ---" << endl;
			}
			else {
				cout << " --- Error al modificar la informacion ---" << endl;
			}
		}
		else {
			cout << " --- Error en conexion ---" << endl;
		}
		con.cerrarConexion();
	}

	void eliminarPuesto() {
		int q_estado;
		ConexionDB con = ConexionDB();
		con.abrirConexion();
		if (con.getConectar()) {
			string query = "DELETE FROM PUESTOS WHERE IDPUESTO=" + id;
			const char* i = query.c_str();
			q_estado = mysql_query(con.getConectar(), i);
			if (!q_estado) {
				cout << " --- Eliminacion exitosa ---" << endl;
			}
			else {
				cout << " --- Error al eliminar la informacion ---" << endl;
			}
		}
		else {
			cout << " --- Error en conexion ---" << endl;
		}
		con.cerrarConexion();
	}
};

