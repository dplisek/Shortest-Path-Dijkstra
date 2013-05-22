//
//  main.cpp
//  Dijskra
//
//  Created by Dominik Plíšek on 5/21/13.
//  Copyright (c) 2013 Dominik Plíšek. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

#define INF_DIST 9999
#define NO_NODE 0


#ifndef __PROGTEST__
#include "CGraph.h"
#include "t_edge.h"
#include "t_node.h"
#endif

void initPaths(CGraph& g, const int startIndex) {
    for (int i = 1; i <= g.getNodeCounter(); ++i) {
        t_node node = g.getNode(i);
        if (i == startIndex) {
            node.distance = 0;
        } else {
            node.distance = INF_DIST;
        }
        node.predecessorIndex = NO_NODE;
        g.setNode(i, node);
    }
}

int getNearestIndex(CGraph& g, bool* processed) {
    int nearestDist = INF_DIST;
    int nearestIndex = NO_NODE;
    for (int i = 1; i <= g.getNodeCounter(); ++i) {
        if (processed[i - 1]) continue;
        if (g.getNode(i).distance < nearestDist) {
            nearestDist = g.getNode(i).distance;
            nearestIndex = i;
        }
    }
    return nearestIndex;
}

vector<int>* getAdjEdges(CGraph& g, int nodeIndex) {
    vector<int>* adjEdges = new vector<int>();
    for (int i = 1; i <= g.getEdgeCounter(); ++i) {
        t_edge edge = g.getEdge(i);
		if (edge.sourceIndex != nodeIndex) continue;
        adjEdges->push_back(i);
	}
	return adjEdges;
}

void relax(CGraph& g, int edgeIndex) {
    t_edge edge = g.getEdge(edgeIndex);
    int sourceDist = g.getNode(edge.sourceIndex).distance;
    t_node destNode = g.getNode(edge.destinationIndex);
    int destDist = destNode.distance;
    int newDestDist = sourceDist + edge.value;
    if (newDestDist >= destDist) return;
    destNode.distance = newDestDist;
    destNode.predecessorIndex = edge.sourceIndex;
    g.setNode(edge.destinationIndex, destNode);
}

void Dijskra(CGraph& g, const int startIndex) {
    initPaths(g, startIndex);
    bool* processed = new bool[g.getNodeCounter()];
    for (int i = 1; i <= g.getNodeCounter(); ++i) {
        processed[i - 1] = false;
    }
    int nearestIndex;
    while ((nearestIndex = getNearestIndex(g, processed)) != NO_NODE) {
        processed[nearestIndex - 1] = true;
        vector<int>* adjEdges = getAdjEdges(g, nearestIndex);
        for (vector<int>::iterator it = adjEdges->begin(); it != adjEdges->end(); ++it) {
            relax(g, *it);
        }
        delete adjEdges;
    }
    delete [] processed;
}

#ifndef __PROGTEST__
int main(int argc, const char * argv[]) {
    CGraph g;
    t_node node1;
    t_node node2;
    t_node node3;
    t_node node4;
    t_node node5;
    g.addNode(node1);
    g.addNode(node2);
    g.addNode(node3);
    g.addNode(node4);
    g.addNode(node5);
    t_edge edge1(1, 2, 10);
    t_edge edge2(1, 4, 5);
    t_edge edge3(2, 4, 2);
    t_edge edge4(2, 3, 1);
    t_edge edge5(3, 5, 4);
    t_edge edge6(4, 2, 3);
    t_edge edge7(4, 3, 9);
    t_edge edge8(4, 5, 2);
    t_edge edge9(5, 1, 7);
    t_edge edge10(5, 3, 6);
    g.addEdge(edge1);
    g.addEdge(edge2);
    g.addEdge(edge3);
    g.addEdge(edge4);
    g.addEdge(edge5);
    g.addEdge(edge6);
    g.addEdge(edge7);
    g.addEdge(edge8);
    g.addEdge(edge9);
    g.addEdge(edge10);
    
    Dijskra(g, 1);
    
    cout << g << endl;
    
    return 0;
}
#endif
