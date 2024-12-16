#ifndef GAMESETUP_H 
#define GAMESETUP_H 


#include <iostream> 
#include <vector> 
#include <limits>

#include "console_io.h"

// класс настройки игры
class GameSetup {
public:
    void read_start_data();                // метод чтения начальных данных игры
    int get_ships_count();                 // метод получения количества кораблей
    const std::vector<int>& get_sizes();   // метод получения массива размеров кораблей
    int get_field_size();                  // метод получения размера игрового поля
    void serialize(std::ostream& os);      // метод преобразования данных состояния объекта GameSetup в поток вывода
    void deserialize(std::istream& is);    // метод преобразования данных состояния объекта GameSetup из потока ввода

private:
    int field_size;         // размер игрового поля
    int ships_count;        // количество кораблей
    std::vector<int> sizes; // массив размеров кораблей
    ConsoleIO console;      // объект для работы с консолью
};

#endif 
