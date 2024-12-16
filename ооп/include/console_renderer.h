#ifndef CONSOLERENDERER_H 
#define CONSOLERENDERER_H

#include "board.h" 
#include "console_io.h" 

// класс, отвечающий за отображение игрового процесса в консоли
class ConsoleRenderer {
public:
    void display(Board& player_board, Board& enemy_board);              // метод отображения игровых полей игрока и противника

private:
    void print_separating_row(int size);                                // метод печати разделительной строки
    void print_data_row(Board& board, int rw_counter, bool is_enemy);   // метод печати строки с данными игрового поля
    void print_letters_row(int size);                                   // метод для печати строки с буквами
    ConsoleIO console;                                                  // объект для работы с консольным вводом/выводом
};

#endif 