#ifndef BOARD_H 
#define BOARD_H

#include <iostream>      
#include <iomanip>        
#include <vector>     
#include <map>           
#include <set>         
#include <algorithm>     

#include "ship.h"         
#include "exception.h"  
#include "ship_manager.h"
#include "console_io.h"

// класс игрового поля
class Board {
public:
    // структура клетки поля
    struct Cell {
        Cell(); 
        Segment* segment;     // указатель на сегмент корабля
        char actual_display;  // символ, состояния клетки
        char public_display;  // символ, отображаемый для игрока
    };

    Board(int size);                                                                          // конструктор создания поля 
    Board(const Board& other);                                                                // конструктор копирования
    Board(Board&& other) noexcept;                                                            // конструктор перемещения
    Board& operator=(const Board& other);                                                     // оператор присваивания копированием
    Board& operator=(Board&& other) noexcept;                                                 // оператор присваивания перемещением
    bool place_ship(Ship& ship, std::vector<std::pair<char, int>>& coords, char orientation, bool show_errors = true); // метод размещения корабля на поле
    bool have_ship(std::pair<char, int> coords);                                              // метод проверки наличия корабля в указанной клетке
    bool shoot(std::pair<char, int>& coords, int damage = 1, bool silent = false);            // метод обработки выстрела по координатам
    int get_field_size();                                                                     // метод получения размера игрового поля
    const Cell& get_cell(int x, int y);                                                       // метод получения ссылки на клетку поля
    void serialize(std::ostream& os);                                                         // метод преобразования данных состояния игровой сессии в поток вывода
    void deserialize(std::istream& is, ShipManager& manager);                                 // метод преобразования данных состояния игровой сессии из потока ввода

private:
    std::vector<std::vector<Cell>> field;                                           // двумерный массив, содержащий клетки поля
    void validate_positions(Ship& ship, std::vector<std::pair<char, int>>& coords); // метод проверки корректности позиций размещаемого корабля
    ConsoleIO console;                                                              // объект для работы с консолью
};

#endif 
