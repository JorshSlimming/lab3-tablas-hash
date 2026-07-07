#include "tabla_hash.h"

//funcion hash para clave string, suma los valores numericos de los caracteres del string y luego aplica el modulo n

int h1(string k, int n) {

    unsigned long long hash = 0;

    for (char c : k) {
        hash = hash * 31 + c;
    }

    return hash % n;
};


int linear_probing(string k, int n, int i) {
    return (h1(k, n) + i) % n;
}

int quadratic_probing(string k, int n, int i) {
    return (h1(k, n) + i + 2 * i * i) % n;
}


//la tecnica de resolucion de colisiones es la correspondiente al probing de la tabla

int HashTable::probe(string key, int i) {

    if (tipo_de_probing == Probing::LINEAR) {

        return linear_probing(key, size, i);

    }

    return quadratic_probing(key, size, i);

}

void HashTable::insert(string key, int value) {

    // Si supera el factor de carga máximo
    if ((float)(elements + 1) / size > 0.60) {
        resize();
    }

    for (int i = 0; i < size; i++) {
        int index = probe(key, i);

        if (table[index].state == EMPTY || table[index].state == DELETED) {
            table[index].key = key;
            table[index].value = value;
            table[index].state = OCCUPIED;

            elements++;

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

int HashTable::get(string key) {
    for (int i = 0; i < size; i++) {
        int index = probe(key, i);
        if (table[index].state == EMPTY) break; // ya no va a aparecer

        if (table[index].state == OCCUPIED && table[index].key == key) {
            return table[index].value;
        }
    }
    return 0;
}

void HashTable::remove(string key) {
    for (int i = 0; i < size; i++) {
        int index = probe(key, i);

        if (table[index].state == EMPTY) break;

        if (table[index].state == OCCUPIED && table[index].key == key) {
            table[index].state = DELETED;
            elements--;
            return;
        }
    }
}


Probing HashTable::getProbing(){

    return tipo_de_probing;
}

bool HashTable::is_prime(int n){
    if (n <= 1)
        return false;

    if (n == 2)
        return true;

    if (n % 2 == 0)
        return false;

    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0)
            return false;
    }

    return true;

}

int HashTable::next_prime(int n){

    while (!is_prime(n)) {
        n++;
    }

    return n;
}

void HashTable::resize(){

    int oldSize = size;

    // Nueva capacidad: siguiente primo después de duplicar
    int newSize = next_prime(size * 2);

    vector<Entry> oldTable = table;

    // Crear nueva tabla vacía
    table.clear();
    table.resize(newSize);

    size = newSize;
    elements = 0;

    // Reinsertar todos los elementos
    for (int i = 0; i < oldSize; i++) {

        if (oldTable[i].state == OCCUPIED) {
            insert(oldTable[i].key, oldTable[i].value);
        }
    }

}




