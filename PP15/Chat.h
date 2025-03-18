#pragma once
#include "User.h"
#include "AlgoritmAutoText.h"

class Chat {
    vector<User> _users;    //Учётные записи всех пользователей
    User _cUser;            //Учётная запись текущего пользователя, создаётся из AddNewUser() или присваевается из списка пользователей _users
    vector<string> _chatMsg;
    unique_ptr<TTree> tree = nullptr;  //указатель на тернарное дерево (словарь)
public:
    void Start();
    void ShowMain();
    void ShowUserMenu();
    void ShowChatMenu();
    void LogIn();
    bool CheckPass(const User& user);
    void AddNewUser();
    string CreateLogin();
    string CreatePassword();
    string CreateName();
    string CreateMessage();
    string CreateAutoTextMsg(const string& pat);
    void SendMessage();
    void MyMessages();
    void ShowAllUsers();    
    void SendChatMsg();
    void ShowChatMsg();
};