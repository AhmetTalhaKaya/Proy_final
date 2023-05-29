#ifndef DB_LOCAL_H
#define DB_LOCAL_H

#include <string>
#include <sqlite3.h>
#include "medicion.h"

using namespace std;

class DB_Local {
public:
    DB_Local(const string& url);
    bool CrearTabla();
    bool Abrir_DB();
    bool Ingresar(const Medicion& med);
    bool Recuperar(Medicion& prom);
    bool Cerrar_DB();

private:
    string url;
    sqlite3* db;
};

#endif // DB_LOCAL_H


