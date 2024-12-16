#include "../include/ship.h"

Ship::Ship(): length(0), segments(0), orientation(Ship::ship_orientation::Horizontal) {}

Ship::Ship(int length) 
    : length(length),                                     // инициализация длины корабля
      segments(length),                                   // инициализация массива сегментов заданной длины
      orientation(Ship::ship_orientation::Horizontal) {}  // установка начальной ориентации корабля

// метод установки ориентации корабля
void Ship::set_orientation(char direction) {
    
    if (direction == 'V') {

        orientation = Ship::ship_orientation::Vertical; 

    } else {

        orientation = Ship::ship_orientation::Horizontal; 
    }
}

// метод получения текущей ориентации корабля
Ship::ship_orientation Ship::get_orientation() {
    return orientation; 
}

// метод получения массива сегментов корабля
std::vector<Segment>& Ship::get_segments() {
    return segments; 
}

// метод нахождения сегмента по ID
Segment* Ship::get_segment_by_id(int id) {
    for (auto& segment : segments) {
        if (segment.get_id() == id) {
            return &segment;
        }
    }
    return nullptr;
}

// метод получения длины корабля
int Ship::get_length() const {
    return length; 
}

// метод проверки уничтожения корабля 
bool Ship::killed() const {
    
    // проверка, все ли сегменты корабля находятся в состоянии 'уничтожен'
    return std::all_of(segments.begin(), segments.end(), [](const Segment& segment) {
        return segment.is_destroyed(); 
    });
}

// метод преобразования данных состояния игровой сессии в поток вывода
void Ship::serialize(std::ostream& os) {
    os << length << ' ';
    os << (int)(orientation) << '\n';
    for (int i = 0; i < length; ++i) {
        segments[i].serialize(os);
    }
}

// метод преобразования данных состояния игровой сессии из потока ввода
void Ship::deserialize(std::istream& is) {
    int i_orientation;
    is >> length;
    is >> i_orientation;
    orientation = (ship_orientation)i_orientation;
    segments.resize(length);
    for (int i = 0; i < length; ++i) {
        segments[i].deserialize(is);
    }
}


