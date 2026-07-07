#pragma once

#include "load_dataset.h"
#include "tabla_hash.h"
#include <iostream>
#include <filesystem>


int main() {


	std::cout << "inicio" <<std::endl; 

	HashTable* tabla = new HashTable(101, Probing::LINEAR);

	load_para_user_id(tabla);

	std::cout << "fin" << std::endl;

	return 0;

}