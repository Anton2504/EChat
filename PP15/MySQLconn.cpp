#include "MySQLconn.h"
#include <iostream>
#include <codecvt> // Для кодировки w_char

MySQLconn::MySQLconn()  {}

void MySQLconn::Init() {
    mysql_init(&_conn);
    if (!&_conn) {
        cout << "Error: can't create MySQL-descriptor" << endl;
    }
    if (!mysql_real_connect(&_conn, "localhost", "root", "qwerty", "echat_db", 0, NULL, 0)) {
        cout << "Error: can't connect to database " << mysql_error(&_conn) << endl;
    }
    mysql_set_character_set(&_conn, "utf8mb4");
}

void MySQLconn::SendPrepareQueryBd(const string& query, const string& str_param, const int& int_param) {
    call_once(initialized, &MySQLconn::Init, this);

    MYSQL_BIND bind[2];
    int id = int_param;
    unsigned long name_len = strlen(str_param.c_str());
    const char* sql = query.c_str();

    memset(bind, 0, sizeof(bind));

    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char*)str_param.c_str();
    bind[0].buffer_length = strlen(str_param.c_str());
    bind[0].length = &name_len;

    bind[1].buffer_type = MYSQL_TYPE_LONG;
    bind[1].buffer = &id;

    _stmt = mysql_stmt_init(&_conn);
    if (!_stmt) {
        cout << "mysql_stmt_init() failed" << endl;
        return;
    }
    if (mysql_stmt_prepare(_stmt, sql, strlen(query.c_str()))) {
        cout << "mysql_stmt_prepare() failed: " << mysql_stmt_error(_stmt) << endl;
        mysql_stmt_close(_stmt);
        return;
    }
    if (mysql_stmt_bind_param(_stmt, bind)) {
        cout << "mysql_stmt_bind_param() failed: " << mysql_stmt_error(_stmt) << endl;
        mysql_stmt_close(_stmt);
    }
    if (mysql_stmt_execute(_stmt)) {
        cout << "mysql_stmt_execute() failed: " << mysql_stmt_error(_stmt) << endl;
        mysql_stmt_close(_stmt);
        return;
    }
    mysql_stmt_close(_stmt);
    return;
}

void MySQLconn::SendPrepareQueryBd(const string& query, const string& str_param, const int& int_param_1, const int& int_param_2) {
    call_once(initialized, &MySQLconn::Init, this);

    MYSQL_BIND bind[3];
    int id_s = int_param_1;
    int id_r = int_param_2;
    unsigned long name_len = strlen(str_param.c_str());
    const char* sql = query.c_str();

    memset(bind, 0, sizeof(bind));

    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char*)str_param.c_str();
    bind[0].buffer_length = strlen(str_param.c_str());
    bind[0].length = &name_len;

    bind[1].buffer_type = MYSQL_TYPE_LONG;
    bind[1].buffer = &id_s;

    bind[2].buffer_type = MYSQL_TYPE_LONG;
    bind[2].buffer = &id_r;

    _stmt = mysql_stmt_init(&_conn);
    if (!_stmt) {
        cout << "mysql_stmt_init() failed" << endl;
        return;
    }
    if (mysql_stmt_prepare(_stmt, sql, strlen(query.c_str()))) {
        cout << "mysql_stmt_prepare() failed: " << mysql_stmt_error(_stmt) << endl;
        mysql_stmt_close(_stmt);
        return;
    }
    if (mysql_stmt_bind_param(_stmt, bind)) {
        cout << "mysql_stmt_bind_param() failed: " << mysql_stmt_error(_stmt) << endl;
        mysql_stmt_close(_stmt);
    }
    if (mysql_stmt_execute(_stmt)) {
        cout << "mysql_stmt_execute() failed: " << mysql_stmt_error(_stmt) << endl;
        mysql_stmt_close(_stmt);
        return;
    }
    mysql_stmt_close(_stmt);
    return;
}

void MySQLconn::SendQueryMySQL(const string& query) {
    call_once(initialized, &MySQLconn::Init, this);
    mysql_query(&_conn, query.c_str());
}

vector<string> MySQLconn::SendAndResQueryMySQL(const string& query) {
    call_once(initialized, &MySQLconn::Init, this);
    string row_string;
    vector<string> result;
    MYSQL_RES* res;
    MYSQL_ROW row;
    mysql_query(&_conn, query.c_str());
    if (res = mysql_store_result(&_conn)) {
        while (row = mysql_fetch_row(res)) {
            row_string.clear();
            for (size_t i = 0; i < mysql_num_fields(res); i++) {
                if (row[i]) {
                    row_string = row_string + row[i] + "  ";
                }
                else {
                    row_string = row_string + "No data" + "  ";
                }
            }
            result.push_back(row_string);
        }
    }
    else
        cout << "Ошибка MySql номер " << mysql_error(&_conn);
    mysql_free_result(res);
    return result;
}

vector<wstring> MySQLconn::SendAndResQueryMySQL_rus(const string& query) {
    call_once(initialized, &MySQLconn::Init, this);
    wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    wstring row_string;
    vector<wstring> result;
    MYSQL_RES* res;
    MYSQL_ROW row;
    mysql_query(&_conn, query.c_str());
    if (res = mysql_store_result(&_conn)) {
        while (row = mysql_fetch_row(res)) {
            row_string.clear();
            for (size_t i = 0; i < mysql_num_fields(res); i++) {
                if (row[i]) {
                    row_string = row_string + converter.from_bytes(row[i]) + L"  ";
                }
                else {
                    row_string = row_string + L"No data" + L"  ";
                }
            }
            result.push_back(row_string);
        }
    }
    else
        cout << "Ошибка MySql номер " << mysql_error(&_conn);
    mysql_free_result(res);
    return result;
}

MySQLconn::~MySQLconn() {    mysql_close(&_conn);    }

MYSQL* MySQLconn::GetConnect()  {
    call_once(initialized, &MySQLconn::Init, this);
    return &_conn;     }
