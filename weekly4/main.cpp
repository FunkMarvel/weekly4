// Weekly 4, week 38 & 39, Anders P. Åsbø.
#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <random>
#include <algorithm>

// common commands:
using std::cout; using std::endl;
using std::cin; using std::vector;
using std::string; using std::stoi;

struct Person {
	// Struct for Person used in task 3. Holds name and phone number.
	string name{};
	unsigned int phone_number{};
};

struct Dice {
	// Struct for dice used in dice task. Holds value of roll.
	unsigned int value{1};

	Dice() { roll(); }  // default constructor runs roll-method.

	void roll() {
		// roll method generates random integer from interval [1, 6]
		// and asignes value to current dice object.
		std::random_device rd{};
		std::mt19937_64 gen(rd());
		std::uniform_int_distribution<int> face_dist(1, 6);
		
		value = face_dist(gen);
	}

	// overloads of 'equal to' operator:
	inline bool operator ==(Dice some_dice) {
		// comparing two dice returns true if their values are equal,
		// and false otherwise.
		return value == some_dice.value;
	}

	inline bool operator ==(int some_value) {
		// comparing dice to int returns true if dice value equals value of int,
		// and false otherwise.
		return value == some_value;
	}
	friend bool operator ==(int some_value, Dice some_dice) {
		// comparing dice to int returns true if dice value equals value of int,
		// and false otherwise.
		return some_dice.value == some_value;
	}

	friend std::ostream& operator <<(std::ostream &os, Dice some_dice) {
		// Overload of stream-insertion operator. Passing Dice object to stream
		// results in value of dice being inserted in stream.
		os << some_dice.value;
		return os;
	}
};

// declerations of functions:
void task1();
void task2();
void checkBounds(vector<vector<char>>&, vector<int>&);
void displayBoard(vector<vector<char>>&);
void populateLevels(vector<vector<vector<char>>>&);
void task3();
void diceTask();
vector<Dice> roll5dice();
unsigned int countFaces(vector<Dice>&, unsigned int);
vector<vector<Dice>> findPair(vector<Dice>&);
void clearCin();

int main() {
	// main program function contains loop for task selection.
	while (true) {
		char answer{};
		system("cls");

		// printing options:
		for (int i = 1; i < 5; i++) {
			if (i != 4) { cout << " Task " << i << ". " << endl; }
			else { cout << " Dice task." << endl; }
		}
		// taking answer:
		cout << " Type number of task, 'd' for dice task, or 'q' to quit: ";
		cin >> answer;

		// switching to selected:
		switch (tolower(answer)) {
		case '1':
			task1();
			break;
		case '2':
			task2();
			break;
		case '3':
			task3();
			break;
		case '4': case 'd':
			diceTask();
			break;
		case 'q':
			return 0;
		default:
			break;
		}
		system("pause");
	}
	return 1;
}

void task1() {
	// calculator function.
	// Takes in two double float numbers and performs the selected arithmetic operation.
	double a{};
	double b{};
	double result{};
	int idx{};
	vector<vector<string>> operations{  // vector with operations
		{"Add", "Subtract", "Multiply", "Divide"},
		{"+","-","*","/"}
	};
	char operation{};
	bool valid_selec{ false };

	// asks for first number:
	cout << " Input first number: ";
	cin >> a; cout << endl;
	system("cls");

	// asks for second number:
	cout << " Input second number: ";
	cin >> b; cout << endl;
	system("cls");


	while (!valid_selec) {  // loops until valid selection is made.

		// prints options for operations
		for (int i = 0; i < operations[0].size(); i++) {
			cout << " " << i + 1 << ". " << operations[0][i] << endl;
		}
		cout << " Choose an operation: ";
		cin >> operation; cout << endl;  // takes in selection.
		system("cls");

		// switches to selected operation and performs calculation:
		switch (tolower(operation)) {
		case '1': case 'a':
			result = a + b;
			valid_selec = true;
			idx = 0;
			break;
		case '2': case 's':
			result = a - b;
			valid_selec = true;
			idx = 1;
			break;
		case '3': case 'm':
			result = a * b;
			valid_selec = true;
			idx = 2;
			break;
		case '4': case 'd':
			result = a / b;
			valid_selec = true;
			idx = 3;
		default:
			break;
		}
		system("cls");
	}

	// prints result:
	cout << a << " " << operations[1][idx] << " " << b
		<< " = " << result << endl;
	system("pause");
}

