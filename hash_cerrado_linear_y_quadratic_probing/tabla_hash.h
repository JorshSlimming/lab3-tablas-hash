#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

enum State { EMPTY, OCCUPIED, DELETED };

enum Probing { LINEAR,QUADRATIC };

struct Entry {
    string key;
    int value;
    State state;

    Entry() : key(""), value(0), state(EMPTY) {}
};

const float A = (sqrt(5) - 1) / 2;

int h1(string k, int n);


// Linear Probing
int linear_probing(string k, int n, int i);

// Quadratic Probing
int quadratic_probing(string k, int n, int i);


class HashTable {
private:
    vector<Entry> table;
    int size;
    //cantidad de elementos ocupados
    int elements = 0;


    //va a almacenar el tipo de probing de la tabla
    Probing tipo_de_probing;


public:


    //el tipo de probing de la tabla se define desde el constructor

    HashTable(int tableSize, Probing probing ) : size(tableSize) {

        tipo_de_probing = probing;

        table.resize(size);
    }

    
  
    int probe(string key, int i);

    void insert(string key, int value);

    int get(string key);

    void remove(string key);

    Probing getProbing();
    
    bool is_prime(int n);

    int next_prime(int n);

    //resize para rehashing

    void resize();

    //para obtener el peso de la tabla

    size_t memory_usage() const;

};


