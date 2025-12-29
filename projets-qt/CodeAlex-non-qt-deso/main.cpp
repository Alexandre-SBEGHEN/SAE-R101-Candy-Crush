/**
 * @file main.cpp
 * @brief Script principal du jeu
 * @author Alexandre SBEGHEN
 * @date 24/12/2025
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
highsc_table highScores;
execoption startOptions = {
    {"-lang", "lang/en.lang"},
    {"-highsc", "none"},
    {"-fancydisplay", "false"}
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
    ACTION,
    ACTION_PLAY,

    ACTION_HIGHSC_SHOW,
    ACTION_HIGHSC_SAVE,
    ACTION_HIGHSC_LOAD,

    ACTION_PARAM_LANG_FR,
    ACTION_PARAM_LANG_EN,

    ACTION_PARAM_MOV_ABS,
    ACTION_PARAM_MOV_REL,
};
GameMenuButton* GameMenuButton_create(string* name, const GameMenuButtonAction & action, GameMenuButton* parent = nullptr) {
    GameMenuButton* button = new GameMenuButton;
    button->parent = parent;
    button->name = name;
    button->action = action;
    return button;
}


//Coeur du jeu
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
            highscores_loadto(startOptions["-highsc"], highScores);
        else cout << "Warning, highscore file doesn't exist or not found -- creating an empty table." << endl;
    }

    //Activer ou non le mode graphismes élevés
    bool FANCY_DISPLAY = false;
    if (startOptions["-fancydisplay"] != "false" && startOptions["-fancydisplay"] != "0") FANCY_DISPLAY = true;
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
    GameMenu->children[1]->children.push_back(GameMenuButton_create(&languageTexts["menu__highscores__show"], ACTION_HIGHSC_SHOW, GameMenu->children[1]));
    GameMenu->children[1]->children.push_back(GameMenuButton_create(&languageTexts["menu__highscores__save"], ACTION_HIGHSC_SAVE, GameMenu->children[1]));
    GameMenu->children[1]->children.push_back(GameMenuButton_create(&languageTexts["menu__highscores__load"], ACTION_HIGHSC_LOAD, GameMenu->children[1]));
    GameMenu->children[1]->children.push_back(GameMenuButton_create(&languageTexts["menu__misc__back"], BACKWARD, GameMenu->children[1]));
    
    //Options
    GameMenu->children[2]->children.push_back(GameMenuButton_create(&languageTexts["menu__param__language"], FORWARD, GameMenu->children[2]));
    GameMenu->children[2]->children.push_back(GameMenuButton_create(&languageTexts["menu__param__movingway"], FORWARD, GameMenu->children[2]));
    GameMenu->children[2]->children.push_back(GameMenuButton_create(&languageTexts["menu__misc__back"], BACKWARD, GameMenu->children[2]));

    //A propos
    GameMenu->children[3]->children.push_back(GameMenuButton_create(&languageTexts["menu__misc__back"], BACKWARD, GameMenu->children[3]));
    
    //Options->Langue
    GameMenu->children[2]->children[0]->children.push_back(GameMenuButton_create(&languageTexts["menu__param__language__french"], ACTION_PARAM_LANG_FR, GameMenu->children[2]->children[0]));
    GameMenu->children[2]->children[0]->children.push_back(GameMenuButton_create(&languageTexts["menu__param__language__english"], ACTION_PARAM_LANG_EN, GameMenu->children[2]->children[0]));
    GameMenu->children[2]->children[0]->children.push_back(GameMenuButton_create(&languageTexts["menu__misc__back"], BACKWARD, GameMenu->children[2]->children[0]));
    
    //Options->Movingway
    GameMenu->children[2]->children[1]->children.push_back(GameMenuButton_create(&languageTexts["menu__param__movingway__abs"], ACTION_PARAM_MOV_ABS, GameMenu->children[2]->children[1]));
    GameMenu->children[2]->children[1]->children.push_back(GameMenuButton_create(&languageTexts["menu__param__movingway__rel"], ACTION_PARAM_MOV_REL, GameMenu->children[2]->children[1]));
    GameMenu->children[2]->children[1]->children.push_back(GameMenuButton_create(&languageTexts["menu__misc__back"], BACKWARD, GameMenu->children[2]->children[1]));
    // (en vrai ça va je m'attendais à pire)

    //Sous menu actuel
    GameMenuButton* GameMenuCurrent = GameMenu;
    //////////

    ////////// Boucle principale (commence par l'écran titre)
    while (true) {
        //Effacer l'écran
        cout << "\033[H\033[2J" << endl;

        //Afficher le titre du jeu
        cout << R"(
 _____                 _         _____                _     
/  __ \               | |       /  __ \              | |    
| /  \/ __ _ _ __   __| |_   _  | /  \/_ __ _   _ ___| |__  
| |    / _` | '_ \ / _` | | | | | |   | '__| | | / __| '_ \ 
| \__/\ (_| | | | | (_| | |_| | | \__/\ |  | |_| \__ \ | | |
 \____/\__,_|_| |_|\__,_|\__, |  \____/_|   \__,_|___/_| |_|
                          __/ |                             
                         |___/                              
        )" << endl;

        //Afficher le à propos
        if (*(GameMenuCurrent->name) == languageTexts["menu__main__about"]) {
            cout << "==============================" << endl;
            cout << languageTexts["menu__about__title"] << endl;
            cout << "==============================" << endl;

            cout << endl << languageTexts["menu__about__name"] << " Candy Crush C++" << endl;
            cout << languageTexts["menu__about__version"] << " 1.0.0" << endl;

            cout << endl << languageTexts["menu__about__authors"] << endl;
            cout << "- METERY DROUIN Audren" << endl;
            cout << "- MOYENIN Nicolas" << endl;
            cout << "- SBEGHEN Alexandre" << endl;

            cout << endl << languageTexts["menu__about__desc"] << endl;
            cout << languageTexts["menu__about__descline"] << endl;

            cout << endl << languageTexts["menu__about__legal"] << endl;
            cout << languageTexts["menu__about__legaldesc_l1"] << endl;
            cout << languageTexts["menu__about__legaldesc_l2"] << endl;

            cout << "==============================" << endl << endl;
        }

        //Afficher les différents boutons
        for (size_t i = 0; i < GameMenuCurrent->children.size(); ++i) cout << i+1 << " -  " << *(GameMenuCurrent->children[i]->name) << endl;
        
        //Faire le choix d'un bouton et le convertir en nombre
        string choice_raw;
        while (choice_raw.length() != 1 || !isdigit(choice_raw[0]) || stoull(choice_raw) == 0 || stoull(choice_raw) > GameMenuCurrent->children.size()) {
            cout << endl << languageTexts["menu__misc__choosebutton"] << ' ';
            cin >> choice_raw;
        }

        size_t choice = stoull(choice_raw) - 1;
        int action = (GameMenuCurrent->children[choice]->action);
        
        //Choisir quoi faire en fonction de `action`
        switch (action) {
            //Parcourir le menu vers l'avant
            case FORWARD:
                GameMenuCurrent = GameMenuCurrent->children[choice];
                break;
            
            //Retourner vers le sous menu parent ou quitter
            case BACKWARD:
                if (GameMenuCurrent->parent == nullptr) //Si on est à la racine on quitte
                    return 0;
                else
                    GameMenuCurrent = GameMenuCurrent->parent; //Sinon on va en arrière
                
                break;
            
            //Ne rien faire
            case ACTION: break;

            //Jouer
            case ACTION_PLAY:
                /* PLACER LA PROCÉDURE QUI DEMARRE LE JEU */
                break;

            //Afficher la table des high scores
            case ACTION_HIGHSC_SHOW:
                for (size_t i = 0; i < highScores.size(); ++i) cout << i+1 << " -  " << highScores[i].second << '\t' << highScores[i].first << endl;

                cout << languageTexts["menu__misc__pressenter"];
                cin.ignore();
                cin.get();

                break;
            
            //Sauvegarder la table des high scores
            case ACTION_HIGHSC_SAVE: {
                cout << languageTexts["menu__highscores__savename"] << ' ' << endl;
                string filename;
                cin >> filename;

                highscores_saveto(highScores, filename + ".hs");

                cout << languageTexts["menu__highscores__saved"] << ' ' << languageTexts["menu__misc__pressenter"];
                cin.ignore();
                cin.get();

                break;
            }
            //Charger la table des high scores
            case ACTION_HIGHSC_LOAD: {
                cout << languageTexts["menu__highscores__loadname"] << ' ' << endl;
                string filename;
                cin >> filename;

                bool isloaded = highscores_loadto(filename + ".hs", highScores);
                
                cout << ((isloaded) ? languageTexts["menu__highscores__loaded"] : languageTexts["menu__highscores__loaderr"]);


                cout << ' ' << languageTexts["menu__misc__pressenter"];
                cin.ignore();
                cin.get();

                break;
            }
        }
    }
    
    //////////




    ///// DEBUG
    // for (GameMenuButton* i: GameMenuCurrent->children) cout << '|' << *(i->name) << '|' << endl;
    // for (auto & p: languageTexts) cout << '|' << p.second << '|' << endl;

    // cout << "Exécution réussie." << endl;
    // for (auto & p: startOptions) cout << p.first << '\t' << p.second << endl;
    // cout << fancyGame << endl;

    // for (auto & p: LANGUAGE_TEXTS) cout << p.first << '\t' << p.second << endl;
    /////
    return 0;
}