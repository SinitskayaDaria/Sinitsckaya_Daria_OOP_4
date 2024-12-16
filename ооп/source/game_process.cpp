#include "../include/game_process.h"

GameSession::GameSession()
    : player(0, 0, {}),
      enemy(0, 0, {}),
      abilities_manager(player, enemy) {}

GameSession::GameSession(GameSetup& gameSetup)
    : setup(gameSetup),
      player(setup.get_field_size(), setup.get_ships_count(), setup.get_sizes()),
      enemy(setup.get_field_size(), setup.get_ships_count(), setup.get_sizes()),
      abilities_manager(player, enemy) {}

// функция выполнения одного шага игры
GameSession::step_result GameSession::run_game_step(std::pair<char, int> coordinates) {
    console.print("\033[2J\033[H");         // очистка консоли и перемещение курсора в верхний левый угол
    console.print("Your turn -> ");         // сообщение о ходе игрока
    player.make_shot(enemy, coordinates);   // игрок стреляет по противнику
    
    // проверка обновления статуса противника после хода игрока
    if (enemy.update()) {
        abilities_manager.add_ability(); // противник обновился, добавление способности игрока
    }
    
    // проверка проигрыша противника
    if (enemy.is_lose()) {
        console.print_success(" You win! Next round...\n");                                // сообщение о победе игрока   
        enemy = Enemy(setup.get_field_size(), setup.get_ships_count(), setup.get_sizes()); // создание нового противника для следующего раунда
        enemy.place_ships();                                                               // расстановка кораблей нового противника
    }

    console.print("Enemy turn -> ");       // сообщение о ходе противника
    enemy.make_shot(player, std::nullopt); // противник стреляет по игроку
    player.update();                       // обновление статуса игрока после хода противника
    
    // проверка проигрыша игрока
    if (player.is_lose()) {
        console.print_error(" Enemy win!\n");       // сообщение о пободе противника
        return GameSession::step_result::GameOver;  // завершение игры
    }

    field_renderer.display(player.get_board(), enemy.get_board()); // отображение состояния игрового поля игроков в консоли

    return GameSession::step_result::PlayerAlive; // возврат статуса игры: игрок жив
}

// метод размещения кораблей на поле
void GameSession::place_ships() {
    field_renderer.display(player.get_board(), enemy.get_board()); // отображение текущего состояния полей 
    player.place_ships();                                          // размещение кораблей игроком
    
    // проверка размещения кораблей противником
    if (!enemy.place_ships()) {
        console.print_error("The enemy was unable to position the ships!\nTry entering other data.\n"); // сообщение об ошибке
        return;
    }
    console.print("\n"); // печать новой строки
}

// функция использования способностей
bool GameSession::use_ability() {
    try {
        abilities_manager.use_ability(); // попытка использавания способности
        return true; 
    } catch (GameException& exception) {
        console.print(exception.what()); // сообщение об ошибке
        return false; 
    }
}

// метод преобразования данных состояния игровой сессии в поток вывода
void GameSession::serialize(std::ostream& os) {
    setup.serialize(os);                // настройки игры
    player.serialize(os);               // игрок
    enemy.serialize(os);                // противник
    abilities_manager.serialize(os);    // менеджер способностей
}

// метод преобразования данных состояния игровой сессии из потока ввода
void GameSession::deserialize(std::istream& is) {
    setup.deserialize(is);              // настройки игры
    player.deserialize(is);             // игрок
    enemy.deserialize(is);              // противник
    abilities_manager.deserialize(is);  // менеджер способностей
}
