#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <random>

using std::cout; using std::endl;
using std::cin; using std::vector;
using std::string; using std::stoi;

void task1();
void task2();
void checkBounds(vector<vector<char>>&, vector<int>&);
void displayBoard(vector<vector<char>>&);
void populateLevels(vector<vector<vector<char>>>&);
void task3();
void diceTask();
void clearCin();

struct Person
{
	string name{};
	unsigned int phone_number{};
};

int main() {
	/*task1();
	task2();*/
	task3();
	return 0;
}

void task1() {
	double a{};
	double b{};
	double result{};
	int idx{};
	vector<vector<string>> operations{
		{"Add", "Subtract", "Multiply", "Divide"},
		{"+","-","*","/"}
	};
	char operation{};
	bool valid_selec{ false };

	cout << " Input first number: ";
	cin >> a; cout << endl;
	system("cls");

	cout << " Input second number: ";
	cin >> b; cout << endl;
	system("cls");


	while (!valid_selec)
	{
		for (int i = 0; i < operations[0].size(); i++)
		{
			cout << " " << i + 1 << ". " << operations[0][i] << endl;
		}
		cout << " Choose an operation: ";
		cin >> operation; cout << endl;
		system("cls");

		switch (tolower(operation))
		{
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
	
	cout << a << " " << operations[1][idx] << " " << b
		<< " = " << result << endl;
	system("pause");
}

void task2()
{
	int n{ 10 };
	char free_space{ '.' };
	int current_level{};

	vector<vector<vector<char>>> levels(4, vector<vector<char>> (n, vector<char>(n, free_space)));
	populateLevels(levels);
	
	vector<vector<char>> board(n, vector<char> (n, free_space));
	copy(levels[current_level].begin(), levels[current_level].end(), board.begin());
	
	board[0][0] = '@';
	displayBoard(board);

	vector<int> position(2, 0);

	while (true)
	{
		vector<int> old_pos = position;
		board[position[1]][position[0]] = free_space;
		char input{};
		input = _getch();
		system("cls");

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
		checkBounds(board, position);

		switch (board[position[1]][position[0]])
		{
		case 'G':
			exit(0);
			break;
		case '/':
			current_level++;
			copy(levels[current_level].begin(), levels[current_level].end(), board.begin());
			break;
		case '\\':
			current_level--;
			copy(levels[current_level].begin(), levels[current_level].end(), board.begin());
			break;
		default:
			break;
		}

		board[position[1]][position[0]] = '@';
		displayBoard(board);
	}
}

void checkBounds(vector<vector<char>> &board, vector<int> &position) {
	if (position[0] == -1) position[0] = board.size() - 1;
	else if (position[0] == board.size()) position[0] = 0;
	if (position[1] == -1) position[1] = board.size() - 1;
	else if (position[1] == board.size()) position[1] = 0;
}

void displayBoard(vector<vector<char>> &board)
{
	for (int i = 0; i < board.size(); i++)
	{
		for (int j = 0; j < board[0].size(); j++)
		{
			cout << " " << board[i][j];
		}
		cout << endl;
	}
}

void populateLevels(vector<vector<vector<char>>> &levels) {
	std::random_device rd{};
	std::mt19937_64 gen(rd());
	std::uniform_real_distribution<double> RNG(0, 1);

	bool exit_placed{ false };
	bool stair_down_placed{ false };
	bool stair_up_placed{ false };
	double wheight{ 0.95 };
	double draw{};

	for (int i = 0; i < levels.size(); i++)
	{
		stair_down_placed = false;
		stair_up_placed = false;

		for (int j = 1; j < levels[0].size() - 1; j++)
		{
			for (int k = 1; k < levels[0][0].size() - 1; k++)
			{
				draw = RNG(gen);
				if (!exit_placed && draw > 0.99)
				{
					levels[i][j][k] = 'G';
					exit_placed = true;
				}
				if (levels[i][j][k] != 'G' && !stair_down_placed && i != levels.size()-1 && draw < 1-wheight)
				{
					levels[i][j][k] = '/';
					stair_down_placed = true;
				}
				if (levels[i][j][k] != 'G' && !stair_up_placed && i != 0 && draw >= wheight)
				{
					levels[i][j][k] = '\\';
					stair_up_placed = true;
				}

				if (exit_placed && stair_down_placed && stair_up_placed) break;
			}

			if (exit_placed && stair_down_placed && stair_up_placed) break;
		}
		if (!stair_down_placed && i != levels.size() - 1) levels[i][1][1] = '/';
		if (!stair_up_placed && i != 0) levels[i][levels[0].size() - 2][levels[0][0].size() - 2] = '\\';
	}

	if (!exit_placed) levels[levels.size()-1][0][0] = 'G';
}

void task3()
{
	int i{};
	char add_more{ 'y' };
	vector<Person> people{};

	while (i < 10) {
		
		cout << " Add a person? y/n: ";
		cin >> add_more;
		if (tolower(add_more) == 'n') break;

		Person temp_person{};
		
		cout << " Name: ";
		clearCin();
		getline(cin, temp_person.name);

		cout << " Phone number: ";
		cin >> temp_person.phone_number;
		
		people.push_back(temp_person);
		i++;
	}

	for (int i = 0; i < people.size(); i++)
	{
		cout << " Name: " << people[i].name << " Phone number: " << people[i].phone_number << endl;
	}
}

void diceTask()
{
}

void clearCin()
{
	// Function that clears cin buffer.
	// Courtesy of Johannes Skjeltorp-Borgaas.

	std::cin.clear();
	std::cin.ignore(32767, '\n');
}