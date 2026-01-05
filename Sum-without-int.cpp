#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

string addStrings(string a, string b) {
    int carry = 0;
    string res = "";
    while (a.size() < b.size()) a = "0" + a;
    while (b.size() < a.size()) b = "0" + b;
    for (int i = a.size() - 1; i >= 0; i--) {
        int sum = (a[i] - '0') + (b[i] - '0') + carry;
        carry = sum / 10;
        res = char(sum % 10 + '0') + res;
    }
    if (carry) res = "1" + res;
    return res;
}

string Sum(string num1, string num2) {
    string numS[2] = {num1, num2};
    string intS[2] = {"", ""};
    string decS[2] = {"", ""};

    for (int i = 0; i < 2; i++) {
        if (numS[i].empty()) numS[i] = "0.0";
        if (numS[i].find('.') == string::npos) numS[i] += ".0";
    }

    for (int i = 0; i < 2; i++) {
        bool pot = false;
        for (char c : numS[i]) {
            if (c == '.') pot = true;
            else {
                if (pot) decS[i] += c;
                else intS[i] += c;
            }
        }
        if (decS[i].empty()) decS[i] = "0";
    }

    int maxFrac = max(decS[0].length(), decS[1].length());
    for (int i = 0; i < 2; i++)
        while ((int)decS[i].length() < maxFrac)
            decS[i] += "0";

    string sumDec = addStrings(decS[0], decS[1]);
    string carry = "0";
    if ((int)sumDec.size() > maxFrac) {
        carry = sumDec.substr(0, sumDec.size() - maxFrac);
        sumDec = sumDec.substr(sumDec.size() - maxFrac);
    }

    string sumInt = addStrings(intS[0], intS[1]);
    if (carry != "0")
        sumInt = addStrings(sumInt, carry);

    return sumInt + "." + sumDec;
}

int main() {
    string num1, num2;
    cin >> num1 >> num2;
    cout << Sum(num1, num2);
    return 0;
}
