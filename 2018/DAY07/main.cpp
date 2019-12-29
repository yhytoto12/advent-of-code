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

struct Work {
	int step;
	int Tstart, Tend;
	Work(int st, int ts, int te) : step(st), Tstart(ts), Tend(te) {

	}
};

int part2(std::vector<std::vector<int>> &adj) {
    const int duration = 61;
    const int Nworker = 5;
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
    std::priority_queue<int, std::vector<int>, std::greater<int>> Qtime;
    Qtime.push(0);
    std::vector<std::queue<Work>> worker(Nworker);
    for(int i = 0; i < 26; ++i) if(indegree[i] == 0 && appear[i]) Qstep.push(i);
	int t = 0;
    while(!Qtime.empty()) {
    	t = Qtime.top(); Qtime.pop();
    	for(int i = 0; i < Nworker; ++i) {
    		if(!worker[i].empty() && worker[i].front().Tend == t) {
    			Work finishedWork = worker[i].front(); worker[i].pop();
    			for(auto &nextStep : adj[finishedWork.step]) {
    				if(--indegree[nextStep] == 0) Qstep.push(nextStep);
    			}
    		}
    	}
    	for(int i = 0; i < Nworker; ++i) {
    		if(!Qstep.empty() && worker[i].empty()) { // if work exist && worker 'i' can work
    			Work newWork(Qstep.top(), t, t + Qstep.top() + duration);
    			Qstep.pop();
    			worker[i].push(newWork);
    			Qtime.push(newWork.Tend);
    		}
    	}
    }
    return t;
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
    std::cout << "the answer of part 2 is ";
    std::cout << part2(adj) << std::endl;
}
