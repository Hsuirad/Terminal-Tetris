#include <cstdlib>
#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

void displayBoard(char board[11][11]);
void moveBlock(string direction, char board[11][11], int &x, int &y);

int main(){
	char board[11][11] = {
		{'_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_'},
		{'_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_'},
		{'_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_'},
		{'_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_'},
		{'_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_'},
		{'_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_'},
		{'_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_'},
		{'_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_'},
		{'_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_'},
		{'_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_'},
		{'_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_'}
	};

	int blockx = 5; //really 6 but indexes start at 0
	int blocky = 1;
	int x = 0;

	string answer, quityn;

	bool wk, ak, dk, sk, playing;
	playing = true;
	wk = ak = dk = sk = false;
	system("color fc");
	cout << "Welcome to Terminal Tetris! \nWould you like to start a game (y/n)?\n";
	cin >> answer;
	if (!(answer == "y" || answer == "Y")) {
		return 0;
	}
	cout << "The game has started, press ESC at anytime to quit\n";
	Sleep(500);
	displayBoard(board);
	
	while(playing){
		x++;
		if(x % 100000 == 0){
			if (blocky != 10 && (board[blocky + 1][blockx] != '#' && board[blocky + 1][blockx - 1] != '#')) {
				board[blocky][blockx] = '_';
				board[blocky - 1][blockx] = '_';
				board[blocky][blockx - 1] = '_';
				board[blocky - 1][blockx - 1] = '_';
			}
			else {
				blocky = 1;
			}
			blocky += 1;
			board[blocky][blockx] = '#';
			board[blocky][blockx - 1] = '#';
			board[blocky - 1][blockx] = '#';
			board[blocky - 1][blockx - 1] = '#';
			displayBoard(board);
		}
		else if (GetKeyState(VK_LEFT) & 0x8000) {
			moveBlock("left", board, blockx, blocky);
		}
		else if (GetKeyState(VK_RIGHT) & 0x8000) {
			moveBlock("right", board, blockx, blocky);
		}
		else if (GetKeyState(VK_DOWN) & 0x8000) {
			moveBlock("down", board, blockx, blocky);
		}
		else if (GetKeyState(VK_ESCAPE) & 0x8000) {
			cout << "Are you sure you want to quit the game (y/n)?\n";
			cin >> quityn;
			if (quityn == "y") {
				playing = false;
				system("cls");
				cout << "Goodbye!\n";
				Sleep(2000);
			}
		}
	}

	return 0;
}

void displayBoard(char board[11][11]) {
	system("cls");
	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 11; j++) {
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
}

void moveBlock(string direction, char board[11][11], int &x, int &y) {
	if (direction == "down") {
		if (y != 10 && (board[y + 1][x] != '#' && board[y + 1][x - 1] != '#')) {
			board[y][x] = '_';
			board[y][x - 1] = '_';
			board[y - 1][x] = '_';
			board[y - 1][x - 1] = '_';
		}
		else {
			y = 1;
		}
		y += 1;
		board[y][x] = '#';
		board[y - 1][x] = '#';
		board[y][x - 1] = '#';
		board[y - 1][x - 1] = '#';
		displayBoard(board);
		Sleep(200);
	}
	else if (direction == "right") {
		board[y][x] = '_';
		board[y - 1][x] = '_';
		board[y][x - 1] = '_';
		board[y - 1][x - 1] = '_';
		x += 1;
		board[y][x] = '#';
		board[y - 1][x] = '#';
		board[y][x - 1] = '#';
		board[y - 1][x - 1] = '#';
		displayBoard(board);
		Sleep(250);
	}
	else if (direction == "left") {
		board[y][x] = '_';
		board[y - 1][x] = '_';
		board[y][x - 1] = '_';
		board[y - 1][x - 1] = '_';
		x -= 1;
		board[y][x] = '#';
		board[y - 1][x] = '#';
		board[y][x - 1] = '#';
		board[y - 1][x - 1] = '#';
		displayBoard(board);
		Sleep(250);
	}
}
