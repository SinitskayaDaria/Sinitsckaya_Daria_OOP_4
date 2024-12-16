#include "../include/CLI_handler.h"

// чтение команды из консоли
CommandHandler::command CLIHandler::read_command() {
    while (true) {                                          // цикл ожидания ввода команды
        if (console.char_available()) {                     // проверка доступа ввода символа
            char key = console.get_char();                  // считывание символа из консоли
            try {
                return binds.at(key);                       // возврат соответствующей команды из бинд-команд
            } catch (std::out_of_range& e) {
                return CommandHandler::command::Unknown;    // символ не соответствует ни одной команде
            }
        }
    }
}

// чтение координат из консоли
std::pair<char, int> CLIHandler::read_coordinate() {
    return console.get_coordinate(); 
}

// метод перезагрузки бинд-команд из конфигурационного файла
void CLIHandler::reload_binds() {
    std::string filename = "config.txt";            // имя конфигурационного файла
    bool reloading = true;                          // флаг, отслеживать состояние перезагрузки
    while (reloading) {                             // цикл для повторной попытки загрузки
        std::ifstream is(filename);                 // открытие файла для чтения
        if (!is.is_open()) {                        // проверка открытия файла
            console.print_error("Failed to open configuration file '", filename, "'.");
            return; 
        }
        
        std::map<char, CommandHandler::command> new_binds;      // создание временных контейнеров для новых бинд-команд
        std::set<char> used_keys;                               // хранение использованных клавиш
        std::set<CommandHandler::command> assigned_commands;    // хранение назначенных команд
        std::string line;                                       // хранение текущей строки

        try {
            // чтение файла построчно
            while (std::getline(is, line)) {
                std::istringstream iss(line);                   // создание потока для чтения строки
                std::string key, equals, value;
                
                // разбор строки на ключ, знак равенства и значение
                if (iss >> key >> equals >> value && equals == "=") {
                    // удаление кавычек, если они есть
                    if (!value.empty() && value.front() == '"' && value.back() == '"') {
                        value = value.substr(1, value.size() - 2);
                    }

                    auto requested_key_it = requested_keys.find(key);                   // поиск запрашиваемого ключа
                    if (requested_key_it != requested_keys.end() && !value.empty()) {
                        char bind_key = toupper(value[0]);                              // приведение первого символа значения к верхнему регистру
                        auto command = requested_key_it->second;                        // получение соответствующей команды

                        // проверка на наличие дубликатов
                        if (used_keys.count(bind_key)) {
                            throw MultipleBindException(); // исключение при попытке создать дубликат клавиши
                        }
                        if (assigned_commands.count(command)) {
                            throw MultipleBindException(); // исключение при попытке назначить дубликат команды
                        }

                        // запись нового соответствия клавиши и команды
                        new_binds[bind_key] = command;
                        used_keys.insert(bind_key);         // добавление клавиши в использованные
                        assigned_commands.insert(command);  // добавление команды в назначенные
                    }
                }
            }

            // проверка на назначение всех запрашиваемых команд
            for (const auto &[key, command]: requested_keys) {
                if (assigned_commands.find(command) == assigned_commands.end()) {
                    throw NotEnoughBindsException(); // исключение, если для команды нет бинда
                }
            }

            // обновление бинд-команд
            binds = std::move(new_binds);
            is.close(); // закрытие файла
            console.print_success("Configuration successfully loaded.\n"); // "Конфигурация успешно загружена."
            return;

        } catch (const GameException &e) {                                                              // обработка исключений
            console.print_error("Error loading configuration: ", e.what());                             // вывод сообщения об ошибке
            console.print_warning("Please fix the configuration file and press any key to reload...");  // "Пожалуйста, исправьте конфигурационный файл и нажмите любую клавишу для перезагрузки..."
            reloading = false;
            while (true) {                          // ожидание нажатия клавиши для перезагрузки
                if (console.char_available()) {
                    is.close();                     // закрытие файла
                    break;                          // выход из цикла
                }
            }
        }
    }
}
