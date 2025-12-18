#include <iostream>
#include <ctime>
// Modules
#include <inGameDisplay.h>

using namespace std;

enum StatusGame StatusDuJeu = IDLE;
maPosition PositionActuelle;

void TestGridAffichage() {
    unsigned int Taille = 12;
    mat Tableau;
    EtatMat TableauEtat;

    initGrid(Tableau, Taille);
    initEtatGrid(TableauEtat, Taille);

    PositionActuelle.abs = 6;
    PositionActuelle.ord = 3;

    StatusDuJeu = MOUVEMENT;

    displayGrid(Tableau, TableauEtat, StatusDuJeu, PositionActuelle);
}

int main()
{
    srand(time(0));

    TestGridAffichage();

    cout << "Hello World!" << endl;
    return 0;
}
