#pragma once
#include <unordered_map>
#include <string>
#include <fstream>
#include <iostream>
#include "tabla_hash.h"
#include <chrono>



enum Clave { USER_ID, USER_SCREEN_NAME };










double load_dataset(HashTable* tabla_hash,int limite_de_tweets, Clave clave);


