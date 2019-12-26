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

void getInputs(vector<int> &input, int &messageOffset) {
    string s; cin >> s;
    for(auto &x : s) {
        input.push_back(x - '0');
    }
    messageOffset = stoi(s.substr(0, 7));
}
int X[] = {0, 1, 0, -1};

int main() {
    vector<int> input;
    int messageOffset = 0;
    getInputs(input, messageOffset);
    int N = sz(input);
    vector<int> output(N, 0);
    int phase = 100;
    rep(step, phase) {
        // cout << step << " step after : " << input;
        repp(k, 1, N) {
            output[k - 1] = 0;
            rep(i, N) {
                output[k - 1] += input[i] * X[(i + 1) % (4 * k) / k];
                // cout << input[i] << "*" << X[(i + 1) % (4 * k) / k] << "\t+ ";
            }
            output[k - 1] %= 10;
            output[k - 1] = abs(output[k - 1]);
            
            // cout << " = " << output[k - 1] << "\n";
        }
        input = output;
    }
    rep(i, 8) cout << output[i];
    cout << "\n";
}
