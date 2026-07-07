#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

enum State { EMPTY, OCCUPIED, DELETED };

enum Probing { LINEAR,QUADRATIC };

struct Entry {
    int key;
    string value;
    State state;

    Entry() : key(0), value(""), state(EMPTY) {}
};

const float A = (sqrt(5) - 1) / 2;

int h1(int k, int n);

int h2(int k, int n);

// Linear Probing
int linear_probing(int k, int n, int i);

// Quadratic Probing
int quadratic_probing(int k, int n, int i);


class HashTable {
private:
    vector<Entry> table;
    int size;


    //va a almacenar el tipo de probing de la tabla
    Probing tipo_de_probing;


public:

    //el tipo de probing de la tabla se define desde el constructor

    HashTable(int tableSize, Probing probing ) : size(tableSize) {

        tipo_de_probing = probing;

        table.resize(size);
    }

    
  
    int probe(int key, int i);

    void insert(int key, string value);

    string get(int key);

    void remove(int key);

};


