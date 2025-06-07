#pragma once
#include "User.h"
#include "AlgoritmAutoText.h"
#include "SHA256.h"
#include "mysql.h"
#include <string>

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
    bool CheckPass();
    void AddNewUser();
    void CreateLogin();
    void CreatePassword();
    void CreateName();
    string CreateMessage();
    string CreateAutoTextMsg(const string& pat);
    void SendMessage();
    void MyMessages();
    void ShowAllUsers();    
    void SendChatMsg();
    void ShowChatMsg();
    void SendQueryMySQL(const string& query);
    vector<string> SendAndResQueryMySQL(const string& query);
    bool IsAlNumString(const string& check);
    bool CheckMaskPass(const string& pass);
    void ShowAutoTextMenu();


    friend class SHA256;        //Hash класс
};