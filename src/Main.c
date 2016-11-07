#include <stdint.h>
#include <stdlib.h>

/**
 * @author: Hendrik Werner
 */

// a cell of the Sudoku
struct Cell {
	char value;
	uint16_t *row;
	uint16_t *column;
	uint16_t *block;
};

int main(int argc, char** argv) {
	return EXIT_SUCCESS;
}
