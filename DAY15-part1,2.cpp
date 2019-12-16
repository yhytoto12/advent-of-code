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

enum SPACE {
    BLANK, WALL, OXYZEN
};

char tile[] = {' ', '#', 'O', 'D'};
int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};

int right(int x) {
    if(x == 0) return 3;
    else if(x == 1) return 2;
    else if(x == 2) return 0;
    else return 1;
    
}

ll part1(vector<ll> &program) {
    VMIntCodeComputer computer(program);
    const int MAXN = 44;
    vector<vector<int>> space(MAXN, vector<int>(MAXN, BLANK));
    int SY = MAXN / 2, SX = MAXN / 2;   // start pos
    int EY = -1, EX = -1;                 // oxyzen pos
    int currY = SY, currX = SX;
    int inst = 1000000;
    while(!computer.is_halt && --inst) {
        int k = rand() % 4;
        int nextY = currY + dy[k];
        int nextX = currX + dx[k];
        computer.setInput(k + 1);
        int status = computer.run();
        if(status == 0) {
            space[nextY][nextX] = WALL;
        } else if(status == 1) {
            space[nextY][nextX] = BLANK;
            currY = nextY;
            currX = nextX;
        } else if(status == 2) {
            space[nextY][nextX] = OXYZEN;
            EY = nextY;
            EX = nextX;
            currY = nextY;
            currX = nextX;
        } else {
            // error
        }
    }
    space[SY][SX] = 3;
    // draw
    rep(i, MAXN) {
        rep(j, MAXN){
            cout << tile[space[i][j]];
        }
        cout << "\n";
    }
    // bfs
    queue<pair<int, int>> Q;
    vector<vector<int>> dist(MAXN, vector<int>(MAXN, -1));
    dist[SY][SX] = 0;
    Q.push({SY, SX});
    while(!Q.empty()) {
        int HY = Q.front().first, HX = Q.front().second;
        Q.pop();
        rep(i, 4) {
            int NY = HY + dy[i], NX = HX + dx[i];
            if(space[NY][NX] != WALL && dist[NY][NX] == -1) {
                dist[NY][NX] = dist[HY][HX] + 1;
                Q.push({NY, NX});
            }
        }
    }
    return dist[EY][EX];
}

ll part2(vector<ll> &program) {
    VMIntCodeComputer computer(program);
    const int MAXN = 44;
    vector<vector<int>> space(MAXN, vector<int>(MAXN, BLANK));
    int OY = -1, OX = -1;                 // oxyzen pos
    int currY = MAXN / 2, currX = MAXN / 2;
    int inst = 1000000;
    while(!computer.is_halt && --inst) {
        int k = rand() % 4;
        int nextY = currY + dy[k];
        int nextX = currX + dx[k];
        computer.setInput(k + 1);
        int status = computer.run();
        if(status == 0) {
            space[nextY][nextX] = WALL;
        } else if(status == 1) {
            space[nextY][nextX] = BLANK;
            currY = nextY;
            currX = nextX;
        } else if(status == 2) {
            space[nextY][nextX] = OXYZEN;
            OY = nextY;
            OX = nextX;
            currY = nextY;
            currX = nextX;
        } else {
            // error
        }
    }
    // bfs
    queue<pair<int, int>> Q;
    vector<vector<int>> dist(MAXN, vector<int>(MAXN, -1));
    dist[OY][OX] = 0;
    Q.push({OY, OX});
    while(!Q.empty()) {
        int HY = Q.front().first, HX = Q.front().second;
        Q.pop();
        rep(i, 4) {
            int NY = HY + dy[i], NX = HX + dx[i];
            if(space[NY][NX] != WALL && dist[NY][NX] == -1) {
                dist[NY][NX] = dist[HY][HX] + 1;
                Q.push({NY, NX});
            }
        }
    }
    int res = 0;
    rep(i, MAXN) rep(j, MAXN) res = max(res, dist[i][j]);
    return res;
}


int main() {
    /* get inputs */ 
	vector<ll> program;
	getInputString(program);
	program.resize(500000);
	cout << "Part 1 ans is : \n" << part1(program) << "\n";
	cout << "Part 2 ans is : \n" << part2(program) << "\n";
}
