#ifndef SEARCH_H
#define SEARCH_H

#include "fileinput.h"

bool samePhone(int* phone1, int* phone2);
void filesearch(string filename);
void fileReset(const string& filename, queue& cq, queue& sq, node* prenode, node* current);

#endif
