#include "../include/abstract_player.h"

AbstractPlayer::AbstractPlayer(int field_size, int ships_count, const std::vector<int>& sizes)
    : board(field_size), ship_manager(ships_count, sizes) {} // инициализация поля и менеджера кораблей

// метод обновления состояния игрока
bool AbstractPlayer::update() {
    return ship_manager.check_ships(); // проверка состояния кораблей игрока
}

// метод получения значения урона игрока
int AbstractPlayer::get_damage() {
    return damage;
}

// метод установки значения урона игрока
void AbstractPlayer::set_damage(int dmg) {
    damage = dmg;
}

// метод получения ссылки на игровое поле
Board& AbstractPlayer::get_board() {
    return board; // ссылка на объект поле игрока
}

// метод получения ссылки на менеджер кораблей
ShipManager& AbstractPlayer::get_ship_manager() {
    return ship_manager; // ссылка на объект ship_manager
}

// метод проверки проигрыша игрока
bool AbstractPlayer::is_lose() {
    return ship_manager.is_all_ships_destroyed(); // проверка уничтожения всех кораблей игрока
}

// метод преобразования данных состояния игровой сессии в поток вывода
void AbstractPlayer::serialize(std::ostream& os) {
    ship_manager.serialize(os);
    board.serialize(os);
}

void AbstractPlayer::deserialize(std::istream& is) {
    ship_manager.deserialize(is);
    board.deserialize(is, ship_manager);
}
