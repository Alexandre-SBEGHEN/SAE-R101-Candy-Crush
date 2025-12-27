/**
 * @file main.cpp
 * @brief Script de gestion de flux d'entrée et de sortie
 * @author Alexandre SBEGHEN
 * @date 24/12/2025
 * @version 1.0
 */
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include "include/file.h"
#include "include/language.h"
#include "include/highscores.h"
#include "include/option.h"
using namespace std;

gametexts languageTexts;
highsc_table highscores;
execoption startOptions = {
    {"-lang", "lang/en.lang"},
    {"-highsc", "none"},
    {"-fancygame", "false"}
};

int main(int argc, char** arg) {
    //Vérifier si le programme est exécuté avec les bonnes options
    if (!option_assert_validity(argc)) {
        cerr << "Invalid option -- program can't start." << endl;
        return 1;
    }
    option_parse_to(startOptions, argc, arg);

    //Charger les textes du jeu
    if (file_exists(startOptions["-lang"])) {
        language_get_texts_from_file_to(startOptions["-lang"], languageTexts);
    } else {
        cerr << "Language file doesn't exist or not found -- program can't start." << endl;
        return 1;
    }

    //Charger une potentielle table de highscore
    if (startOptions["-highsc"] != "none") {
        if (file_exists(startOptions["-highsc"]))
            highscores_loadto(startOptions["-highsc"], highscores);
        else cout << "Warning, highscore file doesn't exist or not found -- creating an empty table." << endl;
    }

    //Activer ou non le mode graphismes élevés
    bool fancyGame = false;
    if (startOptions["-fancygame"] != "false" && startOptions["-fancygame"] != "0") fancyGame = true;

    //Boucle principale (commence par l'écran titre)



    // cout << "Exécution réussie." << endl;
    // for (auto & p: startOptions) cout << p.first << '\t' << p.second << endl;
    // cout << fancyGame << endl;



    //for (auto & p: LANGUAGE_TEXTS) cout << p.first << '\t' << p.second << endl;

    return 0;
}