void task2() {
	// Function generating a 10x10 grid with spaces that the player can navigate.
	int n{ 10 };  // dimension of each level
	char free_space{ '.' };  // the character representing a free space on the board
	int current_level{};  // the current level of the player

	// vector containing 4 levels:
	vector<vector<vector<char>>> levels(4, vector<vector<char>>(n, vector<char>(n, free_space)));
	populateLevels(levels);  // populating levels with '\\', '/' and 'G'

	vector<vector<char>> board(n, vector<char>(n, free_space));  // creating game board
	copy(levels[current_level].begin(), levels[current_level].end(), board.begin());  // copying starting level to game board

	board[0][0] = '@';  // setting player character to upper left corner
	displayBoard(board);  // displaying current game board

	vector<int> position(2, 0);  // vector tracking position (x, y).

	while (true) {
		board[position[1]][position[0]] = free_space;  // clearing old tile on game board.
		char input{};  // geting input
		input = _getch();
		system("cls");

		// switch to adjust position according to key press
		switch (tolower(input)) {
		case 'w':
			position[1]--;
			break;
		case 'a':
			position[0]--;
			break;
		case 's':
			position[1]++;
			break;
		case 'd':
			position[0]++;
			break;
		}
		checkBounds(board, position);  // loops player character around board if position is out of bounds.

		switch (board[position[1]][position[0]]) { // checks if new position is special tile
		case 'G':  // exits program on 'G'
			exit(0);
			break;
		case '/':  // moves up one level on '/'
			current_level++;
			copy(levels[current_level].begin(), levels[current_level].end(), board.begin());
			break;
		case '\\':  // moves down one level on '\\'
			current_level--;
			copy(levels[current_level].begin(), levels[current_level].end(), board.begin());
			break;
		default:
			break;
		}

		board[position[1]][position[0]] = '@';  // sets player character to new position
		displayBoard(board);
	}
}

void checkBounds(vector<vector<char>> &board, vector<int> &position) {
	// Function checking if player is out of bounds, and moves them to other side of board if they are:
	if (position[0] == -1) position[0] = board.size() - 1;
	else if (position[0] == board.size()) position[0] = 0;
	if (position[1] == -1) position[1] = board.size() - 1;
	else if (position[1] == board.size()) position[1] = 0;
}

void displayBoard(vector<vector<char>>& board) {
	// function displaying game board as 10x10 grid:
	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[0].size(); j++) {
			cout << " " << board[i][j];
		}
		cout << endl;
	}
}

void populateLevels(vector<vector<vector<char>>>& levels) {
	// Function that generates each level.
	std::random_device rd{};
	std::mt19937_64 gen(rd());
	std::uniform_real_distribution<double> RNG(0, 1);

	// bools for keeping track of special tiles:
	bool exit_placed{ false };
	bool stair_down_placed{ false };
	bool stair_up_placed{ false };
	double wheight{ 0.95 };
	double draw{};

	// looping through number of levels
	for (int i = 0; i < levels.size(); i++) {
		stair_down_placed = false;
		stair_up_placed = false;

		// looping through each tile on a level
		for (int j = 1; j < levels[0].size() - 1; j++) {
			for (int k = 1; k < levels[0][0].size() - 1; k++) {
				draw = RNG(gen);  // draws random number
				if (!exit_placed && draw > 0.99) {  // places exit tile semi randomly
					levels[i][j][k] = 'G';
					exit_placed = true;
				}
				// places stair down semi-randomly:
				if (levels[i][j][k] != 'G' && !stair_down_placed && i != levels.size() - 1 && draw < 1 - wheight) {
					levels[i][j][k] = '/';
					stair_down_placed = true;
				}
				// places stair up semi-randomly:
				if (levels[i][j][k] != 'G' && !stair_up_placed && i != 0 && draw >= wheight) {
					levels[i][j][k] = '\\';
					stair_up_placed = true;
				}
				
				// breaks if all special tiles have been placed:
				if (exit_placed && stair_down_placed && stair_up_placed) break;
			}

			// breaks if all special tiles have been placed:
			if (exit_placed && stair_down_placed && stair_up_placed) break;
		}
		// places stair up and down if not placed randomly:
		if (!stair_down_placed && i != levels.size() - 1) levels[i][1][1] = '/';
		if (!stair_up_placed && i != 0) levels[i][levels[0].size() - 2][levels[0][0].size() - 2] = '\\';
	}

	// places exit tile if not placed randomly:
	if (!exit_placed) levels[levels.size() - 1][0][0] = 'G';
}

