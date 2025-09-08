// 2. Stack : CO1, CO2 
// Implement stack as an abstract data type using singly linked list and use this ADT for 
// conversion of infix expression to postfix, prefix 
 
#include <iostream> 
#include <string> 
#include <cctype> 
#include <algorithm> 
using namespace std; 
 
// Node structure 
struct Node { 
    char data; 
    Node* next; 
}; 
 
// Stack ADT using singly linked list 
class Stack { 
    Node* top; 
 
public: 
    Stack() { 
        top = nullptr; 
    } 
 
    void push(char val) { 
        Node* temp = new Node; 
        temp->data = val; 
        temp->next = top; 
        top = temp; 
    } 
 
    char pop() { 
        if (isEmpty()) { 
            return '\0'; 
        } 
        Node* temp = top; 
        char popped = top->data; 
        top = top->next; 
        delete temp; 
        return popped; 
    } 
 
    char peek() { 
        if (!isEmpty()) 
            return top->data; 
        return '\0'; 
    } 
 
    bool isEmpty() { 
        return top == nullptr; 
    } 
 
    ~Stack() { 
        while (!isEmpty()) 
            pop(); 
    } 
}; 
 
// Operator precedence 
int precedence(char op) { 
    if (op == '^') return 3; 
    if (op == '*' || op == '/') return 2; 
    if (op == '+' || op == '-') return 1; 
    return 0; 
} 
 
// Check if character is operator 
bool isOperator(char c) { 
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^'; 
} 
 
// Infix → Postfix conversion 
string infixToPostfix(string infix) { 
    Stack s; 
    string postfix = ""; 
 
    for (char& ch : infix) { 
        if (isalnum(ch)) { 
            postfix += ch; 
        } 
        else if (ch == '(') { 
            s.push(ch); 
        } 
        else if (ch == ')') { 
            while (!s.isEmpty() && s.peek() != '(') { 
                postfix += s.pop(); 
            } 
            s.pop(); // remove '(' 
        } 
        else if (isOperator(ch)) { 
            while (!s.isEmpty() && precedence(ch) <= precedence(s.peek())) { 
                postfix += s.pop(); 
            } 
            s.push(ch); 
        } 
    } 
 
    while (!s.isEmpty()) { 
        postfix += s.pop(); 
    } 
 
    return postfix; 
} 
 
// Infix → Prefix conversion 
string infixToPrefix(string infix) { 
    // Step 1: Reverse infix and swap ( and ) 
    reverse(infix.begin(), infix.end()); 
    for (char& ch : infix) { 
        if (ch == '(') ch = ')'; 
        else if (ch == ')') ch = '('; 
    } 
 
    // Step 2: Convert to postfix 
    string postfix = infixToPostfix(infix); 
 
    // Step 3: Reverse postfix → prefix 
    reverse(postfix.begin(), postfix.end()); 
    return postfix; 
} 
 
// MAIN FUNCTION 
int main() { 
    string infix; 
 
    cout << "Enter infix expression: "; 
    cin >> infix; 
 
    string postfix = infixToPostfix(infix); 
    string prefix = infixToPrefix(infix); 
cout << "\nPostfix: " << postfix; 
cout << "\nPrefix : " << prefix; 
return 0; 
} 