#include<iostream>
void debug() { std::cout << std::endl; }
template<typename T, typename ...R> void debug (T f, R ...r) { std::cout << "[" << f << "]"; debug (r...); }

int main(){
    int i = 1, j = 2, k = 3;
    debug("hello", i, j, k, "world");
}
