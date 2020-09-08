#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;
int checktype(int x, int y, vector<vector<int>>& board);

int block[203];
int find(vector<vector<int>> board) {
	int x, y;
	int n = board.size();
	int res;
	int cnt=0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (board[j][i] > 0 && block[board[j][i]] == 0) {
				
				if (cnt < board[j][i])
					cnt = board[j][i];
				x = i; y = j;
				checktype(x, y, board);
				//return;
			}
		}		
	}

	return cnt;
}

int check(int x, int y, int n, vector<vector<int>>& board) {

	if (!(0 <= x && x < n && 0 <= y && y < n )) {
		return -1;
	}

	return board[y][x];
}

void print(vector<vector<int>> board) {

	printf("----------------------------\n");
	int n = board.size();
	for (int i = 0; i < n; i++) {
		int cnt = 0;
		for (int j = 0; j < n; j++) {
			printf("%2d ", board[i][j]);
		}
		printf("\n");
	}


}


int checktype(int x, int y, vector<vector<int>>& board) {

	int num = board[y][x];
	int n = board.size();

	//1-3
	if (check(x, y + 1, n, board) == num && check(x + 1, y + 1, n, board) == num && check(x + 2, y + 1, n, board) == num) {
		block[num] = 130000 + x*100+y;
		return block[num];
	}

	//1-4
	if (check(x+1, y , n, board) == num && check(x + 1, y - 1, n, board) == num && check(x + 1, y - 2, n, board) == num) {
		block[num] = 140000 + x * 100 + y;
		return block[num];
	}

	//2-2
	if (check(x , y+1, n, board) == num && check(x , y +2, n, board) == num && check(x + 1, y + 2, n, board) == num) {
		block[num] = 220000 + x * 100 + y;
		return block[num];
	}
	//2-3
	if (check(x+1, y , n, board) == num && check(x+2, y, n, board) == num && check(x + 2, y -1, n, board) == num) {
		block[num] = 230000 + x * 100 + y;
		return block[num];
	}
	//3-1
	if (check(x + 1, y, n, board) == num && check(x + 1, y-1, n, board) == num && check(x + 2, y , n, board) == num) {
		block[num] = 310000 + x * 100 + y;
		return block[num];
	}

	block[num] = -1;
	return block[num];

}

