#include <bits/stdc++.h>
using namespace std;

int calculate(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        case '%': return a % b;
        default: throw invalid_argument("Invalid operator");
    }
}

int main() {
    string input;
    cout << "Enter an arithmetic expression: ";
    getline(cin, input);

    istringstream iss(input);
    char op;
    stack<int> numStack;
    stack<char> opStack;

    while (iss >> op) {
        if (isdigit(op)) {
            iss.putback(op);
            int num;
            iss >> num;
            numStack.push(num);
        } else if (op == '(') {
            opStack.push(op);
        } else if (op == ')') {
            while (!opStack.empty() && opStack.top() != '(') {
                char oper = opStack.top();
                opStack.pop();
                if (oper == 's') { 
                    int num = numStack.top();
                    numStack.pop();
                    if (num < 0)
                        throw invalid_argument("Cannot calculate square root of a negative number");
                    numStack.push(sqrt(num));
                } else if (oper == '^') { 
                    int exponent = numStack.top();
                    numStack.pop();
                    int base = numStack.top();
                    numStack.pop();
                    numStack.push(pow(base, exponent));
                } else { 
                    int b = numStack.top();
                    numStack.pop();
                    int a = numStack.top();
                    numStack.pop();
                    numStack.push(calculate(a, b, oper));
                }
            }
            opStack.pop(); 
        } else {
            opStack.push(op);
        }
    }

    while (!opStack.empty()) {
        char oper = opStack.top();
        opStack.pop();
        if (oper == 's') { 
            int num = numStack.top();
            numStack.pop();
            if (num < 0)
                throw invalid_argument("Cannot calculate square root of a negative number");
            numStack.push(sqrt(num));
        } else if (oper == '^') { 
            int exponent = numStack.top();
            numStack.pop();
            int base = numStack.top();
            numStack.pop();
            numStack.push(pow(base, exponent));
        } else { 
            int b = numStack.top();
            numStack.pop();
            int a = numStack.top();
            numStack.pop();
            numStack.push(calculate(a, b, oper));
        }
    }

    if (numStack.size() == 1) {
        cout << "Result: " << numStack.top() << endl;
    } else {
        cout << "Invalid expression" << endl;
    }

    return 0;
}
