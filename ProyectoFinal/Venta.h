#pragma once
#include <iostream>
#include "ConexionDB.h"
#include "Detalle.h"
#include <string>
#include <regex>
using namespace std;

class Venta{
//Atributos de la clase Venta
private: string idVenta, nofac, serie, fechafac, cliente, empleado, fechaingreso;

//Constructor
public:
	Venta(){}
	Venta(string idVenta,string nofac, string serie, string fechafac, string cliente, string empleado, string fechaingreso ) {
		this->idVenta = idVenta;
		this->nofac = nofac;
		this->serie = serie;
		this->fechafac = fechafac;
		this->cliente = cliente;
		this->empleado = empleado;
		this->fechaingreso = fechaingreso;
	}

	string getNofac() {
		return nofac;
	}

	string getSerie() {
		return serie;
	}

	void dataVentas() {
		Detalle d = Detalle();
		int q_estado;
		ConexionDB con = ConexionDB();
		MYSQL_ROW fila;
		MYSQL_RES* res;
		con.abrirConexion();
		if (con.getConectar()) {
			string query = " SELECT v.idventa,CONCAT(v.serie,'-',v.nofactura) fact,v.fechafactura, concat(c.nombres,' ',c.apellidos, '-',c.nit) cliente, concat(e.nombres,' ',e.apellidos) empleado, v.fechaingreso from VENTAS v inner join CLIENTES c on v.idcliente = c.idcliente inner join EMPLEADOS e on e.idempleado = v.idempleado";
			const char* c = query.c_str();
			q_estado = mysql_query(con.getConectar(), c);
			if (!q_estado) {
				res = mysql_store_result(con.getConectar());
				cout << "\n\n\t************************* VENTAS ****************************" << endl;
				cout << "\tID  | FACTURA | FECHA FACTURA |	CLIENTE			|	 EMPLEADO   | FECHA INGRESO\n" << endl;
				while (fila = mysql_fetch_row(res)) {
					cout << "\t" << fila[0] << " | " << fila[1] << " | " << fila[2] << " | " << fila[3] << " | " << fila[4] << " | " << fila[5] << endl;
					d.setIdOpe(fila[0]);
					d.dataDetalle("ventas_detalle","idventa","idventa_detalle");
				}
			}
		}
		else {
			cout << "\n\n\t -- Error en conexion --" << endl;
		}
		con.cerrarConexion();
	}

	void visualizarVenta() {
		Detalle d = Detalle();
		int q_estado;
		ConexionDB con = ConexionDB();
		MYSQL_ROW fila;
		MYSQL_RES* res;
		con.abrirConexion();
		if (con.getConectar()) {
			string query = " SELECT v.idventa,CONCAT(v.serie,'-',v.nofactura) fact,v.fechafactura, concat(c.nombres,' ',c.apellidos, '-',c.nit) cliente, concat(e.nombres,' ',e.apellidos) empleado, v.fechaingreso from VENTAS v inner join CLIENTES c on v.idcliente = c.idcliente inner join EMPLEADOS e on e.idempleado = v.idempleado where idVenta="+idVenta;
			const char* c = query.c_str();
			q_estado = mysql_query(con.getConectar(), c);
			if (!q_estado) {
				res = mysql_store_result(con.getConectar());
				cout << "\n\n\t************************* VENTA ****************************" << endl;
				cout << "\tID  | FACTURA | FECHA FACTURA |	CLIENTE			|	 EMPLEADO   | FECHA INGRESO\n" << endl;
				while (fila = mysql_fetch_row(res)) {
					cout << "\t" << fila[0] << " | " << fila[1] << " | " << fila[2] << " | " << fila[3] << " | " << fila[4] << " | " << fila[5] << endl;
					d.setIdOpe(fila[0]);
					d.dataDetalle("ventas_detalle", "idventa", "idventa_detalle");
				}
				query = "SELECT idVenta, fechafactura, idcliente, idempleado where idVenta=" + idVenta;
				const char* select = query.c_str();
				q_estado = mysql_query(con.getConectar(), select);
				if (!q_estado) {
					res = mysql_store_result(con.getConectar());
					while (fila = mysql_fetch_row(res)) {
						idVenta = fila[0];
						fechafac = fila[1];
						cliente = fila[2];
						empleado = fila[3];
					}
				}
			}
		}
		else {
			cout << "\n\n\t -- Error en conexion --" << endl;
		}
		con.cerrarConexion();
	}

