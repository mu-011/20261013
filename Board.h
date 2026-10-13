#pragma once
#include <iostream>

//盤面サイズ（9×9）
const int SIZE = 9;

//石の種類
enum Stone
{
	EMPTY,  //空
	BLACK,  //黒
	WHITE	//白
};

class Board
{
private:
	Stone board[SIZE][SIZE];  //盤面

public:
	Board();  //初期化
	void printf() const;  //盤面表示

	//石を置く
	bool placeStone(int x, int y, Stone color);

	//呼吸点チェック
	bool hasLiberty(int x, int y, Stone color, bool visited[SIZE][SIZE]);

	//グループ除去（呼吸点ゼロの石を取る）
	void removeGroup(int x, int y, Stone color);

	//盤面外チェック
	bool inBounds(int x, int y)const;
};
