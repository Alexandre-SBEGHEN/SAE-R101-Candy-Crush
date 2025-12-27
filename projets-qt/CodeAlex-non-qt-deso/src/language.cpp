/**
 * @file language.cpp
 * @brief Script de traductions des textes
 * @author Alexandre SBEGHEN
 * @date 24/12/2025
 * @version 1.3
 */
#include <iostream>
#include <map>
#include <fstream>
#include "../include/language.h"
#include "../include/file.h"
using namespace std;

/* Corps de la fonction `language_get_text_map_from_file` qui crée la map de tous les textes du jeu à partir d'un fichier */
gametexts language_get_text_map_from_file(const string & filename) {
    ifstream file(filename);

    //Récupérer le nom de langue
    const string FILE_LANG = file_readline(file);
    gametexts text_map;
    text_map["LANGUAGE"] = FILE_LANG;
    
    //Récupérer les couples clé/valeur et les assiner à 'text_map'
    while (!file.eof()) {
        string line = file_readline(file);
        string key = file_line_to_key(line);
        string val = file_line_to_val(line);
        text_map[key] = val;
    }

    //Fermer le fichier
    file.close();

    //Renvoyer la map
    return text_map;
}