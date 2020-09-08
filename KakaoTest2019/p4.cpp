#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <queue>

using namespace std;

class food {
public:
	food(int stime, int sindex) : time(stime), index(sindex) {}
	int time, index;
	
	bool operator > (const food& rhs) const { return time  > rhs.time ; }
	
};


int solution(vector<int> food_times, long long k) {
	long long answer = 0;
	long long fsize = food_times.size();

	long long sum=0;
	for (int i = 0; i < fsize; i++) {
		sum += food_times[i];
	}

	if (sum <= k)
		return -1;

	priority_queue<food, vector<food>, greater<food> > q;

	priority_queue<int, vector<int>, greater<int>> clear[2];

	for (int i = 0; i < fsize; i++) {
		food f(food_times[i],i+1);
		q.push(f);
	}

	long long len = fsize;
	long long ate=0;

	while (k >= len) {

		food f = q.top();
		q.pop();
		f.time = f.time - ate;
		if (f.time == 0) {
			//먹은것
			clear[0].push(f.index);
			len--;

		}
		else {
			long long eat = f.time;
			if (k >= eat * len) {

				k -= eat * len;
				ate += eat;
				len--;
				clear[0].push(f.index);
			}
			else {
				k = k % len;
			}

		}


		if (q.empty()) {
			if(k>0)
				return -1;
			else {
				if (clear[0].size() < fsize)
					return f.index;
				else
					return -1;
			}
		}
		if (k < len) {
			break;

		}
	}

	//남은 음식중에 다먹은거 있는지 확인
	while (!q.empty()) {
		food f = q.top();
		q.pop();
		if (f.time <= ate)
			clear[0].push(f.index);
	}

	if (clear[0].size() == fsize)
		return -1;

	long long index = k+1;

	int ind = 0;
	while (1)
	{


		int clearesize = clear[ind].size();
		while (clearesize--) {
			int qt = clear[ind].top();
			clear[ind].pop();
			clear[1 - ind].push(qt);
			if (qt <= index) {
				index++;
			}
		}

		if (index > fsize) {
			index -= fsize;
			ind = 1 - ind;
		}
		else
			break;
	}
	return index;
}


int bad_sol(vector<int> food_times, long long k) {

	int max = food_times.size();
	int cnt=0;
	int loopcnt = 0;
	k++;
	while (k--) {
		loopcnt = 0;
		while (food_times[cnt] <= 0) {

			cnt++;
			cnt %= max;
			loopcnt++;
			if (loopcnt >= max)
				return -1;
		}

		if (k == 0) {
			break;
		}

		if (food_times[cnt] > 0) {
			food_times[cnt]--;
		}

		cnt++;
		cnt %= max;

	}

	//for (int i = 0; i < max; i++) {
	//	printf("%d ",food_times[i]);
	//}
	//printf("\n");

	return cnt+1;
}

#include <time.h>
#include <random>

bool test() {
	srand(time(NULL));

	vector<int> food_times;
	for (int i = 0; i < 20; i++) {
		int a = rand()%1000+1;
		food_times.push_back(a);
	}

	for (int i = 0; i < 20000; i++) {

		int res = solution(food_times, i);
		int r = bad_sol(food_times, i);

		if (res != r) {
			printf("errrrrr!!!\n");
			printf("input\n");
			for (int i = 0; i < 20; i++) {
				printf("%d ", food_times[i]);
			}
			printf("\n");

			printf("i : %d\n",i);
			return false;
		}
	}

	return true;
}

int main() {

	//while (1) {
	//	bool t = test();
	//	if (t)
	//		printf("onon\n");
	//	else
	//		break;
	//}

	//return 0;

	//int input[] = { 656, 656, 380 ,447 ,318 ,157 ,417 ,961 ,63, 207 ,560 ,347, 223, 797 ,277 ,730, 820, 46 ,499, 444 };
	//int input[] = { 352	,988,	859	,901,	901,	180,	490,	336,	959,	41 };
	int input[] = {1,1,1,1 };

	vector<int> food_times;
	long long k = 4;
	

	for (int i = 0; i < 4; i++) {
		food_times.push_back(input[i]);
	}

	int res = solution(food_times, k);
	printf("%d\n", res);
	res = bad_sol(food_times, k);
	printf("%d\n", res);

	//for (int i = 1; i <= 25; i++) {

	//	int res = solution(food_times, i);
	//	int r = bad_sol(food_times,i);
	//	if(res != r)
	//	printf("err ! %d - %d / %d\n",i, res,r);
	//	else
	//		printf("coo ! %d - %d / %d\n", i, res, r);

	//}



}