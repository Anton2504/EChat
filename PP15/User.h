#pragma once
#include "MessageBox.h"

struct User {
    User() = default;
    User(const string& login, const string& pass, const string& name);  //�����������
    ~User() {}
    User(const User& user);
    User& operator=(const User& user);  //����������� �����������
    void SetLogin(const string& l);
    void SetPass(const string& p);
    void SetName(const string& n);
    void SetMessageBox(const string& msg);
    void SetMessageBox(string&& msg);
    string GetLogin() const;
    string GetPass() const;
    string GetName() const;
    MessageBox GetMessageBox() const;   //�������� ���� ������������ vector<string>
    bool GetAutorized() const;
    void SetAutorized(bool&& autoriz);
private:
    string _login;
    string _pass;
    string _name;
    bool _autorized = 0;        //������������� �� ������������
    MessageBox _msgs;
};