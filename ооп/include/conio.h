#ifndef CONIO_H
#define CONIO_H

#include <iostream> 
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

// функция считывает один символ с клавиатуры без ожидания нажатия клавиши Enter
int _getch();

// функция проверяет, была ли нажата клавиша (не блокируя выполнение)
int _kbhit();

#endif