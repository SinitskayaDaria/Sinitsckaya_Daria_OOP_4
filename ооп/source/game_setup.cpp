#include "../include/game_setup.h" // Подключаем заголовочный файл GameSetup

// метод считывания начальных данных игры
void GameSetup::read_start_data() {
    console.print("Enter field size: ");  // запрос на ввод размера игрового поля
    bool field_size_is_correct = false;   // флаг корректности введенного размера поля
    
    // пока пользователь не введет корректный размер поля
    while(!field_size_is_correct) {
        std::cin >> field_size; 

        // проверка состояния потока на буквы
        if (std::cin.fail()) {
        console.print_error("Invalid input! Please enter a number.\n");
        console.print("Try again: ");
        std::cin.clear(); // сброс состояния ошибки
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // пропуск некорректного ввода
        } else 
        {   // проверка нахождения размера в допустимом диапазоне от 1 до 26 
            if (field_size > 26 || field_size < 1) {
                console.print_error("Field sizes should be in the range [1, 26]!\n");
                console.print("Try again: "); 
            } else {
                field_size_is_correct = true; // размер корректен
            }
        }
    }

    console.print("Enter ships count: "); // запрос на ввод количества кораблей
    while (true) { // цикл для проверки ввода
        try {
            std::string input = console.get_line(); // получение строки ввода
            ships_count = std::stoi(input);        // попытка преобразовать строку в число

            if (ships_count <= 0) { // проверка на положительное значение
                console.print_error("Invalid input! Ships count must be a positive integer.\n");
                console.print("Try again: ");
            } else {
                break; // ввод корректен, выход из цикла
            }
        } catch (const std::invalid_argument&) {
            // обработка ситуации, когда std::stoi не может преобразовать строку
            console.print_error("Invalid input! Please enter a valid positive integer.\n");
            console.print("Try again: ");
        } 
    }

    console.print("Enter the size of each ship separated by a space: "); // запрос на ввод размеров кораблей
    // считывание размеров кораблей
    for (int i = 0; i < ships_count; ++i) {
        int size; // размер корабля
        while (true) { // цикл продолжается до тех пор, пока ввод не станет корректным
            std::cin >> size;

            if (std::cin.fail() || size <= 0) { // проверка на некорректный ввод и отрицательный/нулевой размер
                console.print_error("Invalid input! Please enter a positive integer.\n");
                console.print("Try again: ");
                std::cin.clear(); // сброс состояния потока
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // очистка некорректного ввода
            } else {
                break; // выход из цикла, если ввод корректный
            }
        }
        sizes.push_back(size); // добавление размера в массив размеров кораблей
    }
}

// Метод для получения количества кораблей
int GameSetup::get_ships_count() {
    return ships_count; // Возвращаем количество кораблей
}

// Метод для получения размеров кораблей
const std::vector<int>& GameSetup::get_sizes() {
    return sizes; // Возвращаем вектор размеров кораблей
}

// Метод для получения размера поля
int GameSetup::get_field_size() {
    return field_size; // Возвращаем размер поля
}

// метод преобразования данных состояния игровой сессии в поток вывода
void GameSetup::serialize(std::ostream& os) {
    os << field_size << " " << ships_count << " "; // размер поля и количество кораблей
    for (auto& size : sizes) {                     // проход по всем размерам кораблей
        os << size << " ";                         // каждый размер корабля
    }
    os << "\n";                                    // завершение записи новой строкой
}

 // метод преобразования данных состояния игровой сессии из потока ввода
void GameSetup::deserialize(std::istream& is){
    is >> field_size >> ships_count;                // считывание размера поля и количества кораблей из потока
    sizes.resize(ships_count);                      // изменение размера массива sizes, чтобы он соответствовал количеству кораблей
    for (int i = 0; i < ships_count; ++i) {         // проход по количеству кораблей
        is >> sizes[i];                             // считывание размера каждого корабля из потока
    }
}
