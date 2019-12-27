#include<bits/stdc++.h>

struct Claim {
    int id;
    int px, py;
    int sx, sy;
};

int main() {
    // read input
    std::vector<Claim> claims;
    std::string str;
    while(std::getline(std::cin, str)) {
        int _1 = 0;
        int _2 = str.find('@', _1);
        int _3 = str.find(',', _2);
        int _4 = str.find(':', _3);
        int _5 = str.find('x', _4);
        Claim clm;
        clm.id = std::stoi(str.substr(_1 + 1, _2 - _1 - 2));
        clm.px = std::stoi(str.substr(_2 + 2, _3 - _2 - 2));
        clm.py = std::stoi(str.substr(_3 + 1, _4 - _3 - 1));
        clm.sx = std::stoi(str.substr(_4 + 2, _5 - _4 - 2));
        clm.sy = std::stoi(str.substr(_5 + 1));
        claims.push_back(clm);
    }
    int n = claims.size();
    
    // part1
    int Xmax = 0, Ymax = 0;
    for(auto &clm : claims) {
        Xmax = std::max(Xmax, clm.px + clm.sx);
        Ymax = std::max(Ymax, clm.py + clm.sy);
    }
    std::vector<std::vector<int>> numberOfClaimed(Xmax, std::vector<int>(Ymax, 0));
    for(auto &clm : claims) {
        for(int x = 0; x < clm.sx; ++x) {
            for(int y = 0; y < clm.sy; ++y) {
                numberOfClaimed[clm.px + x][clm.py + y]++;        
            }
        }
    }
    int cnt = 0;
    for(int x = 0; x < Xmax; ++x) {
        for(int y = 0; y < Ymax; ++y) {
            if(numberOfClaimed[x][y] >= 2) ++cnt;
        }
    }
    std::cout << "the answer of part 1 is ";
    std::cout << cnt << std::endl;
    
    // part2
    std::vector<int> ans;
    for(auto &clm : claims) {
        bool notOverlap = true;
        for(int i = 0; i < clm.sx; ++i) {
            for(int j = 0; j < clm.sy; ++j) {
                if(numberOfClaimed[clm.px + i][clm.py + j] != 1) notOverlap = false;
            }
        }
        if(notOverlap) ans.push_back(clm.id);
    }
    std::cout << "the answer of part 2 is ";
    for(auto &x : ans) std::cout << x << " ";
    std::cout << std::endl; 
}
