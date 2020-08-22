#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "minesweeper.h"

Minesweeper::Minesweeper(int length, int width): length_(length), width_(width) {
	srand(time(0));
	boardInit(length);
	visit = vector<vector<int>> (length_+2, vector<int>(width_+2));		
}

Minesweeper::Minesweeper(int length, int width, int minesNum): length_(length), width_(width) {
	srand(time(0));
	boardInit(minesNum);
	visit = vector<vector<int>> (length_+2, vector<int>(width_+2));		
}

void Minesweeper::boardInit(int minesNum) {
	board = vector<vector<char>>(length_+2, vector<char>(width_+2, 'E'));		
    
    for(int i = 1; i < length_ + 1; i++) {
        board[0][i] = i + '0';
        board[length_+1][i] = i + '0';
    }
    for(int i = 1; i < width_ + 1; i++) {
        board[i][0] = i + '0';
        board[i][width_+1] = i + '0';
     }
    board[0][0] = board[0][width_+1] = board[length_+1][0] = board[length_+1][width_+1] = '*';
	while(minesNum-- > 0) {
		mines.push_back(getMinePos());
	}
}

pair<int, int> Minesweeper::getMinePos() {
	int x = rand() % length_ + 1;
	int y = rand() % width_  + 1;
	return {x, y};
}

bool Minesweeper::updateBoard(pair<int, int> click) {
    int x = click.first, y = click.second;
    if(isMine(x, y)) {
        board[x][y] = 'X';
        return false;
    }
    solve(x, y);
    return true;
}

int Minesweeper::compute(int x, int y) {
    int sum = 0;
    if(x-1 > 0 && isMine(x-1, y)) sum++;
    if(y-1 > 0 && isMine(x, y-1)) sum++;
    if(x+1 < length_+1 && isMine(x+1, y)) sum++;
    if(y+1 < width_+1 && isMine(x, y+1)) sum++;
    if(x-1 > 0 && y-1 > 0 && isMine(x-1, y-1)) sum++;
    if(x-1 > 0 && y+1 < width_+1 && isMine(x-1, y+1)) sum++;
    if(x+1 < length_+1 && y-1 > 0 && isMine(x+1, y-1)) sum++;
    if(x+1 < length_+1 && y+1 < width_+1 && isMine(x+1, y+1)) sum++;
    return sum;
}

bool Minesweeper::isMine(const int x, const int y) {
    for(auto mine : mines) {
        if(mine.first == x && mine.second == y)
            return true;
    }
    return false;
}

void Minesweeper::solve(const int x, const int y) const {
    if(x > length_ || x < 1 || y > width_ || y < 1 || board[x][y] != 'E') 
        return;
    int sum = compute(x, y);
    if(sum > 0) board[x][y] = sum + '0';
    else board[x][y] = 'B';
    visit[x][y] = 1;
    if(board[x][y] == 'B') {
        if(x-1 > 0 && !visit[x-1][y]) solve(x-1, y);
        if(y-1 > 0 && !visit[x][y-1]) solve(x, y-1);
        if(x+1 < length_+1 && !visit[x+1][y]) solve(x+1, y);
        if(y+1 < width_+1 && !visit[x][y+1]) solve(x, y+1);
        if(x-1 > 0 && y-1 > 0 && !visit[x-1][y-1]) solve(x-1, y-1);
        if(x-1 > 0 && y+1 < width_+1 && !visit[x-1][y+1]) solve(x-1, y+1);
        if(x+1 < length_+1 && y-1 > 0 && !visit[x+1][y-1]) solve(x+1, y-1);
        if(x+1 < length_+1 && y+1 < width_+1 && !visit[x+1][y+1]) solve(x+1, y+1);
    }
    return;
}

void Minesweeper::showBoard() const {
    for(auto bd : board) {
        for(auto b : bd) {
            cout << b << " ";
        }
        cout << endl;
    }
}

bool Minesweeper::isClear() {
    for(int i = 1; i <= length_; i++) {
        for(int j = 1; j <= width_; j++) {
            if(board[i][j] == 'E' && !isMine(i, j)) 
                return false;
        }
    }
    return true;
}

void Minesweeper::showResult() {
    for(int i = 1; i <= length_; i++) {
        for(int j = 1; j <= width_; j++) {
            if(board[i][j] == 'E' && isMine(i, j)) 
                board[i][j] = 'M';
        }		
    }
}

int main(int argc, char *argv[]) 
{
    int length, width;
    pair<int, int> click;
    bool result = true;

    if(argc != 3) {
        cout << "Usage: " << argv[0] << "length width" <<endl;
    }

    length = atoi(argv[1]);
    width = atoi(argv[2]);

    if(length < 0 || length > 40 || width < 0 || width > 40) {
        cout << "Please input length or width in 0 ~ 40" << endl;   
        return 0;
    }

    Minesweeper minesweeper(length, width);
    minesweeper.showBoard();

    while(!minesweeper.isClear() && result) {
        cin >> click.first >> click.second;
        if(click.first > length || click.second > width) {
            cout << "wrong pos!" << endl;
            continue;
        }
        result = minesweeper.updateBoard(click);
        minesweeper.showBoard();
    }

    if(minesweeper.isClear()) cout << "You Win!" << endl;
    else cout << "Boom!" << endl;
    minesweeper.showResult();
    minesweeper.showBoard();

    return 0;
}


