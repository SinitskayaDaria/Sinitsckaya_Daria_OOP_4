#ifndef EXCEPTION_H  
#define EXCEPTION_H

#include <stdexcept>  
#include <string>     

// класс всех исключений
class GameException : public std::runtime_error {
public:
    GameException(const std::string& message); // конструктор, принимающий сообщение об ошибке
};

// класс исключения для случаев, когда способность недоступна
class AbilityUnavailableException : public GameException {
public:
    AbilityUnavailableException();             // конструктор, вызывающий конструктор GameException
};

// класс исключения для ошибок при размещении кораблей
class ShipPlacementException : public GameException {
public:
    ShipPlacementException();                  // конструктор, вызывающий конструктор GameException
};

// класс исключения для атак, выходящих за границы игрового поля
class OutOfBoundsAttackException : public GameException {
public:
    OutOfBoundsAttackException();              // конструктор, вызывающий конструктор GameException
};

// класс исключения для ошибок, связанных с неправильными координатами корабля
class WrongShipCoordinatesException : public GameException {
public:
    WrongShipCoordinatesException();           // конструктор, вызывающий конструктор GameException
};

// класс исключения для ошибок, возницающих, при не хватке привязок команд
class NotEnoughBindsException : public GameException {
public:
    NotEnoughBindsException();                // конструктор, вызывающий конструктор класса GameException
};

// класс исключения для ошибок, возникающих при множественных привязках клавиш в конфигурационном файле
class MultipleBindException : public GameException {
public:
    MultipleBindException();                 // конструктор, вызывающий конструктор класса GameException
};

#endif


