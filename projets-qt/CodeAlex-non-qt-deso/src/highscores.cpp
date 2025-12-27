/**
 * @file highscores.cpp
 * @brief Script pour le fonctionnement de la table des high scores
 * @author Alexandre SBEGHEN
 * @date 26/12/2025
 * @version 1.1
 */
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include "../include/highscores.h"
#include "../include/file.h"
using namespace std;

/* Corps du prédicat `highscores_sort_condition` qui sert pour le tri de la table des highscores */
bool highscores_sort_condition(const highsc_entry & a, const highsc_entry & b) {
    return a.second > b.second;
}

/* Corps de la procédure `highscores_sort` qui trie une table de highscores */
void highscores_sort(highsc_table & table) {
    sort(table.begin(), table.end(), highscores_sort_condition);
}

/* Corps de la procédure `highscores_insert_entry_into` qui insère à la bonne posisition un nouveau joueur dans la table des highscores */
void highscores_insert_entry_into(const highsc_entry & entry, highsc_table & table) {
    //Chercher le bon index d'insertion
    size_t index_to_insert = 0;
    while (index_to_insert < table.size() && entry.second <= table[index_to_insert].second) ++index_to_insert; //On effectue ici la comparaison `<=` au lieu de `<` de manière à ce que, si deux joueurs ont le même score, celui qui l'a atteint en premier apparait au dessus dans le classement.

    //Insérer la paire
    table.insert(table.begin() + index_to_insert, entry);

    //Supprimer les derniers joueurs
    while (table.size() > HIGHSC_MAX_PLAYERS) table.pop_back();
}

/* Corps de la procédure `highscores_saveto` qui sauvegarde une table de highscores dans un fichier */
void highscores_saveto(const highsc_table & table, const string & filename) {
    //Fichier de sortie
    ofstream file(filename);

    //Insérer tous les joueurs dans le fichier
    for (highsc_entry entry: table) {
        file << entry.first << "  " << entry.second; //Enregistrer le couple
        //Aller à la ligne si la ligne actuelle ne correspond pas au dernier couple de la table
        if (entry.second != table[table.size() - 1].second) file << endl;
    }

    //Fermer le fichier
    file.close();
}

/* Corps de la procédure `highscores_loadto` qui charge une table de high scores depuis un fichier */
void highscores_loadto(const string & filename, highsc_table & table) {
    ifstream file(filename);

    //Récupérer les couples nom/score et les assiner à `table`
    while (!file.eof()) {
        string line = file_readline(file);
        if (line.length() == 0) break;
        string name = file_line_to_key(line);
        size_t score = stoull(file_line_to_val(line));

        highscores_insert_entry_into(highsc_entry(name, score), table);
    }

    //Fermer le fichier
    file.close();
}