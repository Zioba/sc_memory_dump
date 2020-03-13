//
// Created by alexander on 17.02.20.
//

#include "Node.h"
#include <vector>

sc_addr Node::getAddr() {
    return this->addr;
}

Node::Node(sc_addr addr, int id) {
    this->addr = addr;
    this->id = id;
    this->types;
}

int Node::getId() {
    return this->id;
}

std::vector<std::string> Node::getTypes() {
    return this->types;
}

Node::~Node() {
    this->types.clear();

}

void Node::addType(std::string type) {
    this->types.push_back(type);
}
