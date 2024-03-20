#include<bits/stdc++.h>
using namespace std;

double clc(char op, double left, double right = 0) {
    
    if (op == '+') 
        return left + right; 
    else if (op == '-') 
        return left - right; 
    else if (op == '*') 
        return left * right; 
    else if (op == '/') { 
        if (right != 0) 
            return left / right; 
        else {
            cout << "Error: Division by zero!" << endl; 
            return 0;
        }
    }
    else if (op == '^') 
        return pow(left, right); 
    else if (op == 's') 
        return sqrt(left); 
    else if (op == 'r')
        return round(left); 
    else if (op == 'a') 
        return abs(left);
    return 0; 
}

int opr(char op) {
    if (op == '^' || op=='r' || op == 's' || op == 'a') 
        return 3;
    else if (op == '*' || op == '/') 
        return 2; 
    else if (op == '+' || op == '-') 
        return 1; 
    return -1; 
}

int main() {
    cout << "Welcome to the Calculator!" << endl;
    char choice = 'y';
    while (choice == 'y' || choice == 'Y') {
       
        string exp;
        cout << "Please enter your arithmetic expression: ";
        getline(cin, exp);

        stack<char> s; 
        stack<double> op_s; 

        double number = 0; 
        double decimalPlace = 10;

        for (auto i = 0; i < exp.size(); i++) {
            if (isdigit(exp[i])) { 
                number = number * 10 + (exp[i] - '0'); 
            } else if (exp[i] == '.') { 
                i++; 
                while (i < exp.size() && isdigit(exp[i])) { 
                    number += (exp[i] - '0') / decimalPlace; 
                    decimalPlace *= 10; 
                    i++; 
                }
                i--; 
            } else if (exp[i] == '(') { 
                s.push('('); 
            } else if (exp[i] == ')') { 
                op_s.push(number); 
                number = 0; 
                decimalPlace = 10; 
                while (s.top() != '(') { 
                    double r = op_s.top(); 
                    op_s.pop(); 
                    double l = op_s.top(); 
                    op_s.pop();
                    double re = clc(s.top(), l, r); 
                    op_s.push(re); 
                    s.pop(); 
                }
                s.pop(); 
            } 
            else if (exp[i] == '+' ||  exp[i] == '-' ||  exp[i] == '*' || exp[i] == '/' || exp[i] == '^' || exp[i] == 's' || exp[i] == 'r' || exp[i] == 'a')
            { 
                op_s.push(number); 
                number = 0; 
                decimalPlace = 10; 

                int pC = opr(exp[i]); 
                while (!s.empty() && opr(s.top()) >= pC) { 
                    double r = op_s.top(); 
                    op_s.pop(); 
                    double l = op_s.top(); 
                    op_s.pop(); 
                    double re = clc(s.top(), l, r); 
                    op_s.push(re); 
                    s.pop(); 
                }
                s.push(exp[i]); 
            }
        }
        op_s.push(number);

        while (!s.empty()) {
            double r = op_s.top(); 
            op_s.pop(); 
            double l = op_s.top(); 
            op_s.pop(); 
            double re = clc(s.top(), l, r); 
            op_s.push(re); 
            s.pop(); 
        }
        cout << "Result:" << op_s.top() << endl;
        cout << "Do you want to continue (y/n)?";
        cin >> choice;
        
       while (cin.get() != '\n');

    }
    
    cout << "Thank you for using the calculator!" << endl; 
    return 0;
}
