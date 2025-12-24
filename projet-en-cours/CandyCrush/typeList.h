/**
 *  @date : 24 décembre 2025
 *  @author : Audren Metery-Drouin
 *  @Brief : Les types ou struct custom utilisés par les autres scripts
**/

#include <vector>
using namespace std;

#ifndef TYPE_LIST // Pour éviter de définir plusieurs fois les types dans le main.cpp
#define TYPE_LIST

const unsigned KImpossible = 0;

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
// Enum des états des cases de la grille
enum StatusCase {
    NORMAL,
    GLACE,
    GLACE_FAIBLE,
};
// Matrice des états des cases de la grille
typedef vector <enum StatusCase> Etatline;
typedef vector <Etatline> EtatMat;

// Enum des niveaux de graphismes
enum graphisme {
    LOW, // Sous forme de chiffres
    HIGH, // Sous forme d'émojis
};

// Enum des différentes gravités possibles
enum gravType {
    UP,
    DOWN,
    LEFT,
    RIGHT,
};

#endif
