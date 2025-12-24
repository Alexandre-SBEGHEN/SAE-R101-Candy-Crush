/**
 *  @date : 24 décembre 2025
 *  @author : Audren Metery-Drouin
 *  @Brief : Les fonctions utilisées pour éliminer les bonbons et cases et appliquer la gravité
**/

#include <typeList.h>

//------------------------------ Fonctions pour vérifier les lignes de bonbons
/**
 * @brief renvoie le booléen true si 3 bonbons ou plus sont trouvés à la suite dans une colonne
 * @param Grid La grille à vérifier
 * @param pos La position qui à été échanger
 * @param howMany La valeur retourner donnant la taille de la ligne trouvé
 */
bool atLeastThreeInAColumn(const mat & Grid, maPosition & pos, unsigned & howMany);

/**
 * @brief renvoie le booléen true si 3 bonbons ou plus sont trouvés à la suite dans une ligne
 * @param Grid La grille à vérifier
 * @param pos La position qui à été échanger
 * @param howMany La valeur retourner donnant la taille de la ligne trouvé
 */
bool atLeastThreeInARow(const mat & Grid, maPosition & pos, unsigned & howMany);

//------------------------------ Fonction pour éliminer un bonbon dans une case
/**
 * @brief enlève le bonbon dans une case de la grille
 * @param Grid La grille
 * @param EtatGrid La matrice des états de la grille
 * @param ord L'ordonnée de la case
 * @param abs L'abscisse de la case
 */
void removalInCell(mat & Grid, EtatMat & EtatGrid, unsigned ord, unsigned abs);

//------------------------------ Fonctions pour éliminer les lignes de bonbons
/**
 * @brief enlève la colonne de bonbons trouvé
 * @param Grid La grille où la colonne à été trouvé
 * @param EtatGrid La matrice des états de la grille
 * @param pos La position où la colonne à été trouvé
 * @param howMany La taille de la colonne
 */
void removalInColumn(mat & Grid, EtatMat & EtatGrid, maPosition pos, unsigned howMany);

/**
 * @brief enlève la ligne de bonbons trouvé
 * @param Grid La grille où la ligne à été trouvé
 * @param EtatGrid La matrice des états de la grille
 * @param pos La position où la ligne à été trouvé
 * @param howMany La taille de la ligne
 */
void removalInRow(mat & Grid, EtatMat & EtatGrid, maPosition pos, unsigned howMany);

//------------------------------ Fonction pour faire tomber les bonbons
/**
 * @brief Applique la gravité aux bonbons de la grille pour les faire tomber
 * @param Grid La grille
 * @param EtatGrid La matrice des états des cases de la grille
 * @param gravDirection La direction de la gravité
 */
void graviter(mat & Grid, EtatMat & EtatGrid, enum gravType gravDirection);
