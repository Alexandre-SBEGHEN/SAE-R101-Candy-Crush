#include <iostream>
#include <vector>
#include <QThread>

using namespace std;

typedef vector <unsigned> line; // un type représentant une ligne de la grille
typedef vector <line> mat; // un type représentant la grille
struct maPosition {
    unsigned abs;
    unsigned ord;
};

// QThread::msleep(500);

// On efface tout l'écran
void clearScreen () {
    cout << "\033[H\033[2J";
}

void displayGrid() {

}

int main()
{

    return 0;
}
