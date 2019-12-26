#include<bits/stdc++.h>

int main() {
    // read input
    std::vector<int> changeFq;
    int val;
    while(std::cin >> val) {
        changeFq.push_back(val);
    }
    
    // part 1
    int currFq = 0;
    for(int &diff : changeFq) currFq += diff;
    std::cout << "the answer of part 1 is ";
    std::cout << currFq << std::endl;
    
    // part 2
    currFq = 0;
    int idx = 0;
    int n = changeFq.size();
    std::set<int> appear;
    while(true) {
        if(appear.find(currFq) == appear.end()) appear.insert(currFq);
        else break;
        currFq += changeFq[idx];
        idx = (idx + 1) % n;
    }
    std::cout << "the answer of part 2 is ";
    std::cout << currFq << std::endl;
}
