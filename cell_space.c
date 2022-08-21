#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "cell_space.h"

CellSpace* create_cell_space(int height, int width) {
    assert(height > 2);
    assert(width > 2);

    CellSpace *cs = malloc(sizeof(CellSpace));
    if (!cs)
        perror("create_cell_space"), exit(-1);

    char **cell = malloc(height * sizeof(char*));
    if (!cell)
        perror("create_cell_space"), free(cs), exit(-1);

    char **buffer = malloc(height * sizeof(char*));
    if (!buffer)
        perror("create_cell_space"), free(cs), exit(-1);
    
    for (int i = 0; i < height; i++) {
        char *row = malloc(width * sizeof(char));
        char *row_buf = malloc(width * sizeof(char));

        if (row != NULL && row_buf != NULL) {
            cell[i] = row;
            buffer[i] = row_buf;
        } else {
            for (int k = 0; k < i; k++) {
                free(cell[k]);
                free(buffer[k]);
            }
            if (row) free(row);
            if (row_buf) free(row_buf);

            perror("create_cell_space");
            exit(-1);
        }
    }

    for (int i = 0; i < cs->height; i++)  {
        for (int j = 0; j < cs->width; j++) {
            cell[i][j] = DEAD;
        }
    }

    cs->cell = cell;
    cs->buffer = buffer;
    cs->height = height;
    cs->width = width;
    return cs;
}

void delete_cell_space(CellSpace *cs) {
    assert(cs);
    assert(cs->cell);
    assert(cs->buffer);

    for (int i = 0; i < cs->height; i++) {
        free(cs->cell[i]);
        free(cs->buffer[i]);
    }
    free(cs);
}

char get_cell(CellSpace *cs, int i, int j) {
    assert(cs);
    assert(cs->cell);

    if (i < 0 || i >= cs->height)
        return DEAD;

    if (j < 0 || j >= cs->width)
        return DEAD;

    return cs->cell[i][j];
}

int alive_neighbors(CellSpace *cs, int i, int j) {
    assert(cs);
    assert(cs->cell);
    assert(i >= 0 || i <= cs->height);
    assert(j >= 0 || j <= cs->width);
   
    int n = 0;
    n += (int)get_cell(cs, i-1, j-1);
    n += (int)get_cell(cs, i-1, j);
    n += (int)get_cell(cs, i-1, j+1);
    n += (int)get_cell(cs, i,   j+1);
    n += (int)get_cell(cs, i,   j-1);
    n += (int)get_cell(cs, i+1, j-1);
    n += (int)get_cell(cs, i+1, j);
    n += (int)get_cell(cs, i+1, j+1);
    return n;
}

static void swap(CellSpace *cs) {
    char **tmp = cs->cell;
    cs->cell = cs->buffer;
    cs->buffer = tmp;
}

void transition(CellSpace *cs) {
    assert(cs);
    assert(cs->cell);
    assert(cs->buffer);

    for (int i = 0; i < cs->height; i++) {
        for (int j = 0; j < cs->width; j++) {
            int an = alive_neighbors(cs, i, j);
            if (cs->cell[i][j] == ALIVE) 
                cs->buffer[i][j] = (an > 3 || an < 2) ? DEAD : ALIVE;
            else
                cs->buffer[i][j] = (an == 3) ? ALIVE : DEAD;
        }
    }
    swap(cs);
}
