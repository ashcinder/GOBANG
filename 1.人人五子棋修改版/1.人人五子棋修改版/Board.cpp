#include "Board.h"
#include <cmath>
#include <graphics.h>
#include <vector>

Board::Board() {
	matrix = vector<vector<int>>(21, vector<int>(21));//创建棋盘
	initGame();//创建像素表格	
}

void Board::play() {
	MOUSEMSG m;
	int a = 0, b = 0;//棋盘坐标
	int x = 0, y = 0;//像素表坐标

	while (1) {
		m = GetMouseMsg();
		mapMouseToBoard(m.x, m.y, a, b, x, y);

		if (m.uMsg == WM_LBUTTONDOWN) {
			if (matrix[a][b] != 0) {//棋子重复落在一个位置上
				MessageBoxW(NULL, L"已经有棋子，请重新选择", L"提示", MB_OK);//弹出提示框
				continue;
			}
			else {
				drawPiece(x, y, a, b);//落子
			}
		}

		if (isGameOver(a,b)) {
			if ((flag - 1) % 2 == 0) {//黑棋赢
				MessageBoxW(NULL, L"黑棋胜利", L"游戏结束", MB_OK);
			}
			else {//白棋赢
				MessageBoxW(NULL, L"白棋胜利", L"游戏结束", MB_OK);
			}

			exit(0);//退出游戏
		}
	}
}

void Board::initGame() {
	initgraph(600, 500);//创建表格，600宽度像素，500高度像素

	loadimage(NULL, L"D:\\preview.PNG");//加载图片

	for (int i = 0;i <= 500;i += 25) {
		line(0, i, 500, i);//横线
		line(i, 0, i, 500);//竖线
	}

	line(501, 0, 501, 500);//最右边的竖线

	outtextxy(510, 100, L"玩家1：黑棋");
	outtextxy(510, 200, L"玩家2：白棋");//在相应位置上输出文本信息
}

void Board::overflow(int& a) {//防止他娘的越界
	if (a < 0) {
		a=0;
	}
	else if (a >20) {
		a = 20;
	}
}

void Board::mapMouseToBoard(int mouseX, int mouseY, int& a, int& b, int& x, int& y) {
	a = (mouseX + 12) / 25;
	b = (mouseY + 12) / 25;//映射到棋盘上
	
	overflow(a);
	overflow(b);

	x = a * 25;
	y = b * 25;//映射到像素表格上
}

void Board::drawPiece(int x, int y,int a,int b) {
	setfillcolor(flag % 2 == 0 ? BLACK : WHITE);
	solidcircle(x, y, 10);
	matrix[a][b] = (flag % 2 == 0 ? 1 : 2);
	flag++;
}

bool Board::isGameOver(int a, int b) {
	int currentColor = matrix[a][b];

	if (currentColor == 0) { //无棋子
		return false;
	}

	for (int i = 0; i < 4; i++) { // 因为要检查两个相对方向，所以只需4个方向
		int count = 1;
		int dx = direction_X[i];
		int dy = direction_Y[i];

		for (int step = 1; step <= 4; step++) {//顺着这个方向
			int newX = a + step * dx;
			int newY = b + step * dy;

			if (!isValidPosition(newX, newY) || matrix[newX][newY] != currentColor) {
				break;
			}
			count++;
		}

		for (int step = 1; step <= 4; step++) { //反着这个方向
			int newX = a - step * dx;
			int newY = b - step * dy;

			if (!isValidPosition(newX, newY) || matrix[newX][newY] != currentColor) {
				break;
			}
			count++;
		}

		if (count >= 5) {
			return true;
		}
	}
	return false;
}

bool Board::isValidPosition(int x, int y) {
	return x >= 0 && x <= 20 && y >= 0 && y <= 20;
}
