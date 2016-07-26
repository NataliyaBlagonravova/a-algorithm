#ifndef _GRAPH
#define _GRAPH

#include <cstdint>
#include <vector>
#include <set>
#include <stack>
#include <iostream>

using namespace std;

struct TPoint {
    double Longitude;
    double Lattitude;
};

struct TNeighbor {
    uint64_t Id;
    double Distance;
};

struct TNode {
    TPoint Coordinates;
    uint64_t ConnectedComponentId;
    vector<TNeighbor> Neighbors;
};


class TGraph
{
private:
    vector <TNode> Nodes;

    void DFS(uint64_t startNodeId,  uint64_t componentId, vector<bool> &vesitedNodes);
public:
    TGraph();
    TGraph(vector<TNode> &nodes);
    TGraph(const TGraph &graph);
    TNode &GetNode(uint64_t nodeId);
    uint64_t GetNodeCount();
    void FindConnectedComponents();
    bool NodesInOneConnectedComponent(uint64_t startNodeId, uint64_t finishNodeId);
};


#endif