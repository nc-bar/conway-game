#ifndef __OUTPUT__
#define __OUTPUT__

#include <stdio.h>
#include "cell_space.h"

void print_cell_space(CellSpace *cs, FILE *file);
void print_transitions(CellSpace *cs, int iter, FILE *file);
void print_transitions_stop_motion(CellSpace *cs);
void show_transitions(CellSpace *cs, int iter);

#endif
