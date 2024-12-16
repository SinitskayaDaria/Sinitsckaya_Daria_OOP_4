#include "../include/game_state.h"

GameState::GameState(GameSession& gameSession): session(gameSession) {}

// метод сохранения состояния игры в файл
bool GameState::save(const char* filename) {
    
    std::ofstream os(filename); // открытие файла для записи
    if (os.is_open()) {         // проверка успешности открытия файла
        os << *this;            // запись текущего состояния объекта
        os.close();             // закрытие файла
        return true;            // сохранение прошло успешно
    }
    return false;               // файл не удалось открыть
}

// метод загрузки состояния игры из файла
bool GameState::load(const char* filename) {
    
    std::ifstream is(filename); // открытие файла для чтения
    if (is.is_open()) {         // проверка успешности открытия файла
        is >> *this;            // чтение данных из файла и заполнение текущего состояния объекта
        is.close();             // закрытие файла
        return true;            // загрузка прошла успешно
    }
    return false;               // файл не удалось открыть
}

// перегрузка оператора вывода 
std::ostream& operator<<(std::ostream& os, const GameState& state) {
    state.session.serialize(os);    // преобразование данных состояния игровой сессии в поток вывода
    return os;                    
}

// перегрузка оператора ввода 
std::istream& operator>>(std::istream& is, GameState& state) {
    state.session.deserialize(is);  // преобразование данных из потока ввода в состояние игровой сессии
    return is;                     
}
