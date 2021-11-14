#include <iostream>
#include<stack>
#include<string>

using namespace std;

#define MAX 50

class Stack{

    
public:
    int a[MAX];
    int top;
    
    Stack()   //constructor
    {
        top = -1;
    }
    
    bool isEmpty(){
        return top==-1;
    }
    bool isFull(){
        
        return (top > (MAX - 1));
    }
    
    void push(int value){
        if (!isFull()){
            
            a[++top] = value;
        }
        else
            cout<<"overflow is not allowed";
        
    }
    
    int pop(){
        int c;
        if(isEmpty())
        cout<<"stack underflow";
            
        else
             c = a[top];
         top--;
            return c;
    }
   
    void peak()
    {
        if(isEmpty())
            cout<<"stack is empty\n";
        else
            cout<<a[top];
    }
    
};
    
bool IsOperand(char C)
{
    if (C >= '0' && C <= '9')
        return true;
    if (C >= 'a' && C <= 'z')
        return true;
    if (C >= 'A' && C <= 'Z')
        return true;
    return false;
}

// Function to verify whether a character is operator symbol or not.
bool IsOperator(char C)
{
    if (C == '+' || C == '-' || C == '*' || C == '/' || C == '$')
        return true;

    return false;
}

// Function to verify whether an operator is right associative or not.
int IsRightAssociative(char op)
{
    if (op == '$') return true;
    return false;
}

// Function to get weight of an operator. An operator with higher weight will have higher precedence.
int GetOperatorWeight(char op)
{
    int weight = -1;
    switch (op)
    {
    case '+':
    case '-':
        weight = 1;
    case '*':
    case '/':
        weight = 2;
    case '$':
        weight = 3;
    }
    return weight;
}

// Function to perform an operation and return output.
int HasHigherPrecedence(char op1, char op2)
{
    int op1Weight = GetOperatorWeight(op1);
    int op2Weight = GetOperatorWeight(op2);

    // If operators have equal precedence, return true if they are left associative.
    // return false, if right associative.
    // if operator is left-associative, left one should be given priority.
    if (op1Weight == op2Weight)
    {
        if (IsRightAssociative(op1)) return false;
        else return true;
    }
    return op1Weight > op2Weight ? true : false;
}



// Function to evaluate Postfix expression and return output
string InfixToPostfix(string expression)
{
    // Declaring a Stack from Standard template library in C++.
    stack<char> S;
    string postfix = ""; // Initialize postfix as empty string.
    for (int i = 0; i < expression.length(); i++) {

        // Scanning each character from left.
        // If character is a delimitter, move on.
        if (expression[i] == ' ' || expression[i] == ',') continue;

        // If character is operator, pop two elements from stack, perform operation and push the result back.
        else if (IsOperator(expression[i]))
        {
            while (!S.empty() && S.top() != '(' && HasHigherPrecedence(S.top(), expression[i]))
            {
                postfix += S.top();
                S.pop();
            }
            S.push(expression[i]);
        }
        // Else if character is an operand
        else if (IsOperand(expression[i]))
        {
            postfix += expression[i];
        }

        else if (expression[i] == '(')
        {
            S.push(expression[i]);
        }

        else if (expression[i] == ')')
        {
            while (!S.empty() && S.top() != '(') {
                postfix += S.top();
                S.pop();
            }
            S.pop();
        }
    }

    while (!S.empty()) {
        postfix += S.top();
        S.pop();
    }

    return postfix;
}
    

bool IsNumericDigit(char C)
{
    if (C >= '0' && C <= '9') return true;
    return false;
}



// Function to perform an operation and return output.
int PerformOperation(char operation, int operand1, int operand2)
{
    if (operation == '+') return operand1 + operand2;
    else if (operation == '-') return operand1 - operand2;
    else if (operation == '*') return operand1 * operand2;
    else if (operation == '/') return operand1 / operand2;

    else cout << "Unexpected Error \n";
    return -1;
}

int EvaluatePostfix(string expression)
{
    // Declaring a Stack from Standard template library in C++.
    stack<int> S;

    for (int i = 0; i < expression.length(); i++) {

        // Scanning each character from left.
        // If character is a delimitter, move on.
        if (expression[i] == ' ' || expression[i] == ',') continue;

        // If character is operator, pop two elements from stack, perform operation and push the result back.
        else if (IsOperator(expression[i])) {
            // Pop two operands.
            int operand2 = S.top(); S.pop();
            int operand1 = S.top(); S.pop();
            // Perform operation
            int result = PerformOperation(expression[i], operand1, operand2);
            //Push back result of operation on stack.
            S.push(result);
        }
        else if (IsNumericDigit(expression[i])) {
            // Extract the numeric operand from the string
            // Keep incrementing i as long as you are getting a numeric digit.
            int operand = 0;
            while (i < expression.length() && IsNumericDigit(expression[i])) {
                // For a number with more than one digits, as we are scanning from left to right.
                // Everytime , we get a digit towards right, we can multiply current total in operand by 10
                // and add the new digit.
                operand = (operand * 10) + (expression[i] - '0');
                i++;
            }
            // Finally, you will come out of while loop with i set to a non-numeric character or end of string
            // decrement i because it will be incremented in increment section of loop once again.
            // We do not want to skip the non-numeric character by incrementing i twice.
            i--;

            // Push operand on stack.
            S.push(operand);
        }
    }
    // If expression is in correct format, Stack will finally have one element. This will be the output.
    return S.top();
}

    
int main() {
    // insert code here...
    string expression;
    cout << "Enter Infix Expression \n";
    getline(cin, expression);
    string postfix = InfixToPostfix(expression);
    cout << "Postfix = " << postfix << endl;
    cout << "Output = " << EvaluatePostfix("10 3+5-") << "\n";

    
    
    return 0;
}
