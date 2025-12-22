#include <typeList.h>

using namespace std;

const unsigned NbCandies = 9; // Nombre maximum de la valeur du bonbon

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

/**
 * @brief Met en couleur le terminal selon la valeur choisis
 * @param coul La valeur de la couleur choisis
 */
void couleur (const unsigned & coul);

/**
 * @brief couleurBonbon
 * @param Met la bonne couleur dans le terminal selon le bonbon actuelle
 */
void couleurBonbon(unsigned Bonbon);

/**
 * @brief couleurCase
 * @param Met la bonne couleur dans le terminal selon l'état de la case actuelle de la grille
 */
void couleurCase(enum StatusCase status);

/**
 * @brief Efface tout l'écran
 */
void clearScreen ();

/**
 * @brief Affiche la grille
 * @param Tableau Le contenu de la grille
 * @param TableauEtat Les états des cases de la grille
 * @param Status Ce que le joueur est actuellement en train de faire
 * @param CurrentPos La position actuelle sélectionner
 */
void displayGrid(mat Tableau, EtatMat TableauEtat, enum StatusGame Status, maPosition CurrentPos);

//------------------------------ Fonctions d'initialisation des grilles

/**
 * @brief Initialisation des valeurs de la grille
 * @param Tableau La Grille à initialiser
 * @param Taille Taille de la grille
 */
void initGrid(mat & Tableau, unsigned Taille);

/**
 * @brief Initialisation des états des cases de la grille
 * @param TableauEtat La grille des états à initialiser
 * @param Taille Taille de la grille
 */
void initEtatGrid(EtatMat & TableauEtat, unsigned Taille);
