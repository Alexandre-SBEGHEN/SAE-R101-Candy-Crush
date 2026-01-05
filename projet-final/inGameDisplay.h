/**
 * @file inGameDisplay.h
 * @brief Les fonctions utilisées pour afficher la grille
 * @date 26 décembre 2025
 * @author Audren Metery-Drouin
 */

#include <typeList.h>
#include <language.h>

//------------------------------ Fonctions d'affichage
/**
 * @brief Met en couleur le terminal selon la valeur choisis
 * @param coul La valeur de la couleur choisis
 */
void couleur (const unsigned & coul);

/**
 * @brief couleurBonbon
 * @param Met la bonne couleur dans le terminal selon le bonbon actuelle
 */
void couleurBonbon(unsigned Bonbon);

/**
 * @brief couleurCase
 * @param Met la bonne couleur dans le terminal selon l'état de la case actuelle de la grille
 */
void couleurCase(enum StatusCase status);

/**
 * @brief Efface tout l'écran
 */
void clearScreen ();

/**
 * @brief Affiche la grille
 * @param Tableau Le contenu de la grille
 * @param TableauEtat Les états des cases de la grille
 * @param Status Ce que le joueur est actuellement en train de faire
 * @param CurrentPos La position actuelle sélectionner
 * @param coupsRestant Le nombre de coups restants au joueur
 */
void displayGrid(gametexts texts, mat Tableau, EtatMat TableauEtat, enum StatusGame Status, maPosition CurrentPos, enum graphisme Details, size_t score, int coupsRestant);

//------------------------------ Fonctions d'initialisation des grilles
/**
 * @brief Initialisation des valeurs de la grille
 * @param Tableau La Grille à initialiser
 * @param Taille Taille de la grille
 */
void initGrid(mat & Tableau, unsigned Taille);

/**
 * @brief Initialisation des états des cases de la grille
 * @param TableauEtat La grille des états à initialiser
 * @param Taille Taille de la grille
 */
void initEtatGrid(EtatMat & TableauEtat, unsigned Taille);
