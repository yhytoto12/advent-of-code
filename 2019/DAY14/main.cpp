#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll, ll> pll;
#define PI 3.14159265358979
#define rep(i, n) for(int i = 0; i < (n); ++i)
#define repp(i, s, e) for(int i = (s); i <= (e); ++i)
#define sz(x) ((int)x.size())
#define all(x) x.begin(), x.end()
#define FAST_IO() ios::sync_with_stdio(0); cin.tie(0)
template<typename T>
ostream& operator<<(ostream &os, const vector<T> &v) { for (auto x : v) os << x << " "; return os << "\n"; }
template<class U, class V>
ostream& operator<<(ostream &os, const pair<U, V> &p) { return os << "(" << p.first << "," << p.second << ")";}

typedef pair<ll, string> Ingredient;
struct Reaction {
    vector<Ingredient> inputs;
    Ingredient output;
};

void getInputs(vector<Reaction> &reactions) {
    string s;
    while(getline(cin, s)) {
        int equalIdx = -1;
        rep(i, sz(s)) {
            if(s[i] == ',') s[i] = ' ';
            if(s[i] == '=') equalIdx = i;
        }
        Reaction react;
        stringstream input_str(s.substr(0, equalIdx - 1));
        stringstream output_str(s.substr(equalIdx + 3));
        string num, name;
        while(input_str >> num >> name) {
            react.inputs.push_back({stoll(num), name});
        }
        while(output_str >> num >> name) {
            react.output = {stoll(num), name};
        }
        reactions.push_back(react);
    }
}

ll part1(vector<Reaction> &reactions) {
    // mapping name -> idx
    map<string, int> mat2idx;
    int numberOfmaterial = 0;
    for(auto &r : reactions) {
        for(auto &p : r.inputs) {
            if(mat2idx.find(p.second) == mat2idx.end()) {
                mat2idx[p.second] = numberOfmaterial++;
            }
        }
        if(mat2idx.find(r.output.second) == mat2idx.end()) {
            mat2idx[r.output.second] = numberOfmaterial++;
        }
    }
    int ORE = mat2idx["ORE"];
    int FUEL = mat2idx["FUEL"];
    // make graph (output -> input)
    vector<vector<pair<int, ll>>> adj(numberOfmaterial);
    vector<ll> coefficient(numberOfmaterial, 1);
    vector<int> indegree(numberOfmaterial, 0);
    for(auto &r : reactions) {
        int ridx = mat2idx[r.output.second];
        coefficient[ridx] = r.output.first;
        for(auto &I : r.inputs) {
            adj[ridx].push_back({mat2idx[I.second], I.first});
            indegree[mat2idx[I.second]]++;
        }
    }
    // Topology sort
    queue<int> Q;
    rep(i, numberOfmaterial) if(indegree[i] == 0) Q.push(i);
    vector<int> sorted;
    while(!Q.empty()) {
        int here = Q.front(); Q.pop();
        sorted.push_back(here);
        for(auto &p : adj[here]) {
            int next = p.first;
            if(--indegree[next] == 0) Q.push(next);
        }
    }
    // dynamic approach
    vector<ll> need(numberOfmaterial, 0);
    need[FUEL] = 1;
    rep(i, numberOfmaterial) {
        int here = sorted[i];
        ll factor = (need[here] + coefficient[here] - 1) / coefficient[here];
        for(auto &p : adj[here]) {
            int next = p.first;
            need[next] += p.second * factor;
        }
    }
    return need[ORE];
}

ll part2(vector<Reaction> &reactions) {
    // mapping name -> idx
    map<string, int> mat2idx;
    int numberOfmaterial = 0;
    for(auto &r : reactions) {
        for(auto &p : r.inputs) {
            if(mat2idx.find(p.second) == mat2idx.end()) {
                mat2idx[p.second] = numberOfmaterial++;
            }
        }
        if(mat2idx.find(r.output.second) == mat2idx.end()) {
            mat2idx[r.output.second] = numberOfmaterial++;
        }
    }
    int ORE = mat2idx["ORE"];
    int FUEL = mat2idx["FUEL"];
    // make graph (output -> input)
    vector<vector<pair<int, ll>>> adj(numberOfmaterial);
    vector<ll> coefficient(numberOfmaterial, 1);
    vector<int> indegree(numberOfmaterial, 0);
    for(auto &r : reactions) {
        int ridx = mat2idx[r.output.second];
        coefficient[ridx] = r.output.first;
        for(auto &I : r.inputs) {
            adj[ridx].push_back({mat2idx[I.second], I.first});
            indegree[mat2idx[I.second]]++;
        }
    }
    // Topology sort
    queue<int> Q;
    rep(i, numberOfmaterial) if(indegree[i] == 0) Q.push(i);
    vector<int> sorted;
    while(!Q.empty()) {
        int here = Q.front(); Q.pop();
        sorted.push_back(here);
        for(auto &p : adj[here]) {
            int next = p.first;
            if(--indegree[next] == 0) Q.push(next);
        }
    }
    // binary search
    ll lo = 0, hi = 1e12;
    ll maxProduction = -1;
    while(lo <= hi) {
        ll mid = (lo + hi) >> 1;
        vector<ll> need(numberOfmaterial, 0);
        need[FUEL] = mid;
        rep(i, numberOfmaterial) {
            int here = sorted[i];
            ll factor = (need[here] + coefficient[here] - 1) / coefficient[here];
            for(auto &p : adj[here]) {
                int next = p.first;
                need[next] += p.second * factor;
            }
        }
        if(need[ORE] <= 1e12) { // ok
            maxProduction = mid;
            lo = mid + 1;
        } else hi = mid - 1;
    }
    return maxProduction;
}

int main() {
    vector<Reaction> reactions;
    getInputs(reactions);
    cout << "Part 1 is : " << part1(reactions) << "\n";
    cout << "Part 2 is : " << part2(reactions) << "\n";
}
