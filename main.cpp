#include <iostream>
#include <vector>
#include <iterator>
#include <map>

using namespace std;

void print_matrix(int *mat, int rows, int cols) {
	std::cout << "Printing Matrix: " << std::endl;
	for (int row = 0; row < rows; row++) {
		for (int col = 0; col < cols; col++) {
			std::cout << *((mat + row * cols) + col) << " ";
		}
		std::cout << std::endl;
	}
	cout << std::endl;
}

void multiply_matrix(
	int* mat_1, int rows_1, int cols_1,
	int* mat_2, int rows_2, int cols_2
) {
	if (cols_1 != rows_2) {
		std::cout << "Cannot multiply these matrices of dimensions:\n"
			<< "\t" << rows_1 << " x " << cols_1
			<< "\n\tby:"
			<< "\t" << rows_2 << " x " << cols_2;
		return;
	}
	int *result_mat = (int *)calloc(rows_1*cols_2, sizeof(int));

	for (int i = 0; i < rows_1; i++) {
		for (int j = 0; j < cols_2; j++) {
			for (int k = 0; k < cols_1; k++) {
				int mat_1_val = (*((mat_1 + i * cols_1) + k));
				int mat_2_val = (*((mat_2 + k * rows_2) + j));
				*((result_mat + i * cols_2) + j) += mat_1_val * mat_2_val;
			}
		}
	}

	print_matrix(result_mat, rows_1, cols_2);

	free(result_mat);
}

int main() {

	int test_matrix[4][4] = {
		{1, 2, 1, 0},
		{2, 2, 1, 0},
		{0, 0, 1, 2},
	};

	int matrix_a[2][3] = { 1 };
	int matrix_b[4][4] = {
		{1, 1, 1, 1},
		{1, 2, 1, 1},
		{1, 1, 3, 1},
		{1, 1, 1, 4}
	};

	print_matrix(*test_matrix, 3, 4);
	print_matrix(*matrix_b, 4, 4);

	multiply_matrix(
		*test_matrix, 3, 4,
		*matrix_b, 4, 4
		);

	return 0;
}