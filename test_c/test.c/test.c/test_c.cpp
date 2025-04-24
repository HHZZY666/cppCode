#include <iostream>
using namespace std;

class TPoint {
    int X, Y;
public:
    TPoint(int x, int y) {
        X = x;
        Y = y;
        cout << "constructor" << endl;
    }
    TPoint(TPoint& p) {
        X = p.X;
        Y = p.Y;
        cout << "Copy" << endl;
    }
    ~TPoint() {}
};

// 将返回类型修改为 void
void f(TPoint Q) {
    TPoint R(20, 30);
    cout << "In f()" << endl;
}

int main() {
    TPoint M(20, 35);
    TPoint N(M);
    f(N);
    return 0;
}