#ifndef SEGMENT_H 
#define SEGMENT_H

#include <iostream>

class Segment {
public:
    enum class segment_state { // состояния сегмента

        Whole,      // целый
        Damaged,    // повреждён
        Destroyed   // уничтожен
};  
    
    Segment();
    void hit();                             // метод обработки попадания в сегмент
    bool is_destroyed() const;              // метод проверки уничтожения сегмента
    void destroy();                         // метод мгновенного уничтножения сегмента
    int get_id();                           // метод получения ID сегмента
    void serialize(std::ostream& os);       // метод преобразования данных состояния игровой сессии в поток вывода
    void deserialize(std::istream& is);     // метод преобразования данных состояния игровой сессии из потока ввода

private:
    int id;                       // ID сегмента
    Segment::segment_state state; // текущее состояние сегмента
    static int next_id;           // следующий ID сегмента
};

#endif 
