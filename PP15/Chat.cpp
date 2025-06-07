#include "Chat.h"
#include <codecvt> // Для кодировки

void Chat::Start() {    
    User test1("Tor2", "1234", "Ant");        //Тестовые пользователи
    User test2("Locki", "123t4", "Wasd777");
    _users.push_back(move(test1));                    //Тестовые пользователи добавляем в _users
    _users.push_back(move(test2));
    tree = make_unique<TTree>();                    //Тестовое дерево
    vector<string> words{ "string","vector","char","int","auto" };
    for (string str : words)
        tree->Insert(&tree->root, str);             //Добавление слов в дерево из вектора words
    
    
    bool runMainMenu = 1; int choice;       //Переменные в Start() для навигации и выбора по меню с помощью проверок
    while (runMainMenu) {
        ShowMain();
        if (cin >> choice) {
            switch (choice) {
            case 1:
                AddNewUser();
                if (_cUser.GetAutorized())
                    ShowUserMenu();
                break;
            case 2:
                LogIn();
                if (_cUser.GetAutorized())
                    ShowUserMenu();
                break;
            case 3:
                runMainMenu = 0;
                break;
            default:
                break;
            }
        }
        else return;
    }
    return;
}

void Chat::ShowMain() {
    cout << "\n   Добро пожаловать в EChat 1.3\n" << endl;
    cout << "    1 - Зарегистрироваться\n    2 - Войти\n    3 - Выход\n";
}

void Chat::ShowUserMenu() {    
    bool runUserMenu = 1;
    while (runUserMenu) {
        cout << "\n   Главное Меню\n\n";
        cout << "    1 - Отправить сообщение пользователю\n    2 - Проверить почтовый ящик\n    3 - Войти в Чат\n";
        cout << "    4 - Все пользователи\n    5 - Функция автотескта\n    6 - Выйти из учётной записи\n";
        int choice = 0;
        if (cin >> choice) {
            switch (choice) {
            case 1:
                SendMessage();
                break;
            case 2:
                MyMessages();
                break;
            case 3:
                ShowChatMenu();
                break;
            case 4:
                ShowAllUsers();
                break;
            case 5:
                ShowAutoTextMenu();
                break;
            case 6:
                _cUser.SetAutorized(0);
                return;
            }
        }
    }
}

void Chat::ShowChatMenu() {
    bool runChatMenu = 1;
    while (runChatMenu) {
        cout << "\n   Меню Чата\n" << endl;
        cout << "    1 - Отправить сообщение в Чат\n    2 - Просмотреть сообщения Чата\n    3 - Покинуть Чат\n";
        int choice;
        if (cin >> choice) {
            switch (choice) {
            case 1:
                SendChatMsg();
                break;
            case 2:
                ShowChatMsg();
                break;
            case 3:
                runChatMenu = 0;
                return;
            }
        }
    }
}
void Chat::LogIn() {
    cout << "   Введите свой Login" << endl;
    string login_check;
    if (cin >> login_check) {
        if (IsAlNumString(login_check)) {
            vector<string> mySQL_res;
            string query{ "SELECT login FROM users where login = '" + login_check + "';" };
            cout << "query  = " << query << endl;
            mySQL_res = SendAndResQueryMySQL(query);
            if (mySQL_res.empty()) {
                cout << "   Данный Login отсутсвует в списке пользователей\n   Введите корректный Login или зарегистрируйтесь\n";
            }
            else {
                _cUser.SetLogin(login_check);
                if (CheckPass()) {
                    query = { "SELECT name FROM users where login = '" + login_check + "';" };
                    mySQL_res = SendAndResQueryMySQL(query);
                    if (!mySQL_res.empty()) {
                        _cUser.SetName(mySQL_res[0]);
                    }
                    _cUser.SetAutorized(1);
                    return;
                }
            }
        }
    }
}


