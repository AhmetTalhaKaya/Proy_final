#include "db_local.h"
#include "medicion.h"
#include <iostream>

using namespace std;

DB_Local::DB_Local(const string& url) : url(url), db(nullptr) {}

bool DB_Local::CrearTabla(){
    string consulta = "CREATE TABLE IF NOT EXISTS mediciones("
                          "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                          "temperatura REAL,"
                          "humedad REAL,"
                          "precipitacion REAL,"
                          "intensidad_luz REAL,"
                          "timestamp DATETIME DEFAULT CURRENT_TIMESTAMP)";


        char* errMsg;
        int resultado = sqlite3_exec(db, consulta.c_str(), nullptr, nullptr, &errMsg);
        if (resultado != SQLITE_OK) {
            cerr << "Error al crear la tabla: " << errMsg << endl;
            sqlite3_free(errMsg);
            return false;
        }
        return true;

}

bool DB_Local::Abrir_DB() {
    int result = sqlite3_open(url.c_str(), &db);
    if (result != SQLITE_OK) {
        cerr << "Error al abrir la base de datos: " << sqlite3_errmsg(db) << endl;
        return false;
    }
    return true;
}

bool DB_Local::Ingresar(const Medicion& med) {
    if (!db) {
        cerr << "Error: Base de datos no abierta." << endl;
        return false;
    }
    // Como poner valores creados al VALUES ??
    string query = "INSERT INTO mediciones(temperatura, humedad, precipitacion, intensidad_luz) VALUES ("
                        + to_string(med.temperatura) + ", "
                        + to_string(med.humedad) + ", "
                        + to_string(med.precipitacion) + ", "
                        + to_string(med.intensidadLuz) + ");";

    char* errMsg;
    int result = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errMsg);
    if (result != SQLITE_OK) {
        cerr << "Error al ingresar los datos en la base de datos: " << errMsg << endl;
        sqlite3_free(errMsg);
        return false;
    }

    return true;
}

bool DB_Local::Recuperar(Medicion& prom) {
    if (!db) {
        cerr << "Error: Base de datos no abierta." << endl;
        return false;
    }

    string query = "SELECT AVG(temperatura), AVG(humedad), AVG(precipitacion), AVG(intensidad_luz) FROM mediciones;";

    char* errMsg;
    int result = sqlite3_exec(
        db,
        query.c_str(),
        [](void* data, int argc, char** argv, char** /*colNames*/) {
            if (argc == 4) {
                Medicion* promedio = static_cast<Medicion*>(data);
                promedio->temperatura = stof(argv[0]);
                promedio->humedad = stof(argv[1]);
                promedio->precipitacion = stof(argv[2]);
                promedio->intensidadLuz = stof(argv[3]);
            }
            return 0;
        },
        &prom,
        &errMsg);

    if (result != SQLITE_OK) {
        cerr << "Error al recuperar los datos de la base de datos: " << errMsg << endl;
        sqlite3_free(errMsg);
        return false;
    }

    return true;
}

bool DB_Local::Cerrar_DB() {
    if (db) {
        int result = sqlite3_close(db);
        if (result != SQLITE_OK) {
            cerr << "Error al cerrar la base de datos: " << sqlite3_errmsg(db) << endl;
            return false;
        }
        db = nullptr;
    }
    return true;
}



