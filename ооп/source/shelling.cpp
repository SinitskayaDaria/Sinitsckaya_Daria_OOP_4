#include "../include/shelling.h" 

ShellingAbility::ShellingAbility(Board& opponent_board) : board(opponent_board) {}

// метод использования способности обстрела
void ShellingAbility::use() {
    int size = board.get_field_size(); // получение размера поля
    bool hit = false;                  // переменная для отслеживания попадания

    std::uniform_int_distribution<> letter(65, 64 + size); // определение равномерного распределения для букв 
    std::uniform_int_distribution<> digit(1, size);        // определение равномерного распределения для цифр

    // пока не будет сделано успешное попадание
    while (!hit) {
        // генератор случайных чисел
        std::random_device rd;  // получение случайного начального значения
        std::mt19937 gen(rd()); // инициализация генератора Mersenne Twister

        // генерация случайной пару координат
        std::pair<char, int> coordinate((char)(letter(gen)), digit(gen));
        
        // проверка наличия корабля на сгенерированных координатах
        if (board.have_ship(coordinate)) {
            // есть корабль, выстрел и отметка попадания
            board.shoot(coordinate);
            hit = true; 
        }
    }
}

std::string ShellingAbility::get_name() {return "Shelling";} // возвращает имя способности