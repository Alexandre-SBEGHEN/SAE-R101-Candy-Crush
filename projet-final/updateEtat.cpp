/**
 * @file updateEtat.cpp
 * @brief Les fonctions utilisées pour éliminer les bonbons et cases et appliquer la gravité
 * @date 25 décembre 2025
 * @author Audren Metery-Drouin
 */

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
bool graviter(mat & Grid, enum gravType gravDirection) {
    bool change = false;

    if (gravDirection == UP || gravDirection == LEFT) {
        // We start scanning the grid from the top left corner
        for (unsigned ord=0; ord < Grid.size(); ord++) {
            for (unsigned abs=0; abs < Grid.size(); abs++) {
                // Make sure the current cell is not empty
                if (Grid[ord][abs] != KImpossible) {
                    if (gravDirection == UP) {
                        //--------------------- Up gravity
                        // Check if the cell on top of the current cell is empty
                        if (ord > 0) {
                            if (Grid[ord-1][abs] == KImpossible) {
                                // Make the number fall onto that cell
                                Grid[ord-1][abs] = Grid[ord][abs];
                                Grid[ord][abs] = KImpossible;
                                // Update variable
                                change = true;
                            }
                        }
                    } else {
                        //--------------------- Left gravity
                        // Check if the cell onto the left of the current cell is empty
                        if (abs > 0) {
                            if (Grid[ord][abs-1] == KImpossible) {
                                // Make the number fall onto that cell
                                Grid[ord][abs-1] = Grid[ord][abs];
                                Grid[ord][abs] = KImpossible;
                                // Update variable
                                change = true;
                            }
                        }
                    }
                }
            }
        }
    } else {
        // We start scanning the grid from the bottom right corner
        for (int ord = int(Grid.size())-1; ord >= 0; ord--) {
            for (int abs = int(Grid.size())-1; abs >= 0; abs--) {
                // Make sure the current cell is not empty
                if (Grid[ord][abs] != KImpossible) {
                    if (gravDirection == DOWN) {
                        //--------------------- Down gravity
                        // Check if the cell on top of the current cell is empty
                        if (ord < int(Grid.size())-1) {
                            if (Grid[ord+1][abs] == KImpossible) {
                                // Make the number fall onto that cell
                                Grid[ord+1][abs] = Grid[ord][abs];
                                Grid[ord][abs] = KImpossible;
                                // Update variable
                                change = true;
                            }
                        }
                    } else {
                        //--------------------- Right gravity
                        // Check if the cell onto the left of the current cell is empty
                        if (abs < int(Grid[ord].size())-1) {
                            if (Grid[ord][abs+1] == KImpossible) {
                                // Make the number fall onto that cell
                                Grid[ord][abs+1] = Grid[ord][abs];
                                Grid[ord][abs] = KImpossible;
                                // Update variable
                                change = true;
                            }
                        }
                    }
                }
            }
        }
    }

    return change;
}
