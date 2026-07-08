
#include "load_dataset.h"
#include "tabla_hash.h"
#include <iostream>
#include <filesystem>
#include <vector>
#include <cmath>




int cant_tweets[4] = { 10000,20000,30000,180000 };

double desviacion_estandar_muestral(double suma, const std::vector<double>& datos);

void linear_probing_user_id();

void linear_probing_user_screen_name();

void quadratic_probing_user_id();

void quadratic_probing_user_screen_name();


int main() {

    std::cout << "inicio" << std::endl;

    linear_probing_user_id();

    linear_probing_user_screen_name();

    quadratic_probing_user_id();

    quadratic_probing_user_screen_name();

	std::cout << "fin" << std::endl;

	return 0;

}

double desviacion_estandar_muestral(double suma, const std::vector<double>& datos) {

    double media = suma / 20.0;

    double sumatoria = 0.0;

    for (double x : datos) {
        sumatoria += std::pow(x - media, 2);
    }

    double varianza = sumatoria / 19;

    return std::sqrt(varianza);
}




void linear_probing_user_id() {

    //para cada una de las 4 cantidades de tweets definidas en el arreglo

    for (int i=0 ; i < 4;i++) {

        //almacena los tiempos de cada una de las 20 iteraciones

        std::vector<double> tiempos;

        double suma = 0;

        double media = 0;

        double peso = 0;

        //20 iteraciones para sacar media y desviacion estandar
        
        for (int j = 0; j< 20;j++) {

            //tabla vacia

            HashTable* tabla = new HashTable(101, Probing::LINEAR);

            //se carga el dataset, se añade el tiempo del insert interno a la suma y se inserta en el vector

            double tiempo = load_dataset(tabla, cant_tweets[i], Clave::USER_ID);

            suma += tiempo;

            tiempos.push_back(tiempo);

            if (j == 19) {

                peso = tabla->memory_usage();

            }
            
            //se libera la memoria
            delete tabla;
        }

        media = suma / 20.0;


        std::cout << "linear probing, clave: user_id , tamanio: " << cant_tweets[i] << "\n" << std::endl;

        for (int k = 0; k < 20;k++) {
        
            std::cout << "tiempo iteracion " << k+1 << " : " << tiempos[k] <<std::endl;

        }

        std::cout << "media: "<< media << std::endl;

        std::cout << "desviacion estandar muestral: " << desviacion_estandar_muestral(suma, tiempos)<< std::endl;

        std::cout << "peso de la estructura: " << peso << "\n" << std::endl;
        
       
    }
}

void linear_probing_user_screen_name() {

    //para cada una de las 4 cantidades de tweets definidas en el arreglo

    for (int i = 0; i < 4;i++) {

        //almacena los tiempos de cada una de las 20 iteraciones

        std::vector<double> tiempos;

        double suma = 0;

        double media = 0;

        double peso = 0;

        //20 iteraciones para sacar media y desviacion estandar

        for (int j = 0; j < 20;j++) {

            //tabla vacia

            HashTable* tabla = new HashTable(101, Probing::LINEAR);

            //se carga el dataset, se añade el tiempo del insert interno a la suma y se inserta en el vector

            double tiempo = load_dataset(tabla, cant_tweets[i], Clave::USER_SCREEN_NAME);

            suma += tiempo;

            tiempos.push_back(tiempo);

            if (j == 19) {

                peso = tabla->memory_usage();

            }

            //se libera la memoria
            delete tabla;
        }

        media = suma / 20.0;


        std::cout << "linear probing, clave: user_screen_name , tamanio: " << cant_tweets[i] << "\n" << std::endl;

        for (int k = 0; k < 20;k++) {

            std::cout << "tiempo iteracion " << k + 1 << " : " << tiempos[k] << std::endl;

        }

        std::cout << "media: " << media << std::endl;

        std::cout << "desviacion estandar muestral: " << desviacion_estandar_muestral(suma, tiempos) << std::endl;

        std::cout << "peso de la estructura: " << peso << "\n" << std::endl;


    }
}


void quadratic_probing_user_id() {

    //para cada una de las 4 cantidades de tweets definidas en el arreglo

    for (int i = 0; i < 4;i++) {

        //almacena los tiempos de cada una de las 20 iteraciones

        std::vector<double> tiempos;

        double suma = 0;

        double media = 0;

        double peso = 0;

        //20 iteraciones para sacar media y desviacion estandar

        for (int j = 0; j < 20;j++) {

            //tabla vacia

            HashTable* tabla = new HashTable(101, Probing::QUADRATIC);

            //se carga el dataset, se añade el tiempo del insert interno a la suma y se inserta en el vector

            double tiempo = load_dataset(tabla, cant_tweets[i], Clave::USER_ID);

            suma += tiempo;

            tiempos.push_back(tiempo);

            if (j == 19) {

                peso = tabla->memory_usage();

            }

            //se libera la memoria
            delete tabla;
        }

        media = suma / 20.0;


        std::cout << "quadratic probing, clave: user_id, tamanio: " << cant_tweets[i] << "\n" << std::endl;

        for (int k = 0; k < 20;k++) {

            std::cout << "tiempo iteracion " << k + 1 << " : " << tiempos[k] << std::endl;

        }

        std::cout << "media: " << media << std::endl;

        std::cout << "desviacion estandar muestral: " << desviacion_estandar_muestral(suma, tiempos) << std::endl;

        std::cout << "peso de la estructura: " << peso << "\n" << std::endl;


    }
}


void quadratic_probing_user_screen_name() {

    //para cada una de las 4 cantidades de tweets definidas en el arreglo

    for (int i = 0; i < 4;i++) {

        //almacena los tiempos de cada una de las 20 iteraciones

        std::vector<double> tiempos;

        double suma = 0;

        double media = 0;

        double peso = 0;

        //20 iteraciones para sacar media y desviacion estandar

        for (int j = 0; j < 20;j++) {

            //tabla vacia

            HashTable* tabla = new HashTable(101, Probing::QUADRATIC);

            //se carga el dataset, se añade el tiempo del insert interno a la suma y se inserta en el vector

            double tiempo = load_dataset(tabla, cant_tweets[i], Clave::USER_SCREEN_NAME);

            suma += tiempo;

            tiempos.push_back(tiempo);

            if (j == 19) {

                peso = tabla->memory_usage();

            }

            //se libera la memoria
            delete tabla;
        }

        media = suma / 20.0;


        std::cout << "quadratic probing, clave: user_screen_name, tamanio: " << cant_tweets[i] << "\n" << std::endl;

        for (int k = 0; k < 20;k++) {

            std::cout << "tiempo iteracion " << k + 1 << " : " << tiempos[k] << std::endl;

        }

        std::cout << "media: " << media << std::endl;

        std::cout << "desviacion estandar muestral: " << desviacion_estandar_muestral(suma, tiempos) << std::endl;

        std::cout << "peso de la estructura: " << peso << "\n" << std::endl;


    }
}



