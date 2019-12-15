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
	vector<ll> output;
	
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
	VMIntCodeComputer(const vector<ll> &inst, ll ps) {
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

	vector<ll> getOutput() {
		return output;
	}
	
	void resetOutput() {
	    output.clear();
	}

	void run() {
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
				output.push_back(a[x]);
				i += 2;
				return;
			} else if(opcode == 99) {
				// program halt!
				is_halt = true;
				return;
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
					// program error!
					is_halt = true;
					cout << "Wrong Opcode\n";
					return;
				}
			}
		}
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

//          U, R, D, L
int dy[] = {-1, 0, 1, 0};
int dx[] = {0, 1, 0, -1};

int main() {
    /* get inputs */ 
	vector<ll> program;
	getInputString(program);
	program.resize(300000);
	/* upload program to VMIntCodeComputer */
	VMIntCodeComputer computer(program, 0);
	/* make panel and set the current position */
	const int MAX_PANEL = 500;
	vector<vector<int>> panel(MAX_PANEL, vector<int>(MAX_PANEL));
	int currY = MAX_PANEL / 2, currX = MAX_PANEL / 2;
	vector<vector<bool>> painted(MAX_PANEL, vector<bool>(MAX_PANEL));
	/* system operating */
	int dir = 0;
	int cnt = 0;
	int instructionCnt = 0;
	while(!computer.is_halt) {
	    /*rep(i, MAX_PANEL) rep(j, MAX_PANEL) cout << panel[i][j] << " \n"[j == MAX_PANEL - 1];
	    cout << "---------------------------------\n";*/
	    computer.setInput(panel[currY][currX]);
	    computer.run();
	    if(computer.is_halt) break;
	    computer.run();
	    int outputColor = computer.getOutput()[0];
	    int outputDir = computer.getOutput()[1];
	    ++instructionCnt;
	    computer.resetOutput();
	    computer.resetInput();
	    panel[currY][currX] = outputColor;
	    if(painted[currY][currX] == false) {
	        painted[currY][currX] = true;
	        ++cnt;
	    }
	    if(outputDir == 0) { // turn left
	        dir = (dir + 3) % 4;
	    } else { // turn right
	        dir = (dir + 1) % 4;
	    }
        currY += dy[dir];
	    currX += dx[dir];
	}
	cout << cnt << "\n";
} 
