/*
 * Name: Laraib Fatima
 * CMS ID: 542052
 * Course: CS-250: Data Structures and Algorithms
 * Lab 6: Stacks and Queues - Task 1
 * Date: 12th October 2025
 * Instructor: Dr. Fahad Ahmed Satti
 * Lab Engineer: Hassan Mohtashim
 * Description: Simple implementation of expression conversion and evaluation.
 */

#include <iostream>
#include <string>
#include <cctype>
#include <cmath>
#include <algorithm>

using namespace std;

// 1. Simple Character Stack
class CharStack {
private:
    struct Node {
        char data;
        Node* next;
        Node(char val) {
            data = val;
            next = nullptr;
        }
    };
    Node* topNode;

public:
    CharStack() { topNode = nullptr; }

    void push(char val) {
        Node* newNode = new Node(val);
        newNode->next = topNode;
        topNode = newNode;
    }

    char pop() {
        if (isEmpty()) return '\0';
        Node* temp = topNode;
        char val = temp->data;
        topNode = topNode->next;
        delete temp;
        return val;
    }

    char peek() {
        if (isEmpty()) return '\0';
        return topNode->data;
    }

    bool isEmpty() {
        return topNode == nullptr;
    }
};

// 2. Simple Double Stack 
class DoubleStack {
private:
    struct Node {
        double data;
        Node* next;
        Node(double val) {
            data = val;
            next = nullptr;
        }
    };
    Node* topNode;

public:
    DoubleStack() { topNode = nullptr; }

    void push(double val) {
        Node* newNode = new Node(val);
        newNode->next = topNode;
        topNode = newNode;
    }

    double pop() {
        if (isEmpty()) return 0;
        Node* temp = topNode;
        double val = temp->data;
        topNode = topNode->next;
        delete temp;
        return val;
    }

    bool isEmpty() {
        return topNode == nullptr;
    }
};

// 3. Simple String Stack 
class StringStack {
private:
    struct Node {
        string data;
        Node* next;
        Node(string val) {
            data = val;
            next = nullptr;
        }
    };
    Node* topNode;

public:
    StringStack() { topNode = nullptr; }

    void push(string val) {
        Node* newNode = new Node(val);
        newNode->next = topNode;
        topNode = newNode;
    }

    string pop() {
        if (isEmpty()) return "";
        Node* temp = topNode;
        string val = temp->data;
        topNode = topNode->next;
        delete temp;
        return val;
    }

    bool isEmpty() {
        return topNode == nullptr;
    }
};

// Function for operator precedence
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

// Infix to Postfix function
string infix_to_postfix(string expr) {
    CharStack s;
    string result = "";
    
    for (int i = 0; i < expr.length(); i++) {
        char c = expr[i];
        
        if (isalnum(c)) {
            result += c;
        } 
        else if (c == '(') {
            s.push(c);
        } 
        else if (c == ')') {
            while (!s.isEmpty() && s.peek() != '(') {
                result += s.pop();
            }
            s.pop(); 
        } 
        else {
            while (!s.isEmpty() && precedence(s.peek()) >= precedence(c)) {
                result += s.pop();
            }
            s.push(c);
        }
    }
    
    while (!s.isEmpty()) {
        result += s.pop();
    }
    
    return result;
}

// Infix to Prefix function
string infix_to_prefix(string expr) {
    string rev = "";
    for (int i = expr.length() - 1; i >= 0; i--) {
        if (expr[i] == '(') rev += ')';
        else if (expr[i] == ')') rev += '(';
        else rev += expr[i];
    }
    
    string postfix = infix_to_postfix(rev);
    reverse(postfix.begin(), postfix.end());
    return postfix;
}

// Postfix to Infix function
string postfix_to_infix(string expr) {
    StringStack s;
    
    for (int i = 0; i < expr.length(); i++) {
        char c = expr[i];
        
        if (isalnum(c)) {
            s.push(string(1, c));
        } else {
            string op2 = s.pop();
            string op1 = s.pop();
            string temp = "(" + op1 + c + op2 + ")";
            s.push(temp);
        }
    }
    
    if (s.isEmpty()) return "";
    return s.pop();
}

// Evaluate Postfix function
double evaluate_postfix(string expr) {
    DoubleStack s;
    
    for (int i = 0; i < expr.length(); i++) {
        char c = expr[i];
        
        if (isdigit(c)) {
            s.push(c - '0'); // Convert char to number
        } else {
            double val2 = s.pop();
            double val1 = s.pop();
            
            if (c == '+') s.push(val1 + val2);
            else if (c == '-') s.push(val1 - val2);
            else if (c == '*') s.push(val1 * val2);
            else if (c == '/') s.push(val1 / val2);
            else if (c == '^') s.push(pow(val1, val2));
        }
    }
    
    if (s.isEmpty()) {
        return 0;
    }
    return s.pop();
}

// Evaluate Prefix function
double evaluate_prefix(string expr) {
    DoubleStack s;
    
    for (int i = expr.length() - 1; i >= 0; i--) {
        char c = expr[i];
        
        if (isdigit(c)) {
            s.push(c - '0');
        } else {
            double val1 = s.pop();
            double val2 = s.pop();
            
            if (c == '+') s.push(val1 + val2);
            else if (c == '-') s.push(val1 - val2);
            else if (c == '*') s.push(val1 * val2);
            else if (c == '/') s.push(val1 / val2);
            else if (c == '^') s.push(pow(val1, val2));
        }
    }
    
    if (s.isEmpty()) {
        return 0;
    }
    return s.pop();
}

int main() {
    string userExpr;
    cout << "Enter an infix expression: ";
    cin >> userExpr;

    string post = infix_to_postfix(userExpr);
    string pref = infix_to_prefix(userExpr);

    cout << "\n--- Results ---" << endl;
    cout << "Postfix: " << post << endl;
    cout << "Prefix: " << pref << endl;
    cout << "Evaluated Postfix: " << evaluate_postfix(post) << endl;
    cout << "Evaluated Prefix: " << evaluate_prefix(pref) << endl;

    return 0;
}