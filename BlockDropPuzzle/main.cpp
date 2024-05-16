#define _CRT_NONSTDC_NO_WARNINGS	//kbhit(), getch()���g�p���邽�߂̋L�q

#include<stdio.h>
#include<conio.h>		//�L�[���͗p
#include<Windows.h>		//sleep()���g������
#include <time.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_SPACE 32
//�t�B�[���h�̒�`
#define FIELD_HEIGHT 22
#define FIELD_WIDTH 12	

//�F�̒�`
enum { BLACK, RED, GREEN, YELLOW, MAGENTA, CYAN, WHITE };

typedef struct {
	int shape[4][4];
	int size; // �u���b�N�̃T�C�Y�i�ő�4�j
} Block;

// I�^�u���b�N
Block I = { {
	{0, 0, 0, 0},
	{1, 1, 1, 1}, 
	{0, 0, 0, 0}, 
	{0, 0, 0, 0} },
	4 };

// O�^�u���b�N
Block O = { { 
	{1, 1}, 
	{1, 1} }, 
	2 };

// T�^�u���b�N
Block T = { { 
	{0, 1, 0},
	{1, 1, 1}, 
	{0, 0, 0} },
	3 };

// S�^�u���b�N
Block S = { { 
	{0, 1, 1}, 
	{1, 1, 0}, 
	{0, 0, 0} }, 
	3 };

// Z�^�u���b�N
Block Z = { { 
	{1, 1, 0},
	{0, 1, 1},
	{0, 0, 0} }, 
	3 };

// J�^�u���b�N
Block J = { {
	{1, 0, 0}, 
	{1, 1, 1}, 
	{0, 0, 0} },
	3 };

// L�^�u���b�N
Block L = { { 
	{0, 0, 1}, 
	{1, 1, 1}, 
	{0, 0, 0} }, 
	3 };

//�u���b�N��z��ɂ܂Ƃ߂�
Block blocks[] = { I, O, T, S, Z, J, L };

//�Q�[���Ŏg�p���鎞�Ƀu���b�N���i�[����ϐ�
Block currentBlock;
//��̃u���b�N�̈ʒu
int currentX = FIELD_WIDTH / 2;
int currentY = 0;

//

//#:�ǁA@:�u���b�N
int field[FIELD_HEIGHT][FIELD_WIDTH] = {
	{ 1,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1 }
};


// �֐��̃v���g�^�C�v�錾
void drawField();				//�Q�[����ʂ�`�悷��
void cursor(int x, int y);		//�J�[�\���ʒu��ύX����	
void color(int col);			//�����̐F��ύX����
void eraseBlock();
void drawBlock();
void spawnBlock();				//�u���b�N�𐶐�����
void move(int x);				//�~�m�����E�Ɉړ�����
void rotate90(Block* block);	//�u���b�N�̔z���90�x��]������
void rotate();					//�~�m����]������(��]�\�������肷��)
void drop();					//�~�m���}���ɗ���������
void fall();					//�~�m�̎��R��������
void eraseLine();				//���C��������������������
bool isGameOver();				//�Q�[���I�[�o�[�`�F�b�N(��ԏ�܂ŋl�݂���������)


//main�֐�
int main(void) {
	spawnBlock();
	//�Q�[�����[�v
	while (1) {
		//����u���b�N����������
		eraseBlock();

		//�L�[���́A�v���C���[�̈ړ�
		int key = 0;
		if (kbhit())key = getch();
		//���܂ŗ���������
		if (key == KEY_DOWN) drop();
		//�ړ���
		if (key == KEY_LEFT) move(-1);
		//�ړ��E
		if (key == KEY_RIGHT) move(1);
		//��]
		if (key == KEY_SPACE) rotate();

		//�u���b�N���t�B�[���h�ɏ�����
		drawBlock();

		//�~�m�����R����������
		fall();
		//�}�b�v�̍X�V
		drawField();

		//�ҋ@����
		Sleep(50);

		//�Q�[���I�[�o�[����
		if (isGameOver()) {
			Sleep(1000);
			return 0;
		}
	}
}

//�Q�[����ʂ�`���֐�
void drawField(void) {
	for (int y = 0; y < FIELD_HEIGHT; y++) {
		for (int x = 0; x < FIELD_WIDTH; x++) {
			//if (field[y][x] == '#') color(GREEN);
			//if (field[y][x] == 'B') color(YELLOW);
			//if (field[y][x] == 'G') color(WHITE);
			//if (field[y][x] == 'P') color(RED);
			if (field[y][x] == 1) {
				cursor(x, y);
				printf("#");
			}
			if (field[y][x] == 0) {
				cursor(x, y);
				printf(" ");
			}
		}
	}
}

//�J�[�\���ʒu���w�肷��֐�
void cursor(int x, int y) {
	printf("\x1b[%d;%dH", y + 1, x + 1);
}

//�����╶����̐F���w�肷��֐�
void color(int col) {
	printf("\x1b[3%dm", col);
}

void eraseBlock() {
	int size = currentBlock.size;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (currentBlock.shape[i][j] == 1) {
				field[currentY + i][currentX + j] = 0;
			}
		}
	}
}

void drawBlock(){
	int size = currentBlock.size;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			field[currentY + i][currentX + j] = currentBlock.shape[i][j];
		}
	}

}

//�u���b�N�������_���ɐ�������
void spawnBlock() {
	int size = currentBlock.size;
	srand(time(NULL));
	currentBlock = blocks[rand() % 7];
	currentX = FIELD_WIDTH / 2 - size / 2;
	currentY = 0;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			field[currentY + i][currentX + j] = currentBlock.shape[i][j];
		}
	}
}

//�~�m�����E�Ɉړ�����
void move(int x) {

}

//�u���b�N�̔z���90�x��]������
void rotate90(Block* block) {
	int size = block->size;
	int temp[4][4];
	
	//temp�ɏc������ւ��Ċi�[����
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			temp[j][size - 1 - i] = block->shape[i][j];
		}
	}
	//��]��̃u���b�N�����̃u���b�N�ɃR�s�[����
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			block->shape[i][j] = temp[i][j];
		}
	}

}


//�~�m����]������
void rotate() {
	//Block temp = currentBlock;
	rotate90(&currentBlock);
}

//�~�m���}���ɗ���������
void drop() {

}

//�~�m�̎��R��������
void fall() {

}

//���C��������������������
void eraseLine() {

}

//�Q�[���I�[�o�[�`�F�b�N(��ԏ�܂ŋl�݂���������)
bool isGameOver() {
	return FALSE;
}