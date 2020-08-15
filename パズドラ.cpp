#include<stdio.h> // for printf etc...
#include<conio.h> // for getch() to input
#include<stdlib.h> // for system
#include<time.h>
#include<string.h>//文字列操作関数

#define FIELD_WIDTH 8
#define FIELD_HEIGHT 8
#define BLOCK_TYPE_MAX 7

enum {//列挙
	CELL_TYPE_NONE,
	CELL_TYPE_BLOCK_0,
	CELL_TYPE_BLOCK_1,
	CELL_TYPE_BLOCK_2,
	CELL_TYPE_BLOCK_3,
	CELL_TYPE_BLOCK_4,
	CELL_TYPE_BLOCK_5,
	CELL_TYPE_BLOCK_6,
	CELL_TYPE_MAX
};

char cellAA[][2 + 1] = {//?????????????
	"・",//CELL_TYPE_NONE
	"〇",//CELL_TYPE_BLOCK_0
	"△",//CELL_TYPE_BLOCK_1
	"□",//CELL_TYPE_BLOCK_2
	"●",//CELL_TYPE_BLOCK_3
	"▲",//CELL_TYPE_BLOCK_4
	"■",//CELL_TYPE_BLOCK_5
	"☆",//CELL_TYPE_BLOCK_6

};

int cells[FIELD_HEIGHT][FIELD_WIDTH];
int checked[FIELD_HEIGHT][FIELD_WIDTH];//check済みかどうか
bool locked = true;//落ちコンのための変数　カーソルが動くか動かんか
int cursorX, cursorY;//カーソルの位置定義 グローバル変数は０で初期化
int selectedX=-1, selectedY=-1;
//連結しているブロックの関数
int getConnectedBlockCount(int _x, int _y, int _cellType, int _count) {
	if (
		(_x < 0) || (_x >= FIELD_WIDTH) || (_y < 0) || (_y >= FIELD_HEIGHT)
		|| checked[_y][_x]
		|| (cells[_y][_x] == CELL_TYPE_NONE)
		|| (cells[_y][_x] != _cellType)
		)
		return _count;
	_count++;
	checked[_y][_x] = true;
	//再起処理という!!!!!!!!!!!!!!!!!????????????????????????????????
	_count = getConnectedBlockCount(_x, _y-1, _cellType, _count);
	_count = getConnectedBlockCount(_x-1, _y, _cellType, _count);
	_count = getConnectedBlockCount(_x, _y+1 , _cellType, _count);
	_count = getConnectedBlockCount(_x+1 , _y, _cellType, _count);
}

void eraseConnectedBlocks(int _x, int _y, int _cellType) {
	if (
		(_x < 0) || (_x >= FIELD_WIDTH) || (_y < 0) || (_y >= FIELD_HEIGHT)
		|| (cells[_y][_x] == CELL_TYPE_NONE)
		|| (cells[_y][_x] != _cellType)
		)
		return;

	cells[_y][_x] = CELL_TYPE_NONE;
	eraseConnectedBlocks(_x, _y-1, _cellType);
	eraseConnectedBlocks(_x-1, _y, _cellType);
	eraseConnectedBlocks(_x, _y+1, _cellType);
	eraseConnectedBlocks(_x+1, _y, _cellType);
}

void eraseConnectedBlocksAll() {
	//ブロックを消す処理
	memset(checked, 0, sizeof checked);//チェックフラグを０で回避
	for (int y = 0; y < FIELD_HEIGHT; y++)
		for (int x = 0; x < FIELD_WIDTH; x++) {
			int n = getConnectedBlockCount(x, y, cells[y][x], 0);
			if (n >= 3) {
				eraseConnectedBlocks(x, y, cells[y][x]);//ブロックを消す。連続したやつ
				locked = true;
			}
		}

}

void display() {//途中で関数化して再描画しやすくする。全部書いた後関数を作っていた。
	system("cls");//画面のクリア
	for (int y = 0; y < FIELD_HEIGHT; y++) {
		for (int x = 0; x < FIELD_WIDTH; x++)
			if ((x == cursorX) && (y == cursorY)&&(!locked))
				printf("◎");//その位置だけ動かす石
			else
				printf("%s", cellAA[cells[y][x]]);//ほかは6種類の石
		if (y == selectedY)
			printf("←");
		printf("\n");
	}
	for (int x = 0; x < FIELD_WIDTH; x++)
		printf("%s", (x == selectedX) ? "↑" : "　");//この文の意味が分からん
}

int main() {
	srand((unsigned int)time(NULL));
	for (int y = 0; y < FIELD_HEIGHT; y++)
		for (int x = 0; x < FIELD_WIDTH; x++)
			cells[y][x] = CELL_TYPE_BLOCK_0 + rand() % BLOCK_TYPE_MAX;

	

	time_t t = time(NULL);//時間関数？？？
	while (1) {
		if (t < time(NULL)) {
			t = time(NULL);//現在の時間を再設定

			if (locked) {//落ちコンの関数
				eraseConnectedBlocksAll();
				locked = false;//一旦仮釈放
				for (int y = FIELD_HEIGHT - 2; y >= 0; y--) {
					for (int x = 0; x < FIELD_WIDTH; x++) {
						if ((cells[y][x] != CELL_TYPE_NONE)
							&& (cells[y + 1][x] == CELL_TYPE_NONE)) {
							cells[y + 1][x] = cells[y][x];
							cells[y][x] = CELL_TYPE_NONE;
							locked = true;//再びユーザーが操作可能
						}
					}
				
				}
				for (int x = 0; x < FIELD_WIDTH; x++) {
					if (cells[0][x] == CELL_TYPE_NONE) {
						cells[0][x] = CELL_TYPE_BLOCK_0 + rand() % BLOCK_TYPE_MAX;/*ランダムスポーン(落ち込ん)*/
						locked = true;
			     	}
				} 
				if (!locked) {
					eraseConnectedBlocksAll();//初期盤面の落ち今冬終わった後に
				}

			}
			display();	
		}

		if (_kbhit()) {//もし、キーボード入力があればという意味
			if (locked)
				_getch();//もし、ユーザーロックがかかっていたら読み込みをよみすてるため
			else {
				switch (_getch()) {//スイッチ文にキーボードの入力をもらう
				case 'w':
					cursorY--; break;
				case 's':
					cursorY++; break;
				case 'a':
					cursorX--; break;
				case 'd':
					cursorX++; break;
				case'c'://本当はdefaultだったとこだけど正常ではなかった。
					if (selectedX < 0) {
						selectedX = cursorX;
						selectedY = cursorY;
					}
					else {
						int distance =abs( selectedX - cursorX)+abs(selectedY-cursorY);//隣り合うブロックのみ入れ替え
						if (distance == 0) {
							selectedX =
								selectedY = -1;
						}
						else if (distance == 1) {
							int temp = cells[cursorY][cursorX];
							cells[cursorY][cursorX] = cells[selectedY][selectedX];
							cells[selectedY][selectedX] = temp;
							eraseConnectedBlocksAll();
							

							selectedX =//これはなに;
								selectedY = -1;//同じ行に書いて、三個のものがイコールで等価であることを示している。
							locked = true;
							
						}
						else {
							printf("\a");
						}
						
					}break;

				}
				display();//画面のレスポンスをよくするため.カーソルが動いたら即座に再描画
			}
		}
	}
}