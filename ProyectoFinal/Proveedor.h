#pragma once
#include "ConexionDB.h"
#include <iostream>
using namespace std;

class Proveedor{
//Atributos de la clase Proveedor
private:
	   string id,proveedor, nit, direccion, telefono;

//Constructor
public:
	Proveedor(){}
	Proveedor(string id, string proveedor, string nit, string direccion, string telefono) {
		this->id = id;
		this->proveedor = proveedor;
		this->nit = nit;
		this->direccion = direccion;
		this->telefono = telefono;
	}

	void dataProveedor() {
		int q_estado;
		ConexionDB con = ConexionDB();
		MYSQL_ROW fila;
		MYSQL_RES* res;
		con.abrirConexion();
		if (con.getConectar()) {
			string query = "SELECT * FROM PROVEEDORES";
			const char* c = query.c_str();
			q_estado = mysql_query(con.getConectar(), c);
			if (!q_estado) {
				res = mysql_store_result(con.getConectar());

				while (fila = mysql_fetch_row(res)) {
					cout << fila[0] << "," << fila[1] << endl;
				}
			}
		}
		else {
			cout << " -- Error en conexion --" << endl;
		}
		con.cerrarConexion();
	}

	void crearProveedor() {
		int q_estado;
		ConexionDB con = ConexionDB();
		con.abrirConexion();
		if (con.getConectar()) {
			string query = "INSERT INTO PROVEEDORES(proveedor,nit,direccion,telefono) VALUES ('" + proveedor + "','" + nit + "','" + direccion + "','" + telefono + "')";
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

	void modificarProveedor() {
		int q_estado;
		ConexionDB con = ConexionDB();
		con.abrirConexion();
		if (con.getConectar()) {
			string query = "UPDATE PROVEEDORES SET proveedor='" + proveedor + "',nit='" + nit + "',direccion='" + direccion + "',telefono='" + telefono + "' WHERE idProveedor=" + id;
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

	void eliminarProveedor() {
		int q_estado;
		ConexionDB con = ConexionDB();
		con.abrirConexion();
		if (con.getConectar()) {
			string query = "DELETE FROM PROVEEDORES WHERE idProveedor=" + id;
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

