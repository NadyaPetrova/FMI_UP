/*The task is to make a simple hangman game.
The game should look like this: 

Guess the word (max 5 mistakes):

[0/5] _ _ _ _ _ _ _  History: 
Choose a letter: a
No such letter!

[1/5] _ _ _ _ _ _ _  History: a
Choose a letter: e
OK

[1/5] _ e _ _ _ _ e  History: a e
Choose a letter: i
OK

[1/5] _ e _ i _ _ e  History: a e i
Choose a letter: v
OK

[1/5] v e _ i _ _ e  History: a e i v
Choose a letter: b
No such letter!

[2/5] v e _ i _ _ e  History: a e i v b
*/

#include <iostream>
#include <time.h>
#include <cstring>
using namespace std;

const unsigned int maxMistakes = 5;
const unsigned int wordsCount = 50;

void startGame();
const char* getWord();
char* createSequence(const char* word);
void printSequence(char* sequence, int mistakes);
void printHistory(char* history);
char toLowerCase(char letter);
const char getLetter();

int main() {
	srand(time(NULL));
	cout << "You are playing hangman. You are guessing one of the 50 U.S. states." << endl;
	while (true) {
		startGame();
		char answer;
		cout << "Do you want to play again?(y/n): ";
		cin >> answer;
		if (answer == 'n') {
			cout << "You left the game!" << endl;
			break;
		}
	}
	return 0;
}

void startGame() {
	const char* word = getWord();

	char* sequence = createSequence(word);
	char* history = new char[maxMistakes*strlen(word)];
	history[0] = '\0';

	int mistakes = 0, guesses = 0;

	cout << "Guess the word (max " << maxMistakes << " mistakes): " << endl;
	while (true) 
	{
		printSequence(sequence, mistakes);
		printHistory(history);

		//in case you make more mistakes than you are allowed to
		if (mistakes == maxMistakes) {
			cout << "Sorry, you lost. The word was " << word << endl;
			break;
		}

		const char letter = getLetter();

		//fill the array with the previous guesses
		history[guesses++] = letter;
		history[guesses] = '\0';

		bool missed = true, //the letter is not from the word
			 guessed = true; //guessed the whole word

		for (int i = 0; i < strlen(word); i++) {
			if (toLowerCase(word[i]) == letter) {
				sequence[i] = letter;
				missed = false; //made a right guess
			}
			if (sequence[i] == '_') {
				guessed = false; //there are still letters left to guess
			}
		}

		if (!missed) {
			cout << "OK" << endl;
		}
		if (missed) {
			cout << "No such letter!"<<endl;
			mistakes++;
		}
		if (guessed) {
			cout << "Good job. You guessed the word " << word << "." << endl;
			break;
		}

		cout << endl;
	}

	delete[] sequence;
	delete[] history;
}

void printSequence(char* sequence, int mistakes) {
	cout << "[" << mistakes << "/" << maxMistakes << "] ";
	for (int i = 0; i < strlen(sequence); i++) {
		cout << sequence[i] << " ";
	}
}

//prints the previous guesses
void printHistory(char* history) {
	cout << "History: ";
	for (int i = 0; i < strlen(history); i++) {
		cout << history[i] << " ";
	}
	cout << endl;
}

char toLowerCase(char letter) {
	if (letter >= 'A' && letter <= 'Z') {
		return letter + ('a' - 'A');
	}
	return letter;	
}

//guess a letter from the word
const char getLetter() {
	char letter;
	cout << "Choose a letter: ";
	cin >> letter;

	return letter;
}

//creates a sequence of underscores with the length of the searched word
char* createSequence(const char* word) {
	unsigned length = strlen(word);
	char* sequence = new char[length + 1];
	for (int i = 0; i < strlen(word); i++) {
		if (word[i] == ' ') {
			sequence[i] = ' '; //in case the string consists of more than one word
		}
		else {
			sequence[i] = '_';
		}
	}
	sequence[length] = '\0';
	return sequence;
}

//function that gets random word from a list
const char* getWord() {
	const char* words[] = {
	  "Alabama", "Alaska" , "Arizona", "Arkansas", "California", "Colorado", "Connecticut", "Delaware", "Florida",
	  "Georgia", "Hawaii", "Idaho", "Illinois", "Indiana", "Iowa", "Kansas", "Kentucky", "Louisiana", "Maine", "Maryland",
	  "Massachusetts", "Michigan", "Minnesota", "Mississippi", "Missouri", "Montana", "Nebraska", "Nevada", "New Hampshire",
	  "New Jersey", "New Mexico", "New York","North Carolina", "North Dakota", "Ohio", "Oklahoma", "Oregon", "Pennsylvania", "Rhode Island",
	  "South Carolina", "South Dakota", "Tennessee", "Texas", "Utah", "Vermont", "Virginia", "Washington","West Virginia", "Wisconsin", "Wyoming"
	};

	int random = rand() % wordsCount;
	return words[random];
}