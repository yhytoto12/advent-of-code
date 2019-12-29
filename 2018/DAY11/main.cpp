#include <bits/stdc++.h>

int powerLevel(int x, int y, int s) {
    return (((x + 10) * y + s) * (x + 10)) / 100 % 10 - 5;
}

std::string part1(int serialnum) {
    const int GRID = 300;
    std::vector<std::vector<int>> A(GRID + 1, std::vector<int> (GRID + 1));
    for(int i = 1; i <= GRID; ++i) {
        for(int j = 1; j <= GRID; ++j) {
            A[i][j] = (((i + 10) * j + serialnum) * (i + 10)) / 100 % 10 - 5;
        }
    }
    int max_power_sum = INT_MIN;
    int X = -1, Y = -1;
    for(int i = 1; i <= GRID - 2; ++i) {
        for(int j = 1; j <= GRID - 2; ++j) {
            int power_sum = 0;
            for(int u = 0; u < 3; ++u) {
                for(int v = 0; v < 3; ++v) {
                    power_sum += A[i + u][j + v];
                }
            }
            if(power_sum > max_power_sum) {
                max_power_sum = power_sum;
                X = i;
                Y = j;
            }
        }
    }
    return std::to_string(X) + "," + std::to_string(Y);
}

std::string part2(int serialnum) {
    const int GRID = 300;
    std::vector<std::vector<int>> A(GRID + 1, std::vector<int> (GRID + 1));
    for(int i = 1; i <= GRID; ++i) {
        for(int j = 1; j <= GRID; ++j) {
            A[i][j] = (((i + 10) * j + serialnum) * (i + 10)) / 100 % 10 - 5;
        }
    }
    std::vector<std::vector<int>> psum(GRID + 1, std::vector<int> (GRID + 1));
    for(int i = 1; i <= GRID; ++i) {
        for(int j = 1; j <= GRID; ++j) {
            psum[i][j] = psum[i - 1][j] + psum[i][j - 1] - psum[i - 1][j - 1] + A[i][j];
        }
    }
    int max_power_sum = INT_MIN;
    int X = -1, Y = -1, SIZE = -1;
    for(int k = 1; k <= GRID; ++k) { // k = square size
        for(int i = 1; i <= GRID - k + 1; ++i) {
            for(int j = 1; j <= GRID - k + 1; ++j) {
                int power_sum = psum[i + k - 1][j + k - 1] - psum[i + k - 1][j - 1]
                                - psum[i - 1][j + k - 1] + psum[i - 1][j - 1];
                if(power_sum > max_power_sum) {
                    max_power_sum = power_sum;
                    X = i;
                    Y = j;
                    SIZE = k;
                }
            }
        }
    }
    return std::to_string(X) + "," + std::to_string(Y) + "," + std::to_string(SIZE);
}

int main() {
    // read input
    int serialnum;
    std::cin >> serialnum;
    
    // part 1
    std::cout << "the answer of part 1 is ";
    std::cout << part1(serialnum) << std::endl;
    
    std::cout << "the answer of part 2 is ";
    std::cout << part2(serialnum) << std::endl;
}
