//
//  CGraph.cpp
//  JarnikPrim
//
//  Created by Dominik Plíšek on 5/20/13.
//  Copyright (c) 2013 Dominik Plíšek. All rights reserved.
//

#include "CGraph.h"
#include <iostream>

using namespace std;

ostream& operator<<(ostream& os, const CGraph & graph) {
	os << "Graph: " << endl;
	for (int i = 1; i <= graph.getNodeCounter(); ++i) {
		os << graph.getNode(i) << endl;
	}
	for (int i = 1; i <= graph.getEdgeCounter(); ++i) {
		os << graph.getEdge(i) << endl;
	}
	return os;
}

int CGraph::getEdgeCounter() const {
    return (int) edges.size();
}

t_edge& CGraph::getEdge(const int index) const {
	return *(new t_edge(edges[index - 1]));
}

void CGraph::setEdge(const int index, const t_edge& edge) {
	edges[index - 1] = edge;
}

void CGraph::addEdge(const t_edge& edge) {
    edges.push_back(edge);
}

void CGraph::deleteEdge(const int index) {
    edges.erase(edges.begin() + (index - 1));
}

int CGraph::getNodeCounter() const {
	return (int) nodes.size();
}

t_node& CGraph::getNode(const int index) const {
	return *(new t_node(nodes[index - 1]));
}

void CGraph::setNode(const int index, const t_node& node) {
    nodes[index - 1] = node;
}

void CGraph::addNode(const t_node& node) {
    nodes.push_back(node);
}