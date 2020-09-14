#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <vector>
#include <unordered_set>

namespace Minesweeper {

static const char wall = '+';
static const char empty = '@';
static const char mine = '*';
static const char black = ' ';

typedef struct Pos {
    int x;
    int y;
    Pos(): x(0), y(0){};
    Pos(int a, int b): x(a), y(b){};
} Pos;

class Board {
public:
    Board(int length, int width, int minesNum);

    bool updateBoard(Pos click);
    void showBoard() const;
    bool isClear();
    void showMines();
private:
    int length_, width_;
    struct posHash {
        size_t operator()(const Pos& pos) const {
            int temp = pos.x*100 + pos.y;
            return std::hash<int>()(temp);
        }
    };
    std::vector<std::vector<char>> board;
    std::vector<std::vector<int>> visit;
    std::vector<std::pair<int, int>> direction;
    std::unordered_set<Pos, posHash> mines;

    void solve();
    bool isMine(const Pos pos);
    void boardInit(int minesNum);
    void getMinePos(Pos &pos);
    int computeMines(const Pos pos);
    void solve(Pos pos);
};

inline bool operator==(const Pos &p1, const Pos &p2)
{ 
    return std::hash<int>()(p1.x*100 + p1.y) == std::hash<int>()(p2.x*100 + p2.y); 
}

} //namespace Minesweeper

#endif
