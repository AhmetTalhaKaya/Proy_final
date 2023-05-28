#include <iostream>
#include "db_local.h"
#include "medicion.h"

using namespace std;

int main() {
    string url = "database.db";
    DB_Local db(url);

    // Abrir base de datos
    if (!db.Abrir_DB()) {
        return 1;
    }

    // Crear la tabla "mediciones"
    if (!db.CrearTabla()) {
        db.Cerrar_DB();
        return 1;
    }


    Medicion medicion;
    // Prueba para ver si funciona aleatoriamente
    medicion.temperatura = -10 + (rand() % 56);  // Valor aleatorio entre -10 y 45
    medicion.humedad = rand() % 101;  // Valor aleatorio entre 0 y 100
    medicion.precipitacion = rand() % 51;  // Valor aleatorio entre 0 y 50
    medicion.intensidadLuz = rand() % 2001;  // Valor aleatorio entre 0 y 2000

    if (db.Ingresar(medicion)) {
        cout << "Datos ingresados en la base de datos." << endl;
    } else {
        cerr << "Error al ingresar los datos." << endl;
    }

    // Recuperar las mediciones de la base de datos

    Medicion medicionRecuperada;
    if (db.Recuperar(medicionRecuperada)) {
        cout << "Medicion recuperada: " << medicionRecuperada << "TEST" << endl;
    } else {
        cerr << "Error al recuperar los datos." << endl;
    }

    db.Cerrar_DB();

    return 0;
}
