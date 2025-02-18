#pragma once
#include "User.h"

class Chat {
    vector<User> _users;    //Учётные записи всех пользователей
    User _cUser;            //Учётная запись текущего пользователя, создаётся из AddNewUser() или присваевается из списка пользователей _users
    vector<string> _chatMsg;
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
    void SendMessage();
    void MyMessages();
    void ShowAllUsers();    
    void SendChatMsg();
    void ShowChatMsg();
};