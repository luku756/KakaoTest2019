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
	int answer = 0;
	int fsize = food_times.size();

	priority_queue<food, vector<food>, greater<food> > q;

	priority_queue<int, vector<int>, greater<int>> clear;

	for (int i = 0; i < fsize; i++) {
		food f(food_times[i],i+1);
		q.push(f);
	}

	int len = fsize;
	int ate=0;

	while (k >= len) {

		food f = q.top();
		q.pop();
		f.time = f.time - ate;
		if (f.time == 0) {
			//¸ÔÀº°Í
			clear.push(f.index);
			len--;

		}
		else {
			int eat = f.time;
			if (k >= eat * len) {

				k -= eat * len;
				ate += eat;
				len--;
				clear.push(f.index);
			}
			else {
				k = k % len;
			}

		}


		if (q.empty()) {
			if(k>0)
				return -1;
			else {
				if (clear.size() < fsize)
					return f.index;
				else
					return -1;
			}
		}
		if (k < len) {
			break;

		}
	}

	int index = k+1;

	while (!clear.empty()) {
		int qt = clear.top();
		clear.pop();
		if (qt <= index)
			index++;
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

	return cnt+1;
}

#include <time.h>
#include <random>

bool test() {
	srand(time(NULL));

	vector<int> food_times;
	for (int i = 0; i < 10; i++) {
		int a = rand()%1000;
		food_times.push_back(a);
	}

	for (int i = 0; i < 10000; i++) {

		int res = solution(food_times, i);
		int r = bad_sol(food_times, i);

		if (res != r) {
			printf("errrrrr!!!\n");
			printf("input\n");
			for (int i = 0; i < 10; i++) {
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

	int input[] = { 656, 656, 380 ,447 ,318 ,157 ,417 ,961 ,63, 207 ,560 ,347, 223, 797 ,277 ,730, 820, 46 ,499, 444 };

	vector<int> food_times;
	long long k = 8321;
	

	for (int i = 0; i < 20; i++) {
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