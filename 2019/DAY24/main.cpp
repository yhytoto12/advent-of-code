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

int di[] = {0, 0, -1, 1};
int dj[] = {1, -1, 0, 0};

int biodiversity_rating(vector<string> &A) {
    int ret = 0;
    rep(i, 5) rep(j, 5) {
        if(A[i][j] == '#') ret += (1 << (i * 5 + j));
    }
    return ret;
}

void update(vector<string> &A) {
    int cnt[5][5] = {0};
    rep(i, 5) rep(j, 5) {
        rep(k, 4) {
            int ni = i + di[k], nj = j + dj[k];
            if(ni >= 0 && ni < 5 && nj >= 0 && nj < 5 && A[ni][nj] == '#') {
                cnt[i][j]++;
            }
        }
    }
    rep(i, 5) rep(j, 5) {
        if(A[i][j] == '#' && cnt[i][j] != 1) {
            A[i][j] = '.';
        } else if(A[i][j] == '.' && (cnt[i][j] == 1 || cnt[i][j] == 2)) {
            A[i][j] = '#';
        }
    }
}

void print(vector<string> &A) {
    rep(i, 5) cout << A[i] << "\n";
}

int part1(vector<string> A) {
    vector<bool> appear(1 << 25, false);
    int step = 0;
    while(true) {
        // cout << step++ << " steps after : \n";
        // print(A);
        appear[biodiversity_rating(A)] = true;
        update(A);
        if(appear[biodiversity_rating(A)]) {
            break;
        }
    }
    // cout << step << " steps after : \n";
    // print(A);
    return biodiversity_rating(A);
}

int part2(vector<string> A) {
    const int L = 200;
    vector<string> SPACE(5);
    rep(i, 5) SPACE[i] = ".....";
    vector<vector<string>> B(2 * L + 1, vector<string>(SPACE)); // B[i + L] : depth i
    vector<vector<vector<int>>> cnt(2 * L + 1, vector<vector<int>>(5, vector<int>(5, 0)));
    B[L] = A;
    int step = 0;
    while(++step <= L) {
        repp(depth, -L, L) {
            rep(i, 5) rep(j, 5) {
                if(i == 2 && j == 2) continue;
                rep(k, 4) {
                    int ni = i + di[k], nj = j + dj[k];
                    if(ni >= 0 && ni < 5 && nj >= 0 && nj < 5 && B[L + depth][ni][nj] == '#') {
                        cnt[L + depth][i][j]++;
                    }
                }
            }
            if(depth > -L) {
                if(B[L + depth - 1][1][2] == '#') rep(i, 5) cnt[L + depth][0][i]++;
                if(B[L + depth - 1][2][3] == '#') rep(i, 5) cnt[L + depth][i][4]++;
                if(B[L + depth - 1][3][2] == '#') rep(i, 5) cnt[L + depth][4][i]++;
                if(B[L + depth - 1][2][1] == '#') rep(i, 5) cnt[L + depth][i][0]++;
            }
            if(depth < L) {
                int c;
                c = 0; rep(i, 5) if(B[L + depth + 1][0][i] == '#') c++;
                cnt[L + depth][1][2] += c;
                c = 0; rep(i, 5) if(B[L + depth + 1][i][4] == '#') c++;
                cnt[L + depth][2][3] += c;
                c = 0; rep(i, 5) if(B[L + depth + 1][4][i] == '#') c++;
                cnt[L + depth][3][2] += c;
                c = 0; rep(i, 5) if(B[L + depth + 1][i][0] == '#') c++;
                cnt[L + depth][2][1] += c;
            }
        }
        repp(depth, -L, L) {
            rep(i, 5) rep(j, 5) {
                if(i == 2 && j == 2) continue;
                if(B[L + depth][i][j] == '#' && cnt[L + depth][i][j] != 1) {
                    B[L + depth][i][j] = '.';
                } else if(B[L + depth][i][j] == '.' && (cnt[L + depth][i][j] == 1 || cnt[L + depth][i][j] == 2)) {
                    B[L + depth][i][j] = '#';
                }
                cnt[L + depth][i][j] = 0;
            }
        }
        /*cout << step << "steps after -------\n";
        repp(depth, -L, L) {
            cout << "Depth " << depth << " : \n";
            print(B[L + depth]);
        }*/
    }
    // after 200 steps
    int ans = 0;
    repp(depth, -L, L) {
        rep(i, 5) rep(j, 5) {
            if(i == 2 && j == 2) continue;
            ans += (B[L + depth][i][j] == '#');
        }
    }
    return ans;
}

int main() {
    vector<string> A(5);
    rep(i, 5) cin >> A[i];
    cout << "part1 is : " << part1(A) << "\n";
    cout << "part2 is : " << part2(A) << "\n";
}
