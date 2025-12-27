#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include "include/file.h"
#include "include/language.h"
#include "include/highscores.h"
using namespace std;

const gametexts LANGUAGE_TEXTS = language_get_text_map_from_file("lang/fr.lang");

int main(int argc, char** arg) {
    highsc_table HIGH_SCORES;
    
    // highscores_insert_entry_into(highsc_entry("Jean neuille", 994), HIGH_SCORES);
    // highscores_insert_entry_into(highsc_entry("Casali", 840), HIGH_SCORES);
    // highscores_insert_entry_into(highsc_entry("Alexandre", 1000), HIGH_SCORES);
    // highscores_insert_entry_into(highsc_entry("Goofy", 100), HIGH_SCORES);
    // highscores_insert_entry_into(highsc_entry("Mimi", 500), HIGH_SCORES);

    // highscores_saveto(HIGH_SCORES, HIGHSC_FILENAME);
    highscores_loadto(string(arg[1]), HIGH_SCORES);

    for (highsc_entry & entry: HIGH_SCORES) cout << entry.first << "\t" << entry.second << endl;

    return 0;
}