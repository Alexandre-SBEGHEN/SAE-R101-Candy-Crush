/**
 * @file language.h
 * @brief Fichier header de traductions des textes
 * @author Alexandre SBEGHEN
 * @date 24/12/2025
 * @version 1.3
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
 * @brief Charge les textes issus d'un fichier dans une map `gametexts`.
 * 
 * @param filename Le nom du fichier sous forme de `string`.
 * @param texts La map vers laquelle les données sont enregistrées.
 */
void language_get_texts_from_file_to(const string & filename, gametexts & texts);

 #endif