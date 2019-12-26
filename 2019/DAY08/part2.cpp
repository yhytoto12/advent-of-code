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
	int W = 25, H = 6;
	int P = W * H;
	string S; cin >> S;
	int L = sz(S) / P;
	string rendered_layer(P, '2');
	rep(j, P) {
		for(int i = L - 1; i >= 0; --i) {
			if(rendered_layer[j] == '2') rendered_layer[j] = S[i * P + j];
			else {
				if(S[i * P + j] != '2') rendered_layer[j] = S[i * P + j];
			} 
		}
	}
	cout << "Rendered_layer Image : \n";
	rep(i, H) {
		rep(j, W) {
			cout << (rendered_layer[i * W + j] == '0' ? ' ' : '#');
		}
		cout << "\n";
	}
} 
