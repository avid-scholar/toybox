#ifndef AEON__EXE_LU_DIE_H
#define AEON__EXE_LU_DIE_H 1

void die_actually (char const * file, long line, char const * fmt, ...);

#define die(fmt...) die_actually (__FILE__, __LINE__, fmt);

#endif //AEON__EXE_LU_DIE_H
