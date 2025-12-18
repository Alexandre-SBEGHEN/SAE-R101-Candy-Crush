#include <iostream>
// Modules
#include <inGameDisplay.h>

using namespace std;

enum StatusGame StatusDuJeu = IDLE;
maPosition PositionActuelle;

int main()
{
    unsigned int Taille = 12;
    mat Tableau;
    EtatMat TableauEtat;

    initGrid(Tableau, Taille);
    initEtatGrid(TableauEtat, Taille);

    PositionActuelle.abs = 6;
    PositionActuelle.ord = 3;

    StatusDuJeu = MOUVEMENT;

    displayGrid(Tableau, TableauEtat, StatusDuJeu, PositionActuelle);

    cout << "Hello World!" << endl;
    return 0;
}
