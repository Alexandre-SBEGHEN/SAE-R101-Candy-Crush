/**
 * @file language.h
 * @brief Fichier header de traductions des textes
 * @author Alexandre SBEGHEN
 * @date 24/12/2025
 */
#include <iostream>
#include <map>
#include <fstream>
using namespace std;
#ifndef LANGUAGE_H
#define LANGUAGE_H

/**
 * @brief Lit une ligne issue d'un fichier en ignorant les lignes commentées (`//`)
 * 
 * @param file Le fichier de type `ifstream`
 * @return La ligne lue sous forme de string
 */
string language_file_readline(ifstream & file);

/**
 * @brief Prend en entrée une ligne qui contient la clé de la map et sa valeurs séparés par minimum DEUX espaces, et renvoie la string de la clé.
 * 
 * @param line La string de la ligne qui contient le couple clé/valeur.
 * @return La clé sous forme de string.
 */
string language_line_to_key(const string & line);

/**
 * @brief Prend en entrée une ligne qui contient la clé de la map et sa valeurs séparés par minimum DEUX espaces, et renvoie la string de la valeur.
 * 
 * @param line La string de la ligne qui contient le couple clé/valeur.
 * @return La valeur sous forme de string.
 */
string language_line_to_val(const string & line);

/**
 * @brief Prend un entrée le nom d'un fichier .lang, et renvoie la map de tous les textes du jeu dans la langue en question, sous forme de map.
 * 
 * @param filename Le nom du fichier sous forme de `string`.
 * @return La map des textes du jeu.
 */
map<string, string> language_get_text_map_from_file(const string & filename);

 #endif