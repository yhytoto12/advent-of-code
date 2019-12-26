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

struct Moon {
    ll x[3] = {0};
    ll v[3] = {0};
};

const int N = 4;


int main() {
    vector<Moon> A(N);
    rep(i, N) rep(j, 3) cin >> A[i].x[j];
    vector<Moon> initial = A;
    vector<ll> period(3, 0);
    rep(k, 3) {
        while(true) {
            // gravity
            rep(i, N) rep(j, N) {
                if(A[i].x[k] < A[j].x[k]) A[i].v[k]++;
                else if(A[i].x[k] > A[j].x[k]) A[i].v[k]--;
            }
            // velocity
            rep(i, N) {
                A[i].x[k] += A[i].v[k];
            }
            bool done = true;
            rep(i, N) {
                done &= (A[i].x[k] == initial[i].x[k]);
                done &= (A[i].v[k] == initial[i].v[k]);
            }
            ++period[k];
            if(done) break;
        }
        cout << period[k] << "\n";
    }
    ll ans = 1;
    rep(i, 3) ans = lcm(ans, period[i]);
    cout << ans << "\n";
}


/* my input
-2 9 -5
16 19 9
0 3 6
11 0 11
*/
