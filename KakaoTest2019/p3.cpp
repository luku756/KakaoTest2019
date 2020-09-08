#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

void printPicked(vector<int>& picked) {

	cout << "( ";

	for (int i = 0; i < picked.size(); i++) {
		cout << picked[i] << " ";
	}
	cout << ")" << endl;

	//allcnt++;
}

void pick(int n, vector<int>& picked, int toPick, vector<vector<int>>& selected) {
	//기저 사례 : 더 고를 원소가 없을 때 고른 원소들을 출력한다
	if (toPick == 0) {
		vector<int> a;
		for (int i = 0; i < picked.size(); i++)
			a.push_back(picked[i]);
		selected.push_back(a);
		return;
	}

	//고를 수 있는 가장 작은 번호를 계산한다. 
	//picked가 비어있다면(처음이면) 0이지만, 아니라면 마지막 원소보다 커야 한다.
	int smallest = picked.empty() ? 0 : picked.back() + 1;

	//이 단계에서 원소 하나를 고른다
	for (int next = smallest; next < n; next++) {
		picked.push_back(next);
		pick(n, picked, toPick - 1, selected);
		picked.pop_back();
	}
}

bool check(vector<vector<string>> relation, vector<int> targetList) {

	if (targetList.size() == 0)
		return false;

	vector<string> total;


	for (int i = 0; i < relation.size(); i++) {
		total.push_back("");
		for (int j = 0; j < targetList.size(); j++) {
			total[i] += relation[i][targetList[j]];
		}
	}

	for (int i = 0; i < relation.size(); i++) {
		for (int j = i+1; j < relation.size(); j++) {
			if (total[i] == total[j] && i != j)
				return false;
		}
	}


	return true;
}

void remove(vector<vector<int>>& selected, int index, vector<int> target) {

	int cnt=0;
	int max = target.size();

	for (int i = index + 1; i < selected.size(); i++) {

		if (selected[i].size() > max) {

			cnt = 0;
			for (int p = 0; p < max; p++) {

				for (int q = 0; q < selected[i].size(); q++) {
					if (target[p] == selected[i][q]) {
						cnt++;
						break;
					}
				}

			}

			if (cnt == max) {

				selected[i].clear();
			}


		}

	}

}

int solution(vector<vector<string>> relation) {
	int answer = 0;

	int colsize = relation[0].size();
	int rowsize = relation.size();
	vector<vector<int>> selected;
	vector<int> picked;

	//모든 경우의 수 찾기
	for (int max = 0; max < colsize; max++) {
		pick(colsize, picked, max + 1, selected);
	}

	

	for (int i = 0; i < selected.size(); i++) {
		if (check(relation, selected[i])) {
			remove(selected, i, selected[i]);
			answer++;
		}
	}

	return answer;
}

int main() {

	string input[6][4] = {{ "100", "ryan", "music", "2" }, { "200", "apeach", "math", "2" }, { "300", "tube", "computer", "3" },
	{ "400", "con", "computer", "4" }, { "500", "muzi", "music", "3" }, { "600", "apeach", "music", "2" }};

	vector<vector<string>> relation;

	for (int i = 0; i < 6; i++) {
		vector<string> a;
		for (int j = 0; j < 4; j++) {
			a.push_back(input[i][j]);
		}
		relation.push_back(a);
	}

	int res = solution(relation);
	printf("%d\n", res);



}