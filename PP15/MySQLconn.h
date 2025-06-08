#pragma once
#include "mysql.h"

struct MySQLconn {

    MySQLconn();  //Конструктор 
    ~MySQLconn();

    MYSQL* GetConnect();

private:   
    MYSQL _conn;
};
