#include <iostream>
#include "B_tree.h"
using namespace std;

int main() {
    cout << "Hello, World!" << endl;

    B_tree<int, 5> mytree;

    mytree.insert(5);

    return 0;
}