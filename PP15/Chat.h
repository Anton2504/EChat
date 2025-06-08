#pragma once
#include "User.h"
#include "AlgoritmAutoText.h"
#include "SHA256.h"
#include "MySQLconn.h"
#include <string>

class Chat {
    User _cUser;            //Учётная запись текущего пользователя  
    MYSQL* _conn = nullptr;     //Коннектор bd
    unique_ptr<TTree> tree = nullptr;  //указатель на тернарное дерево (словарь)
public:

    void Start();
    void ShowUserMenu();
    void ShowChatMenu();
    void ShowAutoTextMenu();

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

    bool IsAlNumString(const string& check);        //Проверка на датинские символы
    bool CheckMaskPass(const string& pass);         //Проверка маски пароля

    MySQLconn _mysql;               //MSQL коннектор
    void SendQueryMySQL(MYSQL* mysql, const string& query);         //запрос к bd
    vector<string> SendAndResQueryMySQL(MYSQL* mysql, const string& query);
    vector<wstring> SendAndResQueryMySQL_rus(MYSQL* mysql, const string& query);   //вывод Русских букв из bd

    friend class SHA256;        //Hash класс
};