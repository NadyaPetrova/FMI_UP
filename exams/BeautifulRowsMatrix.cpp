/*User inputs two integers m & n and then memory is allocated for a matrix with m rows and n cols with unsigned integers in it.
Input the elements of the matrix from the user or generate them randomly. Beautiful row in a matrix is a row in which the number 
of all bytes with value 1 in all elements in the row is an even number. Create dynamically allocated array and save the
concatenation of all the beautiful rows of the matrix. The size of the array should be exactly that much as its needed for 
saving the elements. Print the matrix on the screen.
Input:
3 5
3 4 5 1 2
5 3 0 9 0
1 2 4 5 8
Output:
5 3 0 9 0 1 2 4 5 8
*/

#include <iostream>
using namespace std;

void print(unsigned int** matrix, unsigned m, unsigned n);
unsigned int** inputMatrix(unsigned m, unsigned n);
int sumRow(unsigned int** matrix, unsigned row, unsigned n);
int countOnes(int number);
void printRows(unsigned int* result, size_t size);

int main() {
	unsigned m, n;
	cin >> m >> n;

	unsigned int** matrix = inputMatrix(m, n);

	int countRows = 0;
	for (size_t i = 0; i < m; i++) {
		if (sumRow(matrix, i, n) % 2 == 0) {
			countRows++;
		}
	}

	size_t size = n*countRows;
	unsigned int* result = new unsigned int[n*countRows];
	if (!result) {
		cerr << "Memory issue" << endl;
	}

	size_t index = 0;
	for (size_t i = 0; i < m; i++) {
		if (sumRow(matrix, i, n) % 2 == 0) {
			for (size_t j = 0; j < n; j++) {
				result[index++] = matrix[i][j];
			}
		}
	}

	cout << "Beautiful rows: ";
	printRows(result, size);
	cout << endl;

	delete[] result;

	for (size_t i = 0; i < m; i++) {
		delete[] matrix[i];
	}
	delete matrix;

	return 0;
}

void print(unsigned int ** matrix, unsigned m, unsigned n)
{
	for (size_t i = 0; i < m; i++) {
		for (size_t j = 0; j < n; j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

unsigned int ** inputMatrix(unsigned m, unsigned n)
{
	unsigned int** matrix = new unsigned int*[m];
	if (!matrix) {
		return NULL;
	}

	for (size_t i = 0; i < m; i++) {
		matrix[i] = new unsigned int[n];
	}

	for (size_t i = 0; i < m; i++) {
		for (size_t j = 0; j < n; j++) {
			do {
				cin >> matrix[i][j];
			} while (matrix[i][j] < 0);
		}
	}
	return matrix;
}

int sumRow(unsigned int ** matrix, unsigned row, unsigned n)
{
	int sum = 0;
	for (size_t i = 0; i < n; i++) {
		int current = matrix[row][i];
		sum += countOnes(current);
	}
	return sum;
}

int countOnes(int number)
{
	int count = 0;
	while (number > 0) {
		if (number % 2 == 1) {
			count++;
		}
		number /= 2;
	}
	return count;
}

void printRows(unsigned int * result, size_t size)
{
	for (size_t i = 0; i < size; i++) {
		cout << result[i] << " ";
	}
}