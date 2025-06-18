#pragma once
#include "mysql.h"
#include <string>
#include <vector>
#include <mutex>

using namespace std;

struct MySQLconn {

    MySQLconn();  //Конструктор 
    ~MySQLconn();

    MYSQL* GetConnect();


    void SendPrepareQueryBd(const string& query, const string& str_param, const int& int_param);                //два метода для потенциально опасных SQL-инъекций (Создание сообщения пользователем)
    void SendPrepareQueryBd(const string& query, const string& str_param, const int& int_param_1, const int& int_param_2);

    void SendQueryMySQL(const string& query);         //запрос к bd
    vector<string> SendAndResQueryMySQL(const string& query);
    vector<wstring> SendAndResQueryMySQL_rus(const string& query);   //вывод Русских символов из bd

private:   

    MYSQL _conn;
    MYSQL_STMT* _stmt = nullptr;
    once_flag initialized; // флаг, обозначающий, была ли инициализация
    void Init();
};
