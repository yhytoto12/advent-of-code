#include <bits/stdc++.h>

struct Point {
    int x, y;
    Point(int x1 = 0, int y1 = 0) : x(x1), y(y1) {}
};

int distance(const Point &a, const Point &b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

int findNearest(std::vector<Point> &P, Point a) {
    int dmin = INT_MAX;
    std::vector<int> nearest;
    for(int k = 0; k < (int)P.size(); ++k) {
        int d = distance(a, P[k]);
        if(d < dmin) {
            dmin = d;
            nearest = {k};
        } else if(d == dmin) {
            nearest.push_back(k);
        }
    }
    if(nearest.size() == 1) return nearest[0];
    else return -1;
}

int part1(std::vector<Point> &P) {
    int N = P.size();
    int xmin = INT_MAX, xmax = INT_MIN;
    int ymin = INT_MAX, ymax = INT_MIN;
    for(int i = 0; i < N; ++i) {
        xmin = std::min(xmin, P[i].x);
        ymin = std::min(ymin, P[i].y);
        xmax = std::max(xmax, P[i].x);
        ymax = std::max(ymax, P[i].y);
    }
    
    std::vector<int> area(N);
    std::vector<bool> infinite(N);
    for(int i = xmin - 1; i <= xmax + 1; ++i) {
        for(int j = ymin - 1; j <= ymax + 1; ++j) {
            int k = findNearest(P, {i, j});
            if(i >= xmin && i <= xmax && j >= ymin && j <= ymax) {
                if(k == -1) continue;
                else area[k]++;
            } else {
                if(k == -1) continue;
                else infinite[k] = true;
            }
        }
    }
    int largestArea = -1;
    for(int i = 0; i < N; ++i) {
        if(!infinite[i]) largestArea = std::max(largestArea, area[i]);
    }
    return largestArea;
}

int part2(std::vector<Point> &P) {
    int N = P.size();
    int xmin = INT_MAX, xmax = INT_MIN;
    int ymin = INT_MAX, ymax = INT_MIN;
    for(int i = 0; i < N; ++i) {
        xmin = std::min(xmin, P[i].x);
        ymin = std::min(ymin, P[i].y);
        xmax = std::max(xmax, P[i].x);
        ymax = std::max(ymax, P[i].y);
    }
    int OFFSET = 500;
    int ans = 0;
    for(int i = xmin - OFFSET; i <= xmax + OFFSET; ++i) {
        for(int j = ymin - OFFSET; j <= ymax + OFFSET; ++j) {
            int sumDistance = 0;
            for(int k = 0; k < N; ++k) {
                sumDistance += distance(Point(i, j), P[k]);
            }
            if(sumDistance < 10000) ans++;
        }
    }
    return ans;
}

int main() {
    // read input
    std::string str;
    std::vector<Point> P;
    while(std::getline(std::cin, str)) {
        int comma = str.find(',');
        Point p(stoi(str.substr(0, comma)), stoi(str.substr(comma + 2)));
        P.push_back(p);
    }
    // part 1
    std::cout << "the answer of part 1 is ";
    std::cout << part1(P) << std::endl;
    
    // part 2
    std::cout << "the answer of part 2 is ";
    std::cout << part2(P) << std::endl;
}
