#pragma once
#include "ConexionDB.h"
#include "Persona.h"
using namespace std;

class Cliente : Persona{

//Atributos de clase Cliente
private: string nit, email;

//constructor
public: 
	Cliente(){}
	Cliente(string nit, string email, string nombres, string apellidos, 
		string telefono, string fechaingreso, string id, char genero) : 
		Persona(nombres, apellidos, telefono, fechaingreso,id,genero){
		this->nit = nit;
		this->email = email;
	}

	void dataClientes() {
		int q_estado;
		ConexionDB con = ConexionDB();
		MYSQL_ROW fila;
		MYSQL_RES* res;
		con.abrirConexion();
		if (con.getConectar()) {
			string query = "SELECT * FROM CLIENTES";
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

	void crearCliente() {
		int q_estado;
		ConexionDB con = ConexionDB();
		con.abrirConexion();
		if (con.getConectar()) {
			string query = "INSERT INTO CLIENTES(nombres,apellidos,nit,genero,telefono,correo_electronico,fechaingreso) VALUES ('" + nombres + "','"+apellidos+"','"+nit+"',"+genero+",'"
				+telefono+"','"+email+"',NOW())";
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

	void modificarCliente() {
		int q_estado;
		ConexionDB con = ConexionDB();
		con.abrirConexion();
		if (con.getConectar()) {
			string query = "UPDATE CLIENTES SET nombres='" + nombres + "',apellidos='"+apellidos+"',nit='"+nit+"',genero="+genero+",telefono='"+telefono+"',correo_electronico='"
				+email+"',fechaingreso=NOW() WHERE idCliente=" + id;
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

	void eliminarCliente() {
		int q_estado;
		ConexionDB con = ConexionDB();
		con.abrirConexion();
		if (con.getConectar()) {
			string query = "DELETE FROM CLIENTES WHERE idCliente=" + id;
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

