#include "../include/conio.h"

// функция считывает один символ с клавиатуры без ожидания нажатия клавиши Enter
int _getch() {
    struct termios oldt, newt; // структуры для хранения старых и новых настроек терминала
    int ch;

    // получение текущих настроек терминала
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt; // копирование старых настроек в новые

    // отключение буферизации ввода и отображения символов
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt); // применение новых настроек терминала

    // считывание символа с клавиатуры
    ch = getchar();

    // восстанавление старых настроек терминала
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return ch; // возвращение считанного символа
}

// функция проверяет, была ли нажата клавиша (не блокируя выполнение)
int _kbhit() {
    struct termios oldt, newt; // структуры для хранения старых и новых настроек терминала
    int ch;
    int oldf;

    // получение текущих настроек терминала
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt; // копирование старых настроек в новые

    // отключение буферизации ввода
    newt.c_lflag &= ~(ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt); // применение новых настроек терминала

    // сделать ввод неблокирующим
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0); // сохранение старых флагов
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK); // установка неблокирующего режима

    ch = getchar(); // считывание символа

    // восстанавление старых настроек терминала
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf); // возврат старых флагов

    // был нажат символ, возвращение 1 и помещение символа обратно в поток ввода
    if (ch != EOF) {
        ungetc(ch, stdin); // возвращение символа в поток
        return 1; // символ был нажат
    }

    return 0; // не было нажатий
}