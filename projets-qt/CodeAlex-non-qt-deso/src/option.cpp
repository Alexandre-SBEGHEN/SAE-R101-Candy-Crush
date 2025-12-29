/**
 * @file option.cpp
 * @brief Script de gestion d'options de lancement du programme
 * @author Alexandre SBEGHEN
 * @date 27/12/2025
 * @version 1.0
 */
#include <iostream>
#include "../include/option.h"
using namespace std;

/* Corps du prédicat `check_options_validity` qui assure que le programme est exécuté avec les bonnes options */
bool option_assert_validity(const int & argc) {
    return (argc == 1 || (argc&1) == 1);
}

/* Corps de la procédure `option_parse_to` qui insère les arguments de lancement dans une map d'options */
void option_parse_to(execoption & options, int argc, char** arg) {
    for (int i = 1; i < argc; i += 2) {
        string op_name = string(arg[i]);
        string op_val = string(arg[i + 1]);
        options[op_name] = op_val;
    }
}