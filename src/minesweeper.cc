#include "minesweeper.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <ctime>

using namespace Minesweeper;

Board::Board(int length, int width, int minesNum)
  : length_(length), 
    width_(width), 
    board(std::vector<std::vector<char>> (length+2, std::vector<char>(width+2, empty))), 
    visit(std::vector<std::vector<int>> (length+2, std::vector<int>(width+2)))  
{
    srand(time(0));
    direction = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};   
    boardInit(minesNum);
}

void Board::boardInit(int minesNum) {
    for(int i = 0; i < width_ + 2; i++) {
        board[0][i] = wall;
        board[length_+1][i] = wall;
    }
    for(int i = 0; i < length_ + 2; i++) {
        board[i][0] = wall;
        board[i][width_+1] = wall;
    }
    while(mines.size() < minesNum) {
        Pos pos;
        getMinePos(pos);
        mines.insert(pos);
    }
}

void Board::getMinePos(Pos& pos) {
    int minePos = rand() % (length_ * width_);
    pos.x = minePos / width_ + 1;
    pos.y = minePos % width_ + 1;
}

bool Board::updateBoard(Pos click) {
    if(isMine(click)) {
        board[click.x][click.y] = 'X';
        return false;
    }
    solve(click);
    return true;
}

int Board::computeMines(const Pos pos) {
    int roundmines = 0;
    Pos tempPos;
    for(std::pair<int, int> dir : direction) {
        tempPos = Pos(dir.first + pos.x, dir.second + pos.y);
        if(tempPos.x > 0 && tempPos.x < length_+1 && tempPos.y > 0 && tempPos.y < width_+1 && isMine(tempPos)) 
            roundmines++;
    }
    return roundmines;
}

bool Board::isMine(const Pos pos) {
    for(auto mine : mines) {
        if(mine == pos)
            return true;
    }
    return false;
}

void Board::solve(Pos curpos) {
    if(curpos.x > length_ || curpos.x < 1 || curpos.y > width_ || curpos.y < 1 || board[curpos.x][curpos.y] != empty) 
        return;
    int sum = computeMines(curpos);
    Pos tempPos;
    if(sum > 0) board[curpos.x][curpos.y] = sum + '0';
    else board[curpos.x][curpos.y] = black;
    visit[curpos.x][curpos.y] = 1;
    if(board[curpos.x][curpos.y] == black) {
        for(std::pair<int, int> dir : direction) {
            tempPos.x = dir.first + curpos.x;
            tempPos.y = dir.second + curpos.y;
            if(tempPos.x > 0 && tempPos.x < length_+1 && tempPos.y > 0 && tempPos.y < width_+1 && !visit[tempPos.x][tempPos.y]) 
                solve(tempPos);
        }
    }
    return;
}

void Board::showBoard() const {
    for(auto bd : board) {
        for_each(bd.begin(), bd.end(), [](char elem){ std::cout << elem << " "; });
        std::cout << std::endl;
    }
}

bool Board::isClear() {
    Pos curpos;
    for(int i = 1; i <= length_; i++) {
        for(int j = 1; j <= width_; j++) {
            curpos = Pos(i, j);
            if(board[i][j] == empty && !isMine(curpos)) 
                return false;
        }
    }
    return true;
}

void Board::showMines() {
    Pos curpos;
    for(int i = 1; i <= length_; i++) {
        for(int j = 1; j <= width_; j++) {
            curpos = Pos(i, j);
            if(board[i][j] == empty && isMine(curpos)) 
                board[i][j] = mine;
        }		
    }
}

