/**
 * @file language.cpp
 * @brief Script de traductions des textes
 * @author Alexandre SBEGHEN
 * @date 24/12/2025
 */
#include <iostream>
#include <map>
#include <fstream>
#include "../include/language.h"
using namespace std;

/* Corps de la fonction `` qui lit une ligne d'un fichier de type `` et la renvoie sous forme de string */
string language_file_readline(ifstream & file) {
    string line;
    while (true) {
        getline(file, line);
        if (line.substr(0, 2) != "//") break;
    }
    return line;
}

/* Corps de la foction `language_line_to_key` qui renvoie la clé d'un couple clé/valeur passé en paramètre sous forme de string */
string language_line_to_key(const string & line) {
    size_t substr_index = 0;
    while (line[substr_index] != ' ') ++substr_index;
    return line.substr(0, substr_index);
}

/* Corps de la foction `language_line_to_val` qui renvoie la valeur d'un couple clé/valeur passé en paramètre sous forme de string */
string language_line_to_val(const string & line) {
    size_t substr_index = line.length() - 1;
    while (line[substr_index] != ' ' || line[substr_index - 1] != ' ') --substr_index; //Vérifier 2 espaces pour que la valeur puisse elle même en contenir (ex: 'hello  bon jour' -> 'bon jour')
    return line.substr(substr_index, line.length() - substr_index);
}

/* Corps de la fonction `language_get_text_map_from_file` qui crée la map de tous les textes du jeu à partir d'un fichier */
map<string, string> language_get_text_map_from_file(const string & filename) {
    ifstream file(filename);

    //Récupérer le nom de langue
    const string FILE_LANG = language_file_readline(file);
    map<string, string> text_map;
    text_map["LANGUAGE"] = FILE_LANG;
    
    //Récupérer les couples clé/valeur et les assiner à 'text_map'
    while (!file.eof()) {
        string line = language_file_readline(file);
        string key = language_line_to_key(line);
        string val = language_line_to_val(line);
        text_map[key] = val;
    }

    //Renvoyer la map
    return text_map;
}