#include "../include/abilities_manager.h"

AbilitiesManager::AbilitiesManager(AbstractPlayer& player_ref, AbstractPlayer& enemy_ref)
    : player(player_ref), enemy(enemy_ref) {
    
    factory.register_ability<DoubleDamageAbility>("Double-damage", [](void* object) {
        // создание уникального указателя на способность DoubleDamageAbility
        return std::make_unique<DoubleDamageAbility>(*static_cast<AbstractPlayer*>(object));
    });

    factory.register_ability<ScannerAbility>("Scanner", [](void* object) {
        // создание уникального указателя на способность ScannerAbility
        return std::make_unique<ScannerAbility>(*static_cast<Board*>(object));
    });

    factory.register_ability<ShellingAbility>("Shelling", [](void* object) {
        // создание уникального указателя на способность ShellingAbility
        return std::make_unique<ShellingAbility>(*static_cast<Board*>(object));
    });

    add_ability(); // добавление способности для игрока
}

// метод добавления случайной способности в очередь способностей
void AbilitiesManager::add_ability() {
    std::random_device rd;                          // генератор случайных чисел
    std::mt19937 gen(rd());                         // инициализация генератора
    std::uniform_int_distribution<> range(0, 2);    // диапазон случайных чисел от 0 до 2
    
    int result = range(gen);                        // генерация случайного числа

    // выбор случайной способности
    switch (result) {
        case 0:
            abilities.push_front(factory.create_ability("Double-damage", &player));
            break;
        case 1:
            abilities.push_front(factory.create_ability("Scanner", &enemy.get_board()));
            break;
        case 2:
            abilities.push_front(factory.create_ability("Shelling", &enemy.get_board()));
            break;
    }
}

// метод использования первой способности из очереди
void AbilitiesManager::use_ability() {
    // проверка наличия способности в очереди
    if (!abilities.empty()) {
        console.print("Now using: ", abilities.front()->get_name(), " ability.\n");
        abilities.front()->use(); // использование способности
        abilities.pop_front();    // удаление использованной способности из очереди
    } else {
        throw AbilityUnavailableException();
    }
}

// метод преобразования данных состояния игровой сессии в поток вывода
void AbilitiesManager::serialize(std::ostream& os) {
    os << abilities.size() << '\n';         // запись количества способностей
    for (const auto& ability : abilities) {
        os << ability->get_name() << '\n';  // запись названий способностей
    }
}

// метод преобразования данных состояния игровой сессии из потока ввода
void AbilitiesManager::deserialize(std::istream& is) {
    int abilities_count;
    is >> abilities_count;  // чтение количества способностей
    
    // очистка предыдущих способностей
    abilities = std::deque<std::unique_ptr<Ability>>{};
    
    // восстановление каждой способности на основе ее имени
    for (int i = 0; i < abilities_count; ++i) {
        std::string name;
        is >> name;   // чтение названия способности
        if (name == "Double-damage"){
            // восстановление способности Double-damage для игрока
            abilities.push_front(factory.create_ability(name, &player));
        } else {
            // восстановление других способностей для доски врага
            abilities.push_front(factory.create_ability(name, &enemy.get_board()));
        }
    }
}
