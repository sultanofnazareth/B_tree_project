#include <iostream>
#include "B_tree.h"
using namespace std;

int main() {
    cout << "Hello, World!" << endl;

    B_tree<char, 5> mytree;

    string testinput = "agfbkdhmjesirxclntup";

    for (char& c : testinput) {
        cout << c << endl;
        //mytree.insert(c);
    }

    mytree.insert('a');
    mytree.insert('g');
    mytree.insert('f');
    mytree.insert('b');
    mytree.insert('a');





    return 0;
}