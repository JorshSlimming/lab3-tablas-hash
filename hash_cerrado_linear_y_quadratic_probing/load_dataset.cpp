#include "load_dataset.h"



double load_dataset(HashTable* tabla_hash, int limite_de_tweets, Clave clave) {


    std::ifstream file("../../auspol2019.csv");

    if (!file.is_open()) {



        std::cout << "no se pudo abrir el archivo auspol2019.csv" << std::endl;



        return 0.0;

    }





    double tiempo = 0;


    std::string linea;



    std::getline(file, linea);



    int numero_coma_antes;



    int numero_coma_despues;





    if (clave == Clave::USER_ID) {

        numero_coma_antes = 5;
        numero_coma_despues = 6;
    }

    else if (clave == Clave::USER_SCREEN_NAME) {

        numero_coma_antes = 7;
        numero_coma_despues = 8;
    }




    int contador_de_tweets = 0;



    int contador_de_comas_por_registro = 0;





    bool coma_antes_encontrada = false;



    bool coma_despues_encontrada = false;




    bool dentro_de_comillas = false;



    string id = "";

    while (std::getline(file, linea)) {





        for (int i = 0; i < linea.size(); i++) {



            if (i + 1 < linea.size() && linea[i] ==',' && linea[i+1]=='"') {

                dentro_de_comillas = true;

                contador_de_comas_por_registro++;

            }



            if (i + 1 < linea.size() && (linea[i] == '"' && linea[i+1] == ',') && dentro_de_comillas == true) {

                dentro_de_comillas = false;

            }


            else if (linea[i] == ',' && dentro_de_comillas == false) {

                contador_de_comas_por_registro++;

            }




            if (coma_antes_encontrada && !coma_despues_encontrada && linea[i] != ',') {

                id += linea[i];

            }


            if (contador_de_comas_por_registro == numero_coma_antes) {

                coma_antes_encontrada = true;

            }

            if (contador_de_comas_por_registro == numero_coma_despues) {

                coma_despues_encontrada = true;

                coma_antes_encontrada = false;





                auto inicio = std::chrono::high_resolution_clock::now();

                tabla_hash->insert(id, tabla_hash->get(id)+1);

                auto fin = std::chrono::high_resolution_clock::now();

                double tiempo_insercion = std::chrono::duration<double, std::micro>(fin - inicio).count();

                tiempo += tiempo_insercion;



                id.clear();

            }



            if (contador_de_comas_por_registro == 10) {

                contador_de_comas_por_registro = 0;

                coma_antes_encontrada = false;

                coma_despues_encontrada = false;

                contador_de_tweets++;



                if (contador_de_tweets >= limite_de_tweets) {

                    file.close();

                    return tiempo;

                }

            }

        }


    }



    file.close();

    return tiempo;

}
