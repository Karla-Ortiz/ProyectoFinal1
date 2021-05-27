#pragma once
#include "ConexionDB.h"
#include "Persona.h"
class Empleado : Persona{

//Atributos de clase Empleado
private: string direccion, dpi, fechanac, puesto, fechainilab, email;

//Constructor
public:
	Empleado(){}
	Empleado(string direccion, string dpi, string fechanac, string puesto, string fechainilab,
		string nombres, string apellidos, string telefono, string fechaingreso, string id, char genero,string email) 
		: Persona(nombres, apellidos, telefono, fechaingreso, id, genero){
		this->direccion = direccion;
		this->dpi = dpi;
		this->fechanac = fechanac;
		this->puesto = puesto;
		this->fechainilab = fechainilab;
		this->email = email;
	}

	void dataEmpleados() {
		int q_estado;
		ConexionDB con = ConexionDB();
		MYSQL_ROW fila;
		MYSQL_RES* res;
		con.abrirConexion();
		if (con.getConectar()) {
			string query = "select E.idEmpleado, E.nombres, E.apellidos, E.direccion, E.DPI,E.genero,E.telefono, E.fecha_nacimiento, P.puesto,E.correo_electronico,E.fecha_inicio_labores, E.fechaingreso from empleados E INNER JOIN PUESTOS P ON E.idPuesto = P.idPuesto";
			const char* c = query.c_str();
			q_estado = mysql_query(con.getConectar(), c);
			if (!q_estado) {
				res = mysql_store_result(con.getConectar());
				cout << "\n\n\t**************** EMPLEADOS *******************" << endl;
				cout << "\tID | NOMBRES  |  APELLIDOS   |  DIRECCION  | DPI     | GENERO | TELEFONO | FECHA NACIMIENTO | PUESTO   | EMAIL    | FECHA INICIO LABORES | FECHA INGRESO\n" << endl;
				while (fila = mysql_fetch_row(res)) {
					cout << "\t" << fila[0] << " | " << fila[1] << " | " << fila[2] << " | " <<fila[3] << " | " <<fila[4] << " | " <<fila[5] << " | " <<fila[6] << " | " <<fila[7] << " | " <<fila[8] << " | " <<fila[9] << " | " <<fila[10] << " | " <<fila[11] << endl;
				}
			}
		}
		else {
			cout << " -- Error en conexion --" << endl;
		}
		con.cerrarConexion();
	}

	void crearEmpleado() {
		int q_estado;
		ConexionDB con = ConexionDB();
		con.abrirConexion();
		if (con.getConectar()) {
			string query = "INSERT INTO EMPLEADOS(nombres, apellidos,direccion,DPI,genero,telefono,fecha_nacimiento,puesto,correo_electronico,fecha_inicio_labores,fechaingreso) VALUES ('"
				+ nombres + "','"+apellidos+"','"+direccion+"','"+dpi+"','"+genero+"','"+telefono+"','"+fechanac+"','"+puesto+"','"+email+"','"+fechainilab+"',NOW())";
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

	void modificarEmpleado() {
		int q_estado;
		ConexionDB con = ConexionDB();
		con.abrirConexion();
		if (con.getConectar()) {
			string query = "UPDATE EMPLEADOS SET nombres='" + nombres + "',apellidos='"+apellidos+"',direccion='"+direccion+"',DPI='"+dpi+"',genero="+genero+",telefono='"
				+telefono+"',fecha_nacimiento='"+fechanac+"',puesto="+puesto+",correo_electronico='"+email+"',fecha_inicio_labores='"+fechainilab+"',fechaingreso=NOW() WHERE idEmpleado=" + id;
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

	void eliminarEmpleado() {
		int q_estado;
		ConexionDB con = ConexionDB();
		con.abrirConexion();
		if (con.getConectar()) {
			string query = "DELETE FROM EMPLEADOS WHERE idEmpleado=" + id;
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

