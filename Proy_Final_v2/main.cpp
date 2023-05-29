#include <iostream>
#include "db_local.h"
#include "medicion.h"
#include <vector>
#include <chrono>
#include <thread>
#include <random>

using namespace std;

void delay(unsigned int millisec) {
    this_thread::sleep_for(chrono::milliseconds(millisec));
}

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

    vector<Medicion> mediciones;
    double sumaTemperatura = 0.0;
    double sumaHumedad = 0.0;
    double sumaPrecipitacion = 0.0;
    double sumaIntensidadLuz = 0.0;
    int contador = 0;

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> tempDist(-10.0, 45.0);  // Distribución uniforme entre -10.0 y 45.0
    uniform_real_distribution<double> humDist(0.0, 100.0);  // Distribución uniforme entre 0.0 y 100.0
    uniform_real_distribution<double> precDist(0.0, 50.0);  // Distribución uniforme entre 0.0 y 50.0
    uniform_real_distribution<double> luzDist(0.0, 2000.0);  // Distribución uniforme entre 0.0 y 2000.0


    while (true) {
        delay(5000);

        Medicion medicion;
        // Generar valores aleatorios para las mediciones
        medicion.temperatura   = tempDist(gen);
        medicion.humedad       = humDist(gen);
        medicion.precipitacion = precDist(gen);
        medicion.intensidadLuz = luzDist(gen);

        // Insertar la medición en la base de datos
        if (db.Ingresar(medicion)) {
            cout << "Datos ingresados en la base de datos." << endl;
        } else {
            cerr << "Error al ingresar los datos." << endl;
        }

        // Sumar los valores de las mediciones
        sumaTemperatura += medicion.temperatura;
        sumaHumedad += medicion.humedad;
        sumaPrecipitacion += medicion.precipitacion;
        sumaIntensidadLuz += medicion.intensidadLuz;
        contador++;

        cout << "Temperatura: " << medicion.temperatura << "°C" <<endl;
        cout << "Humedad: " << medicion.humedad << "%" << endl;
        cout << "Precipitacion: " << medicion.precipitacion << " mm" << endl;
        cout << "Intensidad de Luz: " << medicion.intensidadLuz << " lumen" << endl;

        if (contador == 12) { // No olvida cambiar a 12 despues -
            double promedioTemperatura = sumaTemperatura / contador;
            double promedioHumedad = sumaHumedad / contador;
            double promedioPrecipitacion = sumaPrecipitacion / contador;
            double promedioIntensidadLuz = sumaIntensidadLuz / contador;

            Medicion promedio;
            promedio.temperatura = promedioTemperatura;
            promedio.humedad = promedioHumedad;
            promedio.precipitacion = promedioPrecipitacion;
            promedio.intensidadLuz = promedioIntensidadLuz;

            cout << "Promedio de temperatura: " << promedio.temperatura << "°C" <<endl;
            cout << "Promedio de humedad: " << promedio.humedad << "%" <<endl;
            cout << "Promedio de precipitación: " << promedio.precipitacion << " mm" << endl;
            cout << "Promedio de intensidad de luz: " << promedio.intensidadLuz << " lumen" <<  endl;


            // Reiniciar las variables para el próximo promedio
            sumaTemperatura = 0.0;
            sumaHumedad = 0.0;
            sumaPrecipitacion = 0.0;
            sumaIntensidadLuz = 0.0;
            contador = 0;
        }
    }

    db.Cerrar_DB();

    return 0;
}
