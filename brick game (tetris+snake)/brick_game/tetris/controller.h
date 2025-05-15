#ifndef TETRIS_H
#define TETRIS_H

#include <locale.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../../common/bg_objects.h"
#include "tetris_backend.h"
#include "tetris_defines.h"
#include "tetris_matrix.h"
#include "tetris_objects.h"

GameInfo_t updateCurrentState() ;
void userInput(UserAction_t action, bool hold);
params_t *get_tetris_game() ;

#endif
