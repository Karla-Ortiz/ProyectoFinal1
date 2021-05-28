// ProyectoFinal.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//
#include <iostream>
#include "Puesto.h"
#include "Empleado.h"
#include "Marca.h"
#include "Producto.h"
#include "Cliente.h"
#include "Proveedor.h"
#include <Windows.h>
using namespace std;

void moduloPuestos();
void moduloEmpleados();
void moduloMarcas();
void moduloProductos();
void moduloClientes();
void moduloProveedores();

int mostrarMenu(string titulo, string opciones) {
    int opcion = 0;
    system("color 0e");
    system("cls");
    cin.clear();
    cout << "\n\n\n\t\t\t\t\t------------- MODULO " << titulo << " -------------" << endl;
    cout << "\t\t\t\t\t****************************************" << endl;
    cout << "\n\n\n\n\t\t\t\t\tMENU: " << titulo << endl;
    cout << "\t\t\t\t\t---------------------------------------" << endl;
    cout << "\t\t\t\t\t1. Ingresar " << opciones << endl;
    cout << "\t\t\t\t\t2. Visualizar " << opciones << endl;
    cout << "\t\t\t\t\t3. Modificar " << opciones << endl;
    cout << "\t\t\t\t\t4. Eliminar " << opciones << endl;
    cout << "\t\t\t\t\t5. Salir." << endl;
    cout << "\t\t\t\t\tIngrese una opcion: ";
    cin >> opcion;
    return opcion;
}

void barra(string mensaje) {
    int barl = 40;
    cout << "\n\n\t\t\t\t\t SALIENDO DEL MODULO " << mensaje << endl;
    cout << "\n\n\t\t\t\t\t[";
    for (int i = 0; i < barl; i++) {
        Sleep(40);
        cout << ":";
    }
    cout << "]" << endl;
}

void pausa()
{
    cout << "\n\n\n\n\t\t\t\t\tPulsa una tecla para regresar al menu...";
    getwchar();
    getwchar();
}

int main()
{
    int opc = 0;
    while (opc != 7) {
        system("color 80");
        system("cls");
        cin.clear();
        cout << "\n\n\n\t\t\t\t\t------------- BIENVENIDO ---------------" << endl;
        cout << "\t\t\t\t\t****************************************" << endl;
        cout << "\n\n\n\n\t\t\t\t\tMENU PRINCIPAL" << endl;
        cout << "\t\t\t\t\t---------------------------------------" << endl;
        cout << "\t\t\t\t\t1. Modulo de Puestos." << endl;
        cout << "\t\t\t\t\t2. Modulo de Empleados." << endl;
        cout << "\t\t\t\t\t3. Modulo de Marcas." << endl;
        cout << "\t\t\t\t\t4. Modulo de Productos." << endl;
        cout << "\t\t\t\t\t5. Modulo de Clientes." << endl;
        cout << "\t\t\t\t\t6. Modulo de Proveedores." << endl;
        cout << "\t\t\t\t\t7. Salir" << endl;
        cout << "\t\t\t\t\tIngrese una opcion: ";
        cin >> opc;

        switch (opc) {
        case 1: moduloPuestos();
            break;
        case 2: moduloEmpleados();
            break;
        case 3:moduloMarcas();
            break;
        case 4: moduloProductos();
            break;
        case 5: moduloClientes();
            break;
        case 6: moduloProveedores();
            break;
        case 7: cout << "\n\n\t\t\t\t\t***********************************" << endl;
            cout << "\t\t\t\t\t\t Regrese pronto :D\n\n" << endl;
            break;
        default: cout << "\t\t\t\t\tLa opcion ingresada no se encuentra en el menu, pruebe nuevamente" << endl;
            getwchar();
            getwchar();
            break;
        }
    }
}

void moduloPuestos() {
    Puesto p = Puesto();
    int opc = 0;
    char stop;
    while (opc != 5) {
        opc = mostrarMenu("PUESTOS", "puestos");
        switch (opc) {
        case 1: system("cls");
            stop = 's';
            cout << "\n\n\tINGRESO PUESTOS\n" << endl;
            cout << "\t--------------------\n" << endl;
            while (stop != 'n') {
                p.crearPuesto();
                cout << "\n\n\n\tDesea ingresar otro puestos (SI = s / No = n): ";
                cin >> stop;
            }
            pausa();
            break;
        case 2: system("cls");
            p.dataPuestos();
            pausa();
            break;
        case 3: system("cls");
            pausa();
            break;
        case 4: system("cls");
            pausa();
            break;
        }
    }
    barra("PUESTOS");
}

