#include <bits/stdc++.h>

using namespace std;

int main() {
    vector<int> a;
    int x;
    while(cin >> x) {
        a.push_back(x);
    }
    int i = 0;
    int input = 5, output = 0;
    while(a[i] != 99) {
        int opcode = a[i] % 100;
        int first = a[i] / 100 % 10;
        int second = a[i] / 1000 % 10;
        int third = a[i] / 10000 % 10;
        int x = (first == 1) ? a[i + 1] : a[a[i + 1]];
        int y = (second == 1) ? a[i + 2] : a[a[i + 2]];
        switch(opcode) {
            case 1 :
                a[a[i + 3]] = x + y;
                i += 4;
                break;
            case 2 :
                a[a[i + 3]] = x * y;
                i += 4;
                break;
            case 3 :
                a[a[i + 1]] = input;
                i += 2;
                break;
            case 4 :
                output = x;
                i += 2;
                if(output != 0 && a[i] != 99) {
                    cout << "ERROR! output isn't zero : " << output << "\n";
                }
                break;
            case 5:
                if(x != 0) i = y;
                else i += 3;
                break;
            case 6 :
                if(x == 0) i = y;
                else i += 3;
                break;
            case 7 : 
                a[a[i + 3]] = (x < y) ? 1 : 0;
                i += 4;
                break;
            case 8:
                a[a[i + 3]] = (x == y) ? 1 : 0;
                i += 4;
                break;
            default :
                cout << "ERROR\n";
        }
    }
    cout << output << "\n";
}
