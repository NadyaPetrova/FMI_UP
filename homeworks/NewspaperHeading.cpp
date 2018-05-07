/*The task is to generate random heading for scandalous newspaper. There are categories of 
excamations, objects/subjects and actions. The list of subjects and objects is the same,
but they must be placed in the right place in the sentence. Heading should be created from 
a word from every category in the right place and between 3 and 10 exclamation marks. 
Dynamic array of characters is allocated for the heading with the exact size for it. 
The words from the heading are copied to the array
and the array is printed on the screen.   */

#include <iostream>
#include <time.h>
#include <cstring>
using namespace std;

unsigned getHeadings();
const char* getExclamation();
const char* getAction();
int* createArray(int* arr);
int numberOfExclamationMarks();
unsigned getRandom(unsigned words);
char* toLowerCase(char* dest, char* str);

const unsigned numberOfNouns = 5;

int main() {
	srand(time(NULL));
	int headings = getHeadings();

	//create an array to check if the word is a subject or an object
	int* arr = new int[numberOfNouns];
	int* check = createArray(arr);
	char* subject, *heading;

	while (headings > 0) {
		//get exclamation
		const char* exclamation = getExclamation();
		int exclLen = strlen(exclamation);

		//get number of exclamation marks
		int exclMarks = numberOfExclamationMarks();

		//array of objects and subjects
		char* nouns[] = { "Turnip ","Grandma ","Mayor ","Bagger ","Storage " };
		int r;

		//get object; it's valid if the value in check array is 1 or 2
		char* object;
		do {
			r = getRandom(numberOfNouns);
			object = nouns[r];
		} while (check[r] == 0);
		int objectLen = strlen(object);

		//get subject; it's valid if the value in check array is 0 or 2
		do {
			r = getRandom(numberOfNouns);
			subject = new char[strlen(nouns[r]) + 1];
			subject = toLowerCase(subject, nouns[r]);
		} while (check[r] == 1);
		int subjectLen = strlen(subject);

		//get action
		const char* action = getAction();
		int actionLen = strlen(action);

		//allocate enough memory for all words
		heading = new char[exclLen + exclMarks + objectLen + actionLen + subjectLen + 1];

		strcpy(heading, exclamation);

		while (exclMarks > 0) {
			strcat(heading, "!");
			exclMarks--;
		}

		strcat(heading, object);
		strcat(heading, action);
		strcat(heading, subject);

		cout << heading << endl;
		headings--;
	}

	//delete the allocated memory
	delete[] heading;
	delete[] subject;
	delete[] arr;

	return 0;
}

unsigned getHeadings() {
	int n;
	do {
		cout << "Enter number of headings: ";
		cin >> n;
	} while (n < 0);

	return n;
}

const char* getExclamation() {
	const char* exclamations[] = { "Shocking news ","You won't belive it ","Scandal ","Amazing " };
	unsigned numberOfWords = 4;

	int r = getRandom(numberOfWords);
	return exclamations[r];
}

const char* getAction() {
	const char* actions[] = { "crashed ","took ","winked at ","betrayed ","stole ","chased " };
	unsigned numberOfWords = 6;

	int r = getRandom(numberOfWords);
	return actions[r];
}

int* createArray(int* arr)
{
	for (int i = 0; i < numberOfNouns; i++) {
		if (i == numberOfNouns - 1) {
			arr[i] = 0;
		}
		else {
			arr[i] = 2;
		}
	}
	return arr;
}

int numberOfExclamationMarks() {
	int r = rand() % 8 + 3;
	return r;
}

unsigned getRandom(unsigned words) {
	int r = rand() % words;
	return r;
}

char* toLowerCase(char* dest, char* c) {
	for (int i = 0; i < strlen(c); i++) {
		if (c[i] > 'A'&&c[i] < 'Z') {
			dest[i] = c[i] + ('a' - 'A');
		}
		else {
			dest[i] = c[i];
		}
		dest[i + 1] = '\0';
	}
	return dest;
}