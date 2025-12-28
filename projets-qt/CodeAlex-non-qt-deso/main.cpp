/**
 * @file main.cpp
 * @brief Script principal du jeu
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


struct GameMenuButton {
    GameMenuButton* parent;

    string* name;
    int action;

    vector<GameMenuButton*> children;
};
enum GameMenuButtonAction {
    FORWARD,
    BACKWARD,
    ACTION
};
GameMenuButton* GameMenuButton_create(string* name, const GameMenuButtonAction & action, GameMenuButton* parent = nullptr) {
    GameMenuButton* button = new GameMenuButton;
    button->parent = parent;
    button->name = name;
    button->action = action;
    return button;
}




int main(int argc, char** arg) {
    ////////// Options d'exécution
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
    //////////

    ////////// Créer le menu du jeu (ça va pas du tout être une horreur à faire 👍🏼)
    GameMenuButton* GameMenu = GameMenuButton_create((string*)("main"), ACTION);

    //Racine
    GameMenu->children.push_back(GameMenuButton_create(&languageTexts["menu__main__play"], ACTION, GameMenu));
    GameMenu->children.push_back(GameMenuButton_create(&languageTexts["menu__main__highscores"], FORWARD, GameMenu));
    GameMenu->children.push_back(GameMenuButton_create(&languageTexts["menu__main__settings"], FORWARD, GameMenu));
    GameMenu->children.push_back(GameMenuButton_create(&languageTexts["menu__main__about"], FORWARD, GameMenu));
    GameMenu->children.push_back(GameMenuButton_create(&languageTexts["menu__main__quit"], BACKWARD, GameMenu));
    
    //Highscores
    GameMenu->children[1]->children.push_back(GameMenuButton_create(&languageTexts["menu__highscores__save"], ACTION, GameMenu->children[1]));
    GameMenu->children[1]->children.push_back(GameMenuButton_create(&languageTexts["menu__highscores__load"], ACTION, GameMenu->children[1]));
    GameMenu->children[1]->children.push_back(GameMenuButton_create(&languageTexts["menu__misc__back"], BACKWARD, GameMenu->children[1]));
    
    //Options
    GameMenu->children[2]->children.push_back(GameMenuButton_create(&languageTexts["menu__param__language"], FORWARD, GameMenu->children[2]));
    GameMenu->children[2]->children.push_back(GameMenuButton_create(&languageTexts["menu__param__movingway"], FORWARD, GameMenu->children[2]));
    GameMenu->children[2]->children.push_back(GameMenuButton_create(&languageTexts["menu__misc__back"], BACKWARD, GameMenu->children[2]));

    //A propos
    GameMenu->children[3]->children.push_back(GameMenuButton_create(&languageTexts["menu__misc__back"], BACKWARD, GameMenu->children[3]));
    
    //Options->Langue
    GameMenu->children[2]->children[0]->children.push_back(GameMenuButton_create(&languageTexts["menu__param__language__french"], ACTION, GameMenu->children[2]->children[0]));
    GameMenu->children[2]->children[0]->children.push_back(GameMenuButton_create(&languageTexts["menu__param__language__english"], ACTION, GameMenu->children[2]->children[0]));
    GameMenu->children[2]->children[0]->children.push_back(GameMenuButton_create(&languageTexts["menu__misc__back"], BACKWARD, GameMenu->children[2]->children[0]));
    
    //Options->Movingway
    GameMenu->children[2]->children[1]->children.push_back(GameMenuButton_create(&languageTexts["menu__param__movingway__inst"], ACTION, GameMenu->children[2]->children[1]));
    GameMenu->children[2]->children[1]->children.push_back(GameMenuButton_create(&languageTexts["menu__param__movingway__cbc"], ACTION, GameMenu->children[2]->children[1]));
    GameMenu->children[2]->children[1]->children.push_back(GameMenuButton_create(&languageTexts["menu__misc__back"], BACKWARD, GameMenu->children[2]->children[1]));

    //Sous menu actuel
    GameMenuButton* GameMenuCurrent = GameMenu;
    //////////
    
    //language_get_texts_from_file_to("lang/fr.lang", languageTexts);


    ////////// Boucle principale (commence par l'écran titre)
    while (true) {
        //Effacer l'écran
        cout << "\033[H\033[2J" << endl;

        //Afficher les différents boutons
        for (size_t i = 0; i < GameMenuCurrent->children.size(); ++i) cout << i+1 << " -  " << *(GameMenuCurrent->children[i]->name) << endl;
        
        //Faire le choix d'un bouton et le convertir en nombre
        string choice_raw;
        while (choice_raw.length() != 1 || !isdigit(choice_raw[0]) || char(choice_raw[0]) == '0' || char(choice_raw[0]) >= '1' + GameMenuCurrent->children.size()) {
            cout << endl << "Choisissez un bouton : ";
            cin >> choice_raw;
        }

        int choice = stoi(choice_raw) - 1;
        int action = (GameMenuCurrent->children[choice]->action);

        // cout << "choice " << choice << endl;
        // cout << "action " << action << endl;
        

        switch (action) {
            case ACTION: break;

            case FORWARD:
                GameMenuCurrent = GameMenuCurrent->children[choice];
                break;
            
            case BACKWARD:
                if (GameMenuCurrent->parent == nullptr) {
                    return 0;
                } else {
                    GameMenuCurrent = GameMenuCurrent->parent;
                }
                    
                break;
        }
    }
    
    //////////

    // for (GameMenuButton* i: GameMenuCurrent->children) cout << '|' << *(i->name) << '|' << endl;
    // for (auto & p: languageTexts) cout << '|' << p.second << '|' << endl;


    // cout << "Exécution réussie." << endl;
    // for (auto & p: startOptions) cout << p.first << '\t' << p.second << endl;
    // cout << fancyGame << endl;



    //for (auto & p: LANGUAGE_TEXTS) cout << p.first << '\t' << p.second << endl;

    return 0;
}