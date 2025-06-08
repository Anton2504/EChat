#include "MySQLconn.h"
#include <iostream>

MySQLconn::MySQLconn()  {

    mysql_init(&_conn);
    if (!&_conn) {
        std::cout << "Error: can't create MySQL-descriptor" << std::endl;
    }
    if (!mysql_real_connect(&_conn, "localhost", "root", "qwerty", "echat_db", 0, NULL, 0)) {
        std::cout << "Error: can't connect to database " << mysql_error(&_conn) << std::endl;
    }
    mysql_set_character_set(&_conn, "utf8mb4");
}

MySQLconn::~MySQLconn() {    mysql_close(&_conn);    }

MYSQL* MySQLconn::GetConnect()  {    return &_conn;     }
