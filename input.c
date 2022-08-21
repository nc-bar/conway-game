#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "cell_space.h"
#include "input.h"

static int read_size(FILE *fp, int* d) {
    char tmp[7];
    tmp[6] = '\0';
    int c, count = 0;
    for (int i = 0; i < 6; i++) {
        c = fgetc(fp);
        if (feof(fp))
            return 1;
        if (c == '\n')
            break;
        tmp[count] = (char) c;
        count++;
    }
    tmp[count] = '\0';
    *d = atoi(tmp);
    return 0;
}

CellSpace* create_from_file(char *file) {
    FILE *fp = fopen(file, "r");
    if (!fp)
        perror("create_from_file error opening file"), exit(-1);

    int height, width;
    if (read_size(fp, &height))
        fprintf(stderr, "create_from_file error bad format\n"),exit(-1);
    
    if (read_size(fp, &width))
        fprintf(stderr, "create_from_file error bad format\n"),exit(-1);

    int c;
    CellSpace *cs = create_cell_space(height, width);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            c = fgetc(fp);
            
            if (feof(fp))
                fprintf(stderr, "create_from_file: error bad format\nEOF not expected\n"),exit(-1);

            if (c == '\n') {
                fprintf(stderr, "create_from_file: error bad format\n");
                fprintf(stderr, "wrong width in line %d\n", i+1);
                exit(-1);
            }
            cs->cell[i][j] = (c == ' ') ? DEAD : ALIVE;
        }
        c = fgetc(fp);
        if (c != '\n')
            fprintf(stderr, "create_from_file error bad format\n"),exit(-1);
    }
    
    fclose(fp);
    return cs;
}

CellSpace* create_random_cells(int height, int width) {
    CellSpace *cs = create_cell_space(height, width);

    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            cs->cell[i][j] = random() % 2;

    return cs;
}

CellSpace* create_blinker() {
    CellSpace *cs = create_cell_space(3,3);

    cs->cell[0][0] = 0;cs->cell[0][1] = 0;cs->cell[0][2] = 0;
    cs->cell[1][0] = 1;cs->cell[1][1] = 1;cs->cell[1][2] = 1;
    cs->cell[2][0] = 0;cs->cell[2][1] = 0;cs->cell[2][2] = 0;

    return cs;
}

CellSpace* create_toad() {
    CellSpace *cs = create_cell_space(4,4);
    
    cs->cell[0][0] = 0;cs->cell[0][1] = 0;cs->cell[0][2] = 0;cs->cell[0][3] = 0;
    cs->cell[1][0] = 0;cs->cell[1][1] = 1;cs->cell[1][2] = 1;cs->cell[1][3] = 1;
    cs->cell[2][0] = 1;cs->cell[2][1] = 1;cs->cell[2][2] = 1;cs->cell[2][3] = 0;
    cs->cell[3][0] = 0;cs->cell[3][1] = 0;cs->cell[3][2] = 0;cs->cell[3][3] = 0;

    return cs;
}

CellSpace* create_beacon() {
    CellSpace *cs = create_cell_space(4,4);

    cs->cell[0][0] = 1;cs->cell[0][1] = 1;cs->cell[0][2] = 0;cs->cell[0][3] = 0;
    cs->cell[1][0] = 1;cs->cell[1][1] = 0;cs->cell[1][2] = 0;cs->cell[1][3] = 0;
    cs->cell[2][0] = 0;cs->cell[2][1] = 0;cs->cell[2][2] = 0;cs->cell[2][3] = 1;
    cs->cell[3][0] = 0;cs->cell[3][1] = 0;cs->cell[3][2] = 1;cs->cell[3][3] = 1;

    return cs;
}
