#ifndef ABILITYFACTORY_H
#define ABILITYFACTORY_H

#include <memory>
#include <string>
#include <unordered_map>
#include <functional>
#include <stdexcept>

#include "scanner.h"
#include "shelling.h"
#include "double_damage.h"


// класс создания способностей
class AbilityFactory {
public:
    using Creator = std::function<std::unique_ptr<Ability>(void*)>; // функция создания уникального указателя на способность

    // метод регистрации способности с ее именем и функцией-создателем
    template <typename T>                                           
    void register_ability(const std::string& name, Creator creator) {
        // добавление функции-создателя в словарь с именем способности
        creators[name] = [creator](void* object) {
            // проверка на наличие переданного объекта
            if (!object) {
                throw std::invalid_argument("Null object passed to ability creator.");
            }
            return creator(object);
        };
    }

    // метод создания способности по имени и переданному объекту
    std::unique_ptr<Ability> create_ability(const std::string& name, void* object) const {
        // поиск создателя способности в словаре
        auto it = creators.find(name);
        if (it == creators.end()) {
            // способность не зарегистрирована
            throw std::runtime_error("Ability not registered: " + name);
        }
        // создание и возврат способности
        return it->second(object);
    }

private:
    // словарь для хранения функции-создатели для способностей, ассоциированных с их именами
    std::unordered_map<std::string, Creator> creators;
};

#endif
