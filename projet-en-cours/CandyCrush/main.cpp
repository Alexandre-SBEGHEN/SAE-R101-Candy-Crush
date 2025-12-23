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

    while (true) {
        //-------------------------- script TEMPORAIRE (sera remplacer par le control.h)
        //------ On choisis la position
        PositionActuelle.abs = Taille;
        PositionActuelle.ord = Taille;
        string tmp;

        // On choisis l'ordonnée
        StatusDuJeu = ORD;
        displayGrid(Tableau, TableauEtat, StatusDuJeu, PositionActuelle, Details);
        cout << "choisis ord" << endl;
        cin >> tmp;
        PositionActuelle.ord = stoi(tmp)-1;

        // On choisis l'abscisse
        StatusDuJeu = ABS;
        displayGrid(Tableau, TableauEtat, StatusDuJeu, PositionActuelle, Details);
        cout << "choisis abs" << endl;
        cin >> tmp;
        PositionActuelle.abs = stoi(tmp)-1;

        //------ On choisis la direction
        StatusDuJeu = MOUVEMENT;
        displayGrid(Tableau, TableauEtat, StatusDuJeu, PositionActuelle, Details);

        //------ On échange les bonbons

        //-------------------------- On élimine les chaînes de bonbons et on applique la gravité
        //------ Première position
        unsigned int howManyColumn;
        bool columnFound = atLeastThreeInAColumn(Tableau, PositionActuelle, howManyColumn);
        unsigned int howManyRow;
        bool rowFound = atLeastThreeInARow(Tableau, PositionActuelle, howManyRow);
        if (columnFound && rowFound) {
            // Ligne et colonne trouvé en même temps, on élimine donc la chaîne la plus longue
            if (howManyColumn >= howManyRow) {
                // On élimine la colonne
                removalInColumn(Tableau, TableauEtat, PositionActuelle, howManyColumn);
            } else {
                // On élimine la ligne
                removalInRow(Tableau, TableauEtat, PositionActuelle, howManyRow);
            }
        } else if (columnFound) {
            // On élimine la colonne
            removalInColumn(Tableau, TableauEtat, PositionActuelle, howManyColumn);
        } else if (rowFound) {
            // On élimine la ligne
            removalInRow(Tableau, TableauEtat, PositionActuelle, howManyRow);
        }

    }

}

int main()
{
    srand(time(0));

    TestGridAffichage();

    cout << "Hello World!" << endl;
    return 0;
}
