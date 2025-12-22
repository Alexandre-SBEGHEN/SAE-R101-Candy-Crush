#include <vector>
using namespace std;

#ifndef TYPE_LIST
#define TYPE_LIST

//------------------------------ On définis les types custom
// Enum des status possible du jeu
enum StatusGame {
    IDLE, // Rien
    ORD, // Lorsque le joueur est entrain de choisir l'ordonnee de la case
    ABS, // Lorsque le joueur est entrain de choisir l'abscisse de la case
    MOUVEMENT, // Lorsque le joueur est entrain de choisir le mouvement à réaliser
};
// Matrice des valeurs des cases de la grille
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

#endif
