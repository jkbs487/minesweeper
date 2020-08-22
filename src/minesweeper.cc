#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "minesweeper.h"


Minesweeper::Minesweeper(int length, int width): length_(length), width_(width), board(vector<vector<char>>(length+2, vector<char>(width+2, 'E'))), visit(vector<vector<int>> (length+2, vector<int>(width+2))) {
    srand(time(0));
    boardInit(length);
}

Minesweeper::Minesweeper(int length, int width, int minesNum): length_(length), width_(width), board(vector<vector<char>>(length+2, vector<char>(width+2, 'E'))), visit(vector<vector<int>> (length+2, vector<int>(width+2)))  {
    srand(time(0));
    boardInit(minesNum);
}

void Minesweeper::boardInit(int minesNum) {
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
    
    direction.push_back({0, 1});
    direction.push_back({0, -1});
    direction.push_back({1, 0});
    direction.push_back({-1, 0});
    direction.push_back({1, 1});
    direction.push_back({1, -1});
    direction.push_back({-1, 1});
    direction.push_back({-1, -1});
}

Minesweeper::Pos Minesweeper::getMinePos() {
    Minesweeper::Pos pos;
    pos.x = rand() % length_ + 1;
    pos.y = rand() % width_  + 1;
    return pos;
}

bool Minesweeper::updateBoard(Minesweeper::Pos click) {
    if(isMine(click)) {
        board[click.x][click.y] = 'X';
        return false;
    }
    solve(click);
    return true;
}

int Minesweeper::computeMines(const Minesweeper::Pos pos) {
    int mines = 0;
    Minesweeper::Pos tempPos;
    for(pair<int, int> dir : direction) {
        tempPos.x = dir.first + pos.x;
        tempPos.y = dir.second + pos.y;
        if(tempPos.x > 0 && tempPos.x < length_+1 && tempPos.y > 0 && tempPos.y < width_+1 && isMine(tempPos)) 
            mines++;
    }
    return mines;
}

bool Minesweeper::isMine(const Minesweeper::Pos pos) {
    for(auto mine : mines) {
        if(mine.x == pos.x && mine.y == pos.y)
            return true;
    }
    return false;
}

void Minesweeper::solve(Minesweeper::Pos curpos) {
    if(curpos.x > length_ || curpos.x < 1 || curpos.y > width_ || curpos.y < 1 || board[curpos.x][curpos.y] != 'E') 
        return;
    int sum = computeMines(curpos);
    Minesweeper::Pos tempPos;
    if(sum > 0) board[curpos.x][curpos.y] = sum + '0';
    else board[curpos.x][curpos.y] = 'B';
    visit[curpos.x][curpos.y] = 1;
    if(board[curpos.x][curpos.y] == 'B') {
        for(pair<int, int> dir : direction) {
            tempPos.x = dir.first + curpos.x;
            tempPos.y = dir.second + curpos.y;
            if(tempPos.x > 0 && tempPos.x < length_+1 && tempPos.y > 0 && tempPos.y < width_+1 && !visit[tempPos.x][tempPos.y]) 
                solve(tempPos);
        }
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
    Minesweeper::Pos curpos;
    for(int i = 1; i <= length_; i++) {
        for(int j = 1; j <= width_; j++) {
            curpos.x = i;
            curpos.y = j;
            if(board[i][j] == 'E' && !isMine(curpos)) 
                return false;
        }
    }
    return true;
}

void Minesweeper::showMines() {
    Minesweeper::Pos curpos;
    for(int i = 1; i <= length_; i++) {
        for(int j = 1; j <= width_; j++) {
            curpos.x = i;
            curpos.y = j;
            if(board[i][j] == 'E' && isMine(curpos)) 
                board[i][j] = 'M';
        }		
    }
}

int main(int argc, char *argv[]) 
{
    int length, width;
    Minesweeper::Pos click;
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
        cin >> click.x >> click.y;
        if(click.x > length || click.y > width) {
            cout << "wrong pos!" << endl;
            continue;
        }
        result = minesweeper.updateBoard(click);
        minesweeper.showBoard();
    }

    if(minesweeper.isClear()) cout << "You Win!" << endl;
    else cout << "Boom!" << endl;
    minesweeper.showMines();
    minesweeper.showBoard();

    return 0;
}


