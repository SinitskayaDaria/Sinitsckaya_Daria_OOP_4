#ifndef CLIHANDLER_H 
#define CLIHANDLER_H

#include <iostream>        
#include <fstream>         
#include <sstream>         
#include <map>            
#include <set>

#include "command_handler.h" 
#include "console_io.h"      
#include "exception.h"    
#include "conio.h"                      

// класс CLIHandler наследуется от CommandHandler
class CLIHandler: public CommandHandler { 
public:
    CommandHandler::command read_command() override;     // переопределение функции чтения команд из консоли
    std::pair<char, int> read_coordinate() override;     // переопределение функции чтения координат из консоли
    void reload_binds();                                 // функция перезагрузки бинд-команд из конфигурационного файла

private:
    // словарь бинд-команд, связывает символы с соответствующими командами
    std::map<char, CommandHandler::command> binds{
        {'S', CommandHandler::command::CallGameStep},   // команда шага игры (step)
        {'A', CommandHandler::command::CallAbility},    // команда вызова способности (ability)
        {'O', CommandHandler::command::CallSave},       // команда сохранения игры (output)
        {'L', CommandHandler::command::CallLoad},       // команда загрузки игры (load)
        {'Q', CommandHandler::command::CallExit}        // команда выхода из игры (quiet)
    };

    // словарь, связывает строковые ключи с командами
    std::map<std::string, CommandHandler::command> requested_keys{
        {"SHOOT_KEY", CommandHandler::command::CallGameStep},  // ключ стрелять
        {"ABILITY_KEY", CommandHandler::command::CallAbility}, // ключ способности
        {"SAVE_KEY", CommandHandler::command::CallSave},       // ключ сохранения
        {"LOAD_KEY", CommandHandler::command::CallLoad},       // ключ загрузки
        {"EXIT_KEY", CommandHandler::command::CallExit}        // ключ выхода
    };

    ConsoleIO console;  // объект для работы с консолью
};

#endif 
