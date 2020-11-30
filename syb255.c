#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int check_adjacents(int dimensions, int _matrix[dimensions][dimensions], int x, int y) {
    int (*matrix)[dimensions] = _matrix;
    int alive, dead, minx, miny, maxx, maxy;
    int status = matrix[x][y];
    if ((x - 1) >= 0) {
        minx = x - 1;
    }
    else {
        minx = x;
    }
    if ((y - 1) >= 0) {
        miny = y - 1;
    }
    else {
        miny = y;
    }
    if ((x + 1) <= dimensions) {
        maxx = x + 1;
    }
    else {
        maxx = x;
    }
    if ((y + 1) <= dimensions) {
        maxy = y + 1;
    }
    else {
        maxy = y;
    }
    for (int i = minx; i <= maxx; i++) {
        for (int j = miny; j <= maxy; j++) {
            if ((i == x) && (j == y)) {
                continue;
            }
            if (matrix[i][j] >= 1) {
                alive += 1;
            }
            else {
                dead += 1;
            }
        }
    }
    if (status == 1) {
        if (alive < 2) {
            return 0;
        }
        else if (alive > 3) {
            return 0;
        }
        else {
            return 1;
        }
    }
    else {
        if (alive == 3) {
            return 1;
        }
        else {
            return 0;
        }
    }
}

int main(int argc, char *argv[]) {
    int generations = atoi(argv[1]);
    int dimensions = atoi(argv[2]);
    int** matrix = malloc(dimensions * sizeof(*matrix));
    for (int d = 0; d < dimensions; d++) {
        matrix[d] = malloc(dimensions * sizeof(*matrix[d]));
    }
    int threads = atoi(argv[3]);
    int len = strlen(argv[4]);
    char *filename = (char *)malloc(len);
    char *outname = (char *)malloc(len);
    strcat(filename, argv[4]);
    strcat(outname, argv[4]);
    FILE *f;
    f = fopen(filename, "r");
    if (f != NULL) {
        for (int m = 0; m < dimensions; m++) {
            for (int n = 0; n < dimensions; n++) {
                fscanf(f, "%d", &matrix[m][n]);
            }
        }
    }
    fclose(f);
    int updated[dimensions][dimensions];
    double start, finish, total;
    start = omp_get_wtime();
    int x, y;
    for (int i = 1; i <= generations; i++) {
        #pragma omp parallel shared(matrix, updated, dimensions) private(x, y) num_threads(threads)
        {
            #pragma omp for
            for (x = 0; x < dimensions; x++) {
                for (y = 0; y < dimensions; y++) {
                    updated[x][y] = check_adjacents(dimensions, matrix, x, y);
                }
            }
            #pragma omp for
            for (x = 0; x < dimensions; x++) {
                for (y = 0; y < dimensions; y++) {
                    matrix[x][y] = updated[x][y];
                }
            }
        }
    }
    finish = omp_get_wtime();
    total = finish - start;
    printf("Time elapsed for %d threads: %f seconds\n", threads, total);
    FILE *out;
    int e, g;
    e = sprintf(outname, "%s.out", filename);
    out = fopen(outname, "w");
    for (int s = 0; s < dimensions; s++) {
        for (int t = 0; t < dimensions; t++) {
            g = matrix[s][t];
            fprintf(out, "%d ", g);
        }
        fprintf(out, "\n");
    }
    fclose(out);
    return 0;
}
