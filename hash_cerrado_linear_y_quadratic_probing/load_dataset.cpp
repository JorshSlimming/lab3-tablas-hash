#include "load_dataset.h"



double load_dataset(HashTable* tabla_hash, int limite_de_tweets, Clave clave) {


    std::ifstream file("../../auspol2019.csv");

    if (!file.is_open()) {



        std::cout << "no se pudo abrir el archivo auspol2019.csv" << std::endl;

        //falta aun cambiar el retorno

        return 0.0;

    }

    //std::cout << "archivo auspol2019 abierto con exito" << std::endl;

    //tiempo total

    double tiempo = 0;


    std::string linea;

    //se lee la 1ra linea dado que solo contiene la organizacion de los datos

    std::getline(file, linea);

    //el numero de la coma que esta antes del id

    int numero_coma_antes;

    //el numero de la coma que esta despues del id

    int numero_coma_despues;


    //si la clave es user_id este estara entre las comas 5 y 6 del registro, si es user_screen_name este estara entre las comas 7 y 8 del
    //registro

    if (clave == Clave::USER_ID) {

        numero_coma_antes = 5;
        numero_coma_despues = 6;
    }

    else if (clave == Clave::USER_SCREEN_NAME) {

        numero_coma_antes = 7;
        numero_coma_despues = 8;
    }


    //contador general de tweets leidos 

    int contador_de_tweets = 0;

    //contador de comas del registro que se reinicia a 0 al llegar a 10

    int contador_de_comas_por_registro = 0;

    //variables que serviran para saber si se esta entre las comas que encierran el id del

    //coma antes del id

    bool coma_antes_encontrada = false;

    //coma despues del id

    bool coma_despues_encontrada = false;

    //sera true cuando se encuentre ',' seguido de " , lo que significa que se entro a un campo de texto, por lo cual las comas
    //dentro no cuentan como separadores de columnas

    bool dentro_de_comillas = false;

    //variable que permite concatenar y almacenar el id del registro actual

    string id = "";

    while (std::getline(file, linea)) {

       // std::cout << "en curso" << std::endl;

        //se recorren los caracteres de la linea
     
        for (int i = 0; i < linea.size(); i++) {

            //si se encontro una coma y el siguiente caracter es " se dejan de contar las comas

            if (i + 1 < linea.size() && linea[i] ==',' && linea[i+1]=='"') {

                dentro_de_comillas = true;

                contador_de_comas_por_registro++;

            }

            //si se encontro un " y el siguiente caracter es una coma se vuelven a contar las comas

            if (i + 1 < linea.size() && (linea[i] == '"' && linea[i+1] == ',') && dentro_de_comillas == true) {

                dentro_de_comillas = false;

            }


            else if (linea[i] == ',' && dentro_de_comillas == false) {

                contador_de_comas_por_registro++;

            }


            //se le concatenan al string id los caracteres entre coma antes del id y la coma despues del id

            if (coma_antes_encontrada && !coma_despues_encontrada && linea[i] != ',') {

                id += linea[i];

            }


            if (contador_de_comas_por_registro == numero_coma_antes) {

                coma_antes_encontrada = true;

            }

            if (contador_de_comas_por_registro == numero_coma_despues) {

                coma_despues_encontrada = true;

                coma_antes_encontrada = false;


               
                //se inserta el elemento a la tabla con valor= valor_actual + 1 (la cantidad de tweets del usuario con ese id)
               
                auto inicio = std::chrono::high_resolution_clock::now();
    
                tabla_hash->insert(id, tabla_hash->get(id)+1);

                auto fin = std::chrono::high_resolution_clock::now();

                double tiempo_insercion = std::chrono::duration<double, std::micro>(fin - inicio).count();

                tiempo += tiempo_insercion;

                //la variable que almacena el id se vacia 

                id.clear();

            }

            //si se encontro la decima coma se termino el registro y por ende se reinician las variables, se cuenta un tweet

            if (contador_de_comas_por_registro == 10) {

                contador_de_comas_por_registro = 0;

                coma_antes_encontrada = false;

                coma_despues_encontrada = false;

                contador_de_tweets++;

                //si se llega a la cantidad de tweets pedidos se cierra el archivo y termina el metodo

                if (contador_de_tweets >= limite_de_tweets) {

                    file.close();

                    return tiempo;

                }

            }  

        }
        

    }

    //se cierra el archivo

    file.close();

    return tiempo;

}