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

int di[] = {0, 0, -1, 1};
int dj[] = {1, -1, 0, 0};

int biodiversity_rating(vector<string> &A) {
    int ret = 0;
    rep(i, 5) rep(j, 5) {
        if(A[i][j] == '#') ret += (1 << (i * 5 + j));
    }
    return ret;
}

void update(vector<string> &A) {
    int cnt[5][5] = {0};
    rep(i, 5) rep(j, 5) {
        rep(k, 4) {
            int ni = i + di[k], nj = j + dj[k];
            if(ni >= 0 && ni < 5 && nj >= 0 && nj < 5 && A[ni][nj] == '#') {
                cnt[i][j]++;
            }
        }
    }
    rep(i, 5) rep(j, 5) {
        if(A[i][j] == '#' && cnt[i][j] != 1) {
            A[i][j] = '.';
        } else if(A[i][j] == '.' && (cnt[i][j] == 1 || cnt[i][j] == 2)) {
            A[i][j] = '#';
        }
    }
}

void print(vector<string> &A) {
    rep(i, 5) cout << A[i] << "\n";
}

int part1(vector<string> A) {
    vector<bool> appear(1 << 25, false);
    int step = 0;
    while(true) {
        cout << step++ << " steps after : \n";
        print(A);
        appear[biodiversity_rating(A)] = true;
        update(A);
        if(appear[biodiversity_rating(A)]) {
            break;
        }
    }
    cout << step << " steps after : \n";
    print(A);
    return biodiversity_rating(A);
}

int main() {
    vector<string> A(5);
    rep(i, 5) cin >> A[i];
    cout << "part1 is : " << part1(A) << "\n";
}
