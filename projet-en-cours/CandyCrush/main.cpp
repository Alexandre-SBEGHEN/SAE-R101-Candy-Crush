/**
 *  @date : 26 décembre 2025
 *  @author : Audren Metery-Drouin
 *  @Brief : Script main pour temporairement tester les librairies custom
**/

#include <iostream>
#include <ctime>
#include <thread>
#include <chrono>

#include <inGameDisplay.h>
#include <updateEtat.h>

using namespace std;

StatusGame StatusDuJeu = IDLE;
graphisme Details = LOW;
maPosition PositionActuelle;
gravType GravDirection = UP;

void TestGridAffichage() {
    unsigned int Taille = 6;
    mat Tableau;
    EtatMat TableauEtat;

    size_t score = 0;
    size_t scoreParBonbon = 50; // Le score ajouté par bonbon lorsque on détruit une ligne ou colonne

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
        displayGrid(Tableau, TableauEtat, StatusDuJeu, PositionActuelle, Details, score);
        cout << "choisis ord" << endl;
        cin >> tmp;
        PositionActuelle.ord = stoi(tmp)-1;

        // On choisis l'abscisse
        StatusDuJeu = ABS;
        displayGrid(Tableau, TableauEtat, StatusDuJeu, PositionActuelle, Details, score);
        cout << "choisis abs" << endl;
        cin >> tmp;
        PositionActuelle.abs = stoi(tmp)-1;

        //------ On choisis la direction
        StatusDuJeu = MOUVEMENT;
        displayGrid(Tableau, TableauEtat, StatusDuJeu, PositionActuelle, Details, score);
        cout << "choisis direction" << endl;
        char mouvementChoisis;
        cin >> mouvementChoisis;

        StatusDuJeu = IDLE;

        //------ On échange les bonbons
        maPosition AutrePosition;
        if (mouvementChoisis == 'z') {
            // Haut
            unsigned bonbonTmp = Tableau[PositionActuelle.ord][PositionActuelle.abs];
            Tableau[PositionActuelle.ord][PositionActuelle.abs] = Tableau[PositionActuelle.ord-1][PositionActuelle.abs];
            Tableau[PositionActuelle.ord-1][PositionActuelle.abs] = bonbonTmp;
            // Autre position
            AutrePosition.ord = PositionActuelle.ord-1;
            AutrePosition.abs = PositionActuelle.abs;
        } else if (mouvementChoisis == 's') {
            // Bas
            unsigned bonbonTmp = Tableau[PositionActuelle.ord][PositionActuelle.abs];
            Tableau[PositionActuelle.ord][PositionActuelle.abs] = Tableau[PositionActuelle.ord+1][PositionActuelle.abs];
            Tableau[PositionActuelle.ord+1][PositionActuelle.abs] = bonbonTmp;
            // Autre position
            AutrePosition.ord = PositionActuelle.ord+1;
            AutrePosition.abs = PositionActuelle.abs;
        } else if (mouvementChoisis == 'q') {
            // Gauche
            unsigned bonbonTmp = Tableau[PositionActuelle.ord][PositionActuelle.abs];
            Tableau[PositionActuelle.ord][PositionActuelle.abs] = Tableau[PositionActuelle.ord][PositionActuelle.abs-1];
            Tableau[PositionActuelle.ord][PositionActuelle.abs-1] = bonbonTmp;
            // Autre position
            AutrePosition.ord = PositionActuelle.ord;
            AutrePosition.abs = PositionActuelle.abs-1;
        } else if (mouvementChoisis == 'd') {
            // Droite
            unsigned bonbonTmp = Tableau[PositionActuelle.ord][PositionActuelle.abs];
            Tableau[PositionActuelle.ord][PositionActuelle.abs] = Tableau[PositionActuelle.ord][PositionActuelle.abs+1];
            Tableau[PositionActuelle.ord][PositionActuelle.abs+1] = bonbonTmp;
            // Autre position
            AutrePosition.ord = PositionActuelle.ord;
            AutrePosition.abs = PositionActuelle.abs+1;
        }

        //-------------------------- On élimine les chaînes de bonbons et on applique la gravité
        //------ On garde les ancienne versions des tableaux pour pouvoir faire une animation
        mat AncienTableau = Tableau;
        EtatMat AncienTableauEtat = TableauEtat;
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
                // On ajoute au score
                score = score + scoreParBonbon*howManyColumn;
            } else {
                // On élimine la ligne
                removalInRow(Tableau, TableauEtat, PositionActuelle, howManyRow);
                // On ajoute au score
                score = score + scoreParBonbon*howManyRow;
            }
        } else if (columnFound) {
            // On élimine la colonne
            removalInColumn(Tableau, TableauEtat, PositionActuelle, howManyColumn);
            // On ajoute au score
            score = score + scoreParBonbon*howManyColumn;
        } else if (rowFound) {
            // On élimine la ligne
            removalInRow(Tableau, TableauEtat, PositionActuelle, howManyRow);
            // On ajoute au score
            score = score + scoreParBonbon*howManyRow;
        }

        // Animation (Position 1)
        if (columnFound || rowFound) {
            // Old table
            displayGrid(AncienTableau, AncienTableauEtat, StatusDuJeu, PositionActuelle, Details, score);
            this_thread::sleep_for(chrono::milliseconds(500));
            for (unsigned i=0; i<2; i++) {
                // New table
                displayGrid(Tableau, TableauEtat, StatusDuJeu, PositionActuelle, Details, score);
                // Cooldown
                this_thread::sleep_for(chrono::milliseconds(500));
                // Old table
                displayGrid(AncienTableau, AncienTableauEtat, StatusDuJeu, PositionActuelle, Details, score);
                // Cooldown
                this_thread::sleep_for(chrono::milliseconds(500));
            }
        }

        //------ Seconde position
        howManyColumn = 0;
        columnFound = atLeastThreeInAColumn(Tableau, AutrePosition, howManyColumn);
        howManyRow = 0;
        rowFound = atLeastThreeInARow(Tableau, AutrePosition, howManyRow);
        if (columnFound && rowFound) {
            // Ligne et colonne trouvé en même temps, on élimine donc la chaîne la plus longue
            if (howManyColumn >= howManyRow) {
                // On élimine la colonne
                removalInColumn(Tableau, TableauEtat, AutrePosition, howManyColumn);
                // On ajoute au score
                score = score + scoreParBonbon*howManyColumn;
            } else {
                // On élimine la ligne
                removalInRow(Tableau, TableauEtat, AutrePosition, howManyRow);
                // On ajoute au score
                score = score + scoreParBonbon*howManyRow;
            }
        } else if (columnFound) {
            // On élimine la colonne
            removalInColumn(Tableau, TableauEtat, AutrePosition, howManyColumn);
            // On ajoute au score
            score = score + scoreParBonbon*howManyColumn;
        } else if (rowFound) {
            // On élimine la ligne
            removalInRow(Tableau, TableauEtat, AutrePosition, howManyRow);
            // On ajoute au score
            score = score + scoreParBonbon*howManyRow;
        }

        // Animation (Position 2)
        if (columnFound || rowFound) {
            // Old table
            displayGrid(AncienTableau, AncienTableauEtat, StatusDuJeu, PositionActuelle, Details, score);
            this_thread::sleep_for(chrono::milliseconds(500));
            for (unsigned i=0; i<2; i++) {
                // New table
                displayGrid(Tableau, TableauEtat, StatusDuJeu, PositionActuelle, Details, score);
                // Cooldown
                this_thread::sleep_for(chrono::milliseconds(500));
                // Old table
                displayGrid(AncienTableau, AncienTableauEtat, StatusDuJeu, PositionActuelle, Details, score);
                // Cooldown
                this_thread::sleep_for(chrono::milliseconds(500));
            }
        }

        // Display New table
        displayGrid(Tableau, TableauEtat, StatusDuJeu, PositionActuelle, Details, score);

        //-------------------------- On applique la gravité
        bool change = true;
        while (change) {
            change = graviter(Tableau, TableauEtat, GravDirection);
            if (change) {
                this_thread::sleep_for(chrono::milliseconds(500));
                displayGrid(Tableau, TableauEtat, StatusDuJeu, PositionActuelle, Details, score);
            }
        }

        // Debug
        cout << "colonne trouvé: " << columnFound << ", de taille: " << howManyColumn << endl;
        cout << "ligne trouvé: " << rowFound << ", de taille: " << howManyRow << endl;
        this_thread::sleep_for(chrono::milliseconds(3000));
    }

}

int main()
{
    srand(time(0));

    TestGridAffichage();

    cout << "Hello World!" << endl;
    return 0;
}
