#include "Board.h"
#include <cmath>
#include <graphics.h>
#include <vector>

Board::Board() {
	matrix = vector<vector<int>>(21, vector<int>(21));//��������
	initGame();//�������ر��	
}

void Board::play() {
	MOUSEMSG m;
	int a = 0, b = 0;//��������
	int x = 0, y = 0;//���ر�����

	while (1) {
		m = GetMouseMsg();
		mapMouseToBoard(m.x, m.y, a, b, x, y);

		if (m.uMsg == WM_LBUTTONDOWN) {
			if (matrix[a][b] != 0) {//�����ظ�����һ��λ����
				MessageBoxW(NULL, L"�Ѿ������ӣ�������ѡ��", L"��ʾ", MB_OK);//������ʾ��
				continue;
			}
			else {
				drawPiece(x, y, a, b);//����
			}
		}

		if (isGameOver(a,b)) {
			if ((flag - 1) % 2 == 0) {//����Ӯ
				MessageBoxW(NULL, L"����ʤ��", L"��Ϸ����", MB_OK);
			}
			else {//����Ӯ
				MessageBoxW(NULL, L"����ʤ��", L"��Ϸ����", MB_OK);
			}

			exit(0);//�˳���Ϸ
		}
	}
}

void Board::initGame() {
	initgraph(600, 500);//�������600������أ�500�߶�����

	loadimage(NULL, L"D:\\preview.PNG");//����ͼƬ

	for (int i = 0;i <= 500;i += 25) {
		line(0, i, 500, i);//����
		line(i, 0, i, 500);//����
	}

	line(501, 0, 501, 500);//���ұߵ�����

	outtextxy(510, 100, L"���1������");
	outtextxy(510, 200, L"���2������");//����Ӧλ��������ı���Ϣ
}

void Board::overflow(int& a) {//��ֹ�����Խ��
	if (a < 0) {
		a=0;
	}
	else if (a >20) {
		a = 20;
	}
}

void Board::mapMouseToBoard(int mouseX, int mouseY, int& a, int& b, int& x, int& y) {
	a = (mouseX + 12) / 25;
	b = (mouseY + 12) / 25;//ӳ�䵽������
	
	overflow(a);
	overflow(b);

	x = a * 25;
	y = b * 25;//ӳ�䵽���ر����
}

void Board::drawPiece(int x, int y,int a,int b) {
	setfillcolor(flag % 2 == 0 ? BLACK : WHITE);
	solidcircle(x, y, 10);
	matrix[a][b] = (flag % 2 == 0 ? 1 : 2);
	flag++;
}

bool Board::isGameOver(int a, int b) {
	int currentColor = matrix[a][b];

	if (currentColor == 0) { //������
		return false;
	}

	for (int i = 0; i < 4; i++) { // ��ΪҪ���������Է�������ֻ��4������
		int count = 1;
		int dx = direction_X[i];
		int dy = direction_Y[i];

		for (int step = 1; step <= 4; step++) {//˳���������
			int newX = a + step * dx;
			int newY = b + step * dy;

			if (!isValidPosition(newX, newY) || matrix[newX][newY] != currentColor) {
				break;
			}
			count++;
		}

		for (int step = 1; step <= 4; step++) { //�����������
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
