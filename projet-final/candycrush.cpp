/**
 *  @date : 27 décembre 2025
 *  @author : Nicolas Moyenin
 *  @Brief : Script du gameplay
**/

#include <iostream>
#include <ctime>
#include <thread>
#include <chrono>

#include <candycrush.h>
#include <inGameDisplay.h>
#include <updateEtat.h>

using namespace std;

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
    if(tRow < 0 || tRow >= static_cast<int>(grid.size()) ||
        tCol < 0 || tCol >= static_cast<int>(grid[0].size()))
        return false;

    // Sauvegarde
    mat save = grid;

    // Effectuer l'Ã©change
    swap(grid[pos.abs][pos.ord], grid[tRow][tCol]);

    maPosition p;
    unsigned howMany;

    // Tester alignements
    bool ok = atLeastThreeInARow(grid, p, howMany)
              || atLeastThreeInAColumn(grid, p, howMany);

    // Annuler si invalide
    if(!ok)
        grid = save;

    return true;
}

swapResult moveByCoordinates(mat & grid, unsigned ligne, unsigned colonne, char direction)
{
    swapResult res{false, {0,0}, {0,0}};

    maPosition p1{ligne, colonne};
    maPosition p2 = p1;

    switch(direction) {
    case 'Z': case 'z': --p2.abs; break;
    case 'S': case 's': ++p2.abs; break;
    case 'Q': case 'q': --p2.ord; break;
    case 'D': case 'd': ++p2.ord; break;
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
        //displayGrid(grid);
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

    initGrid(Tableau, Taille);
    initEtatGrid(TableauEtat, Taille);

    displayGrid(Tableau, TableauEtat, StatusDuJeu, PositionActuelle, Details, score);

    while (true) {

        swapResult res;

        if (movingway == 0) {
            unsigned l, c;
            char dir;

            cout << "Ligne : ";
            cin >> l;
            cout << "Colonne : ";
            cin >> c;
            cout << "Direction (ZQSD) : ";
            cin >> dir;

            res = moveByCoordinates(Tableau, l, c, dir);
        }
        else if (movingway == 1) {   //Pour deplacement par "curseur"
            res = moveByCursor(Tableau);
        }
        else { // Si l'utilisateur rentre un mauvais mode, on stop
            cout << "Gros Boulet"<<endl;
            break;
        }
        
        if (res.ok) {
            StatusDuJeu = IDLE;
            maPosition PositionActuelle = res.p1;
            maPosition AutrePosition = res.p2;
            
            /*
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
            */

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
            /*
            cout << "colonne trouvé: " << columnFound << ", de taille: " << howManyColumn << endl;
            cout << "ligne trouvé: " << rowFound << ", de taille: " << howManyRow << endl;
            this_thread::sleep_for(chrono::milliseconds(3000));
            */
        } else {
            cout << "mouvement invalide" << endl;
            this_thread::sleep_for(chrono::milliseconds(3000));
            displayGrid(Tableau, TableauEtat, StatusDuJeu, PositionActuelle, Details, score); //Display grid
        }

        
    }
    
    return score;

}
