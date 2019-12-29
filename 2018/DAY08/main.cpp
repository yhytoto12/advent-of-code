#include <bits/stdc++.h>

int foo(std::vector<int> &A, int i, int &sum) {
    int idx = i + 2;
    for(int k = 0; k < A[i]; ++k) {
        idx = foo(A, idx, sum);
    }
    for(int j = 0; j < A[i + 1]; ++j) {
        sum += A[idx + j];
    }
    return idx + A[i + 1];
}

int part1(std::vector<int> &A) {
    int sum = 0;
    foo(A, 0, sum);
    return sum;
}

int boo(std::vector<int> &A, int i, std::vector<int> &value, int &n) {
    int idx = i + 2;
    int currNode = n;
    std::vector<int> ref(A[i]);
    for(int k = 0; k < A[i]; ++k) {
    	ref[k] = ++n;
        idx = boo(A, idx, value, n);
    }
    if(idx == i + 2) { // no child
        for(int j = 0; j < A[i + 1]; ++j) {
            value[currNode] += A[idx + j];
        }
    } else { // exist child
        for(int j = 0; j < A[i + 1]; ++j) {
        	if(A[idx + j] > 0 && A[idx + j] <= A[i]) value[currNode] += value[ref[A[idx + j] - 1]];
        }
    }
    return idx + A[i + 1];
}

int part2(std::vector<int> &A) {
    std::vector<int> value(10000);
    int n = 0;
    boo(A, 0, value, n);
    return value[0];
}

int main() {
    // read input
    std::vector<int> A;
    int x; while(std::cin >> x) A.push_back(x);
    
    // part 1
    std::cout << "the answer of part 1 is ";
    std::cout << part1(A) << std::endl;
    
    // part 2
    std::cout << "the answer of part 2 is ";
    std::cout << part2(A) << std::endl;
}
