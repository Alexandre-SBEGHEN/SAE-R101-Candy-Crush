/**
 *  @date : 23 décembre 2025
 *  @author : Nicolas Moyenin
 *  @Brief : Fonctions qui permettent d'echanger les bonbons
**/


//-------------- Fonction Verif mouv valide --------------//
/**
 * @brief Verifie si le mouvements du joueur est correcte
 * @param grid la grille de jeu
 * @param pos Position actuelle
 * @param direction le sens de déplacement (ZSQD)
 **/

bool moveIsValid(mat & grid, const maPosition & pos, char direction);

// -------------- Mouvements --------------//
struct swapResult {
    bool ok;            // move valide ? --> definie a false par defaut
    maPosition p1;      // première case
    maPosition p2;      // deuxième case
};

/**
 * @brief Deplacement a partir des coordonnees
 * @param grid la grille de jeu
 * @param ligne Coordonnee de la ligne a echanger
 * @param colonne Coordonnee de la colonne a echanger
 * @param direction le sens de déplacement (ZSQD)
 **/
swapResult moveByCoordinates(mat & grid, unsigned ligne, unsigned colonne, char direction);


/**
 * @brief deplacement avec le curseur
 * @param grid la grille de jeu
 */
swapResult moveByCursor(mat & grid);
