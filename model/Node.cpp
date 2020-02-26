//
// Created by alexander on 17.02.20.
//

#include "Node.h"

sc_addr Node::get_addr() {
    return this->addr;
}

Node::Node(sc_addr addr, int id) {
    this->addr = addr;
    this->id = id;
}

int Node::get_Id() {
    return this->id;
}
