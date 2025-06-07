#include "Chat.h"

int main() {

    setlocale(LC_ALL, "rus");    
    system("chcp 1251>nul"); // chcp 65001>nul chcp 1251>nul

    Chat chat;
    chat.Start();

    return 0;
}

