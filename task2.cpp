/*
 * Name: Laraib Fatima
 * CMS ID: 542052
 * Course: CS-250: Data Structures and Algorithms
 * Lab 6: Stacks and Queues - Task 2
 * Date: 12th October 2025
 * Instructor: Dr. Fahad Ahmed Satti
 * Lab Engineer: Hassan Mohtashim
 * Description: Bracket and HTML/XML tag validator using simple stacks.
 */

#include <iostream>
#include <string>

using namespace std;

// Character Stack for Brackets
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

    bool isEmpty() {
        return topNode == nullptr;
    }
};

// String Stack for HTML/XML tags
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

// Part A: Bracket Validator function
bool isValidBrackets(string s) {
    CharStack st;
    
    for (int i = 0; i < s.length(); i++) {
        char c = s[i];
        
        // Push opening brackets
        if (c == '(' || c == '{' || c == '[') {
            st.push(c);
        } 
        // Check closing brackets
        else if (c == ')' || c == '}' || c == ']') {
            if (st.isEmpty()) return false;
            
            char top = st.pop();
            if ((c == ')' && top != '(') ||
                (c == '}' && top != '{') ||
                (c == ']' && top != '[')) {
                return false;
            }
        }
    }
    return st.isEmpty();
}

// Part B: HTML/XML Tag Validator function 
bool validate_markup(string s) {
    StringStack st;
    bool hasError = false;
    int i = 0;
    
    while (i < s.length()) {
        if (s[i] == '<') {
            int j = s.find('>', i);
            if (j == string::npos) {
                cout << "Error: Unclosed tag bracket found." << endl;
                return false;
            }
            
            string tag = s.substr(i + 1, j - i - 1);
            
            // Check if it's a closing tag
            if (!tag.empty() && tag[0] == '/') {
                string tagName = tag.substr(1);
                if (st.isEmpty()) {
                    cout << "Error: Unexpected closing tag </" << tagName << ">" << endl;
                    hasError = true;
                } else {
                    string openTag = st.pop();
                    if (openTag != tagName) {
                        cout << "Error: Mismatched tag. Opened <" << openTag << "> but closed </" << tagName << ">" << endl;
                        hasError = true;
                    }
                }
            } 
            else {
                st.push(tag);
            }
            i = j;
        }
        i++;
    }
    
    while (!st.isEmpty()) {
        cout << "Error: Unclosed tag <" << st.pop() << ">" << endl;
        hasError = true;
    }
    
    return !hasError;
}

int main() {
    string bracketExpr;
    cout << "Enter a bracket expression: ";
    cin >> bracketExpr;
    
    if (isValidBrackets(bracketExpr)) {
        cout << "Brackets are balanced and valid!\n" << endl;
    } else {
        cout << "Brackets are NOT balanced!\n" << endl;
    }

    string htmlExpr;
    cout << "Enter HTML/XML string: ";
    cin.ignore();
    getline(cin, htmlExpr);
    
    cout << "\nValidating HTML/XML..." << endl;
    if (validate_markup(htmlExpr)) {
        cout << "HTML/XML markup is valid!" << endl;
    } else {
        cout << "HTML/XML markup is invalid!" << endl;
    }

    return 0;
}