void task3() {
	// function for task 3
	int i{};  // number of people added
	char add_more{ 'y' };  // answer to add more question
	vector<Person> people{};  // vector of Person objects

	while (i < 10) {  // loops until 10 people have been added, or user stops adding people.

		// asks if user wants to add a person:
		system("cls");
		cout << " Add a person? y/n: ";
		cin >> add_more;

		if (tolower(add_more) == 'n') { break; }  // breaks if user said no
		else if (tolower(add_more) == 'y') {  // ads person if user said yes
			Person temp_person{};  // temp object

			// gets name from user and adds to temp object:
			cout << " Name: ";
			clearCin();
			getline(cin, temp_person.name);

			// gets phone number from user and adds to temp object:
			cout << " Phone number: ";
			cin >> temp_person.phone_number;

			// ads temp person to people vector:
			people.push_back(temp_person);
			i++; // counts up by one
		}
	}

	// prints table of people:
	cout << " Name:\t\tPhone number: " << endl;
	for (int i = 0; i < people.size(); i++) {
		cout << " " << people[i].name << "\t " << people[i].phone_number << endl;
	}
}

void diceTask() {
	// function for dice task.
	vector<Dice> held_rolls{};  // vector for holding rolls.

	while (true) {  // loops until user quits
		vector<Dice> rolls = roll5dice();  // vector for current rolls
		vector<char> selections{ '1','2','3','4','5' };
		char roll_to_hold{};  // user provided roll to hold

		// prints current rolls
		for (int i = 0; i < rolls.size(); i++) {
			cout << " Dice nr. " << i+1 << ": " << rolls[i] << endl;
		}
		while (true) {  // loops until user quits
			cout << " Type the number of the dice you wish to hold, type 'c' to roll again, or type 'H' to stop: ";
			cin >> roll_to_hold;

			// if selected roll is a possible selection, corresponding dice is stored in held_dice vector:
			if (std::binary_search(selections.begin(), selections.end(), roll_to_hold)) {
				held_rolls.push_back(rolls[roll_to_hold - '0' - 1]);  // converting numeric char to integer by subtracting ascii value of '0'
				cout << " Dice nr. " << roll_to_hold << " has been saved." << endl;
			}
			// breaks loop if user continues, quits, or has held 5 dice:
			else if (tolower(roll_to_hold) == 'c' || roll_to_hold == 'H' || rolls.size() - held_rolls.size() == 0) { break; }
		}
		system("cls");
		if (roll_to_hold == 'H' || rolls.size() - held_rolls.size() == 0) break;  // stops rolling dice if user quits or has held 5 dice.
	}

	// prints number of 6es in rolls:
	cout << " There are " << countFaces(held_rolls, 6) << " number of 6s among the rolls you held" << endl;

	vector<vector<Dice>> pairs = findPair(held_rolls);  // finding vector of pairs among held rolls.
	for (int i = 0; i < pairs.size(); i++) {  // printing pairs:
		cout << " Pair nr. " << i + 1 << " is " << pairs[i][0] << " and " << pairs[i][1] << endl;
	}
}

vector<Dice> roll5dice() {
	// function that rolls 5 dice.
	vector<Dice> rolls{}; // return vector.
	for (int i = 0; i < 5; i++) {
		rolls.push_back(Dice());  // adds 5 dice to return vector, value of dice is rolled on constructor call.
	}

	return rolls;  // returns vector of 5 rolled dice.
}

unsigned int countFaces(vector<Dice> &held_rolls, unsigned int face) {
	// Function counting number of a given face among held rolls.
	unsigned int number_of_faces{};
	
	for (int i = 0; i < held_rolls.size(); i++) {
		if (held_rolls[i] == face) number_of_faces++;  // counts number of values equal to face.
	}

	return number_of_faces;  // returns counted number.
}

vector<vector<Dice>> findPair(vector<Dice> &held_rolls) {
	// Function finding pairs of equal values in vector of dice.

	// creating copy of input vector:
	vector<Dice> rolls(held_rolls.size(), Dice());
	std::copy(held_rolls.begin(), held_rolls.end(), rolls.begin());

	// creating output vector:
	vector<vector<Dice>> pairs{};

	for (int i = 0; i < rolls.size(); i++) {  // iterating through rolls.
		for (int j = i + 1; j < rolls.size(); j ++) {  // comparing held rolls to find pairs
			if (rolls[i] == rolls[j]) {
				// stored pairs in return vector:
				vector<Dice> temp{ rolls[i], rolls[j] };

				// removes dice that has been matched to avoid counting dice nr. j in more than one pair:
				rolls.erase(rolls.begin() + j);
				pairs.push_back(temp);
				break;  // breaking on found pair to avoid counting dice nr. i in more than one pair.
			}
		}
	}

	return pairs;  // returns vector of dice pairs.
}

void clearCin() {
	// Function that clears cin buffer.
	// Courtesy of Johannes Skjeltorp-Borgaas.

	std::cin.clear();
	std::cin.ignore(32767, '\n');
}