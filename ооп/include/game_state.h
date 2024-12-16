#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <iostream> 
#include <fstream> 
#include <vector> 

#include "game_process.h" 

// класс состояния игры
class GameState {
public:
    GameState(GameSession& gameSession);                                        // конструктор, принимающий объект GameSession по ссылке
    bool save(const char* filename);                                            // метод сохранения состояния игры в файл
    bool load(const char* filename);                                            // метод загрузки состояния игры из файла
    friend std::ostream& operator<<(std::ostream& os, const GameState& state);  // перегрузка оператора вывода для класса GameState
    friend std::istream& operator>>(std::istream& is, GameState& state);        // перегрузка оператора ввода для класса GameState

private:
    GameSession& session;                                                       // ссылка на объект GameSession, текущая сессия игры
};

#endif