void moduloEmpleados() {
    Empleado emp = Empleado();
    int opc = 0;
    char stop = 'a';
    while (opc != 5) {
        opc = mostrarMenu("EMPLEADOS", "empleados");
        switch (opc) {
        case 1: system("cls");
            cout << "\n\n\tINGRESO EMPLEADOS\n" << endl;
            cout << "\t--------------------\n" << endl;
            while (stop != 'n') {
                emp.crearEmpleado();
                cout << "\n\n\n\tDesea ingresar otro empleado (SI = s / No = n): ";
                cin >> stop;
            }
            pausa();
            break;
        case 2: system("cls");
            emp.dataEmpleados();
            pausa();
            break;
        case 3: system("cls");
            pausa();
            break;
        case 4: system("cls");
            pausa();
            break;
        }
    }
    barra("EMPLEADOS");
}

void moduloProductos() {
    Producto p = Producto();
    int opc = 0;
    char stop = 's';
    while (opc != 5) {
        opc = mostrarMenu("PRODUCTOS","productos");
        switch (opc) {
        case 1: system("cls");
            cout << "\n\n\tINGRESO PRODUCTOS\n" << endl;
            cout << "\t--------------------\n" << endl;
            while (stop != 'n') {
                p.crearProducto();
                cout << "\n\n\n\tDesea ingresar otro producto (SI = s / No = n): ";
                cin >> stop;
            }
            pausa();
            break;
        case 2: system("cls");
            p.dataProductos();
            pausa();
            break;
        case 3: system("cls");
            pausa();
            break;
        case 4: system("cls");
            pausa();
            break;
        }
    }
    barra("PRODUCTOS");
}

void moduloClientes() { 
    Cliente c = Cliente();
    int opc = 0;
    char stop = 's';
    while (opc != 5) {
        opc = mostrarMenu("CLIENTES", "clientes");
        switch (opc) {
        case 1: system("cls");
            cout << "\n\n\tINGRESO CLIENTES\n" << endl;
            cout << "\t--------------------\n" << endl;
            while (stop != 'n') {
                c.crearCliente();
                cout << "\n\n\n\tDesea ingresar otro cliente (SI = s / No = n): ";
                cin >> stop;
            }
            pausa();
            break;
        case 2: system("cls");
            c.dataClientes();
            pausa();
            break;
        case 3: system("cls");
            pausa();
            break;
        case 4: system("cls");
            pausa();
            break;
        }
    }
    barra("CLIENTES");
}

void moduloMarcas() {
    Marca m = Marca();
    int opc = 0;
    char stop = 's';
    while (opc != 5) {
        opc = mostrarMenu("MARCAS", "marcas");
        switch (opc) {
        case 1: system("cls");
            cout << "\n\n\tINGRESO MARCAS\n" << endl;
            cout << "\t--------------------\n" << endl;
            while (stop != 'n') {
                m.crearMarca();
                cout << "\n\n\n\tDesea ingresar otra marca (SI = s / No = n): ";
                cin >> stop;
            }
            pausa();
            break;
        case 2: system("cls");
            m.dataMarcas();
            pausa();
            break;
        case 3: system("cls");
            cout << "\n\n\tMODIFICACION MARCAS\n" << endl;
            cout << "\t-------------------------\n" << endl;
            while (stop != 'n') {
                m.modificarMarca();
                cout << "\n\n\n\tDesea modificar otra marca (SI = s / No = n): ";
                cin >> stop;
            }
            pausa();
            break;
        case 4: system("cls");
            pausa();
            break;
        }
    }
    barra("MARCAS");
}

void moduloProveedores() {
    Proveedor p = Proveedor();
    int opc = 0;
    char stop;
    while (opc != 5) {
        opc = mostrarMenu("PROVEEDORES", "proveedores");
        switch (opc) {
        case 1: system("cls");
            stop = 's';
            cout << "\n\n\tINGRESO PROVEEDORES\n" << endl;
            cout << "\t--------------------\n" << endl;
            while (stop != 'n') {
                p.crearProveedor();
                cout << "\n\n\n\tDesea ingresar otro proveedor (SI = s / No = n): ";
                cin >> stop;
            }
            pausa();
            break;
        case 2: system("cls");
            p.dataProveedor();
            pausa();
            break;
        case 3: system("cls");
            stop = 's';
            cout << "\n\n\tMODIFICACION PROVEEDORES\n" << endl;
            cout << "\t-------------------------\n" << endl;
            while (stop != 'n') {
                p.modificarProveedor();
                cout << "\n\n\n\tDesea modificar otro proveedor (SI = s / No = n): ";
                cin >> stop;
            }
            pausa();
            break;
        case 4: system("cls");
            stop = 's';
            cout << "\n\n\tELIMINACION PROVEEDORES\n" << endl;
            cout << "\t--------------------\n" << endl;
            while (stop != 'n') {
                p.eliminarProveedor();
                cout << "\n\n\n\tDesea eliminar otro proveedor (SI = s / No = n): ";
                cin >> stop;
            }
            pausa();
            break;
        }
    }
    barra("PROVEEDORES");
}
// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración
