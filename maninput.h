#ifndef MANINPUT_H
#define MANINPUT_H

#include "class.h"
#include "fileinput.h"
#include <string>
#include <sstream>
#include <limits>
#include <iomanip>

void getValidNumber(int& number);
void InputTime(int& h, int& m);
void PrintTime(int h, int m);
void setTime();
void maninput(queue& cq, queue& sq);

#endif