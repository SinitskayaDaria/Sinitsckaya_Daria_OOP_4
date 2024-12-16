#include "../include/console_renderer.h"

// метод отображения игровых полей игрока и противника
void ConsoleRenderer::display(Board& player_board, Board& enemy_board) {
    int size = player_board.get_field_size();                  // размер игрового поля
    int rw_counter = 1;                                        // счетчик для отображения номеров строк
    
    for (int i = 0; i < 2 * size + 1; ++i) {                   // проход по количеству строк
        if (i % 2 == 0) {                                      // строка четная (разделительная строка)
            print_separating_row(size);                        // печать разделительной строки
            console.print("      ");                           // пробел между полями
            print_separating_row(size);                        // печать разделительной строки для противника
            console.print("\n");                               
        } else {                                               // строка нечетная (строка с данными)
            print_data_row(player_board, rw_counter, false);   // печать строки данных для игрока
            console.print("      ");                           // пробел между полями
            print_data_row(enemy_board, rw_counter, true);     // печать строки данных для противника
            console.print("\n");                              
            rw_counter++;                                      // увеличение счетчика строк
        }
    }

    print_letters_row(size);                                   // печать нумерации столбцов для игрока 
    console.print("      ");                                   // пробел между полями
    print_letters_row(size);                                   // печать нумерации столбцов для противника
    console.print("\n\n");                                     
}

// метод печати разделительной строки
void ConsoleRenderer::print_separating_row(int size) {
    console.print("    ");              
    for (int j = 0; j < size; ++j) {    // проход по количеству клеток в строке
        console.print("+ — ");          // печать разделителей между клетками
    }
    console.print("+");                 // завершающий разделитель
}

// метод печати строки с данными игрового поля
void ConsoleRenderer::print_data_row(Board& board, int rw_counter, bool is_enemy) {
    console.print(std::setw(2), rw_counter, ". ");                          // печать номера строки

    for (int j = 0; j < board.get_field_size(); ++j) {                      // проход по количеству клеток в строке
        console.print("| ");                                                // печать разделителя слева от клетки
        char cell_display;
        if (is_enemy) {                                                      // поле противника
            cell_display = board.get_cell(rw_counter - 1, j).public_display; // получение публичного отображения клетки
        } else {                                                             // поле игрока
            cell_display = board.get_cell(rw_counter - 1, j).actual_display; // получение фактического отображения клетки
        }

         // выбор отображения в зависимости от содержимого клетки
        switch (cell_display) {
            case '~': // пусто
                console.print("  ");
                break;
            default:
                console.print(cell_display, " ");
        }
        
    }
    console.print("|");                          // завершение строки с данными
}

// метод для печати строки с буквами
void ConsoleRenderer::print_letters_row(int size) {
    char letters[26];
        for (int i = 0; i < 26; ++i) {
            letters[i] = 'A' + i;  // Заполнение буквами от 'A' до 'Z'
        }
    console.print("    ");                    
    for (int j = 0; j < size; ++j) {            // проход по количеству столбцов
        console.print("  ", letters[j], " ");   // печать буквы с отступами
    }
    console.print(" ");                         // завершение строки с буквами
}
