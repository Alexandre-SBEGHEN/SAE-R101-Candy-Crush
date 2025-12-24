#include <iostream>
#include "include/language.h"
using namespace std;

const map<string, string> LANGUAGE_TEXTS = language_get_text_map_from_file("lang/fr.lang");

int main(int argc, char** arg) {
    for (auto & paire: LANGUAGE_TEXTS) {
        cout << paire.first << '\t' << paire.second << endl;
    }

    return 0;
}