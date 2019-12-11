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
    vector<int> origin_a;
    int t;
    while(cin >> t) {
        origin_a.push_back(t);
    }
    origin_a.resize(5000);
    int n = sz(origin_a);
    vector<int> a;
    int maxSignal = INT_MIN;
    vector<int> ps = {0, 1, 2, 3, 4};
    do {
        int Firstinput = 0, Secondinput = 0, output = 0;
        bool error = false;
        rep(j, 5) {
            if(error) break;
            int currPhaseSetting = ps[j];
            a = origin_a;
            int i = 0;
            bool isFirstInputInstruction = true;
            Firstinput = currPhaseSetting;
            Secondinput = output;
            while(0 <= i && i < n) {
                int opcode = a[i] % 100;
                int first = a[i] / 100 % 10;
                int second = a[i] / 1000 % 10;
                int third = a[i] / 10000 % 10;
                int x = (first == 1) ? a[i + 1] : a[a[i + 1]];
                int y = (second == 1) ? a[i + 2] : a[a[i + 2]];
                if(opcode == 1) {
                    a[a[i + 3]] = x + y;
                    i += 4;
                } else if(opcode == 2) {
                    a[a[i + 3]] = x * y;
                    i += 4;
                } else if(opcode == 3) {
                    if(isFirstInputInstruction) {
                        a[a[i + 1]] = Firstinput;
                        isFirstInputInstruction = false;
                    } else a[a[i + 1]] = Secondinput;
                    i += 2;
                } else if(opcode == 4) {
                    output = x;
                    i += 2;
                    if(a[i] == 99) {
                        // cout << "Program Halt\n";
                        break;
                    } else if(output != 0){
                        // cout << "output isn't zero Error!\n";
                        error = true;
                        break;
                    }
                } else if(opcode == 5) {
                    if(x != 0) i = y;
                    else i += 3;
                } else if(opcode == 6) {
                    if(x == 0) i = y;
                    else i += 3;
                } else if(opcode == 7) {
                    a[a[i + 3]] = (x < y) ? 1 : 0;
                    i += 4;
                } else if(opcode == 8) {
                    a[a[i + 3]] = (x == y) ? 1 : 0;
                    i += 4;
                } else if(opcode == 99) {
                    // cout << "opcode 99 Program halt!\n";
                    error = true;
                    break;
                } else {
                    // cout << "opcode Error!\n";
                    error = true;
                    break;
                }
            }
        }
        // cout << "PS : " << ps << "signal : " << output << "\n";
        if(!error) maxSignal = max(maxSignal, output);
    } while(next_permutation(all(ps)));
    cout << maxSignal << "\n";
}
