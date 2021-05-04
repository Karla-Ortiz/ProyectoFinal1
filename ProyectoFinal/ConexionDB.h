#pragma once
#include <mysql.h>
#include <iostream>
using namespace std;

class ConexionDB {
private: MYSQL* conectar;

public: 
	void abrirConexion() {
	   conectar = mysql_init(0);
	   conectar = mysql_real_connect(conectar,"localhost","root","root","proyectoFinal",3306,NULL,0);
    }
	MYSQL* getConectar() {
		return conectar;
	}

	void cerrarConexion() {
		mysql_close(conectar);
	}
};

