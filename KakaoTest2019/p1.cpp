#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>

using namespace std;

typedef struct st {
	string id;
	int type;//0 µé¾î 1³ª°¬
};

vector<string> solution(vector<string> record) {
	vector<st> log;
	vector<string> answer;
	map<string, string> name;
	string buf[3];
	char op[10], id[20], nickname[20];

	for (int i = 0; i < record.size(); i++) {
		istringstream ss(record[i]);
		int cnt = 0;
		while (getline(ss, buf[cnt], ' '))
		{
			cnt++;
		}

		if (buf[0] == "Enter") {
			st a;
			a.id = buf[1];
			a.type = 0;
			log.push_back(a);
			name[buf[1]] = buf[2];
		}

		else if (buf[0] == "Leave") {
			st a;
			a.id = buf[1];
			a.type = 1;
			log.push_back(a);
		}
		else {
			name[buf[1]] = buf[2];

		}


	}

	for (int i = 0; i < log.size(); i++) {
		if (log[i].type == 0) {
			answer.push_back(name[log[i].id] + "´ÔÀÌ µé¾î¿Ô½À´Ï´Ù.");
		}
		else if (log[i].type ==1) {
			answer.push_back(name[log[i].id] + "´ÔÀÌ ³ª°¬½À´Ï´Ù.");
		}

	}

	return answer;
}

int main() {

	string input[] = { "Enter uid1234 Muzi", "Enter uid4567 Prodo","Leave uid1234","Enter uid1234 Prodo","Change uid4567 Ryan" };
	vector<string> record;
	
	for (int i = 0; i < 5; i++) {
		record.push_back(input[i]);
	}

	vector<string> res = solution(record);

	for (int i = 0; i < res.size(); i++) {
		printf("%s\n",res[i].c_str());
	}

}