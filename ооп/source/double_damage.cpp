#include "../include/double_damage.h" 

DoubleDamageAbility::DoubleDamageAbility(AbstractPlayer& player_ref): player(player_ref) {}

// метод использования способности двойного урона
void DoubleDamageAbility::use() {
    player.set_damage(2);
}

std::string DoubleDamageAbility::get_name() {return "Double-damage";} // возвращает имя способности