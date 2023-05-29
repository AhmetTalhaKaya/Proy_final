#include "sensor.h"

using namespace std;

//No olvidar implementarlo en main !!
bool Sensor::Actualizar(Medicion& med) {
    // Generar valores aleatorios para las mediciones
    med.temperatura = -10 + (rand() % 56);  // Valor aleatorio entre -10 y 45
    med.humedad = rand() % 101;  // Valor aleatorio entre 0 y 100
    med.precipitacion = rand() % 51;  // Valor aleatorio entre 0 y 50
    med.intensidadLuz = rand() % 2001;  // Valor aleatorio entre 0 y 2000

    return true;
}

