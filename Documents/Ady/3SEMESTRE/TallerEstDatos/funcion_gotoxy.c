#include <windows.h>

int gotoxy(short x, short y)
{
   COORD coord;
   HANDLE h_stdout;

   coord.X = x;
   coord.Y = y;

   if ((h_stdout = GetStdHandle(STD_OUTPUT_HANDLE)) == INVALID_HANDLE_VALUE)
      return 0;

   if (SetConsoleCursorPosition(h_stdout, coord) == 0)
      return 0;

   return 1;
}

