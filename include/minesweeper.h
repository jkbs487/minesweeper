#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <vector>

using namespace std;


class Minesweeper {
public:
    typedef int Pos;
	Minesweeper(int length, int width);
	Minesweeper(int length, int width, int minesNum);

    bool updateBoard(pair<int, int> click);
	void showBoard() const;
	bool isClear();
	void showResult();

private:
	vector<vector<char>> board;
    vector<vector<int>> visit;
	int length_, width_;
	void solve();
	bool isMine(int x, int y);
	vector<pair<int, int>> mines;
	void boardInit(int minesNum);
	pair<int, int> getMinePos();
    int compute(const int x, const int y) const;
    void solve(int x, int y);
};


#endif
