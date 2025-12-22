#include <iostream>
#include <vector>
#include <QThread>
#include <ctime>
#include <iomanip>

using namespace std;

//------------------------------ On définis les types custom
// Matrice des valeurs des cases de la grille
unsigned NbCandies = 9; // Nombre maximum de la valeur du bonbon
typedef vector <unsigned> line;
typedef vector <line> mat;
// Type position custom
struct maPosition {
    unsigned abs;
    unsigned ord;
};
// Matrice des états des cases de la grille
enum StatusCase {
    NORMAL,
    GLACE,
    GLACE_FAIBLE,
};
typedef vector <enum StatusCase> Etatline;
typedef vector <Etatline> EtatMat;

// Enum des status possible du jeu
enum StatusGame {
    IDLE, // Rien
    ORD, // Lorsque le joueur est entrain de choisir l'ordonnee de la case
    ABS, // Lorsque le joueur est entrain de choisir l'abscisse de la case
    MOUVEMENT, // Lorsque le joueur est entrain de choisir le mouvement à réaliser
};

// Liste des couleurs
const unsigned KReset   (0);
const unsigned KNoir    (30);

const unsigned KRouge   (31);
const unsigned KVert    (32);
const unsigned KJaune   (33);
const unsigned KBleu    (34);
const unsigned KMagenta (35);
const unsigned KCyan    (36);
const unsigned KRougeClair (91);
const unsigned KVertClair  (92);
const unsigned KBeige      (93);

// QThread::msleep(500);

//------------------------------ Fonctions d'affichage
void couleur (const unsigned & coul) {
    cout << "\033[" << coul <<"m";
}

void couleurBonbon(unsigned Bonbon) {
    unsigned NbCoulPossible = 9;
    if (Bonbon%NbCoulPossible == 1) couleur(KRouge);
    else if (Bonbon%NbCoulPossible == 2) couleur(KVert);
    else if (Bonbon%NbCoulPossible == 3) couleur(KJaune);
    else if (Bonbon%NbCoulPossible == 4) couleur(KBleu);
    else if (Bonbon%NbCoulPossible == 5) couleur(KMagenta);
    else if (Bonbon%NbCoulPossible == 6) couleur(KCyan);
    else if (Bonbon%NbCoulPossible == 7) couleur(KRougeClair);
    else if (Bonbon%NbCoulPossible == 8) couleur(KVertClair);
    else if (Bonbon%NbCoulPossible == 0) couleur(KBeige);
}
void couleurCase(enum StatusCase status) {
    if (status == GLACE) couleur(KBleu+10);
    else if (status == GLACE_FAIBLE) couleur(KCyan+10);
}

// On efface tout l'écran
void clearScreen () {
    cout << "\033[H\033[2J";
}

void displayGrid(mat Tableau, EtatMat TableauEtat, enum StatusGame Status, maPosition CurrentPos) {

    // Affichage des abscisses
    if (Status == ABS || Status == MOUVEMENT) {
        couleur(KVert);
        cout << "Abscisse --> |";
        for (size_t i=0; i<size(Tableau); ++i) {
            if (i == CurrentPos.abs) {
                couleur(KRougeClair+10);
                couleur(KNoir);
            }
            cout << setw(2) << i+1 << ' ';
            couleur(KReset);
            couleur(KVert);
            cout << '|';
        }
        cout << endl;
    }
    // Skip line if no abscisse displayed
    if (Status != ABS && Status != MOUVEMENT) cout << endl;

    // Affichage des ordonnées
    if (Status == ORD || Status == MOUVEMENT) {
        couleur(KVert);
        cout << "Ordonnée v" << endl;
    } else cout << endl;

    // Display of the grid
    for (size_t ord=0; ord < Tableau.size(); ord=ord+1) {

        // Indice de l'ordonné
        if (Status == ORD || Status == MOUVEMENT) {
            couleur(KVert);
            cout << string(8, ' ');
            if (ord == CurrentPos.ord) {
                couleur(KRougeClair+10);
                couleur(KNoir);
            }
            cout << setw(2) << ord+1 << ' ';
            couleur(KReset);
            cout << "  ";
        }
        else cout << string(13, ' ');
        // Affichage de la ligne
        couleur(KReset);
        cout << '|';
        for (size_t abs=0; abs < Tableau[ord].size(); abs=abs+1) {
            couleur(KReset);
            // Candy Color
            couleurBonbon(Tableau[ord][abs]);
            // Cell Color
            couleurCase(TableauEtat[ord][abs]);
            // Write cell candy number
            cout << setw(2) << Tableau[ord][abs] << ' ';
            // Close cell
            couleur(KReset);
            cout << '|';
        }
        cout << endl;
    }
}

//------------------------------ Fonctions d'initialisation des grilles
void initGrid(mat & Tableau, unsigned Taille) {
    Tableau.resize(Taille);
    for (unsigned ord=0; ord < Tableau.size(); ord=ord+1) {
        Tableau[ord].resize(Taille);
        for (unsigned abs=0; abs < Tableau[ord].size(); abs=abs+1) {
            Tableau[ord][abs] = (rand()%NbCandies)+1;
        }
    }
}
void initEtatGrid(EtatMat & TableauEtat, unsigned Taille) {
    TableauEtat.resize(Taille);
    for (unsigned ord=0; ord < TableauEtat.size(); ord=ord+1) {
        TableauEtat[ord].resize(Taille);
        for (unsigned abs=0; abs < TableauEtat[ord].size(); abs=abs+1) {

            int choosen = (rand()%3)+1;
            if (choosen < 3) TableauEtat[ord][abs] = NORMAL;
            else TableauEtat[ord][abs] = GLACE;

        }
    }
}

//------------------------------ Main (A enlever lorsque l'on transformera le script en une librairy?)
int main()
{

    // Randomize
    srand(time(0));

    //------------------------------ Variables
    enum StatusGame Status = IDLE;
    mat Tableau;
    EtatMat TableauEtat;
    unsigned Taille = 12;

    // Test
    maPosition Pos;
    Pos.ord = 4;
    Pos.abs = 4;

    Status = MOUVEMENT;
    initGrid(Tableau, Taille);
    initEtatGrid(TableauEtat, Taille);
    displayGrid(Tableau, TableauEtat, Status, Pos);

    return 0;
}
