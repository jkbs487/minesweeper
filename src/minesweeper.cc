#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "minesweeper.h"


Minesweeper::Minesweeper(int length, int width, int minesNum): length_(length), width_(width), board(vector<vector<char>>(length+2, vector<char>(width+2, empty))), visit(vector<vector<int>> (length+2, vector<int>(width+2)))  {
    srand(time(0));
    direction = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};   
    boardInit(minesNum);
}

void Minesweeper::boardInit(int minesNum) {
    for(int i = 0; i < width_ + 2; i++) {
        board[0][i] = wall;
        board[length_+1][i] = wall;
    }
    for(int i = 0; i < length_ + 2; i++) {
        board[i][0] = wall;
        board[i][width_+1] = wall;
    }
    for(int i = 0; i < minesNum; i++) {
        Minesweeper::Pos pos;
        getMinePos(pos);
        mines.push_back(pos);
    }
}

void Minesweeper::getMinePos(Minesweeper::Pos& pos) {
    pos.x = rand() % length_ + 1;
    pos.y = rand() % width_  + 1;
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
    if(curpos.x > length_ || curpos.x < 1 || curpos.y > width_ || curpos.y < 1 || board[curpos.x][curpos.y] != empty) 
        return;
    int sum = computeMines(curpos);
    Minesweeper::Pos tempPos;
    if(sum > 0) board[curpos.x][curpos.y] = sum + '0';
    else board[curpos.x][curpos.y] = black;
    visit[curpos.x][curpos.y] = 1;
    if(board[curpos.x][curpos.y] == black) {
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
            if(board[i][j] == empty && !isMine(curpos)) 
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
            if(board[i][j] == empty && isMine(curpos)) 
                board[i][j] = mine;
        }		
    }
}

