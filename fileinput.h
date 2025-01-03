#ifndef FILEINPUT_H
#define FILEINPUT_H

#include "class.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <iomanip>

void getValidNumber(int& number);
void InputTime(int& h, int& m);
void inputPhone(int* phone);
void inputId(string& id);
void inputArrtime(int& arrtime, int& pretime);
void inputReqtime(int& reqtime, const int& arrtime, const bool& kind);
void PrintTime(int h, int m);
void PrintClient(client c);
bool fileread(const string& filename, queue& cq, queue& sq);
void filewrite(const string& filename, queue& q, bool verwrite);
void fileclean(const string& filename);

#endif