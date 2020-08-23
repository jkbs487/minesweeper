#include "minesweeper.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) 
{
    int length, width, mines;
    Minesweeper::Pos click;
    bool result = true;
    int level;

    cout << "Please choose a level: " << endl;
    cout << "1 low level 8*8 size 10 mines" << endl;
    cout << "2 middle level 16*16 size 40 mines" << endl;
    cout << "3 high level 30*16 size 99 mines" << endl;
    cout << "4 custom" << endl;
    
    cin >> level;
    
    switch(level) {
        case 1:
            length = 8, width = 8, mines = 10;
            break;
        case 2:
            length =16 , width = 16, mines = 40;
            break;
        case 3:
            length = 30, width = 16, mines = 99;
            break;
        case 4:
            cout << "length: ";
            cin >> length;
            cout << "width: ";
            cin >> width;
            cout << "mines: ";
            cin >> mines;
            break;
        default:
            cout << "Please input number 1-4" << endl;
    }
    
    if(length < 0 || length > 40 || width < 0 || width > 40) {
        cout << "Please input length or width in 0 ~ 40" << endl;   
        return 1;
    }
    
    Minesweeper minesweeper(length, width, mines);
    minesweeper.showBoard();
    while(!minesweeper.isClear() && result) {
        cin >> click.x >> click.y;
        if(cin.fail()) {
            cout << "illegal charactor!" << endl;
            cin.clear();
            cin.sync();
            break;
        }
        if(click.x > length || click.y > width || cin.fail()) {
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


