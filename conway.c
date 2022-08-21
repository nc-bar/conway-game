#include <stdio.h>
#include <stdlib.h>

#include "cell_space.h"
#include "input.h"
#include "output.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        exit(-1);
    }

    CellSpace *cs = create_from_file(argv[1]);
    show_transitions(cs, 1000000);
    delete_cell_space(cs);
}
