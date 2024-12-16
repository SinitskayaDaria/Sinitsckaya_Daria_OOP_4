#include "../include/console_io.h" 

// функция пулучения символа от пользователя и преобразования его в верхний регистр
char ConsoleIO::get_char() {
    return (char)toupper(_getch());
}

// функция проверки доступа символа для чтения
bool ConsoleIO::char_available() {
    return _kbhit(); // возвращает true, если клавиша была нажата
}

// функция получения строки ввода от пользователя
std::string ConsoleIO::get_line() {
    std::string input;
    std::getline(std::cin >> std::ws, input); // чтение строки с игнорированием пробелов в начале
    return input;
}

// функция запроса у пользователя координаты 
std::pair<char, int> ConsoleIO::get_coordinate() {
    while (true) {          // цикл для повторного запроса ввода до получения корректных данных
        std::string input;
        std::cin >> input;  // чтение строки ввода

        // проверка длины ввода
        if (input.length() < 2 || input.length() > 3) {
            print_error("Invalid input. Expected format: letter + number (for example, A1).\n"); // "Неверный ввод. Ожидаемый формат: буква + цифра (например, A1)."
        }

        char letter = toupper(input[0]); // преобразование первой буквы в верхний регистр
        // проверка, введённая буква находится в диапазоне от A до Z
        if (letter < 'A' || letter > 'Z') {
            print_error("Invalid letter. Use letters A to Z.\n"); // "Неверная буква. Используйте буквы от А до Z."
        }

        std::string digit_str = input.substr(1); // извлечение строки, представляющей число
        int digit;
        try {
            digit = std::stoi(digit_str); // преобразование строки в целое число
        } catch (const std::exception &) {
            print_error("Incorrect number. Use numbers from 1 to 26.\n"); // "Неверный номер. Используйте цифры от 1 до 26."
        }

        // проверка, число в диапазоне от 1 до 26
        if (digit < 1 || digit > 26) {
            print_error("The number must be from 1 to 26.\n"); // "Это число должно быть от 1 до 26."
        }

        return std::make_pair(letter, digit); // возврат пары 
    }
}
