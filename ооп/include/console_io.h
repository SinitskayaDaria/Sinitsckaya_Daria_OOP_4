#ifndef CONSOLEIO_H 
#define CONSOLEIO_H

#include "conio.h"
#include <iostream> 

// класс, предоставляющий методы для взаимодействия с пользователем через консоль
class ConsoleIO {
public:
    // метод принимает переменное количество аргументов и выводит их в консоль
    template<class... Args>
    void print(Args... text){
        (std::cout << ... << text); // использует fold expression для вывода всех аргументов
        std::cout << std::flush;    // очищает буфер вывода
    }

    // метод выводит сообщение об ошибке в красном цвете
    template<class... Args>
    void print_error(Args... text) {
        std::cout << "\033[31m";                // установка красного цвета текста
        (std::cout << ... << text);             // вывод аргументов
        std::cout << "\033[0m" << std::flush;   // сброс цвета текста к умолчанию
    }

    // метод выводит сообщение об успехе в зеленом цвете
    template<class... Args>
    void print_success(Args... text){
        std::cout << "\033[32m";                // установка зеленого цвета текста
        (std::cout << ... << text);             // вывод аргументов
        std::cout << "\033[0m" << std::flush;   // сброс цвета текста к умолчанию
    }

    // метод выводит предупреждение в желтом цвете
    template<class... Args>
    void print_warning(Args... text){
        std::cout << "\033[33m";                // установка желтого цвета текста
        (std::cout << ... << text);             // вывод аргументов
        std::cout << "\033[0m" << std::flush;   // сброс цвета текста к умолчанию
    }

    char get_char();                            // функция пулучения символа от пользователя и преобразования его в верхний регистр
    bool char_available();                      // функция проверки доступа символа для чтения
    std::string get_line();                     // функция получения строки ввода от пользователя
    std::pair<char, int> get_coordinate();      // функция запроса у пользователя координаты 
};

#endif 