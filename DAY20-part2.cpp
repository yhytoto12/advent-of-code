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

const int MAXN = 150;
string A[MAXN];
int idx[MAXN][MAXN];
int osy, osx, oey, oex;
int isy = -1, isx = -1, iey = -1, iex = -1;
int N, M, V;
int L = 0; // maximum level

int main() {
    while(getline(cin, A[N])) {
        ++N;
    }
    N -= 4;
    M = sz(A[0]) - 4;
    osy = 2;
    osx = 2;
    oey = osy + N - 1;
    oex = osx + M - 1;
    repp(i, osy, oey) {
        if(isy != -1) break;
        repp(j, osx, oex) {
            if(A[i][j] != '#' && A[i][j] != '.') {
                isy = i;
                isx = j;
                break;
            }
        }
    }
    for(int i = oey; i >= osy; --i) {
        if(iey != -1) break;
        for(int j = oex; j >= osx; --j) {
            if(A[i][j] != '#' && A[i][j] != '.') {
                iey = i;
                iex = j;
                break;
            }
        }
    }
    // cout << make_pair(osy, osx) << " " << make_pair(oey, oex) << "\n";
    // cout << make_pair(isy, isx) << " " << make_pair(iey, iex) << "\n";
    repp(i, osy, oey) {
        repp(j, osx, oex) {
            if(i >= isy && i <= iey && j >= isx && j <= iex) continue;
            if(A[i][j] == '.') {
                idx[i][j] = V++;
            }
        }
    }
    map<string, deque<int>> portal;
    repp(j, osx, oex) {
        if(A[osy][j] == '.') {
            string name = "";
            name.push_back(A[osy - 2][j]);
            name.push_back(A[osy - 1][j]);
            portal[name].push_back(idx[osy][j]);
        }
        if(A[oey][j] == '.') {
            string name = "";
            name.push_back(A[oey + 1][j]);
            name.push_back(A[oey + 2][j]);
            portal[name].push_back(idx[oey][j]);
        }
    }
    repp(i, osy, oey) {
        if(A[i][osx] == '.') {
            string name = "";
            name.push_back(A[i][osx - 2]);
            name.push_back(A[i][osx - 1]);
            portal[name].push_back(idx[i][osx]);
        }
        if(A[i][oex] == '.') {
            string name = "";
            name.push_back(A[i][oex + 1]);
            name.push_back(A[i][oex + 2]);
            portal[name].push_back(idx[i][oex]);
        }
    }
    repp(j, isx, iex) {
        if(A[isy - 1][j] == '.') {
            string name = "";
            name.push_back(A[isy][j]);
            name.push_back(A[isy + 1][j]);
            portal[name].push_front(idx[isy - 1][j]);
        }
        if(A[iey + 1][j] == '.') {
            string name = "";
            name.push_back(A[iey - 1][j]);
            name.push_back(A[iey][j]);
            portal[name].push_front(idx[iey + 1][j]);
        }
    }
    repp(i, isy, iey) {
        if(A[i][isx - 1] == '.') {
            string name = "";
            name.push_back(A[i][isx]);
            name.push_back(A[i][isx + 1]);
            portal[name].push_front(idx[i][isx - 1]);
        }
        if(A[i][iex + 1] == '.') {
            string name = "";
            name.push_back(A[i][iex - 1]);
            name.push_back(A[i][iex]);
            portal[name].push_front(idx[i][iex + 1]);
        }
    }
    L = sz(portal);
    int dy[] = {-1, 0, 1, 0};
    int dx[] = {0, 1, 0, -1};
    vector<vector<int>> adj(L * V);
    rep(l, L) {
        repp(i, osy, oey) {
            repp(j, osx, oex) {
                if(i >= isy && i <= iey && j >= isx && j <= iex) continue;
                if(A[i][j] == '.') {
                   rep(k, 4) {
                        int ni = i + dy[k], nj = j + dx[k];
                        if(A[ni][nj] == '.') {
                            adj[idx[i][j] + l*V].push_back(idx[ni][nj] + l*V);
                        }
                    }
                }
            }
        }
    }
    int start = portal["AA"].front();
    int end = portal["ZZ"].front();
    for(auto &a : portal) {
        if(sz(a.second) == 2) {
            rep(l, L - 1) {
                adj[a.second.front() + l*V].push_back(a.second.back() + (l + 1)*V);
                adj[a.second.back() + (l + 1)*V].push_back(a.second.front() + l*V);
                // cout << a.second.front() + l*V << "\t- " << a.second.back() + (l+1)*V << "\tconnected!\n";
            }
        }
    }
    /*cout << "V : " << V << " L : " << L << "\n";
    for(auto &a : portal) {
        cout << a.first << " : ";
        for(auto &b : a.second) {
            cout << b << " ";
        }
        cout << "\n";
    }*/
    // bfs
    vector<int> depth(L * V, -1);
    queue<int> Q;
    depth[start] = 0;
    Q.push(start);
    while(!Q.empty()) {
        int here = Q.front(); Q.pop();
        for(auto &next : adj[here]) {
            if(depth[next] == -1) {
                depth[next] = depth[here] + 1;
                Q.push(next);
            }
        }
    }
    /*repp(i, osy, oey) {
        repp(j, osx, oex) {
            if(i >= isy && i <= iey && j >= isx && j <= iex) cout << " \t";
            else if(A[i][j] == '.') {
                cout << depth[idx[i][j]] << "\t";
            } else {
                cout << "#\t";
            }
        }
        cout << "\n";
    }*/
    cout << depth[end] << "\n";
}
