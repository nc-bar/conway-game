#ifndef __INPUT__
#define __INPUT__

#include "cell_space.h"

CellSpace* create_from_file(char *file);

CellSpace* create_random_cells(int height, int weight);
CellSpace* create_blinker();
CellSpace* create_toad();
CellSpace* create_beacon();

#endif

