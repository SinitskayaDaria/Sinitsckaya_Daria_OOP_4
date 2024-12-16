#ifndef GAMECONTROL_H
#define GAMECONTROL_H

#include "game_process.h" 
#include "game_state.h"   
#include "game_setup.h"   
#include "command_handler.h" 

// шаблонный класс для управления игрой
template<class T>
class GameControl {
public:
    // конструктор класса, принимает ссылку на объект GameSession
    GameControl(GameSession& gameSession)
        // инициализация членов класса: текущей сессии, обработчика команд и состояния игры
        : current_command(CommandHandler::command::Unknown), cmd_handler(), session(gameSession), state(gameSession) {
        cmd_handler.reload_binds(); // перезагрузка привязки команд
        }

    // метод выполнения игрового цикла
    void run() {
        while (true) { 
            display_line("...");                          // отображение текущей строки действий
            current_command = cmd_handler.read_command(); // считывание команды от игрока
            
            // обработка введенной команды
            switch (current_command) {
                case CommandHandler::command::CallSave: // команда - сохранить игру
                    if (state.save("game_save.txt")) {
                        display_line("Saving", "\033[32m Game saved successfully \033[0m\n");
                    } else {
                        display_line("Saving", "\033[31m Failed to save game \033[0m\n");
                    }
                    break;

                case CommandHandler::command::CallLoad: // команда - загрузить игру
                    if (state.load("game_save.txt")) {
                        display_line("Loading", "\033[32m Game loaded successfully \033[0m\n");
                    } else {
                        display_line("Loading", "\033[31m Failed to load game \033[0m\n");
                    }
                    break;

                case CommandHandler::command::CallAbility: // команда - использовать способность
                    display_line("Use Ability"); // отображение информации об использовании способности
                    session.use_ability();       // метод использования способности
                    break;

                case CommandHandler::command::CallGameStep: { // команда - выполнить ход игры
                    display_line("Shoot");                                                     // отображение информации о ходе
                    std::pair<char, int> coordinates = cmd_handler.read_coordinate();          // считывание координат выстрела
                    GameSession::step_result step_result = session.run_game_step(coordinates); // выполенние хода игры
                    
                    // проверка на завершение игры
                    if (step_result == GameSession::step_result::GameOver) {
                        console.print_error(" Game over. A new game starts...\n");
                        return; 
                    }
                    break;
                }

                case CommandHandler::command::CallExit: // команда - выйти из игры
                    exit(0); 
                    
                default:
                    break;
            }
        }
    }

private:
    // метод отображения текущего действия и статуса
    void display_line(const std::string& cur_act, const std::optional<std::string>& status = std::nullopt) {
        console.print("\r\033[KCurrent action: ", cur_act, "> ", status.value_or("")); // вывод строки с текущим действием и статусом
    }

    CommandHandler::command current_command; // текущая команда
    T cmd_handler;                           // обработчик команд
    GameSession& session;                    // ссылка на игровую сессию
    GameState state;                         // состояние игры
    ConsoleIO console;                       // объект для ввода-вывода в консоль
};

#endif
