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
			    ll x = 0; setMode(mode1, i + 1, x);
				a[x] = input.front();
				// cout << "Input Instruction! input is : " << a[x] << "\n";
				input.pop();
				i += 2;
			} else if(opcode == 4) {
			    ll x = 0; setMode(mode1, i + 1, x);
				output.push(a[x]);
				i += 2;
				// cout << "Output Instruction! output is : " << output.back() << "\n";
				return output.back();
			} else if(opcode == 99) {
				// cout << "program halt!\n";
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

int part1(vector<ll> &program) {
    const int MAX_GRID = 50;
    int cnt = 0;
    rep(i, MAX_GRID) {
        rep(j, MAX_GRID) {
            VMIntCodeComputer computer(program);
            computer.setInput(i);
            computer.setInput(j);
            int output = computer.run();
            if(output == 1) cnt++;
            cout << (output == 1 ? '#' : '.');
        }
        cout << "\n";
    }
    return cnt;
}

int part2(vector<ll> &program) {
    const int MAX_GRID = 10000;
    const int SHIP_SIZE = 100;
    int s = 11, e = 13;
    int X = -1, Y = -1;
    repp(i, 10, MAX_GRID - 1) {
         repp(j, s, MAX_GRID - 1) {
             VMIntCodeComputer computer(program);
             computer.setInput(i);
             computer.setInput(j);
             if(computer.run() == 1) {
                s = j;
                break;
             }
         }
         repp(j, e, MAX_GRID - 1) {
             VMIntCodeComputer computer(program);
             computer.setInput(i);
             computer.setInput(j);
             if(computer.run() == 0) {
                e = j;
                break;
             }
         }
         repp(j, s, e - 1) {
             VMIntCodeComputer computer1(program), computer2(program);
             computer1.setInput(i + SHIP_SIZE - 1);
             computer1.setInput(j);
             computer2.setInput(i);
             computer2.setInput(j + SHIP_SIZE - 1);
             if(computer1.run() == 1 && computer2.run() == 1) {
                 X = i;
                 Y = j;
                 break;
             }
         }
         if(X != -1 && Y != -1) break;
    }
    return X * 10000 + Y;
}

int main() {
    vector<ll> program;
    getInputString(program);
    program.resize(500);
    cout << "part 1 is : \n";
    cout << part1(program) << "\n";
    cout << "part 2 is : \n";
    cout << part2(program) << "\n";
}
