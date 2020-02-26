//
// Created by alexander on 17.02.20.
//

#ifndef WAVE_NODE_H
#define WAVE_NODE_H


#include <sc-store/sc_types.h>

class Node {
private:
    sc_addr addr;
    int id;

public:

    Node(sc_addr addr, int id);
    sc_addr get_addr();
    int get_Id();

};


#endif //WAVE_NODE_H
