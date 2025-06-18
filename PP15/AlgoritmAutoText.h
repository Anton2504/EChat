#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct TTree {
    struct Node {       //Структура Ноды
        char data;
        bool end;
        Node* left;
        Node* mid;
        Node* right;
    };
    Node* CreateNode(char newData);
    void Insert(Node** root, string word, int pos = 0);
    void Traverse(Node* root, vector<string>& ret, char* buff, int depth);
    vector<string> TraverseUtil(Node* root, string pattern);
    vector<string> AutoComplete(Node* root, string pattern);
    string ChoiceWordFromTree(vector<string> sugg, string pat);
    
    Node* root = nullptr;       //Корень тернарного дерева
};