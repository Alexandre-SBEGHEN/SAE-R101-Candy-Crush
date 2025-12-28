/**
 * @file language.cpp
 * @brief Script de traductions des textes
 * @author Alexandre SBEGHEN
 * @date 24/12/2025
 * @version 1.5
 */
#include <iostream>
#include <map>
#include <fstream>
#include "../include/language.h"
#include "../include/file.h"
using namespace std;

/* Corps de la procédure `language_get_texts_from_file_to` qui crée la map de tous les textes du jeu à partir d'un fichier */
void language_get_texts_from_file_to(const string & filename, gametexts & texts) {
    ifstream file(filename);

    //Récupérer le nom de langue
    const string FILE_LANG = file_readline(file);
    
    //Effacer `texts`
    //texts.clear();
    
    //Récupérer les couples clé/valeur et les assiner à 'texts'
    while (!file.eof()) {
        string line = file_readline(file);
        if (line.length() == 0) break;
        string key = file_line_to_key(line);
        string val = file_line_to_val(line);
        texts[key] = val;
    }

    //Fermer le fichier
    file.close();
}