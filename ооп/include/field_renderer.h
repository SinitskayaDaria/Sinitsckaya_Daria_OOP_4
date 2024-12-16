#ifndef FIELDRENDERER_H
#define FIELDRENDERER_H

#include "board.h"

// шаблонный класс для отображения игровых полей
template<class Renderer>
class FieldRenderer {
public:
    FieldRenderer() : renderer() {} // конструктор по умолчанию

    // метод отображения полей игрока и противника
    void display(Board& player_board, Board& enemy_board) {
        renderer.display(player_board, enemy_board);
    }

private:
    Renderer renderer; 
};

#endif 
