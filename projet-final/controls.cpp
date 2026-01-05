#include <iostream>
#include <controls.h>
#include <inGameDisplay.h>
#include <language.h>
using namespace std;

bool moveIsValid(mat & grid, const maPosition & pos, char direction)
{
    // Calcul de la case cible
    int tRow = static_cast<int>(pos.ord);
    int tCol = static_cast<int>(pos.abs);

    switch(direction)
    {
    case 'Z': case 'z': tRow--; break;
    case 'S': case 's': tRow++; break;
    case 'Q': case 'q': tCol--; break;
    case 'D': case 'd': tCol++; break;
    default: return false;
    }

    // Hors grille
    if(tCol < 0 || tCol >= static_cast<int>(grid.size()) || tRow < 0 || tRow >= static_cast<int>(grid[tCol].size()))
        return false;

    /*
    // Sauvegarde
    mat save = grid;

    // Effectuer l'échange
    swap(grid[pos.abs][pos.ord], grid[tRow][tCol]);
    cout << "SWAP" << endl;

    maPosition p;
    unsigned howMany;

    // Tester alignements
    bool ok = atLeastThreeInARow(grid, p, howMany)
              || atLeastThreeInAColumn(grid, p, howMany);

    // Annuler si invalide
    if(!ok)
        grid = save;
    */

    return true;
}

swapResult moveByCoordinates(mat & grid, unsigned ligne, unsigned colonne, char direction)
{
    swapResult res{false, {0,0}, {0,0}};

    maPosition p1{ligne, colonne};
    maPosition p2 = p1;

    switch(direction) {
    case 'Z': case 'z': --p2.ord; break;
    case 'S': case 's': ++p2.ord; break;
    case 'Q': case 'q': --p2.abs; break;
    case 'D': case 'd': ++p2.abs; break;
    default:
        return res;
    }

    // Vérification limites
    if (p2.ord >= grid.size() || p2.abs >= grid[p2.ord].size())
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


swapResult moveByCursor(gametexts texts, mat & grid, EtatMat EtatGrid, graphisme details, size_t score, int coupsRestant)
{
    maPosition cursor{0, 0};
    char input;

    while (true) {

        displayGrid(texts, grid, EtatGrid, MOUVEMENT, cursor, details, score, coupsRestant);

        cout << texts["ingame__play__cursor"] << cursor.abs+1 << "," << cursor.ord+1 << ")\n";
        cout << "ZQSD " << texts["ingame__play__move"] << ", E " << texts["ingame__play__confirm"] << ' ';
        cin >> input;

        if (input == 'E' || input == 'e')
            break;

        switch(input) {
        case 'Z': if (cursor.ord > 0) cursor.ord--; break;
        case 'S': if (cursor.ord + 1 < grid.size()) cursor.ord++; break;
        case 'Q': if (cursor.abs > 0) cursor.abs--; break;
        case 'D': if (cursor.abs + 1 < grid[0].size()) cursor.abs++; break;
        }
    }

    cout << texts["ingame__play__swapdir"] << " (ZQSD) : ";
    char dir;
    cin >> dir;

    return moveByCoordinates(grid, cursor.abs, cursor.ord, dir);
}
