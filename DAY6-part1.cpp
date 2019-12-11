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

int main() {
    string s;
    int N = 0; // number of planet
    map<string, int> str2idx;
    vector<vector<int>> adj(3000);
    while(cin >> s) {
        string a = s.substr(0, 3);
        string b = s.substr(4, 3);
        int ia, ib;
        if(str2idx.find(a) == str2idx.end()) {
            ia = N++;
            str2idx[a] = ia;
        } else ia = str2idx[a];
        if(str2idx.find(b) == str2idx.end()) {
            ib = N++;
            str2idx[b] = ib;
        } else ib = str2idx[b];
        adj[ia].push_back(ib);
    }
    int COM = str2idx["COM"];
    vector<int> depth(N, -1);
    depth[COM] = 0;
    queue<int> Q;
    Q.push(COM);
    while(!Q.empty()) {
        int here = Q.front(); Q.pop();
        for(auto &next : adj[here]) {
            if(depth[next] == -1) {
                depth[next] = depth[here] + 1;
                Q.push(next);
            }
        }
    }
    int ans = 0;
    for(int i = 0; i < N; ++i) {
        if(depth[i] == -1) cout << "i : " << i << " oops!\n";
        ans += depth[i];
    }
    cout << ans << "\n";
}
