#include <bits/stdc++.h>

std::string part1(std::vector<std::vector<int>> &adj) {
    std::vector<int> indegree(26);
    std::vector<bool> appear(26, false);
    for(int u = 0; u < 26; ++u) {
        if(adj[u].empty()) continue;
        appear[u] = true;
        for(auto &v : adj[u]) {
            indegree[v]++;
            appear[v] = true;
        }
    }
    // topology sort
    std::string ret;
    std::priority_queue<int, std::vector<int>, std::greater<int>> Q;
    for(int i = 0; i < 26; ++i) if(indegree[i] == 0) Q.push(i);
    for(int i = 0; i < 26; ++i) {
        int u = Q.top(); Q.pop();
        if(appear[u]) ret.push_back((char)(u + 'A'));
        for(auto &v : adj[u]) {
            if(--indegree[v] == 0) Q.push(v);
        }
    }
    return ret;
}


int part2(std::vector<std::vector<int>> &adj) {
    const int duration = 0;
    const int Nworker = 2;
    std::vector<int> indegree(26);
    std::vector<bool> appear(26, false);
    for(int u = 0; u < 26; ++u) {
        if(adj[u].empty()) continue;
        appear[u] = true;
        for(auto &v : adj[u]) {
            indegree[v]++;
            appear[v] = true;
        }
    }
    // topology sort
    std::priority_queue<int, std::vector<int>, std::greater<int>> Qstep;
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> Qtime;
    Qtime.push(0);
    std::vector<pair<int, int>> worker(5); // {end time, step}
    for(int i = 0; i < 26; ++i) {
        int t = Qtime.top().first; Qtime.pop();
        int numberOfcanWork = 0;
        for(int j = 0; j < 5; ++j) {
            if(worker[j].first <= t) {
                int u = worker[j].second;
                for(auto &v : adj[u]) {
                    if(--indegree[v] == 0) Qstep.push(v);
                }
            }
        }
        for(int j = 0; j < 5; ++j) {
            if(worker[j].first <= t && !Qstep.empty()) {
                int u = Qstep.top(); Qstep.pop();
                worker[j].first = t + u + duration;
            }
        }
        if(!appear[u]) continue;
    }
    int ans = 0;
    for(int i = 0; i < 5; ++i) {
        ans = std::max(ans, worker[i].first);
    }
    return ans;
}

int main() {
    // read input
    std::vector<std::vector<int>> adj(26);
    std::string str;
    while(std::getline(std::cin, str)) {
        int u = str[5] - 'A';
        int v = str[36] - 'A';
        adj[u].push_back(v);
    }
    
    // part1
    std::cout << "the answer of part 1 is ";
    std::cout << part1(adj) << std::endl;
    
    // part2
    // std::cout << "the answer of part 2 is ";
    std::cout << part2(adj) << std::endl;
}
