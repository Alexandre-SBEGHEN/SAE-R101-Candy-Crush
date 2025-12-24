/**
 *  @date : 24 décembre 2025
 *  @author : Audren Metery-Drouin
 *  @Brief : Les fonctions utilisées pour éliminer les bonbons et cases et appliquer la gravité
**/

#include <updateEtat.h>

//------------------------------ Fonctions pour vérifier les lignes de bonbons
bool atLeastThreeInAColumn(const mat & Grid, maPosition & pos, unsigned & howMany) {
    // On initialise
    howMany = 1;
    unsigned offset = 0;
    // On cherche vers le haut
    while (pos.ord-offset > 0) {
        offset = offset+1;
        if (Grid[pos.ord-offset][pos.abs] == Grid[pos.ord][pos.abs])
            howMany = howMany+1;
        else
            break;
    }
    // On cherche vers le bas
    offset = 0;
    while (pos.ord+offset < Grid.size()-1) {
        offset = offset+1;
        if (Grid[pos.ord+offset][pos.abs] == Grid[pos.ord][pos.abs])
            howMany = howMany+1;
        else
            break;
    }

    return (howMany >= 3);
}
bool atLeastThreeInARow(const mat & Grid, maPosition & pos, unsigned & howMany) {
    // On initialise
    howMany = 1;
    unsigned offset = 0;
    // On cherche vers la gauche
    while (pos.abs-offset > 0) {
        offset = offset+1;
        if (Grid[pos.ord][pos.abs-offset] == Grid[pos.ord][pos.abs])
            howMany = howMany+1;
        else
            break;
    }
    // On cherche vers le bas
    offset = 0;
    while (pos.abs+offset < Grid.size()-1) {
        offset = offset+1;
        if (Grid[pos.ord][pos.abs+offset] == Grid[pos.ord][pos.abs])
            howMany = howMany+1;
        else
            break;
    }

    return (howMany >= 3);
}

//------------------------------ Fonction pour éliminer un bonbon dans une case
void removalInCell(mat & Grid, EtatMat & EtatGrid, unsigned ord, unsigned abs) {
    // On enlève le bonbon dans la case
    Grid[ord][abs] = KImpossible;

    // On actualise l'état de la case
    if (EtatGrid[ord][abs] == GLACE) {
        EtatGrid[ord][abs] = GLACE_FAIBLE;
    } else if (EtatGrid[ord][abs] == GLACE_FAIBLE) {
        EtatGrid[ord][abs] = NORMAL;
    }
}

//------------------------------ Fonctions pour éliminer les lignes de bonbons
void removalInColumn(mat & Grid, EtatMat & EtatGrid, maPosition pos, unsigned howMany) {
    unsigned offset = 0;
    unsigned compteur = 1;
    // On enlève vers le haut
    while (pos.ord-offset > 0) {
        offset = offset+1;
        if (Grid[pos.ord-offset][pos.abs] == Grid[pos.ord][pos.abs]) {
            // On enlève le bonbon de la ligne
            removalInCell(Grid, EtatGrid, pos.ord-offset, pos.abs);
            // On continue de compter le nombre de bonbons enlever de la ligne
            compteur = compteur+1;
        } else
            break;
    }
    // On enlève vers le bas (on connaît le nombre de bonbons restant à éliminer)
    for (offset = 1; compteur < howMany; compteur = compteur+1) {
        // On enlève le bonbon de la ligne
        removalInCell(Grid, EtatGrid, pos.ord+offset, pos.abs);
        // On continue d'avancer
        offset = offset+1;
    }
    // On enlève le bonbon de la position originale
    removalInCell(Grid, EtatGrid, pos.ord, pos.abs);
}
void removalInRow(mat & Grid, EtatMat & EtatGrid, maPosition pos, unsigned howMany) {
    unsigned offset = 0;
    unsigned compteur = 1;
    // On enlève vers la gauche
    while (pos.abs-offset > 0) {
        offset = offset+1;
        if (Grid[pos.ord][pos.abs-offset] == Grid[pos.ord][pos.abs]) {
            // On enlève le bonbon de la ligne
            removalInCell(Grid, EtatGrid, pos.ord, pos.abs-offset);
            // On continue de compter le nombre de bonbons enlever de la ligne
            compteur = compteur+1;
        } else
            break;
    }
    // On enlève vers la droite (on connaît le nombre de bonbons restant à éliminer)
    for (offset = 1; compteur < howMany; compteur = compteur+1) {
        // On enlève le bonbon de la ligne
        removalInCell(Grid, EtatGrid, pos.ord, pos.abs+offset);
        // On continue d'avancer
        offset = offset+1;
    }
    // On enlève le bonbon de la position originale
    removalInCell(Grid, EtatGrid, pos.ord, pos.abs);
}

//------------------------------ Fonctions pour faire tomber les bonbons
void graviter(mat & Grid, EtatMat & EtatGrid, enum gravType gravDirection) {

}
