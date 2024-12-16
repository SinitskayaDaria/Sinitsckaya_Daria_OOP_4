#ifndef COMMANDHANDLER_H 
#define COMMANDHANDLER_H

#include <vector> 

// класс для определения интерфейса обработчиков команд
class CommandHandler {
public:
    // определение для различных команд, которые может выполнять игра
    enum class command {
        CallGameStep, // команда выполнения шага игры
        CallAbility,  // команда использования способности
        CallSave,     // команда сохранения игры
        CallLoad,     // команда загрузки игры
        CallExit,     // команда выхода из игры
        Unknown       // неизвестная команда
    };

    virtual CommandHandler::command read_command() = 0; // функция чтения команды
    virtual std::pair<char, int> read_coordinate() = 0; // функция чтения координат
};

#endif 
