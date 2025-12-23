/**
 *  @date : 23 décembre 2025
 *  @author : Audren Metery-Drouin
 *  @Brief : Script main pour temporairement tester les librairies custom
**/

#include <iostream>
#include <ctime>

#include <inGameDisplay.h>
#include <updateEtat.h>

using namespace std;

enum StatusGame StatusDuJeu = IDLE;
enum graphisme Details = LOW;
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
    Details = LOW;

    displayGrid(Tableau, TableauEtat, StatusDuJeu, PositionActuelle, Details);
}

int main()
{
    srand(time(0));

    TestGridAffichage();

    cout << "Hello World!" << endl;
    return 0;
}
