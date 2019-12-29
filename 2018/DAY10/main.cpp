#include <bits/stdc++.h>


int main() {
	// read input
	std::string str;
	std::vector<std::pair<int, int>> pos;
	std::vector<std::pair<int, int>> vel;
	while(std::getline(std::cin, str)) {
		pos.push_back({stoi(str.substr(10, 6)), stoi(str.substr(18, 6))});
		vel.push_back({stoi(str.substr(36, 2)), stoi(str.substr(40, 2))});
	}
	int N = pos.size();
	const int OFFSET = 10000;
	for(int i = 0; i < N; ++i) {
		pos[i].first += vel[i].first * OFFSET;
		pos[i].second += vel[i].second * OFFSET;
	}
	for(auto &p : pos) { 
		std::cout << p.first << " " << p.second << "\n";
	}
}
