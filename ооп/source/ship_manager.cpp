#include "../include/ship_manager.h"

ShipManager::ShipManager(): destroyed_ships(0), ships(0) {}

ShipManager::ShipManager(int count, std::vector<int> sizes) : destroyed_ships(0) {
    for (int i = 0; i < count; ++i) {
        ships.emplace_back(sizes[i]);  // добавляем новый корабль
    }
}

// метод получения ссылки на массив кораблей
std::vector<Ship>& ShipManager::get_ships() {
    return ships; 
}

// метод нахождения сегмента по ID
Segment* ShipManager::find_segment_by_id(int id) {
    Segment* seg_ptr = nullptr; // указатель на сегмент
    for (auto& ship : ships) {
        seg_ptr = ship.get_segment_by_id(id);
        if (seg_ptr) {
            break;
        }
    }
    return seg_ptr;
}

// метод обновления состояния кораблей
bool ShipManager::check_ships() {
    auto it = ships.begin();
    int temp_destroyed_ships_counter = 0; // временный счетчик уничтоженных кораблей

    while (it != ships.end()) {
        if ((*it).killed()) { // проверка на уничтожение текущего корабля
            temp_destroyed_ships_counter++; 

            if (temp_destroyed_ships_counter > destroyed_ships) {
                destroyed_ships = temp_destroyed_ships_counter; // обновление общего количества уничтоженных кораблей
                console.print("Ship destroyed.\n"); 
            }
        }
        it++;
    }
    
    return false;
}

// метод проверки уничтожения всех кораблей
bool ShipManager::is_all_ships_destroyed() { 
    return destroyed_ships == static_cast<int>(ships.size());
}

// метод преобразования данных состояния игровой сессии в поток вывода
void ShipManager::serialize(std::ostream& os) {
    os << destroyed_ships << " ";
    os << ships.size() << "\n";
    for (auto& ship : ships) {
        ship.serialize(os);
    }
}

// метод преобразования данных состояния игровой сессии из потока ввода
void ShipManager::deserialize(std::istream& is) {
    int ships_count;
    is >> destroyed_ships;
    is >> ships_count;
    ships.resize(ships_count);
    for (auto& ship : ships) {
        ship.deserialize(is);
    }
}