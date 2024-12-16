#include "../include/enemy.h"

Enemy::Enemy(int field_size, int ships_count, const std::vector<int>& sizes)
    : AbstractPlayer(field_size, ships_count, sizes) {} 

// метод расстановки кораблей на поле
bool Enemy::place_ships() {
    // ориентации размещения кораблей
    char orientations[] {
        'H',   // горизонтальная ориентация
        'V'    // вертикальная ориентация
    };

    // генератор случайных чисел
    std::random_device rd;   // генератор случайных чисел
    std::mt19937 gen(rd());  // инициализация генератора Mersenne Twister
    
    // определение диапазонов для случайного выбора ориентации и координат
    orient_range = std::uniform_int_distribution<>(0, 1);                            // диапозон для ориентации
    letter_range = std::uniform_int_distribution<>(65, 64 + board.get_field_size()); // диапазон для букв 
    digit_range = std::uniform_int_distribution<>(1, board.get_field_size());        // диапазон для цифр

    // получение доступа к массиву кораблей игрока
    std::vector<Ship>& ships = ship_manager.get_ships(); 

    // перебор всех кораблей для их расстановки
    for (auto& ship : ships) {
        bool placed = false; // флаг успешного размещения корабля
        int attempts = 50;   // максимальное количество попыток для размещения корабля
        
        // размещение корабля до тех пор, пока не будет размещен или не закончатся попытки
        while (!placed && attempts > 0) {
            std::vector<std::pair<char, int>> coords;           // массив координат корабля
            char orientation = orientations[orient_range(gen)]; // случайная ориентация корабля
            int digit = digit_range(gen);                       // случайная цифра для размещения
            int letter_code = letter_range(gen);                // случайный код буквы для размещения

            // определение координаты корабля в зависимости от его ориентации
            if (orientation == 'H') { // горизонтальная ориентация
                for (int i = 0; i < ship.get_length(); ++i) {
                    coords.emplace_back((char)(letter_code + i), digit); // добавление координаты
                }
            } else { // вертикальная ориентация
                for (int i = 0; i < ship.get_length(); ++i) {
                    coords.emplace_back((char)letter_code, digit + i); // добавление координаты
                }
            }

            // размещение корабля на поле
            if (board.place_ship(ship, coords, orientation, false)) {
                placed = true; // успешно размещен
            }
            attempts--; // уменьшение количества оставшихся попыток
        }

        // корабль не был размещен после всех попыток
        if (attempts <= 0 && !placed) {
            return false;
        }
    }
    return true; // корабли успешно размещены
}

// метод выстрела по противнику
bool Enemy::make_shot(AbstractPlayer& opponent, std::optional<std::pair<char, int>> coords) {
    // генератор случайных чисел
    std::random_device rd;
    std::mt19937 gen(rd());
    
    // генерация случайных координат для выстрела
    char letter = (char)letter_range(gen); // случайная буква
    int digit = digit_range(gen);          // случайная цифра

    std::pair<char, int> coordinate(letter, digit); // формирование пары координат
    return opponent.get_board().shoot(coordinate);  // выстрел по противнику
}