bool Chat::CheckPass() {
    cout << "   Введите пароль\n";
    string pass;
    bool check_run{ true };
    int count{ 3 };
    while (check_run) {
        if (cin >> pass) {
            if (CheckMaskPass(pass) && (count > 0)) {
                vector<string> mySQL_res;
                SHA256 temp;
                temp.update(pass);
                pass = temp.backToString(temp.digest());    //возвращаем хеш пароля
                string query{ "select pass from users_login where user_login = '" + _cUser.GetLogin() + "' and pass = '" + pass + "';" };
                cout << "query = " << query << endl;
                cout << "pass = " << pass << endl;
                mySQL_res = SendAndResQueryMySQL(query);
                if (!mySQL_res.empty()) {
                    cout << "    Авторизация выполнена\n";
                    return true;
                }
                else {
                    cout << "    Неверный пароль\nПопробуйте ещё раз. Осталось попыток: " << count << endl;
                    --count;
                    continue;
                }
            }
            check_run = false;
        }
    }
    return false;
}

void Chat::AddNewUser() {    
    CreateLogin();
    CreateName();
    CreatePassword();
    cout << "   Учётная запись успешно создана" << endl;
    //_users.push_back(_cUser);
    _cUser.SetAutorized(1);
}

void Chat::CreateLogin() {
    string login; bool valid_login{ false };       //Переменная для цикла, пока Login не пройдёт проверку    
    vector<string> mySQL_res;
    cout << "   Введите Login" << endl;
    while (!valid_login) {
        if (cin >> login) {
            if (IsAlNumString(login)) {
                string query{ "SELECT login FROM users where login = '" + login + "';" };
                cout << "query  = " << query << endl;
                mySQL_res = SendAndResQueryMySQL(query);
                if (!mySQL_res.empty()) {
                    cout << "   Ошибка при создании пользователя :(\n   Попробуйте ещё раз\n";
                    continue;
                }
                else {
                    query = "insert into users (login) values ('" + login + "');";
                    cout << "query  = " << query << endl;
                    SendQueryMySQL(query);
                    valid_login = 1;
                    _cUser.SetLogin(login);
                    cout << "   Login " << login << " создан\n";
                    continue;
                }
            }
            else {
                cout << "   Ошибка при создании login пользователя\n   Только латинские символы или натуральные числа\n";
                continue;
            }
        }
    }
}

void Chat::CreatePassword() {
    bool valid_pass{ 0 };       //Переменная для цикла, пока Password не пройдёт проверку
    const int size_pass{ 14 };
    string pass;
    cout << "   Создайте пароль от учётной записи" << endl;
    cout << "Пароль должен быть от 4 до " << size_pass << "символов, \nсодержать только латинские, специальные символы и числа\n";
    while (!valid_pass) {
        if (cin >> pass) {
            if (CheckMaskPass(pass) && (pass.size() <= size_pass) && (pass.size() > 4)) {
                SHA256 temp;
                temp.update(pass);
                pass = temp.backToString(temp.digest());    //возвращаем хеш пароля
                string query{ "update users_login set pass ='" + pass + "' where user_login = '" + _cUser.GetLogin() + "';" };
                cout << "query  = " << query << endl;
                SendQueryMySQL(query);
                cout << "   Пароль успешно создан"  << endl;
                valid_pass = 1;     //Выходим из цикла
                continue;
            }
            else {
                cout << "   Ошибка при создании pasword пользователя\n   Только латинские, специальные символы и числа. От 4 до " << size_pass << endl;
                continue;
            }
        }
    }
}

void Chat::CreateName() {
    cout << "   Введите имя" << endl;
    bool valid_name{ 0 };       //Переменная для цикла, пока name не пройдёт проверку
    string name;
    vector<string> mySQL_res;
    while (!valid_name) {
        if (cin >> name) {
            if (IsAlNumString(name)) {
                string query{ "SELECT name FROM users where name = '" + name + "';" };
                cout << "query  = " << query << endl;
                mySQL_res = SendAndResQueryMySQL(query);
                if (!mySQL_res.empty()) {
                    cout << "   Ошибка при создании name \n   Пользователь с таким именем уже существует\n";
                    continue;
                }
                else {
                    query = { "update users set name ='" + name + "' where login = '" + _cUser.GetLogin() + "';" };
                    cout << "query  = " << query << endl;
                    SendQueryMySQL(query);
                    _cUser.SetName(name);
                    valid_name = true;
                    cout << "   Приветсвую " << name << endl;
                    return;
                }
            }
            else {
                cout << "   Ошибка при создании name пользователя\n   Только латинские символы и числа\n";
                continue;
            }
        }
    }
}

