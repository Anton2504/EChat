#pragma once
#include <iostream>
#include <vector>
using namespace std;

struct MessageBox {
    vector<string> _text;
    void push_back(const string& lhs);
    void push_back(string&& rhs);
};
