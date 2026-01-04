/**
 *  @date : 4 janvier 2026
 *  @author : Audren Metery-Drouin
 *  @Brief : Script du gameplay
**/

#include <iostream>
#include <ctime>
#include <thread>
#include <chrono>

#include <candycrush.h>
#include <inGameDisplay.h>
#include <updateEtat.h>
#include <controls.h>

using namespace std;



size_t candycrush_play(const gametexts & texts, const size_t & movingway, const bool & fancydisplay) {

    srand(time(0));

    StatusGame StatusDuJeu = IDLE;
    maPosition PositionActuelle;
    gravType GravDirection = UP;
    
    graphisme Details = (fancydisplay) ? HIGH : LOW;

    unsigned int Taille = 6;
    mat Tableau;
    EtatMat TableauEtat;

    size_t score = 0;
    size_t scoreParBonbon = 50; // Le score ajouté par bonbon lorsque on détruit une ligne ou colonne

    int coupsRestant = 10; // Le nombre de coups restants

    initGrid(Tableau, Taille);
    initEtatGrid(TableauEtat, Taille);

    while (coupsRestant > 0) {

        // Position impossible pour une position non choisis
        PositionActuelle.abs = Taille;
        PositionActuelle.ord = Taille;

        // On affiche la grille
        StatusDuJeu = IDLE;
        displayGrid(Tableau, TableauEtat, StatusDuJeu, PositionActuelle, Details, score, coupsRestant);


        // Code de Nicolas pour gérer les entrées d'utilisateurs
        swapResult res;

        if (movingway == 1) {
            unsigned line, column;
            char dir;

            // Ordonnée
            StatusDuJeu = ORD;
            displayGrid(Tableau, TableauEtat, StatusDuJeu, PositionActuelle, Details, score, coupsRestant);

            cout << "Ligne : ";
            cin >> line;
            PositionActuelle.ord = line-1;

            // Abscisse
            StatusDuJeu = ABS;
            displayGrid(Tableau, TableauEtat, StatusDuJeu, PositionActuelle, Details, score, coupsRestant);

            cout << "Colonne : ";
            cin >> column;
            PositionActuelle.abs = column-1;

            // Mouvement
            StatusDuJeu = MOUVEMENT;
            displayGrid(Tableau, TableauEtat, StatusDuJeu, PositionActuelle, Details, score, coupsRestant);

            cout << "Direction (ZQSD) : ";
            cin >> dir;

            res = moveByCoordinates(Tableau, PositionActuelle.abs, PositionActuelle.ord, dir);
        }
        else if (movingway == 1) {   //Pour deplacement par "curseur"
            res = moveByCursor(Tableau, TableauEtat, Details, score, coupsRestant);
        }
        else { // Si l'utilisateur rentre un mauvais mode, on stop
            cout << "Gros Boulet"<<endl;
            break;
        }
        //


        
        //------------ On utilise le résultat pour savoir si la position et le mouvement sont valides
        if (res.ok) {
            PositionActuelle = res.p1;
            maPosition AutrePosition = res.p2;

            // DEBUG
            /*
            StatusDuJeu = MOUVEMENT;
            displayGrid(Tableau, TableauEtat, StatusDuJeu, PositionActuelle, Details, score, coupsRestant);
            cout << "Voici la position 1" << endl;
            this_thread::sleep_for(chrono::milliseconds(2000));

            displayGrid(Tableau, TableauEtat, StatusDuJeu, AutrePosition, Details, score, coupsRestant);
            cout << "Voici la position 2" << endl;
            this_thread::sleep_for(chrono::milliseconds(2000));

            StatusDuJeu = IDLE;
            */
            //

            //------ On échange les bonbons
            unsigned bonbonTmp = Tableau[PositionActuelle.ord][PositionActuelle.abs];
            Tableau[PositionActuelle.ord][PositionActuelle.abs] = Tableau[AutrePosition.ord][AutrePosition.abs];
            Tableau[AutrePosition.ord][AutrePosition.abs] = bonbonTmp;

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
                displayGrid(AncienTableau, AncienTableauEtat, StatusDuJeu, PositionActuelle, Details, score, coupsRestant);
                this_thread::sleep_for(chrono::milliseconds(500));
                for (unsigned i=0; i<2; i++) {
                    // New table
                    displayGrid(Tableau, TableauEtat, StatusDuJeu, PositionActuelle, Details, score, coupsRestant);
                    // Cooldown
                    this_thread::sleep_for(chrono::milliseconds(500));
                    // Old table
                    displayGrid(AncienTableau, AncienTableauEtat, StatusDuJeu, PositionActuelle, Details, score, coupsRestant);
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
                displayGrid(AncienTableau, AncienTableauEtat, StatusDuJeu, PositionActuelle, Details, score, coupsRestant);
                this_thread::sleep_for(chrono::milliseconds(500));
                for (unsigned i=0; i<2; i++) {
                    // New table
                    displayGrid(Tableau, TableauEtat, StatusDuJeu, PositionActuelle, Details, score, coupsRestant);
                    // Cooldown
                    this_thread::sleep_for(chrono::milliseconds(500));
                    // Old table
                    displayGrid(AncienTableau, AncienTableauEtat, StatusDuJeu, PositionActuelle, Details, score, coupsRestant);
                    // Cooldown
                    this_thread::sleep_for(chrono::milliseconds(500));
                }
            }

            // Display New table
            displayGrid(Tableau, TableauEtat, StatusDuJeu, PositionActuelle, Details, score, coupsRestant);

            //-------------------------- On applique la gravité
            bool change = true;
            while (change) {
                change = graviter(Tableau, TableauEtat, GravDirection);
                if (change) {
                    this_thread::sleep_for(chrono::milliseconds(500));
                    displayGrid(Tableau, TableauEtat, StatusDuJeu, PositionActuelle, Details, score, coupsRestant);
                }
            }

            // Debug
            /*
            cout << "colonne trouvé: " << columnFound << ", de taille: " << howManyColumn << endl;
            cout << "ligne trouvé: " << rowFound << ", de taille: " << howManyRow << endl;
            this_thread::sleep_for(chrono::milliseconds(3000));
            */
        } else {
            cout << "mouvement invalide" << endl;
            this_thread::sleep_for(chrono::milliseconds(3000));
            displayGrid(Tableau, TableauEtat, StatusDuJeu, PositionActuelle, Details, score, coupsRestant); //Display grid
        }

        // On réduit le nomdre de coups restant
        --coupsRestant;
    }

    // Plus de coups restants
    displayGrid(Tableau, TableauEtat, StatusDuJeu, PositionActuelle, Details, score, coupsRestant);
    this_thread::sleep_for(chrono::milliseconds(1000));
    cout << "Vous avez épuisé tout les coups disponibles!" << endl;
    this_thread::sleep_for(chrono::milliseconds(1000));
    cout << "Votre score final: " << score;
    this_thread::sleep_for(chrono::milliseconds(2000));
    cout << " Pas mal!" << endl;
    this_thread::sleep_for(chrono::milliseconds(4000));
    
    return score;

}
