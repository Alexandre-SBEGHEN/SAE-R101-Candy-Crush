/**
 * @file file.h
 * @brief Fichier header pour la gestion de flux d'entrée et de sortie
 * @author Alexandre SBEGHEN
 * @date 26/12/2025
 * @version 1.0
 */
#ifndef FILE_H
#define FILE_H
#include <iostream>
#include <fstream>
using namespace std;

/**
 * @brief Lit une ligne issue d'un fichier en ignorant les lignes commentées (`//`)
 * 
 * @param file Le fichier de type `ifstream`
 * @return La ligne lue sous forme de string
 */
string file_readline(ifstream & file);

/**
 * @brief Prend en entrée une ligne qui contient la clé de la map et sa valeurs séparés par minimum DEUX espaces, et renvoie la string de la clé.
 * 
 * @param line La string de la ligne qui contient le couple clé/valeur.
 * @return La clé sous forme de string.
 */
string file_line_to_key(const string & line);

/**
 * @brief Prend en entrée une ligne qui contient la clé de la map et sa valeurs séparés par minimum DEUX espaces, et renvoie la string de la valeur.
 * 
 * @param line La string de la ligne qui contient le couple clé/valeur.
 * @return La valeur sous forme de string.
 */
string file_line_to_val(const string & line);

#endif