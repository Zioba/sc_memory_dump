//
// Created by alexander on 17.02.20.
//

#ifndef WAVE_NODE_H
#define WAVE_NODE_H


#include <sc-store/sc_types.h>
#include <vector>
#include <string>

class Node {
private:
    sc_addr addr;
    int id;
    std::vector<std::string> types;


public:

    Node(sc_addr addr, int id);
    ~Node();
    sc_addr getAddr();
    int getId();
    std::vector<std::string> getTypes();
    void addType(std::string type);

};


#endif //WAVE_NODE_H
