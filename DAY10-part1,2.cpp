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

double theta(int y, int x) {
    double res = atan2(0, -1) / 2.0 + atan2(y, x);
    res += (res < 0) ? 2 * atan2(0, -1) : 0;
    return res;
}

struct Point{
    int y, x;
    bool operator<(const Point &a) const {
        return theta(y, x) < theta(a.y, a.x);
    }
};

int gcd(int a, int b) {
    return (b == 0) ? a : gcd(b, a%b);
}

int main() {
    const int NX = 33;
    const int NY = 33;
    vector<string> S(NY);
    vector<vector<int>> ans(NY, vector<int>(NX));
    rep(y, NY) cin >> S[y];
    vector<pii> a;
    rep(y, NY) rep(x, NX) if(S[y][x] == '#') a.push_back({y, x});
    int maxDetected = 0;
    int X = -1, Y = -1;
    for(auto &p : a) {
        int detected = 0;
        map<pii, bool> chk;
        rep(y, NY) rep(x, NX) {
            if(y == p.first && x == p.second) continue;
            int ry = y - p.first, rx = x - p.second;
            int d = gcd(abs(ry), abs(rx));
            if(S[y][x] == '#') {
                if(chk.find({ry / d, rx / d}) == chk.end()) {
                    chk[{ry / d, rx / d}] = true;
                    detected++;
                }
            }
        }
        ans[p.first][p.second] = detected;
        if(detected > maxDetected) {
            maxDetected = detected;
            Y = p.first; X = p.second;
        }
    }
    /* Part1 Solution */
    cout << "Part1 : \n";
    cout << maxDetected << "\n";
    cout << X << " " << Y << "\n";
    map<Point, vector<Point>> mp;
    for(auto &p : a) {
        if(p.first == Y && p.second == X) continue;
        int ry = p.first - Y, rx = p.second - X;
        int d = gcd(abs(ry), abs(rx));
        mp[{ry / d, rx / d}].push_back({ry, rx});
    }
    vector<vector<int>> b(NY, vector<int>(NX));
    for(auto &p : mp) {
        // sort by distance from (Y, X)
        sort(all(p.second), [](const Point &a, const Point &b) {
            return a.y*a.y+a.x*a.x > b.y*b.y+b.x*b.x;
        });
    }
    b[Y][X] = -1;
    int cnt = 0;
    int wantToFind = 5;
    while(cnt < sz(a) - 1) {
        for(auto &p : mp) {
            if(!p.second.empty()) {
                b[Y + p.second.back().y][X + p.second.back().x] = ++cnt;
                p.second.pop_back();
            }
        }
    }
    int ax = -1, ay = -1;
    rep(i, NY) {
        rep(j, NX) {
            if(b[i][j] == wantToFind) {
                ay = i; ax = j;
            }
            cout << b[i][j] << "\t";
        }
        cout << "\n";
    }
    // Find wantToFind-th asteroid!!
    cout << wantToFind << "-th asteroid is (";
    cout << ay << "," << ax << ")\n";
}
