#pragma once
#include <unordered_map>
#include <string>
#include <fstream>
#include <iostream>
#include "tabla_hash.h"



//carga el dataset en una estructura HashTable usando user_id como clave

void load_para_user_id(HashTable* tabla_hash);

//carga el dataset en una estructura HashTableusando user_screen_name como clave

void load_para_user_screen_name(HashTable* tabla_hash);

