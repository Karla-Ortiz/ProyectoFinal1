#pragma once
#include "ConexionDB.h"
#include <iostream>
#include <string>
#include "Marca.h"
using namespace std;

class Producto{
//Atributos de la clase Producto
private: string idProd, prod, marca, desc, imagen, precioC, precioV, existencia, fechaingreso;

//Constructor
public:
	Producto(){}
	Producto(string idProd, string prod, string marca, string desc, string imagen, string precioC, string precioV, string existencia, string fechaingreso) {
		this->idProd = idProd;
		this->prod = prod;
		this->marca = marca;
		this->desc = desc;
		this->imagen = imagen;
		this->precioC = precioC;
		this->precioV = precioV;
		this->existencia = existencia;
		this->fechaingreso = fechaingreso;
	}

	void dataProductos() {
		int q_estado;
		ConexionDB con = ConexionDB();
		MYSQL_ROW fila;
		MYSQL_RES* res;
		con.abrirConexion();
		if (con.getConectar()) {
			string query = "SELECT p.idProducto,p.producto,m.marca,p.descripcion,p.precio_costo,p.precio_venta,p.existencia, p.fecha_ingreso FROM PRODUCTOS p inner join marcas m on p.idmarca = m.idmarca";
			const char* c = query.c_str();
			q_estado = mysql_query(con.getConectar(), c);
			if (!q_estado) {
				res = mysql_store_result(con.getConectar());
				cout << "\n\n\t**************** PPODUCTOS *******************" << endl;
				cout << "\tID    |  PRODUCTO  | MARCAR | DESCRIPCION  | PRECIO COSTO | PRECIO VENTA | EXISTENCIA | FECHA INGRESO\n" << endl;
				while (fila = mysql_fetch_row(res)) {
					cout << "\t" << fila[0] << " | " << fila[1] << " | " <<fila[2] << " | " <<fila[3] << " | " <<fila[4] << " | " <<fila[5] << " | " <<fila[6] << " | " <<fila[7] << endl;
				}
			}
		}
		else {
			cout << "\n\n\t -- Error en conexion --" << endl;
		}
		con.cerrarConexion();
	}

	void crearProducto() {
		Marca m = Marca();
		int q_estado;
		cout << "\tIngrese producto: ";
		getline(cin, prod);
		cout << "\n\n";
		m.dataMarcas();
		cout << "\n\tIngrese el id de una marca: ";
		cin >> marca;
		cout << "\tIngrese descripcion: ";
		getline(cin, desc);
		cout << "\tIngrese precio costo: ";
		cin >> precioC;
		cout << "\tIngrese precio venta: ";
		cin >> precioV;
		cout << "\tIngrese existencias: ";
		cin >> existencia;
		ConexionDB con = ConexionDB();
		con.abrirConexion();
		if (con.getConectar()) {
			string query = "INSERT INTO PRODUCTOS(producto,idmarca,descripcion,precio_costo,precio_venta,existencia,fecha_ingreso) VALUES ('" + prod + "',"+marca+",'"+desc+"',"+precioC+","
				+precioV+","+existencia+",NOW())";
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

	void modificarProducto() {
		int q_estado;
		ConexionDB con = ConexionDB();
		con.abrirConexion();
		if (con.getConectar()) {
			string query = "UPDATE PRODUCTOS SET producto='" + prod + "',idMarca="+marca+",descripcion='"+desc+"',precio_costo="+precioC+",precio_venta="
				+precioV+",exitencia="+existencia+",fecha_ingreso=NOW() WHERE idProducto=" + idProd;
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

	void eliminarPrdocuto() {
		int q_estado;
		ConexionDB con = ConexionDB();
		con.abrirConexion();
		if (con.getConectar()) {
			string query = "DELETE FROM PRODUCTOS WHERE idProducto=" + idProd;
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

