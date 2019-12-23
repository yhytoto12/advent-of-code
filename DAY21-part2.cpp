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

int nthDigit(ll x, int n) {
	int d = 1;
	rep(i, n) d *= 10;
	return x / d % 10;
}

class VMIntCodeComputer {
private :
	vector<ll> a;
	ll phaseSetting;
	ll i, relative_base;
	queue<ll> input;
	queue<ll> output;
	
	void setMode(int mode, ll val, ll &resAddress) {
	    if(mode == 0) resAddress = a[val];
	    else if(mode == 1) resAddress = val; 
	    else if(mode == 2) resAddress = a[val] + relative_base;
	}
	/* Instruction Implementation */
	void ADD(int mode1, int mode2, int mode3, ll v1, ll v2, ll v3) {
        setMode(mode1, v1, v1);
        setMode(mode2, v2, v2);
        setMode(mode3, v3, v3);
        a[v3] = a[v1] + a[v2];
        i += 4;
	}
	
	void MUL(int mode1, int mode2, int mode3, ll v1, ll v2, ll v3) {
        setMode(mode1, v1, v1);
        setMode(mode2, v2, v2);
        setMode(mode3, v3, v3);
        a[v3] = a[v1] * a[v2];
        i += 4;
	}
	
	void JUMP_IF_TRUE(int mode1, int mode2, ll v1, ll v2) {
	    setMode(mode1, v1, v1);
	    setMode(mode2, v2, v2);
	    if(a[v1] != 0) i = a[v2];
	    else i += 3;
	}
	
	void JUMP_IF_FALSE(int mode1, int mode2, ll v1, ll v2) {
	    setMode(mode1, v1, v1);
	    setMode(mode2, v2, v2);
	    if(a[v1] == 0) i = a[v2];
	    else i += 3;
	}
	
	void LESS_THAN(int mode1, int mode2, int mode3, ll v1, ll v2, ll v3) {
        setMode(mode1, v1, v1);
        setMode(mode2, v2, v2);
        setMode(mode3, v3, v3);
        if(a[v1] < a[v2]) a[v3] = 1;
        else a[v3] = 0;
        i += 4;
	}
	
	void EQUAL(int mode1, int mode2, int mode3, ll v1, ll v2, ll v3) {
        setMode(mode1, v1, v1);
        setMode(mode2, v2, v2);
        setMode(mode3, v3, v3);
        if(a[v1] == a[v2]) a[v3] = 1;
        else a[v3] = 0;
        i += 4;
	}
	
	void ADJUST_RELATIVE_BASE(int mode1, ll v1) {
	    setMode(mode1, v1, v1);
	    relative_base += a[v1];
	    i += 2;
	}

public :
	bool is_halt;
	VMIntCodeComputer(const vector<ll> &inst, ll ps = 0) {
		a = inst;
		phaseSetting = ps;
		i = 0;
		relative_base = 0;
		is_halt = false;
	}
	void setInput(ll in) {
	    input.push(in);
	}
	
	void resetInput() {
	    while(!input.empty()) input.pop();
	}

	ll getOutput() {
		return output.back();
	}
	
	void resetOutput() {
	    while(!output.empty()) output.pop();
	}

	ll run() {
		while(!is_halt) {
			int opcode = nthDigit(a[i], 0) + nthDigit(a[i], 1) * 10;
			int mode1 = nthDigit(a[i], 2);
			int mode2 = nthDigit(a[i], 3);
			int mode3 = nthDigit(a[i], 4);
			if(opcode == 3) {
			 //   cout << "Input Instruction!\n";
			    ll x = 0; setMode(mode1, i + 1, x);
				a[x] = input.front();
				input.pop();
				i += 2;
			} else if(opcode == 4) {
			 //   cout << "Output Instruction!\n";
			    ll x = 0; setMode(mode1, i + 1, x);
				output.push(a[x]);
				i += 2;
				return output.back();
			} else if(opcode == 99) {
				// program halt!
				is_halt = true;
				return output.back();
			} else {
				if(opcode == 1) {
					ADD(mode1, mode2, mode3, i + 1, i + 2, i + 3);
				} else if(opcode == 2) {
					MUL(mode1, mode2, mode3, i + 1, i + 2, i + 3);
				} else if(opcode == 5) {
					JUMP_IF_TRUE(mode1, mode2, i + 1, i + 2);
				} else if(opcode == 6) {
					JUMP_IF_FALSE(mode1, mode2, i + 1, i + 2);
				} else if(opcode == 7) {
					LESS_THAN(mode1, mode2, mode3, i + 1, i + 2, i + 3);
				} else if(opcode == 8) {
					EQUAL(mode1, mode2, mode3, i + 1, i + 2, i + 3);
				} else if(opcode == 9) {
					ADJUST_RELATIVE_BASE(mode1, i + 1);
				} else {
				    // Error
				}
			}
		}
		return output.back();
	}
};

void getInputString(vector<ll> &inputs) {
    string s;
    getline(cin, s);
    int l = 0, r = 0;
    while(l < sz(s)) {
        if(s[r] != ',' && r < sz(s)) {
            ++r;
        } else {
            inputs.push_back(stoll(s.substr(l, r - l)));
            l = ++r;
        }
    }
}

int main() {
    vector<ll> program;
    getInputString(program);
    program.resize(100000);
    VMIntCodeComputer computer(program);
    // J = D(A' + C'H + AB'C)
    vector<string> input_str = {
        "NOT A J",
        "NOT C T",
        "AND H T",
        "OR T J",
        "NOT B T",
        "AND A T",
        "AND C T",
        "OR T J",
        "AND D J",
        "RUN",
    };
    for(auto &inst : input_str) {
        for(auto &ch : inst) {
            computer.setInput(ch);
        }
        computer.setInput('\n');
    }
    while(!computer.is_halt) {
        int output = computer.run();
        if(output <= 127) cout << (char) output;
        else cout << output << "\n";
    }
}
