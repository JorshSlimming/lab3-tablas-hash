#pragma once
#include <unordered_map>
#include <string>
#include <fstream>
#include <iostream>
#include "tabla_hash.h"



//carga el dataset en una estructura HashTable con linear probing , la cual es retornada 

HashTable load_en_linear_probing();


//carga el dataset en una estructura HashTable con quadratic probing, la cual es retornada

HashTable load_en_quadratic_probing();

