#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Types
typedef vector<unsigned> line;
typedef vector<line> mat;
struct maPosition { unsigned abs; unsigned ord; };

// Constantes
const unsigned KNbCandies = 6;

// -------------- Fonctions de bases -------------- //
void clearScreen() { cout << "\033[H\033[2J"; }
void couleur(const unsigned &coul) { cout << "\033[" << coul << "m"; }

// -------------- Initialisation -------------- //
void initGrid(mat & grid, const size_t & matSize)
{
    grid.assign(matSize, line(matSize, 0));
    for(size_t i = 0; i < matSize; i++)
        for(size_t j = 0; j < matSize; j++)
            grid[i][j] = (rand() % KNbCandies) + 1;
}

// -------------- Couleurs -------------- //
unsigned getColor(unsigned val)
{
    switch(val){
    case 1: return 31; // Rouge
    case 2: return 32; // Vert
    case 3: return 33; // Jaune
    case 4: return 34; // Bleu
    case 5: return 35; // Magenta
    case 6: return 36; // Cyan
    default: return 0;
    }
}

// -------------- Affichage --------------//
void displayGrid(const mat & grid)
{
    clearScreen();
    for(size_t i = 0; i < grid.size(); i++){
        for(size_t j = 0; j < grid[i].size(); j++){
            unsigned val = grid[i][j];
            if(val >= 1 && val <= KNbCandies){
                couleur(getColor(val));
                cout << val << " ";
                couleur(0);
            } else {
                cout << ". ";  // cases vides
            }
        }
        cout << endl;
    }
}





//-------------- Détection horizontal --------------//
bool atLeastThreeInARow(const mat & grid, maPosition & pos, unsigned & howMany)
{
    const size_t nRows = grid.size();
    const size_t nCols = grid[0].size();

    for(size_t i = 0; i < nRows; i++) {
        unsigned count = 1;
        unsigned currentValue = grid[i][0];
        size_t startCol = 0;

        for(size_t j = 1; j < nCols; j++) {
            if(grid[i][j] == currentValue && currentValue != 0) {
                count++;
            } else {
                currentValue = grid[i][j];
                count = 1;
                startCol = j;
            }

            if(count >= 3) {
                pos.abs = i;
                pos.ord = startCol;
                howMany = count;
                return true;
            }
        }
    }
    return false;
}



// -------------- Détection vertical --------------//

bool atLeastThreeInAColumn(const mat & grid, maPosition & pos, unsigned & howMany)
{
    const size_t nRows = grid.size();
    const size_t nCols = grid[0].size();

    for(size_t j = 0; j < nCols; j++) {
        unsigned count = 1;
        unsigned currentValue = grid[0][j];
        size_t startRow = 0;

        for(size_t i = 1; i < nRows; i++) {
            if(grid[i][j] == currentValue && currentValue != 0) {
                count++;
            } else {
                currentValue = grid[i][j];
                count = 1;
                startRow = i;
            }

            if(count >= 3) {
                pos.abs = startRow;
                pos.ord = j;
                howMany = count;
                return true;
            }
        }
    }
    return false;
}



// -------------- Supprimer les "bonbons" en ligne --------------//
void removeRow(mat & grid, const maPosition & pos, unsigned howMany)
{
    for(unsigned j = 0; j < howMany; j++)
        grid[pos.abs][pos.ord + j] = 0;
}



// -------------- Supprimer les "bonbons" en colonne ---------------//
void removeColumn(mat & grid, const maPosition & pos, unsigned howMany)
{
    for(unsigned i = 0; i < howMany; i++)
        grid[pos.abs + i][pos.ord] = 0;
}



// -------------- Faire tomber les "bonbons" --------------//
void dropCandies(mat & grid)
{
    const size_t nRows = grid.size();
    const size_t nCols = grid[0].size();

    for(size_t j = 0; j < nCols; j++) {
        for(int i = nRows - 1; i > 0; i--) {
            if(grid[i][j] == 0) {
                int k = i - 1;
                while(k >= 0 && grid[k][j] == 0) k--;
                if(k >= 0) {
                    grid[i][j] = grid[k][j];
                    grid[k][j] = 0;
                }
            }
        }
    }
}

// -------------- Remplir les cases vides --------------//
void fillEmpty(mat & grid)
{
    for(size_t i = 0; i < grid.size(); i++)
        for(size_t j = 0; j < grid[i].size(); j++)
            if(grid[i][j] == 0)
                grid[i][j] = (rand() % KNbCandies) + 1;
}


// -------------- Supprimer toutes les suites de lignes et colonnes --------------//
void removeColRow(mat & grid)
{
    bool found = true;
    while(found) {
        found = false;
        maPosition pos;
        unsigned howMany;

        // Supprimer les lignes
        while(atLeastThreeInARow(grid, pos, howMany)) {
            removeRow(grid, pos, howMany);
            found = true;
        }

        // Supprimer les colonnes
        while(atLeastThreeInAColumn(grid, pos, howMany)) {
            removeColumn(grid, pos, howMany);
            found = true;
        }

        if(found) {
            dropCandies(grid);
            fillEmpty(grid);
        }
    }
}

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

    return ok;
}


// -------------- Mouvements --------------//
struct swapResult {
    bool ok;            // le mouvement est valide ?
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


//-------------- Fonction jouer --------------//
void jouer()
{
    const size_t taille = 8; // taille de la grille
    mat grid;
    srand(time(nullptr));
    initGrid(grid, taille);
    removeColRow(grid);

    char quitter = 'N';

    while (quitter != 'O' && quitter != 'o') {
        displayGrid(grid);

        cout << "Mode de jeu ?" <<endl;
        cout << "1 - Coordonnees" <<endl;
        cout << "2 - Curseur" <<endl;
        cout << "Choix : ";

        int mode;
        cin >> mode;

        swapResult res;

        if (mode == 1) {
            unsigned l, c;
            char dir;

            cout << "Ligne : ";
            cin >> l;
            cout << "Colonne : ";
            cin >> c;
            cout << "Direction (ZQSD) : ";
            cin >> dir;

            res = moveByCoordinates(grid, l, c, dir);
        }
        else if (mode == 2) {   //Pour deplacement par "curseur"
            res = moveByCursor(grid);
        }
        else { // Si l'utilisateur rentre un mauvais mode, on stop
            cout << "Gros Boulet"<<endl;
            break;
        }

        if (res.ok) { //Mouvement correcte
            removeColRow(grid);
            displayGrid(grid);
            cout << "Echange entre ("
                 << res.p1.abs << "," << res.p1.ord << ") et ("
                 << res.p2.abs << "," << res.p2.ord << ")" <<endl;
        } else { //Mouvement incorrecte
            cout << "Mouvement impossible !" <<endl;
        }

        cout << "Quitter ? (O/N) : ";
        cin >> quitter;
    }

    cout << "Game Over !" << endl;
}


// -------------- Fonction Principale --------------//
int main()
{
    jouer();
    return 0;
}
