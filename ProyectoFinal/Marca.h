#pragma once
#include "ConexionDB.h"
#include <string>
#include <iostream>
using namespace std;

class Marca{
//Atributos de la clase Marca
private:
	   string marca,id;
	   
//Constructor
public:
	Marca() {}
	Marca(string id, string marca) {
		this->id = id;
		this->marca = marca;
	}

	void dataMarcas() {
		int q_estado;
		ConexionDB con = ConexionDB();
		MYSQL_ROW fila;
		MYSQL_RES* res;
		con.abrirConexion();
		if (con.getConectar()) {
			string query = "SELECT * FROM MARCAS";
			const char* c = query.c_str();
			q_estado = mysql_query(con.getConectar(), c);
			if (!q_estado) {
				res = mysql_store_result(con.getConectar());
				cout << "\n\n\t**************** MARCAS *******************" << endl;
				cout << "\tID    |  MARCA\n" << endl;
				while (fila = mysql_fetch_row(res)) {
					cout << "\t" << fila[0] << " | " << fila[1] << endl;
				}
			}
		}
		else {
			cout << "\n\n\t -- Error en conexion --" << endl;
		}
		con.cerrarConexion();
	}

	void crearMarca() {
		int q_estado;
		cin.ignore();
		cout << "\tIngrese la marca: ";
		getline(cin, marca);
		ConexionDB con = ConexionDB();
		con.abrirConexion();
		if (con.getConectar()) {
			string query = "INSERT INTO MARCAS(marca) VALUES ('" + marca + "')";
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

	void modificarMarca() {
		int q_estado;
		cout << "\tIngrese el id del proveedor que desea modificar: ";
		cin >> id;
		visualizarMarca();
		cin.ignore();
		cout << "\n\tIngrese marca: ";
		getline(cin, marca);
		ConexionDB con = ConexionDB();
		con.abrirConexion();
		if (con.getConectar()) {
			string query = "UPDATE MARCAS SET marca='" + marca + "' WHERE idmarca=" + id;
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

	void deleteMarca() {
		int q_estado;
		ConexionDB con = ConexionDB();
		con.abrirConexion();
		if (con.getConectar()) {
			string query = "DELETE FROM MARCAS WHERE idmarca=" + id;
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

	void eliminarMarca() {
		char conf;
		cout << "\tIngrese el id de la marca a eliminar: ";
		cin >> id;
		visualizarMarca();
		cout << "\n\tSeguro que desea eliminar el registro. Esta operacion no se puede revertir (SI = s / No = n): ";
		cin >> conf;
		if (conf == 's') {
			deleteMarca();
		}
		else {
			cout << "\n\tRegisto no eliminado" << endl;;
		}
	}

	void visualizarMarca() {
		int q_estado;
		ConexionDB con = ConexionDB();
		MYSQL_ROW fila;
		MYSQL_RES* res;
		con.abrirConexion();
		if (con.getConectar()) {
			string query = "SELECT * FROM MARCAS where IDMARCA=" + id;
			const char* c = query.c_str();
			q_estado = mysql_query(con.getConectar(), c);
			if (!q_estado) {
				res = mysql_store_result(con.getConectar());
				cout << "\n\n\t**************** MARCAS *******************" << endl;
				cout << "\tID    |  MARCA\n" << endl;
				while (fila = mysql_fetch_row(res)) {
					cout << "\t" << fila[0] << " | " << fila[1] << endl;
					id = (string)fila[0];
					marca = fila[1];
				}
			}
		}
		else {
			cout << "\n\n\t -- Error en conexion --" << endl;
		}
		con.cerrarConexion();
	}
};

