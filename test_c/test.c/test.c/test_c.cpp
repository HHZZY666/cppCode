#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class BigInt {
private:
    string num;    
    bool isNeg;   

public:
    BigInt(string s = "0") {
        if (s.empty()) s = "0";
        isNeg = (s[0] == '-');
        num = isNeg ? s.substr(1) : s;
        while (num.length() > 1 && num[0] == '0')
            num = num.substr(1);
        if (num == "0") isNeg = false;
    }

    BigInt operator+(const BigInt& b) const {
        if (isNeg == b.isNeg) {
            BigInt res;
            res.isNeg = isNeg;
            res.num = add(num, b.num);
            return res;
        }
        else {
            int cmp = compareAbs(num, b.num);
            if (cmp == 0) return BigInt("0");
            BigInt res;
            res.isNeg = (cmp > 0) ? isNeg : b.isNeg;
            res.num = (cmp > 0) ? subtract(num, b.num) : subtract(b.num, num);
            return res;
        }
    }

    BigInt operator-(const BigInt& b) const {
        BigInt nb = b;
        nb.isNeg = !b.isNeg;
        return *this + nb;
    }

    friend ostream& operator<<(ostream& os, const BigInt& b) {
        if (b.isNeg && b.num != "0") os << '-';
        os << b.num;
        return os;
    }

private:
    string add(const string& a, const string& b) const {
        string res;
        int carry = 0;
        for (int i = a.length() - 1, j = b.length() - 1;
            i >= 0 || j >= 0 || carry;
            i--, j--) {
            int sum = carry;
            if (i >= 0) sum += a[i] - '0';
            if (j >= 0) sum += b[j] - '0';
            res.push_back(sum % 10 + '0');
            carry = sum / 10;
        }
        reverse(res.begin(), res.end());
        return res;
    }

    string subtract(const string& a, const string& b) const {
        string res;
        int borrow = 0;
        for (int i = a.length() - 1, j = b.length() - 1; i >= 0; i--, j--) {
            int d = (a[i] - '0') - borrow;
            if (j >= 0) d -= (b[j] - '0');
            if (d < 0) {
                d += 10;
                borrow = 1;
            }
            else {
                borrow = 0;
            }
            res.push_back(d + '0');
        }
        reverse(res.begin(), res.end());
        while (res.length() > 1 && res[0] == '0')
            res = res.substr(1);
        return res;
    }

    int compareAbs(const string& a, const string& b) const {
        if (a.length() != b.length())
            return a.length() > b.length() ? 1 : -1;
        return a.compare(b);
    }
};

int main() {
    BigInt a("12345678901234567890");
    BigInt b("98765432109876543210");
    BigInt c("-50000000000000000000");

    cout << "a + b = " << a + b << endl;
    cout << "a - b = " << a - b << endl;
    cout << "b - a = " << b - a << endl;
    cout << "a + c = " << a + c << endl;
    cout << "a - c = " << a - c << endl;
    cout << "c - a = " << c - a << endl;

    return 0;
}