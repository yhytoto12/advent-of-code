#include <bits/stdc++.h>

void part12(std::vector<std::pair<int, int>> &pos, std::vector<std::pair<int, int>> &vel, int t) {
    int N = pos.size();
    const int MAXGRID = 350;
    char A[MAXGRID][MAXGRID] = {' '};
    for(int k = 0; k < N; ++k) {
        int x = pos[k].first + vel[k].first * t;
        int y = pos[k].second + vel[k].second * t;
        if(x >= 0 && x < MAXGRID && y >= 0 && y < MAXGRID) A[x][y] = '#';
    }
    std::cout << t << " time after : \n";
    for(int i = 0; i < MAXGRID; ++i) {
        for(int j = 0; j < MAXGRID; ++j) {
            std::cout << A[j][i];
        }
        std::cout << std::endl;
    }
}

int main() {
	// read input
	std::string str;
	std::vector<std::pair<int, int>> pos;
	std::vector<std::pair<int, int>> vel;
	while(std::getline(std::cin, str)) {
		pos.push_back({stoi(str.substr(10, 6)), stoi(str.substr(18, 6))});
		vel.push_back({stoi(str.substr(36, 2)), stoi(str.substr(40, 2))});
	}
	
	// part1
	std::cout << "=========== PART 1 & 2 ===========\n";
	part12(pos, vel, 10054);
}
