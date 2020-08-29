#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <vector>

using namespace std;

static const char wall = '+';
static const char empty = '@';
static const char mine = '*';
static const char black = ' ';

class Minesweeper {
public:
    typedef struct {
        int x;
        int y;
    } Pos;
    
    Minesweeper(int length, int width, int minesNum);

    bool updateBoard(Pos click);
    void showBoard() const;
    bool isClear();
    void showMines();

private:
    int length_, width_;
    vector<vector<char>> board;
    vector<vector<int>> visit;
    vector<pair<int, int>> direction;
    vector<Pos> mines;

    void solve();
    bool isMine(const Pos pos);
    void boardInit(int minesNum);
    void getMinePos(Pos &pos);
    int computeMines(const Pos pos);
    void solve(Pos pos);
};


#endif
