#include <bits/stdc++.h>
#include "Vector2D.cpp"
using namespace std;

int main(){
    Vector2D a(5,5);
    Vector2D b(1,20);
    Vector2D c = a.project(b);
    cout << "X - " << c.x << " Y - " << c.y << "\n";

    
    cout << "hello";
}
