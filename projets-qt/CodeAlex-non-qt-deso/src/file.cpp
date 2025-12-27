/**
 * @file file.cpp
 * @brief Script de gestion de flux d'entrée et de sortie
 * @author Alexandre SBEGHEN
 * @date 26/12/2025
 * @version 1.0
 */
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include "../include/file.h"
using namespace std;

/* Corps de la fonction `` qui lit une ligne d'un fichier de type `` et la renvoie sous forme de string */
string file_readline(ifstream & file) {
    string line;
    while (!file.eof()) {
        getline(file, line);
        if (line.length() > 0 && line.substr(0, 2) != "//") break;
    }
    return line;
}

/* Corps de la foction `file_line_to_key` qui renvoie la clé d'un couple clé/valeur passé en paramètre sous forme de string */
string file_line_to_key(const string & line) {
    size_t substr_index = 0;
    while (line[substr_index] != ' ' || line[substr_index + 1] != ' ') ++substr_index;
    return line.substr(0, substr_index);
}

/* Corps de la foction `file_line_to_val` qui renvoie la valeur d'un couple clé/valeur passé en paramètre sous forme de string */
string file_line_to_val(const string & line) {
    size_t substr_index = line.length() - 1;
    while (line[substr_index] != ' ' || line[substr_index - 1] != ' ') --substr_index; //Vérifier 2 espaces pour que la valeur puisse elle même en contenir (ex: 'hello  bon jour' -> 'bon jour')
    return line.substr(substr_index, line.length() - substr_index);
}

/* Corps du précidat `file_exists` qui vérifie l'existence ou non d'un fichier (dossier inclus) */
bool file_exists(const string & filename) {
    ifstream file(filename);
    return file.good();
}