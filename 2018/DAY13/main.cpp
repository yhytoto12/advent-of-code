#include <bits/stdc++.h>



struct Cart {
    const static int GO = 0;
    const static int LEFT = 3;
    const static int RIGHT = 1;
    int id;
    int x, y;
    int dir;
    int istate;
    bool crashed = false;
    Cart(int ID, int X, int Y, int DIR, int ISTATE = LEFT) {
        id = ID;
        x = X; y = Y;
        dir = DIR;
        istate = ISTATE;
    }
    bool operator<(const Cart c) {
        return id < c.id;
    }
    
    void setNextState() {
        if(istate == LEFT) istate = GO;
        else if(istate == GO) istate = RIGHT;
        else istate = LEFT;
    }
};

int dx[] = {0, 1, 0, -1};
int dy[] = {-1, 0, 1, 0};
int DIR[] = {'^', '>', 'v', '<'};

std::string part1(std::vector<std::string> &A, std::vector<std::vector<int>> isCartHere, std::vector<Cart> carts) {
    bool collision = false;
    int collisionX = -1, collisionY = -1;
    while(!collision) {
        for(auto &cart : carts) {
            int cx = cart.x, cy = cart.y;
            int nx = cart.x + dx[cart.dir], ny = cart.y + dy[cart.dir];
            isCartHere[cy][cx] = -1;
            if(isCartHere[ny][nx] != -1) {
                // collision!!!
                collision = true;
                collisionX = nx;
                collisionY = ny;
                break;
            }
            cart.x = nx;
            cart.y = ny;
            if(A[ny][nx] == '+') {
                cart.dir = (cart.dir + cart.istate) % 4;
                cart.setNextState();
            } else {
                if(A[ny][nx] == '/') {
                    if(cart.dir == 0 || cart.dir == 2) {
                        cart.dir = (cart.dir + 1) % 4;
                    } else {
                        cart.dir = (cart.dir + 3) % 4;
                    }
                } else if(A[ny][nx] == '\\') {
                    if(cart.dir == 0 || cart.dir == 2) {
                        cart.dir = (cart.dir + 3) % 4;
                    } else {
                        cart.dir = (cart.dir + 1) % 4;
                    }
                }
            }
            isCartHere[ny][nx] = cart.id;
        }
        /*for(int i = 0; i < R; ++i) {
            for(int j = 0; j < C; ++j) {
                if(isCartHere[i][j] != -1) std::cerr << (char)DIR[carts[isCartHere[i][j]].dir];
                else std::cerr << A[i][j];
            }
            std::cerr << std::endl;
        }
        std::cerr << std::endl;*/
    }
    return std::to_string(collisionX) + "," + std::to_string(collisionY);
}

std::string part2(std::vector<std::string> &A, std::vector<std::vector<int>> isCartHere, std::vector<Cart> carts) {
    int remainCarts = carts.size();
    while(remainCarts > 1) {
        for(auto &cart : carts) {
            if(cart.crashed) continue;
            int cx = cart.x, cy = cart.y;
            int nx = cart.x + dx[cart.dir], ny = cart.y + dy[cart.dir];
            isCartHere[cy][cx] = -1;
            if(isCartHere[ny][nx] != -1) {
                // collision!!!
                cart.crashed = true;
                carts[isCartHere[ny][nx]].crashed = true;
                isCartHere[ny][nx] = -1;
                remainCarts -= 2;
                continue;
            }
            cart.x = nx;
            cart.y = ny;
            if(A[ny][nx] == '+') {
                cart.dir = (cart.dir + cart.istate) % 4;
                cart.setNextState();
            } else {
                if(A[ny][nx] == '/') {
                    if(cart.dir == 0 || cart.dir == 2) {
                        cart.dir = (cart.dir + 1) % 4;
                    } else {
                        cart.dir = (cart.dir + 3) % 4;
                    }
                } else if(A[ny][nx] == '\\') {
                    if(cart.dir == 0 || cart.dir == 2) {
                        cart.dir = (cart.dir + 3) % 4;
                    } else {
                        cart.dir = (cart.dir + 1) % 4;
                    }
                }
            }
            isCartHere[ny][nx] = cart.id;
        }
    }
    // remain cart
    int X = -1, Y = -1;
    for(auto &cart : carts) {
        if(!cart.crashed) {
            X = cart.x;
            Y = cart.y;
            break;
        }
    }
    return std::to_string(X) + "," + std::to_string(Y);
}
int main() {
    // read input
    std::vector<std::string> A;
    std::string str;
    while(std::getline(std::cin, str)) {
        A.push_back(str);
    }
    std::vector<Cart> carts;
    int R = A.size();
    int C = A[0].size();
    int N = 0;
    std::vector<std::vector<int>> isCartHere(R, std::vector<int>(C, -1));
    for(int i = 0; i < R; ++i) {
        for(int j = 0; j < C; ++j) {
            if(A[i][j] == '^') {
                isCartHere[i][j] = N;
                Cart c(N++, j, i, 0);
                carts.push_back(c);
                A[i][j] = '|';
            } else if(A[i][j] == '>') {
                isCartHere[i][j] = N;
                Cart c(N++, j, i, 1);
                carts.push_back(c);
                A[i][j] = '-';
            } else if(A[i][j] == 'v') {
                isCartHere[i][j] = N;
                Cart c(N++, j, i, 2);
                carts.push_back(c);
                A[i][j] = '|';
            } else if(A[i][j] == '<') {
                isCartHere[i][j] = N;
                Cart c(N++, j, i, 3);
                carts.push_back(c);
                A[i][j] = '-';
            }
        }
    }
    
    // part 1
    std::cout << "the answer of part 1 is ";
    std::cout << part1(A, isCartHere, carts) << std::endl;
    
    // part 2
    std::cout << "the answer of part 2 is ";
    std::cout << part2(A, isCartHere, carts) << std::endl;
}
