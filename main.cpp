#include <iostream>
#include <vector>
#include <iterator>
#include <map>

using namespace std;

struct Matrix {
	int rows, cols;
	std::string name;
	std::vector<std::vector<int>> data;

	// Constructor to initialize matrix with a name and list of lists (2D vector)
	Matrix(const std::string& matrix_name, const std::vector<std::vector<int>>& input_data)
		: name(matrix_name), rows(input_data.size()), cols(input_data.empty() ? 0 : input_data[0].size()), data(input_data) {

		// Sanity check
		for (const auto& row : input_data) {
			if (row.size() != cols) {
				throw std::invalid_argument("Invalid input argument, all rows must have the same number of columns");
			}
		}
	}

	// Accessor function to get a value
	int get(int r, int c) const {
		if (r < 0 || r >= rows || c < 0 || c >= cols) {
			throw std::out_of_range("Matrix indices are out of range");
		}
		return data[r][c];
	}

	// Mutator function to set a value
	void set(int r, int c, int value) {
		if (r < 0 || r >= rows || c < 0 || c >= cols) {
			throw std::out_of_range("Matrix indices are out of range");
		}
		data[r][c] = value;
	}

	void print() {
		std::cout << "Printing Matrix: " << name << std::endl;
		for (int row = 0; row < rows; row++) {
			for (int col = 0; col < cols; col++) {
				std::cout << data[row][col] << " ";
			}
			std::cout << std::endl;
		}
		cout << std::endl;
	}

	// Matrix multiplication function
	Matrix multiply(const Matrix& other) const {

		std::cout << "Multiplying " << name << " with " << other.name << std::endl;

		// is multiplication is possible?
		if (cols != other.rows) {
			throw std::invalid_argument("Matrix dimensions do not match for multiplication.");
		}

		// Create a new matrix
		std::vector<std::vector<int>> result_data(rows, std::vector<int>(other.cols, 0));

		// Perform matrix multiplication
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < other.cols; ++j) {
				for (int k = 0; k < cols; ++k) {
					result_data[i][j] += get(i, k) * other.get(k, j);
				}
			}
		}

		// Return a new matrix with the result
		return Matrix("Result of " + name + " * " + other.name, result_data);
	}
};

int main() {

	Matrix initial_matrix = Matrix(
		"Initial Matrix",
		{
			{1, 2, 1, 0},
			{2, 2, 1, 0},
			{0, 0, 1, 2},
		}
	);

	Matrix invalid_matrix = Matrix(
		"Invalid Matrix",
		{
			{ 1 }
		}
	);

	Matrix valid_matrix = Matrix(
		"Valid Matrix",
		{
			{1, 1, 1, 1},
			{1, 2, 1, 1},
			{1, 1, 3, 1},
			{1, 1, 1, 4}
		}
	);

	try {
		Matrix invalid_result = initial_matrix.multiply(invalid_matrix);
	}
	catch (const std::invalid_argument& e) {
		std::cout << e.what() << std::endl;
	}

	Matrix valid_result = initial_matrix.multiply(valid_matrix);
	valid_result.print();

	return 0;
}