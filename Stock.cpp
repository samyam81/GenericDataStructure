#include <iostream>
#include <stack>
#include <string>
#include <stdexcept>

using namespace std; 

template<typename T>
class GenericStack {

private:
    stack<T> stack; 
public:
    GenericStack() {}

    
    void push(T t) {
        stack.push(t);
    }

   
    T pop() {
        if (stack.empty()) {
            throw runtime_error("Stack is empty"); /
        }
        T top = stack.top();
        stack.pop();
        return top;
    }
};
