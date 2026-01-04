/**
 * @file candycrush.h
 * @brief Fichier header du gameplay
 * @author Audren Metery-Drouin
 * @date 03/01/2026
 * @version 1.0
 */
#ifndef CANDYCRUSH_H
#define CANDYCRUSH_H
#include <language.h>

/**
 * @brief Lance une partie de Candy Crush.
 * 
 * @param texts Les textes du jeu dans la bonne langue.
 * @param movingway Le mode de déplacement.
 * @param fancydisplay Activer ou non les graphismes élevés.
 */
size_t candycrush_play(gametexts texts, const size_t & movingway, const bool & fancydisplay);


#endif
