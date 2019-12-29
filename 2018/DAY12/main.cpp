#include <bits/stdc++.h>

int state2num(std::string str) {
    int ret = 0;
    for(int i = 0; i < 5; ++i) {
        ret += (str[i] == '#' ? (1 << i) : 0); 
    }
    return ret;
}

int part1(std::string &initstate_str, std::vector<char> &change) {
    const int STEP = 20;
    int pos = STEP + 5;
    std::string currState = initstate_str;
    std::string nextState;
    currState = std::string(pos, '.') + currState + std::string(pos, '.');
    // std::cout << 0 << "\t: " << currState << "\n";
    for(int step = 0; step < STEP; ++step) {
        nextState = currState;
        for(int i = 0; i <= (int)currState.size() - 5; ++i) {
            nextState[i + 2] = change[state2num(currState.substr(i, 5))];
        }
        currState = nextState;
        // std::cout << step + 1 << "\t: " << currState << "\n";
    }
    int ans = 0;
    for(int i = 0; i < (int)currState.size(); ++i) {
        if(currState[i] == '#') {
            ans += i - pos;
        }
    }
    return ans;
}

long long part2(std::string &initstate_str, std::vector<char> &change) {
    const long long STEP = 50000000000LL;
    const long long IDLE_STEP = 250;
    int pos = IDLE_STEP + 5;
    std::string currState = initstate_str;
    std::string nextState;
    currState = std::string(pos, '.') + currState + std::string(pos, '.');
    for(int step = 0; step < IDLE_STEP; ++step) {
        nextState = currState;
        for(int i = 0; i <= (int)currState.size() - 5; ++i) {
            nextState[i + 2] = change[state2num(currState.substr(i, 5))];
        }
        currState = nextState;
    }
    long long ans = 0, cnt = 0;
    for(int i = 0; i < (int)currState.size(); ++i) {
        if(currState[i] == '#') {
            ans += i - pos;
            cnt++;
        }
    }
    std::cout << ans << " " << cnt << " ";
    return ans + cnt * (STEP - IDLE_STEP);
}

int main() {
    // read input;
    std::string initstate_str, condition_str;
    std::getline(std::cin, initstate_str);
    initstate_str = initstate_str.substr(15);
    std::getline(std::cin, condition_str);
    std::vector<char> change(1 << 5, '.');
    while(std::getline(std::cin, condition_str)) {
        change[state2num(condition_str.substr(0, 5))] = condition_str[9];
    }
    
    // part 1
    std::cout << "the answer of part 1 is ";
    std::cout << part1(initstate_str, change) << std::endl;
    
    // part 2
    std::cout << "the answer of part 2 is ";
    std::cout << part2(initstate_str, change) << std::endl;
}
