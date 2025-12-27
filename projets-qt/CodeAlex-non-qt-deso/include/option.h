/**
 * @file option.h
 * @brief Fichier header de gestion d'options de lancement du programme
 * @author Alexandre SBEGHEN
 * @date 27/12/2025
 * @version 1.0
 */
#ifndef OPTION_H
#define OPTION_H
#include <iostream>
#include <map>
using namespace std;

//Créer le type de donnée `execoptn` -> la table des options de lancement
using execoption = map<string, string>;

/**
 * @brief Vérifie que les options d'éxécution du programme soient valides.
 * 
 * Il doit y avoir soit aucune option, soit un ou plusieurs COUPLES (option, valeur).
 * 
 * Mettre des options inexistantes n'aura aucun effet tant qu'elles sont enregistrées correctement.
 * 
 * @param argc Le nombre d'arguments lors de l'appel du programme.
 * @return La validité des options d'exécution.
 */
bool option_assert_validity(const int & argc);

/**
 * @brief Insère ou modifie les options d'exécution dans une/d'une table `execoption`.
 * 
 * @param options La table `execoption` à modifier.
 * @param argc Le nombre d'arguments lors de l'exécution du programme.
 * @param arg La liste des arguments.
 */
void option_parse_to(execoption & options, int argc, char** arg);


#endif