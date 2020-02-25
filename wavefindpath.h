//
// Created by artsiom on 2/25/20.
//

#ifndef KNOWLEDGE_BASE_DUMP_WAVEFINDPATH_H
#define KNOWLEDGE_BASE_DUMP_WAVEFINDPATH_H

#include <cstdio>

bool printEl(sc_memory_context *context, sc_addr element, FILE *f);
void printEl2(sc_memory_context *context, sc_addr element, FILE *f);
bool isAddrExist(sc_addr addr);
void processElement(_sc_addr addr);
int getIdByAddr(sc_addr addr);

#endif //KNOWLEDGE_BASE_DUMP_WAVEFINDPATH_H
