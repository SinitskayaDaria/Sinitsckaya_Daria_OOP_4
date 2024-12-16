#include "../include/segment.h"

int Segment::next_id = 0;

Segment::Segment() : id(next_id++), state(Segment::segment_state::Whole) {} // установка начального состояния сегмента

// метод обработки попадания в сегмент
void Segment::hit() {

    switch (state) {

        case segment_state::Whole:
            state = Segment::segment_state::Damaged; // сегмент 'целый', помечаем его как 'повреждён'
            break;

        case segment_state::Damaged:
            state = Segment::segment_state::Destroyed; // сегмент 'повреждён', помечаем его как 'уничтожен'
            break;

        case segment_state::Destroyed: // сегмент 'уничтожен'
            break;
    }
}

// метод проверки уничтожения сегмента
bool Segment::is_destroyed() const {
    return state == Segment::segment_state::Destroyed; 
}

// метод мгновенного уничтожения сегмента
void Segment::destroy() {
    state = Segment::segment_state::Destroyed; // сегмент становится 'уничтожен'
}

// метод получения ID сегмента
int Segment::get_id() {
    return id;
}

// метод преобразования данных состояния игровой сессии в поток вывода
void Segment::serialize(std::ostream& os) {
    os << id << ' ';
    os << (int)(state) << "\n";
}

// метод преобразования данных состояния игровой сессии из потока ввода
void Segment::deserialize(std::istream& is) {
    int state_int;
    is >> id >> state_int;
    state = (segment_state)(state_int);
}