#include "Chat.h"

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
    cout << "\n   Добро пожаловать в EChat 1.2\n" << endl;
    cout << "    1 - Зарегистрироваться\n    2 - Войти\n    3 - Выход\n";
}

void Chat::ShowUserMenu() {    
    bool runUserMenu = 1;
    while (runUserMenu) {
        cout << "\n   Главное Меню\n" << endl;
        cout << "    1 - Отправить сообщение пользователю\n    2 - Проверить почтовый ящик\n    3 - Войти в Чат\n    4 - Все пользователи\n    5 - Выйти из учётной записи\n";
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
    ShowAllUsers();
    bool login_find = 0;
    string choice_str;                         //Переменная для выбора Пользователя из списка уже существующих
    if (cin >> choice_str) {
        for (size_t i = 0; i != (_users.size()); ++i)    //Ищем его в векторе _users
            if (_users[i].GetLogin() == choice_str) {
                if (CheckPass(_users[i])) {
                    _cUser = _users[i];
                    _cUser.SetAutorized(1);
                    login_find = 1;
                }                
            }
    }
    if (!login_find)
        cout << "   Данный Login отсутсвует в списке пользователей\n   Введите корректный Login или зарегистрируйтесь\n";
}

bool Chat::CheckPass(const User& user) {
    cout << "   Введите пароль\n";
    SHA256 temp;
    string check_pass;
    int count{ 3 };
    while ((cin >> check_pass) && (count > 0)) {
        temp.update(check_pass);
        check_pass = temp.backToString(temp.digest());
        if (check_pass == user.GetPass()) {
            cout << "    Авторизация выполнена\n";
            return true;
        }
        else {
            cout << "    Неверный пароль\nПопробуйте ещё раз. Осталось попыток: " << count << endl;
            --count;
        }
    }
    return false;
}

void Chat::AddNewUser() {
    cout << "   Введите Login" << endl;
    _cUser.SetLogin(CreateLogin());
    cout << "   Введите имя" << endl;
    _cUser.SetName(CreateName());
    cout << "   Создайте пароль от учётной записи" << endl;
    _cUser.SetPass(CreatePassword());
    cout << "   Учётная запись успешно создана" << endl;
    _users.push_back(_cUser);
    _cUser.SetAutorized(1);
}

string Chat::CreateLogin() {
    string login; bool valid_login{ false };       //Переменная для цикла, пока Login не пройдёт проверку
    while (!valid_login) {
        if (cin >> login) {
            try {
                for (size_t i = 0;i != login.size();++i) {
                    if (!isalnum(login[i])) {            //Только латинские и буквы, по каждому симолу в login
                        throw runtime_error("   Ошибка при создании login пользователя\n");
                    }
                }
            }
            catch (runtime_error err) {
                cout << err.what() << "   Только латинские символы или натуральные числа\n";
                continue;   //Возвращаемся в начало цикла, если ловим исключение
            }
            bool check_login{ 0 };      //Переменная для проверки совпадения с существующим Login в _users
            for (size_t i = 0; i != (_users.size()); ++i) {
                if (_users[i].GetLogin() == login) {
                    cout << "   Пользователь с таким login уже существует :( \n";
                    check_login = true;  //Если нашли, через else в начало цикла
                }
            }
            if (!check_login) {      //Не нашли - возвращаем
                cout << "   Ваш login создан успешно" << endl << endl;
                valid_login = 1;
                return login;
            }
            else continue;
        }
    }
}

string Chat::CreatePassword() {
    bool valid_pass{ 0 };       //Переменная для цикла, пока Password не пройдёт проверку
    const int size_pass{ 14 };
    string pass;
    cout << "Пароль должен быть от 4 до " << size_pass << "символов, \nсодержать только латинские символы или натуральные числа\n";
    while (!valid_pass) {
        if (cin >> pass) {
            try {
                for (int i = 0;i != pass.size();++i)
                {
                    if ((size_pass <= pass.size()) || (!isalnum(pass[i])) || (pass.size() < 4)) {            //Только латинские и буквы, по каждому символу в pass. 4<pass<14(size_pass)
                        throw runtime_error("   Ошибка при создании пароля\n");
                    }
                }
            }
            catch (runtime_error err) {
                cout << err.what() << "   Только латинские символы или натуральные числа\n   Длина пароля от 4 до " << size_pass << endl;
                continue;   //Возвращаемся в начало цикла, если ловим исключение
            }
        }
        cout << "   Пароль успешно создан" << endl << endl;
        valid_pass = 1;     //Выходим из цикла
    }
    SHA256 temp;
    temp.update(pass);
    return temp.backToString(temp.digest());    //возвращаем хеш пароля
}

string Chat::CreateName() {
    bool valid_name{ 0 };       //Переменная для цикла, пока name не пройдёт проверку
    string name;
    while (!valid_name) {
        if (cin >> name) {
            try {
                for (size_t i = 0;i != name.size();++i) {
                    if (!isalnum(name[i])) {            //Только латинские и буквы, по каждому символу в name
                        throw runtime_error("   Ошибка при создании имени пользователя\n");
                    }
                }
            }
            catch (runtime_error err) {
                cout << err.what() << "   Только латинские символы или натуральные числа\n";
                continue;   //Возвращаемся в начало цикла, если ловим исключение
            }
            bool check_name{ 0 };           //Переменная для проверки совпадения с существующим именем в _users
            for (size_t i = 0; i != (_users.size()); ++i) {
                if (_users[i].GetName() == name) {
                    cout << "   Пользователь с таким именем существует :( \n";
                    check_name = true;  //Если нашли, через else в начало цикла
                }
            }
            if (!check_name) {      //Не нашли - возвращаем
                cout << "   Приветствую " << name << endl << endl;
                check_name = 1;
                return name;
            }
            else continue;
        }
    }
}

string Chat::CreateMessage() {
    string msg;
    cout << "    Введите сообщение\n";
    if (cin >> msg) {
        msg = CreateAutoTextMsg(msg);           //Функция АвтоТекста
        msg.replace(0, 0, " пишет:");           //Добавляем в начало строки "Пользователь пишет: "
        msg.replace(0, 0, _cUser.GetName());
    }
    return msg;
}

void Chat::SendMessage() {  //Отправка сообщения пользователю
    string msg;
    ShowAllUsers();
    string choice_str;                         //Переменная для сравнения Пользователя из списка уже существующих
    cout << "    Введите имя пользователя из списка\n";
    if (cin >> choice_str) {
        for (size_t i = 0; i != (_users.size()); ++i)    //Ищем его в векторе _users
            if (_users[i].GetLogin() == choice_str) {
                msg = CreateMessage();
                _users[i].SetMessageBox(msg);
            }
    }
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
    for (size_t i = 0; i != _users.size(); ++i) {       //Найти в векторе пользователей _users
        if (_users[i].GetLogin() == _cUser.GetLogin()) {        //Login текущего пользователя(нас интересует индекс i)
            for (size_t j = 0; j != (_users[i].GetMessageBox())._text.size();++j) {     //Текущему пользователю показать его почтовый ящик из учётки в векторе _users
                cout << "    " << j << " - " << (_users[i].GetMessageBox())._text[j] << endl;
            }
        }
    }
}

void Chat::ShowAllUsers() {
    cout << "   Зарегистрированные пользователи:\n";
    for (size_t i = 0; i != _users.size(); ++i) {           // Вывести вектор _users в cout
        cout << "    Пользователь [" << i << "] " << _users[i].GetLogin() << endl;
    }
}

void Chat::SendChatMsg() {
    string msg(CreateMessage());
    _chatMsg.push_back(msg);    //Добавляем сообщение в vectror<string>
    return;
}

void Chat::ShowChatMsg() {  //Сообщения Чата
    cout << "    Сообщения Чата:\n";
    for (size_t i = 0; i != _chatMsg.size(); ++i)
        cout << "  " << _chatMsg[i] << endl;
}