/**
 * @file inGameDisplay.cpp
 * @brief Les fonctions utilisées pour afficher la grille
 * @date 27 décembre 2025
 * @author Audren Metery-Drouin
 */

#include <iostream>
#include <vector>
#include <QThread>
#include <ctime>
#include <iomanip>

#include <inGameDisplay.h>

using namespace std;

//------------------------------ Constantes
// Nombre maximum de la valeur du bonbon
const unsigned NbCandies = 9;

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
    if (status == GLACE) couleur(KCyan+10);
    else if (status == GLACE_FAIBLE) couleur(KBleu+10);
}

void clearScreen () {
    cout << "\033[H\033[2J";
}

void displayGrid(gametexts texts, mat Tableau, EtatMat TableauEtat, enum StatusGame Status, maPosition CurrentPos, enum graphisme Details, size_t score, int coupsRestant) {

    // On efface l'écran
    clearScreen();

    // Affichage des abscisses
    if (Status == ABS || Status == MOUVEMENT) {
        couleur(KVert);
        cout << texts["ingame__ui__x"] << " --> |";
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
    // On skip la ligne si il n'y a pas d'abscisse à afficher
    if (Status != ABS && Status != MOUVEMENT) cout << endl;

    // Affichage des ordonnées
    if (Status == ORD || Status == ABS || Status == MOUVEMENT) {
        couleur(KVert);
        cout << texts["ingame__ui__y"] << " v" << endl;
    } else cout << endl;

    // Display of the grid
    for (size_t ord=0; ord < Tableau.size(); ord=ord+1) {

        // Indice de l'ordonné
        if (Status == ORD || Status == ABS || Status == MOUVEMENT) {
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
            if (TableauEtat[ord][abs] == GLACE || TableauEtat[ord][abs] == GLACE_FAIBLE) {
                // If cell is ice then we color the text black to see correctly
                couleur(KNoir);
            }
            // Write cell candy number
            if (Tableau[ord][abs] != KImpossible) {
                if (Details == LOW)
                    // Low Graphisms, candy displayed as numbers
                    cout << setw(2) << Tableau[ord][abs] << ' ';
                else if (Details == HIGH) {
                    // High Graphisms, candy displayed as emojis
                    int r = (Tableau[ord][abs]%9)+1;
                    if (r==1) {cout << " 🍬";}
                    else if (r==2) {cout << " 🍭";}
                    else if (r==3) {cout << " 🍫";}
                    else if (r==4) {cout << " 🧁";}
                    else if (r==5) {cout << " 🍰";}
                    else if (r==6) {cout << " 🍦";}
                    else if (r==7) {cout << " 🍨";}
                    else if (r==8) {cout << " 🍧";}
                    else if (r==9) {cout << " 🍢";}
                }
            } else {
                // Case vide
                cout << string(3, ' ');
            }
            // Close cell
            couleur(KReset);
            cout << '|';
        }
        // Display score
        string scoreTxt = texts["ingame__ui__score"] + " " + to_string(score);
        string coupsRestantTxt = texts["ingame__ui__remmoves"] + " " + to_string(coupsRestant);

        size_t maxSize = scoreTxt.size();
        if (coupsRestantTxt.size()>maxSize) maxSize=coupsRestantTxt.size();

        if (ord == 0) {
            cout << " /" << string(maxSize+2, '-') << '\\';
        } else if (ord == 3) {
            cout << " \\" << string(maxSize+2, '-') << '/';
        } else if (ord == 1) {
            cout << " | " << scoreTxt;
            if (scoreTxt.size()<maxSize) {
                cout << string(maxSize-scoreTxt.size(), ' ');
            }
            cout << " |";
        } else if (ord == 2) {
            cout << " | " << coupsRestantTxt;
            if (coupsRestantTxt.size()<maxSize) {
                cout << string(maxSize-coupsRestantTxt.size(), ' ');
            }
            cout << " |";
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
