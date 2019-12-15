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

struct Moon {
    int x[3] = {0};
    int v[3] = {0};
};

const int N = 4;

int main() {
    vector<Moon> A(N);
    rep(i, N) rep(j, 3) cin >> A[i].x[j];
    int totalStep = 1000;
    int totalEnergy = 0;
    repp(step, 0, totalStep) {
        // calculate totalEnergy
        totalEnergy = 0;
        rep(i, N) {
            int kinEnergy = 0, potEnergy = 0;
            rep(k, 3) {
                kinEnergy += abs(A[i].v[k]);
                potEnergy += abs(A[i].x[k]);
            }
            totalEnergy += kinEnergy * potEnergy;
        }
        /*// currState : 
        cout << "Step " << step << " / totalEnergy : " << totalEnergy << "\n";
        rep(i, N) {
            cout << "pos:(" << A[i].x[0] << "," << A[i].x[1] << "," << A[i].x[2] << ")\t";
            cout << "vel:(" << A[i].v[0] << "," << A[i].v[1] << "," << A[i].v[2] << ")\n";
        }*/
        // calculate gravity
        rep(i, N) {
            rep(j, N) {
                rep(k, 3) {
                    if(A[i].x[k] < A[j].x[k]) A[i].v[k]++;
                    else if(A[i].x[k] > A[j].x[k]) A[i].v[k]--;
                }
            }
        }
        
        // adjust position
        rep(i, N) {
            rep(k, 3) {
                A[i].x[k] += A[i].v[k];
            }
        }
    }
    cout << totalEnergy << "\n";
}
