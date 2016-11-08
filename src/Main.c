#include <stdint.h>
#include <stdlib.h>

/**
 * @author: Hendrik Werner
 */

#define ALL_NUMBERS_ALLOWED 1022

// a cell of the Sudoku
struct Cell {
	unsigned char value;
	uint16_t *row;
	uint16_t *column;
	uint16_t *block;
};

struct Sudoku {
	struct Cell cells[81];
	uint16_t rows[9];
	uint16_t columns[9];
	uint16_t blocks[3][3];
};

/**
 * Generate a Sudoku and return a pointer to it (which must be freed).
 */
struct Sudoku *generate_sudoku() {
	struct Sudoku *sudoku = malloc(sizeof(struct Sudoku));
	for (int i = 0; i < 9; i++) {
		sudoku->rows[i] = ALL_NUMBERS_ALLOWED;
		sudoku->columns[i] = ALL_NUMBERS_ALLOWED;
		sudoku->blocks[i / 3][i % 3] = ALL_NUMBERS_ALLOWED;
	}
	int i = 0;
	for (int x = 0; x < 9; x++) {
		for (int y = 0; y < 9; y++) {
			sudoku->cells[i].row = &sudoku->rows[y];
			sudoku->cells[i].column = &sudoku->columns[x];
			sudoku->cells[i].block = &sudoku->blocks[y / 3][x / 3];
			i++;
		}
	}
	return sudoku;
}

int main(int argc, char** argv) {
	return EXIT_SUCCESS;
}
