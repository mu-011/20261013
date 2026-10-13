#include "Board.h"


//初期化
Board::Board()
{
	for (int y = 0; y < SIZE; y++)
	{
		for (int x = 0; x < SIZE; x++)
		{
			board[y][x] = EMPTY;
		}
	}
}

//表示
void Board::printf() const
{
	for (int y = 0; y < SIZE; y++)
	{
		for (int x = 0; x < SIZE; x++)
		{
			if (board[y][x] == EMPTY)
				std::cout << "・";
			else if (board[y][x] == BLACK)
				std::cout << "●";
			else
				std::cout << "〇";
		}

		std::cout << "\n";
	}
}

//盤面外チェック
bool Board::inBounds(int x, int y)const
{
	return(x >= 0 && x < SIZE && y >= 0 && y < SIZE);
}

//呼吸点チェック
bool Board::hasLiberty(int x, int y, Stone color, bool visited[SIZE][SIZE])
{
	//盤面外なら探索不可
	if (!inBounds(x, y)) return false;

	//すでに調べた石ならスキップ
	if (visited[y][x]) return false;

	visited[y][x] = true;  //この石を調べたと記録

	//隣接4方向（上下左右）
	const int dx[4] = { 1, -1, 0, 0 };
	const int dy[4] = { 0, 0, 1, -1 };

	//隣接マスを順番にチェック
	for (int i = 0; i < 4; i++) 
	{
		int nx = x + dx[i];
		int ny = y + dy[i];

		if (!inBounds(nx, ny)) continue;

		//空きがあれば呼吸点あり
		if (board[ny][nx] == EMPTY)
			return true;

		//同じ色ならグループとして再帰探索
		if (board[ny][nx] == color)
			if (hasLiberty(nx, ny, color, visited))
				return true;
	}

	//呼吸点なし
	return false;
}

//グループ除去
void Board::removeGroup(int x, int y, Stone color) 
{
	if (!inBounds(x, y)) return;
	if (board[y][x] != color) return;

	//この石を取り除く
	board[y][x] = EMPTY;

	//隣接方向
	const int dx[4] = { 1, -1, 0, 0 };
	const int dy[4] = { 0, 0, 1, -1 };

	//同じ色の石を再帰的に除去
	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];

		if (inBounds(nx, ny) && board[ny][nx] == color)
			removeGroup(nx, ny, color);
	}
}

//石を置く
bool Board::placeStone(int x, int y, Stone color)
{
	//盤面外
	if (!inBounds(x, y)) return false;

	//すでに石がある
	if (board[y][x] != EMPTY) return false;

	//仮置き
	board[y][x] = color;

	Stone enemy = (color == BLACK ? WHITE : BLACK);

	//隣接方向
	const int dx[4] = { 1, -1, 0, 0 };
	const int dy[4] = { 0, 0, 1, -1 };

	//敵の石の呼吸点チェック
	for (int i = 0; i < 4; i++) 
	{
		int nx = x + dx[i];
		int ny = y + dy[i];

		if (!inBounds(nx, ny)) continue;

		if (board[ny][nx] == enemy) {
			bool visited[SIZE][SIZE] = { false };

			// 敵グループが呼吸点ゼロなら除去
			if (!hasLiberty(nx, ny, enemy, visited)) 
			{
				removeGroup(nx, ny, enemy);
			}
		}
	}

	//自分の呼吸点チェック（自殺手判定）
	{
		bool visited[SIZE][SIZE] = { false };
		if (!hasLiberty(x, y, color, visited)) {
			// 自殺手 → 置けないので戻す
			board[y][x] = EMPTY;
			return false;
		}
	}

	//合法手
	return true;
}
