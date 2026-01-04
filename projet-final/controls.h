/**
 * @file controls.h
 * @brief Fichier header pour la gestion de flux d'entrée et de sortie
 * @author Nicolas MOYENIN
 * @date 04/01/2026
 * @version 1.0
 */
#ifndef CONTROLS_H
#define CONTROLS_H
#include <typeList.h>
#include <language.h>
using namespace std;

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
 * @param EtatGrid La matrice des états de la grille du jeu
 * @param details Le niveau de graphisme
 * @param score Le score actuel du joueur
 */
swapResult moveByCursor(gametexts texts, mat & grid, EtatMat EtatGrid, graphisme details, size_t score, int coupsRestant);

/**
 * @brief Vérifie si un mouvement est valide.
 *
 * @param grid La grille du jeu
 * @param pos Position actuelle
 * @param direction La direction du mouvement
 * @return Si le mouvement est valide
 */
bool moveIsValid(mat & grid, const maPosition & pos, char direction);

#endif
