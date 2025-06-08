#pragma once
#include <iostream>

using namespace std;

struct User {
    User() = default;
    User(const string& login, const string& pass, const string& name);  //Конструктор
    ~User() {}
    User(const User& user);
    User& operator=(const User& user);  //Конструкоры копирования
    void SetLogin(const string& l);
    void SetPass(const string& p);
    void SetName(const string& n);
    string GetLogin() const;
    string GetPass() const;
    string GetName() const;
    bool GetAutorized() const;
    bool GetAutoText() const;
    void SetAutorized(bool&& autoriz);
    void SetAutoText(bool&& autotext);
private:
    string _login;
    string _pass;               //Хранит хеш пароля (SHA256)
    string _name;
    bool _autotext = 0;         //Функция автотекста
    bool _autorized = 0;        //Авторизирован ли пользователь
};