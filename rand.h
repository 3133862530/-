#ifndef RAND_H
#define RAND_H

#include "class.h"
#include "fileinput.h"
#include <string>
#include <random>
#include <cstdlib>
#include <ctime>
#include <chrono>

string randname();
void randphone(int* phone);
string randid();
void randinput(queue& cq, queue& sq);

#endif
