#include <vector>
using namespace std;

class Board {
public:
    Board();
    void play();

private:
    vector<vector<int>> matrix;
    int direction_X[4] = {1,0,-1,1};
    int direction_Y[4] = {0,1,1,1};
    int flag;

    void overflow(int &a);
    void initGame();
    void mapMouseToBoard(int mouseX, int mouseY, int& a, int& b, int& x, int& y);
    void drawPiece(int x, int y,int a,int b);
    bool isGameOver(int a, int b);
    bool isValidPosition(int x, int y);
};

