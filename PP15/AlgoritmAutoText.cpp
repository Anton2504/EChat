#pragma once
#include "AlgoritmAutoText.h"


TTree::Node* TTree::CreateNode(char newData)
{
    Node* newNode = new Node();
    newNode->data = newData;
    newNode->end = 0;
    newNode->left = nullptr;
    newNode->mid = nullptr;
    newNode->right = nullptr;
    return newNode;
}

void TTree::Insert(Node** root, string word, int pos) {
    if (!(*root))
        *root = CreateNode(word[pos]);

    if ((*root)->data > word[pos])
        Insert(&((*root)->left), word, pos);

    else if ((*root)->data < word[pos])
        Insert(&((*root)->right), word, pos);

    else {
        if (pos + 1 == word.size())
            (*root)->end = 1;
        else
            Insert(&((*root)->mid), word, pos + 1);
    }
}

void TTree::Traverse(Node* root, vector<string>& ret, char* buff, int depth = 0) {
    if (!root)
        return;
    Traverse(root->left, ret, buff, depth);
    buff[depth] = root->data;
    if (root->end) {
        buff[depth + 1] = '\0';
        ret.push_back(string(buff));
    }
    Traverse(root->mid, ret, buff, depth + 1);
    Traverse(root->right, ret, buff, depth);
}

vector<string> TTree::TraverseUtil(Node* root, string pattern) {
    char buffer[40];
    vector<string> ret;
    Traverse(root, ret, buffer);
    if (root && (root->end == 1))
        ret.push_back(pattern);
    return ret;
}

vector<string> TTree::AutoComplete(Node* root, string pattern) { 
    vector<string> words;
    int pos = 0;
    if (pattern.empty())
        return words;
    while (root && pos < pattern.length()) {

        if (root->data > pattern[pos])
            root = root->left;

        else if (root->data < pattern[pos])
            root = root->right;

        else if (root->data == pattern[pos]) {
            root = root->mid;
            pos++;
        }
        else
            return words;
    }
    words = TraverseUtil(root, pattern);
    return words;
}

string TTree::ChoiceWordFromTree(vector<string> sugg, string pat) {
    cout << "   В словаре есть следующие слова:\n";
    for (int i = 0; i < sugg.size() && i < 10; i++)             //Ограничение на вывод слов 10
        cout << "    [" << i << "] " << pat << sugg[i] << "\n";
    cout << "   Введите индекс слова которое вам подходит\n";
    int choice;
    string word;
    if (cin >> choice)
        if ((choice >= 0) && (choice < 10) && choice < sugg.size())
            word = pat + sugg[choice];
        else
            cout << "   Неверный индекс\n";
    return word;
}