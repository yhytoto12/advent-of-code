#include<bits/stdc++.h>

int part1(std::string &str) {
    std::list<char> A;
    for(auto &ch : str) A.push_back(ch);
    auto it = A.begin();
    while(it != A.end()) {
        char i1 = *it++;
        if(it == A.end()) break;
        char i2 = *it--;
        if(abs(i1 - i2) == abs('A' - 'a')) {
            it = A.erase(it);
            it = A.erase(it);
            if(it != A.begin()) --it;
        } else {
            ++it;
        }
    }
    return A.size();
}

int part2(std::string &str) {
    int ans = INT_MAX;
    for(int i = 0; i < 26; ++i) {
        std::string newStr;
        for(auto &ch : str) if(ch != 'a' + i && ch != 'A' + i) newStr.push_back(ch);
        std::list<char> A;
        for(auto &ch : newStr) A.push_back(ch);
        auto it = A.begin();
        while(it != A.end()) {
            char i1 = *it++;
            if(it == A.end()) break;
            char i2 = *it--;
            if(abs(i1 - i2) == abs('A' - 'a')) {
                it = A.erase(it);
                it = A.erase(it);
                if(it != A.begin()) --it;
            } else {
                ++it;
            }
        }
        ans = std::min(ans, (int)A.size());
    }
    return ans;
}

int main() {
    // read input
    std::string str;
    std::cin >> str;
    
    // part 1
    std::cout << "the answer of part 1 is ";
    std::cout << part1(str) << std::endl;
    
    // part 2
    std::cout << "the answer of part 2 is ";
    std::cout << part2(str) << std::endl;
}
