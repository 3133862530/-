#ifndef FILEINPUT_H
#define FILEINPUT_H

#include "class.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

void fileread(const string& filename, queue& cq, queue& sq);
void filewrite(const string& filename, queue& q, bool verwrite);

node* filesearch(const string& filename, const string& Name);
node* filesearchPrev(const string& filename, const string& Name);
void fileReset(const string& filename, const string& Name, queue& q);


#endif