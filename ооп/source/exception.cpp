#include "../include/exception.h" 

GameException::GameException(const std::string& message) 
    : std::runtime_error(message) {} 

AbilityUnavailableException::AbilityUnavailableException()
    : GameException("Attempted to use an ability when none are available.\n") {} // "Попытка использовать способность, когда ни одна из них не доступна."

ShipPlacementException::ShipPlacementException()
    : GameException("Attempted to place a ship too close to another ship or out of bounds.\n") {} // "Попытка разместить корабль слишком близко к другому кораблю или за его пределами."

OutOfBoundsAttackException::OutOfBoundsAttackException()
    : GameException("Attack attempted out of field bounds.\n") {} // "Попытка нападения за пределами поля боя."

WrongShipCoordinatesException::WrongShipCoordinatesException()
    : GameException("Attempted to place a ship with incorrect coordinates.\n") {} // "Предпринята попытка определить местоположение корабля с неверными координатами."

NotEnoughBindsException::NotEnoughBindsException()
    : GameException("Not all commands have assigned keys.\n") {} // "Не для всех команд назначены ключи."

MultipleBindException::MultipleBindException()
    : GameException("Detection of multiple key bindings in the configuration file.\n") {} // "Обнаружение нескольких привязок клавиш в файле конфигурации."
