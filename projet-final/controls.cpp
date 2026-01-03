/**
 *  @date : 23 décembre 2025
 *  @author : Nicolas Moyenin
 *  @Brief : Fonctions qui permettent d'echanger les bonbons
**/

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#include <controls.h>

using namespace std;
//-------------- Fonction Verif mouv valide --------------//


bool moveIsValid(mat & grid, const maPosition & pos, char direction)
{
    // Calcul de la case cible
    int tRow = static_cast<int>(pos.abs);
    int tCol = static_cast<int>(pos.ord);

    switch(direction)
    {
    case 'Z': tRow--; break;
    case 'S': tRow++; break;
    case 'Q': tCol--; break;
    case 'D': tCol++; break;
    default: return false;
    }

    // Hors grille
    if(tRow < 0 || tRow >= static_cast<int>(grid.size()) || //static_cast permet de convertir un type en un autre. Tres important ici
        tCol < 0 || tCol >= static_cast<int>(grid[0].size()))
        return false;

    // Sauvegarde
    mat save = grid;

    // Effectue echange
    swap(grid[pos.abs][pos.ord], grid[tRow][tCol]);

    maPosition p;
    unsigned howMany;

    // Teste alignements
    bool ok = atLeastThreeInARow(grid, p, howMany)
              || atLeastThreeInAColumn(grid, p, howMany);

    // Cancel si invalide
    if(!ok)
        grid = save;

    return ok;
}


// -------------- Mouvements --------------//
struct swapResult {
    bool ok;            // move valide ? --> definie a false par defaut
    maPosition p1;      // première case
    maPosition p2;      // deuxième case
};


swapResult moveByCoordinates(mat & grid, unsigned ligne, unsigned colonne, char direction)
{
    swapResult res{false, {0,0}, {0,0}};

    maPosition p1{ligne, colonne};
    maPosition p2 = p1;

    switch(direction) {
    case 'Z': case 'z': p2.abs--; break;
    case 'S': case 's': p2.abs++; break;
    case 'Q': case 'q': p2.ord--; break;
    case 'D': case 'd': p2.ord++; break;
    default:
        return res;
    }

    // Vérification limites
    if (p2.abs >= grid.size() || p2.ord >= grid[0].size())
        return res;

    // Vérifier si mouvement valide (Candy Crush)
    if (!moveIsValid(grid, p1, direction))
        return res;

    // Mouvement validé
    res.ok = true;
    res.p1 = p1;
    res.p2 = p2;

    return res;
}


swapResult moveByCursor(mat & grid)
{
    maPosition cursor{0, 0};
    char input;

    while (true) {
        displayGrid(grid);
        cout << "Curseur : (" << cursor.abs << "," << cursor.ord << ")\n";
        cout << "ZQSD déplacer, E valider : ";
        cin >> input;

        if (input == 'E' || input == 'e')
            break;

        switch(input) {
        case 'Z': if (cursor.abs > 0) cursor.abs--; break;
        case 'S': if (cursor.abs + 1 < grid.size()) cursor.abs++; break;
        case 'Q': if (cursor.ord > 0) cursor.ord--; break;
        case 'D': if (cursor.ord + 1 < grid[0].size()) cursor.ord++; break;
        }
    }

    cout << "Direction échange (ZQSD) : ";
    char dir;
    cin >> dir;

    return moveByCoordinates(grid, cursor.abs, cursor.ord, dir);
}
