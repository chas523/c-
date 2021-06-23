#include <iostream>
#include <stack>
#include <sstream>

using namespace std;

template <typename T>
double ONP(string s){

    stack<T> stack;
    stringstream ss(s);
    std::cout << ss.str() << std::endl;
    std::string var;

    while(ss >> var){
        if(var == "+" || var == "-" || var == "*" || var == "/"){
            T x = stack.top();
            stack.pop();
            T y = stack.top();
            stack.pop();
            if (var == "+")
                stack.push(y + x);
            else if(var == "-")
                stack.push(y - x);
            else if(var == "*")
                stack.push(y * x);
            else
                stack.push(y / x);
            std::cout << stack.top() << std::endl;
        }else{
            stack.push(std::stod(var));
        }
    }

    return stack.top();
}



int main(){

    string expr="6  5  4  +  +  3  2  1  -  *  /";
    std::cout << ONP<double>(expr) << std::endl;

    return 0;
}