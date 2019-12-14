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

int nthDigit(int x, int n) {
	int d = 1;
	rep(i, n) d *= 10;
	return x / d % 10;
}

class VMIntCodeComputer {
private :
	vector<ll> inst;
	ll phaseSetting;
	bool isFirstInputInstruction = true;
	int i, relative_base;
	int input, output;
	/* Instruction Implementation */
	void ADD(int mode1, int mode2, int mode3, int v1, int v2, int v3) {

	}

public :
	bool is_halt;
	VMIntCodeComputer(const vector<ll> &a, ll ps) {
		inst = a;
		phaseSetting = ps;
		i = 0;
		relative_base = 0;
		input = 0;
		output = 0;
	}

	ll getOutput() {
		return output;
	}

	void run(ll in) {
		while(!is_halt) {
			int opcode = nthDigit(a[i], 0);
			int mode1 = nthDigit(a[i], 1);
			int mode2 = nthDigit(a[i], 2);
			int mode3 = nthDigit(a[i], 3);
			if(opcode == 3) {
				if(isFirstInputInstruction) {
					a[a[i + 1]] = phaseSetting;
					isFirstInputInstruction = false;
				} else a[a[i + 1]] = in;
				i += 2;
			} else if(opcode == 4) {
				output = a[a[i + 1]];
				i += 2;
				return;
			} else if(opcode == 99) {
				// program halt!
				is_halt = true;
				return;
			} else {
				if(opcode == 1) {
					ADD(mode1, mode2, mode3, a[i + 1], a[i + 2], a[i + 3]);
				} else if(opcode == 2) {
					MUL(mode1, mode2, mode3, a[i + 1], a[i + 2], a[i + 3]);
				} else if(opcode == 5) {
					NOT_ZERO(mode1, mode2, a[i + 1], a[i + 2]);
				} else if(opcode == 6) {
					ZERO(mode1, mode2, a[i + 1], a[i + 2]);
				} else if(opcode == 7) {
					LESS_THAN(mode1, mode2, mode3, a[i + 1], a[i + 2], a[i + 3]);
				} else if(opcode == 8) {
					EQUAL(mode1, mode2, mode3, a[i + 1], a[i + 2], a[i + 3]);
				} else if(opcode == 9) {
					ADJUST_RELATIVE_BASE(mode1, mode2, a[i + 1], a[i + 2]);
				} else {
					// program error!
				}
			}
		}
	}
};

int main() {
	
} 
