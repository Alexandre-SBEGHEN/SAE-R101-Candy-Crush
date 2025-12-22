#include <iostream>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

string lang_file_readline(ifstream & file) {
    string line;
    while (true) {
        getline(file, line);
        if (line.substr(0, 2) != "//") break;
    }
    return line;
}

string lang_file_line_to_key(const string & line) {
    size_t index = 0;
    while (line[index] != ' ') ++index;
    return line.substr(0, index);
}
string lang_file_line_to_val(const string & line) {
    size_t index = line.length() - 1;
    while (line[index] != ' ' || line[index - 1] != ' ') --index;
    return line.substr(index + 1, line.length() - index);
}

void lang_file_to_map(const string & filename) {
    ifstream file(filename);

    //Récupérer le nom de langue
    const string FILE_LANG = lang_file_readline(file);
    map<string, string> file_map;
    file_map["LANGUAGE"] = FILE_LANG;
    
    //Récupérer les couples clé/valeur et les assiner à 'file_map'
    while (!file.eof()) {
        string line = lang_file_readline(file);
        string key = lang_file_line_to_key(line);
        string val = lang_file_line_to_val(line);
        file_map[key] = val;
    }

    for (auto const & pair: file_map) cout << pair.second << endl;
}

const map<string, vector<string>> TITLE_BUTTONS = {
    //Play, High scores, Settings, About
    {"main", {
        "Play",
        "High scores",
        "Settings",
        "About",
        "Quit"
    }},
    {"high_scores", {
        "Save high scores",
        "Load high scores",
        "Back"
    }},
    {"settings", {
        "Language",
        "Moving way",
        "Back"
    }},
    {"about", {
        "Back"
    }},
    //Settings->Language, Settings->Moving way
    {"settings__language", {
        "French",
        "English (current)",
        "Back"
    }},
    {"settings__moving_way", {
        "Cell by cell (sequence of keys)",
        "Instantaneous (coordinates)",
        "Back"
    }}
};

int main(int argc, char** arg) {
    
    lang_file_to_map(arg[1]);
    
    return 0;
 }