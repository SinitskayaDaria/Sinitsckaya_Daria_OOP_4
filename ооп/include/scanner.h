#ifndef SCANNER_H 
#define SCANNER_H

#include "abilities.h"      
#include "console_io.h"
#include "CLI_handler.h"

// класс способности сканирования
class ScannerAbility : public Ability {
public:
    ScannerAbility(Board& opponent_board); // конструктор, принимающий ссылку на поле противника
    void use() override;                   // переопределение метода для реализации сканирования
    std::string get_name() override;       // переопределение метода для получения имени способности
    ~ScannerAbility() = default;           // деструктор класса, по умолчанию

private:
    ConsoleIO console;                     // объект для работы с консольным вводом/выводом
    Board& board;                          // ссылка на поле противника
};

#endif 
