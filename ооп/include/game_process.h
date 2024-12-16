#ifndef GAMEPROCESS_H 
#define GAMEPROCESS_H

#include <fstream>
#include <iostream>

#include "player.h"   
#include "enemy.h"  
#include "abilities_manager.h"
#include "game_setup.h"
#include "console_renderer.h"
#include "field_renderer.h"

// класс игрового процесса
class GameSession {
public:
    enum class step_result {GameOver, PlayerAlive};                              // перечисление для результатов шага игры
    GameSession();                                                               // конструктор по умолчанию
    GameSession(GameSetup& gameSetup);                                           // конструктор, принимающий настройки игры
    GameSession::step_result run_game_step(std::pair<char, int> coordinates);    // функция выполнения одного шага игры
    void place_ships();                                                          // метод размещения кораблей на поле
    bool use_ability();                                                          // функция использования способностей 
    void serialize(std::ostream& os);                                            // метод преобразования данных состояния игровой сессии в поток вывода
    void deserialize(std::istream& is);                                          // метод преобразования данных состояния игровой сессии из потока ввода

private:
    GameSetup setup;                                                    // объект, представляющий настройки игры
    FieldRenderer<ConsoleRenderer> field_renderer;                      // объект для отоброжения игрового поля в консоли
    ConsoleIO console;                                                  // объект для работы с консольным вводом/выводом
    Player player;                                                      // объект игрока
    Enemy enemy;                                                        // объект противника
    AbilitiesManager abilities_manager;                                 // менеджер управления способностями
};

#endif 
