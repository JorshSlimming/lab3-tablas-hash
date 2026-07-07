#include "load_dataset.h"



void load_para_user_id(HashTable* tabla_hash) {


   
    std::ifstream file("../../auspol2019.csv");

    if (!file.is_open()) {



        std::cout << "no se pudo abrir el archivo auspol2019.csv" << std::endl;

        //falta aun cambiar el retorno

        return;

    }

    std::cout << "archivo auspol2019 abierto con exito" << std::endl;

    std::string linea;

    //se lee la 1ra linea dado que solo contiene la organizacion de los datos

    std::getline(file, linea);

    int contador_de_comas_por_registro = 0;

    //variables que serviran para saber si se esta entre la 5ta coma y 6ta coma de un registro que es donde esta el user_id

    bool quinta_coma_encontrada = false;

    bool sexta_coma_encontrada = false;

    //sera true cuando se encuentre ',' seguido de " , lo que significa que se entro a un campo de texto, por lo cual las comas
    //dentro no cuentan como separadores de columnas

    bool dentro_de_comillas = false;

    //almacena el ultimo user_id encontrado

    string user_id = "";

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


            //se le concatenan a user_id los caracteres entre la 5ta y 6ta coma

            if (quinta_coma_encontrada && !sexta_coma_encontrada && linea[i] != ',') {

                user_id += linea[i];

            }


            if (contador_de_comas_por_registro == 5) {

                quinta_coma_encontrada = true;

            }

            if (contador_de_comas_por_registro == 6) {

                sexta_coma_encontrada = true;

                quinta_coma_encontrada = false;


                //se inserta el elemento a la tabla con valor= valor_actual + 1 (la cantidad de tweets del usuario con ese user_id)

                tabla_hash->insert(user_id, tabla_hash->get(user_id)+1);

                //se vacia user_id 

                user_id.clear();

            }

            //si se encontro la decima coma se termino el registro y por ende se reinician las variables

            if (contador_de_comas_por_registro == 10) {

                contador_de_comas_por_registro = 0;

                quinta_coma_encontrada = false;

                sexta_coma_encontrada = false;

            }
  

        }
        

    }


    file.close();


}