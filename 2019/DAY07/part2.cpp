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

const int MAXN = 100000;

void getInput(vector<int> &origin) {
    string s; getline(cin, s);
    int l = 0, r = 0;
    while(l < sz(s)) {
        for(r = l; s[r] != ',' && r < sz(s); ++r) {}
        origin.push_back(stoi(s.substr(l, r - l)));
        l = r + 1;
    }
}

class Amplifer {
public:
    int n;
    vector<int> a; // program;
    int currA = 0; // current Address for program
    int phaseSetting;
    int inputSignal = 0, outputSignal = 0;
    bool halt = false;
    bool isFirstInputInstruction = true;
    
    Amplifer(const vector<int> &origin, int ps) : a(origin), phaseSetting(ps){
        n = sz(a);
    }
    
    void setInputSignal(int is) {
        if(isFirstInputInstruction) {
            inputSignal = phaseSetting;
            isFirstInputInstruction = false;
        }
        else inputSignal = is;
    }
    
    bool doInstruction() { // if true outputSignal changed or halt
        int opcode = a[currA] % 100;
        int fi = a[currA] / 100 % 10;
        int si = a[currA] / 1000 % 10;
        int fv = (fi == 1) ? a[currA + 1] : a[a[currA + 1]];
        int sv = (si == 1) ? a[currA + 2] : a[a[currA + 2]];
        if(opcode == 1) {
            a[a[currA + 3]] = fv + sv;
            currA += 4;
        } else if(opcode == 2) {
            a[a[currA + 3]] = fv * sv;
            currA += 4;
        } else if(opcode == 3) {
            // input instruction
            a[a[currA + 1]] = inputSignal;
            currA += 2;
        } else if(opcode == 4) {
            outputSignal = fv;
            currA += 2;
            return true;
        } else if(opcode == 5) {
            if(fv != 0) currA = sv;
            else currA += 3;
        } else if(opcode == 6) {
            if(fv == 0) currA = sv;
            else currA += 3;
        } else if(opcode == 7) {
            a[a[currA + 3]] = (fv < sv) ? 1 : 0;
            currA += 4;
        } else if(opcode == 8) {
            a[a[currA + 3]] = (fv == sv) ? 1 : 0;
            currA += 4;
        } else if(opcode == 99) {
            // program halt
            halt = true;
            return true;
        } else {
            // wrong opcode
            return true;
        }
        return false;
    }
    
};

int main() {
    FAST_IO();
    vector<int> orginProgram;
    getInput(orginProgram);
    int N = orginProgram.size();   
    int maxSignal = INT_MIN;

    vector<int> phaseSetting = {5, 6, 7, 8, 9};
    do {
        vector<Amplifer> amps;
        for(int i = 0; i < 5; ++i) {
            Amplifer amp(orginProgram, phaseSetting[i]);
            amps.push_back(amp);
        }
        int currAmp = 0;
        while(!amps[4].halt) {
            if(amps[currAmp].halt) currAmp = (currAmp + 1) % 5;
            amps[currAmp].setInputSignal(amps[(currAmp + 4) % 5].outputSignal);
            bool res = amps[currAmp].doInstruction();
            if(res) {
	            currAmp = (currAmp + 1) % 5;
            }
        }
        maxSignal = max(maxSignal, amps[4].outputSignal);
    } while(next_permutation(all(phaseSetting)));
    
    cout << maxSignal << "\n";
}
