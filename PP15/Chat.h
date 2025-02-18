#pragma once
#include "User.h"

class Chat {
    vector<User> _users;    //������� ������ ���� �������������
    User _cUser;            //������� ������ �������� ������������, �������� �� AddNewUser() ��� ������������� �� ������ ������������� _users
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