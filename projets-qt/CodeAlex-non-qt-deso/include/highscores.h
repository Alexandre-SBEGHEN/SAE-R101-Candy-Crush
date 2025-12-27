/**
 * @file highscores.h
 * @brief Fichier header pour le fonctionnement de la table des high scores
 * @author Alexandre SBEGHEN
 * @date 26/12/2025
 * @version 1.0
 */
#ifndef HIGHSCORES_H
#define HIGHSCORES_H
#include <iostream>
#include <vector>
#include <map>
using namespace std;

//Création des constantes
#define HIGHSC_MAX_PLAYERS 10 //Nombre max de joueurs à inclure dans les highscores
#define HIGHSC_FILENAME "highscores.hs" //Nom du fichier dans lequel stocker et charger les high scores

//Création des alias
using highsc_entry = pair<string, size_t>; //Une paire `(nom, score)`
using highsc_table = vector<highsc_entry>; //Une table de high scores

/**
 * @brief Prédicat pour la procédure `highscores_sort` de tri d'une table de highscores.
 * 
 * Compare deux éléments de la table des highscores pour effectuer le tri décroissant.
 * 
 * @param a La première paire `highsc_entry` de la comparaison.
 * @param b La seconde paire `highsc_entry` de la comparaison.
 * @return Le résultat de la comparison `score de a > score de b`.
 */
bool highscores_sort_condition(const highsc_entry & a, const highsc_entry & b);

/**
 * @brief Trie une table de highscores dans l'ordre décroissant de valeur.
 * 
 * Le premier élément sera le meilleur joueur, le deuxième sera le deuxième meilleur joueur, etc.
 * 
 * @param table La table `highsc_table` à trier.
 */
void highscores_sort(highsc_table & table);

/**
 * @brief Ajoute un nouveau joueur dans la table des highscores.
 * 
 * La table est supposée triée par ordre décroissant de valeur, et la paire est insérée à la bonne position.
 * 
 * @param entry La paire `highsc_table` (nom, score) à insérer dans la table.
 * @param table La table `highsc_table` dans laquelle la paire sera insérée.
 */
void highscores_insert_entry_into(const highsc_entry & entry, highsc_table & table);

/**
 * @brief Sauvegarde une table de high scores dans un fichier `.hs` (.highscore).
 * 
 * @param table La table `highsc_table` à sauvegarder.
 * @param filename Le nom du fichier dans lequel sera enregistré les scores.
 */
void highscores_saveto(const highsc_table & table, const string & filename);

/**
 * @brief Charge une table de highscores vers une table `highsc_table`.
 * 
 * @param filename Le nom du fichier depuis lequel les données seront chargées.
 * @param table La table vers laquelle les scores seront transférés.
 */
void highscores_loadto(const string & filename, highsc_table & table);

#endif