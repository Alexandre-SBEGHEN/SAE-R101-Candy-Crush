/**
 * @file language.h
 * @brief Fichier header de traductions des textes
 * @author Alexandre SBEGHEN
 * @date 24/12/2025
 * @version 1.2
 */
#ifndef LANGUAGE_H
#define LANGUAGE_H
#include <iostream>
#include <map>
#include <fstream>
using namespace std;

//Créer le type de donnée `gametexts` -> la table des textes du jeu
using gametexts = map<string, string>;

/**
 * @brief Prend un entrée le nom d'un fichier .lang, et renvoie la map de tous les textes du jeu dans la langue en question, sous forme de map.
 * 
 * @param filename Le nom du fichier sous forme de `string`.
 * @return La map des textes du jeu.
 */
gametexts language_get_text_map_from_file(const string & filename);

 #endif