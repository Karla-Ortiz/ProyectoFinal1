#pragma once
#include "ConexionDB.h"
#include "Persona.h"
#include "Puesto.h"
#include <string>
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
			cout << "\n\n\t -- Error en conexion --" << endl;
		}
		con.cerrarConexion();
	}

	void visualizarEmpleado() {
		int q_estado;
		ConexionDB con = ConexionDB();
		MYSQL_ROW fila;
		MYSQL_RES* res;
		con.abrirConexion();
		if (con.getConectar()) {
			string query = "select * FROM EMPLADOS WHERE IDEMPLEADO=" + id;
			const char* c = query.c_str();
			q_estado = mysql_query(con.getConectar(), c);
			if (!q_estado) {
				res = mysql_store_result(con.getConectar());
				cout << "\n\n\t**************** EMPLEADOS *******************" << endl;
				cout << "\tID | NOMBRES  |  APELLIDOS   |  DIRECCION  | DPI     | GENERO | TELEFONO | FECHA NACIMIENTO | ID PUESTO | EMAIL    | FECHA INICIO LABORES | FECHA INGRESO\n" << endl;
				while (fila = mysql_fetch_row(res)) {
					cout << "\t" << fila[0] << " | " << fila[1] << " | " << fila[2] << " | " << fila[3] << " | " << fila[4] << " | " << fila[5] << " | " << fila[6] << " | " << fila[7] << " | " << fila[8] << " | " << fila[9] << " | " << fila[10] << " | " << fila[11] << endl;
					id = fila[0];
					nombres = fila[1];
					apellidos = fila[2];
					direccion = fila[3];
					dpi = fila[4];
					genero = (char)fila[5];
					telefono = fila[6];
					fechanac = fila[7];
					puesto = fila[8];
					email = fila[9];
					fechainilab = fila[10];
					fechaingreso = fila[11];
				}
			}
		}
		else {
			cout << "\n\n\t -- Error en conexion --" << endl;
		}
		con.cerrarConexion();
	}

	void crearEmpleado() {
		Puesto p = Puesto();
		int q_estado;
		cin.ignore();
		cout << "\n\tIngrese nombres: ";
		getline(cin, nombres);
		cin.ignore();
		cout << "\tIngrese apellidos: ";
		getline(cin, apellidos);
		cin.ignore();
		cout << "\tIngrese direccion: ";
		getline(cin, direccion);
		cout << "\tIngrese DPI: ";
		cin >> dpi;
		cout << "\tIngrese genero (FEMENINO = 0 / MASCULINO = 1): ";
		cin >> genero;
		cout << "\tIngrese telefono: ";
		cin >> telefono;
		cout << "\tIngrese fecha de nacimiento (yyyy-MM-dd): ";
		cin >> fechanac;
		p.dataPuestos();
		cout << "\tIngrese id puesto: ";
		cin >> puesto;
		cout << "\tIngrese correo electronico: ";
		cin >> email;
		cout << "\tIngrese fecha inicio de labores: ";
		cin >> fechainilab;
		ConexionDB con = ConexionDB();
		con.abrirConexion();
		if (con.getConectar()) {
			string query = "INSERT INTO EMPLEADOS(nombres, apellidos,direccion,DPI,genero,telefono,fecha_nacimiento,puesto,correo_electronico,fecha_inicio_labores,fechaingreso) VALUES ('"
				+ nombres + "','"+apellidos+"','"+direccion+"','"+dpi+"','"+genero+"','"+telefono+"','"+fechanac+"','"+puesto+"','"+email+"','"+fechainilab+"',NOW())";
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

	void modificarEmpleado() {
		Puesto p = Puesto();
		int q_estado;
		string dato;
		cout << "\n\tIngrese id empleado: ";
		cin >> id;
		visualizarEmpleado();
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
		cin.ignore();
		cout << "\tDireccion: ";
		getline(cin, dato);
		if (dato.compare("n") != 0) {
			direccion = dato;
		}
		cout << "\tDPI: ";
		cin >> dato;
		if (dato.compare("n") != 0) {
			dpi = dato;
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
		cout << "\tFecha de nacimiento (yyyy-MM-dd): ";
		cin >> dato;
		if (dato.compare("n") != 0) {
			fechanac = dato;
		}
		p.dataPuestos();
		cout << "\tId puesto: ";
		cin >> dato;
		if (dato.compare("n") != 0) {
			puesto = dato;
		}
		cout << "\tCorreo electronico: ";
		cin >> dato;
		if (dato.compare("n") != 0) {
			email = dato;
		}
		cout << "\tFecha inicio de labores: ";
		cin >> dato;
		if (dato.compare("n") != 0) {
			fechainilab = dato;
		}
		ConexionDB con = ConexionDB();
		con.abrirConexion();
		if (con.getConectar()) {
			string query = "UPDATE EMPLEADOS SET nombres='" + nombres + "',apellidos='"+apellidos+"',direccion='"+direccion+"',DPI='"+dpi+"',genero="+genero+",telefono='"
				+telefono+"',fecha_nacimiento='"+fechanac+"',puesto="+puesto+",correo_electronico='"+email+"',fecha_inicio_labores='"+fechainilab+"' WHERE idEmpleado=" + id;
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

	void deleteEmpleado() {
		int q_estado;
		ConexionDB con = ConexionDB();
		con.abrirConexion();
		if (con.getConectar()) {
			string query = "DELETE FROM EMPLEADOS WHERE idEmpleado=" + id;
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

	void eliminarEmpleado() {
		char conf;
		cout << "\tIngrese el id del empleado a eliminar: ";
		cin >> id;
		visualizarEmpleado();
		cout << "\n\tSeguro que desea eliminar el registro. Esta operacion no se puede revertir (SI = s / No = n): ";
		cin >> conf;
		if (conf == 's') {
			deleteEmpleado();
		}
		else {
			cout << "\n\tRegisto no eliminado" << endl;;
		}
	}

	boolean empleadoValido(string idemp) {
		boolean valido = false;
		int q_estado;
		ConexionDB con = ConexionDB();
		MYSQL_ROW fila;
		MYSQL_RES* res;
		con.abrirConexion();
		if (con.getConectar()) {
			string query = "select idempleado from empleados where idempleado=" + idemp;
			const char* c = query.c_str();
			q_estado = mysql_query(con.getConectar(), c);
			if (!q_estado) {
				res = mysql_store_result(con.getConectar());
				while (mysql_fetch_row(res)) {
					valido = true;
				}
			}
		}
		else {
			cout << "\n\n\t -- Error en conexion --" << endl;
		}
		con.cerrarConexion();
	}
};

