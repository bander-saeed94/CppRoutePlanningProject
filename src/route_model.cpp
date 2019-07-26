#include "route_model.h"
#include <iostream>

RouteModel::RouteModel(const std::vector<std::byte> &xml) : Model(xml) {
    int counter = 0;
    for(auto node: this->Nodes()){
        m_Nodes.push_back(Node(counter++, this, node));
    }
}