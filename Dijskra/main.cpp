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

bool* initProcessed(CGraph& g) {
    bool* processed = new bool[g.getNodeCounter()];
    for (int i = 0; i < g.getNodeCounter(); ++i) {
        processed = false;
    }
    return processed;
}

int getNearestIndex(CGraph& g, bool* processed) {
    int nearestDist = INF_DIST;
    int nearestIndex = NO_NODE;
    for (int i = 1; i <= g.getNodeCounter(); ++i) {
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
    bool* processed = initProcessed(g);
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
int main(int argc, const char * argv[])
{
    
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
#endif
