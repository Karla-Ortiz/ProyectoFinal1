#pragma once
#include <iostream>
#include "ConexionDB.h"
#include "Producto.h"
#include <string>
using namespace std;

class Detalle{
//Atributos clase Detalle
private: string id, idOpe,producto;
	   int cantidad;
	   double precioU, total = 0.0;

//Constructor
public:
	Detalle(){}
	Detalle(string id, string idope,string producto, int cantidad, double precio) {
		this->id = id;
		this->idOpe = idope;
		this->producto = producto;
		this->cantidad = cantidad;
		precioU = precio;
	}

	void setIdOpe(string id) {
		idOpe = id;
	}

	double getTotal() {
		return total;
	}

	void dataDetalle(string tabla, string campo, string campo2) {
		int q_estado;
		ConexionDB con = ConexionDB();
		MYSQL_ROW fila;
		MYSQL_RES* res;
		con.abrirConexion();
		if (con.getConectar()) {
			string query = "SELECT "+campo2+", concat(v.idproducto,'-',p.producto,' marca ',m.marca) prod,v.cantidad, v.precio_unitario FROM " + tabla + " v "
				+ "inner join productos p on p.idproducto = v.idproducto "
				+ "inner join marcas m on p.idmarca = m.idmarca where " + campo + "=" + idOpe;
			const char* c = query.c_str();
			q_estado = mysql_query(con.getConectar(), c);
			if (!q_estado) {
				res = mysql_store_result(con.getConectar());
				if (tabla.compare("ventas_detalle") == 0) {
					cout << "\n\n\t**************** Detalle venta *******************" << endl;
				}
				else {
					cout << "\n\n\t**************** Detalle compra *******************" << endl;
				}
				cout << "\tID DETALLE |    PRODUCTO    | CANTIDAD | PRECIO UNITARIO\n" << endl;
				while (fila = mysql_fetch_row(res)) {
					cout << "\t" << fila[0] << " | " << fila[1] << " | " << fila[2] << " | " << fila[3] << endl;
					cantidad = (int)fila[2];
					precioU = atof(fila[3]);
					total += cantidad * precioU;
				}
			}
		}
		else {
			cout << "\n\n\t -- Error en conexion --" << endl;
		}
		con.cerrarConexion();
	}

	void getLineaDetalle(string tabla, string campo) {
		int q_estado;
		ConexionDB con = ConexionDB();
		MYSQL_ROW fila;
		MYSQL_RES* res;
		con.abrirConexion();
		if (con.getConectar()) {
			string query = "SELECT v.idproducto, concat('-',p.producto,' marca ',m.marca) prod,v.cantidad, v.precio_unitario FROM " + tabla + " v "
				+ "inner join productos p on p.idproducto = v.idproducto "
				+ "inner join marcas m on p.idmarca = m.idmarca where " + campo + "=" + id;
			const char* c = query.c_str();
			q_estado = mysql_query(con.getConectar(), c);
			if (!q_estado) {
				res = mysql_store_result(con.getConectar());
				if (tabla.compare("ventas_detalle") == 0) {
					cout << "\n\n\t**************** Linea detalle venta *******************" << endl;
				}
				else {
					cout << "\n\n\t**************** Linea detalle compra *******************" << endl;
				}
				cout << "\t    PRODUCTO    | CANTIDAD | PRECIO UNITARIO\n" << endl;
				while (fila = mysql_fetch_row(res)) {
					cout << "\t"<< fila[0]<< fila[1] << " | " << fila[2] << " | " << fila[3] << " | " << endl;
					producto = fila[0];
					cantidad = (int)fila[2];
				}
			}
		}
		else {
			cout << "\n\n\t -- Error en conexion --" << endl;
		}
		con.cerrarConexion();
	}

