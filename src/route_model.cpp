#include "route_model.h"
#include <iostream>
#include <vector>
using std::vector;
RouteModel::RouteModel(const std::vector<std::byte> &xml) : Model(xml) {
    int counter = 0;
    for(auto node: this->Nodes()){
        m_Nodes.push_back(Node(counter++, this, node));
    }
    CreateNodeToRoadHashmap();
}
void RouteModel::CreateNodeToRoadHashmap(){
    for(auto &road : Roads()){
        if(road.type != Model::Road::Type::Footway){
            for(auto node_idx : Ways()[road.way].nodes){
                if(node_to_road.find(node_idx) == node_to_road.end()){
                    node_to_road[node_idx] = vector<const Model::Road*> ();
                }
                node_to_road[node_idx].push_back(&road);
            }
        }
    }
};

RouteModel::Node* RouteModel::Node::FindNeighbor(vector<int> node_indices){
    Node *closest_node = nullptr;
    Node node;
    for(int index : node_indices){
        node = parent_model->SNodes()[index];
        if(!node.visited && this->distance(node) != 0){
            if(closest_node != nullptr || this->distance(node) < this->distance(*closest_node)){
                closest_node = &parent_model->SNodes()[index];
            }
        }
    }
    return closest_node;
}
