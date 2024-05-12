#define _CRT_NONSTDC_NO_WARNINGS	//kbhit(), getch()���g�p���邽�߂̋L�q
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_SPACE 32

#include<stdio.h>
#include<conio.h>		//�L�[���͗p
#include<Windows.h>		//sleep()���g������

//�F�̒�`
enum { BLACK, RED, GREEN, YELLOW, MAGENTA, CYAN, WHITE };

//
#define HEIGHT 22
#define WIDTH 13	//\0(�I�[����)���܂߂�̂�12�{1��13
//#:�ǁA@:�u���b�N
char field[HEIGHT][WIDTH] = {
	"############",
	"#          #",
	"#          #",
	"#          #",
	"#          #",
	"#          #",
	"#          #",
	"#          #",
	"#          #",
	"#          #",
	"#          #",
	"#          #",
	"#          #",
	"#          #",
	"#          #",
	"#          #",
	"#          #",
	"#          #",
	"#          #",
	"#          #",
	"#          #",
	"############"
};

// �֐��̃v���g�^�C�v�錾
void drawField();				//�Q�[����ʂ�`�悷��
void cursor(int x, int y);		//�J�[�\���ʒu��ύX����	
void color(int col);			//�����̐F��ύX����
void move(int x);				//�~�m�����E�Ɉړ�����
void rotate();					//�~�m����]������
void drop();					//�~�m���}���ɗ���������
void fall();					//�~�m�̎��R��������
void eraseLine();				//���C��������������������
bool isGameOver();				//�Q�[���I�[�o�[�`�F�b�N(��ԏ�܂ŋl�݂���������)


//main�֐�
int main(void) {

	//�Q�[�����[�v
	while (1) {

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
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			if (field[y][x] == '#') color(GREEN);
			if (field[y][x] == 'B') color(YELLOW);
			if (field[y][x] == 'G') color(WHITE);
			if (field[y][x] == 'P') color(RED);
			cursor(x, y);
			printf("%c", field[y][x]);
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

//�~�m�����E�Ɉړ�����
void move(int x) {

}

//�~�m����]������
void rotate() {

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