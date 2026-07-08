#pragma once
#include <unordered_map>
#include <string>
#include <fstream>
#include <iostream>
#include "tabla_hash.h"


//claves de un tweet

enum Clave { USER_ID, USER_SCREEN_NAME };


//el metodo carga el dataset en una estructura HashTable dado un puntero a ella usando

//limite_de_tweets: indica cuantos tweets se leeran, cargaran y contaran, tras superar esa cantidad 
//el metodo terminara su ejecucion

//clave: el id de los registros del dataset que se utilizara como clave en la tabla, ya sea user_id o user_screen_name

void load_dataset(HashTable* tabla_hash,int limite_de_tweets, Clave clave);


