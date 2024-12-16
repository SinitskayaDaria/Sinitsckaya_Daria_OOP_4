#include "../include/board.h"

// конструктор инициализирующий игровое поле
Board::Board(int size) {
    for (int i = 0; i < size; ++i) {
        field.emplace_back();             // добавление новой строки в поле
        for (int j = 0; j < size; ++j) {
            field[i].emplace_back();      // добавление новой клетки в текущую строку
        }
    }
}

// конструктор копирования
Board::Board(const Board &other) : field(other.field) {}

// конструктор перемещения
Board::Board(Board &&other) noexcept : field(std::move(other.field)) {}

// оператор копирования
Board& Board::operator=(const Board& other) {
    if (this != &other) {      // проверка на самоприсвоение
        field = other.field;   // копирование содержимого поля
    }
    return *this;              // текущий объект
}

// оператор перемещения
Board& Board::operator=(Board&& other) noexcept {
    if (this != &other) {               // проверка на самоприсвоение
        field = std::move(other.field); // перемещение содержимого поля
    }
    return *this;                       // текущий объект
}

// конструктор клетки поля 
Board::Cell::Cell() : segment(nullptr), actual_display('~'),  public_display('~') {}

// метод размещения корабля на поле
bool Board::place_ship(Ship& ship, std::vector<std::pair<char, int>>& coords, char orientation, bool show_errors) {
    ship.set_orientation(orientation);         // установка ориентации корабля
    try {
        validate_positions(ship, coords);      // проверка допустимости позиции для размещения
    } catch (GameException& exception) {
        if (show_errors) {
        console.print_error(exception.what()); // вывод сообщения об ошибке
        }
        return false;
    }

    // проход по координатам и размещение корабля
    for (size_t i = 0; i < coords.size(); ++i) {
        int row = coords[i].second - 1;                    // получение строки
        int col = coords[i].first - 'A';                   // получение столбца
        field[row][col].actual_display = 'S';              // установка отображения клетки как занятой
        field[row][col].segment = &ship.get_segments()[i]; // привязка сегмента корабля к клетке
    }
    return true;  // успешное размещение
}

// метод проверки наличия корабля в клетке
bool Board::have_ship(std::pair<char, int> coords) {
    try {
        int column = coords.first - 'A'; // получение столбца
        int row = coords.second - 1;     // получение строки
        // проверка границ поля
        if (row >= static_cast<int>(field.size()) || column >= static_cast<int>(field.size())) { 
            throw std::out_of_range("Out of range"); // "Вне зоны досягаемости"
        }
        return (field[row][column].segment != nullptr); // есть сегмент
    } catch (std::exception &e) {
        return false; // возникновение исключения
    }
}

// метод выстрела по координате
bool Board::shoot(std::pair<char, int>& coords, int damage, bool silent) {
    int row = coords.second - 1;                   // получение строки
    int col = coords.first - 'A';                  // получение столбца
    Cell* cell_ptr = nullptr; 
    try {
        cell_ptr = &(field.at(row).at(col));       // указатель на ячейку
    } catch (std::out_of_range &e) {
        if (!silent) {
            console.print_error(OutOfBoundsAttackException().what()); // вывод сообщения об ошибке
        }
        return false; // координаты выходят за пределы поля
    }
    Cell& cell = *cell_ptr; // целевая ячейка

    // обработка попадания или промаха
    if (cell.segment) { // в ячейке есть сегмент корабля
        if (damage == 2) {
            // Непосредственное уничтожение сегмента
            cell.segment->destroy();    // Уничтожение сегмента
            cell.actual_display = 'X';  // Обновление отображения
            cell.public_display = cell.actual_display;
            console.print(coords.first, coords.second, ": Segment destroyed.\n");
            
        } else {
            cell.segment->hit(); // удар по сегменту
            if (!silent) {
                // обновление отображения и вывод результов
                if (cell.segment->is_destroyed()) {
                    cell.actual_display = 'X';                 // установка отображения как уничтоженное
                    cell.public_display = cell.actual_display; // обновление отображения для противника
                    console.print(coords.first, coords.second, ": Segment destroyed.\n");
                } else {
                    cell.actual_display = '!';                 // установка отображения как пораженное
                    cell.public_display = cell.actual_display; // обновление отображения для противника
                    console.print(coords.first, coords.second, ": Target hit.\n");
                }
            }
        }
    } else { // в ячейке нет сегмента
        if (!silent) {
            cell.actual_display = '*'; // обновление отображения как промах
            cell.public_display = cell.actual_display;
            console.print(coords.first, coords.second, ": Miss.\n");
        }
        return false; // промах
    }
    return true; // успешный выстрел
}