bool checkremove(vector<vector<int>>& board) {
	int x, y;
	//find(x,y,board);
	int n = board.size();

	int hole = -2;

	int num;

	int newx, newy;

	for (int i = 0; i < n; i++) {
		int cnt = 0;
		for (int j = 0; j < n; j++) {
			if (board[j][i] > 0 ) {
				x = i; y = j;

				//하나 발견
				num = board[y][x];

				newx = x; newy = y + 1;
				if (check(newx, newy, n, board) == num) {//아래가 동일
					//1-3, 2-2

					int newx2, newy2;
					//2-2
					newx2 = newx; newy2 = newy + 1;
					if (check(newx2, newy2, n, board) == num) {//아래가 동일
						int newx3 = newx2 + 1, newy3 = newy2;
						if (check(newx3, newy3, n, board) == num) {//확정
							//printf("%d 2-2\n",num);

							int ckx = x + 1, cky = y, ckx2 = x + 1, cky2 = y + 1;
							if (check(ckx, cky, n, board) == hole && check(ckx2, cky2, n, board) == hole) {
								board[y][x] = hole;
								board[newy][newx] = 0;
								board[newy2][newx2] = 0;
								board[newy3][newx3] = 0;
								return true;
							}

						}

					}
					//1-3
					newx2 = newx + 1; newy2 = newy;
					if (check(newx2, newy2, n, board) == num) {//오른쪽 동일

						int newx3 = newx2 + 1, newy3 = newy2;
						if (check(newx3, newy3, n, board) == num) {
							//printf("%d 1-3\n",num);

							int ckx = x + 1, cky = y, ckx2 = x + 2, cky2 = y;
							if (check(ckx, cky, n, board) == hole && check(ckx2, cky2, n, board) == hole) {
								board[y][x] = 0;
								board[newy][newx] = 0;
								board[newy2][newx2] = 0;
								board[newy3][newx3] = 0;
								return true;
							}


						}

					}

				}
				else {

					newx = x + 1; newy = y;
					if (check(newx, newy, n, board) == num) {//우측 동일
						//1-4, 2-3,3-1

						int newx2 = newx, newy2 = newy - 1;//위로
						if (check(newx2, newy2, n, board) == num) {//1-4,3-1

							int newx3 = newx2, newy3 = newy2 - 1;//위로, 1-4
							if (check(newx3, newy3, n, board) == num) {
								//printf("%d 1-4\n",num);
								int ckx = x, cky = y - 1, ckx2 = x, cky2 = y - 2;
								if (check(ckx, cky, n, board) == hole && check(ckx2, cky2, n, board) == hole) {
									board[y][x] = 0;
									board[newy][newx] = 0;
									board[newy2][newx2] = 0;
									board[newy3][newx3] = 0;
									return true;
								}

							}

							newx3 = newx2 + 1, newy3 = newy2 + 1;//우하, 3-1
							if (check(newx3, newy3, n, board) == num) {
								//printf("%d 3-1\n",num);
								int ckx = x, cky = y - 1, ckx2 = x + 2, cky2 = y - 1;
								if (check(ckx, cky, n, board) == hole && check(ckx2, cky2, n, board) == hole) {
									board[y][x] = 0;
									board[newy][newx] = 0;
									board[newy2][newx2] = 0;
									board[newy3][newx3] = 0;
									return true;
								}

							}


						}

						else {
							newx2 = newx + 1, newy2 = newy;//2-3
							if (check(newx2, newy2, n, board) == num) {
								int newx3 = newx2, newy3 = newy2 - 1;
								if (check(newx3, newy3, n, board) == num) {
									//printf("%d 2-3\n",num);
									int ckx = x, cky = y - 1, ckx2 = x + 1, cky2 = y - 1;
									if (check(ckx, cky, n, board) == hole && check(ckx2, cky2, n, board) == hole) {
										board[y][x] = 0;
										board[newy][newx] = 0;
										board[newy2][newx2] = 0;
										board[newy3][newx3] = 0;
										return true;
									}
								}

							}
						}

					}

				}


				
			}
		}
	}

	return false;

/*

	for (int i = 0; i < n; i++) {
		int cnt = 0;
		for (int j = 0; j < n; j++) {
			if (board[j][i] != 0) {
				x = i; y = j;
				cnt = j;
				break;
			}
		}
		if (cnt == 0)
			cnt = n;
		for (int j = 0; j < cnt; j++) {
			board[j][i] = 9;
		}
	}*/


}

void cover(vector<vector<int>>& board) {
	int n = board.size();
	for (int i = 0; i < n; i++) {
		int cnt = 0;
		for (int j = 0; j < n; j++) {
			if (board[j][i] > 0) {
				cnt = j;
				break;
			}
		}
		if (cnt == 0)
			cnt = n;
		for (int j = 0; j < cnt; j++) {
			board[j][i] = -2;
		}
	}



}

bool rmcheck(vector<vector<int>>& board, int x, int y) {
	int n = board.size();
	for (int i = y - 1; i >= 0; i--) {
		if (board[i][x] != 0)
			return false;
	}

	return true;

}

