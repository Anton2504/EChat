#include "Chat.h"

void Chat::Start() {
    User test1("Tor2", "1234", "Ant");        //�������� ������������
    User test2("Locki", "123t4", "Wasd777");
    _users.push_back(move(test1));                    //�������� ������������ ��������� � _users
    _users.push_back(move(test2));
    bool runMainMenu = 1; int choice;       //���������� � Start() ��� ��������� � ������ �� ���� � ������� ��������
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
    cout << "\n   ����� ���������� � EChat 1.0\n" << endl;
    cout << "    1 - ������������������\n    2 - �����\n    3 - �����\n";
}

void Chat::ShowUserMenu() {
    bool runUserMenu = 1;
    while (runUserMenu) {
        cout << "\n   ������� ����\n" << endl;
        cout << "    1 - ��������� ��������� �������������\n    2 - ��������� �������� ����\n    3 - ����� � ���\n    4 - ��� ������������\n    5 - ����� �� ������� ������\n";
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
        cout << "\n   ���� ����\n" << endl;
        cout << "    1 - ��������� ��������� � ���\n    2 - ����������� ��������� ����\n    3 - �������� ���\n";
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
    cout << "   ������� ���� Login" << endl;
    ShowAllUsers();
    string choice_str;                         //���������� ��� ������ ������������ �� ������ ��� ������������
    if (cin >> choice_str) {
        for (size_t i = 0; i != (_users.size()); ++i)    //���� ��� � ������� _users
            if (_users[i].GetLogin() == choice_str) {
                if (CheckPass(_users[i])) {
                    _cUser = _users[i];
                    _cUser.SetAutorized(1);
                }
            }
    }
}

bool Chat::CheckPass(const User& user) {
    cout << "   ������� ������\n";
    string check_pass;
    int count{ 3 };
    while ((cin >> check_pass) && (count > 0)) {
        if (check_pass == user.GetPass()) {
            cout << "    ����������� ���������\n";
            return true;
        }
        else {
            cout << "    �������� ������\n���������� ��� ���. �������� �������: " << count << endl;
            --count;
        }
    }
    return false;
}

void Chat::AddNewUser() {
    cout << "   ������� Login" << endl;
    _cUser.SetLogin(CreateLogin());
    cout << "   ������� ���" << endl;
    _cUser.SetName(CreateName());
    cout << "   �������� ������ �� ������� ������" << endl;
    _cUser.SetPass(CreatePassword());
    cout << "   ������� ������ ������� �������" << endl;
    _users.push_back(_cUser);
    _cUser.SetAutorized(1);
}

string Chat::CreateLogin() {
    string login; bool valid_login{ false };       //���������� ��� �����, ���� Login �� ������ ��������
    while (!valid_login) {
        if (cin >> login) {
            try {
                for (size_t i = 0;i != login.size();++i) {
                    if (!isalnum(login[i])) {            //������ ��������� � �����, �� ������� ������ � login
                        throw runtime_error("   ������ ��� �������� login ������������\n");
                    }
                }
            }
            catch (runtime_error err) {
                cout << err.what() << "   ������ ��������� ������� ��� ����������� �����\n";
                continue;   //������������ � ������ �����, ���� ����� ����������
            }
            bool check_login{ 0 };      //���������� ��� �������� ���������� � ������������ Login � _users
            for (size_t i = 0; i != (_users.size()); ++i) {
                if (_users[i].GetLogin() == login) {
                    cout << "   ������������ � ����� login ��� ���������� :( \n";
                    check_login = true;  //���� �����, ����� else � ������ �����
                }
            }
            if (!check_login) {      //�� ����� - ����������
                cout << "   ��� login ������ �������" << endl << endl;
                valid_login = 1;
                return login;
            }
            else continue;
        }
    }
}

string Chat::CreatePassword() {
    bool valid_pass{ 0 };       //���������� ��� �����, ���� Password �� ������ ��������
    const int size_pass{ 14 };
    string pass;
    cout << "������ ������ ���� �� 4 �� " << size_pass << "��������, \n��������� ������ ��������� ������� ��� ����������� �����\n";
    while (!valid_pass) {
        if (cin >> pass) {
            try {
                for (int i = 0;i != pass.size();++i)
                {
                    if ((size_pass <= pass.size()) || (!isalnum(pass[i])) || (pass.size() < 4)) {            //������ ��������� � �����, �� ������� ������ � pass. 4<pass<14(size_pass)
                        throw runtime_error("   ������ ��� �������� ������\n");
                    }
                }
            }
            catch (runtime_error err) {
                cout << err.what() << "   ������ ��������� ������� ��� ����������� �����\n   ����� ������ �� 4 �� " << size_pass << endl;
                continue;   //������������ � ������ �����, ���� ����� ����������
            }
        }
        cout << "   ������ ������� ������" << endl << endl;
        valid_pass = 1;     //������� �� �����
    }
    return pass;
}

string Chat::CreateName() {
    bool valid_name{ 0 };       //���������� ��� �����, ���� name �� ������ ��������
    string name;
    while (!valid_name) {
        if (cin >> name) {
            try {
                for (size_t i = 0;i != name.size();++i) {
                    if (!isalnum(name[i])) {            //������ ��������� � �����, �� ������� ������ � name
                        throw runtime_error("   ������ ��� �������� ����� ������������\n");
                    }
                }
            }
            catch (runtime_error err) {
                cout << err.what() << "   ������ ��������� ������� ��� ����������� �����\n";
                continue;   //������������ � ������ �����, ���� ����� ����������
            }
            bool check_name{ 0 };           //���������� ��� �������� ���������� � ������������ ������ � _users
            for (size_t i = 0; i != (_users.size()); ++i) {
                if (_users[i].GetName() == name) {
                    cout << "   ������������ � ����� ������ ���������� :( \n";
                    check_name = true;  //���� �����, ����� else � ������ �����
                }
            }
            if (!check_name) {      //�� ����� - ����������
                cout << "   ����������� " << name << endl << endl;
                check_name = 1;
                return name;
            }
            else continue;
        }
    }
}

string Chat::CreateMessage() {
    string msg;
    cout << "    ������� ���������\n";
    if (cin >> msg) {
        msg.replace(0, 0, " �����:");           //��������� � ������ ������ "������������ �����: "
        msg.replace(0, 0, _cUser.GetName());
    }
    return msg;
}

void Chat::SendMessage() {  //�������� ��������� ������������
    string msg;
    ShowAllUsers();
    string choice_str;                         //���������� ��� ��������� ������������ �� ������ ��� ������������
    cout << "    ������� ��� ������������ �� ������\n";
    if (cin >> choice_str) {
        for (size_t i = 0; i != (_users.size()); ++i)    //���� ��� � ������� _users
            if (_users[i].GetLogin() == choice_str) {
                msg = CreateMessage();
                _users[i].SetMessageBox(msg);
            }
    }
}

void Chat::MyMessages() {
    cout << "    ���� ���������:\n";
    for (size_t i = 0; i != _users.size(); ++i) {       //����� � ������� ������������� _users
        if (_users[i].GetLogin() == _cUser.GetLogin()) {        //Login �������� ������������(��� ���������� ������ i)
            for (size_t j = 0; j != (_users[i].GetMessageBox())._text.size();++j) {     //�������� ������������ �������� ��� �������� ���� �� ������ � ������� _users
                cout << "    " << j << " - " << (_users[i].GetMessageBox())._text[j] << endl;
            }
        }
    }
}

void Chat::ShowAllUsers() {
    cout << "   ������������������ ������������:\n";
    for (size_t i = 0; i != _users.size(); ++i) {           // ������� ������ _users � cout
        cout << "    ������������ [" << i << "] " << _users[i].GetLogin() << endl;
    }
}

void Chat::SendChatMsg() {
    string msg(CreateMessage());
    _chatMsg.push_back(msg);    //��������� ��������� � vectror<string>
    return;
}

void Chat::ShowChatMsg() {  //��������� ����
    cout << "    ��������� ����:\n";
    for (size_t i = 0; i != _chatMsg.size(); ++i)
        cout << "  " << _chatMsg[i] << endl;
}