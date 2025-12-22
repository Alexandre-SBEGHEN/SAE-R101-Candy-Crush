#include <iostream>
using namespace std;

//Convertir un entier u8 (0-255) en string qui contient le caractère en question
//Prise en charge des caractère accentués mais doivent être placés à la main
string ascii_ext_to_string(const unsigned char & ascii) {
    switch (ascii) {
        default: return string(1, ascii); break;
            
        case 0x82: return "é"; break;
        case 0x8A: return "è"; break;
    }
}

