#include "User.h"

User::User(const string& login, const string& pass, const string& name) : _login(login), _pass(pass), _name(name) {
    _autorized = 0; _autotext = 0;
}

User::User(const User& user) {
    _login = user._login;
    _pass = user._pass;
    _name = user._name;
    _msgs = user._msgs;
    _autorized = user._autorized;
    _autotext = user._autotext;
}

User& User::operator=(const User& user) {
    _login = user._login;
    _pass = user._pass;
    _name = user._name;
    _msgs = user._msgs;
    _autorized = user._autorized;
    _autotext = user._autotext;
    return *this;
}

void User::SetLogin(const string& l) { _login = l; }

void User::SetPass(const string& p) { _pass = p; }

void User::SetName(const string& n) { _name = n; }

void User::SetMessageBox(const string& msg) { _msgs.push_back(msg); }

void User::SetMessageBox(string&& msg) { _msgs.push_back(move(msg)); }

string User::GetLogin() const { return _login; }

string User::GetPass() const { return _pass; }

string User::GetName() const { return _name; }

MessageBox User::GetMessageBox() const { return _msgs; }

bool User::GetAutorized() const { return _autorized; }

bool User::GetAutoText() const { return _autotext; }

void User::SetAutorized(bool&& autoriz) { _autorized = autoriz; }

void User::SetAutoText(bool&& autotext) { _autotext = autotext; }