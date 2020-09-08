#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

int visit[600];
int stop[600];
float score[600];

vector<int> solution(int N, vector<int> stages) {
	vector<int> answer;
	vector<float> score;
	vector<int> index;

	for (int i = 0; i <= N; i++) {
		visit[i] = 0;
		stop[i] = 0;
	}

	for (int i = 0; i < stages.size(); i++) {

		for (int j = 1; j <= stages[i]; j++)
		{
			visit[j]++;
		}
		stop[stages[i]]++;
	}

	score.resize(N);
	index.resize(N);
	for (int i = 1; i <= N; i++) {
		score[i-1] = (float)stop[i] / (float)visit[i];
		index[i - 1] = i;
	}


	for (int i = 0; i < N; i++) {
		for (int j = i; j < N; j++) {
			if (score[i] < score[j]) {
				float tmp = score[i];
				score[i] = score[j];
				score[j] = tmp;

				int it = index[i];
				index[i] = index[j];
				index[j] = it;
			}
			else if (score[i] == score[j] && index[i] > index[j]) {
				float tmp = score[i];
				score[i] = score[j];
				score[j] = tmp;

				int it = index[i];
				index[i] = index[j];
				index[j] = it;

			}
		}
	}


	return index;
}

int main() {
	
	int n = 4;
	int input[] = {4,4,4,4,4};
	vector<int> stages;

	for (int i = 0; i < 5; i++) {
		stages.push_back(input[i]);
	}

	vector<int> res = solution(n, stages);

	for (int i = 0; i < res.size(); i++) {
		printf("%d\n", res[i]);
	}

}