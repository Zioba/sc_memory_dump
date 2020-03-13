//
// Created by artsiom on 2/25/20.
//

#ifndef KNOWLEDGE_BASE_DUMP_WAVEFINDPATH_H
#define KNOWLEDGE_BASE_DUMP_WAVEFINDPATH_H

#include <cstdio>
#include "model/Node.h"

bool printEl(sc_memory_context *context, sc_addr element, FILE *f);
bool printEl2(sc_memory_context *context, sc_addr element, FILE *f);
void printEdge(sc_addr element, const char* connector, Node* node);
bool isAddrExist(sc_addr addr);
int getIdByAddr(sc_addr addr);

#endif //KNOWLEDGE_BASE_DUMP_WAVEFINDPATH_H
