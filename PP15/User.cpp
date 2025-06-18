#include "User.h"

User::User(const string& login, const string& name) : _login(login), _name(name) {
    _autorized = 0; _autotext = 0;
}

User::User(const User& user) {
    _login = user._login;
    _name = user._name;
    _autorized = user._autorized;
    _autotext = user._autotext;
}

User& User::operator=(const User& user) {
    _login = user._login;
    _name = user._name;
    _autorized = user._autorized;
    _autotext = user._autotext;
    return *this;
}

void User::SetLogin(const string& l) { _login = l; }

void User::SetName(const string& n) { _name = n; }

string User::GetLogin() const { return _login; }

string User::GetName() const { return _name; }

bool User::GetAutorized() const { return _autorized; }

bool User::GetAutoText() const { return _autotext; }

void User::SetAutorized(bool&& autoriz) { _autorized = autoriz; }

void User::SetAutoText(bool&& autotext) { _autotext = autotext; }