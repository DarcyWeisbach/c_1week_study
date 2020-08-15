#include<stdio.h> // for printf etc...
#include<conio.h> // for getch() to input
#include<stdlib.h> // for system
#include<time.h>
#include<string.h>//�����񑀍�֐�

#define FIELD_WIDTH 8
#define FIELD_HEIGHT 8
#define BLOCK_TYPE_MAX 7

enum {//��
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
	"�E",//CELL_TYPE_NONE
	"�Z",//CELL_TYPE_BLOCK_0
	"��",//CELL_TYPE_BLOCK_1
	"��",//CELL_TYPE_BLOCK_2
	"��",//CELL_TYPE_BLOCK_3
	"��",//CELL_TYPE_BLOCK_4
	"��",//CELL_TYPE_BLOCK_5
	"��",//CELL_TYPE_BLOCK_6

};

int cells[FIELD_HEIGHT][FIELD_WIDTH];
int checked[FIELD_HEIGHT][FIELD_WIDTH];//check�ς݂��ǂ���
bool locked = true;//�����R���̂��߂̕ϐ��@�J�[�\����������������
int cursorX, cursorY;//�J�[�\���̈ʒu��` �O���[�o���ϐ��͂O�ŏ�����
int selectedX=-1, selectedY=-1;
//�A�����Ă���u���b�N�̊֐�
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
	//�ċN�����Ƃ���!!!!!!!!!!!!!!!!!????????????????????????????????
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
	//�u���b�N����������
	memset(checked, 0, sizeof checked);//�`�F�b�N�t���O���O�ŉ��
	for (int y = 0; y < FIELD_HEIGHT; y++)
		for (int x = 0; x < FIELD_WIDTH; x++) {
			int n = getConnectedBlockCount(x, y, cells[y][x], 0);
			if (n >= 3) {
				eraseConnectedBlocks(x, y, cells[y][x]);//�u���b�N�������B�A���������
				locked = true;
			}
		}

}

void display() {//�r���Ŋ֐������čĕ`�悵�₷������B�S����������֐�������Ă����B
	system("cls");//��ʂ̃N���A
	for (int y = 0; y < FIELD_HEIGHT; y++) {
		for (int x = 0; x < FIELD_WIDTH; x++)
			if ((x == cursorX) && (y == cursorY)&&(!locked))
				printf("��");//���̈ʒu������������
			else
				printf("%s", cellAA[cells[y][x]]);//�ق���6��ނ̐�
		if (y == selectedY)
			printf("��");
		printf("\n");
	}
	for (int x = 0; x < FIELD_WIDTH; x++)
		printf("%s", (x == selectedX) ? "��" : "�@");//���̕��̈Ӗ����������
}

int main() {
	srand((unsigned int)time(NULL));
	for (int y = 0; y < FIELD_HEIGHT; y++)
		for (int x = 0; x < FIELD_WIDTH; x++)
			cells[y][x] = CELL_TYPE_BLOCK_0 + rand() % BLOCK_TYPE_MAX;

	

	time_t t = time(NULL);//���Ԋ֐��H�H�H
	while (1) {
		if (t < time(NULL)) {
			t = time(NULL);//���݂̎��Ԃ��Đݒ�

			if (locked) {//�����R���̊֐�
				eraseConnectedBlocksAll();
				locked = false;//��U���ߕ�
				for (int y = FIELD_HEIGHT - 2; y >= 0; y--) {
					for (int x = 0; x < FIELD_WIDTH; x++) {
						if ((cells[y][x] != CELL_TYPE_NONE)
							&& (cells[y + 1][x] == CELL_TYPE_NONE)) {
							cells[y + 1][x] = cells[y][x];
							cells[y][x] = CELL_TYPE_NONE;
							locked = true;//�Ăу��[�U�[������\
						}
					}
				
				}
				for (int x = 0; x < FIELD_WIDTH; x++) {
					if (cells[0][x] == CELL_TYPE_NONE) {
						cells[0][x] = CELL_TYPE_BLOCK_0 + rand() % BLOCK_TYPE_MAX;/*�����_���X�|�[��(��������)*/
						locked = true;
			     	}
				} 
				if (!locked) {
					eraseConnectedBlocksAll();//�����Ֆʂ̗������~�I��������
				}

			}
			display();	
		}

		if (_kbhit()) {//�����A�L�[�{�[�h���͂�����΂Ƃ����Ӗ�
			if (locked)
				_getch();//�����A���[�U�[���b�N���������Ă�����ǂݍ��݂���݂��Ă邽��
			else {
				switch (_getch()) {//�X�C�b�`���ɃL�[�{�[�h�̓��͂����炤
				case 'w':
					cursorY--; break;
				case 's':
					cursorY++; break;
				case 'a':
					cursorX--; break;
				case 'd':
					cursorX++; break;
				case'c'://�{����default�������Ƃ������ǐ���ł͂Ȃ������B
					if (selectedX < 0) {
						selectedX = cursorX;
						selectedY = cursorY;
					}
					else {
						int distance =abs( selectedX - cursorX)+abs(selectedY-cursorY);//�ׂ荇���u���b�N�̂ݓ���ւ�
						if (distance == 0) {
							selectedX =
								selectedY = -1;
						}
						else if (distance == 1) {
							int temp = cells[cursorY][cursorX];
							cells[cursorY][cursorX] = cells[selectedY][selectedX];
							cells[selectedY][selectedX] = temp;
							eraseConnectedBlocksAll();
							

							selectedX =//����͂Ȃ�;
								selectedY = -1;//�����s�ɏ����āA�O�̂��̂��C�R�[���œ����ł��邱�Ƃ������Ă���B
							locked = true;
							
						}
						else {
							printf("\a");
						}
						
					}break;

				}
				display();//��ʂ̃��X�|���X���悭���邽��.�J�[�\�����������瑦���ɍĕ`��
			}
		}
	}
}