#include <vector>
#include <iostream>

using namespace std;

int main (){
    vector<int> test = {2, 1, 2, 6, 2, 4, 3, 3};
    for (size_t i = 0 ; i < test.size(); ++i)
        cout << test[i] << " ";
    cout << "\n";
}
