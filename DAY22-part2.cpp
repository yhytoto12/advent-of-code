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

int main() {
    FAST_IO();
    const ll N = 119315717514047LL;
    string statement;
    vector<string> techniques;
    while(getline(cin, statement)) {
        techniques.push_back(statement);
    }
    ll pos = 2020;
    reverse(all(techniques));
    ll repeat = 0;
    while(repeat++ < 7000) {
        // cout << repeat << " times repeated : " << pos << " change into ";
        for(auto &str : techniques) {
            if(str[0] == 'c') {  // cut x
                ll x = stoll(str.substr(4));
                x = (x < 0) ? N + x : x;
                if(pos >= 0 && pos < N - x) pos = pos + x;
                else pos = pos - N + x;
            } else if(str[5] == 'w') { // increment x
                ll x = stoll(str.substr(20));
                pos = modmul(pos, modpow(x, N - 2, N), N);
            } else { // reverse
                pos = N - 1 - pos;
            }
        }
        // cout <<  pos << "\n";
        if(pos == 2020) {
            cout << "Found period : " << repeat << "\n";
            break;
        }
    }
    cout << "Not Found!\n";
}