	void crearVenta() {
		string nitc;
		Detalle d = Detalle();
		Empleado e = Empleado();
		Cliente c = Cliente();
		int q_estado;
		cout << "\n\tIngrese su id de empleado: ";
		cin >> empleado;
		if (e.empleadoValido(empleado)) {
			cout << "\tIngrese nit del cliente: ";
			cin >> nitc;
			if (nitValido(nitc)) {
				if (!c.buscarCliente(nitc)) {
					cout << "\n\tCliente no existe, ingrese los siguientes datos para crearlo" << endl;
					if (c.crearClienteParcial(nitc)) {
						c.buscarCliente(nitc);
					}
					else {
						return;
					}
				}
				if (correlFactura()) {
					ConexionDB con = ConexionDB();
					con.abrirConexion();
					if (con.getConectar()) {
						string query = "INSERT INTO VENTAS(nofactura,serie,fechafactura,idcliente,idempleado,fechaingres) VALUES ("+nofac+",'"+serie+"',CURDATE(),"+c.getId()+","+empleado+",NOW())";
						const char* i = query.c_str();
						q_estado = mysql_query(con.getConectar(), i);
						if (!q_estado) {
							idVenta = idVentaActual();
							d.menuDetalle('v', idVenta);
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
				else {
					cout << "\n\tNo se logro obtener correlativo de factura" << endl;
				}
			}
			else {
				cout << "\n\n\tEl nit no es valido" << endl;
			}
		}
		else {
			cout << "\n\tEl id de empleado no es valido" << endl;
		}
	}

	void modificarVenta() {
		Detalle d = Detalle();
		int q_estado;
		string dato;
		cout << "\tIngrese el id de la venta que desea modificar: ";
		cin >> idVenta;
		visualizarVenta();
		cout << "\n\tIngrese datos nuevos (si no desea cambiar un dato ingrese n)" << endl;
		cout << "Ingrese fecha de factura (yyyy-MM-dd): ";
		cin >> dato;
		if (dato.compare("n") != 0) {
			fechafac = dato;
		}
		cout << "\n\tIngrese nuevo id cliente: ";
		cin >> dato;
		if (dato.compare("n") != 0) {
			cliente = dato;
		}
		cout << "Ingrese id de empleado: ";
		cin >> dato;
		if (dato.compare("n") != 0) {
			empleado = dato;
		}
		
		ConexionDB con = ConexionDB();
		con.abrirConexion();
		if (con.getConectar()) {
			string query = "UPDATE VENTAS SET fechafactura='"+fechafac+"',idcliente="+cliente+"idempleado="+empleado+" WHERE idVenta=" + idVenta;
			const char* i = query.c_str();
			q_estado = mysql_query(con.getConectar(), i);
			if (!q_estado) {
				cout << "\n\n\t --- Modificacion exitoso ---" << endl;
				cout << "\n\n\tDesea modificar el detalle? (s=si / n=no) ";
				cin >> dato;
				if (dato.compare("s") == 0) {
					d.menuDetalle('v', idVenta);
				}
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

	void deleteVenta() {
		Detalle d = Detalle();
		d.deleteDetalleRel('v', idVenta);
		int q_estado;
		ConexionDB con = ConexionDB();
		con.abrirConexion();
		if (con.getConectar()) {
			string query = "DELETE FROM VENTAS WHERE idmarca=" + idVenta;
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

	void eliminarVenta() {
		char conf;
		cout << "\tIngrese el id de la venta a eliminar: ";
		cin >> idVenta;
		visualizarVenta();
		cout << "\n\tSeguro que desea eliminar el registro. Se eliminara la venta junto con el detalle. Esta operacion no se puede revertir (SI = s / No = n): ";
		cin >> conf;
		if (conf == 's') {
			deleteVenta();
		}
		else {
			cout << "\n\tRegisto no eliminado" << endl;;
		}
	}

	string idVentaActual() {
		string id = "";
		int q_estado;
		ConexionDB con = ConexionDB();
		MYSQL_ROW fila;
		MYSQL_RES* res;
		con.abrirConexion();
		if (con.getConectar()) {
			string query = "SELECT idventa FROM VENTAS where nofactura=" + nofac + " and serie='" + serie + "'";
			const char* c = query.c_str();
			q_estado = mysql_query(con.getConectar(), c);
			if (!q_estado) {
				res = mysql_store_result(con.getConectar());
				while (fila = mysql_fetch_row(res)) {
					id = fila[0];
				}
			}
		}
		else {
			cout << "\n\n\t -- Error en conexion --" << endl;
		}
		con.cerrarConexion();
	}

	boolean correlFactura() {
		boolean genero = false;
		int q_estado;
		ConexionDB con = ConexionDB();
		MYSQL_ROW fila;
		MYSQL_RES* res;
		con.abrirConexion();
		if (con.getConectar()) {
			string query = "SELECT nofactura, serie FROM VENTAS order by idventa desc limit 1";
			const char* c = query.c_str();
			q_estado = mysql_query(con.getConectar(), c);
			if (!q_estado) {
				res = mysql_store_result(con.getConectar());
				while (fila = mysql_fetch_row(res)) {
					int factura = (int)fila[0]+1;
					serie = fila[1];
					nofac = to_string(factura);
				}
				genero = true;
			}
		}
		else {
			cout << "\n\n\t -- Error en conexion --" << endl;
		}
		con.cerrarConexion();
	}

	boolean nitValido(string nit) {
		boolean valido = false;
		smatch sm;
		
		if (regex_match(nit, sm, regex( "([0-9]*)" ))) {
			const auto capture = sm[1].str();
			if (capture.length() == nit.length()) {
				valido = true;
			}
		}
		else if (regex_match(nit, sm, regex("([Cc/Ff]{3})"))) {
			valido = true;
		}
		else if (regex_match(nit, sm, regex("([Cc]{1}[Ff]{1})"))) {
			valido = true;
		}
		return valido;
	}
};

