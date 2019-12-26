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

const ll D = 10000LL;
ll modmul(ll a, ll b, ll MOD) {
    ll ret = 0;
    ll b0 = b % D; b /= D;
    ll b1 = b % D; b /= D;
    ll b2 = b % D; b /= D;
    ll b3 = b % D; b /= D;
    if(b != 0) cout << "ERROR!\n";
    ret = (ret + a * b0 % MOD) % MOD;
    ret = (ret + a * b1 % MOD * D % MOD) % MOD;
    ret = (ret + a * b2 % MOD * D % MOD * D % MOD) % MOD;
    ret = (ret + a * b3 % MOD * D % MOD * D % MOD * D % MOD) % MOD;
    return ret;
}

ll modpow(ll x, ll n, ll MOD) {
    ll ret = 1;
    while(n > 0) {
        if(n % 2 == 1) ret = modmul(ret, x, MOD);
        x = modmul(x, x, MOD);
        n /= 2;
    }
    return ret;
}

ll modinv(ll x, ll MOD) {
    return modpow(x, MOD - 2, MOD);
}

int main() {
    const ll N = 119315717514047LL;
    const ll T = 101741582076661LL;
    string statement;
    vector<string> techniques;
    while(getline(cin, statement)) {
        techniques.push_back(statement);
    }
    ll a = 1, b = 0;
    for(auto &str : techniques) {
        if(str[0] == 'c') {
            ll x = stoll(str.substr(4));
            b = (b - x + N) % N;
        } else if(str[5] == 'w') {
            ll x = stoll(str.substr(20));
            a = a * x % N;
            b = b * x % N;
        } else {
            a = (N - a) % N;
            b = (N - b - 1) % N;
        }
    }
    ll A = modpow(a, T, N);
    ll B = modmul(modmul(A - 1, modinv(a - 1, N), N), b, N);
    // Ax + B = 2020 (mod N)
    cout << modmul(modinv(A, N), (2020 - B + N) % N, N);
}
