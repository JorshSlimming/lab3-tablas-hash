#pragma once

#include "load_dataset.h"
#include "tabla_hash.h"
#include <iostream>
#include <filesystem>


int main() {


	std::cout << "inicio" <<std::endl; 

	HashTable* tabla = new HashTable(101, Probing::LINEAR);

	load_dataset(tabla, 10.000, Clave::USER_ID);

	std::cout << "fin" << std::endl;

	return 0;

}