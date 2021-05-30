#pragma once
#include <iostream>
#include "ConexionDB.h"
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

