#ifndef SHELLING_H 
#define SHELLING_H

#include "abilities.h" 

// класс способности обстрела
class ShellingAbility : public Ability {
public:
    ShellingAbility(Board& opponent_board); // конструктор, принимающий ссылку на поле противника
    void use() override;                    // переопределение метода для реализации способности обстрела
    std::string get_name() override;        // переопределение метода для получения имени способности
    ~ShellingAbility() = default;           // деструктор класса, по умолчанию

private:
    Board& board; // ссылка на поле противника
};

#endif 
