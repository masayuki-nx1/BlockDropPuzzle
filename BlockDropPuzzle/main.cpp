#define _CRT_NONSTDC_NO_WARNINGS	//kbhit(), getch()を使用するための記述
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_SPACE 32

#include<stdio.h>
#include<conio.h>		//キー入力用
#include<Windows.h>		//sleep()を使うため

//色の定義
enum { BLACK, RED, GREEN, YELLOW, MAGENTA, CYAN, WHITE };

//
#define HEIGHT 22
#define WIDTH 13	//\0(終端文字)を含めるので12＋1＝13
//#:壁、@:ブロック
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

// 関数のプロトタイプ宣言
void drawField();				//ゲーム画面を描画する
void cursor(int x, int y);		//カーソル位置を変更する	
void color(int col);			//文字の色を変更する
void move(int x);				//ミノを左右に移動する
void rotate();					//ミノを回転させる
void drop();					//ミノを急速に落下させる
void fall();					//ミノの自然落下処理
void eraseLine();				//ラインがそろったら消去する
bool isGameOver();				//ゲームオーバーチェック(一番上まで詰みあがった時)


//main関数
int main(void) {

	//ゲームループ
	while (1) {

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

//カーソル位置を指定する関数
void cursor(int x, int y) {
	printf("\x1b[%d;%dH", y + 1, x + 1);
}

//文字や文字列の色を指定する関数
void color(int col) {
	printf("\x1b[3%dm", col);
}

//ミノを左右に移動する
void move(int x) {

}

//ミノを回転させる
void rotate() {

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