int remove(vector<vector<int>>& board, int num) {
	int id = num / 10000;
	num = num % 10000;
	int x = num / 100;
	int y = num % 100;

	switch (id) {
	case 13:
		if (rmcheck(board, x + 1, y) && rmcheck(board, x + 2, y)) {
			board[y][x] = 0;
			board[y + 1][x] = 0;
			board[y + 1][x+1] = 0;
			board[y + 1][x+2] = 0;
			return 1;
		}

		break;
	case 14:
		if (rmcheck(board, x , y-1) && rmcheck(board, x , y-2)) {
			board[y][x] = 0;
			board[y ][x+1] = 0;
			board[y - 1][x + 1] = 0;
			board[y -2][x + 1] = 0;
			return 1;
		}

		break;
	case 22:
		if (rmcheck(board, x+1, y) && rmcheck(board, x+1, y +1)) {
			board[y][x] = 0;
			board[y+1][x] = 0;
			board[y +2][x] = 0;
			board[y + 2][x + 1] = 0;
			return 1;
		}

		break;
	case 23:
		if (rmcheck(board, x, y-1) && rmcheck(board, x + 1, y - 1)) {
			board[y][x] = 0;
			board[y ][x+1] = 0;
			board[y][x+2] = 0;
			board[y -1][x + 2] = 0;
			return 1;
		}

		break;
	case 31 :
		if (rmcheck(board, x, y - 1) && rmcheck(board, x + 2, y - 1)) {
			board[y][x] = 0;
			board[y][x + 1] = 0;
			board[y-1][x + 1] = 0;
			board[y][x + 2] = 0;
			return 1;
		}

		break;


	}

	return -1;
}

int solution(vector<vector<int>> board) {
	int answer = 0;

	for (int i = 0; i < 202; i++)
		block[i] = 0;

	int r = find(board);
	int deleteable = 0;
	for (int i = 1; i <= r; i++)
	{
		if (block[i] > 0)
			deleteable++;

	}

	int cnt = 0;
	int res;
	int rmcnt = 0;
	//print(board);


	while (1) {
		if (block[cnt] > 0) {
			res = remove(board, block[cnt]);
			if (res > 0) {//삭제됨
				//printf("rm cnt %d\n",cnt);
				//print(board);
				block[cnt] = -2;
				rmcnt++;
				cnt = 0;
				continue;
			}

		}
		cnt++;

		if (cnt > r)
			break;

	}

	return rmcnt;

	//cover(board);

	//print(board);


	while (1) {
		bool ck = checkremove(board);
		if (ck) {
			//print(board);
			cover(board);
			//print(board);
			answer++;
		}
		else
			break;

	}

	//printf("\n");
	//printf("\n");
	//cover(board);


	//for (int i = 0; i < n; i++) {
	//	int cnt = 0;
	//	for (int j = 0; j < n; j++) {
	//		printf("%d ", board[i][j]);
	//	}
	//	printf("\n");
	//}

	return answer;
}

int main() {

	//int input[10][10] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 4, 0, 0, 0}, {0, 0, 0, 0, 0, 4, 4, 0, 0, 0}, {0, 0, 0, 0, 3, 0, 4, 0, 0, 0}, {0, 0, 0, 2, 3, 0, 0, 0, 5, 5}, {1, 2, 2, 2, 3, 3, 0, 0, 0, 5}, {1, 1, 1, 0, 0, 0, 0, 0, 0, 5}};
	int input[10][10] = { 
	{0, 0, 0, 0, 0, 0, 0, 9, 0, 0}, 
	{10, 0, 0, 0, 0, 0, 9, 9, 9, 0}, 
	{10, 10, 10, 0, 0, 0, 0, 0, 0, 0}, 
	{0, 8, 0, 6, 0, 0, 0, 0, 0, 0}, 
	{8, 8, 8, 6, 0, 0, 4, 0, 0, 0}, 
	{0, 7, 0, 6, 6, 4, 4, 0, 0, 0}, 
	{0, 7, 7, 7, 3, 0, 4, 0, 0, 0}, 
	{0, 0, 0, 2, 3, 0, 0, 0, 5, 5}, 
	{1, 2, 2, 2, 3, 3, 0, 0, 0, 5}, 
	{1, 1, 1, 0, 0, 0, 0, 0, 0, 5} };

	//int input[5][5] = {{0, 0, 0, 0, 0}, {1, 0, 0, 2, 0}, {1, 2, 2, 2, 0}, {1, 1, 0, 0, 0}, {0, 0, 0, 0, 0}};

	int N = 10;	vector<vector<int>> board;

	for (int i = 0; i < N; i++) {
		vector<int> a;
		for (int j = 0; j < N; j++) {
			a.push_back(input[i][j]);
		}
		board.push_back(a);
	}

	int res = solution(board);
	printf("%d\n", res);



}