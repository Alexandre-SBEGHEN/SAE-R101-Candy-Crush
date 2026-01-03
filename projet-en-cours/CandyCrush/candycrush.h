/**
 * @file candycrush.h
 * @brief Fichier header du gameplay
 * @author Nicolas Moyenin, Audren Metery-Drouin, Alexandre SBEGHEN
 * @date 03/01/2026
 * @version 1.0
 */
#ifndef CANDYCRUSH_H
#define CANDYCRUSH_H
#include <language.h>

//Struct de validation du mouvement entre deux positions
struct swapResult {
    bool ok;            // le mouvement est valide ?
    maPosition p1;      // première case
    maPosition p2;      // deuxième case
};

/**
 * @brief Se déplacer selon la méthode 1
 * 
 * @param grid La grille du jeu
 * @param ligne La ligne acuelle
 * @param colonne La colonne actuelle
 * @param direction La direction du mouvement
 */
swapResult moveByCoordinates(mat & grid, unsigned ligne, unsigned colonne, char direction);

/**
 * @brief Se déplacer selon la méthode 2
 * 
 * @param grid La grille du jeu
 */
swapResult moveByCursor(mat & grid);

/**
 * @brief Vérifie si un mouvement est valide.
 * 
 * @param grid La grille du jeu
 * @param pos Position actuelle
 * @param direction La direction du mouvement
 * @return Si le mouvement est valide
 */
bool moveIsValid(mat & grid, const maPosition & pos, char direction);

/**
 * @brief Lance une partie de Candy Crush.
 * 
 * @param texts Les textes du jeu dans la bonne langue.
 * @param movingway Le mode de déplacement.
 * @param fancydisplay Activer ou non les graphismes élevés.
 */
size_t candycrush_play(const gametexts & texts, const size_t & movingway, const bool & fancydisplay);


#endif
