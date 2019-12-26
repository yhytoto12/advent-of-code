#include<bits/stdc++.h>

int main() {
    // read input
    std::vector<std::string> candidates;
    std::string strbuf;
    while(std::getline(std::cin, strbuf)) {
        candidates.push_back(strbuf);
    }
    
    // part 1
    int numberOf2 = 0;
    int numberOf3 = 0;
    for(auto &str : candidates) {
        std::vector<int> cnt(26);
        for(char &ch : str) cnt[ch - 'a']++;
        int add2 = 0, add3 = 0;
        for(int i = 0; i < 26; ++i) {
            if(cnt[i] == 2) add2 = 1;
            if(cnt[i] == 3) add3 = 1;
        }
        numberOf2 += add2;
        numberOf3 += add3;
    }
    std::cout << "the answer of part 1 is ";
    std::cout << numberOf2 * numberOf3 << std::endl;
    
    // part 2
    int n = candidates.size();
    int m = candidates[0].size();
    std::pair<int, int> correctBox = {-1, -1};
    int minDiff = m + 1;
    for(int i = 0; i < n; ++i) {
        for(int j = i + 1; j < n; ++j) {
            // calculate differece between can[i], can[j]
            int diff = 0;
            for(int k = 0; k < m; ++k) {
                if(candidates[i][k] != candidates[j][k]) diff++;
            }
            if(diff < minDiff) {
                minDiff = diff;
                correctBox = {i, j};
            }
        }
    }
    std::cout << "the answer of part 2 is ";
    for(int k = 0; k < m; ++k) {
        if(candidates[correctBox.first][k] == candidates[correctBox.second][k])
            std::cout << candidates[correctBox.first][k];
    }
    std::cout << std::endl;
}