string Chat::CreateMessage() {
    wstring msg;
    string utf8_string;
    cout << "    Введите сообщение\n";
    if (wcin >> msg) {
        //if(_cUser.GetAutoText())
            //msg = CreateAutoTextMsg(msg);        //Функция АвтоТекста
        //msg.replace(0, 0, " пишет:");           //Добавляем в начало строки "Пользователь пишет: "
        //msg.replace(0, 0, _cUser.GetName());

        // Преобразование wstring в char*
        wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;
        utf8_string = converter.to_bytes(msg);
    }
    return utf8_string;
}

void Chat::SendMessage() {  //Отправка сообщения пользователю
    ShowAllUsers();
    string user;
    int id_send = 0;
    int id_recipient = 0;
    vector<string> mySQL_res;
    cout << "    Введите имя пользователя из списка\n";
    if (cin >> user) {
        string query{ "SELECT name FROM users where name = '" + user + "';" };
        cout << "query  = " << query << endl;
        mySQL_res = SendAndResQueryMySQL(query);
        if (mySQL_res.empty()) {
            cout << "   Пользователь не найден\n";
            return;
        }
        else {
            query = { "SELECT id FROM users where Login = '" + _cUser.GetLogin() + "';" };
            mySQL_res = SendAndResQueryMySQL(query);
            if (mySQL_res.empty()) {
                cout << "   Ошибка!\n";
                return;
            }
            else {
                id_send = stoi(mySQL_res[0]);
            }
            query = { "SELECT id FROM users where name = '" + user + "';" };
            mySQL_res = SendAndResQueryMySQL(query);
            if (mySQL_res.empty()) {
                cout << "   Ошибка!\n";
                return;
            }
            else {
                id_recipient = stoi(mySQL_res[0]);
            }
            query = { "insert into messages (text, id_send, id_recipient) values ('" + CreateMessage() + "','" + to_string(id_send) + "','" + to_string(id_recipient) + "');" };
            cout << query;
            SendQueryMySQL(query);
        }
    }
    return;
}

string Chat::CreateAutoTextMsg(const string& pat) {
    string pattern = pat;
    vector<string> sugg = tree->AutoComplete(tree->root, pattern);
    if (sugg.size() == 0) {
        cout << "    В нашем словаре отсутвуют слова которые начинаются на " << pattern << endl;
        cout << "    Желаете добавить новое слово в наш словарь? \n    y - yes    n - no\n";
        char choice;
        if (cin >> choice) {
            if (choice == 'y') {
                tree->Insert(&tree->root, pattern);
                cout << "    Слово успешно добавлено\n";
                return pattern;
            }
        }
    }
    else
        return tree->ChoiceWordFromTree(sugg, pattern);
    return pattern;
}

void Chat::MyMessages() {
    cout << "    Ваши сообщения:\n";
    int id_recipient = 0;
    vector<string> mySQL_res;
    string query{ "SELECT id FROM users where Login = '" + _cUser.GetLogin() + "';" };
    mySQL_res = SendAndResQueryMySQL(query);
    if (mySQL_res.empty()) {
        cout << "   Ошибка!\n";
        return;
    }
    else {
        id_recipient = stoi(mySQL_res[0]);
    }
    query = "select name, text, date, time from (select id_send, text, date, time from messages join users where users.id = messages.id_recipient and messages.id_recipient = " + to_string(id_recipient) + ") as t join users where t.id_send = users.id";
    mySQL_res = SendAndResQueryMySQL(query);
    if (mySQL_res.empty()) {
        cout << "   Ошибка!\n";
        return;
    }
    else {
        for (size_t i = 0; i != mySQL_res.size(); ++i) {
            //wstring msg((mySQL_res[i]).begin(), (mySQL_res[i]).end());
            cout << mySQL_res[i] << endl;
        }
    }
}


void Chat::ShowAllUsers() {
    cout << "   Зарегистрированные пользователи:\n";
    vector<string> mySQL_res;
    string query{ "SELECT name FROM users;" };
    mySQL_res = SendAndResQueryMySQL(query);
    cout << "                    " << "  Name  " <<  endl;
    for (size_t i = 0; i != mySQL_res.size(); ++i) {           
        cout << "    Пользователь [" << i + 1 << "] " << mySQL_res[i] << endl;
    }
}