// метод проверки позиций корабля перед его размещением
void Board::validate_positions(Ship& ship, std::vector<std::pair<char, int>>& coords) {
    // направления для проверки наличия соседних занятых ячеек
    std::vector<std::pair<int, int>> directions = {
            {-1, -1}, {-1, 0}, {-1, 1},
            { 0, -1}, { 0, 0}, { 0, 1},
            { 1, -1}, { 1, 0}, { 1, 1}
    };
    
    // проверка каждой пары координат
    for (auto& coord_pair: coords) {
        // проверка диапазона букв и цифр
        if ((int)coord_pair.first > 90 || (int)coord_pair.first < 65 || coord_pair.second > 26 || coord_pair.second < 1) {
            throw ShipPlacementException(); // координаты выходят за пределы
        }

        int column = coord_pair.first - 'A';                  // получение столбца
        int row = coord_pair.second - 1;                      // получение строки

        // проверка выхода за пределы игрового поля
        if (static_cast<size_t>(row) > field.size() - 1 || static_cast<size_t>(column) > field.size() - 1) {
            throw ShipPlacementException();
        }

        // проверка соседних ячеек на наличие занятых
        for (auto &dir: directions) {
            int temp_column = column + dir.second;
            int temp_row = row + dir.first;
            // соседняя ячейка занята, выбрасываем исключение
            if (temp_row >= 0 && temp_column >= 0 && static_cast<size_t>(temp_row) < field.size() && static_cast<size_t>(temp_column) < field.size()) {

                if (field[temp_row][temp_column].actual_display == 'S') {
                    throw ShipPlacementException();
                }
            }
        }
    }

    // проверка уникальности координат и ориентации корабля
    std::vector<char> letters;
    std::vector<int> digits;
    for (auto [letter, digit] : coords) {
        digits.push_back(digit);
        letters.push_back(letter);
    }
    std::set<int> unique_digits(digits.begin(), digits.end());
    std::set<char> unique_letters(letters.begin(), letters.end());

    // проверка для вертикального размещения
    if (ship.get_orientation() == Ship::ship_orientation::Vertical) {
        int min = *std::min_element(digits.begin(), digits.end());
        int max = *std::max_element(digits.begin(), digits.end());

        if (unique_letters.size() != 1) { throw WrongShipCoordinatesException(); }
        if (static_cast<size_t>(max - min) != digits.size() - 1) { throw WrongShipCoordinatesException(); }
        if (unique_digits.size() != digits.size()) { throw WrongShipCoordinatesException(); }
    } else { // проверка для горизонтального размещения
        int min = *std::min_element(letters.begin(), letters.end());
        int max = *std::max_element(letters.begin(), letters.end());

        if (unique_digits.size() != 1) { throw WrongShipCoordinatesException(); }
        if (static_cast<size_t>(max - min) != letters.size() - 1) { throw WrongShipCoordinatesException(); }
        if (unique_letters.size() != letters.size()) { throw WrongShipCoordinatesException(); }
    }
}

// метод получения размера игрового поля
int Board::get_field_size() {
    return (int)field.size(); 
}

// метод получения клетки по координатам
const Board::Cell& Board::get_cell(int x, int y) {
    return field[x][y]; // ссылка на клетку
}

// метод преобразования данных состояния игровой сессии в поток вывода
void Board::serialize(std::ostream& os) {
    os << field.size() << "\n"; // запись размера игрового поля
    
    // проход по всем элементам игрового поля
    for (std::size_t i = 0; i < field.size(); ++i) {
        for (std::size_t j = 0; j < field.size(); ++j) {
            // состояние каждой ячейки поля
            os << field[i][j].actual_display << " " << field[i][j].public_display << " ";
            // проверка наличия сегмента в ячейке
            if (field[i][j].segment) {
                // сегмент существует, записываем его ID
                os << field[i][j].segment->get_id() << "\n";
            } else {
                // сегмент отсутствует, записываем -1
                os << -1 << '\n';
            }
        }
    }
}

// метод преобразования данных состояния игровой сессии из потока ввода
void Board::deserialize(std::istream& is, ShipManager& manager) {
    int temp_size;           //размер игрового поля
    is >> temp_size;         // считывание размера игрового поля
    field.resize(temp_size); // изменение размера игрового поля до считанного значения
    
    // проход по всем элементам игрового поля
    for (int i = 0; i < temp_size; ++i) {
        field[i].resize(temp_size); 
        
        for (int j = 0; j < temp_size; ++j) {
            int temp_id;
            // чтение данных для каждой ячейки
            is >> field[i][j].actual_display >> field[i][j].public_display >> temp_id;
            
            // проверка на ID сегмента
            if (temp_id >= 0) {
                // нахождение соответствующего сегмента и присваиваение его ячейке
                field[i][j].segment = manager.find_segment_by_id(temp_id);
            } else {
                field[i][j].segment = nullptr;
            }
        }
    }
}
