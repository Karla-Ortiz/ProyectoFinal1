#pragma once
#include "ConexionDB.h"
#include <string>
#include <stdio.h>
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
				cout << "\n\n\t**************** PROVEEDORES *******************" << endl;
				cout << "\tID    |  PROVEEDOR   | NIT | DIRECCION | TELEFONO\n" << endl;
				while (fila = mysql_fetch_row(res)) {
					cout << "\t" << fila[0] << " | " << fila[1] << " | " << fila[2] << " | " << fila[3] << " | " << fila[4] << " | "  << endl;
				}
			}
		}
		else {
			cout << "\n\n\t -- Error en conexion --" << endl;
		}
		con.cerrarConexion();
	}

	void crearProveedor() {
		int q_estado;
		cin.ignore();
		cout << "\tIngrese proveedor: ";
		getline(cin, proveedor);
		cout << "\tIngrese nit: ";
		cin >> nit;
		cin.ignore();
		cout << "\tIngrese direccion: ";
		getline(cin, direccion);
		cout << "\tIngrese telefono: ";
		cin >> telefono;
		ConexionDB con = ConexionDB();
		con.abrirConexion();
		if (con.getConectar()) {
			string query = "INSERT INTO PROVEEDORES(proveedor,nit,direccion,telefono) VALUES ('" + proveedor + "','" + nit + "','" + direccion + "','" + telefono + "')";
			const char* i = query.c_str();
			q_estado = mysql_query(con.getConectar(), i);
			if (!q_estado) {
				cout << "\n\n\t --- Ingreso exitoso ---" << endl;
			}
			else {
				cout << "\n\n\t --- Error al ingresar la informacion ---" << endl;
			}
		}
		else {
			cout << "\n\n\t --- Error en conexion ---" << endl;
		}
		con.cerrarConexion();
	}

	void modificarProveedor() {
		int q_estado;
		string dato;
		cout << "\tIngrese el id del proveedor que desea modificar: ";
		cin >> id;
		visualizarProv();
		cout << "\n\tIngrese datos nuevos (si no desea cambiar un dato ingrese n)" << endl;
		cin.ignore();
		cout << "\tProveedor: ";
		getline(cin,dato);
		if (dato.compare("n")!=0) {
			proveedor = dato;
		}
		cout << "\tNit: ";
		cin >> dato;
		if (dato.compare("n") != 0) {
			nit = dato;
		}
		cin.ignore();
		cout << "\tDireccion: ";
		getline(cin,dato);
		if (dato.compare("n") != 0) {
			direccion = dato;
		}
		cout << "\tTelefono: ";
		cin >> dato;
		if (dato.compare("n") != 0) {
			telefono = dato;
		}
		ConexionDB con = ConexionDB();
		con.abrirConexion();
		if (con.getConectar()) {
			string query = "UPDATE PROVEEDORES SET proveedor='" + proveedor + "',nit='" + nit + "',direccion='" + direccion + "',telefono='" + telefono + "' WHERE idProveedor=" + id;
			const char* i = query.c_str();
			q_estado = mysql_query(con.getConectar(), i);
			if (!q_estado) {
				cout << "\n\n\t --- Modificacion exitoso ---" << endl;
			}
			else {
				cout << "\n\n\t --- Error al modificar la informacion ---" << endl;
			}
		}
		else {
			cout << "\n\n\t --- Error en conexion ---" << endl;
		}
		con.cerrarConexion();
	}

	void deleteProv() {
		int q_estado;
		ConexionDB con = ConexionDB();
		con.abrirConexion();
		if (con.getConectar()) {
			string query = "DELETE FROM PROVEEDORES WHERE idProveedor=" + id;
			const char* i = query.c_str();
			q_estado = mysql_query(con.getConectar(), i);
			if (!q_estado) {
				cout << "\n\n\t --- Eliminacion exitosa ---" << endl;
			}
			else {
				cout << "\n\n\t --- Error al eliminar la informacion ---" << endl;
			}
		}
		else {
			cout << "\n\n\t --- Error en conexion ---" << endl;
		}
		con.cerrarConexion();
	}

	void eliminarProveedor() {
		char conf;
		cout << "\tIngrese el id del proveedor a eliminar: ";
		cin >> id;
		visualizarProv();
		cout << "\n\tSeguro que desea eliminar el registro. Esta operacion no se puede revertir (SI = s / No = n): ";
		cin >> conf;
		if (conf == 's') {
			deleteProv();
		}
		else {
			cout << "\n\tRegisto no eliminado" << endl;;
		}
	}

	void visualizarProv() {
		int q_estado;
		ConexionDB con = ConexionDB();
		MYSQL_ROW fila;
		MYSQL_RES* res;
		con.abrirConexion();
		if (con.getConectar()) {
			string query = "SELECT * FROM PROVEEDORES WHERE IDPROVEEDOR=" + id;
			const char* c = query.c_str();
			q_estado = mysql_query(con.getConectar(), c);
			if (!q_estado) {
				res = mysql_store_result(con.getConectar());
				cout << "\n\n\t**************** PROVEEDOR "<<id<<" *******************" << endl;
				cout << "\tID    |  PROVEEDOR   | NIT | DIRECCION | TELEFONO\n" << endl;
				while (fila = mysql_fetch_row(res)) {
					cout << "\t" << fila[0] << " | " << fila[1] << " | " << fila[2] << " | " << fila[3] << " | " << fila[4] << " | " << endl;
					id = (string)fila[0];
					proveedor = fila[1];
					nit = fila[2];
					direccion = fila[3];
					telefono = fila[4];
				}
			}
		}
		else {
			cout << "\n\n\t -- Error en conexion --" << endl;
		}
		con.cerrarConexion();
	}
};

