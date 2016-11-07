#include <stdint.h>
#include <stdlib.h>

/**
 * @author: Hendrik Werner
 */

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
	uint16_t blocks[9];
};

int main(int argc, char** argv) {
	return EXIT_SUCCESS;
}
