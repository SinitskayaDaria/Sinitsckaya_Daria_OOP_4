#ifndef ABILITIESMANAGER_H 
#define ABILITIESMANAGER_H

#include <queue>        
#include <random>      
#include <memory>      

#include "abilities.h" 
#include "abilities_factory.h"
#include "double_damage.h" 
#include "scanner.h"   
#include "shelling.h"  
#include "abstract_player.h" 
#include "exception.h" 
#include "console_io.h"  

// класс управления способностями игрока
class AbilitiesManager {
public:
    AbilitiesManager(AbstractPlayer& player_ref, AbstractPlayer& enemy_ref); // конструктор принимает ссылки на игрока и врага, инициализируя менеджер способностей
    void add_ability();                                                      // метод добавления способности в очередь
    void use_ability();                                                      // метод использования способности из очереди
    void serialize(std::ostream& os);                                        // метод преобразования данных состояния игровой сессии в поток вывода
    void deserialize(std::istream& is);                                      // метод преобразования данных состояния игровой сессии из потока ввода

private:
    std::deque<std::unique_ptr<Ability>> abilities;                          // очередь для хранения указателей на способности
    AbstractPlayer& player;                                                  // ссылка на игрока
    AbstractPlayer& enemy;                                                   // ссылка на противника
    ConsoleIO console;                                                       // объект для работы с консольным вводом/выводом
    AbilityFactory factory;                                                  // фабрика для создания способностей
};

#endif