	void createDetalle(char operacion) {
		int q_estado;
		string cant = to_string(cantidad);
		cin.ignore();
		ConexionDB con = ConexionDB();
		con.abrirConexion();
		if (con.getConectar()) {
			string query = "";
			if (operacion == 'v') {
				query = "INSERT INTO ventas_detalle(idventa,idproducto,cantidad,precio_unitario) VALUES (" + idOpe + "," + producto + "," + cant + ","
					+ "(select precio_venta from productos where idproducto=" + producto + "))";
			}
			else if (operacion == 'c') {
				query = "INSERT INTO compras_detalle(idcompra,idproducto,cantidad,precio_unitario) VALUES (" + idOpe + "," + producto + "," + cant + ","
					+ "(select precio_costo from productos where idproducto=" + producto + "))";
			} 
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

	void modificarDetalle(char operacion) {
		int q_estado;
		string cant = to_string(cantidad);
		cin.ignore();
		ConexionDB con = ConexionDB();
		con.abrirConexion();
		if (con.getConectar()) {
			string query = "";
			if (operacion == 'c') {
				query = "UPDATE COMPRAS_DETALLE SET idproducto=" + producto + ", cantidad=" + cant + ", precio_unitario="
					+ "(select precio_costo from productos where idproducto=" + producto + ") where idcompra_detalle=" + id;
			}
			else {
				query = "UPDATE VENTAS_DETALLE SET idproducto=" + producto + ", cantidad=" + cant + ", precio_unitario="
					+ "(select precio_venta from productos where idproducto=" + producto + ") where idventa_detalle=" + id;
			}
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

	void deleteDetalle(char operacion) {
		int q_estado;
		ConexionDB con = ConexionDB();
		con.abrirConexion();
		if (con.getConectar()) {
			string query = "";
			if (operacion == 'c') {
				query = "DELETE FROM COMPRAS WHERE idcompra_detalle=" + id;
			}
			else {
				query = "DELETE FROM VENTAS WHERE idventa_detalle=" + id;
			}
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

	boolean deleteDetalleRel(char operacion, string idOperacion) {
		boolean del = false;
		ConexionDB con = ConexionDB();
		con.abrirConexion();
		if (con.getConectar()) {
			string query = "";
			if (operacion == 'c') {
				query = "DELETE FROM COMPRAS WHERE idcompra=" + idOperacion;
			}
			else {
				query = "DELETE FROM VENTAS WHERE idventa=" + idOperacion;
			}
			const char* i = query.c_str();
			mysql_query(con.getConectar(), i);
		}
		else {
			cout << "\n\n\t --- Error en conexion ---" << endl;
		}
		con.cerrarConexion();
	}

	void pausa(string operacion)
	{
		cout << "\n\n\n\n\t\t\t\t\tPulsa una tecla para regresar " + operacion + "...";
		getwchar();
		getwchar();
	}

	void insertarProductosDetalle(char operacion) {
		Producto p = Producto();
		p.dataProductos();
		char stop = 's';
		cout << "\n\t------------INGRESO PRODUCTOS EN DETALLE------------------";
		while (stop != 'n') {
			cout << "\n\tIngrese id del producto: ";
			cin >> producto;
			cout << "\tIngrese cantidad: ";
			cin >> cantidad;
			createDetalle(operacion);
			cout << "\n\n\n\tDesea agregar otro producto (SI = s / No = n): ";
			cin >> stop;
		}
	}

	void modificarProductosDetalle(char operacion) {
		Producto p = Producto();
		if (operacion == 'c') {
			dataDetalle("COMPRAS", "idcompra","idcompra_detalle");
		}
		else {
			dataDetalle("VENTAS", "idventa","idventa_detalle");
		}
		char stop = 's';
		string dato;
		cout << "\n\n\t------------MODIFICACION PRODUCTOS EN DETALLE------------------";
		while (stop != 'n') {
			cout << "\n\tIngrese id de la linea del detalle: ";
			cin >> id;
			p.dataProductos();
			if (operacion == 'c') {
				getLineaDetalle("COMPRAS", "idcompra_detalle");
			}
			else {
				getLineaDetalle("VENTAS","idventa_detalle");
			}
			cout << "\n\tIngrese datos nuevos (si no desea cambiar un dato ingrese n)" << endl;
			cout << "\tIngrese id producto: ";
			cin >> dato;
			if (dato.compare("n") != 0) {
				producto = dato;
			}
			cout << "\tIngrese cantidad: ";
			cin >> dato;
			if (dato.compare("n") != 0) {
				cantidad = stoi(dato);
			}
			modificarDetalle(operacion);
			cout << "\n\n\n\tDesea modificar otra linea del detalle (SI = s / No = n): ";
			cin >> stop;
		}
	}

	void eliminarDetalle(char operacion) {
		char conf;
		if (operacion == 'c') {
			dataDetalle("COMPRAS", "idcompra", "idcompra_detalle");
			cout << "\tIngrese el id de la linea del detalle a eliminar: ";
			cin >> id;
			getLineaDetalle("COMPRAS", "idcompra_detalle");
		}
		else {
			dataDetalle("VENTAS", "idventa", "idventa_detalle");
			cout << "\tIngrese el id de la linea del detalle a eliminar: ";
			cin >> id;
			getLineaDetalle("VENTAS", "idventa_detalle");
		}
		cout << "\n\tSeguro que desea eliminar el registro. Esta operacion no se puede revertir (SI = s / No = n): ";
		cin >> conf;
		if (conf == 's') {
			deleteDetalle(operacion);
		}
		else {
			cout << "\n\tRegisto no eliminado" << endl;
		}
	}

	int menuDetalle(char operacion, string id) {
		int opc = 0;
		char stop = 's';
		idOpe = id;
		while (opc != 5) {
			system("cls");
			system("color 0b");
			cin.clear();
			cout << "\n\t--------------DETALLE--------------" << endl;
			cout << "1. Nuevo producto en detalle" << endl;
			cout << "2. Visualizar detalle" << endl;
			cout << "3. Eliminar producto en detalle" << endl;
			cout << "4. Modificar producto en detalle" << endl;
			cout << "5. Finalizar detalle" << endl;
			cout << "Seleccione una opcion: ";
			cin >> opc;

			switch (opc) {
			case 1: system("cls");
				insertarProductosDetalle(operacion);
				break;
			case 2: system("cls");
				if (operacion == 'c') {
					dataDetalle("COMPRAS", "idcompra", "idcompra_detalle");
				}
				else {
					dataDetalle("VENTAS", "idventa", "idventa_detalle");
				}
				pausa("");
				break;
			case 3: system("cls");
				modificarProductosDetalle(operacion);
				break;
			case 4: system("cls");
				eliminarDetalle(operacion);
				break;
			}
		}
		if (operacion == 'c') {
			pausa("al modulo compras");
		}
		else {
			pausa("al modulo ventas");
		}
	}
};

