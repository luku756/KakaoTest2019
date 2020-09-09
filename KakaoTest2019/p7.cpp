#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

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

void fillLine(vector<vector<int>>& board, int x) {

	int n = board.size();
	for (int i = 0; i < n; i++) {

		if (board[i][x] > 0)
			break;

		board[i][x] = -2;

	}


}

int checkrect(vector<vector<int>>& board, int x, int y) {
	int n = board.size();
	int num = board[y][x];

	int numcnt = 0;
	int boxcnt = 0;

	int id_x[4][2] = { {0,2}, {0,2} , {0,1} , {0, 1} };
	int id_y[4][2] = { {-1,0}, {0,1} , {0,2} , {-2,0} };

	for (int t = 0; t < 4; t++) {
		numcnt = 0;
		boxcnt = 0;
		//ooo
		//xoo
		for (int i = id_x[t][0]; i <= id_x[t][1]; i++) {
			for (int j = id_y[t][0]; j <= id_y[t][1]; j++) {
				int newx = i + x, newy = j + y;
				if (0 <= newx && newx < n && 0 <= newy && newy < n) {
					if (board[newy][newx] == num)
						numcnt++;
					if (board[newy][newx] == -2)
						boxcnt++;
				}
			}
		}

		if (boxcnt == 2 && numcnt == 4) {
			//printf("find remove target : %d, num %d\n",t,num);
			//print(board);
			for (int i = id_x[t][0]; i <= id_x[t][1]; i++) {
				for (int j = id_y[t][0]; j <= id_y[t][1]; j++) {
					int newx = i + x, newy = j + y;
					board[newy][newx] = 0;					
				}
			}

			for (int i = id_x[t][0]; i <= id_x[t][1]; i++) {
				fillLine(board,i + x);
			}

			//print(board);
			return 1;
		}
	}

	return 0;

}

int solution(vector<vector<int>> board) {

	//print(board);
	int n = board.size();
	for (int i = 0; i < n; i++) {
		fillLine(board, i);
	}


	//cover(board);
	//print(board);

	int answer = 0;
	int res;
	int ck = -1;

	while (answer != ck) {
		ck = answer;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (board[j][i] > 0) {
					res = checkrect(board, i, j);
					answer += res;
				}
			}
		}
	}


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