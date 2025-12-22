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


// -------------- Mouvements --------------//
int makeAMove(mat & grid, const maPosition & pos, const char & direction)
{
    int tRow = static_cast<int>(pos.abs);
    int tCol = static_cast<int>(pos.ord);

    switch(direction)
    {
    case 'Z': tRow -= 1; break;
    case 'S': tRow += 1; break;
    case 'Q': tCol -= 1; break;
    case 'D': tCol += 1; break;
    default:
        cout << "Direction invalide !" << endl;
        return 1;
    }

    // Vérification des limites
    if(tRow < 0 || tRow >= static_cast<int>(grid.size()) ||
        tCol < 0 || tCol >= static_cast<int>(grid[0].size()))
    {
        cout << "Mouvement hors grille !" << endl;
        return 1;
    }

    swap(grid[pos.abs][pos.ord], grid[tRow][tCol]);
    return 0;
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
    // Sauvegarde de la grille
    mat save = grid;

    // Essayer le mouvement
    if (makeAMove(grid, pos, direction) != 0)
        return false; // mouvement invalide (hors grille)

    maPosition p;
    unsigned howMany;

    // Tester s'il y a au moins un alignement
    bool ok = atLeastThreeInARow(grid, p, howMany)
              || atLeastThreeInAColumn(grid, p, howMany);

    // Si pas d'alignement --> on annule le mouvement
    if (!ok) {
        grid = save;
    }

    return ok;
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

    while(quitter != 'O' && quitter != 'o') {
        displayGrid(grid);

        cout << "Choisissez une ligne à déplacer : ";
        unsigned ligne, colonne;
        cin >> ligne;

        cout << "Choisissez une colonne à déplacer : ";
        cin >> colonne;

        // Vérification des limites
        if(ligne >= grid.size() || colonne >= grid[0].size()) {
            cout << "Case invalide! " << endl;
            continue;
        }

        cout << "Choisissez la direction (Z = Haut, S = Bas, Q = Gauche, D = Droite) : " <<endl;
        char dir;
        cin >> dir;

        maPosition pos{ligne, colonne};

        if (moveIsValid(grid, pos, dir)) {
            removeColRow(grid);
        } else {
            cout << "Mouvement interdit : aucun alignement possible !" << endl;
            cin.ignore(10000, '\n');
            cin.get(); // pause pour lire le message
        }


        // Affiche grille après tour
        displayGrid(grid);

        cout << "Voulez-vous quitter/ abandonner ? (O/N) : ";
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
