//
// Created by anton on 23.04.2017.
//

#include <iostream>
#include "Vector.h"

using namespace std;

int main() {
    Vector<int> a;
    a.push_back(4);
    a.push_back(7);
    a.push_back(17);
    a.push_back(0);
    a.push_back(1);
    a.push_back(42);
    a.push_back(73);
    a.push_back(7);
    a.push_back(5);
    a.push_back(10);
    Vector<int>::reverse_iterator it;
    for (it = a.rbegin(); it != a.rend(); it++)
        cout << *it << ' ';
    return 0;
}
