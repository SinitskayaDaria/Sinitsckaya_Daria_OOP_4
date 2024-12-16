#include "../include/player.h" 

Player::Player(int field_size, int ships_count, const std::vector<int>& sizes)
    : AbstractPlayer(field_size, ships_count, sizes) {}

// метод размещения кораблей игрока на поле
bool Player::place_ships() {
    // получение доступа к менеджеру кораблей для игрока
    std::vector<Ship>& ships = ship_manager.get_ships();

    // проход по каждому кораблю для его размещения
    for (auto& ship : ships) {
        bool placed = false; // флаг успешного размещения корабля
        while (!placed) { 
            std::vector<std::pair<char, int>> coords;   // массив координат размещаемого корабля
            console.print("Enter orientation and coordinates for a ship of length ", ship.get_length(), ": "); // запрос ввода ориентации и координат

            std::string input = console.get_line();     // ввода пользователя
            std::stringstream ss(input);                // строковый поток для обработки ввода
            char orientation;                           // ориентация корабля
            ss >> orientation; 

            // считывание координат для размещения корпуса корабля
            for (int i = 0; i < ship.get_length(); ++i) {
                std::pair<char, int> position; // пара для хранения координат (буква и число)
                std::string coord;             // переменная для считывания координаты
                ss >> coord; 

                // провеока пустого ввода или размера координат меньше 2
                if (coord.empty() || coord.size() < 2) { 
                    console.print_error("Invalid input format.\n"); // сообщение об ошибке
                    coords.clear();                                 // очистка вектора координат
                    continue;                                       // переход к следующей итерации цикла
                }

                // преобразование координаты в нужный формат
                position.first = toupper(coord[0]);           // перевод буквы в верхний регистр
                try {
                    // преобразование подстроки координат в целое число
                    position.second = std::stoi(coord.substr(1));
                } catch (std::exception& e) {
                    console.print_error("Invalid coordinate.\n");   // сообщение об ошибке
                    coords.clear();                                 // очистка вектора координат
                    continue;                                       // переход к следующей итерации цикла
                }

                coords.push_back(position);                         // добавление координаты в массив
            }

            // проверка совпадения количества указанных координат с длиной корабля
            if (ship.get_length() < 0 || coords.size() != static_cast<size_t>(ship.get_length())) {
            console.print_warning("Invalid number of coordinates.\n"); // сообщение об ошибке
            continue;                                                  // переход к следующей итерации цикла
            }

            // размещение корабля на поле
            if (!board.place_ship(ship, coords, toupper(orientation))) {
                console.print_warning("Cannot place here. Try again.\n"); // вывод сообщения, если размещение невозможно
            } else {
                placed = true; 
            }
        }
    }
    return true; // все корабли успешно размещены
}

// метод выстрела противника
bool Player::make_shot(AbstractPlayer& opponent, std::optional<std::pair<char, int>> coords) {
    if(coords){
        return opponent.get_board().shoot(coords.value());     // выполенение выстрела противника по указанным координатам и возвращение результата
    } 
    return false;
}
