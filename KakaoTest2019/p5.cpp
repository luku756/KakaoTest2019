#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

typedef struct node {

	int x, y;
	int num;
	node* parent;
	node* left;
	node* right;
};

vector<node*> levels[1002];

bool check_right(node* target, node* me) {
	//모든 조상을 보고, 그 x값이 나보다 작은지 확인.


}
bool check_left(node* target, node* me) {
	//모든 조상을 보고, 그 x값이 나보다 큰지 확인.


}

vector<vector<int>> solution(vector<vector<int>> nodeinfo) {
	vector<vector<int>> answer;

	vector<node> tree;

	int maxlv = 0;
	int N = nodeinfo.size();

	for (int i = 0; i < nodeinfo.size(); i++) {
		node n;
		n.left = NULL; n.right = NULL;
		n.num = i + 1;
		n.x = nodeinfo[i][0]; n.y = nodeinfo[i][1];
		if (maxlv < n.y)
			maxlv = n.y;

		tree.push_back(n);
	}



	for (int i = 0; i < N; i++) {
		for (int j = i; j < N; j++) {
			if (tree[i].y < tree[j].y) {
				node tmp = tree[i];
				tree[i] = tree[j];
				tree[j] = tmp;

			}
			else if (tree[i].y == tree[j].y && tree[i].x < tree[j].x) {
				node tmp = tree[i];
				tree[i] = tree[j];
				tree[j] = tmp;

			}
		}
	}

	node* top = &tree[0];
	int nowlevel = tree[0].y;
	int nowlevelcnt=0;
	levels[nowlevelcnt].push_back(&tree[0]);

	for (int i = 1; i < tree.size(); i++) {
		int lv = tree[i].y;
		if (nowlevel != lv) {
			nowlevelcnt++;
			nowlevel = lv;
		}

		int prelv = nowlevelcnt-1;

		int j;
		for ( j = 0; j < levels[prelv].size()-1; j++) {
			if (levels[prelv][j]->x > tree[i].x) {
				levels[prelv][j]->left = &tree[i];
			}

			if (levels[prelv][j]->x < tree[i].x && levels[prelv][j + 1]->x > tree[i].x) {

			}
		}

	}


	for (int lv = maxlv; lv >= 1; lv--) {



	}

	return answer;
}

int main() {

	int input[9][2] = {{5, 3}, {11, 5}, {13, 3}, {3, 5}, {6, 1}, {1, 3}, {8, 6}, {7, 2}, {2, 2}};

	vector<vector<int>> nodeinfo;

	for (int i = 0; i < 9; i++) {
		vector<int> a;
		for (int j = 0; j < 2; j++) {
			a.push_back(input[i][j]);
		}
		nodeinfo.push_back(a);
	}

	vector<vector<int>> res = solution(nodeinfo);


	for (int i = 0; i < res.size(); i++) {
		for (int j = 0; j < res[i].size(); j++) {
			printf("%d ", res[i][j]);
		}
		printf("\n");
	}




}