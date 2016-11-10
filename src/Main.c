#include <ctype.h>
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
	unsigned char empty;
	uint16_t rows[9];
	uint16_t columns[9];
	uint16_t blocks[3][3];
};

/**
 * Generate a Sudoku and return a pointer to it (which must be freed).
 */
struct Sudoku *generate_sudoku() {
	struct Sudoku *sudoku = malloc(sizeof(struct Sudoku));
	for (int x = 0, i = 0; x < 9; x++) {
		sudoku->rows[x] = ALL_NUMBERS_ALLOWED;
		sudoku->columns[x] = ALL_NUMBERS_ALLOWED;
		sudoku->blocks[x / 3][x % 3] = ALL_NUMBERS_ALLOWED;
		for (int y = 0; y < 9; y++, i++) {
			sudoku->cells[i].value = 0;
			sudoku->cells[i].row = &sudoku->rows[y];
			sudoku->cells[i].column = &sudoku->columns[x];
			sudoku->cells[i].block = &sudoku->blocks[y / 3][x / 3];
		}
	}
	sudoku->empty = 81;
	return sudoku;
}

/**
 * Return a character representing the value given.
 */
char to_character(unsigned char value) {
	if (value) {
		return '0' + value;
	}
	return '.';
}

/**
 * Return a string representation of the Sudoku given (which must be freed).
 */
char *to_string(struct Sudoku *sudoku) {
	char *str = malloc(82);
	for (int i = 0; i < 81; i++) {
		str[i] = to_character(sudoku->cells[i].value);
	}
	str[81] = '\0';
	return str;
}

/**
 * Check whether a given value is allowed in a given area.
 */
uint16_t is_allowed_area(uint16_t *area, unsigned char value) {
	return *area & (1 << value);
}

/**
 * Check whether a given value is allowed for a given Cell.
 */
uint16_t is_allowed(struct Cell *cell, unsigned char value) {
	return is_allowed_area(cell->row, value)
		&& is_allowed_area(cell->column, value)
		&& is_allowed_area(cell->block, value);
}

/**
 * Set the flag of a given area corresponding to a given value to 1.
 */
void set_allowed_area(uint16_t *area, unsigned char value) {
	*area = *area | (1 << value);
}

/**
 * Set flags of all areas of a given cell corresponding to a given value to 1.
 */
void set_allowed(struct Cell *cell, unsigned char value) {
	set_allowed_area(cell->row, value);
	set_allowed_area(cell->column, value);
	set_allowed_area(cell->block, value);
}

/**
 * Set the flag of a given area corresponding to a given value to 0.
 */
void set_disallowed_area(uint16_t *area, unsigned char value) {
	*area = *area & ~(1 << value);
}

/**
 * Set flags of all areas of a given cell corresponding to a given value to 0.
 */
void set_disallowed(struct Cell *cell, unsigned char value) {
	set_disallowed_area(cell->row, value);
	set_disallowed_area(cell->column, value);
	set_disallowed_area(cell->block, value);
}

/**
 * Set the value of a given cell to a given value and update its the areas.
 */
void set_value(struct Cell *cell, unsigned char value) {
	cell->value = value;
	set_disallowed(cell, value);
}

/**
 * Clear a given cell by setting its value to 0 and updating its areas.
 */
void clear(struct Cell *cell) {
	set_allowed(cell, cell->value);
	cell->value = 0;
}

/**
 * Read in a Sudoku from a given seed. Everything other than 1..9 is treated as
 * an empty cell.
 */
void read(struct Sudoku *sudoku, char *seed) {
	for (int i = 0; i < 81; i++) {
		char c;
		if (!(c = seed[i])) {
			return;
		} else if (isdigit(c) && c != '0') {
			set_value(&sudoku->cells[i], c - '0');
			sudoku->empty--;
		}
	}
}

/**
 * Solve a given Sudoku using backtracking.
 */
int backtrack(struct Sudoku *sudoku) {
	if (sudoku->empty == 0) {
		return 1;
	}
	for (int i = 0; i < 81; i++) {
		struct Cell *cell = &sudoku->cells[i];
		if (!cell->value) {
			for (int v = 1; v <= 9; v++) {
				if (is_allowed(cell, v)) {
					set_value(cell, v);
					sudoku->empty--;
					if (backtrack(sudoku)) {
						return 1;
					}
					clear(cell);
					sudoku->empty++;
				}
			}
			return 0;
		}
	}
	return 0; // satisfy the compiler
}

int main(int argc, char** argv) {
	return EXIT_SUCCESS;
}