void Chat::SendChatMsg() {
    int id_send = 0;
    vector<string> mySQL_res;
    string query{ "SELECT id FROM users where Login = '" + _cUser.GetLogin() + "';" };
    mySQL_res = SendAndResQueryMySQL(query);
    if (mySQL_res.empty()) {
        cout << "   Ошибка!\n";
        return;
    }
    else {
        id_send = stoi(mySQL_res[0]);
    }
    query = "insert into chat (text, user_id) values ('" + CreateMessage() + "','" + to_string(id_send) + "');";
    cout << query;
    SendQueryMySQL(query);
    return;
}

void Chat::ShowChatMsg() {  //Сообщения Чата
    cout << "    Сообщения Чата:\n";
    vector<string> mySQL_res;
    string query{ "select name, text, date, time from users join chat where users.id = chat.user_id" };
    mySQL_res = SendAndResQueryMySQL(query);
    for (size_t i = 0; i != mySQL_res.size(); ++i) {           
        //wstring msg((mySQL_res[i]).begin(), (mySQL_res[i]).end());
        cout << mySQL_res[i] << endl;
    }
}


void Chat::SendQueryMySQL(const string& query) {
    MYSQL mysql; 
    mysql_init(&mysql);
    if (!&mysql) {
        cout << "Error: can't create MySQL-descriptor" << endl;
    }
    if (!mysql_real_connect(&mysql, "localhost", "root", "Vthrekmtd@$7753191", "echat_db", 0, NULL, 0)) {
        cout << "Error: can't connect to database " << mysql_error(&mysql) << endl;
    }
    else {
        cout << "Success!" << endl;
    }
    mysql_set_character_set(&mysql, "utf8mb4");
    mysql_query(&mysql, query.c_str());
    mysql_close(&mysql);
}

vector<string> Chat::SendAndResQueryMySQL(const string& query) {
    string row_string;
    vector<string> result;
    MYSQL mysql;
    MYSQL_RES* res;
    MYSQL_ROW row;
    mysql_init(&mysql);
    if (!&mysql) {
        cout << "Error: can't create MySQL-descriptor" << endl;
    }
    if (!mysql_real_connect(&mysql, "localhost", "root", "Vthrekmtd@$7753191", "echat_db", 0, NULL, 0)) {
        cout << "Error: can't connect to database " << mysql_error(&mysql) << endl;
    }
    else {
        cout << "Success!" << endl;
    }
    mysql_set_character_set(&mysql, "utf8mb4");
    mysql_query(&mysql, query.c_str());
    if (res = mysql_store_result(&mysql)) {
        while (row = mysql_fetch_row(res)) {
            row_string.clear();
            for (size_t i = 0; i < mysql_num_fields(res); i++) {
                if (row[i]) {
                    cout << row[i] << "  ";
                    row_string = row_string + row[i] + "  ";
                }
                else {
                    row_string = row_string + "No data" + "  ";
                }
            }
            cout << endl;
            result.push_back(row_string);
        }
    }
    else
        cout << "Ошибка MySql номер " << mysql_error(&mysql);
    mysql_free_result(res);
    mysql_close(&mysql);
    return result;
}

bool Chat::IsAlNumString(const string& check) {
    for (size_t i = 0;i != check.size();++i) {
        if (!isalnum(check[i]))
            return false;
    }
    return true;
}

bool Chat::CheckMaskPass(const string& pass) {
    string mask_pass = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!#$%&()*+,-./|\\\"':;<=>?@[]^_`{}~";
    bool run = true;
    while (run) {
        for (size_t i = 0;i != pass.size();++i) {
            if (mask_pass.find(pass[i]) > mask_pass.size()) 
                return false;            
        }
        run = false;
    }
    return true;
}

void Chat::ShowAutoTextMenu() {
    bool runMenuAT = 1;
    while (runMenuAT) {
        cout << "\n   Меню Функции автотеста\n" << endl;
        cout << "    Сейчас Автотекст " << ((_cUser.GetAutoText()) ? "включен" : "выключен");
        cout << "\n    1 - Включить Автотекст\n    2 - Выключить Автотекст\n    3 - Вернуться в главное меню\n";
        int choice;
        if (cin >> choice) {
            switch (choice) {
            case 1:
                _cUser.SetAutoText(1);
                break;
            case 2:
                _cUser.SetAutoText(0);
                break;
            case 3:
                runMenuAT = 0;
                return;
            }
        }
    }
}