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
