#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <ncurses.h>

#include "cell_space.h"
#include "output.h"

void print_cell_space(CellSpace *cs, FILE* file) {
    assert(cs);
    assert(cs->cell);
    
    for (int i = 0; i < cs->height; i++) {
        for (int j = 0; j < cs->width; j++)
            fprintf(file, "%c", cs->cell[i][j] == ALIVE ? '#' : ' ');
        
        fprintf(file, "\n");
    }
}

void print_transitions(CellSpace *cs, int iter, FILE *file) {
    for (int i = 0; i < iter; i++) {
        print_cell_space(cs, file);
        transition(cs);
        fprintf(file, "\n\n");
    }
}

void print_transitions_stop_motion(CellSpace *cs) {
    for (;;) {
        print_cell_space(cs, stdout);
        transition(cs);
        sleep(1);
        system("clear");
    }
}

/*
TODO:
    Centrar el automata en pantalla
         
*/

void show_transitions(CellSpace *cs, int iter) {
    if (!initscr()) {
        fprintf(stderr, "initscr() failed in show_transttions");
        exit(-1);
    }
    cbreak(); // disable buffering
    noecho(); // suppress the echo
    curs_set(0); // hiding cursor

    int h, w;
    getmaxyx(stdscr, h, w);
    if (cs->height > h || cs->width > w) {
        fprintf(stderr, "CellSpace bigger than screen.");
        endwin();
        exit(-1);
    }
    
    for (int k = 1; k < iter; k++) {
        for (int i = 0; i < cs->height; i++) {
            for (int j = 0; j < cs->width; j++) {
                move(i,j);
                int alive = cs->cell[i][j];
                if (alive) {
                    addch(' ' | A_REVERSE);
                } else {
                    addch(' ');
                }
            }
        }
        refresh();

        sleep(1);
        transition(cs);
    }

    endwin();
}
