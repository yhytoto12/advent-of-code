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
    const int N = 10007;
    vector<int> A(N), B(N);
    rep(i, N) A[i] = i;
    string statement;
    int step = 0;
    while(getline(cin, statement)) {
        if(statement[0] == 'c') { // cut x
            int x = stoi(statement.substr(4));
            x = (x < 0)? N + x : x;
            rep(i, x) B[i + N - x] = A[i];
            repp(i, x, N - 1) B[i - x] = A[i];
            A = B;
            // cout << "cut " << x << "\n";
        } else if(statement[5] == 'w') { // deal with increment x
            int x = stoi(statement.substr(20));
            rep(i, N) B[x * i % N] = A[i];
            A = B;
            // cout << "deal with increment " << x << "\n";
        } else { // deal into new stack
            reverse(all(A));
            // cout << "deal into new stack\n";
        }
        ++step;
    }
    cout << step << " techniques after : position of card 2019 is ";
    rep(i, N) {
        if(A[i] == 2019) {
            cout << i << "\n";
            break;
        }
    }
}
