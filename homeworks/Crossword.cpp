/*The task is to check whether a crossword contains only of words in a specified dictionary. 
You read a number from the standart input and then input this many words - your dictionary. 
Then you save them in an array of characters. The words contain only small latin letters and are
between 2 and 40 symbols. Then you input 2 numbers - the rows and columns of your crossword - both 
less than 100. Lastly you input rows*cols symbols - letters or stars. In the crossword every 
sequence of 2 or more letters in a row or a column that starts in the beginning of it or after a star
is a word and should be checked whether it is a part of the dictionary. If all words are from the
dictionary -> print true on the screen, else print false. 
Example: 
Input:
13
apple tomato google program array recursion math algebra
ant pig dog cat leg 
6 7
a*g*a**
program
p*o*r*a
leg*ant
e*l*y*h
**e****
Output:
true
*/

#include <iostream>
#include <cstring>
using namespace std;

unsigned readNumber();
char** createMatrix(unsigned words);
unsigned readRowsCols();
char** createCrossword(unsigned rows, unsigned cols);
bool checkRows(char** arr, char** crossword, char* word, unsigned rows, unsigned cols, unsigned words);
bool checkCols(char** arr, char** crossword, char* word, unsigned rows, unsigned cols, unsigned words);
char* allocateMemory(char* arr, unsigned rowsCols);
void deleteMatrix(char** matrix, unsigned size);
bool isValid(char* str);

const int Ã¿X_LENGTH = 40;
const int MIN_LENGTH = 2;
const int MAX_ROWS_COLS = 100;

int main() {

	unsigned words = readNumber(); //how many words will be inputted
	char** arr = createMatrix(words); //create a matrix with the inputted words
	unsigned rows = readRowsCols(); //how many rows has the crossword
	unsigned cols = readRowsCols(); //how many cols has the crossword
	char** crossword = createCrossword(rows, cols); //create the crossword

	char* wordRows = '\0';
	wordRows=allocateMemory(wordRows, cols);
	char* wordCols = '\0';
	wordCols=allocateMemory(wordCols, rows);

	if (checkRows(arr, crossword, wordRows, rows, cols, words) && checkCols(arr, crossword, wordCols, rows, cols, words)) {
		cout << "true" << endl;
	}
	else {
		cout << "false" << endl;
	}

	//clear the dynamically allocated memory
	deleteMatrix(arr, words);
	deleteMatrix(crossword, rows);
	delete[] wordRows;
	delete[] wordCols;

	return 0;
}

unsigned readNumber() {
	unsigned words;
	do {
		cout << "How many words in the dictionary: ";
		cin >> words;
	} while (words < 0);

	return words;
}

char ** createMatrix(unsigned words) {
	char** arr = new(nothrow) char*[words + 1];
	if (!arr) {
		cerr << "Not enough memory!" << endl;
		return NULL;
	}

	for (int i = 0; i < words; i++) {
		arr[i] = new char[Ã¿X_LENGTH + 1];
		//validate the input
		do {
			cin >> arr[i];
		} while (strlen(arr[i]) > Ã¿X_LENGTH || strlen(arr[i]) < MIN_LENGTH || !isValid(arr[i]));
	}
	return arr;
}

unsigned readRowsCols() {
	unsigned n;
	do {
		cin >> n;
	} while (n >= MAX_ROWS_COLS);

	return n;
}

char ** createCrossword(unsigned rows, unsigned cols) {
	//create the crossword
	char** crossword = new(nothrow) char*[rows + 1]; //allocate enough memory
	if (!crossword) {
		cerr << "Not enough memory!" << endl;
		return NULL;
	}

	for (int i = 0; i < rows; i++) {
		crossword[i] = new char[cols];
	}
	//and input the symbols in it 
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cin >> crossword[i][j];
		}
	}
	return crossword;
}

bool checkRows(char** arr, char** crossword, char* word, unsigned rows, unsigned cols, unsigned words) {
	
	*word = '\0';
	int counter = 0,	   //count the letters before a '*' or the end of the row
		countWords = 0,   //count the valid words(with length >= 2)
		countEqual = 0;  //count the equal words(from the crossword and the dictionary)

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if ((crossword[i][j] == '*' || (j == cols - 1 && crossword[i][j - 1] == '*'))) {
				counter = 0;
				*word = '\0';
				continue;
			}
			else {
				strncat(word, &crossword[i][j], 1);
				counter++;
			}
			if ((counter >= 2 && (j == cols - 1 || crossword[i][j + 1] == '*'))) {
				countWords++;
				for (int i = 0; i < words; i++) {
					if (strcmp(word, arr[i]) == 0) {
						countEqual++;
						break;
					}
				}
				counter = 0;
				*word = '\0';
			}
		}
	}
	return (countWords >= 1 && countWords == countEqual) ? true : false;
}

bool checkCols(char ** arr, char ** crossword, char * word, unsigned rows, unsigned cols, unsigned words)
{
	*word = '\0';
	int counter = 0,  //count the letters before a '*' or the end of the col
		countWords = 0,   //count the valid words(with length >= 2)
		countEqual = 0;  //count the equal words(from the crossword and the dictionary)

	for (int j = 0; j < cols; j++) {
		for (int i = 0; i < rows; i++) {
			if ((crossword[i][j] == '*' || (i == rows - 1 && crossword[i - 1][j] == '*'))) {
				counter = 0;
				*word = '\0';
				continue;
			}
			else {
				strncat(word, &crossword[i][j], 1);
				counter++;
			}
			if ((counter >= 2 && (i == rows - 1 || crossword[i + 1][j] == '*'))) {
				countWords++;
				for (int i = 0; i < words; i++) {
					if (strcmp(word, arr[i]) == 0) {
						countEqual++;
						break;
					}
				}
				counter = 0;
				*word = '\0';
			}
		}
	}
	return (countWords >= 1 && countWords == countEqual) ? true : false;
}

char * allocateMemory(char * arr, unsigned rowsCols) {
	char* word = new(nothrow) char[rowsCols + 1];
	if (!word) {
		cerr << "Not enough memory!" << endl;
		return false;
	}	
	return word;
}

void deleteMatrix(char ** matrix, unsigned size)
{
	for (int i = 0; i < size; i++)
		delete[] matrix[i];
	delete[] matrix;
}

bool isValid(char * str)
{
	for (int i = 0; i < strlen(str); i++) {
		if (!(str[i] >= 'a'&&str[i] <= 'z')) {
			return false;
		}
	}
	return true;
}