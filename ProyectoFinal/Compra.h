#pragma once
#include <iostream>
#include "ConexionDB.h"
#include "Detalle.h"
#include "Proveedor.h"
using namespace std;
class Compra{
//Atributos de clase Compra
private: string fechaorden, fechaingreso, prov, idCompra, orden;

//Constructor
public: 
	Compra(){}
	Compra(string idCompra,string orden, string fechaorden, string fechaingreso, string prov) {
		this->idCompra = idCompra;
		this->orden = orden;
		this->fechaorden = fechaorden;
		this->fechaingreso = fechaingreso;
		this->prov = prov;
	}

	void dataCompras() {
		Detalle d = Detalle();
		int q_estado;
		ConexionDB con = ConexionDB();
		MYSQL_ROW fila;
		MYSQL_RES* res;
		con.abrirConexion();
		if (con.getConectar()) {
			string query = "SELECT c.idcompra, c.no_orden_compra, p.proveedor, c.fecha_orden, c.fechaingreso from COMPRAS c inner join PROVEEDORES p on c.idproveedor = p.idproveedor";
			const char* c = query.c_str();
			q_estado = mysql_query(con.getConectar(), c);
			if (!q_estado) {
				res = mysql_store_result(con.getConectar());
				cout << "\n\n\t************************* COMPRAS ****************************" << endl;
				cout << "\tID   | NO. ORDEN COMPRA |	PROVEEDOR			|	 FECHA ORDEN   | FECHA INGRESO\n" << endl;
				while (fila = mysql_fetch_row(res)) {
					cout << "\t" << fila[0] << " | " << fila[1] << " | " << fila[2] << " | " << fila[3] << " | " << fila[4] << endl;
					d.setIdOpe(fila[0]);
					d.dataDetalle("compras_detalle", "idcompra", "idcompra_detalle");
				}
			}
		}
		else {
			cout << "\n\n\t -- Error en conexion --" << endl;
		}
		con.cerrarConexion();
	}

	void visualizarCompra() {
		Detalle d = Detalle();
		int q_estado;
		ConexionDB con = ConexionDB();
		MYSQL_ROW fila;
		MYSQL_RES* res;
		con.abrirConexion();
		if (con.getConectar()) {
			string query = "SELECT * from COMPRAS where idcompra=" + idCompra;
			const char* c = query.c_str();
			q_estado = mysql_query(con.getConectar(), c);
			if (!q_estado) {
				res = mysql_store_result(con.getConectar());
				cout << "\n\n\t************************* COMPRA ****************************" << endl;
				cout << "\tID  | NO. ORDEN COMPRA | ID PROVEEDOR | FECHA ORDEN | FECHA INGRESO\n" << endl;
				while (fila = mysql_fetch_row(res)) {
					cout << "\t" << fila[0] << " | " << fila[1] << " | " << fila[2] << " | " << fila[3] << " | " << fila[4]  << endl;
					d.setIdOpe(fila[0]);
					d.dataDetalle("compras_detalle", "idcompra", "idcompra_detalle");
					idCompra = fila[0];
					orden = fila[1];
					prov = fila[2];
					fechaorden = fila[3];
				}
			}
		}
		else {
			cout << "\n\n\t -- Error en conexion --" << endl;
		}
		con.cerrarConexion();
	}

	void crearCompra() {
		string nitc;
		Detalle d = Detalle();
		Proveedor p = Proveedor();
		int q_estado;
		cout << "\n\tIngrese orden de compra: ";
		cin >> orden;
		p.dataProveedor();
		cout << "\tIngrese id proveedor: ";
		cin >> prov;
		cout << "\tIngrese fecha orden (yyyy-MM-dd): ";
		cin >> fechaorden;
		ConexionDB con = ConexionDB();
		con.abrirConexion();
		if (con.getConectar()) {
			string query = "INSERT INTO COMPRAS(no_orden_compra,idproveedor,fecha_orden,fechaingreso) VALUES (" + orden + "," + prov + ",'"+fechaorden+"',NOW()";
			const char* i = query.c_str();
			q_estado = mysql_query(con.getConectar(), i);
			if (!q_estado) {
				idCompra = idCompraActual();
				d.menuDetalle('c', idCompra);
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

	void modificarCompra() {
		Detalle d = Detalle();
		Proveedor p = Proveedor();
		int q_estado;
		string dato;
		cout << "\tIngrese el id de la compra que desea modificar: ";
		cin >> idCompra;
		visualizarCompra();
		cout << "\n\tIngrese datos nuevos (si no desea cambiar un dato ingrese n)" << endl;
		cout << "No. orden compra: ";
		cin >> dato;
		if (dato.compare("n") != 0) {
			orden = dato;
		}
		p.dataProveedor();
		cout << "\n\tIngrese nuevo id proveedor: ";
		cin >> dato;
		if (dato.compare("n") != 0) {
			prov = dato;
		}
		cout << "\tIngrese fecha orden (yyyy-MM-dd): ";
		cin >> dato;
		if (dato.compare("n") != 0) {
			fechaorden = dato;
		}

		ConexionDB con = ConexionDB();
		con.abrirConexion();
		if (con.getConectar()) {
			string query = "UPDATE COMPRAS SET no_orden_compra=" + orden + ",idproveedor=" + prov + ",fecha_orden='" + fechaorden + "' WHERE idCompra=" + idCompra;
			const char* i = query.c_str();
			q_estado = mysql_query(con.getConectar(), i);
			if (!q_estado) {
				cout << "\n\n\t --- Modificacion exitoso ---" << endl;
				cout << "\n\n\tDesea modificar el detalle? (s=si / n=no) ";
				cin >> dato;
				if (dato.compare("s") == 0) {
					d.menuDetalle('c', idCompra);
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

	void deleteCompra(){
		Detalle d = Detalle();
		d.deleteDetalleRel('c', idCompra);
		int q_estado;
		ConexionDB con = ConexionDB();
		con.abrirConexion();
		if (con.getConectar()) {
			string query = "DELETE FROM COMPRAS WHERE idcompra=" + idCompra;
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

	void eliminarCompra() {
		char conf;
		cout << "\tIngrese el id de la compra a eliminar: ";
		cin >> idCompra;
		visualizarCompra();
		cout << "\n\tSeguro que desea eliminar el registro. Se eliminara la venta junto con el detalle. Esta operacion no se puede revertir (SI = s / No = n): ";
		cin >> conf;
		if (conf == 's') {
			deleteCompra();
		}
		else {
			cout << "\n\tRegisto no eliminado" << endl;
		}
	}

	string idCompraActual() {
		string id = "";
		int q_estado;
		ConexionDB con = ConexionDB();
		MYSQL_ROW fila;
		MYSQL_RES* res;
		con.abrirConexion();
		if (con.getConectar()) {
			string query = "SELECT idcompra FROM COMPRAS where no_orden_compra="+orden;
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
};

