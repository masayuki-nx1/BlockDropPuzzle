#define _CRT_NONSTDC_NO_WARNINGS	//kbhit(), getch()を使用するための記述

#include<stdio.h>
#include<conio.h>		//キー入力用
#include<Windows.h>		//sleep()を使うため
#include <time.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_SPACE 32
//フィールドの定義
#define FIELD_HEIGHT 22
#define FIELD_WIDTH 12	

//色の定義
enum { BLACK, RED, GREEN, YELLOW, MAGENTA, CYAN, WHITE };

typedef struct {
	int shape[4][4];
	int size; // ブロックのサイズ（最大4）
} Block;

// I型ブロック
Block I = { {
	{0, 0, 0, 0},
	{1, 1, 1, 1}, 
	{0, 0, 0, 0}, 
	{0, 0, 0, 0} },
	4 };

// O型ブロック
Block O = { { 
	{1, 1}, 
	{1, 1} }, 
	2 };

// T型ブロック
Block T = { { 
	{0, 1, 0},
	{1, 1, 1}, 
	{0, 0, 0} },
	3 };

// S型ブロック
Block S = { { 
	{0, 1, 1}, 
	{1, 1, 0}, 
	{0, 0, 0} }, 
	3 };

// Z型ブロック
Block Z = { { 
	{1, 1, 0},
	{0, 1, 1},
	{0, 0, 0} }, 
	3 };

// J型ブロック
Block J = { {
	{1, 0, 0}, 
	{1, 1, 1}, 
	{0, 0, 0} },
	3 };

// L型ブロック
Block L = { { 
	{0, 0, 1}, 
	{1, 1, 1}, 
	{0, 0, 0} }, 
	3 };

//ブロックを配列にまとめる
Block blocks[] = { I, O, T, S, Z, J, L };

//ゲームで使用する時にブロックを格納する変数
Block currentBlock;
//場のブロックの位置
int currentX = FIELD_WIDTH / 2;
int currentY = 0;

//

//#:壁、@:ブロック
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


// 関数のプロトタイプ宣言
void drawField();				//ゲーム画面を描画する
void cursor(int x, int y);		//カーソル位置を変更する	
void color(int col);			//文字の色を変更する
void eraseBlock();
void drawBlock();
void spawnBlock();				//ブロックを生成する
void move(int x);				//ミノを左右に移動する
void rotate90(Block* block);	//ブロックの配列を90度回転させる
void rotate();					//ミノを回転させる(回転可能かも判定する)
void drop();					//ミノを急速に落下させる
void fall();					//ミノの自然落下処理
void eraseLine();				//ラインがそろったら消去する
bool isGameOver();				//ゲームオーバーチェック(一番上まで詰みあがった時)


//main関数
int main(void) {
	spawnBlock();
	//ゲームループ
	while (1) {
		//毎回ブロックを消去する
		eraseBlock();

		//キー入力、プレイヤーの移動
		int key = 0;
		if (kbhit())key = getch();
		//下まで落下させる
		if (key == KEY_DOWN) drop();
		//移動左
		if (key == KEY_LEFT) move(-1);
		//移動右
		if (key == KEY_RIGHT) move(1);
		//回転
		if (key == KEY_SPACE) rotate();

		//ブロックをフィールドに書込む
		drawBlock();

		//ミノを自然落下させる
		fall();
		//マップの更新
		drawField();

		//待機する
		Sleep(50);

		//ゲームオーバー処理
		if (isGameOver()) {
			Sleep(1000);
			return 0;
		}
	}
}

//ゲーム画面を描く関数
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

//カーソル位置を指定する関数
void cursor(int x, int y) {
	printf("\x1b[%d;%dH", y + 1, x + 1);
}

//文字や文字列の色を指定する関数
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

//ブロックをランダムに生成する
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

//ミノを左右に移動する
void move(int x) {

}

//ブロックの配列を90度回転させる
void rotate90(Block* block) {
	int size = block->size;
	int temp[4][4];
	
	//tempに縦横入れ替えて格納する
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			temp[j][size - 1 - i] = block->shape[i][j];
		}
	}
	//回転後のブロックを元のブロックにコピーする
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			block->shape[i][j] = temp[i][j];
		}
	}

}


//ミノを回転させる
void rotate() {
	//Block temp = currentBlock;
	rotate90(&currentBlock);
}

//ミノを急速に落下させる
void drop() {

}

//ミノの自然落下処理
void fall() {

}

//ラインがそろったら消去する
void eraseLine() {

}

//ゲームオーバーチェック(一番上まで詰みあがった時)
bool isGameOver() {
	return FALSE;
}