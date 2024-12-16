#ifndef SHIP_H 
#define SHIP_H

#include <vector>  
#include <map>      
#include <string>  
#include <algorithm> 

#include "segment.h"

class Ship {
public:
    enum class ship_orientation { 
        Horizontal,  // горизонтальное положение
        Vertical     // вертикальное положение 
    };  
    Ship();                                     // конструктор по умолчанию
    Ship(int length);                           // конструктор, принимающий длину корабля
    void set_orientation(char orientation);     // метод установки ориентации корабля 
    Ship::ship_orientation get_orientation();   // метод получения текущей ориентации корабля
    std::vector<Segment>& get_segments();       // метод получения массива сегментов корабля
    Segment* get_segment_by_id(int id);         // метод нахождения сегмента по ID
    int get_length() const;                     // метод получения длины корабля
    bool killed() const;                        // метод проверки уничтожения корабля 
    void serialize(std::ostream& os);           // метод преобразования данных состояния игровой сессии в поток вывода
    void deserialize(std::istream& is);         // метод преобразования данных состояния игровой сессии из потока ввода

private:
    int length;                             // длина корабля
    std::vector<Segment> segments;          // массив сегментов корабля
    Ship::ship_orientation orientation;     // ориентация корабля 
    
};

#endif


