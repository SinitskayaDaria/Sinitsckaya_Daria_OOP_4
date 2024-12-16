#include "../include/scanner.h" 

ScannerAbility::ScannerAbility(Board& opponent_board) : board(opponent_board) {}

// реализация метода способности сканера
void ScannerAbility::use() {
    std::pair<char, int> coordinate = console.get_coordinate(); // считывание координаты
    
    // направления, в которых будет происходить поиск
    std::vector<std::pair<int, int>> directions = {
            {0, 0},   // центр
            {1, 0},   // вправо
            {0, 1},   // вниз
            {1, 1},   // вправо и вниз
    };

    bool anything_find = false;                   // переменная для отслеживания нашедшихся кораблей
    int field_size = board.get_field_size();      // размер игрового поля

    // сканирование по всем направлениям
    for (auto& pos : directions) {
        std::pair<char, int> temp_coords((char)((int)coordinate.first + pos.first), coordinate.second + pos.second); // вычисление временных координат на основе направления

        // проверка границ игрового поля
        int row = temp_coords.second - 1;    // индекс строки (0-индексация)
        int col = (temp_coords.first - 'A'); // индекс столбца (0-индексация)

        if (row >= 0 && row < field_size && col >= 0 && col < field_size) {
            // проверка наличия корабля на найденной позиции
            if (board.have_ship(temp_coords)) {
                console.print("Scanner: Ship found\n");  // корабль найден
                anything_find = true;                    // флаг найдено 
                break;
            }
        }
    }
    
    // корабли не найдены
    if (!anything_find) {
        console.print("Scanner: Nothing found\n");
    }
}

std::string ScannerAbility::get_name() {return "Scanner";} // возвращает имя способности