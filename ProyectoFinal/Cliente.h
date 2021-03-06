#pragma once
#include "ConexionDB.h"
#include "Persona.h"
#include <iostream>
#include <string>
#include <cstring>
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

	string getId() {
		return id;
	}
	string getNombres() {
		return nombres;
	}
	string getApellidos() {
		return apellidos;
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
				cout << "\n\n\t**************** CLIENTES *******************" << endl;
				cout << "\tID    |  NOMBRES  | APELLIDOS | NIT  | GENERO | TELEFONO | EMAIL | FECHA INGRESO\n" << endl;
				while (fila = mysql_fetch_row(res)) {
					cout << "\t" << fila[0] << " | " << fila[1] << " | " << fila[2] << " | " << fila[3] << " | ";
					if (strcmp(fila[4],"0")==0) {
						cout << "FEMENINO";
					}
					else {
						cout << "MASCULINO";
					}
					cout << " | " << fila[5] << " | " << fila[6] << " | " << fila[7] << endl;
				}
			}
		}
		else {
			cout << "\n\n\t -- Error en conexion --" << endl;
		}
		con.cerrarConexion();
	}

	boolean buscarCliente(string nitc) {
		boolean existe = false;
		int q_estado;
		ConexionDB con = ConexionDB();
		MYSQL_ROW fila;
		MYSQL_RES* res;
		con.abrirConexion();
		if (con.getConectar()) {
			string query = "SELECT idCliente,nombres, apellidos FROM CLIENTES where nit="+nitc;
			const char* c = query.c_str();
			q_estado = mysql_query(con.getConectar(), c);
			if (!q_estado) {
				res = mysql_store_result(con.getConectar());
				while (fila = mysql_fetch_row(res)) {
					existe = true;
					id = fila[0];
					nombres = fila[1];
					apellidos = fila[2];
				}
			}
		}
		else {
			cout << "\n\n\t -- Error en conexion --" << endl;
		}
		con.cerrarConexion();
		return existe;
	}

	boolean crearClienteParcial(string nitc) {
		boolean ingreso = false;
		int q_estado;
		nit = nitc;
		cin.ignore();
		cout << "\tIngrese nombres: ";
		getline(cin, nombres);
		cin.ignore();
		cout << "\tIngrese apellidos: ";
		getline(cin, apellidos);
		cout << "\tIngrese genero (FEMENINO = 0 / MASCULINO = 1): ";
		cin >> genero;
		cout << "\tIngrese telefono: ";
		cin >> telefono;
		cout << "\tIngrese correo electronico: ";
		cin >> email;
		ConexionDB con = ConexionDB();
		con.abrirConexion();
		if (con.getConectar()) {
			string query = "INSERT INTO CLIENTES(nombres,apellidos,nit,genero,telefono,correo_electronico,fechaingreso) VALUES ('" + nombres + "','" + apellidos + "','" + nit + "','" + genero + "','"
				+ telefono + "','" + email + "',NOW())";
			const char* i = query.c_str();
			q_estado = mysql_query(con.getConectar(), i);
			if (!q_estado) {
				ingreso = true;
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

	void crearCliente() {
		int q_estado;
		cin.ignore();
		cout << "\tIngrese nombres: ";
		getline(cin, nombres);
		cin.ignore();
		cout << "\tIngrese apellidos: ";
		getline(cin, apellidos);
		cout << "\tIngrese nit: ";
		cin >> nit;
		cout << "\tIngrese genero (FEMENINO = 0 / MASCULINO = 1): ";
		cin >> genero;
		cout << "\tIngrese telefono: ";
		cin >> telefono;
		cout << "\tIngrese correo electronico: ";
		cin >> email;
		ConexionDB con = ConexionDB();
		con.abrirConexion();
		if (con.getConectar()) {
			string query = "INSERT INTO CLIENTES(nombres,apellidos,nit,genero,telefono,correo_electronico,fechaingreso) VALUES ('" + nombres + "','"+apellidos+"','"+nit+"','"+genero+"','"
				+telefono+"','"+email+"',NOW())";
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

	void modificarCliente() {
		int q_estado;
		string dato;
		cout << "\tIngrese el id del cliente que desea modificar: ";
		cin >> id;
		visualizarCliente();
		cin.ignore();
		cout << "\n\tIngrese datos nuevos (si no desea cambiar un dato ingrese n)" << endl;
		cout << "\tNombres: ";
		getline(cin, dato);
		if (dato.compare("n") != 0) {
			nombres = dato;
		}
		cin.ignore();
		cout << "\tApellidos: ";
		getline(cin, dato);
		if (dato.compare("n") != 0) {
			apellidos = dato;
		}
		cout << "\tNit: ";
		cin >> dato;
		if (dato.compare("n") != 0) {
			apellidos = dato;
		}
		char gen;
		cout << "\tGenero (FEMENINO = 0 / MASCULINO = 1): ";
		cin >> gen;
		if (gen != 'n') {
			genero = gen;
		}
		cout << "\tTelefono: ";
		cin >> dato;
		if (dato.compare("n") != 0) {
			telefono = dato;
		}
		cout << "\tEmail: ";
		cin >> dato;
		if (dato.compare("n") != 0) {
			email = dato;
		}
		ConexionDB con = ConexionDB();
		con.abrirConexion();
		if (con.getConectar()) {
			string query = "UPDATE CLIENTES SET nombres='" + nombres + "',apellidos='"+apellidos+"',nit='"+nit+"',genero='"+genero+"',telefono='"+telefono+"',correo_electronico='"
				+email+"',fechaingreso=NOW() WHERE idCliente=" + id;
			cout << query << endl;
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

	void deleteCliente() {
		int q_estado;
		ConexionDB con = ConexionDB();
		con.abrirConexion();
		if (con.getConectar()) {
			string query = "DELETE FROM CLIENTES WHERE idCliente=" + id;
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

	void eliminarCliente() {
		char conf;
		cout << "\tIngrese el id del cliente a eliminar: ";
		cin >> id;
		visualizarCliente();
		cout << "\n\tSeguro que desea eliminar el registro. Esta operacion no se puede revertir (SI = s / No = n): ";
		cin >> conf;
		if (conf == 's') {
			deleteCliente();
		}
		else {
			cout << "\n\tRegisto no eliminado" << endl;;
		}
	}

	void visualizarCliente() {
		int q_estado;
		ConexionDB con = ConexionDB();
		MYSQL_ROW fila;
		MYSQL_RES* res;
		con.abrirConexion();
		if (con.getConectar()) {
			string query = "SELECT * FROM CLIENTES where IDCLIENTE=" + id;
			const char* c = query.c_str();
			q_estado = mysql_query(con.getConectar(), c);
			if (!q_estado) {
				res = mysql_store_result(con.getConectar());
				cout << "\n\n\t**************** CLIENTES *******************" << endl;
				cout << "\tID    |  NOMBRES  | APELLIDOS | NIT  | GENERO | TELEFONO | EMAIL | FECHA INGRESO\n" << endl;
				while (fila = mysql_fetch_row(res)) {
					cout << "\t" << fila[0] << " | " << fila[1] << " | " << fila[2] << " | " << fila[3] << " | ";
					if (strcmp(fila[4], "0") == 0) {
						cout << "FEMENINO";
					}
					else {
						cout << "MASCULINO";
					}
					cout << " | " << fila[5] << " | " << fila[6] << " | " << fila[7] << endl;
					id = (string)fila[0];
					nombres = fila[1];
					apellidos = fila[2];
					nit = fila[3];
					genero = (char)fila[4];
					telefono = fila[5];
					email = fila[6];
					fechaingreso = fila[7];
				}
			}
		}
		else {
			cout << "\n\n\t -- Error en conexion --" << endl;
		}
		con.cerrarConexion();
	}
};

