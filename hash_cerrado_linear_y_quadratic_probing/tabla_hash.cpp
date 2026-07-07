#include "tabla_hash.h"

int h1(int k, int n) {
    return k % n;
};

int h2(int k, int n) {
    float a = (float)k * A;
    a -= (int)a;
    return n * a;
}


int linear_probing(int k, int n, int i) {
    return (h1(k, n) + i) % n;
}

int quadratic_probing(int k, int n, int i) {
    return (h1(k, n) + i + 2 * i * i) % n;
}


//la funcion hash usada es la correspondiente al probing de la tabla

int HashTable::probe(int key, int i) {

    if (tipo_de_probing == Probing::LINEAR) {

        return linear_probing(key, size, i);

    }

    return quadratic_probing(key, size, i);

}

void HashTable::insert(int key, string value) {
    for (int i = 0; i < size; i++) {
        int index = probe(key, i);

        if (table[index].state == EMPTY || table[index].state == DELETED) {
            table[index].key = key;
            table[index].value = value;
            table[index].state = OCCUPIED;
            return;
        }

        // Si ya existe, actualizar
        if (table[index].state == OCCUPIED && table[index].key == key) {
            table[index].value = value;
            return;
        }
    }

    cout << "Tabla llena, no se pudo insertar " << key << endl;
}

string HashTable::get(int key) {
    for (int i = 0; i < size; i++) {
        int index = probe(key, i);
        if (table[index].state == EMPTY) break; // ya no va a aparecer

        if (table[index].state == OCCUPIED && table[index].key == key) {
            return table[index].value;
        }
    }
    return "No encontrado";
}

void HashTable::remove(int key) {
    for (int i = 0; i < size; i++) {
        int index = probe(key, i);

        if (table[index].state == EMPTY) break;

        if (table[index].state == OCCUPIED && table[index].key == key) {
            table[index].state = DELETED;
            return;
        }
    }
}




