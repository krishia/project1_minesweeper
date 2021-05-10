#include "minesweeper.h"

void minesweeper(string input, string output)
{
	char arr_board[SIZE][SIZE];//보드생성
	bool arr_touched_board[SIZE][SIZE];//터치한 곳을 표시할 보드생성
	int counter = 0;//터치한 횟수

	for (int row = 0; row < SIZE; ++row) {
		for (int col = 0; col < SIZE; ++col) {
			arr_touched_board[row][col] = false;
		}
	}//arr_touched_board false로 초기화



	bool is_gameover = false;//게임오버 불리언

	ifstream fin_commands;//커맨드 택스트 읽어드릴 ifstream
	fin_commands.open(input);
	ofstream fout_output;//결과를 표시할 ofstream
	fout_output.open(output);

	string first_command_line;
	getline(fin_commands, first_command_line);

	fout_output << "Command: " << first_command_line << endl;
	string board_fileName = first_command_line.substr(5);//선택할 보드이름


	initBoard(arr_board, board_fileName);//위의 arr_board를 선택한 보드와 동일하게 바꾸는 과정

	string temp_command_line;//커맨드라인 원문
	string command_line;//커맨드
	string command_name;



	while (getline(fin_commands, temp_command_line) && !is_gameover) {
		int x, y;//좌표
		fout_output << "Command: " << temp_command_line << endl;
		command_name = temp_command_line.substr(0, 4);
		if (command_name == "disp") {
			for (int row = 0; row < SIZE; ++row) {
				for (int col = 0; col < SIZE; ++col) {
					if (arr_touched_board[row][col] == false) {
						fout_output << '.';
					}
					else {
						fout_output << arr_board[row][col];
					}
				}
				fout_output << endl;
			}
			fout_output << endl;
			break;
		}
		command_line = temp_command_line.substr(6, 3);

		x = (int)command_line.at(0) - 49;


		y = (int)command_line.at(2) - 49;



		initTouched(fout_output, arr_touched_board, x, y, counter);

		touchBoard(fout_output, arr_board, x, y, is_gameover);
		if (is_gameover) {
			break;
		}


	}
	displayBoard(fout_output, arr_board, arr_touched_board, is_gameover, counter);
}
void determinder(char board[][SIZE], int x, int y, int& mines) {
	if (board[x][y] == '*') {
		++mines;
	}
}
void initBoard(char board[][SIZE], string file)
{
	// Implement this
	string board_row;
	ifstream fin;

	fin.open(file);

	for (int row = 0; row < SIZE; ++row) {
		getline(fin, board_row);
		for (int col = 0; col < SIZE; ++col) {
			board[row][col] = board_row.at(col);
		}
	}
}

void displayBoard(ostream& fout, char board[][SIZE], bool touchedBoard[][SIZE], bool gameOver, int counter)
{
	// Implement this
	fout << "Game Over" << endl;
	fout << "~~~~~~~~~" << endl;
	fout << "Final Board" << endl;
	for (int row = 0; row < SIZE; ++row) {
		for (int col = 0; col < SIZE; ++col) {
			if ((touchedBoard[row][col] == false) && (board[row][col] == '*')) {
				board[row][col] = '@';
			}
			fout << board[row][col];
		}
		fout << endl;
	}
	fout << endl;
	fout << "Spaces touched: " << counter;
	fout << endl;
}

void initTouched(ostream& fout, bool touchedBoard[][SIZE], int a, int b, int& counter)
{
	//	fout << "Command: touch " << a << " " << b << endl;
	touchedBoard[a][b] = true;
	++counter;
}

void touchBoard(ostream& fout, char board[][SIZE], int x, int y, bool& gameover)
{
	// Implement this
	if (board[x][y] == '*') {
		gameover = true;
		return;
	}
	else {
		int num_of_mines = 0;
		if (x == 0 && y == 0) {
			determinder(board, x + 1, y, num_of_mines);
			determinder(board, x, y + 1, num_of_mines);
			determinder(board, x + 1, y + 1, num_of_mines);
		}
		else if (x == 0 && y == 7) {
			determinder(board, x + 1, y, num_of_mines);
			determinder(board, x, y - 1, num_of_mines);
			determinder(board, x + 1, y - 1, num_of_mines);
		}
		else if (x == 7 && y == 0) {
			determinder(board, x - 1, y, num_of_mines);
			determinder(board, x, y + 1, num_of_mines);
			determinder(board, x - 1, y + 1, num_of_mines);
		}
		else if (x == 7 && y == 7) {
			determinder(board, x - 1, y, num_of_mines);
			determinder(board, x, y - 1, num_of_mines);
			determinder(board, x - 1, y - 1, num_of_mines);
		}
		else if (x == 0 && (y > 0 && y < 7)) {
			determinder(board, x, y - 1, num_of_mines);
			determinder(board, x + 1, y - 1, num_of_mines);
			determinder(board, x + 1, y, num_of_mines);
			determinder(board, x + 1, y + 1, num_of_mines);
			determinder(board, x, y + 1, num_of_mines);
		}
		else if (x == 7 && (y > 0 && y < 7)) {
			determinder(board, x, y - 1, num_of_mines);
			determinder(board, x - 1, y - 1, num_of_mines);
			determinder(board, x - 1, y, num_of_mines);
			determinder(board, x - 1, y + 1, num_of_mines);
			determinder(board, x, y + 1, num_of_mines);
		}
		else if ((x > 0 && x < 7) && y == 0) {
			determinder(board, x - 1, y, num_of_mines);
			determinder(board, x - 1, y + 1, num_of_mines);
			determinder(board, x, y + 1, num_of_mines);
			determinder(board, x + 1, y + 1, num_of_mines);
			determinder(board, x + 1, y, num_of_mines);
		}
		else if ((x > 0 && x < 7) && y == 7) {
			determinder(board, x - 1, y, num_of_mines);
			determinder(board, x - 1, y - 1, num_of_mines);
			determinder(board, x, y - 1, num_of_mines);
			determinder(board, x + 1, y - 1, num_of_mines);
			determinder(board, x + 1, y, num_of_mines);
		}
		else if ((x > 0 && x < 7) && (y > 0 && y < 7)) {
			determinder(board, x, y - 1, num_of_mines);
			determinder(board, x - 1, y - 1, num_of_mines);
			determinder(board, x - 1, y, num_of_mines);
			determinder(board, x - 1, y + 1, num_of_mines);
			determinder(board, x, y + 1, num_of_mines);
			determinder(board, x + 1, y + 1, num_of_mines);
			determinder(board, x + 1, y, num_of_mines);
			determinder(board, x + 1, y - 1, num_of_mines);
		}
		board[x][y] = num_of_mines + 48;
	}
}

int main() {
	cout << "enter the command list's file name: ";
	string input_command_file_name;
	cin >> input_command_file_name;
	cin.ignore();
	cout << "enter the output file name: ";
	string output_file_name;
	cin >> output_file_name;
	cin.ignore();
	minesweeper(input_command_file_name, output_file_name);

	return 0;
}