#include <stdlib.h>

/**
 * @author: Hendrik Werner
 */

// a cell of the Sudoku
struct Cell {
	char value;
	int16_t *row;
	int16_t *column;
	int16_t *block;
};

int main(int argc, char** argv) {
	return EXIT_SUCCESS;
}
