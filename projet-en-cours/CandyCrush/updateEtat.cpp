/**
 *  @date : 23 décembre 2025
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

}

//------------------------------ Fonctions pour éliminer les lignes de bonbons
void removalInColumn(mat & Grid, EtatMat & EtatGrid, maPosition pos, unsigned howMany) {

}
void removalInRow(mat & Grid, EtatMat & EtatGrid, maPosition pos, unsigned howMany) {

}

//------------------------------ Fonctions pour faire tomber les bonbons
void graviter(mat & Grid, EtatMat & EtatGrid, enum gravType gravDirection) {

}
