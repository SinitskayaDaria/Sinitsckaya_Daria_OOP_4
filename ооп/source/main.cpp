#include "../include/game_process.h" 
#include "../include/game_control.h"  
#include "../include/CLI_handler.h"    

int main() {
    while (true) { 
        GameSetup config;                         // cоздание объекта для настройки игры
        config.read_start_data();                 // чтение начальных данных для настройки игры
        GameSession session(config);              // создание объекта сессии игры с использованием настроек
        session.place_ships();                    // размещение кораблей на игровом поле
        GameControl<CLIHandler> control(session); // создание управляющего объекта для взаимодействия с пользователем 
        control.run();                            // запуск игрового цикла управления
    }

    return 0; 
}
