#ifndef __CELL_SPACE__
#define __CELL_SPACE__

#define ALIVE 1
#define DEAD 0

typedef 
struct {
    char **cell;
    char **buffer;
    int height;
    int width;
} CellSpace;

//Methods to interact with a CellSpace
CellSpace* create_cell_space(int height, int width);
void delete_cell_space(CellSpace *cs);
char get_cell(CellSpace *cs, int i, int j);
void change_cell(CellSpace *cs, int i, int j);
int alive_neighbors(CellSpace *cs, int i, int j);
void transition(CellSpace *cs);

#endif

