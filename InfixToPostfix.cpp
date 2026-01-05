#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
#include <set>
#include <cmath>

using namespace std;

// Check operator precedence
int precedence(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

// Check if character is an operand (a-z)
bool isOperand(char c) {
    return (c >= 'a' && c <= 'z');
}

// Convert infix expression to postfix expression using stack
string infixToPostfix(const string& infix) {
    stack<char> st;
    string postfix;

    for (char c : infix) {
        // Operand goes directly to output
        if (isOperand(c)) {
            postfix += c;
        }
        // Opening parenthesis
        else if (c == '(') {
            st.push(c);
        }
        // Closing parenthesis
        else if (c == ')') {
            while (!st.empty() && st.top() != '(') {
                postfix += st.top();
                st.pop();
            }
            if (!st.empty())
                st.pop(); // Remove '('
        }
        // Operator
        else {
            while (!st.empty() &&
                   precedence(st.top()) >= precedence(c) &&
                   !(c == '^' && st.top() == '^')) {
                postfix += st.top();
                st.pop();
            }
            st.push(c);
        }
    }

    // Pop remaining operators
    while (!st.empty()) {
        postfix += st.top();
        st.pop();
    }

    return postfix;
}

// Evaluate postfix expression using stack
double evaluatePostfix(const string& postfix,
                       unordered_map<char, double>& values) {
    stack<double> st;

    for (char c : postfix) {
        if (isOperand(c)) {
            st.push(values[c]);
        } else {
            double b = st.top(); st.pop();
            double a = st.top(); st.pop();

            switch (c) {
                case '+': st.push(a + b); break;
                case '-': st.push(a - b); break;
                case '*': st.push(a * b); break;
                case '/': st.push(a / b); break;
                case '^': st.push(pow(a, b)); break;
            }
        }
    }

    return st.top();
}

int main() {
    string infix;
    getline(cin, infix);

    // Extract UNIQUE operands in order of first appearance
    vector<char> operands;
    set<char> seen;

    for (char c : infix) {
        if (isOperand(c) && seen.count(c) == 0) {
            operands.push_back(c);
            seen.insert(c);
        }
    }

    // Read values for each operand
    unordered_map<char, double> values;
    for (char op : operands) {
        cin >> values[op];
    }

    // Convert and evaluate
    string postfix = infixToPostfix(infix);
    double result = evaluatePostfix(postfix, values);

    // Output
    cout << postfix << endl;
    cout << (int)result << endl;

    return 0;
}