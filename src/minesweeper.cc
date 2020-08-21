#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class Minesweeper {
public:
	Minesweeper(int length, int width): length_(length), width_(width) {
		srand(time(0));
		boardInit(4);
		vector<vector<int>> temp(length_, vector<int>(width_));		
		visit = temp;
	}

	Minesweeper(int length, int width, int minesNum): length_(length), width_(width) {
		srand(time(0));
		boardInit(minesNum);
		vector<vector<int>> temp(length_, vector<int>(width_));		
		visit = temp;
	}

	void boardInit(int minesNum) {
		vector<vector<char>> temp (length_, vector<char>(width_, 'E'));		
		board = temp;
		while(minesNum-- > 0) {
			mines.push_back(getMinePos());
		}
	}

	pair<int, int> getMinePos() {
		int x = rand() % length_;
		int y = rand() % width_;
		
		return {x, y};
	}

    bool updateBoard(pair<int, int> click) {
        int x = click.first, y = click.second;
        if(isMine(x, y)) {
            board[x][y] = 'X';
            return false;
        }
        solve(x, y);
        return true;
    }

    int compute(int x, int y) {
        int sum = 0;
        if(x-1 >= 0 && isMine(x-1, y)) sum++;
        if(y-1 >= 0 && isMine(x, y-1)) sum++;
        if(x+1 < length_ && isMine(x+1, y)) sum++;
        if(y+1 < width_ && isMine(x, y+1)) sum++;
        if(x-1 >= 0 && y-1 >= 0 && isMine(x-1, y-1)) sum++;
        if(x-1 >= 0 && y+1 < width_ && isMine(x-1, y+1)) sum++;
        if(x+1 < length_ && y-1 >= 0 && isMine(x+1, y-1)) sum++;
        if(x+1 < length_ && y+1 < width_ && isMine(x+1, y+1)) sum++;
        return sum;
    }

	bool isMine(int x, int y) {
		for(auto mine : mines) {
			if(mine.first == x && mine.second == y)
				return true;
		}
		return false;
	}

    void solve(int x, int y) {
        if(x >= length_ || x < 0 || y >= width_ || y < 0 || board[x][y] != 'E') 
            return;
        int sum = compute(x, y);
        if(sum > 0) board[x][y] = sum + '0';
        else board[x][y] = 'B';
        visit[x][y] = 1;
        if(board[x][y] == 'B') {
            if(x-1 >= 0 && !visit[x-1][y]) solve(x-1, y);
            if(y-1 >= 0 && !visit[x][y-1]) solve(x, y-1);
            if(x+1 < board.size() && !visit[x+1][y]) solve(x+1, y);
            if(y+1 < board[0].size() && !visit[x][y+1]) solve(x, y+1);
            if(x-1 >= 0 && y-1 >= 0 && !visit[x-1][y-1]) solve(x-1, y-1);
            if(x-1 >= 0 && y+1 < board[0].size() && !visit[x-1][y+1]) solve(x-1, y+1);
            if(x+1 < board.size() && y-1 >= 0 && !visit[x+1][y-1]) solve(x+1, y-1);
            if(x+1 < board.size() && y+1 < board[0].size() && !visit[x+1][y+1]) solve(x+1, y+1);
        }
        return;
    }
	
	void showBoard() {
		for(auto bd : board) {
			for(auto b : bd) {
				cout << b << " ";
			}
			cout << endl;
		}
	}

private:
	vector<vector<char>> board;
    vector<vector<int>> visit;
	int length_, width_;
	void solve();
	vector<pair<int, int>> mines;
	//void boardInit(int wines);
	//pair<int, int> getWinePos(int length, int width);
	//int computeMines(int x, int y);
};


int main() 
{
	Minesweeper minesweeper(10, 10);
	minesweeper.showBoard();
	pair<int, int> click;
	bool result = true;
	while(result) {
		cin >> click.first >> click.second;
		result = minesweeper.updateBoard(click);
		minesweeper.showBoard();
	}

	return 0;
}





