#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <vector>
#include <unordered_set>

using namespace std;

static const char wall = '+';
static const char empty = '@';
static const char mine = '*';
static const char black = ' ';

class Minesweeper {
public:
    typedef struct Pos {
        int x;
        int y;
        Pos(): x(0), y(0){};
        Pos(int a, int b): x(a), y(b){};
    } Pos;

    Minesweeper(int length, int width, int minesNum);

    bool updateBoard(Pos click);
    void showBoard() const;
    bool isClear();
    void showMines();
private:
    int length_, width_;
    struct posHash {
        size_t operator()(const Pos& pos) const {
            int temp = pos.x*10 + pos.y;
            return hash<int>()(temp);
        }
    };
    vector<vector<char>> board;
    vector<vector<int>> visit;
    vector<pair<int, int>> direction;
    unordered_set<Pos, posHash> mines;

    void solve();
    bool isMine(const Pos pos);
    void boardInit(int minesNum);
    void getMinePos(Pos &pos);
    int computeMines(const Pos pos);
    void solve(Pos pos);
};


#endif
