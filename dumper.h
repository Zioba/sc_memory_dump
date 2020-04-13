//
// Created by artsiom on 2/25/20.
//

#ifndef KNOWLEDGE_BASE_DUMP_WAVEFINDPATH_H
#define KNOWLEDGE_BASE_DUMP_WAVEFINDPATH_H
#define NREL_FORMAT_STR     "nrel_format"
#define DUMP_FOLDER "/home/alexander/Desktop/KnowledgeDump.scs"
#define DUMP_CONTENT_FOLDER "/home/alexander/Desktop/content/"

#include <cstdio>
#include "model/Node.h"

using namespace std;

sc_char *getScLinkData(const sc_addr &idtf, sc_uint32 &read_length);
bool printEl(sc_addr element, string *strBuilder);
bool printEl2(sc_addr element, string *strBuilder);
void printEdge(sc_addr element, const char* connector, Node* node, string *strBuilder);
sc_char *printContent(sc_addr element);
bool checkLinkFormat(sc_addr element, string *format);
sc_char *saveContentFile(sc_addr element, char* data, string format, sc_uint32 &read_length);
bool isAddrExist(sc_addr addr);
int getIdByAddr(sc_addr addr);

#endif //KNOWLEDGE_BASE_DUMP_WAVEFINDPATH_H
